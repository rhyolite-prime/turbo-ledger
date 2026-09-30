#include "RbacService.h"

#include <bcrypt.h>
#include <drogon/orm/CoroMapper.h>
#include <memory>
#include <sstream>

#include "models/Users.h"
#include "turbo/TenantDb.h"

using drogon::HttpStatusCode;
using drogon::orm::CoroMapper;
using drogon::orm::Criteria;
using drogon::orm::CompareOperator;
using drogon::orm::DrogonDbException;
using UsersModel = drogon_model::TlIdentity::Users;

namespace turbo_ledger_identity::rbac {

namespace {

Json::Value parseJsonOrEmpty(const std::string &text) {
    Json::Value out;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream stream(text);
    if (!Json::parseFromStream(builder, stream, &out, &errs)) out = Json::Value(Json::objectValue);
    return out;
}

std::string asStringOr(const Json::Value &v, const char *key, const std::string &fallback = "") {
    return v.isMember(key) && v[key].isString() ? v[key].asString() : fallback;
}

bool allowSelfApproval() {
    const auto &cfg = drogon::app().getCustomConfig();
    if (cfg.isMember("identity") && cfg["identity"].isMember("maker_checker"))
        return cfg["identity"]["maker_checker"].get("allow_self_approval", true).asBool();
    return true;  // dev-friendly default; production should turn this off
}

}  // namespace

drogon::orm::DbClientPtr RbacService::db() { return drogon::app().getDbClient(); }

// ---------------------------------------------------------------------------
// Principal
// ---------------------------------------------------------------------------

drogon::Task<Principal> RbacService::resolvePrincipal(const turbo::RequestContext &ctx) {
    Principal p;
    if (ctx.userId.empty()) co_return p;
    p.userId = ctx.userId;
    p.username = ctx.username;

    // 1) tenant-schema user
    try {
        auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
        auto rows = co_await txn->execSqlCoro(
            "SELECT id::text AS id, username, is_active, is_locked_out "
            "FROM users WHERE id::text = $1",
            ctx.userId);
        if (rows.size() == 1) {
            const auto &u = rows[0];
            if (!u["is_active"].as<bool>() || u["is_locked_out"].as<bool>())
                throw ApiError(drogon::k403Forbidden, "User account is inactive or locked",
                               "error.msg.identity.user.inactive");
            p.found = true;
            p.username = u["username"].isNull() ? p.username : u["username"].as<std::string>();
            auto perms = co_await txn->execSqlCoro(
                "SELECT DISTINCT rp.permission_code FROM user_roles ur "
                "JOIN roles r ON r.id = ur.role_id AND NOT r.is_disabled "
                "JOIN role_permissions rp ON rp.role_id = r.id "
                "WHERE ur.user_id::text = $1",
                ctx.userId);
            for (const auto &row : perms)
                p.permissions.insert(row["permission_code"].as<std::string>());
            p.superUser = p.permissions.contains("ALL_FUNCTIONS");
            co_return p;
        }
    } catch (const ApiError &) {
        throw;
    } catch (const std::exception &) {
        // schema missing / malformed id — fall through to host lookup
    }

    // 2) host operator (public.users) — platform super-user
    try {
        CoroMapper<UsersModel> mapper(db());
        auto user = co_await mapper.findOne(
            Criteria(UsersModel::Cols::_id, CompareOperator::EQ, ctx.userId));
        if (user.getValueOfIsActive() && !user.getValueOfIsLockedOut()) {
            p.found = true;
            p.isHost = true;
            p.superUser = true;
            p.username = user.getValueOfUsername();
        }
    } catch (const std::exception &) {
        // not a host user either
    }
    co_return p;
}

void RbacService::requirePermission(const Principal &p, const std::string &code, bool readOnly) {
    if (!p.found)
        throw ApiError(drogon::k401Unauthorized, "Authenticated platform user required",
                       "error.msg.platform.unauthorized");
    const bool ok = readOnly ? p.canRead(code) : p.has(code);
    if (!ok)
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

// ---------------------------------------------------------------------------
// Permissions
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> RbacService::listPermissions(const turbo::RequestContext &ctx) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "READ_PERMISSION", /*readOnly=*/true);

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT grouping, code, entity_name, action_name, can_maker_checker "
        "FROM permissions ORDER BY grouping, code");
    Json::Value list(Json::arrayValue);
    for (const auto &row : rows) {
        Json::Value j;
        j["grouping"] = row["grouping"].as<std::string>();
        j["code"] = row["code"].as<std::string>();
        j["entityName"] = row["entity_name"].isNull() ? "" : row["entity_name"].as<std::string>();
        j["actionName"] = row["action_name"].isNull() ? "" : row["action_name"].as<std::string>();
        j["makerCheckerEnabled"] = row["can_maker_checker"].as<bool>();
        list.append(j);
    }
    Json::Value out;
    out["permissions"] = list;
    out["totalCount"] = static_cast<Json::UInt64>(rows.size());
    co_return out;
}

