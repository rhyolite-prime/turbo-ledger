//
// Phase 6 — loans (126 endpoints in Fineract's inventory). This controller
// implements the `:loanId`-addressed branch only; the parallel
// `external-id/:loanExternalId/...` mirror that Fineract (and this
// codebase's PortfolioService, via its idOrExternalId/byExternalId
// parameters) also supports at every level is intentionally NOT wired here
// to keep the route surface manageable — see IMPLEMENTATION_PLAN.md /
// session notes for the explicit scope call. `downloadtemplate`/
// `uploadtemplate` CSV bulk-import endpoints and `at-date/*` point-in-time
// endpoints are likewise out of scope (consistent with the same omissions
// made in earlier phases for Accounting/DAM CSV bulk endpoints).
//
// Sub-resources folded into this single controller class (matching the
// DAM SavingsAccountsController precedent of folding charges/transactions
// into one class per aggregate root): charges, collaterals, guarantors,
// disbursement details, interest pauses, postdated checks, buydown fees
// (read-only), capitalized income (read-only), delinquency actions/tags
// (read-only), transactions, reassignment, GLIM, and the COB catch-up
// surface.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class LoansController : public drogon::HttpController<LoansController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/loans/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        // ---- core CRUD + lifecycle ------------------------------------------
        ADD_METHOD_TO(LoansController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::calculateSchedule, std::string(PREFIX) + "calculate-schedule", Post,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(LoansController::update, std::string(PREFIX) + "{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoansController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(LoansController::command, std::string(PREFIX) + "{1}/command/{2}", Post, Options,
                     FILTER);
        ADD_METHOD_TO(LoansController::templateEndpoint, std::string(PREFIX) + "template", Get, Options,
                     FILTER);
        ADD_METHOD_TO(LoansController::approvedAmountHistory,
                     std::string(PREFIX) + "{1}/approved-amount-history", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::updateApprovedAmount,
                     std::string(PREFIX) + "{1}/approved-amount/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoansController::updateAvailableDisbursementAmount,
                     std::string(PREFIX) + "{1}/available-disbursement-amount/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(LoansController::recalculateSchedule, std::string(PREFIX) + "{1}/schedule", Post,
                     Options, FILTER);

        // ---- charges ----------------------------------------------------------
        ADD_METHOD_TO(LoansController::chargesGetAll, std::string(PREFIX) + "{1}/charges/get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::chargesTemplate, std::string(PREFIX) + "{1}/charges/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::chargesGetDetail,
                     std::string(PREFIX) + "{1}/charges/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::chargesCreate, std::string(PREFIX) + "{1}/charges/create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::chargesUpdate, std::string(PREFIX) + "{1}/charges/{2}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::chargesCommand,
                     std::string(PREFIX) + "{1}/charges/{2}/command/{3}", Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::chargesDelete, std::string(PREFIX) + "{1}/charges/{2}/delete",
                     Delete, Options, FILTER);

        // ---- collaterals ---------------------------------------------------------
        ADD_METHOD_TO(LoansController::collateralsGetAll, std::string(PREFIX) + "{1}/collaterals/get-all",
                     Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::collateralsTemplate,
                     std::string(PREFIX) + "{1}/collaterals/template", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::collateralsGetDetail,
                     std::string(PREFIX) + "{1}/collaterals/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::collateralsCreate, std::string(PREFIX) + "{1}/collaterals/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::collateralsUpdate,
                     std::string(PREFIX) + "{1}/collaterals/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoansController::collateralsDelete,
                     std::string(PREFIX) + "{1}/collaterals/{2}/delete", Delete, Options, FILTER);

        // ---- guarantors -----------------------------------------------------------
        ADD_METHOD_TO(LoansController::guarantorsGetAll, std::string(PREFIX) + "{1}/guarantors/get-all",
                     Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::guarantorsTemplate, std::string(PREFIX) + "{1}/guarantors/template",
                     Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::guarantorsGetDetail,
                     std::string(PREFIX) + "{1}/guarantors/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::guarantorsCreate, std::string(PREFIX) + "{1}/guarantors/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::guarantorsUpdate,
                     std::string(PREFIX) + "{1}/guarantors/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoansController::guarantorsDelete,
                     std::string(PREFIX) + "{1}/guarantors/{2}/delete", Delete, Options, FILTER);

        // ---- disbursement details -----------------------------------------------
        ADD_METHOD_TO(LoansController::disbursementGetDetail,
                     std::string(PREFIX) + "{1}/disbursements/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::disbursementUpdateDate,
                     std::string(PREFIX) + "{1}/disbursements/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoansController::disbursementsEdit, std::string(PREFIX) + "{1}/disbursements/edit",
                     Post, Options, FILTER);

        // ---- interest pauses ----------------------------------------------------
        ADD_METHOD_TO(LoansController::interestPausesGetAll,
                     std::string(PREFIX) + "{1}/interest-pauses/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::interestPausesCreate,
                     std::string(PREFIX) + "{1}/interest-pauses/create", Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::interestPausesUpdate,
                     std::string(PREFIX) + "{1}/interest-pauses/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoansController::interestPausesDelete,
                     std::string(PREFIX) + "{1}/interest-pauses/{2}/delete", Delete, Options, FILTER);

        // ---- postdated checks ---------------------------------------------------
        ADD_METHOD_TO(LoansController::postdatedChecksGetAll,
                     std::string(PREFIX) + "{1}/postdatedchecks/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::postdatedChecksGetDetail,
                     std::string(PREFIX) + "{1}/postdatedchecks/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::postdatedChecksCreate,
                     std::string(PREFIX) + "{1}/postdatedchecks/create", Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::postdatedChecksUpdate,
                     std::string(PREFIX) + "{1}/postdatedchecks/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoansController::postdatedChecksDelete,
                     std::string(PREFIX) + "{1}/postdatedchecks/{2}/delete", Delete, Options, FILTER);

        // ---- buydown fees / capitalized income (read-only) -----------------------
        ADD_METHOD_TO(LoansController::buydownFeesGetAll, std::string(PREFIX) + "{1}/buydown-fees/get-all",
                     Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::buydownFeesGetDetail,
                     std::string(PREFIX) + "{1}/buydown-fees/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::capitalizedIncomeGetAll,
                     std::string(PREFIX) + "{1}/capitalized-income/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::capitalizedIncomeGetDetail,
                     std::string(PREFIX) + "{1}/capitalized-income/{2}/get-detail", Get, Options, FILTER);

        // ---- delinquency sub-resources --------------------------------------------
        ADD_METHOD_TO(LoansController::delinquencyActionsGetAll,
                     std::string(PREFIX) + "{1}/delinquency-actions/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::delinquencyActionsCreate,
                     std::string(PREFIX) + "{1}/delinquency-actions/create", Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::delinquencyTagsGetAll,
                     std::string(PREFIX) + "{1}/delinquencytags/get-all", Get, Options, FILTER);

        // ---- transactions -----------------------------------------------------------
        ADD_METHOD_TO(LoansController::transactionsGetAll, std::string(PREFIX) + "{1}/transactions/get-all",
                     Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::transactionsTemplate,
                     std::string(PREFIX) + "{1}/transactions/template", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::transactionsGetDetail,
                     std::string(PREFIX) + "{1}/transactions/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::transactionsCreate,
                     std::string(PREFIX) + "{1}/transactions/command/{2}", Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::transactionsAdjust,
                     std::string(PREFIX) + "{1}/transactions/{2}/adjust", Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::transactionsUndoWaiveCharge,
                     std::string(PREFIX) + "{1}/transactions/{2}/undo-waive-charge", Put, Options, FILTER);

        // ---- reassignment / GLIM / COB -----------------------------------------------
        ADD_METHOD_TO(LoansController::reassignmentTemplate, std::string(PREFIX) + "reassignment/template",
                     Get, Options, FILTER);
        ADD_METHOD_TO(LoansController::reassignmentCreate, std::string(PREFIX) + "reassignment/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(LoansController::glimGetDetails, std::string(PREFIX) + "glim/{1}/get-detail", Get,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::glimCommand, std::string(PREFIX) + "glim/{1}/command/{2}", Post,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::cobCatchUp, std::string(PREFIX) + "cob-catch-up/create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::cobCatchUpStatus, std::string(PREFIX) + "cob-catch-up/status", Get,
                     Options, FILTER);
        ADD_METHOD_TO(LoansController::lockedLoans, std::string(PREFIX) + "locked/get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(LoansController::oldestCobClosedLoan, std::string(PREFIX) + "oldest-cob-closed", Get,
                     Options, FILTER);
    METHOD_LIST_END

    // core
    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> calculateSchedule(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string id, std::string cmd);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> approvedAmountHistory(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> updateApprovedAmount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> updateAvailableDisbursementAmount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> recalculateSchedule(HttpRequestPtr req, std::string id);

    // charges
    Task<HttpResponsePtr> chargesGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargesTemplate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargesGetDetail(HttpRequestPtr req, std::string id, std::string chargeId);
    Task<HttpResponsePtr> chargesCreate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargesUpdate(HttpRequestPtr req, std::string id, std::string chargeId);
    Task<HttpResponsePtr> chargesCommand(HttpRequestPtr req, std::string id, std::string chargeId,
                                        std::string cmd);
    Task<HttpResponsePtr> chargesDelete(HttpRequestPtr req, std::string id, std::string chargeId);

    // collaterals
    Task<HttpResponsePtr> collateralsGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> collateralsTemplate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> collateralsGetDetail(HttpRequestPtr req, std::string id, std::string collateralId);
    Task<HttpResponsePtr> collateralsCreate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> collateralsUpdate(HttpRequestPtr req, std::string id, std::string collateralId);
    Task<HttpResponsePtr> collateralsDelete(HttpRequestPtr req, std::string id, std::string collateralId);

    // guarantors
    Task<HttpResponsePtr> guarantorsGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> guarantorsTemplate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> guarantorsGetDetail(HttpRequestPtr req, std::string id, std::string guarantorId);
    Task<HttpResponsePtr> guarantorsCreate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> guarantorsUpdate(HttpRequestPtr req, std::string id, std::string guarantorId);
    Task<HttpResponsePtr> guarantorsDelete(HttpRequestPtr req, std::string id, std::string guarantorId);

    // disbursement details
    Task<HttpResponsePtr> disbursementGetDetail(HttpRequestPtr req, std::string id,
                                               std::string disbursementId);
    Task<HttpResponsePtr> disbursementUpdateDate(HttpRequestPtr req, std::string id,
                                                std::string disbursementId);
    Task<HttpResponsePtr> disbursementsEdit(HttpRequestPtr req, std::string id);

    // interest pauses
    Task<HttpResponsePtr> interestPausesGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> interestPausesCreate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> interestPausesUpdate(HttpRequestPtr req, std::string id, std::string variationId);
    Task<HttpResponsePtr> interestPausesDelete(HttpRequestPtr req, std::string id, std::string variationId);

    // postdated checks
    Task<HttpResponsePtr> postdatedChecksGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> postdatedChecksGetDetail(HttpRequestPtr req, std::string id, std::string checkId);
    Task<HttpResponsePtr> postdatedChecksCreate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> postdatedChecksUpdate(HttpRequestPtr req, std::string id, std::string checkId);
    Task<HttpResponsePtr> postdatedChecksDelete(HttpRequestPtr req, std::string id, std::string checkId);

    // buydown fees / capitalized income
    Task<HttpResponsePtr> buydownFeesGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> buydownFeesGetDetail(HttpRequestPtr req, std::string id, std::string txnId);
    Task<HttpResponsePtr> capitalizedIncomeGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> capitalizedIncomeGetDetail(HttpRequestPtr req, std::string id, std::string txnId);

    // delinquency
    Task<HttpResponsePtr> delinquencyActionsGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> delinquencyActionsCreate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> delinquencyTagsGetAll(HttpRequestPtr req, std::string id);

    // transactions
    Task<HttpResponsePtr> transactionsGetAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> transactionsTemplate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> transactionsGetDetail(HttpRequestPtr req, std::string id, std::string txnId);
    Task<HttpResponsePtr> transactionsCreate(HttpRequestPtr req, std::string id, std::string cmd);
    Task<HttpResponsePtr> transactionsAdjust(HttpRequestPtr req, std::string id, std::string txnId);
    Task<HttpResponsePtr> transactionsUndoWaiveCharge(HttpRequestPtr req, std::string id, std::string txnId);

    // reassignment / GLIM / COB
    Task<HttpResponsePtr> reassignmentTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> reassignmentCreate(HttpRequestPtr req);
    Task<HttpResponsePtr> glimGetDetails(HttpRequestPtr req, std::string glimId);
    Task<HttpResponsePtr> glimCommand(HttpRequestPtr req, std::string glimId, std::string cmd);
    Task<HttpResponsePtr> cobCatchUp(HttpRequestPtr req);
    Task<HttpResponsePtr> cobCatchUpStatus(HttpRequestPtr req);
    Task<HttpResponsePtr> lockedLoans(HttpRequestPtr req);
    Task<HttpResponsePtr> oldestCobClosedLoan(HttpRequestPtr req);
};
