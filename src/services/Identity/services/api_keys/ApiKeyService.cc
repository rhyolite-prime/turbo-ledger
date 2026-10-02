//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//
// Note: this file deliberately avoids drogon::orm::Mapper<T>/CoroMapper<T>
// against a Transaction. Plain Mapper<T> methods (findByPrimaryKey, findBy,
// insert, ...) are SYNCHRONOUS/blocking (they internally force
// Mode::Blocking) and are not awaitable — co_await-ing them is a hard
// compile error ("no member await_ready"). Only drogon::orm::CoroMapper<T>
// is actually co_await-able, and this service follows the same convention
// already used everywhere else in Identity's tenant-scoped code
// (RbacService, UserService, AuditLogService): raw, parameterised SQL via
// Transaction::execSqlCoro, which IS a proper drogon::Task<Result>.
//

#include "ApiKeyService.h"

#include <bcrypt.h>
#include <drogon/drogon.h>

#include "services/audit_logs/AuditScope.h"
#include "services/redis/RedisCacheManager.h"
#include "turbo/TenantDb.h"
#include "utils/IdGeneratorUtils.h"

namespace turbo_ledger_identity::services {

namespace {
std::string cacheKeyFor(const std::string &tenantId, const std::string &clientId) {
    return "apikey:" + tenantId + ":" + clientId;
}

std::string asStringOr(const Json::Value &row, const char *col, const std::string &fallback = "") {
    return row[col].isNull() ? fallback : row[col].as<std::string>();
}
}  // namespace

drogon::orm::DbClientPtr ApiKeyService::db() { return drogon::app().getDbClient(); }

drogon::Task<Json::Value> ApiKeyService::listApiKeys(const turbo::RequestContext &ctx, int pageNo,
                                                     int pageSize, const std::string &query) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);

    int limit = pageSize > 0 ? pageSize : 10;
    if (limit > 200) limit = 200;
    const int offset = pageNo > 1 ? (pageNo - 1) * limit : 0;

    // limit/offset are validated ints under our own control (not raw user
    // strings), so folding them into the SQL text is safe — matching the
    // pattern used by turbo::PageRequest::toSqlSuffix().
    const std::string sql =
        "SELECT id::text AS id, business_name, label, scopes::text AS scopes, "
        "  allowed_ips::text AS allowed_ips, is_active, last_used_at::text AS last_used_at, "
        "  api_key_user_id::text AS api_key_user_id, created_by::text AS created_by, "
        "  created_at::text AS created_at, modified_by::text AS modified_by, "
        "  modified_at::text AS modified_at "
        "FROM api_keys WHERE ($1 = '' OR label ILIKE '%' || $1 || '%') "
        "ORDER BY created_at DESC NULLS LAST LIMIT " +
        std::to_string(limit) + " OFFSET " + std::to_string(offset);

    auto rows = co_await txn->execSqlCoro(sql, query);

    Json::Reader reader;
    Json::Value result(Json::arrayValue);
    for (const auto &row : rows) {
        Json::Value j;
        j["id"] = row["id"].as<std::string>();
        j["businessName"] = asStringOr(row, "business_name");
        j["label"] = asStringOr(row, "label");

        Json::Value scopesJson(Json::arrayValue);
        if (!row["scopes"].isNull()) reader.parse(row["scopes"].as<std::string>(), scopesJson);
        j["scopes"] = scopesJson;

        j["allowedIps"] = asStringOr(row, "allowed_ips");
        j["isActive"] = row["is_active"].isNull() ? false : row["is_active"].as<bool>();
        j["lastUsedAt"] = asStringOr(row, "last_used_at");
        j["apiKeyUserId"] = asStringOr(row, "api_key_user_id");
        j["createdBy"] = asStringOr(row, "created_by");
        j["createdAt"] = asStringOr(row, "created_at");
        j["modifiedBy"] = asStringOr(row, "modified_by");
        j["modifiedAt"] = asStringOr(row, "modified_at");
        result.append(j);
    }
    co_return result;
}

