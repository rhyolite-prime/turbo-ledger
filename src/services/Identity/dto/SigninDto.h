#pragma once

#include <json/json.h>
#include <string>

namespace turbo_ledger_identity::dto {

    class SigninDto
    {
    public:
        SigninDto() = default;
        explicit SigninDto(const Json::Value& json);

        void fromJson(const Json::Value& json);

        // Getters
        const std::string& getUsernameOrEmail() const { return usernameOrEmail_; }
        const std::string& getPassword() const { return password_; }

        // Setters
        void setUsernameOrEmail(const std::string& usernameOrEmail) { usernameOrEmail_ = usernameOrEmail; }
        void setPassword(const std::string& password) { password_ = password; }

    private:
        std::string usernameOrEmail_;
        std::string password_;
    };

}