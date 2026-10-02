--
-- V011__phase8_heartbeat_permissions.sql — Phase 8: HeartBeat (scheduler)
-- domain (`jobs`, `scheduler`) permission catalog additions.
--
-- EXECUTE_JOB is split from UPDATE_JOB (matching Fineract's own
-- permission model, where triggering a job run is a materially different
-- and more operationally sensitive action than editing its cron
-- configuration).
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    ('heartbeat', 'READ_JOB',         'JOB',       'READ'),
    ('heartbeat', 'UPDATE_JOB',       'JOB',       'UPDATE'),
    ('heartbeat', 'EXECUTE_JOB',      'JOB',       'EXECUTE'),
    ('heartbeat', 'READ_SCHEDULER',   'SCHEDULER', 'READ'),
    ('heartbeat', 'UPDATE_SCHEDULER', 'SCHEDULER', 'UPDATE')
ON CONFLICT (code) DO NOTHING;

-- Extend the "Admin" role template to the new Phase 8 'heartbeat' grouping,
-- matching the precedent set for every prior phase (V004-V010).
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'heartbeat'
ON CONFLICT DO NOTHING;
