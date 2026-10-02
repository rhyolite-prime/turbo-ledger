--
-- V003__phase6.sql — Lending & Shares (Phase 6).
--
-- Schema deviation note: unlike V001__baseline.sql (which was extracted
-- from a genuine ground-truth dump, src/scripts/TlPortfolio.sql, covering
-- only loanproduct_provisioning_entry / provisioning_history), no
-- ground-truth dump exists for the loans/shares domain itself. The tables
-- below are hand-designed against the Apache Fineract API surface
-- (ENDPOINT_INVENTORY.md's `loans`/`loanproducts`/.../`shareproduct`
-- groups) and this codebase's existing conventions (uuid PKs, tl_outbox
-- event emission, flattened discriminator columns rather than Fineract's
-- deep inheritance hierarchies). Column sets are a pragmatic subset of
-- Fineract's (the long tail of rarely-used product-config toggles is
-- omitted) sufficient to support real amortization math, real GL posting,
-- and the lifecycle/command surface implemented in
-- PortfolioService.cc — see IMPLEMENTATION_PLAN.md's Phase 6 entry for the
-- full list of disclosed simplifications.
--
-- Money columns use NUMERIC (not FLOAT) throughout, matching
-- turbo::Money's string-based decimal representation used elsewhere in
-- this codebase.
--

-- =============================================================================
-- loan products
-- =============================================================================

CREATE TABLE loan_product (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    name                            VARCHAR(100) NOT NULL,
    short_name                      VARCHAR(4)   NOT NULL,
    description                     TEXT,
    fund_id                         UUID,
    currency_code                   VARCHAR(3)   NOT NULL,
    currency_digits                 INTEGER      NOT NULL DEFAULT 2,
    min_principal_amount            NUMERIC(20,6),
    default_principal_amount        NUMERIC(20,6) NOT NULL,
    max_principal_amount            NUMERIC(20,6),
    min_number_of_repayments        INTEGER,
    default_number_of_repayments    INTEGER      NOT NULL,
    max_number_of_repayments        INTEGER,
    repayment_every                 INTEGER      NOT NULL DEFAULT 1,
    repayment_frequency_type        INTEGER      NOT NULL DEFAULT 2, -- 0=days,1=weeks,2=months
    min_interest_rate_per_period    NUMERIC(10,4),
    default_interest_rate_per_period NUMERIC(10,4) NOT NULL,
    max_interest_rate_per_period    NUMERIC(10,4),
    interest_period_frequency_type  INTEGER      NOT NULL DEFAULT 3, -- 2=per month,3=per year
    annual_nominal_interest_rate    NUMERIC(10,4) NOT NULL,
    interest_method                 INTEGER      NOT NULL DEFAULT 0, -- 0=declining_balance,1=flat
    interest_calculation_period_type INTEGER     NOT NULL DEFAULT 1, -- 0=daily,1=same_as_repayment
    amortization_type               INTEGER      NOT NULL DEFAULT 1, -- 0=equal_principal,1=equal_installments
    transaction_processing_strategy VARCHAR(40)  NOT NULL DEFAULT 'mifos-standard-strategy',
    grace_on_principal_payment      INTEGER      NOT NULL DEFAULT 0,
    grace_on_interest_payment       INTEGER      NOT NULL DEFAULT 0,
    grace_on_interest_charged       INTEGER      NOT NULL DEFAULT 0,
    grace_on_arrears_ageing         INTEGER      NOT NULL DEFAULT 0,
    overdue_days_for_npa            INTEGER      NOT NULL DEFAULT 90,
    days_in_year_type               INTEGER      NOT NULL DEFAULT 365, -- 360 or 365
    days_in_month_type              INTEGER      NOT NULL DEFAULT 30,  -- 30 or actual(0)
    min_days_between_disbursal_and_first_repayment INTEGER NOT NULL DEFAULT 0,
    allow_partial_period_interest   BOOLEAN      NOT NULL DEFAULT TRUE,
    is_linked_to_floating_rate      BOOLEAN      NOT NULL DEFAULT FALSE,
    floating_rate_id                UUID,
    default_differential_lending_rate NUMERIC(10,4),
    is_equal_amortization           BOOLEAN      NOT NULL DEFAULT FALSE,
    allow_attribute_overrides       BOOLEAN      NOT NULL DEFAULT TRUE,
    can_use_for_topup               BOOLEAN      NOT NULL DEFAULT FALSE,
    close_date                      DATE,
    start_date                      DATE,
    delinquency_bucket_id           UUID,
    accounting_type                 INTEGER      NOT NULL DEFAULT 1, -- 1=none,2=cash,3=accrual
    fund_source_account_id          UUID,
    loan_portfolio_account_id       UUID,
    interest_on_loan_account_id     UUID,
    income_from_fees_account_id     UUID,
    income_from_penalties_account_id UUID,
    income_from_recovery_account_id UUID,
    losses_written_off_account_id   UUID,
    overpayment_liability_account_id UUID,
    interest_receivable_account_id  UUID,
    fee_receivable_account_id       UUID,
    penalty_receivable_account_id   UUID,
    is_active                       BOOLEAN      NOT NULL DEFAULT TRUE,
    created_by                      UUID,
    created_at                      TIMESTAMPTZ  NOT NULL DEFAULT now(),
    updated_by                      UUID,
    updated_at                      TIMESTAMPTZ  NOT NULL DEFAULT now(),
    UNIQUE (short_name)
);

