//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_WITHDRAWCLIENT_H
#define CUSTOMER_WITHDRAWCLIENT_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class WithdrawClientDto {
    public:
        WithdrawClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getWithdrawalDate() const { return withdrawal_date; }
        [[nodiscard]] const std::string& getWithdrawalReasonCvId() const { return withdrawal_reason_cv_id; }

        // Setters
        void setWithdrawalDate(const std::string& value) { withdrawal_date = value; }
        void setWithdrawalReasonCvId(const std::string& value) { withdrawal_reason_cv_id = value; }

    private:

        std::string withdrawal_date;
        std::string withdrawal_reason_cv_id;
    };

    inline void WithdrawClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("withdrawalDate") && !json["withdrawalDate"].isNull()) {
            withdrawal_date = json["withdrawalDate"].asString();
        }

        if (json.isMember("withdrawalReasonId") && !json["withdrawalReasonId"].isNull()) {
            withdrawal_reason_cv_id = json["withdrawalReasonId"].asString();
        }

    }


}



#endif //CUSTOMER_WITHDRAWCLIENT_H