// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

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
    reply_.set_user_id(register_response.user_id);
    reply_.set_token(register_response.token);
    co_return;
}
