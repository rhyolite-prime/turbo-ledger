#include "AuditScope.h"
#include "AuditLogService.h"

namespace turbo_ledger_identity::services
{
    AuditScope::AuditScope(
        const std::string& actorId,
        const std::string& businessId,
        const std::string& entityType,
        const std::string& entityId,
        const std::string& action,
        const std::string& ipAddress,
        const std::string& userAgent
    ) : actorId_(actorId),
        businessId_(businessId),
        entityType_(entityType),
        entityId_(entityId),
        action_(action),
        ipAddress_(ipAddress),
        userAgent_(userAgent)
    {
    }

    AuditScope::~AuditScope()
    {
        if (isCommitted_)
        {
            AuditLogService::logActivity(
                actorId_,
                businessId_,
                entityType_,
                entityId_,
                action_,
                oldValues_,
                newValues_,
                ipAddress_,
                userAgent_
            );
        }
    }

    void AuditScope::setOldValues(const Json::Value& oldValues)
    {
        oldValues_ = oldValues;
    }

    void AuditScope::setNewValues(const Json::Value& newValues)
    {
        newValues_ = newValues;
    }

    void AuditScope::setEntityId(const std::string& entityId)
    {
        entityId_ = entityId;
    }

    void AuditScope::commit()
    {
        isCommitted_ = true;
    }
}
