
#pragma once

#include <string>
#include <json/json.h>
#include "models/Users.h" // Include the database model

namespace turbo_ledger_identity::dto
{
    class UserDto
    {
    public:
        // Default constructor
        UserDto() = default;

        // Constructor to convert a database model to a DTO
        explicit UserDto(const drogon_model::TurboLedgerIdentity::Users& user)
        {
            // We assume the UUID is retrieved as a string from the model
            id_ = user.getValueOfId(); 
            username_ = user.getValueOfUsername();
            status_ = user.getValueOfIsActive();
            
            // Convert timestamp to ISO 8601 string format for JSON
             
        }

        // Getters
        const std::string& getId() const { return id_; }
        const std::string& getUsername() const { return username_; }
        const std::string& getStatus() const { return status_; }
        const std::string& getCreatedAt() const { return createdAt_; }
        const std::string& getUpdatedAt() const { return updatedAt_; }

    private:
        std::string id_;
        std::string username_;
        std::string status_;
        std::string createdAt_;
        std::string updatedAt_;
    };
}

// Drogon template specialization to convert UserDto to JSON
namespace drogon
{
    template <>
    inline Json::Value to_json(const turbo_ledger_identity::dto::UserDto& dto)
    {
        Json::Value json;
        json["id"] = dto.getId();
        json["username"] = dto.getUsername();
        json["status"] = dto.getStatus();
        json["created_at"] = dto.getCreatedAt();
        json["updated_at"] = dto.getUpdatedAt();
        return json;
    }
}
