//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_WITHDRAWCLIENTTRANSFERDTO_H
#define CUSTOMER_WITHDRAWCLIENTTRANSFERDTO_H

#include <string>
#include <json/json.h>

namespace customer::dto {

    class WithdrawOrRejectClientTransferDto {
    public:
        WithdrawOrRejectClientTransferDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getNote() const { return note; }

        // Setters
        void setNote(const std::string& value) { note = value; }

    private:

        std::string note;
    };

    inline void WithdrawOrRejectClientTransferDto::fromJson(const Json::Value& json) {

        if (json.isMember("note") && !json["note"].isNull()) {
            note = json["note"].asString();
        }

    }
}


#endif //CUSTOMER_WITHDRAWCLIENTTRANSFERDTO_H