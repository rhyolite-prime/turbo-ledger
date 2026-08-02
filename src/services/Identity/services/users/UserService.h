
#pragma once

#include <drogon/drogon.h>
#include "dto/BaseApiResponse.h"
#include "dto/SigninDto.h"
#include "dto/UserDto.h"


namespace turbo_ledger_identity::services
{
    class UserService
    {
    public:


        drogon::Task<dto::BaseApiResponse> getAll(const std::string &businessId, int pageNo, int pageSize, const std::string &query);
        drogon::Task<dto::BaseApiResponse> getDetails(const std::string &businessId, const std::string &id);

        drogon::Task<dto::BaseApiResponse> create(const std::string &businessId, const dto::UserDto &dto);

        drogon::Task<dto::BaseApiResponse> update(const std::string &businessId, const dto::UserDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> lockUserAccount(const std::string &businessId, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> unlockUserAccount(const std::string &businessId, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> activateUserAccount(const std::string &businessId, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> deactivateUserAccount(const std::string &businessId, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> deleteUser(const std::string &businessId, const std::string &userId);

        drogon::Task<dto::BaseApiResponse> validateUserCredentials(const dto::SigninDto &dto);


    };
}
