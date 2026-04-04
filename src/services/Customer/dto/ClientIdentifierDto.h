//
// Created by Emmanuel Addo-Odame on 04/04/2026.
//

#ifndef CUSTOMER_CLIENTIDENTIFIERDTO_H
#define CUSTOMER_CLIENTIDENTIFIERDTO_H

#include <string>
#include <json/json.h>

namespace customer::dto {

    class ClientIdentifierDto {
    public:
        ClientIdentifierDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getDocumentTypeId() const { return document_type_id; }
        [[nodiscard]] const std::string& getDocumentKey() const { return document_key; }
        [[nodiscard]] const std::string& getDescription() const { return description; }

        // Setters
        void setDocumentTypeId(const std::string& value) { document_type_id = value; }
        void setDocumentKey(const std::string& value) { document_key = value; }
        void setDescription(const std::string& value) { description = value; }

    private:

        std::string document_type_id;
        std::string document_key;
        std::string description;
    };

    inline void ClientIdentifierDto::fromJson(const Json::Value& json) {

        if (json.isMember("documentTypeId") && !json["documentTypeId"].isNull()) {
            document_type_id = json["documentTypeId"].asString();
        }

        if (json.isMember("documentKey") && !json["documentKey"].isNull()) {
            document_key = json["documentKey"].asString();
        }

        if (json.isMember("description") && !json["description"].isNull()) {
            description = json["description"].asString();
        }

    }
}


#endif //CUSTOMER_CLIENTIDENTIFIERDTO_H