--
-- V001__baseline.sql — generated from src/scripts/TlAccounting.sql by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

--
-- PostgreSQL database dump
--

-- Dumped from database version 15.14 (Postgres.app)
-- Dumped by pg_dump version 18.4

-- Started on 2026-09-30 07:14:17 GMT

--
-- TOC entry 2 (class 3079 OID 5632455)
-- Name: uuid-ossp; Type: EXTENSION; Schema: -; Owner: -
--

--
-- TOC entry 3705 (class 0 OID 0)
-- Dependencies: 2
-- Name: EXTENSION "uuid-ossp"; Type: COMMENT; Schema: -; Owner: 
--

--
-- TOC entry 218 (class 1259 OID 5632720)
-- Name: accounting_rules; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE accounting_rules (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    name character varying(100) DEFAULT NULL::character varying,
    office_id uuid,
    debit_account_id integer,
    allow_multiple_debits boolean DEFAULT false NOT NULL,
    credit_account_id integer,
    allow_multiple_credits boolean DEFAULT false NOT NULL,
    description character varying(500) DEFAULT NULL::character varying,
    system_defined boolean DEFAULT false NOT NULL
);

--
-- TOC entry 216 (class 1259 OID 5632638)
-- Name: accounts; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE accounts (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    name character varying(200) NOT NULL,
    parent_id uuid NOT NULL,
    hierarchy character varying(50) DEFAULT NULL::character varying,
    gl_code character varying(45) NOT NULL,
    disabled boolean DEFAULT false NOT NULL,
    manual_journal_entries_allowed boolean DEFAULT true NOT NULL,
    account_usage integer DEFAULT 2 NOT NULL,
    classification integer NOT NULL,
    tag_id uuid,
    description character varying(500) DEFAULT NULL::character varying
);

--
-- TOC entry 219 (class 1259 OID 5632752)
-- Name: financial_activity_accounts; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE financial_activity_accounts (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    gl_account_id uuid NOT NULL,
    financial_activity_type integer NOT NULL
);

--
-- TOC entry 215 (class 1259 OID 5632589)
-- Name: gl_closure; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE gl_closure (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    office_id uuid,
    closing_date date NOT NULL,
    is_deleted boolean DEFAULT false NOT NULL,
    createdby_id bigint,
    lastmodifiedby_id bigint,
    created_date timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    lastmodified_date timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    comments character varying(500) DEFAULT NULL::character varying
);

--
-- TOC entry 217 (class 1259 OID 5632656)
-- Name: journal_entries; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE journal_entries (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    account_id uuid NOT NULL,
    office_id uuid NOT NULL,
    reversal_id uuid,
    currency_code character varying(3) NOT NULL,
    transaction_id character varying(50) NOT NULL,
    loan_transaction_id uuid,
    savings_transaction_id uuid,
    client_transaction_id uuid,
    reversed boolean DEFAULT false NOT NULL,
    ref_num character varying(100) DEFAULT NULL::character varying,
    manual_entry boolean DEFAULT false NOT NULL,
    entry_date date NOT NULL,
    type_enum smallint NOT NULL,
    amount numeric(19,6) NOT NULL,
    description character varying(500) DEFAULT NULL::character varying,
    entity_type_enum smallint,
    entity_id uuid,
    created_by uuid,
    last_modified_by uuid,
    created_date timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    lastmodified_date timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    is_running_balance_calculated boolean DEFAULT false NOT NULL,
    office_running_balance numeric(19,6) DEFAULT 0.000000 NOT NULL,
    organization_running_balance numeric(19,6) DEFAULT 0.000000 NOT NULL,
    payment_details_id uuid,
    share_transaction_id uuid,
    transaction_date date,
    created_on_utc timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    last_modified_on_utc timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    submitted_on_date date NOT NULL
);

--
-- TOC entry 3698 (class 0 OID 5632720)
-- Dependencies: 218
-- Data for Name: accounting_rules; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY accounting_rules (id, name, office_id, debit_account_id, allow_multiple_debits, credit_account_id, allow_multiple_credits, description, system_defined) FROM stdin;
\.

--
-- TOC entry 3696 (class 0 OID 5632638)
-- Dependencies: 216
-- Data for Name: accounts; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY accounts (id, name, parent_id, hierarchy, gl_code, disabled, manual_journal_entries_allowed, account_usage, classification, tag_id, description) FROM stdin;
\.

--
-- TOC entry 3699 (class 0 OID 5632752)
-- Dependencies: 219
-- Data for Name: financial_activity_accounts; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY financial_activity_accounts (id, gl_account_id, financial_activity_type) FROM stdin;
\.

--
-- TOC entry 3695 (class 0 OID 5632589)
-- Dependencies: 215
-- Data for Name: gl_closure; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY gl_closure (id, office_id, closing_date, is_deleted, createdby_id, lastmodifiedby_id, created_date, lastmodified_date, comments) FROM stdin;
\.

--
-- TOC entry 3697 (class 0 OID 5632656)
-- Dependencies: 217
-- Data for Name: journal_entries; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY journal_entries (id, account_id, office_id, reversal_id, currency_code, transaction_id, loan_transaction_id, savings_transaction_id, client_transaction_id, reversed, ref_num, manual_entry, entry_date, type_enum, amount, description, entity_type_enum, entity_id, created_by, last_modified_by, created_date, lastmodified_date, is_running_balance_calculated, office_running_balance, organization_running_balance, payment_details_id, share_transaction_id, transaction_date, created_on_utc, last_modified_on_utc, submitted_on_date) FROM stdin;
\.

