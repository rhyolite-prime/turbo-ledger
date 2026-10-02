#include "PartiesController.h"

#include "services/InteroperationService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_interoperation::ApiError;
using turbo_ledger_interoperation::InteroperationService;

namespace {
InteroperationService &svc() {
    static InteroperationService instance;
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

Task<HttpResponsePtr> PartiesController::registerParty(HttpRequestPtr req, std::string idType,
                                                        std::string idValue) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().registerParty(*ctx, idType, idValue, "", *body),
                                      "Party registered");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> PartiesController::registerPartySub(HttpRequestPtr req, std::string idType,
                                                          std::string idValue,
                                                          std::string subIdOrType) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        co_return ApiResponse::httpOk(
            co_await svc().registerParty(*ctx, idType, idValue, subIdOrType, *body), "Party registered");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> PartiesController::getParty(HttpRequestPtr req, std::string idType,
                                                  std::string idValue) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getParty(*ctx, idType, idValue, "")); }
    SELF_CATCH
}

Task<HttpResponsePtr> PartiesController::getPartySub(HttpRequestPtr req, std::string idType,
                                                     std::string idValue, std::string subIdOrType) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().getParty(*ctx, idType, idValue, subIdOrType));
    }
    SELF_CATCH
}

Task<HttpResponsePtr> PartiesController::removeParty(HttpRequestPtr req, std::string idType,
                                                     std::string idValue) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_await svc().removeParty(*ctx, idType, idValue, "");
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Party removed");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> PartiesController::removePartySub(HttpRequestPtr req, std::string idType,
                                                        std::string idValue, std::string subIdOrType) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_await svc().removeParty(*ctx, idType, idValue, subIdOrType);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Party removed");
    }
    SELF_CATCH
}