drogon::Task<Json::Value> RbacService::setMakerChecker(const turbo::RequestContext &ctx,
                                                       const std::string &code, bool enabled) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "UPDATE_PERMISSION");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE permissions SET can_maker_checker = $2 WHERE code = $1 "
        "RETURNING code, can_maker_checker",
        code, enabled);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Unknown permission code: " + code,
                       "error.msg.identity.permission.not.found");
    Json::Value out;
    out["code"] = rows[0]["code"].as<std::string>();
    out["makerCheckerEnabled"] = rows[0]["can_maker_checker"].as<bool>();
    co_return out;
}

// ---------------------------------------------------------------------------
// Roles
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> RbacService::roleToJson(Txn txn, const std::string &roleId) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, description, is_disabled FROM roles WHERE id::text = $1",
        roleId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Role not found", "error.msg.identity.role.not.found");
    Json::Value j;
    j["id"] = rows[0]["id"].as<std::string>();
    j["name"] = rows[0]["name"].as<std::string>();
    j["description"] =
        rows[0]["description"].isNull() ? "" : rows[0]["description"].as<std::string>();
    j["disabled"] = rows[0]["is_disabled"].as<bool>();
    Json::Value codes(Json::arrayValue);
    auto perms = co_await txn->execSqlCoro(
        "SELECT permission_code FROM role_permissions WHERE role_id::text = $1 "
        "ORDER BY permission_code",
        roleId);
    for (const auto &row : perms) codes.append(row["permission_code"].as<std::string>());
    j["permissions"] = codes;
    auto users = co_await txn->execSqlCoro(
        "SELECT count(*) AS c FROM user_roles WHERE role_id::text = $1", roleId);
    j["userCount"] = users[0]["c"].as<Json::Int64>();
    co_return j;
}

drogon::Task<Json::Value> RbacService::listRoles(const turbo::RequestContext &ctx) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "READ_ROLE", true);

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT r.id::text AS id, r.name, r.description, r.is_disabled, "
        "  (SELECT count(*) FROM role_permissions rp WHERE rp.role_id = r.id) AS perm_count, "
        "  (SELECT count(*) FROM user_roles ur WHERE ur.role_id = r.id) AS user_count "
        "FROM roles r ORDER BY r.name");
    Json::Value list(Json::arrayValue);
    for (const auto &row : rows) {
        Json::Value j;
        j["id"] = row["id"].as<std::string>();
        j["name"] = row["name"].as<std::string>();
        j["description"] = row["description"].isNull() ? "" : row["description"].as<std::string>();
        j["disabled"] = row["is_disabled"].as<bool>();
        j["permissionCount"] = row["perm_count"].as<Json::Int64>();
        j["userCount"] = row["user_count"].as<Json::Int64>();
        list.append(j);
    }
    Json::Value out;
    out["roles"] = list;
    out["totalCount"] = static_cast<Json::UInt64>(rows.size());
    co_return out;
}

