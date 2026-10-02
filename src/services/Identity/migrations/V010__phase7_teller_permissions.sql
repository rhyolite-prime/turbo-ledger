--
-- V010__phase7_teller_permissions.sql — Phase 7: Teller domain
-- (`tellers`, `cashiers`, `cashiersjournal`) permission catalog additions.
-- Completes Phase 7 alongside the Group retrofit added in V009.
--
-- Cash movement (allocate/settle) gets its own fine-grained codes rather
-- than being folded into UPDATE_CASHIER, matching Fineract's own
-- ALLOCATECASH_CASHIER/SETTLECASH_CASHIER permission split (a teller
-- supervisor role might manage cashier rosters without touching the cash
-- vault, or vice versa).
--
-- `cashiersjournal` (the standalone `GET /cashiersjournal` global view) and
-- `cashiers` (the standalone `GET /cashiers` global view) both read the
-- same underlying tables as the nested teller endpoints, so they reuse
-- READ_CASHIER / READ_CASHIERTRANSACTIONS rather than minting new codes —
-- same precedent as grouplevels reusing READ_GROUPLEVEL for its one route.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    -- teller: core CRUD + teller-level transaction/journal views
    ('teller', 'READ_TELLER',               'TELLER',             'READ'),
    ('teller', 'CREATE_TELLER',             'TELLER',             'CREATE'),
    ('teller', 'UPDATE_TELLER',             'TELLER',             'UPDATE'),
    ('teller', 'DELETE_TELLER',             'TELLER',             'DELETE'),
    -- teller: cashiers (nested roster under a teller, and the standalone
    -- `GET /cashiers` global view)
    ('teller', 'READ_CASHIER',              'CASHIER',            'READ'),
    ('teller', 'CREATE_CASHIER',            'CASHIER',            'CREATE'),
    ('teller', 'UPDATE_CASHIER',            'CASHIER',            'UPDATE'),
    ('teller', 'DELETE_CASHIER',            'CASHIER',            'DELETE'),
    -- teller: cashier cash movement
    ('teller', 'ALLOCATECASH_CASHIER',      'CASHIER',            'ALLOCATECASH'),
    ('teller', 'SETTLECASH_CASHIER',        'CASHIER',            'SETTLECASH'),
    -- teller: cashier transaction history (cashier-nested, summary, and the
    -- standalone `GET /cashiersjournal` global view)
    ('teller', 'READ_CASHIERTRANSACTIONS',  'CASHIERTRANSACTION', 'READ')
ON CONFLICT (code) DO NOTHING;

-- Extend the "Admin" role template to the new Phase 7 'teller' grouping,
-- matching the precedent set for every prior phase (V004-V009).
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'teller'
ON CONFLICT DO NOTHING;
