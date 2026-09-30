//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_INDIVIDUALCOLLECTIONSHEETDTO_H
#define GROUP_INDIVIDUALCOLLECTIONSHEETDTO_H

#include <string>
#include <json/json.h>

namespace group::dto {

    class IndividualCollectionSheetDto {
    public:
        IndividualCollectionSheetDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getOfficeId() const { return office_id; }
        [[nodiscard]] const std::string& getTransactionDate() const { return transaction_date; }

        // Setters
        void setOfficeId(const std::string& value) { office_id = value; }
        void setTransactionDate(const std::string& value) { transaction_date = value; }

    private:

        std::string office_id;
        std::string transaction_date;
    };

    inline void IndividualCollectionSheetDto::fromJson(const Json::Value& json) {

        if (json.isMember("officeId") && !json["officeId"].isNull()) {
            office_id = json["officeId"].asString();
        }

        if (json.isMember("transactionDate") && !json["transactionDate"].isNull()) {
            transaction_date = json["transactionDate"].asString();
        }

    }
}



#endif //GROUP_INDIVIDUALCOLLECTIONSHEETDTO_H