//
// Created by Emmanuel Addo-Odame on 02/08/2026.
//

#ifndef IDENTITY_USERIDENTITYDTO_H
#define IDENTITY_USERIDENTITYDTO_H
#include <string>
#include <drogon/HttpRequest.h>

namespace turbo_ledger_identity::dto {

    struct UserIdentityDto
    {
        std::string user_id;
        std::string business_id;
        std::string business_name;
        std::string first_name;
        std::string surname;
        std::string email;
        [[nodiscard]] std::string full_name() const { return first_name + " " + surname; }

        static UserIdentityDto fromRequest(const drogon::HttpRequestPtr& req) {
            UserIdentityDto identity;
            if (req->attributes()->find("businessId")) {
                identity.business_id = req->attributes()->get<std::string>("businessId");
            }
            if (req->attributes()->find("userId")) {
                identity.user_id = req->attributes()->get<std::string>("userId");
            }
            if (req->attributes()->find("email")) {
                identity.email = req->attributes()->get<std::string>("email");
            }
            if (req->attributes()->find("firstName")) {
                identity.first_name = req->attributes()->get<std::string>("firstName");
            }
            if (req->attributes()->find("surName")) {
                identity.surname = req->attributes()->get<std::string>("surName");
            }
            return identity;
        }
    };

}
#endif //IDENTITY_USERIDENTITYDTO_H
