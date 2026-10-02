--
-- V004__phase2_permissions.sql — Phase 2: Organization & SystemConfig permission
-- catalog additions.
--
-- These codes are enforced entirely from the gateway-signed TL-Context (the
-- caller's permission set is resolved once at signin and embedded in the JWT
-- by UserService — see plan §2.3/§2.4), so Organization/SystemConfig never
-- need a network round trip back to Identity to authorize a request.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    -- organization: offices
    ('organization', 'READ_OFFICE',              'OFFICE',              'READ'),
    ('organization', 'CREATE_OFFICE',             'OFFICE',              'CREATE'),
    ('organization', 'UPDATE_OFFICE',             'OFFICE',              'UPDATE'),
    ('organization', 'DELETE_OFFICE',             'OFFICE',              'DELETE'),
    -- organization: office transactions
    ('organization', 'READ_OFFICETRANSACTION',    'OFFICETRANSACTION',   'READ'),
    ('organization', 'CREATE_OFFICETRANSACTION',  'OFFICETRANSACTION',   'CREATE'),
    ('organization', 'DELETE_OFFICETRANSACTION',  'OFFICETRANSACTION',   'DELETE'),
    -- organization: staff
    ('organization', 'READ_STAFF',                'STAFF',               'READ'),
    ('organization', 'CREATE_STAFF',               'STAFF',              'CREATE'),
    ('organization', 'UPDATE_STAFF',               'STAFF',              'UPDATE'),
    -- organization: holidays
    ('organization', 'READ_HOLIDAY',              'HOLIDAY',             'READ'),
    ('organization', 'CREATE_HOLIDAY',            'HOLIDAY',             'CREATE'),
    ('organization', 'UPDATE_HOLIDAY',            'HOLIDAY',             'UPDATE'),
    ('organization', 'DELETE_HOLIDAY',            'HOLIDAY',             'DELETE'),
    ('organization', 'ACTIVATE_HOLIDAY',          'HOLIDAY',             'ACTIVATE'),
    -- organization: working days
    ('organization', 'READ_WORKINGDAYS',          'WORKINGDAYS',         'READ'),
    ('organization', 'UPDATE_WORKINGDAYS',        'WORKINGDAYS',         'UPDATE'),
    -- organization: currencies
    ('organization', 'READ_CURRENCY',             'CURRENCY',            'READ'),
    ('organization', 'UPDATE_CURRENCY',           'CURRENCY',            'UPDATE'),
    -- organization: funds
    ('organization', 'READ_FUND',                 'FUND',                'READ'),
    ('organization', 'CREATE_FUND',               'FUND',                'CREATE'),
    ('organization', 'UPDATE_FUND',               'FUND',                'UPDATE'),
    -- organization: payment types
    ('organization', 'READ_PAYMENTTYPE',          'PAYMENTTYPE',         'READ'),
    ('organization', 'CREATE_PAYMENTTYPE',        'PAYMENTTYPE',         'CREATE'),
    ('organization', 'UPDATE_PAYMENTTYPE',        'PAYMENTTYPE',         'UPDATE'),
    ('organization', 'DELETE_PAYMENTTYPE',        'PAYMENTTYPE',         'DELETE'),
    -- organization: entity to entity mapping
    ('organization', 'READ_ENTITYTOENTITYMAPPING',   'ENTITYTOENTITYMAPPING', 'READ'),
    ('organization', 'CREATE_ENTITYTOENTITYMAPPING', 'ENTITYTOENTITYMAPPING', 'CREATE'),
    ('organization', 'UPDATE_ENTITYTOENTITYMAPPING', 'ENTITYTOENTITYMAPPING', 'UPDATE'),
    ('organization', 'DELETE_ENTITYTOENTITYMAPPING', 'ENTITYTOENTITYMAPPING', 'DELETE'),
    -- organization: taxes
    ('organization', 'READ_TAXCOMPONENT',         'TAXCOMPONENT',        'READ'),
    ('organization', 'CREATE_TAXCOMPONENT',       'TAXCOMPONENT',        'CREATE'),
    ('organization', 'UPDATE_TAXCOMPONENT',       'TAXCOMPONENT',        'UPDATE'),
    ('organization', 'READ_TAXGROUP',             'TAXGROUP',            'READ'),
    ('organization', 'CREATE_TAXGROUP',           'TAXGROUP',            'CREATE'),
    ('organization', 'UPDATE_TAXGROUP',           'TAXGROUP',            'UPDATE'),
    -- systemconfig: codes
    ('systemconfig', 'READ_CODE',                 'CODE',                'READ'),
    ('systemconfig', 'CREATE_CODE',               'CODE',                'CREATE'),
    ('systemconfig', 'UPDATE_CODE',               'CODE',                'UPDATE'),
    ('systemconfig', 'DELETE_CODE',               'CODE',                'DELETE'),
    ('systemconfig', 'READ_CODEVALUE',            'CODEVALUE',           'READ'),
    ('systemconfig', 'CREATE_CODEVALUE',          'CODEVALUE',           'CREATE'),
    ('systemconfig', 'UPDATE_CODEVALUE',          'CODEVALUE',           'UPDATE'),
    ('systemconfig', 'DELETE_CODEVALUE',          'CODEVALUE',           'DELETE'),
    -- systemconfig: global configuration
    ('systemconfig', 'READ_CONFIGURATION',        'CONFIGURATION',       'READ'),
    ('systemconfig', 'UPDATE_CONFIGURATION',      'CONFIGURATION',       'UPDATE'),
    -- systemconfig: external services / events
    ('systemconfig', 'READ_EXTERNALSERVICE',      'EXTERNALSERVICE',     'READ'),
    ('systemconfig', 'UPDATE_EXTERNALSERVICE',    'EXTERNALSERVICE',     'UPDATE'),
    ('systemconfig', 'READ_EXTERNALEVENTS',       'EXTERNALEVENTS',      'READ'),
    ('systemconfig', 'UPDATE_EXTERNALEVENTS',     'EXTERNALEVENTS',      'UPDATE'),
    -- systemconfig: audits / hooks / caches / business date / field config
    ('systemconfig', 'READ_AUDIT',                'AUDIT',               'READ'),
    ('systemconfig', 'READ_HOOK',                 'HOOK',                'READ'),
    ('systemconfig', 'CREATE_HOOK',               'HOOK',                'CREATE'),
    ('systemconfig', 'UPDATE_HOOK',               'HOOK',                'UPDATE'),
    ('systemconfig', 'DELETE_HOOK',               'HOOK',                'DELETE'),
    ('systemconfig', 'READ_CACHE',                'CACHE',               'READ'),
    ('systemconfig', 'UPDATE_CACHE',              'CACHE',               'UPDATE'),
    ('systemconfig', 'READ_BUSINESSDATE',         'BUSINESSDATE',        'READ'),
    ('systemconfig', 'UPDATE_BUSINESSDATE',       'BUSINESSDATE',        'UPDATE'),
    ('systemconfig', 'READ_FIELDCONFIGURATION',   'FIELDCONFIGURATION',  'READ'),
    -- systemconfig: datatables
    ('systemconfig', 'READ_DATATABLE',            'DATATABLE',           'READ'),
    ('systemconfig', 'CREATE_DATATABLE',          'DATATABLE',           'CREATE'),
    ('systemconfig', 'UPDATE_DATATABLE',          'DATATABLE',           'UPDATE'),
    ('systemconfig', 'DELETE_DATATABLE',          'DATATABLE',           'DELETE'),
    ('systemconfig', 'CREATE_ENTITYDATATABLECHECK','ENTITYDATATABLECHECK','CREATE'),
    ('systemconfig', 'READ_ENTITYDATATABLECHECK', 'ENTITYDATATABLECHECK','READ'),
    ('systemconfig', 'DELETE_ENTITYDATATABLECHECK','ENTITYDATATABLECHECK','DELETE'),
    -- systemconfig: imports
    ('systemconfig', 'READ_IMPORT',               'IMPORT',              'READ'),
    -- systemconfig: generic entity documents/notes/images/calendars/meetings
    ('systemconfig', 'READ_DOCUMENT',             'DOCUMENT',            'READ'),
    ('systemconfig', 'CREATE_DOCUMENT',           'DOCUMENT',            'CREATE'),
    ('systemconfig', 'UPDATE_DOCUMENT',           'DOCUMENT',            'UPDATE'),
    ('systemconfig', 'DELETE_DOCUMENT',           'DOCUMENT',            'DELETE'),
    ('systemconfig', 'READ_NOTE',                 'NOTE',                'READ'),
    ('systemconfig', 'CREATE_NOTE',               'NOTE',                'CREATE'),
    ('systemconfig', 'UPDATE_NOTE',               'NOTE',                'UPDATE'),
    ('systemconfig', 'DELETE_NOTE',               'NOTE',                'DELETE'),
    ('systemconfig', 'READ_IMAGE',                'IMAGE',               'READ'),
    ('systemconfig', 'CREATE_IMAGE',              'IMAGE',               'CREATE'),
    ('systemconfig', 'UPDATE_IMAGE',              'IMAGE',               'UPDATE'),
    ('systemconfig', 'DELETE_IMAGE',              'IMAGE',               'DELETE'),
    ('systemconfig', 'READ_CALENDAR',             'CALENDAR',            'READ'),
    ('systemconfig', 'CREATE_CALENDAR',           'CALENDAR',            'CREATE'),
    ('systemconfig', 'UPDATE_CALENDAR',           'CALENDAR',            'UPDATE'),
    ('systemconfig', 'DELETE_CALENDAR',           'CALENDAR',            'DELETE'),
    ('systemconfig', 'READ_MEETING',              'MEETING',             'READ'),
    ('systemconfig', 'CREATE_MEETING',            'MEETING',             'CREATE'),
    ('systemconfig', 'UPDATE_MEETING',            'MEETING',             'UPDATE'),
    ('systemconfig', 'DELETE_MEETING',            'MEETING',             'DELETE')
ON CONFLICT (code) DO NOTHING;

-- The "Admin" role template already gets every 'identity'/'special' permission
-- (V003); extend it to the new Phase 2 groupings so a seeded tenant admin
-- (Super user role, which already holds ALL_FUNCTIONS) or an "Admin"
-- delegate can manage reference data out of the box.
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping IN ('organization', 'systemconfig')
ON CONFLICT DO NOTHING;
