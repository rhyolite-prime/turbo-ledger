//
// Turbo Ledger platform library — per-request tenant/user context.
//
// The ApiGateway authenticates every request once, then forwards a signed
// TL-Context header. Services verify the signature locally (no network call)
// and read the context from the request attributes.
//
#pragma once

#include <drogon/HttpRequest.h>
#include <json/json.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace turbo {

class RequestContext {
  public:
    /// Attribute key under which the verified context is stored on the request.
    static constexpr const char *kAttributeKey = "turbo_request_context";
    /// Header carrying the signed context between gateway and services.
    static constexpr const char *kHeaderName = "TL-Context";
    /// Header carrying the tenant identifier from the outside world.
    static constexpr const char *kTenantHeaderName = "TL-Tenant-Id";
    /// Header carrying the correlation / request id.
    static constexpr const char *kRequestIdHeaderName = "X-Request-Id";

    std::string tenantId;                 ///< e.g. "default", "acme_bank"
    std::string userId;                   ///< platform user id (empty for pure M2M keys)
    std::string username;                 ///< display / login name
    std::string authScheme;               ///< "jwt" | "api-key" | "system"
    std::vector<std::string> permissions; ///< resolved permission codes (may be empty; services can lazy-load)
    std::string requestId;                ///< correlation id, generated at the edge
    std::int64_t issuedAtEpoch{0};        ///< unix seconds, set by the gateway
    std::int64_t expiresAtEpoch{0};       ///< unix seconds; short (~60s) validity window

    /// Postgres schema that holds this tenant's data inside a service database.
    [[nodiscard]] std::string tenantSchema() const { return "t_" + tenantId; }

    /// Tenant ids are restricted so they can safely become schema names.
    static bool isValidTenantId(const std::string &id);

    [[nodiscard]] bool hasPermission(const std::string &permission) const;

    [[nodiscard]] Json::Value toJson() const;
    static std::optional<RequestContext> fromJson(const Json::Value &json);

    // ---- request plumbing -------------------------------------------------

    /// Store this (verified) context on a request.
    void attachTo(const drogon::HttpRequestPtr &req) const;

    /// Fetch the verified context previously attached by a filter/gateway.
    static std::optional<RequestContext> from(const drogon::HttpRequestPtr &req);
};

}  // namespace turbo
