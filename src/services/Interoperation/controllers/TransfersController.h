//
// Phase 9 — interoperation/transfers* (3 endpoints: PREPARE / COMMIT|ABORT /
// get, local genuinely-computed workflow state — see InteroperationService.h).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TransfersController : public drogon::HttpController<TransfersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/interoperation/transfers";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(TransfersController::prepare, std::string(PREFIX), Post, Options, FILTER);
        ADD_METHOD_TO(TransfersController::action, std::string(PREFIX) + "/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(TransfersController::get, std::string(PREFIX) + "/{1}/{2}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> prepare(HttpRequestPtr req);
    Task<HttpResponsePtr> action(HttpRequestPtr req, std::string transactionCode);
    Task<HttpResponsePtr> get(HttpRequestPtr req, std::string transactionCode, std::string transferCode);
};
