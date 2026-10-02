//
// Phase 8 — notifications (2 endpoints): per-user inbox.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class NotificationsController : public drogon::HttpController<NotificationsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/notifications";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(NotificationsController::getAll, std::string(PREFIX), Get, Options, FILTER);
        ADD_METHOD_TO(NotificationsController::markRead, std::string(PREFIX), Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> markRead(HttpRequestPtr req);
};
