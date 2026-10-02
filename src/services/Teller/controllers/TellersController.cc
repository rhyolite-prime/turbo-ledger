#include "TellersController.h"

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

Task<HttpResponsePtr> TellersController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().listTellers(
            *ctx, req->getParameter("officeId"), req->getParameter("status"),
            req->getParameter("nameLike"), offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createTeller(*ctx, *body), "Teller created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::getDetails(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getTeller(*ctx, tellerId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::update(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateTeller(*ctx, tellerId, *body), "Teller updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::remove(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteTeller(*ctx, tellerId);
        co_return ApiResponse::httpOk(Json::Value(), "Teller deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::transactionsGetAll(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().tellerTransactions(*ctx, tellerId, offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::transactionsGetDetail(HttpRequestPtr req, std::string tellerId,
                                                               std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().tellerTransactionDetail(*ctx, tellerId, transactionId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::journalsGetAll(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().tellerJournal(*ctx, tellerId, offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashiersGetAll(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listCashiers(*ctx, tellerId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashiersCreate(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp =
            ApiResponse::httpOk(co_await svc().createCashier(*ctx, tellerId, *body), "Cashier created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashiersTemplate(HttpRequestPtr req, std::string tellerId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(svc().cashierTemplate(*ctx, tellerId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashiersGetDetail(HttpRequestPtr req, std::string tellerId,
                                                           std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getCashier(*ctx, tellerId, cashierId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashiersUpdate(HttpRequestPtr req, std::string tellerId,
                                                        std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateCashier(*ctx, tellerId, cashierId, *body),
                                      "Cashier updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashiersDelete(HttpRequestPtr req, std::string tellerId,
                                                        std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteCashier(*ctx, tellerId, cashierId);
        co_return ApiResponse::httpOk(Json::Value(), "Cashier deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashierTransactionsGetAll(HttpRequestPtr req, std::string tellerId,
                                                                   std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().cashierTransactions(
            *ctx, tellerId, cashierId, req->getParameter("currencyCode"), offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashierTransactionsTemplate(HttpRequestPtr req, std::string tellerId,
                                                                     std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().cashierTransactionTemplate(*ctx, tellerId, cashierId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::cashierSummaryAndTransactions(HttpRequestPtr req,
                                                                       std::string tellerId,
                                                                       std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    const int offset = parseIntOrDefault(req->getParameter("offset"), 0);
    const int limit = parseIntOrDefault(req->getParameter("limit"), 50);
    try {
        co_return ApiResponse::httpOk(co_await svc().cashierSummaryAndTransactions(
            *ctx, tellerId, cashierId, req->getParameter("currencyCode"), offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::allocateCashToCashier(HttpRequestPtr req, std::string tellerId,
                                                               std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().allocateCash(*ctx, tellerId, cashierId, *body),
                                      "Cash allocated to cashier");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> TellersController::settleCashToCashier(HttpRequestPtr req, std::string tellerId,
                                                             std::string cashierId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().settleCash(*ctx, tellerId, cashierId, *body),
                                      "Cash settled from cashier");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