drogon::Task<Json::Value> ApiKeyService::createApiKey(const turbo::RequestContext &ctx,
                                                      const dto::ApiKeyDto &apiKeyDto) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);

    // 1. Generate Client ID and Client Secret
    const std::string clientId = utils::IdGeneratorUtils::generateAlphanumericId(10);
    const std::string clientSecret = utils::IdGeneratorUtils::generateAlphanumericId(18);

    // 2. Hash Client Secret
    const std::string clientSecretHash = bcrypt::generateHash(clientSecret, 6);

    // 3. Derive allowed scopes from the role(s) assigned to apiKeyUserId — a
    // legacy mechanism distinct from RbacService's relational
    // user_roles/role_permissions tables: Users.roles and Roles.permissions
    // are each a JSON array column. Resolved inside the same tenant
    // transaction as the key itself.
    Json::Value scopesJson(Json::arrayValue);
    Json::Reader reader;
    if (!apiKeyDto.getApiKeyUserId().empty()) {
        try {
            auto userRows = co_await txn->execSqlCoro(
                "SELECT roles::text AS roles FROM users WHERE id = $1::uuid", apiKeyDto.getApiKeyUserId());
            if (!userRows.empty() && !userRows[0]["roles"].isNull()) {
                Json::Value rolesJson;
                if (reader.parse(userRows[0]["roles"].as<std::string>(), rolesJson) && rolesJson.isArray()) {
                    for (const auto &roleVal : rolesJson) {
                        std::string roleId;
                        if (roleVal.isString()) {
                            roleId = roleVal.asString();
                        } else if (roleVal.isObject() && roleVal.isMember("id")) {
                            roleId = roleVal["id"].asString();
                        }
                        if (roleId.empty()) continue;

                        try {
                            auto roleRows = co_await txn->execSqlCoro(
                                "SELECT permissions::text AS permissions FROM roles WHERE id = $1::uuid",
                                roleId);
                            if (!roleRows.empty() && !roleRows[0]["permissions"].isNull()) {
                                Json::Value permsJson;
                                if (reader.parse(roleRows[0]["permissions"].as<std::string>(), permsJson) &&
                                    permsJson.isArray()) {
                                    for (const auto &p : permsJson) scopesJson.append(p);
                                }
                            }
                        } catch (const std::exception &) {
                            // unknown/garbage role id — skip it, don't fail key creation
                        }
                    }
                }
            }
        } catch (const std::exception &e) {
            LOG_ERROR << "Failed to resolve scopes for API key user " << apiKeyDto.getApiKeyUserId() << ": "
                      << e.what();
        }
    }
    Json::FastWriter writer;
    const std::string scopesStr = writer.write(scopesJson);

    std::string allowedIpsStr = "{";
    const auto &ips = apiKeyDto.getAllowedIps();
    for (size_t i = 0; i < ips.size(); ++i) {
        allowedIpsStr += "\"" + ips[i] + "\"";
        if (i + 1 < ips.size()) allowedIpsStr += ",";
    }
    allowedIpsStr += "}";

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", "", "CREATE");

    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO api_keys "
        "  (business_name, client_id, client_secret_hash, label, scopes, allowed_ips, "
        "   is_active, api_key_user_id, created_by) "
        "VALUES ($1, $2, $3, NULLIF($4, ''), $5::jsonb, $6::inet[], true, "
        "  NULLIF($7, '')::uuid, NULLIF($8, '')::uuid) "
        "RETURNING id::text AS id",
        apiKeyDto.getBusinessName(), clientId, clientSecretHash, apiKeyDto.getLabel(), scopesStr,
        allowedIpsStr, apiKeyDto.getApiKeyUserId(), ctx.userId);

    const std::string newId = rows[0]["id"].as<std::string>();

    Json::Value result;
    result["clientId"] = clientId;
    result["clientSecret"] = clientSecret;

    Json::Value newValues;
    newValues["id"] = newId;
    newValues["businessName"] = apiKeyDto.getBusinessName();
    newValues["label"] = apiKeyDto.getLabel();
    newValues["scopes"] = scopesJson;
    auditScope.setEntityId(newId);
    auditScope.setNewValues(newValues);
    auditScope.commit();

    // Cache the hash + scopes for fast validation, keyed per-tenant so two
    // tenants can never collide on the same generated clientId.
    Json::Value cached;
    cached["tenantId"] = ctx.tenantId;
    cached["clientSecretHash"] = clientSecretHash;
    cached["scopes"] = scopesJson;
    try {
        RedisCacheManager redisManager;
        co_await redisManager.setValue(cacheKeyFor(ctx.tenantId, clientId), writer.write(cached));
    } catch (const std::exception &e) {
        LOG_ERROR << "Failed to save API key to Redis via RedisCacheManager: " << e.what();
    }

    co_return result;
}

drogon::Task<Json::Value> ApiKeyService::revokeApiKey(const turbo::RequestContext &ctx,
                                                      const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);

    auto rows = co_await txn->execSqlCoro(
        "SELECT client_id, is_active FROM api_keys WHERE id = $1::uuid", id);
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "API key not found", "error.msg.identity.apikey.not.found");

    const std::string clientId = rows[0]["client_id"].as<std::string>();

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", id, "REVOKE");
    Json::Value oldValues;
    oldValues["id"] = id;
    oldValues["isActive"] = rows[0]["is_active"].isNull() ? false : rows[0]["is_active"].as<bool>();
    auditScope.setOldValues(oldValues);

    co_await txn->execSqlCoro(
        "UPDATE api_keys SET is_active = false, modified_by = NULLIF($2, '')::uuid, modified_at = now() "
        "WHERE id = $1::uuid",
        id, ctx.userId);

    Json::Value newValues = oldValues;
    newValues["isActive"] = false;
    auditScope.setNewValues(newValues);
    auditScope.commit();

    try {
        RedisCacheManager redisManager;
        co_await redisManager.removeValue(cacheKeyFor(ctx.tenantId, clientId));
    } catch (const std::exception &e) {
        LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
    }

    co_return Json::Value(Json::objectValue);
}

