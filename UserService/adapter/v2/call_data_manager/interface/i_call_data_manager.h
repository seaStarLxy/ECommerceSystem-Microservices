// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#pragma once
#include <memory>
#include <UserService/v1/user_service.grpc.pb.h>
#include <grpcpp/completion_queue.h>
#include <boost/asio/io_context.hpp>

namespace user_service::adapter::v2 {
    // ICallData 定义文件包含了该文件，这里使用前向声明更多是为了防止嵌套包含
    class ICallData;
    // 提供 manager 统一接口
    class ICallDataManager {
    public:
        ICallDataManager(const size_t initiate_size, const std::shared_ptr<boost::asio::io_context>& ioc, grpc::ServerCompletionQueue * cq):
            initial_size_(initiate_size), ioc_(ioc), cq_(cq) {
            if (!cq_) {
                throw std::invalid_argument("CQ cannot be null.");
            }
        }
        virtual ~ICallDataManager() = default;
        // 调用了这个函数就一定要用他的结果（编译期保证）
        [[nodiscard]] boost::asio::io_context& GetIOContext() const {
            return *ioc_;
        }
    protected:
        size_t initial_size_;
        std::shared_ptr<boost::asio::io_context> ioc_;
        grpc::ServerCompletionQueue *cq_;
    };

}
