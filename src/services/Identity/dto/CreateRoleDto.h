#pragma once

#include <json/json.h>
#include <json/writer.h>
#include <string>

namespace turbo_ledger_identity::dto {

    class CreateRoleDto
    {
    public:
        // Default constructor
        CreateRoleDto() = default;

        void fromJson(const Json::Value& json);

        // Getters

        const std::string& getName() const { return name_; }
        const std::string& getDescription() const { return description_; }
        const std::string& getPermissions() const { return permissions_; }

        // Setters

        void setName(const std::string& name) { name_ = name; }
        void setDescription(const std::string& description) { description_ = description; }
        void setPermissions(const std::string& permissions) { permissions_ = permissions; }

    private:

        std::string name_;               // varchar(100), NOT NULL
        std::string description_;        // text, nullable
        std::string permissions_;        // jsonb, default '[]'::jsonb
    };

    inline void CreateRoleDto::fromJson(const Json::Value& json) {

        if (json.isMember("name") && !json["name"].isNull()) {
            name_ = json["name"].asString();
        }
        if (json.isMember("description") && !json["description"].isNull()) {
            description_ = json["description"].asString();
        }
        if (json.isMember("permissions") && json["permissions"].isArray()) {
            Json::StreamWriterBuilder builder;
            builder["commentStyle"] = "None";
            builder["indentation"] = "";  // Compact JSON
            permissions_ = Json::writeString(builder, json["permissions"]);
        } else {
            permissions_ = "[]";  // Default empty array
        }
    }
}
