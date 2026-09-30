#pragma once

#include <drogon/HttpFilter.h>
#include "plugins/CustomerServicePlugin.h"

using namespace drogon;

class ApiKeyAuthFilter : public HttpFilter<ApiKeyAuthFilter>
{
  public:
    ApiKeyAuthFilter() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};
