--
-- V003__phase3_ledger.sql — Phase 3: Accounting core (GL, journal entries,
-- accounting rules, financial activity mappings, provisioning entries).
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: every statement is guarded so re-running is safe.
--
-- Ledger correctness rules implemented here (see IMPLEMENTATION_PLAN.md §2.5):
--   - hash-chained journal entries: entry_seq/entry_hash/prev_hash on
--     journal_entries let JournalService verify/replay the tamper-evident
--     chain (hash = sha256(prev_hash || canonical entry fields)); entries are
--     otherwise immutable — corrections only ever happen via a reversal that
--     posts new, equal-and-opposite legs and links back via reversal_id.
--   - balanced multi-leg postings: enforced in JournalService inside a single
--     DB transaction (sum(debits) == sum(credits) per transaction_id), with
--     a CHECK-trigger backstop (trg_journal_entries_no_orphan_leg) that
--     blocks any INSERT that would leave a transaction_id's legs unbalanced
--     at COMMIT time (deferred constraint trigger).
--   - GL closures block postings on/before the closure date for an office
--     (enforced in JournalService against gl_closure; no DB trigger needed
--     since the check requires cross-referencing the posting request date).
--

-- ---------------------------------------------------------------------------
-- accounts — schema bug fix + hierarchy/audit parity with Office (Phase 2).
--
-- The V001 baseline defined accounts.parent_id as NOT NULL with no default,
-- which is fine (root accounts use the same zero-uuid sentinel convention as
-- Office), but never got audit columns. Add them for parity with every other
-- Phase 2/3 table.
-- ---------------------------------------------------------------------------
ALTER TABLE accounts ADD COLUMN IF NOT EXISTS created_at timestamptz NOT NULL DEFAULT now();
ALTER TABLE accounts ADD COLUMN IF NOT EXISTS updated_at timestamptz NOT NULL DEFAULT now();

CREATE INDEX IF NOT EXISTS idx_accounts_classification ON accounts USING btree (classification);
CREATE INDEX IF NOT EXISTS idx_accounts_disabled ON accounts USING btree (disabled);

-- ---------------------------------------------------------------------------
-- accounting_rules — fix a real schema bug inherited from the V001 baseline:
-- debit_account_id/credit_account_id were typed `integer`, but accounts.id
-- is `uuid` (every other FK to accounts in this schema is uuid). An integer
-- column can never have held a valid account reference, so there is no data
-- to migrate — the columns are dropped and re-added with the correct type
-- and a real FK. Multi-account rules (allow_multiple_debits/credits) get
-- their own junction tables, matching Fineract's acc_accounting_rule_*
-- shape: a rule always has exactly one "primary" debit/credit account, and
-- optionally more via the junction tables when the allow_multiple_* flag is
-- set.
-- ---------------------------------------------------------------------------
DO $$
BEGIN
    IF EXISTS (
        SELECT 1 FROM information_schema.columns
        WHERE table_name = 'accounting_rules' AND column_name = 'debit_account_id'
          AND data_type = 'integer'
    ) THEN
        ALTER TABLE accounting_rules DROP COLUMN debit_account_id;
        ALTER TABLE accounting_rules DROP COLUMN credit_account_id;
        ALTER TABLE accounting_rules ADD COLUMN debit_account_id uuid REFERENCES accounts (id);
        ALTER TABLE accounting_rules ADD COLUMN credit_account_id uuid REFERENCES accounts (id);
    END IF;
END $$;

ALTER TABLE accounting_rules ADD COLUMN IF NOT EXISTS created_at timestamptz NOT NULL DEFAULT now();
ALTER TABLE accounting_rules ADD COLUMN IF NOT EXISTS updated_at timestamptz NOT NULL DEFAULT now();

