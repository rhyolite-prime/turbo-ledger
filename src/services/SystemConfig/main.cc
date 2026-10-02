#include <drogon/drogon.h>

#include "turbo/Health.h"
#include "turbo/filters/TrustedContextFilter.h"

// Anchor: force the linker to keep libturbo's TrustedContextFilter object file
// so its drogon auto-registration runs (static libraries drop unreferenced TUs).
static const turbo::TrustedContextFilter kTrustedContextFilterAnchor{};

int main() {
    // Load config file
    drogon::app().loadConfigFile("../config.json");

    // Standard platform /health endpoint (used by the ApiGateway fan-out).
    turbo::registerHealthEndpoint("SystemConfig", "0.1");

    drogon::app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            const std::vector<std::string> allowedOrigins = {
                "http://localhost:7501", "http://localhost:7502", "http://localhost:7503",
                "http://localhost:7504", "http://localhost:7505", "http://localhost:7506",
                "http://localhost:7507", "http://localhost:7508"};

            auto origin = req->getHeader("Origin");
            if (std::find(allowedOrigins.begin(), allowedOrigins.end(), origin) !=
                allowedOrigins.end()) {
                resp->addHeader("Access-Control-Allow-Origin", origin);
                resp->addHeader("Access-Control-Allow-Credentials", "true");
            }
            resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            resp->addHeader("Access-Control-Allow-Headers",
                            "Content-Type, Authorization, Referer, User-Agent, Accept, "
                            "X-Requested-With, Origin");
        });

    // Run HTTP framework, the method will block in the internal event loop.
    drogon::app().run();
    return 0;
}
