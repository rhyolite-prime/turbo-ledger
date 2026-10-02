--
-- V001__baseline.sql — generated from src/scripts/TlOrganizationDb.sql by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

-- extracted from /home/user/turbo-ledger/src/scripts/TlOrganizationDb.sql
-- source database: TlOrganizationDb (server 15.14 (Postgres.app), pg_dump 18.4, archive v1.16)

--
-- EXTENSION: uuid-ossp
--

--
-- TABLE: loan_product
--
CREATE TABLE loan_product (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    short_name character varying(4) NOT NULL,
    currency_code character varying(3) NOT NULL,
    currency_digits smallint NOT NULL,
    currency_multiplesof smallint,
    principal_amount numeric(19,6) DEFAULT NULL::numeric,
    min_principal_amount numeric(19,6) DEFAULT NULL::numeric,
    max_principal_amount numeric(19,6) DEFAULT NULL::numeric,
    arrearstolerance_amount numeric(19,6) DEFAULT NULL::numeric,
    name character varying(100) NOT NULL,
    description character varying(500) DEFAULT NULL::character varying,
    fund_id uuid,
    is_linked_to_floating_interest_rates boolean DEFAULT false NOT NULL,
    allow_variabe_installments boolean DEFAULT false NOT NULL,
    nominal_interest_rate_per_period numeric(19,6) DEFAULT NULL::numeric,
    min_nominal_interest_rate_per_period numeric(19,6) DEFAULT NULL::numeric,
    max_nominal_interest_rate_per_period numeric(19,6) DEFAULT NULL::numeric,
    interest_period_frequency_enum smallint,
    annual_nominal_interest_rate numeric(19,6) DEFAULT NULL::numeric,
    interest_method_enum smallint NOT NULL,
    interest_calculated_in_period_enum smallint DEFAULT 1 NOT NULL,
    allow_partial_period_interest_calcualtion boolean DEFAULT false NOT NULL,
    term_frequency smallint DEFAULT 0 NOT NULL,
    term_period_frequency_enum smallint DEFAULT 2 NOT NULL,
    repay_every smallint NOT NULL,
    repayment_period_frequency_enum smallint NOT NULL,
    number_of_repayments smallint NOT NULL,
    min_number_of_repayments smallint,
    max_number_of_repayments smallint,
    grace_on_principal_periods smallint,
    recurring_moratorium_principal_periods smallint,
    grace_on_interest_periods smallint,
    grace_interest_free_periods smallint,
    amortization_method_enum smallint NOT NULL,
    accounting_type smallint NOT NULL,
    loan_transaction_strategy_id uuid,
    external_id character varying(100) DEFAULT NULL::character varying,
    include_in_borrower_cycle boolean DEFAULT false NOT NULL,
    use_borrower_cycle boolean DEFAULT false NOT NULL,
    start_date date,
    close_date date,
    allow_multiple_disbursals boolean DEFAULT false NOT NULL,
    max_disbursals integer,
    max_outstanding_loan_balance numeric(19,6) DEFAULT NULL::numeric,
    grace_on_arrears_ageing smallint,
    overdue_days_for_npa smallint,
    days_in_month_enum smallint DEFAULT 1 NOT NULL,
    days_in_year_enum smallint DEFAULT 1 NOT NULL,
    interest_recalculation_enabled boolean DEFAULT false NOT NULL,
    min_days_between_disbursal_and_first_repayment integer,
    hold_guarantee_funds boolean DEFAULT false NOT NULL,
    principal_threshold_for_last_installment numeric(5,2) DEFAULT 50.00 NOT NULL,
    account_moves_out_of_npa_only_on_arrears_completion boolean DEFAULT false NOT NULL,
    can_define_fixed_emi_amount boolean DEFAULT false NOT NULL,
    instalment_amount_in_multiples_of numeric(19,6) DEFAULT NULL::numeric,
    can_use_for_topup boolean DEFAULT false NOT NULL,
    sync_expected_with_disbursement_date boolean DEFAULT false,
    is_equal_amortization boolean DEFAULT false NOT NULL,
    fixed_principal_percentage_per_installment numeric(5,2) DEFAULT NULL::numeric,
    disallow_expected_disbursements boolean DEFAULT false NOT NULL,
    allow_approved_disbursed_amounts_over_applied boolean DEFAULT false NOT NULL,
    over_applied_calculation_type character varying(10) DEFAULT NULL::character varying,
    over_applied_number integer,
    delinquency_bucket_id uuid,
    loan_transaction_strategy_code character varying(100) DEFAULT '-'::character varying NOT NULL,
    loan_transaction_strategy_name character varying(100) DEFAULT '-'::character varying NOT NULL,
    due_days_for_repayment_event integer,
    overdue_days_for_repayment_event integer,
    enable_down_payment boolean DEFAULT false NOT NULL,
    disbursed_amount_percentage_for_down_payment numeric(9,6) DEFAULT NULL::numeric,
    enable_installment_level_delinquency boolean DEFAULT false NOT NULL,
    enable_auto_repayment_for_down_payment boolean DEFAULT false NOT NULL,
    repayment_start_date_type_enum smallint DEFAULT 1 NOT NULL,
    disable_schedule_extension_for_down_payment boolean DEFAULT false NOT NULL,
    loan_schedule_type character varying(20) DEFAULT 'CUMULATIVE'::character varying NOT NULL,
    loan_schedule_processing_type character varying(20) DEFAULT 'HORIZONTAL'::character varying NOT NULL
);