drogon::Task<Json::Value> RbacService::getRole(const turbo::RequestContext &ctx,
                                               const std::string &id) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "READ_ROLE", true);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await roleToJson(txn, id);
}

drogon::Task<Json::Value> RbacService::createRole(const turbo::RequestContext &ctx,
                                                  const Json::Value &body) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "CREATE_ROLE");

    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "Role name is required",
                       "error.msg.identity.role.name.required");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto exists = co_await txn->execSqlCoro("SELECT 1 FROM roles WHERE name = $1", name);
    if (exists.size() > 0)
        throw ApiError(drogon::k409Conflict, "A role with this name already exists",
                       "error.msg.identity.role.duplicate.name");

    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO roles (name, description, permissions) VALUES ($1, $2, '[]'::jsonb) "
        "RETURNING id::text AS id",
        name, asStringOr(body, "description"));
    const std::string roleId = rows[0]["id"].as<std::string>();

    if (body.isMember("permissions") && body["permissions"].isArray()) {
        for (const auto &code : body["permissions"]) {
            auto ok = co_await txn->execSqlCoro(
                "INSERT INTO role_permissions (role_id, permission_code) "
                "SELECT $1::uuid, code FROM permissions WHERE code = $2 "
                "ON CONFLICT DO NOTHING RETURNING permission_code",
                roleId, code.asString());
            if (ok.size() == 0)
                throw ApiError(drogon::k400BadRequest,
                               "Unknown permission code: " + code.asString(),
                               "error.msg.identity.permission.not.found");
        }
    }
    co_return co_await roleToJson(txn, roleId);
}

drogon::Task<Json::Value> RbacService::updateRole(const turbo::RequestContext &ctx,
                                                  const std::string &id, const Json::Value &body) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "UPDATE_ROLE");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE roles SET name = COALESCE(NULLIF($2, ''), name), "
        "  description = COALESCE(NULLIF($3, ''), description), modified_at = now() "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "name"), asStringOr(body, "description"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Role not found", "error.msg.identity.role.not.found");
    co_return co_await roleToJson(txn, id);
}

drogon::Task<void> RbacService::deleteRole(const turbo::RequestContext &ctx,
                                           const std::string &id) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "DELETE_ROLE");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto role = co_await txn->execSqlCoro(
        "SELECT name FROM roles WHERE id::text = $1", id);
    if (role.size() == 0)
        throw ApiError(drogon::k404NotFound, "Role not found", "error.msg.identity.role.not.found");
    if (role[0]["name"].as<std::string>() == "Super user")
        throw ApiError(drogon::k403Forbidden, "The Super user role cannot be deleted",
                       "error.msg.identity.role.protected");
    auto used = co_await txn->execSqlCoro(
        "SELECT count(*) AS c FROM user_roles WHERE role_id::text = $1", id);
    if (used[0]["c"].as<Json::Int64>() > 0)
        throw ApiError(drogon::k409Conflict, "Role is assigned to users and cannot be deleted",
                       "error.msg.identity.role.in.use");
    co_await txn->execSqlCoro("DELETE FROM roles WHERE id::text = $1", id);
    co_return;
}

drogon::Task<Json::Value> RbacService::setRoleDisabled(const turbo::RequestContext &ctx,
                                                       const std::string &id, bool disabled) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, disabled ? "DISABLE_ROLE" : "ENABLE_ROLE");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto role = co_await txn->execSqlCoro("SELECT name FROM roles WHERE id::text = $1", id);
    if (role.size() == 0)
        throw ApiError(drogon::k404NotFound, "Role not found", "error.msg.identity.role.not.found");
    if (disabled && role[0]["name"].as<std::string>() == "Super user")
        throw ApiError(drogon::k403Forbidden, "The Super user role cannot be disabled",
                       "error.msg.identity.role.protected");
    co_await txn->execSqlCoro("UPDATE roles SET is_disabled = $2, modified_at = now() "
                              "WHERE id::text = $1", id, disabled);
    co_return co_await roleToJson(txn, id);
}

