#include "LoansController.h"

#include "services/PortfolioService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_portfolio::ApiError;
using turbo_ledger_portfolio::PortfolioService;

namespace {
PortfolioService &svc() {
    static PortfolioService instance;
    return instance;
}

// All routes in this controller address loans/sub-resources by numeric id
// only (see header note on the external-id-mirror scope trim).
constexpr bool kByExternalId = false;
}  // namespace

#define TRY_BEGIN try {
#define TRY_END                                                             \
    }                                                                       \
    catch (const ApiError &e) {                                             \
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode()); \
    }                                                                       \
    catch (const std::exception &e) {                                      \
        co_return ApiResponse::httpError(k500InternalServerError, e.what()); \
    }

// ============================================================================
// core
// ============================================================================

Task<HttpResponsePtr> LoansController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        auto clientId = req->getParameter("clientId");
        auto status = req->getParameter("status");
        int offset = 0, limit = 200;
        if (!req->getParameter("offset").empty()) offset = std::stoi(req->getParameter("offset"));
        if (!req->getParameter("limit").empty()) limit = std::stoi(req->getParameter("limit"));
        co_return ApiResponse::httpOk(co_await svc().listLoans(*ctx, clientId, status, offset, limit));
    TRY_END
}

Task<HttpResponsePtr> LoansController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        auto resp = ApiResponse::httpOk(co_await svc().createLoan(*ctx, *body), "Loan created");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::calculateSchedule(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(svc().calculateLoanSchedule(*ctx, *body));
    TRY_END
}

Task<HttpResponsePtr> LoansController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().getLoan(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::update(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().updateLoan(*ctx, id, kByExternalId, *body),
                                      "Loan updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::remove(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_await svc().deleteLoan(*ctx, id, kByExternalId);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Loan deleted");
    TRY_END
}

Task<HttpResponsePtr> LoansController::command(HttpRequestPtr req, std::string id, std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().handleLoanCommand(*ctx, id, kByExternalId, cmd, b));
    TRY_END
}

Task<HttpResponsePtr> LoansController::templateEndpoint(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().loanTemplate(*ctx));
}

