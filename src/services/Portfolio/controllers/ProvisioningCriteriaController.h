#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ProvisioningCriteriaController : public drogon::HttpController<ProvisioningCriteriaController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/provisioning-criteria/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ProvisioningCriteriaController::getProvisioningCriteria, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(ProvisioningCriteriaController::getProvisioningCriteriaDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(ProvisioningCriteriaController::createProvisioningCriteria, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(ProvisioningCriteriaController::updateProvisioningCriteria, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(ProvisioningCriteriaController::deleteProvisioningCriteria, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void getProvisioningCriteria(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getProvisioningCriteriaDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createProvisioningCriteria(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateProvisioningCriteria(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteProvisioningCriteria(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
