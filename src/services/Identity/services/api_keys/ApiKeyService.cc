//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//


#include "ApiKeyService.h"
#include "services/redis/RedisCacheManager.h"
#include "services/audit_logs/AuditScope.h"
#include "models/ApiKeys.h"
#include "models/Users.h"
#include "models/Roles.h"
#include "models/BusinessAccounts.h"
#include "utils/JsonUtils.h"
#include <drogon/drogon.h>
#include <drogon/orm/CoroMapper.h>
#include <bcrypt.h>

#include "constants/ErrorCodes.h"
#include "utils/IdGeneratorUtils.h"

using namespace drogon::orm;

namespace turbo_ledger_identity::services {

    drogon::Task<dto::BaseApiResponse> ApiKeyService::getAll(const dto::UserIdentityDto &identity, int pageNo, int pageSize, const std::string &query) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::ApiKeys> mapper(dbClient);

            drogon::orm::Criteria criteria;
            if (!identity.business_id.empty()) {
                criteria = drogon::orm::Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, drogon::orm::CompareOperator::EQ, identity.business_id);
            } else {
                criteria = drogon::orm::Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, drogon::orm::CompareOperator::IsNull);
            }

            if (!query.empty()) {
                criteria = criteria && (Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_label, CompareOperator::Like, "%" + query + "%"));
            }

            auto apiKeys = co_await mapper.paginate(pageNo, pageSize).findBy(criteria);

            Json::Value result(Json::arrayValue);
            for (const auto &apiKey : apiKeys) {

                auto json = apiKey.toJson();
                json.removeMember("client_id");
                json.removeMember("client_secret_hash");

                result.append(utils::JsonUtils::convertKeysToCamelCase(json));
            }

            response.success = true;
            response.message = "Business API keys retrieved successfully";
            response.result = result;
        } catch (const std::exception &e) {
            response.success = false;
            response.message = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> ApiKeyService::create(const dto::UserIdentityDto &identity, const dto::ApiKeyDto &dto) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::ApiKeys> mapper(dbClient);

            // 1. Generate Client ID and Client Secret
            std::string clientId = utils::IdGeneratorUtils::generateAlphanumericId(10);
            std::string clientSecret = utils::IdGeneratorUtils::generateAlphanumericId(18);

            // 2. Hash Client Secret
            std::string clientSecretHash = bcrypt::generateHash(clientSecret,6);

            drogon_model::TlIdentity::ApiKeys apiKey;
            if (!identity.business_id.empty()) { apiKey.setBusinessId(identity.business_id); } else { apiKey.setBusinessIdToNull(); }
            apiKey.setClientId(clientId);
            apiKey.setClientSecretHash(clientSecretHash);
            apiKey.setLabel(dto.getLabel());
            apiKey.setBusinessName(dto.getBusinessName());

            // get allowed permissions for api key - dto.getApiKeyUserId() user and use it to set the scopes
            Json::Value scopesJson(Json::arrayValue);
            if (!dto.getApiKeyUserId().empty()) {
                try {
                    drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> userMapper(dbClient);
                    auto user = co_await userMapper.findByPrimaryKey(dto.getApiKeyUserId());
                    std::string rolesStr = user.getValueOfRoles();
                    
                    if (!rolesStr.empty()) {
                        Json::Value rolesJson;
                        Json::Reader reader;
                        if (reader.parse(rolesStr, rolesJson) && rolesJson.isArray()) {
                            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> roleMapper(dbClient);
                            for (const auto& roleVal : rolesJson) {
                                std::string roleId;
                                if (roleVal.isString()) {
                                    roleId = roleVal.asString();
                                } else if (roleVal.isObject() && roleVal.isMember("id")) {
                                    roleId = roleVal["id"].asString();
                                }
                                
                                if (!roleId.empty()) {
                                    try {
                                        auto role = co_await roleMapper.findByPrimaryKey(roleId);
                                        std::string permsStr = role.getValueOfPermissions();
                                        if (!permsStr.empty()) {
                                            Json::Value permsJson;
                                            if (reader.parse(permsStr, permsJson) && permsJson.isArray()) {
                                                for (const auto& p : permsJson) {
                                                    scopesJson.append(p);
                                                }
                                            }
                                        }
                                    } catch (...) {}
                                }
                            }
                        }
                    }
                } catch (const drogon::orm::DrogonDbException &) {
                    LOG_ERROR << "Failed to find user " << dto.getApiKeyUserId() << " for API key scopes";
                }
            }
            Json::FastWriter writer;
            apiKey.setScopes(writer.write(scopesJson));

            std::string allowedIpsStr = "{";
            const auto &ips = dto.getAllowedIps();
            for (size_t i = 0; i < ips.size(); ++i) {
                allowedIpsStr += "\"" + ips[i] + "\"";
                if (i < ips.size() - 1) {
                    allowedIpsStr += ",";
                }
            }
            allowedIpsStr += "}";
            apiKey.setAllowedIps(allowedIpsStr);

            // Set basic default fields
            apiKey.setIsActive(true);

            services::AuditScope auditScope(identity.user_id, identity.business_id, "ApiKey", "", "CREATE");

            auto newApiKey = co_await mapper.insert(apiKey);

            response.success = true;
            response.message = "Business API key created successfully";
            response.result["clientId"] = clientId;
            response.result["clientSecret"] = clientSecret;
            auditScope.setEntityId(newApiKey.getValueOfId());
            auditScope.setNewValues(newApiKey.toJson());
            auditScope.commit();

            //save to redis cache
            std::string cacheKey = "apikey:" + clientId;

            Json::Value jsonResult;
            jsonResult["isValid"] = true;
            jsonResult["clientSecretHash"] = clientSecretHash;
            jsonResult["scopes"] = scopesJson;
            
            if (!identity.business_id.empty()) {
                jsonResult["businessId"] = identity.business_id;
                try {
                    drogon::orm::CoroMapper<drogon_model::TlIdentity::BusinessAccounts> baMapper(dbClient);
                    auto ba = co_await baMapper.findByPrimaryKey(identity.business_id);
                    jsonResult["accountId"] = ba.getValueOfAccountId();
                } catch (const drogon::orm::DrogonDbException &) {
                    // Ignore if BusinessAccount not found
                }
            }

            try {
                services::RedisCacheManager redisManager;
                co_await redisManager.setValue(cacheKey, Json::FastWriter().write(jsonResult));
            } catch (const std::exception &e) {
                LOG_ERROR << "Failed to save API key to Redis via RedisCacheManager: " << e.what();
            }

        } catch (const std::exception &e) {
            response.success = false;
            response.message = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> ApiKeyService::revoke(const dto::UserIdentityDto &identity, const std::string &id) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::ApiKeys> mapper(dbClient);

            drogon::orm::Criteria criteria(drogon_model::TlIdentity::ApiKeys::Cols::_id, drogon::orm::CompareOperator::EQ, id);
            if (!identity.business_id.empty()) {
                criteria = criteria && drogon::orm::Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, drogon::orm::CompareOperator::EQ, identity.business_id);
            } else {
                criteria = criteria && drogon::orm::Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, drogon::orm::CompareOperator::IsNull);
            }
            auto keys = co_await mapper.findBy(criteria);

            if (keys.empty()) {
                response.success = false;
                response.message = "API key not found or unauthorized";
                response.error["code"] = constants::ErrorCode::ERR_DB_NOT_FOUND;
                co_return response;
            }

            auto apiKey = keys.front();
            services::AuditScope auditScope(identity.user_id, identity.business_id, "ApiKey", id, "REVOKE");
            auditScope.setOldValues(apiKey.toJson());
            apiKey.setIsActive(false);

            co_await mapper.update(apiKey);
            
            try {
                services::RedisCacheManager redisManager;
                co_await redisManager.removeValue("apikey:" + apiKey.getValueOfClientId());
            } catch (const std::exception &e) {
                LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
            }

            response.success = true;
            response.message = "Business API key revoked successfully";
        } catch (const std::exception &e) {
            response.success = false;
            response.message = e.what();
            response.error["code"] = constants::ErrorCode::ERR_INTERNAL;
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> ApiKeyService::activate(const dto::UserIdentityDto &identity, const std::string &id) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::ApiKeys> mapper(dbClient);

            drogon::orm::Criteria criteria(drogon_model::TlIdentity::ApiKeys::Cols::_id, drogon::orm::CompareOperator::EQ, id);
            if (!identity.business_id.empty()) {
                criteria = criteria && drogon::orm::Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, drogon::orm::CompareOperator::EQ, identity.business_id);
            } else {
                criteria = criteria && drogon::orm::Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, drogon::orm::CompareOperator::IsNull);
            }
            auto keys = co_await mapper.findBy(criteria);

            if (keys.empty()) {
                response.success = false;
                response.message = "API key not found or unauthorized";
                response.error["code"] = constants::ErrorCode::ERR_DB_NOT_FOUND;
                co_return response;
            }

            auto apiKey = keys.front();
            services::AuditScope auditScope(identity.user_id, identity.business_id, "ApiKey", id, "ACTIVATE");
            auditScope.setOldValues(apiKey.toJson());

            apiKey.setIsActive(true);

            co_await mapper.update(apiKey);
            auditScope.setNewValues(apiKey.toJson());
            auditScope.commit();
            
            try {
                services::RedisCacheManager redisManager;
                co_await redisManager.removeValue("apikey:" + apiKey.getValueOfClientId());
            } catch (const std::exception &e) {
                LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
            }

            response.success = true;
            response.message = "Business API key activated successfully";
        } catch (const std::exception &e) {
            response.success = false;
            response.message = e.what();
            response.error["code"] = constants::ErrorCode::ERR_INTERNAL;
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> ApiKeyService::deleteApiKey(const dto::UserIdentityDto &identity, const std::string &id) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            CoroMapper<drogon_model::TlIdentity::ApiKeys> mapper(dbClient);

            Criteria criteria(drogon_model::TlIdentity::ApiKeys::Cols::_id, CompareOperator::EQ, id);
            if (!identity.business_id.empty()) {
                criteria = criteria && Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, CompareOperator::EQ, identity.business_id);
            } else {
                criteria = criteria && Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_business_id, CompareOperator::IsNull);
            }
            auto keys = co_await mapper.findBy(criteria);

            if (keys.empty()) {
                response.success = false;
                response.message = "API key not found or unauthorized";
                response.error["code"] = constants::ErrorCode::ERR_DB_NOT_FOUND;
                co_return response;
            }

            auto apiKey = keys.front();
            services::AuditScope auditScope(identity.user_id, identity.business_id, "ApiKey", id, "DELETE");
            auditScope.setOldValues(apiKey.toJson());
            co_await mapper.deleteByPrimaryKey(id);
            auditScope.commit();
            
            try {
                services::RedisCacheManager redisManager;
                co_await redisManager.removeValue("apikey:" + apiKey.getValueOfClientId());
            } catch (const std::exception &e) {
                LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
            }

            response.success = true;
            response.message = "Business API key deleted successfully";
        } catch (const std::exception &e) {
            response.success = false;
            response.message = e.what();
            response.error["code"] = constants::ErrorCode::ERR_INTERNAL;
        }
        co_return response;
    }

    drogon::Task<ApiCredentialsValidationResult> ApiKeyService::validateApiCredentials(const std::string &clientId, const std::string &clientSecret) {
        ApiCredentialsValidationResult result;
        try {
            auto dbClient = drogon::app().getDbClient();
            
            // Try Redis first
            std::string cacheKey = "apikey:" + clientId;
            try {
                services::RedisCacheManager redisManager;
                std::string cachedData = co_await redisManager.getValue(cacheKey);
                if (!cachedData.empty()) {
                    Json::Value jsonResult;
                    Json::Reader reader;
                    if (reader.parse(cachedData, jsonResult)) {
                        std::string cachedHash = jsonResult["clientSecretHash"].asString();
                        if (!bcrypt::validatePassword(clientSecret, cachedHash)) {
                            result.isValid = false;
                            result.errorMessage = "Invalid API credentials";
                            result.errorCode = constants::ErrorCode::ERR_AUTH_INVALID_CREDENTIALS;
                            co_return result;
                        }
                        
                        result.isValid = true;
                        result.businessId = jsonResult.isMember("businessId") ? jsonResult["businessId"].asString() : "";
                        result.accountId = jsonResult.isMember("accountId") ? jsonResult["accountId"].asString() : "";
                        co_return result;
                    }
                }
            } catch (const std::exception &e) {
                LOG_ERROR << "Redis cache error in validateApiCredentials: " << e.what();
            }

            // Fallback to DB if not in cache
            CoroMapper<drogon_model::TlIdentity::ApiKeys> apiKeyMapper(dbClient);

            auto keys = co_await apiKeyMapper.findBy(
                Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_client_id, CompareOperator::EQ, clientId) && Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_is_active, CompareOperator::EQ, true)
            );

            if (keys.empty()) {
                result.isValid = false;
                result.errorMessage = "Invalid API credentials";
                result.errorCode = constants::ErrorCode::ERR_DB_NOT_FOUND;
                co_return result;
            }

            auto apiKey = keys.front();

            if (!bcrypt::validatePassword(clientSecret, apiKey.getValueOfClientSecretHash())) {
                result.isValid = false;
                result.errorMessage = "Invalid API credentials";
                result.errorCode = constants::ErrorCode::ERR_AUTH_INVALID_CREDENTIALS;
                co_return result;
            }

            const std::string& businessId = apiKey.getValueOfBusinessId();

            CoroMapper<drogon_model::TlIdentity::BusinessAccounts> accountMapper(dbClient);

            drogon_model::TlIdentity::BusinessAccounts account;

            try {
                account = co_await accountMapper.findByPrimaryKey(businessId);
            } catch (const UnexpectedRows &) {
                result.isValid = false;
                result.errorCode = constants::ERR_RESOURCE_NOT_FOUND;
                result.errorMessage = "Business account not found.";
                co_return result;
            }

            result.isValid = true;
            result.accountId = account.getValueOfAccountId();
            result.businessId = businessId;
        } catch (const std::exception &e) {
            result.isValid = false;
            result.errorMessage = e.what();
            result.errorCode = constants::ErrorCode::ERR_INTERNAL;
        }
        co_return result;
    }

}
