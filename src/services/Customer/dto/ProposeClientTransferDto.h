//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_PROPOSECLIENTTRANSFERDTO_H
#define CUSTOMER_PROPOSECLIENTTRANSFERDTO_H

#include <string>
#include <json/json.h>

namespace customer::dto {

    class ProposeClientTransferDto {
    public:
        ProposeClientTransferDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getTransferDate() const { return transfer_date; }
        [[nodiscard]] const std::string& getDestinationOfficeId() const { return destination_office_id; }
        [[nodiscard]] const std::string& getNote() const { return note; }

        // Setters
        void setTransferDate(const std::string& value) { transfer_date = value; }
        void setDestinationOfficeId(const std::string& value) { destination_office_id = value; }
        void setNote(const std::string& value) { note = value; }

    private:

        std::string transfer_date;
        std::string destination_office_id;
        std::string note;
    };

    inline void ProposeClientTransferDto::fromJson(const Json::Value& json) {

        if (json.isMember("transferDate") && !json["transferDate"].isNull()) {
            transfer_date = json["transferDate"].asString();
        }

        if (json.isMember("destinationOfficeId") && !json["destinationOfficeId"].isNull()) {
            destination_office_id = json["destinationOfficeId"].asString();
        }

        if (json.isMember("note") && !json["note"].isNull()) {
            note = json["note"].asString();
        }

    }
}
#endif //CUSTOMER_PROPOSECLIENTTRANSFERDTO_H