drogon::Task<Json::Value> RbacService::setRolePermissions(const turbo::RequestContext &ctx,
                                                          const std::string &id,
                                                          const Json::Value &codes) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "PERMISSIONS_ROLE");
    if (!codes.isArray())
        throw ApiError(drogon::k400BadRequest, "'permissions' must be an array of codes",
                       "error.msg.identity.permissions.invalid");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto role = co_await txn->execSqlCoro("SELECT 1 FROM roles WHERE id::text = $1", id);
    if (role.size() == 0)
        throw ApiError(drogon::k404NotFound, "Role not found", "error.msg.identity.role.not.found");

    co_await txn->execSqlCoro("DELETE FROM role_permissions WHERE role_id::text = $1", id);
    for (const auto &code : codes) {
        auto ok = co_await txn->execSqlCoro(
            "INSERT INTO role_permissions (role_id, permission_code) "
            "SELECT $1::uuid, code FROM permissions WHERE code = $2 RETURNING permission_code",
            id, code.asString());
        if (ok.size() == 0)
            throw ApiError(drogon::k400BadRequest, "Unknown permission code: " + code.asString(),
                           "error.msg.identity.permission.not.found");
    }
    co_return co_await roleToJson(txn, id);
}

// ---------------------------------------------------------------------------
// Users
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> RbacService::listUsers(const turbo::RequestContext &ctx, int pageNo,
                                                 int pageSize) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "READ_USER", true);
    pageSize = std::clamp(pageSize, 1, 200);
    pageNo = std::max(1, pageNo);

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto total = co_await txn->execSqlCoro("SELECT count(*) AS c FROM users");
    auto rows = co_await txn->execSqlCoro(
        "SELECT u.id::text AS id, u.first_name, u.last_name, u.email, u.username, "
        "  u.is_active, u.is_locked_out, "
        "  COALESCE((SELECT json_agg(r.name ORDER BY r.name) FROM user_roles ur "
        "            JOIN roles r ON r.id = ur.role_id WHERE ur.user_id = u.id), '[]') AS roles "
        "FROM users u ORDER BY u.username NULLS LAST, u.email "
        "LIMIT $1 OFFSET $2",
        pageSize, (pageNo - 1) * pageSize);

    Json::Value list(Json::arrayValue);
    for (const auto &row : rows) {
        Json::Value j;
        j["id"] = row["id"].as<std::string>();
        j["firstName"] = row["first_name"].isNull() ? "" : row["first_name"].as<std::string>();
        j["lastName"] = row["last_name"].isNull() ? "" : row["last_name"].as<std::string>();
        j["email"] = row["email"].as<std::string>();
        j["username"] = row["username"].isNull() ? "" : row["username"].as<std::string>();
        j["active"] = row["is_active"].as<bool>();
        j["lockedOut"] = row["is_locked_out"].as<bool>();
        j["roles"] = parseJsonOrEmpty(row["roles"].as<std::string>());
        list.append(j);
    }
    Json::Value out;
    out["users"] = list;
    out["pageNo"] = pageNo;
    out["pageSize"] = pageSize;
    out["totalCount"] = total[0]["c"].as<Json::Int64>();
    co_return out;
}

