//
// Phase 2 — external service configuration (2 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ExternalServiceController : public drogon::HttpController<ExternalServiceController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/externalservice/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ExternalServiceController::getDetails, std::string(PREFIX) + "{1}", Get, Options, FILTER);
        ADD_METHOD_TO(ExternalServiceController::update,     std::string(PREFIX) + "{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string name);
};
