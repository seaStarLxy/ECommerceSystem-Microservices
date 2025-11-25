// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#include "domain/user.h"

using namespace user_service::domain;

void User::ChangePassword(const std::string& new_hash, const std::string& new_salt) {
    if (new_hash.empty() || new_salt.empty()) {
        throw std::invalid_argument("Hash and salt cannot be empty");
    }
    password_hash_ = new_hash;
    salt_ = new_salt;
}

void User::UpdateProfile(std::optional<std::string> username,
                   std::optional<std::string> email,
                   std::optional<std::string> avatar_url) {
    if (username.has_value()) username_ = username;
    if (email.has_value()) email_ = email;
    if (avatar_url.has_value()) avatar_url_ = avatar_url;
}

void User::MarkAsDeleted() {
    status_ = UserStatus::DELETED;
    deleted_at_ = std::chrono::system_clock::now();
}