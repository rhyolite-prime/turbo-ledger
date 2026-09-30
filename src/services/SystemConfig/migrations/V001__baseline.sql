--
-- V001__baseline.sql — generated from src/scripts/TlSystemConfigDb.sql by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

-- extracted from /home/user/turbo-ledger/src/scripts/TlSystemConfigDb.sql
-- source database: TlSystemConfigDb (server 15.14 (Postgres.app), pg_dump 18.4, archive v1.16)

--
-- EXTENSION: uuid-ossp
--

--
-- TABLE: code
--
CREATE TABLE code (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    code_name character varying(100) DEFAULT NULL::character varying,
    is_system_defined boolean DEFAULT false NOT NULL
);

--
-- TABLE: code_value
--
CREATE TABLE code_value (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    code_id uuid NOT NULL,
    code_value character varying(100) DEFAULT NULL::character varying,
    code_description character varying(500) DEFAULT NULL::character varying,
    order_position integer DEFAULT 0 NOT NULL,
    code_score integer,
    is_active boolean DEFAULT true NOT NULL,
    is_mandatory boolean DEFAULT false NOT NULL
);

--
-- CONSTRAINT: code code_code_name_key
--
ALTER TABLE ONLY code
    ADD CONSTRAINT code_code_name_key UNIQUE (code_name);

--
-- CONSTRAINT: code code_pkey
--
ALTER TABLE ONLY code
    ADD CONSTRAINT code_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: code_value code_value_code_id_code_value_key
--
ALTER TABLE ONLY code_value
    ADD CONSTRAINT code_value_code_id_code_value_key UNIQUE (code_id, code_value);

--
-- CONSTRAINT: code_value code_value_pkey
--
ALTER TABLE ONLY code_value
    ADD CONSTRAINT code_value_pkey PRIMARY KEY (id);

--
-- INDEX: idx_code_value_code_id
--
CREATE INDEX idx_code_value_code_id ON code_value USING btree (code_id);

--
-- FK CONSTRAINT: code_value fk_code_value_code_id
--
ALTER TABLE ONLY code_value
    ADD CONSTRAINT fk_code_value_code_id FOREIGN KEY (code_id) REFERENCES code(id);
