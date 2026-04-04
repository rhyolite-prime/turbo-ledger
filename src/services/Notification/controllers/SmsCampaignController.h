#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SmsCampaignController : public drogon::HttpController<SmsCampaignController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/sms-campaign";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SmsCampaignController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(SmsCampaignController::getSmsCampaigns, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(SmsCampaignController::createSmsCampaign, std::string(PREFIX) + "create", Post); //create or define charge.
    ADD_METHOD_TO(SmsCampaignController::updateSmsCampaign, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(SmsCampaignController::retrieveSmsCampaignDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(SmsCampaignController::activateSmsCampaign, std::string(PREFIX) + "{1}/activate", Get);
    ADD_METHOD_TO(SmsCampaignController::deActivateSmsCampaign, std::string(PREFIX) + "{1}/deactivate", Get);
    ADD_METHOD_TO(SmsCampaignController::runScheduledSmsCampaign, std::string(PREFIX) + "{1}/run", Get); //run scheduled campaign
    ADD_METHOD_TO(SmsCampaignController::deleteSmsCampaign, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSmsCampaigns(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createSmsCampaign(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateSmsCampaign(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveSmsCampaignDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteSmsCampaign(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateSmsCampaign(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deActivateSmsCampaign(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void runScheduledSmsCampaign(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
