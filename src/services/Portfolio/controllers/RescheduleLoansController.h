//
// Phase 6 — rescheduleloans (5 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RescheduleLoansController : public drogon::HttpController<RescheduleLoansController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/rescheduleloans/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RescheduleLoansController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(RescheduleLoansController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(RescheduleLoansController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(RescheduleLoansController::command, std::string(PREFIX) + "{1}/command/{2}", Post,
                     Options, FILTER);
        ADD_METHOD_TO(RescheduleLoansController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string id, std::string cmd);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
};
