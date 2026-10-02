//
// Phase 2 — generic entity calendars (6 endpoints). Distinct
// `entity-calendars/` prefix — see EntityDocumentsController.h for the
// routing-convention note.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EntityCalendarsController : public drogon::HttpController<EntityCalendarsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/entity-calendars/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(EntityCalendarsController::getAll,      std::string(PREFIX) + "{1}/{2}/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(EntityCalendarsController::getTemplate, std::string(PREFIX) + "{1}/{2}/template", Get, Options, FILTER);
        ADD_METHOD_TO(EntityCalendarsController::create,      std::string(PREFIX) + "{1}/{2}/create", Post, Options, FILTER);
        ADD_METHOD_TO(EntityCalendarsController::getDetails,  std::string(PREFIX) + "{1}/{2}/get-details/{3}", Get, Options, FILTER);
        ADD_METHOD_TO(EntityCalendarsController::update,      std::string(PREFIX) + "{1}/{2}/update/{3}", Put, Options, FILTER);
        ADD_METHOD_TO(EntityCalendarsController::remove,      std::string(PREFIX) + "{1}/{2}/delete/{3}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string entityType, std::string entityId);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string entityType, std::string entityId,
                                     std::string calendarId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string entityType, std::string entityId,
                                 std::string calendarId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string entityType, std::string entityId,
                                 std::string calendarId);
};
