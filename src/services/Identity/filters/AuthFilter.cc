#include <drogon/drogon.h>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>
#include <drogon/HttpFilter.h>

class AuthFilter : public drogon::HttpFilter<AuthFilter> {
public:
    AuthFilter() = default;

    void doFilter(const drogon::HttpRequestPtr &req,
                 drogon::FilterCallback &&fcb,
                 drogon::FilterChainCallback &&fccb) override {
        // Check for Authorization header
        const auto &headers = req->headers();
        auto authHeader = headers.find("Authorization");
        if (authHeader == headers.end() || authHeader->second.find("Bearer ") != 0) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
            resp->setBody("Missing or invalid authorization header");
            fcb(resp);
            return;
        }

        // Extract the token
        std::string token = authHeader->second.substr(7); // Remove "Bearer " prefix

        try {
            // Verify token
            // Note: Replace "your_secret_key" with your actual secret key from config
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{"your_secret_key"});

            auto decoded = jwt::decode(token);
            verifier.verify(decoded);

            // Extract payload claims for permission checking
            auto payload = decoded.get_payload_json();

            // Store user info in request attributes for controllers to use
            if (payload.contains("user_id")) {
                req->setParameter("user_id", payload["user_id"].get<std::string>());
            }

            // Check permissions
            // This example checks if the user has the required permission for this path
            if (payload.contains("permissions")) {
                auto permissions = payload["permissions"];
                std::string requiredPermission = getRequiredPermissionForPath(req->path());

                if (!hasPermission(permissions, requiredPermission)) {
                    auto resp = drogon::HttpResponse::newHttpResponse();
                    resp->setStatusCode(drogon::HttpStatusCode::k403Forbidden);
                    resp->setBody("Insufficient permissions");
                    fcb(resp);
                    return;
                }
            }

            // JWT is valid and permissions are sufficient, continue to the next filter or handler
            fccb();

        } catch (const std::exception &e) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);
            resp->setBody(std::string("Invalid token: ") + e.what());
            fcb(resp);
            return;
        }
    }

private:
    // Helper method to determine required permission for a given path
    std::string getRequiredPermissionForPath(const std::string &path) {
        // This is a simple example; in a real application, you might have
        // a more sophisticated mapping of paths to required permissions
        if (path.find("/admin") == 0) {
            return "admin";
        } else if (path.find("/api/users") == 0) {
            return "users:read";
        } else if (path.find("/api/posts") == 0) {
            return "posts:read";
        }
        return "basic";
    }

    // Helper method to check if a user has a specific permission
    // Helper method to check if a user has a specific permission
    bool hasPermission(const picojson::value &permissions, const std::string &requiredPermission) {
        if (permissions.is<picojson::array>()) {
            const auto &permArray = permissions.get<picojson::array>();
            for (const auto &permission : permArray) {
                if (permission.is<std::string>() &&
                    permission.get<std::string>() == requiredPermission) {
                    return true;
                }
            }
        }
        return false;
    }
};