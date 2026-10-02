#include "UserService.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include "models/Users.h"
#include "models/LoginHistory.h"
#include "constants/ErrorCodes.h"
#include "utils/PasswordUtils.h"
#include <bcrypt.h>
#include <jwt-cpp/jwt.h>
#include "turbo/TenantDb.h"

using namespace drogon::orm;

namespace turbo_ledger_identity::services
{

    drogon::Task<dto::BaseApiResponse> UserService::validateUserCredentials(const dto::SigninDto &signin_dto) {
        co_return co_await validateUserCredentials(signin_dto, "");
    }

    // Phase 1: tenant-scoped signin. Looks the user up in the tenant schema
    // (t_<tenantId>.users) first; a miss falls back to the legacy host lookup
    // in public.users so platform operators can sign in under any tenant.
    drogon::Task<std::optional<dto::BaseApiResponse>> UserService::tryTenantSignin(
        const dto::SigninDto &signin_dto, const std::string &tenantId) {
        auto dbClient = drogon::app().getDbClient();
        try {
            auto txn = co_await turbo::db::beginTenantTxn(dbClient, tenantId);
            auto rows = co_await txn->execSqlCoro(
                "SELECT id::text AS id, username, email, first_name, last_name, "
                "  password_hash, is_active, is_locked_out "
                "FROM users WHERE username = $1 OR email = $1",
                signin_dto.getUsernameOrEmail());
            if (rows.size() == 0) co_return std::nullopt;  // fall back to host lookup

            const auto &u = rows[0];
            dto::BaseApiResponse response;
            std::string status = "FAILED";
            std::string failureReason;

            if (!u["is_active"].as<bool>() || u["is_locked_out"].as<bool>()) {
                failureReason = "User inactive or locked";
                response.success = false;
                response.message = "User account is inactive or locked";
                response.error["code"] = constants::ERR_AUTH_INVALID_CREDENTIALS;
            } else {
                const std::string storedHash =
                    utils::PasswordUtils::normalizeBcryptHash(u["password_hash"].as<std::string>());
                if (bcrypt::validatePassword(signin_dto.getPassword(), storedHash)) {
                    status = "SUCCESS";
                    auto customConfig = drogon::app().getCustomConfig();
                    const std::string jwtSecurityKey =
                        customConfig["JwtBearer"]["JwtSecurityKey"].asString();
                    const std::string jwtIssuer =
                        customConfig["JwtBearer"]["JwtIssuer"].asString();
                    const std::string username =
                        u["username"].isNull() ? "" : u["username"].as<std::string>();
                    const std::string email = u["email"].as<std::string>();

                    // Phase 2: resolve the caller's permission set once, at signin,
                    // and embed it in the token so every downstream service can
                    // enforce RBAC from the gateway-signed TL-Context alone — no
                    // per-request round trip back to Identity (see plan §2.3/§2.4).
                    std::string permClaim;
                    bool superUser = false;
                    try {
                        auto permRows = co_await txn->execSqlCoro(
                            "SELECT DISTINCT rp.permission_code FROM user_roles ur "
                            "JOIN roles r ON r.id = ur.role_id AND NOT r.is_disabled "
                            "JOIN role_permissions rp ON rp.role_id = r.id "
                            "WHERE ur.user_id::text = $1",
                            u["id"].as<std::string>());
                        for (const auto &row : permRows) {
                            const auto code = row["permission_code"].as<std::string>();
                            if (code == "ALL_FUNCTIONS") superUser = true;
                            if (!permClaim.empty()) permClaim += ",";
                            permClaim += code;
                        }
                    } catch (...) {
                        // permission tables may not exist yet on very old tenants —
                        // fall back to an empty permission set rather than failing signin.
                    }

                    auto tokenBuilder =
                        jwt::create()
                            .set_issuer(jwtIssuer)
                            .set_type("JWT")
                            .set_issued_at(std::chrono::system_clock::now())
                            .set_expires_at(std::chrono::system_clock::now() +
                                            std::chrono::hours(24))
                            .set_payload_claim("userId", jwt::claim(u["id"].as<std::string>()))
                            .set_payload_claim("username", jwt::claim(username))
                            .set_payload_claim("email", jwt::claim(email))
                            .set_payload_claim("tenantId", jwt::claim(tenantId))
                            .set_payload_claim("perm", jwt::claim(permClaim))
                            .set_payload_claim("su", jwt::claim(std::string(superUser ? "1" : "0")));
                    auto token = tokenBuilder.sign(jwt::algorithm::hs256{jwtSecurityKey});
                    response.success = true;
                    response.message = "Authentication successful";
                    response.result["token"] = token;
                    response.result["userId"] = u["id"].as<std::string>();
                    response.result["username"] = username;
                    response.result["email"] = email;
                    response.result["tenantId"] = tenantId;
                    const std::string first =
                        u["first_name"].isNull() ? "" : u["first_name"].as<std::string>();
                    const std::string last =
                        u["last_name"].isNull() ? "" : u["last_name"].as<std::string>();
                    response.result["fullName"] = first + " " + last;
                } else {
                    failureReason = "Invalid password";
                    response.success = false;
                    response.message = "Invalid credentials";
                    response.error["code"] = constants::ERR_AUTH_INVALID_CREDENTIALS;
                }
            }

            try {
                co_await txn->execSqlCoro(
                    "INSERT INTO login_history (user_id, status, failure_reason, login_time) "
                    "VALUES ($1::uuid, $2, NULLIF($3, ''), now())",
                    u["id"].as<std::string>(), status, failureReason);
            } catch (...) {
                // never fail a signin because audit logging failed
            }
            co_return response;
        } catch (const std::exception &) {
            // tenant schema missing or DB error — let the host path decide
            co_return std::nullopt;
        }
    }

