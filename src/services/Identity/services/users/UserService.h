
#pragma once

#include <drogon/drogon.h>
#include "dto/BaseApiResponse.h"
#include "dto/CreateUserDto.h"


namespace turbo_ledger_identity::services
{
    class UserService
    {
    public:



        /**
         * @brief Create a new user in the database.
         * @param userData The DTO containing new user information.
         * @param tenantId The identifier for the tenant.
         * @param callback The callback function to handle the response.
         */
        void createUser(
            const dto::CreateUserDto& userData,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        /**
         * @brief Validate a user's credentials.
         *
         * @param username The user's username.
         * @param password The user's plaintext password.
         * @param tenantId The identifier for the tenant.
         * @param callback The callback function to handle the response.
         */
        void validateUserCredentials(
            const std::string& username,
            const std::string& password,
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
