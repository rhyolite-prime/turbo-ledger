//
// Phase 3 — Accounting core: chart of accounts (glaccounts), the general
// ledger (journalentries), accounting closures (glclosures), accounting
// rules (accountingrules), financial-activity-to-account mappings
// (financialactivityaccounts), provisioning entries (provisioningentries)
// and the periodic accrual job (runaccruals).
//
// Every operation runs inside the caller's tenant schema (t_<tenantId>) via
// turbo::db::beginTenantTxn. RBAC is enforced entirely from the gateway-signed
// TL-Context (turbo::RequestContext::hasPermission), matching Organization
// and SystemConfig — this service never calls back to Identity on the
// request hot path.
//
// Ledger correctness rules (see IMPLEMENTATION_PLAN.md §2.5), all enforced
// here:
//   - balanced multi-leg postings: createJournalEntries validates
//     sum(debits) == sum(credits) before touching the database, then posts
//     every leg inside one DB transaction. A deferred constraint trigger in
//     V003__phase3_ledger.sql (trg_journal_entries_balanced) is the backstop
//     that would catch a bug in this check or a direct SQL edit.
//   - immutability / reversal-only corrections: nothing in this service ever
//     UPDATEs or DELETEs a posted journal_entries row's financial fields;
//     reverseJournalEntries posts new, equal-and-opposite legs and marks the
//     originals `reversed = true`, linking via reversal_id.
//   - hash-chained entries: every inserted leg gets entry_hash =
//     sha256(prev_hash || canonical fields), chained from the previous leg
//     in entry_seq order (a per-tenant Postgres advisory lock serializes
//     concurrent postings so the chain never forks — see
//     lockJournalChain()).
//   - running balances are maintained in the same transaction as the
//     posting (office + organization running balance per account), not by a
//     separate batch job; recalculateRunningBalances exists to repair drift
//     (the nightly HeartBeat reconciliation job the plan describes would
//     call the same code path).
//   - GL closures block postings on/before the closure date for the posting
//     office (assertNotClosed). Full hierarchy-aware inheritance from parent
//     offices is deferred — see the note on assertNotClosed — since office
//     hierarchy lives in the Organization service's database, not this
//     one, and there is no cross-service lookup client in this codebase yet.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_accounting {

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

