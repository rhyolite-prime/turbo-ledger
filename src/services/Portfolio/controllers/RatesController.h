//
// Phase 6 — rates (4 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RatesController : public drogon::HttpController<RatesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/rates/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RatesController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(RatesController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(RatesController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(RatesController::update, std::string(PREFIX) + "{1}/update", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
};
