#pragma once

#include <drogon/drogon.h>
#include <string>
#include <json/json.h>

namespace turbo_ledger_identity::services
{
    class AuditLogService
    {
    public:
        /**
         * @brief Asynchronously logs an activity to the tenant-schema audit_logs
         *        table (t_<tenantId>.audit_logs — see V001__baseline.sql).
         *
         * @param tenantId The tenant whose schema the entry belongs in. Required
         *        and must be a valid tenant id (see turbo::RequestContext::isValidTenantId);
         *        invalid/empty ids are logged and dropped rather than silently
         *        mis-filed via an unscoped connection.
         * @param actorId The ID (UUID) of the user performing the action. Pass empty string for system actions.
         * @param entityType The type of entity being modified (e.g., "User", "Role").
         * @param entityId The ID (UUID) of the entity being modified.
         * @param action The action performed (e.g., "CREATE", "UPDATE", "DELETE").
         * @param oldValues JSON representation of the entity before the change.
         * @param newValues JSON representation of the entity after the change.
         * @param ipAddress The IP address of the client performing the action.
         * @param userAgent The User-Agent string of the client performing the action.
         */
        static void logActivity(
            const std::string& tenantId,
            const std::string& actorId,
            const std::string& entityType,
            const std::string& entityId,
            const std::string& action,
            const Json::Value& oldValues = Json::Value(),
            const Json::Value& newValues = Json::Value(),
            const std::string& ipAddress = "",
            const std::string& userAgent = ""
        );
    };
}
