#include "turbo/Ids.h"

#include <openssl/rand.h>
#include <chrono>
#include <cstdio>

namespace turbo::ids {

std::string newUuid() {
    unsigned char b[16];
    RAND_bytes(b, sizeof(b));
    b[6] = static_cast<unsigned char>((b[6] & 0x0F) | 0x40);  // version 4
    b[8] = static_cast<unsigned char>((b[8] & 0x3F) | 0x80);  // variant 10
    char out[37];
    std::snprintf(out, sizeof(out),
                  "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                  b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10], b[11],
                  b[12], b[13], b[14], b[15]);
    return std::string(out);
}

std::string newRequestId() {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
    unsigned char r[4];
    RAND_bytes(r, sizeof(r));
    char out[32];
    std::snprintf(out, sizeof(out), "%llx-%02x%02x%02x%02x",
                  static_cast<unsigned long long>(ms), r[0], r[1], r[2], r[3]);
    return std::string(out);
}

}  // namespace turbo::ids
