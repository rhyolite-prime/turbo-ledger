//
// Created by Emmanuel Addo-Odame on 07/09/2025.
//

#ifndef CREATEGLACCOUNTDTO_H
#define CREATEGLACCOUNTDTO_H

#include <json/json.h>
#include <string>

namespace turbo_ledger_accounting::dto {

    class CreateGlAccountDto {

        public:

        // Default constructor
        CreateGlAccountDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getName() const { return name_; }
        [[nodiscard]] const std::string& getDescription() const { return description_; }

        // Setters
        void setName(const std::string& name) { name_ = name; }
        void setDescription(const std::string& description) { description_ = description; }

    private:

        std::string name_;
        std::string description_;
    };

    inline void CreateGlAccountDto::fromJson(const Json::Value& json) {

        if (json.isMember("name") && !json["name"].isNull()) {
            name_ = json["name"].asString();
        }
        if (json.isMember("description") && !json["description"].isNull()) {
            description_ = json["description"].asString();
        }

    }
}

#endif //CREATEGLACCOUNTDTO_H
