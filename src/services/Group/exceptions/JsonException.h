//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_JSONEXCEPTION_H
#define GROUP_JSONEXCEPTION_H
#include <string>

namespace group::dto {

    class JsonException : public std::exception {
    public:
        JsonException(const std::string& message) : message_(message) {}
        const char* what() const throw() { return message_.c_str(); }
        [[nodiscard]] std::string getMessage() const { return message_; }

    private:
        std::string message_;
    };

}


#endif //GROUP_JSONEXCEPTION_H