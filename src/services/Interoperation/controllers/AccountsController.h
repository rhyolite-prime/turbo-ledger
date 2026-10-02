//
// Phase 9 — interoperation/accounts/* (3 endpoints: genuine composition with
// Portfolio/DepositAccountManagement — see InteroperationService.h).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class InteropAccountsController : public drogon::HttpController<InteropAccountsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/interoperation/accounts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(InteropAccountsController::getAccount, std::string(PREFIX) + "{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(InteropAccountsController::transactions,
                     std::string(PREFIX) + "{1}/transactions", Get, Options, FILTER);
        ADD_METHOD_TO(InteropAccountsController::transactionDetail,
                     std::string(PREFIX) + "{1}/transactions/{2}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAccount(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactions(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactionDetail(HttpRequestPtr req, std::string accountId,
                                            std::string transactionId);
};
