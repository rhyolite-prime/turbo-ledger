//
// Phase 2 — Organization: offices, staff, holidays, working days, currencies,
// funds, payment types, taxes and entity-to-entity mapping.
//
// Every operation runs inside the caller's tenant schema (t_<tenantId>) via
// turbo::db::beginTenantTxn. RBAC is enforced entirely from the gateway-signed
// TL-Context (turbo::RequestContext::hasPermission) — the caller's permission
// set is resolved once at signin by Identity and embedded in the JWT, so this
// service never has to call back to Identity on the request hot path.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>

#include "turbo/RequestContext.h"

namespace turbo_ledger_organization {

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

class OrganizationService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- offices (9) --------------------------------------------------------
    drogon::Task<Json::Value> listOffices(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getOffice(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> getOfficeByExternalId(const turbo::RequestContext &ctx,
                                                    const std::string &externalId);
    drogon::Task<Json::Value> createOffice(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateOffice(const turbo::RequestContext &ctx, const std::string &id,
                                           const Json::Value &body);
    drogon::Task<Json::Value> updateOfficeByExternalId(const turbo::RequestContext &ctx,
                                                       const std::string &externalId,
                                                       const Json::Value &body);
    drogon::Task<Json::Value> officeTemplate(const turbo::RequestContext &ctx);

    // ---- office transactions (4) ---------------------------------------------
    drogon::Task<Json::Value> listOfficeTransactions(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createOfficeTransaction(const turbo::RequestContext &ctx,
                                                      const Json::Value &body);
    drogon::Task<void> deleteOfficeTransaction(const turbo::RequestContext &ctx,
                                               const std::string &id);
    drogon::Task<Json::Value> officeTransactionTemplate(const turbo::RequestContext &ctx);

    // ---- staff (6) -------------------------------------------------------------
    drogon::Task<Json::Value> listStaff(const turbo::RequestContext &ctx, const std::string &officeId,
                                        bool loanOfficersOnly);
    drogon::Task<Json::Value> getStaff(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createStaff(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateStaff(const turbo::RequestContext &ctx, const std::string &id,
                                          const Json::Value &body);

    // ---- holidays (7) ------------------------------------------------------------
    drogon::Task<Json::Value> listHolidays(const turbo::RequestContext &ctx,
                                           const std::string &officeId);
    drogon::Task<Json::Value> getHoliday(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createHoliday(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateHoliday(const turbo::RequestContext &ctx, const std::string &id,
                                            const Json::Value &body);
    drogon::Task<void> deleteHoliday(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> activateHoliday(const turbo::RequestContext &ctx, const std::string &id);
    Json::Value holidayTemplate(const turbo::RequestContext &ctx);

    // ---- working days (3) -------------------------------------------------------
    drogon::Task<Json::Value> getWorkingDays(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> updateWorkingDays(const turbo::RequestContext &ctx,
                                                const Json::Value &body);
    Json::Value workingDaysTemplate(const turbo::RequestContext &ctx);

    // ---- currencies (2) ----------------------------------------------------------
    drogon::Task<Json::Value> getCurrencies(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> updateCurrencies(const turbo::RequestContext &ctx,
                                               const Json::Value &body);

    // ---- funds (4) -----------------------------------------------------------------
    drogon::Task<Json::Value> listFunds(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getFund(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createFund(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateFund(const turbo::RequestContext &ctx, const std::string &id,
                                         const Json::Value &body);

    // ---- payment types (5) ---------------------------------------------------------
    drogon::Task<Json::Value> listPaymentTypes(const turbo::RequestContext &ctx, bool onlyActive);
    drogon::Task<Json::Value> getPaymentType(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createPaymentType(const turbo::RequestContext &ctx,
                                                const Json::Value &body);
    drogon::Task<Json::Value> updatePaymentType(const turbo::RequestContext &ctx,
                                                const std::string &id, const Json::Value &body);
    drogon::Task<void> deletePaymentType(const turbo::RequestContext &ctx, const std::string &id);

    // ---- entity-to-entity mapping (6) ------------------------------------------------
    drogon::Task<Json::Value> listEntityMappings(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getEntityMapping(const turbo::RequestContext &ctx,
                                               const std::string &mapId);
    drogon::Task<Json::Value> queryEntityMappings(const turbo::RequestContext &ctx,
                                                  const std::string &relId,
                                                  const std::string &fromId,
                                                  const std::string &toId);
    drogon::Task<Json::Value> createEntityMapping(const turbo::RequestContext &ctx,
                                                  const std::string &relId, const Json::Value &body);
    drogon::Task<Json::Value> updateEntityMapping(const turbo::RequestContext &ctx,
                                                  const std::string &mapId, const Json::Value &body);
    drogon::Task<void> deleteEntityMapping(const turbo::RequestContext &ctx,
                                           const std::string &mapId);

    // ---- taxes (10) --------------------------------------------------------------------
    drogon::Task<Json::Value> listTaxComponents(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getTaxComponent(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createTaxComponent(const turbo::RequestContext &ctx,
                                                 const Json::Value &body);
    drogon::Task<Json::Value> updateTaxComponent(const turbo::RequestContext &ctx,
                                                 const std::string &id, const Json::Value &body);
    drogon::Task<Json::Value> listTaxGroups(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getTaxGroup(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createTaxGroup(const turbo::RequestContext &ctx,
                                             const Json::Value &body);
    drogon::Task<Json::Value> updateTaxGroup(const turbo::RequestContext &ctx, const std::string &id,
                                             const Json::Value &body);
    Json::Value taxComponentTemplate(const turbo::RequestContext &ctx);
    Json::Value taxGroupTemplate(const turbo::RequestContext &ctx);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);
    drogon::Task<Json::Value> officeToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> staffToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> holidayToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> fundToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> paymentTypeToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> taxComponentToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> taxGroupToJson(Txn txn, const std::string &id);
};

}  // namespace turbo_ledger_organization
