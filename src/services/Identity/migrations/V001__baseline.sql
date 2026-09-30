--
-- V001__baseline.sql — generated from src/scripts/TlIdentity.sql by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

-- extracted from /home/user/turbo-ledger/src/scripts/TlIdentity.sql
-- source database: TlIdentity (server 15.14 (Postgres.app), pg_dump 18.4, archive v1.16)

--
-- EXTENSION: uuid-ossp
--

--
-- TABLE: api_keys
--
CREATE TABLE api_keys (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    business_name character varying(155) NOT NULL,
    client_id character varying(50) NOT NULL,
    client_secret_hash text NOT NULL,
    label character varying(100),
    scopes jsonb DEFAULT '[]'::jsonb,
    allowed_ips inet[] DEFAULT '{}'::inet[],
    is_active boolean DEFAULT true,
    last_used_at timestamp with time zone,
    api_key_user_id uuid,
    created_by uuid,
    created_at timestamp with time zone DEFAULT now(),
    modified_by uuid,
    modified_at timestamp with time zone DEFAULT now()
);

--
-- TABLE: audit_logs
--
CREATE TABLE audit_logs (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    actor_id uuid,
    entity_type character varying(100) NOT NULL,
    entity_id uuid NOT NULL,
    action character varying(50) NOT NULL,
    old_values jsonb,
    new_values jsonb,
    ip_address inet,
    is_archived boolean DEFAULT false NOT NULL,
    user_agent character varying(512),
    created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP
);

--
-- TABLE: business_accounts
--
CREATE TABLE business_accounts (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_name character varying(155) NOT NULL,
    account_id character varying(10) DEFAULT lpad(((floor((random() * (900000)::double precision)) + (100000)::double precision))::text, 6, '0'::text) NOT NULL,
    contact_person_name character varying(100),
    contact_person_email character varying(150),
    contact_person_phone_no character varying(20),
    business_email character varying(150),
    business_phone_no character varying(20),
    country character varying(100),
    currency character varying(10) DEFAULT 'GHS'::character varying,
    status integer,
    sub_account_enabled boolean DEFAULT true,
    subscription_model jsonb,
    configuration_data jsonb,
    require_two_factor_auth boolean DEFAULT false,
    business_logo bytea,
    subscription_start_date timestamp with time zone,
    subscription_end_date timestamp with time zone,
    created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp without time zone,
    CONSTRAINT check_logo_size CHECK ((octet_length(business_logo) <= 1048576))
);

--
-- TABLE: login_history
--
CREATE TABLE login_history (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    user_id uuid NOT NULL,
    login_time timestamp with time zone DEFAULT CURRENT_TIMESTAMP,
    ip_address inet,
    user_agent character varying(512),
    device_id character varying(128),
    status character varying(50) NOT NULL,
    failure_reason character varying(255),
    location character varying(255),
    CONSTRAINT chk_login_status CHECK (((status)::text = ANY (ARRAY[('SUCCESS'::character varying)::text, ('FAILED'::character varying)::text, ('CHALLENGE_REQUIRED'::character varying)::text, ('2FA_PENDING'::character varying)::text])))
);

--
-- TABLE: roles
--
CREATE TABLE roles (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    name character varying(100) NOT NULL,
    description character varying(250),
    permissions jsonb NOT NULL,
    created_by uuid,
    created_at timestamp with time zone DEFAULT now(),
    modified_by uuid,
    modified_at timestamp with time zone DEFAULT now()
);

--
-- TABLE: users
--
CREATE TABLE users (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    business_id uuid,
    first_name character varying(100),
    last_name character varying(100),
    email character varying(255) NOT NULL,
    username character varying(100),
    email_verified_at timestamp without time zone DEFAULT CURRENT_TIMESTAMP,
    password_hash character varying(255),
    last_active_device text,
    profile_image_url character varying(255),
    require_two_factor_auth boolean DEFAULT false,
    phone_number character varying(255),
    country character varying(255),
    phone_verified_at timestamp without time zone,
    is_locked_out boolean DEFAULT false NOT NULL,
    is_active boolean DEFAULT false NOT NULL,
    credential_id bytea,
    public_key bytea,
    public_key_algorithm integer,
    sign_count bigint DEFAULT 0,
    user_handle bytea,
    transports text[],
    credential_type text,
    last_active timestamp with time zone,
    roles jsonb,
    created_by uuid,
    created_at timestamp with time zone DEFAULT now(),
    modified_by uuid,
    modified_at timestamp with time zone DEFAULT now()
);

--
-- CONSTRAINT: api_keys api_keys_client_id_key
--
ALTER TABLE ONLY api_keys
    ADD CONSTRAINT api_keys_client_id_key UNIQUE (client_id);

--
-- CONSTRAINT: api_keys api_keys_pkey
--
ALTER TABLE ONLY api_keys
    ADD CONSTRAINT api_keys_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: audit_logs audit_logs_pkey
--
ALTER TABLE ONLY audit_logs
    ADD CONSTRAINT audit_logs_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: business_accounts business_account_account_id
--
ALTER TABLE ONLY business_accounts
    ADD CONSTRAINT business_account_account_id UNIQUE (account_id);

--
-- CONSTRAINT: business_accounts business_account_pkey
--
ALTER TABLE ONLY business_accounts
    ADD CONSTRAINT business_account_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: login_history login_history_pkey
--
ALTER TABLE ONLY login_history
    ADD CONSTRAINT login_history_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: roles role_pkey
--
ALTER TABLE ONLY roles
    ADD CONSTRAINT role_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: users users_credential_id_key
--
ALTER TABLE ONLY users
    ADD CONSTRAINT users_credential_id_key UNIQUE (credential_id);

--
-- CONSTRAINT: users users_email_key
--
ALTER TABLE ONLY users
    ADD CONSTRAINT users_email_key UNIQUE (email);

--
-- CONSTRAINT: users users_phone_number_key
--
ALTER TABLE ONLY users
    ADD CONSTRAINT users_phone_number_key UNIQUE (phone_number);

--
-- CONSTRAINT: users users_pkey
--
ALTER TABLE ONLY users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);

--
-- INDEX: idx_audit_logs_actor_id
--
CREATE INDEX idx_audit_logs_actor_id ON audit_logs USING btree (actor_id);

--
-- INDEX: idx_audit_logs_created_at
--
CREATE INDEX idx_audit_logs_created_at ON audit_logs USING btree (created_at DESC);

--
-- INDEX: idx_audit_logs_entity
--
CREATE INDEX idx_audit_logs_entity ON audit_logs USING btree (entity_type, entity_id);

--
-- INDEX: idx_audit_logs_new_values
--
CREATE INDEX idx_audit_logs_new_values ON audit_logs USING gin (new_values);

--
-- INDEX: idx_login_history_login_time
--
CREATE INDEX idx_login_history_login_time ON login_history USING btree (login_time DESC);

--
-- INDEX: idx_login_history_user_id
--
CREATE INDEX idx_login_history_user_id ON login_history USING btree (user_id);

--
-- INDEX: idx_login_history_user_status
--
CREATE INDEX idx_login_history_user_status ON login_history USING btree (user_id, status) WHERE ((status)::text = 'FAILED'::text);
