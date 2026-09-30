//
// Phase 2 — generic entity-to-entity mapping (6 endpoints). New in Phase 2 —
// did not exist in the legacy service tree.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EntityToEntityMappingController
    : public drogon::HttpController<EntityToEntityMappingController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/entity-to-entity-mapping/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(EntityToEntityMappingController::getAll,     std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(EntityToEntityMappingController::query,      std::string(PREFIX) + "query", Get, Options, FILTER);
        ADD_METHOD_TO(EntityToEntityMappingController::getDetails, std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(EntityToEntityMappingController::create,     std::string(PREFIX) + "create/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(EntityToEntityMappingController::update,     std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(EntityToEntityMappingController::remove,     std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> query(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string relationId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
