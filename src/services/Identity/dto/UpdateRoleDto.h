#pragma once

#include <json/json.h>
#include <string>

namespace turbo_ledger_identity::dto {

    class UpdateRoleDto
    {
    public:
        // Default constructor
        UpdateRoleDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        const std::string& getId() const { return id_; }
        const std::string& getName() const { return name_; }
        const std::string& getDescription() const { return description_; }
        const std::string& getPermissions() const { return permissions_; }

        // Setters
        void setId(const std::string& id) { id_ = id; }
        void setName(const std::string& name) { name_ = name; }
        void setDescription(const std::string& description) { description_ = description; }
        void setPermissions(const std::string& permissions) { permissions_ = permissions; }

    private:
        std::string id_;                 // uuid, NOT NULL
        std::string name_;               // varchar(100), NOT NULL
        std::string description_;        // text, nullable
        std::string permissions_;        // jsonb, default '[]'::jsonb
    };

    inline void UpdateRoleDto::fromJson(const Json::Value& json) {
        if (json.isMember("id") && !json["id"].isNull()) {
            id_ = json["id"].asString();
        }

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