--
-- TABLE: office
--
CREATE TABLE office (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    parent_id uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    hierarchy character varying(250) DEFAULT NULL::character varying,
    external_id character varying(100) DEFAULT NULL::character varying,
    name character varying(50) NOT NULL,
    opening_date date NOT NULL,
    updated_at date NOT NULL
);

--
-- TABLE: office_transaction
--
CREATE TABLE office_transaction (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    from_office_id uuid,
    to_office_id uuid,
    currency_code character varying(5) NOT NULL,
    currency_digits integer NOT NULL,
    transaction_amount numeric(19,6) NOT NULL,
    transaction_date date NOT NULL,
    description character varying(100) DEFAULT NULL::character varying
);

--
-- TABLE: organisation_creditbureau
--
CREATE TABLE organisation_creditbureau (
    id bigint NOT NULL,
    alias character varying(50) NOT NULL,
    creditbureau_id bigint NOT NULL,
    is_active boolean
);

--
-- SEQUENCE: organisation_creditbureau_id_seq
--
CREATE SEQUENCE organisation_creditbureau_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

--
-- SEQUENCE OWNED BY: organisation_creditbureau_id_seq
--
ALTER SEQUENCE organisation_creditbureau_id_seq OWNED BY organisation_creditbureau.id;

--
-- TABLE: organisation_currency
--
CREATE TABLE organisation_currency (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    code character varying(3) NOT NULL,
    decimal_places smallint NOT NULL,
    currency_multiplesof smallint,
    name character varying(50) NOT NULL,
    display_symbol character varying(10) DEFAULT NULL::character varying,
    internationalized_name_code character varying(50) NOT NULL
);

--
-- TABLE: payment_type
--
CREATE TABLE payment_type (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    value character varying(100) DEFAULT NULL::character varying,
    description character varying(500) DEFAULT NULL::character varying,
    is_cash_payment boolean DEFAULT false,
    order_position integer DEFAULT 0 NOT NULL,
    code_name character varying(100) DEFAULT NULL::character varying,
    is_system_defined boolean DEFAULT false NOT NULL
);

--
-- DEFAULT: organisation_creditbureau id
--
ALTER TABLE ONLY organisation_creditbureau ALTER COLUMN id SET DEFAULT nextval('organisation_creditbureau_id_seq'::regclass);

--
-- CONSTRAINT: loan_product loan_product_external_id_key
--
ALTER TABLE ONLY loan_product
    ADD CONSTRAINT loan_product_external_id_key UNIQUE (external_id);

--
-- CONSTRAINT: loan_product loan_product_name_key
--
ALTER TABLE ONLY loan_product
    ADD CONSTRAINT loan_product_name_key UNIQUE (name);

--
-- CONSTRAINT: loan_product loan_product_pkey
--
ALTER TABLE ONLY loan_product
    ADD CONSTRAINT loan_product_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: loan_product loan_product_short_name_key
--
ALTER TABLE ONLY loan_product
    ADD CONSTRAINT loan_product_short_name_key UNIQUE (short_name);

--
-- CONSTRAINT: office office_external_id_key
--
ALTER TABLE ONLY office
    ADD CONSTRAINT office_external_id_key UNIQUE (external_id);

--
-- CONSTRAINT: office office_name_key
--
ALTER TABLE ONLY office
    ADD CONSTRAINT office_name_key UNIQUE (name);

--
-- CONSTRAINT: office office_pkey
--
ALTER TABLE ONLY office
    ADD CONSTRAINT office_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: office_transaction office_transaction_pkey
--
ALTER TABLE ONLY office_transaction
    ADD CONSTRAINT office_transaction_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: organisation_creditbureau organisation_creditbureau_alias_creditbureau_id_key
--
ALTER TABLE ONLY organisation_creditbureau
    ADD CONSTRAINT organisation_creditbureau_alias_creditbureau_id_key UNIQUE (alias, creditbureau_id);

--
-- CONSTRAINT: organisation_creditbureau organisation_creditbureau_pkey
--
ALTER TABLE ONLY organisation_creditbureau
    ADD CONSTRAINT organisation_creditbureau_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: organisation_currency organisation_currency_pkey
--
ALTER TABLE ONLY organisation_currency
    ADD CONSTRAINT organisation_currency_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: payment_type payment_type_pkey
--
ALTER TABLE ONLY payment_type
    ADD CONSTRAINT payment_type_pkey PRIMARY KEY (id);

--
-- INDEX: idx_tl_loan_product_delinquency_bucket_id
--
CREATE INDEX idx_tl_loan_product_delinquency_bucket_id ON loan_product USING btree (delinquency_bucket_id);

--
-- INDEX: idx_tl_loan_product_fund_id
--
CREATE INDEX idx_tl_loan_product_fund_id ON loan_product USING btree (fund_id);

--
-- INDEX: idx_tl_loan_product_loan_transaction_strategy_id
--
CREATE INDEX idx_tl_loan_product_loan_transaction_strategy_id ON loan_product USING btree (loan_transaction_strategy_id);

--
-- INDEX: idx_tl_office_parent_id
--
CREATE INDEX idx_tl_office_parent_id ON office USING btree (parent_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- INDEX: idx_tl_office_transaction_from_office_id
--
CREATE INDEX idx_tl_office_transaction_from_office_id ON office_transaction USING btree (from_office_id);

--
-- INDEX: idx_tl_office_transaction_to_office_id
--
CREATE INDEX idx_tl_office_transaction_to_office_id ON office_transaction USING btree (to_office_id);

--
-- INDEX: idx_tl_organisation_creditbureau_creditbureau_id
--
CREATE INDEX idx_tl_organisation_creditbureau_creditbureau_id ON organisation_creditbureau USING btree (creditbureau_id);
