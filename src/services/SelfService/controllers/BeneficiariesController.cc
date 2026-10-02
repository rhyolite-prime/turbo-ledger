#include "BeneficiariesController.h"

#include "services/SelfServiceService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_selfservice::ApiError;
using turbo_ledger_selfservice::SelfServiceService;

namespace {
SelfServiceService &svc() {
    static SelfServiceService instance;
    return instance;
}
}  // namespace

#define SELF_TRY try
#define SELF_CATCH                                                                     \
    catch (const ApiError &e) {                                                       \
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode()); \
    }                                                                                 \
    catch (const std::exception &e) {                                                 \
        co_return ApiResponse::httpError(k500InternalServerError, e.what());          \
    }

Task<HttpResponsePtr> BeneficiariesController::tptTemplate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().tptTemplate(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::tptList(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().listTptBeneficiaries(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::tptCreate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().createTptBeneficiary(*ctx, *body),
                                        "Beneficiary created");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::tptUpdate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().updateTptBeneficiary(*ctx, id, *body),
                                      "Beneficiary updated");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::tptDelete(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_await svc().deleteTptBeneficiary(*ctx, id);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Beneficiary deleted");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::deviceList(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().listDeviceRegistrations(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::deviceCreate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().createDeviceRegistration(*ctx, *body),
                                        "Device registered");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::deviceGet(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getDeviceRegistration(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::deviceUpdate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().updateDeviceRegistration(*ctx, id, *body),
                                      "Device registration updated");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::deviceDelete(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_await svc().deleteDeviceRegistration(*ctx, id);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Device registration deleted");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::pocketsList(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().listPockets(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> BeneficiariesController::pocketsCreate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().createPocket(*ctx, *body), "Pocket created");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}
