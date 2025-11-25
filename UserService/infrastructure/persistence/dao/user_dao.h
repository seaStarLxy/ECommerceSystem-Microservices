// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include <optional>

#include "domain/user.h"
#include "infrastructure/persistence/postgresql/include/async_connection_pool.h"

namespace user_service::infrastructure
{
    class UserDao
    {
    public:
        explicit UserDao(const std::shared_ptr<AsyncConnectionPool>& pool);
        ~UserDao();
        boost::asio::awaitable<std::optional<domain::User>> GetUserByPhoneNumber(const std::string& phone_number);
    private:
        const std::shared_ptr<AsyncConnectionPool> pool_;
    };
}