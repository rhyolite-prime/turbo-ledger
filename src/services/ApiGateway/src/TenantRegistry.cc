#include "TenantRegistry.h"

#include <trantor/utils/Logger.h>
#include <chrono>

#include "turbo/ContextCodec.h"
#include "turbo/RequestContext.h"

namespace gateway {

void TenantRegistry::loadFromConfig(const Json::Value &tenantsConfig) {
    std::lock_guard<std::mutex> lock(mutex_);
    staticTenants_.clear();
    if (!tenantsConfig.isArray()) return;
    for (const auto &t : tenantsConfig) {
        TenantInfo info;
        info.id = t.get("id", "").asString();
        info.name = t.get("name", "").asString();
        info.status = t.get("status", "ACTIVE").asString();
        if (!info.id.empty()) staticTenants_[info.id] = info;
    }
    LOG_INFO << "TenantRegistry loaded " << staticTenants_.size() << " tenant(s) from config";
}

void TenantRegistry::configureProvisioner(const std::string &baseUrl, double ttlSeconds,
                                          const std::string &contextSecret) {
    std::lock_guard<std::mutex> lock(mutex_);
    provisionerBaseUrl_ = baseUrl;
    ttlSeconds_ = ttlSeconds > 0 ? ttlSeconds : 5.0;
    contextSecret_ = contextSecret;
    if (!baseUrl.empty())
        LOG_INFO << "TenantRegistry: dynamic refresh from " << baseUrl << " (ttl "
                 << ttlSeconds_ << "s)";
}

drogon::Task<void> TenantRegistry::refreshIfStale() {
    std::string baseUrl;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (provisionerBaseUrl_.empty() || refreshing_) co_return;
        const auto now = std::chrono::steady_clock::now();
        const auto age =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRefresh_).count();
        if (lastRefresh_.time_since_epoch().count() != 0 && age < ttlSeconds_ * 1000.0) co_return;
        refreshing_ = true;
        baseUrl = provisionerBaseUrl_;
        if (!client_) client_ = drogon::HttpClient::newHttpClient(baseUrl);
    }

    try {
        // Mint a short-lived system context so the Provisioner trusts the call.
        turbo::RequestContext ctx;
        ctx.tenantId = "default";
        ctx.authScheme = "system";
        ctx.username = "api-gateway";
        const auto now = std::chrono::duration_cast<std::chrono::seconds>(
                             std::chrono::system_clock::now().time_since_epoch())
                             .count();
        ctx.issuedAtEpoch = now;
        ctx.expiresAtEpoch = now + 60;

        auto req = drogon::HttpRequest::newHttpRequest();
        req->setMethod(drogon::Get);
        req->setPath("/api/v1/tenants/get-all");
        req->addHeader(turbo::RequestContext::kHeaderName,
                       turbo::ContextCodec::encode(ctx, contextSecret_));

        auto resp = co_await client_->sendRequestCoro(req, 3.0);
        if (resp->statusCode() == drogon::k200OK) {
            auto json = resp->getJsonObject();
            if (json && (*json)["result"]["tenants"].isArray()) {
                std::unordered_map<std::string, TenantInfo> fresh;
                for (const auto &t : (*json)["result"]["tenants"]) {
                    TenantInfo info;
                    info.id = t.get("id", "").asString();
                    info.name = t.get("name", "").asString();
                    info.status = t.get("status", "ACTIVE").asString();
                    if (!info.id.empty()) fresh[info.id] = info;
                }
                std::lock_guard<std::mutex> lock(mutex_);
                dynamicTenants_ = std::move(fresh);
            }
        } else {
            LOG_WARN << "TenantRegistry refresh got HTTP " << resp->statusCode();
        }
    } catch (const std::exception &e) {
        LOG_WARN << "TenantRegistry refresh failed (serving cached list): " << e.what();
    }

    std::lock_guard<std::mutex> lock(mutex_);
    lastRefresh_ = std::chrono::steady_clock::now();
    refreshing_ = false;
    co_return;
}

drogon::Task<std::optional<TenantInfo>> TenantRegistry::find(std::string tenantId) {
    co_await refreshIfStale();
    std::lock_guard<std::mutex> lock(mutex_);
    // dynamic view wins; static config is the bootstrap/fallback layer
    if (auto it = dynamicTenants_.find(tenantId); it != dynamicTenants_.end())
        co_return it->second;
    if (auto it = staticTenants_.find(tenantId); it != staticTenants_.end())
        co_return it->second;
    co_return std::nullopt;
}

size_t TenantRegistry::size() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::unordered_map<std::string, TenantInfo> merged = staticTenants_;
    for (const auto &[id, t] : dynamicTenants_) merged[id] = t;
    return merged.size();
}

}  // namespace gateway
