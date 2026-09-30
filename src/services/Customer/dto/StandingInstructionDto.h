//
// Created by Emmanuel Addo-Odame on 10/08/2026.
//

#ifndef CUSTOMER_STANDINGINSTRUCTIONDTO_H
#define CUSTOMER_STANDINGINSTRUCTIONDTO_H
#include <string>
#include <json/json.h>
#include <trantor/utils/Date.h>

namespace turbo_ledger_customer::dto {

    class StandingInstructionDto {
    public:
        StandingInstructionDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getFromOfficeId() const { return from_office_id_; }
        [[nodiscard]] const std::string& getFromClientId() const { return from_client_id_; }
        [[nodiscard]] int32_t getFromAccountType() const { return from_account_type_; }
        [[nodiscard]] const std::string& getName() const { return name_; }
        [[nodiscard]] const std::string& getTransferType() const { return transfer_type_; }
        [[nodiscard]] int32_t getPriority() const { return priority_; }
        [[nodiscard]] int32_t getStatus() const { return status_; }
        [[nodiscard]] const std::string& getFromAccountId() const { return from_account_id_; }
        [[nodiscard]] const std::string& getToOfficeId() const { return to_office_id_; }
        [[nodiscard]] const std::string& getToClientId() const { return to_client_id_; }
        [[nodiscard]] int32_t getToAccountType() const { return to_account_type_; }
        [[nodiscard]] const std::string& getToAccountId() const { return to_account_id_; }
        [[nodiscard]] int32_t getInstructionType() const { return instruction_type_; }
        [[nodiscard]] double getAmount() const { return amount_; }
        [[nodiscard]] const trantor::Date& getValidFrom() const { return valid_from_; }
        [[nodiscard]] int32_t getRecurrenceType() const { return recurrence_type_; }
        [[nodiscard]] int32_t getRecurrenceInterval() const { return recurrence_interval_; }
        [[nodiscard]] int32_t getRecurrenceFrequency() const { return recurrence_frequency_; }
        [[nodiscard]] const std::string& getRecurrenceOnMonthDay() const { return recurrence_on_month_day_; }

        // Setters
        void setFromOfficeId(const std::string& value) { from_office_id_ = value; }
        void setFromClientId(const std::string& value) { from_client_id_ = value; }
        void setFromAccountType(int32_t value) { from_account_type_ = value; }
        void setName(const std::string& value) { name_ = value; }
        void setTransferType(const std::string& value) { transfer_type_ = value; }
        void setPriority(int32_t value) { priority_ = value; }
        void setStatus(int32_t value) { status_ = value; }
        void setFromAccountId(const std::string& value) { from_account_id_ = value; }
        void setToOfficeId(const std::string& value) { to_office_id_ = value; }
        void setToClientId(const std::string& value) { to_client_id_ = value; }
        void setToAccountType(int32_t value) { to_account_type_ = value; }
        void setToAccountId(const std::string& value) { to_account_id_ = value; }
        void setInstructionType(int32_t value) { instruction_type_ = value; }
        void setAmount(double value) { amount_ = value; }
        void setValidFrom(const trantor::Date& value) { valid_from_ = value; }
        void setRecurrenceType(int32_t value) { recurrence_type_ = value; }
        void setRecurrenceInterval(int32_t value) { recurrence_interval_ = value; }
        void setRecurrenceFrequency(int32_t value) { recurrence_frequency_ = value; }
        void setRecurrenceOnMonthDay(const std::string& value) { recurrence_on_month_day_ = value; }

    private:

        std::string from_office_id_;
        std::string from_client_id_;
        int32_t from_account_type_{0};
        std::string name_;
        std::string transfer_type_;
        int32_t priority_{0};
        int32_t status_{0};
        std::string from_account_id_;
        std::string to_office_id_;
        std::string to_client_id_;
        int32_t to_account_type_{0};
        std::string to_account_id_;
        int32_t instruction_type_{0};
        double amount_{0.0};
        trantor::Date valid_from_;
        int32_t recurrence_type_{0};
        int32_t recurrence_interval_{0};
        int32_t recurrence_frequency_{0};
        std::string recurrence_on_month_day_;
    };

    inline void StandingInstructionDto::fromJson(const Json::Value& json) {

        if (json.isMember("fromOfficeId") && !json["fromOfficeId"].isNull()) {
            setFromOfficeId(json["fromOfficeId"].asString());
        }
        if (json.isMember("fromClientId") && !json["fromClientId"].isNull()) {
            from_client_id_ = json["fromClientId"].asString();
        }
        if (json.isMember("fromAccountType") && !json["fromAccountType"].isNull()) {
            from_account_type_ = json["fromAccountType"].asInt();
        }
        if (json.isMember("name") && !json["name"].isNull()) {
            name_ = json["name"].asString();
        }
        if (json.isMember("transferType") && !json["transferType"].isNull()) {
            transfer_type_ = json["transferType"].asString();
        }
        if (json.isMember("priority") && !json["priority"].isNull()) {
            priority_ = json["priority"].asInt();
        }
        if (json.isMember("status") && !json["status"].isNull()) {
            status_ = json["status"].asInt();
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
        if (json.isMember("instructionType") && !json["instructionType"].isNull()) {
            instruction_type_ = json["instructionType"].asInt();
        }
        if (json.isMember("amount") && !json["amount"].isNull()) {
            amount_ = json["amount"].asDouble();
        }
        if (json.isMember("validFrom") && !json["validFrom"].isNull()) {
            if (json["validFrom"].isString()) {
                valid_from_ = trantor::Date::fromDbStringLocal(json["validFrom"].asString());
            } else if (json["validFrom"].isInt64()) {
                valid_from_ = trantor::Date(json["validFrom"].asInt64());
            }
        }
        if (json.isMember("recurrenceType") && !json["recurrenceType"].isNull()) {
            recurrence_type_ = json["recurrenceType"].asInt();
        }
        if (json.isMember("recurrenceInterval") && !json["recurrenceInterval"].isNull()) {
            recurrence_interval_ = json["recurrenceInterval"].asInt();
        }
        if (json.isMember("recurrenceFrequency") && !json["recurrenceFrequency"].isNull()) {
            recurrence_frequency_ = json["recurrenceFrequency"].asInt();
        }
        if (json.isMember("recurrenceOnMonthDay") && !json["recurrenceOnMonthDay"].isNull()) {
            recurrence_on_month_day_ = json["recurrenceOnMonthDay"].asString();
        }

    }
}


#endif //CUSTOMER_STANDINGINSTRUCTIONDTO_H
