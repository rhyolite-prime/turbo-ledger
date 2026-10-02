//
// Phase 8 — smscampaigns (8 endpoints): scheduled/triggered SMS campaigns.
// Activating a campaign flips its status only — the real schedule trigger
// (and SMS dispatch) is stubbed, see NotificationService header note.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SmsCampaignsController : public drogon::HttpController<SmsCampaignsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/smscampaigns";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SmsCampaignsController::getAll, std::string(PREFIX), Get, Options, FILTER);
        ADD_METHOD_TO(SmsCampaignsController::create, std::string(PREFIX), Post, Options, FILTER);

        ADD_METHOD_TO(SmsCampaignsController::creationTemplate, std::string(PREFIX) + "/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SmsCampaignsController::preview, std::string(PREFIX) + "/preview", Post, Options,
                     FILTER);

        ADD_METHOD_TO(SmsCampaignsController::getOne, std::string(PREFIX) + "/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(SmsCampaignsController::update, std::string(PREFIX) + "/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(SmsCampaignsController::remove, std::string(PREFIX) + "/{1}", Delete, Options, FILTER);
        ADD_METHOD_TO(SmsCampaignsController::command, std::string(PREFIX) + "/{1}", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> creationTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> preview(HttpRequestPtr req);
    Task<HttpResponsePtr> getOne(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string id);
};
