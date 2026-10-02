--
-- V003__phase2_reference_data.sql — Phase 2: SystemConfig platform tables.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent.
--

-- ---------------------------------------------------------------------------
-- codes / code values — Fineract-parity default reference-data catalog so a
-- brand-new tenant never starts with an empty picklist set.
-- ---------------------------------------------------------------------------
INSERT INTO code (code_name, is_system_defined) VALUES
    ('ClientType', true),
    ('ClientClassification', true),
    ('Gender', true),
    ('MaritalStatus', true),
    ('AddressType', true),
    ('IdentifierType', true),
    ('LoanCollateral', true),
    ('LoanPurpose', true),
    ('YesNo', true)
ON CONFLICT (code_name) DO NOTHING;

INSERT INTO code_value (code_id, code_value, order_position, is_active)
    SELECT c.id, v.code_value, v.order_position, true
    FROM code c
    JOIN (VALUES
        ('Gender', 'Male', 1), ('Gender', 'Female', 2), ('Gender', 'Other', 3),
        ('MaritalStatus', 'Single', 1), ('MaritalStatus', 'Married', 2),
        ('MaritalStatus', 'Divorced', 3), ('MaritalStatus', 'Widowed', 4),
        ('ClientType', 'Individual', 1), ('ClientType', 'Corporate', 2),
        ('ClientClassification', 'Standard', 1), ('ClientClassification', 'High Value', 2),
        ('AddressType', 'Residential', 1), ('AddressType', 'Business', 2), ('AddressType', 'Postal', 3),
        ('IdentifierType', 'Passport', 1), ('IdentifierType', 'National ID', 2), ('IdentifierType', 'Driving License', 3),
        ('LoanCollateral', 'Real Estate', 1), ('LoanCollateral', 'Vehicle', 2), ('LoanCollateral', 'None', 3),
        ('LoanPurpose', 'Business', 1), ('LoanPurpose', 'Education', 2), ('LoanPurpose', 'Housing', 3), ('LoanPurpose', 'Personal', 4),
        ('YesNo', 'Yes', 1), ('YesNo', 'No', 2)
    ) AS v(code_name, code_value, order_position) ON v.code_name = c.code_name
    ON CONFLICT (code_id, code_value) DO NOTHING;

-- ---------------------------------------------------------------------------
-- global configuration
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS configuration (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    name          varchar(100) NOT NULL UNIQUE,
    value         varchar(500),
    date_value    date,
    is_enabled    boolean     NOT NULL DEFAULT false,
    description   varchar(500),
    modified_at   timestamptz NOT NULL DEFAULT now()
);
INSERT INTO configuration (name, value, is_enabled, description) VALUES
    ('maker-checker',                        NULL, false, 'Require maker-checker approval for guarded actions'),
    ('amazon-S3',                            NULL, false, 'Store documents/images in Amazon S3 instead of the database'),
    ('organisation-start-date',              NULL, false, 'Earliest business date the platform will accept postings for'),
    ('reschedule-future-repayments',         NULL, true,  'Automatically reschedule repayments that fall on a non-working day'),
    ('savings-interest-posting-current-period', NULL, true, 'Post savings interest into the current period'),
    ('password-expires-days',                '90', false, 'Number of days after which a user password expires'),
    ('min-clients-in-group',                 '1',  false, 'Minimum number of clients required in a group'),
    ('max-clients-in-group',                 '50', false, 'Maximum number of clients allowed in a group')
ON CONFLICT (name) DO NOTHING;

-- ---------------------------------------------------------------------------
-- external service configuration (e.g. SMS/email/object-storage providers)
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS external_service (
    service_name  varchar(100) PRIMARY KEY,
    config        jsonb       NOT NULL DEFAULT '{}'::jsonb,
    modified_at   timestamptz NOT NULL DEFAULT now()
);

-- ---------------------------------------------------------------------------
-- hooks (webhook configuration — firing arrives with EventHub, Phase 10)
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS hook (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    name          varchar(100) NOT NULL,
    display_name  varchar(100) NOT NULL,
    is_active     boolean     NOT NULL DEFAULT true,
    config        jsonb       NOT NULL DEFAULT '{}'::jsonb,
    events        jsonb       NOT NULL DEFAULT '[]'::jsonb,
    created_at    timestamptz NOT NULL DEFAULT now(),
    modified_at   timestamptz NOT NULL DEFAULT now()
);

-- ---------------------------------------------------------------------------
-- caches
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS cache_config (
    id            int PRIMARY KEY DEFAULT 1,
    cache_type    varchar(20) NOT NULL DEFAULT 'NO_CACHE',
    modified_at   timestamptz NOT NULL DEFAULT now(),
    CONSTRAINT chk_cache_config_singleton CHECK (id = 1),
    CONSTRAINT chk_cache_type CHECK (cache_type IN ('NO_CACHE', 'SINGLE_NODE', 'DISTRIBUTED'))
);
INSERT INTO cache_config (id) VALUES (1) ON CONFLICT (id) DO NOTHING;

-- ---------------------------------------------------------------------------
-- business date
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS business_date (
    type          varchar(30) PRIMARY KEY,
    date_value    date        NOT NULL,
    modified_at   timestamptz NOT NULL DEFAULT now()
);
INSERT INTO business_date (type, date_value) VALUES
    ('BUSINESS_DATE', CURRENT_DATE),
    ('COB_DATE', CURRENT_DATE)
ON CONFLICT (type) DO NOTHING;

