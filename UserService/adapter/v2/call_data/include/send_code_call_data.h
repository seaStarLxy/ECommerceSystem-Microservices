// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#pragma once
#include "adapter/v2/call_data/interface/call_data.hpp"
#include <UserService/v1/user_service.grpc.pb.h>

namespace user_service::adapter::v2 {
    class SendCodeCallDataManager;
    class SendCodeCallData final: public CallData<proto::v1::SendCodeRequest, proto::v1::SendCodeResponse, SendCodeCallDataManager, SendCodeCallData> {
        friend SendCodeCallDataManager;
    public:
        explicit SendCodeCallData(SendCodeCallDataManager* manager);
        ~SendCodeCallData() override;
        boost::asio::awaitable<void> RunSpecificLogic();
    };
}