//
// Phase 2 — generic entity notes (5 endpoints). Distinct `entity-notes/`
// prefix — see EntityDocumentsController.h for the routing-convention note.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EntityNotesController : public drogon::HttpController<EntityNotesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/entity-notes/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(EntityNotesController::getAll,     std::string(PREFIX) + "{1}/{2}/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(EntityNotesController::create,     std::string(PREFIX) + "{1}/{2}/create", Post, Options, FILTER);
        ADD_METHOD_TO(EntityNotesController::getDetails, std::string(PREFIX) + "{1}/{2}/get-details/{3}", Get, Options, FILTER);
        ADD_METHOD_TO(EntityNotesController::update,     std::string(PREFIX) + "{1}/{2}/update/{3}", Put, Options, FILTER);
        ADD_METHOD_TO(EntityNotesController::remove,     std::string(PREFIX) + "{1}/{2}/delete/{3}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string resourceType, std::string resourceId);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string resourceType, std::string resourceId);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string resourceType, std::string resourceId,
                                     std::string noteId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string resourceType, std::string resourceId,
                                 std::string noteId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string resourceType, std::string resourceId,
                                 std::string noteId);
};
