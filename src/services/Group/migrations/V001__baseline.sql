--
-- V001__baseline.sql — generated from src/scripts/TlGroupDb.sql by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

-- extracted from /home/user/turbo-ledger/src/scripts/TlGroupDb.sql
-- source database: TlGroupDb (server 15.14 (Postgres.app), pg_dump 18.4, archive v1.16)

--
-- EXTENSION: uuid-ossp
--

--
-- TABLE: group_roles
--
CREATE TABLE group_roles (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    client_id uuid,
    group_id uuid,
    role_cv_id uuid
);

--
-- TABLE: groups
--
CREATE TABLE groups (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    external_id character varying(100) DEFAULT NULL::character varying,
    status_enum integer DEFAULT 300 NOT NULL,
    activation_date date,
    office_id uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    staff_id uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    parent_id uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    level_id uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    display_name character varying(100) NOT NULL,
    hierarchy character varying(100) DEFAULT NULL::character varying,
    closure_reason_cv_id uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    closedon_date date,
    activatedon_userid uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    submittedon_date date,
    submittedon_userid uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    closedon_userid uuid DEFAULT '00000000-0000-0000-0000-000000000000'::uuid NOT NULL,
    account_no character varying(20) NOT NULL
);

--
-- CONSTRAINT: group_roles group_roles_client_id_group_id_role_cv_id_key
--
ALTER TABLE ONLY group_roles
    ADD CONSTRAINT group_roles_client_id_group_id_role_cv_id_key UNIQUE (client_id, group_id, role_cv_id);

--
-- CONSTRAINT: group_roles group_roles_pkey
--
ALTER TABLE ONLY group_roles
    ADD CONSTRAINT group_roles_pkey PRIMARY KEY (id);

--
-- CONSTRAINT: groups groups_display_name_level_id_key
--
ALTER TABLE ONLY groups
    ADD CONSTRAINT groups_display_name_level_id_key UNIQUE (display_name, level_id);

--
-- CONSTRAINT: groups groups_external_id_key
--
ALTER TABLE ONLY groups
    ADD CONSTRAINT groups_external_id_key UNIQUE (external_id);

--
-- CONSTRAINT: groups groups_external_id_level_id_key
--
ALTER TABLE ONLY groups
    ADD CONSTRAINT groups_external_id_level_id_key UNIQUE (external_id, level_id);

--
-- CONSTRAINT: groups groups_pkey
--
ALTER TABLE ONLY groups
    ADD CONSTRAINT groups_pkey PRIMARY KEY (id);

--
-- INDEX: idx_group_closure_reason_cv_id
--
CREATE INDEX idx_group_closure_reason_cv_id ON groups USING btree (closure_reason_cv_id);

--
-- INDEX: idx_group_level_id
--
CREATE INDEX idx_group_level_id ON groups USING btree (level_id);

--
-- INDEX: idx_group_office_id
--
CREATE INDEX idx_group_office_id ON groups USING btree (office_id);

--
-- INDEX: idx_group_parent_id
--
CREATE INDEX idx_group_parent_id ON groups USING btree (parent_id);

--
-- INDEX: idx_group_roles_client_id
--
CREATE INDEX idx_group_roles_client_id ON group_roles USING btree (client_id);

--
-- INDEX: idx_group_roles_group_id
--
CREATE INDEX idx_group_roles_group_id ON group_roles USING btree (group_id);

--
-- INDEX: idx_group_roles_role_cv_id
--
CREATE INDEX idx_group_roles_role_cv_id ON group_roles USING btree (role_cv_id);

--
-- INDEX: idx_group_staff_id
--
CREATE INDEX idx_group_staff_id ON groups USING btree (staff_id);
