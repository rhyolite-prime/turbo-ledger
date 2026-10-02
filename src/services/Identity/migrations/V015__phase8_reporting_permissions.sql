--
-- V015__phase8_reporting_permissions.sql — Phase 8: Reporting service
-- permission catalog addition.
--
-- READ_REPORT covers both browsing report_definitions (ReportsController)
-- and executing them (RunReportsController); CREATE/UPDATE/DELETE_REPORT
-- gate authoring custom report definitions (seeded core reports are
-- additionally protected from deletion at the data layer via is_core).
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    ('reporting', 'READ_REPORT',   'REPORT', 'READ'),
    ('reporting', 'CREATE_REPORT', 'REPORT', 'CREATE'),
    ('reporting', 'UPDATE_REPORT', 'REPORT', 'UPDATE'),
    ('reporting', 'DELETE_REPORT', 'REPORT', 'DELETE')
ON CONFLICT (code) DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'reporting'
ON CONFLICT DO NOTHING;
