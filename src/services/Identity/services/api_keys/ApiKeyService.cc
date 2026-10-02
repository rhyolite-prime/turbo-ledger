//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#include "ApiKeyService.h"

#include <bcrypt.h>
#include <drogon/drogon.h>
#include <drogon/orm/Mapper.h>

#include "models/ApiKeys.h"
#include "models/Roles.h"
#include "models/Users.h"
#include "services/audit_logs/AuditScope.h"
#include "services/redis/RedisCacheManager.h"
#include "turbo/TenantDb.h"
#include "utils/IdGeneratorUtils.h"
#include "utils/JsonUtils.h"

using namespace drogon::orm;

namespace turbo_ledger_identity::services {

namespace {
std::string cacheKeyFor(const std::string &tenantId, const std::string &clientId) {
    return "apikey:" + tenantId + ":" + clientId;
}
}  // namespace

drogon::orm::DbClientPtr ApiKeyService::db() { return drogon::app().getDbClient(); }

drogon::Task<Json::Value> ApiKeyService::listApiKeys(const turbo::RequestContext &ctx, int pageNo,
                                                     int pageSize, const std::string &query) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<drogon_model::TlIdentity::ApiKeys> mapper(txn);

    std::vector<drogon_model::TlIdentity::ApiKeys> apiKeys;
    if (!query.empty()) {
        Criteria criteria(drogon_model::TlIdentity::ApiKeys::Cols::_label, CompareOperator::Like,
                          "%" + query + "%");
        apiKeys = co_await mapper.paginate(pageNo, pageSize).findBy(criteria);
    } else {
        apiKeys = co_await mapper.paginate(pageNo, pageSize).findAll();
    }

    Json::Value result(Json::arrayValue);
    for (const auto &apiKey : apiKeys) {
        auto json = apiKey.toJson();
        json.removeMember("client_id");
        json.removeMember("client_secret_hash");
        result.append(utils::JsonUtils::convertKeysToCamelCase(json));
    }
    co_return result;
}

drogon::Task<Json::Value> ApiKeyService::createApiKey(const turbo::RequestContext &ctx,
                                                      const dto::ApiKeyDto &apiKeyDto) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<drogon_model::TlIdentity::ApiKeys> mapper(txn);

    // 1. Generate Client ID and Client Secret
    const std::string clientId = utils::IdGeneratorUtils::generateAlphanumericId(10);
    const std::string clientSecret = utils::IdGeneratorUtils::generateAlphanumericId(18);

    // 2. Hash Client Secret
    const std::string clientSecretHash = bcrypt::generateHash(clientSecret, 6);

    drogon_model::TlIdentity::ApiKeys apiKey;
    apiKey.setClientId(clientId);
    apiKey.setClientSecretHash(clientSecretHash);
    apiKey.setLabel(apiKeyDto.getLabel());
    apiKey.setBusinessName(apiKeyDto.getBusinessName());

    // Derive allowed scopes from the role(s) assigned to apiKeyUserId, all
    // resolved inside the same tenant schema as the key itself.
    Json::Value scopesJson(Json::arrayValue);
    if (!apiKeyDto.getApiKeyUserId().empty()) {
        try {
            Mapper<drogon_model::TlIdentity::Users> userMapper(txn);
            auto user = co_await userMapper.findByPrimaryKey(apiKeyDto.getApiKeyUserId());
            const std::string rolesStr = user.getValueOfRoles();

            if (!rolesStr.empty()) {
                Json::Value rolesJson;
                Json::Reader reader;
                if (reader.parse(rolesStr, rolesJson) && rolesJson.isArray()) {
                    Mapper<drogon_model::TlIdentity::Roles> roleMapper(txn);
                    for (const auto &roleVal : rolesJson) {
                        std::string roleId;
                        if (roleVal.isString()) {
                            roleId = roleVal.asString();
                        } else if (roleVal.isObject() && roleVal.isMember("id")) {
                            roleId = roleVal["id"].asString();
                        }

                        if (roleId.empty()) continue;
                        try {
                            auto role = co_await roleMapper.findByPrimaryKey(roleId);
                            const std::string permsStr = role.getValueOfPermissions();
                            if (!permsStr.empty()) {
                                Json::Value permsJson;
                                if (reader.parse(permsStr, permsJson) && permsJson.isArray()) {
                                    for (const auto &p : permsJson) scopesJson.append(p);
                                }
                            }
                        } catch (...) {
                        }
                    }
                }
            }
        } catch (const drogon::orm::DrogonDbException &) {
            LOG_ERROR << "Failed to find user " << apiKeyDto.getApiKeyUserId() << " for API key scopes";
        }
    }
    Json::FastWriter writer;
    apiKey.setScopes(writer.write(scopesJson));

    std::string allowedIpsStr = "{";
    const auto &ips = apiKeyDto.getAllowedIps();
    for (size_t i = 0; i < ips.size(); ++i) {
        allowedIpsStr += "\"" + ips[i] + "\"";
        if (i < ips.size() - 1) allowedIpsStr += ",";
    }
    allowedIpsStr += "}";
    apiKey.setAllowedIps(allowedIpsStr);
    apiKey.setIsActive(true);

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", "", "CREATE");

    auto newApiKey = co_await mapper.insert(apiKey);

    Json::Value result;
    result["clientId"] = clientId;
    result["clientSecret"] = clientSecret;
    auditScope.setEntityId(newApiKey.getValueOfId());
    auditScope.setNewValues(newApiKey.toJson());
    auditScope.commit();

    // Cache the hash + scopes for fast validation, keyed per-tenant so two
    // tenants can never collide on the same generated clientId.
    Json::Value cached;
    cached["tenantId"] = ctx.tenantId;
    cached["clientSecretHash"] = clientSecretHash;
    cached["scopes"] = scopesJson;
    try {
        RedisCacheManager redisManager;
        co_await redisManager.setValue(cacheKeyFor(ctx.tenantId, clientId), Json::FastWriter().write(cached));
    } catch (const std::exception &e) {
        LOG_ERROR << "Failed to save API key to Redis via RedisCacheManager: " << e.what();
    }

    co_return result;
}

