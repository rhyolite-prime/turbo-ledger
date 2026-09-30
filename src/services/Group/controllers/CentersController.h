#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CentersController : public drogon::HttpController<CentersController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/centers/";
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(CentersController::getCenters, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(CentersController::createCenter, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(CentersController::getCenterDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(CentersController::updateCenter, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(CentersController::deleteCenter, std::string(PREFIX) + "{1}", Delete);
    ADD_METHOD_TO(CentersController::activateCenter, std::string(PREFIX) + "{1}/activate", Post);
    ADD_METHOD_TO(CentersController::closeCenter, std::string(PREFIX) + "{1}/close", Post);
    ADD_METHOD_TO(CentersController::associateGroupsToCenter, std::string(PREFIX) + "{1}/associate-groups", Post);
    ADD_METHOD_TO(CentersController::disassociateGroupsToCenter, std::string(PREFIX) + "{1}/disassociate-groups", Post);
    ADD_METHOD_TO(CentersController::getCenterAccountsOverview, std::string(PREFIX) + "{1}/accounts", Get);

    ADD_METHOD_TO(CentersController::generateCollectionSheet, std::string(PREFIX) + "{1}/generate-collection-sheet", Post);
    ADD_METHOD_TO(CentersController::saveCollectionSheet, std::string(PREFIX) + "{1}/save-collection-sheet", Post);
    METHOD_LIST_END

    Task<HttpResponsePtr> getCenters(HttpRequestPtr req);
    Task<HttpResponsePtr> createCenter(HttpRequestPtr req);
    Task<HttpResponsePtr> getCenterDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> updateCenter(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> deleteCenter(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> activateCenter(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> closeCenter(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> associateGroupsToCenter(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> disassociateGroupsToCenter(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getCenterAccountsOverview(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> generateCollectionSheet(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> saveCollectionSheet(HttpRequestPtr req, const std::string &id);

};
