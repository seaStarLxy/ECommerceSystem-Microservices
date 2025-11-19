// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#include "infrastructure/persistence/dao/user_dao.h"
#include <spdlog/spdlog.h>

using namespace user_service::infrastructure;
using namespace user_service::domain;

UserDao::UserDao(const std::shared_ptr<AsyncConnectionPool>& pool): pool_(pool) {

}

UserDao::~UserDao() = default;

boost::asio::awaitable<std::optional<User>> UserDao::GetUserByPhoneNumber(const std::string& phone_number)
{

}