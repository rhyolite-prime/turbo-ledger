--
-- V001__baseline.sql — generated from src/scripts/TlPortfolio.sql by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

-- extracted from /home/user/turbo-ledger/src/scripts/TlPortfolio.sql
-- source database: TlPortfolio (server 15.14 (Postgres.app), pg_dump 18.4, archive v1.16)

--
-- EXTENSION: uuid-ossp
--

--
-- TABLE: loanproduct_provisioning_entry
--
CREATE TABLE loanproduct_provisioning_entry (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    history_id uuid NOT NULL,
    criteria_id uuid NOT NULL,
    currency_code character varying(3) NOT NULL,
    office_id uuid NOT NULL,
    product_id uuid NOT NULL,
    category_id uuid NOT NULL,
    overdue_in_days bigint DEFAULT 0,
    reseve_amount numeric(20,6) DEFAULT 0.000000,
    liability_account uuid,
    expense_account uuid
);

--
-- TABLE: provisioning_history
--
CREATE TABLE provisioning_history (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    journal_entry_created boolean DEFAULT false,
    createdby_id uuid,
    created_date date,
    lastmodifiedby_id uuid,
    lastmodified_date date
);

--
-- CONSTRAINT: loanproduct_provisioning_entry loanproduct_provisioning_entry_pkey
--
ALTER TABLE ONLY loanproduct_provisioning_entry
    ADD CONSTRAINT loanproduct_provisioning_entry_pkey PRIMARY KEY (id);

--
-- INDEX: idx_loanproduct_provisioning_entry_category_id
--
CREATE INDEX idx_loanproduct_provisioning_entry_category_id ON loanproduct_provisioning_entry USING btree (category_id);

--
-- INDEX: idx_loanproduct_provisioning_entry_criteria_id
--
CREATE INDEX idx_loanproduct_provisioning_entry_criteria_id ON loanproduct_provisioning_entry USING btree (criteria_id);

--
-- INDEX: idx_loanproduct_provisioning_entry_expense_account
--
CREATE INDEX idx_loanproduct_provisioning_entry_expense_account ON loanproduct_provisioning_entry USING btree (expense_account);

--
-- INDEX: idx_loanproduct_provisioning_entry_history_id
--
CREATE INDEX idx_loanproduct_provisioning_entry_history_id ON loanproduct_provisioning_entry USING btree (history_id);

--
-- INDEX: idx_loanproduct_provisioning_entry_liability_account
--
CREATE INDEX idx_loanproduct_provisioning_entry_liability_account ON loanproduct_provisioning_entry USING btree (liability_account);

--
-- INDEX: idx_loanproduct_provisioning_entry_office_id
--
CREATE INDEX idx_loanproduct_provisioning_entry_office_id ON loanproduct_provisioning_entry USING btree (office_id);

--
-- INDEX: idx_loanproduct_provisioning_entry_product_id
--
CREATE INDEX idx_loanproduct_provisioning_entry_product_id ON loanproduct_provisioning_entry USING btree (product_id);

--
-- INDEX: idx_provisioning_history_createdby_id
--
CREATE INDEX idx_provisioning_history_createdby_id ON provisioning_history USING btree (createdby_id);

--
-- INDEX: idx_provisioning_history_lastmodifiedby_id
--
CREATE INDEX idx_provisioning_history_lastmodifiedby_id ON provisioning_history USING btree (lastmodifiedby_id);
