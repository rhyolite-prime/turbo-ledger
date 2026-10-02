--
-- V003__seed_core_reports.sql — the locked "core_set" catalog of 10 banking /
-- business / accounting reports (11 rows: Identity's "Active Users & Audit
-- Trail" bullet is split into two reports since they read different tables).
--
-- Every report here is is_core = true (cannot be deleted via ReportsController,
-- only deactivated) and targets exactly one data_source — no in-engine
-- cross-service joins. Report ids are fixed (deterministic, namespaced UUIDv5)
-- so they are identical across every tenant schema. Idempotent: safe to re-run.
--

-- ---------------------------------------------------------------------------
-- 1. Trial Balance (accounting)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    'b887dbe9-b53b-5d69-95bc-25cc2b21d089',
    'Trial Balance',
    'Accounting',
    'accounting',
    'SELECT a.gl_code AS "glCode", a.name AS "accountName", ' ||
    '       CASE a.classification WHEN 1 THEN ''ASSET'' WHEN 2 THEN ''LIABILITY'' WHEN 3 THEN ''EQUITY'' ' ||
    '            WHEN 4 THEN ''INCOME'' WHEN 5 THEN ''EXPENSE'' ELSE ''UNKNOWN'' END AS "accountType", ' ||
    '       COALESCE(SUM(CASE WHEN je.type_enum = 2 THEN je.amount ELSE 0 END), 0) AS "totalDebit", ' ||
    '       COALESCE(SUM(CASE WHEN je.type_enum = 1 THEN je.amount ELSE 0 END), 0) AS "totalCredit" ' ||
    'FROM accounts a ' ||
    'LEFT JOIN journal_entries je ON je.account_id = a.id AND je.reversed = false ' ||
    '                             AND je.entry_date <= ${asOfDate}::date ' ||
    'WHERE a.account_usage = 1 AND a.disabled = false ' ||
    'GROUP BY a.id, a.gl_code, a.name, a.classification ' ||
    'ORDER BY a.gl_code',
    'Postable GL account balances (debit/credit) as of a given date.',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT 'b887dbe9-b53b-5d69-95bc-25cc2b21d089', 'asOfDate', 'As of date', 'DATE', true, 1
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = 'b887dbe9-b53b-5d69-95bc-25cc2b21d089' AND parameter_name = 'asOfDate');

-- ---------------------------------------------------------------------------
-- 2. Income Statement (accounting)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '52bfd5f6-7e90-534d-baaf-6b1885a42671',
    'Income Statement',
    'Accounting',
    'accounting',
    'SELECT a.gl_code AS "glCode", a.name AS "accountName", ' ||
    '       CASE a.classification WHEN 4 THEN ''INCOME'' WHEN 5 THEN ''EXPENSE'' ELSE ''UNKNOWN'' END AS "accountType", ' ||
    '       COALESCE(SUM(CASE WHEN a.classification = 4 THEN (CASE WHEN je.type_enum = 1 THEN je.amount ELSE -je.amount END) ' ||
    '                         ELSE (CASE WHEN je.type_enum = 2 THEN je.amount ELSE -je.amount END) END), 0) AS "netAmount" ' ||
    'FROM accounts a ' ||
    'LEFT JOIN journal_entries je ON je.account_id = a.id AND je.reversed = false ' ||
    '                             AND je.entry_date BETWEEN ${fromDate}::date AND ${toDate}::date ' ||
    'WHERE a.classification IN (4, 5) AND a.account_usage = 1 AND a.disabled = false ' ||
    'GROUP BY a.id, a.gl_code, a.name, a.classification ' ||
    'ORDER BY a.classification, a.gl_code',
    'Net income/expense activity per GL account over a date range (P&L).',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT v.report_id, v.name, v.label, 'DATE', true, v.ord
FROM (VALUES
    ('52bfd5f6-7e90-534d-baaf-6b1885a42671'::uuid, 'fromDate', 'From date', 1),
    ('52bfd5f6-7e90-534d-baaf-6b1885a42671'::uuid, 'toDate',   'To date',   2)
) AS v(report_id, name, label, ord)
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = v.report_id AND parameter_name = v.name);

