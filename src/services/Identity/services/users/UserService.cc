#include "UserService.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include "models/Users.h"
#include "models/BusinessAccounts.h"
#include "models/LoginHistory.h"
#include "constants/ErrorCodes.h"
#include "utils/PasswordUtils.h"
#include <bcrypt.h>
#include <jwt-cpp/jwt.h>
#include "services/audit_logs/AuditScope.h"

using namespace drogon::orm;

namespace turbo_ledger_identity::services
{

    drogon::Task<dto::BaseApiResponse> UserService::getAll(const dto::UserIdentityDto &identity, int pageNo, int pageSize, const std::string &query) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            Criteria criteria;
            if (!identity.business_id.empty()) {
                criteria = Criteria(drogon_model::TlIdentity::Users::Cols::_business_id, CompareOperator::EQ, identity.business_id);
            } else {
                criteria = Criteria(drogon_model::TlIdentity::Users::Cols::_business_id, CompareOperator::IsNull);
            }

            if (!query.empty()) {
                Criteria searchCriteria = Criteria(drogon_model::TlIdentity::Users::Cols::_first_name, CompareOperator::Like, "%" + query + "%") || 
                           Criteria(drogon_model::TlIdentity::Users::Cols::_last_name, CompareOperator::Like, "%" + query + "%") ||
                           Criteria(drogon_model::TlIdentity::Users::Cols::_email, CompareOperator::Like, "%" + query + "%") ||
                           Criteria(drogon_model::TlIdentity::Users::Cols::_username, CompareOperator::Like, "%" + query + "%");
                criteria = criteria && searchCriteria;
            }
            
            size_t totalCount = co_await mapper.count(criteria);

            if (totalCount == 0) {
                response.success = true;
                response.result["data"] = Json::arrayValue;
                response.result["totalCount"] = 0;
                response.result["pageNo"] = pageNo;
                response.result["pageSize"] = pageSize;
                response.result["totalPages"] = 0;
                response.result["lowerBound"] = 0;
                response.result["upperBound"] = 0;
                co_return response;
            }

            int offset = (pageNo - 1) * pageSize;
            auto users = co_await mapper.limit(pageSize).offset(offset).findBy(criteria);
            auto totalPages = (totalCount + pageSize - 1) / pageSize;

            response.success = true;
            response.result["totalCount"] = (Json::UInt64)totalCount;
            response.result["pageNo"] = pageNo;
            response.result["pageSize"] = pageSize;
            response.result["totalPages"] = (int)totalPages;
            response.result["lowerBound"] = pageSize * (pageNo - 1) + 1;
            response.result["upperBound"] = (int)totalPages == pageNo ? (Json::UInt64)totalCount  : (Json::UInt64)(pageNo * pageSize);

