//
// Phase 2 — generic entity meetings (7 endpoints). Distinct
// `entity-meetings/` prefix — see EntityDocumentsController.h for the
// routing-convention note.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EntityMeetingsController : public drogon::HttpController<EntityMeetingsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/entity-meetings/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(EntityMeetingsController::getAll,      std::string(PREFIX) + "{1}/{2}/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(EntityMeetingsController::getTemplate, std::string(PREFIX) + "{1}/{2}/template", Get, Options, FILTER);
        ADD_METHOD_TO(EntityMeetingsController::create,      std::string(PREFIX) + "{1}/{2}/create", Post, Options, FILTER);
        ADD_METHOD_TO(EntityMeetingsController::getDetails,  std::string(PREFIX) + "{1}/{2}/get-details/{3}", Get, Options, FILTER);
        ADD_METHOD_TO(EntityMeetingsController::update,      std::string(PREFIX) + "{1}/{2}/update/{3}", Put, Options, FILTER);
        ADD_METHOD_TO(EntityMeetingsController::remove,      std::string(PREFIX) + "{1}/{2}/delete/{3}", Delete, Options, FILTER);
        ADD_METHOD_TO(EntityMeetingsController::command,     std::string(PREFIX) + "{1}/{2}/commands/{3}", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string entityType, std::string entityId,
                                     std::string meetingId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string entityType, std::string entityId,
                                 std::string meetingId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string entityType, std::string entityId,
                                 std::string meetingId);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string entityType, std::string entityId,
                                  std::string meetingId);
};
