//
// Phase 2 — funds (4 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class FundsController : public drogon::HttpController<FundsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/funds/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(FundsController::getAll,     std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(FundsController::create,     std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(FundsController::getDetails, std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(FundsController::update,     std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
};
