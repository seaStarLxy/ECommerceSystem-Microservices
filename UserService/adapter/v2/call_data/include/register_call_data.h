// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#pragma once
#include "adapter/v2/call_data/interface/call_data.hpp"
#include <UserService/v1/user_service.grpc.pb.h>

namespace user_service::adapter::v2 {
    class RegisterCallDataManager;
    class RegisterCallData final: public CallData<proto::v1::RegisterRequest, proto::v1::RegisterResponse, RegisterCallDataManager, RegisterCallData> {
        friend RegisterCallDataManager;
    public:
        explicit RegisterCallData(RegisterCallDataManager* manager);
        ~RegisterCallData() override;
        boost::asio::awaitable<void> RunSpecificLogic();
    };
}
