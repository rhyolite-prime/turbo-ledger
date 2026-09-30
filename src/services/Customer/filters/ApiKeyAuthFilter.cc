 #include "ApiKeyAuthFilter.h"
#include <drogon/utils/Utilities.h>
#include <drogon/utils/coroutine.h>
#include <drogon/drogon.h>
#include "plugins/CustomerServicePlugin.h"


void ApiKeyAuthFilter::doFilter(const HttpRequestPtr &req,
                                FilterCallback &&fcb,
                                FilterChainCallback &&fccb)
{
    LOG_DEBUG << "[ApiKeyAuthFilter] Incoming request: " << req->getMethodString() << " " << req->getPath();

    // Check Authorization header for Basic auth
    std::string authHeader = req->getHeader("Authorization");
    if (authHeader.empty() || authHeader.substr(0, 6) != "Basic ") {
        LOG_WARN << "[ApiKeyAuthFilter] Missing or malformed Authorization header. Value: '" << authHeader << "'";
        auto res = HttpResponse::newHttpResponse();
        res->setStatusCode(k401Unauthorized);
        res->setContentTypeCode(CT_APPLICATION_JSON);
        res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Missing or invalid Authorization header.\"}");
        fcb(res);
        return;
    }

    std::string base64Str = authHeader.substr(6);
    std::string decodedStr = drogon::utils::base64Decode(base64Str);
    LOG_DEBUG << "[ApiKeyAuthFilter] Decoded Basic auth string length: " << decodedStr.size();

    auto colonPos = decodedStr.find(':');
    if (colonPos == std::string::npos) {
        LOG_WARN << "[ApiKeyAuthFilter] No ':' separator found in decoded auth string.";
        auto res = HttpResponse::newHttpResponse();
        res->setStatusCode(k401Unauthorized);
        res->setContentTypeCode(CT_APPLICATION_JSON);
        res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Invalid Basic Auth format.\"}");
        fcb(res);
        return;
    }

    std::string clientId = decodedStr.substr(0, colonPos);
    std::string clientSecret = decodedStr.substr(colonPos + 1);
    LOG_DEBUG << "[ApiKeyAuthFilter] Extracted clientId: '" << clientId << "' (secret length: " << clientSecret.size() << ")";

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    if (!plugin) {
        LOG_ERROR << "[ApiKeyAuthFilter] CustomerServicePlugin is null — plugin not registered or failed to init.";
        auto res = HttpResponse::newHttpResponse();
        res->setStatusCode(k500InternalServerError);
        res->setContentTypeCode(CT_APPLICATION_JSON);
        res->setBody("{\"error\": \"Internal Error\", \"message\": \"Service plugin unavailable.\"}");
        fcb(res);
        return;
    }
    LOG_DEBUG << "[ApiKeyAuthFilter] Plugin resolved. Queuing async credential validation.";

    // Launch a coroutine to await the async validation method
    drogon::app().getLoop()->queueInLoop([req, fcb = std::move(fcb), fccb = std::move(fccb), clientId, clientSecret, plugin]() mutable {
        drogon::async_run([req, fcb = std::move(fcb), fccb = std::move(fccb), clientId, clientSecret, plugin]() mutable -> drogon::Task<void> {
            try {
                LOG_DEBUG << "[ApiKeyAuthFilter] Calling validateAndCacheApiCredentials for clientId: " << clientId;
                auto &identityApi = plugin->getIdentityApi();
                auto result = co_await identityApi.validateAndCacheApiCredentials(clientId, clientSecret);
                LOG_DEBUG << "[ApiKeyAuthFilter] validateAndCacheApiCredentials returned isValid=" << result.isValid
                          << " accountId='" << result.accountId << "' businessId='" << result.businessId << "'";

                if (!result.isValid) {
                    LOG_WARN << "[ApiKeyAuthFilter] Credentials invalid. errorCode=" << result.errorCode
                             << " message='" << result.errorMessage << "'";
                    auto res = HttpResponse::newHttpResponse();
                    res->setStatusCode(k401Unauthorized);
                    res->setContentTypeCode(CT_APPLICATION_JSON);
                    res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Invalid API credentials.\"}");
                    fcb(res);
                    co_return;
                }

                // Inject accountId and businessId into request
                req->getAttributes()->insert("accountId", result.accountId);
                req->getAttributes()->insert("businessId", result.businessId);
                LOG_DEBUG << "[ApiKeyAuthFilter] Auth passed. Forwarding to handler.";

                fccb();
            } catch (const std::exception& e) {
                LOG_ERROR << "[ApiKeyAuthFilter] Exception during credential validation: " << e.what();
                auto res = HttpResponse::newHttpResponse();
                res->setStatusCode(k500InternalServerError);
                res->setContentTypeCode(CT_APPLICATION_JSON);
                res->setBody(std::string("{\"error\": \"Internal Error\", \"message\": \"") + e.what() + "\"}");
                fcb(res);
            }
        });
    });
}
