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

#include "turbo/RequestContext.h"

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

    /// Phase 8 — Batch API (`POST /api/v1/batches`): executes a JSON array of
    /// sub-requests sequentially against this same gateway's routing table,
    /// reusing the already-authenticated tenant/user context. Sub-requests
    /// may reference an earlier sub-response's JSON body via
    /// "$.<requestId>.<dotted.field.path>" placeholders inside `relativeUrl`
    /// or any string leaf of `body`. Best-effort only: there is no
    /// cross-service transaction, so a failed sub-request does not roll
    /// back ones that already succeeded — each entry in the response array
    /// reports its own status independently.
    drogon::Task<drogon::HttpResponsePtr> handleBatch(drogon::HttpRequestPtr req,
                                                       turbo::RequestContext ctx,
                                                       std::string requestId);

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
