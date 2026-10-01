--
-- V013__phase8_notification_permissions.sql — Phase 8: Notification domain
-- permission catalog additions (notifications, sms, smscampaigns, email,
-- emailcampaign, emailconfiguration, reportmailingjob).
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
-- Idempotent: safe to re-run.
--
<<<<<<< HEAD
INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    ('notification', 'READ_NOTIFICATION',          'NOTIFICATION',          'READ'),
    ('notification', 'UPDATE_NOTIFICATION',         'NOTIFICATION',          'UPDATE'),
=======

INSERT INTO permissions (grouping, code, entity_name, action_name) VALUES
    ('notification', 'READ_NOTIFICATION',          'NOTIFICATION',          'READ'),
    ('notification', 'UPDATE_NOTIFICATION',         'NOTIFICATION',          'UPDATE'),

>>>>>>> ad0f45f820be566765966e7fc4527c466864dcb5
    ('notification', 'READ_SMS',                    'SMS',                   'READ'),
    ('notification', 'CREATE_SMS',                  'SMS',                   'CREATE'),
    ('notification', 'UPDATE_SMS',                  'SMS',                   'UPDATE'),
    ('notification', 'DELETE_SMS',                  'SMS',                   'DELETE'),
<<<<<<< HEAD
=======

>>>>>>> ad0f45f820be566765966e7fc4527c466864dcb5
    ('notification', 'READ_SMSCAMPAIGN',            'SMSCAMPAIGN',           'READ'),
    ('notification', 'CREATE_SMSCAMPAIGN',          'SMSCAMPAIGN',           'CREATE'),
    ('notification', 'UPDATE_SMSCAMPAIGN',          'SMSCAMPAIGN',           'UPDATE'),
    ('notification', 'DELETE_SMSCAMPAIGN',          'SMSCAMPAIGN',           'DELETE'),
    ('notification', 'EXECUTE_SMSCAMPAIGN',         'SMSCAMPAIGN',           'EXECUTE'),
<<<<<<< HEAD
    ('notification', 'READ_EMAILCONFIGURATION',     'EMAILCONFIGURATION',    'READ'),
    ('notification', 'UPDATE_EMAILCONFIGURATION',   'EMAILCONFIGURATION',    'UPDATE'),
=======

    ('notification', 'READ_EMAILCONFIGURATION',     'EMAILCONFIGURATION',    'READ'),
    ('notification', 'UPDATE_EMAILCONFIGURATION',   'EMAILCONFIGURATION',    'UPDATE'),

>>>>>>> ad0f45f820be566765966e7fc4527c466864dcb5
    ('notification', 'READ_EMAILCAMPAIGN',          'EMAILCAMPAIGN',         'READ'),
    ('notification', 'CREATE_EMAILCAMPAIGN',        'EMAILCAMPAIGN',         'CREATE'),
    ('notification', 'UPDATE_EMAILCAMPAIGN',        'EMAILCAMPAIGN',         'UPDATE'),
    ('notification', 'DELETE_EMAILCAMPAIGN',        'EMAILCAMPAIGN',         'DELETE'),
    ('notification', 'EXECUTE_EMAILCAMPAIGN',       'EMAILCAMPAIGN',         'EXECUTE'),
<<<<<<< HEAD
=======

>>>>>>> ad0f45f820be566765966e7fc4527c466864dcb5
    ('notification', 'READ_EMAIL',                  'EMAIL',                 'READ'),
    ('notification', 'CREATE_EMAIL',                'EMAIL',                 'CREATE'),
    ('notification', 'UPDATE_EMAIL',                'EMAIL',                 'UPDATE'),
    ('notification', 'DELETE_EMAIL',                'EMAIL',                 'DELETE'),
<<<<<<< HEAD
=======

>>>>>>> ad0f45f820be566765966e7fc4527c466864dcb5
    ('notification', 'READ_REPORTMAILINGJOB',       'REPORTMAILINGJOB',      'READ'),
    ('notification', 'CREATE_REPORTMAILINGJOB',     'REPORTMAILINGJOB',      'CREATE'),
    ('notification', 'UPDATE_REPORTMAILINGJOB',     'REPORTMAILINGJOB',      'UPDATE'),
    ('notification', 'DELETE_REPORTMAILINGJOB',     'REPORTMAILINGJOB',      'DELETE')
ON CONFLICT (code) DO NOTHING;
<<<<<<< HEAD
=======

>>>>>>> ad0f45f820be566765966e7fc4527c466864dcb5
INSERT INTO role_permissions (role_id, permission_code)
    SELECT r.id, p.code FROM roles r, permissions p
    WHERE r.name = 'Admin' AND p.grouping = 'notification'
ON CONFLICT DO NOTHING;
<<<<<<< HEAD

=======
>>>>>>> ad0f45f820be566765966e7fc4527c466864dcb5
