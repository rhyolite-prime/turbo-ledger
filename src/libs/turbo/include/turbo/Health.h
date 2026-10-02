//
// Turbo Ledger platform library — standard /health endpoint.
//
// Call turbo::registerHealthEndpoint("Identity", "0.1") from main() before
// app().run(). The gateway's /health fan-out expects this shape:
//   { "service": "...", "version": "...", "status": "UP", "timeEpochMs": ... }
//
#pragma once

#include <string>

namespace turbo {

void registerHealthEndpoint(const std::string &serviceName, const std::string &version);

}  // namespace turbo
