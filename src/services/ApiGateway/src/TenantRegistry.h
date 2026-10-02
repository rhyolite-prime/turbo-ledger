//
// ApiGateway — tenant registry with cache.
//
// Phase 0: tenants come from config (custom_config.gateway.tenants).
// Phase 1: when custom_config.gateway.provisioner.base_url is set, the
// registry refreshes from the Provisioner (GET /api/v1/tenants/get-all,
// authenticated with a gateway-minted "system" TL-Context) on a TTL and
// merges the result over the static list. If the Provisioner is unreachable
// the last good snapshot (or the static list) keeps serving.
//
#pragma once

#include <drogon/HttpClient.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <chrono>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

#include "turbo/TenantStatus.h"

namespace gateway {

struct TenantInfo {
    std::string id;
    std::string name;
    turbo::TenantStatus status{turbo::TenantStatus::Pending};
    bool isActive() const { return turbo::isServing(status); }
    std::string statusLabel() const { return std::string(turbo::toString(status)); }
};

class TenantRegistry {
  public:
    void loadFromConfig(const Json::Value &tenantsConfig);

    /// Enable dynamic refresh from the Provisioner.
    void configureProvisioner(const std::string &baseUrl, double ttlSeconds,
                              const std::string &contextSecret);

    /// Resolve a tenant, refreshing from the Provisioner when the cache is stale.
    drogon::Task<std::optional<TenantInfo>> find(std::string tenantId);

    size_t size();

  private:
    drogon::Task<void> refreshIfStale();

    std::mutex mutex_;
    std::unordered_map<std::string, TenantInfo> staticTenants_;
    std::unordered_map<std::string, TenantInfo> dynamicTenants_;

    std::string provisionerBaseUrl_;
    std::string contextSecret_;
    double ttlSeconds_{5.0};
    std::chrono::steady_clock::time_point lastRefresh_{};
    bool refreshing_{false};
    drogon::HttpClientPtr client_;
};

}  // namespace gateway
