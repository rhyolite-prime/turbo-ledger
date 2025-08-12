#include <drogon/drogon.h>
#include <string>
#include <drogon/HttpFilter.h>


class TenantFilter : public drogon::HttpFilter<TenantFilter> {
public:
    TenantFilter() = default;

    void doFilter(const drogon::HttpRequestPtr &req,
                 drogon::FilterCallback &&fcb,
                 drogon::FilterChainCallback &&fccb) override {
        // Try to get tenant information from different sources
        std::string tenantId;

        // Option 1: Check header (X-Tenant-ID)
        auto headers = req->headers();
        auto tenantHeader = headers.find("X-Tenant-ID");
        if (tenantHeader != headers.end()) {
            tenantId = tenantHeader->second;
        }

        // Option 2: Check subdomain (tenant1.example.com)
        if (tenantId.empty()) {
            const std::string &host = req->getHeader("Host");
            tenantId = extractTenantFromSubdomain(host);
        }

        // Option 3: Check path parameter (/api/v1/{tenant}/resources)
        if (tenantId.empty()) {
            tenantId = extractTenantFromPath(req->path());
        }

        // If we couldn't find tenant info, return error
        if (tenantId.empty()) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
            resp->setBody("Missing tenant information");
            fcb(resp);
            return;
        }

        // Validate tenant exists and is active
        if (!isValidTenant(tenantId)) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::HttpStatusCode::k403Forbidden);
            resp->setBody("Invalid or inactive tenant");
            fcb(resp);
            return;
        }

        // Store tenant ID in request attributes for controllers
        req->setParameter("tenantId", tenantId);

        // Continue to the next filter or handler
        fccb();
    }

private:
    std::string extractTenantFromSubdomain(const std::string &host) {
        // Extract first part of domain (tenant1.example.com -> tenant1)
        size_t pos = host.find('.');
        if (pos != std::string::npos) {
            return host.substr(0, pos);
        }
        return "";
    }

    std::string extractTenantFromPath(const std::string &path) {
        // Extract tenant from path segment
        // Example: /api/v1/{tenant}/resources
        std::vector<std::string> segments = splitPath(path);

        // Adjust index based on your URL structure
        if (segments.size() >= 3 && segments[0] == "api" && segments[1] == "v1") {
            return segments[2];
        }
        return "";
    }

    std::vector<std::string> splitPath(const std::string &path) {
        std::vector<std::string> segments;
        std::string segment;

        for (char c : path) {
            if (c == '/') {
                if (!segment.empty()) {
                    segments.push_back(segment);
                    segment.clear();
                }
            } else {
                segment += c;
            }
        }

        if (!segment.empty()) {
            segments.push_back(segment);
        }

        return segments;
    }

    bool isValidTenant(const std::string &tenantId) {
        // TODO: Implement tenant validation logic
        // This could query a database or cache to check if tenant exists and is active

        // Mock implementation for now
        return tenantId != "invalid" && tenantId != "inactive";
    }
};