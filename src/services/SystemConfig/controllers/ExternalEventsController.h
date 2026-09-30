//
// Phase 2 — external events configuration (2 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ExternalEventsController : public drogon::HttpController<ExternalEventsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/externalevents/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ExternalEventsController::getConfiguration, std::string(PREFIX) + "configuration", Get, Options, FILTER);
        ADD_METHOD_TO(ExternalEventsController::updateConfiguration, std::string(PREFIX) + "configuration", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getConfiguration(HttpRequestPtr req);
    Task<HttpResponsePtr> updateConfiguration(HttpRequestPtr req);
};
