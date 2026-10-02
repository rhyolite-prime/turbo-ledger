--
-- V001__baseline.sql — generated from src/scripts/TlCustomerDb.sql by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

--
-- PostgreSQL database dump
--

-- Dumped from database version 15.14 (Postgres.app)
-- Dumped by pg_dump version 18.4

-- Started on 2026-09-30 07:17:11 GMT

--
-- TOC entry 2 (class 3079 OID 5621125)
-- Name: uuid-ossp; Type: EXTENSION; Schema: -; Owner: -
--

--
-- TOC entry 3804 (class 0 OID 0)
-- Dependencies: 2
-- Name: EXTENSION "uuid-ossp"; Type: COMMENT; Schema: -; Owner: 
--

--
-- TOC entry 225 (class 1259 OID 5633033)
-- Name: account_transfer_standing_instructions; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE account_transfer_standing_instructions (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    name character varying(250) NOT NULL,
    account_transfer_details_id uuid NOT NULL,
    priority integer NOT NULL,
    status integer NOT NULL,
    instruction_type integer NOT NULL,
    amount numeric(19,6) DEFAULT NULL::numeric,
    valid_from date NOT NULL,
    valid_till date,
    recurrence_type integer NOT NULL,
    recurrence_frequency integer,
    recurrence_interval integer,
    recurrence_on_day integer,
    recurrence_on_month integer,
    last_run_date date
);

--
-- TOC entry 226 (class 1259 OID 5633043)
-- Name: account_transfer_standing_instructions_history; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE account_transfer_standing_instructions_history (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    standing_instruction_id uuid NOT NULL,
    status character varying(20) NOT NULL,
    execution_time timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    amount numeric(19,6) NOT NULL,
    error_log character varying(500) DEFAULT NULL::character varying
);

--
-- TOC entry 216 (class 1259 OID 5632821)
-- Name: client; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    account_no character varying(20) NOT NULL,
    external_id character varying(100) DEFAULT NULL::character varying,
    status integer DEFAULT 300 NOT NULL,
    sub_status integer,
    activation_date date,
    office_joining_date date,
    office_id uuid,
    transfer_to_office_id uuid,
    staff_id uuid,
    firstname character varying(80) DEFAULT NULL::character varying,
    middlename character varying(80) DEFAULT NULL::character varying,
    lastname character varying(80) DEFAULT NULL::character varying,
    fullname character varying(240) DEFAULT NULL::character varying,
    display_name character varying(200) DEFAULT NULL::character varying,
    mobile_no character varying(20) DEFAULT NULL::character varying,
    is_staff boolean DEFAULT false NOT NULL,
    gender_cv_id uuid,
    date_of_birth date,
    image_id uuid,
    closure_reason_cv_id uuid,
    closedon_date date,
    updated_by uuid,
    updated_on date,
    submittedon_date date,
    activatedon_userid uuid,
    closedon_userid uuid,
    default_savings_product uuid,
    default_savings_account uuid,
    client_type_cv_id uuid,
    client_classification_cv_id uuid,
    reject_reason_cv_id uuid,
    rejectedon_date date,
    rejectedon_userid uuid,
    withdraw_reason_cv_id uuid,
    withdrawn_on_date date,
    withdraw_on_userid uuid,
    reactivated_on_date date,
    reactivated_on_userid uuid,
    legal_structure integer,
    reopened_on_date date,
    reopened_by_userid uuid,
    email_address character varying(150) DEFAULT NULL::character varying,
    proposed_transfer_date date,
    created_by uuid,
    created_at timestamp with time zone DEFAULT now(),
    modified_by uuid,
    modified_at timestamp with time zone DEFAULT now()
);

--
-- TOC entry 217 (class 1259 OID 5632863)
-- Name: client_address; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_address (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    client_id uuid,
    street character varying(150) DEFAULT NULL::character varying,
    address_line_1 character varying(150) DEFAULT NULL::character varying,
    address_line_2 character varying(150) DEFAULT NULL::character varying,
    city character varying(150) DEFAULT NULL::character varying,
    state_or_province character varying(150) DEFAULT NULL::character varying,
    country character varying(150) DEFAULT NULL::character varying,
    country_code character varying(150) DEFAULT NULL::character varying,
    address_type_id uuid,
    is_active boolean DEFAULT false NOT NULL
);

