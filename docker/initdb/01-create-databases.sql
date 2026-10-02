-- Turbo Ledger — create one database per service (dev stack).
CREATE DATABASE "TlIdentity";
CREATE DATABASE "TlAccounting";
CREATE DATABASE "TlCustomerDb";
CREATE DATABASE "TlDamDb";
CREATE DATABASE "TlGroupDb";
CREATE DATABASE "TlOrganizationDb";
-- NOTE: was "TlPortfolio" (without the "Db" suffix), which never matched
-- Portfolio's own config.json dbname ("TlPortfolioDb") — fixed here as a
-- drive-by correction while wiring Reporting's read-only db_client to it.
CREATE DATABASE "TlPortfolioDb";
CREATE DATABASE "TlSystemConfigDb";
CREATE DATABASE "TlTellerDb";
CREATE DATABASE "TlHeartBeatDb";
CREATE DATABASE "TlTemplateDb";
CREATE DATABASE "TlNotificationDb";
CREATE DATABASE "TlReportingDb";
