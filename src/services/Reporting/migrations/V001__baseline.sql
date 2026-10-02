--
-- V001__baseline.sql — Reporting service baseline (per tenant schema).
--
-- Reporting owns a small, generic report-definition catalog (Fineract-style
-- "generic" report engine) rather than one table per report. Each row in
-- report_definitions is a named, parameterized SQL SELECT that is executed
-- against exactly one other service's own tenant schema (report_definitions
-- never joins across services in-engine — see ReportingService.cc).
--
-- Hand-authored (no live Postgres available in this workspace to generate a
-- baseline dump from, same situation already documented for Organization's
-- V003 models) — kept intentionally small and dependency-free.
--
-- Applied per tenant into schema t_<tenantId> by the Provisioner service /
-- src/tools/migrate.py (both pin search_path; do NOT add SET search_path
-- here).
--

CREATE TABLE report_definitions (
    id               uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    report_name      character varying(100) NOT NULL,
    report_category  character varying(60) NOT NULL,
    -- data_source selects which read-only named Drogon db_client this report
    -- runs against: identity | accounting | customer | organization |
    -- portfolio | depositaccountmanagement. Validated against that allow-list
    -- in ReportingService, not by a DB constraint, so new sources can be
    -- added without a migration.
    data_source      character varying(60) NOT NULL,
    -- report_sql is a single read-only SELECT containing ${paramName} tokens;
    -- the engine replaces each token with a bound positional placeholder
    -- ($1, $2, ...) — never string interpolation — before executing it
    -- inside a read-only, statement-timeout-guarded transaction on the
    -- resolved data_source client. Column aliases in the SELECT list become
    -- the JSON keys of each result row, so report authors must alias every
    -- computed/joined column (e.g. SELECT a.gl_code AS "glCode").
    report_sql       text NOT NULL,
    description      character varying(500),
    -- is_core protects the seeded catalog (V003) from deletion; core reports
    -- can still be edited (e.g. to tune SQL) but not removed.
    is_core          boolean NOT NULL DEFAULT false,
    is_active        boolean NOT NULL DEFAULT true,
    created_by       uuid,
    created_at       timestamptz NOT NULL DEFAULT now(),
    updated_by       uuid,
    updated_at       timestamptz NOT NULL DEFAULT now(),
    CONSTRAINT uq_report_definitions_name UNIQUE (report_name)
);

CREATE TABLE report_parameters (
    id               uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    report_id        uuid NOT NULL REFERENCES report_definitions(id) ON DELETE CASCADE,
    -- parameter_name must match a ${parameter_name} token in the owning
    -- report's report_sql, camelCase by convention (e.g. "asOfDate").
    parameter_name   character varying(60) NOT NULL,
    parameter_label  character varying(120) NOT NULL,
    -- parameter_type is used for light input validation only (STRING | DATE
    -- | NUMBER); the SQL template itself is responsible for casting the
    -- bound text value to the right Postgres type (e.g. ${asOfDate}::date).
    parameter_type   character varying(20) NOT NULL DEFAULT 'STRING',
    is_mandatory     boolean NOT NULL DEFAULT true,
    default_value    character varying(200),
    display_order    integer NOT NULL DEFAULT 0,
    CONSTRAINT uq_report_parameters_report_name UNIQUE (report_id, parameter_name)
);

CREATE INDEX idx_report_parameters_report_id ON report_parameters (report_id);
CREATE INDEX idx_report_definitions_category ON report_definitions (report_category);
CREATE INDEX idx_report_definitions_data_source ON report_definitions (data_source);
