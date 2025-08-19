#include "UserService.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include <iostream> // For placeholder logging
#include <jwt-cpp/jwt.h>
#include "Users.h"
#include "dto/BaseApiResponse.h"
#include "bcrypt.h"
#include "dto/ErrorCodes.h"
#include "dto/SigninDto.h"
#include "dto/UpdateUserDto.h"
// --- IMPORTANT ---
// This is a placeholder for a real password hashing library.

// --- IMPORTANT ---

namespace turbo_ledger_identity::dto {
    class SigninDto;
}

using namespace drogon::orm;
using namespace drogon_model::TurboLedgerIdentity;


namespace turbo_ledger_identity::services
{


    void UserService::getUsers(
    int pageNo,
    int pageSize,
    const std::string& query,
    const std::string& tenantId,
    const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        auto mp = std::make_shared<Mapper<Users>>(dbClient);

        // 1. Build the search criteria
        Criteria criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);
        if (!query.empty())
        {
            std::string likeQuery = "%" + query + "%";

            Criteria searchCriteria =
                Criteria(Users::Cols::_username, CompareOperator::Like, likeQuery) ||
                Criteria(Users::Cols::_first_name, CompareOperator::Like, likeQuery) ||
                Criteria(Users::Cols::_last_name, CompareOperator::Like, likeQuery) ||
                Criteria(Users::Cols::_email, CompareOperator::Like, likeQuery);

            criteria = criteria && searchCriteria;
        }

