//
// Phase 1 — tenant-scoped RBAC + maker-checker command store.
//
// All operations run inside the caller's tenant schema (t_<tenantId>) via
// turbo::db::beginTenantTxn. The permission model follows Apache Fineract:
// a seeded permission catalog, roles carrying permission sets, and per-action
// maker-checker (four-eyes) via the tl_commands store.
//
// Host operators (rows in public.users, e.g. the platform admin) resolve as
// super-users inside any tenant.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <set>
#include <stdexcept>
#include <string>

#include "turbo/RequestContext.h"

namespace turbo_ledger_identity::rbac {

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

struct Principal {
    bool found{false};
    bool isHost{false};       ///< resolved from public.users (platform operator)
    bool superUser{false};    ///< host user or holder of ALL_FUNCTIONS
    std::string userId;
    std::string username;
    std::set<std::string> permissions;

    [[nodiscard]] bool has(const std::string &code) const {
        return superUser || permissions.contains(code) ||
               permissions.contains("ALL_FUNCTIONS");
    }
    [[nodiscard]] bool canRead(const std::string &code) const {
        return has(code) || permissions.contains("ALL_FUNCTIONS_READ");
    }
};

class RbacService {
  public:
    // ---- principal ---------------------------------------------------------
    drogon::Task<Principal> resolvePrincipal(const turbo::RequestContext &ctx);
    /// Throws ApiError(403) unless the principal holds `code`.
    static void requirePermission(const Principal &p, const std::string &code,
                                  bool readOnly = false);

    // ---- permissions (2) ---------------------------------------------------
    drogon::Task<Json::Value> listPermissions(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> setMakerChecker(const turbo::RequestContext &ctx,
                                              const std::string &code, bool enabled);

    // ---- roles (8) ---------------------------------------------------------
    drogon::Task<Json::Value> listRoles(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getRole(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createRole(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateRole(const turbo::RequestContext &ctx, const std::string &id,
                                         const Json::Value &body);
    drogon::Task<void> deleteRole(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> setRoleDisabled(const turbo::RequestContext &ctx,
                                              const std::string &id, bool disabled);
    drogon::Task<Json::Value> setRolePermissions(const turbo::RequestContext &ctx,
                                                 const std::string &id, const Json::Value &codes);

    // ---- users (9) ---------------------------------------------------------
    drogon::Task<Json::Value> listUsers(const turbo::RequestContext &ctx, int pageNo, int pageSize);
    drogon::Task<Json::Value> getUser(const turbo::RequestContext &ctx, const std::string &id);
    /// Maker-checker aware: returns {"pendingApproval":true,...} when queued.
    drogon::Task<Json::Value> createUser(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateUser(const turbo::RequestContext &ctx, const std::string &id,
                                         const Json::Value &body);
    drogon::Task<void> deleteUser(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> setUserFlag(const turbo::RequestContext &ctx, const std::string &id,
                                          const std::string &column, bool value,
                                          const std::string &permissionCode);
    drogon::Task<Json::Value> assignRoles(const turbo::RequestContext &ctx, const std::string &id,
                                          const Json::Value &roles);

    // ---- maker-checker (4) -------------------------------------------------
    drogon::Task<Json::Value> listCommands(const turbo::RequestContext &ctx,
                                           const std::string &status);
    drogon::Task<Json::Value> approveCommand(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> rejectCommand(const turbo::RequestContext &ctx, const std::string &id,
                                            const std::string &reason);
    drogon::Task<void> deleteCommand(const turbo::RequestContext &ctx, const std::string &id);

    // ---- self --------------------------------------------------------------
    drogon::Task<Json::Value> selfDetails(const turbo::RequestContext &ctx);
    drogon::Task<void> changePassword(const turbo::RequestContext &ctx,
                                      const std::string &oldPassword,
                                      const std::string &newPassword);

  private:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    /// Insert the user row inside `txn` (validation, hashing, role links).
    drogon::Task<Json::Value> createUserInTxn(Txn txn, const Json::Value &body);
    drogon::Task<Json::Value> roleToJson(Txn txn, const std::string &roleId);
    static drogon::orm::DbClientPtr db();
};

}  // namespace turbo_ledger_identity::rbac
