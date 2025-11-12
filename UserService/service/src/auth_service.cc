// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#include "../include/auth_service.h"
#include <spdlog/spdlog.h>

using namespace user_service::service;

AuthService::AuthService() {

}

AuthService::~AuthService() = default;

boost::asio::awaitable<SendCodeResponse> AuthService::SendCode(const SendCodeRequest& send_code_request) {
    SPDLOG_DEBUG("send a code to {}", send_code_request.phone_number);
    co_return SendCodeResponse(true);
}

boost::asio::awaitable<LoginResult> AuthService::LoginByCode(const LoginByCodeRequest&) {

}

boost::asio::awaitable<LoginResult> AuthService::LoginByPassword(const LoginByCodeRequest&) {

}