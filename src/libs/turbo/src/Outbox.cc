#include "turbo/Outbox.h"

#include "turbo/Ids.h"

namespace turbo::outbox {

drogon::Task<void> writeEvent(std::shared_ptr<drogon::orm::Transaction> txn,
                              const RequestContext &ctx,
                              const std::string &aggregateType,
                              const std::string &aggregateId,
                              const std::string &eventType,
                              const Json::Value &payload) {
    Json::StreamWriterBuilder w;
    w["indentation"] = "";
    const std::string payloadStr = Json::writeString(w, payload);

    co_await txn->execSqlCoro(
        "INSERT INTO tl_outbox (id, tenant_id, aggregate_type, aggregate_id, event_type, "
        "payload, request_id, actor_user_id, occurred_at) "
        "VALUES ($1, $2, $3, $4, $5, $6::jsonb, $7, $8, now())",
        ids::newUuid(), ctx.tenantId, aggregateType, aggregateId, eventType, payloadStr,
        ctx.requestId, ctx.userId);
    co_return;
}

}  // namespace turbo::outbox
