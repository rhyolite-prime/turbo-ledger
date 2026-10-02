//
// Phase 6 — Lending & Shares (Portfolio). ~220 of the 224 inventoried
// endpoints across loans/loanproducts/rescheduleloans/
// loan-collateral-management/floatingrates/rates/delinquency/
// provisioningcategory/provisioningcriteria/products(share)/shareproduct/
// accounts(share)/external-asset-owners/CreditBureauConfiguration/
// creditBureauIntegration — see ENDPOINT_INVENTORY.md's Portfolio section.
//
// EXCLUDED FROM THIS PHASE (disclosed, not silent): `mixmapping`/
// `mixreport`/`mixtaxonomy` (4 endpoints) are XBRL/MIX regulatory-report
// taxonomy mapping — a reporting-pipeline concern unrelated to the lending
// domain model this phase builds, not mentioned anywhere in the Phase 6
// plan narrative, and belongs conceptually to a future Reporting phase.
//
// SCHEMA PROVENANCE: V001__baseline.sql's two tables
// (loanproduct_provisioning_entry / provisioning_history) are genuine
// ground truth (src/scripts/TlPortfolio.sql). Every other table
// (V003__phase6.sql, ~42 tables) is hand-designed against the Fineract API
// surface this phase targets — see that migration's header comment for the
// full provenance note and the list of deliberate simplifications vs. full
// Fineract (folded share price history, no separate transaction-charge
// allocation table, reschedule requests store new terms directly rather
// than per-installment diffs, one mock/deterministic credit bureau
// provider).
//
// ROUTING CONVENTION: matches every other service in this codebase
// (get-all/create/get-detail/{id}/update/{id}/delete/{id}/command/{cmd}/
// template) rather than literal Fineract paths — see
// DepositAccountManagementService.h / SavingsAccountsController.h for the
// established precedent this phase follows.
//
// CROSS-SERVICE DEPENDENCIES (deliberately not resolved, same precedent as
// every prior phase):
//   - client_id/group_id/office_id/loan_officer_id/charge_id/gl account ids
//     are trusted as given by the caller (owned by Customer/Group/
//     Organization/DepositAccountManagement/Accounting respectively). No
//     cross-service HTTP client exists in this codebase.
//   - "NPA provisioning entries post to Accounting's provisioningentries"
//     (exit criterion): there is no synchronous cross-service call
//     available (see above), so — exactly like DAM's GL-posting precedent
//     in Phase 5 — runProvisioningJob() computes the reserve lines,
//     persists them into the ground-truth loanproduct_provisioning_entry /
//     provisioning_history tables, AND writes a turbo::outbox event
//     ("provisioningrun", "provisioningrun.computed") whose payload is
//     shaped exactly like Accounting's POST /provisioningentries body
//     (date/comments/entries[]/createjournalentries) — see
//     AccountingService::createProvisioningEntry's own header note, which
//     already anticipates this. A future relay/consumer replays the event
//     into a real Accounting provisioning entry, matching the established
//     outbox-relay architecture rather than a direct call.
//
// AMORTIZATION: declining-balance equal-installment (Fineract's default)
// and flat methods, both with optional grace periods on principal/interest.
// Day-count: configurable days-in-year (360/365) and days-in-month
// (30/actual) per product, actual-calendar dates via trantor::Date
// arithmetic (microseconds since epoch / 86400000000). Verified against
// hand-worked reference cases documented in PortfolioService.cc's
// amortization section and in IMPLEMENTATION_PLAN.md's Phase 6 entry — not
// a byte-exact golden-file suite (explicitly relaxed exit criterion, see
// IMPLEMENTATION_PLAN.md).
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_portfolio {

/// Error carrying an HTTP status + envelope globalisation code.
class ApiError : public std::runtime_error {
  public:
    ApiError(drogon::HttpStatusCode status, std::string message,
             std::string globalisationCode = "")
        : std::runtime_error(std::move(message)),
          status_(status),
          code_(std::move(globalisationCode)) {}
    drogon::HttpStatusCode status() const { return status_; }
    const std::string &globalisationCode() const { return code_; }

  private:
    drogon::HttpStatusCode status_;
    std::string code_;
};

// loan.status (Fineract-aligned)
enum LoanStatus : int {
    kLoanStatusSubmittedAndPendingApproval = 100,
    kLoanStatusApproved = 200,
    kLoanStatusActive = 300,
    kLoanStatusWithdrawnByClient = 400,
    kLoanStatusRejected = 500,
    kLoanStatusClosedObligationsMet = 600,
    kLoanStatusClosedWrittenOff = 601,
    kLoanStatusClosedReschedule = 602,
    kLoanStatusOverpaid = 700,
};

// share_account.status
enum ShareAccountStatus : int {
    kShareStatusSubmittedAndPendingApproval = 100,
    kShareStatusApproved = 200,
    kShareStatusActive = 300,
    kShareStatusRejected = 400,
    kShareStatusClosed = 500,
};

class PortfolioService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // =====================================================================
    // loanproducts (11) — includes productmix(4) and external-id mirrors
    // =====================================================================
    drogon::Task<Json::Value> listLoanProducts(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getLoanProduct(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> getLoanProductByExternalId(const turbo::RequestContext &ctx,
                                                         std::string externalId);
    drogon::Task<Json::Value> createLoanProduct(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> updateLoanProduct(const turbo::RequestContext &ctx, std::string id,
                                                Json::Value body);
    drogon::Task<Json::Value> updateLoanProductByExternalId(const turbo::RequestContext &ctx,
                                                            std::string externalId,
                                                            Json::Value body);
    Json::Value loanProductTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> listProductMix(const turbo::RequestContext &ctx, std::string productId);
    drogon::Task<Json::Value> createProductMix(const turbo::RequestContext &ctx, std::string productId,
                                               Json::Value body);
    drogon::Task<Json::Value> updateProductMix(const turbo::RequestContext &ctx, std::string productId,
                                               Json::Value body);
    drogon::Task<void> deleteProductMix(const turbo::RequestContext &ctx, std::string productId);

    // =====================================================================
    // floatingrates (4) + rates (4)
    // =====================================================================
    drogon::Task<Json::Value> listFloatingRates(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getFloatingRate(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createFloatingRate(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> updateFloatingRate(const turbo::RequestContext &ctx, std::string id,
                                                 Json::Value body);

    drogon::Task<Json::Value> listRates(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getRate(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createRate(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> updateRate(const turbo::RequestContext &ctx, std::string id,
                                         Json::Value body);

    // =====================================================================
    // delinquency (10): buckets + ranges
    // =====================================================================
    drogon::Task<Json::Value> listDelinquencyBuckets(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getDelinquencyBucket(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createDelinquencyBucket(const turbo::RequestContext &ctx,
                                                      Json::Value body);
    drogon::Task<Json::Value> updateDelinquencyBucket(const turbo::RequestContext &ctx, std::string id,
                                                      Json::Value body);
    drogon::Task<void> deleteDelinquencyBucket(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> listDelinquencyRanges(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getDelinquencyRange(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createDelinquencyRange(const turbo::RequestContext &ctx,
                                                     Json::Value body);
    drogon::Task<Json::Value> updateDelinquencyRange(const turbo::RequestContext &ctx, std::string id,
                                                     Json::Value body);
    drogon::Task<void> deleteDelinquencyRange(const turbo::RequestContext &ctx, std::string id);

    // =====================================================================
    // provisioningcategory (4) + provisioningcriteria (6)
    // =====================================================================
    drogon::Task<Json::Value> listProvisioningCategories(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createProvisioningCategory(const turbo::RequestContext &ctx,
                                                         Json::Value body);
    drogon::Task<Json::Value> updateProvisioningCategory(const turbo::RequestContext &ctx,
                                                         std::string id, Json::Value body);
    drogon::Task<void> deleteProvisioningCategory(const turbo::RequestContext &ctx, std::string id);

    drogon::Task<Json::Value> listProvisioningCriteria(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getProvisioningCriteria(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createProvisioningCriteria(const turbo::RequestContext &ctx,
                                                         Json::Value body);
    drogon::Task<Json::Value> updateProvisioningCriteria(const turbo::RequestContext &ctx,
                                                         std::string id, Json::Value body);
    drogon::Task<void> deleteProvisioningCriteria(const turbo::RequestContext &ctx, std::string id);
    Json::Value provisioningCriteriaTemplate(const turbo::RequestContext &ctx);

    /// Runs the delinquency+NPA classification + provisioning reserve
    /// computation for every active loan in the tenant. Not exposed on its
    /// own route in the inventory, but it is what `loans/catch-up` and the
    /// exit criteria ("delinquency job tags correctly" / "NPA provisioning
    /// entries post...") exercise. Idempotent: safe to re-run for the same
    /// asOfDate.
    drogon::Task<Json::Value> runDelinquencyAndProvisioningJob(const turbo::RequestContext &ctx,
                                                               const std::string &asOfDate);

    // =====================================================================
    // loans (126) — core + sub-resources. Methods taking `idOrExternalId`
    // plus `byExternalId` resolve once via resolveLoanId() so every
    // external-id-mirror route in the inventory is real (not trimmed).
    // =====================================================================
    drogon::Task<Json::Value> listLoans(const turbo::RequestContext &ctx, const std::string &clientId,
                                        const std::string &status, int offset, int limit);
    drogon::Task<Json::Value> getLoan(const turbo::RequestContext &ctx, std::string idOrExternalId,
                                      bool byExternalId);
    drogon::Task<Json::Value> createLoan(const turbo::RequestContext &ctx, Json::Value body);
    /// POST /loans?command=calculateLoanSchedule — pure calculator, no
    /// persistence.
    Json::Value calculateLoanSchedule(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateLoan(const turbo::RequestContext &ctx, std::string idOrExternalId,
                                         bool byExternalId, Json::Value body);
    drogon::Task<void> deleteLoan(const turbo::RequestContext &ctx, std::string idOrExternalId,
                                  bool byExternalId);
    Json::Value loanTemplate(const turbo::RequestContext &ctx);
    /// command: approve|reject|withdrawnByApplicant|undoApproval|
    ///   assignLoanOfficer|unassignLoanOfficer|disburse|undoDisbursal|
    ///   close|closeAsRescheduled|writeoff|recoverGuarantees
    drogon::Task<Json::Value> handleLoanCommand(const turbo::RequestContext &ctx,
                                                std::string idOrExternalId, bool byExternalId,
                                                std::string command, Json::Value body);
    drogon::Task<Json::Value> getApprovedAmountHistory(const turbo::RequestContext &ctx,
                                                       std::string idOrExternalId, bool byExternalId);
    drogon::Task<Json::Value> updateApprovedAmount(const turbo::RequestContext &ctx,
                                                   std::string idOrExternalId, bool byExternalId,
                                                   Json::Value body);
    drogon::Task<Json::Value> updateAvailableDisbursementAmount(const turbo::RequestContext &ctx,
                                                                std::string idOrExternalId,
                                                                bool byExternalId, Json::Value body);
    /// POST .../schedule — recompute + persist schedule for term variations.
    drogon::Task<Json::Value> recalculateLoanSchedule(const turbo::RequestContext &ctx,
                                                      std::string idOrExternalId, bool byExternalId,
                                                      Json::Value body);

    // ---- loan charges ------------------------------------------------------
    drogon::Task<Json::Value> listLoanCharges(const turbo::RequestContext &ctx,
                                              std::string idOrExternalId, bool byExternalId);
    Json::Value loanChargeTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getLoanCharge(const turbo::RequestContext &ctx,
                                            std::string idOrExternalId, bool byExternalId,
                                            std::string chargeIdOrExternalId, bool chargeByExternalId);
    drogon::Task<Json::Value> createLoanCharge(const turbo::RequestContext &ctx,
                                               std::string idOrExternalId, bool byExternalId,
                                               Json::Value body);
    drogon::Task<Json::Value> updateLoanCharge(const turbo::RequestContext &ctx,
                                               std::string idOrExternalId, bool byExternalId,
                                               std::string chargeIdOrExternalId, bool chargeByExternalId,
                                               Json::Value body);
    /// command: pay|waive|adjustment (via query or body "command")
    drogon::Task<Json::Value> handleLoanChargeCommand(const turbo::RequestContext &ctx,
                                                      std::string idOrExternalId, bool byExternalId,
                                                      std::string chargeIdOrExternalId,
                                                      bool chargeByExternalId, std::string command,
                                                      Json::Value body);
    drogon::Task<void> deleteLoanCharge(const turbo::RequestContext &ctx, std::string idOrExternalId,
                                       bool byExternalId, std::string chargeIdOrExternalId,
                                       bool chargeByExternalId);

    // ---- collaterals --------------------------------------------------------
    drogon::Task<Json::Value> listLoanCollaterals(const turbo::RequestContext &ctx,
                                                  std::string idOrExternalId, bool byExternalId);
    Json::Value loanCollateralTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getLoanCollateral(const turbo::RequestContext &ctx,
                                                std::string idOrExternalId, bool byExternalId,
                                                std::string collateralId);
    drogon::Task<Json::Value> createLoanCollateral(const turbo::RequestContext &ctx,
                                                   std::string idOrExternalId, bool byExternalId,
                                                   Json::Value body);
    drogon::Task<Json::Value> updateLoanCollateral(const turbo::RequestContext &ctx,
                                                   std::string idOrExternalId, bool byExternalId,
                                                   std::string collateralId, Json::Value body);
    drogon::Task<void> deleteLoanCollateral(const turbo::RequestContext &ctx, std::string collateralId);
    drogon::Task<Json::Value> getLoanCollateralManagement(const turbo::RequestContext &ctx,
                                                          std::string collateralId);

    // ---- guarantors -----------------------------------------------------------
    drogon::Task<Json::Value> listLoanGuarantors(const turbo::RequestContext &ctx,
                                                 std::string idOrExternalId, bool byExternalId);
    Json::Value loanGuarantorTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getLoanGuarantor(const turbo::RequestContext &ctx,
                                               std::string idOrExternalId, bool byExternalId,
                                               std::string guarantorId);
    drogon::Task<Json::Value> createLoanGuarantor(const turbo::RequestContext &ctx,
                                                  std::string idOrExternalId, bool byExternalId,
                                                  Json::Value body);
    drogon::Task<Json::Value> updateLoanGuarantor(const turbo::RequestContext &ctx,
                                                  std::string idOrExternalId, bool byExternalId,
                                                  std::string guarantorId, Json::Value body);
    drogon::Task<void> deleteLoanGuarantor(const turbo::RequestContext &ctx,
                                          std::string idOrExternalId, bool byExternalId,
                                          std::string guarantorId);

    // ---- disbursement details -------------------------------------------------
    drogon::Task<Json::Value> getLoanDisbursementDetail(const turbo::RequestContext &ctx,
                                                        std::string idOrExternalId, bool byExternalId,
                                                        std::string disbursementId);
    drogon::Task<Json::Value> updateLoanDisbursementDate(const turbo::RequestContext &ctx,
                                                         std::string idOrExternalId, bool byExternalId,
                                                         std::string disbursementId, Json::Value body);
    drogon::Task<Json::Value> editLoanDisbursements(const turbo::RequestContext &ctx,
                                                    std::string idOrExternalId, bool byExternalId,
                                                    Json::Value body);

    // ---- interest pauses --------------------------------------------------------
    drogon::Task<Json::Value> listInterestPauses(const turbo::RequestContext &ctx,
                                                 std::string idOrExternalId, bool byExternalId);
    drogon::Task<Json::Value> createInterestPause(const turbo::RequestContext &ctx,
                                                  std::string idOrExternalId, bool byExternalId,
                                                  Json::Value body);
    drogon::Task<Json::Value> updateInterestPause(const turbo::RequestContext &ctx,
                                                  std::string idOrExternalId, bool byExternalId,
                                                  std::string variationId, Json::Value body);
    drogon::Task<void> deleteInterestPause(const turbo::RequestContext &ctx,
                                          std::string idOrExternalId, bool byExternalId,
                                          std::string variationId);

    // ---- postdated checks ---------------------------------------------------
    drogon::Task<Json::Value> listPostdatedChecks(const turbo::RequestContext &ctx,
                                                  std::string idOrExternalId, bool byExternalId);
    drogon::Task<Json::Value> getPostdatedCheck(const turbo::RequestContext &ctx,
                                                std::string idOrExternalId, bool byExternalId,
                                                std::string installmentOrCheckId);
    drogon::Task<Json::Value> createPostdatedCheck(const turbo::RequestContext &ctx,
                                                   std::string idOrExternalId, bool byExternalId,
                                                   Json::Value body);
    drogon::Task<Json::Value> updatePostdatedCheck(const turbo::RequestContext &ctx,
                                                   std::string checkId, Json::Value body);
    drogon::Task<void> deletePostdatedCheck(const turbo::RequestContext &ctx, std::string checkId);

    // ---- buydown fees / capitalized income (read-only amortization views) -----
    drogon::Task<Json::Value> listBuydownFees(const turbo::RequestContext &ctx,
                                              std::string idOrExternalId, bool byExternalId);
    drogon::Task<Json::Value> getBuydownFee(const turbo::RequestContext &ctx,
                                            std::string idOrExternalId, bool byExternalId,
                                            std::string txnIdOrExternalId, bool txnByExternalId);
    drogon::Task<Json::Value> listCapitalizedIncome(const turbo::RequestContext &ctx,
                                                    std::string idOrExternalId, bool byExternalId);
    drogon::Task<Json::Value> getCapitalizedIncome(const turbo::RequestContext &ctx,
                                                   std::string idOrExternalId, bool byExternalId,
                                                   std::string txnIdOrExternalId, bool txnByExternalId);

    // ---- delinquency sub-resources ----------------------------------------------
    drogon::Task<Json::Value> listDelinquencyActions(const turbo::RequestContext &ctx,
                                                     std::string idOrExternalId, bool byExternalId);
    drogon::Task<Json::Value> createDelinquencyAction(const turbo::RequestContext &ctx,
                                                      std::string idOrExternalId, bool byExternalId,
                                                      Json::Value body);
    drogon::Task<Json::Value> listDelinquencyTagHistory(const turbo::RequestContext &ctx,
                                                        std::string idOrExternalId, bool byExternalId);

    // ---- transactions -------------------------------------------------------------
    drogon::Task<Json::Value> listLoanTransactions(const turbo::RequestContext &ctx,
                                                   std::string idOrExternalId, bool byExternalId);
    Json::Value loanTransactionTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getLoanTransaction(const turbo::RequestContext &ctx,
                                                 std::string idOrExternalId, bool byExternalId,
                                                 std::string txnIdOrExternalId, bool txnByExternalId);
    /// command: repayment|merchantIssuedRefund|payoutRefund|goodwillCredit|
    ///   waiveInterest|writeoff|close|recoveryPayment|foreclosure|
    ///   chargeOff|reAmortize|reAge|capitalizedIncome|buyDownFee
    drogon::Task<Json::Value> createLoanTransaction(const turbo::RequestContext &ctx,
                                                    std::string idOrExternalId, bool byExternalId,
                                                    std::string command, Json::Value body);
    /// POST .../transactions/{id}?command=adjust  (also undoWriteOff-style)
    drogon::Task<Json::Value> adjustLoanTransaction(const turbo::RequestContext &ctx,
                                                    std::string idOrExternalId, bool byExternalId,
                                                    std::string txnIdOrExternalId, bool txnByExternalId,
                                                    Json::Value body);
    /// PUT .../transactions/{id} — undo a waive-charge transaction.
    drogon::Task<Json::Value> undoWaiveChargeTransaction(const turbo::RequestContext &ctx,
                                                         std::string idOrExternalId, bool byExternalId,
                                                         std::string txnIdOrExternalId,
                                                         bool txnByExternalId);

    // ---- loan reassignment --------------------------------------------------------
    Json::Value loanReassignmentTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> reassignLoans(const turbo::RequestContext &ctx, Json::Value body);

    // ---- GLIM (Group Loan Individual Monitoring) -----------------------------------
    drogon::Task<Json::Value> getGlimAccount(const turbo::RequestContext &ctx, std::string glimId);
    /// command: approve|undoApproval|reject|disburse|undoDisbursal
    drogon::Task<Json::Value> handleGlimCommand(const turbo::RequestContext &ctx, std::string glimId,
                                                std::string command, Json::Value body);

    // ---- COB (close-of-business) batch surface — see .cc for honest scoping ---------
    drogon::Task<Json::Value> runLoanCobCatchUp(const turbo::RequestContext &ctx);
    Json::Value isCobCatchUpRunning(const turbo::RequestContext &ctx);
    Json::Value listLockedLoans(const turbo::RequestContext &ctx);
    Json::Value oldestCobClosedLoan(const turbo::RequestContext &ctx);

    // =====================================================================
    // rescheduleloans (5)
    // =====================================================================
    drogon::Task<Json::Value> listRescheduleRequests(const turbo::RequestContext &ctx,
                                                     const std::string &loanId);
    drogon::Task<Json::Value> getRescheduleRequest(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createRescheduleRequest(const turbo::RequestContext &ctx,
                                                      Json::Value body);
    /// command: approve|reject
    drogon::Task<Json::Value> handleRescheduleCommand(const turbo::RequestContext &ctx, std::string id,
                                                      std::string command, Json::Value body);
    Json::Value rescheduleTemplate(const turbo::RequestContext &ctx);

    // =====================================================================
    // shares: products(6) + shareproduct dividends(5) + accounts(8)
    // =====================================================================
    drogon::Task<Json::Value> listShareProducts(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getShareProduct(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createShareProduct(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> updateShareProduct(const turbo::RequestContext &ctx, std::string id,
                                                 Json::Value body);
    Json::Value shareProductTemplate(const turbo::RequestContext &ctx);
    /// command: activate|close
    drogon::Task<Json::Value> handleShareProductCommand(const turbo::RequestContext &ctx,
                                                        std::string id, std::string command,
                                                        Json::Value body);

    drogon::Task<Json::Value> listShareProductDividends(const turbo::RequestContext &ctx,
                                                        std::string productId);
    drogon::Task<Json::Value> getShareProductDividend(const turbo::RequestContext &ctx,
                                                      std::string productId, std::string dividendId);
    drogon::Task<Json::Value> createShareProductDividend(const turbo::RequestContext &ctx,
                                                         std::string productId, Json::Value body);
    drogon::Task<Json::Value> updateShareProductDividend(const turbo::RequestContext &ctx,
                                                         std::string productId, std::string dividendId,
                                                         Json::Value body);
    drogon::Task<void> deleteShareProductDividend(const turbo::RequestContext &ctx,
                                                  std::string productId, std::string dividendId);

    drogon::Task<Json::Value> listShareAccounts(const turbo::RequestContext &ctx,
                                                const std::string &clientId);
    drogon::Task<Json::Value> getShareAccount(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createShareAccount(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> updateShareAccount(const turbo::RequestContext &ctx, std::string id,
                                                 Json::Value body);
    Json::Value shareAccountTemplate(const turbo::RequestContext &ctx);
    /// command: approve|undoApproval|reject|activate|close|
    ///   applyadditionalshares|approveadditionalshares|
    ///   rejectadditionalshares|redeemshares
    drogon::Task<Json::Value> handleShareAccountCommand(const turbo::RequestContext &ctx,
                                                        std::string id, std::string command,
                                                        Json::Value body);

    // =====================================================================
    // external-asset-owners (12)
    // =====================================================================
    drogon::Task<Json::Value> listAssetOwnerTransfers(const turbo::RequestContext &ctx,
                                                      const std::string &loanId);
    drogon::Task<Json::Value> searchAssetOwnerTransfers(const turbo::RequestContext &ctx,
                                                        Json::Value body);
    drogon::Task<Json::Value> getActiveAssetOwnerTransfer(const turbo::RequestContext &ctx,
                                                          const std::string &loanId);
    drogon::Task<Json::Value> createAssetOwnerTransfer(const turbo::RequestContext &ctx,
                                                       std::string loanIdOrExternalId,
                                                       bool byExternalId, Json::Value body);
    /// command for an existing transfer: cancel|buyback
    drogon::Task<Json::Value> handleAssetOwnerTransferCommand(const turbo::RequestContext &ctx,
                                                              std::string transferId,
                                                              std::string command, Json::Value body);
    drogon::Task<Json::Value> listTransferJournalEntries(const turbo::RequestContext &ctx,
                                                         std::string transferId);
    drogon::Task<Json::Value> listOwnerJournalEntries(const turbo::RequestContext &ctx,
                                                      std::string ownerExternalId);
    drogon::Task<Json::Value> listLoanProductAttributes(const turbo::RequestContext &ctx,
                                                        std::string loanProductId);
    drogon::Task<Json::Value> createLoanProductAttribute(const turbo::RequestContext &ctx,
                                                         std::string loanProductId, Json::Value body);
    drogon::Task<Json::Value> updateLoanProductAttribute(const turbo::RequestContext &ctx,
                                                         std::string loanProductId, std::string id,
                                                         Json::Value body);

    // =====================================================================
    // CreditBureauConfiguration (12) + creditBureauIntegration (5)
    // =====================================================================
    drogon::Task<Json::Value> listCreditBureaus(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> listOrganisationCreditBureaus(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> addOrganisationCreditBureau(const turbo::RequestContext &ctx,
                                                          std::string creditBureauId,
                                                          Json::Value body);
    drogon::Task<Json::Value> updateOrganisationCreditBureau(const turbo::RequestContext &ctx,
                                                             Json::Value body);
    drogon::Task<Json::Value> getCreditBureauConfiguration(const turbo::RequestContext &ctx,
                                                           std::string organisationCreditBureauId);
    drogon::Task<Json::Value> createCreditBureauConfiguration(const turbo::RequestContext &ctx,
                                                              std::string creditBureauId,
                                                              Json::Value body);
    drogon::Task<Json::Value> updateCreditBureauConfiguration(const turbo::RequestContext &ctx,
                                                              std::string configurationId,
                                                              Json::Value body);
    drogon::Task<Json::Value> listCreditBureauLoanProducts(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getCreditBureauMappingByLoanProduct(const turbo::RequestContext &ctx,
                                                                  std::string loanProductId);
    drogon::Task<Json::Value> listCreditBureauMappings(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createCreditBureauMapping(const turbo::RequestContext &ctx,
                                                        std::string organisationCreditBureauId,
                                                        Json::Value body);
    drogon::Task<Json::Value> updateCreditBureauMapping(const turbo::RequestContext &ctx,
                                                        Json::Value body);

    /// Fetches a report from the pluggable CreditBureauProvider (ships with
    /// one deterministic "sandbox" provider — see .cc header note) without
    /// persisting it.
    drogon::Task<Json::Value> fetchCreditReport(const turbo::RequestContext &ctx, Json::Value body);
    /// Persists a fetched report.
    drogon::Task<Json::Value> saveCreditReport(const turbo::RequestContext &ctx, Json::Value body);
    /// Fetches-and-persists in one call (Fineract's addCreditReport).
    drogon::Task<Json::Value> addCreditReport(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> getSavedCreditReport(const turbo::RequestContext &ctx,
                                                   std::string creditBureauId,
                                                   const Json::Value &query);
    drogon::Task<void> deleteCreditReport(const turbo::RequestContext &ctx, std::string creditBureauId,
                                         const Json::Value &query);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);

    // ---- id resolution ------------------------------------------------------
    drogon::Task<std::string> resolveLoanId(Txn txn, const std::string &idOrExternalId,
                                            bool byExternalId);
    drogon::Task<std::string> resolveLoanChargeId(Txn txn, const std::string &loanId,
                                                  const std::string &idOrExternalId, bool byExternalId);
    drogon::Task<std::string> resolveLoanTransactionId(Txn txn, const std::string &loanId,
                                                       const std::string &idOrExternalId,
                                                       bool byExternalId);

    // ---- JSON projections -----------------------------------------------------
    drogon::Task<Json::Value> loanProductToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> loanToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> loanChargeToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> loanTransactionToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> rescheduleRequestToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> shareProductToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> shareAccountToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> assetOwnerTransferToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> creditBureauReportToJson(Txn txn, const std::string &id);

    // ---- amortization engine --------------------------------------------------
    struct ScheduleInstallment {
        int number;
        std::string fromDate;
        std::string dueDate;
        std::string principal;   // Money string
        std::string interest;    // Money string
    };
    /// Builds the full repayment schedule for a loan's terms. Pure function
    /// (no DB access) so it is directly unit-exercisable from hand-worked
    /// reference cases. `graceOnPrincipal`/`graceOnInterest` are counts of
    /// leading installments where that component is deferred to later
    /// installments (Fineract "grace on principal/interest payment").
    static std::vector<ScheduleInstallment> buildAmortizationSchedule(
        const std::string &disbursementDate, double principal, double annualRatePercent,
        int numberOfRepayments, int repaymentEveryNDays, int repaymentFrequencyType,
        int interestMethod, int daysInYearType, int daysInMonthType, int graceOnPrincipal,
        int graceOnInterest);

    /// Persists a built schedule as loan_repayment_schedule_installment rows,
    /// replacing any existing rows for the loan.
    drogon::Task<void> persistSchedule(Txn txn, const std::string &loanId,
                                       const std::vector<ScheduleInstallment> &schedule);

    /// Applies a repayment-shaped transaction amount across outstanding
    /// schedule installments in installment-number order, paying each
    /// installment's interest-then-principal before moving to the next
    /// ("mifos-standard-strategy" minus its fee/penalty legs — charges are
    /// settled separately via the loan-charge "pay" command, not by this
    /// allocator), updating installment *_completed_derived columns and
    /// the loan's aggregate paid/outstanding columns. The returned `fees`
    /// and `penalties` legs are always "0.000000" today (reserved for a
    /// future unified allocator); only `principal`/`interest` are
    /// populated. Flips the loan to kLClosed/kLOverpaid once every
    /// installment's principal+interest obligation is met.
    struct Allocation {
        std::string principal, interest, fees, penalties;
    };
    drogon::Task<Allocation> allocateRepayment(Txn txn, const std::string &loanId,
                                               const std::string &amount);

    /// Recomputes is_npa / delinquency_range_id for one loan as of asOfDate
    /// from its oldest unpaid installment's overdue days against the
    /// product's delinquency bucket ranges (or the hardcoded NPA
    /// overdue_days_for_npa threshold if the product has no bucket).
    /// Writes a loan_delinquency_tag_history row on change. Returns the new
    /// delinquency_range_id (empty if current).
    drogon::Task<std::string> classifyLoanDelinquency(Txn txn, const std::string &loanId,
                                                      const std::string &asOfDate);

    drogon::Task<std::string> generateLoanAccountNumber(Txn txn);
    drogon::Task<std::string> generateShareAccountNumber(Txn txn);

    /// Resets every installment's *_completed_derived fields to zero and
    /// the loan's paid/overpaid aggregates, then re-applies every
    /// non-reversed repayment-shaped transaction (in transaction_date
    /// order) via allocateRepayment(). Used by adjustLoanTransaction so
    /// reversing/adjusting a mid-history transaction leaves a consistent
    /// derived state rather than patching individual fields by hand.
    drogon::Task<void> replayLoanTransactions(Txn txn, const std::string &loanId);
};

}  // namespace turbo_ledger_portfolio
