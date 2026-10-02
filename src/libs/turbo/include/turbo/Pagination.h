//
// Turbo Ledger platform library — Fineract-style pagination & sorting.
//
// Query parameters: offset, limit, orderBy, sortOrder (ASC|DESC).
// Response envelope: { "totalFilteredRecords": N, "pageItems": [...] }
//
#pragma once

#include <drogon/HttpRequest.h>
#include <json/json.h>
#include <string>
#include <vector>

namespace turbo {

struct PageRequest {
    int offset{0};
    int limit{50};
    std::string orderBy;    ///< validated against a whitelist; empty = default
    bool descending{false};

    static constexpr int kMaxLimit = 200;

    /// Parse and clamp pagination params. `sortableColumns` is a whitelist of
    /// permitted orderBy values (SQL injection guard); anything else is dropped.
    static PageRequest fromRequest(const drogon::HttpRequestPtr &req,
                                   const std::vector<std::string> &sortableColumns = {},
                                   int defaultLimit = 50);

    /// " ORDER BY <col> <dir> LIMIT <n> OFFSET <m>" (orderBy already whitelisted).
    [[nodiscard]] std::string toSqlSuffix(const std::string &defaultOrderBy = "") const;
};

/// Build the Fineract paged envelope.
Json::Value pagedResult(std::int64_t totalFilteredRecords, Json::Value pageItems);

}  // namespace turbo
