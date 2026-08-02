//
// Created by Emmanuel Addo-Odame on 01/08/2026.
//

#ifndef IDENTITY_PASSWORDUTILS_H
#define IDENTITY_PASSWORDUTILS_H
#include <string>

namespace turbo_ledger_identity::utils {

    class PasswordUtils {
    public:
        /**
         * @brief Generates a random alphanumeric password
         * @param length The length of the password to generate (default: 8)
         * @return A random password string
         */
        static std::string generateRandomPassword(int length = 8);
        static std::string normalizeBcryptHash(std::string hash);
    };

}
#endif //IDENTITY_PASSWORDUTILS_H
