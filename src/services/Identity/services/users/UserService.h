
#pragma once

#include <drogon/drogon.h>
#include <optional>
#include "dto/BaseApiResponse.h"
#include "dto/SigninDto.h"
#include "dto/UserDto.h"
#include "dto/UserIdentityDto.h"


namespace turbo_ledger_identity::services
{
    class UserService
    {
    public:


        drogon::Task<dto::BaseApiResponse> getAll(const dto::UserIdentityDto &identity, int pageNo, int pageSize, const std::string &query);
        drogon::Task<dto::BaseApiResponse> getDetails(const dto::UserIdentityDto &identity, const std::string &id);

        drogon::Task<dto::BaseApiResponse> create(const dto::UserIdentityDto &identity, const dto::UserDto &dto);

        drogon::Task<dto::BaseApiResponse> update(const dto::UserIdentityDto &identity, const dto::UserDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> lockUserAccount(const dto::UserIdentityDto &identity, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> unlockUserAccount(const dto::UserIdentityDto &identity, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> activateUserAccount(const dto::UserIdentityDto &identity, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> deactivateUserAccount(const dto::UserIdentityDto &identity, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> deleteUser(const dto::UserIdentityDto &identity, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> validateUserCredentials(const dto::SigninDto &dto);

        /// Phase 1: tenant-aware signin — tenant schema first, host fallback.
        drogon::Task<dto::BaseApiResponse> validateUserCredentials(const dto::SigninDto &dto,
                                                                   const std::string &tenantId);

    private:
        drogon::Task<std::optional<dto::BaseApiResponse>> tryTenantSignin(
            const dto::SigninDto &dto, const std::string &tenantId);


    };
}
