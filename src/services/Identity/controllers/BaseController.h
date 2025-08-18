#pragma once

#include <drogon/HttpController.h>

// A base class for controllers that need access to common request data, like the tenant ID.
template <typename T>
class BaseController : public drogon::HttpController<T>
{
  protected:
    // Helper method to get the tenant ID that was set by the TenantFilter.
    // It throws an exception if the tenant ID is not found, as this should not happen
    // if the filter is configured correctly.
    static std::string getTenantFromRequest(const drogon::HttpRequestPtr& req)
    {
        const auto& tenantId = req->getHeader("X-Tenant-ID");
        if (!tenantId.empty()) {
            return tenantId;
        }
        throw std::runtime_error("Invalid Tenant Identifier !");
    }
};
