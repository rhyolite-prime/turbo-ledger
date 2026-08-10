//
// Created by Emmanuel Addo-Odame on 09/08/2026.
//

#include "IdentityApi.h"

#include <json/json.h>
#include <jwt-cpp/jwt.h>
#include "plugins/AccountingServicePlugin.h"
#include <bcrypt.h>

namespace turbo_ledger_accounting::services {

drogon::Task<ApiCredentialsValidationResult> IdentityApi::validateApiCredentials(const std::string &clientId, const std::string &clientSecret) {
  ApiCredentialsValidationResult result;

  auto customConfig = drogon::app().getCustomConfig();
  std::string baseUrl =  customConfig["TurboLedgerApi"]["Ra"]["BaseUrl"].asString();

  auto client = drogon::HttpClient::newHttpClient(baseUrl);
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::Post);

  std::string pathPrefix = "/";
  size_t pos = baseUrl.find("://");
  if (pos != std::string::npos) {
    pos = baseUrl.find('/', pos + 3);
    if (pos != std::string::npos) {
      pathPrefix = baseUrl.substr(pos);
    }
  }
  if (pathPrefix.empty() || pathPrefix.back() != '/') {
    pathPrefix += "/";
  }

  req->setPath(pathPrefix + "api-keys/validate-api-keys");

  Json::Value jsonReq;
  jsonReq["clientId"] = clientId;
  jsonReq["clientSecret"] = clientSecret;

  Json::FastWriter writer;
  req->setContentTypeCode(drogon::CT_APPLICATION_JSON);
  req->setBody(writer.write(jsonReq));

  try {
    auto resp = co_await client->sendRequestCoro(req);
    if (resp && (resp->getStatusCode() == drogon::k200OK ||
                 resp->getStatusCode() == drogon::k401Unauthorized)) {
      auto jsonResp = resp->getJsonObject();
      if (jsonResp && (*jsonResp)["success"].asBool()) {
        result.isValid = true;
        auto resultObj = (*jsonResp)["result"];
        result.accountId = resultObj.isMember("accountId")
                               ? resultObj["accountId"].asString()
                               : "";
        result.businessId = resultObj.isMember("businessId")
                                ? resultObj["businessId"].asString()
                                : "";
      } else {
        result.isValid = false;
        result.errorMessage = jsonResp ? (*jsonResp)["message"].asString()
                                       : "Invalid credentials";
        result.errorCode =
            jsonResp ? (*jsonResp)["error"]["code"].asInt() : 401;
      }
    } else {
      result.isValid = false;
      result.errorMessage = "Failed to communicate with Identity service";
      result.errorCode = 500;
    }
  } catch (const std::exception &e) {
    result.isValid = false;
    result.errorMessage = std::string("Error: ") + e.what();
    result.errorCode = 500;
  }

  co_return result;
}

drogon::Task<ApiCredentialsValidationResult> IdentityApi::validateAndCacheApiCredentials(const std::string &clientId, const std::string &clientSecret) {

  auto plugin = drogon::app().getPlugin<plugins::AccountingServicePlugin>();
  auto &redisCacheManager = plugin->getRedisCacheManager();

  std::string cacheKey = "apikey:" + clientId;

  // 1. Check Redis Cache
  std::string cachedValue = co_await redisCacheManager.getValue(cacheKey);
  if (!cachedValue.empty()) {
    Json::Value jsonResult;
    Json::Reader reader;
    if (reader.parse(cachedValue, jsonResult)) {
      ApiCredentialsValidationResult result;
      if (jsonResult.isMember("clientSecretHash")) {
        std::string cachedHash = jsonResult["clientSecretHash"].asString();
        if (!bcrypt::validatePassword(clientSecret, cachedHash)) {
          result.isValid = false;
          result.errorMessage = "Invalid API credentials";
          result.errorCode = 401;
          co_return result;
        }
        result.isValid = true;
        result.accountId = jsonResult.isMember("accountId")
                               ? jsonResult["accountId"].asString()
                               : "";
        result.businessId = jsonResult.isMember("businessId")
                                ? jsonResult["businessId"].asString()
                                : "";
        co_return result;
      }
    }
  }

  // 2. Cache Miss: Validate against Identity Service
  ApiCredentialsValidationResult result =
      co_await validateApiCredentials(clientId, clientSecret);

  // 3. Cache the result if valid
  if (result.isValid) {
    Json::Value jsonResult;
    jsonResult["isValid"] = result.isValid;
    jsonResult["clientSecretHash"] = bcrypt::generateHash(clientSecret, 6);
    if (!result.accountId.empty())
      jsonResult["accountId"] = result.accountId;
    if (!result.businessId.empty())
      jsonResult["businessId"] = result.businessId;

    Json::FastWriter writer;
    std::string jsonStr = writer.write(jsonResult);

    // Set in Redis with 5 minutes TTL (300 seconds)
    co_await redisCacheManager.setValue(cacheKey, jsonStr);
  }

  co_return result;
}




drogon::Task<ApiCredentialsValidationResult> IdentityApi::validateJwtToken(const std::string &jwtToken) {
  ApiCredentialsValidationResult result;

  try {
    // --- Read JWT configuration ---
    auto customConfig = drogon::app().getCustomConfig();
    const std::string jwtSecurityKey = customConfig["JwtBearer"]["JwtSecurityKey"].asString();
    const std::string jwtIssuer      = customConfig["JwtBearer"]["JwtIssuer"].asString();
    const std::string jwtAudience    = customConfig["JwtBearer"]["JwtAudience"].asString();

    LOG_DEBUG << "[IdentityApi::validateJwtToken] Verifying token — issuer: " << jwtIssuer
              << ", audience: " << jwtAudience;

    // --- Decode & verify (signature, issuer, audience, expiry) ---
    auto decoded = jwt::decode(jwtToken);

    auto verifier = jwt::verify()
                        .allow_algorithm(jwt::algorithm::hs256{jwtSecurityKey})
                        .with_issuer(jwtIssuer)
                        .with_audience(jwtAudience)
                        .leeway(60UL); // allow 60-second clock skew

    verifier.verify(decoded); // throws jwt::error::* on any failure

    LOG_DEBUG << "[IdentityApi::validateJwtToken] Token signature and claims verified.";

    // --- Extract payload claims into result struct ---
    auto extractClaim = [&decoded](const std::string &name) -> std::string {
      if (decoded.has_payload_claim(name)) {
        try { return decoded.get_payload_claim(name).as_string(); }
        catch (...) { /* claim exists but is not a string — skip */ }
      }
      return {};
    };

    result.userId    = extractClaim("userId");
    result.userEmail = extractClaim("email");
    result.username  = extractClaim("username");
    result.firstName = extractClaim("firstName");
    result.lastName  = extractClaim("surName"); // map surName → lastName field
    result.accountId = extractClaim("accountId");
    result.businessId = extractClaim("businessId");

    LOG_DEBUG << "[IdentityApi::validateJwtToken] userId=" << result.userId
              << " email=" << result.userEmail
              << " username=" << result.username;

    result.isValid = true;

  } catch (const jwt::error::token_verification_exception &e) {
    LOG_WARN << "[IdentityApi::validateJwtToken] Verification failed: " << e.what();
    result.isValid      = false;
    result.errorMessage = std::string("Token verification failed: ") + e.what();
    result.errorCode    = 401;

  } catch (const std::exception &e) {
    LOG_ERROR << "[IdentityApi::validateJwtToken] Unexpected error: " << e.what();
    result.isValid      = false;
    result.errorMessage = std::string("JWT validation error: ") + e.what();
    result.errorCode    = 500;
  }

  co_return result;
}


}