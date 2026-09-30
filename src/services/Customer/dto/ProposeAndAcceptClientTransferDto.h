//
// Created by Emmanuel Addo-Odame on 04/04/2026.
//

#ifndef CUSTOMER_PROPOSEANDACCEPTCLIENTTRANSFERDTO_H
#define CUSTOMER_PROPOSEANDACCEPTCLIENTTRANSFERDTO_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class ProposeAndAcceptClientTransferDto {
    public:
        ProposeAndAcceptClientTransferDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getDestinationOfficeId() const { return destination_office_id; }
        [[nodiscard]] const std::string& getDestinationGroupId() const { return destination_group_id; }
        [[nodiscard]] const std::string& getStaffId() const { return staff_id; }
        [[nodiscard]] const std::string& getNote() const { return note; }

        // Setters
        void setDestinationOfficeId(const std::string& value) { destination_office_id = value; }
        void setDestinationGroupId(const std::string& value) { destination_group_id = value; }
        void setStaffId(const std::string& value) { staff_id = value; }
        void setNote(const std::string& value) { note = value; }

    private:

        std::string destination_office_id;
        std::string destination_group_id;
        std::string staff_id;
        std::string note;
    };

    inline void ProposeAndAcceptClientTransferDto::fromJson(const Json::Value& json) {

        if (json.isMember("destinationOfficeId") && !json["destinationOfficeId"].isNull()) {
            destination_office_id = json["destinationOfficeId"].asString();
        }

        if (json.isMember("destinationGroupId") && !json["destinationGroupId"].isNull()) {
            destination_group_id = json["destinationGroupId"].asString();
        }

        if (json.isMember("staffId") && !json["staffId"].isNull()) {
            staff_id = json["staffId"].asString();
        }

        if (json.isMember("note") && !json["note"].isNull()) {
            note = json["note"].asString();
        }

    }
}


#endif //CUSTOMER_PROPOSEANDACCEPTCLIENTTRANSFERDTO_H