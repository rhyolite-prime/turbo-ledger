#pragma once

#include <json/json.h>
#include <string>

namespace turbo_ledger_identity::dto {

    class CreateRoleDto
    {
    public:
        // Default constructor
        CreateRoleDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        const std::string& getTenantIdentifier() const { return tenant_identifier_; }
        const std::string& getName() const { return name_; }
        const std::string& getDescription() const { return description_; }
        const std::string& getPermissions() const { return permissions_; }

        // Setters
        void setTenantIdentifier(const std::string& tenant_identifier) { tenant_identifier_ = tenant_identifier; }
        void setName(const std::string& name) { name_ = name; }
        void setDescription(const std::string& description) { description_ = description; }
        void setPermissions(const std::string& permissions) { permissions_ = permissions; }

    private:
        std::string tenant_identifier_;  // varchar(32), NOT NULL
        std::string name_;               // varchar(100), NOT NULL
        std::string description_;        // text, nullable
        std::string permissions_;        // jsonb, default '[]'::jsonb
    };

    inline void CreateRoleDto::fromJson(const Json::Value& json) {
        if (json.isMember("tenant_identifier") && !json["tenant_identifier"].isNull()) {
            tenant_identifier_ = json["tenant_identifier"].asString();
        }
        if (json.isMember("name") && !json["name"].isNull()) {
            name_ = json["name"].asString();
        }
        if (json.isMember("description") && !json["description"].isNull()) {
            description_ = json["description"].asString();
        }
        if (json.isMember("permissions") && !json["permissions"].isNull()) {
            permissions_ = json["permissions"].asString();
        } else {
            permissions_ = "[]";  // Default empty array
        }
    }
}