drogon::Task<Json::Value> ApiKeyService::revokeApiKey(const turbo::RequestContext &ctx,
                                                      const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<drogon_model::TlIdentity::ApiKeys> mapper(txn);

    drogon_model::TlIdentity::ApiKeys apiKey;
    try {
        apiKey = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "API key not found", "error.msg.identity.apikey.not.found");
    }

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", id, "REVOKE");
    auditScope.setOldValues(apiKey.toJson());
    apiKey.setIsActive(false);
    co_await mapper.update(apiKey);
    auditScope.setNewValues(apiKey.toJson());
    auditScope.commit();

    try {
        RedisCacheManager redisManager;
        co_await redisManager.removeValue(cacheKeyFor(ctx.tenantId, apiKey.getValueOfClientId()));
    } catch (const std::exception &e) {
        LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
    }

    co_return Json::Value(Json::objectValue);
}

drogon::Task<Json::Value> ApiKeyService::activateApiKey(const turbo::RequestContext &ctx,
                                                        const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<drogon_model::TlIdentity::ApiKeys> mapper(txn);

    drogon_model::TlIdentity::ApiKeys apiKey;
    try {
        apiKey = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "API key not found", "error.msg.identity.apikey.not.found");
    }

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", id, "ACTIVATE");
    auditScope.setOldValues(apiKey.toJson());
    apiKey.setIsActive(true);
    co_await mapper.update(apiKey);
    auditScope.setNewValues(apiKey.toJson());
    auditScope.commit();

    try {
        RedisCacheManager redisManager;
        co_await redisManager.removeValue(cacheKeyFor(ctx.tenantId, apiKey.getValueOfClientId()));
    } catch (const std::exception &e) {
        LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
    }

    co_return Json::Value(Json::objectValue);
}

drogon::Task<void> ApiKeyService::deleteApiKey(const turbo::RequestContext &ctx, const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<drogon_model::TlIdentity::ApiKeys> mapper(txn);

    drogon_model::TlIdentity::ApiKeys apiKey;
    try {
        apiKey = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "API key not found", "error.msg.identity.apikey.not.found");
    }

    AuditScope auditScope(ctx.userId, ctx.tenantId, "ApiKey", id, "DELETE");
    auditScope.setOldValues(apiKey.toJson());
    co_await mapper.deleteByPrimaryKey(id);
    auditScope.commit();

    try {
        RedisCacheManager redisManager;
        co_await redisManager.removeValue(cacheKeyFor(ctx.tenantId, apiKey.getValueOfClientId()));
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
        Mapper<drogon_model::TlIdentity::ApiKeys> apiKeyMapper(txn);
        auto keys = co_await apiKeyMapper.findBy(
            Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_client_id, CompareOperator::EQ, clientId) &&
            Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_is_active, CompareOperator::EQ, true));

        if (keys.empty()) {
            result.isValid = false;
            result.errorMessage = "Invalid API credentials";
            result.errorCode = drogon::k404NotFound;
            co_return result;
        }

        const auto &apiKey = keys.front();
        if (!bcrypt::validatePassword(clientSecret, apiKey.getValueOfClientSecretHash())) {
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