--
-- TOC entry 218 (class 1259 OID 5632881)
-- Name: client_attendance; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_attendance (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    client_id uuid NOT NULL,
    meeting_id uuid,
    attendance_type integer NOT NULL
);

--
-- TOC entry 215 (class 1259 OID 5631612)
-- Name: client_charge; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_charge (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    client_id uuid NOT NULL,
    charge_id uuid NOT NULL,
    is_penalty boolean NOT NULL,
    charge_time_enum integer NOT NULL,
    charge_due_date date,
    charge_calculation_enum integer NOT NULL,
    amount numeric(19,6) NOT NULL,
    amount_paid_derived numeric(19,6) DEFAULT NULL::numeric,
    amount_waived_derived numeric(19,6) DEFAULT NULL::numeric,
    amount_writtenoff_derived numeric(19,6) DEFAULT NULL::numeric,
    amount_outstanding_derived numeric(19,6) NOT NULL,
    is_paid_derived boolean,
    waived boolean,
    is_active boolean,
    inactivated_on_date date
);

--
-- TOC entry 219 (class 1259 OID 5632890)
-- Name: client_charge_paid_by; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_charge_paid_by (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    client_transaction_id uuid,
    client_charge_id uuid NOT NULL,
    amount numeric(19,6) NOT NULL
);

--
-- TOC entry 220 (class 1259 OID 5632899)
-- Name: client_collateral_management; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_collateral_management (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    quantity numeric(20,5) NOT NULL,
    client_id uuid,
    collateral_id uuid
);

--
-- TOC entry 224 (class 1259 OID 5632964)
-- Name: client_identifier; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_identifier (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    client_id uuid NOT NULL,
    document_type_id uuid NOT NULL,
    document_key character varying(50) NOT NULL,
    status integer DEFAULT 300 NOT NULL,
    active integer,
    description character varying(500) DEFAULT NULL::character varying,
    created_by uuid NOT NULL,
    last_modified_by uuid NOT NULL,
    created_date timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    lastmodified_date timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    created_on_utc timestamp(6) without time zone DEFAULT NULL::timestamp without time zone,
    last_modified_on_utc timestamp(6) without time zone DEFAULT NULL::timestamp without time zone
);

--
-- TOC entry 221 (class 1259 OID 5632907)
-- Name: client_non_person; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_non_person (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    client_id uuid NOT NULL,
    constitution_cv_id uuid NOT NULL,
    incorp_no character varying(50) DEFAULT NULL::character varying,
    incorp_validity_till date,
    main_business_line_cv_id uuid,
    remarks character varying(150) DEFAULT NULL::character varying
);

--
-- TOC entry 222 (class 1259 OID 5632917)
-- Name: client_transaction; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_transaction (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    client_id uuid NOT NULL,
    office_id uuid NOT NULL,
    currency_code character varying(20) NOT NULL,
    payment_detail_id uuid,
    is_reversed boolean NOT NULL,
    external_id character varying(50) DEFAULT NULL::character varying,
    transaction_date date NOT NULL,
    transaction_type integer NOT NULL,
    amount numeric(19,6) NOT NULL,
    created_by uuid,
    created_at timestamp with time zone DEFAULT now(),
    modified_by uuid,
    modified_at timestamp with time zone DEFAULT now(),
    submitted_on_date date NOT NULL
);

--
-- TOC entry 223 (class 1259 OID 5632932)
-- Name: client_transfer_details; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE client_transfer_details (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    client_id uuid NOT NULL,
    from_office_id uuid NOT NULL,
    to_office_id uuid NOT NULL,
    proposed_transfer_date date,
    transfer_type integer NOT NULL,
    submitted_on date NOT NULL,
    submitted_by uuid NOT NULL
);

