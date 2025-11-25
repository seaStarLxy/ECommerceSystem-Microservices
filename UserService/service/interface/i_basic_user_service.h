// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "../model/basic_user_model.h"
#include <boost/asio.hpp>

namespace user_service::service {
    class IBasicUserService {
    public:
        virtual ~IBasicUserService() = default;
        virtual boost::asio::awaitable<RegisterResponse> Register(const RegisterRequest&) = 0;
        virtual boost::asio::awaitable<GetUserInfoResponse> GetUserInfo(const GetUserInfoRequest&) = 0;
        virtual boost::asio::awaitable<UpdateUserInfoResponse> UpdateUserInfo(const UpdateUserInfoRequest&) = 0;
    };
}