-- ---------------------------------------------------------------------------
-- external events posting configuration
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS external_event_configuration (
    category      varchar(60) PRIMARY KEY,
    is_enabled    boolean     NOT NULL DEFAULT false,
    modified_at   timestamptz NOT NULL DEFAULT now()
);
INSERT INTO external_event_configuration (category, is_enabled) VALUES
    ('ALL', false),
    ('CLIENT', false),
    ('LOAN', false),
    ('SAVINGS', false),
    ('PAYMENT', false)
ON CONFLICT (category) DO NOTHING;

-- ---------------------------------------------------------------------------
-- entity field configuration
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS field_configuration (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    entity        varchar(60) NOT NULL,
    field_name    varchar(100) NOT NULL,
    is_enabled    boolean     NOT NULL DEFAULT true,
    is_mandatory  boolean     NOT NULL DEFAULT false,
    validation_regex varchar(255),
    CONSTRAINT uq_field_configuration UNIQUE (entity, field_name)
);
INSERT INTO field_configuration (entity, field_name, is_enabled, is_mandatory) VALUES
    ('client', 'externalId', true, false),
    ('client', 'mobileNo',   true, false),
    ('client', 'dateOfBirth', true, false),
    ('loan',   'externalId', true, false)
ON CONFLICT DO NOTHING;

-- ---------------------------------------------------------------------------
-- datatables engine — registry of dynamically created tables (physical
-- tables are named dt_<datatableName>, created/altered/dropped by the
-- DataTableService with strict identifier validation).
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS tl_datatable_registry (
    datatable_name    varchar(60) PRIMARY KEY,
    apptable_name      varchar(60) NOT NULL,
    category           int         NOT NULL DEFAULT 0,
    is_multi_row       boolean     NOT NULL DEFAULT true,
    columns            jsonb       NOT NULL DEFAULT '[]'::jsonb,
    created_at         timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_tl_datatable_registry_apptable
    ON tl_datatable_registry (apptable_name);

CREATE TABLE IF NOT EXISTS tl_entity_datatable_check (
    id              uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    entity          varchar(60) NOT NULL,
    status_code     varchar(60) NOT NULL,
    datatable_name  varchar(60) NOT NULL,
    product_id      varchar(80),
    created_at      timestamptz NOT NULL DEFAULT now(),
    CONSTRAINT uq_entity_datatable_check UNIQUE (entity, status_code, datatable_name, product_id)
);

-- ---------------------------------------------------------------------------
-- imports (bulk import job history — upload endpoints live per-entity)
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS tl_import_document (
    id                uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    entity_type       varchar(60) NOT NULL,
    file_name         varchar(255) NOT NULL,
    import_time       timestamptz NOT NULL DEFAULT now(),
    end_time          timestamptz,
    total_records     int         NOT NULL DEFAULT 0,
    successful_count  int         NOT NULL DEFAULT 0,
    failed_count      int         NOT NULL DEFAULT 0,
    status            varchar(20) NOT NULL DEFAULT 'PENDING',
    created_by        varchar(64),
    CONSTRAINT chk_import_status CHECK (status IN ('PENDING', 'RUNNING', 'COMPLETED', 'FAILED'))
);

-- ---------------------------------------------------------------------------
-- generic entity attachments: documents, notes, images, calendars, meetings
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS tl_document (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    entity_type   varchar(60) NOT NULL,
    entity_id     varchar(80) NOT NULL,
    name          varchar(255) NOT NULL,
    file_name     varchar(255) NOT NULL,
    content_type  varchar(120),
    description   varchar(500),
    size_bytes    bigint      NOT NULL DEFAULT 0,
    content       bytea,
    created_by    varchar(64),
    created_at    timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_tl_document_entity ON tl_document (entity_type, entity_id);

CREATE TABLE IF NOT EXISTS tl_note (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    resource_type varchar(60) NOT NULL,
    resource_id   varchar(80) NOT NULL,
    note          text        NOT NULL,
    created_by    varchar(64),
    created_at    timestamptz NOT NULL DEFAULT now(),
    modified_at   timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_tl_note_resource ON tl_note (resource_type, resource_id);

CREATE TABLE IF NOT EXISTS tl_image (
    entity_type   varchar(60) NOT NULL,
    entity_id     varchar(80) NOT NULL,
    content_type  varchar(120),
    content       bytea       NOT NULL,
    modified_at   timestamptz NOT NULL DEFAULT now(),
    PRIMARY KEY (entity_type, entity_id)
);

CREATE TABLE IF NOT EXISTS tl_calendar (
    id             uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    entity_type    varchar(60) NOT NULL,
    entity_id      varchar(80) NOT NULL,
    title          varchar(150) NOT NULL,
    description    varchar(500),
    location       varchar(255),
    start_date     date        NOT NULL,
    end_date       date,
    calendar_type  varchar(30) NOT NULL DEFAULT 'COLLECTION',
    recurrence     varchar(120),
    remind_by_days int,
    created_at     timestamptz NOT NULL DEFAULT now(),
    modified_at    timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_tl_calendar_entity ON tl_calendar (entity_type, entity_id);

CREATE TABLE IF NOT EXISTS tl_meeting (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    entity_type   varchar(60) NOT NULL,
    entity_id     varchar(80) NOT NULL,
    calendar_id   uuid REFERENCES tl_calendar (id) ON DELETE SET NULL,
    meeting_date  date        NOT NULL,
    notes         text,
    status        varchar(20) NOT NULL DEFAULT 'SCHEDULED',
    created_at    timestamptz NOT NULL DEFAULT now(),
    modified_at   timestamptz NOT NULL DEFAULT now(),
    CONSTRAINT chk_meeting_status CHECK (status IN ('SCHEDULED', 'HELD', 'CANCELLED'))
);
CREATE INDEX IF NOT EXISTS idx_tl_meeting_entity ON tl_meeting (entity_type, entity_id);
