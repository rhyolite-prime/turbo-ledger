//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_CENTERDTO_H
#define GROUP_CENTERDTO_H

#include <string>
#include <json/json.h>

#include "exceptions/JsonException.h"

namespace group::dto {

    class CenterDto {
    public:
        CenterDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getName() const { return name_; }
        [[nodiscard]] const std::string& getOfficeId() const { return office_id_; }
        [[nodiscard]] bool getIsActive() const { return is_active_; }


        // Setters
        void setName(const std::string& value) { name_ = value; }
        void setOfficeId(const std::string& value) { office_id_ = value; }
        void setIsActive(const std::string& value) { office_id_ = value; }


    private:

        std::string name_;
        std::string office_id_;
        bool is_active_ = false;
        std::string activation_date_;
        std::string external_id_;
        std::string staff_id_;
        std::string group_id_;
        std::vector<std::string> group_members_;

    };

    inline void CenterDto::fromJson(const Json::Value& json) {

        if (json.isMember("name") && !json["name"].isNull()) {
            name_ = json["name"].asString();
        }

        if (json.isMember("officeId") && !json["officeId"].isNull()) {
            office_id_ = json["officeId"].asString();
        }

        if (json.isMember("isActive") && !json["isActive"].isNull()) {
            is_active_ = json["isActive"].asBool();
        }

        if (json.isMember("activationDate") && !json["activationDate"].isNull()) {
            activation_date_ = json["activationDate"].asString();
        }

        if (json.isMember("isActive") && !json["isActive"].isNull() && json["isActive"].asBool()) {
            is_active_ = true;
            // Check for activation date and throw an exception if it's not present
            if (!json.isMember("activationDate") || json["activationDate"].isNull()) {
                throw JsonException("Activation date is required when isActive=true");
            }
        } else {
            is_active_ = false;  // Default value
        }

        if (json.isMember("externalId") && !json["externalId"].isNull()) {
            external_id_ = json["externalId"].asString();
        }

        if (json.isMember("staffId") && !json["staffId"].isNull()) {
            staff_id_ = json["staffId"].asString();
        }


        if (json.isMember("groupMembers") && !json["groupMembers"].isArray()) {
            group_members_.clear();
            for (const auto& member : json["groupMembers"]) {
                group_members_.push_back(member.asString());
            }
        }

    }
}


#endif //GROUP_CENTERDTO_H