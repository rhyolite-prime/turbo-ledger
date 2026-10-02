//
// Phase 8 — email (20 endpoints): SMTP configuration, email campaigns, and
// ad hoc email messages. Real SMTP dispatch is stubbed (see
// NotificationService header note) — created messages/activated campaigns
// are queued with status PENDING only.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EmailController : public drogon::HttpController<EmailController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/email";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        // ---- configuration --------------------------------------------------
        ADD_METHOD_TO(EmailController::getConfiguration, std::string(PREFIX) + "/configuration", Get,
                     Options, FILTER);
        ADD_METHOD_TO(EmailController::updateConfiguration, std::string(PREFIX) + "/configuration", Put,
                     Options, FILTER);

        // ---- campaigns --------------------------------------------------------
        ADD_METHOD_TO(EmailController::campaignGetAll, std::string(PREFIX) + "/campaign", Get, Options,
                     FILTER);
        ADD_METHOD_TO(EmailController::campaignCreate, std::string(PREFIX) + "/campaign", Post, Options,
                     FILTER);
        ADD_METHOD_TO(EmailController::campaignTemplate, std::string(PREFIX) + "/campaign/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(EmailController::campaignEditTemplate,
                     std::string(PREFIX) + "/campaign/template/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(EmailController::campaignPreview, std::string(PREFIX) + "/campaign/preview", Post,
                     Options, FILTER);
        ADD_METHOD_TO(EmailController::campaignGetOne, std::string(PREFIX) + "/campaign/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(EmailController::campaignUpdate, std::string(PREFIX) + "/campaign/{1}", Put, Options,
                     FILTER);
        ADD_METHOD_TO(EmailController::campaignRemove, std::string(PREFIX) + "/campaign/{1}", Delete,
                     Options, FILTER);
        ADD_METHOD_TO(EmailController::campaignCommand, std::string(PREFIX) + "/campaign/{1}", Post, Options,
                     FILTER);

        // ---- filtered views -----------------------------------------------------
        ADD_METHOD_TO(EmailController::failedEmail, std::string(PREFIX) + "/failedEmail", Get, Options,
                     FILTER);
        ADD_METHOD_TO(EmailController::pendingEmail, std::string(PREFIX) + "/pendingEmail", Get, Options,
                     FILTER);
        ADD_METHOD_TO(EmailController::sentEmail, std::string(PREFIX) + "/sentEmail", Get, Options, FILTER);
        ADD_METHOD_TO(EmailController::messageByStatus, std::string(PREFIX) + "/messageByStatus", Get,
                     Options, FILTER);

        // ---- ad hoc messages ----------------------------------------------------
        ADD_METHOD_TO(EmailController::getAll, std::string(PREFIX), Get, Options, FILTER);
        ADD_METHOD_TO(EmailController::create, std::string(PREFIX), Post, Options, FILTER);
        ADD_METHOD_TO(EmailController::getOne, std::string(PREFIX) + "/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(EmailController::update, std::string(PREFIX) + "/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(EmailController::remove, std::string(PREFIX) + "/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getConfiguration(HttpRequestPtr req);
    Task<HttpResponsePtr> updateConfiguration(HttpRequestPtr req);

    Task<HttpResponsePtr> campaignGetAll(HttpRequestPtr req);
    Task<HttpResponsePtr> campaignCreate(HttpRequestPtr req);
    Task<HttpResponsePtr> campaignTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> campaignEditTemplate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> campaignPreview(HttpRequestPtr req);
    Task<HttpResponsePtr> campaignGetOne(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> campaignUpdate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> campaignRemove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> campaignCommand(HttpRequestPtr req, std::string id);

    Task<HttpResponsePtr> failedEmail(HttpRequestPtr req);
    Task<HttpResponsePtr> pendingEmail(HttpRequestPtr req);
    Task<HttpResponsePtr> sentEmail(HttpRequestPtr req);
    Task<HttpResponsePtr> messageByStatus(HttpRequestPtr req);

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getOne(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
