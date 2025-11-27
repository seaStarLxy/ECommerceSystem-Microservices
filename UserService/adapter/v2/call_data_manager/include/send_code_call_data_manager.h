// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "adapter/v2/call_data_manager/interface/call_data_manager.hpp"
#include "service/interface/i_auth_service.h"

namespace user_service::adapter::v2 {
    class SendCodeCallData;
    class SendCodeCallDataManager final: public CallDataManager<proto::v1::AuthService::AsyncService, SendCodeCallData, service::IAuthService, SendCodeCallDataManager> {
        friend SendCodeCallData;
    public:
        SendCodeCallDataManager(size_t initial_size, proto::v1::AuthService::AsyncService* grpc_service,
            service::IAuthService* business_service, util::IJwtUtil* jwt_util,
            const std::shared_ptr<boost::asio::io_context>& ioc, grpc::ServerCompletionQueue *cq);

        ~SendCodeCallDataManager() override;

        void SpecificRegisterCallDataToCQ(SendCodeCallData* call_data) const;
    };
}