//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_CLOSEGROUPDTO_H
#define GROUP_CLOSEGROUPDTO_H

#include <string>
#include <json/json.h>

namespace group::dto {

    class CloseGroupDto {
    public:
        CloseGroupDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getClosureDate() const { return closure_date; }
        [[nodiscard]] const std::string& getClosureReasonId() const { return closure_reason_id; }

        // Setters
        void setClosureDate(const std::string& value) { closure_date = value; }
        void setClosureReasonId(const std::string& value) { closure_reason_id = value; }

    private:

        std::string closure_date;
        std::string closure_reason_id;
    };

    inline void CloseGroupDto::fromJson(const Json::Value& json) {

        if (json.isMember("closureDate") && !json["closureDate"].isNull()) {
            closure_date = json["closureDate"].asString();
        }

        if (json.isMember("closureReasonId") && !json["closureReasonId"].isNull()) {
            closure_reason_id = json["closureReasonId"].asString();
        }

    }
}



#endif //GROUP_CLOSEGROUPDTO_H