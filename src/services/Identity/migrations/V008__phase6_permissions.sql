--
-- V008__phase6_permissions.sql — Phase 6: Portfolio (lending & shares)
-- permission catalog additions.
--
-- These codes are enforced entirely from the gateway-signed TL-Context (the
-- caller's permission set is resolved once at signin and embedded in the
-- JWT by UserService — see plan §2.3/§2.4), so Portfolio never needs a
-- network round trip back to Identity to authorize a request, matching
-- every prior phase's precedent.
--
-- SCOPE NOTE: this single 'portfolio' grouping covers lending (loan
-- products, loans + every loan sub-resource, reschedule requests, rates/
-- floating rates, delinquency buckets/provisioning), shares (products,
-- dividends, accounts) and the external-asset-owner / credit-bureau
-- surfaces. A handful of loan sub-resources (collateral, guarantors,
-- charges, disbursement details, interest pauses, post-dated checks,
-- buydown fees, capitalized income, delinquency actions/tags,
-- transactions, GLIM, COB catch-up, reschedule requests,
-- external-asset-owner transfers, loan-product attributes) are
-- intentionally NOT given their own CRUD permission codes beyond the ones
-- below where they are always reached through (and permission-gated by)
-- their parent loan's READ_LOAN/UPDATE_LOAN/CREATE_LOAN/DELETE_LOAN check
-- in PortfolioService — the exceptions are loan charges, loan collateral
-- and loan guarantors, which Fineract itself permissions independently
-- (e.g. a teller role might manage guarantors without full loan-edit
-- rights), so those three keep their own READ/CREATE/UPDATE/DELETE codes.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    -- portfolio: loan products
    ('portfolio', 'READ_LOANPRODUCT',                    'LOANPRODUCT',             'READ'),
    ('portfolio', 'CREATE_LOANPRODUCT',                  'LOANPRODUCT',             'CREATE'),
    ('portfolio', 'UPDATE_LOANPRODUCT',                  'LOANPRODUCT',             'UPDATE'),
    -- portfolio: rates + floating rates (used by loan products' interest terms)
    ('portfolio', 'READ_RATE',                           'RATE',                    'READ'),
    ('portfolio', 'CREATE_RATE',                         'RATE',                    'CREATE'),
    ('portfolio', 'UPDATE_RATE',                         'RATE',                    'UPDATE'),
    ('portfolio', 'READ_FLOATINGRATE',                   'FLOATINGRATE',            'READ'),
    ('portfolio', 'CREATE_FLOATINGRATE',                 'FLOATINGRATE',            'CREATE'),
    ('portfolio', 'UPDATE_FLOATINGRATE',                 'FLOATINGRATE',            'UPDATE'),
    -- portfolio: delinquency buckets + ranges
    ('portfolio', 'READ_DELINQUENCY_BUCKET',             'DELINQUENCY_BUCKET',      'READ'),
    ('portfolio', 'CREATE_DELINQUENCY_BUCKET',           'DELINQUENCY_BUCKET',      'CREATE'),
    ('portfolio', 'UPDATE_DELINQUENCY_BUCKET',           'DELINQUENCY_BUCKET',      'UPDATE'),
    ('portfolio', 'DELETE_DELINQUENCY_BUCKET',           'DELINQUENCY_BUCKET',      'DELETE'),
    -- portfolio: NPA provisioning category + criteria
    ('portfolio', 'READ_PROVISIONCATEGORY',              'PROVISIONCATEGORY',       'READ'),
    ('portfolio', 'CREATE_PROVISIONCATEGORY',            'PROVISIONCATEGORY',       'CREATE'),
    ('portfolio', 'UPDATE_PROVISIONCATEGORY',            'PROVISIONCATEGORY',       'UPDATE'),
    ('portfolio', 'DELETE_PROVISIONCATEGORY',            'PROVISIONCATEGORY',       'DELETE'),
    ('portfolio', 'READ_PROVISIONCRITERIA',              'PROVISIONCRITERIA',       'READ'),
    ('portfolio', 'CREATE_PROVISIONCRITERIA',            'PROVISIONCRITERIA',       'CREATE'),
    ('portfolio', 'UPDATE_PROVISIONCRITERIA',            'PROVISIONCRITERIA',       'UPDATE'),
    ('portfolio', 'DELETE_PROVISIONCRITERIA',            'PROVISIONCRITERIA',       'DELETE'),
    -- portfolio: loans (core + full lifecycle — also gates every
    -- sub-resource reached via a loan id: schedule, transactions,
    -- disbursement details, interest pauses, post-dated checks, buydown
    -- fees, capitalized income, delinquency actions/tags, GLIM, COB,
    -- reschedule requests, asset-owner transfers, loan-product attributes)
    ('portfolio', 'READ_LOAN',                           'LOAN',                    'READ'),
    ('portfolio', 'CREATE_LOAN',                         'LOAN',                    'CREATE'),
    ('portfolio', 'UPDATE_LOAN',                         'LOAN',                    'UPDATE'),
    ('portfolio', 'DELETE_LOAN',                         'LOAN',                    'DELETE'),
    ('portfolio', 'APPROVE_LOAN',                        'LOAN',                    'APPROVE'),
    ('portfolio', 'REJECT_LOAN',                         'LOAN',                    'REJECT'),
    ('portfolio', 'WITHDRAW_LOAN',                       'LOAN',                    'WITHDRAW'),
    ('portfolio', 'DISBURSE_LOAN',                       'LOAN',                    'DISBURSE'),
    ('portfolio', 'CLOSE_LOAN',                          'LOAN',                    'CLOSE'),
    ('portfolio', 'WRITEOFF_LOAN',                       'LOAN',                    'WRITEOFF'),
    ('portfolio', 'ASSIGNSTAFF_LOAN',                    'LOAN',                    'ASSIGNSTAFF'),
    -- portfolio: loan charges / collateral / guarantors (independently
    -- permissioned sub-resources — see scope note above)
    ('portfolio', 'READ_LOANCHARGE',                     'LOANCHARGE',              'READ'),
    ('portfolio', 'CREATE_LOANCHARGE',                   'LOANCHARGE',              'CREATE'),
    ('portfolio', 'UPDATE_LOANCHARGE',                   'LOANCHARGE',              'UPDATE'),
    ('portfolio', 'DELETE_LOANCHARGE',                   'LOANCHARGE',              'DELETE'),
    ('portfolio', 'READ_LOANCOLLATERAL',                 'LOANCOLLATERAL',          'READ'),
    ('portfolio', 'CREATE_LOANCOLLATERAL',               'LOANCOLLATERAL',          'CREATE'),
    ('portfolio', 'UPDATE_LOANCOLLATERAL',               'LOANCOLLATERAL',          'UPDATE'),
    ('portfolio', 'DELETE_LOANCOLLATERAL',               'LOANCOLLATERAL',          'DELETE'),
    ('portfolio', 'READ_LOANGUARANTOR',                  'LOANGUARANTOR',           'READ'),
    ('portfolio', 'CREATE_LOANGUARANTOR',                'LOANGUARANTOR',           'CREATE'),
    ('portfolio', 'UPDATE_LOANGUARANTOR',                'LOANGUARANTOR',           'UPDATE'),
    ('portfolio', 'DELETE_LOANGUARANTOR',                'LOANGUARANTOR',           'DELETE'),
    -- portfolio: share products (+ dividends, reached via the same code)
    ('portfolio', 'READ_SHAREPRODUCT',                   'SHAREPRODUCT',            'READ'),
    ('portfolio', 'CREATE_SHAREPRODUCT',                 'SHAREPRODUCT',            'CREATE'),
    ('portfolio', 'UPDATE_SHAREPRODUCT',                 'SHAREPRODUCT',            'UPDATE'),
    -- portfolio: share accounts (+ additional-shares / redemption commands)
    ('portfolio', 'READ_SHAREACCOUNT',                   'SHAREACCOUNT',            'READ'),
    ('portfolio', 'CREATE_SHAREACCOUNT',                 'SHAREACCOUNT',            'CREATE'),
    ('portfolio', 'UPDATE_SHAREACCOUNT',                 'SHAREACCOUNT',            'UPDATE'),
    ('portfolio', 'APPROVE_SHAREACCOUNT',                'SHAREACCOUNT',            'APPROVE'),
    ('portfolio', 'ACTIVATE_SHAREACCOUNT',               'SHAREACCOUNT',            'ACTIVATE'),
    ('portfolio', 'CLOSE_SHAREACCOUNT',                  'SHAREACCOUNT',            'CLOSE'),
    -- portfolio: credit bureau configuration + integration (report fetch/save)
    ('portfolio', 'READ_CREDITBUREAU',                   'CREDITBUREAU',            'READ'),
    ('portfolio', 'UPDATE_CREDITBUREAU',                 'CREDITBUREAU',            'UPDATE')
ON CONFLICT (code) DO NOTHING;

-- Extend the "Admin" role template to the new Phase 6 grouping, matching the
-- precedent set for Phase 2's organization/systemconfig groupings in V004,
-- Phase 3's accounting grouping in V005, Phase 4's customer grouping in
-- V006, and Phase 5's deposits grouping in V007.
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'portfolio'
ON CONFLICT DO NOTHING;
