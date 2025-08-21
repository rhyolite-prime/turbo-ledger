#pragma once

#include <json/json.h>
#include <string>
#include <optional>

namespace turbo_ledger_identity::dto {

    class UpdateTenantDto
    {
    public:
        // Default constructor
        UpdateTenantDto() = default;

        // Constructor from JSON object, used in the controller
        explicit UpdateTenantDto(const Json::Value& json);

        void fromJson(const Json::Value& json);

        // Getters
        const std::string& getId() const { return id_; }
        const std::string& getIdentifier() const { return identifier_; }
        const std::string& getName() const { return name_; }
        const std::string& getEmail() const { return email_; }
        const std::string& getPhoneNumber() const { return phoneNumber_; }
        bool isActive() const { return isActive_; }

        // Setters
        void setId(const std::string& tenantId) { id_ = tenantId; }
        void setIdentifier(const std::string& identifier) { identifier_ = identifier; }
        void setName(const std::string& name) { name_ = name; }
        void setEmail(const std::string& email) { email_ = email; }
        void setPhoneNumber(const std::string& phoneNumber) { phoneNumber_ = phoneNumber; }
        void setActive(bool isActive) { isActive_ = isActive; }

    private:
        std::string id_ ;
        std::string identifier_;
        std::string name_;
        std::string email_;
        std::string phoneNumber_;
        bool isActive_;
    };

}
