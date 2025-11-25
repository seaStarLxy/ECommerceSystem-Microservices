// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#include "adapter/v2/call_data/include/register_call_data.h"
#include "adapter/v2/call_data_manager/include/register_call_data_manager.h"
#include "service/interface/i_basic_user_service.h"

using namespace user_service::adapter::v2;


RegisterCallData::RegisterCallData(RegisterCallDataManager* manager): CallData(manager) {

}

RegisterCallData::~RegisterCallData() = default;

boost::asio::awaitable<void> RegisterCallData::RunSpecificLogic() {
    SPDLOG_DEBUG("run RunLogic");
    auto* basic_user_service = manager_->GetBusinessService();
    const service::RegisterRequest register_request(request_.username(), request_.password(),
        request_.phone_number(), request_.code());
    SPDLOG_DEBUG("ready to enter coroutine");
    service::RegisterResponse register_response = co_await basic_user_service->Register(register_request);
    SPDLOG_DEBUG("leave from coroutine");
    proto::v1::CommonStatus* status = reply_.mutable_status();
    status->set_code(static_cast<std::int32_t>(register_response.status.code));
    status->set_message(register_response.status.message);
    reply_.set_user_id(register_response.user_id);
    co_return;
}
