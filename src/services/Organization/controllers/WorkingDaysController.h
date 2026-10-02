//
// Phase 2 — working days (3 endpoints, singleton config).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class WorkingDaysController : public drogon::HttpController<WorkingDaysController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/workingdays/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(WorkingDaysController::get,          std::string(PREFIX) + "get", Get, Options, FILTER);
        ADD_METHOD_TO(WorkingDaysController::getTemplate,  std::string(PREFIX) + "template", Get, Options, FILTER);
        ADD_METHOD_TO(WorkingDaysController::update,       std::string(PREFIX) + "update", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> get(HttpRequestPtr req);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> update(HttpRequestPtr req);
};
