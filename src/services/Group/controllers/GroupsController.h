//
// Phase 7 (retrofit) — groups (13 endpoints per ENDPOINT_INVENTORY.md).
//
// Routing uses explicit action-suffix paths (get-all/create/get-detail/
// {id}/update/{id}/delete/{id}/command/{name}), matching every other
// controller in this codebase, rather than Fineract's single-path +
// HTTP-verb-overload + ?command= style.
//
// `{id}/accounts`, `{id}/glimaccounts`, `{id}/gsimaccounts` are 501s (no
// inter-service RPC client exists to compose DepositAccountManagement /
// Portfolio data) — same precedent as ClientsController::accountsOverview.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GroupsController : public drogon::HttpController<GroupsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/groups/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(GroupsController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(GroupsController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(GroupsController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(GroupsController::update, std::string(PREFIX) + "{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(GroupsController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(GroupsController::command, std::string(PREFIX) + "{1}/command/{2}", Post, Options,
                     FILTER);
        ADD_METHOD_TO(GroupsController::templateEndpoint, std::string(PREFIX) + "template", Get, Options,
                     FILTER);
        ADD_METHOD_TO(GroupsController::accountsOverview, std::string(PREFIX) + "{1}/accounts", Get,
                     Options, FILTER);
        ADD_METHOD_TO(GroupsController::glimAccounts, std::string(PREFIX) + "{1}/glimaccounts", Get,
                     Options, FILTER);
        ADD_METHOD_TO(GroupsController::gsimAccounts, std::string(PREFIX) + "{1}/gsimaccounts", Get,
                     Options, FILTER);
        ADD_METHOD_TO(GroupsController::generateCollectionSheet,
                     std::string(PREFIX) + "{1}/generatecollectionsheet", Post, Options, FILTER);
        ADD_METHOD_TO(GroupsController::saveCollectionSheet,
                     std::string(PREFIX) + "{1}/savecollectionsheet", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    /// command: activate|close|assignStaff|unassignStaff|associateClients|
    ///   disassociateClients|transferClients|assignRole|unassignRole|updateRole
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string id, std::string cmd);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> accountsOverview(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> glimAccounts(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> gsimAccounts(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> generateCollectionSheet(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> saveCollectionSheet(HttpRequestPtr req, std::string id);
};
