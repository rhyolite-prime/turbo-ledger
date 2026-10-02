//
// Turbo Ledger platform library — internal (service-to-service) HTTP client.
//
// Up through Phase 8, only ApiGateway ever made outbound HTTP calls (see
// GatewayCore). Phase 9's SelfService and Interoperation services are
// backend-for-frontend / composition services: they must call Customer,
// Portfolio and DepositAccountManagement directly, bypassing the gateway,
// the same way the gateway itself talks to backend services — by minting a
// freshly-signed TL-Context header with the shared dev secret
// (custom_config.turbo.context_secret) and issuing a drogon::HttpClient
// coroutine request.
//
// Security model: the caller never forwards the inbound context verbatim.
// It constructs a new, deliberately-scoped RequestContext for the outbound
// call — same tenant, authScheme "system", and *only* the permission codes
// the calling code path legitimately needs (see each call site). This
// keeps the downstream call's privilege exactly as wide as the specific
// composition it performs, not a blanket admin identity. Ownership checks
// (e.g. "this self-service user owns this client/account") must happen in
// the calling service *before* using InternalClient — InternalClient itself
// performs no authorization, it only transports an already-decided context.
//
#pragma once

#include <drogon/HttpClient.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>

#include <memory>
#include <mutex>
#include <string>

#include "turbo/RequestContext.h"

namespace turbo {

class InternalClient {
  public:
    struct Result {
        drogon::HttpStatusCode status{drogon::k200OK};
        Json::Value body{Json::nullValue};
        bool ok() const { return static_cast<int>(status) < 400; }
    };

    /// `baseUrl` e.g. "http://127.0.0.1:7504" (scheme+host+port only).
    /// `contextSecret` must match the target service's own
    /// custom_config.turbo.context_secret (shared dev secret across the
    /// platform in this sandbox).
    InternalClient(std::string baseUrl, std::string contextSecret);

    /// Issue a request to `path` (must start with '/'), minting a signed
    /// TL-Context from `ctx`. `jsonBody` is serialized and sent for
    /// methods that carry a body; ignored for Get/Delete.
    drogon::Task<Result> call(const RequestContext &ctx, drogon::HttpMethod method,
                              std::string path, Json::Value jsonBody = Json::Value(),
                              double timeoutSeconds = 10.0) const;

  private:
    std::string baseUrl_;
    std::string contextSecret_;
    mutable std::mutex mutex_;
    mutable drogon::HttpClientPtr client_;

    drogon::HttpClientPtr clientPtr() const;
};

}  // namespace turbo
