
#pragma once

#include <drogon/drogon.h>
#include "dto/BaseApiResponse.h"
#include "dto/CreateUserDto.h"


namespace turbo_ledger_identity::dto {
    class UpdateUserDto;
    class SigninDto;
}

namespace turbo_ledger_identity::services
{
    class UserService
    {
    public:

        /**
         * @brief Retrieve a paginated list of users with optional filtering.
         * @param pageNo The page number (0-based).
         * @param pageSize The number of users per page.
         * @param query Optional search query to filter users.
         * @param tenantId The identifier for the tenant.
         * @param callback The callback function to handle the response.
         */
        void getUsers(
            int pageNo,
            int pageSize,
            const std::string& query,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );


        /**
         * @param userData The DTO containing new user information.
         * @param tenantId The identifier for the tenant.
         * @param callback The callback function to handle the response.
         */
        void createUser(
            const dto::CreateUserDto& userData,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void updateUser(
            const dto::UpdateUserDto& userData,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void lockUserAccount(
            const std::string& userId,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );


        void unlockUserAccount(
            const std::string& userId,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );


        void activateUserAccount(
            const std::string& userId,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void deactivateUserAccount(
            const std::string& userId,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void deleteUser(
            const std::string& userId,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );



        /**
         * @brief Validate a user's credentials.
         *
         * @param signin_dto The user's plaintext password.
         * @param tenantId The identifier for the tenant.
         * @param callback The callback function to handle the response.
         */
        void validateUserCredentials(
            const dto::SigninDto& signin_dto,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );




    private:
        /**
         * @brief Hashes a plaintext password.
         * @note This is a placeholder. Use a strong, slow hashing algorithm like bcrypt or Argon2.
         */
        std::string hashPassword(const std::string& password);

        /**
         * @brief Verifies a plaintext password against a stored hash.
         * @note This is a placeholder. Use a library function that corresponds to your hashPassword method.
         */
        bool verifyPassword(const std::string& password, const std::string& hash);
    };
}
