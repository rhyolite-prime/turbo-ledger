
#include "UserService.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include <iostream> // For placeholder logging

#include "Users.h"
#include "dto/BaseApiResponse.h"

// --- IMPORTANT --- 
// This is a placeholder for a real password hashing library.
// #include <bcrypt.h> 
// --- IMPORTANT --- 

using namespace drogon::orm;
using namespace drogon_model::TurboLedgerIdentity;


namespace turbo_ledger_identity::services
{


    // Placeholder password hashing - REPLACE WITH A REAL LIBRARY
    std::string UserService::hashPassword(const std::string& password)
    {
        // In a real app, you would use something like:
        // char salt[BCRYPT_HASHSIZE];
        // char hash[BCRYPT_HASHSIZE];
        // bcrypt_gensalt(12, salt);
        // bcrypt_hashpw(password.c_str(), salt, hash);
        // return std::string(hash);
        std::cout << "WARNING: Using placeholder password hashing." << std::endl;
        return "hashed_" + password;
    }

    // Placeholder password verification - REPLACE WITH A REAL LIBRARY
    bool UserService::verifyPassword(const std::string& password, const std::string& hash)
    {
        // In a real app, you would use:
        // return bcrypt_checkpw(password.c_str(), hash.c_str()) == 0;
        std::cout << "WARNING: Using placeholder password verification." << std::endl;
        return "hashed_" + password == hash;
    }

    void UserService::createUser(
        const dto::CreateUserDto& userData,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mp(dbClient);

        Users newUser;

        newUser.setFirstName(userData.getFirstName());
        newUser.setLastName(userData.getLastName());
        newUser.setUsername(userData.getUsername());
        newUser.setPasswordHash(hashPassword(userData.getPassword()));
        newUser.setTenantIdentifier(tenantId);
        newUser.setEmail(userData.getEmail());
        newUser.setPhoneNumber(userData.getPhoneNumber());
        newUser.setIsLockedOut(false); // Default to not locked out
        newUser.setIsActive(true); // Default to active


        mp.insert(newUser, [callback](const drogon_model::TurboLedgerIdentity::Users& user) {
            // 5. Prepare success response
            turbo_ledger_identity::dto::BaseApiResponse successResponse;
            successResponse.success = true;
            successResponse.result["message"] = "User created successfully";
            successResponse.result["id"] = user.getValueOfId();

            callback(successResponse);

        }, [callback](const drogon::orm::DrogonDbException& e) {
            // 6. Handle database errors
            turbo_ledger_identity::dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error = "Database error: " + std::string(e.base().what());

            callback(errorResponse);

        });

    }

    void UserService::validateUserCredentials(
        const std::string& username,
        const std::string& password,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mapper(dbClient);

        //return BaseApiResponse as default success
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = true;
        response.result["message"] = "User credentials validated successfully";
        response.result["username"] = username;
        response.result["tenantId"] = tenantId;
        response.result["status"] = "active";
        response.result["createdAt"] = trantor::Date::now().toDbString();
        response.result["updatedAt"] = trantor::Date::now().toDbString();

        callback(response);

    }
}
