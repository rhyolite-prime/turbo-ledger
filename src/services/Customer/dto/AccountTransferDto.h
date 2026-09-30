//
// Created by Emmanuel Addo-Odame on 10/08/2026.
//

#ifndef CUSTOMER_ACCOUNTTRANSFERDTO_H
#define CUSTOMER_ACCOUNTTRANSFERDTO_H

#include <string>
#include <json/json.h>
#include <trantor/utils/Date.h>

namespace turbo_ledger_customer::dto {

    class AccountTransferDto {
    public:
        AccountTransferDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getFromOfficeId() const { return from_office_id_; }
        [[nodiscard]] const std::string& getFromClientId() const { return from_client_id_; }
        [[nodiscard]] int32_t getFromAccountType() const { return from_account_type_; }
        [[nodiscard]] const std::string& getFromAccountId() const { return from_account_id_; }
        [[nodiscard]] const std::string& getToOfficeId() const { return to_office_id_; }
        [[nodiscard]] const std::string& getToClientId() const { return to_client_id_; }
        [[nodiscard]] int32_t getToAccountType() const { return to_account_type_; }
        [[nodiscard]] const std::string& getToAccountId() const { return to_account_id_; }
        [[nodiscard]] const trantor::Date& getTransferDate() const { return transfer_date_; }
        [[nodiscard]] double getTransferAmount() const { return transfer_amount_; }
        [[nodiscard]] const std::string& getTransferDescription() const { return transfer_description_; }

        // Setters
        void setFromOfficeId(const std::string& value) { from_office_id_ = value; }
        void setFromClientId(const std::string& value) { from_client_id_ = value; }
        void setFromAccountType(int32_t value) { from_account_type_ = value; }
        void setFromAccountId(const std::string& value) { from_account_id_ = value; }
        void setToOfficeId(const std::string& value) { to_office_id_ = value; }
        void setToClientId(const std::string& value) { to_client_id_ = value; }
        void setToAccountType(int32_t value) { to_account_type_ = value; }
        void setToAccountId(const std::string& value) { to_account_id_ = value; }
        void setTransferDate(const trantor::Date& value) { transfer_date_ = value; }
        void setTransferAmount(double value) { transfer_amount_ = value; }
        void setTransferDescription(const std::string& value) { transfer_description_ = value; }

    private:

        std::string from_office_id_;
        std::string from_client_id_;
        int32_t from_account_type_{0};
        std::string from_account_id_;
        std::string to_office_id_;
        std::string to_client_id_;
        int32_t to_account_type_{0};
        std::string to_account_id_;
        trantor::Date transfer_date_;
        double transfer_amount_{0.0};
        std::string transfer_description_;



    };

    inline void AccountTransferDto::fromJson(const Json::Value& json) {

        if (json.isMember("fromOfficeId") && !json["fromOfficeId"].isNull()) {
            from_office_id_ = json["fromOfficeId"].asString();
        }

        if (json.isMember("fromClientId") && !json["fromClientId"].isNull()) {
            from_client_id_ = json["fromClientId"].asString();
        }

        if (json.isMember("fromAccountType") && !json["fromAccountType"].isNull()) {
            from_account_type_ = json["fromAccountType"].asInt();
        }

        if (json.isMember("fromAccountId") && !json["fromAccountId"].isNull()) {
            from_account_id_ = json["fromAccountId"].asString();
        }

        if (json.isMember("toOfficeId") && !json["toOfficeId"].isNull()) {
            to_office_id_ = json["toOfficeId"].asString();
        }

        if (json.isMember("toClientId") && !json["toClientId"].isNull()) {
            to_client_id_ = json["toClientId"].asString();
        }

        if (json.isMember("toAccountType") && !json["toAccountType"].isNull()) {
            to_account_type_ = json["toAccountType"].asInt();
        }

        if (json.isMember("toAccountId") && !json["toAccountId"].isNull()) {
            to_account_id_ = json["toAccountId"].asString();
        }

        if (json.isMember("transferAmount") && !json["transferAmount"].isNull()) {
            transfer_amount_ = json["transferAmount"].asDouble();
        }

        if (json.isMember("transferDate") && !json["transferDate"].isNull()) {
            if (json["transferDate"].isString()) {
                transfer_date_ = trantor::Date::fromDbStringLocal(json["transferDate"].asString());
            } else if (json["transferDate"].isInt64()) {
                transfer_date_ = trantor::Date(json["transferDate"].asInt64());
            }
        }

        if (json.isMember("transferDescription") && !json["transferDescription"].isNull()) {
            transfer_description_ = json["transferDescription"].asString();
        }

    }
}


#endif //CUSTOMER_ACCOUNTTRANSFERDTO_H