-- ---------------------------------------------------------------------------
-- 3. Balance Sheet (accounting)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '35c8947c-17c3-5497-a40a-ce0f6991dd76',
    'Balance Sheet',
    'Accounting',
    'accounting',
    'SELECT a.gl_code AS "glCode", a.name AS "accountName", ' ||
    '       CASE a.classification WHEN 1 THEN ''ASSET'' WHEN 2 THEN ''LIABILITY'' WHEN 3 THEN ''EQUITY'' ELSE ''UNKNOWN'' END AS "accountType", ' ||
    '       COALESCE(SUM(CASE WHEN a.classification = 1 THEN (CASE WHEN je.type_enum = 2 THEN je.amount ELSE -je.amount END) ' ||
    '                         ELSE (CASE WHEN je.type_enum = 1 THEN je.amount ELSE -je.amount END) END), 0) AS "netBalance" ' ||
    'FROM accounts a ' ||
    'LEFT JOIN journal_entries je ON je.account_id = a.id AND je.reversed = false ' ||
    '                             AND je.entry_date <= ${asOfDate}::date ' ||
    'WHERE a.classification IN (1, 2, 3) AND a.account_usage = 1 AND a.disabled = false ' ||
    'GROUP BY a.id, a.gl_code, a.name, a.classification ' ||
    'ORDER BY a.classification, a.gl_code',
    'Asset/Liability/Equity balances as of a given date.',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT '35c8947c-17c3-5497-a40a-ce0f6991dd76', 'asOfDate', 'As of date', 'DATE', true, 1
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = '35c8947c-17c3-5497-a40a-ce0f6991dd76' AND parameter_name = 'asOfDate');

-- ---------------------------------------------------------------------------
-- 4. GL Account Statement (accounting)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    'a7c7c9c9-bf2a-53f7-9e2b-1ae8b7199256',
    'GL Account Statement',
    'Accounting',
    'accounting',
    'SELECT je.entry_date AS "entryDate", je.transaction_id AS "transactionId", ' ||
    '       CASE je.type_enum WHEN 1 THEN ''CREDIT'' WHEN 2 THEN ''DEBIT'' ELSE ''UNKNOWN'' END AS "entryType", ' ||
    '       je.amount AS "amount", je.description AS "description", ' ||
    '       je.manual_entry AS "manualEntry", je.reversed AS "reversed" ' ||
    'FROM journal_entries je ' ||
    'JOIN accounts a ON a.id = je.account_id ' ||
    'WHERE a.gl_code = ${glCode}::varchar ' ||
    '  AND je.entry_date BETWEEN ${fromDate}::date AND ${toDate}::date ' ||
    'ORDER BY je.entry_date, je.created_date',
    'Journal entry detail (ledger) for a single GL account over a date range.',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT v.report_id, v.name, v.label, v.ptype, true, v.ord
FROM (VALUES
    ('a7c7c9c9-bf2a-53f7-9e2b-1ae8b7199256'::uuid, 'glCode',   'GL code',   'STRING', 1),
    ('a7c7c9c9-bf2a-53f7-9e2b-1ae8b7199256'::uuid, 'fromDate', 'From date', 'DATE',   2),
    ('a7c7c9c9-bf2a-53f7-9e2b-1ae8b7199256'::uuid, 'toDate',   'To date',   'DATE',   3)
) AS v(report_id, name, label, ptype, ord)
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = v.report_id AND parameter_name = v.name);

-- ---------------------------------------------------------------------------
-- 5. Loan Portfolio Summary (portfolio)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '9fd631ef-0748-5c1c-97b2-507e39290689',
    'Loan Portfolio Summary',
    'Portfolio',
    'portfolio',
    'SELECT lp.name AS "productName", l.status AS "statusCode", ' ||
    '       CASE l.status WHEN 100 THEN ''SUBMITTED_PENDING_APPROVAL'' WHEN 200 THEN ''APPROVED'' WHEN 300 THEN ''ACTIVE'' ' ||
    '            WHEN 400 THEN ''WITHDRAWN_BY_CLIENT'' WHEN 500 THEN ''REJECTED'' WHEN 600 THEN ''CLOSED_OBLIGATIONS_MET'' ' ||
    '            WHEN 601 THEN ''CLOSED_WRITTEN_OFF'' WHEN 602 THEN ''CLOSED_RESCHEDULED'' WHEN 700 THEN ''OVERPAID'' ' ||
    '            ELSE ''OTHER'' END AS "status", ' ||
    '       COUNT(*) AS "loanCount", ' ||
    '       COALESCE(SUM(l.principal_disbursed), 0) AS "totalDisbursed", ' ||
    '       COALESCE(SUM(l.principal_disbursed - l.principal_paid - l.principal_writtenoff), 0) AS "outstandingPrincipal", ' ||
    '       COALESCE(SUM(l.interest_charged - l.interest_paid - l.interest_waived - l.interest_writtenoff), 0) AS "outstandingInterest" ' ||
    'FROM loan l ' ||
    'JOIN loan_product lp ON lp.id = l.product_id ' ||
    'WHERE l.submitted_on_date BETWEEN ${fromDate}::date AND ${toDate}::date ' ||
    'GROUP BY lp.name, l.status ' ||
    'ORDER BY lp.name, l.status',
    'Loan counts and outstanding balances grouped by product and status.',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT v.report_id, v.name, v.label, 'DATE', true, v.ord
