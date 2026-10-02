#include "AuditLogService.h"

#include <drogon/drogon.h>

#include "turbo/RequestContext.h"
#include "turbo/TenantDb.h"

namespace turbo_ledger_identity::services
{
    void AuditLogService::logActivity(
        const std::string& tenantId,
        const std::string& actorId,
        const std::string& entityType,
        const std::string& entityId,
        const std::string& action,
        const Json::Value& oldValues,
        const Json::Value& newValues,
        const std::string& ipAddress,
        const std::string& userAgent
    ) {
        if (!turbo::RequestContext::isValidTenantId(tenantId)) {
            LOG_ERROR << "Dropping audit log for " << action << " on " << entityType
                      << ": invalid/missing tenant id";
            return;
        }

        // Convert JSON to string, handling null/empty cases gracefully
        std::string oldValuesStr = oldValues.isNull() ? "{}" : oldValues.toStyledString();
        std::string newValuesStr = newValues.isNull() ? "{}" : newValues.toStyledString();

        // Fire-and-forget: this is called from AuditScope's destructor, which
        // cannot co_await, so the actual insert runs on a detached coroutine
        // against the tenant schema (t_<tenantId>.audit_logs).
        drogon::async_run(
            [tenantId, actorId, entityType, entityId, action, oldValuesStr,
             newValuesStr, ipAddress, userAgent]() -> drogon::Task<> {
                try {
                    auto txn = co_await turbo::db::beginTenantTxn(drogon::app().getDbClient(), tenantId);
                    co_await txn->execSqlCoro(
                        "INSERT INTO audit_logs ("
                        "  actor_id, entity_type, entity_id, action, "
                        "  old_values, new_values, ip_address, user_agent"
                        ") VALUES ("
                        "  NULLIF($1, '')::uuid, "
                        "  $2, "
                        "  NULLIF($3, '')::uuid, "
                        "  $4, "
                        "  $5::jsonb, "
                        "  $6::jsonb, "
                        "  NULLIF($7, '')::inet, "
                        "  $8"
                        ")",
                        actorId, entityType, entityId, action, oldValuesStr, newValuesStr, ipAddress,
                        userAgent);
                    LOG_TRACE << "Audit log created for " << action << " on " << entityType;
                } catch (const std::exception &e) {
                    LOG_ERROR << "Failed to create audit log for " << action << " on " << entityType << ": "
                              << e.what();
                }
            });
    }
}
