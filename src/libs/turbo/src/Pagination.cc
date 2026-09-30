#include "turbo/Pagination.h"

#include <algorithm>

namespace turbo {

PageRequest PageRequest::fromRequest(const drogon::HttpRequestPtr &req,
                                     const std::vector<std::string> &sortableColumns,
                                     int defaultLimit) {
    PageRequest page;
    page.limit = defaultLimit;

    auto getInt = [&](const char *name, int fallback) {
        auto v = req->getParameter(name);
        if (v.empty()) return fallback;
        try {
            return std::stoi(v);
        } catch (...) {
            return fallback;
        }
    };

    page.offset = std::max(0, getInt("offset", 0));
    page.limit = std::clamp(getInt("limit", defaultLimit), 1, kMaxLimit);

    auto orderBy = req->getParameter("orderBy");
    if (!orderBy.empty() &&
        std::find(sortableColumns.begin(), sortableColumns.end(), orderBy) !=
            sortableColumns.end()) {
        page.orderBy = orderBy;
    }

    auto sortOrder = req->getParameter("sortOrder");
    std::transform(sortOrder.begin(), sortOrder.end(), sortOrder.begin(), ::toupper);
    page.descending = (sortOrder == "DESC");
    return page;
}

std::string PageRequest::toSqlSuffix(const std::string &defaultOrderBy) const {
    std::string sql;
    const std::string &col = orderBy.empty() ? defaultOrderBy : orderBy;
    if (!col.empty()) {
        sql += " ORDER BY " + col + (descending ? " DESC" : " ASC");
    }
    sql += " LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset);
    return sql;
}

Json::Value pagedResult(std::int64_t totalFilteredRecords, Json::Value pageItems) {
    Json::Value out;
    out["totalFilteredRecords"] = static_cast<Json::Int64>(totalFilteredRecords);
    out["pageItems"] = std::move(pageItems);
    return out;
}

}  // namespace turbo
