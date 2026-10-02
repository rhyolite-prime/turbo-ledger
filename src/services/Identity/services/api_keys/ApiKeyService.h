//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//
// Phase 9 cleanup: API keys are a per-tenant resource (the `api_keys` table
// lives inside t_<tenantId>, exactly like every other Identity table — see
// V001__baseline.sql). This service used to query it through a raw,
// unscoped DbClient filtered by a `business_id` column, which never matched
// anything once the schema-per-tenant model landed (the column only ever
// existed inside a tenant schema that the raw client never selected). It
// now goes through turbo::db::beginTenantTxn like every other service.
//

#ifndef IDENTITY_APIKEYSERVICE_H
#define IDENTITY_APIKEYSERVICE_H

#include <drogon/drogon.h>
#include <stdexcept>
#include <string>

#include "dto/ApiKeyDto.h"
#include "turbo/RequestContext.h"

namespace turbo_ledger_identity::services {

/// Error carrying an HTTP status + envelope globalisation code (mirrors
/// turbo_ledger_identity::rbac::ApiError / provisioner::ApiError).
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

struct ApiCredentialsValidationResult {
    bool isValid = false;
    std::string tenantId;
    std::string errorMessage;
    int errorCode = 0;
};

class ApiKeyService {
  public:
    drogon::Task<Json::Value> listApiKeys(const turbo::RequestContext &ctx, int pageNo, int pageSize,
                                          const std::string &query);

    /// Generates an API key inside the caller's tenant schema.
    drogon::Task<Json::Value> createApiKey(const turbo::RequestContext &ctx, const dto::ApiKeyDto &dto);

    drogon::Task<Json::Value> revokeApiKey(const turbo::RequestContext &ctx, const std::string &id);

    drogon::Task<Json::Value> activateApiKey(const turbo::RequestContext &ctx, const std::string &id);

    drogon::Task<void> deleteApiKey(const turbo::RequestContext &ctx, const std::string &id);

    /// Machine-to-machine credential check. Unlike the rest of this service,
    /// there is no signed/trusted context yet at this point (this endpoint
    /// IS how a caller gets one) — the caller must supply the tenant id
    /// explicitly (e.g. from TL-Tenant-Id), since api_keys lives inside that
    /// tenant's own schema and there is no cross-tenant key lookup anymore.
    drogon::Task<ApiCredentialsValidationResult> validateApiCredentials(const std::string &tenantId,
                                                                        const std::string &clientId,
                                                                        const std::string &clientSecret);

  private:
    static drogon::orm::DbClientPtr db();
};

}  // namespace turbo_ledger_identity::services

#endif  // IDENTITY_APIKEYSERVICE_H
