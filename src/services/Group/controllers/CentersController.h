//
// Phase 7 (retrofit) — centers (10 endpoints per ENDPOINT_INVENTORY.md).
//
// A Center is the same `groups` row shape as a Group, one level up the
// hierarchy (level_id = the "Center" group_levels row) — see
// GroupService.h's header note. `{id}/accounts` is a 501 (same precedent
// as GroupsController's accounts/glim/gsim stubs).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CentersController : public drogon::HttpController<CentersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/centers/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CentersController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CentersController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(CentersController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(CentersController::update, std::string(PREFIX) + "{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(CentersController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(CentersController::command, std::string(PREFIX) + "{1}/command/{2}", Post, Options,
                     FILTER);
        ADD_METHOD_TO(CentersController::templateEndpoint, std::string(PREFIX) + "template", Get, Options,
                     FILTER);
        ADD_METHOD_TO(CentersController::accountsOverview, std::string(PREFIX) + "{1}/accounts", Get,
                     Options, FILTER);
        ADD_METHOD_TO(CentersController::generateCollectionSheet,
                     std::string(PREFIX) + "{1}/generatecollectionsheet", Post, Options, FILTER);
        ADD_METHOD_TO(CentersController::saveCollectionSheet,
                     std::string(PREFIX) + "{1}/savecollectionsheet", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    /// command: activate|close|assignStaff|unassignStaff|associateGroups|disassociateGroups
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string id, std::string cmd);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> accountsOverview(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> generateCollectionSheet(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> saveCollectionSheet(HttpRequestPtr req, std::string id);
};