drogon::Task<Json::Value> RbacService::getUser(const turbo::RequestContext &ctx,
                                               const std::string &id) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "READ_USER", true);

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT u.id::text AS id, u.first_name, u.last_name, u.email, u.username, "
        "  u.phone_number, u.is_active, u.is_locked_out, "
        "  COALESCE((SELECT json_agg(json_build_object('id', r.id::text, 'name', r.name)) "
        "            FROM user_roles ur JOIN roles r ON r.id = ur.role_id "
        "            WHERE ur.user_id = u.id), '[]') AS roles "
        "FROM users u WHERE u.id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "User not found", "error.msg.identity.user.not.found");
    const auto &row = rows[0];
    Json::Value j;
    j["id"] = row["id"].as<std::string>();
    j["firstName"] = row["first_name"].isNull() ? "" : row["first_name"].as<std::string>();
    j["lastName"] = row["last_name"].isNull() ? "" : row["last_name"].as<std::string>();
    j["email"] = row["email"].as<std::string>();
    j["username"] = row["username"].isNull() ? "" : row["username"].as<std::string>();
    j["phoneNumber"] = row["phone_number"].isNull() ? "" : row["phone_number"].as<std::string>();
    j["active"] = row["is_active"].as<bool>();
    j["lockedOut"] = row["is_locked_out"].as<bool>();
    j["roles"] = parseJsonOrEmpty(row["roles"].as<std::string>());
    co_return j;
}

drogon::Task<Json::Value> RbacService::createUserInTxn(Txn txn, const Json::Value &body) {
    const std::string username = asStringOr(body, "username");
    const std::string email = asStringOr(body, "email");
    const std::string password = asStringOr(body, "password");
    if (username.empty() || email.empty())
        throw ApiError(drogon::k400BadRequest, "'username' and 'email' are required",
                       "error.msg.identity.user.fields.required");
    if (password.size() < 8)
        throw ApiError(drogon::k400BadRequest, "'password' must be at least 8 characters",
                       "error.msg.identity.user.password.weak");

    auto dup = co_await txn->execSqlCoro(
        "SELECT 1 FROM users WHERE username = $1 OR email = $2", username, email);
    if (dup.size() > 0)
        throw ApiError(drogon::k409Conflict, "Username or email already in use",
                       "error.msg.identity.user.duplicate");

    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO users (first_name, last_name, email, username, password_hash, "
        "                   phone_number, is_active, is_locked_out, roles) "
        "VALUES ($1, $2, $3, $4, $5, NULLIF($6, ''), true, false, '[]'::jsonb) "
        "RETURNING id::text AS id",
        asStringOr(body, "firstName"), asStringOr(body, "lastName"), email, username,
        bcrypt::generateHash(password, 10), asStringOr(body, "phoneNumber"));
    const std::string userId = rows[0]["id"].as<std::string>();

    if (body.isMember("roles") && body["roles"].isArray()) {
        for (const auto &role : body["roles"]) {
            auto ok = co_await txn->execSqlCoro(
                "INSERT INTO user_roles (user_id, role_id) "
                "SELECT $1::uuid, id FROM roles WHERE id::text = $2 OR name = $2 "
                "ON CONFLICT DO NOTHING RETURNING role_id",
                userId, role.asString());
            if (ok.size() == 0)
                throw ApiError(drogon::k400BadRequest, "Unknown role: " + role.asString(),
                               "error.msg.identity.role.not.found");
        }
    }
    Json::Value out;
    out["id"] = userId;
    out["username"] = username;
    out["email"] = email;
    co_return out;
}

drogon::Task<Json::Value> RbacService::createUser(const turbo::RequestContext &ctx,
                                                  const Json::Value &body) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "CREATE_USER");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto mc = co_await txn->execSqlCoro(
        "SELECT can_maker_checker FROM permissions WHERE code = 'CREATE_USER'");
    const bool makerChecker = mc.size() > 0 && mc[0]["can_maker_checker"].as<bool>();

    if (makerChecker) {
        Json::StreamWriterBuilder w;
        w["indentation"] = "";
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO tl_commands (action, entity_name, payload, maker_id, maker_username) "
            "VALUES ('CREATE_USER', 'USER', $1::jsonb, NULLIF($2, '')::uuid, $3) "
            "RETURNING id::text AS id, made_on::text AS made_on",
            Json::writeString(w, body), principal.userId, principal.username);
        Json::Value out;
        out["pendingApproval"] = true;
        out["commandId"] = rows[0]["id"].as<std::string>();
        out["action"] = "CREATE_USER";
        out["madeOn"] = rows[0]["made_on"].as<std::string>();
        co_return out;
    }
    co_return co_await createUserInTxn(txn, body);
}

