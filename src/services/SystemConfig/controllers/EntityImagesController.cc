#include "EntityImagesController.h"

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

Task<HttpResponsePtr> EntityImagesController::get(HttpRequestPtr req, std::string entity,
                                                  std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        // Content is returned base64-encoded inside the standard ApiResponse envelope.
        co_return ApiResponse::httpOk(co_await svc().getImage(*ctx, entity, entityId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityImagesController::create(HttpRequestPtr req, std::string entity,
                                                     std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().putImage(*ctx, entity, entityId, *body),
                                        "Image saved");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityImagesController::update(HttpRequestPtr req, std::string entity,
                                                     std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().putImage(*ctx, entity, entityId, *body),
                                      "Image saved");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> EntityImagesController::remove(HttpRequestPtr req, std::string entity,
                                                     std::string entityId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteImage(*ctx, entity, entityId);
        Json::Value result;
        result["resourceId"] = entityId;
        co_return ApiResponse::httpOk(result, "Image deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
