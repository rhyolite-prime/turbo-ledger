//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef IDENTITY_ROLEDTO_H
#define IDENTITY_ROLEDTO_H
#include <json/json.h>

namespace turbo_ledger_identity::dto {

    class RoleDto {

        public:

        RoleDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getName() const { return name_; }
        [[nodiscard]] const std::string& getDescription() const { return description_; }
        [[nodiscard]] const std::string& getBusinessId() const { return business_id_; }
        [[nodiscard]] const std::vector<std::string> &getPermissions() const { return permissions_; }

        // Setters
        void setName(const std::string& value) { name_ = value; }
        void setDescription(const std::string& value) { description_ = value; }
        void setBusinessId(const std::string& value) { business_id_ = value; }
        void setPermissions(const std::vector<std::string> &value) { permissions_ = value; }

    private:

        std::string name_;
        std::string description_;
        std::string business_id_;
        std::vector<std::string> permissions_;
    };

    inline void RoleDto::fromJson(const Json::Value& json) {

        if (json.isMember("name") && !json["name"].isNull()) {
           setName(json["name"].asString());
        }

        if (json.isMember("description") && !json["description"].isNull()) {
            setDescription(json["description"].asString());
        }

        if (json.isMember("businessId") && !json["Business"].isNull()) {
            setBusinessId(json["businessId"].asString());
        }

        if (json.isMember("permissions") && json["permissions"].isArray()) {
            for (const auto &ip : json["permissions"]) {
                permissions_.push_back(ip.asString());
            }
        }

    }


}
#endif //IDENTITY_ROLEDTO_H
