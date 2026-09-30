//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_REJECTCLIENTDTO_H
#define CUSTOMER_REJECTCLIENTDTO_H

#include <string>
#include <json/json.h>

namespace turbo_ledger_customer::dto {

    class RejectClientDto {
    public:
        RejectClientDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getRejectionDate() const { return rejection_date; }
        [[nodiscard]] const std::string& getRejectionCvId() const { return rejection_reason_cv_id; }

        // Setters
        void setRejectionDate(const std::string& value) { rejection_date = value; }
        void setRejectionCvId(const std::string& value) { rejection_reason_cv_id = value; }

    private:

        std::string rejection_date;
        std::string rejection_reason_cv_id;
    };

    inline void RejectClientDto::fromJson(const Json::Value& json) {

        if (json.isMember("rejectionDate") && !json["rejectionDate"].isNull()) {
            rejection_date = json["activationDate"].asString();
        }

        if (json.isMember("rejectionReasonId") && !json["rejectionReasonId"].isNull()) {
            rejection_reason_cv_id = json["rejectionReasonId"].asString();
        }

    }
}


#endif //CUSTOMER_REJECTCLIENTDTO_H