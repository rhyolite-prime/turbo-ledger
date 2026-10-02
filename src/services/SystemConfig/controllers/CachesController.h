//
// Phase 2 — caches (2 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CachesController : public drogon::HttpController<CachesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/caches/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CachesController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CachesController::update, std::string(PREFIX) + "update", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> update(HttpRequestPtr req);
};
