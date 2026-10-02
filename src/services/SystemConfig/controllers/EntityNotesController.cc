#include "EntityNotesController.h"

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

Task<HttpResponsePtr> EntityNotesController::getAll(HttpRequestPtr req, std::string resourceType,
                                                    std::string resourceId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listNotes(*ctx, resourceType, resourceId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityNotesController::create(HttpRequestPtr req, std::string resourceType,
                                                    std::string resourceId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createNote(*ctx, resourceType, resourceId, *body),
                                        "Note created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityNotesController::getDetails(HttpRequestPtr req, std::string resourceType,
                                                        std::string resourceId, std::string noteId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getNote(*ctx, resourceType, resourceId, noteId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityNotesController::update(HttpRequestPtr req, std::string resourceType,
                                                    std::string resourceId, std::string noteId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateNote(*ctx, resourceType, resourceId, noteId, *body),
                                      "Note updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityNotesController::remove(HttpRequestPtr req, std::string resourceType,
                                                    std::string resourceId, std::string noteId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteNote(*ctx, resourceType, resourceId, noteId);
        Json::Value result;
        result["resourceId"] = noteId;
        co_return ApiResponse::httpOk(result, "Note deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
