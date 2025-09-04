#pragma once

#ifndef ROLESERVICE_H
#define ROLESERVICE_H

#include <drogon/drogon.h>
#include "dto/BaseApiResponse.h"
#include "dto/CreateRoleDto.h"

namespace turbo_ledger_identity::dto {
    class UpdateRoleDto;
}

namespace turbo_ledger_identity::services {

    class RoleService {

    public:

        void getRoles(
            int pageNo,
            int pageSize,
            const std::string& query,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void createRole(
            const dto::CreateRoleDto& roleData,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void updateRole(
            const dto::UpdateRoleDto& roleData,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void deleteRole(
            const std::string& roleId,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        // permissions

        void getAllPermissions(
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

    };


}


#endif //ROLESERVICE_H
