//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_ASSIGNSTAFFDTO_H
#define GROUP_ASSIGNSTAFFDTO_H


#include <string>
#include <json/json.h>

namespace group::dto {

    class AssignStaffDto {
    public:
        AssignStaffDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getStaffId() const { return staff_id; }


        // Setters
        void setStaffId(const std::string& value) { staff_id = value; }


    private:

        std::string staff_id;

    };

    inline void AssignStaffDto::fromJson(const Json::Value& json) {

        if (json.isMember("staffId") && !json["staffId"].isNull()) {
            staff_id = json["staffId"].asString();
        }


    }
}



#endif //GROUP_ASSIGNSTAFFDTO_H