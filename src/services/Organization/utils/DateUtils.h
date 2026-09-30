//
// Created by Emmanuel Addo-Odame on 07/04/2026.
//

#ifndef ORGANIZATION_DATEUTILS_H
#define ORGANIZATION_DATEUTILS_H

#include <trantor/utils/Date.h>
#include <string>

namespace organization {
    namespace utils {

        class DateUtils {
        public:
            static trantor::Date stringToDate(const std::string &dateStr);
        };

    }
}

#endif //ORGANIZATION_DATEUTILS_H
