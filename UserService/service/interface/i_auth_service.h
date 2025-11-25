// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "../model/auth_model.h"
#include <boost/asio.hpp>

namespace user_service::service {

    class IAuthService {
    public:
        virtual ~IAuthService() = default;
        virtual boost::asio::awaitable<SendCodeResponse> SendCode(const SendCodeRequest&) = 0;
        virtual boost::asio::awaitable<LoginResult> LoginByCode(const LoginByCodeRequest&) = 0;
        virtual boost::asio::awaitable<LoginResult> LoginByPassword(const LoginByPasswordRequest&) = 0;
    };
}