--
-- TOC entry 3797 (class 0 OID 5633033)
-- Dependencies: 225
-- Data for Name: account_transfer_standing_instructions; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY account_transfer_standing_instructions (id, business_id, name, account_transfer_details_id, priority, status, instruction_type, amount, valid_from, valid_till, recurrence_type, recurrence_frequency, recurrence_interval, recurrence_on_day, recurrence_on_month, last_run_date) FROM stdin;
\.

--
-- TOC entry 3798 (class 0 OID 5633043)
-- Dependencies: 226
-- Data for Name: account_transfer_standing_instructions_history; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY account_transfer_standing_instructions_history (id, business_id, standing_instruction_id, status, execution_time, amount, error_log) FROM stdin;
\.

--
-- TOC entry 3788 (class 0 OID 5632821)
-- Dependencies: 216
-- Data for Name: client; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client (id, business_id, account_no, external_id, status, sub_status, activation_date, office_joining_date, office_id, transfer_to_office_id, staff_id, firstname, middlename, lastname, fullname, display_name, mobile_no, is_staff, gender_cv_id, date_of_birth, image_id, closure_reason_cv_id, closedon_date, updated_by, updated_on, submittedon_date, activatedon_userid, closedon_userid, default_savings_product, default_savings_account, client_type_cv_id, client_classification_cv_id, reject_reason_cv_id, rejectedon_date, rejectedon_userid, withdraw_reason_cv_id, withdrawn_on_date, withdraw_on_userid, reactivated_on_date, reactivated_on_userid, legal_structure, reopened_on_date, reopened_by_userid, email_address, proposed_transfer_date, created_by, created_at, modified_by, modified_at) FROM stdin;
\.

--
-- TOC entry 3789 (class 0 OID 5632863)
-- Dependencies: 217
-- Data for Name: client_address; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_address (id, business_id, client_id, street, address_line_1, address_line_2, city, state_or_province, country, country_code, address_type_id, is_active) FROM stdin;
\.

--
-- TOC entry 3790 (class 0 OID 5632881)
-- Dependencies: 218
-- Data for Name: client_attendance; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_attendance (id, business_id, client_id, meeting_id, attendance_type) FROM stdin;
\.

--
-- TOC entry 3787 (class 0 OID 5631612)
-- Dependencies: 215
-- Data for Name: client_charge; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_charge (id, client_id, charge_id, is_penalty, charge_time_enum, charge_due_date, charge_calculation_enum, amount, amount_paid_derived, amount_waived_derived, amount_writtenoff_derived, amount_outstanding_derived, is_paid_derived, waived, is_active, inactivated_on_date) FROM stdin;
\.

--
-- TOC entry 3791 (class 0 OID 5632890)
-- Dependencies: 219
-- Data for Name: client_charge_paid_by; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_charge_paid_by (id, business_id, client_transaction_id, client_charge_id, amount) FROM stdin;
\.

--
-- TOC entry 3792 (class 0 OID 5632899)
-- Dependencies: 220
-- Data for Name: client_collateral_management; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_collateral_management (id, business_id, quantity, client_id, collateral_id) FROM stdin;
\.

--
-- TOC entry 3796 (class 0 OID 5632964)
-- Dependencies: 224
-- Data for Name: client_identifier; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_identifier (id, business_id, client_id, document_type_id, document_key, status, active, description, created_by, last_modified_by, created_date, lastmodified_date, created_on_utc, last_modified_on_utc) FROM stdin;
\.

--
-- TOC entry 3793 (class 0 OID 5632907)
-- Dependencies: 221
-- Data for Name: client_non_person; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_non_person (id, business_id, client_id, constitution_cv_id, incorp_no, incorp_validity_till, main_business_line_cv_id, remarks) FROM stdin;
\.

--
-- TOC entry 3794 (class 0 OID 5632917)
-- Dependencies: 222
-- Data for Name: client_transaction; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_transaction (id, business_id, client_id, office_id, currency_code, payment_detail_id, is_reversed, external_id, transaction_date, transaction_type, amount, created_by, created_at, modified_by, modified_at, submitted_on_date) FROM stdin;
\.

