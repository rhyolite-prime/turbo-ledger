--
-- V003__phase2_reference_data.sql — Phase 2: Organization reference-data layer.
--
-- Adds the tables needed for offices (hierarchy + lifecycle already present
-- from the V001 baseline), staff, holidays, working days, the enabled-currency
-- catalog, funds, taxes and entity-to-entity mapping. Runs inside a tenant
-- schema (search_path pinned by the migration runner). Idempotent.
--

-- ---------------------------------------------------------------------------
-- offices — extend the V001 baseline with lifecycle fields Fineract exposes.
-- ---------------------------------------------------------------------------
ALTER TABLE office ADD COLUMN IF NOT EXISTS is_deleted   boolean NOT NULL DEFAULT false;
ALTER TABLE office ADD COLUMN IF NOT EXISTS created_at   timestamptz NOT NULL DEFAULT now();

-- office_transaction — extend the V001 baseline with an audit timestamp.
ALTER TABLE office_transaction ADD COLUMN IF NOT EXISTS created_at timestamptz NOT NULL DEFAULT now();

-- Seed the root "Head Office" for brand-new tenants (Fineract-parity default
-- so the office tree is never empty). Idempotent: skipped if any office row
-- already exists (e.g. re-running migrations on a tenant provisioned before
-- this migration shipped). Hierarchy convention matches OrganizationService::
-- createOffice: root offices hang off the zero-uuid sentinel with
-- hierarchy = "." + id + ".".
DO $$
DECLARE
    head_office_id uuid;
BEGIN
    IF NOT EXISTS (SELECT 1 FROM office) THEN
        INSERT INTO office (parent_id, name, opening_date, updated_at)
        VALUES ('00000000-0000-0000-0000-000000000000'::uuid, 'Head Office', CURRENT_DATE, CURRENT_DATE)
        RETURNING id INTO head_office_id;
        UPDATE office SET hierarchy = '.' || head_office_id || '.' WHERE id = head_office_id;
    END IF;
END $$;

-- ---------------------------------------------------------------------------
-- staff
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS staff (
    id                uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    office_id         uuid        NOT NULL REFERENCES office (id),
    firstname         varchar(100) NOT NULL,
    lastname          varchar(100) NOT NULL,
    display_name      varchar(200) GENERATED ALWAYS AS (lastname || ', ' || firstname) STORED,
    external_id       varchar(100),
    mobile_no         varchar(40),
    is_loan_officer   boolean     NOT NULL DEFAULT false,
    is_active         boolean     NOT NULL DEFAULT true,
    joining_date      date,
    created_at        timestamptz NOT NULL DEFAULT now(),
    modified_at       timestamptz NOT NULL DEFAULT now(),
    CONSTRAINT uq_staff_external_id UNIQUE (external_id)
);
CREATE INDEX IF NOT EXISTS idx_staff_office_id ON staff (office_id);

-- ---------------------------------------------------------------------------
-- holidays
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS holiday (
    id                       uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    name                     varchar(100) NOT NULL,
    from_date                date        NOT NULL,
    to_date                  date        NOT NULL,
    repayment_scheduled_to   date,
    description              varchar(500),
    status                   varchar(20) NOT NULL DEFAULT 'PENDING_FOR_ACTIVATION',
    applies_to_all_offices   boolean     NOT NULL DEFAULT true,
    created_at               timestamptz NOT NULL DEFAULT now(),
    modified_at              timestamptz NOT NULL DEFAULT now(),
    CONSTRAINT chk_holiday_status CHECK
        (status IN ('PENDING_FOR_ACTIVATION', 'ACTIVE', 'DELETED')),
    CONSTRAINT chk_holiday_dates CHECK (to_date >= from_date)
);

CREATE TABLE IF NOT EXISTS holiday_office (
    holiday_id  uuid NOT NULL REFERENCES holiday (id) ON DELETE CASCADE,
    office_id   uuid NOT NULL REFERENCES office (id) ON DELETE CASCADE,
    PRIMARY KEY (holiday_id, office_id)
);

-- ---------------------------------------------------------------------------
-- working days (singleton configuration row)
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS working_days (
    id                             int PRIMARY KEY DEFAULT 1,
    working_days                   varchar(40) NOT NULL DEFAULT 'MON,TUE,WED,THU,FRI',
    repayment_rescheduling_type    varchar(30) NOT NULL DEFAULT 'MOVE_TO_NEXT_WORKING_DAY',
    extend_term_for_daily_repayments boolean   NOT NULL DEFAULT false,
    modified_at                    timestamptz NOT NULL DEFAULT now(),
    CONSTRAINT chk_working_days_singleton CHECK (id = 1),
    CONSTRAINT chk_repayment_rescheduling_type CHECK (repayment_rescheduling_type IN
        ('SAME_DAY', 'MOVE_TO_NEXT_WORKING_DAY', 'MOVE_TO_NEXT_REPAYMENT_MEETING_DAY'))
);
INSERT INTO working_days (id) VALUES (1) ON CONFLICT (id) DO NOTHING;

