//
// Phase 9 — SelfService (BFF): the "self/*" Fineract module (60 endpoints).
//
// This service owns no ledger data of its own. It composes Customer,
// Portfolio and DepositAccountManagement over signed internal HTTP calls
// (turbo::InternalClient) on behalf of a single self-service user who is
// linked 1:1 to exactly one Customer client id (see V001__baseline.sql for
// the scope rationale). Every method that addresses a client/account by id
// re-verifies ownership — that the resource's clientId equals the caller's
// linked client id — before returning composed data; this is the only
// authorization check these endpoints perform (self-service users carry no
// Fineract RBAC permission codes, matching real Fineract's separate
// "mobile"/self-service role model).
//
// Local-only concerns (no composition target exists): self-service identity
// (self_service_users/self_service_registrations), device push-notification
// registration, TPT beneficiaries, pockets (dashboard account ordering) and
// client profile images (Customer has no image support).
//
// Disclosed stubs (no Reporting/PPI subsystem exists in this codebase):
// runreports and the surveys/scorecards family return a clear 501, not fake
// data — consistent with every other phase's disclosed-limitation pattern.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/InternalClient.h"
#include "turbo/RequestContext.h"

namespace turbo_ledger_selfservice {

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

class SelfServiceService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- registration / authentication / profile ---------------------------
    drogon::Task<Json::Value> submitRegistration(const turbo::RequestContext &ctx,
                                                 const Json::Value &body);
    drogon::Task<Json::Value> createRegistrationUser(const turbo::RequestContext &ctx,
                                                     const Json::Value &body);
    drogon::Task<Json::Value> authenticate(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> getUserDetails(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> updateUser(const turbo::RequestContext &ctx, const Json::Value &body);

    // ---- clients -------------------------------------------------------------
    drogon::Task<Json::Value> listClients(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getClient(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> accountsOverview(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> obligeeDetails(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> clientCharges(const turbo::RequestContext &ctx, const std::string &id,
                                            const std::string &chargeId);
    drogon::Task<Json::Value> clientTransactions(const turbo::RequestContext &ctx, const std::string &id,
                                                 const std::string &transactionId);
    drogon::Task<Json::Value> getClientImage(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> putClientImage(const turbo::RequestContext &ctx, const std::string &id,
                                             const Json::Value &body);
    drogon::Task<void> deleteClientImage(const turbo::RequestContext &ctx, const std::string &id);

    // ---- loans -----------------------------------------------------------------
    drogon::Task<Json::Value> loanProducts(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> loansTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getLoan(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createLoan(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> loanCommand(const turbo::RequestContext &ctx, const std::string &id,
                                          const Json::Value &body);
    drogon::Task<Json::Value> loanCharges(const turbo::RequestContext &ctx, const std::string &id,
                                          const std::string &chargeId);
    drogon::Task<Json::Value> loanGuarantors(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> loanTransaction(const turbo::RequestContext &ctx, const std::string &id,
                                              const std::string &transactionId);

    // ---- savings accounts ------------------------------------------------------
    drogon::Task<Json::Value> savingsProducts(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> savingsTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getSavingsAccount(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> updateSavingsAccount(const turbo::RequestContext &ctx, const std::string &id,
                                                   const Json::Value &body);
    drogon::Task<Json::Value> createSavingsAccount(const turbo::RequestContext &ctx,
                                                   const Json::Value &body);
    drogon::Task<Json::Value> savingsCharges(const turbo::RequestContext &ctx, const std::string &id,
                                             const std::string &chargeId);
    drogon::Task<Json::Value> savingsTransaction(const turbo::RequestContext &ctx, const std::string &id,
                                                 const std::string &transactionId);

    // ---- share accounts --------------------------------------------------------
    drogon::Task<Json::Value> shareProducts(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> shareAccountsTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getShareAccount(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createShareAccount(const turbo::RequestContext &ctx,
                                                 const Json::Value &body);

    // ---- account transfers ------------------------------------------------------
    drogon::Task<Json::Value> accountTransfersTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createAccountTransfer(const turbo::RequestContext &ctx,
                                                    const Json::Value &body);

    // ---- TPT beneficiaries -------------------------------------------------------
    drogon::Task<Json::Value> tptTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> listTptBeneficiaries(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createTptBeneficiary(const turbo::RequestContext &ctx,
                                                   const Json::Value &body);
    drogon::Task<Json::Value> updateTptBeneficiary(const turbo::RequestContext &ctx,
                                                   const std::string &id, const Json::Value &body);
    drogon::Task<void> deleteTptBeneficiary(const turbo::RequestContext &ctx, const std::string &id);

    // ---- device registration (push) ----------------------------------------------
    drogon::Task<Json::Value> listDeviceRegistrations(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createDeviceRegistration(const turbo::RequestContext &ctx,
                                                       const Json::Value &body);
    drogon::Task<Json::Value> getDeviceRegistration(const turbo::RequestContext &ctx,
                                                    const std::string &id);
    drogon::Task<Json::Value> updateDeviceRegistration(const turbo::RequestContext &ctx,
                                                       const std::string &id, const Json::Value &body);
    drogon::Task<void> deleteDeviceRegistration(const turbo::RequestContext &ctx, const std::string &id);

    // ---- pockets ------------------------------------------------------------------
    drogon::Task<Json::Value> listPockets(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createPocket(const turbo::RequestContext &ctx, const Json::Value &body);

    // ---- disclosed stubs: runreports / surveys (no Reporting/PPI subsystem) ------
    drogon::Task<Json::Value> runReport(const turbo::RequestContext &ctx, const std::string &reportName);
    drogon::Task<Json::Value> surveys(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> surveyScorecards(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> submitSurveyScorecard(const turbo::RequestContext &ctx,
                                                     const std::string &surveyId, const Json::Value &body);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);

    /// Find the self_service_users row linked to ctx.userId, or throw 403.
    drogon::Task<Json::Value> requireLinkedUser(Txn txn, const turbo::RequestContext &ctx);

    /// Build a short-lived, narrowly-scoped outbound context for an internal
    /// composition call (see turbo/InternalClient.h for the security model).
    static turbo::RequestContext systemCtx(const turbo::RequestContext &callerCtx,
                                           std::vector<std::string> perms);

    turbo::InternalClient &customerClient();
    turbo::InternalClient &portfolioClient();
    turbo::InternalClient &damClient();

    /// Throws ApiError(403) unless `body["clientId"] == linkedClientId`.
    static void enforceClientOwnership(const Json::Value &body, const std::string &linkedClientId);
};

}  // namespace turbo_ledger_selfservice