            Json::Value data = Json::arrayValue;
            for (const auto& user : users) {
                auto roleJson = user.toJson();
                Json::Value camelCaseRole;

                camelCaseRole["id"] = roleJson["id"];
                camelCaseRole["firstName"] = roleJson["first_name"];
                camelCaseRole["lastName"] = roleJson["last_name"];
                camelCaseRole["email"] = roleJson["email"];
                camelCaseRole["phoneNumber"] = roleJson["phone_number"];
                camelCaseRole["country"] = roleJson["country"];
                camelCaseRole["profileImageUrl"] = roleJson["profile_image_url"];
                camelCaseRole["isLockedOut"] = roleJson["is_locked_out"];
                camelCaseRole["isActive"] = roleJson["is_active"];
                camelCaseRole["createdAt"] = roleJson["created_at"];
                camelCaseRole["updatedAt"] = roleJson["updated_at"];
                data.append(camelCaseRole);
            }
            response.result["data"] = data;
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error retrieving users.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::getDetails(const dto::UserIdentityDto &identity, const std::string &id) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            auto users = co_await mapper.findBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, id));
            if (users.empty()) {
                response.success = false;
                response.error["message"] = "User not found.";
                co_return response;
            }
            response.success = true;
            auto json = users.front().toJson();
            json.removeMember("password_hash");
            response.result = json;
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error fetching user.";
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::create(const dto::UserIdentityDto &identity, const dto::UserDto &dto) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            drogon_model::TlIdentity::Users newUser;
            newUser.setFirstName(dto.getFirstName());
            newUser.setLastName(dto.getLastName());
            newUser.setEmail(dto.getEmail());
            newUser.setUsername(dto.getUsername());
            newUser.setPasswordHash(bcrypt::generateHash(dto.getPassword(),8));
            newUser.setPhoneNumber(dto.getPhoneNumber());
            newUser.setCountry(dto.getCountry());
            newUser.setIsActive(true);
            newUser.setIsLockedOut(false);
            
            services::AuditScope auditScope(identity.user_id, identity.business_id, "User", "", "CREATE");

            auto savedUser = co_await mapper.insert(newUser);
            auto json = savedUser.toJson();
            json.removeMember("password_hash");
            
            auditScope.setEntityId(json["id"].asString());
            auditScope.setNewValues(json);
            auditScope.commit();
            
            response.success = true;
            response.result = json;
        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.error["message"] = "Database error creating user.";
            response.error["detail"] = e.base().what();
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Unknown error creating user.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::update(const dto::UserIdentityDto &identity, const dto::UserDto &dto, const std::string &id) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            auto users = co_await mapper.findBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, id));
            if (users.empty()) {
                response.success = false;
                response.error["message"] = "User not found.";
                co_return response;
            }
            
            auto user = users.front();
            
            services::AuditScope auditScope(identity.user_id, identity.business_id, "User", user.toJson()["id"].asString(), "UPDATE");
            auto oldJson = user.toJson();
            oldJson.removeMember("password_hash");
            auditScope.setOldValues(oldJson);
            
            if (!dto.getFirstName().empty()) user.setFirstName(dto.getFirstName());
            if (!dto.getLastName().empty()) user.setLastName(dto.getLastName());
            if (!dto.getEmail().empty()) user.setEmail(dto.getEmail());
            if (!dto.getUsername().empty()) user.setUsername(dto.getUsername());
            if (!dto.getPhoneNumber().empty()) user.setPhoneNumber(dto.getPhoneNumber());
            if (!dto.getCountry().empty()) user.setCountry(dto.getCountry());
            
            auto updatedCount = co_await mapper.update(user);
            auto json = user.toJson();
            json.removeMember("password_hash");
            
            response.success = updatedCount > 0;
            if (response.success) {
                auditScope.setNewValues(json);
                auditScope.commit();
                response.result = json;
            }
            else {
                response.error["message"] = "Failed to update user.";
            }
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error updating user.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::lockUserAccount(const dto::UserIdentityDto &identity, const std::string &userId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            auto users = co_await mapper.findBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, userId));
            if (users.empty()) {
                response.success = false;
                response.error["message"] = "User not found.";
                co_return response;
            }
            
            auto user = users.front();
            
            services::AuditScope auditScope(identity.user_id, identity.business_id, "User", user.toJson()["id"].asString(), "LOCK");
            auto oldJson = user.toJson();
            oldJson.removeMember("password_hash");
            auditScope.setOldValues(oldJson);
            
            user.setIsLockedOut(true);
            co_await mapper.update(user);
            
            auto newJson = user.toJson();
            newJson.removeMember("password_hash");
            auditScope.setNewValues(newJson);
            auditScope.commit();
            
            response.success = true;
            response.message = "User account locked.";
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error locking user account.";
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::unlockUserAccount(const dto::UserIdentityDto &identity, const std::string &userId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            auto users = co_await mapper.findBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, userId));
            if (users.empty()) {
                response.success = false;
                response.error["message"] = "User not found.";
                co_return response;
            }
            
            auto user = users.front();

            services::AuditScope auditScope(identity.user_id, identity.business_id, "User", user.toJson()["id"].asString(), "UNLOCK");
            auto oldJson = user.toJson();
            oldJson.removeMember("password_hash");
            auditScope.setOldValues(oldJson);

            user.setIsLockedOut(false);
            co_await mapper.update(user);
            
            auto newJson = user.toJson();
            newJson.removeMember("password_hash");
            auditScope.setNewValues(newJson);
            auditScope.commit();
            
            response.success = true;
            response.message = "User account unlocked.";
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error unlocking user account.";
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::activateUserAccount(const dto::UserIdentityDto &identity, const std::string &userId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            auto users = co_await mapper.findBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, userId));
            if (users.empty()) {
                response.success = false;
                response.error["message"] = "User not found.";
                co_return response;
            }
            
            auto user = users.front();

            services::AuditScope auditScope(identity.user_id, identity.business_id, "User", user.toJson()["id"].asString(), "ACTIVATE");
            auto oldJson = user.toJson();
            oldJson.removeMember("password_hash");
            auditScope.setOldValues(oldJson);

            user.setIsActive(true);
            co_await mapper.update(user);
            
            auto newJson = user.toJson();
            newJson.removeMember("password_hash");
            auditScope.setNewValues(newJson);
            auditScope.commit();
            
            response.success = true;
            response.message = "User account activated.";
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error activating user account.";
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::deactivateUserAccount(const dto::UserIdentityDto &identity, const std::string &userId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            auto users = co_await mapper.findBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, userId));
            if (users.empty()) {
                response.success = false;
                response.error["message"] = "User not found.";
                co_return response;
            }
            
            auto user = users.front();

            services::AuditScope auditScope(identity.user_id, identity.business_id, "User", user.toJson()["id"].asString(), "DEACTIVATE");
            auto oldJson = user.toJson();
            oldJson.removeMember("password_hash");
            auditScope.setOldValues(oldJson);

            user.setIsActive(false);
            co_await mapper.update(user);

            auto newJson = user.toJson();
            newJson.removeMember("password_hash");
            auditScope.setNewValues(newJson);
            auditScope.commit();
            
            response.success = true;
            response.message = "User account deactivated.";
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error deactivating user account.";
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::deleteUser(const dto::UserIdentityDto &identity, const std::string &userId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
            
            auto users = co_await mapper.findBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, userId));
            if (users.empty()) {
                response.success = false;
                response.error["message"] = "User not found.";
                co_return response;
            }

            auto user = users.front();
            services::AuditScope auditScope(identity.user_id, identity.business_id, "User", userId, "DELETE");
            auto oldJson = user.toJson();
            oldJson.removeMember("password_hash");
            auditScope.setOldValues(oldJson);

            auto deletedCount = co_await mapper.deleteBy(Criteria(drogon_model::TlIdentity::Users::Cols::_id, CompareOperator::EQ, userId));
            if (deletedCount > 0) {
                auditScope.commit();
                response.success = true;
                response.message = "User deleted successfully.";
            } else {
                response.success = false;
                response.error["message"] = "User not found.";
            }
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error deleting user.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> UserService::validateUserCredentials(const dto::SigninDto &signin_dto) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);
        
        std::string targetBusinessId = "";
        std::string targetUserId = "";
        std::string loginStatus = "";
        std::string loginFailureReason = "";

        Criteria criteria =
            (Criteria(drogon_model::TlIdentity::Users::Cols::_username, CompareOperator::EQ, signin_dto.getUsernameOrEmail()) || 
             Criteria(drogon_model::TlIdentity::Users::Cols::_phone_number, CompareOperator::EQ, signin_dto.getUsernameOrEmail()) ||
             Criteria(drogon_model::TlIdentity::Users::Cols::_email, CompareOperator::EQ, signin_dto.getUsernameOrEmail())) &&
            Criteria(drogon_model::TlIdentity::Users::Cols::_is_active, CompareOperator::EQ, true) &&
            Criteria(drogon_model::TlIdentity::Users::Cols::_is_locked_out, CompareOperator::EQ, false);

        if (signin_dto.getAccountId().empty()) {
            // Host signin: business_id should be null
            criteria = criteria && Criteria(drogon_model::TlIdentity::Users::Cols::_business_id, CompareOperator::IsNull);
        }
        else {
            // Tenant signin: lookup business account by account_id
            CoroMapper<drogon_model::TlIdentity::BusinessAccounts> businessMapper(dbClient);
            auto businessAccounts = co_await businessMapper.findBy(Criteria(drogon_model::TlIdentity::BusinessAccounts::Cols::_account_id, CompareOperator::EQ, signin_dto.getAccountId()));
            
            if (businessAccounts.empty()) {
                dto::BaseApiResponse response;
                response.success = false;
                response.message = "Invalid credentials";
                response.error["code"] = constants::ERR_AUTH_INVALID_CREDENTIALS;
                response.error["message"] = "Invalid account ID";
                
                // Record login history
                drogon_model::TlIdentity::LoginHistory history;
                history.setStatus("FAILED");
                history.setFailureReason("Invalid account ID");
                history.setLoginTime(trantor::Date::now());
                try {
                    CoroMapper<drogon_model::TlIdentity::LoginHistory> historyMapper(dbClient);
                    co_await historyMapper.insert(history);
                } catch (...) {}
                
                co_return response;
            }
            
            targetBusinessId = businessAccounts.front().getValueOfId();
            criteria = criteria && Criteria(drogon_model::TlIdentity::Users::Cols::_business_id, CompareOperator::EQ, targetBusinessId);
        }

        dto::BaseApiResponse response;

        try {
            drogon_model::TlIdentity::Users user = co_await mapper.findOne(criteria);
            
            targetUserId = user.getValueOfId();
            if (targetBusinessId.empty() && user.getBusinessId()) {
                targetBusinessId = user.getValueOfBusinessId();
            }

            std::string storedHash = utils::PasswordUtils::normalizeBcryptHash(user.getValueOfPasswordHash());
            bool passwordMatches = bcrypt::validatePassword(signin_dto.getPassword(), storedHash);

            if (passwordMatches) {
                loginStatus = "SUCCESS";
            
                drogon_model::TlIdentity::Users userToUpdate = user;
                userToUpdate.setLastActive(trantor::Date::now());
                co_await mapper.update(userToUpdate);

                // Password is correct, generate JWT token
                auto &app = drogon::app();
                auto customConfig = app.getCustomConfig();
                std::string jwtSecurityKey = customConfig["JwtBearer"]["JwtSecurityKey"].asString();
                std::string jwtIssuer = customConfig["JwtBearer"]["JwtIssuer"].asString();

                auto token = jwt::create()
                        .set_issuer(jwtIssuer)
                        .set_type("JWT")
                        .set_issued_at(std::chrono::system_clock::now())
                        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(24 * 120))
                        .set_payload_claim("businessId", jwt::claim(user.getValueOfBusinessId()))
                        .set_payload_claim("userId", jwt::claim(user.getValueOfId()))
                        .set_payload_claim("username", jwt::claim(user.getValueOfUsername()))
                        .set_payload_claim("email", jwt::claim(user.getValueOfEmail()))
                        .sign(jwt::algorithm::hs256{jwtSecurityKey});

                response.success = true;
                response.message = "Authentication successful";
                response.result["token"] = token;
                response.result["userId"] = user.getValueOfId();
                response.result["username"] = user.getValueOfUsername();
                response.result["fullName"] = user.getValueOfFirstName() + " " + user.getValueOfLastName();
                response.result["email"] = user.getValueOfEmail();
            } else {
                loginStatus = "FAILED";
                loginFailureReason = "Invalid password";
                
                response.success = false;
                response.message = "Invalid credentials";
                response.error["code"] = constants::ERR_AUTH_INVALID_CREDENTIALS;
            }
        } catch (const DrogonDbException &e) {
            loginStatus = "FAILED";
            loginFailureReason = "User not found";
            
            response.success = false;
            response.message = "User not found";
            response.error["code"] = constants::ERR_RESOURCE_NOT_FOUND;
            response.error["message"] = "User not found";
        }
        
        // Log LoginHistory
        try {
            drogon_model::TlIdentity::LoginHistory history;
            if (!targetBusinessId.empty()) {
                history.setBusinessId(targetBusinessId);
            }
            if (!targetUserId.empty()) {
                history.setUserId(targetUserId);
            }
            history.setStatus(loginStatus);
            if (!loginFailureReason.empty()) {
                history.setFailureReason(loginFailureReason);
            }
            history.setLoginTime(trantor::Date::now());
            
            CoroMapper<drogon_model::TlIdentity::LoginHistory> historyMapper(dbClient);
            co_await historyMapper.insert(history);
        } catch (...) {
            // Ignore history insertion errors to not fail the login request
        }
        
        co_return response;
    }

}
