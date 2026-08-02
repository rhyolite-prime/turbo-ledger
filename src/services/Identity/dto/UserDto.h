//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef IDENTITY_USERDTO_H
#define IDENTITY_USERDTO_H

#include <json/json.h>

namespace turbo_ledger_identity::dto {

    class UserDto {

    public:

        UserDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getFirstName() const { return first_name_; }
        [[nodiscard]] const std::string& getLastName() const { return last_name_; }
        [[nodiscard]] const std::string& getEmail() const { return email_; }
        [[nodiscard]] const std::string& getUsername() const { return username_; }
        [[nodiscard]] const std::string& getPassword() const { return password_; }
        [[nodiscard]] const std::string& getPhoneNumber() const { return phone_number_; }
        [[nodiscard]] const std::string& getCountry() const { return country_; }

        // Setters
        void setFirstName(const std::string& value) { first_name_ = value; }
        void setLastName(const std::string& value) { last_name_ = value; }
        void setEmail(const std::string& value) { email_ = value; }
        void setUsername(const std::string& value) { username_ = value; }
        void setPassword(const std::string& value) { password_ = value; }
        void setPhoneNumber(const std::string& value) { phone_number_ = value; }
        void setCountry(const std::string& value) { country_ = value; }


    private:

        std::string first_name_;
        std::string last_name_;
        std::string username_;
        std::string email_;
        std::string password_;
        std::string phone_number_;
        std::string country_;
    };

    inline void UserDto::fromJson(const Json::Value& json) {

        if (json.isMember("firstName") && !json["firstName"].isNull()) {
            setFirstName(json["firstName"].asString());
        }

        if (json.isMember("lastName") && !json["lastName"].isNull()) {
            setLastName(json["lastName"].asString()) ;
        }

        if (json.isMember("username") && !json["username"].isNull()) {
            setUsername(json["username"].asString()) ;
        }

         if (json.isMember("email") && !json["email"].isNull()) {
             setEmail(json["email"].asString()) ;
         }

        if (json.isMember("password") && !json["password"].isNull()) {
            setPassword(json["password"].asString()) ;
        }

        if (json.isMember("phoneNumber") && !json["phoneNumber"].isNull()) {
            setPhoneNumber(json["phoneNumber"].asString());
        }

        if (json.isMember("country") && !json["country"].isNull()) {
            setCountry(json["country"].asString());
        }

    }

}


#endif //IDENTITY_USERDTO_H
