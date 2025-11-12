// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#include "../include/send_code_call_data.h"
#include "service/interface/i_auth_service.h"

using namespace user_service::adapter::v2;

SendCodeCallData::SendCodeCallData(ICallDataManager* manager): ICallData(manager) {

}
SendCodeCallData::~SendCodeCallData() = default;

boost::asio::awaitable<void> SendCodeCallData::RunLogic() {
    SPDLOG_DEBUG("run RunLogic");
    auto* auth_service = static_cast<service::IAuthService*>(manager_->GetBusinessService());
    const service::SendCodeRequest send_code_request(request_.phone_number(), static_cast<service::CodeUsage>(request_.usage()));
    SPDLOG_DEBUG("ready to enter coroutine");
    service::SendCodeResponse register_response = co_await auth_service->SendCode(send_code_request);
    SPDLOG_DEBUG("leave from coroutine");
    reply_.set_status(register_response.status);
    co_return;
}