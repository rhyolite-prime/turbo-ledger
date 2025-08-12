
#pragma once

#include <json/json.h>
#include <string>

namespace turbo_ledger_identity::dto {

    class CreateUserDto
    {
    public:
        // Default constructor
        CreateUserDto() = default;

        // Constructor from JSON object, used in the controller
        explicit CreateUserDto(const Json::Value& json)
        {
            if (json.isMember("username") && json["username"].isString()) {
                username_ = json["username"].asString();
            }
            if (json.isMember("password") && json["password"].isString()) {
                password_ = json["password"].asString();
            }
        }

        // Getters
        const std::string& getUsername() const { return username_; }
        const std::string& getPassword() const { return password_; }
        const std::string& getFirstName() const { return firstname_; }
        const std::string& getLastName() const { return lastname_; }
        bool isActive() const { return isactive_; }
        bool isLockedOut() const { return islockedout_; }


        // Setters
        void setUsername(const std::string& username) { username_ = username; }
        void setPassword(const std::string& password) { password_ = password; }
        void setFirstName(const std::string& firstname) { firstname_ = firstname; }
        void setLastName(const std::string& lastname) { lastname_ = lastname; }
        void setActive(bool isActive) { isactive_ = isActive; }
        void setLockedOut(bool isLockedOut) { islockedout_ = isLockedOut; }



    private:
        std::string username_;
        std::string firstname_;
        std::string lastname_;
        std::string password_;
        std::string tenantIdentifier_;
        bool isactive_;
        bool islockedout_;
    };

}


