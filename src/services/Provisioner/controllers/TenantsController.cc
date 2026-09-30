#include "TenantsController.h"

#include "services/ProvisioningService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using provisioner::ApiError;
using provisioner::ProvisioningService;
using turbo::ApiResponse;

namespace {

/// Tenant management is a host-plane operation: JWT principal, host tenant.
bool isHostAdmin(const turbo::RequestContext &ctx) {
    return ctx.authScheme == "jwt" && !ctx.userId.empty() && ctx.tenantId == "default";
}

}  // namespace

Task<HttpResponsePtr> TenantsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await ProvisioningService::instance().listTenants());
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TenantsController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await ProvisioningService::instance().getTenant(id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TenantsController::instanceMode(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(ProvisioningService::instance().instanceMode());
}

Task<HttpResponsePtr> TenantsController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    if (!isHostAdmin(*ctx))
        co_return ApiResponse::httpError(k403Forbidden,
                                         "Tenant management requires a host-tenant JWT principal",
                                         "error.msg.provisioner.host.required");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto result = co_await ProvisioningService::instance().createTenant(*body);
        auto resp = ApiResponse::httpOk(result, "Tenant provisioned");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TenantsController::activate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    if (!isHostAdmin(*ctx))
        co_return ApiResponse::httpError(k403Forbidden,
                                         "Tenant management requires a host-tenant JWT principal",
                                         "error.msg.provisioner.host.required");
    try {
        co_return ApiResponse::httpOk(
            co_await ProvisioningService::instance().setStatus(id, "ACTIVE"), "Tenant activated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TenantsController::suspend(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    if (!isHostAdmin(*ctx))
        co_return ApiResponse::httpError(k403Forbidden,
                                         "Tenant management requires a host-tenant JWT principal",
                                         "error.msg.provisioner.host.required");
    try {
        co_return ApiResponse::httpOk(
            co_await ProvisioningService::instance().setStatus(id, "SUSPENDED"),
            "Tenant suspended");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TenantsController::close(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    if (!isHostAdmin(*ctx))
        co_return ApiResponse::httpError(k403Forbidden,
                                         "Tenant management requires a host-tenant JWT principal",
                                         "error.msg.provisioner.host.required");
    try {
        co_return ApiResponse::httpOk(
            co_await ProvisioningService::instance().setStatus(id, "CLOSED"), "Tenant closed");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
