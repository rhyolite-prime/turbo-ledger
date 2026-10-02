//
// Phase 2 — tax components & tax groups (10 endpoints). New in Phase 2 — did
// not exist in the legacy service tree.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TaxesController : public drogon::HttpController<TaxesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/taxes/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(TaxesController::getAllComponents,    std::string(PREFIX) + "tax-components/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(TaxesController::getComponentTemplate,std::string(PREFIX) + "tax-components/template", Get, Options, FILTER);
        ADD_METHOD_TO(TaxesController::getComponentDetails, std::string(PREFIX) + "tax-components/get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(TaxesController::createComponent,     std::string(PREFIX) + "tax-components/create", Post, Options, FILTER);
        ADD_METHOD_TO(TaxesController::updateComponent,     std::string(PREFIX) + "tax-components/update/{1}", Put, Options, FILTER);

        ADD_METHOD_TO(TaxesController::getAllGroups,        std::string(PREFIX) + "tax-groups/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(TaxesController::getGroupTemplate,    std::string(PREFIX) + "tax-groups/template", Get, Options, FILTER);
        ADD_METHOD_TO(TaxesController::getGroupDetails,     std::string(PREFIX) + "tax-groups/get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(TaxesController::createGroup,         std::string(PREFIX) + "tax-groups/create", Post, Options, FILTER);
        ADD_METHOD_TO(TaxesController::updateGroup,         std::string(PREFIX) + "tax-groups/update/{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAllComponents(HttpRequestPtr req);
    Task<HttpResponsePtr> getComponentTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getComponentDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createComponent(HttpRequestPtr req);
    Task<HttpResponsePtr> updateComponent(HttpRequestPtr req, std::string id);

    Task<HttpResponsePtr> getAllGroups(HttpRequestPtr req);
    Task<HttpResponsePtr> getGroupTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getGroupDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createGroup(HttpRequestPtr req);
    Task<HttpResponsePtr> updateGroup(HttpRequestPtr req, std::string id);
};
