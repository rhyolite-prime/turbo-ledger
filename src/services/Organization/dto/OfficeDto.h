//
// Created by Emmanuel Addo-Odame on 06/04/2026.
//

#ifndef ORGANIZATION_OFFICEDTO_H
#define ORGANIZATION_OFFICEDTO_H
#include <json/json.h>
#include <string>

namespace organization::dto {

    class OfficeDto {
    public:
        OfficeDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getParentId() const { return parent_id; }
        [[nodiscard]] const std::string& getHierarchy() const { return hierarchy; }
        [[nodiscard]] const std::string& getExternalId() const { return external_id; }
        [[nodiscard]] const std::string& getName() const { return name; }
        [[nodiscard]] const std::string& getOpeningDate() const { return opening_date; }

        // Setters
        void setParentId(const std::string& value) { parent_id = value; }
        void setHierarchy(const std::string& value) { hierarchy = value; }
        void setExternalId(const std::string& value) { external_id = value; }
        void setName(const std::string& value) { name = value; }
        void setOpeningDate(const std::string& value) { opening_date = value; }

    private:

        std::string parent_id;
        std::string hierarchy;
        std::string external_id;
        std::string name;
        std::string opening_date;
    };

    inline void OfficeDto::fromJson(const Json::Value& json) {

        if (json.isMember("parentId") && !json["parentId"].isNull()) {
            parent_id = json["parentId"].asString();
        }

        if (json.isMember("hierarchy") && !json["hierarchy"].isNull()) {
            hierarchy = json["hierarchy"].asString();
        }

        if (json.isMember("externalId") && !json["externalId"].isNull()) {
            external_id = json["externalId"].asString();
        }

        if (json.isMember("name") && !json["name"].isNull()) {
            name = json["name"].asString();
        }

        if (json.isMember("openingDate") && !json["openingDate"].isNull()) {
            opening_date = json["openingDate"].asString();
        }

    }

}

#endif //ORGANIZATION_OFFICEDTO_H