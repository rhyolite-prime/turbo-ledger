//
// Phase 6 — provisioningcategory (4 endpoints). No delete-by-get-detail
// endpoint in Fineract's inventory here; category has no standalone get.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ProvisioningCategoryController : public drogon::HttpController<ProvisioningCategoryController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/provisioningcategory/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ProvisioningCategoryController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ProvisioningCategoryController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(ProvisioningCategoryController::update, std::string(PREFIX) + "{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(ProvisioningCategoryController::remove, std::string(PREFIX) + "{1}/delete", Delete,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
