//
// Created by Emmanuel Addo-Odame on 04/04/2026.
//

#ifndef CUSTOMER_CLIENTCHARGEDTO_H
#define CUSTOMER_CLIENTCHARGEDTO_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class ClientChargeDto {
    public:
        ClientChargeDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getAmount() const { return amount; }
        [[nodiscard]] const std::string& getChargeId() const { return charge_id; }
        [[nodiscard]] const std::string& getDueDate() const { return due_date; }


        // Setters
        void setAmount(const std::string& value) { amount = value; }
        void setChargeId(const std::string& value) { charge_id = value; }
        void setDueDate(const std::string& value) { due_date = value; }


    private:
        std::string amount;
        std::string charge_id;
        std::string due_date;

    };

    inline void ClientChargeDto::fromJson(const Json::Value& json) {

        if (json.isMember("amount") && !json["amount"].isNull()) {
            amount = json["amount"].asString();
        }

        if (json.isMember("chargeId") && !json["chargeId"].isNull()) {
            charge_id = json["chargeId"].asString();
        }

        if (json.isMember("dueDate") && !json["dueDate"].isNull()) {
            due_date = json["dueDate"].asString();
        }

    }
}


#endif //CUSTOMER_CLIENTCHARGEDTO_H