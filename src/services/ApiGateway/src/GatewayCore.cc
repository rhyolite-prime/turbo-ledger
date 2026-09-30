#include "GatewayCore.h"

#include <drogon/drogon.h>
#include <jwt-cpp/jwt.h>
#include <algorithm>
#include <chrono>

#include "turbo/ApiResponse.h"
#include "turbo/ContextCodec.h"
#include "turbo/Ids.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo::RequestContext;

namespace gateway {

GatewayCore &core() {
    static GatewayCore instance;
    return instance;
}

void GatewayCore::initFromAppConfig() {
    const auto &cfg = drogon::app().getCustomConfig()["gateway"];

    contextSecret_ = cfg.get("context_secret", "").asString();
    jwtSecurityKey_ = cfg["jwt"].get("security_key", "").asString();
    jwtIssuer_ = cfg["jwt"].get("issuer", "").asString();
    upstreamTimeoutSeconds_ = cfg.get("upstream_timeout_seconds", 15.0).asDouble();

    for (const auto &o : cfg["allowed_origins"]) allowedOrigins_.push_back(o.asString());

    for (const auto &name : cfg["services"].getMemberNames())
        services_[name] = cfg["services"][name].asString();

    for (const auto &r : cfg["routes"]) {
        Route route;
        route.prefix = r.get("prefix", "").asString();
        route.service = r.get("service", "").asString();
        route.isPublic = r.get("public", false).asBool();
        if (!route.prefix.empty() && services_.count(route.service)) routes_.push_back(route);
    }
    // longest prefix first
    std::sort(routes_.begin(), routes_.end(),
              [](const Route &a, const Route &b) { return a.prefix.size() > b.prefix.size(); });

    const auto &rl = cfg["rate_limit"];
    rateLimiter_ = std::make_unique<RateLimiter>(rl.get("requests_per_second", 50.0).asDouble(),
                                                 rl.get("burst", 100.0).asDouble());

    tenants_.loadFromConfig(cfg["tenants"]);
    tenants_.configureProvisioner(cfg["provisioner"].get("base_url", "").asString(),
                                  cfg["provisioner"].get("cache_ttl_seconds", 5.0).asDouble(),
                                  contextSecret_);

    if (contextSecret_.empty())
        LOG_ERROR << "gateway.context_secret is not configured — internal context signing "
                     "will reject all requests";
    LOG_INFO << "Gateway initialised: " << routes_.size() << " route(s), " << services_.size()
             << " service(s), " << tenants_.size() << " tenant(s)";
}

const Route *GatewayCore::matchRoute(const std::string &path) const {
    for (const auto &r : routes_) {
        if (path.rfind(r.prefix, 0) == 0) return &r;
    }
    return nullptr;
}

drogon::HttpClientPtr GatewayCore::clientFor(const std::string &service) {
    std::lock_guard<std::mutex> lock(clientsMutex_);
    auto it = clients_.find(service);
    if (it != clients_.end()) return it->second;
    auto client = drogon::HttpClient::newHttpClient(services_[service]);
    clients_[service] = client;
    return client;
}

void GatewayCore::decorate(const drogon::HttpRequestPtr &req,
                           const drogon::HttpResponsePtr &resp,
                           const std::string &requestId) const {
    resp->addHeader(RequestContext::kRequestIdHeaderName, requestId);
    const auto origin = req->getHeader("Origin");
    if (!origin.empty() &&
        (allowedOrigins_.empty() ||
         std::find(allowedOrigins_.begin(), allowedOrigins_.end(), origin) !=
             allowedOrigins_.end())) {
        resp->addHeader("Access-Control-Allow-Origin", origin);
        resp->addHeader("Access-Control-Allow-Credentials", "true");
        resp->addHeader("Vary", "Origin");
    }
}

void GatewayCore::handle(const drogon::HttpRequestPtr &req,
                         std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto cb = std::make_shared<std::function<void(const drogon::HttpResponsePtr &)>>(
        std::move(callback));
    drogon::async_run([this, req, cb]() -> drogon::Task<> {
        drogon::HttpResponsePtr resp;
        try {
            resp = co_await handleAsync(req);
        } catch (const std::exception &e) {
            LOG_ERROR << "Gateway pipeline error: " << e.what();
            resp = ApiResponse::httpError(drogon::k500InternalServerError,
                                          "Gateway pipeline error");
        }
        (*cb)(resp);
        co_return;
    });
}

drogon::Task<drogon::HttpResponsePtr> GatewayCore::handleAsync(drogon::HttpRequestPtr req) {
    const std::string requestId = turbo::ids::newRequestId();
    const std::string path = req->path();

    // ---- CORS preflight ----------------------------------------------------
    if (req->method() == drogon::Options) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, PATCH, DELETE, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers",
                        "Content-Type, Authorization, TL-Tenant-Id, Idempotency-Key, "
                        "ClientId, ClientSecret, X-Requested-With, Origin, Accept");
        resp->addHeader("Access-Control-Max-Age", "600");
        decorate(req, resp, requestId);
        co_return resp;
    }

    // ---- route -------------------------------------------------------------
    const Route *route = matchRoute(path);
    if (route == nullptr) {
        auto resp = ApiResponse::httpError(drogon::k404NotFound,
                                           "No route for path: " + path,
                                           "error.msg.gateway.route.not.found");
        decorate(req, resp, requestId);
        co_return resp;
    }

    // ---- tenant ------------------------------------------------------------
    const std::string tenantId = req->getHeader(RequestContext::kTenantHeaderName);
    if (tenantId.empty()) {
        auto resp = ApiResponse::httpBadRequest(
            std::string("Missing required header: ") + RequestContext::kTenantHeaderName);
        decorate(req, resp, requestId);
        co_return resp;
    }
    if (!RequestContext::isValidTenantId(tenantId)) {
        auto resp = ApiResponse::httpBadRequest("Malformed tenant id");
        decorate(req, resp, requestId);
        co_return resp;
    }
    auto tenant = co_await tenants_.find(tenantId);
    if (!tenant) {
        auto resp = ApiResponse::httpError(drogon::k404NotFound, "Unknown tenant: " + tenantId,
                                           "error.msg.gateway.tenant.unknown");
        decorate(req, resp, requestId);
        co_return resp;
    }
    if (!tenant->isActive()) {
        auto resp = ApiResponse::httpError(drogon::k403Forbidden,
                                           "Tenant is not active: " + tenant->statusLabel(),
                                           "error.msg.gateway.tenant.inactive");
        decorate(req, resp, requestId);
        co_return resp;
    }

    // ---- rate limit ----------------------------------------------------------
    const std::string peer = req->getPeerAddr().toIp();
    if (!rateLimiter_->allow(tenantId + "|" + peer)) {
        auto resp = ApiResponse::httpError(drogon::k429TooManyRequests, "Rate limit exceeded",
                                           "error.msg.gateway.rate.limited");
        resp->addHeader("Retry-After", "1");
        decorate(req, resp, requestId);
        co_return resp;
    }

    // ---- authentication ------------------------------------------------------
    RequestContext ctx;
    ctx.tenantId = tenantId;
    ctx.requestId = requestId;
    const auto now = std::chrono::duration_cast<std::chrono::seconds>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count();
    ctx.issuedAtEpoch = now;
    ctx.expiresAtEpoch = now + 60;

    const std::string authHeader = req->getHeader("Authorization");
    const bool hasApiKey =
        !req->getHeader("ClientId").empty() && !req->getHeader("ClientSecret").empty();

    if (!route->isPublic) {
        if (authHeader.rfind("Bearer ", 0) == 0) {
            try {
                auto decoded = jwt::decode(authHeader.substr(7));
                auto verifier = jwt::verify()
                                    .allow_algorithm(jwt::algorithm::hs256{jwtSecurityKey_})
                                    .with_issuer(jwtIssuer_);
                verifier.verify(decoded);
                ctx.authScheme = "jwt";
                if (decoded.has_payload_claim("userId"))
                    ctx.userId = decoded.get_payload_claim("userId").as_string();
                if (decoded.has_payload_claim("username"))
                    ctx.username = decoded.get_payload_claim("username").as_string();
                // Phase 2: the token carries the caller's resolved permission set
                // (embedded by Identity at signin) so every downstream service can
                // enforce RBAC from the signed TL-Context alone — see plan §2.3/§2.4.
                if (decoded.has_payload_claim("su") &&
                    decoded.get_payload_claim("su").as_string() == "1") {
                    ctx.permissions.push_back("ALL_FUNCTIONS");
                } else if (decoded.has_payload_claim("perm")) {
                    const auto permClaim = decoded.get_payload_claim("perm").as_string();
                    size_t start = 0;
                    while (start <= permClaim.size()) {
                        auto comma = permClaim.find(',', start);
                        auto code = permClaim.substr(
                            start, comma == std::string::npos ? std::string::npos : comma - start);
                        if (!code.empty()) ctx.permissions.push_back(code);
                        if (comma == std::string::npos) break;
                        start = comma + 1;
                    }
                }
                // Cross-tenant replay protection: a token minted for one tenant
                // must not be usable under another tenant's header.
                if (decoded.has_payload_claim("tenantId")) {
                    const auto tokenTenant =
                        decoded.get_payload_claim("tenantId").as_string();
                    if (!tokenTenant.empty() && tokenTenant != tenantId) {
                        auto resp = ApiResponse::httpUnauthorized(
                            "Token was issued for a different tenant");
                        decorate(req, resp, requestId);
                        co_return resp;
                    }
                }
            } catch (const std::exception &e) {
                auto resp = ApiResponse::httpUnauthorized(
                    std::string("Invalid bearer token: ") + e.what());
                decorate(req, resp, requestId);
                co_return resp;
            }
        } else if (hasApiKey) {
            // Machine-to-machine path: credentials are validated by the upstream
            // service against Identity (legacy flow, kept during Phase 0/1).
            ctx.authScheme = "api-key";
        } else {
            auto resp = ApiResponse::httpUnauthorized(
                "Provide a Bearer token or ClientId/ClientSecret headers");
            decorate(req, resp, requestId);
            co_return resp;
        }
    } else {
        ctx.authScheme = "anonymous";
    }

    // ---- idempotency ---------------------------------------------------------
    const std::string idempotencyKey = req->getHeader("Idempotency-Key");
    std::string idemStoreKey;
    const bool isMutation = req->method() == drogon::Post || req->method() == drogon::Put ||
                            req->method() == drogon::Patch;
    if (isMutation && !idempotencyKey.empty()) {
        idemStoreKey = tenantId + "|" + req->getMethodString() + "|" + path + "|" + idempotencyKey;
        StoredResponse replay;
        switch (idempotency_.begin(idemStoreKey, replay)) {
            case IdempotencyStore::BeginResult::kReplayed: {
                auto resp = drogon::HttpResponse::newHttpResponse();
                resp->setStatusCode(static_cast<drogon::HttpStatusCode>(replay.statusCode));
                resp->setBody(replay.body);
                if (!replay.contentType.empty())
                    resp->addHeader("Content-Type", replay.contentType);
                resp->addHeader("Idempotency-Replayed", "true");
                decorate(req, resp, requestId);
                co_return resp;
            }
            case IdempotencyStore::BeginResult::kInFlight: {
                auto resp = ApiResponse::httpError(
                    drogon::k409Conflict,
                    "A request with this Idempotency-Key is already in progress",
                    "error.msg.gateway.idempotency.in.progress");
                decorate(req, resp, requestId);
                co_return resp;
            }
            case IdempotencyStore::BeginResult::kNew:
                break;
        }
    }

    // ---- proxy -----------------------------------------------------------------
    auto upstreamReq = drogon::HttpRequest::newHttpRequest();
    upstreamReq->setMethod(req->method());
    std::string fullPath = path;
    const auto &query = req->query();
    if (!query.empty()) fullPath += "?" + query;
    upstreamReq->setPath(fullPath);
    upstreamReq->setPathEncode(false);
    upstreamReq->setBody(std::string(req->getBody()));

    const auto contentType = req->getHeader("Content-Type");
    if (!contentType.empty()) upstreamReq->setContentTypeString(contentType);
    if (!authHeader.empty()) upstreamReq->addHeader("Authorization", authHeader);
    if (hasApiKey) {
        upstreamReq->addHeader("ClientId", req->getHeader("ClientId"));
        upstreamReq->addHeader("ClientSecret", req->getHeader("ClientSecret"));
    }
    upstreamReq->addHeader(RequestContext::kTenantHeaderName, tenantId);
    upstreamReq->addHeader(RequestContext::kRequestIdHeaderName, requestId);
    // Never trust inbound TL-Context; always mint a fresh signed one.
    upstreamReq->addHeader(RequestContext::kHeaderName,
                           turbo::ContextCodec::encode(ctx, contextSecret_));

    drogon::HttpResponsePtr upstreamResp;
    try {
        upstreamResp =
            co_await clientFor(route->service)->sendRequestCoro(upstreamReq,
                                                                upstreamTimeoutSeconds_);
    } catch (const std::exception &e) {
        if (!idemStoreKey.empty()) idempotency_.abandon(idemStoreKey);
        LOG_ERROR << "Upstream " << route->service << " failed: " << e.what();
        auto resp = ApiResponse::httpError(drogon::k502BadGateway,
                                           "Upstream service unavailable: " + route->service,
                                           "error.msg.gateway.upstream.unavailable");
        decorate(req, resp, requestId);
        co_return resp;
    }

    if (!idemStoreKey.empty()) {
        idempotency_.complete(idemStoreKey,
                              StoredResponse{static_cast<int>(upstreamResp->statusCode()),
                                             std::string(upstreamResp->getHeader("Content-Type")),
                                             std::string(upstreamResp->getBody())});
    }

    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(upstreamResp->statusCode());
    resp->setBody(std::string(upstreamResp->getBody()));
    const auto upstreamCt = upstreamResp->getHeader("Content-Type");
    if (!upstreamCt.empty()) resp->addHeader("Content-Type", upstreamCt);
    decorate(req, resp, requestId);
    co_return resp;
}

