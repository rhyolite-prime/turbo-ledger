//
// Phase 2 — offices (9 endpoints). All routes require the gateway-signed
// TL-Context (turbo::TrustedContextFilter).
//
// Note: routes follow the RPC-style convention established in Identity's
// Phase 1 controllers (literal action segments rather than a bare `{id}`
// sharing a path level with literal siblings) rather than Fineract's exact
// REST paths — see README "Conventions" / compat-notes.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class OfficeController : public drogon::HttpController<OfficeController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/offices/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(OfficeController::getOffices,        std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(OfficeController::getTemplate,        std::string(PREFIX) + "template", Get, Options, FILTER);
        ADD_METHOD_TO(OfficeController::downloadTemplate,   std::string(PREFIX) + "downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(OfficeController::uploadTemplate,     std::string(PREFIX) + "uploadtemplate", Post, Options, FILTER);
        ADD_METHOD_TO(OfficeController::createOffice,       std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(OfficeController::getByExternalId,    std::string(PREFIX) + "external-id/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(OfficeController::updateByExternalId, std::string(PREFIX) + "external-id/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(OfficeController::getDetails,         std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(OfficeController::updateOffice,       std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getOffices(HttpRequestPtr req);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> downloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> uploadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> createOffice(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> updateOffice(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> getByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> updateByExternalId(HttpRequestPtr req, std::string externalId);
};
