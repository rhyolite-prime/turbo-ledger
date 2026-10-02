--
-- V001__baseline.sql — Phase 7: Teller cash management baseline schema
-- (`tellers`, `cashiers`, `cashiersjournal`, 21 endpoints).
--
-- Fineract's Teller Cash Management module: a `teller` belongs to an office
-- and has one or more `cashier` assignments (a staff member rostered to
-- work that teller for a date range / time window); cash is allocated to a
-- cashier from the teller's vault and settled back, each movement logged as
-- a `cashier_transaction`. This schema follows that shape directly (same
-- three-table design Fineract itself uses: m_teller / m_cashiers /
-- m_cashier_transactions).
--
-- `office_id`/`staff_id` are cross-service opaque ids (Organization's own
-- database), trusted as given — same "cross-service ids intentionally
-- trusted as caller-supplied" precedent as every prior phase. No inter-
-- service RPC client exists in this codebase to validate them.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

CREATE TABLE IF NOT EXISTS tellers (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    office_id       uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    name            varchar(100) NOT NULL,
    description     text,
    -- status_enum: 300 = Active, 400 = Inactive (Fineract's own convention
    -- for this resource, e.g. the sample createTeller request body in the
    -- legacy API docs: {"status":300, ...}).
    status_enum     integer DEFAULT 300 NOT NULL,
    start_date      date NOT NULL,
    end_date        date,
    created_at      timestamptz DEFAULT now() NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_tellers_office_id ON tellers (office_id);

CREATE TABLE IF NOT EXISTS cashiers (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    teller_id       uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL
                        REFERENCES tellers(id) ON DELETE CASCADE,
    staff_id        uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    description     text,
    start_date      date NOT NULL,
    end_date        date,
    -- Mandatory per Fineract's own create-cashier rule: full-day assignment
    -- OR an explicit start/end time window, not both.
    is_full_day     boolean DEFAULT true NOT NULL,
    start_time      varchar(8),
    end_time        varchar(8),
    created_at      timestamptz DEFAULT now() NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_cashiers_teller_id ON cashiers (teller_id);
CREATE INDEX IF NOT EXISTS idx_cashiers_staff_id ON cashiers (staff_id);

CREATE TABLE IF NOT EXISTS cashier_transactions (
    id              uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    cashier_id      uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL
                        REFERENCES cashiers(id) ON DELETE CASCADE,
    -- txn_type: Fineract's own fixed codes -- 101 = Allocate Cash,
    -- 102 = Settle Cash (the only two commands this phase wires; 103/104
    -- = Cash In/Cash Out are reserved for a future DepositAccountManagement
    -- teller-transaction integration, which needs an inter-service posting
    -- client this codebase doesn't have yet -- same class of cross-service
    -- composition gap as every prior phase's documented 501 stubs).
    txn_type        integer NOT NULL,
    txn_amount      numeric(19,6) NOT NULL,
    txn_date        date NOT NULL,
    currency_code   varchar(3) NOT NULL,
    entity_id       uuid,
    entity_type     varchar(50),
    txn_note        text,
    created_at      timestamptz DEFAULT now() NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_cashier_transactions_cashier_id ON cashier_transactions (cashier_id);
CREATE INDEX IF NOT EXISTS idx_cashier_transactions_txn_date ON cashier_transactions (txn_date);
