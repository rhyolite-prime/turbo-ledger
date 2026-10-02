--
-- V007__phase5_permissions.sql — Phase 5: DepositAccountManagement (deposits)
-- permission catalog additions.
--
-- These codes are enforced entirely from the gateway-signed TL-Context (the
-- caller's permission set is resolved once at signin and embedded in the JWT
-- by UserService — see plan §2.3/§2.4), so DepositAccountManagement never
-- needs a network round trip back to Identity to authorize a request,
-- matching every prior phase's precedent.
--
-- NAMING NOTE: plain savings, fixed-deposit (FD) and recurring-deposit (RD)
-- products/accounts share the same savings_product/savings_account tables
-- (discriminated by deposit_type), but each deposit_type gets ITS OWN
-- permission codes and its own PRODUCT vs ACCOUNT codes — e.g.
-- READ_SAVINGSPRODUCT is distinct from READ_SAVINGSACCOUNT, and both are
-- distinct from READ_FIXEDDEPOSITPRODUCT/READ_FIXEDDEPOSITACCOUNT. This
-- matches Fineract's own permission naming and avoids a caller permissioned
-- for the products catalog implicitly being able to read/write accounts (or
-- vice versa).
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    -- deposits: charges catalog (shared by all deposit products)
    ('deposits', 'READ_CHARGE',                         'CHARGE',                  'READ'),
    ('deposits', 'CREATE_CHARGE',                        'CHARGE',                  'CREATE'),
    ('deposits', 'UPDATE_CHARGE',                        'CHARGE',                  'UPDATE'),
    ('deposits', 'DELETE_CHARGE',                        'CHARGE',                  'DELETE'),
    -- deposits: account number formats
    ('deposits', 'READ_ACCOUNTNUMBERFORMAT',             'ACCOUNTNUMBERFORMAT',     'READ'),
    ('deposits', 'CREATE_ACCOUNTNUMBERFORMAT',           'ACCOUNTNUMBERFORMAT',     'CREATE'),
    ('deposits', 'UPDATE_ACCOUNTNUMBERFORMAT',           'ACCOUNTNUMBERFORMAT',     'UPDATE'),
    ('deposits', 'DELETE_ACCOUNTNUMBERFORMAT',           'ACCOUNTNUMBERFORMAT',     'DELETE'),
    -- deposits: interest rate charts + slabs
    ('deposits', 'READ_INTERESTRATECHART',               'INTERESTRATECHART',       'READ'),
    ('deposits', 'CREATE_INTERESTRATECHART',             'INTERESTRATECHART',       'CREATE'),
    ('deposits', 'UPDATE_INTERESTRATECHART',             'INTERESTRATECHART',       'UPDATE'),
    ('deposits', 'DELETE_INTERESTRATECHART',             'INTERESTRATECHART',       'DELETE'),
    -- deposits: savings products / accounts
    ('deposits', 'READ_SAVINGSPRODUCT',                  'SAVINGSPRODUCT',          'READ'),
    ('deposits', 'CREATE_SAVINGSPRODUCT',                'SAVINGSPRODUCT',          'CREATE'),
    ('deposits', 'UPDATE_SAVINGSPRODUCT',                'SAVINGSPRODUCT',          'UPDATE'),
    ('deposits', 'DELETE_SAVINGSPRODUCT',                'SAVINGSPRODUCT',          'DELETE'),
    ('deposits', 'READ_SAVINGSACCOUNT',                  'SAVINGSACCOUNT',          'READ'),
    ('deposits', 'CREATE_SAVINGSACCOUNT',                'SAVINGSACCOUNT',          'CREATE'),
    ('deposits', 'UPDATE_SAVINGSACCOUNT',                'SAVINGSACCOUNT',          'UPDATE'),
    ('deposits', 'DELETE_SAVINGSACCOUNT',                'SAVINGSACCOUNT',          'DELETE'),
    ('deposits', 'APPROVE_SAVINGSACCOUNT',               'SAVINGSACCOUNT',          'APPROVE'),
    ('deposits', 'REJECT_SAVINGSACCOUNT',                'SAVINGSACCOUNT',          'REJECT'),
    ('deposits', 'WITHDRAW_SAVINGSACCOUNT',              'SAVINGSACCOUNT',          'WITHDRAW'),
    ('deposits', 'ACTIVATE_SAVINGSACCOUNT',              'SAVINGSACCOUNT',          'ACTIVATE'),
    ('deposits', 'CLOSE_SAVINGSACCOUNT',                 'SAVINGSACCOUNT',          'CLOSE'),
    ('deposits', 'ASSIGNSTAFF_SAVINGSACCOUNT',           'SAVINGSACCOUNT',          'ASSIGNSTAFF'),
    -- deposits: fixed deposit products / accounts
    ('deposits', 'READ_FIXEDDEPOSITPRODUCT',             'FIXEDDEPOSITPRODUCT',     'READ'),
    ('deposits', 'CREATE_FIXEDDEPOSITPRODUCT',           'FIXEDDEPOSITPRODUCT',     'CREATE'),
    ('deposits', 'UPDATE_FIXEDDEPOSITPRODUCT',           'FIXEDDEPOSITPRODUCT',     'UPDATE'),
    ('deposits', 'DELETE_FIXEDDEPOSITPRODUCT',           'FIXEDDEPOSITPRODUCT',     'DELETE'),
    ('deposits', 'READ_FIXEDDEPOSITACCOUNT',             'FIXEDDEPOSITACCOUNT',     'READ'),
    ('deposits', 'CREATE_FIXEDDEPOSITACCOUNT',           'FIXEDDEPOSITACCOUNT',     'CREATE'),
    ('deposits', 'UPDATE_FIXEDDEPOSITACCOUNT',           'FIXEDDEPOSITACCOUNT',     'UPDATE'),
    ('deposits', 'DELETE_FIXEDDEPOSITACCOUNT',           'FIXEDDEPOSITACCOUNT',     'DELETE'),
    ('deposits', 'APPROVE_FIXEDDEPOSITACCOUNT',          'FIXEDDEPOSITACCOUNT',     'APPROVE'),
    ('deposits', 'REJECT_FIXEDDEPOSITACCOUNT',           'FIXEDDEPOSITACCOUNT',     'REJECT'),
    ('deposits', 'WITHDRAW_FIXEDDEPOSITACCOUNT',         'FIXEDDEPOSITACCOUNT',     'WITHDRAW'),
    ('deposits', 'ACTIVATE_FIXEDDEPOSITACCOUNT',         'FIXEDDEPOSITACCOUNT',     'ACTIVATE'),
    ('deposits', 'CLOSE_FIXEDDEPOSITACCOUNT',            'FIXEDDEPOSITACCOUNT',     'CLOSE'),
    ('deposits', 'ASSIGNSTAFF_FIXEDDEPOSITACCOUNT',      'FIXEDDEPOSITACCOUNT',     'ASSIGNSTAFF'),
    -- deposits: recurring deposit products / accounts
    ('deposits', 'READ_RECURRINGDEPOSITPRODUCT',         'RECURRINGDEPOSITPRODUCT', 'READ'),
    ('deposits', 'CREATE_RECURRINGDEPOSITPRODUCT',       'RECURRINGDEPOSITPRODUCT', 'CREATE'),
    ('deposits', 'UPDATE_RECURRINGDEPOSITPRODUCT',       'RECURRINGDEPOSITPRODUCT', 'UPDATE'),
    ('deposits', 'DELETE_RECURRINGDEPOSITPRODUCT',       'RECURRINGDEPOSITPRODUCT', 'DELETE'),
    ('deposits', 'READ_RECURRINGDEPOSITACCOUNT',         'RECURRINGDEPOSITACCOUNT', 'READ'),
    ('deposits', 'CREATE_RECURRINGDEPOSITACCOUNT',       'RECURRINGDEPOSITACCOUNT', 'CREATE'),
    ('deposits', 'UPDATE_RECURRINGDEPOSITACCOUNT',       'RECURRINGDEPOSITACCOUNT', 'UPDATE'),
    ('deposits', 'DELETE_RECURRINGDEPOSITACCOUNT',       'RECURRINGDEPOSITACCOUNT', 'DELETE'),
    ('deposits', 'APPROVE_RECURRINGDEPOSITACCOUNT',      'RECURRINGDEPOSITACCOUNT', 'APPROVE'),
    ('deposits', 'REJECT_RECURRINGDEPOSITACCOUNT',       'RECURRINGDEPOSITACCOUNT', 'REJECT'),
    ('deposits', 'WITHDRAW_RECURRINGDEPOSITACCOUNT',     'RECURRINGDEPOSITACCOUNT', 'WITHDRAW'),
    ('deposits', 'ACTIVATE_RECURRINGDEPOSITACCOUNT',     'RECURRINGDEPOSITACCOUNT', 'ACTIVATE'),
    ('deposits', 'CLOSE_RECURRINGDEPOSITACCOUNT',        'RECURRINGDEPOSITACCOUNT', 'CLOSE'),
    ('deposits', 'ASSIGNSTAFF_RECURRINGDEPOSITACCOUNT',  'RECURRINGDEPOSITACCOUNT', 'ASSIGNSTAFF'),
    -- deposits: account charges (per-account charge instances)
    ('deposits', 'READ_SAVINGSACCOUNTCHARGE',            'SAVINGSACCOUNTCHARGE',    'READ'),
    ('deposits', 'CREATE_SAVINGSACCOUNTCHARGE',          'SAVINGSACCOUNTCHARGE',    'CREATE'),
    ('deposits', 'UPDATE_SAVINGSACCOUNTCHARGE',          'SAVINGSACCOUNTCHARGE',    'UPDATE'),
    ('deposits', 'DELETE_SAVINGSACCOUNTCHARGE',          'SAVINGSACCOUNTCHARGE',    'DELETE'),
    -- deposits: account transactions (deposit/withdrawal/interest/fees + undo/adjust)
    ('deposits', 'READ_SAVINGSACCOUNTTRANSACTION',       'SAVINGSACCOUNTTRANSACTION', 'READ'),
    ('deposits', 'CREATE_SAVINGSACCOUNTTRANSACTION',     'SAVINGSACCOUNTTRANSACTION', 'CREATE'),
    ('deposits', 'UPDATE_SAVINGSACCOUNTTRANSACTION',     'SAVINGSACCOUNTTRANSACTION', 'UPDATE'),
    -- deposits: account-to-account transfers
    ('deposits', 'READ_ACCOUNTTRANSFER',                 'ACCOUNTTRANSFER',         'READ'),
    ('deposits', 'CREATE_ACCOUNTTRANSFER',               'ACCOUNTTRANSFER',         'CREATE'),
    -- deposits: standing instructions (+ run history)
    ('deposits', 'READ_STANDINGINSTRUCTION',             'STANDINGINSTRUCTION',     'READ'),
    ('deposits', 'CREATE_STANDINGINSTRUCTION',           'STANDINGINSTRUCTION',     'CREATE'),
    ('deposits', 'UPDATE_STANDINGINSTRUCTION',           'STANDINGINSTRUCTION',     'UPDATE')
ON CONFLICT (code) DO NOTHING;

-- Extend the "Admin" role template to the new Phase 5 grouping, matching the
-- precedent set for Phase 2's organization/systemconfig groupings in V004,
-- Phase 3's accounting grouping in V005, and Phase 4's customer grouping in
-- V006.
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'deposits'
ON CONFLICT DO NOTHING;
