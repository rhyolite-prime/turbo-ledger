//
// Phase 5 — Deposits (119 endpoints across savingsaccounts, savingsproducts,
// fixeddepositaccounts, fixeddepositproducts, recurringdepositaccounts,
// recurringdepositproducts, interestratecharts, accounttransfers,
// standinginstructions, standinginstructionrunhistory, accountnumberformats,
// charges — see ENDPOINT_INVENTORY.md).
//
// SCHEMA PROVENANCE (read before touching migrations/V001__baseline.sql):
// unlike every other service, there is no usable Fineract pg_dump for this
// service (src/scripts/TlDamDb.sql is a near-empty PGDMP archive with zero
// table entries — confirmed with src/tools/pgdmp_schema.py). The schema was
// hand-designed from Fineract's public domain model instead of transcribed
// from a dump; see the V001 migration header for the full explanation.
//
// TABLE-FAMILY DESIGN: plain savings, fixed-deposit (FD) and recurring-
// deposit (RD) products/accounts share the same `savings_product` /
// `savings_account` tables, discriminated by `deposit_type`
// (100=SAVINGS/200=FIXED_DEPOSIT/300=RECURRING_DEPOSIT) — this mirrors
// Fineract's own design (FD/RD really are savings products with extra term
// configuration). FD/RD-only term & pre-closure fields live in the 1:1
// `deposit_account_term_and_preclosure` table; RD-only scheduled
// installments live in `recurring_deposit_schedule_installment`.
//
// Every operation runs inside the caller's tenant schema (t_<tenantId>) via
// turbo::db::beginTenantTxn. RBAC is enforced entirely from the gateway-
// signed TL-Context (turbo::RequestContext::hasPermission), matching every
// other service — this service never calls back to Identity on the request
// hot path.
//
// Cross-service dependencies this phase deliberately does NOT resolve
// (documented, not silently skipped):
//   - client_id/group_id/field_officer_id/office_id/payment_detail_id and
//     similar foreign ids from Customer/Organization are trusted as given
//     by the caller, exactly like every prior phase's cross-service ids
//     (e.g. Phase 3's trusted office ids for GL closures, Phase 4's trusted
//     office/staff ids on clients). No cross-service HTTP client exists in
//     this codebase.
//   - GL posting ("correct GL postings" exit criterion): implemented via
//     turbo::outbox::writeEvent carrying a full journal-entry-shaped payload
//     (debit/credit account hints by GL usage, amounts, currency, narrative)
//     on every balance-affecting transaction (deposits, withdrawals, interest
//     posting, charges, transfers). No prior phase makes a live synchronous
//     call to Accounting — this keeps Phase 5 consistent with that
//     precedent. A future Accounting consumer can replay these events into
//     real journal entries once that wiring exists.
//   - GSIM (Group Savings Integrated Monitoring — 3 of the 32 savingsaccounts
//     routes: gsim create/update/commands) are thin 501 stubs: a real GSIM
//     implementation requires distributing a pooled deposit across group
//     members, which requires a Group service that does not exist yet in
//     this codebase. Documented scope trim, not a silent omission.
//   - Share-account routes present in the old pre-inventory scaffold
//     (`ProductsController`/`AccountsController`) are dropped entirely —
//     out of scope per ENDPOINT_INVENTORY.md (they belong to
//     Portfolio/Phase 6's share-account family, not DepositAccountManagement).
//   - `accounttransfers/refundByTransfer` (loan refund by transfer) and its
//     template are 501 stubs: loans don't exist yet (Portfolio/Phase 6).
//
// Interest math: daily-balance method using turbo::Money::timesRatio
// (banker's rounding) — accrued = balance * (annualRate/100) * days/daysInYear,
// compounded/posted per the product's configured periods. FD premature-
// closure penalty follows Fineract's real approach: interest is recomputed
// for the time actually held using (nominal rate - penal rate), then
// reconciled against interest already posted (excess is clawed back from
// the payout, shortfall is topped up).
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_dam {

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

/// deposit_type discriminator shared by savings_product / savings_account.
enum DepositType : int {
    kDepositTypeSavings = 100,
    kDepositTypeFixedDeposit = 200,
    kDepositTypeRecurringDeposit = 300,
};

class DepositAccountManagementService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- charges catalog ----------------------------------------------------
    drogon::Task<Json::Value> listCharges(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getCharge(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createCharge(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> updateCharge(const turbo::RequestContext &ctx, std::string id,
                                           Json::Value body);
    drogon::Task<void> deleteCharge(const turbo::RequestContext &ctx, std::string id);
    Json::Value chargeTemplate(const turbo::RequestContext &ctx);

    // ---- account number formats -----------------------------------------------
    drogon::Task<Json::Value> listAccountNumberFormats(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getAccountNumberFormat(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createAccountNumberFormat(const turbo::RequestContext &ctx,
                                                        Json::Value body);
    drogon::Task<Json::Value> updateAccountNumberFormat(const turbo::RequestContext &ctx,
                                                        std::string id, Json::Value body);
    drogon::Task<void> deleteAccountNumberFormat(const turbo::RequestContext &ctx, std::string id);
    Json::Value accountNumberFormatTemplate(const turbo::RequestContext &ctx);

    // ---- interest rate charts + slabs ------------------------------------------
    drogon::Task<Json::Value> listInterestRateCharts(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getInterestRateChart(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createInterestRateChart(const turbo::RequestContext &ctx,
                                                      Json::Value body);
    drogon::Task<Json::Value> updateInterestRateChart(const turbo::RequestContext &ctx,
                                                      std::string id, Json::Value body);
    drogon::Task<void> deleteInterestRateChart(const turbo::RequestContext &ctx, std::string id);
    Json::Value interestRateChartTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> listChartSlabs(const turbo::RequestContext &ctx, std::string chartId);
    drogon::Task<Json::Value> getChartSlab(const turbo::RequestContext &ctx, std::string chartId,
                                           std::string slabId);
    drogon::Task<Json::Value> createChartSlab(const turbo::RequestContext &ctx, std::string chartId,
                                              Json::Value body);
    drogon::Task<Json::Value> updateChartSlab(const turbo::RequestContext &ctx, std::string chartId,
                                              std::string slabId, Json::Value body);
    drogon::Task<void> deleteChartSlab(const turbo::RequestContext &ctx, std::string chartId,
                                       std::string slabId);
    Json::Value chartSlabTemplate(const turbo::RequestContext &ctx, std::string chartId);

    // ---- products (savings/FD/RD share savings_product, by depositType) -------
    drogon::Task<Json::Value> listProducts(const turbo::RequestContext &ctx, int depositType);
    drogon::Task<Json::Value> getProduct(const turbo::RequestContext &ctx, int depositType,
                                         std::string id);
    drogon::Task<Json::Value> createProduct(const turbo::RequestContext &ctx, int depositType,
                                            Json::Value body);
    drogon::Task<Json::Value> updateProduct(const turbo::RequestContext &ctx, int depositType,
                                            std::string id, Json::Value body);
    drogon::Task<void> deleteProduct(const turbo::RequestContext &ctx, int depositType,
                                     std::string id);
    Json::Value productTemplate(const turbo::RequestContext &ctx, int depositType);

    // ---- accounts (savings/FD/RD share savings_account, by depositType) -------
    drogon::Task<Json::Value> listAccounts(const turbo::RequestContext &ctx, int depositType,
                                           const std::string &clientId, const std::string &status,
                                           int offset, int limit);
    drogon::Task<Json::Value> getAccount(const turbo::RequestContext &ctx, int depositType,
                                         std::string id);
    drogon::Task<Json::Value> getAccountByExternalId(const turbo::RequestContext &ctx,
                                                     int depositType, std::string externalId);
    drogon::Task<Json::Value> createAccount(const turbo::RequestContext &ctx, int depositType,
                                            Json::Value body);
    drogon::Task<Json::Value> updateAccount(const turbo::RequestContext &ctx, int depositType,
                                            std::string id, Json::Value body);
    drogon::Task<Json::Value> updateAccountByExternalId(const turbo::RequestContext &ctx,
                                                        int depositType, std::string externalId,
                                                        Json::Value body);
    drogon::Task<void> deleteAccount(const turbo::RequestContext &ctx, int depositType,
                                     std::string id);
    drogon::Task<void> deleteAccountByExternalId(const turbo::RequestContext &ctx, int depositType,
                                                 std::string externalId);
    Json::Value accountTemplate(const turbo::RequestContext &ctx, int depositType);
    drogon::Task<Json::Value> accountClosureTemplate(const turbo::RequestContext &ctx,
                                                     int depositType, std::string id);
    /// POST .../{id}/command/{cmd}: approve|undoApproval|assignSavingsOfficer|
    ///   unassignSavingsOfficer|reject|withdrawnByApplicant|activate|close|
    ///   prematureClose (FD/RD)|calculateInterest|postInterest|
    ///   updateDepositAmount (RD)
    drogon::Task<Json::Value> handleAccountCommand(const turbo::RequestContext &ctx,
                                                   int depositType, std::string id,
                                                   std::string command, Json::Value body);
    drogon::Task<Json::Value> handleAccountCommandByExternalId(const turbo::RequestContext &ctx,
                                                               int depositType,
                                                               std::string externalId,
                                                               std::string command,
                                                               Json::Value body);
    /// GET fixeddepositaccounts/calculate-fd-interest — standalone calculator,
    /// no persisted account required.
    Json::Value calculateFdInterest(const turbo::RequestContext &ctx, const Json::Value &query);

    // ---- account charges --------------------------------------------------------
    drogon::Task<Json::Value> listAccountCharges(const turbo::RequestContext &ctx,
                                                 std::string accountId);
    drogon::Task<Json::Value> getAccountCharge(const turbo::RequestContext &ctx,
                                               std::string accountId, std::string chargeId);
    drogon::Task<Json::Value> addAccountCharge(const turbo::RequestContext &ctx,
                                               std::string accountId, Json::Value body);
    drogon::Task<Json::Value> updateAccountCharge(const turbo::RequestContext &ctx,
                                                  std::string accountId, std::string chargeId,
                                                  Json::Value body);
    drogon::Task<void> deleteAccountCharge(const turbo::RequestContext &ctx, std::string accountId,
                                           std::string chargeId);
    /// POST .../{chargeId}/command/{cmd}: pay|waive|inactivate
    drogon::Task<Json::Value> handleAccountChargeCommand(const turbo::RequestContext &ctx,
                                                         std::string accountId,
                                                         std::string chargeId, std::string command,
                                                         Json::Value body);
    Json::Value accountChargeTemplate(const turbo::RequestContext &ctx);

    // ---- account transactions -----------------------------------------------------
    drogon::Task<Json::Value> listAccountTransactions(const turbo::RequestContext &ctx,
                                                      std::string accountId);
    drogon::Task<Json::Value> getAccountTransaction(const turbo::RequestContext &ctx,
                                                    std::string accountId,
                                                    std::string transactionId);
    /// command: deposit|withdrawal
    drogon::Task<Json::Value> createAccountTransaction(const turbo::RequestContext &ctx,
                                                       std::string accountId, std::string command,
                                                       Json::Value body);
    /// command: undo|reverse|modify|releaseAmount|adjust
    drogon::Task<Json::Value> handleAccountTransactionCommand(const turbo::RequestContext &ctx,
                                                              std::string accountId,
                                                              std::string transactionId,
                                                              std::string command,
                                                              Json::Value body);
    Json::Value accountTransactionTemplate(const turbo::RequestContext &ctx,
                                           const std::string &accountId);
    drogon::Task<Json::Value> listOnHoldTransactions(const turbo::RequestContext &ctx,
                                                     std::string accountId);

    // ---- account transfers --------------------------------------------------------
    drogon::Task<Json::Value> listAccountTransfers(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getAccountTransfer(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> createAccountTransfer(const turbo::RequestContext &ctx,
                                                    Json::Value body);
    Json::Value accountTransferTemplate(const turbo::RequestContext &ctx);

    // ---- standing instructions --------------------------------------------------
    drogon::Task<Json::Value> listStandingInstructions(const turbo::RequestContext &ctx,
                                                       const std::string &clientId);
    drogon::Task<Json::Value> getStandingInstruction(const turbo::RequestContext &ctx,
                                                     std::string id);
    drogon::Task<Json::Value> createStandingInstruction(const turbo::RequestContext &ctx,
                                                        Json::Value body);
    /// Also handles Fineract's "delete via PUT command=delete" convention.
    drogon::Task<Json::Value> updateStandingInstruction(const turbo::RequestContext &ctx,
                                                        std::string id, Json::Value body);
    Json::Value standingInstructionTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> listStandingInstructionHistory(const turbo::RequestContext &ctx,
                                                             const std::string &clientId);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);

    drogon::Task<Json::Value> chargeToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> accountNumberFormatToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> interestRateChartToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> chartSlabToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> productToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> accountToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> accountChargeToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> transactionToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> transferToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> standingInstructionToJson(Txn txn, const std::string &id);

    drogon::Task<std::string> resolveAccountIdByExternalId(Txn txn, int depositType,
                                                           const std::string &externalId);
    drogon::Task<std::string> generateAccountNumber(Txn txn, int depositType,
                                                    const std::string &seedId);

    /// Posts a deposit/withdrawal/fee/interest transaction, updates derived
    /// balances and writes the GL-posting outbox event. Returns the new
    /// transaction id.
    drogon::Task<std::string> postTransaction(Txn txn, const turbo::RequestContext &ctx,
                                              const std::string &accountId, int transactionType,
                                              const std::string &transactionDate,
                                              const std::string &amountMicros,
                                              const std::string &description);

    /// Daily-balance interest accrual from lastInterestCalculationDate (or the
    /// activation date if interest was never posted) through asOfDate, using
    /// the account's own configured rate/days-in-year. Returns accrued amount
    /// in Money-string (numeric text) form; does not persist.
    drogon::Task<std::string> computeAccruedInterest(Txn txn, const std::string &accountId,
                                                     const std::string &asOfDate);

    /// Daily-balance interest for an arbitrary [fromDate, toDate) window at an
    /// arbitrary annual rate (percent, e.g. "5.5") — the general-purpose
    /// primitive computeAccruedInterest() is built on, and also used directly
    /// for FD/RD premature-closure penalty recomputation (nominal rate minus
    /// penalty rate, over the whole holding period).
    drogon::Task<std::string> computeInterestForPeriod(Txn txn, const std::string &accountId,
                                                       const std::string &fromDate,
                                                       const std::string &toDate,
                                                       const std::string &annualRatePercent,
                                                       int daysInYear);

    /// Shared body of every account lifecycle-command transition.
    drogon::Task<Json::Value> applyAccountCommand(Txn txn, const turbo::RequestContext &ctx,
                                                  int depositType, const std::string &id,
                                                  const std::string &command,
                                                  const Json::Value &body);
};

}  // namespace turbo_ledger_dam