-- ---------------------------------------------------------------------------
-- currencies — extend the V001 baseline (organisation_currency) into an
-- ISO catalog with a per-tenant enabled flag (GET/PUT /currencies).
-- ---------------------------------------------------------------------------
ALTER TABLE organisation_currency ADD COLUMN IF NOT EXISTS is_enabled boolean NOT NULL DEFAULT false;
CREATE UNIQUE INDEX IF NOT EXISTS uq_organisation_currency_code ON organisation_currency (code);

INSERT INTO organisation_currency (code, decimal_places, currency_multiplesof, name, display_symbol, internationalized_name_code, is_enabled) VALUES
    ('USD', 2, 1, 'US Dollar',            '$',   'currency.USD', true),
    ('EUR', 2, 1, 'Euro',                 '€',   'currency.EUR', true),
    ('GBP', 2, 1, 'British Pound',        '£',   'currency.GBP', false),
    ('GHS', 2, 1, 'Ghanaian Cedi',        'GH₵', 'currency.GHS', true),
    ('NGN', 2, 1, 'Nigerian Naira',       '₦',   'currency.NGN', false),
    ('KES', 2, 1, 'Kenyan Shilling',      'KSh', 'currency.KES', false),
    ('UGX', 0, 1, 'Ugandan Shilling',     'USh', 'currency.UGX', false),
    ('TZS', 2, 1, 'Tanzanian Shilling',   'TSh', 'currency.TZS', false),
    ('ZAR', 2, 1, 'South African Rand',   'R',   'currency.ZAR', false),
    ('XOF', 0, 1, 'West African CFA Franc','CFA','currency.XOF', false),
    ('INR', 2, 1, 'Indian Rupee',         '₹',   'currency.INR', false),
    ('CAD', 2, 1, 'Canadian Dollar',      'CA$', 'currency.CAD', false),
    ('AUD', 2, 1, 'Australian Dollar',    'A$',  'currency.AUD', false),
    ('CNY', 2, 1, 'Chinese Yuan',         '¥',   'currency.CNY', false)
ON CONFLICT (code) DO NOTHING;

-- ---------------------------------------------------------------------------
-- funds
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS fund (
    id           uuid DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    name         varchar(100) NOT NULL UNIQUE,
    external_id  varchar(100) UNIQUE,
    created_at   timestamptz NOT NULL DEFAULT now(),
    modified_at  timestamptz NOT NULL DEFAULT now()
);

-- ---------------------------------------------------------------------------
-- taxes
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS tax_component (
    id                  uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    name                varchar(100) NOT NULL UNIQUE,
    percentage          numeric(19,6) NOT NULL,
    start_date          date        NOT NULL,
    debit_account_id    varchar(80),   -- GL account id (Accounting lands in Phase 3)
    credit_account_id   varchar(80),
    created_at          timestamptz NOT NULL DEFAULT now(),
    modified_at         timestamptz NOT NULL DEFAULT now()
);

CREATE TABLE IF NOT EXISTS tax_group (
    id           uuid DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    name         varchar(100) NOT NULL UNIQUE,
    created_at   timestamptz NOT NULL DEFAULT now(),
    modified_at  timestamptz NOT NULL DEFAULT now()
);

CREATE TABLE IF NOT EXISTS tax_group_mapping (
    id                uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    tax_group_id      uuid        NOT NULL REFERENCES tax_group (id) ON DELETE CASCADE,
    tax_component_id  uuid        NOT NULL REFERENCES tax_component (id),
    start_date        date        NOT NULL,
    CONSTRAINT uq_tax_group_mapping UNIQUE (tax_group_id, tax_component_id, start_date)
);

-- ---------------------------------------------------------------------------
-- entity-to-entity mapping
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS entity_relation (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    code_from     varchar(100) NOT NULL,
    code_to       varchar(100) NOT NULL,
    mapping_types varchar(40) NOT NULL DEFAULT 'ONE_TO_MANY',
    CONSTRAINT uq_entity_relation UNIQUE (code_from, code_to)
);
INSERT INTO entity_relation (code_from, code_to, mapping_types) VALUES
    ('OFFICE', 'STAFF', 'ONE_TO_MANY'),
    ('CLIENT', 'STAFF', 'MANY_TO_ONE')
ON CONFLICT DO NOTHING;

CREATE TABLE IF NOT EXISTS entity_mapping (
    id            uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    relation_id   uuid        NOT NULL REFERENCES entity_relation (id),
    from_id       varchar(80) NOT NULL,
    to_id         varchar(80) NOT NULL,
    created_at    timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_entity_mapping_relation ON entity_mapping (relation_id, from_id);