--
-- TOC entry 3795 (class 0 OID 5632932)
-- Dependencies: 223
-- Data for Name: client_transfer_details; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY client_transfer_details (id, business_id, client_id, from_office_id, to_office_id, proposed_transfer_date, transfer_type, submitted_on, submitted_by) FROM stdin;
\.

--
-- TOC entry 3643 (class 2606 OID 5633052)
-- Name: account_transfer_standing_instructions_history account_transfer_standing_instructions_history_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY account_transfer_standing_instructions_history
    ADD CONSTRAINT account_transfer_standing_instructions_history_pkey PRIMARY KEY (id);

--
-- TOC entry 3638 (class 2606 OID 5633041)
-- Name: account_transfer_standing_instructions account_transfer_standing_instructions_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY account_transfer_standing_instructions
    ADD CONSTRAINT account_transfer_standing_instructions_name_key UNIQUE (name);

--
-- TOC entry 3640 (class 2606 OID 5633039)
-- Name: account_transfer_standing_instructions account_transfer_standing_instructions_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY account_transfer_standing_instructions
    ADD CONSTRAINT account_transfer_standing_instructions_pkey PRIMARY KEY (id);

--
-- TOC entry 3569 (class 2606 OID 5632842)
-- Name: client client_account_no_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client
    ADD CONSTRAINT client_account_no_key UNIQUE (account_no);

--
-- TOC entry 3593 (class 2606 OID 5632878)
-- Name: client_address client_address_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_address
    ADD CONSTRAINT client_address_pkey PRIMARY KEY (id);

--
-- TOC entry 3597 (class 2606 OID 5632888)
-- Name: client_attendance client_attendance_client_id_meeting_id_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_attendance
    ADD CONSTRAINT client_attendance_client_id_meeting_id_key UNIQUE (client_id, meeting_id);

--
-- TOC entry 3599 (class 2606 OID 5632886)
-- Name: client_attendance client_attendance_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_attendance
    ADD CONSTRAINT client_attendance_pkey PRIMARY KEY (id);

--
-- TOC entry 3602 (class 2606 OID 5632895)
-- Name: client_charge_paid_by client_charge_paid_by_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_charge_paid_by
    ADD CONSTRAINT client_charge_paid_by_pkey PRIMARY KEY (id);

--
-- TOC entry 3565 (class 2606 OID 5631620)
-- Name: client_charge client_charge_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_charge
    ADD CONSTRAINT client_charge_pkey PRIMARY KEY (id);

--
-- TOC entry 3606 (class 2606 OID 5632904)
-- Name: client_collateral_management client_collateral_management_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_collateral_management
    ADD CONSTRAINT client_collateral_management_pkey PRIMARY KEY (id);

--
-- TOC entry 3571 (class 2606 OID 5632844)
-- Name: client client_external_id_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client
    ADD CONSTRAINT client_external_id_key UNIQUE (external_id);

--
-- TOC entry 3573 (class 2606 OID 5632846)
-- Name: client client_external_id_legal_form_enum_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client
    ADD CONSTRAINT client_external_id_legal_form_enum_key UNIQUE (external_id, legal_structure);

--
-- TOC entry 3628 (class 2606 OID 5632981)
-- Name: client_identifier client_identifier_client_id_document_type_id_active_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_identifier
    ADD CONSTRAINT client_identifier_client_id_document_type_id_active_key UNIQUE (client_id, document_type_id, active);

--
-- TOC entry 3630 (class 2606 OID 5632979)
-- Name: client_identifier client_identifier_document_type_id_document_key_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_identifier
    ADD CONSTRAINT client_identifier_document_type_id_document_key_key UNIQUE (document_type_id, document_key);

--
-- TOC entry 3632 (class 2606 OID 5632977)
-- Name: client_identifier client_identifier_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_identifier
    ADD CONSTRAINT client_identifier_pkey PRIMARY KEY (id);

--
-- TOC entry 3575 (class 2606 OID 5632848)
-- Name: client client_mobile_no_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client
    ADD CONSTRAINT client_mobile_no_key UNIQUE (mobile_no);

