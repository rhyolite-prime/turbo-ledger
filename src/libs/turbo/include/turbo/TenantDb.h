//
// Turbo Ledger platform library — tenant-scoped database access.
//
// Every service database hosts one Postgres schema per tenant ("t_<tenantId>").
// ALL SQL must run inside a transaction obtained from beginTenantTxn(), which
// pins search_path to the tenant schema for the lifetime of the transaction
// (SET LOCAL). Raw execSqlCoro on a bare client is forbidden by convention and
// flagged in CI.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <drogon/utils/coroutine.h>
#include <memory>
#include <string>

#include "turbo/RequestContext.h"

namespace turbo::db {

/// Quote a Postgres identifier ("t_acme" -> "\"t_acme\""). Throws on invalid chars.
std::string quoteIdentifier(const std::string &ident);

/// Begin a transaction bound to the tenant schema of `ctx`.
/// Throws std::invalid_argument for malformed tenant ids.
drogon::Task<std::shared_ptr<drogon::orm::Transaction>> beginTenantTxn(
    drogon::orm::DbClientPtr client, const RequestContext &ctx);

/// Same, for maintenance flows that only have a tenant id (jobs, provisioning).
drogon::Task<std::shared_ptr<drogon::orm::Transaction>> beginTenantTxn(
    drogon::orm::DbClientPtr client, const std::string &tenantId);

}  // namespace turbo::db
