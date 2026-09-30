//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_ASSIGNROLEDTO_H
#define GROUP_ASSIGNROLEDTO_H


#include <string>
#include <json/json.h>

namespace group::dto {

    class AssignRoleDto {
    public:
        AssignRoleDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getClientId() const { return client_id; }
        [[nodiscard]] const std::string& getRoleId() const { return role_id; }

        // Setters
        void setClientId(const std::string& value) { client_id = value; }
        void setRoleId(const std::string& value) { role_id = value; }

    private:

        std::string client_id;
        std::string role_id;
    };

    inline void AssignRoleDto::fromJson(const Json::Value& json) {

        if (json.isMember("clientId") && !json["clientId"].isNull()) {
            client_id = json["clientId"].asString();
        }

        if (json.isMember("roleId") && !json["roleId"].isNull()) {
            role_id = json["roleId"].asString();
        }



    }
}



#endif //GROUP_ASSIGNROLEDTO_H