--
-- TOC entry 3610 (class 2606 OID 5632916)
-- Name: client_non_person client_non_person_client_id_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_non_person
    ADD CONSTRAINT client_non_person_client_id_key UNIQUE (client_id);

--
-- TOC entry 3612 (class 2606 OID 5632914)
-- Name: client_non_person client_non_person_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_non_person
    ADD CONSTRAINT client_non_person_pkey PRIMARY KEY (id);

--
-- TOC entry 3577 (class 2606 OID 5632840)
-- Name: client client_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client
    ADD CONSTRAINT client_pkey PRIMARY KEY (id);

--
-- TOC entry 3614 (class 2606 OID 5632927)
-- Name: client_transaction client_transaction_external_id_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_transaction
    ADD CONSTRAINT client_transaction_external_id_key UNIQUE (external_id);

--
-- TOC entry 3616 (class 2606 OID 5632925)
-- Name: client_transaction client_transaction_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_transaction
    ADD CONSTRAINT client_transaction_pkey PRIMARY KEY (id);

--
-- TOC entry 3622 (class 2606 OID 5632937)
-- Name: client_transfer_details client_transfer_details_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY client_transfer_details
    ADD CONSTRAINT client_transfer_details_pkey PRIMARY KEY (id);

--
-- TOC entry 3641 (class 1259 OID 5633042)
-- Name: idx_account_transfer_standing_instructions_account_transfer_det; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_account_transfer_standing_instructions_account_transfer_det ON account_transfer_standing_instructions USING btree (account_transfer_details_id);

--
-- TOC entry 3644 (class 1259 OID 5633053)
-- Name: idx_account_transfer_standing_instructions_history_standing_ins; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_account_transfer_standing_instructions_history_standing_ins ON account_transfer_standing_instructions_history USING btree (standing_instruction_id);

--
-- TOC entry 3633 (class 1259 OID 5632982)
-- Name: idx_client_identifier_client_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_client_identifier_client_id ON client_identifier USING btree (client_id);

--
-- TOC entry 3634 (class 1259 OID 5632984)
-- Name: idx_client_identifier_created_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_client_identifier_created_by ON client_identifier USING btree (created_by);

--
-- TOC entry 3635 (class 1259 OID 5632983)
-- Name: idx_client_identifier_document_type_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_client_identifier_document_type_id ON client_identifier USING btree (document_type_id);

--
-- TOC entry 3636 (class 1259 OID 5632985)
-- Name: idx_client_identifier_last_modified_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_client_identifier_last_modified_by ON client_identifier USING btree (last_modified_by);

