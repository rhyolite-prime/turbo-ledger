//
// Matches the identical helper carried by every other Turbo Ledger service
// (see e.g. src/services/Accounting/utils/codecvt_helper.h) — forced in via
// -include so <codecvt>/<locale> are available ahead of Drogon's own headers.
//
#pragma once
#include <codecvt>
#include <locale>
