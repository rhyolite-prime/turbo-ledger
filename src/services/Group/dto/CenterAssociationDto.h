//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_CENTERASSOCIATIONDTO_H
#define GROUP_CENTERASSOCIATIONDTO_H
#include <string>
#include <json/json.h>

namespace group::dto {

    class CenterAssociationDto {
    public:
        CenterAssociationDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::vector<std::string>& getClientMembers() const { return client_members; }

        // Setters
        void setClientMembers(const std::vector<std::string>& value) { client_members = value; }



    private:

        std::vector<std::string> client_members;

    };

    inline void CenterAssociationDto::fromJson(const Json::Value& json) {

        if (json.isMember("clientMembers") && !json["clientMembers"].isArray()) {
            client_members.clear();

            for (const auto& member : json["clientMembers"]) {
                client_members.push_back(member.asString());
            }
        }

    };

}


#endif //GROUP_CENTERASSOCIATIONDTO_H