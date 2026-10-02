#include "GroupsController.h"

#include "services/GroupService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_group::ApiError;
using turbo_ledger_group::GroupService;

namespace {
GroupService &svc() {
    static GroupService instance;
    return instance;
}

int parseIntOrDefault(const std::string &text, int fallback) {
    if (text.empty()) return fallback;
    try {
        return std::stoi(text);
    } catch (...) {
        return fallback;
    }
}
}  // namespace

Task<HttpResponsePtr> GroupsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().listGroups(
            *ctx, req->getParameter("officeId"), req->getParameter("staffId"),
            req->getParameter("status"), req->getParameter("nameLike"), offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GroupsController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createGroup(*ctx, *body), "Group created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GroupsController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getGroup(*ctx, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GroupsController::update(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateGroup(*ctx, id, *body), "Group updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GroupsController::remove(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteGroup(*ctx, id);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Group deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GroupsController::command(HttpRequestPtr req, std::string id, std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(co_await svc().handleGroupCommand(*ctx, id, cmd, b),
                                      "Command '" + cmd + "' applied");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GroupsController::templateEndpoint(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(svc().groupTemplate(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

// ---- 501s: cross-service composition with no RPC client (see header note) ---

Task<HttpResponsePtr> GroupsController::accountsOverview(HttpRequestPtr, std::string) {
    co_return ApiResponse::httpNotImplemented(
        "groups/{id}/accounts (composes DepositAccountManagement + Portfolio account summaries)");
}

Task<HttpResponsePtr> GroupsController::glimAccounts(HttpRequestPtr, std::string) {
    co_return ApiResponse::httpNotImplemented("groups/{id}/glimaccounts (composes Portfolio GLIM loans)");
}

Task<HttpResponsePtr> GroupsController::gsimAccounts(HttpRequestPtr, std::string) {
    co_return ApiResponse::httpNotImplemented(
        "groups/{id}/gsimaccounts (composes DepositAccountManagement GSIM savings accounts)");
}

Task<HttpResponsePtr> GroupsController::generateCollectionSheet(HttpRequestPtr, std::string) {
    co_return ApiResponse::httpNotImplemented(
        "groups/{id}/generatecollectionsheet (needs Portfolio repayment schedules + DAM savings-due "
        "amounts + attendance/calendar data this phase doesn't own)");
}

Task<HttpResponsePtr> GroupsController::saveCollectionSheet(HttpRequestPtr, std::string) {
    co_return ApiResponse::httpNotImplemented("groups/{id}/savecollectionsheet (see generatecollectionsheet)");
}
