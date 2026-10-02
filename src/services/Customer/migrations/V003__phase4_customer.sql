--
-- V003__phase4_customer.sql — Phase 4 (Customer domain) additions.
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--
-- What this adds:
--   1. `collateral_management` — the product-level collateral registry
--      backing the top-level `collateral-management` (6) endpoint group.
--      `client_collateral_management.collateral_id` (V001) pointed at this
--      table conceptually but the table itself never existed — a real gap,
--      same class of bug as Phase 3's accounting_rules int/uuid mismatch.
--   2. `client_family_members` — backs `clients/:id/familymembers` (6); no
--      table existed for it at all in the V001 baseline.
--   3. FK tightening for every client_* child table that referenced
--      client(id) (or another child table) by bare uuid with no constraint,
--      mirroring Phase 2/3's FK-tightening passes on other services' V001
--      baselines.
--   4. Client risk attributes (⭐ modern addition per IMPLEMENTATION_PLAN.md
--      Phase 4: KYC status, risk rating, FATCA/CRS flags) as first-class
--      columns on `client`, ahead of Compliance (Phase 9+) consuming them.
--   5. Audit columns (created_by/created_at/updated_by/updated_at) on the
--      two child tables that lacked any (client_address,
--      client_collateral_management), plus real uniqueness constraints
--      Fineract itself enforces (account_no, external_id, identifier
--      client+type+key).
--

-- ---------------------------------------------------------------------
-- 1. Product-level collateral registry
-- ---------------------------------------------------------------------
CREATE TABLE collateral_management (
    id            uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    name          character varying(200) NOT NULL,
    quality       character varying(200),
    base_price    numeric(19,6),
    currency_code character varying(3),
    pct_to_base   numeric(19,6),
    unit_type     character varying(200),
    created_by    uuid,
    created_at    timestamp with time zone DEFAULT now(),
    updated_by    uuid,
    updated_at    timestamp with time zone DEFAULT now()
);

-- ---------------------------------------------------------------------
-- 2. Client family members
-- ---------------------------------------------------------------------
CREATE TABLE client_family_members (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    client_id           uuid NOT NULL REFERENCES client(id),
    firstname           character varying(80) NOT NULL,
    middlename          character varying(80),
    lastname            character varying(80) NOT NULL,
    qualification       character varying(100),
    mobile_number       character varying(20),
    age                 integer,
    is_dependent        boolean NOT NULL DEFAULT false,
    relationship_cv_id  uuid,
    marital_status_cv_id uuid,
    gender_cv_id        uuid,
    date_of_birth       date,
    profession_cv_id    uuid,
    created_by          uuid,
    created_at          timestamp with time zone DEFAULT now(),
    updated_by          uuid,
    updated_at          timestamp with time zone DEFAULT now()
);
CREATE INDEX idx_client_family_members_client ON client_family_members (client_id);

-- ---------------------------------------------------------------------
-- 3. FK tightening on V001 child tables (all previously bare uuid columns)
-- ---------------------------------------------------------------------
ALTER TABLE client_address
    ALTER COLUMN client_id SET NOT NULL,
    ADD CONSTRAINT fk_client_address_client FOREIGN KEY (client_id) REFERENCES client(id),
    ADD COLUMN created_by uuid,
    ADD COLUMN created_at timestamp with time zone DEFAULT now(),
    ADD COLUMN updated_by uuid,
    ADD COLUMN updated_at timestamp with time zone DEFAULT now();

ALTER TABLE client_charge
    ADD CONSTRAINT fk_client_charge_client FOREIGN KEY (client_id) REFERENCES client(id);

ALTER TABLE client_charge_paid_by
    ADD CONSTRAINT fk_client_charge_paid_by_charge FOREIGN KEY (client_charge_id) REFERENCES client_charge(id),
    ADD CONSTRAINT fk_client_charge_paid_by_txn FOREIGN KEY (client_transaction_id) REFERENCES client_transaction(id);

ALTER TABLE client_collateral_management
    ALTER COLUMN client_id SET NOT NULL,
    ALTER COLUMN collateral_id SET NOT NULL,
    ADD CONSTRAINT fk_client_collateral_client FOREIGN KEY (client_id) REFERENCES client(id),
    ADD CONSTRAINT fk_client_collateral_collateral FOREIGN KEY (collateral_id) REFERENCES collateral_management(id),
    ADD COLUMN created_by uuid,
    ADD COLUMN created_at timestamp with time zone DEFAULT now(),
    ADD COLUMN updated_by uuid,
    ADD COLUMN updated_at timestamp with time zone DEFAULT now();

ALTER TABLE client_identifier
    ADD CONSTRAINT fk_client_identifier_client FOREIGN KEY (client_id) REFERENCES client(id),
    ADD CONSTRAINT uq_client_identifier UNIQUE (client_id, document_type_id, document_key);

ALTER TABLE client_non_person
    ADD CONSTRAINT fk_client_non_person_client FOREIGN KEY (client_id) REFERENCES client(id),
    ADD CONSTRAINT uq_client_non_person_client UNIQUE (client_id);

ALTER TABLE client_transaction
    ADD CONSTRAINT fk_client_transaction_client FOREIGN KEY (client_id) REFERENCES client(id);

ALTER TABLE client_transfer_details
    ADD CONSTRAINT fk_client_transfer_details_client FOREIGN KEY (client_id) REFERENCES client(id);

-- ---------------------------------------------------------------------
-- 4. Client risk attributes (⭐ modern addition, consumed by Compliance later)
-- ---------------------------------------------------------------------
ALTER TABLE client
    ADD COLUMN kyc_status  integer NOT NULL DEFAULT 100, -- 100=PENDING,200=VERIFIED,300=REJECTED (local enum, see CustomerService.cc)
    ADD COLUMN risk_rating integer NOT NULL DEFAULT 100, -- 100=LOW,200=MEDIUM,300=HIGH
    ADD COLUMN fatca_flag  boolean NOT NULL DEFAULT false,
    ADD COLUMN crs_flag    boolean NOT NULL DEFAULT false;

-- Real uniqueness constraints Fineract itself enforces.
ALTER TABLE client ADD CONSTRAINT uq_client_account_no UNIQUE (account_no);
CREATE UNIQUE INDEX uq_client_external_id ON client (external_id) WHERE external_id IS NOT NULL;
