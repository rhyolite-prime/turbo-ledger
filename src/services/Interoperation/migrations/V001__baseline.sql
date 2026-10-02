--
-- V001__baseline.sql — Interoperation (Payments v1) baseline schema.
--
-- Mojaloop-style wallet-interoperability primitives. Scope decision (see
-- IMPLEMENTATION_PLAN.md Phase 9 as-built notes): this sandbox has no other
-- FSP to settle against, so `parties`/`quotes`/`requests`/`transfers` are
-- genuinely computed (fee calculation, state machine, idempotent codes) and
-- persisted, but the cross-FSP settlement leg of the real Mojaloop
-- prepare/commit protocol never happens — there is nothing on the other
-- side of the wire to commit with. This is a disclosed limitation, not a
-- silent lie: every record's status honestly reflects "accepted locally,
-- never externally settled". `disburse`/`loanrepayment`, by contrast, ARE
-- real: they compose directly with Portfolio's loan commands against this
-- platform's own accounts.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
--

CREATE TABLE IF NOT EXISTS interop_identifiers (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    id_type             varchar(50) NOT NULL,     -- MSISDN, EMAIL, ACCOUNT_ID, ALIAS, ...
    id_value            varchar(150) NOT NULL,
    sub_id_or_type       varchar(50),
    account_id           varchar(64) NOT NULL,     -- internal savings/loan/share account id
    account_type         varchar(20) NOT NULL,     -- SAVINGS, LOAN, SHARE
    created_at           timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_interop_identifiers_lookup
    ON interop_identifiers(id_type, id_value, sub_id_or_type);

CREATE TABLE IF NOT EXISTS interop_quotes (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    transaction_code    varchar(64) NOT NULL,
    quote_code          varchar(64) NOT NULL,
    account_id          varchar(64) NOT NULL,
    amount              numeric NOT NULL,
    fee_amount          numeric NOT NULL DEFAULT 0,
    currency            varchar(10) NOT NULL DEFAULT 'USD',
    expiration          timestamptz,
    status              varchar(20) NOT NULL DEFAULT 'ACTIVE',
    created_at          timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_interop_quotes_lookup ON interop_quotes(transaction_code, quote_code);

CREATE TABLE IF NOT EXISTS interop_requests (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    transaction_code    varchar(64) NOT NULL,
    request_code        varchar(64) NOT NULL,
    account_id          varchar(64) NOT NULL,
    amount              numeric NOT NULL,
    currency            varchar(10) NOT NULL DEFAULT 'USD',
    status              varchar(20) NOT NULL DEFAULT 'PENDING',
    created_at          timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_interop_requests_lookup ON interop_requests(transaction_code, request_code);

CREATE TABLE IF NOT EXISTS interop_transfers (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    transaction_code    varchar(64) NOT NULL,
    transfer_code       varchar(64) NOT NULL,
    account_id          varchar(64) NOT NULL,
    amount              numeric NOT NULL,
    currency            varchar(10) NOT NULL DEFAULT 'USD',
    transfer_action     varchar(20) NOT NULL DEFAULT 'PREPARE',
    status              varchar(20) NOT NULL DEFAULT 'PENDING',
    created_at          timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_interop_transfers_lookup ON interop_transfers(transaction_code, transfer_code);
