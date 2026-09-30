//
// ApiGateway — request pipeline.
//
//   request id -> CORS -> route match -> tenant resolution -> authentication
//   -> rate limit -> idempotency -> sign TL-Context -> proxy -> respond
//
#pragma once

#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "IdempotencyStore.h"
#include "RateLimiter.h"
#include "TenantRegistry.h"

namespace gateway {

struct Route {
    std::string prefix;   ///< path prefix, e.g. "/api/v1/auth/"
    std::string service;  ///< upstream service name
    bool isPublic{false}; ///< no end-user authentication required
};

class GatewayCore {
  public:
    /// Read custom_config.gateway. Must be called after loadConfigFile().
    void initFromAppConfig();

    /// Entry point wired into drogon::app().setDefaultHandler().
    void handle(const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    /// GET /health — fan out to all upstream services.
    drogon::Task<drogon::HttpResponsePtr> healthFanOut();

    /// GET /gateway/routes — operational visibility.
    drogon::HttpResponsePtr describeRoutes();

  private:
    drogon::Task<drogon::HttpResponsePtr> handleAsync(drogon::HttpRequestPtr req);

    const Route *matchRoute(const std::string &path) const;
    drogon::HttpClientPtr clientFor(const std::string &service);
    void decorate(const drogon::HttpRequestPtr &req,
                  const drogon::HttpResponsePtr &resp,
                  const std::string &requestId) const;

    // config
    std::string contextSecret_;
    std::string jwtSecurityKey_;
    std::string jwtIssuer_;
    std::vector<std::string> allowedOrigins_;
    std::vector<Route> routes_;                              // longest-prefix order
    std::unordered_map<std::string, std::string> services_;  // name -> base url
    double upstreamTimeoutSeconds_{15.0};

    // components
    TenantRegistry tenants_;
    std::unique_ptr<RateLimiter> rateLimiter_;
    IdempotencyStore idempotency_;

    std::mutex clientsMutex_;
    std::unordered_map<std::string, drogon::HttpClientPtr> clients_;
};

GatewayCore &core();

}  // namespace gateway
