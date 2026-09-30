//
// Created by Emmanuel Addo-Odame on 04/04/2026.
//

#ifndef CUSTOMER_CLIENTADDRESSDTO_H
#define CUSTOMER_CLIENTADDRESSDTO_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class ClientAddressDto {
    public:
        ClientAddressDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getStreet() const { return street; }
        [[nodiscard]] const std::string& getAddressLine1() const { return addressLine1; }
        [[nodiscard]] const std::string& getAddressLine2() const { return addressLine2; }
        [[nodiscard]] const std::string& getCity() const { return city; }
        [[nodiscard]] const std::string& getCountry() const { return country; }
        [[nodiscard]] const std::string& getCountryCode() const { return country_code; }
        [[nodiscard]] const std::string& getStateOrProvince() const { return state_or_province; }
        [[nodiscard]] const std::string& getAddressTypeId() const { return address_type_id; }

        // Setters
        void setStreet(const std::string& value) { street = value; }
        void setAddressLine1(const std::string& value) { addressLine1 = value; }
        void setAddressLine2(const std::string& value) { addressLine2 = value; }
        void setCity(const std::string& value) { city = value; }
        void setCountry(const std::string& value) { country = value; }
        void setCountryCode(const std::string& value) { country_code = value; }
        void setStateOrProvince(const std::string& value) { state_or_province = value; }
        void setAddressTypeId(const std::string& value) { address_type_id = value; }

    private:

        std::string street;
        std::string addressLine1;
        std::string addressLine2;
        std::string city;
        std::string country;
        std::string country_code;
        std::string state_or_province;
        std::string address_type_id;
    };

    inline void ClientAddressDto::fromJson(const Json::Value& json) {

        if (json.isMember("withdrawalDate") && !json["withdrawalDate"].isNull()) {
            street = json["withdrawalDate"].asString();
        }

        if (json.isMember("withdrawalReasonId") && !json["withdrawalReasonId"].isNull()) {
            addressLine1 = json["withdrawalReasonId"].asString();
        }

    }
}


#endif //CUSTOMER_CLIENTADDRESSDTO_H