#include <drogon/drogon.h>

#include "services/ProvisioningService.h"
#include "turbo/Health.h"
#include "turbo/filters/TrustedContextFilter.h"

// Anchor: force the linker to keep libturbo's TrustedContextFilter object file
// so its drogon auto-registration runs (static libraries drop unreferenced TUs).
static const turbo::TrustedContextFilter kTrustedContextFilterAnchor{};

int main() {
    drogon::app().loadConfigFile("../config.json");

    // Standard platform /health endpoint (used by the ApiGateway fan-out).
    turbo::registerHealthEndpoint("Provisioner", "0.1");

    drogon::app().registerBeginningAdvice([]() {
        auto &service = provisioner::ProvisioningService::instance();
        service.initFromConfig();
        drogon::async_run([&service]() -> drogon::Task<> {
            try {
                co_await service.ensureRegistry();
            } catch (const std::exception &e) {
                LOG_ERROR << "Tenant registry bootstrap failed (will retry lazily): "
                          << e.what();
            }
            co_return;
        });
    });

    drogon::app().run();
    return 0;
}