Task<HttpResponsePtr> LoansController::approvedAmountHistory(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().getApprovedAmountHistory(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::updateApprovedAmount(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().updateApprovedAmount(*ctx, id, kByExternalId, *body), "Approved amount updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::updateAvailableDisbursementAmount(HttpRequestPtr req,
                                                                        std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().updateAvailableDisbursementAmount(*ctx, id, kByExternalId, *body),
            "Available disbursement amount updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::recalculateSchedule(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().recalculateLoanSchedule(*ctx, id, kByExternalId, b));
    TRY_END
}

// ============================================================================
// charges
// ============================================================================

Task<HttpResponsePtr> LoansController::chargesGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listLoanCharges(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::chargesTemplate(HttpRequestPtr req, std::string) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().loanChargeTemplate(*ctx));
}

Task<HttpResponsePtr> LoansController::chargesGetDetail(HttpRequestPtr req, std::string id,
                                                       std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getLoanCharge(*ctx, id, kByExternalId, chargeId, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::chargesCreate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        auto resp = ApiResponse::httpOk(co_await svc().createLoanCharge(*ctx, id, kByExternalId, *body),
                                        "Loan charge created");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::chargesUpdate(HttpRequestPtr req, std::string id,
                                                    std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().updateLoanCharge(*ctx, id, kByExternalId, chargeId, kByExternalId, *body),
            "Loan charge updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::chargesCommand(HttpRequestPtr req, std::string id,
                                                     std::string chargeId, std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().handleLoanChargeCommand(
            *ctx, id, kByExternalId, chargeId, kByExternalId, cmd, b));
    TRY_END
}

Task<HttpResponsePtr> LoansController::chargesDelete(HttpRequestPtr req, std::string id,
                                                    std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_await svc().deleteLoanCharge(*ctx, id, kByExternalId, chargeId, kByExternalId);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Loan charge deleted");
    TRY_END
}

// ============================================================================
// collaterals
// ============================================================================

Task<HttpResponsePtr> LoansController::collateralsGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listLoanCollaterals(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::collateralsTemplate(HttpRequestPtr req, std::string) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().loanCollateralTemplate(*ctx));
}

Task<HttpResponsePtr> LoansController::collateralsGetDetail(HttpRequestPtr req, std::string id,
                                                           std::string collateralId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getLoanCollateral(*ctx, id, kByExternalId, collateralId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::collateralsCreate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        auto resp = ApiResponse::httpOk(co_await svc().createLoanCollateral(*ctx, id, kByExternalId, *body),
                                        "Collateral created");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::collateralsUpdate(HttpRequestPtr req, std::string id,
                                                        std::string collateralId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().updateLoanCollateral(*ctx, id, kByExternalId, collateralId, *body),
            "Collateral updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::collateralsDelete(HttpRequestPtr req, std::string,
                                                        std::string collateralId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_await svc().deleteLoanCollateral(*ctx, collateralId);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Collateral deleted");
    TRY_END
}

// ============================================================================
// guarantors
// ============================================================================

Task<HttpResponsePtr> LoansController::guarantorsGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listLoanGuarantors(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::guarantorsTemplate(HttpRequestPtr req, std::string) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().loanGuarantorTemplate(*ctx));
}

Task<HttpResponsePtr> LoansController::guarantorsGetDetail(HttpRequestPtr req, std::string id,
                                                          std::string guarantorId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getLoanGuarantor(*ctx, id, kByExternalId, guarantorId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::guarantorsCreate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        auto resp = ApiResponse::httpOk(co_await svc().createLoanGuarantor(*ctx, id, kByExternalId, *body),
                                        "Guarantor created");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::guarantorsUpdate(HttpRequestPtr req, std::string id,
                                                       std::string guarantorId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().updateLoanGuarantor(*ctx, id, kByExternalId, guarantorId, *body),
            "Guarantor updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::guarantorsDelete(HttpRequestPtr req, std::string id,
                                                       std::string guarantorId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_await svc().deleteLoanGuarantor(*ctx, id, kByExternalId, guarantorId);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Guarantor deleted");
    TRY_END
}

// ============================================================================
// disbursement details
// ============================================================================

Task<HttpResponsePtr> LoansController::disbursementGetDetail(HttpRequestPtr req, std::string id,
                                                             std::string disbursementId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getLoanDisbursementDetail(*ctx, id, kByExternalId, disbursementId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::disbursementUpdateDate(HttpRequestPtr req, std::string id,
                                                              std::string disbursementId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().updateLoanDisbursementDate(*ctx, id, kByExternalId, disbursementId, *body),
            "Disbursement date updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::disbursementsEdit(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().editLoanDisbursements(*ctx, id, kByExternalId, *body), "Disbursements updated");
    TRY_END
}

// ============================================================================
// interest pauses
// ============================================================================

Task<HttpResponsePtr> LoansController::interestPausesGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listInterestPauses(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::interestPausesCreate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        auto resp =
            ApiResponse::httpOk(co_await svc().createInterestPause(*ctx, id, kByExternalId, *body),
                                "Interest pause created");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::interestPausesUpdate(HttpRequestPtr req, std::string id,
                                                            std::string variationId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().updateInterestPause(*ctx, id, kByExternalId, variationId, *body),
            "Interest pause updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::interestPausesDelete(HttpRequestPtr req, std::string id,
                                                            std::string variationId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_await svc().deleteInterestPause(*ctx, id, kByExternalId, variationId);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Interest pause deleted");
    TRY_END
}

// ============================================================================
// postdated checks
// ============================================================================

Task<HttpResponsePtr> LoansController::postdatedChecksGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listPostdatedChecks(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::postdatedChecksGetDetail(HttpRequestPtr req, std::string id,
                                                                std::string checkId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getPostdatedCheck(*ctx, id, kByExternalId, checkId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::postdatedChecksCreate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        auto resp =
            ApiResponse::httpOk(co_await svc().createPostdatedCheck(*ctx, id, kByExternalId, *body),
                                "Post-dated check created");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::postdatedChecksUpdate(HttpRequestPtr req, std::string,
                                                             std::string checkId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().updatePostdatedCheck(*ctx, checkId, *body),
                                      "Post-dated check updated");
    TRY_END
}

Task<HttpResponsePtr> LoansController::postdatedChecksDelete(HttpRequestPtr req, std::string,
                                                             std::string checkId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_await svc().deletePostdatedCheck(*ctx, checkId);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Post-dated check deleted");
    TRY_END
}

// ============================================================================
// buydown fees / capitalized income (read-only)
// ============================================================================

Task<HttpResponsePtr> LoansController::buydownFeesGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listBuydownFees(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::buydownFeesGetDetail(HttpRequestPtr req, std::string id,
                                                            std::string txnId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getBuydownFee(*ctx, id, kByExternalId, txnId, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::capitalizedIncomeGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listCapitalizedIncome(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::capitalizedIncomeGetDetail(HttpRequestPtr req, std::string id,
                                                                  std::string txnId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getCapitalizedIncome(*ctx, id, kByExternalId, txnId, kByExternalId));
    TRY_END
}

// ============================================================================
// delinquency sub-resources
// ============================================================================

Task<HttpResponsePtr> LoansController::delinquencyActionsGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listDelinquencyActions(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::delinquencyActionsCreate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        auto resp = ApiResponse::httpOk(
            co_await svc().createDelinquencyAction(*ctx, id, kByExternalId, *body), "Delinquency action recorded");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::delinquencyTagsGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listDelinquencyTagHistory(*ctx, id, kByExternalId));
    TRY_END
}

// ============================================================================
// transactions
// ============================================================================

Task<HttpResponsePtr> LoansController::transactionsGetAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().listLoanTransactions(*ctx, id, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::transactionsTemplate(HttpRequestPtr req, std::string) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().loanTransactionTemplate(*ctx));
}

Task<HttpResponsePtr> LoansController::transactionsGetDetail(HttpRequestPtr req, std::string id,
                                                             std::string txnId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().getLoanTransaction(*ctx, id, kByExternalId, txnId, kByExternalId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::transactionsCreate(HttpRequestPtr req, std::string id,
                                                          std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    TRY_BEGIN
        auto resp =
            ApiResponse::httpOk(co_await svc().createLoanTransaction(*ctx, id, kByExternalId, cmd, b),
                                "Loan transaction created");
        resp->setStatusCode(k201Created);
        co_return resp;
    TRY_END
}

Task<HttpResponsePtr> LoansController::transactionsAdjust(HttpRequestPtr req, std::string id,
                                                          std::string txnId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    TRY_BEGIN
        co_return ApiResponse::httpOk(
            co_await svc().adjustLoanTransaction(*ctx, id, kByExternalId, txnId, kByExternalId, b),
            "Loan transaction adjusted");
    TRY_END
}

Task<HttpResponsePtr> LoansController::transactionsUndoWaiveCharge(HttpRequestPtr req, std::string id,
                                                                  std::string txnId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().undoWaiveChargeTransaction(
            *ctx, id, kByExternalId, txnId, kByExternalId));
    TRY_END
}

// ============================================================================
// reassignment / GLIM / COB
// ============================================================================

Task<HttpResponsePtr> LoansController::reassignmentTemplate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().loanReassignmentTemplate(*ctx));
}

Task<HttpResponsePtr> LoansController::reassignmentCreate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().reassignLoans(*ctx, *body), "Loans reassigned");
    TRY_END
}

Task<HttpResponsePtr> LoansController::glimGetDetails(HttpRequestPtr req, std::string glimId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().getGlimAccount(*ctx, glimId));
    TRY_END
}

Task<HttpResponsePtr> LoansController::glimCommand(HttpRequestPtr req, std::string glimId,
                                                  std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().handleGlimCommand(*ctx, glimId, cmd, b));
    TRY_END
}

Task<HttpResponsePtr> LoansController::cobCatchUp(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    TRY_BEGIN
        co_return ApiResponse::httpOk(co_await svc().runLoanCobCatchUp(*ctx));
    TRY_END
}

Task<HttpResponsePtr> LoansController::cobCatchUpStatus(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().isCobCatchUpRunning(*ctx));
}

Task<HttpResponsePtr> LoansController::lockedLoans(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().listLockedLoans(*ctx));
}

Task<HttpResponsePtr> LoansController::oldestCobClosedLoan(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().oldestCobClosedLoan(*ctx));
}

#undef TRY_BEGIN
#undef TRY_END
