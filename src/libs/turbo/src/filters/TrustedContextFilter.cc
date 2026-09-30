#include "turbo/filters/TrustedContextFilter.h"

#include <drogon/drogon.h>

#include "turbo/ApiResponse.h"
#include "turbo/ContextCodec.h"
#include "turbo/RequestContext.h"

namespace turbo {

void TrustedContextFilter::doFilter(const drogon::HttpRequestPtr &req,
                                    drogon::FilterCallback &&fcb,
                                    drogon::FilterChainCallback &&fccb) {
    if (req->getMethod() == drogon::Options) {  // CORS preflight
        fccb();
        return;
    }

    const auto header = req->getHeader(RequestContext::kHeaderName);
    if (header.empty()) {
        fcb(ApiResponse::httpUnauthorized("Missing TL-Context header (requests must come "
                                          "through the API gateway)"));
        return;
    }

    const auto &config = drogon::app().getCustomConfig();
    const std::string secret = config["turbo"]["context_secret"].asString();

    std::string error;
    auto ctx = ContextCodec::decode(header, secret, &error);
    if (!ctx) {
        LOG_WARN << "TL-Context rejected: " << error;
        fcb(ApiResponse::httpUnauthorized("Invalid TL-Context: " + error));
        return;
    }

    ctx->attachTo(req);
    fccb();
}

}  // namespace turbo
