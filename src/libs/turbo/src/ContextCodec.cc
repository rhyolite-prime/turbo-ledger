#include "turbo/ContextCodec.h"

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <json/json.h>
#include <chrono>
#include <cstring>
#include <memory>

namespace turbo {

namespace {

constexpr char kB64UrlChars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

int b64UrlIndex(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '-' || c == '+') return 62;
    if (c == '_' || c == '/') return 63;
    return -1;
}

bool constantTimeEquals(const std::string &a, const std::string &b) {
    if (a.size() != b.size()) return false;
    unsigned char diff = 0;
    for (size_t i = 0; i < a.size(); ++i)
        diff |= static_cast<unsigned char>(a[i]) ^ static_cast<unsigned char>(b[i]);
    return diff == 0;
}

std::int64_t nowEpoch() {
    return std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

}  // namespace

std::string ContextCodec::base64UrlEncode(const unsigned char *data, size_t len) {
    std::string out;
    out.reserve(((len + 2) / 3) * 4);
    for (size_t i = 0; i < len; i += 3) {
        unsigned v = data[i] << 16;
        if (i + 1 < len) v |= data[i + 1] << 8;
        if (i + 2 < len) v |= data[i + 2];
        out.push_back(kB64UrlChars[(v >> 18) & 0x3F]);
        out.push_back(kB64UrlChars[(v >> 12) & 0x3F]);
        if (i + 1 < len) out.push_back(kB64UrlChars[(v >> 6) & 0x3F]);
        if (i + 2 < len) out.push_back(kB64UrlChars[v & 0x3F]);
    }
    return out;  // no padding
}

std::optional<std::string> ContextCodec::base64UrlDecode(const std::string &in) {
    std::string out;
    out.reserve((in.size() / 4) * 3 + 3);
    int buffer = 0, bits = 0;
    for (char c : in) {
        if (c == '=') break;
        int idx = b64UrlIndex(c);
        if (idx < 0) return std::nullopt;
        buffer = (buffer << 6) | idx;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out.push_back(static_cast<char>((buffer >> bits) & 0xFF));
        }
    }
    return out;
}

std::string ContextCodec::hmacSha256(const std::string &data, const std::string &secret) {
    unsigned char mac[EVP_MAX_MD_SIZE];
    unsigned int macLen = 0;
    HMAC(EVP_sha256(), secret.data(), static_cast<int>(secret.size()),
         reinterpret_cast<const unsigned char *>(data.data()), data.size(), mac, &macLen);
    return std::string(reinterpret_cast<char *>(mac), macLen);
}

std::string ContextCodec::encode(const RequestContext &ctx, const std::string &secret) {
    Json::StreamWriterBuilder w;
    w["indentation"] = "";
    const std::string payload = Json::writeString(w, ctx.toJson());
    const std::string payloadB64 =
        base64UrlEncode(reinterpret_cast<const unsigned char *>(payload.data()), payload.size());
    const std::string toSign = "v1." + payloadB64;
    const std::string mac = hmacSha256(toSign, secret);
    return toSign + "." +
           base64UrlEncode(reinterpret_cast<const unsigned char *>(mac.data()), mac.size());
}

std::optional<RequestContext> ContextCodec::decode(const std::string &headerValue,
                                                   const std::string &secret,
                                                   std::string *error) {
    auto fail = [&](const char *why) -> std::optional<RequestContext> {
        if (error) *error = why;
        return std::nullopt;
    };
    if (secret.empty()) return fail("context secret not configured");

    const auto firstDot = headerValue.find('.');
    const auto lastDot = headerValue.rfind('.');
    if (firstDot == std::string::npos || lastDot == firstDot)
        return fail("malformed context token");
    if (headerValue.substr(0, firstDot) != "v1") return fail("unsupported context version");

    const std::string toSign = headerValue.substr(0, lastDot);
    const std::string sigB64 = headerValue.substr(lastDot + 1);
    const std::string expected = hmacSha256(toSign, secret);
    const std::string expectedB64 =
        base64UrlEncode(reinterpret_cast<const unsigned char *>(expected.data()), expected.size());
    if (!constantTimeEquals(sigB64, expectedB64)) return fail("bad context signature");

    const auto payloadRaw =
        base64UrlDecode(headerValue.substr(firstDot + 1, lastDot - firstDot - 1));
    if (!payloadRaw) return fail("bad context payload encoding");

    Json::CharReaderBuilder rb;
    Json::Value json;
    std::string errs;
    std::unique_ptr<Json::CharReader> reader(rb.newCharReader());
    if (!reader->parse(payloadRaw->data(), payloadRaw->data() + payloadRaw->size(), &json, &errs))
        return fail("bad context payload json");

    auto ctx = RequestContext::fromJson(json);
    if (!ctx) return fail("invalid context payload");
    if (ctx->expiresAtEpoch > 0 && nowEpoch() > ctx->expiresAtEpoch)
        return fail("context expired");
    return ctx;
}

}  // namespace turbo
