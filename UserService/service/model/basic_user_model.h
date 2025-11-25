// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include "service/model/common_model.h"
#include <string>

namespace user_service::service {
    // 注册
    struct RegisterRequest {
        std::string username;
        std::string password;
        std::string phone_number;
        std::string code;
    };

    struct RegisterResponse {
        CommonStatus status;
        std::string user_id;
    };

    // 获取信息
    struct GetUserInfoRequest {
        std::string user_id;
    };
    struct GetUserInfoResponse {
        CommonStatus status;
        std::string user_id;
        std::string username;
        std::string email;
        std::string avatar_url;
    };

    // 更新信息
    struct UpdateUserInfoRequest {
        std::string username;
        std::string email;
        std::string avatar_url;
    };

    struct UpdateUserInfoResponse {
        CommonStatus status;
    };
}

