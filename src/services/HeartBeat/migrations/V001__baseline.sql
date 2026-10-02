--
-- V001__baseline.sql — Phase 8: HeartBeat (scheduler) baseline schema
-- (`jobs` 14 + `scheduler` 2 = 16 endpoints).
--
-- Fineract's "Scheduler" module: a catalog of named background jobs (the
-- real product runs interest posting, accruals, delinquency
-- classification, standing instructions, report mailing, etc. on a cron
-- schedule), plus per-run history and, in newer Fineract, a configurable
-- "business step" pipeline per Close-Of-Business-style job.
--
-- Scope decision (see IMPLEMENTATION_PLAN.md Phase 8 as-built notes): this
-- service provides the full admin API surface (job registry, run history,
-- manual/inline triggering, business-step configuration, scheduler
-- pause/resume) against durable Postgres-backed tables. It does **not**
-- implement an actual cron engine or cross-service job *execution* (there
-- is no inter-service RPC client in this codebase to call into
-- Accounting/Portfolio/DepositAccountManagement's real interest-posting /
-- accrual / delinquency logic) — "running" a job here records a
-- `job_run_history` row documenting the attempt rather than performing
-- real business work. Same class of deferred cross-service composition as
-- every prior phase's documented 501s / stubs, just surfaced here as an
-- honest no-op completion instead of a 501, since the *admin API* itself
-- (the actual Phase 8 scope) is fully real.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

CREATE TABLE IF NOT EXISTS jobs (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    short_name      varchar(100) NOT NULL UNIQUE,
    display_name    varchar(200) NOT NULL,
    description     text,
    cron_expression varchar(100),
    is_active       boolean DEFAULT true NOT NULL,
    is_misfired     boolean DEFAULT false NOT NULL,
    created_at      timestamptz DEFAULT now() NOT NULL,
    updated_at      timestamptz DEFAULT now() NOT NULL
);

CREATE TABLE IF NOT EXISTS job_run_history (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    job_id          uuid NOT NULL REFERENCES jobs(id) ON DELETE CASCADE,
    version         bigint NOT NULL,
    start_time      timestamptz NOT NULL,
    end_time        timestamptz,
    status          varchar(20) NOT NULL,
    trigger_type    varchar(20) NOT NULL,
    error_log       text,
    created_at      timestamptz DEFAULT now() NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_job_run_history_job_id ON job_run_history (job_id);

-- Business-step pipeline per job (Fineract's newer COB-style per-job step
-- configuration). One row per step; `is_enabled`/`step_order` are the
-- mutable "configured" state, the row's existence is what `available-steps`
-- reports (the full catalog), matching the fixed-catalog-but-configurable-
-- pipeline shape Fineract itself uses.
CREATE TABLE IF NOT EXISTS job_business_steps (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    job_id          uuid NOT NULL REFERENCES jobs(id) ON DELETE CASCADE,
    step_name       varchar(200) NOT NULL,
    step_order      integer NOT NULL,
    is_enabled      boolean DEFAULT true NOT NULL,
    created_at      timestamptz DEFAULT now() NOT NULL,
    updated_at      timestamptz DEFAULT now() NOT NULL,
    UNIQUE (job_id, step_name)
);

-- Single-row table: the global scheduler on/off switch. CHECK(id = 1)
-- enforces exactly one row (same single-row-table pattern as SystemConfig's
-- business-date override).
CREATE TABLE IF NOT EXISTS scheduler_state (
    id              integer PRIMARY KEY DEFAULT 1 CHECK (id = 1),
    is_active       boolean DEFAULT true NOT NULL,
    updated_at      timestamptz DEFAULT now() NOT NULL
);

INSERT INTO scheduler_state (id, is_active) VALUES (1, true)
    ON CONFLICT (id) DO NOTHING;

-- Seed the standard Fineract-style job catalog (illustrative short_name /
-- display_name / cron_expression — actual execution is deferred, see
-- header note above).
INSERT INTO jobs (short_name, display_name, description, cron_expression) VALUES
    ('interest-posting',          'Apply Interest To Savings',         'Posts accrued interest to all eligible savings accounts.', '0 0 23 * * ?'),
    ('loan-accrual',              'Add Accrual Transactions',          'Posts accrued interest/fee income for active loans.', '0 10 23 * * ?'),
    ('delinquency-classification','Loan Delinquency Classification',   'Re-classifies loan accounts into delinquency buckets.', '0 20 23 * * ?'),
    ('standing-instructions',     'Execute Standing Instructions',     'Runs due standing instruction transfers.', '0 30 0 * * ?'),
    ('report-mailing',            'Execute Report Mailing Jobs',       'Runs due report-mailing jobs and dispatches generated reports by email.', '0 0 6 * * ?'),
    ('update-npa',                'Update Non Performing Assets',      'Flags loan accounts crossing the configured overdue threshold.', '0 40 23 * * ?')
ON CONFLICT (short_name) DO NOTHING;

INSERT INTO job_business_steps (job_id, step_name, step_order)
    SELECT j.id, s.step_name, s.step_order
    FROM jobs j
    CROSS JOIN LATERAL (VALUES
        ('validate', 1),
        ('execute', 2),
        ('finalize', 3)
    ) AS s(step_name, step_order)
    WHERE j.short_name IN ('loan-accrual', 'delinquency-classification')
ON CONFLICT (job_id, step_name) DO NOTHING;