FROM (VALUES
    ('9fd631ef-0748-5c1c-97b2-507e39290689'::uuid, 'fromDate', 'From date', 1),
    ('9fd631ef-0748-5c1c-97b2-507e39290689'::uuid, 'toDate',   'To date',   2)
) AS v(report_id, name, label, ord)
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = v.report_id AND parameter_name = v.name);

-- ---------------------------------------------------------------------------
-- 6. Par / Arrears Aging (portfolio)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '9bf4590f-1ef1-5663-b9d1-27c64fec6567',
    'Par/Arrears Aging',
    'Portfolio',
    'portfolio',
    'SELECT lp.name AS "productName", l.account_no AS "accountNo", ' ||
    '       (l.principal_disbursed - l.principal_paid - l.principal_writtenoff) AS "outstandingPrincipal", ' ||
    '       l.overdue_since_date AS "overdueSinceDate", ' ||
    '       (${asOfDate}::date - l.overdue_since_date) AS "daysOverdue", ' ||
    '       COALESCE(dr.classification, ''NOT_CLASSIFIED'') AS "delinquencyClassification", ' ||
    '       l.is_npa AS "isNpa" ' ||
    'FROM loan l ' ||
    'JOIN loan_product lp ON lp.id = l.product_id ' ||
    'LEFT JOIN delinquency_range dr ON dr.id = l.delinquency_range_id ' ||
    'WHERE l.status = 300 AND l.overdue_since_date IS NOT NULL ' ||
    '  AND l.overdue_since_date <= ${asOfDate}::date ' ||
    'ORDER BY "daysOverdue" DESC',
    'Active loans in arrears as of a given date, ordered by days overdue (PAR).',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT '9bf4590f-1ef1-5663-b9d1-27c64fec6567', 'asOfDate', 'As of date', 'DATE', true, 1
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = '9bf4590f-1ef1-5663-b9d1-27c64fec6567' AND parameter_name = 'asOfDate');

-- ---------------------------------------------------------------------------
-- 7. Deposit Portfolio Summary (depositaccountmanagement)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '8476a551-97c6-5672-8795-eef671441e75',
    'Deposit Portfolio Summary',
    'Deposits',
    'depositaccountmanagement',
    'SELECT sp.name AS "productName", ' ||
    '       CASE sa.deposit_type WHEN 100 THEN ''SAVINGS'' WHEN 200 THEN ''FIXED_DEPOSIT'' WHEN 300 THEN ''RECURRING_DEPOSIT'' ELSE ''OTHER'' END AS "depositType", ' ||
    '       CASE sa.status WHEN 100 THEN ''SUBMITTED_PENDING_APPROVAL'' WHEN 200 THEN ''APPROVED'' WHEN 300 THEN ''ACTIVE'' ' ||
    '            WHEN 400 THEN ''WITHDRAWN_BY_CLIENT'' WHEN 500 THEN ''REJECTED'' WHEN 600 THEN ''CLOSED'' ' ||
    '            WHEN 601 THEN ''PREMATURE_CLOSED'' WHEN 602 THEN ''MATURED'' ELSE ''OTHER'' END AS "status", ' ||
    '       COUNT(*) AS "accountCount", ' ||
    '       COALESCE(SUM(sa.account_balance_derived), 0) AS "totalBalance", ' ||
    '       COALESCE(SUM(sa.total_deposits_derived), 0) AS "totalDeposits", ' ||
    '       COALESCE(SUM(sa.total_withdrawals_derived), 0) AS "totalWithdrawals", ' ||
    '       COALESCE(SUM(sa.total_interest_posted_derived), 0) AS "totalInterestPosted" ' ||
    'FROM savings_account sa ' ||
    'JOIN savings_product sp ON sp.id = sa.product_id ' ||
    'WHERE sa.submitted_on_date IS NOT NULL AND sa.submitted_on_date <= ${asOfDate}::date ' ||
    'GROUP BY sp.name, sa.deposit_type, sa.status ' ||
    'ORDER BY sp.name, sa.status',
    'Deposit account counts and balances grouped by product, type and status.',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT '8476a551-97c6-5672-8795-eef671441e75', 'asOfDate', 'As of date', 'DATE', true, 1
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = '8476a551-97c6-5672-8795-eef671441e75' AND parameter_name = 'asOfDate');

