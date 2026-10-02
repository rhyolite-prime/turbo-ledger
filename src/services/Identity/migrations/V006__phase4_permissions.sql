--
-- V006__phase4_permissions.sql — Phase 4: Customer domain permission catalog
-- additions.
--
-- These codes are enforced entirely from the gateway-signed TL-Context (the
-- caller's permission set is resolved once at signin and embedded in the JWT
-- by UserService — see plan §2.3/§2.4), so Customer never needs a network
-- round trip back to Identity to authorize a request.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    -- customer: clients (core CRUD)
    ('customer', 'READ_CLIENT',                   'CLIENT',              'READ'),
    ('customer', 'CREATE_CLIENT',                 'CLIENT',              'CREATE'),
    ('customer', 'UPDATE_CLIENT',                 'CLIENT',              'UPDATE'),
    ('customer', 'DELETE_CLIENT',                 'CLIENT',              'DELETE'),
    -- customer: client lifecycle & transfer commands
    ('customer', 'ACTIVATE_CLIENT',               'CLIENT',              'ACTIVATE'),
    ('customer', 'CLOSE_CLIENT',                  'CLIENT',              'CLOSE'),
    ('customer', 'REJECT_CLIENT',                 'CLIENT',              'REJECT'),
    ('customer', 'WITHDRAW_CLIENT',               'CLIENT',              'WITHDRAW'),
    ('customer', 'REACTIVATE_CLIENT',             'CLIENT',              'REACTIVATE'),
    ('customer', 'UNDOREJECTION_CLIENT',          'CLIENT',              'UNDOREJECTION'),
    ('customer', 'UNDOWITHDRAWAL_CLIENT',         'CLIENT',              'UNDOWITHDRAWAL'),
    ('customer', 'ASSIGNSTAFF_CLIENT',            'CLIENT',              'ASSIGNSTAFF'),
    ('customer', 'UNASSIGNSTAFF_CLIENT',          'CLIENT',              'UNASSIGNSTAFF'),
    ('customer', 'UPDATESAVINGSACCOUNT_CLIENT',   'CLIENT',              'UPDATESAVINGSACCOUNT'),
    ('customer', 'PROPOSETRANSFER_CLIENT',        'CLIENT',              'PROPOSETRANSFER'),
    ('customer', 'WITHDRAWTRANSFER_CLIENT',       'CLIENT',              'WITHDRAWTRANSFER'),
    ('customer', 'ACCEPTTRANSFER_CLIENT',         'CLIENT',              'ACCEPTTRANSFER'),
    ('customer', 'REJECTTRANSFER_CLIENT',         'CLIENT',              'REJECTTRANSFER'),
    -- customer: client addresses
    ('customer', 'READ_CLIENTADDRESS',            'CLIENTADDRESS',       'READ'),
    ('customer', 'CREATE_CLIENTADDRESS',          'CLIENTADDRESS',       'CREATE'),
    ('customer', 'UPDATE_CLIENTADDRESS',          'CLIENTADDRESS',       'UPDATE'),
    -- customer: client identifiers
    ('customer', 'READ_CLIENTIDENTIFIER',         'CLIENTIDENTIFIER',    'READ'),
    ('customer', 'CREATE_CLIENTIDENTIFIER',       'CLIENTIDENTIFIER',    'CREATE'),
    ('customer', 'UPDATE_CLIENTIDENTIFIER',       'CLIENTIDENTIFIER',    'UPDATE'),
    ('customer', 'DELETE_CLIENTIDENTIFIER',       'CLIENTIDENTIFIER',    'DELETE'),
    -- customer: client family members
    ('customer', 'READ_CLIENTFAMILYMEMBER',       'CLIENTFAMILYMEMBER',  'READ'),
    ('customer', 'CREATE_CLIENTFAMILYMEMBER',     'CLIENTFAMILYMEMBER',  'CREATE'),
    ('customer', 'UPDATE_CLIENTFAMILYMEMBER',     'CLIENTFAMILYMEMBER',  'UPDATE'),
    ('customer', 'DELETE_CLIENTFAMILYMEMBER',     'CLIENTFAMILYMEMBER',  'DELETE'),
    -- customer: client-level collateral pledges
    ('customer', 'READ_CLIENTCOLLATERAL',         'CLIENTCOLLATERAL',    'READ'),
    ('customer', 'CREATE_CLIENTCOLLATERAL',       'CLIENTCOLLATERAL',    'CREATE'),
    ('customer', 'UPDATE_CLIENTCOLLATERAL',       'CLIENTCOLLATERAL',    'UPDATE'),
    ('customer', 'DELETE_CLIENTCOLLATERAL',       'CLIENTCOLLATERAL',    'DELETE'),
    -- customer: client charges
    ('customer', 'READ_CLIENTCHARGE',             'CLIENTCHARGE',        'READ'),
    ('customer', 'CREATE_CLIENTCHARGE',           'CLIENTCHARGE',        'CREATE'),
    ('customer', 'DELETE_CLIENTCHARGE',           'CLIENTCHARGE',        'DELETE'),
    ('customer', 'PAY_CLIENTCHARGE',              'CLIENTCHARGE',        'PAY'),
    ('customer', 'WAIVE_CLIENTCHARGE',            'CLIENTCHARGE',        'WAIVE'),
    -- customer: client transactions
    ('customer', 'READ_CLIENTTRANSACTION',        'CLIENTTRANSACTION',   'READ'),
    ('customer', 'UNDO_CLIENTTRANSACTION',        'CLIENTTRANSACTION',   'UNDO'),
    -- customer: collateral-management (product-level registry)
    ('customer', 'READ_COLLATERALPRODUCT',        'COLLATERALPRODUCT',   'READ'),
    ('customer', 'CREATE_COLLATERALPRODUCT',      'COLLATERALPRODUCT',   'CREATE'),
    ('customer', 'UPDATE_COLLATERALPRODUCT',      'COLLATERALPRODUCT',   'UPDATE'),
    ('customer', 'DELETE_COLLATERALPRODUCT',      'COLLATERALPRODUCT',   'DELETE')
ON CONFLICT (code) DO NOTHING;

-- Extend the "Admin" role template to the new Phase 4 grouping, matching the
-- precedent set for Phase 2's organization/systemconfig groupings in V004
-- and Phase 3's accounting grouping in V005.
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'customer'
ON CONFLICT DO NOTHING;
