//
// Phase 2 — currencies (2 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CurrenciesController : public drogon::HttpController<CurrenciesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/currencies/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CurrenciesController::get,    std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CurrenciesController::update, std::string(PREFIX) + "update", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> get(HttpRequestPtr req);
    Task<HttpResponsePtr> update(HttpRequestPtr req);
};
