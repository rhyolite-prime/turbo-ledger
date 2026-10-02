--
-- V001__baseline.sql — Notification service baseline schema.
--
-- Covers 6 Fineract resource groups: `notifications` (per-user inbox),
-- `sms` + `smscampaigns`, `email` (ad hoc + campaigns + SMTP config),
-- `reportmailingjobs` + `reportmailingjobrunhistory`.
--
-- Scope decision (see IMPLEMENTATION_PLAN.md Phase 8 as-built notes): real
-- SMS/email provider network dispatch is stubbed — creating a message or
-- activating a campaign queues a row with status PENDING and writes an
-- outbox event; no real network call ever flips it to SENT. This is a
-- pluggable-provider-interface placeholder, not a silent lie: an operator
-- can see every queued/sent/failed message and its status honestly
-- reflects "nothing was actually dispatched". Likewise `reportmailingjobs`
-- links a report by name/params only (the Reporting service, including its
-- `runreports` executor, is built later in this same phase) and a job
-- "run" is the same disclosed no-op pattern as HeartBeat's `jobs`.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
--

-- ---------------------------------------------------------------------------
-- notifications: per-user inbox
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS notifications (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    user_id         varchar(64) NOT NULL,     -- recipient (platform user id)
    actor_id        varchar(64),              -- who/what triggered it (nullable: system events)
    object_type     varchar(50) NOT NULL,     -- e.g. "loan", "client", "job"
    object_id       varchar(64),
    action          varchar(50) NOT NULL,     -- e.g. "created", "approved", "failed"
    content         text NOT NULL,
    is_read         boolean NOT NULL DEFAULT false,
    created_at      timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_notifications_user_id ON notifications(user_id, is_read);

-- ---------------------------------------------------------------------------
-- sms / smscampaigns
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS sms_campaigns (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    campaign_name       varchar(200) NOT NULL,
    campaign_type       varchar(20) NOT NULL DEFAULT 'DIRECT',  -- DIRECT | SCHEDULE | TRIGGERED
    message             text NOT NULL,
    param_value         jsonb NOT NULL DEFAULT '{}'::jsonb,
    recurrence          varchar(100),
    next_trigger_date   timestamptz,
    status              varchar(20) NOT NULL DEFAULT 'PENDING', -- PENDING | ACTIVE | CLOSED
    provider_id         varchar(100),
    created_at          timestamptz NOT NULL DEFAULT now(),
    updated_at          timestamptz NOT NULL DEFAULT now(),
    UNIQUE (campaign_name)
);

CREATE TABLE IF NOT EXISTS sms_messages (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    campaign_id         uuid REFERENCES sms_campaigns(id) ON DELETE SET NULL,
    client_id           varchar(64),
    group_id            varchar(64),
    staff_id            varchar(64),
    mobile_no           varchar(32) NOT NULL,
    message             text NOT NULL,
    status              varchar(20) NOT NULL DEFAULT 'PENDING', -- PENDING | SENT | FAILED | UNDELIVERABLE
    provider_id         varchar(100),
    error_message       text,
    submitted_on_date   timestamptz,
    delivered_on_date   timestamptz,
    created_at          timestamptz NOT NULL DEFAULT now(),
    updated_at          timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_sms_messages_campaign_id ON sms_messages(campaign_id);
CREATE INDEX IF NOT EXISTS idx_sms_messages_status ON sms_messages(status);

-- ---------------------------------------------------------------------------
-- email / email campaigns / SMTP configuration
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS email_configuration (
    id              int PRIMARY KEY DEFAULT 1 CHECK (id = 1),  -- singleton row, like scheduler_state
    smtp_host       varchar(255),
    smtp_port       int NOT NULL DEFAULT 587,
    smtp_username   varchar(255),
    smtp_password   varchar(255),
    from_email      varchar(255),
    from_name       varchar(255),
    use_tls         boolean NOT NULL DEFAULT true,
    updated_at      timestamptz NOT NULL DEFAULT now()
);
INSERT INTO email_configuration (id) VALUES (1) ON CONFLICT (id) DO NOTHING;

CREATE TABLE IF NOT EXISTS email_campaigns (
    id                          uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    campaign_name               varchar(200) NOT NULL,
    subject                     varchar(255) NOT NULL,
    message                     text NOT NULL,
    param_value                 jsonb NOT NULL DEFAULT '{}'::jsonb,
    recurrence                  varchar(100),
    next_trigger_date           timestamptz,
    status                      varchar(20) NOT NULL DEFAULT 'PENDING', -- PENDING | ACTIVE | CLOSED
    attachment_file_format      varchar(10),  -- PDF | XLS | CSV
    stretchy_report_name        varchar(200),
    created_at                  timestamptz NOT NULL DEFAULT now(),
    updated_at                  timestamptz NOT NULL DEFAULT now(),
    UNIQUE (campaign_name)
);

CREATE TABLE IF NOT EXISTS email_messages (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    campaign_id     uuid REFERENCES email_campaigns(id) ON DELETE SET NULL,
    client_id       varchar(64),
    group_id        varchar(64),
    staff_id        varchar(64),
    email_address   varchar(255) NOT NULL,
    email_subject   varchar(255) NOT NULL,
    email_message   text NOT NULL,
    status          varchar(20) NOT NULL DEFAULT 'PENDING', -- PENDING | SENT | FAILED
    error_message   text,
    created_at      timestamptz NOT NULL DEFAULT now(),
    updated_at      timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_email_messages_campaign_id ON email_messages(campaign_id);
CREATE INDEX IF NOT EXISTS idx_email_messages_status ON email_messages(status);

-- ---------------------------------------------------------------------------
-- reportmailingjobs / reportmailingjobrunhistory
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS report_mailing_jobs (
    id                          uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    name                        varchar(200) NOT NULL,
    description                 text,
    report_name                 varchar(200) NOT NULL,
    report_params               jsonb NOT NULL DEFAULT '{}'::jsonb,
    start_date_time             timestamptz NOT NULL,
    recurrence                  varchar(100),
    email_recipients            text NOT NULL,  -- comma-separated list
    email_subject               varchar(255) NOT NULL,
    email_message               text,
    email_attachment_file_format varchar(10) NOT NULL DEFAULT 'PDF',  -- PDF | XLS | CSV
    is_active                   boolean NOT NULL DEFAULT true,
    previous_run_status         varchar(20),
    previous_run_error_message  text,
    previous_run_start_time     timestamptz,
    previous_run_end_time       timestamptz,
    next_run_time               timestamptz,
    created_at                  timestamptz NOT NULL DEFAULT now(),
    updated_at                  timestamptz NOT NULL DEFAULT now(),
    UNIQUE (name)
);

CREATE TABLE IF NOT EXISTS report_mailing_job_run_history (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    job_id          uuid NOT NULL REFERENCES report_mailing_jobs(id) ON DELETE CASCADE,
    start_time      timestamptz NOT NULL,
    end_time        timestamptz,
    status          varchar(20) NOT NULL,  -- COMPLETED | FAILED
    error_message   text,
    created_at      timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_report_mailing_job_run_history_job_id ON report_mailing_job_run_history(job_id);
