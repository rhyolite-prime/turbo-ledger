//
// Phase 7 — Teller cash management: `tellers`, `cashiers`, `cashiersjournal`
// (21 endpoints), completing Phase 7 alongside the Group retrofit
// (groups/centers/grouplevels/collectionsheet) implemented earlier.
//
// Mirrors Fineract's own Teller Cash Management module shape: a `teller`
// belongs to an office; one or more `cashiers` are staff rostered to work
// that teller for a date range (full day, or an explicit time window); cash
// movements between the teller's vault and a cashier are logged as
// `cashier_transactions` (txn_type 101 = Allocate Cash, 102 = Settle Cash —
// Fineract's own fixed codes, see V002__phase7_teller.sql). Settling is
// balance-checked against that cashier's net allocated cash in the same
// currency so a cashier can never be settled for more than was allocated.
//
// Every operation runs inside the caller's tenant schema
// (turbo::db::beginTenantTxn). RBAC is enforced entirely from the
// gateway-signed TL-Context, matching every other service in this codebase
// — no callback to Identity on the request hot path.
//
// Cross-service ids intentionally trusted as caller-supplied, not
// validated (same precedent as every prior phase): office_id, staff_id
// (Organization's own database). No inter-service RPC client exists in
// this codebase, so officeName/staffName are omitted from responses rather
// than faked — same precedent as Group's groupTemplate/centerTemplate
// stubs and Customer's omitted cross-service dropdown catalogs.
//
// CSV bulk-import/download-template endpoints don't exist for this
// resource in Fineract either, so there is nothing to skip here (unlike
// every prior phase).
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_teller {

/// Error carrying an HTTP status + envelope globalisation code.
class ApiError : public std::runtime_error {
  public:
    ApiError(drogon::HttpStatusCode status, std::string message, std::string globalisationCode = "")
        : std::runtime_error(std::move(message)), status_(status), code_(std::move(globalisationCode)) {}
    drogon::HttpStatusCode status() const { return status_; }
    const std::string &globalisationCode() const { return code_; }

  private:
    drogon::HttpStatusCode status_;
    std::string code_;
};

class TellerService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- tellers: core CRUD --------------------------------------------------
    drogon::Task<Json::Value> listTellers(const turbo::RequestContext &ctx, const std::string &officeId,
                                          const std::string &status, const std::string &nameLike,
                                          int offset, int limit);
    drogon::Task<Json::Value> getTeller(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createTeller(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateTeller(const turbo::RequestContext &ctx, const std::string &id,
                                           const Json::Value &body);
    drogon::Task<void> deleteTeller(const turbo::RequestContext &ctx, const std::string &id);

    // ---- teller-level views (aggregated across its cashiers) -----------------
    drogon::Task<Json::Value> tellerTransactions(const turbo::RequestContext &ctx, const std::string &tellerId,
                                                 int offset, int limit);
    drogon::Task<Json::Value> tellerTransactionDetail(const turbo::RequestContext &ctx,
                                                      const std::string &tellerId,
                                                      const std::string &transactionId);
    /// "journal" is the same underlying data as tellerTransactions — Fineract
    /// itself documents no distinct semantics for the two reads at this
    /// resource; kept as a separate method so the controller mapping stays
    /// 1:1 with the endpoint inventory.
    drogon::Task<Json::Value> tellerJournal(const turbo::RequestContext &ctx, const std::string &tellerId,
                                            int offset, int limit);

    // ---- cashiers (nested under a teller) -------------------------------------
    drogon::Task<Json::Value> listCashiers(const turbo::RequestContext &ctx, const std::string &tellerId);
    drogon::Task<Json::Value> createCashier(const turbo::RequestContext &ctx, const std::string &tellerId,
                                            const Json::Value &body);
    drogon::Task<Json::Value> getCashier(const turbo::RequestContext &ctx, const std::string &tellerId,
                                         const std::string &cashierId);
    drogon::Task<Json::Value> updateCashier(const turbo::RequestContext &ctx, const std::string &tellerId,
                                            const std::string &cashierId, const Json::Value &body);
    drogon::Task<void> deleteCashier(const turbo::RequestContext &ctx, const std::string &tellerId,
                                     const std::string &cashierId);
    /// Synchronous (no DB access needed) — staffOptions is an empty-array
    /// stub, same precedent as Group's template endpoints (no inter-service
    /// Staff lookup client exists).
    Json::Value cashierTemplate(const turbo::RequestContext &ctx, const std::string &tellerId);

    // ---- cashier transactions --------------------------------------------------
    drogon::Task<Json::Value> cashierTransactions(const turbo::RequestContext &ctx, const std::string &tellerId,
                                                  const std::string &cashierId, const std::string &currencyCode,
                                                  int offset, int limit);
    drogon::Task<Json::Value> cashierTransactionTemplate(const turbo::RequestContext &ctx,
                                                         const std::string &tellerId,
                                                         const std::string &cashierId);
    drogon::Task<Json::Value> cashierSummaryAndTransactions(const turbo::RequestContext &ctx,
                                                            const std::string &tellerId,
                                                            const std::string &cashierId,
                                                            const std::string &currencyCode, int offset,
                                                            int limit);
    /// command=allocate: txn_type=101 (Allocate Cash).
    drogon::Task<Json::Value> allocateCash(const turbo::RequestContext &ctx, const std::string &tellerId,
                                           const std::string &cashierId, const Json::Value &body);
    /// command=settle: txn_type=102 (Settle Cash). Rejected (400) if the
    /// settlement amount would exceed the cashier's net allocated balance
    /// in that currency.
    drogon::Task<Json::Value> settleCash(const turbo::RequestContext &ctx, const std::string &tellerId,
                                         const std::string &cashierId, const Json::Value &body);

    // ---- top-level global queries (span every teller/cashier) -----------------
    drogon::Task<Json::Value> listCashiersGlobal(const turbo::RequestContext &ctx, const std::string &officeId,
                                                 const std::string &staffId, const std::string &tellerId,
                                                 const std::string &date, int offset, int limit);
    drogon::Task<Json::Value> cashiersJournal(const turbo::RequestContext &ctx, const std::string &cashierId,
                                              const std::string &tellerId, const std::string &currencyCode,
                                              const std::string &fromDate, const std::string &toDate,
                                              int offset, int limit);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);
};

}  // namespace turbo_ledger_teller
