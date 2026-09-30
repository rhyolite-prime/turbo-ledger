//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_UPDATEDEFAULTSAVINGSACCOUNTDTO_H
#define CUSTOMER_UPDATEDEFAULTSAVINGSACCOUNTDTO_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class UpdateDefaultSavingsAccountDto {
    public:
        UpdateDefaultSavingsAccountDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getSavingsAccountId() const { return savings_account_id; }

        // Setters
        void setSavingsAccountId(const std::string& value) { savings_account_id = value; }

    private:

        std::string savings_account_id;
    };

    inline void UpdateDefaultSavingsAccountDto::fromJson(const Json::Value& json) {

        if (json.isMember("savingsAccountId") && !json["savingsAccountId"].isNull()) {
            savings_account_id = json["savingsAccountId"].asString();
        }

    }
}
#endif //CUSTOMER_UPDATEDEFAULTSAVINGSACCOUNTDTO_H