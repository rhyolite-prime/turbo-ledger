//
// Provisioner — tenant registry + per-service schema provisioning pipeline.
//
// The registry lives in TlProvisioner.public.tenants. Creating a tenant:
//   1. registers it (status PROVISIONING),
//   2. for every configured service database: creates schema t_<id>, applies
//      pending V###__*.sql migrations (tracked in t_<id>.tl_schema_history,
//      wire-compatible with src/tools/migrate.py),
//   3. seeds the tenant admin (Super user role) in the Identity database,
//   4. flips the tenant ACTIVE and returns the one-time admin credentials.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/TenantStatus.h"

namespace provisioner {

class ApiError : public std::runtime_error {
  public:
    ApiError(drogon::HttpStatusCode status, std::string message, std::string code = "")
        : std::runtime_error(std::move(message)), status_(status), code_(std::move(code)) {}
    drogon::HttpStatusCode status() const { return status_; }
    const std::string &globalisationCode() const { return code_; }

  private:
    drogon::HttpStatusCode status_;
    std::string code_;
};

struct ServiceTarget {
    std::string name;           ///< e.g. "Identity"
    std::string dbClient;       ///< drogon db client name
    std::string migrationsDir;  ///< path with V###__*.sql files
    bool seedAdmin{false};      ///< seed the tenant admin user here
};

class ProvisioningService {
  public:
    static ProvisioningService &instance();

    void initFromConfig();

    /// Create registry table if needed and upsert the configured static tenants.
    drogon::Task<void> ensureRegistry();

    drogon::Task<Json::Value> listTenants();
    drogon::Task<Json::Value> getTenant(const std::string &id);
    drogon::Task<Json::Value> createTenant(const Json::Value &body);
    drogon::Task<Json::Value> setStatus(const std::string &id, turbo::TenantStatus newStatus);
    Json::Value instanceMode() const;

    /// Split a migration file into single statements (quotes, dollar-quoting
    /// and comments aware) so they can run through the extended protocol.
    static std::vector<std::string> splitSqlStatements(const std::string &sql);

  private:
    drogon::Task<int> provisionServiceSchemas(const ServiceTarget &target,
                                              const std::string &tenantId);
    drogon::Task<void> seedTenantAdmin(const ServiceTarget &target, const std::string &tenantId,
                                       const std::string &username, const std::string &email,
                                       const std::string &passwordHash);

    std::vector<ServiceTarget> targets_;
    Json::Value staticTenants_{Json::arrayValue};
    Json::Value instanceMode_{Json::objectValue};
    bool registryReady_{false};
};

}  // namespace provisioner
