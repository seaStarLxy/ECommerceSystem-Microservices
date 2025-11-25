// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once

namespace user_service {
    class ICallData {
    public:
        virtual ~ICallData() = default;
        virtual void Proceed() = 0;
    };
}