        // 2. Asynchronously get the total count matching the criteria
        mp->count(criteria, 
            [=](const size_t totalCount) {
                if (totalCount == 0)
                {
                    dto::BaseApiResponse response;
                    response.success = true;
                    response.result["data"] = Json::arrayValue;
                    response.result["totalCount"] = 0;
                    callback(response);
                    return;
                }

                // 3. Asynchronously find the paginated data
                int offset = (pageNo - 1) * pageSize;
                mp->limit(pageSize).offset(offset).findBy(criteria,
                    [=](const std::vector<Users>& users) {
                        // 4. Build the final response inside the callback
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.result["totalCount"] = (Json::UInt64)totalCount;
                        response.result["pageNo"] = pageNo;
                        response.result["pageSize"] = pageSize;
                        response.result["totalPages"] = (int)((totalCount + pageSize - 1) / pageSize);

                        Json::Value data = Json::arrayValue;
                        for (const auto& user : users)
                        {
                            Json::Value userJson = user.toJson();
                            userJson.removeMember("password_hash");

                            // Convert snake_case to camelCase
                            Json::Value camelCaseUser;
                            camelCaseUser["id"] = userJson["id"];
                            camelCaseUser["username"] = userJson["username"];
                            camelCaseUser["firstName"] = userJson["first_name"];
                            camelCaseUser["lastName"] = userJson["last_name"];
                            camelCaseUser["email"] = userJson["email"];
                            camelCaseUser["phoneNumber"] = userJson["phone_number"];
                            camelCaseUser["isActive"] = userJson["is_active"];
                            camelCaseUser["isLockedOut"] = userJson["is_locked_out"];
                            camelCaseUser["tenantIdentifier"] = userJson["tenant_identifier"];
                            camelCaseUser["createdAt"] = userJson["created_at"];
                            camelCaseUser["updatedAt"] = userJson["updated_at"];

                            data.append(camelCaseUser);
                        }
                        response.result["data"] = data;
                        callback(response);
                    },
                    [callback](const DrogonDbException& e) {
                        // Handle find error
                        dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.error["message"] = "Database error while fetching users.";
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [callback](const DrogonDbException& e) {
                // Handle count error
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = ERR_DB_QUERY;
                errorResponse.error["message"] = "Database error while fetching users.";
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
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
        newUser.setPasswordHash(bcrypt::generateHash(userData.getPassword()));
        newUser.setTenantIdentifier(tenantId);
        newUser.setEmail(userData.getEmail());
        newUser.setPhoneNumber(userData.getPhoneNumber());
        newUser.setIsLockedOut(false); // Default to not locked out
        newUser.setIsActive(true); // Default to active


        mp.insert(newUser, [callback](const drogon_model::TurboLedgerIdentity::Users& user) {
            // 5. Prepare success response
            turbo_ledger_identity::dto::BaseApiResponse successResponse;
            successResponse.success = true;
            successResponse.message = "User created successfully";
            successResponse.result["id"] = user.getValueOfId();

            callback(successResponse);

        }, [callback](const drogon::orm::DrogonDbException& e) {
            // 6. Handle database errors
            // C++
            turbo_ledger_identity::dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.message = "Database error while creating user";
            errorResponse.error["code"] = ERR_DB_QUERY;
            callback(errorResponse);

        });

    }


    void UserService::updateUser(
        const dto::UpdateUserDto& userData,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mp(dbClient);

        Criteria criteria = Criteria(Users::Cols::_id, CompareOperator::EQ, userData.getId()) &&
                            Criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        mp.findOne(criteria,
            [=](Users user) {
                if (!userData.getFirstName().empty()) user.setFirstName(userData.getFirstName());
                if (!userData.getLastName().empty()) user.setLastName(userData.getLastName());
                if (!userData.getEmail().empty()) user.setEmail(userData.getEmail());
                if (!userData.getPhoneNumber().empty()) user.setPhoneNumber(userData.getPhoneNumber());
                if (!userData.getPassword().empty()) user.setPasswordHash(bcrypt::generateHash(userData.getPassword()));
                user.setIsActive(userData.getIsActive());
                user.setIsLockedOut(userData.getIsLockedOut());


                Mapper<Users> updateMp(dbClient);
                // Save the changes to the database
                updateMp.update(user, [callback](const size_t count) {

                    // Successfully updated
                    turbo_ledger_identity::dto::BaseApiResponse response;
                    response.success = true;
                    response.message = "User updated successfully";
                    callback(response);
                },
                [=](const DrogonDbException& e) {
                    // Error during update
                    turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                    errorResponse.success = false;
                    errorResponse.message = "Failed to update user";
                    errorResponse.error["code"] = ERR_DB_QUERY;
                    errorResponse.error["detail"] = e.base().what();
                    callback(errorResponse);
                }
            );

            },
            [callback](const DrogonDbException& e) {
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "User not found";
                errorResponse.error["code"] = ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


    void UserService::activateUserAccount(
        const std::string& userId,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mp(dbClient);

        // Create criteria to find the user with specified ID in the tenant
        Criteria criteria = Criteria(Users::Cols::_id, CompareOperator::EQ, userId) &&
                            Criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        // Find the user first
        mp.findOne(criteria,
            [=](Users user) {
                // Set the user as active
                user.setIsActive(true);

                // Update the user in the database
                Mapper<Users> updateMp(dbClient);
                updateMp.update(user,
                    [callback](const size_t count) {
                        // Successfully updated
                        turbo_ledger_identity::dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "User account activated successfully";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error during update
                        turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.message = "Failed to activate user account";
                        errorResponse.error["code"] = ERR_DB_QUERY;
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [callback](const DrogonDbException& e) {
                // User not found
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "User not found";
                errorResponse.error["code"] = ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }

    void UserService::deactivateUserAccount(
        const std::string& userId,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mp(dbClient);

        // Create criteria to find the user with specified ID in the tenant
        Criteria criteria = Criteria(Users::Cols::_id, CompareOperator::EQ, userId) &&
                            Criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        // Find the user first
        mp.findOne(criteria,
            [=](Users user) {
                // Set the user as inactive
                user.setIsActive(false);

                // Update the user in the database
                Mapper<Users> updateMp(dbClient);
                updateMp.update(user,
                    [callback](const size_t count) {
                        // Successfully updated
                        turbo_ledger_identity::dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "User account deactivated successfully";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error during update
                        turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.message = "Failed to deactivate user account";
                        errorResponse.error["code"] = ERR_DB_QUERY;
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [callback](const DrogonDbException& e) {
                // User not found
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "User not found";
                errorResponse.error["code"] = ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


    void UserService::deleteUser(
        const std::string& userId,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mp(dbClient);

        // Create criteria to find the user with specified ID in the tenant
        Criteria criteria = Criteria(Users::Cols::_id, CompareOperator::EQ, userId) &&
                            Criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        // First verify the user exists
        mp.findOne(criteria,
            [=](const Users& user) {
                // User found, proceed with deletion
                Mapper<Users> deleteMp(dbClient);
                deleteMp.deleteBy(criteria,
                    [=](const size_t count) {
                        if (count > 0) {
                            // Successfully deleted
                            turbo_ledger_identity::dto::BaseApiResponse response;
                            response.success = true;
                            response.message = "User deleted successfully";
                            callback(response);
                        } else {
                            // No rows were deleted (shouldn't happen if we found the user)
                            turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                            errorResponse.success = false;
                            errorResponse.message = "Failed to delete user";
                            errorResponse.error["code"] = ERR_DB_QUERY;
                            callback(errorResponse);
                        }
                    },
                    [=](const DrogonDbException& e) {
                        // Error during deletion
                        turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.message = "Failed to delete user";
                        errorResponse.error["code"] = ERR_DB_QUERY;
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // User not found
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "User not found";
                errorResponse.error["code"] = ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


    void UserService::validateUserCredentials(
        const dto::SigninDto& signin_dto,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();

        Mapper<Users> mapper(dbClient);

        Criteria criteria = (Criteria(Users::Cols::_username, CompareOperator::EQ, signin_dto.getUsernameOrEmail()) ||
                                 Criteria(Users::Cols::_email, CompareOperator::EQ, signin_dto.getUsernameOrEmail())) &&
                                     Criteria(Users::Cols::_is_active, CompareOperator::EQ, true) &&
                                         Criteria(Users::Cols::_is_locked_out, CompareOperator::EQ, false) &&
                                             Criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);



        mapper.findOne(criteria,
        [=](const Users& user) {

            bool passwordMatches = bcrypt::validatePassword(signin_dto.getPassword(), user.getValueOfPasswordHash());

            if (passwordMatches) {
                // Password is correct, generate JWT token
                auto& app = drogon::app();
                auto customConfig = app.getCustomConfig();
                std::string jwtSecurityKey = customConfig["JwtBearer"]["JwtSecurityKey"].asString();
                std::string jwtIssuer = customConfig["JwtBearer"]["JwtIssuer"].asString();

                auto token = jwt::create()
                    .set_issuer(jwtIssuer)
                    .set_type("JWT")
                    .set_issued_at(std::chrono::system_clock::now())
                    .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(24))
                    .set_payload_claim("userId", jwt::claim(user.getValueOfId()))
                    .set_payload_claim("username", jwt::claim(user.getValueOfUsername()))
                    .set_payload_claim("email", jwt::claim(user.getValueOfEmail()))
                    .set_payload_claim("tenantId", jwt::claim(user.getValueOfTenantIdentifier()))
                    .sign(jwt::algorithm::hs256{jwtSecurityKey});

                turbo_ledger_identity::dto::BaseApiResponse response;
                response.success = true;
                response.message = "Authentication successful";
                response.result["token"] = token;
                response.result["userId"] = user.getValueOfId();
                response.result["username"] = user.getValueOfUsername();
                response.result["fullName"] = user.getValueOfFirstName() + " " + user.getValueOfLastName();
                response.result["email"] = user.getValueOfEmail();

                callback(response);
            } else {
                // Password is incorrect
                turbo_ledger_identity::dto::BaseApiResponse response;
                response.success = false;
                response.message = "Invalid credentials";
                response.error["code"] = ERR_AUTH_INVALID_CREDENTIALS;
                callback(response);
            }
        },
        [callback](const DrogonDbException& e) {
            // Database error or user not found
            turbo_ledger_identity::dto::BaseApiResponse response;
            response.success = false;
            response.message = "User not found";
            response.error["code"] = ERR_RESOURCE_NOT_FOUND;
            response.error["message"] = "User not found";
            callback(response);
        }
    );


    }


    void UserService::lockUserAccount(
        const std::string& userId,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mp(dbClient);

        // Create criteria to find the user with specified ID in the tenant
        Criteria criteria = Criteria(Users::Cols::_id, CompareOperator::EQ, userId) &&
                            Criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        // Find the user first
        mp.findOne(criteria,
            [=](Users user) {
                // Set the user as locked out
                user.setIsLockedOut(true);

                // Update the user in the database
                Mapper<Users> updateMp(dbClient);
                updateMp.update(user,
                    [callback](const size_t count) {
                        // Successfully updated
                        turbo_ledger_identity::dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "User account locked successfully";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error during update
                        turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.message = "Failed to lock user account";
                        errorResponse.error["code"] = ERR_DB_QUERY;
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [callback](const DrogonDbException& e) {
                // User not found
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "User not found";
                errorResponse.error["code"] = ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }



    void UserService::unlockUserAccount(
        const std::string& userId,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<Users> mp(dbClient);

        // Create criteria to find the user with specified ID in the tenant
        Criteria criteria = Criteria(Users::Cols::_id, CompareOperator::EQ, userId) &&
                            Criteria(Users::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        // Find the user first
        mp.findOne(criteria,
            [=](Users user) {
                // Set the user as not locked out
                user.setIsLockedOut(false);

                // Update the user in the database
                Mapper<Users> updateMp(dbClient);
                updateMp.update(user,
                    [callback](const size_t count) {
                        // Successfully updated
                        turbo_ledger_identity::dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "User account unlocked successfully";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error during update
                        turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.message = "Failed to unlock user account";
                        errorResponse.error["code"] = ERR_DB_QUERY;
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [callback](const DrogonDbException& e) {
                // User not found
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "User not found";
                errorResponse.error["code"] = ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


}
