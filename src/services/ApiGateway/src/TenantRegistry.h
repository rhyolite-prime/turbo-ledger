//
// ApiGateway — tenant registry with cache.
//
// Phase 0: tenants come from config (custom_config.tenants). When the
// Provisioner service is live, set custom_config.provisioner.base_url and the
// registry refreshes from GET /api/v1/tenants/get-all on a TTL, falling back
// to the static list when unreachable.
//
#pragma once

#include <json/json.h>
#include <chrono>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

namespace gateway {

struct TenantInfo {
    std::string id;
    std::string name;
    std::string status;  // ACTIVE | SUSPENDED | CLOSED | PENDING
    bool isActive() const { return status == "ACTIVE"; }
};

class TenantRegistry {
  public:
    void loadFromConfig(const Json::Value &tenantsConfig);

    std::optional<TenantInfo> find(const std::string &tenantId);

    size_t size();

  private:
    std::mutex mutex_;
    std::unordered_map<std::string, TenantInfo> tenants_;
};

}  // namespace gateway
