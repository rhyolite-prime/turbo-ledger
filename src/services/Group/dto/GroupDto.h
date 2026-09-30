//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//
#include <string>
#include <json/json.h>

namespace group::dto {

    class GroupDto {
    public:
        GroupDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getOfficeId() const { return office_id; }
        [[nodiscard]] const std::string& getName() const { return name; }
        [[nodiscard]] bool getIsActive() const { return is_active; }

        // Setters
        void setOfficeId(const std::string& value) { office_id = value; }
        void setName(const std::string& value) { name = value; }
        void setIsActive(const bool value) { is_active = value; }

    private:

        std::string office_id;
        std::string name;
        bool is_active = true;
    };

    inline void GroupDto::fromJson(const Json::Value& json) {

        if (json.isMember("officeId") && !json["officeId"].isNull()) {
            office_id = json["officeId"].asString();
        }

        if (json.isMember("name") && !json["name"].isNull()) {
            name = json["name"].asString();
        }

        if (json.isMember("isActive") && !json["isActive"].isNull()) {
            is_active = json["isActive"].asBool();
        }

    }
}


#ifndef GROUP_GROUPDTO_H
#define GROUP_GROUPDTO_H

#endif //GROUP_GROUPDTO_H