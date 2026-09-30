#include "turbo/TenantDb.h"

#include <stdexcept>

namespace turbo::db {

std::string quoteIdentifier(const std::string &ident) {
    for (unsigned char c : ident) {
        if (!(std::isalnum(c) || c == '_'))
            throw std::invalid_argument("invalid SQL identifier: " + ident);
    }
    return "\"" + ident + "\"";
}

static drogon::Task<std::shared_ptr<drogon::orm::Transaction>> beginWithSchema(
    drogon::orm::DbClientPtr client, const std::string &tenantId) {
    if (!RequestContext::isValidTenantId(tenantId))
        throw std::invalid_argument("invalid tenant id: " + tenantId);
    auto txn = co_await client->newTransactionCoro();
    const std::string schema = quoteIdentifier("t_" + tenantId);
    // SET LOCAL scopes the search_path to this transaction only.
    co_await txn->execSqlCoro("SET LOCAL search_path TO " + schema + ", public");
    co_return txn;
}

drogon::Task<std::shared_ptr<drogon::orm::Transaction>> beginTenantTxn(
    drogon::orm::DbClientPtr client, const RequestContext &ctx) {
    co_return co_await beginWithSchema(std::move(client), ctx.tenantId);
}

drogon::Task<std::shared_ptr<drogon::orm::Transaction>> beginTenantTxn(
    drogon::orm::DbClientPtr client, const std::string &tenantId) {
    co_return co_await beginWithSchema(std::move(client), tenantId);
}

}  // namespace turbo::db
