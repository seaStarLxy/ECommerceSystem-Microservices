// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#pragma once
#include "adapter/v2/call_data_manager/interface/call_data_manager.hpp"
#include "adapter/v2/call_data/include/register_call_data.h"
#include "service/interface/i_basic_user_service.h"

namespace user_service::adapter::v2 {
    class RegisterCallDataManager final: public CallDataManager<proto::v1::UserService::AsyncService, RegisterCallData, service::IBasicUserService, RegisterCallDataManager> {
    public:
        RegisterCallDataManager(const size_t initial_size, proto::v1::UserService::AsyncService* grpc_service,
            service::IBasicUserService* business_service, const std::shared_ptr<boost::asio::io_context>& ioc,
            grpc::ServerCompletionQueue *cq);

        ~RegisterCallDataManager() override;

        void SpecificRegisterCallDataToCQ(RegisterCallData* call_data) const;
    };
}