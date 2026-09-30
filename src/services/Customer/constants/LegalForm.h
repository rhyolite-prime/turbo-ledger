//
// Created by Emmanuel Addo-Odame on 02/04/2026.
//

#ifndef CUSTOMER_LEGALFORM_H
#define CUSTOMER_LEGALFORM_H

namespace turbo_ledger_customer::constants {

    enum LegalStructure {
        INDIVIDUAL = 0,
        SOLE_PROPRIETORSHIP = 100,
        PARTNERSHIP = 200,
        LIMITED_LIABILITY_COMPANY = 300,
        CORPORATION = 400,
        NON_PROFIT_ORGANIZATION = 500,
        GOVERNMENT_ENTITY = 600,
        TRUST = 700,
        COOPERATIVE = 800,
        JOINT_VENTURE = 900,
        PRIVATE_LIMITED_COMPANY = 1000,
        PUBLIC_LIMITED_COMPANY = 1100,
        BRANCH_OFFICE = 1200,
        REPRESENTATIVE_OFFICE = 1300,
        SUBSIDIARY = 1400,
        HOLDING_COMPANY = 1500
    };

}
#endif //CUSTOMER_LEGALFORM_H