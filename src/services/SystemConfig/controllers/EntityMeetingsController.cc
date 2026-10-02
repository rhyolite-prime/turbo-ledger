#include "EntityMeetingsController.h"

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

Task<HttpResponsePtr> EntityMeetingsController::getAll(HttpRequestPtr req, std::string entityType,
                                                       std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listMeetings(*ctx, entityType, entityId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityMeetingsController::getTemplate(HttpRequestPtr req, std::string, std::string) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().meetingTemplate(*ctx));
}

Task<HttpResponsePtr> EntityMeetingsController::create(HttpRequestPtr req, std::string entityType,
                                                       std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createMeeting(*ctx, entityType, entityId, *body),
                                        "Meeting created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityMeetingsController::getDetails(HttpRequestPtr req, std::string entityType,
                                                           std::string entityId, std::string meetingId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getMeeting(*ctx, entityType, entityId, meetingId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityMeetingsController::update(HttpRequestPtr req, std::string entityType,
                                                       std::string entityId, std::string meetingId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().updateMeeting(*ctx, entityType, entityId, meetingId, *body),
            "Meeting updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityMeetingsController::remove(HttpRequestPtr req, std::string entityType,
                                                       std::string entityId, std::string meetingId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteMeeting(*ctx, entityType, entityId, meetingId);
        Json::Value result;
        result["resourceId"] = meetingId;
        co_return ApiResponse::httpOk(result, "Meeting deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityMeetingsController::command(HttpRequestPtr req, std::string entityType,
                                                        std::string entityId, std::string meetingId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value payload = body ? *body : Json::Value(Json::objectValue);
    const std::string cmd = req->getParameter("command");
    if (cmd.empty()) co_return ApiResponse::httpBadRequest("Missing required 'command' query parameter");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().meetingCommand(*ctx, entityType, entityId, meetingId, cmd, payload),
            "Meeting command '" + cmd + "' applied");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
