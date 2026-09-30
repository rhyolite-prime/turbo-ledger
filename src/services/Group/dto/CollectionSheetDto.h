//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_COLLECTIONSHEETDTO_H
#define GROUP_COLLECTIONSHEETDTO_H


#include <string>
#include <json/json.h>

namespace group::dto {

    class CollectionSheetDto {
    public:
        CollectionSheetDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getCalendarId() const { return calendar_id_; }
        [[nodiscard]] const std::string& getTransactionDate() const { return transaction_date_; }
        [[nodiscard]] const std::string& getActualDisbursementDate() const { return actual_disbursement_date_; }
        [[nodiscard]] const std::string& getClientsAttendance() const { return clients_attendance_; }
        [[nodiscard]] const std::string& getBulkDisbursementTransactions() const { return bulk_disbursement_transactions_; }
        [[nodiscard]] const std::string& getBulkRepaymentTransactions() const { return bulk_repayment_transactions_; }
        [[nodiscard]] const std::string& getBulkSavingsDueTransactions() const { return bulk_savings_due_transactions_; }

        // Setters
        void setCalendarId(const std::string& value) { calendar_id_ = value; }
        void setTransactionDate(const std::string& value) { transaction_date_ = value; }
        void setActualDisbursementDate(const std::string& value) { actual_disbursement_date_ = value; }
        void setClientsAttendance(const std::string& value) { clients_attendance_ = value; }
        void setBulkDisbursementTransactions(const std::string& value) { bulk_disbursement_transactions_ = value; }
        void setBulkRepaymentTransactions(const std::string& value) { bulk_disbursement_transactions_ = value; }
        void setBulkSavingsDueTransactions(const std::string& value) { bulk_savings_due_transactions_ = value; }

    private:

        std::string calendar_id_;
        std::string transaction_date_;
        std::string actual_disbursement_date_;
        //optional fields
        std::string clients_attendance_;
        std::string bulk_disbursement_transactions_;
        std::string bulk_repayment_transactions_;
        std::string bulk_savings_due_transactions_;
    };

    inline void CollectionSheetDto::fromJson(const Json::Value& json) {

        if (json.isMember("calendarId") && !json["calendarId"].isNull()) {
            calendar_id_ = json["calendarId"].asString();
        }

        if (json.isMember("transactionDate") && !json["transactionDate"].isNull()) {
            transaction_date_ = json["transactionDate"].asString();
        }

        if (json.isMember("actualDisbursementDate") && !json["actualDisbursementDate"].isNull()) {
            actual_disbursement_date_ = json["actualDisbursementDate"].asString();
        }

        if (json.isMember("clientsAttendance") && !json["clientsAttendance"].isNull()) {
            clients_attendance_ = json["clientsAttendance"].asString();
        }

        if (json.isMember("bulkDisbursementTransactions") && !json["bulkDisbursementTransactions"].isNull()) {
            bulk_disbursement_transactions_ = json["bulkDisbursementTransactions"].asString();
        }

        if (json.isMember("bulkRepaymentTransactions") && !json["bulkRepaymentTransactions"].isNull()) {
            bulk_repayment_transactions_ = json["bulkRepaymentTransactions"].asString();
        }

        if (json.isMember("bulkSavingsDueTransactions") && !json["bulkSavingsDueTransactions"].isNull()) {
            bulk_savings_due_transactions_ = json["bulkSavingsDueTransactions"].asString();
        }


    }
}


#endif //GROUP_COLLECTIONSHEETDTO_H