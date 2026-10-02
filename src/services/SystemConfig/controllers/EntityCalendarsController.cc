#include "EntityCalendarsController.h"

#include "services/SystemConfigService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_systemconfig::ApiError;
using turbo_ledger_systemconfig::SystemConfigService;

namespace {
SystemConfigService &svc() {
    static SystemConfigService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> EntityCalendarsController::getAll(HttpRequestPtr req, std::string entityType,
                                                        std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listCalendars(*ctx, entityType, entityId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityCalendarsController::getTemplate(HttpRequestPtr req, std::string, std::string) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().calendarTemplate(*ctx));
}

Task<HttpResponsePtr> EntityCalendarsController::create(HttpRequestPtr req, std::string entityType,
                                                        std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createCalendar(*ctx, entityType, entityId, *body),
                                        "Calendar created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityCalendarsController::getDetails(HttpRequestPtr req, std::string entityType,
                                                            std::string entityId,
                                                            std::string calendarId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getCalendar(*ctx, entityType, entityId, calendarId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityCalendarsController::update(HttpRequestPtr req, std::string entityType,
                                                        std::string entityId, std::string calendarId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().updateCalendar(*ctx, entityType, entityId, calendarId, *body),
            "Calendar updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityCalendarsController::remove(HttpRequestPtr req, std::string entityType,
                                                        std::string entityId, std::string calendarId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteCalendar(*ctx, entityType, entityId, calendarId);
        Json::Value result;
        result["resourceId"] = calendarId;
        co_return ApiResponse::httpOk(result, "Calendar deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
