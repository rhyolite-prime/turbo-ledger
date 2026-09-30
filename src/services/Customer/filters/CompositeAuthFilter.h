/**
 *
 *  CompositeAuthFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
#include "plugins/CustomerServicePlugin.h"

using namespace drogon;


class CompositeAuthFilter : public HttpFilter<CompositeAuthFilter>
{
  public:
    CompositeAuthFilter() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