drogon::Task<Json::Value> RbacService::updateUser(const turbo::RequestContext &ctx,
                                                  const std::string &id, const Json::Value &body) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "UPDATE_USER");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE users SET first_name = COALESCE(NULLIF($2, ''), first_name), "
        "  last_name  = COALESCE(NULLIF($3, ''), last_name), "
        "  email      = COALESCE(NULLIF($4, ''), email), "
        "  phone_number = COALESCE(NULLIF($5, ''), phone_number) "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "firstName"), asStringOr(body, "lastName"),
        asStringOr(body, "email"), asStringOr(body, "phoneNumber"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "User not found", "error.msg.identity.user.not.found");
    co_return co_await getUser(ctx, id);
}

drogon::Task<void> RbacService::deleteUser(const turbo::RequestContext &ctx,
                                           const std::string &id) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "DELETE_USER");
    if (principal.userId == id)
        throw ApiError(drogon::k403Forbidden, "You cannot delete your own account",
                       "error.msg.identity.user.self.delete");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "DELETE FROM users WHERE id::text = $1 RETURNING id", id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "User not found", "error.msg.identity.user.not.found");
    co_return;
}

drogon::Task<Json::Value> RbacService::setUserFlag(const turbo::RequestContext &ctx,
                                                   const std::string &id,
                                                   const std::string &column, bool value,
                                                   const std::string &permissionCode) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, permissionCode);
    if (column != "is_active" && column != "is_locked_out")
        throw ApiError(drogon::k500InternalServerError, "Unsupported user flag");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    const std::string sql =
        "UPDATE users SET " + column + " = $2 WHERE id::text = $1 RETURNING id::text AS id";
    auto rows = co_await txn->execSqlCoro(sql, id, value);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "User not found", "error.msg.identity.user.not.found");
    co_return co_await getUser(ctx, id);
}

drogon::Task<Json::Value> RbacService::assignRoles(const turbo::RequestContext &ctx,
                                                   const std::string &id,
                                                   const Json::Value &roles) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "ASSIGNROLES_USER");
    if (!roles.isArray())
        throw ApiError(drogon::k400BadRequest, "'roles' must be an array (ids or names)",
                       "error.msg.identity.roles.invalid");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await txn->execSqlCoro("SELECT 1 FROM users WHERE id::text = $1", id);
    if (user.size() == 0)
        throw ApiError(drogon::k404NotFound, "User not found", "error.msg.identity.user.not.found");

    co_await txn->execSqlCoro("DELETE FROM user_roles WHERE user_id::text = $1", id);
    for (const auto &role : roles) {
        auto ok = co_await txn->execSqlCoro(
            "INSERT INTO user_roles (user_id, role_id) "
            "SELECT $1::uuid, id FROM roles WHERE id::text = $2 OR name = $2 "
            "ON CONFLICT DO NOTHING RETURNING role_id",
            id, role.asString());
        if (ok.size() == 0)
            throw ApiError(drogon::k400BadRequest, "Unknown role: " + role.asString(),
                           "error.msg.identity.role.not.found");
    }
    co_return co_await getUser(ctx, id);
}

