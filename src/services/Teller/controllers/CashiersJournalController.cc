#include "CashiersJournalController.h"

#include "services/TellerService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_teller::ApiError;
using turbo_ledger_teller::TellerService;

namespace {
TellerService &svc() {
    static TellerService instance;
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

Task<HttpResponsePtr> CashiersJournalController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().cashiersJournal(
            *ctx, req->getParameter("cashierId"), req->getParameter("tellerId"),
            req->getParameter("currencyCode"), req->getParameter("fromDate"),
            req->getParameter("toDate"), offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
