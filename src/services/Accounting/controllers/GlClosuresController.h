//
// Phase 3 — glclosures (5 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GlClosuresController : public drogon::HttpController<GlClosuresController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/glclosures/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(GlClosuresController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(GlClosuresController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(GlClosuresController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(GlClosuresController::update, std::string(PREFIX) + "{1}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(GlClosuresController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
