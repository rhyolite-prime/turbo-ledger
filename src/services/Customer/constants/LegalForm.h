//
// Created by Emmanuel Addo-Odame on 02/04/2026.
//

#ifndef CUSTOMER_LEGALFORM_H
#define CUSTOMER_LEGALFORM_H

namespace customer::constants {

    enum LegalForm {
        PERSON = 1,
        ENTITY = 2,
        JOINT  = 3,
        GROUP  = 4
    };

}
#endif //CUSTOMER_LEGALFORM_H