--
-- TOC entry 3525 (class 2606 OID 5632652)
-- Name: accounts account_gl_code_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY accounts
    ADD CONSTRAINT account_gl_code_key UNIQUE (gl_code);

--
-- TOC entry 3527 (class 2606 OID 5632650)
-- Name: accounts account_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY accounts
    ADD CONSTRAINT account_pkey PRIMARY KEY (id);

--
-- TOC entry 3545 (class 2606 OID 5632734)
-- Name: accounting_rules accounting_rules_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY accounting_rules
    ADD CONSTRAINT accounting_rules_name_key UNIQUE (name);

--
-- TOC entry 3547 (class 2606 OID 5632732)
-- Name: accounting_rules accounting_rules_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY accounting_rules
    ADD CONSTRAINT accounting_rules_pkey PRIMARY KEY (id);

--
-- TOC entry 3549 (class 2606 OID 5632759)
-- Name: financial_activity_accounts financial_activity_accounts_financial_activity_type_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY financial_activity_accounts
    ADD CONSTRAINT financial_activity_accounts_financial_activity_type_key UNIQUE (financial_activity_type);

--
-- TOC entry 3551 (class 2606 OID 5632757)
-- Name: financial_activity_accounts financial_activity_accounts_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY financial_activity_accounts
    ADD CONSTRAINT financial_activity_accounts_pkey PRIMARY KEY (id);

--
-- TOC entry 3518 (class 2606 OID 5632602)
-- Name: gl_closure gl_closure_office_id_closing_date_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY gl_closure
    ADD CONSTRAINT gl_closure_office_id_closing_date_key UNIQUE (office_id, closing_date);

--
-- TOC entry 3520 (class 2606 OID 5632600)
-- Name: gl_closure gl_closure_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY gl_closure
    ADD CONSTRAINT gl_closure_pkey PRIMARY KEY (id);

--
-- TOC entry 3543 (class 2606 OID 5632674)
-- Name: journal_entries journal_entries_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY journal_entries
    ADD CONSTRAINT journal_entries_pkey PRIMARY KEY (id);

--
-- TOC entry 3528 (class 1259 OID 5632653)
-- Name: idx_account_parent_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_account_parent_id ON accounts USING btree (parent_id);

--
-- TOC entry 3529 (class 1259 OID 5632654)
-- Name: idx_account_tag_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_account_tag_id ON accounts USING btree (tag_id);

--
-- TOC entry 3552 (class 1259 OID 5632760)
-- Name: idx_financial_activity_account_gl_account_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_financial_activity_account_gl_account_id ON financial_activity_accounts USING btree (gl_account_id);

--
-- TOC entry 3521 (class 1259 OID 5632603)
-- Name: idx_gl_closure_createdby_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_gl_closure_createdby_id ON gl_closure USING btree (createdby_id);

--
-- TOC entry 3522 (class 1259 OID 5632604)
-- Name: idx_gl_closure_lastmodifiedby_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_gl_closure_lastmodifiedby_id ON gl_closure USING btree (lastmodifiedby_id);

--
-- TOC entry 3523 (class 1259 OID 5632605)
-- Name: idx_gl_closure_office_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_gl_closure_office_id ON gl_closure USING btree (office_id);

--
-- TOC entry 3530 (class 1259 OID 5632679)
-- Name: idx_journal_entries_client_transaction_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_client_transaction_id ON journal_entries USING btree (client_transaction_id);

--
-- TOC entry 3531 (class 1259 OID 5632677)
-- Name: idx_journal_entries_created_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_created_by ON journal_entries USING btree (created_by);

--
-- TOC entry 3532 (class 1259 OID 5632675)
-- Name: idx_journal_entries_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_id ON journal_entries USING btree (account_id);

--
-- TOC entry 3533 (class 1259 OID 5632678)
-- Name: idx_journal_entries_last_modified_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_last_modified_by ON journal_entries USING btree (last_modified_by);

--
-- TOC entry 3534 (class 1259 OID 5632680)
-- Name: idx_journal_entries_loan_transaction_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_loan_transaction_id ON journal_entries USING btree (loan_transaction_id);

--
-- TOC entry 3535 (class 1259 OID 5632681)
-- Name: idx_journal_entries_office_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_office_id ON journal_entries USING btree (office_id);

--
-- TOC entry 3536 (class 1259 OID 5632682)
-- Name: idx_journal_entries_payment_details_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_payment_details_id ON journal_entries USING btree (payment_details_id);

--
-- TOC entry 3537 (class 1259 OID 5632676)
-- Name: idx_journal_entries_reversal_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_reversal_id ON journal_entries USING btree (reversal_id);

--
-- TOC entry 3538 (class 1259 OID 5632683)
-- Name: idx_journal_entries_savings_transaction_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_savings_transaction_id ON journal_entries USING btree (savings_transaction_id);

--
-- TOC entry 3539 (class 1259 OID 5632684)
-- Name: idx_journal_entries_share_transaction_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_share_transaction_id ON journal_entries USING btree (share_transaction_id);

--
-- TOC entry 3540 (class 1259 OID 5632686)
-- Name: idx_journal_entries_submitted_on_date; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_submitted_on_date ON journal_entries USING btree (submitted_on_date);

--
-- TOC entry 3541 (class 1259 OID 5632685)
-- Name: idx_journal_entries_transaction_date; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_journal_entries_transaction_date ON journal_entries USING btree (transaction_date);

-- Completed on 2026-09-30 07:14:17 GMT

--
-- PostgreSQL database dump complete
--
