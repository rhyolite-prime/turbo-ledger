#pragma once

#ifndef ROLESERVICE_H
#define ROLESERVICE_H

#include <drogon/drogon.h>
#include "dto/BaseApiResponse.h"
#include "dto/RoleDto.h"
#include "dto/UserIdentityDto.h"


namespace turbo_ledger_identity::services {

    class RoleService {

    public:

        drogon::Task<dto::BaseApiResponse> getAll(const dto::UserIdentityDto &identity, int pageNo, int pageSize, const std::string &query);

        drogon::Task<dto::BaseApiResponse> getTenantPermissions();

        drogon::Task<dto::BaseApiResponse> getHostPermissions();

        drogon::Task<dto::BaseApiResponse> create(const dto::UserIdentityDto &identity, const dto::RoleDto &dto);

        drogon::Task<dto::BaseApiResponse> update(const dto::UserIdentityDto &identity, const dto::RoleDto &dto, const std::string &roleId);

        drogon::Task<dto::BaseApiResponse> deleteRole(const dto::UserIdentityDto &identity, const std::string &roleId);

    };


}


#endif //ROLESERVICE_H
