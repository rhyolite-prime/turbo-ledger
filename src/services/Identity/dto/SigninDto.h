//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef IDENTITY_SIGNINDTO_H
#define IDENTITY_SIGNINDTO_H

#include <json/json.h>

namespace turbo_ledger_identity::dto {

    class SigninDto {

    public:
        SigninDto() = default;
        explicit SigninDto(const Json::Value& json);

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getAccountId() const { return account_id_; }
        [[nodiscard]] const std::string& getUsernameOrEmail() const { return usernameOrEmail_; }
        [[nodiscard]] const std::string& getPassword() const { return password_; }

        // Setters
        void setAccountId(const std::string& accountId) { account_id_ = accountId; }
        void setUsernameOrEmail(const std::string& usernameOrEmail) { usernameOrEmail_ = usernameOrEmail; }
        void setPassword(const std::string& password) { password_ = password; }

    private:
        std::string account_id_;
        std::string usernameOrEmail_;
        std::string password_;
    };

    inline void SigninDto::fromJson(const Json::Value& json) {

        if (json.isMember("accountId") && !json["accountId"].isNull()) {
            account_id_ = json["accountId"].asString();
        }

        if (json.isMember("usernameOrEmail") && !json["usernameOrEmail"].isNull()) {
            usernameOrEmail_ = json["usernameOrEmail"].asString();
        }

        if (json.isMember("password") && !json["password"].isNull()) {
            password_ = json["password"].asString();
        }

    }

}

#endif //IDENTITY_SIGNINDTO_H
