//
// Phase 2 — generic entity documents (6 endpoints).
//
// Deliberate deviation from Fineract's literal top-level `{entityType}/{entityId}/documents`
// paths: SystemConfig doesn't own top-level segments like `clients/` or `loans/`
// (owned by future Customer/Portfolio services), so this uses a distinct
// `entity-documents/` prefix with {entityType}/{entityId} as the first path
// params. See SystemConfigService.h header comment for the full rationale.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EntityDocumentsController : public drogon::HttpController<EntityDocumentsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/entity-documents/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(EntityDocumentsController::getAll,     std::string(PREFIX) + "{1}/{2}/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(EntityDocumentsController::create,     std::string(PREFIX) + "{1}/{2}/create", Post, Options, FILTER);
        ADD_METHOD_TO(EntityDocumentsController::getDetails, std::string(PREFIX) + "{1}/{2}/get-details/{3}", Get, Options, FILTER);
        ADD_METHOD_TO(EntityDocumentsController::update,     std::string(PREFIX) + "{1}/{2}/update/{3}", Put, Options, FILTER);
        ADD_METHOD_TO(EntityDocumentsController::remove,     std::string(PREFIX) + "{1}/{2}/delete/{3}", Delete, Options, FILTER);
        ADD_METHOD_TO(EntityDocumentsController::getAttachment, std::string(PREFIX) + "{1}/{2}/attachment/{3}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string entityType, std::string entityId,
                                     std::string documentId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string entityType, std::string entityId,
                                 std::string documentId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string entityType, std::string entityId,
                                 std::string documentId);
    Task<HttpResponsePtr> getAttachment(HttpRequestPtr req, std::string entityType, std::string entityId,
                                        std::string documentId);
};
