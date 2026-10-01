--
-- V009__phase7_group_permissions.sql — Phase 7 (retrofit): Group domain
-- (`groups`, `centers`, `grouplevels`) permission catalog additions.
--
-- Lifecycle-command codes are entity-scoped the same way DAM's savings
-- account commands are (APPROVE_SAVINGSACCOUNT-style, see V007) rather than
-- bundled under a single generic code, matching Fineract's own
-- fine-grained permission model (e.g. a teller role might manage group
-- client associations without full group-edit rights).
--
-- `grouplevels` is read-only (no CRUD surface — the two rows are seeded by
-- migration) so it only gets a READ code.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    -- group: core CRUD + lifecycle
    ('group', 'READ_GROUP',               'GROUP',       'READ'),
    ('group', 'CREATE_GROUP',             'GROUP',       'CREATE'),
    ('group', 'UPDATE_GROUP',             'GROUP',       'UPDATE'),
    ('group', 'DELETE_GROUP',             'GROUP',       'DELETE'),
    ('group', 'ACTIVATE_GROUP',           'GROUP',       'ACTIVATE'),
    ('group', 'CLOSE_GROUP',              'GROUP',       'CLOSE'),
    ('group', 'ASSIGNSTAFF_GROUP',        'GROUP',       'ASSIGNSTAFF'),
    ('group', 'ASSOCIATECLIENTS_GROUP',   'GROUP',       'ASSOCIATECLIENTS'),
    ('group', 'ASSIGNROLE_GROUP',         'GROUP',       'ASSIGNROLE'),
    -- group: center core CRUD + lifecycle (same `groups` table, "Center" level)
    ('group', 'READ_CENTER',              'CENTER',      'READ'),
    ('group', 'CREATE_CENTER',            'CENTER',      'CREATE'),
    ('group', 'UPDATE_CENTER',            'CENTER',      'UPDATE'),
    ('group', 'DELETE_CENTER',            'CENTER',      'DELETE'),
    ('group', 'ACTIVATE_CENTER',          'CENTER',      'ACTIVATE'),
    ('group', 'CLOSE_CENTER',             'CENTER',      'CLOSE'),
    ('group', 'ASSIGNSTAFF_CENTER',       'CENTER',      'ASSIGNSTAFF'),
    ('group', 'ASSOCIATEGROUPS_CENTER',   'CENTER',      'ASSOCIATEGROUPS'),
    -- group: grouplevels (read-only lookup)
    ('group', 'READ_GROUPLEVEL',          'GROUPLEVEL',  'READ')
ON CONFLICT (code) DO NOTHING;

-- Extend the "Admin" role template to the new Phase 7 'group' grouping,
-- matching the precedent set for every prior phase (V004-V008).
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'group'
ON CONFLICT DO NOTHING;
