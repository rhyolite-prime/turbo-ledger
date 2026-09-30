#include "TenantRegistry.h"

#include <trantor/utils/Logger.h>

namespace gateway {

void TenantRegistry::loadFromConfig(const Json::Value &tenantsConfig) {
    std::lock_guard<std::mutex> lock(mutex_);
    tenants_.clear();
    if (!tenantsConfig.isArray()) return;
    for (const auto &t : tenantsConfig) {
        TenantInfo info;
        info.id = t.get("id", "").asString();
        info.name = t.get("name", "").asString();
        info.status = t.get("status", "ACTIVE").asString();
        if (!info.id.empty()) tenants_[info.id] = info;
    }
    LOG_INFO << "TenantRegistry loaded " << tenants_.size() << " tenant(s) from config";
}

std::optional<TenantInfo> TenantRegistry::find(const std::string &tenantId) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = tenants_.find(tenantId);
    if (it == tenants_.end()) return std::nullopt;
    return it->second;
}

size_t TenantRegistry::size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return tenants_.size();
}

}  // namespace gateway
