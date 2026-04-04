#pragma once

#include <drogon/HttpFilter.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

namespace customer::filters
{
class JsonBodyFilter : public drogon::HttpFilter<JsonBodyFilter>
{
  public:
    JsonBodyFilter() {}
    void doFilter(const drogon::HttpRequestPtr &req,
                  drogon::FilterCallback &&fcb,
                  drogon::FilterChainCallback &&fccb) override;
};
} // namespace customer::filters
