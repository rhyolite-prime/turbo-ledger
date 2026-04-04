//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_ASSIGNSTAFFTOCLIENTDTO_H
#define CUSTOMER_ASSIGNSTAFFTOCLIENTDTO_H


#include <string>
#include <json/json.h>

namespace customer::dto {

    class AssignStaffToClientDto {
    public:
        AssignStaffToClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getStaffId() const { return staff_id; }

        // Setters
        void setStaffId(const std::string& value) { staff_id = value; }

    private:

        std::string staff_id;
    };

    inline void AssignStaffToClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("staffId") && !json["staffId"].isNull()) {
            staff_id = json["staffId"].asString();
        }

    }
}



#endif //CUSTOMER_ASSIGNSTAFFTOCLIENTDTO_H