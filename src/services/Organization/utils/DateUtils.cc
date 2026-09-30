//
// Created by Emmanuel Addo-Odame on 07/04/2026.
//

#include "DateUtils.h"
#include <ctime>
#include <cstring>

namespace organization::utils {

    trantor::Date DateUtils::stringToDate(const std::string &dateStr) {
        if (dateStr.empty()) return trantor::Date();
        struct tm stm;
        memset(&stm, 0, sizeof(stm));
        if (strptime(dateStr.c_str(), "%Y-%m-%d", &stm) == nullptr) {
            return trantor::Date();
        }
        time_t t = mktime(&stm);
        return trantor::Date(static_cast<int64_t>(t) * 1000000);
    }

}

