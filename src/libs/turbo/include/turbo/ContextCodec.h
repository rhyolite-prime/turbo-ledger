//
// Turbo Ledger platform library — signing/verification of the TL-Context header.
//
// Format:  v1.<base64url(json payload)>.<base64url(hmac-sha256(payload))>
//
// The secret is shared between the gateway and internal services
// (custom_config.turbo.context_secret). Services accept a context only when
// the signature verifies and the expiry window has not passed — this replaces
// per-request network calls back to Identity.
//
#pragma once

#include <optional>
#include <string>

#include "turbo/RequestContext.h"

namespace turbo {

class ContextCodec {
  public:
    /// Sign a context into a TL-Context header value.
    static std::string encode(const RequestContext &ctx, const std::string &secret);

    /// Verify + parse a TL-Context header value. Returns std::nullopt (and fills
    /// `error` when provided) if the token is malformed, tampered or expired.
    static std::optional<RequestContext> decode(const std::string &headerValue,
                                                const std::string &secret,
                                                std::string *error = nullptr);

    // Exposed for reuse/testing.
    static std::string base64UrlEncode(const unsigned char *data, size_t len);
    static std::optional<std::string> base64UrlDecode(const std::string &in);
    static std::string hmacSha256(const std::string &data, const std::string &secret);
};

}  // namespace turbo
