#pragma once

#ifndef ROLESERVICE_H
#define ROLESERVICE_H

#include <drogon/drogon.h>
#include "dto/BaseApiResponse.h"
#include "dto/RoleDto.h"


namespace turbo_ledger_identity::services {

    class RoleService {

    public:

        drogon::Task<dto::BaseApiResponse> getAll(const std::string &businessId, int pageNo, int pageSize, const std::string &query);

        drogon::Task<dto::BaseApiResponse> getAllPermissions();

        drogon::Task<dto::BaseApiResponse> create(const std::string &businessId, const dto::RoleDto &dto);

        drogon::Task<dto::BaseApiResponse> update(const std::string &businessId, const dto::RoleDto &dto, const std::string &roleId);

        drogon::Task<dto::BaseApiResponse> deleteRole(const std::string &businessId, const std::string &roleId);

    };


}


#endif //ROLESERVICE_H
