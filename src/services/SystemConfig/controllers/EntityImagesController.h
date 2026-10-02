//
// Phase 2 — generic entity images (4 endpoints, singleton per entity).
// Distinct `entity-images/` prefix — see EntityDocumentsController.h for the
// routing-convention note. POST and PUT both upsert (putImage).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EntityImagesController : public drogon::HttpController<EntityImagesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/entity-images/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(EntityImagesController::get,    std::string(PREFIX) + "{1}/{2}/get", Get, Options, FILTER);
        ADD_METHOD_TO(EntityImagesController::create, std::string(PREFIX) + "{1}/{2}/create", Post, Options, FILTER);
        ADD_METHOD_TO(EntityImagesController::update, std::string(PREFIX) + "{1}/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(EntityImagesController::remove, std::string(PREFIX) + "{1}/{2}/delete", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> get(HttpRequestPtr req, std::string entity, std::string entityId);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string entity, std::string entityId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string entity, std::string entityId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string entity, std::string entityId);
};
