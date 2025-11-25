// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "service/model/auth_model.h"
#include <boost/asio.hpp>
#include <optional>
#include "domain/user.h"

namespace user_service::domain
{
    class IUserRepository
    {
    public:
        virtual ~IUserRepository() = default;
        virtual boost::asio::awaitable<User> GetUserByPhoneNumber(const std::string& phoneNumber) = 0;
    };
}
