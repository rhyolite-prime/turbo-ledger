//
// Phase 8 — scheduler (2 endpoints): global on/off switch for the job
// scheduler.
//
// Fineract's literal paths are a bare `GET/POST v1/scheduler` with no
// sub-path. That shape doesn't work with this codebase's gateway, whose
// route prefixes are matched as a literal string prefix including the
// trailing slash (e.g. "/api/v1/scheduler/") — a bare "/api/v1/scheduler"
// request wouldn't match. Every other controller in this codebase avoids
// that pitfall with an explicit action-suffix path (get-all/create/...);
// scheduler follows the same convention here for consistency.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SchedulerController : public drogon::HttpController<SchedulerController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/scheduler/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SchedulerController::getStatus, std::string(PREFIX) + "status", Get, Options, FILTER);
        ADD_METHOD_TO(SchedulerController::updateStatus, std::string(PREFIX) + "update", Post, Options,
                     FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getStatus(HttpRequestPtr req);
    Task<HttpResponsePtr> updateStatus(HttpRequestPtr req);
};
