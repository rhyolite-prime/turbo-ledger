//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_CLOSECLIENTDTO_H
#define CUSTOMER_CLOSECLIENTDTO_H

#include <string>
#include <json/json.h>

namespace customer::dto {

    class CloseClientDto {
    public:
        CloseClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getClosureDate() const { return closure_date; }
        [[nodiscard]] const std::string& getClosureReasonCvId() const { return closure_reason_cv_id; }

        // Setters
        void setClosureDate(const std::string& value) { closure_date = value; }
        void setClosureReasonCvId(const std::string& value) { closure_reason_cv_id = value; }

    private:

        std::string closure_date;
        std::string closure_reason_cv_id;
    };

    inline void CloseClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("closureDate") && !json["closureDate"].isNull()) {
            closure_date = json["closureDate"].asString();
        }

        if (json.isMember("closureReasonCvId") && !json["closureReasonCvId"].isNull()) {
            closure_reason_cv_id = json["closureReasonCvId"].asString();
        }

    }
}


#endif //CUSTOMER_CLOSECLIENTDTO_H