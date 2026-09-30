//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_TRANSFERCLIENTSDTO_H
#define GROUP_TRANSFERCLIENTSDTO_H

#include <string>
#include <json/json.h>

namespace group::dto {

    class TransferClientsDto {
    public:
        TransferClientsDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getDestinationGroupId() const { return destination_group_id_; }
        [[nodiscard]] const std::vector<std::string>& getClients() const { return clients_; }

        // Setters
        void setDestinationGroupId(const std::string& value) { destination_group_id_ = value; }
        void setClients(const std::vector<std::string>& value) { clients_ = value; }



    private:

        std::string destination_group_id_;
        std::vector<std::string> clients_;

    };

    inline void TransferClientsDto::fromJson(const Json::Value& json) {

        if (json.isMember("destinationGroupId") && !json["destinationGroupId"].isNull()) {
            destination_group_id_ = json["destinationGroupId"].asString();
        }

        if (json.isMember("clientMembers") && !json["clientMembers"].isArray()) {

            clients_.clear();
            for (const auto& member : json["clients"]) {
                clients_.push_back(member.asString());
            }
        }

    };

}



#endif //GROUP_TRANSFERCLIENTSDTO_H