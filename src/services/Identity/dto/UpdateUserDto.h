// dto/UpdateUserDto.h
#pragma once

#include <json/json.h>
#include <string>
#include <optional>

namespace turbo_ledger_identity::dto {

    class UpdateUserDto
    {
    public:
        // Default constructor
        UpdateUserDto() = default;

        // Constructor from JSON object
        explicit UpdateUserDto(const Json::Value& json);

        void fromJson(const Json::Value& json);

        // Getters
        const std::string& getId() const { return id_; }
        const std::string& getFirstName() const { return firstname_; }
        const std::string& getLastName() const { return lastname_; }
        const std::string& getPhoneNumber() const { return phonenumber_; }
        const std::string& getEmail() const { return email_; }
        const std::string& getPassword() const { return password_; }
        bool getIsActive() const { return isactive_; }
        bool getIsLockedOut() const { return islockedout_; }


        // Setters
        void setId(const std::string& id) { id_ = id; }
        void setFirstName(const std::string& firstname) { firstname_ = firstname; }
        void setLastName(const std::string& lastname) { lastname_ = lastname; }
        void setPhoneNumber(const std::string& phonenumber) { phonenumber_ = phonenumber; }
        void setEmail(const std::string& email) { email_ = email; }
        void setPassword(const std::string& password) { password_ = password; }
        void setIsActive(bool isActive) { isactive_ = isActive; }
        void setIsLockedOut(bool isLockedOut) { islockedout_ = isLockedOut; }

    private:
        std::string id_;
        std::string firstname_;
        std::string lastname_;
        std::string phonenumber_;
        std::string email_;
        std::string password_;
        bool isactive_;
        bool islockedout_;
    };

}