--
-- V014__phase9_selfservice_permissions.sql — Phase 9: SelfService domain
-- permission catalog addition.
--
-- Self-service (mobile-banking) users carry no RBAC permission codes of
-- their own — every self/* endpoint's authorization is "does the caller
-- have a self_service_users row linked to the addressed client", enforced
-- inside SelfServiceService, matching real Fineract's separate mobile-user
-- role model (see IMPLEMENTATION_PLAN.md Phase 9 as-built notes).
--
-- The one exception is CREATE_SELFSERVICEUSER: linking an existing Identity
-- platform user id to an existing Customer client id (POST
-- self/registration/user) is an administrative approval action performed
-- by a staff user with ordinary RBAC, not by the self-service user it
-- creates.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    ('selfservice', 'CREATE_SELFSERVICEUSER', 'SELFSERVICEUSER', 'CREATE')
ON CONFLICT (code) DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'selfservice'
ON CONFLICT DO NOTHING;
