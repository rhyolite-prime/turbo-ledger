--
-- V003__phase7_group.sql — Phase 7 additions on top of the real pg_dump
-- baseline (V001__baseline.sql, from TlGroupDb) and the platform outbox
-- (V002__platform.sql).
--
-- The real dump already ships Fineract's actual design for `groups` (one
-- table for both "Group" and "Center" — Fineract itself treats a Center as
-- just a Group one level up the hierarchy, discriminated by `level_id`) and
-- `group_roles` (client role assignments within a group). Two things a
-- Fineract-complete schema needs are missing from that dump and are added
-- here instead of hand-editing the generated V001 file:
--
--   1. `group_levels` — Fineract seeds exactly two fixed levels at install
--      time (id=1 "Center", parentLevel=null; id=2 "Group",
--      parentLevel=1). `groups.level_id` already exists as a column with no
--      real table behind it; this gives it one, and GroupsController /
--      CentersController simply filter `groups` by `level_id` — same
--      "one physical table, two logical resources discriminated by a type
--      column" pattern already used in this codebase for
--      SavingsAccount.deposit_type (DAM) and PortfolioService's share
--      account "type" path segment.
--
--   2. `group_clients` — client↔group membership. Fineract's real schema
--      has `m_group_client` for this; the dump's `groups`/`group_roles`
--      pair has no equivalent, so associateClients/disassociateClients/
--      transferClients (and GSIM's groupId-driven member list in DAM) has
--      nothing to read from without it.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

CREATE TABLE IF NOT EXISTS group_levels (
    id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    parent_level_id uuid REFERENCES group_levels(id),
    level_name varchar(50) NOT NULL UNIQUE,
    super_parent boolean NOT NULL DEFAULT false,
    created_at timestamptz NOT NULL DEFAULT now()
);

-- client_id/group_id are cross-service/cross-table opaque ids, trusted as
-- given (see every other phase's "cross-service ids intentionally trusted"
-- precedent) — client_id in particular lives in the Customer service's own
-- database, not this one.
CREATE TABLE IF NOT EXISTS group_clients (
    id uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    group_id uuid NOT NULL REFERENCES groups(id) ON DELETE CASCADE,
    client_id uuid NOT NULL,
    created_at timestamptz NOT NULL DEFAULT now(),
    UNIQUE (group_id, client_id)
);

CREATE INDEX IF NOT EXISTS idx_group_clients_group_id ON group_clients (group_id);
CREATE INDEX IF NOT EXISTS idx_group_clients_client_id ON group_clients (client_id);

-- Seed the two fixed Fineract group levels. Fixed, well-known names (not
-- ids) are matched by GroupService at startup-of-request time to resolve
-- "the Center level" / "the Group level" — same spirit as this codebase
-- resolving Fineract's fixed code values by name elsewhere.
INSERT INTO group_levels (parent_level_id, level_name, super_parent)
VALUES (NULL, 'Center', true)
ON CONFLICT (level_name) DO NOTHING;

INSERT INTO group_levels (parent_level_id, level_name, super_parent)
SELECT id, 'Group', false FROM group_levels WHERE level_name = 'Center'
ON CONFLICT (level_name) DO NOTHING;
