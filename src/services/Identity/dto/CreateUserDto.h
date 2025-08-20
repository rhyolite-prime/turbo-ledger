
#pragma once

#include <json/json.h>
#include <string>

namespace turbo_ledger_identity::dto {

    class CreateUserDto
    {
    public:
        // Default constructor
        CreateUserDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        const std::string& getUsername() const { return username_; }
        const std::string& getPassword() const { return password_; }
        const std::string& getFirstName() const { return firstname_; }
        const std::string& getLastName() const { return lastname_; }
        const std::string& getPhoneNumber() const { return phonenumber_; }
        const std::string& getEmail() const { return email_; }
        bool isActive() const { return isactive_; }
        bool isLockedOut() const { return islockedout_; }


        // Setters
        void setUsername(const std::string& username) { username_ = username; }
        void setPassword(const std::string& password) { password_ = password; }
        void setFirstName(const std::string& firstname) { firstname_ = firstname; }
        void setLastName(const std::string& lastname) { lastname_ = lastname; }
        void setPhoneNumber(const std::string& phonenumber) { phonenumber_ = phonenumber; }
        void setEmail(const std::string& email) { email_ = email; }
        void setActive(bool isActive) { isactive_ = isActive; }
        void setLockedOut(bool isLockedOut) { islockedout_ = isLockedOut; }


    private:
        std::string username_;
        std::string firstname_;
        std::string lastname_;
        std::string phonenumber_;
        std::string email_;
        std::string password_;
        std::string tenantIdentifier_;
        bool isactive_;
        bool islockedout_;
    };

}


