//
// Phase 8 — sms (6 endpoints): ad hoc outbound SMS messages. Real provider
// dispatch is stubbed (see NotificationService header note) — created
// messages are queued with status PENDING only.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SmsController : public drogon::HttpController<SmsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/sms";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SmsController::getAll, std::string(PREFIX), Get, Options, FILTER);
        ADD_METHOD_TO(SmsController::create, std::string(PREFIX), Post, Options, FILTER);

        ADD_METHOD_TO(SmsController::messageByStatus, std::string(PREFIX) + "/{1}/messageByStatus", Get,
                     Options, FILTER);

        ADD_METHOD_TO(SmsController::getOne, std::string(PREFIX) + "/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(SmsController::update, std::string(PREFIX) + "/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(SmsController::remove, std::string(PREFIX) + "/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> messageByStatus(HttpRequestPtr req, std::string campaignId);
    Task<HttpResponsePtr> getOne(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
