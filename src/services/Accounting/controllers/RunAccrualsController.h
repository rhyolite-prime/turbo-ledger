//
// Phase 3 — runaccruals (1 endpoint).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RunAccrualsController : public drogon::HttpController<RunAccrualsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/runaccruals/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RunAccrualsController::run, std::string(PREFIX) + "run", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> run(HttpRequestPtr req);
};
