//
// Created by Emmanuel Addo-Odame on 04/04/2026.
//

#ifndef CUSTOMER_PAYCLIENTCHARGEDTO_H
#define CUSTOMER_PAYCLIENTCHARGEDTO_H


#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class PayClientChargeDto {
    public:
        PayClientChargeDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getAmount() const { return amount; }
        [[nodiscard]] const std::string& getTransactionDate() const { return transaction_date; }

        // Setters
        void setAmount(const std::string& value) { amount = value; }
        void setTransactionDate(const std::string& value) { transaction_date = value; }

    private:

        std::string amount;
        std::string transaction_date;
    };

    inline void PayClientChargeDto::fromJson(const Json::Value& json) {

        if (json.isMember("amount") && !json["amount"].isNull()) {
            amount = json["amount"].asString();
        }

        if (json.isMember("transactionDate") && !json["transactionDate"].isNull()) {
            transaction_date = json["transactionDate"].asString();
        }

    }
}



#endif //CUSTOMER_PAYCLIENTCHARGEDTO_H