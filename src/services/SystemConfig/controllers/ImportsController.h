//
// Phase 2 — imports (3 endpoints, bulk Excel/CSV import scaffolding).
// Actual file-based bulk import (upload/parse/apply) is out of Phase 2 scope
// and deferred like Organization's offices/uploadtemplate — see
// downloadOutputTemplate below.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ImportsController : public drogon::HttpController<ImportsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/imports/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ImportsController::getAll,                  std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ImportsController::downloadOutputTemplate,  std::string(PREFIX) + "downloadOutputTemplate", Get, Options, FILTER);
        ADD_METHOD_TO(ImportsController::getOutputTemplateLocation, std::string(PREFIX) + "getOutputTemplateLocation", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> downloadOutputTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getOutputTemplateLocation(HttpRequestPtr req);
};
