
#pragma once

#include <json/json.h>
#include <string>

namespace turbo_ledger_identity::dto {

    class CreateTenantDto
    {
    public:
        // Default constructor
        CreateTenantDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        const std::string& getIdentifier() const { return identifier_; }
        const std::string& getName() const { return name_; }
        const std::string& getEmail() const { return email_; }
        const std::string& getPhoneNumber() const { return phoneNumber_; }
        const std::string& getConnectionString() const { return connectionString_; }
        bool isActive() const { return isActive_; }

        // Setters
        void setIdentifier(const std::string& identifier) { identifier_ = identifier; }
        void setName(const std::string& name) { name_ = name; }
        void setEmail(const std::string& email) { email_ = email; }
        void setPhoneNumber(const std::string& phoneNumber) { phoneNumber_ = phoneNumber; }
        void setConnectionString(const std::string& connectionString) { connectionString_ = connectionString; }
        void setActive(bool isActive) { isActive_ = isActive; }

    private:
        std::string identifier_;
        std::string name_;
        std::string email_;
        std::string phoneNumber_;
        std::string connectionString_;
        bool isActive_ = true;
    };

}
