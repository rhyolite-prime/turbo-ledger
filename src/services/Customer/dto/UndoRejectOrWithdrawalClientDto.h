//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_UNDOREJECTCLIENTDTO_H
#define CUSTOMER_UNDOREJECTCLIENTDTO_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class UndoRejectOrWithdrawalClientDto {
    public:
        UndoRejectOrWithdrawalClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getReopenedDate() const { return reopened_date; }

        // Setters
        void setReopenedDate(const std::string& value) { reopened_date = value; }

    private:

        std::string reopened_date;
    };

    inline void UndoRejectOrWithdrawalClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("reopenedDate") && !json["reopenedDate"].isNull()) {
            reopened_date = json["reopenedDate"].asString();
        }

    }
}


#endif //CUSTOMER_UNDOREJECTCLIENTDTO_H