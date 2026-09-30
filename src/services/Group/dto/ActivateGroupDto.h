//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_ACTIVATEGROUPDTO_H
#define GROUP_ACTIVATEGROUPDTO_H

#include <string>
#include <json/json.h>

namespace group::dto {

    class ActivateGroupDto {
    public:
        ActivateGroupDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getActivationDate() const { return activation_date; }

        // Setters
        void setActivationDate(const std::string& value) { activation_date = value; }


    private:

        std::string activation_date;
    };

    inline void ActivateGroupDto::fromJson(const Json::Value& json) {

        if (json.isMember("activationDate") && !json["activationDate"].isNull()) {
            activation_date = json["activationDate"].asString();
        }



    }
}



#endif //GROUP_ACTIVATEGROUPDTO_H