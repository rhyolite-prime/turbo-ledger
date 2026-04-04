//
// Created by Emmanuel Addo-Odame on 02/04/2026.
//

#ifndef CUSTOMER_CREATECLIENTDTO_H
#define CUSTOMER_CREATECLIENTDTO_H
#include <string>
#include <json/json.h>

namespace customer::dto {

    class ClientDto {
    public:

        ClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getAccountNo() const { return account_no_; }
        [[nodiscard]] const std::string& getExternalId() const { return external_id_; }
        [[nodiscard]] int getStatusEnum() const { return status_enum_; }
        [[nodiscard]] int getSubStatus() const { return sub_status_; }
        [[nodiscard]] const std::string& getActivationDate() const { return activation_date_; }
        [[nodiscard]] const std::string& getOfficeJoiningDate() const { return office_joining_date_; }
        [[nodiscard]] const std::string& getOfficeId() const { return office_id_; }
        [[nodiscard]] const std::string& getTransferToOfficeId() const { return transfer_to_office_id_; }
        [[nodiscard]] const std::string& getStaffId() const { return staff_id_; }
        [[nodiscard]] const std::string& getFirstname() const { return firstname_; }
        [[nodiscard]] const std::string& getMiddlename() const { return middle_name_; }
        [[nodiscard]] const std::string& getLastname() const { return last_name_; }
        [[nodiscard]] const std::string& getFullname() const { return full_name_; }
        [[nodiscard]] const std::string& getDisplayName() const { return display_name_; }
        [[nodiscard]] const std::string& getMobileNo() const { return mobile_no_; }
        [[nodiscard]] bool getIsStaff() const { return is_staff_; }
        [[nodiscard]] const std::string& getGenderCvId() const { return gender_cv_id_; }
        [[nodiscard]] const std::string& getDateOfBirth() const { return date_of_birth_; }
        [[nodiscard]] int getLegalFormEnum() const { return legal_form_enum_; }
        [[nodiscard]] const std::string& getEmailAddress() const { return email_address_; }

        // Setters
        void setAccountNo(const std::string& value) { account_no_ = value; }
        void setExternalId(const std::string& value) { external_id_ = value; }
        void setStatusEnum(int value) { status_enum_ = value; }
        void setSubStatus(int value) { sub_status_ = value; }
        void setActivationDate(const std::string& value) { activation_date_ = value; }
        void setOfficeJoiningDate(const std::string& value) { office_joining_date_ = value; }
        void setOfficeId(const std::string& value) { office_id_ = value; }
        void setTransferToOfficeId(const std::string& value) { transfer_to_office_id_ = value; }
        void setStaffId(const std::string& value) { staff_id_ = value; }
        void setFirstname(const std::string& value) { firstname_ = value; }
        void setMiddlename(const std::string& value) { middle_name_ = value; }
        void setLastname(const std::string& value) { last_name_ = value; }
        void setFullname(const std::string& value) { full_name_ = value; }
        void setDisplayName(const std::string& value) { display_name_ = value; }
        void setMobileNo(const std::string& value) { mobile_no_ = value; }
        void setIsStaff(bool value) { is_staff_ = value; }
        void setGenderCvId(const std::string& value) { gender_cv_id_ = value; }
        void setDateOfBirth(const std::string& value) { date_of_birth_ = value; }
        void setLegalFormEnum(int value) { legal_form_enum_ = value; }
        void setEmailAddress(const std::string& value) { email_address_ = value; }


    private:

        std::string account_no_;
        std::string external_id_;
        int status_enum_ = 0;
        int sub_status_ = 0;
        std::string activation_date_;
        std::string office_joining_date_;
        std::string office_id_;
        std::string transfer_to_office_id_;
        std::string staff_id_;
        std::string firstname_;
        std::string middle_name_;
        std::string last_name_;
        std::string full_name_;
        std::string display_name_;
        std::string mobile_no_;
        bool is_staff_ = false;
        std::string date_of_birth_;
        std::string gender_cv_id_;
        int legal_form_enum_ = 0;
        std::string email_address_;
    };

    inline void ClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("accountNo") && !json["accountNo"].isNull()) {
            account_no_ = json["accountNo"].asString();
        }

        if (json.isMember("externalId") && !json["externalId"].isNull()) {
            external_id_ = json["externalId"].asString();
        }

        if (json.isMember("statusEnum") && !json["statusEnum"].isNull()) {
            status_enum_ = json["statusEnum"].asInt();
        }

        if (json.isMember("subStatus") && !json["subStatus"].isNull()) {
            sub_status_ = json["subStatus"].asInt();
        }

        if (json.isMember("activationDate") && !json["activationDate"].isNull()) {
            activation_date_ = json["activationDate"].asString();
        }

        if (json.isMember("officeJoiningDate") && !json["officeJoiningDate"].isNull()) {
            office_joining_date_ = json["officeJoiningDate"].asString();
        }

        if (json.isMember("officeId") && !json["officeId"].isNull()) {
            office_id_ = json["officeId"].asString();
        }

        if (json.isMember("transferToOfficeId") && !json["transferToOfficeId"].isNull()) {
            transfer_to_office_id_ = json["transferToOfficeId"].asString();
        }

        if (json.isMember("staffId") && !json["staffId"].isNull()) {
            staff_id_ = json["staffId"].asString();
        }

        if (json.isMember("firstname") && !json["firstname"].isNull()) {
            firstname_ = json["firstname"].asString();
        }

        if (json.isMember("middlename") && !json["middlename"].isNull()) {
            middle_name_ = json["middlename"].asString();
        }

        if (json.isMember("lastname") && !json["lastname"].isNull()) {
            last_name_ = json["lastname"].asString();
        }

        if (json.isMember("fullname") && !json["fullname"].isNull()) {
            full_name_ = json["fullname"].asString();
        }

        if (json.isMember("displayName") && !json["displayName"].isNull()) {
            display_name_ = json["displayName"].asString();
        }

        if (json.isMember("mobileNo") && !json["mobileNo"].isNull()) {
            mobile_no_ = json["mobileNo"].asString();
        }

        if (json.isMember("isStaff") && !json["isStaff"].isNull()) {
            is_staff_ = json["isStaff"].asBool();
        }

        if (json.isMember("genderCvId") && !json["genderCvId"].isNull()) {
            gender_cv_id_ = json["genderCvId"].asInt();
        }

        if (json.isMember("dateOfBirth") && !json["dateOfBirth"].isNull()) {
            date_of_birth_ = json["dateOfBirth"].asString();
        }

        if (json.isMember("legalFormEnum") && !json["legalFormEnum"].isNull()) {
            legal_form_enum_ = json["legalFormEnum"].asInt();
        }

        if (json.isMember("emailAddress") && !json["emailAddress"].isNull()) {
            email_address_ = json["emailAddress"].asString();
        }


    }
}
#endif //CUSTOMER_CREATECLIENTDTO_H