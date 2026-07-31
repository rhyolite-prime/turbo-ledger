//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_REACTIVATECLIENTDTO_H
#define CUSTOMER_REACTIVATECLIENTDTO_H

#include <string>
#include <json/json.h>

namespace customer::dto {

    class ReactivateClientDto {
    public:
        ReactivateClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getReactivationDate() const { return reactivation_date; }

        // Setters
        void setReactivationDate(const std::string& value) { reactivation_date = value; }

    private:

        std::string reactivation_date;
    };

    inline void ReactivateClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("reactivationDate") && !json["reactivationDate"].isNull()) {
            reactivation_date = json["reactivationDate"].asString();
        }

    }
}



#endif //CUSTOMER_REACTIVATECLIENTDTO_H