    // Host signin: platform operators that aren't scoped to any tenant at
    // all, resolved from public.users (the default search_path on a bare,
    // unscoped DbClient — no tenant schema is ever selected for this path,
    // by design; see RbacService::resolvePrincipal's matching "host
    // operator" fallback). There is no business_id/account_id concept here
    // any more — the old business_accounts-keyed lookup this used to do was
    // Identity's own, pre-Provisioner tenant registry, superseded once the
    // Provisioner service + t_<tenantId> schemas became the single source
    // of truth for tenants (Phase 9 cleanup).
    drogon::Task<dto::BaseApiResponse> UserService::validateUserCredentials(
        const dto::SigninDto &signin_dto, const std::string &tenantId) {
        if (!tenantId.empty()) {
            auto tenantResult = co_await tryTenantSignin(signin_dto, tenantId);
            if (tenantResult) co_return *tenantResult;
        }
        const std::string jwtTenantClaim = tenantId.empty() ? "default" : tenantId;

        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlIdentity::Users> mapper(dbClient);

        std::string targetUserId;
        std::string loginStatus;
        std::string loginFailureReason;

        Criteria criteria =
            (Criteria(drogon_model::TlIdentity::Users::Cols::_username, CompareOperator::EQ, signin_dto.getUsernameOrEmail()) ||
             Criteria(drogon_model::TlIdentity::Users::Cols::_phone_number, CompareOperator::EQ, signin_dto.getUsernameOrEmail()) ||
             Criteria(drogon_model::TlIdentity::Users::Cols::_email, CompareOperator::EQ, signin_dto.getUsernameOrEmail())) &&
            Criteria(drogon_model::TlIdentity::Users::Cols::_is_active, CompareOperator::EQ, true) &&
            Criteria(drogon_model::TlIdentity::Users::Cols::_is_locked_out, CompareOperator::EQ, false);

        dto::BaseApiResponse response;

        try {
            drogon_model::TlIdentity::Users user = co_await mapper.findOne(criteria);

            targetUserId = user.getValueOfId();

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

                // Host operators (public.users) always resolve as tenant super-users
                // (see RbacService::resolvePrincipal) — embed the same wildcard here.
                auto token = jwt::create()
                        .set_issuer(jwtIssuer)
                        .set_type("JWT")
                        .set_issued_at(std::chrono::system_clock::now())
                        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(24 * 120))
                        .set_payload_claim("userId", jwt::claim(user.getValueOfId()))
                        .set_payload_claim("username", jwt::claim(user.getValueOfUsername()))
                        .set_payload_claim("email", jwt::claim(user.getValueOfEmail()))
                        .set_payload_claim("tenantId", jwt::claim(jwtTenantClaim))
                        .set_payload_claim("perm", jwt::claim(std::string("ALL_FUNCTIONS")))
                        .set_payload_claim("su", jwt::claim(std::string("1")))
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