drogon::Task<drogon::HttpResponsePtr> GatewayCore::healthFanOut() {
    Json::Value out;
    out["service"] = "ApiGateway";
    out["status"] = "UP";
    Json::Value upstream(Json::objectValue);

    for (const auto &[name, baseUrl] : services_) {
        Json::Value s;
        try {
            auto healthReq = drogon::HttpRequest::newHttpRequest();
            healthReq->setMethod(drogon::Get);
            healthReq->setPath("/health");
            auto resp = co_await clientFor(name)->sendRequestCoro(healthReq, 3.0);
            s["status"] = resp->statusCode() == drogon::k200OK ? "UP" : "DEGRADED";
            s["httpStatus"] = static_cast<int>(resp->statusCode());
        } catch (const std::exception &) {
            s["status"] = "DOWN";
        }
        s["baseUrl"] = baseUrl;
        upstream[name] = s;
        if (upstream[name]["status"] != "UP") out["status"] = "DEGRADED";
    }
    out["services"] = upstream;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(out);
    co_return resp;
}

drogon::HttpResponsePtr GatewayCore::describeRoutes() {
    Json::Value out(Json::arrayValue);
    for (const auto &r : routes_) {
        Json::Value j;
        j["prefix"] = r.prefix;
        j["service"] = r.service;
        j["public"] = r.isPublic;
        j["upstream"] = services_.count(r.service) ? services_.at(r.service) : "";
        out.append(j);
    }
    return drogon::HttpResponse::newHttpJsonResponse(out);
}

}  // namespace gateway