--
-- TOC entry 3594 (class 1259 OID 5632879)
-- Name: idx_tl_client_address_address_type_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_address_address_type_id ON client_address USING btree (address_type_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3595 (class 1259 OID 5632880)
-- Name: idx_tl_client_address_client_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_address_client_id ON client_address USING btree (client_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3600 (class 1259 OID 5632889)
-- Name: idx_tl_client_attendance_meeting_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_attendance_meeting_id ON client_attendance USING btree (meeting_id);

--
-- TOC entry 3566 (class 1259 OID 5631621)
-- Name: idx_tl_client_charge_charge_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_charge_charge_id ON client_charge USING btree (charge_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3567 (class 1259 OID 5631622)
-- Name: idx_tl_client_charge_client_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_charge_client_id ON client_charge USING btree (client_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3603 (class 1259 OID 5632896)
-- Name: idx_tl_client_charge_paid_by_client_charge_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_charge_paid_by_client_charge_id ON client_charge_paid_by USING btree (client_charge_id);

--
-- TOC entry 3604 (class 1259 OID 5632897)
-- Name: idx_tl_client_charge_paid_by_client_transaction_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_charge_paid_by_client_transaction_id ON client_charge_paid_by USING btree (client_transaction_id);

--
-- TOC entry 3578 (class 1259 OID 5632849)
-- Name: idx_tl_client_classification_cv_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_classification_cv_id ON client USING btree (client_classification_cv_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3579 (class 1259 OID 5632850)
-- Name: idx_tl_client_client_type_cv_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_client_type_cv_id ON client USING btree (client_type_cv_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3580 (class 1259 OID 5632851)
-- Name: idx_tl_client_closure_reason_cv_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_closure_reason_cv_id ON client USING btree (closure_reason_cv_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3607 (class 1259 OID 5632905)
-- Name: idx_tl_client_collateral_management_client_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_collateral_management_client_id ON client_collateral_management USING btree (client_id);

--
-- TOC entry 3608 (class 1259 OID 5632906)
-- Name: idx_tl_client_collateral_management_collateral_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_collateral_management_collateral_id ON client_collateral_management USING btree (collateral_id);

--
-- TOC entry 3581 (class 1259 OID 5632852)
-- Name: idx_tl_client_created_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_created_by ON client USING btree (created_by) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3582 (class 1259 OID 5632853)
-- Name: idx_tl_client_default_savings_account; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_default_savings_account ON client USING btree (default_savings_account) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3583 (class 1259 OID 5632854)
-- Name: idx_tl_client_default_savings_product; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_default_savings_product ON client USING btree (default_savings_product) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3584 (class 1259 OID 5632855)
-- Name: idx_tl_client_gender_cv_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_gender_cv_id ON client USING btree (gender_cv_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3585 (class 1259 OID 5632856)
-- Name: idx_tl_client_image_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_image_id ON client USING btree (image_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3586 (class 1259 OID 5632857)
-- Name: idx_tl_client_office_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_office_id ON client USING btree (office_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3587 (class 1259 OID 5632858)
-- Name: idx_tl_client_reject_reason_cv_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_reject_reason_cv_id ON client USING btree (reject_reason_cv_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3588 (class 1259 OID 5632859)
-- Name: idx_tl_client_staff_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_staff_id ON client USING btree (staff_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3589 (class 1259 OID 5632860)
-- Name: idx_tl_client_sub_status; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_sub_status ON client USING btree (sub_status) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3617 (class 1259 OID 5632928)
-- Name: idx_tl_client_transaction_client_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transaction_client_id ON client_transaction USING btree (client_id);

--
-- TOC entry 3618 (class 1259 OID 5632929)
-- Name: idx_tl_client_transaction_created_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transaction_created_by ON client_transaction USING btree (created_by);

--
-- TOC entry 3619 (class 1259 OID 5632930)
-- Name: idx_tl_client_transaction_modified_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transaction_modified_by ON client_transaction USING btree (modified_by);

--
-- TOC entry 3620 (class 1259 OID 5632931)
-- Name: idx_tl_client_transaction_submitted_on_date; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transaction_submitted_on_date ON client_transaction USING btree (submitted_on_date);

--
-- TOC entry 3623 (class 1259 OID 5632938)
-- Name: idx_tl_client_transfer_details_client_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transfer_details_client_id ON client_transfer_details USING btree (client_id);

--
-- TOC entry 3624 (class 1259 OID 5632939)
-- Name: idx_tl_client_transfer_details_from_office_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transfer_details_from_office_id ON client_transfer_details USING btree (from_office_id);

--
-- TOC entry 3625 (class 1259 OID 5632940)
-- Name: idx_tl_client_transfer_details_submitted_by; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transfer_details_submitted_by ON client_transfer_details USING btree (submitted_by);

--
-- TOC entry 3626 (class 1259 OID 5632941)
-- Name: idx_tl_client_transfer_details_to_office_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transfer_details_to_office_id ON client_transfer_details USING btree (to_office_id);

--
-- TOC entry 3590 (class 1259 OID 5632861)
-- Name: idx_tl_client_transfer_to_office_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_transfer_to_office_id ON client USING btree (transfer_to_office_id) WITH (fillfactor='100', deduplicate_items='true');

--
-- TOC entry 3591 (class 1259 OID 5632862)
-- Name: idx_tl_client_withdraw_reason_cv_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX idx_tl_client_withdraw_reason_cv_id ON client USING btree (withdraw_reason_cv_id) WITH (fillfactor='100', deduplicate_items='true');

-- Completed on 2026-09-30 07:17:11 GMT

--
-- PostgreSQL database dump complete
--
