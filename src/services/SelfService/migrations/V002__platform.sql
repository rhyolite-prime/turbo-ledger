--
-- V002__platform.sql — Turbo Ledger platform tables (per tenant schema).
--
-- tl_outbox: transactional outbox. Every business mutation inserts an event
-- row in the same transaction (turbo::outbox::writeEvent). A relay publishes
-- rows to the event bus and marks them published.
--
-- Identical copy of every other service's V00x__platform.sql (Accounting,
-- Customer, DepositAccountManagement, Portfolio, Group, Notification, ...).
--

CREATE TABLE IF NOT EXISTS tl_outbox (
    id              UUID PRIMARY KEY,
    tenant_id       VARCHAR(40)  NOT NULL,
    aggregate_type  VARCHAR(80)  NOT NULL,
    aggregate_id    VARCHAR(80)  NOT NULL,
    event_type      VARCHAR(120) NOT NULL,
    payload         JSONB        NOT NULL DEFAULT '{}'::jsonb,
    request_id      VARCHAR(64),
    actor_user_id   VARCHAR(64),
    occurred_at     TIMESTAMPTZ  NOT NULL DEFAULT now(),
    published_at    TIMESTAMPTZ
);

CREATE INDEX IF NOT EXISTS idx_tl_outbox_unpublished
    ON tl_outbox (occurred_at) WHERE published_at IS NULL;
CREATE INDEX IF NOT EXISTS idx_tl_outbox_aggregate
    ON tl_outbox (aggregate_type, aggregate_id);
