import sys

with open("ApiKeyService.cc", "r") as f:
    content = f.read()

# 1. Update Create
old_create = """            //save to redis cache
            std::string cacheKey = "apikey:" + clientId + ":" + clientSecret;

            Json::Value jsonResult;
            jsonResult["isValid"] = true;
            jsonResult["scopes"] = scopesJson;"""

new_create = """            //save to redis cache
            std::string cacheKey = "apikey:" + clientId;

            Json::Value jsonResult;
            jsonResult["isValid"] = true;
            jsonResult["clientSecretHash"] = clientSecretHash;
            jsonResult["scopes"] = scopesJson;"""

if old_create in content:
    content = content.replace(old_create, new_create)
else:
    print("Could not find create logic")


# 2. Update Revoke
old_revoke = """            co_await mapper.update(apiKey);

            response.success = true;
            response.message = "Business API key revoked successfully";"""

new_revoke = """            co_await mapper.update(apiKey);
            
            try {
                services::RedisCacheManager redisManager;
                co_await redisManager.removeValue("apikey:" + apiKey.getValueOfClientId());
            } catch (const std::exception &e) {
                LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
            }

            response.success = true;
            response.message = "Business API key revoked successfully";"""

if old_revoke in content:
    content = content.replace(old_revoke, new_revoke)
else:
    print("Could not find revoke logic")

# 3. Update Activate
old_activate = """            co_await mapper.update(apiKey);
            auditScope.setNewValues(apiKey.toJson());
            auditScope.commit();

            response.success = true;
            response.message = "Business API key activated successfully";"""

new_activate = """            co_await mapper.update(apiKey);
            auditScope.setNewValues(apiKey.toJson());
            auditScope.commit();
            
            try {
                services::RedisCacheManager redisManager;
                co_await redisManager.removeValue("apikey:" + apiKey.getValueOfClientId());
            } catch (const std::exception &e) {
                LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
            }

            response.success = true;
            response.message = "Business API key activated successfully";"""

if old_activate in content:
    content = content.replace(old_activate, new_activate)
else:
    print("Could not find activate logic")


# 4. Update Delete
old_delete = """            co_await mapper.deleteByPrimaryKey(id);
            auditScope.commit();

            response.success = true;
            response.message = "Business API key deleted successfully";"""

new_delete = """            co_await mapper.deleteByPrimaryKey(id);
            auditScope.commit();
            
            try {
                services::RedisCacheManager redisManager;
                co_await redisManager.removeValue("apikey:" + apiKey.getValueOfClientId());
            } catch (const std::exception &e) {
                LOG_ERROR << "Failed to remove API key from Redis: " << e.what();
            }

            response.success = true;
            response.message = "Business API key deleted successfully";"""

if old_delete in content:
    content = content.replace(old_delete, new_delete)
else:
    print("Could not find delete logic")


# 5. Update validateApiCredentials
old_validate = """            auto dbClient = drogon::app().getDbClient();
            CoroMapper<drogon_model::TlIdentity::ApiKeys> apiKeyMapper(dbClient);

            auto keys = co_await apiKeyMapper.findBy(
                Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_client_id, CompareOperator::EQ, clientId) && Criteria(drogon_model::TlIdentity::ApiKeys::Cols::_is_active, CompareOperator::EQ, true)
            );"""

new_validate = """            auto dbClient = drogon::app().getDbClient();
            
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
            );"""

if old_validate in content:
    content = content.replace(old_validate, new_validate)
else:
    print("Could not find validate logic")

with open("ApiKeyService.cc", "w") as f:
    f.write(content)

print("Done updating ApiKeyService.cc")