CREATE TABLE loan_product_charge (
    id                UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_product_id   UUID NOT NULL REFERENCES loan_product(id),
    charge_id         UUID NOT NULL
);
CREATE INDEX idx_loan_product_charge_product ON loan_product_charge(loan_product_id);

-- Fineract "loan product mix": pairs of products that are mutually
-- restricted (a client/group cannot hold both at once) or require the
-- restricted product to be fully paid off first.
CREATE TABLE loan_product_mix (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    product_id              UUID NOT NULL REFERENCES loan_product(id),
    restricted_product_id   UUID NOT NULL REFERENCES loan_product(id),
    UNIQUE (product_id, restricted_product_id)
);

CREATE TABLE loan_product_attribute (
    id                UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_product_id   UUID NOT NULL REFERENCES loan_product(id),
    attribute_key     VARCHAR(100) NOT NULL,
    attribute_value   TEXT,
    created_at        TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (loan_product_id, attribute_key)
);

-- =============================================================================
-- floating rates & general rates
-- =============================================================================

CREATE TABLE floating_rate (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    name                    VARCHAR(100) NOT NULL,
    is_base_lending_rate    BOOLEAN NOT NULL DEFAULT FALSE,
    is_active               BOOLEAN NOT NULL DEFAULT TRUE,
    created_by              UUID,
    created_at              TIMESTAMPTZ NOT NULL DEFAULT now(),
    updated_by              UUID,
    updated_at              TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (name)
);

