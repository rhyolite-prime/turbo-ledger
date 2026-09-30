//
// Turbo Ledger platform library — transactional outbox writer.
//
// Every committed business mutation writes an event row in the SAME
// transaction. A relay (HeartBeat job / EventHub) publishes rows later.
// Table `tl_outbox` is created by each service's V002__platform.sql migration.
//
#pragma once

#include <drogon/orm/DbClient.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <memory>
#include <string>

#include "turbo/RequestContext.h"

namespace turbo::outbox {

/// Insert an event into tl_outbox inside `txn` (which must be tenant-scoped).
/// eventType convention: "<aggregate>.<verb>" e.g. "glaccount.created".
drogon::Task<void> writeEvent(std::shared_ptr<drogon::orm::Transaction> txn,
                              const RequestContext &ctx,
                              const std::string &aggregateType,
                              const std::string &aggregateId,
                              const std::string &eventType,
                              const Json::Value &payload);

}  // namespace turbo::outbox
