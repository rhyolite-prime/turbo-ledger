//
// Created by Emmanuel Addo-Odame on 04/04/2026.
//

#ifndef CUSTOMER_ACCEPTCLIENTTRANSFERDTO_H
#define CUSTOMER_ACCEPTCLIENTTRANSFERDTO_H

#include <string>
#include <json/json.h>

namespace customer::dto {

    class AcceptClientTransferDto {
    public:
        AcceptClientTransferDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getDestinationId() const { return destination_group_id; }
        [[nodiscard]] const std::string& getStaffId() const { return staff_id; }
        [[nodiscard]] const std::string& getNote() const { return note; }

        // Setters
        void setDestinationId(const std::string& value) { destination_group_id = value; }
        void setStaffId(const std::string& value) { staff_id = value; }
        void setNote(const std::string& value) { note = value; }

    private:

        std::string destination_group_id;
        std::string staff_id;
        std::string note;
    };

    inline void AcceptClientTransferDto::fromJson(const Json::Value& json) {

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


#endif //CUSTOMER_ACCEPTCLIENTTRANSFERDTO_H