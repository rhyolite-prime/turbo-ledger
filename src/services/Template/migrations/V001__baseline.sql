--
-- V001__baseline.sql — Template service baseline schema.
--
-- Fineract calls this entity a "UGD" (User Generated Document): a named,
-- reusable Mustache-style text template (used to render notification/report
-- bodies) plus an ordered list of "mappers" — the variable names the
-- template's merge step expects to be supplied with a value.
--
-- Scope decision (see IMPLEMENTATION_PLAN.md Phase 8 as-built notes): the
-- real Fineract "mapper" concept pulls live field values out of another
-- domain entity (a client, a loan, ...) by a declarative mapper key. No
-- inter-service RPC client exists in this codebase to fetch that data, so
-- "merge" here only substitutes values the caller supplies directly in the
-- merge request body — an honest, documented scope trim, not a silent
-- difference. Substitution uses "{{mapperKey}}" placeholders, a minimal
-- regex-based renderer (no mustache library is vendored in this project).
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
--

CREATE TABLE IF NOT EXISTS templates (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    name            varchar(200) NOT NULL,
    text            text NOT NULL,
    entity          varchar(100) NOT NULL,   -- e.g. "client", "loan", "savings", "generic"
    template_type   varchar(20) NOT NULL,    -- "EMAIL" | "SMS" | "DOCUMENT"
    created_at      timestamptz NOT NULL DEFAULT now(),
    updated_at      timestamptz NOT NULL DEFAULT now(),
    UNIQUE (name)
);

CREATE TABLE IF NOT EXISTS template_mappers (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    template_id     uuid NOT NULL REFERENCES templates(id) ON DELETE CASCADE,
    mapper_key      varchar(100) NOT NULL,
    mapper_order    int NOT NULL DEFAULT 0,
    created_at      timestamptz NOT NULL DEFAULT now(),
    UNIQUE (template_id, mapper_key)
);

CREATE INDEX IF NOT EXISTS idx_template_mappers_template_id ON template_mappers(template_id);

-- Seed a couple of illustrative templates so `GET /templates` and the merge
-- flow have something to demonstrate against out of the box.
INSERT INTO templates (name, text, entity, template_type) VALUES
    ('welcome-email', 'Dear {{firstName}}, welcome to {{organisationName}}! Your account number is {{accountNumber}}.', 'client', 'EMAIL'),
    ('payment-reminder-sms', 'Hi {{firstName}}, your payment of {{amount}} {{currency}} is due on {{dueDate}}.', 'loan', 'SMS')
ON CONFLICT (name) DO NOTHING;

INSERT INTO template_mappers (template_id, mapper_key, mapper_order)
    SELECT id, m.key, m.ord FROM templates t
    CROSS JOIN LATERAL (VALUES ('firstName', 0), ('organisationName', 1), ('accountNumber', 2)) AS m(key, ord)
    WHERE t.name = 'welcome-email'
ON CONFLICT DO NOTHING;

INSERT INTO template_mappers (template_id, mapper_key, mapper_order)
    SELECT id, m.key, m.ord FROM templates t
    CROSS JOIN LATERAL (VALUES ('firstName', 0), ('amount', 1), ('currency', 2), ('dueDate', 3)) AS m(key, ord)
    WHERE t.name = 'payment-reminder-sms'
ON CONFLICT DO NOTHING;
