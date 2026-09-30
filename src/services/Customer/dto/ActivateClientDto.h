//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_ACTIVATECLIENTDTO_H
#define CUSTOMER_ACTIVATECLIENTDTO_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class ActivateClientDto {
    public:
        ActivateClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getActivationDate() const { return activation_date; }

        // Setters
        void setActivationDate(const std::string& value) { activation_date = value; }

    private:

        std::string activation_date;
    };

    inline void ActivateClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("activationDate") && !json["activationDate"].isNull()) {
            activation_date = json["activationDate"].asString();
        }

    }
}



#endif //CUSTOMER_ACTIVATECLIENTDTO_H