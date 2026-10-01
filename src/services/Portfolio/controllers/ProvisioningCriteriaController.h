//
// Phase 6 — provisioningcriteria (6 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ProvisioningCriteriaController : public drogon::HttpController<ProvisioningCriteriaController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/provisioningcriteria/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ProvisioningCriteriaController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ProvisioningCriteriaController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(ProvisioningCriteriaController::getDetails,
                     std::string(PREFIX) + "get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(ProvisioningCriteriaController::update, std::string(PREFIX) + "{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(ProvisioningCriteriaController::remove, std::string(PREFIX) + "{1}/delete", Delete,
                     Options, FILTER);
        ADD_METHOD_TO(ProvisioningCriteriaController::templateEndpoint, std::string(PREFIX) + "template",
                     Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
};
