// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "domain/interface/i_user_repository.h"
#include "infrastructure/persistence/dao/user_dao.h"
#include "infrastructure/state_storage/redis_dao/redis_client.h"

namespace user_service::infrastructure {
    class UserRepository final : public domain::IUserRepository {
    public:
        explicit UserRepository(const std::shared_ptr<UserDao>& user_dao, const std::shared_ptr<RedisClient>& redis_client);
        ~UserRepository() override;
        boost::asio::awaitable<std::expected<void, DbError>> CreateUser(const domain::User& user) override;
        boost::asio::awaitable<std::expected<std::optional<domain::User>, DbError>> GetUserById(const std::string& id) override;
        boost::asio::awaitable<std::expected<std::optional<domain::User>, DbError>> GetUserByPhoneNumber(const std::string& phoneNumber) override;
    private:
        const std::shared_ptr<UserDao> user_dao_;
        const std::shared_ptr<RedisClient> redis_client_;
    };
}