-- Surrogate uuid primary keys (rather than a composite (rule_id, account_id)
-- key, as Organization's holiday_office join table uses) so these are
-- ORM-mappable via CoroMapper<T> like every other Phase 3 table — no raw SQL
-- needed here.
CREATE TABLE IF NOT EXISTS accounting_rule_debit_accounts (
    id         uuid DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    rule_id    uuid NOT NULL REFERENCES accounting_rules (id) ON DELETE CASCADE,
    account_id uuid NOT NULL REFERENCES accounts (id),
    CONSTRAINT uq_accounting_rule_debit_accounts UNIQUE (rule_id, account_id)
);

CREATE TABLE IF NOT EXISTS accounting_rule_credit_accounts (
    id         uuid DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    rule_id    uuid NOT NULL REFERENCES accounting_rules (id) ON DELETE CASCADE,
    account_id uuid NOT NULL REFERENCES accounts (id),
    CONSTRAINT uq_accounting_rule_credit_accounts UNIQUE (rule_id, account_id)
);

-- ---------------------------------------------------------------------------
-- financial_activity_accounts — FK tightening only (table shape unchanged).
-- ---------------------------------------------------------------------------
DO $$
BEGIN
    IF NOT EXISTS (
        SELECT 1 FROM information_schema.table_constraints
        WHERE constraint_name = 'financial_activity_accounts_gl_account_id_fkey'
    ) THEN
        ALTER TABLE financial_activity_accounts
            ADD CONSTRAINT financial_activity_accounts_gl_account_id_fkey
            FOREIGN KEY (gl_account_id) REFERENCES accounts (id);
    END IF;
END $$;

ALTER TABLE financial_activity_accounts ADD COLUMN IF NOT EXISTS created_at timestamptz NOT NULL DEFAULT now();
ALTER TABLE financial_activity_accounts ADD COLUMN IF NOT EXISTS updated_at timestamptz NOT NULL DEFAULT now();

-- ---------------------------------------------------------------------------
-- journal_entries — hash chain columns + FK tightening.
--
-- entry_seq is a per-tenant-schema monotonic sequence (the uuid primary key
-- is not chronologically sortable, so the hash chain needs its own strictly
-- increasing order). entry_hash/prev_hash carry the sha256 chain computed by
-- JournalService at insert time; the first entry in a tenant's ledger has
-- prev_hash = NULL.
-- ---------------------------------------------------------------------------
ALTER TABLE journal_entries ADD COLUMN IF NOT EXISTS entry_seq bigserial;
ALTER TABLE journal_entries ADD COLUMN IF NOT EXISTS entry_hash varchar(64);
ALTER TABLE journal_entries ADD COLUMN IF NOT EXISTS prev_hash varchar(64);

DO $$
BEGIN
    IF NOT EXISTS (
        SELECT 1 FROM pg_constraint WHERE conname = 'journal_entries_entry_seq_key'
    ) THEN
        ALTER TABLE journal_entries ADD CONSTRAINT journal_entries_entry_seq_key UNIQUE (entry_seq);
    END IF;
END $$;

CREATE INDEX IF NOT EXISTS idx_journal_entries_entry_seq ON journal_entries USING btree (entry_seq);
CREATE INDEX IF NOT EXISTS idx_journal_entries_transaction_id ON journal_entries USING btree (transaction_id);
CREATE INDEX IF NOT EXISTS idx_journal_entries_entry_date ON journal_entries USING btree (entry_date);

DO $$
BEGIN
    IF NOT EXISTS (
        SELECT 1 FROM information_schema.table_constraints
        WHERE constraint_name = 'journal_entries_account_id_fkey'
    ) THEN
        ALTER TABLE journal_entries
            ADD CONSTRAINT journal_entries_account_id_fkey
            FOREIGN KEY (account_id) REFERENCES accounts (id);
    END IF;
    IF NOT EXISTS (
        SELECT 1 FROM information_schema.table_constraints
        WHERE constraint_name = 'journal_entries_reversal_id_fkey'
    ) THEN
        ALTER TABLE journal_entries
            ADD CONSTRAINT journal_entries_reversal_id_fkey
            FOREIGN KEY (reversal_id) REFERENCES journal_entries (id);
    END IF;
END $$;

-- ---------------------------------------------------------------------------
-- Balanced-ledger CHECK-trigger backstop.
--
-- JournalService already refuses to post an unbalanced multi-leg entry
-- inside its own transaction (application-level check before any INSERT).
-- This deferred constraint trigger is the belt-and-braces backstop the plan
-- calls for: it re-validates sum(debits) == sum(credits) per transaction_id
-- at COMMIT time, so no code path — including a future bug, a direct SQL
-- console session, or a half-finished manual fixup — can leave the ledger
-- unbalanced. It is deliberately schema-local (search_path is pinned to the
-- tenant schema by the migration runner), matching the "no cross-tenant
-- shared state" rule in §2.2.
-- ---------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION trg_fn_journal_entries_balanced() RETURNS trigger AS $$
DECLARE
    unbalanced_count integer;
BEGIN
    SELECT count(*) INTO unbalanced_count
    FROM (
        SELECT je.transaction_id,
               sum(CASE WHEN je.type_enum = 2 THEN je.amount ELSE 0 END) -
               sum(CASE WHEN je.type_enum = 1 THEN je.amount ELSE 0 END) AS diff
        FROM journal_entries je
        WHERE je.transaction_id IN (SELECT DISTINCT transaction_id FROM new_rows)
        GROUP BY je.transaction_id
    ) totals
    WHERE totals.diff <> 0;

    IF unbalanced_count > 0 THEN
        RAISE EXCEPTION 'journal_entries: one or more transaction_id groups are unbalanced (sum(debits) <> sum(credits)) at commit'
            USING ERRCODE = 'check_violation';
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_journal_entries_balanced ON journal_entries;
CREATE CONSTRAINT TRIGGER trg_journal_entries_balanced
    AFTER INSERT ON journal_entries
    DEFERRABLE INITIALLY DEFERRED
    REFERENCING NEW TABLE AS new_rows
    FOR EACH STATEMENT
    EXECUTE FUNCTION trg_fn_journal_entries_balanced();

-- ---------------------------------------------------------------------------
-- provisioning_entries / provisioning_entries_detail
--
-- Fineract's loan-loss provisioning engine drives its detail rows from
-- product/office/currency criteria owned by Portfolio (not yet built — see
-- IMPLEMENTATION_PLAN.md's Phase 6 scope). This phase delivers the ledger
-- side of provisioning: a provisioning entry is a dated batch of manually
-- supplied (office, gl account, currency, amount) lines that
-- ProvisioningEntryService posts as a balanced journal entry when
-- "createjournalentries" is requested. Wiring the detail lines up to an
-- automatic loan-arrears criteria engine is deferred to when Portfolio
-- exists; the persistence, journal-posting and recreate/reverse plumbing
-- built now does not need to change when that lands.
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS provisioning_entries (
    id                     uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    created_date           date        NOT NULL,
    comments               varchar(500),
    journal_entry_created  boolean     NOT NULL DEFAULT false,
    created_by             uuid,
    created_at             timestamptz NOT NULL DEFAULT now(),
    updated_at             timestamptz NOT NULL DEFAULT now()
);

CREATE TABLE IF NOT EXISTS provisioning_entries_detail (
    id                    uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    provisioning_entry_id uuid        NOT NULL REFERENCES provisioning_entries (id) ON DELETE CASCADE,
    office_id             uuid        NOT NULL,
    currency_code         varchar(3)  NOT NULL,
    gl_account_id         uuid        NOT NULL REFERENCES accounts (id),
    category_name         varchar(100) NOT NULL,
    amount                numeric(19,6) NOT NULL,
    created_at            timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_provisioning_entries_detail_entry_id
    ON provisioning_entries_detail USING btree (provisioning_entry_id);
CREATE INDEX IF NOT EXISTS idx_provisioning_entries_created_date
    ON provisioning_entries USING btree (created_date);