drogon::Task<Json::Value> ApiKeyService::activateApiKey(const turbo::RequestContext &ctx,
                                                        const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);

    auto rows = co_await txn->execSqlCoro(
        "SELECT client_id, is_active FROM api_keys WHERE id = $1::uuid", id);
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "API key not found", "error.msg.identity.apikey.not.found");

    const std::string clientId = rows[0]["client_id"].as<std::string>();

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", id, "ACTIVATE");
    Json::Value oldValues;
    oldValues["id"] = id;
    oldValues["isActive"] = rows[0]["is_active"].isNull() ? false : rows[0]["is_active"].as<bool>();
    auditScope.setOldValues(oldValues);

    co_await txn->execSqlCoro(
        "UPDATE api_keys SET is_active = true, modified_by = NULLIF($2, '')::uuid, modified_at = now() "
        "WHERE id = $1::uuid",
        id, ctx.userId);

    Json::Value newValues = oldValues;
    newValues["isActive"] = true;
    auditScope.setNewValues(newValues);
    auditScope.commit();

    try {
        RedisCacheManager redisManager;
        co_await redisManager.removeValue(cacheKeyFor(ctx.tenantId, clientId));
    } catch (const std::exception &e) {
        LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
    }

    co_return Json::Value(Json::objectValue);
}

drogon::Task<void> ApiKeyService::deleteApiKey(const turbo::RequestContext &ctx, const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);

    auto rows = co_await txn->execSqlCoro("SELECT client_id FROM api_keys WHERE id = $1::uuid", id);
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "API key not found", "error.msg.identity.apikey.not.found");

    const std::string clientId = rows[0]["client_id"].as<std::string>();

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", id, "DELETE");
    Json::Value oldValues;
    oldValues["id"] = id;
    auditScope.setOldValues(oldValues);

    co_await txn->execSqlCoro("DELETE FROM api_keys WHERE id = $1::uuid", id);
    auditScope.commit();

    try {
        RedisCacheManager redisManager;
        co_await redisManager.removeValue(cacheKeyFor(ctx.tenantId, clientId));
    } catch (const std::exception &e) {
        LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
    }
}

drogon::Task<ApiCredentialsValidationResult> ApiKeyService::validateApiCredentials(
    const std::string &tenantId, const std::string &clientId, const std::string &clientSecret) {
    ApiCredentialsValidationResult result;
    if (!turbo::RequestContext::isValidTenantId(tenantId)) {
        result.isValid = false;
        result.errorMessage = "Invalid or missing tenant id";
        result.errorCode = drogon::k400BadRequest;
        co_return result;
    }

    // Try Redis first.
    const std::string cacheKey = cacheKeyFor(tenantId, clientId);
    try {
        RedisCacheManager redisManager;
        const std::string cachedData = co_await redisManager.getValue(cacheKey);
        if (!cachedData.empty()) {
            Json::Value cached;
            Json::Reader reader;
            if (reader.parse(cachedData, cached)) {
                if (!bcrypt::validatePassword(clientSecret, cached["clientSecretHash"].asString())) {
                    result.isValid = false;
                    result.errorMessage = "Invalid API credentials";
                    result.errorCode = drogon::k401Unauthorized;
                    co_return result;
                }
                result.isValid = true;
                result.tenantId = tenantId;
                co_return result;
            }
        }
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis cache error in validateApiCredentials: " << e.what();
    }

    // Fallback to the tenant schema.
    try {
        auto txn = co_await turbo::db::beginTenantTxn(db(), tenantId);
        auto rows = co_await txn->execSqlCoro(
            "SELECT client_secret_hash FROM api_keys WHERE client_id = $1 AND is_active = true", clientId);

        if (rows.empty()) {
            result.isValid = false;
            result.errorMessage = "Invalid API credentials";
            result.errorCode = drogon::k404NotFound;
            co_return result;
        }

        if (!bcrypt::validatePassword(clientSecret, rows[0]["client_secret_hash"].as<std::string>())) {
            result.isValid = false;
            result.errorMessage = "Invalid API credentials";
            result.errorCode = drogon::k401Unauthorized;
            co_return result;
        }

        result.isValid = true;
        result.tenantId = tenantId;
    } catch (const std::exception &e) {
        result.isValid = false;
        result.errorMessage = e.what();
        result.errorCode = drogon::k500InternalServerError;
    }
    co_return result;
}

}  // namespace turbo_ledger_identity::services