// ---------------------------------------------------------------------------
// Maker-checker
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> RbacService::listCommands(const turbo::RequestContext &ctx,
                                                    const std::string &status) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "READ_MAKERCHECKER", true);

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    const std::string wanted = status.empty() ? "PENDING" : status;
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, action, entity_name, status, payload::text AS payload, "
        "  maker_username, made_on::text AS made_on, checker_username, "
        "  checked_on::text AS checked_on, failure_reason "
        "FROM tl_commands WHERE status = $1 OR $1 = 'ALL' ORDER BY made_on DESC LIMIT 200",
        wanted);
    Json::Value list(Json::arrayValue);
    for (const auto &row : rows) {
        Json::Value j;
        j["commandId"] = row["id"].as<std::string>();
        j["action"] = row["action"].as<std::string>();
        j["entityName"] = row["entity_name"].isNull() ? "" : row["entity_name"].as<std::string>();
        j["status"] = row["status"].as<std::string>();
        j["payload"] = parseJsonOrEmpty(row["payload"].as<std::string>());
        j["maker"] = row["maker_username"].isNull() ? "" : row["maker_username"].as<std::string>();
        j["madeOn"] = row["made_on"].as<std::string>();
        if (!row["checker_username"].isNull())
            j["checker"] = row["checker_username"].as<std::string>();
        if (!row["checked_on"].isNull()) j["checkedOn"] = row["checked_on"].as<std::string>();
        if (!row["failure_reason"].isNull())
            j["failureReason"] = row["failure_reason"].as<std::string>();
        list.append(j);
    }
    Json::Value out;
    out["commands"] = list;
    out["totalCount"] = static_cast<Json::UInt64>(rows.size());
    co_return out;
}

drogon::Task<Json::Value> RbacService::approveCommand(const turbo::RequestContext &ctx,
                                                      const std::string &id) {
    auto principal = co_await resolvePrincipal(ctx);
    if (!principal.found)
        throw ApiError(drogon::k401Unauthorized, "Authenticated platform user required",
                       "error.msg.platform.unauthorized");
    if (!(principal.superUser || principal.has("APPROVE_MAKERCHECKER") ||
          principal.permissions.contains("CHECKER_SUPER_USER")))
        throw ApiError(drogon::k403Forbidden, "Missing permission: APPROVE_MAKERCHECKER",
                       "error.msg.platform.permission.denied");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, action, payload::text AS payload, maker_id::text AS maker_id "
        "FROM tl_commands WHERE id::text = $1 AND status = 'PENDING' FOR UPDATE",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "No pending command with this id",
                       "error.msg.identity.command.not.found");

    const std::string makerId =
        rows[0]["maker_id"].isNull() ? "" : rows[0]["maker_id"].as<std::string>();
    if (!allowSelfApproval() && makerId == principal.userId)
        throw ApiError(drogon::k403Forbidden,
                       "Four-eyes: the maker of a command cannot approve it",
                       "error.msg.identity.command.self.approval");

    const std::string action = rows[0]["action"].as<std::string>();
    const Json::Value payload = parseJsonOrEmpty(rows[0]["payload"].as<std::string>());

    Json::Value result;
    if (action == "CREATE_USER") {
        result = co_await createUserInTxn(txn, payload);
    } else {
        throw ApiError(drogon::k400BadRequest, "No executor registered for action: " + action,
                       "error.msg.identity.command.unsupported");
    }

    Json::StreamWriterBuilder w;
    w["indentation"] = "";
    co_await txn->execSqlCoro(
        "UPDATE tl_commands SET status = 'APPROVED', checker_id = NULLIF($2, '')::uuid, "
        "  checker_username = $3, checked_on = now(), result = $4::jsonb "
        "WHERE id::text = $1",
        id, principal.userId, principal.username, Json::writeString(w, result));

    Json::Value out;
    out["commandId"] = id;
    out["status"] = "APPROVED";
    out["action"] = action;
    out["result"] = result;
    co_return out;
}

