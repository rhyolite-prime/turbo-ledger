//
// Turbo Ledger platform library — id generation.
//
#pragma once

#include <string>

namespace turbo::ids {

/// Random UUID v4 (lowercase, dashed).
std::string newUuid();

/// Sortable correlation id: "<unix-millis-hex>-<random-hex>", e.g. "18f2c3a9b21-9f31d2c4".
std::string newRequestId();

}  // namespace turbo::ids
