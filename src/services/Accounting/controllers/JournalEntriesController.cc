#include "JournalEntriesController.h"

#include "services/AccountingService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_accounting::AccountingService;
using turbo_ledger_accounting::ApiError;

namespace {
AccountingService &svc() {
    static AccountingService instance;
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

Task<HttpResponsePtr> JournalEntriesController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createJournalEntries(*ctx, *body),
                                        "Journal entries posted");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().searchJournalEntries(
            *ctx, req->getParameter("officeId"), req->getParameter("glAccountId"),
            req->getParameter("manualEntriesOnly"), req->getParameter("fromDate"),
            req->getParameter("toDate"), req->getParameter("transactionId"), offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getJournalEntry(*ctx, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::openingBalance(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getOpeningBalance(
            *ctx, req->getParameter("officeId"), req->getParameter("currencyCode")));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::provisioning(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().getProvisioningJournalEntries(*ctx, offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::templateEndpoint(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().journalEntryTemplate(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::reverse(HttpRequestPtr req, std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value payload = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(co_await svc().reverseJournalTransaction(*ctx, transactionId, payload),
                                      "Journal transaction reversed");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::recalculateRunningBalance(HttpRequestPtr req,
                                                                          std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().recalculateRunningBalances(*ctx, transactionId),
                                      "Running balances recalculated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> JournalEntriesController::downloadTemplate(HttpRequestPtr) {
    co_return ApiResponse::httpNotImplemented("journalentries/downloadtemplate (bulk import, Phase 8)");
}

Task<HttpResponsePtr> JournalEntriesController::uploadTemplate(HttpRequestPtr) {
    co_return ApiResponse::httpNotImplemented("journalentries/uploadtemplate (bulk import, Phase 8)");
}
