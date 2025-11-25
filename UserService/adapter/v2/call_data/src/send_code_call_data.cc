// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#include "adapter/v2/call_data/include/send_code_call_data.h"
#include "adapter/v2/call_data_manager/include/send_code_call_data_manager.h"
#include "service/interface/i_auth_service.h"
#include "service/model/common_model.h"

using namespace user_service::adapter::v2;


SendCodeCallData::SendCodeCallData(SendCodeCallDataManager* manager): CallData(manager) {

}

SendCodeCallData::~SendCodeCallData() = default;

boost::asio::awaitable<void> SendCodeCallData::RunSpecificLogic() {
    SPDLOG_DEBUG("run RunLogic");
    auto* auth_service = manager_->GetBusinessService();
    const service::SendCodeRequest send_code_request(request_.phone_number(), static_cast<service::CodeUsage>(request_.usage()));
    SPDLOG_DEBUG("ready to enter coroutine");
    service::SendCodeResponse send_code_response = co_await auth_service->SendCode(send_code_request);
    SPDLOG_DEBUG("leave from coroutine");
    proto::v1::CommonStatus* status = reply_.mutable_status();
    status->set_code(static_cast<std::int32_t>(send_code_response.status.code));
    status->set_message(send_code_response.status.message);
    co_return;
}
