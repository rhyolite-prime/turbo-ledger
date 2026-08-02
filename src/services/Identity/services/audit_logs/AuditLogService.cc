#include "AuditLogService.h"

namespace turbo_ledger_identity::services
{
    void AuditLogService::logActivity(
        const std::string& actorId,
        const std::string& businessId,
        const std::string& entityType,
        const std::string& entityId,
        const std::string& action,
        const Json::Value& oldValues,
        const Json::Value& newValues,
        const std::string& ipAddress,
        const std::string& userAgent
    ) {
        auto dbClient = drogon::app().getDbClient();
        
        // Convert JSON to string, handling null/empty cases gracefully
        std::string oldValuesStr = oldValues.isNull() ? "{}" : oldValues.toStyledString();
        std::string newValuesStr = newValues.isNull() ? "{}" : newValues.toStyledString();

        // Using NULLIF($X, '') to safely handle empty strings by converting them to SQL NULLs
        std::string sql = R"(
            INSERT INTO audit_logs (
                actor_id, business_id, entity_type, entity_id, action, 
                old_values, new_values, ip_address, user_agent
            ) VALUES (
                NULLIF($1, '')::uuid, 
                NULLIF($2, '')::uuid,
                $3, 
                NULLIF($4, '')::uuid, 
                $5, 
                $6::jsonb, 
                $7::jsonb, 
                NULLIF($8, '')::inet, 
                $9
            )
        )";

        dbClient->execSqlAsync(
            sql,
            [entityType, action](const drogon::orm::Result& result) {
                LOG_TRACE << "Audit log created for " << action << " on " << entityType;
            },
            [entityType, action](const drogon::orm::DrogonDbException& e) {
                LOG_ERROR << "Failed to create audit log for " << action << " on " << entityType << ": " << e.base().what();
            },
            actorId,
            businessId,
            entityType,
            entityId,
            action,
            oldValuesStr,
            newValuesStr,
            ipAddress,
            userAgent
        );
    }
}
