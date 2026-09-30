#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GroupsController : public drogon::HttpController<GroupsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/groups/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(GroupsController::getGroups, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(GroupsController::createGroup, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(GroupsController::activateGroup, std::string(PREFIX) + "{1}/activate", Post);
    ADD_METHOD_TO(GroupsController::associateClientToGroup, std::string(PREFIX) + "{1}/associate-clients", Post);
    ADD_METHOD_TO(GroupsController::disassociateClientToGroup, std::string(PREFIX) + "{1}/disassociate-clients", Post);
    ADD_METHOD_TO(GroupsController::transferClientAcrossGroups, std::string(PREFIX) + "{1}/transfer-clients", Post);
    ADD_METHOD_TO(GroupsController::generateCollectionSheet, std::string(PREFIX) + "{1}/generate-collection-sheet", Post);
    ADD_METHOD_TO(GroupsController::saveCollectionSheet, std::string(PREFIX) + "{1}/save-collection-sheet", Post);
    ADD_METHOD_TO(GroupsController::assignStaff, std::string(PREFIX) + "{1}/assign-staff", Post);
    ADD_METHOD_TO(GroupsController::unassignStaff, std::string(PREFIX) + "{1}/unassign-staff", Post);
    ADD_METHOD_TO(GroupsController::closeGroup, std::string(PREFIX) + "{1}/close", Post);
    ADD_METHOD_TO(GroupsController::assignRole, std::string(PREFIX) + "{1}/assign-role", Post);
    ADD_METHOD_TO(GroupsController::unassignRole, std::string(PREFIX) + "{1}/unassign-role", Post);
    ADD_METHOD_TO(GroupsController::updateRole, std::string(PREFIX) + "{1}/update-role", Post);
    ADD_METHOD_TO(GroupsController::getGroupDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(GroupsController::getGroupAccountsOverview, std::string(PREFIX) + "{1}/accounts", Get);
    ADD_METHOD_TO(GroupsController::updateGroup, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(GroupsController::deleteGroup, std::string(PREFIX) + "{1}", Delete);
    //gsim
    ADD_METHOD_TO(GroupsController::getGsimApplications, std::string(PREFIX) + "{1}/gsim-accounts", Get);
    ADD_METHOD_TO(GroupsController::getGlimApplications, std::string(PREFIX) + "{1}/glim-accounts", Get);

    METHOD_LIST_END

    Task<HttpResponsePtr> getGroups(HttpRequestPtr req);
    Task<HttpResponsePtr> createGroup(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> activateGroup(HttpRequestPtr req);
    Task<HttpResponsePtr> associateClientToGroup(HttpRequestPtr req);
    Task<HttpResponsePtr> disassociateClientToGroup(HttpRequestPtr req);
    Task<HttpResponsePtr> transferClientAcrossGroups(HttpRequestPtr req);
    Task<HttpResponsePtr> generateCollectionSheet(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> saveCollectionSheet(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> assignStaff(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> unassignStaff(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> closeGroup(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> assignRole(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> unassignRole(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> updateRole(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> getGroupDetails(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> getGroupAccountsOverview(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> updateGroup(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> deleteGroup(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> getGsimApplications(HttpRequestPtr req,const std::string &id);
    Task<HttpResponsePtr> getGlimApplications(HttpRequestPtr req,const std::string &id);

};