CREATE TABLE floating_rate_period (
    id                          UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    floating_rate_id            UUID NOT NULL REFERENCES floating_rate(id),
    from_date                   DATE NOT NULL,
    interest_rate               NUMERIC(10,4) NOT NULL,
    is_differential_to_bln      BOOLEAN NOT NULL DEFAULT FALSE,
    bln_differential_rate       NUMERIC(10,4),
    is_active                   BOOLEAN NOT NULL DEFAULT TRUE,
    created_by                  UUID,
    created_at                  TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_floating_rate_period_rate ON floating_rate_period(floating_rate_id);

CREATE TABLE rate (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    name            VARCHAR(100) NOT NULL,
    percentage      NUMERIC(10,4) NOT NULL,
    is_active       BOOLEAN NOT NULL DEFAULT TRUE,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (name)
);

-- =============================================================================
-- delinquency
-- =============================================================================

CREATE TABLE delinquency_range (
    id                  UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    classification      VARCHAR(100) NOT NULL,
    min_overdue_days    INTEGER NOT NULL,
    max_overdue_days    INTEGER,
    created_at          TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (classification)
);

CREATE TABLE delinquency_bucket (
    id      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    name    VARCHAR(100) NOT NULL,
    created_at TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (name)
);

CREATE TABLE delinquency_bucket_range (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    delinquency_bucket_id   UUID NOT NULL REFERENCES delinquency_bucket(id),
    delinquency_range_id    UUID NOT NULL REFERENCES delinquency_range(id),
    UNIQUE (delinquency_bucket_id, delinquency_range_id)
);

-- =============================================================================
-- provisioning (category/criteria feed Accounting's provisioningentries via
-- loanproduct_provisioning_entry, already present from the ground-truth
-- V001 baseline).
-- =============================================================================

CREATE TABLE provisioning_category (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    category_name   VARCHAR(100) NOT NULL,
    category_description TEXT,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (category_name)
);

CREATE TABLE provisioning_criteria (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    criteria_name   VARCHAR(100) NOT NULL,
    created_by      UUID,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now(),
    updated_by      UUID,
    updated_at      TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (criteria_name)
);

CREATE TABLE provisioning_criteria_definition (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    criteria_id             UUID NOT NULL REFERENCES provisioning_criteria(id),
    category_id             UUID NOT NULL REFERENCES provisioning_category(id),
    min_overdue_days        INTEGER NOT NULL,
    max_overdue_days        INTEGER,
    provisioning_percentage NUMERIC(10,4) NOT NULL,
    liability_account_id    UUID,
    expense_account_id      UUID
);
CREATE INDEX idx_provisioning_criteria_definition_criteria ON provisioning_criteria_definition(criteria_id);

-- =============================================================================
-- loans
-- =============================================================================

CREATE TABLE loan (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    account_no                      VARCHAR(20) NOT NULL,
    external_id                     VARCHAR(100),
    client_id                       UUID,
    group_id                        UUID,
    product_id                      UUID NOT NULL REFERENCES loan_product(id),
    loan_officer_id                 UUID,
    fund_id                         UUID,
    loan_purpose                    VARCHAR(200),
    loan_type                       INTEGER NOT NULL DEFAULT 1, -- 1=individual,2=group,3=jlg
    currency_code                   VARCHAR(3) NOT NULL,
    currency_digits                 INTEGER NOT NULL DEFAULT 2,
    principal_amount                NUMERIC(20,6) NOT NULL,
    approved_principal              NUMERIC(20,6),
    net_disbursal_amount            NUMERIC(20,6),
    number_of_repayments            INTEGER NOT NULL,
    repayment_every                 INTEGER NOT NULL,
    repayment_frequency_type        INTEGER NOT NULL,
    interest_rate_per_period        NUMERIC(10,4) NOT NULL,
    interest_period_frequency_type  INTEGER NOT NULL,
    annual_nominal_interest_rate    NUMERIC(10,4) NOT NULL,
    interest_method                 INTEGER NOT NULL,
    interest_calculation_period_type INTEGER NOT NULL,
    amortization_type               INTEGER NOT NULL,
    transaction_processing_strategy VARCHAR(40) NOT NULL,
    days_in_year_type               INTEGER NOT NULL DEFAULT 365,
    days_in_month_type              INTEGER NOT NULL DEFAULT 30,
    grace_on_principal_payment      INTEGER NOT NULL DEFAULT 0,
    grace_on_interest_payment       INTEGER NOT NULL DEFAULT 0,
    grace_on_interest_charged       INTEGER NOT NULL DEFAULT 0,
    grace_on_arrears_ageing         INTEGER NOT NULL DEFAULT 0,
    is_equal_amortization           BOOLEAN NOT NULL DEFAULT FALSE,
    is_floating_interest_rate       BOOLEAN NOT NULL DEFAULT FALSE,
    floating_rate_id                UUID,
    interest_rate_differential      NUMERIC(10,4),
    submitted_on_date                DATE NOT NULL,
    submitted_by                    UUID,
    approved_on_date                DATE,
    approved_by                     UUID,
    expected_disbursement_date      DATE,
    actual_disbursement_date        DATE,
    disbursed_by                    UUID,
    expected_first_repayment_on_date DATE,
    interest_charged_from_date      DATE,
    expected_maturity_date          DATE,
    maturity_date                   DATE,
    closed_on_date                  DATE,
    closed_by                       UUID,
    rejected_on_date                DATE,
    withdrawn_on_date               DATE,
    writtenoff_on_date              DATE,
    status                          INTEGER NOT NULL DEFAULT 100,
    -- 100 submitted_and_pending_approval, 200 approved, 300 active,
    -- 400 withdrawn_by_client, 500 rejected, 600 closed_obligations_met,
    -- 601 closed_written_off, 602 closed_reschedule_outstanding_amount,
    -- 700 overpaid
    sub_status                      INTEGER, -- 1=inArrears,2=pause-interest(on hold)
    is_npa                          BOOLEAN NOT NULL DEFAULT FALSE,
    delinquency_range_id            UUID,
    overdue_since_date              DATE,
    principal_disbursed             NUMERIC(20,6) NOT NULL DEFAULT 0,
    principal_paid                  NUMERIC(20,6) NOT NULL DEFAULT 0,
    principal_writtenoff            NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_charged                NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_paid                   NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_waived                 NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_writtenoff             NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_charged             NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_paid                NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_waived              NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_writtenoff          NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_charged         NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_paid            NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_waived          NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_writtenoff      NUMERIC(20,6) NOT NULL DEFAULT 0,
    total_recovered                 NUMERIC(20,6) NOT NULL DEFAULT 0,
    total_overpaid                  NUMERIC(20,6) NOT NULL DEFAULT 0,
    buydown_fee_amount              NUMERIC(20,6) NOT NULL DEFAULT 0,
    capitalized_income_amount       NUMERIC(20,6) NOT NULL DEFAULT 0,
    -- GLIM (Group Loan Individual Monitoring): a loan_type=4 "glim parent"
    -- row aggregates N member loans, each with glim_parent_loan_id set to
    -- the parent's id and its own independent repayment schedule.
    glim_parent_loan_id             UUID REFERENCES loan(id),
    created_at                      TIMESTAMPTZ NOT NULL DEFAULT now(),
    updated_at                      TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (account_no),
    UNIQUE (external_id)
);
CREATE INDEX idx_loan_client ON loan(client_id);
CREATE INDEX idx_loan_group ON loan(group_id);
CREATE INDEX idx_loan_product ON loan(product_id);
CREATE INDEX idx_loan_status ON loan(status);

CREATE TABLE loan_disbursement_detail (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                 UUID NOT NULL REFERENCES loan(id),
    expected_disburse_date  DATE NOT NULL,
    actual_disburse_date    DATE,
    principal               NUMERIC(20,6) NOT NULL
);
CREATE INDEX idx_loan_disbursement_detail_loan ON loan_disbursement_detail(loan_id);

CREATE TABLE loan_charge (
    id                          UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                     UUID NOT NULL REFERENCES loan(id),
    charge_id                   UUID NOT NULL,
    is_penalty                  BOOLEAN NOT NULL DEFAULT FALSE,
    charge_time_type            INTEGER NOT NULL, -- 1=disbursement,2=specified_due_date,8=installment_fee,9=overdue_installment
    charge_calculation_type     INTEGER NOT NULL, -- 1=flat,2=%amount,3=%amount+interest,4=%interest
    due_date                    DATE,
    installment_number          INTEGER,
    amount                      NUMERIC(20,6) NOT NULL,
    amount_paid_derived         NUMERIC(20,6) NOT NULL DEFAULT 0,
    amount_waived_derived       NUMERIC(20,6) NOT NULL DEFAULT 0,
    amount_writtenoff_derived   NUMERIC(20,6) NOT NULL DEFAULT 0,
    amount_outstanding_derived  NUMERIC(20,6) NOT NULL DEFAULT 0,
    is_paid_derived             BOOLEAN NOT NULL DEFAULT FALSE,
    is_waived                   BOOLEAN NOT NULL DEFAULT FALSE,
    is_active                   BOOLEAN NOT NULL DEFAULT TRUE,
    created_at                  TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_charge_loan ON loan_charge(loan_id);

CREATE TABLE loan_collateral (
    id                  UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id             UUID NOT NULL REFERENCES loan(id),
    collateral_type_id  VARCHAR(40) NOT NULL,
    value               NUMERIC(20,6),
    description         TEXT,
    created_at          TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_collateral_loan ON loan_collateral(loan_id);

CREATE TABLE loan_guarantor (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                 UUID NOT NULL REFERENCES loan(id),
    guarantor_type          INTEGER NOT NULL DEFAULT 1, -- 1=external,2=existing_client
    client_id               UUID,
    first_name              VARCHAR(100),
    last_name               VARCHAR(100),
    address_line_1          VARCHAR(200),
    city                    VARCHAR(100),
    mobile_number           VARCHAR(40),
    amount                  NUMERIC(20,6),
    created_at              TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_guarantor_loan ON loan_guarantor(loan_id);

CREATE TABLE loan_rate (
    id          UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id     UUID NOT NULL REFERENCES loan(id),
    rate_id     UUID NOT NULL REFERENCES rate(id),
    UNIQUE (loan_id, rate_id)
);

CREATE TABLE loan_interest_pause (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id         UUID NOT NULL REFERENCES loan(id),
    external_id     VARCHAR(100),
    start_date      DATE NOT NULL,
    end_date        DATE NOT NULL,
    created_by      UUID,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_interest_pause_loan ON loan_interest_pause(loan_id);

CREATE TABLE loan_postdated_check (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id         UUID NOT NULL REFERENCES loan(id),
    installment_id  UUID,
    check_number    VARCHAR(40) NOT NULL,
    bank_name       VARCHAR(100),
    check_date      DATE NOT NULL,
    amount          NUMERIC(20,6) NOT NULL,
    status          INTEGER NOT NULL DEFAULT 1, -- 1=pending,2=presented,3=cleared,4=bounced
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_postdated_check_loan ON loan_postdated_check(loan_id);

CREATE TABLE loan_buydown_fee (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                 UUID NOT NULL REFERENCES loan(id),
    loan_transaction_id     UUID,
    amount                  NUMERIC(20,6) NOT NULL,
    amortized_amount        NUMERIC(20,6) NOT NULL DEFAULT 0,
    created_at              TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_buydown_fee_loan ON loan_buydown_fee(loan_id);

CREATE TABLE loan_capitalized_income (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                 UUID NOT NULL REFERENCES loan(id),
    loan_transaction_id     UUID,
    income_type             VARCHAR(40) NOT NULL DEFAULT 'fee',
    amount                  NUMERIC(20,6) NOT NULL,
    amortized_amount        NUMERIC(20,6) NOT NULL DEFAULT 0,
    created_at              TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_capitalized_income_loan ON loan_capitalized_income(loan_id);

CREATE TABLE loan_repayment_schedule_installment (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                         UUID NOT NULL REFERENCES loan(id),
    installment_number              INTEGER NOT NULL,
    from_date                       DATE NOT NULL,
    due_date                        DATE NOT NULL,
    principal_amount                NUMERIC(20,6) NOT NULL,
    principal_completed_derived     NUMERIC(20,6) NOT NULL DEFAULT 0,
    principal_writtenoff_derived    NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_amount                 NUMERIC(20,6) NOT NULL,
    interest_completed_derived      NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_waived_derived         NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_writtenoff_derived     NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_amount              NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_completed_derived   NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_waived_derived      NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_amount          NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_completed_derived NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_waived_derived  NUMERIC(20,6) NOT NULL DEFAULT 0,
    completed_derived               BOOLEAN NOT NULL DEFAULT FALSE,
    obligations_met_on_date         DATE,
    recalculated_interest           BOOLEAN NOT NULL DEFAULT FALSE,
    UNIQUE (loan_id, installment_number)
);
CREATE INDEX idx_loan_repayment_schedule_loan ON loan_repayment_schedule_installment(loan_id);

CREATE TABLE loan_transaction (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                         UUID NOT NULL REFERENCES loan(id),
    external_id                     VARCHAR(100),
    office_id                       UUID,
    transaction_type                INTEGER NOT NULL,
    -- 1=disbursement,2=repayment,4=waive_interest,6=write_off,
    -- 8=recovery_repayment,9=waive_charges,15=charge_payment,
    -- 16=refund,17=refund_for_active_loan,18=income_posting,
    -- 19=charge_off,20=reage,21=reamortize
    transaction_date                DATE NOT NULL,
    amount                          NUMERIC(20,6) NOT NULL,
    principal_portion               NUMERIC(20,6) NOT NULL DEFAULT 0,
    interest_portion                NUMERIC(20,6) NOT NULL DEFAULT 0,
    fee_charges_portion             NUMERIC(20,6) NOT NULL DEFAULT 0,
    penalty_charges_portion         NUMERIC(20,6) NOT NULL DEFAULT 0,
    overpayment_portion             NUMERIC(20,6) NOT NULL DEFAULT 0,
    outstanding_loan_balance_derived NUMERIC(20,6),
    is_reversed                     BOOLEAN NOT NULL DEFAULT FALSE,
    reversed_on_date                DATE,
    submitted_on_date               DATE NOT NULL DEFAULT CURRENT_DATE,
    created_by                      UUID,
    created_at                      TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (external_id)
);
CREATE INDEX idx_loan_transaction_loan ON loan_transaction(loan_id);

-- =============================================================================
-- loan reschedule requests
-- =============================================================================

CREATE TABLE reschedule_loan_request (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                         UUID NOT NULL REFERENCES loan(id),
    reason_code                     VARCHAR(100) NOT NULL,
    reason_comment                  TEXT,
    status                          INTEGER NOT NULL DEFAULT 100, -- 100=pending,200=approved,300=rejected
    reschedule_from_installment     INTEGER,
    reschedule_from_date            DATE,
    submitted_on_date               DATE NOT NULL,
    submitted_by                    UUID,
    extra_terms                     INTEGER,
    grace_on_principal              INTEGER,
    grace_on_interest               INTEGER,
    new_interest_rate               NUMERIC(10,4),
    adjusted_due_date               DATE,
    approved_on_date                DATE,
    approved_by                     UUID,
    created_at                      TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_reschedule_loan_request_loan ON reschedule_loan_request(loan_id);

-- =============================================================================
-- loan delinquency tagging
-- =============================================================================

CREATE TABLE loan_delinquency_tag_history (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id                 UUID NOT NULL REFERENCES loan(id),
    delinquency_range_id    UUID NOT NULL REFERENCES delinquency_range(id),
    classification_date     DATE NOT NULL,
    liftoff_date            DATE,
    created_at              TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_delinquency_tag_history_loan ON loan_delinquency_tag_history(loan_id);

CREATE TABLE loan_delinquency_action (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    loan_id         UUID NOT NULL REFERENCES loan(id),
    action          INTEGER NOT NULL, -- 1=pause,2=resume
    start_date      DATE NOT NULL,
    end_date        DATE,
    created_by      UUID,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_delinquency_action_loan ON loan_delinquency_action(loan_id);

-- =============================================================================
-- credit bureau
-- =============================================================================

CREATE TABLE credit_bureau (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    name            VARCHAR(100) NOT NULL,
    country         VARCHAR(2),
    is_active       BOOLEAN NOT NULL DEFAULT TRUE,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (name)
);

CREATE TABLE organisation_credit_bureau (
    id                  UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    credit_bureau_id    UUID NOT NULL REFERENCES credit_bureau(id),
    alias               VARCHAR(100) NOT NULL,
    is_active           BOOLEAN NOT NULL DEFAULT TRUE,
    created_at          TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_organisation_credit_bureau_bureau ON organisation_credit_bureau(credit_bureau_id);

CREATE TABLE credit_bureau_configuration (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    organisation_credit_bureau_id   UUID NOT NULL REFERENCES organisation_credit_bureau(id),
    config_key                      VARCHAR(100) NOT NULL,
    config_value                    TEXT,
    UNIQUE (organisation_credit_bureau_id, config_key)
);

CREATE TABLE credit_bureau_loan_product_mapping (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    organisation_credit_bureau_id   UUID NOT NULL REFERENCES organisation_credit_bureau(id),
    loan_product_id                 UUID NOT NULL REFERENCES loan_product(id),
    is_active                       BOOLEAN NOT NULL DEFAULT TRUE,
    UNIQUE (organisation_credit_bureau_id, loan_product_id)
);

-- credit_bureau_report.report_data stores the structured response from the
-- provider adapter (see PortfolioService.h's CreditBureauProvider interface
-- — ships with a deterministic local "sandbox" provider; wiring a real
-- external bureau is a configuration-time exercise behind the same
-- interface, see IMPLEMENTATION_PLAN.md Phase 6 disclosed simplifications).
CREATE TABLE credit_bureau_report (
    id                              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    organisation_credit_bureau_id   UUID NOT NULL REFERENCES organisation_credit_bureau(id),
    client_id                       UUID,
    loan_id                         UUID,
    national_id                     VARCHAR(60),
    report_data                     JSONB NOT NULL DEFAULT '{}'::jsonb,
    requested_by                    UUID,
    requested_on                    TIMESTAMPTZ NOT NULL DEFAULT now(),
    is_active                       BOOLEAN NOT NULL DEFAULT TRUE
);
CREATE INDEX idx_credit_bureau_report_bureau ON credit_bureau_report(organisation_credit_bureau_id);
CREATE INDEX idx_credit_bureau_report_client ON credit_bureau_report(client_id);

-- =============================================================================
-- external asset owners (loan sales / transfers)
-- =============================================================================

CREATE TABLE external_asset_owner (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    external_id     VARCHAR(100) NOT NULL,
    name            VARCHAR(150) NOT NULL,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (external_id)
);

CREATE TABLE loan_owner_transfer (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    external_id             VARCHAR(100),
    loan_id                 UUID NOT NULL REFERENCES loan(id),
    owner_id                UUID NOT NULL REFERENCES external_asset_owner(id),
    transfer_type           INTEGER NOT NULL DEFAULT 1, -- 1=sale,2=buyback
    status                  INTEGER NOT NULL DEFAULT 1, -- 1=pending,2=active,3=completed,4=cancelled,5=declined
    settlement_date         DATE,
    effective_date          DATE NOT NULL,
    purchase_price_ratio    NUMERIC(10,6) NOT NULL DEFAULT 1,
    created_by              UUID,
    created_at              TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (external_id)
);
CREATE INDEX idx_loan_owner_transfer_loan ON loan_owner_transfer(loan_id);
CREATE INDEX idx_loan_owner_transfer_owner ON loan_owner_transfer(owner_id);

CREATE TABLE loan_owner_transfer_journal_entry (
    id              UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    transfer_id     UUID NOT NULL REFERENCES loan_owner_transfer(id),
    entry_type      VARCHAR(40) NOT NULL,
    amount          NUMERIC(20,6) NOT NULL,
    gl_account_id   UUID,
    created_at      TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_loan_owner_transfer_journal_entry_transfer ON loan_owner_transfer_journal_entry(transfer_id);

-- =============================================================================
-- shares
-- =============================================================================

CREATE TABLE share_product (
    id                          UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    name                        VARCHAR(100) NOT NULL,
    short_name                  VARCHAR(4) NOT NULL,
    description                 TEXT,
    currency_code               VARCHAR(3) NOT NULL,
    currency_digits             INTEGER NOT NULL DEFAULT 2,
    total_shares                BIGINT NOT NULL,
    total_shares_to_be_issued   BIGINT NOT NULL,
    nominal_price               NUMERIC(20,6) NOT NULL,
    market_price                NUMERIC(20,6),
    share_capital_type          INTEGER NOT NULL DEFAULT 1, -- 1=paid_up,2=authorized
    minimum_shares              BIGINT,
    default_shares              BIGINT,
    maximum_shares              BIGINT,
    allow_dividends_for_inactive_clients BOOLEAN NOT NULL DEFAULT FALSE,
    lockin_period               INTEGER,
    lockin_period_frequency_type INTEGER, -- 0=days,1=weeks,2=months,3=years
    accounting_type             INTEGER NOT NULL DEFAULT 1,
    share_reference_account_id  UUID,
    share_suspense_account_id   UUID,
    share_equity_account_id     UUID,
    is_active                   BOOLEAN NOT NULL DEFAULT TRUE,
    start_date                  DATE,
    close_date                  DATE,
    created_at                  TIMESTAMPTZ NOT NULL DEFAULT now(),
    updated_at                  TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (short_name)
);

CREATE TABLE share_product_charge (
    id                  UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    share_product_id    UUID NOT NULL REFERENCES share_product(id),
    charge_id           UUID NOT NULL
);
CREATE INDEX idx_share_product_charge_product ON share_product_charge(share_product_id);

CREATE TABLE share_product_dividend (
    id                          UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    share_product_id            UUID NOT NULL REFERENCES share_product(id),
    dividend_period_start_date  DATE NOT NULL,
    dividend_period_end_date    DATE NOT NULL,
    dividend_amount             NUMERIC(20,6) NOT NULL,
    status                      INTEGER NOT NULL DEFAULT 100, -- 100=pending,300=approved
    created_by                  UUID,
    created_at                  TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_share_product_dividend_product ON share_product_dividend(share_product_id);

CREATE TABLE share_account (
    id                      UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    account_no              VARCHAR(20) NOT NULL,
    external_id             VARCHAR(100),
    client_id               UUID,
    group_id                UUID,
    product_id              UUID NOT NULL REFERENCES share_product(id),
    currency_code           VARCHAR(3) NOT NULL,
    submitted_date           DATE NOT NULL,
    submitted_by            UUID,
    approved_date            DATE,
    approved_by             UUID,
    activated_date           DATE,
    rejected_date            DATE,
    closed_date              DATE,
    status                  INTEGER NOT NULL DEFAULT 100,
    -- 100=submitted_and_pending_approval,200=approved,300=active,
    -- 400=rejected,500=closed
    requested_shares        BIGINT NOT NULL,
    approved_shares         BIGINT NOT NULL DEFAULT 0,
    lockin_period           INTEGER,
    lockin_period_frequency_type INTEGER,
    created_at              TIMESTAMPTZ NOT NULL DEFAULT now(),
    UNIQUE (account_no),
    UNIQUE (external_id)
);
CREATE INDEX idx_share_account_client ON share_account(client_id);
CREATE INDEX idx_share_account_product ON share_account(product_id);

CREATE TABLE share_account_charge (
    id                  UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    share_account_id    UUID NOT NULL REFERENCES share_account(id),
    charge_id           UUID NOT NULL,
    amount              NUMERIC(20,6) NOT NULL,
    amount_paid_derived NUMERIC(20,6) NOT NULL DEFAULT 0,
    is_active           BOOLEAN NOT NULL DEFAULT TRUE
);
CREATE INDEX idx_share_account_charge_account ON share_account_charge(share_account_id);

CREATE TABLE share_purchase_request (
    id                  UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    share_account_id    UUID NOT NULL REFERENCES share_account(id),
    requested_date      DATE NOT NULL,
    requested_shares    BIGINT NOT NULL,
    requested_price     NUMERIC(20,6),
    status              INTEGER NOT NULL DEFAULT 100, -- 100=pending,200=approved,300=rejected,400=applied
    requested_by        UUID,
    decided_by          UUID,
    decided_date        DATE,
    created_at          TIMESTAMPTZ NOT NULL DEFAULT now()
);
CREATE INDEX idx_share_purchase_request_account ON share_purchase_request(share_account_id);
