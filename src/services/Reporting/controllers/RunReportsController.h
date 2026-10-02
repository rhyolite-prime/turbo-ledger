//
// Phase 8 — generic report execution endpoint (Fineract's `runreports`).
// Report parameter values are supplied as ordinary query-string parameters,
// e.g. GET /api/v1/runreports/{id}?asOfDate=2026-09-30
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RunReportsController : public drogon::HttpController<RunReportsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/runreports/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RunReportsController::run, std::string(PREFIX) + "{1}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> run(HttpRequestPtr req, std::string id);
};
