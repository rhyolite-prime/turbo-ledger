/**
 *
 *  CompositeAuthFilter.cc
 *
 */

#include "CompositeAuthFilter.h"
#include <drogon/utils/Utilities.h>
#include <drogon/utils/coroutine.h>
#include <drogon/drogon.h>

#include "plugins/AccountingServicePlugin.h"

using namespace drogon;

void CompositeAuthFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    LOG_DEBUG << "[CompositeAuthFilter] Incoming request: " << req->getMethodString() << " " << req->getPath();

    std::string authHeader = req->getHeader("Authorization");
    if (authHeader.empty()) {
        LOG_WARN << "[CompositeAuthFilter] Missing Authorization header.";
        auto res = HttpResponse::newHttpResponse();
        res->setStatusCode(k401Unauthorized);
        res->setContentTypeCode(CT_APPLICATION_JSON);
        res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Missing Authorization header.\"}");
        fcb(res);
        return;
    }

    auto plugin = app().getPlugin<turbo_ledger_accounting::plugins::AccountingServicePlugin>();
    if (!plugin) {
        LOG_ERROR << "[CompositeAuthFilter] CustomerServicePlugin is null — plugin not registered or failed to init.";
        auto res = HttpResponse::newHttpResponse();
        res->setStatusCode(k500InternalServerError);
        res->setContentTypeCode(CT_APPLICATION_JSON);
        res->setBody("{\"error\": \"Internal Error\", \"message\": \"Service plugin unavailable.\"}");
        fcb(res);
        return;
    }

    // --- CASE 1: Basic Authentication ---
    if (authHeader.rfind("Basic ", 0) == 0) { // Starts with "Basic "
        std::string base64Str = authHeader.substr(6);
        std::string decodedStr = drogon::utils::base64Decode(base64Str);

        auto colonPos = decodedStr.find(':');
        if (colonPos == std::string::npos) {
            LOG_WARN << "[CompositeAuthFilter] No ':' separator found in decoded Basic auth string.";
            auto res = HttpResponse::newHttpResponse();
            res->setStatusCode(k401Unauthorized);
            res->setContentTypeCode(CT_APPLICATION_JSON);
            res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Invalid Basic Auth format.\"}");
            fcb(res);
            return;
        }

        std::string clientId = decodedStr.substr(0, colonPos);
        std::string clientSecret = decodedStr.substr(colonPos + 1);

        drogon::app().getLoop()->queueInLoop([req, fcb = std::move(fcb), fccb = std::move(fccb), clientId, clientSecret, plugin]() mutable {
            drogon::async_run([req, fcb = std::move(fcb), fccb = std::move(fccb), clientId, clientSecret, plugin]() mutable -> drogon::Task<void> {
                try {
                    LOG_DEBUG << "[CompositeAuthFilter] Validating Basic Auth for clientId: " << clientId;
                    auto &identityApi = plugin->getIdentityApi();
                    auto result = co_await identityApi.validateAndCacheApiCredentials(clientId, clientSecret);

                    if (!result.isValid) {
                        LOG_WARN << "[CompositeAuthFilter] Basic credentials invalid.";
                        auto res = HttpResponse::newHttpResponse();
                        res->setStatusCode(k401Unauthorized);
                        res->setContentTypeCode(CT_APPLICATION_JSON);
                        res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Invalid API credentials.\"}");
                        fcb(res);
                        co_return;
                    }

                    // Inject attributes into request
                    req->getAttributes()->insert("accountId", result.accountId);
                    req->getAttributes()->insert("businessId", result.businessId);
                    req->getAttributes()->insert("authType", std::string("Basic"));

                    fccb();
                } catch (const std::exception& e) {
                    LOG_ERROR << "[CompositeAuthFilter] Exception during Basic validation: " << e.what();
                    auto res = HttpResponse::newHttpResponse();
                    res->setStatusCode(k500InternalServerError);
                    res->setContentTypeCode(CT_APPLICATION_JSON);
                    res->setBody(std::string("{\"error\": \"Internal Error\", \"message\": \"") + e.what() + "\"}");
                    fcb(res);
                }
            });
        });
        return;
    }

    // --- CASE 2: Bearer (JWT) Authentication ---
    if (authHeader.rfind("Bearer ", 0) == 0) { // Starts with "Bearer "
        std::string jwtToken = authHeader.substr(7);

        drogon::app().getLoop()->queueInLoop([req, fcb = std::move(fcb), fccb = std::move(fccb), jwtToken, plugin]() mutable {
            drogon::async_run([req, fcb = std::move(fcb), fccb = std::move(fccb), jwtToken, plugin]() mutable -> drogon::Task<void> {
                try {
                    LOG_DEBUG << "[CompositeAuthFilter] Validating JWT Bearer token...";
                    auto &identityApi = plugin->getIdentityApi();

                    // Adjust this line based on your IdentityApi method name for JWT validation:
                    auto result = co_await identityApi.validateJwtToken(jwtToken);

                    if (!result.isValid) {
                        LOG_WARN << "[CompositeAuthFilter] Invalid or expired JWT token.";
                        auto res = HttpResponse::newHttpResponse();
                        res->setStatusCode(k401Unauthorized);
                        res->setContentTypeCode(CT_APPLICATION_JSON);
                        res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Invalid or expired JWT token.\"}");
                        fcb(res);
                        co_return;
                    }

                    // Inject claims/attributes into request
                    req->getAttributes()->insert("accountId",  result.accountId);
                    req->getAttributes()->insert("businessId", result.businessId);
                    req->getAttributes()->insert("userId",     result.userId);
                    req->getAttributes()->insert("userEmail",  result.userEmail);
                    req->getAttributes()->insert("username",   result.username);
                    req->getAttributes()->insert("firstName",  result.firstName);
                    req->getAttributes()->insert("lastName",   result.lastName);
                    req->getAttributes()->insert("authType", std::string("Bearer"));

                    fccb();
                } catch (const std::exception& e) {
                    LOG_ERROR << "[CompositeAuthFilter] Exception during JWT validation: " << e.what();
                    auto res = HttpResponse::newHttpResponse();
                    res->setStatusCode(k500InternalServerError);
                    res->setContentTypeCode(CT_APPLICATION_JSON);
                    res->setBody(std::string("{\"error\": \"Internal Error\", \"message\": \"") + e.what() + "\"}");
                    fcb(res);
                }
            });
        });
        return;
    }

    // --- FALLBACK: Unsupported Authentication Scheme ---
    LOG_WARN << "[CompositeAuthFilter] Unsupported authorization scheme: '" << authHeader << "'";
    auto res = HttpResponse::newHttpResponse();
    res->setStatusCode(k401Unauthorized);
    res->setContentTypeCode(CT_APPLICATION_JSON);
    res->setBody("{\"error\": \"Unauthorized\", \"message\": \"Unsupported authorization scheme. Use Basic or Bearer.\"}");
    fcb(res);
}
