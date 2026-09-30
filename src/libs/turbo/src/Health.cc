#include "turbo/Health.h"

#include <drogon/drogon.h>
#include <chrono>

namespace turbo {

void registerHealthEndpoint(const std::string &serviceName, const std::string &version) {
    drogon::app().registerHandler(
        "/health",
        [serviceName, version](const drogon::HttpRequestPtr &,
                               std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            Json::Value j;
            j["service"] = serviceName;
            j["version"] = version;
            j["status"] = "UP";
            j["timeEpochMs"] = static_cast<Json::Int64>(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count());
            auto resp = drogon::HttpResponse::newHttpJsonResponse(j);
            callback(resp);
        },
        {drogon::Get});
}

}  // namespace turbo
