--
-- V005__phase3_permissions.sql — Phase 3: Accounting permission catalog
-- additions.
--
-- These codes are enforced entirely from the gateway-signed TL-Context (the
-- caller's permission set is resolved once at signin and embedded in the JWT
-- by UserService — see plan §2.3/§2.4), so Accounting never needs a network
-- round trip back to Identity to authorize a request.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    -- accounting: chart of accounts
    ('accounting', 'READ_GLACCOUNT',                 'GLACCOUNT',                 'READ'),
    ('accounting', 'CREATE_GLACCOUNT',               'GLACCOUNT',                 'CREATE'),
    ('accounting', 'UPDATE_GLACCOUNT',               'GLACCOUNT',                 'UPDATE'),
    ('accounting', 'DELETE_GLACCOUNT',               'GLACCOUNT',                 'DELETE'),
    -- accounting: closures
    ('accounting', 'READ_GLCLOSURE',                 'GLCLOSURE',                 'READ'),
    ('accounting', 'CREATE_GLCLOSURE',               'GLCLOSURE',                 'CREATE'),
    ('accounting', 'UPDATE_GLCLOSURE',               'GLCLOSURE',                 'UPDATE'),
    ('accounting', 'DELETE_GLCLOSURE',               'GLCLOSURE',                 'DELETE'),
    -- accounting: accounting rules
    ('accounting', 'READ_ACCOUNTINGRULE',            'ACCOUNTINGRULE',            'READ'),
    ('accounting', 'CREATE_ACCOUNTINGRULE',          'ACCOUNTINGRULE',            'CREATE'),
    ('accounting', 'UPDATE_ACCOUNTINGRULE',          'ACCOUNTINGRULE',            'UPDATE'),
    ('accounting', 'DELETE_ACCOUNTINGRULE',          'ACCOUNTINGRULE',            'DELETE'),
    -- accounting: financial activity to account mappings
    ('accounting', 'READ_FINANCIALACTIVITYACCOUNT',  'FINANCIALACTIVITYACCOUNT',  'READ'),
    ('accounting', 'CREATE_FINANCIALACTIVITYACCOUNT','FINANCIALACTIVITYACCOUNT',  'CREATE'),
    ('accounting', 'UPDATE_FINANCIALACTIVITYACCOUNT','FINANCIALACTIVITYACCOUNT',  'UPDATE'),
    ('accounting', 'DELETE_FINANCIALACTIVITYACCOUNT','FINANCIALACTIVITYACCOUNT',  'DELETE'),
    -- accounting: journal entries (create covers post + reverse + running-balance recalc)
    ('accounting', 'READ_JOURNALENTRY',              'JOURNALENTRY',              'READ'),
    ('accounting', 'CREATE_JOURNALENTRY',            'JOURNALENTRY',              'CREATE'),
    ('accounting', 'UPDATE_JOURNALENTRY',            'JOURNALENTRY',              'UPDATE'),
    -- accounting: provisioning entries
    ('accounting', 'READ_PROVISIONINGENTRY',         'PROVISIONINGENTRY',         'READ'),
    ('accounting', 'CREATE_PROVISIONINGENTRY',       'PROVISIONINGENTRY',         'CREATE')
ON CONFLICT (code) DO NOTHING;

-- Extend the "Admin" role template to the new Phase 3 grouping, matching the
-- precedent set for Phase 2's organization/systemconfig groupings in V004.
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'accounting'
ON CONFLICT DO NOTHING;
