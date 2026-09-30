//
// Created by Emmanuel Addo-Odame on 03/04/2026.
//

#ifndef CUSTOMER_CLIENTSTATUS_H
#define CUSTOMER_CLIENTSTATUS_H
namespace turbo_ledger_customer::constants {

    enum ClientStatus {
        INVALID         = 0,
        PENDING         = 100,
        ACTIVE          = 300,
        CLOSED          = 600,
        REJECTED        = 700,
        WITHDRAWN       = 800,
        TRANSFER_IN_PROGRESS = 900,
    };

}
#endif //CUSTOMER_CLIENTSTATUS_H