// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include <string>

namespace user_service::util {
    class IVerificationCodeGenerator {
    public:
        virtual ~IVerificationCodeGenerator() = default;
        virtual std::string Generate(int length) = 0;
    };
}