-- ---------------------------------------------------------------------------
-- 8. Client Listing (customer)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '7ffb47be-de34-508f-80cd-02cb9b75e266',
    'Client Listing',
    'Customer',
    'customer',
    'SELECT c.account_no AS "accountNo", c.display_name AS "displayName", ' ||
    '       c.mobile_no AS "mobileNo", c.email_address AS "emailAddress", ' ||
    '       CASE c.status WHEN 100 THEN ''PENDING'' WHEN 300 THEN ''ACTIVE'' WHEN 600 THEN ''CLOSED'' ' ||
    '            WHEN 700 THEN ''REJECTED'' WHEN 800 THEN ''WITHDRAWN'' ELSE ''OTHER'' END AS "status", ' ||
    '       c.activation_date AS "activationDate", c.office_id AS "officeId" ' ||
    'FROM client c ' ||
    'WHERE c.submittedon_date BETWEEN ${fromDate}::date AND ${toDate}::date ' ||
    '  AND (${clientStatus}::varchar IS NULL OR c.status::varchar = ${clientStatus}::varchar) ' ||
    'ORDER BY c.display_name',
    'Clients submitted within a date range, optionally filtered by status code.',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT v.report_id, v.name, v.label, v.ptype, v.mandatory, v.ord
FROM (VALUES
    ('7ffb47be-de34-508f-80cd-02cb9b75e266'::uuid, 'fromDate',     'From date',          'DATE',   true,  1),
    ('7ffb47be-de34-508f-80cd-02cb9b75e266'::uuid, 'toDate',       'To date',            'DATE',   true,  2),
    ('7ffb47be-de34-508f-80cd-02cb9b75e266'::uuid, 'clientStatus', 'Client status code', 'STRING', false, 3)
) AS v(report_id, name, label, ptype, mandatory, ord)
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = v.report_id AND parameter_name = v.name);

-- ---------------------------------------------------------------------------
-- 9. Active Users Listing (identity)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    'c0c11dd8-185c-5f35-b05c-bea1ea512fd7',
    'Active Users Listing',
    'Identity',
    'identity',
    'SELECT u.username AS "username", u.email AS "email", ' ||
    '       u.first_name AS "firstName", u.last_name AS "lastName", ' ||
    '       u.is_locked_out AS "isLockedOut", u.last_active AS "lastActive" ' ||
    'FROM users u ' ||
    'WHERE u.is_active = true ' ||
    'ORDER BY u.last_active DESC NULLS LAST',
    'Platform users currently marked active, most recently active first.',
    true
) ON CONFLICT (report_name) DO NOTHING;

-- (no parameters)

-- ---------------------------------------------------------------------------
-- 10. Audit Trail (identity)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '43f44988-d097-5729-98ef-6c6865ba2c2e',
    'Audit Trail',
    'Identity',
    'identity',
    'SELECT al.created_at AS "occurredAt", COALESCE(u.username, u.email, ''SYSTEM'') AS "actor", ' ||
    '       al.entity_type AS "entityType", al.entity_id AS "entityId", al.action AS "action", ' ||
    '       al.ip_address::text AS "ipAddress" ' ||
    'FROM audit_logs al ' ||
    'LEFT JOIN users u ON u.id = al.actor_id ' ||
    'WHERE al.created_at BETWEEN ${fromDate}::timestamptz AND (${toDate}::date + INTERVAL ''1 day'')::timestamptz ' ||
    'ORDER BY al.created_at DESC ' ||
    'LIMIT 500',
    'Recent audit log entries (actor, entity, action) within a date range, most recent first (capped at 500 rows).',
    true
) ON CONFLICT (report_name) DO NOTHING;

INSERT INTO report_parameters (report_id, parameter_name, parameter_label, parameter_type, is_mandatory, display_order)
SELECT v.report_id, v.name, v.label, 'DATE', true, v.ord
FROM (VALUES
    ('43f44988-d097-5729-98ef-6c6865ba2c2e'::uuid, 'fromDate', 'From date', 1),
    ('43f44988-d097-5729-98ef-6c6865ba2c2e'::uuid, 'toDate',   'To date',   2)
) AS v(report_id, name, label, ord)
WHERE NOT EXISTS (SELECT 1 FROM report_parameters WHERE report_id = v.report_id AND parameter_name = v.name);

-- ---------------------------------------------------------------------------
-- 11. Office/Branch Summary (organization)
-- ---------------------------------------------------------------------------
INSERT INTO report_definitions (id, report_name, report_category, data_source, report_sql, description, is_core)
VALUES (
    '8395618f-0832-5691-8e9c-f383914b934d',
    'Office/Branch Summary',
    'Organization',
    'organization',
    'SELECT o.name AS "officeName", o.hierarchy AS "hierarchy", o.opening_date AS "openingDate", ' ||
    '       COUNT(s.id) AS "totalStaff", ' ||
    '       COUNT(s.id) FILTER (WHERE s.is_active) AS "activeStaff", ' ||
    '       COUNT(s.id) FILTER (WHERE s.is_loan_officer) AS "loanOfficers" ' ||
    'FROM office o ' ||
    'LEFT JOIN staff s ON s.office_id = o.id ' ||
    'GROUP BY o.id, o.name, o.hierarchy, o.opening_date ' ||
    'ORDER BY o.hierarchy',
    'Staff headcount per office/branch.',
    true
) ON CONFLICT (report_name) DO NOTHING;

-- (no parameters)
