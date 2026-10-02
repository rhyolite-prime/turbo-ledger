#pragma once

#include <string>
#include <json/json.h>

namespace turbo_ledger_identity::services
{
    /**
     * @brief An RAII wrapper for safely managing and dispatching audit logs.
     * 
     * Instantiate this at the beginning of your service methods. 
     * Once all database operations succeed, call `commit()`.
     * The audit log will be fired asynchronously when this object is destroyed (if committed).
     */
    class AuditScope
    {
    public:
        AuditScope(
            const std::string& actorId,
            const std::string& tenantId,
            const std::string& entityType,
            const std::string& entityId,
            const std::string& action,
            const std::string& ipAddress = "",
            const std::string& userAgent = ""
        );

        ~AuditScope();

        // Prevent copying
        AuditScope(const AuditScope&) = delete;
        AuditScope& operator=(const AuditScope&) = delete;

        // Allow moving
        AuditScope(AuditScope&&) noexcept = default;
        AuditScope& operator=(AuditScope&&) noexcept = default;

        /**
         * @brief Sets the JSON state of the entity BEFORE the operation.
         */
        void setOldValues(const Json::Value& oldValues);

        /**
         * @brief Sets the JSON state of the entity AFTER the operation.
         */
        void setNewValues(const Json::Value& newValues);

        /**
         * @brief Updates the entity ID (useful for CREATE actions where the ID isn't known initially).
         */
        void setEntityId(const std::string& entityId);

        /**
         * @brief Marks the audit log to be successfully dispatched upon destruction.
         */
        void commit();

    private:
        std::string actorId_;
        std::string tenantId_;
        std::string entityType_;
        std::string entityId_;
        std::string action_;
        std::string ipAddress_;
        std::string userAgent_;

        Json::Value oldValues_;
        Json::Value newValues_;

        bool isCommitted_ = false;
    };
}