class AccountingService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- glaccounts (8) -----------------------------------------------------
    drogon::Task<Json::Value> listGlAccounts(const turbo::RequestContext &ctx,
                                             const std::string &manualEntriesAllowed,
                                             const std::string &disabled,
                                             const std::string &usage,
                                             const std::string &classification);
    drogon::Task<Json::Value> getGlAccount(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createGlAccount(const turbo::RequestContext &ctx,
                                              const Json::Value &body);
    drogon::Task<Json::Value> updateGlAccount(const turbo::RequestContext &ctx,
                                              const std::string &id, const Json::Value &body);
    drogon::Task<void> deleteGlAccount(const turbo::RequestContext &ctx, const std::string &id);
    Json::Value glAccountTemplate(const turbo::RequestContext &ctx);

    // ---- glclosures (5) -------------------------------------------------------
    drogon::Task<Json::Value> listGlClosures(const turbo::RequestContext &ctx,
                                             const std::string &officeId);
    drogon::Task<Json::Value> getGlClosure(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createGlClosure(const turbo::RequestContext &ctx,
                                              const Json::Value &body);
    drogon::Task<Json::Value> updateGlClosure(const turbo::RequestContext &ctx,
                                              const std::string &id, const Json::Value &body);
    drogon::Task<void> deleteGlClosure(const turbo::RequestContext &ctx, const std::string &id);

    // ---- accountingrules (6) ---------------------------------------------------
    drogon::Task<Json::Value> listAccountingRules(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getAccountingRule(const turbo::RequestContext &ctx,
                                                const std::string &id);
    drogon::Task<Json::Value> createAccountingRule(const turbo::RequestContext &ctx,
                                                   const Json::Value &body);
    drogon::Task<Json::Value> updateAccountingRule(const turbo::RequestContext &ctx,
                                                   const std::string &id, const Json::Value &body);
    drogon::Task<void> deleteAccountingRule(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> accountingRuleTemplate(const turbo::RequestContext &ctx);

    // ---- financialactivityaccounts (6) -----------------------------------------
    drogon::Task<Json::Value> listFinancialActivityAccounts(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getFinancialActivityAccount(const turbo::RequestContext &ctx,
                                                          const std::string &id);
    drogon::Task<Json::Value> createFinancialActivityAccount(const turbo::RequestContext &ctx,
                                                             const Json::Value &body);
    drogon::Task<Json::Value> updateFinancialActivityAccount(const turbo::RequestContext &ctx,
                                                             const std::string &id,
                                                             const Json::Value &body);
    drogon::Task<void> deleteFinancialActivityAccount(const turbo::RequestContext &ctx,
                                                      const std::string &id);
    drogon::Task<Json::Value> financialActivityAccountTemplate(const turbo::RequestContext &ctx);

    // ---- journalentries (8) -----------------------------------------------------
    drogon::Task<Json::Value> createJournalEntries(const turbo::RequestContext &ctx,
                                                   const Json::Value &body);
    drogon::Task<Json::Value> searchJournalEntries(const turbo::RequestContext &ctx,
                                                   const std::string &officeId,
                                                   const std::string &glAccountId,
                                                   const std::string &manualEntriesOnly,
                                                   const std::string &fromDate,
                                                   const std::string &toDate,
                                                   const std::string &transactionId, int offset,
                                                   int limit);
    drogon::Task<Json::Value> getJournalEntry(const turbo::RequestContext &ctx,
                                              const std::string &id);
    drogon::Task<Json::Value> getOpeningBalance(const turbo::RequestContext &ctx,
                                                const std::string &officeId,
                                                const std::string &currencyCode);
    drogon::Task<Json::Value> getProvisioningJournalEntries(const turbo::RequestContext &ctx,
                                                            int offset, int limit);
    drogon::Task<Json::Value> journalEntryTemplate(const turbo::RequestContext &ctx);
    /// POST /journalentries/{transactionId}?command=reverse — reverses every
    /// leg of a posted transaction with equal-and-opposite entries.
    drogon::Task<Json::Value> reverseJournalTransaction(const turbo::RequestContext &ctx,
                                                        const std::string &transactionId,
                                                        const Json::Value &body);
    /// POST /journalentries/{transactionId} (no command) — recomputes
    /// office/organization running balances from this transaction forward;
    /// this is the manually-triggerable form of the nightly reconciliation
    /// the plan describes as a HeartBeat job.
    drogon::Task<Json::Value> recalculateRunningBalances(const turbo::RequestContext &ctx,
                                                         const std::string &transactionId);

    // ---- provisioningentries (5) -------------------------------------------------
    drogon::Task<Json::Value> listProvisioningEntries(const turbo::RequestContext &ctx, int offset,
                                                      int limit);
    drogon::Task<Json::Value> getProvisioningEntry(const turbo::RequestContext &ctx,
                                                   const std::string &id);
    drogon::Task<Json::Value> createProvisioningEntry(const turbo::RequestContext &ctx,
                                                      const Json::Value &body);
    drogon::Task<Json::Value> recreateProvisioningEntry(const turbo::RequestContext &ctx,
                                                        const std::string &id);
    drogon::Task<Json::Value> listProvisioningEntryDetails(const turbo::RequestContext &ctx,
                                                           const std::string &provisioningEntryId,
                                                           int offset, int limit);
    /// Posts the balanced journal entries for a provisioning entry's detail
    /// lines (one transaction per office+currency), rolling back on any
    /// failure. Shared by createProvisioningEntry (createjournalentries=true)
    /// and recreateProvisioningEntry.
    drogon::Task<void> createProvisioningJournalEntries(const std::string &provisioningEntryId,
                                                        const turbo::RequestContext &ctx, Txn txn);
    /// Body of createProvisioningJournalEntries, without the rollback
    /// wrapper (so the wrapper can catch every exception uniformly).
    drogon::Task<void> createProvisioningJournalEntriesImpl(const std::string &provisioningEntryId,
                                                            const turbo::RequestContext &ctx, Txn txn);

    // ---- runaccruals (1) ------------------------------------------------------------
    drogon::Task<Json::Value> runPeriodicAccrualAccounting(const turbo::RequestContext &ctx,
                                                           const Json::Value &body);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);

    drogon::Task<Json::Value> glAccountToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> glClosureToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> accountingRuleToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> financialActivityAccountToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> journalEntryToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> provisioningEntryToJson(Txn txn, const std::string &id);

    /// Serializes concurrent postings for this tenant's hash chain via a
    /// Postgres advisory lock scoped to (fixed namespace, current_schema()).
    /// Must be called once, near the top of the same transaction that will
    /// insert journal_entries rows.
    drogon::Task<void> lockJournalChain(Txn txn);
    /// Returns the entry_hash of the most-recently-inserted leg in this
    /// tenant's chain, or "" if the ledger is empty. Call after
    /// lockJournalChain() so the read is race-free.
    drogon::Task<std::string> currentChainHead(Txn txn);
    /// sha256(prevHash || canonical fields), hex-encoded (64 chars).
    static std::string computeEntryHash(const std::string &prevHash, const std::string &transactionId,
                                        const std::string &accountId, const std::string &officeId,
                                        const std::string &currencyCode, int typeEnum,
                                        const std::string &amount, const std::string &entryDate,
                                        const std::string &description);

    /// Throws ApiError(409) if `officeId` has a gl_closure on/after `entryDate`.
    drogon::Task<void> assertNotClosed(Txn txn, const std::string &officeId,
                                       const std::string &entryDate);

    /// Inserts one journal_entries leg (advancing the hash chain and the
    /// office/organization running balance for accountId+officeId), inside
    /// the caller's transaction. Returns the inserted row's id.
    drogon::Task<std::string> postLeg(Txn txn, const turbo::RequestContext &ctx,
                                      const std::string &transactionId, const std::string &officeId,
                                      const std::string &accountId, const std::string &currencyCode,
                                      int typeEnum, const std::string &amount,
                                      const std::string &entryDate, const std::string &transactionDate,
                                      const std::string &description, const std::string &refNum,
                                      bool manualEntry, const std::string &reversalId,
                                      std::string &prevHash);
};

}  // namespace turbo_ledger_accounting
