//
// Phase 2 — audits (3, read-only endpoints reading this service's own
// tl_outbox as a local audit trail; see SystemConfigService.h for the scope
// note). All routes require the gateway-signed TL-Context.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AuditsController : public drogon::HttpController<AuditsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/audits/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(AuditsController::getAll,           std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(AuditsController::getSearchTemplate, std::string(PREFIX) + "searchtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(AuditsController::getDetails,       std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> getSearchTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
};
