//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef IDENTITY_STATUSTYPE_H
#define IDENTITY_STATUSTYPE_H


namespace turbo_ledger_identity::constants {

    enum class StatusType : uint8_t {
        Pending = 0,
        Active = 1,
        Inactive = 2,
        Suspended = 3,
        Banned = 4,
        Archived = 5,
        Deleted = 6,
    };

}


#endif //IDENTITY_STATUSTYPE_H
