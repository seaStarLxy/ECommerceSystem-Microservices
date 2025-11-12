// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#pragma once
#include "adapter/v2/call_data/interface/i_call_data.h"
#include "adapter/v2/call_data_manager/interface/call_data_manager.hpp"
#include <boost/asio/co_spawn.hpp>
#include <spdlog/spdlog.h>
#include <grpcpp/grpcpp.h>

namespace user_service::adapter::v2 {

    // template<typename T>
    // concept HadSpecificLogic = requires(T& derived) {
    //     // requires 语句检查：
    //     // 1. 是否存在一个名为 RunSpecificLogic 的成员函数
    //     // 2. 它被调用时，返回的类型是否与 boost::asio::awaitable<void> 相同
    //     { derived.RunSpecificLogic() } -> std::same_as<boost::asio::awaitable<void>>;
    // };

    /*
     * 特定类型的 CallData 的公共部分，即：让编译器替我生成每个接口对应的CallData。
     * 但是每个CallData都有不一样的地方，不一样的地方再继承一个子类重写
     */
    template<typename RequestType, typename ResponseType, typename ManagerType, typename SpecificCallDataType>
    class CallData : public ICallData {
        // template<typename GrpcServiceType, typename CallDataType, typename BusinessServiceType, typename Derived>
        // friend class CallDataManager;
    public:
        explicit CallData(ManagerType* manager) : manager_(manager), responder_(&ctx_) {
        }

        ~CallData() override = default;

        void Proceed() override {
            switch (status_) {
                case State::WAIT_PROCESSING:
                    HandleProcess();
                    break;
                case State::FINISHED:
                    HandleFinish();
                    break;
            }
        }

        void HandleProcess() {
            /*
             * 2个陷阱：
             *  1.状态改变不能由 asio线程 执行，必须是工作线程
             *      指令重排列会打乱顺序，他只保证单线程内结果正确，由于改变 status 和 触发放回CQ 单线程内不相干，所以可能指令重排列
             *  2.状态改变需要放在启动协程前
             *      要保证 asio线程 触发放回 CQ 发生前，status 的状态被改为 finish
             */
            // 这里的status_更新实际上是一个预处理，为了线程安全，必须要先改状态再进行业务逻辑
            status_ = State::FINISHED;
            SPDLOG_DEBUG("start register coroutine");

            boost::asio::co_spawn(manager_->GetIOContext(),
                                  [this] { return RunLogic(); },
                                  [this](std::exception_ptr e) { OnLogicFinished(e); }
            );
        }

        void HandleFinish() {
            // 只有处于 WAIT_PROCESSING 状态的 CallData，proceed驱动的时候switch才会跳转执行业务逻辑
            status_ = State::WAIT_PROCESSING;
            Reset();
            // 通过管理器，把自己重新注册给 CQ
            manager_->RegisterCallDataToCQ(static_cast<SpecificCallDataType*>(this));
        }

        void Reset() {
            // ctx不支持复制运算符，只能出此下策
            ctx_.~ServerContext();
            new(&ctx_) grpc::ServerContext();
            // 绑定的不变的成员地址 &ctx_（这里只是为了获取新的responder）
            responder_ = grpc::ServerAsyncResponseWriter<ResponseType>(&ctx_);
            // 重置回复，防止数据泄露
            reply_ = ResponseType();
            // 重置请求，释放内存
            request_ = RequestType();
        }

        boost::asio::awaitable<void> RunLogic() {
            SpecificCallDataType* derived_this = static_cast<SpecificCallDataType*>(this);
            co_await derived_this->RunSpecificLogic();
        }
        // 具体的业务逻辑需要子类重写
        // virtual boost::asio::awaitable<void> RunLogic() = 0;

        // 业务逻辑完成，注册回 CQ
        void OnLogicFinished(std::exception_ptr e) {
            grpc::Status status;
            if (e) {
                std::string error_message = "Internal server error";
                try {
                    std::rethrow_exception(e);
                } catch (const std::exception &ex) {
                    error_message = ex.what();
                    SPDLOG_ERROR("Coroutine finished with error: {}", error_message);
                } catch (...) {
                    error_message = "Unknown exception type";
                    SPDLOG_ERROR("Coroutine finished with non-standard exception.");
                }
                status = grpc::Status(grpc::StatusCode::INTERNAL, error_message);
            } else {
                // 协程成功完成
                SPDLOG_DEBUG("Coroutine finished successfully");
                status = grpc::Status::OK;
            }
            // 调用 Finish 就是把自己放回 CQ
            responder_.Finish(reply_, status, this);
        }

    protected:
        ManagerType* manager_;
        RequestType request_;
        ResponseType reply_;
        grpc::ServerContext ctx_;
        grpc::ServerAsyncResponseWriter<ResponseType> responder_;
    };
}
