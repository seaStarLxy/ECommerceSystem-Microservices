// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "adapter/v2/call_data_manager/interface/i_call_data_manager.h"
#include <UserService/v1/user_service.grpc.pb.h>
#include <type_traits> // for std::is_base_of
#include <vector>
#include <memory>
#include <grpcpp/completion_queue.h>
#include <boost/asio/io_context.hpp>


namespace user_service::adapter::v2 {

    template<typename T, typename SpecificCallDataType>
    concept HasSpecificRegisterCallDataToCQ = requires(T& derived) {
        /*
         * 1. std::declval 表示假设传入一个值
         * 2. 返回必须是 std::same_as 代表不能是强转出来的 void
         */
        { derived.SpecificRegisterCallDataToCQ(std::declval<SpecificCallDataType*>()) } -> std::same_as<void>;
    };

    // 每种特定类型的 CallData 对应一个 Manager
    template<typename GrpcServiceType, typename CallDataType, typename BusinessServiceType, typename SpecificCallDataManagerType>
    class CallDataManager: public ICallDataManager {
    public:
        CallDataManager(const size_t initial_size, GrpcServiceType* grpc_service, BusinessServiceType* business_service,
            const std::shared_ptr<boost::asio::io_context>& ioc, grpc::ServerCompletionQueue *cq):
            ICallDataManager(initial_size, ioc, cq), grpc_service_(grpc_service), business_service_(business_service) {
            static_assert(std::is_base_of_v<ICallData, CallDataType>, "CallDataType must derive from ICallData");

            if (!grpc_service_) {
                throw std::invalid_argument("Service and CQ cannot be null.");
            }
        }

        ~CallDataManager() override = default;

        void Start() {
            // 初始化 call data
            for (size_t i = 0; i < initial_size_; ++i) {
                auto derived_this = static_cast<SpecificCallDataManagerType*>(this);
                auto call_data = std::make_unique<CallDataType>(derived_this);
                RegisterCallDataToCQ(call_data.get());
                pool_.push_back(std::move(call_data));
            }
        }

        void RegisterCallDataToCQ(CallDataType* call_data) requires HasSpecificRegisterCallDataToCQ<SpecificCallDataManagerType, CallDataType> {
            // 利用 CRTP 实现静态多态 （需要保证子类有 SpecificRegisterCallDataToCQ 方法）
            auto specific_call_data_manager = static_cast<SpecificCallDataManagerType*>(this);
            specific_call_data_manager->SpecificRegisterCallDataToCQ(call_data);
        }
        // 此处为利用动态多态实现，为提高性能，采用上面的静态多态
        // virtual void SpecificRegisterCallDataToCQ(CallDataType* call_data) = 0;

        BusinessServiceType* GetBusinessService() {
            return business_service_;
        }
    protected:
        GrpcServiceType * grpc_service_;
        BusinessServiceType * business_service_;
        std::vector<std::unique_ptr<CallDataType>> pool_;
    };
}
