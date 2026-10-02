//
// Phase 3 — provisioningentries (5 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ProvisioningEntriesController : public drogon::HttpController<ProvisioningEntriesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/provisioningentries/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ProvisioningEntriesController::getAll, std::string(PREFIX) + "get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ProvisioningEntriesController::create, std::string(PREFIX) + "create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(ProvisioningEntriesController::getDetails, std::string(PREFIX) + "get-detail/{1}",
                     Get, Options, FILTER);
        ADD_METHOD_TO(ProvisioningEntriesController::recreate, std::string(PREFIX) + "{1}/recreate", Post,
                     Options, FILTER);
        ADD_METHOD_TO(ProvisioningEntriesController::entries, std::string(PREFIX) + "entries", Get,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> recreate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> entries(HttpRequestPtr req);
};
