//
// Phase 9 — interoperation/disburse*, interoperation/loanrepayment (3
// endpoints: genuine composition with Portfolio — see InteroperationService.h).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class DisbursementController : public drogon::HttpController<DisbursementController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/interoperation/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(DisbursementController::disburse, std::string(PREFIX) + "disburse/{1}", Post,
                     Options, FILTER);
        ADD_METHOD_TO(DisbursementController::disburseTransfer,
                     std::string(PREFIX) + "disburse/{1}/transfer", Post, Options, FILTER);
        ADD_METHOD_TO(DisbursementController::loanRepayment,
                     std::string(PREFIX) + "loanrepayment/{1}", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> disburse(HttpRequestPtr req, std::string transactionCode);
    Task<HttpResponsePtr> disburseTransfer(HttpRequestPtr req, std::string transactionCode);
    Task<HttpResponsePtr> loanRepayment(HttpRequestPtr req, std::string transactionCode);
};
