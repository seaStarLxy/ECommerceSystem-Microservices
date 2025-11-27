// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "adapter/v2/call_data_manager/interface/call_data_manager.hpp"
#include "service/interface/i_basic_user_service.h"

namespace user_service::adapter::v2 {
    class RegisterCallData;
    class RegisterCallDataManager final: public CallDataManager<proto::v1::UserService::AsyncService, RegisterCallData, service::IBasicUserService, RegisterCallDataManager> {
        friend RegisterCallData;
    public:
        RegisterCallDataManager(size_t initial_size, proto::v1::UserService::AsyncService* grpc_service,
            service::IBasicUserService* business_service, util::IJwtUtil* jwt_util,
            const std::shared_ptr<boost::asio::io_context>& ioc, grpc::ServerCompletionQueue *cq);

        ~RegisterCallDataManager() override;

        void SpecificRegisterCallDataToCQ(RegisterCallData* call_data) const;
    };
}