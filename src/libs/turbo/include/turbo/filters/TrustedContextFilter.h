//
// Turbo Ledger platform library — verifies the gateway-signed TL-Context header.
//
// Register on routes with "turbo::TrustedContextFilter". On success the parsed
// RequestContext is attached to the request (turbo::RequestContext::from(req)).
//
// Config (service config.json):
//   "custom_config": { "turbo": { "context_secret": "..." } }
//
#pragma once

#include <drogon/HttpFilter.h>

namespace turbo {

class TrustedContextFilter : public drogon::HttpFilter<TrustedContextFilter> {
  public:
    static constexpr const char *kName = "turbo::TrustedContextFilter";
    TrustedContextFilter() = default;
    void doFilter(const drogon::HttpRequestPtr &req,
                  drogon::FilterCallback &&fcb,
                  drogon::FilterChainCallback &&fccb) override;
};

}  // namespace turbo
