//
// Turbo Ledger — ApiGateway
//
// Single public entrypoint for the platform:
//   * resolves the tenant (TL-Tenant-Id) against the tenant registry
//   * authenticates the caller (JWT / API keys) once at the edge
//   * signs an internal TL-Context header trusted by all services
//   * request ids, CORS, rate limiting, Idempotency-Key replay
//   * /health fan-out across every registered service
//
#include <drogon/drogon.h>

#include "src/GatewayCore.h"

int main() {
    drogon::app().loadConfigFile("../config.json");

    // Gateway health + route table (registered handlers win over the default
    // proxy handler below).
    drogon::app().registerHandler(
        "/health",
        [](const drogon::HttpRequestPtr &,
           std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            drogon::async_run([cb = std::move(callback)]() mutable -> drogon::Task<> {
                auto resp = co_await gateway::core().healthFanOut();
                cb(resp);
                co_return;
            });
        },
        {drogon::Get});

    drogon::app().registerHandler(
        "/gateway/routes",
        [](const drogon::HttpRequestPtr &,
           std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            callback(gateway::core().describeRoutes());
        },
        {drogon::Get});

    // Everything else is proxied.
    drogon::app().setDefaultHandler(
        [](const drogon::HttpRequestPtr &req,
           std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            gateway::core().handle(req, std::move(callback));
        });

    drogon::app().registerBeginningAdvice([]() { gateway::core().initFromAppConfig(); });

    drogon::app().run();
    return 0;
}
