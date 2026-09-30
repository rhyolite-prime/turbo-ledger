--
-- V003__rbac_maker_checker.sql — Phase 1: tenant-scoped RBAC + maker-checker.
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--

-- ---------------------------------------------------------------------------
-- Permission catalog (Fineract-style grouping/code/entity/action)
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS permissions (
    id                 uuid        DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    grouping           varchar(45) NOT NULL,
    code               varchar(100) NOT NULL UNIQUE,
    entity_name        varchar(100),
    action_name        varchar(100),
    can_maker_checker  boolean     NOT NULL DEFAULT false
);

-- ---------------------------------------------------------------------------
-- Role <-> permission and user <-> role mappings
-- ---------------------------------------------------------------------------
ALTER TABLE roles ADD COLUMN IF NOT EXISTS is_disabled boolean NOT NULL DEFAULT false;
CREATE UNIQUE INDEX IF NOT EXISTS uq_roles_name ON roles (name);

CREATE TABLE IF NOT EXISTS role_permissions (
    role_id          uuid         NOT NULL REFERENCES roles (id) ON DELETE CASCADE,
    permission_code  varchar(100) NOT NULL REFERENCES permissions (code) ON DELETE CASCADE,
    PRIMARY KEY (role_id, permission_code)
);

CREATE TABLE IF NOT EXISTS user_roles (
    user_id  uuid NOT NULL REFERENCES users (id) ON DELETE CASCADE,
    role_id  uuid NOT NULL REFERENCES roles (id) ON DELETE CASCADE,
    PRIMARY KEY (user_id, role_id)
);

-- ---------------------------------------------------------------------------
-- Maker-checker command store (Fineract: m_portfolio_command_source)
-- ---------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS tl_commands (
    id               uuid         DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY,
    action           varchar(100) NOT NULL,           -- permission code, e.g. CREATE_USER
    entity_name      varchar(100),
    resource_id      varchar(80),
    payload          jsonb        NOT NULL DEFAULT '{}'::jsonb,
    status           varchar(20)  NOT NULL DEFAULT 'PENDING',
    maker_id         uuid,
    maker_username   varchar(100),
    made_on          timestamptz  NOT NULL DEFAULT now(),
    checker_id       uuid,
    checker_username varchar(100),
    checked_on       timestamptz,
    result           jsonb,
    failure_reason   varchar(500),
    CONSTRAINT chk_tl_commands_status CHECK
        (status IN ('PENDING', 'APPROVED', 'REJECTED', 'FAILED', 'DELETED'))
);
CREATE INDEX IF NOT EXISTS idx_tl_commands_status ON tl_commands (status, made_on DESC);

-- ---------------------------------------------------------------------------
-- Seed: permission catalog
-- ---------------------------------------------------------------------------
INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    ('special',       'ALL_FUNCTIONS',        NULL,           NULL),
    ('special',       'ALL_FUNCTIONS_READ',   NULL,           NULL),
    ('special',       'CHECKER_SUPER_USER',   NULL,           NULL),
    ('identity',      'READ_USER',            'USER',         'READ'),
    ('identity',      'CREATE_USER',          'USER',         'CREATE'),
    ('identity',      'UPDATE_USER',          'USER',         'UPDATE'),
    ('identity',      'DELETE_USER',          'USER',         'DELETE'),
    ('identity',      'ACTIVATE_USER',        'USER',         'ACTIVATE'),
    ('identity',      'DEACTIVATE_USER',      'USER',         'DEACTIVATE'),
    ('identity',      'LOCK_USER',            'USER',         'LOCK'),
    ('identity',      'UNLOCK_USER',          'USER',         'UNLOCK'),
    ('identity',      'ASSIGNROLES_USER',     'USER',         'ASSIGNROLES'),
    ('identity',      'READ_ROLE',            'ROLE',         'READ'),
    ('identity',      'CREATE_ROLE',          'ROLE',         'CREATE'),
    ('identity',      'UPDATE_ROLE',          'ROLE',         'UPDATE'),
    ('identity',      'DELETE_ROLE',          'ROLE',         'DELETE'),
    ('identity',      'ENABLE_ROLE',          'ROLE',         'ENABLE'),
    ('identity',      'DISABLE_ROLE',         'ROLE',         'DISABLE'),
    ('identity',      'PERMISSIONS_ROLE',     'ROLE',         'PERMISSIONS'),
    ('identity',      'READ_PERMISSION',      'PERMISSION',   'READ'),
    ('identity',      'UPDATE_PERMISSION',    'PERMISSION',   'UPDATE'),
    ('identity',      'READ_MAKERCHECKER',    'MAKERCHECKER', 'READ'),
    ('identity',      'APPROVE_MAKERCHECKER', 'MAKERCHECKER', 'APPROVE'),
    ('identity',      'REJECT_MAKERCHECKER',  'MAKERCHECKER', 'REJECT'),
    ('identity',      'DELETE_MAKERCHECKER',  'MAKERCHECKER', 'DELETE'),
    ('accounting',    'READ_GLACCOUNT',       'GLACCOUNT',    'READ'),
    ('accounting',    'CREATE_GLACCOUNT',     'GLACCOUNT',    'CREATE'),
    ('accounting',    'UPDATE_GLACCOUNT',     'GLACCOUNT',    'UPDATE'),
    ('accounting',    'DELETE_GLACCOUNT',     'GLACCOUNT',    'DELETE'),
    ('accounting',    'READ_JOURNALENTRY',    'JOURNALENTRY', 'READ'),
    ('accounting',    'CREATE_JOURNALENTRY',  'JOURNALENTRY', 'CREATE'),
    ('accounting',    'REVERSE_JOURNALENTRY', 'JOURNALENTRY', 'REVERSE')
ON CONFLICT (code) DO NOTHING;

-- ---------------------------------------------------------------------------
-- Seed: role templates
-- ---------------------------------------------------------------------------
INSERT INTO roles (name, description, permissions) VALUES
    ('Super user',   'All permissions, including approvals',           '[]'::jsonb),
    ('Admin',        'Full identity administration',                   '[]'::jsonb),
    ('Teller',       'Front-office cash operations',                   '[]'::jsonb),
    ('Loan officer', 'Loan origination and management',                '[]'::jsonb),
    ('Self-service', 'Customer self-service access',                   '[]'::jsonb)
ON CONFLICT (name) DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Super user' AND p.code IN ('ALL_FUNCTIONS', 'CHECKER_SUPER_USER')
ON CONFLICT DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping IN ('identity', 'special')
      AND p.code <> 'ALL_FUNCTIONS'
ON CONFLICT DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Teller'
      AND p.code IN ('ALL_FUNCTIONS_READ', 'READ_JOURNALENTRY', 'CREATE_JOURNALENTRY')
ON CONFLICT DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Loan officer' AND p.code IN ('ALL_FUNCTIONS_READ')
ON CONFLICT DO NOTHING;

INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Self-service' AND p.code IN ('READ_USER')
ON CONFLICT DO NOTHING;
