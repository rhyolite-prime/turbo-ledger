--
-- V012__phase8_template_permissions.sql — Phase 8: Template domain
-- permission catalog additions.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    ('template', 'READ_TEMPLATE',   'TEMPLATE', 'READ'),
    ('template', 'CREATE_TEMPLATE', 'TEMPLATE', 'CREATE'),
    ('template', 'UPDATE_TEMPLATE', 'TEMPLATE', 'UPDATE'),
    ('template', 'DELETE_TEMPLATE', 'TEMPLATE', 'DELETE')
ON CONFLICT (code) DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'template'
ON CONFLICT DO NOTHING;