drogon::Task<Json::Value> RbacService::rejectCommand(const turbo::RequestContext &ctx,
                                                     const std::string &id,
                                                     const std::string &reason) {
    auto principal = co_await resolvePrincipal(ctx);
    if (!principal.found)
        throw ApiError(drogon::k401Unauthorized, "Authenticated platform user required",
                       "error.msg.platform.unauthorized");
    if (!(principal.superUser || principal.has("REJECT_MAKERCHECKER") ||
          principal.permissions.contains("CHECKER_SUPER_USER")))
        throw ApiError(drogon::k403Forbidden, "Missing permission: REJECT_MAKERCHECKER",
                       "error.msg.platform.permission.denied");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE tl_commands SET status = 'REJECTED', checker_id = NULLIF($2, '')::uuid, "
        "  checker_username = $3, checked_on = now(), failure_reason = NULLIF($4, '') "
        "WHERE id::text = $1 AND status = 'PENDING' RETURNING id::text AS id",
        id, principal.userId, principal.username, reason);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "No pending command with this id",
                       "error.msg.identity.command.not.found");
    Json::Value out;
    out["commandId"] = id;
    out["status"] = "REJECTED";
    co_return out;
}

drogon::Task<void> RbacService::deleteCommand(const turbo::RequestContext &ctx,
                                              const std::string &id) {
    auto principal = co_await resolvePrincipal(ctx);
    requirePermission(principal, "DELETE_MAKERCHECKER");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE tl_commands SET status = 'DELETED' WHERE id::text = $1 AND status = 'PENDING' "
        "RETURNING id",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "No pending command with this id",
                       "error.msg.identity.command.not.found");
    co_return;
}

// ---------------------------------------------------------------------------
// Self
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> RbacService::selfDetails(const turbo::RequestContext &ctx) {
    auto principal = co_await resolvePrincipal(ctx);
    if (!principal.found)
        throw ApiError(drogon::k401Unauthorized, "Authenticated platform user required",
                       "error.msg.platform.unauthorized");
    Json::Value out;
    out["userId"] = principal.userId;
    out["username"] = principal.username;
    out["tenantId"] = ctx.tenantId;
    out["hostOperator"] = principal.isHost;
    out["superUser"] = principal.superUser;
    Json::Value perms(Json::arrayValue);
    for (const auto &code : principal.permissions) perms.append(code);
    out["permissions"] = perms;
    if (!principal.isHost) {
        out["profile"] = co_await getUser(ctx, principal.userId);
    }
    co_return out;
}

drogon::Task<void> RbacService::changePassword(const turbo::RequestContext &ctx,
                                               const std::string &oldPassword,
                                               const std::string &newPassword) {
    auto principal = co_await resolvePrincipal(ctx);
    if (!principal.found)
        throw ApiError(drogon::k401Unauthorized, "Authenticated platform user required",
                       "error.msg.platform.unauthorized");
    if (newPassword.size() < 8)
        throw ApiError(drogon::k400BadRequest, "'newPassword' must be at least 8 characters",
                       "error.msg.identity.user.password.weak");

    if (principal.isHost) {
        CoroMapper<UsersModel> mapper(db());
        auto user = co_await mapper.findOne(
            Criteria(UsersModel::Cols::_id, CompareOperator::EQ, principal.userId));
        if (!bcrypt::validatePassword(oldPassword, user.getValueOfPasswordHash()))
            throw ApiError(drogon::k403Forbidden, "Current password is incorrect",
                           "error.msg.identity.password.mismatch");
        user.setPasswordHash(bcrypt::generateHash(newPassword, 10));
        co_await mapper.update(user);
        co_return;
    }

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT password_hash FROM users WHERE id::text = $1", principal.userId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "User not found", "error.msg.identity.user.not.found");
    if (!bcrypt::validatePassword(oldPassword, rows[0]["password_hash"].as<std::string>()))
        throw ApiError(drogon::k403Forbidden, "Current password is incorrect",
                       "error.msg.identity.password.mismatch");
    co_await txn->execSqlCoro("UPDATE users SET password_hash = $2 WHERE id::text = $1",
                              principal.userId, bcrypt::generateHash(newPassword, 10));
    co_return;
}

}  // namespace turbo_ledger_identity::rbac
