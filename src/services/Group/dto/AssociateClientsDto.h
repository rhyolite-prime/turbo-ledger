//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_ASSOCIATECLIENTSDTO_H
#define GROUP_ASSOCIATECLIENTSDTO_H

#include <string>
#include <json/json.h>

namespace group::dto {

    class AssociateClientsDto {
    public:
        AssociateClientsDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::vector<std::string>& getClientMembers() const { return client_members; }

        // Setters
        void setClientMembers(const std::vector<std::string>& value) { client_members = value; }



    private:

        std::vector<std::string> client_members;

    };

    inline void AssociateClientsDto::fromJson(const Json::Value& json) {

        if (json.isMember("clientMembers") && !json["clientMembers"].isArray()) {
            client_members.clear();

            for (const auto& member : json["clientMembers"]) {
                client_members.push_back(member.asString());
            }
        }

    };

}


#endif //GROUP_ASSOCIATECLIENTSDTO_H