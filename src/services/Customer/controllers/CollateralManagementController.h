//
// Phase 4 — collateral-management (6 endpoints): the product-level
// collateral registry (distinct from the client-level pledges nested under
// ClientsController's {id}/collaterals/*).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CollateralManagementController : public drogon::HttpController<CollateralManagementController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/collateral-management/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CollateralManagementController::templateEndpoint, std::string(PREFIX) + "template",
                     Get, Options, FILTER);
        ADD_METHOD_TO(CollateralManagementController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(CollateralManagementController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(CollateralManagementController::getDetails,
                     std::string(PREFIX) + "get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(CollateralManagementController::update, std::string(PREFIX) + "{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(CollateralManagementController::remove, std::string(PREFIX) + "{1}/delete", Delete,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
