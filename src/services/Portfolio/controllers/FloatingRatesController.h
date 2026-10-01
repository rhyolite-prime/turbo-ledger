//
// Phase 6 — floatingrates (4 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class FloatingRatesController : public drogon::HttpController<FloatingRatesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/floatingrates/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(FloatingRatesController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(FloatingRatesController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(FloatingRatesController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(FloatingRatesController::update, std::string(PREFIX) + "{1}/update", Put, Options,
                     FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
};
