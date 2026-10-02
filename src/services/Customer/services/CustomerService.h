//
// Phase 4 — Customer domain: client lifecycle (clients), client addresses
// (client), the product-level collateral registry (collateral-management)
// and client-level collateral pledges, family members, identifiers,
// charges and charge-payment transactions, plus a v2 text search.
//
// Every operation runs inside the caller's tenant schema (t_<tenantId>) via
// turbo::db::beginTenantTxn. RBAC is enforced entirely from the gateway-signed
// TL-Context (turbo::RequestContext::hasPermission), matching Organization
// and Accounting — this service never calls back to Identity on the request
// hot path.
//
// Cross-service dependencies this phase deliberately does NOT resolve
// (documented, not silently skipped — see IMPLEMENTATION_PLAN.md):
//   - office_id/staff_id/charge_id/document_type_id/*_cv_id and similar
//     foreign ids from Organization/SystemConfig/DAM are trusted as given by
//     the caller, exactly like Phase 3 trusted caller-supplied office ids
//     for GL closures. No cross-service HTTP client exists in this codebase
//     yet, and the platform's own direction (see RequestContext) is to keep
//     services decoupled behind the gateway rather than chatty inter-service
//     calls.
//   - `clients/{id}/accounts` (accounts overview) and
//     `clients/{id}/obligeedetails` compose DepositAccountManagement and
//     Portfolio data that doesn't exist yet (Phases 5/6); the controller
//     returns 501 for these, matching the downloadtemplate/uploadtemplate
//     precedent from glaccounts in Phase 3.
//   - Charge amounts are caller-supplied (no `charges` catalog exists yet —
//     it lands in DepositAccountManagement per IMPLEMENTATION_PLAN.md); GL
//     posting of charge payments to Accounting is likewise deferred (no
//     inter-service posting client exists yet).
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_customer {

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

class CustomerService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- clients: core CRUD + lifecycle ------------------------------------
    drogon::Task<Json::Value> listClients(const turbo::RequestContext &ctx,
                                          const std::string &officeId,
                                          const std::string &staffId,
                                          const std::string &status,
                                          const std::string &displayNameLike, int offset,
                                          int limit);
    drogon::Task<Json::Value> getClient(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> getClientByExternalId(const turbo::RequestContext &ctx,
                                                    const std::string &externalId);
    drogon::Task<Json::Value> createClient(const turbo::RequestContext &ctx,
                                           const Json::Value &body);
    drogon::Task<Json::Value> updateClient(const turbo::RequestContext &ctx, const std::string &id,
                                           const Json::Value &body);
    drogon::Task<void> deleteClient(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<void> deleteClientByExternalId(const turbo::RequestContext &ctx,
                                                const std::string &externalId);
    Json::Value clientTemplate(const turbo::RequestContext &ctx);
    /// POST /clients/{id}?command=activate|close|reject|withdraw|reactivate|
    ///   undoRejection|undoWithdrawal|assignStaff|unassignStaff|
    ///   updateSavingsAccount|proposeTransfer|withdrawTransfer|acceptTransfer|
    ///   rejectTransfer
    drogon::Task<Json::Value> handleClientCommand(const turbo::RequestContext &ctx,
                                                  const std::string &id,
                                                  const std::string &command,
                                                  const Json::Value &body);
    drogon::Task<Json::Value> handleClientCommandByExternalId(const turbo::RequestContext &ctx,
                                                              const std::string &externalId,
                                                              const std::string &command,
                                                              const Json::Value &body);
    drogon::Task<Json::Value> clientTransferTemplate(const turbo::RequestContext &ctx,
                                                     const std::string &id);

    // ---- client (addresses) ------------------------------------------------
    drogon::Task<Json::Value> listClientAddresses(const turbo::RequestContext &ctx,
                                                  const std::string &clientId);
    drogon::Task<Json::Value> createClientAddress(const turbo::RequestContext &ctx,
                                                  const std::string &clientId,
                                                  const Json::Value &body);
    drogon::Task<Json::Value> updateClientAddress(const turbo::RequestContext &ctx,
                                                  const std::string &clientId,
                                                  const Json::Value &body);
    Json::Value clientAddressTemplate(const turbo::RequestContext &ctx);

    // ---- client identifiers -------------------------------------------------
    drogon::Task<Json::Value> listClientIdentifiers(const turbo::RequestContext &ctx,
                                                    const std::string &clientId);
    drogon::Task<Json::Value> getClientIdentifier(const turbo::RequestContext &ctx,
                                                  const std::string &clientId,
                                                  const std::string &identifierId);
    drogon::Task<Json::Value> createClientIdentifier(const turbo::RequestContext &ctx,
                                                     const std::string &clientId,
                                                     const Json::Value &body);
    drogon::Task<Json::Value> updateClientIdentifier(const turbo::RequestContext &ctx,
                                                     const std::string &clientId,
                                                     const std::string &identifierId,
                                                     const Json::Value &body);
    drogon::Task<void> deleteClientIdentifier(const turbo::RequestContext &ctx,
                                              const std::string &clientId,
                                              const std::string &identifierId);
    Json::Value clientIdentifierTemplate(const turbo::RequestContext &ctx);

    // ---- client family members -----------------------------------------------
    drogon::Task<Json::Value> listFamilyMembers(const turbo::RequestContext &ctx,
                                                const std::string &clientId);
    drogon::Task<Json::Value> getFamilyMember(const turbo::RequestContext &ctx,
                                              const std::string &clientId,
                                              const std::string &familyMemberId);
    drogon::Task<Json::Value> createFamilyMember(const turbo::RequestContext &ctx,
                                                 const std::string &clientId,
                                                 const Json::Value &body);
    drogon::Task<Json::Value> updateFamilyMember(const turbo::RequestContext &ctx,
                                                 const std::string &clientId,
                                                 const std::string &familyMemberId,
                                                 const Json::Value &body);
    drogon::Task<void> deleteFamilyMember(const turbo::RequestContext &ctx,
                                          const std::string &clientId,
                                          const std::string &familyMemberId);
    Json::Value familyMemberTemplate(const turbo::RequestContext &ctx);

    // ---- client collaterals (client-level pledge against a product) -----------
    drogon::Task<Json::Value> listClientCollaterals(const turbo::RequestContext &ctx,
                                                    const std::string &clientId);
    drogon::Task<Json::Value> getClientCollateral(const turbo::RequestContext &ctx,
                                                  const std::string &clientId,
                                                  const std::string &collateralId);
    drogon::Task<Json::Value> createClientCollateral(const turbo::RequestContext &ctx,
                                                     const std::string &clientId,
                                                     const Json::Value &body);
    drogon::Task<Json::Value> updateClientCollateral(const turbo::RequestContext &ctx,
                                                     const std::string &clientId,
                                                     const std::string &collateralId,
                                                     const Json::Value &body);
    drogon::Task<void> deleteClientCollateral(const turbo::RequestContext &ctx,
                                              const std::string &clientId,
                                              const std::string &collateralId);
    drogon::Task<Json::Value> clientCollateralTemplate(const turbo::RequestContext &ctx);

    // ---- client charges -------------------------------------------------------
    drogon::Task<Json::Value> listClientCharges(const turbo::RequestContext &ctx,
                                                const std::string &clientId);
    drogon::Task<Json::Value> getClientCharge(const turbo::RequestContext &ctx,
                                              const std::string &clientId,
                                              const std::string &chargeId);
    drogon::Task<Json::Value> addClientCharge(const turbo::RequestContext &ctx,
                                              const std::string &clientId,
                                              const Json::Value &body);
    drogon::Task<void> deleteClientCharge(const turbo::RequestContext &ctx,
                                          const std::string &clientId,
                                          const std::string &chargeId);
    /// POST .../charges/{chargeId}?command=pay|waive
    drogon::Task<Json::Value> handleClientChargeCommand(const turbo::RequestContext &ctx,
                                                        const std::string &clientId,
                                                        const std::string &chargeId,
                                                        const std::string &command,
                                                        const Json::Value &body);
    Json::Value clientChargeTemplate(const turbo::RequestContext &ctx);

    // ---- client transactions ---------------------------------------------------
    drogon::Task<Json::Value> listClientTransactions(const turbo::RequestContext &ctx,
                                                     const std::string &clientId);
    drogon::Task<Json::Value> getClientTransaction(const turbo::RequestContext &ctx,
                                                   const std::string &clientId,
                                                   const std::string &transactionId);
    drogon::Task<Json::Value> undoClientTransaction(const turbo::RequestContext &ctx,
                                                    const std::string &clientId,
                                                    const std::string &transactionId);

    // ---- collateral-management (product-level registry) -----------------------
    drogon::Task<Json::Value> listCollateralProducts(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getCollateralProduct(const turbo::RequestContext &ctx,
                                                   const std::string &id);
    drogon::Task<Json::Value> createCollateralProduct(const turbo::RequestContext &ctx,
                                                      const Json::Value &body);
    drogon::Task<Json::Value> updateCollateralProduct(const turbo::RequestContext &ctx,
                                                      const std::string &id,
                                                      const Json::Value &body);
    drogon::Task<void> deleteCollateralProduct(const turbo::RequestContext &ctx,
                                               const std::string &id);
    Json::Value collateralProductTemplate(const turbo::RequestContext &ctx);

    // ---- v2 search --------------------------------------------------------------
    drogon::Task<Json::Value> searchClientsV2(const turbo::RequestContext &ctx,
                                              const Json::Value &body);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);

    drogon::Task<Json::Value> clientToJson(Txn txn, const std::string &id);
    drogon::Task<std::string> resolveClientIdByExternalId(Txn txn, const std::string &externalId);
    drogon::Task<Json::Value> clientAddressToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> clientIdentifierToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> familyMemberToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> clientCollateralToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> clientChargeToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> clientTransactionToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> collateralProductToJson(Txn txn, const std::string &id);

    /// Shared body of every lifecycle-command transition; throws ApiError on
    /// an invalid state transition.
    drogon::Task<Json::Value> applyClientCommand(Txn txn, const turbo::RequestContext &ctx,
                                                 const std::string &id, const std::string &command,
                                                 const Json::Value &body);
};

}  // namespace turbo_ledger_customer
