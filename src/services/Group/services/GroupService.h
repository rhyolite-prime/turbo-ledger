//
// Phase 7 (retrofit) — Group domain: `groups`, `centers`, `grouplevels`,
// `collectionsheet` (25 endpoints total). Originally scoped out of Phase 4
// (Customer) because Customer's client lifecycle didn't need a real Group
// entity to ship; implemented now, retroactively, per explicit user
// direction, before the rest of Phase 7 (Teller) lands.
//
// Fineract models "Group" and "Center" as the SAME entity
// (`m_group`/`groups` here) at different points of a hierarchy, one level
// discriminated by `level_id`: a Center is a Group one level above regular
// (client-bearing) Groups, holding child Groups instead of client members.
// This service follows that exactly — one `groups` table (the real
// pg_dump baseline this service shipped with), one `group_levels` lookup
// table seeded with the two fixed Fineract levels ("Center"/"Group"), and
// GroupsController / CentersController both call into this one service,
// each pinning the `level_id` filter to their own level — same
// "one physical table, two logical resources discriminated by a type
// column" pattern DAM uses for deposit_type and Portfolio uses for share
// account "type" path segments.
//
// Every operation runs inside the caller's tenant schema
// (turbo::db::beginTenantTxn). RBAC is enforced entirely from the
// gateway-signed TL-Context, matching every other service in this codebase
// — no callback to Identity on the request hot path.
//
// Cross-service ids intentionally trusted as caller-supplied, not
// validated (same precedent as every prior phase): office_id, staff_id,
// closure_reason_cv_id (Organization/SystemConfig code values),
// group_clients.client_id (Customer). No inter-service RPC client exists
// in this codebase.
//
// Documented 501 stubs (cross-service composition with no RPC client, or
// genuinely out of scope — same precedent as Customer's
// `clients/{id}/accounts`):
//   - `groups/{id}/accounts`, `centers/{id}/accounts` — would compose
//     DepositAccountManagement + Portfolio account summaries.
//   - `groups/{id}/glimaccounts` — would compose Portfolio's GLIM loans.
//   - `groups/{id}/gsimaccounts` — would compose DepositAccountManagement's
//     GSIM savings accounts (DAM's GSIM retrofit reads `groups`' existence
//     by trusted id only; it does not call back into this service either).
//   - top-level `POST /collectionsheet` and the groups/centers
//     `generateCollectionSheet`/`saveCollectionSheet` sub-commands — a
//     real implementation needs Portfolio (loan repayment schedules) +
//     DepositAccountManagement (savings due amounts) + attendance/calendar
//     data this phase doesn't own; Fineract itself treats this as its own
//     substantial subsystem. Flagged here, not silently dropped.
// CSV bulk-import/download-template endpoints are skipped, consistent with
// every prior phase.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_group {

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

class GroupService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- group levels (read-only; the two rows are seeded by migration) ----
    drogon::Task<Json::Value> listGroupLevels(const turbo::RequestContext &ctx);

    // ---- groups: core CRUD + lifecycle --------------------------------------
    drogon::Task<Json::Value> listGroups(const turbo::RequestContext &ctx, const std::string &officeId,
                                         const std::string &staffId, const std::string &status,
                                         const std::string &nameLike, int offset, int limit);
    drogon::Task<Json::Value> getGroup(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createGroup(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateGroup(const turbo::RequestContext &ctx, const std::string &id,
                                          const Json::Value &body);
    drogon::Task<void> deleteGroup(const turbo::RequestContext &ctx, const std::string &id);
    Json::Value groupTemplate(const turbo::RequestContext &ctx);
    /// command: activate|close|assignStaff|unassignStaff|associateClients|
    ///   disassociateClients|transferClients|assignRole|unassignRole|updateRole
    drogon::Task<Json::Value> handleGroupCommand(const turbo::RequestContext &ctx, const std::string &id,
                                                 const std::string &command, const Json::Value &body);
    // groups/{id}/accounts, /glimaccounts, /gsimaccounts are 501s handled
    // directly in GroupsController (no service method — same precedent as
    // ClientsController::accountsOverview in Phase 4), see header note.

    // ---- centers: core CRUD + lifecycle --------------------------------------
    drogon::Task<Json::Value> listCenters(const turbo::RequestContext &ctx, const std::string &officeId,
                                          const std::string &staffId, const std::string &status,
                                          const std::string &nameLike, int offset, int limit);
    drogon::Task<Json::Value> getCenter(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createCenter(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateCenter(const turbo::RequestContext &ctx, const std::string &id,
                                           const Json::Value &body);
    drogon::Task<void> deleteCenter(const turbo::RequestContext &ctx, const std::string &id);
    Json::Value centerTemplate(const turbo::RequestContext &ctx);
    /// command: activate|close|assignStaff|unassignStaff|associateGroups|disassociateGroups
    drogon::Task<Json::Value> handleCenterCommand(const turbo::RequestContext &ctx, const std::string &id,
                                                  const std::string &command, const Json::Value &body);
    // centers/{id}/accounts is a 501 handled directly in CentersController.

    // collectionsheet (top-level + groups/centers generate/save sub-commands)
    // is entirely 501, handled directly in the controllers — see header note.

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);

    /// Resolves the fixed "Center" or "Group" group_levels row, created by
    /// V003's seed. Throws ApiError(500) if the seed is somehow missing.
    drogon::Task<std::string> resolveLevelId(Txn txn, bool isCenter);
    drogon::Task<Json::Value> entityToJson(Txn txn, const std::string &id, bool isCenter);
    drogon::Task<std::string> generateAccountNumber(Txn txn, bool isCenter, const std::string &seedId);

    /// Shared CRUD/lifecycle implementation for both groups and centers —
    /// `isCenter` picks the level_id filter and a couple of
    /// center-vs-group-only command branches.
    drogon::Task<Json::Value> listEntities(const turbo::RequestContext &ctx, bool isCenter,
                                           const std::string &officeId, const std::string &staffId,
                                           const std::string &status, const std::string &nameLike,
                                           int offset, int limit);
    drogon::Task<Json::Value> getEntity(const turbo::RequestContext &ctx, bool isCenter,
                                        const std::string &id);
    drogon::Task<Json::Value> createEntity(const turbo::RequestContext &ctx, bool isCenter,
                                           const Json::Value &body);
    drogon::Task<Json::Value> updateEntity(const turbo::RequestContext &ctx, bool isCenter,
                                           const std::string &id, const Json::Value &body);
    drogon::Task<void> deleteEntity(const turbo::RequestContext &ctx, bool isCenter,
                                    const std::string &id);
    drogon::Task<Json::Value> handleCommand(const turbo::RequestContext &ctx, bool isCenter,
                                            const std::string &id, const std::string &command,
                                            const Json::Value &body);
};

}  // namespace turbo_ledger_group
