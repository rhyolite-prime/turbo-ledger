//
// Phase 2 — field configuration (1 endpoint).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class FieldConfigurationController : public drogon::HttpController<FieldConfigurationController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/fieldconfiguration/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(FieldConfigurationController::getDetails, std::string(PREFIX) + "{1}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string entity);
};
