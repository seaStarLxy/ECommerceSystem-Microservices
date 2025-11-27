// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "adapter/v2/call_data/interface/call_data.hpp"
#include <UserService/v1/user_service.grpc.pb.h>

namespace user_service::adapter::v2 {
    class RegisterCallDataManager;
    class RegisterCallData final: public CallData<proto::v1::RegisterRequest, proto::v1::RegisterResponse, RegisterCallDataManager, RegisterCallData> {
        friend RegisterCallDataManager;
    public:
        static constexpr bool kRequiresAuth = false;

        explicit RegisterCallData(RegisterCallDataManager* manager);
        ~RegisterCallData() override;
        boost::asio::awaitable<void> RunSpecificLogic([[maybe_unused]] std::string user_id);
    };
}
