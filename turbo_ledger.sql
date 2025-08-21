CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

DROP TABLE IF EXISTS acc_gl_account;

CREATE TABLE acc_gl_account (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(200) NOT NULL,
  parent_id UUID NOT NULL,
  hierarchy VARCHAR(50) DEFAULT NULL,
  gl_code VARCHAR(45) NOT NULL UNIQUE,
  disabled BOOLEAN NOT NULL DEFAULT FALSE,
  manual_journal_entries_allowed BOOLEAN NOT NULL DEFAULT TRUE,
  account_usage SMALLINT NOT NULL DEFAULT 2,
  classification_enum SMALLINT NOT NULL,
  tag_id UUID NOT NULL,
  description VARCHAR(500) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_acc_gl_account_tag_id ON acc_gl_account (tag_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_account_parent_id ON acc_gl_account (parent_id);


DROP TABLE IF EXISTS acc_accounting_rule;

CREATE TABLE acc_accounting_rule (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) DEFAULT NULL UNIQUE,
  office_id UUID NOT NULL,
  debit_account_id UUID NOT NULL,
  allow_multiple_debits BOOLEAN NOT NULL DEFAULT FALSE,
  credit_account_id UUID NOT NULL,
  allow_multiple_credits BOOLEAN NOT NULL DEFAULT FALSE,
  description VARCHAR(500) DEFAULT NULL,
  system_defined BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_acc_accounting_rule_credit_account_id ON acc_accounting_rule (credit_account_id);
CREATE INDEX IF NOT EXISTS idx_acc_accounting_rule_debit_account_id ON acc_accounting_rule (debit_account_id);
CREATE INDEX IF NOT EXISTS idx_acc_accounting_rule_office_id ON acc_accounting_rule (office_id);


DROP TABLE IF EXISTS acc_gl_closure;

CREATE TABLE acc_gl_closure (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  office_id UUID NOT NULL,
  closing_date DATE NOT NULL,
  is_deleted BOOLEAN NOT NULL DEFAULT FALSE,
  createdby_id UUID NOT NULL,
  lastmodifiedby_id UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  comments VARCHAR(500) DEFAULT NULL,
  UNIQUE (office_id, closing_date)
);

CREATE INDEX IF NOT EXISTS idx_acc_gl_closure_createdby_id ON acc_gl_closure (createdby_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_closure_lastmodifiedby_id ON acc_gl_closure (lastmodifiedby_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_closure_office_id ON acc_gl_closure (office_id);



DROP TABLE IF EXISTS acc_gl_financial_activity_account;

CREATE TABLE acc_gl_financial_activity_account (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  gl_account_id UUID NOT NULL,
  financial_activity_type SMALLINT NOT NULL UNIQUE,
  CONSTRAINT fk_acc_gl_financial_activity_account_gl_account FOREIGN KEY (gl_account_id) REFERENCES acc_gl_account (id)
);

CREATE INDEX IF NOT EXISTS idx_acc_gl_financial_activity_account_gl_account_id ON acc_gl_financial_activity_account (gl_account_id);



DROP TABLE IF EXISTS acc_gl_journal_entry;

CREATE TABLE acc_gl_journal_entry (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_id UUID NOT NULL,
  office_id UUID NOT NULL,
  reversal_id UUID DEFAULT NULL,
  currency_code VARCHAR(3) NOT NULL,
  transaction_id VARCHAR(50) NOT NULL,
  loan_transaction_id UUID DEFAULT NULL,
  savings_transaction_id UUID DEFAULT NULL,
  client_transaction_id UUID DEFAULT NULL,
  reversed BOOLEAN NOT NULL DEFAULT FALSE,
  ref_num VARCHAR(100) DEFAULT NULL,
  manual_entry BOOLEAN NOT NULL DEFAULT FALSE,
  entry_date DATE NOT NULL,
  type_enum SMALLINT NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  description VARCHAR(500) DEFAULT NULL,
  entity_type_enum SMALLINT DEFAULT NULL,
  entity_id UUID DEFAULT NULL,
  created_by UUID DEFAULT NULL,
  last_modified_by UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  is_running_balance_calculated BOOLEAN NOT NULL DEFAULT FALSE,
  office_running_balance DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  organization_running_balance DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  payment_details_id UUID DEFAULT NULL,
  share_transaction_id UUID DEFAULT NULL,
  transaction_date DATE DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  submitted_on_date DATE NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_account_id ON acc_gl_journal_entry (account_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_reversal_id ON acc_gl_journal_entry (reversal_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_created_by ON acc_gl_journal_entry (created_by);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_last_modified_by ON acc_gl_journal_entry (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_client_transaction_id ON acc_gl_journal_entry (client_transaction_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_loan_transaction_id ON acc_gl_journal_entry (loan_transaction_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_office_id ON acc_gl_journal_entry (office_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_payment_details_id ON acc_gl_journal_entry (payment_details_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_savings_transaction_id ON acc_gl_journal_entry (savings_transaction_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_share_transaction_id ON acc_gl_journal_entry (share_transaction_id);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_transaction_date ON acc_gl_journal_entry (transaction_date);
CREATE INDEX IF NOT EXISTS idx_acc_gl_journal_entry_submitted_on_date ON acc_gl_journal_entry (submitted_on_date);


DROP TABLE IF EXISTS acc_product_mapping;

CREATE TABLE acc_product_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  gl_account_id UUID NOT NULL,
  product_id UUID NOT NULL,
  product_type UUID NOT NULL,
  payment_type UUID NOT NULL,
  charge_id UUID NOT NULL,
  financial_account_type UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_acc_product_mapping_charge_id ON acc_product_mapping (charge_id);
CREATE INDEX IF NOT EXISTS idx_acc_product_mapping_payment_type ON acc_product_mapping (payment_type);




DROP TABLE IF EXISTS acc_rule_tags;

CREATE TABLE acc_rule_tags (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  acc_rule_id UUID NOT NULL,
  tag_id UUID NOT NULL,
  acc_type UUID NOT NULL,
  UNIQUE (acc_rule_id, tag_id, acc_type)
);

CREATE INDEX IF NOT EXISTS idx_acc_rule_tags_acc_rule_id ON acc_rule_tags (acc_rule_id);
CREATE INDEX IF NOT EXISTS idx_acc_rule_tags_tag_id ON acc_rule_tags (tag_id);



DROP TABLE IF EXISTS batch_custom_job_parameters;

CREATE TABLE batch_custom_job_parameters (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  parameter_json JSONB DEFAULT NULL
);



DROP TABLE IF EXISTS BATCH_JOB_EXECUTION_CONTEXT;

CREATE TABLE BATCH_JOB_EXECUTION_CONTEXT (
  JOB_EXECUTION_ID UUID NOT NULL PRIMARY KEY DEFAULT uuid_generate_v4(),
  SHORT_CONTEXT VARCHAR(2500) NOT NULL,
  SERIALIZED_CONTEXT TEXT DEFAULT NULL
);



DROP TABLE IF EXISTS BATCH_JOB_EXECUTION_PARAMS;

CREATE TABLE BATCH_JOB_EXECUTION_PARAMS (
  JOB_EXECUTION_ID UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  PARAMETER_TYPE VARCHAR(100) DEFAULT NULL,
  PARAMETER_NAME VARCHAR(100) DEFAULT NULL,
  PARAMETER_VALUE VARCHAR(2500) DEFAULT NULL,
  IDENTIFYING CHAR(1) NOT NULL
);

CREATE INDEX IF NOT EXISTS ind_batch_job_execution_params ON BATCH_JOB_EXECUTION_PARAMS (JOB_EXECUTION_ID);



DROP TABLE IF EXISTS BATCH_JOB_EXECUTION;

CREATE TABLE BATCH_JOB_EXECUTION (
  JOB_EXECUTION_ID UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  VERSION BIGINT DEFAULT NULL,
  JOB_INSTANCE_ID UUID NOT NULL,
  CREATE_TIME TIMESTAMP(6) NOT NULL,
  START_TIME TIMESTAMP(6) DEFAULT NULL,
  END_TIME TIMESTAMP(6) DEFAULT NULL,
  STATUS VARCHAR(10) DEFAULT NULL,
  EXIT_CODE VARCHAR(2500) DEFAULT NULL,
  EXIT_MESSAGE VARCHAR(2500) DEFAULT NULL,
  LAST_UPDATED TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_batch_job_execution_job_instance_id ON BATCH_JOB_EXECUTION (JOB_INSTANCE_ID);



DROP TABLE IF EXISTS BATCH_JOB_EXECUTION_SEQ;

CREATE TABLE BATCH_JOB_EXECUTION_SEQ (
  ID BIGINT NOT NULL,
  UNIQUE_KEY CHAR(1) NOT NULL,
  UNIQUE (UNIQUE_KEY)
);



DROP TABLE IF EXISTS BATCH_JOB_INSTANCE;

CREATE TABLE BATCH_JOB_INSTANCE (
  JOB_INSTANCE_ID UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  VERSION BIGINT DEFAULT NULL,
  JOB_NAME VARCHAR(100) NOT NULL,
  JOB_KEY VARCHAR(32) NOT NULL,
  UNIQUE (JOB_NAME, JOB_KEY)
);



DROP TABLE IF EXISTS BATCH_JOB_SEQ;

CREATE TABLE BATCH_JOB_SEQ (
  ID BIGINT NOT NULL,
  UNIQUE_KEY CHAR(1) NOT NULL,
  CONSTRAINT UNIQUE_KEY_UN UNIQUE (UNIQUE_KEY)
);


DROP TABLE IF EXISTS BATCH_STEP_EXECUTION_CONTEXT;

CREATE TABLE BATCH_STEP_EXECUTION_CONTEXT (
  STEP_EXECUTION_ID UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  SHORT_CONTEXT VARCHAR(2500) NOT NULL,
  SERIALIZED_CONTEXT TEXT DEFAULT NULL,
  CONSTRAINT step_exec_ctx_fk FOREIGN KEY (STEP_EXECUTION_ID) REFERENCES BATCH_STEP_EXECUTION (STEP_EXECUTION_ID)
);



DROP TABLE IF EXISTS BATCH_STEP_EXECUTION;

CREATE TABLE BATCH_STEP_EXECUTION (
  STEP_EXECUTION_ID UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  VERSION BIGINT NOT NULL,
  STEP_NAME VARCHAR(100) NOT NULL,
  JOB_EXECUTION_ID UUID NOT NULL,
  START_TIME TIMESTAMP(6) DEFAULT NULL,
  END_TIME TIMESTAMP(6) DEFAULT NULL,
  STATUS VARCHAR(10) DEFAULT NULL,
  COMMIT_COUNT BIGINT DEFAULT NULL,
  READ_COUNT BIGINT DEFAULT NULL,
  FILTER_COUNT BIGINT DEFAULT NULL,
  WRITE_COUNT BIGINT DEFAULT NULL,
  READ_SKIP_COUNT BIGINT DEFAULT NULL,
  WRITE_SKIP_COUNT BIGINT DEFAULT NULL,
  PROCESS_SKIP_COUNT BIGINT DEFAULT NULL,
  ROLLBACK_COUNT BIGINT DEFAULT NULL,
  EXIT_CODE VARCHAR(2500) DEFAULT NULL,
  EXIT_MESSAGE VARCHAR(2500) DEFAULT NULL,
  LAST_UPDATED TIMESTAMP(6) DEFAULT NULL,
  CREATE_TIME TIMESTAMP(6) NOT NULL,
  CONSTRAINT job_exec_step_fk FOREIGN KEY (JOB_EXECUTION_ID) REFERENCES BATCH_JOB_EXECUTION (JOB_EXECUTION_ID)
);

CREATE INDEX IF NOT EXISTS idx_batch_step_execution_step_name_job_execution_id ON BATCH_STEP_EXECUTION (JOB_EXECUTION_ID, STEP_NAME, START_TIME);



DROP TABLE IF EXISTS BATCH_STEP_EXECUTION_SEQ;

CREATE TABLE BATCH_STEP_EXECUTION_SEQ (
  ID BIGINT NOT NULL,
  UNIQUE_KEY CHAR(1) NOT NULL,
  UNIQUE (UNIQUE_KEY)
);



DROP TABLE IF EXISTS c_account_number_format;

CREATE TABLE c_account_number_format (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_type UUID NOT NULL,
  prefix_type UUID DEFAULT NULL,
  prefix_character VARCHAR(50) DEFAULT NULL
);




DROP TABLE IF EXISTS c_cache;

CREATE TABLE c_cache (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  cache_type_enum SMALLINT NOT NULL DEFAULT 1
);




DROP TABLE IF EXISTS c_configuration;

CREATE TABLE c_configuration (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) DEFAULT NULL UNIQUE,
  value INTEGER DEFAULT NULL,
  date_value DATE DEFAULT NULL,
  string_value VARCHAR(100) DEFAULT NULL,
  enabled BOOLEAN NOT NULL DEFAULT FALSE,
  is_trap_door BOOLEAN NOT NULL DEFAULT FALSE,
  description VARCHAR(300) DEFAULT NULL
);



DROP TABLE IF EXISTS c_external_service;

CREATE TABLE c_external_service (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) DEFAULT NULL UNIQUE
);


DROP TABLE IF EXISTS c_external_service_properties;

CREATE TABLE c_external_service_properties (
  name VARCHAR(150) NOT NULL,
  value VARCHAR(250) DEFAULT NULL,
  external_service_id UUID NOT NULL,
);

CREATE INDEX IF NOT EXISTS idx_c_external_service_properties_external_service_id ON c_external_service_properties (external_service_id);



DROP TABLE IF EXISTS client_device_registration;

CREATE TABLE client_device_registration (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL UNIQUE,
  updatedon_date TIMESTAMP(6) DEFAULT NULL,
  registration_id VARCHAR(255) NOT NULL UNIQUE
);



DROP TABLE IF EXISTS glim_accounts;

CREATE TABLE glim_accounts (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  group_id UUID NOT NULL,
  account_number VARCHAR(50) NOT NULL UNIQUE,
  principal_amount DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  child_accounts_count INTEGER NOT NULL,
  accepting_child BOOLEAN NOT NULL DEFAULT FALSE,
  loan_status_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  application_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000'
);

CREATE INDEX IF NOT EXISTS idx_glim_accounts_group_id ON glim_accounts (group_id);



DROP TABLE IF EXISTS gsim_accounts;

CREATE TABLE gsim_accounts (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  group_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  account_number VARCHAR(50) NOT NULL UNIQUE,
  parent_deposit DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  child_accounts_count INTEGER NOT NULL,
  accepting_child BOOLEAN NOT NULL DEFAULT FALSE,
  savings_status_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  application_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000'
);

CREATE INDEX IF NOT EXISTS idx_gsim_accounts_group_id ON gsim_accounts (group_id);



DROP TABLE IF EXISTS interop_identifier;

CREATE TABLE interop_identifier (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_id UUID NOT NULL,
  type VARCHAR(32) NOT NULL,
  a_value VARCHAR(128) NOT NULL,
  sub_value_or_type VARCHAR(128) DEFAULT NULL,
  created_by VARCHAR(32) NOT NULL,
  created_on TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,
  modified_by VARCHAR(32) DEFAULT NULL,
  modified_on TIMESTAMP(6) DEFAULT NULL,
  UNIQUE (account_id, type),
  UNIQUE (type, a_value, sub_value_or_type)
);

CREATE INDEX IF NOT EXISTS idx_interop_identifier_account_id ON interop_identifier (account_id);



DROP TABLE IF EXISTS job_parameters;

CREATE TABLE job_parameters (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  job_id UUID NOT NULL,
  parameter_name VARCHAR(100) NOT NULL,
  parameter_value TEXT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_job_parameters_job_id ON job_parameters (job_id);




DROP TABLE IF EXISTS job;

CREATE TABLE job (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) NOT NULL,
  display_name VARCHAR(100) NOT NULL,
  cron_expression VARCHAR(20) NOT NULL,
  create_time TIMESTAMP(6) DEFAULT NULL,
  task_priority SMALLINT NOT NULL DEFAULT 5,
  group_name VARCHAR(50) DEFAULT NULL,
  previous_run_start_time TIMESTAMP(6) DEFAULT NULL,
  next_run_time TIMESTAMP(6) DEFAULT NULL,
  job_key VARCHAR(500) DEFAULT NULL,
  initializing_errorlog TEXT DEFAULT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  currently_running BOOLEAN NOT NULL DEFAULT FALSE,
  updates_allowed BOOLEAN NOT NULL DEFAULT TRUE,
  scheduler_group SMALLINT NOT NULL DEFAULT 0,
  is_misfired BOOLEAN NOT NULL DEFAULT FALSE,
  node_id UUID NOT NULL,
  is_mismatched_job BOOLEAN DEFAULT TRUE
);



DROP TABLE IF EXISTS job_run_history;

CREATE TABLE job_run_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  job_id UUID NOT NULL,
  version BIGINT NOT NULL,
  start_time TIMESTAMP(6) DEFAULT NULL,
  end_time TIMESTAMP(6) DEFAULT NULL,
  status VARCHAR(10) NOT NULL,
  error_message TEXT DEFAULT NULL,
  trigger_type VARCHAR(25) NOT NULL,
  error_log TEXT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_job_run_history_job_id ON job_run_history (job_id);



DROP TABLE IF EXISTS m_account_transfer_details;

CREATE TABLE m_account_transfer_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  from_office_id UUID NOT NULL,
  to_office_id UUID NOT NULL,
  from_client_id UUID DEFAULT NULL,
  to_client_id UUID DEFAULT NULL,
  from_savings_account_id UUID DEFAULT NULL,
  to_savings_account_id UUID DEFAULT NULL,
  from_loan_account_id UUID DEFAULT NULL,
  to_loan_account_id UUID DEFAULT NULL,
  transfer_type SMALLINT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_from_client_id ON m_account_transfer_details (from_client_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_from_loan_account_id ON m_account_transfer_details (from_loan_account_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_from_office_id ON m_account_transfer_details (from_office_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_from_savings_account_id ON m_account_transfer_details (from_savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_to_client_id ON m_account_transfer_details (to_client_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_to_loan_account_id ON m_account_transfer_details (to_loan_account_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_to_office_id ON m_account_transfer_details (to_office_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_details_to_savings_account_id ON m_account_transfer_details (to_savings_account_id);



DROP TABLE IF EXISTS m_account_transfer_standing_instructions_history;

CREATE TABLE m_account_transfer_standing_instructions_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  standing_instruction_id UUID NOT NULL,
  status VARCHAR(20) NOT NULL,
  execution_time TIMESTAMP(6) DEFAULT NULL,
  amount DECIMAL(19,6) NOT NULL,
  error_log VARCHAR(500) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_account_transfer_sih_standing_instruction_id ON m_account_transfer_standing_instructions_history (standing_instruction_id);




DROP TABLE IF EXISTS m_account_transfer_standing_instructions;

CREATE TABLE m_account_transfer_standing_instructions (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(250) NOT NULL UNIQUE,
  account_transfer_details_id UUID NOT NULL,
  priority SMALLINT NOT NULL,
  status SMALLINT NOT NULL,
  instruction_type SMALLINT NOT NULL,
  amount DECIMAL(19,6) DEFAULT NULL,
  valid_from DATE NOT NULL,
  valid_till DATE DEFAULT NULL,
  recurrence_type SMALLINT NOT NULL,
  recurrence_frequency SMALLINT DEFAULT NULL,
  recurrence_interval SMALLINT DEFAULT NULL,
  recurrence_on_day SMALLINT DEFAULT NULL,
  recurrence_on_month SMALLINT DEFAULT NULL,
  last_run_date DATE DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_account_tsi_account_transfer_details_id ON m_account_transfer_standing_instructions (account_transfer_details_id);




DROP TABLE IF EXISTS m_account_transfer_transaction;

CREATE TABLE m_account_transfer_transaction (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_transfer_details_id UUID NOT NULL,
  from_savings_transaction_id UUID DEFAULT NULL,
  from_loan_transaction_id UUID DEFAULT NULL,
  to_savings_transaction_id UUID DEFAULT NULL,
  to_loan_transaction_id UUID DEFAULT NULL,
  is_reversed BOOLEAN NOT NULL,
  transaction_date DATE NOT NULL,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  amount DECIMAL(19,6) NOT NULL,
  description VARCHAR(200) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_account_transfer_transaction_account_transfer_details_id ON m_account_transfer_transaction (account_transfer_details_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_transaction_from_savings_transaction_id ON m_account_transfer_transaction (from_savings_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_transaction_from_loan_transaction_id ON m_account_transfer_transaction (from_loan_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_transaction_to_savings_transaction_id ON m_account_transfer_transaction (to_savings_account_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_account_transfer_transaction_to_loan_transaction_id ON m_account_transfer_transaction (to_loan_transaction_id);



DROP TABLE IF EXISTS m_address;

CREATE TABLE m_address (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  street VARCHAR(100) DEFAULT NULL,
  address_line_1 VARCHAR(100) DEFAULT NULL,
  address_line_2 VARCHAR(100) DEFAULT NULL,
  address_line_3 VARCHAR(100) DEFAULT NULL,
  town_village VARCHAR(100) DEFAULT NULL,
  city VARCHAR(100) DEFAULT NULL,
  county_district VARCHAR(100) DEFAULT NULL,
  state_province_id UUID DEFAULT NULL,
  country_id UUID DEFAULT NULL,
  postal_code VARCHAR(10) DEFAULT NULL,
  latitude DECIMAL(10,8) DEFAULT 0.00000000,
  longitude DECIMAL(10,8) DEFAULT 0.00000000,
  created_by VARCHAR(100) DEFAULT NULL,
  created_on DATE DEFAULT NULL,
  updated_by VARCHAR(100) DEFAULT NULL,
  updated_on DATE DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_address_state_province_id ON m_address (state_province_id);
CREATE INDEX IF NOT EXISTS idx_m_address_country_id ON m_address (country_id);


DROP TABLE IF EXISTS m_adhoc;

CREATE TABLE m_adhoc (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) DEFAULT NULL,
  query TEXT DEFAULT NULL,
  table_name VARCHAR(100) DEFAULT NULL,
  table_fields VARCHAR(1000) DEFAULT NULL,
  email VARCHAR(500) DEFAULT NULL,
  is_active BOOLEAN DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  createdby_id UUID NOT NULL,
  lastmodifiedby_id UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  report_run_frequency_code INTEGER DEFAULT NULL,
  report_run_every INTEGER DEFAULT NULL,
  last_run TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX IF NOT EXISTS idx_m_adhoc_createdby_id ON m_adhoc (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_adhoc_lastmodifiedby_id ON m_adhoc (lastmodifiedby_id);



DROP TABLE IF EXISTS m_appuser;

CREATE TABLE m_appuser (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  is_deleted BOOLEAN NOT NULL DEFAULT FALSE,
  office_id UUID NOT NULL,
  staff_id UUID NOT NULL,
  username VARCHAR(100) NOT NULL,
  firstname VARCHAR(100) NOT NULL,
  lastname VARCHAR(100) NOT NULL,
  password VARCHAR(255) NOT NULL,
  email VARCHAR(100) NOT NULL,
  firsttime_login_remaining BOOLEAN NOT NULL,
  nonexpired BOOLEAN NOT NULL,
  nonlocked BOOLEAN NOT NULL,
  nonexpired_credentials BOOLEAN NOT NULL,
  enabled BOOLEAN NOT NULL,
  last_time_password_updated TIMESTAMP(6) NOT NULL,
  password_never_expires BOOLEAN NOT NULL DEFAULT FALSE,
  is_self_service_user BOOLEAN NOT NULL DEFAULT FALSE,
  cannot_change_password BOOLEAN DEFAULT FALSE,
  UNIQUE (username)
);

CREATE INDEX IF NOT EXISTS idx_m_appuser_office_id ON m_appuser (office_id);
CREATE INDEX IF NOT EXISTS idx_m_appuser_staff_id ON m_appuser (staff_id);
CREATE INDEX IF NOT EXISTS idx_m_appuser_last_time_password_updated ON m_appuser (last_time_password_updated);



DROP TABLE IF EXISTS m_appuser_previous_password;

CREATE TABLE m_appuser_previous_password (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  user_id UUID NOT NULL,
  password VARCHAR(255) NOT NULL,
  removal_date DATE NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_appuser_previous_password_user_id ON m_appuser_previous_password (user_id);




DROP TABLE IF EXISTS m_appuser_role;

CREATE TABLE m_appuser_role (
  appuser_id UUID NOT NULL,
  role_id UUID NOT NULL,
  PRIMARY KEY (appuser_id, role_id)
);

CREATE INDEX IF NOT EXISTS idx_m_appuser_role_role_id ON m_appuser_role (role_id);
CREATE INDEX IF NOT EXISTS idx_m_appuser_role_appuser_id ON m_appuser_role (appuser_id);




DROP TABLE IF EXISTS m_batch_business_steps;

CREATE TABLE m_batch_business_steps (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  job_name VARCHAR(100) NOT NULL,
  step_name VARCHAR(100) NOT NULL,
  step_order SMALLINT NOT NULL
);



DROP TABLE IF EXISTS m_business_date;

CREATE TABLE m_business_date (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  type VARCHAR(100) NOT NULL UNIQUE,
  actual_date DATE NOT NULL,
  created_by UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  version BIGINT NOT NULL,
  last_modified_by BIGINT NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_business_date_created_by ON m_business_date (created_by);
CREATE INDEX IF NOT EXISTS idx_m_business_date_last_modified_by ON m_business_date (last_modified_by);



DROP TABLE IF EXISTS m_calendar_history;

CREATE TABLE m_calendar_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  calendar_id UUID NOT NULL,
  title VARCHAR(70) NOT NULL,
  description VARCHAR(100) DEFAULT NULL,
  location VARCHAR(50) DEFAULT NULL,
  start_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  duration SMALLINT DEFAULT NULL,
  calendar_type_enum SMALLINT NOT NULL,
  repeating BOOLEAN NOT NULL DEFAULT FALSE,
  recurrence VARCHAR(100) DEFAULT NULL,
  remind_by_enum SMALLINT DEFAULT NULL,
  first_reminder SMALLINT DEFAULT NULL,
  second_reminder SMALLINT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_calendar_history_calendar_id ON m_calendar_history (calendar_id);



DROP TABLE IF EXISTS m_calendar_instance;

CREATE TABLE m_calendar_instance (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  calendar_id UUID NOT NULL,
  entity_id UUID NOT NULL,
  entity_type_enum SMALLINT NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_calendar_instance_calendar_id ON m_calendar_instance (calendar_id);




DROP TABLE IF EXISTS m_calendar;

CREATE TABLE m_calendar (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  title VARCHAR(70) NOT NULL,
  description VARCHAR(100) DEFAULT NULL,
  location VARCHAR(50) DEFAULT NULL,
  start_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  duration SMALLINT DEFAULT NULL,
  calendar_type_enum SMALLINT NOT NULL,
  repeating BOOLEAN NOT NULL DEFAULT FALSE,
  recurrence VARCHAR(100) DEFAULT NULL,
  remind_by_enum SMALLINT DEFAULT NULL,
  first_reminder SMALLINT DEFAULT NULL,
  second_reminder SMALLINT DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by BIGINT NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  meeting_time TIME DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_calendar_created_by ON m_calendar (created_by);
CREATE INDEX IF NOT EXISTS idx_m_calendar_last_modified_by ON m_calendar (last_modified_by);




DROP TABLE IF EXISTS m_cashier_transactions;

CREATE TABLE m_cashier_transactions (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  cashier_id UUID NOT NULL,
  txn_type SMALLINT NOT NULL,
  txn_amount DECIMAL(19,6) NOT NULL,
  txn_date DATE NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  entity_type VARCHAR(50) DEFAULT NULL,
  entity_id UUID NOT NULL,
  txn_note VARCHAR(200) DEFAULT NULL,
  currency_code VARCHAR(3) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_cashier_transactions_cashier_id ON m_cashier_transactions (cashier_id);




DROP TABLE IF EXISTS m_cashiers;

CREATE TABLE m_cashiers (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  staff_id UUID DEFAULT NULL,
  teller_id UUID DEFAULT NULL,
  description VARCHAR(100) DEFAULT NULL,
  start_date DATE DEFAULT NULL,
  end_date DATE DEFAULT NULL,
  start_time VARCHAR(10) DEFAULT NULL,
  end_time VARCHAR(10) DEFAULT NULL,
  full_day BOOLEAN DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_cashiers_staff_id ON m_cashiers (staff_id);
CREATE INDEX IF NOT EXISTS idx_m_cashiers_teller_id ON m_cashiers (teller_id);




DROP TABLE IF EXISTS m_charge;

CREATE TABLE m_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) DEFAULT NULL UNIQUE,
  currency_code VARCHAR(3) NOT NULL,
  charge_applies_to_enum SMALLINT NOT NULL,
  charge_time_enum SMALLINT NOT NULL,
  charge_calculation_enum SMALLINT NOT NULL,
  charge_payment_mode_enum SMALLINT DEFAULT NULL,
  amount DECIMAL(19,6) NOT NULL,
  fee_on_day SMALLINT DEFAULT NULL,
  fee_interval SMALLINT DEFAULT NULL,
  fee_on_month SMALLINT DEFAULT NULL,
  is_penalty BOOLEAN NOT NULL DEFAULT FALSE,
  is_active BOOLEAN NOT NULL,
  is_deleted BOOLEAN NOT NULL DEFAULT FALSE,
  min_cap DECIMAL(19,6) DEFAULT NULL,
  max_cap DECIMAL(19,6) DEFAULT NULL,
  fee_frequency SMALLINT DEFAULT NULL,
  is_free_withdrawal BOOLEAN NOT NULL DEFAULT FALSE,
  free_withdrawal_charge_frequency INTEGER DEFAULT 0,
  restart_frequency INTEGER DEFAULT 0,
  restart_frequency_enum INTEGER DEFAULT 0,
  is_payment_type BOOLEAN DEFAULT FALSE,
  payment_type_id UUID DEFAULT NULL,
  income_or_liability_account_id UUID DEFAULT NULL,
  tax_group_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_charge_income_or_liability_account_id ON m_charge (income_or_liability_account_id);
CREATE INDEX IF NOT EXISTS idx_m_charge_tax_group_id ON m_charge (tax_group_id);
CREATE INDEX IF NOT EXISTS idx_m_charge_payment_type_id ON m_charge (payment_type_id);




DROP TABLE IF EXISTS m_client_address;

CREATE TABLE m_client_address (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  address_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  address_type_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  is_active BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_client_address_address_id ON m_client_address (address_id);
CREATE INDEX IF NOT EXISTS idx_m_client_address_address_type_id ON m_client_address (address_type_id);
CREATE INDEX IF NOT EXISTS idx_m_client_address_client_id ON m_client_address (client_id);


DROP TABLE IF EXISTS m_client_attendance;

CREATE TABLE m_client_attendance (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  meeting_id UUID NOT NULL,
  attendance_type_enum SMALLINT NOT NULL,
  UNIQUE (client_id, meeting_id)
);

CREATE INDEX IF NOT EXISTS idx_m_client_attendance_meeting_id ON m_client_attendance (meeting_id);



DROP TABLE IF EXISTS m_client_charge_paid_by;

CREATE TABLE m_client_charge_paid_by (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_transaction_id UUID NOT NULL,
  client_charge_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_client_charge_paid_by_client_transaction_id ON m_client_charge_paid_by (client_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_client_charge_paid_by_client_charge_id ON m_client_charge_paid_by (client_charge_id);



DROP TABLE IF EXISTS m_client_charge;

CREATE TABLE m_client_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL,
  charge_id UUID NOT NULL,
  is_penalty BOOLEAN NOT NULL,
  charge_time_enum SMALLINT NOT NULL,
  charge_due_date DATE DEFAULT NULL,
  charge_calculation_enum SMALLINT NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  amount_paid_derived DECIMAL(19,6) DEFAULT NULL,
  amount_waived_derived DECIMAL(19,6) DEFAULT NULL,
  amount_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  amount_outstanding_derived DECIMAL(19,6) NOT NULL,
  is_paid_derived BOOLEAN DEFAULT NULL,
  waived BOOLEAN DEFAULT NULL,
  is_active BOOLEAN DEFAULT NULL,
  inactivated_on_date DATE DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_client_charge_charge_id ON m_client_charge (charge_id);
CREATE INDEX IF NOT EXISTS idx_m_client_charge_client_id ON m_client_charge (client_id);



DROP TABLE IF EXISTS m_client_collateral_management;

CREATE TABLE m_client_collateral_management (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  quantity DECIMAL(20,5) NOT NULL,
  client_id UUID DEFAULT NULL,
  collateral_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_client_collateral_management_client_id ON m_client_collateral_management (client_id);
CREATE INDEX IF NOT EXISTS idx_m_client_collateral_management_collateral_id ON m_client_collateral_management (collateral_id);



DROP TABLE IF EXISTS m_client_identifier;

CREATE TABLE m_client_identifier (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL,
  document_type_id UUID NOT NULL,
  document_key VARCHAR(50) NOT NULL,
  status INTEGER NOT NULL DEFAULT 300,
  active INTEGER DEFAULT NULL,
  description VARCHAR(500) DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  UNIQUE (document_type_id, document_key),
  UNIQUE (client_id, document_type_id, active)
);

CREATE INDEX IF NOT EXISTS idx_m_client_identifier_client_id ON m_client_identifier (client_id);
CREATE INDEX IF NOT EXISTS idx_m_client_identifier_document_type_id ON m_client_identifier (document_type_id);
CREATE INDEX IF NOT EXISTS idx_m_client_identifier_created_by ON m_client_identifier (created_by);
CREATE INDEX IF NOT EXISTS idx_m_client_identifier_last_modified_by ON m_client_identifier (last_modified_by);



DROP TABLE IF EXISTS m_client_non_person;

CREATE TABLE m_client_non_person (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL UNIQUE,
  constitution_cv_id UUID NOT NULL,
  incorp_no VARCHAR(50) DEFAULT NULL,
  incorp_validity_till DATE DEFAULT NULL,
  main_business_line_cv_id UUID DEFAULT NULL,
  remarks VARCHAR(150) DEFAULT NULL
);



DROP TABLE IF EXISTS m_client;

CREATE TABLE m_client (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_no VARCHAR(20) NOT NULL UNIQUE,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  status_enum INTEGER NOT NULL DEFAULT 300,
  sub_status INTEGER DEFAULT NULL,
  activation_date DATE DEFAULT NULL,
  office_joining_date DATE DEFAULT NULL,
  office_id UUID NOT NULL,
  transfer_to_office_id UUID DEFAULT NULL,
  staff_id UUID DEFAULT NULL,
  firstname VARCHAR(50) DEFAULT NULL,
  middlename VARCHAR(50) DEFAULT NULL,
  lastname VARCHAR(50) DEFAULT NULL,
  fullname VARCHAR(160) DEFAULT NULL,
  display_name VARCHAR(160) DEFAULT NULL,
  mobile_no VARCHAR(50) DEFAULT NULL UNIQUE,
  is_staff BOOLEAN NOT NULL DEFAULT FALSE,
  gender_cv_id INTEGER DEFAULT NULL,
  date_of_birth DATE DEFAULT NULL,
  image_id UUID DEFAULT NULL,
  closure_reason_cv_id INTEGER DEFAULT NULL,
  closedon_date DATE DEFAULT NULL,
  updated_by UUID DEFAULT NULL,
  updated_on DATE DEFAULT NULL,
  submittedon_date DATE DEFAULT NULL,
  activatedon_userid UUID DEFAULT NULL,
  closedon_userid UUID DEFAULT NULL,
  default_savings_product UUID DEFAULT NULL,
  default_savings_account UUID DEFAULT NULL,
  client_type_cv_id INTEGER DEFAULT NULL,
  client_classification_cv_id INTEGER DEFAULT NULL,
  reject_reason_cv_id INTEGER DEFAULT NULL,
  rejectedon_date DATE DEFAULT NULL,
  rejectedon_userid UUID DEFAULT NULL,
  withdraw_reason_cv_id INTEGER DEFAULT NULL,
  withdrawn_on_date DATE DEFAULT NULL,
  withdraw_on_userid UUID DEFAULT NULL,
  reactivated_on_date DATE DEFAULT NULL,
  reactivated_on_userid UUID DEFAULT NULL,
  legal_form_enum INTEGER DEFAULT NULL,
  reopened_on_date DATE DEFAULT NULL,
  reopened_by_userid UUID DEFAULT NULL,
  email_address VARCHAR(150) DEFAULT NULL,
  proposed_transfer_date DATE DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  UNIQUE (external_id, legal_form_enum)
);

CREATE INDEX IF NOT EXISTS idx_m_client_gender_cv_id ON m_client (gender_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_client_office_id ON m_client (office_id);
CREATE INDEX IF NOT EXISTS idx_m_client_classification_cv_id ON m_client (client_classification_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_client_closure_reason_cv_id ON m_client (closure_reason_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_client_image_id ON m_client (image_id);
CREATE INDEX IF NOT EXISTS idx_m_client_transfer_to_office_id ON m_client (transfer_to_office_id);
CREATE INDEX IF NOT EXISTS idx_m_client_default_savings_account ON m_client (default_savings_account);
CREATE INDEX IF NOT EXISTS idx_m_client_default_savings_product ON m_client (default_savings_product);
CREATE INDEX IF NOT EXISTS idx_m_client_sub_status ON m_client (sub_status);
CREATE INDEX IF NOT EXISTS idx_m_client_client_type_cv_id ON m_client (client_type_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_client_withdraw_reason_cv_id ON m_client (withdraw_reason_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_client_reject_reason_cv_id ON m_client (reject_reason_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_client_staff_id ON m_client (staff_id);
CREATE INDEX IF NOT EXISTS idx_m_client_created_by ON m_client (created_by);
CREATE INDEX IF NOT EXISTS idx_m_client_last_modified_by ON m_client (last_modified_by);




DROP TABLE IF EXISTS m_client_transaction;

CREATE TABLE m_client_transaction (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL,
  office_id UUID NOT NULL,
  currency_code VARCHAR(3) NOT NULL,
  payment_detail_id UUID DEFAULT NULL,
  is_reversed BOOLEAN NOT NULL,
  external_id VARCHAR(50) DEFAULT NULL UNIQUE,
  transaction_date DATE NOT NULL,
  transaction_type_enum SMALLINT NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  submitted_on_date DATE NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_client_transaction_client_id ON m_client_transaction (client_id);
CREATE INDEX IF NOT EXISTS idx_m_client_transaction_created_by ON m_client_transaction (created_by);
CREATE INDEX IF NOT EXISTS idx_m_client_transaction_last_modified_by ON m_client_transaction (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_client_transaction_submitted_on_date ON m_client_transaction (submitted_on_date);




DROP TABLE IF EXISTS m_client_transfer_details;

CREATE TABLE m_client_transfer_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL,
  from_office_id UUID NOT NULL,
  to_office_id UUID NOT NULL,
  proposed_transfer_date DATE DEFAULT NULL,
  transfer_type SMALLINT NOT NULL,
  submitted_on DATE NOT NULL,
  submitted_by UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_client_transfer_details_submitted_by ON m_client_transfer_details (submitted_by);
CREATE INDEX IF NOT EXISTS idx_m_client_transfer_details_client_id ON m_client_transfer_details (client_id);
CREATE INDEX IF NOT EXISTS idx_m_client_transfer_details_from_office_id ON m_client_transfer_details (from_office_id);
CREATE INDEX IF NOT EXISTS idx_m_client_transfer_details_to_office_id ON m_client_transfer_details (to_office_id);


DROP TABLE IF EXISTS m_code;

CREATE TABLE m_code (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  code_name VARCHAR(100) DEFAULT NULL UNIQUE,
  is_system_defined BOOLEAN NOT NULL DEFAULT FALSE
);



DROP TABLE IF EXISTS m_code_value;

CREATE TABLE m_code_value (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  code_id UUID NOT NULL,
  code_value VARCHAR(100) DEFAULT NULL,
  code_description VARCHAR(500) DEFAULT NULL,
  order_position INTEGER NOT NULL DEFAULT 0,
  code_score INTEGER DEFAULT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  is_mandatory BOOLEAN NOT NULL DEFAULT FALSE,
  UNIQUE (code_id, code_value)
);

CREATE INDEX IF NOT EXISTS idx_m_code_value_code_id ON m_code_value (code_id);



DROP TABLE IF EXISTS m_collateral_management;

CREATE TABLE m_collateral_management (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(50) NOT NULL,
  quality VARCHAR(40) NOT NULL,
  base_price DECIMAL(20,5) NOT NULL,
  unit_type VARCHAR(10) NOT NULL,
  pct_to_base DECIMAL(20,5) NOT NULL,
  currency_id UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_collateral_management_currency ON m_collateral_management (currency_id);




DROP TABLE IF EXISTS m_creditbureau_configuration;

CREATE TABLE m_creditbureau_configuration (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  configkey VARCHAR(50) DEFAULT NULL,
  value TEXT DEFAULT NULL,
  organisation_creditbureau_id UUID DEFAULT NULL,
  description VARCHAR(50) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_creditbureau_configuration_creditbureau_id ON m_creditbureau_configuration (organisation_creditbureau_id);



DROP TABLE IF EXISTS m_creditbureau_loanproduct_mapping;

CREATE TABLE m_creditbureau_loanproduct_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  organisation_creditbureau_id UUID NOT NULL,
  loan_product_id UUID NOT NULL,
  is_creditcheck_mandatory BOOLEAN DEFAULT NULL,
  skip_creditcheck_in_failure BOOLEAN DEFAULT NULL,
  stale_period INTEGER DEFAULT NULL,
  is_active BOOLEAN DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_creditbureau_loanproduct_mapping_loan_product_id ON m_creditbureau_loanproduct_mapping (loan_product_id);


DROP TABLE IF EXISTS m_creditbureau;

CREATE TABLE m_creditbureau (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) NOT NULL,
  product VARCHAR(100) NOT NULL,
  country VARCHAR(100) NOT NULL,
  implementation_key VARCHAR(100) DEFAULT NULL,
  UNIQUE (name, product, country, implementation_key)
);


DROP TABLE IF EXISTS m_creditbureau_token;

CREATE TABLE m_creditbureau_token (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  username VARCHAR(128) DEFAULT NULL,
  token TEXT DEFAULT NULL,
  token_type VARCHAR(128) DEFAULT NULL,
  expires_in VARCHAR(128) DEFAULT NULL,
  issued VARCHAR(128) DEFAULT NULL,
  expiry_date DATE DEFAULT NULL
);



DROP TABLE IF EXISTS m_creditreport;

CREATE TABLE m_creditreport (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  credit_bureau_id UUID DEFAULT NULL,
  national_id VARCHAR(128) DEFAULT NULL,
  credit_reports BYTEA DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_creditreport_credit_bureau_id ON m_creditreport (credit_bureau_id);



DROP TABLE IF EXISTS m_currency;

CREATE TABLE m_currency (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  code VARCHAR(3) NOT NULL UNIQUE,
  decimal_places SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  display_symbol VARCHAR(10) DEFAULT NULL,
  name VARCHAR(50) NOT NULL,
  internationalized_name_code VARCHAR(50) NOT NULL
);




DROP TABLE IF EXISTS m_delinquency_bucket_mappings;

CREATE TABLE m_delinquency_bucket_mappings (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  delinquency_range_id UUID NOT NULL,
  delinquency_bucket_id UUID NOT NULL,
  created_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  version BIGINT NOT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_delinquency_bucket_mappings_delinquency_range_id ON m_delinquency_bucket_mappings (delinquency_range_id);
CREATE INDEX IF NOT EXISTS idx_m_delinquency_bucket_mappings_delinquency_bucket_id ON m_delinquency_bucket_mappings (delinquency_bucket_id);



DROP TABLE IF EXISTS m_delinquency_bucket;

CREATE TABLE m_delinquency_bucket (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) NOT NULL UNIQUE,
  created_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  version BIGINT NOT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);



DROP TABLE IF EXISTS m_delinquency_range;

CREATE TABLE m_delinquency_range (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  classification VARCHAR(100) NOT NULL UNIQUE,
  min_age_days BIGINT NOT NULL,
  max_age_days BIGINT DEFAULT NULL,
  created_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  version BIGINT NOT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);




DROP TABLE IF EXISTS m_deposit_account_on_hold_transaction;

CREATE TABLE m_deposit_account_on_hold_transaction (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_account_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  transaction_type_enum SMALLINT NOT NULL,
  transaction_date DATE NOT NULL,
  is_reversed BOOLEAN NOT NULL DEFAULT FALSE,
  created_date TIMESTAMP DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_deposit_account_on_hold_transaction_savings_account_id ON m_deposit_account_on_hold_transaction (savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_deposit_account_on_hold_transaction_created_by ON m_deposit_account_on_hold_transaction (created_by);
CREATE INDEX IF NOT EXISTS idx_m_deposit_account_on_hold_transaction_last_modified_by ON m_deposit_account_on_hold_transaction (last_modified_by);


DROP TABLE IF EXISTS m_deposit_product_interest_rate_chart;

CREATE TABLE m_deposit_product_interest_rate_chart (
  deposit_product_id UUID NOT NULL,
  interest_rate_chart_id UUID NOT NULL,
  UNIQUE (deposit_product_id, interest_rate_chart_id)
);

CREATE INDEX IF NOT EXISTS idx_m_deposit_product_interest_rate_chart_interest_rate_chart_id ON m_deposit_product_interest_rate_chart (interest_rate_chart_id);




DROP TABLE IF EXISTS m_deposit_product_recurring_detail;

CREATE TABLE m_deposit_product_recurring_detail (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_product_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  is_mandatory BOOLEAN NOT NULL DEFAULT TRUE,
  allow_withdrawal BOOLEAN NOT NULL DEFAULT FALSE,
  adjust_advance_towards_future_payments BOOLEAN NOT NULL DEFAULT TRUE
);

CREATE INDEX IF NOT EXISTS idx_m_deposit_product_recurring_detail_savings_product_id ON m_deposit_product_recurring_detail (savings_product_id);



DROP TABLE IF EXISTS m_deposit_product_term_and_preclosure;

CREATE TABLE m_deposit_product_term_and_preclosure (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_product_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  min_deposit_term INTEGER DEFAULT NULL,
  max_deposit_term INTEGER DEFAULT NULL,
  min_deposit_term_type_enum SMALLINT DEFAULT NULL,
  max_deposit_term_type_enum SMALLINT DEFAULT NULL,
  in_multiples_of_deposit_term INTEGER DEFAULT NULL,
  in_multiples_of_deposit_term_type_enum SMALLINT DEFAULT NULL,
  pre_closure_penal_applicable BOOLEAN DEFAULT NULL,
  pre_closure_penal_interest DECIMAL(19,6) DEFAULT NULL,
  pre_closure_penal_interest_on_enum SMALLINT DEFAULT NULL,
  min_deposit_amount DECIMAL(19,6) DEFAULT NULL,
  max_deposit_amount DECIMAL(19,6) DEFAULT NULL,
  deposit_amount DECIMAL(19,6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_deposit_product_term_and_preclosure_savings_product_id ON m_deposit_product_term_and_preclosure (savings_product_id);


DROP TABLE IF EXISTS m_document;

CREATE TABLE m_document (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  parent_entity_type VARCHAR(50) NOT NULL,
  parent_entity_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  name VARCHAR(250) NOT NULL,
  file_name VARCHAR(250) NOT NULL,
  size INTEGER DEFAULT 0,
  type VARCHAR(500) DEFAULT NULL,
  description VARCHAR(1000) DEFAULT NULL,
  location VARCHAR(500) NOT NULL DEFAULT '0',
  storage_type_enum SMALLINT DEFAULT NULL
);



DROP TABLE IF EXISTS m_entity_datatable_check;

CREATE TABLE m_entity_datatable_check (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  application_table_name VARCHAR(200) NOT NULL,
  x_registered_table_name VARCHAR(50) NOT NULL,
  status_enum INTEGER NOT NULL,
  system_defined BOOLEAN NOT NULL DEFAULT FALSE,
  product_id UUID DEFAULT NULL,
  UNIQUE (application_table_name, x_registered_table_name, status_enum, product_id)
);

CREATE INDEX IF NOT EXISTS idx_m_entity_datatable_check_product_id ON m_entity_datatable_check (product_id);
CREATE INDEX IF NOT EXISTS idx_m_entity_datatable_check_x_registered_table_name ON m_entity_datatable_check (x_registered_table_name);




DROP TABLE IF EXISTS m_entity_relation;

CREATE TABLE m_entity_relation (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  from_entity_type INTEGER NOT NULL,
  to_entity_type INTEGER NOT NULL,
  code_name VARCHAR(50) NOT NULL,
  UNIQUE (from_entity_type, to_entity_type, code_name)
);



DROP TABLE IF EXISTS m_entity_to_entity_access;

CREATE TABLE m_entity_to_entity_access (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  entity_type VARCHAR(50) NOT NULL,
  entity_id UUID NOT NULL,
  access_type_code_value_id INTEGER NOT NULL,
  second_entity_type VARCHAR(50) NOT NULL,
  second_entity_id UUID NOT NULL,
  UNIQUE (entity_type, entity_id, access_type_code_value_id, second_entity_type, second_entity_id)
);

CREATE INDEX IF NOT EXISTS idx_m_entity_to_entity_access_access_type_code_value_id ON m_entity_to_entity_access (access_type_code_value_id);
CREATE INDEX IF NOT EXISTS idx_m_entity_to_entity_access_entity_type_entity_id ON m_entity_to_entity_access (entity_type, entity_id);



DROP TABLE IF EXISTS m_entity_to_entity_mapping;

CREATE TABLE m_entity_to_entity_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  rel_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  from_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  to_id UUID NOT NULL,
  start_date DATE DEFAULT NULL,
  end_date DATE DEFAULT NULL,
  UNIQUE (rel_id, from_id, to_id)
);




DROP TABLE IF EXISTS m_external_asset_owner_journal_entry_mapping;

CREATE TABLE m_external_asset_owner_journal_entry_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  journal_entry_id UUID NOT NULL,
  owner_id UUID NOT NULL,
  created_by UUID DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_journal_entry_mapping_created_by ON m_external_asset_owner_journal_entry_mapping (created_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_journal_entry_mapping_modified_by ON m_external_asset_owner_journal_entry_mapping (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_journal_entry_mapping_journal_entry_id ON m_external_asset_owner_journal_entry_mapping (journal_entry_id);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_journal_entry_mapping_owner_id ON m_external_asset_owner_journal_entry_mapping (owner_id);



DROP TABLE IF EXISTS m_external_asset_owner;

CREATE TABLE m_external_asset_owner (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  external_id VARCHAR(100) NOT NULL UNIQUE,
  created_by UUID DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_created_by ON m_external_asset_owner (created_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_modified_by ON m_external_asset_owner (last_modified_by);



DROP TABLE IF EXISTS m_external_asset_owner_transfer_details;

CREATE TABLE m_external_asset_owner_transfer_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  asset_owner_transfer_id UUID NOT NULL,
  total_outstanding_derived DECIMAL(19,6) NOT NULL,
  principal_outstanding_derived DECIMAL(19,6) NOT NULL,
  interest_outstanding_derived DECIMAL(19,6) NOT NULL,
  fee_charges_outstanding_derived DECIMAL(19,6) NOT NULL,
  penalty_charges_outstanding_derived DECIMAL(19,6) NOT NULL,
  total_overpaid_derived DECIMAL(19,6) NOT NULL,
  created_by UUID DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  UNIQUE (asset_owner_transfer_id)
);

CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_details_created_by ON m_external_asset_owner_transfer_details (created_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_details_modified_by ON m_external_asset_owner_transfer_details (last_modified_by);


DROP TABLE IF EXISTS m_external_asset_owner_transfer_loan_mapping;

CREATE TABLE m_external_asset_owner_transfer_loan_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id BIGINT NOT NULL,
  owner_transfer_id BIGINT NOT NULL,
  created_by BIGINT DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_by BIGINT DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_loan_mapping_created_by ON m_external_asset_owner_transfer_loan_mapping (created_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_loan_mapping_modified_by ON m_external_asset_owner_transfer_loan_mapping (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_loan_mapping_owner_transfer_id ON m_external_asset_owner_transfer_loan_mapping (owner_transfer_id);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_loan_mapping_loan_id ON m_external_asset_owner_transfer_loan_mapping (loan_id);


DROP TABLE IF EXISTS m_external_asset_owner_transfer;

CREATE TABLE m_external_asset_owner_transfer (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  owner_id UUID NOT NULL,
  external_id VARCHAR(100) NOT NULL,
  status VARCHAR(50) NOT NULL,
  purchase_price_ratio VARCHAR(50) NOT NULL,
  settlement_date DATE NOT NULL,
  effective_date_from DATE NOT NULL,
  effective_date_to DATE NOT NULL,
  created_by UUID DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  external_loan_id VARCHAR(100) DEFAULT NULL,
  loan_id UUID NOT NULL,
  sub_status VARCHAR(50) DEFAULT NULL,
  UNIQUE (status, external_id)
);

CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_external_id ON m_external_asset_owner_transfer (external_id);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_status ON m_external_asset_owner_transfer (status);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_settlement_date ON m_external_asset_owner_transfer (settlement_date);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_effective_date_from ON m_external_asset_owner_transfer (effective_date_from);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_effective_date_to ON m_external_asset_owner_transfer (effective_date_to);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_created_by ON m_external_asset_owner_transfer (created_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_modified_by ON m_external_asset_owner_transfer (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_owner_id ON m_external_asset_owner_transfer (owner_id);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_sub_status ON m_external_asset_owner_transfer (sub_status);
CREATE INDEX IF NOT EXISTS idx_m_external_asset_owner_transfer_loan_id ON m_external_asset_owner_transfer (loan_id);



DROP TABLE IF EXISTS m_external_event_configuration;

CREATE TABLE m_external_event_configuration (
  type VARCHAR(100) NOT NULL PRIMARY KEY,
  enabled BOOLEAN NOT NULL
);



DROP TABLE IF EXISTS m_external_event;

CREATE TABLE m_external_event (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  type VARCHAR(100) NOT NULL,
  created_at TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,
  status VARCHAR(100) NOT NULL,
  business_date DATE NOT NULL,
  data BYTEA NOT NULL,
  idempotency_key VARCHAR(100) NOT NULL,
  sent_at TIMESTAMP(6) NULL DEFAULT NULL,
  schema VARCHAR(300) NOT NULL,
  category VARCHAR(100) NOT NULL,
  aggregate_root_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_external_event_status ON m_external_event (status);
CREATE INDEX IF NOT EXISTS idx_m_external_event_business_date ON m_external_event (business_date);



DROP TABLE IF EXISTS m_family_members;

CREATE TABLE m_family_members (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID NOT NULL,
  firstname VARCHAR(50) NOT NULL,
  middlename VARCHAR(50) DEFAULT NULL,
  lastname VARCHAR(50) DEFAULT NULL,
  qualification VARCHAR(50) DEFAULT NULL,
  relationship_cv_id UUID NOT NULL,
  marital_status_cv_id UUID DEFAULT NULL,
  gender_cv_id UUID DEFAULT NULL,
  date_of_birth DATE DEFAULT NULL,
  age INTEGER DEFAULT NULL,
  profession_cv_id UUID DEFAULT NULL,
  mobile_number VARCHAR(50) DEFAULT NULL,
  is_dependent BOOLEAN DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_family_members_client_id ON m_family_members (client_id);
CREATE INDEX IF NOT EXISTS idx_m_family_members_gender_cv_id ON m_family_members (gender_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_family_members_marital_status_cv_id ON m_family_members (marital_status_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_family_members_profession_cv_id ON m_family_members (profession_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_family_members_relationship_cv_id ON m_family_members (relationship_cv_id);



DROP TABLE IF EXISTS m_field_configuration;

CREATE TABLE m_field_configuration (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  entity VARCHAR(100) NOT NULL,
  subentity VARCHAR(100) NOT NULL,
  field VARCHAR(100) NOT NULL,
  is_enabled BOOLEAN NOT NULL,
  is_mandatory BOOLEAN NOT NULL,
  validation_regex VARCHAR(50) DEFAULT NULL
);



DROP TABLE IF EXISTS m_floating_rates_periods;

CREATE TABLE m_floating_rates_periods (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  floating_rates_id UUID NOT NULL,
  from_date DATE DEFAULT NULL,
  interest_rate DECIMAL(19,6) NOT NULL,
  is_differential_to_base_lending_rate BOOLEAN NOT NULL DEFAULT FALSE,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  created_by UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_floating_rates_periods_floating_rates_id ON m_floating_rates_periods (floating_rates_id);
CREATE INDEX IF NOT EXISTS idx_m_floating_rates_periods_created_by ON m_floating_rates_periods (created_by);
CREATE INDEX IF NOT EXISTS idx_m_floating_rates_periods_last_modified_by ON m_floating_rates_periods (last_modified_by);



DROP TABLE IF EXISTS m_floating_rates;

CREATE TABLE m_floating_rates (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(200) NOT NULL UNIQUE,
  is_base_lending_rate BOOLEAN NOT NULL DEFAULT FALSE,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  created_by UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_floating_rates_created_by ON m_floating_rates (created_by);
CREATE INDEX IF NOT EXISTS idx_m_floating_rates_last_modified_by ON m_floating_rates (last_modified_by);



DROP TABLE IF EXISTS m_fund;

CREATE TABLE m_fund (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(255) DEFAULT NULL UNIQUE,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE
);




DROP TABLE IF EXISTS m_group_client;

CREATE TABLE m_group_client (
  group_id UUID NOT NULL,
  client_id UUID NOT NULL,
  PRIMARY KEY (group_id, client_id)
);

CREATE INDEX IF NOT EXISTS idx_m_group_client_client_id ON m_group_client (client_id);




DROP TABLE IF EXISTS m_group_level;

CREATE TABLE m_group_level (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  parent_id UUID DEFAULT NULL,
  super_parent BOOLEAN NOT NULL,
  level_name VARCHAR(100) NOT NULL,
  recursable BOOLEAN NOT NULL,
  can_have_clients BOOLEAN NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_group_level_parent_id ON m_group_level (parent_id);


DROP TABLE IF EXISTS m_group;

CREATE TABLE m_group (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  external_id VARCHAR(100) DEFAULT NULL,
  status_enum INTEGER NOT NULL DEFAULT 300,
  activation_date DATE DEFAULT NULL,
  office_id UUID NOT NULL,
  staff_id UUID DEFAULT NULL,
  parent_id UUID DEFAULT NULL,
  level_id UUID NOT NULL,
  display_name VARCHAR(100) NOT NULL,
  hierarchy VARCHAR(100) DEFAULT NULL,
  closure_reason_cv_id UUID DEFAULT NULL,
  closedon_date DATE DEFAULT NULL,
  activatedon_userid UUID DEFAULT NULL,
  submittedon_date DATE DEFAULT NULL,
  submittedon_userid UUID DEFAULT NULL,
  closedon_userid UUID DEFAULT NULL,
  account_no VARCHAR(20) NOT NULL,
  UNIQUE (display_name, level_id),
  UNIQUE (external_id),
  UNIQUE (external_id, level_id)
);

CREATE INDEX IF NOT EXISTS idx_m_group_level_id ON m_group (level_id);
CREATE INDEX IF NOT EXISTS idx_m_group_closure_reason_cv_id ON m_group (closure_reason_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_group_parent_id ON m_group (parent_id);
CREATE INDEX IF NOT EXISTS idx_m_group_office_id ON m_group (office_id);
CREATE INDEX IF NOT EXISTS idx_m_group_staff_id ON m_group (staff_id);


DROP TABLE IF EXISTS m_group_roles;

CREATE TABLE m_group_roles (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID DEFAULT NULL,
  group_id UUID DEFAULT NULL,
  role_cv_id UUID DEFAULT NULL,
  UNIQUE (client_id, group_id, role_cv_id)
);

CREATE INDEX IF NOT EXISTS idx_m_group_roles_client_id ON m_group_roles (client_id);
CREATE INDEX IF NOT EXISTS idx_m_group_roles_group_id ON m_group_roles (group_id);
CREATE INDEX IF NOT EXISTS idx_m_group_roles_role_cv_id ON m_group_roles (role_cv_id);


DROP TABLE IF EXISTS m_guarantor_funding_details;

CREATE TABLE m_guarantor_funding_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  guarantor_id UUID NOT NULL,
  account_associations_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  amount_released_derived DECIMAL(19,6) DEFAULT NULL,
  amount_remaining_derived DECIMAL(19,6) DEFAULT NULL,
  amount_transfered_derived DECIMAL(19,6) DEFAULT NULL,
  status_enum SMALLINT NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_guarantor_funding_details_account_associations_id ON m_guarantor_funding_details (account_associations_id);
CREATE INDEX IF NOT EXISTS idx_m_guarantor_funding_details_guarantor_id ON m_guarantor_funding_details (guarantor_id);




DROP TABLE IF EXISTS m_guarantor;

CREATE TABLE m_guarantor (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  client_reln_cv_id UUID DEFAULT NULL,
  type_enum SMALLINT NOT NULL,
  entity_id UUID DEFAULT NULL,
  firstname VARCHAR(50) DEFAULT NULL,
  lastname VARCHAR(50) DEFAULT NULL,
  dob DATE DEFAULT NULL,
  address_line_1 VARCHAR(500) DEFAULT NULL,
  address_line_2 VARCHAR(500) DEFAULT NULL,
  city VARCHAR(50) DEFAULT NULL,
  state VARCHAR(50) DEFAULT NULL,
  country VARCHAR(50) DEFAULT NULL,
  zip VARCHAR(20) DEFAULT NULL,
  house_phone_number VARCHAR(20) DEFAULT NULL,
  mobile_number VARCHAR(20) DEFAULT NULL,
  comment VARCHAR(500) DEFAULT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE
);

CREATE INDEX IF NOT EXISTS idx_m_guarantor_client_reln_cv_id ON m_guarantor (client_reln_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_guarantor_loan_id ON m_guarantor (loan_id);




DROP TABLE IF EXISTS m_guarantor_transaction;

CREATE TABLE m_guarantor_transaction (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  guarantor_fund_detail_id UUID NOT NULL,
  loan_transaction_id UUID DEFAULT NULL,
  deposit_on_hold_transaction_id UUID NOT NULL,
  is_reversed BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_guarantor_transaction_guarantor_fund_detail_id ON m_guarantor_transaction (guarantor_fund_detail_id);
CREATE INDEX IF NOT EXISTS idx_m_guarantor_transaction_deposit_on_hold_transaction_id ON m_guarantor_transaction (deposit_on_hold_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_guarantor_transaction_loan_transaction_id ON m_guarantor_transaction (loan_transaction_id);




DROP TABLE IF EXISTS m_holiday_office;

CREATE TABLE m_holiday_office (
  holiday_id UUID NOT NULL,
  office_id UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_holiday_office_holiday_id ON m_holiday_office (holiday_id);
CREATE INDEX IF NOT EXISTS idx_m_holiday_office_office_id ON m_holiday_office (office_id);


DROP TABLE IF EXISTS m_holiday;

CREATE TABLE m_holiday (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) NOT NULL,
  from_date DATE DEFAULT NULL,
  to_date DATE DEFAULT NULL,
  repayments_rescheduled_to DATE DEFAULT NULL,
  status_enum INTEGER NOT NULL DEFAULT 100,
  processed BOOLEAN NOT NULL DEFAULT FALSE,
  description VARCHAR(100) DEFAULT NULL,
  rescheduling_type INTEGER NOT NULL DEFAULT 2,
  UNIQUE (name, from_date)
);



DROP TABLE IF EXISTS m_hook;

CREATE TABLE m_hook (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  template_id UUID NOT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  name VARCHAR(45) NOT NULL,
  createdby_id UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  ugd_template_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_hook_template_id ON m_hook (template_id);
CREATE INDEX IF NOT EXISTS idx_m_hook_ugd_template_id ON m_hook (ugd_template_id);


DROP TABLE IF EXISTS m_hook_configuration;

CREATE TABLE m_hook_configuration (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  hook_id UUID DEFAULT NULL,
  field_type VARCHAR(45) NOT NULL,
  field_name VARCHAR(100) NOT NULL,
  field_value VARCHAR(100) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_hook_configuration_hook_id ON m_hook_configuration (hook_id);


DROP TABLE IF EXISTS m_hook_registered_events;


CREATE TABLE m_hook_registered_events (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  hook_id UUID NOT NULL,
  entity_name VARCHAR(45) NOT NULL,
  action_name VARCHAR(45) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_hook_registered_events_hook_id ON m_hook_registered_events (hook_id);



DROP TABLE IF EXISTS m_hook_schema;

CREATE TABLE m_hook_schema (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  hook_template_id UUID NOT NULL,
  field_type VARCHAR(45) NOT NULL,
  field_name VARCHAR(100) NOT NULL,
  placeholder VARCHAR(100) DEFAULT NULL,
  optional BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_hook_schema_hook_template_id ON m_hook_schema (hook_template_id);



DROP TABLE IF EXISTS m_hook_templates;

CREATE TABLE m_hook_templates (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(45) NOT NULL
);



DROP TABLE IF EXISTS m_image;

CREATE TABLE m_image (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  location VARCHAR(500) DEFAULT NULL,
  storage_type_enum SMALLINT DEFAULT NULL
);



DROP TABLE IF EXISTS m_import_document;

CREATE TABLE m_import_document (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  document_id UUID NOT NULL,
  import_time TIMESTAMP(6) DEFAULT NULL,
  end_time TIMESTAMP(6) DEFAULT NULL,
  entity_type SMALLINT NOT NULL,
  completed BOOLEAN DEFAULT FALSE,
  total_records BIGINT DEFAULT 0,
  success_count BIGINT DEFAULT 0,
  failure_count BIGINT DEFAULT 0,
  createdby_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_import_document_createdby_id ON m_import_document (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_import_document_document_id ON m_import_document (document_id);




DROP TABLE IF EXISTS m_interest_incentives;

CREATE TABLE m_interest_incentives (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  interest_rate_slab_id UUID NOT NULL,
  entiry_type SMALLINT NOT NULL,
  attribute_name SMALLINT NOT NULL,
  condition_type SMALLINT NOT NULL,
  attribute_value VARCHAR(50) NOT NULL,
  incentive_type SMALLINT NOT NULL,
  amount DECIMAL(19,6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_interest_incentives_interest_rate_slab_id ON m_interest_incentives (interest_rate_slab_id);


DROP TABLE IF EXISTS m_interest_rate_chart;

CREATE TABLE m_interest_rate_chart (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) DEFAULT NULL,
  description VARCHAR(200) DEFAULT NULL,
  from_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  is_primary_grouping_by_amount BOOLEAN NOT NULL DEFAULT FALSE
);



DROP TABLE IF EXISTS m_interest_rate_slab;

CREATE TABLE m_interest_rate_slab (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  interest_rate_chart_id UUID NOT NULL,
  description VARCHAR(200) DEFAULT NULL,
  period_type_enum SMALLINT DEFAULT NULL,
  from_period INTEGER DEFAULT NULL,
  to_period INTEGER DEFAULT NULL,
  amount_range_from DECIMAL(19,6) DEFAULT NULL,
  amount_range_to DECIMAL(19,6) DEFAULT NULL,
  annual_interest_rate DECIMAL(19,6) NOT NULL,
  currency_code VARCHAR(3) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_interest_rate_slab_interest_rate_chart_id ON m_interest_rate_slab (interest_rate_chart_id);




DROP TABLE IF EXISTS m_loan_account_locks;

CREATE TABLE m_loan_account_locks (
  loan_id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  lock_owner VARCHAR(100) NOT NULL,
  error VARCHAR(255) DEFAULT NULL,
  version BIGINT NOT NULL,
  stacktrace TEXT DEFAULT NULL,
  lock_placed_on TIMESTAMP(6) DEFAULT NULL,
  lock_placed_on_cob_business_date DATE DEFAULT NULL
);



DROP TABLE IF EXISTS m_loan_arrears_aging;

CREATE TABLE m_loan_arrears_aging (
  loan_id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  principal_overdue_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  interest_overdue_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  fee_charges_overdue_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  penalty_charges_overdue_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_overdue_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  overdue_since_date_derived DATE DEFAULT NULL
);



DROP TABLE IF EXISTS m_loan_charge_paid_by;

CREATE TABLE m_loan_charge_paid_by (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_transaction_id UUID NOT NULL,
  loan_charge_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  installment_number SMALLINT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_charge_paid_by_loan_transaction_id ON m_loan_charge_paid_by (loan_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_charge_paid_by_loan_charge_id ON m_loan_charge_paid_by (loan_charge_id);


DROP TABLE IF EXISTS m_loan_charge;

CREATE TABLE m_loan_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  charge_id UUID NOT NULL,
  is_penalty BOOLEAN NOT NULL DEFAULT FALSE,
  charge_time_enum SMALLINT NOT NULL,
  due_for_collection_as_of_date DATE DEFAULT NULL,
  charge_calculation_enum SMALLINT NOT NULL,
  charge_payment_mode_enum SMALLINT NOT NULL DEFAULT 0,
  calculation_percentage DECIMAL(19,6) DEFAULT NULL,
  calculation_on_amount DECIMAL(19,6) DEFAULT NULL,
  charge_amount_or_percentage DECIMAL(19,6) DEFAULT NULL,
  amount DECIMAL(19,6) NOT NULL,
  amount_paid_derived DECIMAL(19,6) DEFAULT NULL,
  amount_waived_derived DECIMAL(19,6) DEFAULT NULL,
  amount_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  amount_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  is_paid_derived BOOLEAN NOT NULL DEFAULT FALSE,
  waived BOOLEAN NOT NULL DEFAULT FALSE,
  min_cap DECIMAL(19,6) DEFAULT NULL,
  max_cap DECIMAL(19,6) DEFAULT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  submitted_on_date DATE DEFAULT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_charge_charge_id ON m_loan_charge (charge_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_charge_loan_id ON m_loan_charge (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_charge_created_by ON m_loan_charge (created_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_charge_last_modified_by ON m_loan_charge (last_modified_by);



DROP TABLE IF EXISTS m_loan_collateral_management;

CREATE TABLE m_loan_collateral_management (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  quantity DECIMAL(20,5) NOT NULL,
  loan_id UUID DEFAULT NULL,
  client_collateral_id UUID DEFAULT NULL,
  is_released BOOLEAN DEFAULT FALSE,
  transaction_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_collateral_management_client_collateral_id ON m_loan_collateral_management (client_collateral_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_collateral_management_loan_id ON m_loan_collateral_management (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_collateral_management_transaction_id ON m_loan_collateral_management (transaction_id);



DROP TABLE IF EXISTS m_loan_collateral;

CREATE TABLE m_loan_collateral (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  type_cv_id UUID NOT NULL,
  value DECIMAL(19,6) DEFAULT NULL,
  description VARCHAR(500) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_collateral_type_cv_id ON m_loan_collateral (type_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_collateral_loan_id ON m_loan_collateral (loan_id);



DROP TABLE IF EXISTS m_loan_delinquency_action;

CREATE TABLE m_loan_delinquency_action (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  action VARCHAR(128) NOT NULL,
  start_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL,
  CONSTRAINT fk_m_loan_delinquency_action_loan_id FOREIGN KEY (loan_id) REFERENCES m_loan (id)
);

CREATE INDEX IF NOT EXISTS idx_m_loan_delinquency_action_loan_id ON m_loan_delinquency_action (loan_id);



DROP TABLE IF EXISTS m_loan_delinquency_tag_history;

CREATE TABLE m_loan_delinquency_tag_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  delinquency_range_id UUID NOT NULL,
  loan_id UUID NOT NULL,
  addedon_date DATE NOT NULL,
  liftedon_date DATE DEFAULT NULL,
  created_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  version BIGINT NOT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_delinquency_tag_history_delinquency_range_id ON m_loan_delinquency_tag_history (delinquency_range_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_delinquency_tag_history_loan_id ON m_loan_delinquency_tag_history (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_delinquency_tag_history_liftedon_date ON m_loan_delinquency_tag_history (liftedon_date);



DROP TABLE IF EXISTS m_loan_disbursement_detail;

CREATE TABLE m_loan_disbursement_detail (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  expected_disburse_date DATE DEFAULT NULL,
  disbursedon_date DATE DEFAULT NULL,
  principal DECIMAL(19,6) NOT NULL,
  net_disbursal_amount DECIMAL(19,6) DEFAULT NULL,
  is_reversed BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_loan_disbursement_detail_loan_id ON m_loan_disbursement_detail (loan_id);




DROP TABLE IF EXISTS m_loan_installment_charge;

CREATE TABLE m_loan_installment_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_charge_id UUID NOT NULL,
  loan_schedule_id UUID NOT NULL,
  due_date DATE DEFAULT NULL,
  amount DECIMAL(19,6) NOT NULL,
  amount_paid_derived DECIMAL(19,6) DEFAULT NULL,
  amount_waived_derived DECIMAL(19,6) DEFAULT NULL,
  amount_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  amount_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  is_paid_derived BOOLEAN NOT NULL DEFAULT FALSE,
  waived BOOLEAN NOT NULL DEFAULT FALSE,
  amount_through_charge_payment DECIMAL(19,6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_installment_charge_loan_charge_id ON m_loan_installment_charge (loan_charge_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_installment_charge_loan_schedule_id ON m_loan_installment_charge (loan_schedule_id);




DROP TABLE IF EXISTS m_loan_installment_delinquency_tag;

CREATE TABLE m_loan_installment_delinquency_tag (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  delinquency_range_id UUID NOT NULL,
  loan_id UUID NOT NULL,
  installment_id UUID NOT NULL,
  addedon_date DATE NOT NULL,
  first_overdue_date DATE NOT NULL,
  outstanding_amount DECIMAL(19,6) NOT NULL,
  liftedon_date DATE DEFAULT NULL,
  created_by UUID NOT NULL,
  version BIGINT NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_installment_delinquency_tag_delinquency_range_id ON m_loan_installment_delinquency_tag (delinquency_range_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_installment_delinquency_tag_loan_id ON m_loan_installment_delinquency_tag (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_installment_delinquency_tag_installment_id ON m_loan_installment_delinquency_tag (installment_id);



DROP TABLE IF EXISTS m_loan_interest_recalculation_additional_details;

CREATE TABLE m_loan_interest_recalculation_additional_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_repayment_schedule_id UUID NOT NULL,
  effective_date DATE NOT NULL,
  amount DECIMAL(19,6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_interest_recalculation_additional_details_loan_repayment_schedule_id ON m_loan_interest_recalculation_additional_details (loan_repayment_schedule_id);


DROP TABLE IF EXISTS m_loan_officer_assignment_history;

CREATE TABLE m_loan_officer_assignment_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  loan_officer_id UUID DEFAULT NULL,
  start_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  createdby_id UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_officer_assignment_history_loan_id ON m_loan_officer_assignment_history (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_officer_assignment_history_loan_officer_id ON m_loan_officer_assignment_history (loan_officer_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_officer_assignment_history_created_by ON m_loan_officer_assignment_history (created_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_officer_assignment_history_last_modified_by ON m_loan_officer_assignment_history (last_modified_by);



DROP TABLE IF EXISTS m_loan_overdue_installment_charge;

CREATE TABLE m_loan_overdue_installment_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_charge_id UUID NOT NULL,
  loan_schedule_id UUID NOT NULL,
  frequency_number INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_overdue_installment_charge_loan_charge_id ON m_loan_overdue_installment_charge (loan_charge_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_overdue_installment_charge_loan_schedule_id ON m_loan_overdue_installment_charge (loan_schedule_id);


DROP TABLE IF EXISTS m_loan_payment_allocation_rule;

CREATE TABLE m_loan_payment_allocation_rule (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  transaction_type VARCHAR(255) NOT NULL,
  allocation_types TEXT NOT NULL,
  future_installment_allocation_rule VARCHAR(255) NOT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL,
  UNIQUE (loan_id, transaction_type)
);

CREATE INDEX IF NOT EXISTS idx_m_loan_payment_allocation_rule_created_by ON m_loan_payment_allocation_rule (created_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_payment_allocation_rule_last_modified_by ON m_loan_payment_allocation_rule (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_payment_allocation_rule_loan_id ON m_loan_payment_allocation_rule (loan_id);



DROP TABLE IF EXISTS m_loan;

CREATE TABLE m_loan (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_no VARCHAR(20) NOT NULL UNIQUE,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  client_id UUID DEFAULT NULL,
  group_id UUID DEFAULT NULL,
  glim_id UUID DEFAULT NULL,
  product_id UUID DEFAULT NULL,
  fund_id UUID DEFAULT NULL,
  loan_officer_id UUID DEFAULT NULL,
  loanpurpose_cv_id UUID DEFAULT NULL,
  loan_status_id UUID NOT NULL,
  loan_type_enum SMALLINT NOT NULL,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  principal_amount_proposed DECIMAL(19,6) NOT NULL,
  principal_amount DECIMAL(19,6) NOT NULL,
  approved_principal DECIMAL(19,6) NOT NULL,
  net_disbursal_amount DECIMAL(19,6) NOT NULL,
  arrearstolerance_amount DECIMAL(19,6) DEFAULT NULL,
  is_floating_interest_rate BOOLEAN DEFAULT FALSE,
  interest_rate_differential DECIMAL(19,6) DEFAULT 0.000000,
  nominal_interest_rate_per_period DECIMAL(19,6) DEFAULT NULL,
  interest_period_frequency_enum SMALLINT DEFAULT NULL,
  annual_nominal_interest_rate DECIMAL(19,6) DEFAULT NULL,
  interest_method_enum SMALLINT NOT NULL,
  interest_calculated_in_period_enum SMALLINT NOT NULL DEFAULT 1,
  allow_partial_period_interest_calcualtion BOOLEAN NOT NULL DEFAULT FALSE,
  term_frequency SMALLINT NOT NULL DEFAULT 0,
  term_period_frequency_enum SMALLINT NOT NULL DEFAULT 2,
  repay_every SMALLINT NOT NULL,
  repayment_period_frequency_enum SMALLINT NOT NULL,
  number_of_repayments SMALLINT NOT NULL,
  grace_on_principal_periods SMALLINT DEFAULT NULL,
  recurring_moratorium_principal_periods SMALLINT DEFAULT NULL,
  grace_on_interest_periods SMALLINT DEFAULT NULL,
  grace_interest_free_periods SMALLINT DEFAULT NULL,
  amortization_method_enum SMALLINT NOT NULL,
  submittedon_date DATE DEFAULT NULL,
  approvedon_date DATE DEFAULT NULL,
  approvedon_userid UUID DEFAULT NULL,
  expected_disbursedon_date DATE DEFAULT NULL,
  expected_firstrepaymenton_date DATE DEFAULT NULL,
  interest_calculated_from_date DATE DEFAULT NULL,
  disbursedon_date DATE DEFAULT NULL,
  disbursedon_userid UUID DEFAULT NULL,
  expected_maturedon_date DATE DEFAULT NULL,
  maturedon_date DATE DEFAULT NULL,
  closedon_date DATE DEFAULT NULL,
  closedon_userid UUID DEFAULT NULL,
  total_charges_due_at_disbursement_derived DECIMAL(19,6) DEFAULT NULL,
  principal_disbursed_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  principal_repaid_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  principal_writtenoff_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  principal_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  interest_charged_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  interest_repaid_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  interest_waived_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  interest_writtenoff_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  interest_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  fee_charges_charged_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  fee_charges_repaid_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  fee_charges_waived_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  fee_charges_writtenoff_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  fee_charges_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  penalty_charges_charged_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  penalty_charges_repaid_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  penalty_charges_waived_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  penalty_charges_writtenoff_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  penalty_charges_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_expected_repayment_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_repayment_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_expected_costofloan_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_costofloan_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_waived_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_writtenoff_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  total_overpaid_derived DECIMAL(19,6) DEFAULT NULL,
  rejectedon_date DATE DEFAULT NULL,
  rejectedon_userid UUID DEFAULT NULL,
  rescheduledon_date DATE DEFAULT NULL,
  rescheduledon_userid UUID DEFAULT NULL,
  withdrawnon_date DATE DEFAULT NULL,
  withdrawnon_userid UUID DEFAULT NULL,
  writtenoffon_date DATE DEFAULT NULL,
  loan_transaction_strategy_id UUID DEFAULT NULL,
  sync_disbursement_with_meeting BOOLEAN DEFAULT NULL,
  loan_counter SMALLINT DEFAULT NULL,
  loan_product_counter SMALLINT DEFAULT NULL,
  fixed_emi_amount DECIMAL(19,6) DEFAULT NULL,
  max_outstanding_loan_balance DECIMAL(19,6) DEFAULT NULL,
  grace_on_arrears_ageing SMALLINT DEFAULT NULL,
  is_npa BOOLEAN NOT NULL DEFAULT FALSE,
  total_recovered_derived DECIMAL(19,6) DEFAULT NULL,
  accrued_till DATE DEFAULT NULL,
  interest_recalcualated_on DATE DEFAULT NULL,
  days_in_month_enum SMALLINT NOT NULL DEFAULT 1,
  days_in_year_enum SMALLINT NOT NULL DEFAULT 1,
  interest_recalculation_enabled BOOLEAN NOT NULL DEFAULT FALSE,
  guarantee_amount_derived DECIMAL(19,6) DEFAULT NULL,
  create_standing_instruction_at_disbursement BOOLEAN DEFAULT NULL,
  version INTEGER NOT NULL DEFAULT 1,
  writeoff_reason_cv_id UUID DEFAULT NULL,
  loan_sub_status_id SMALLINT DEFAULT NULL,
  is_topup BOOLEAN NOT NULL DEFAULT FALSE,
  is_equal_amortization BOOLEAN NOT NULL DEFAULT FALSE,
  fixed_principal_percentage_per_installment DECIMAL(5,2) DEFAULT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  principal_adjustments_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  is_fraud BOOLEAN NOT NULL DEFAULT FALSE,
  loan_transaction_strategy_code VARCHAR(100) NOT NULL DEFAULT '-',
  loan_transaction_strategy_name VARCHAR(100) NOT NULL DEFAULT '-',
  last_closed_business_date DATE DEFAULT NULL,
  overpaidon_date DATE DEFAULT NULL,
  is_charged_off BOOLEAN NOT NULL DEFAULT FALSE,
  charged_off_on_date DATE DEFAULT NULL,
  charge_off_reason_cv_id UUID DEFAULT NULL,
  charged_off_by_userid UUID DEFAULT NULL,
  enable_down_payment BOOLEAN NOT NULL DEFAULT FALSE,
  disbursed_amount_percentage_for_down_payment DECIMAL(9,6) DEFAULT NULL,
  enable_installment_level_delinquency BOOLEAN NOT NULL DEFAULT FALSE,
  enable_auto_repayment_for_down_payment BOOLEAN NOT NULL DEFAULT FALSE,
  disable_schedule_extension_for_down_payment BOOLEAN NOT NULL DEFAULT FALSE,
  loan_schedule_type VARCHAR(20) NOT NULL DEFAULT 'CUMULATIVE',
  loan_schedule_processing_type VARCHAR(20) NOT NULL DEFAULT 'HORIZONTAL'
);

CREATE INDEX IF NOT EXISTS idx_m_loan_fund_id ON m_loan (fund_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_client_id ON m_loan (client_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_product_id ON m_loan (product_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_approvedon_userid ON m_loan (approvedon_userid);
CREATE INDEX IF NOT EXISTS idx_m_loan_closedon_userid ON m_loan (closedon_userid);
CREATE INDEX IF NOT EXISTS idx_m_loan_disbursedon_userid ON m_loan (disbursedon_userid);
CREATE INDEX IF NOT EXISTS idx_m_loan_glim_id ON m_loan (glim_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_loan_officer_id ON m_loan (loan_officer_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_loanpurpose_cv_id ON m_loan (loanpurpose_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_rejectedon_userid ON m_loan (rejectedon_userid);
CREATE INDEX IF NOT EXISTS idx_m_loan_withdrawnon_userid ON m_loan (withdrawnon_userid);
CREATE INDEX IF NOT EXISTS idx_m_loan_writeoff_reason_cv_id ON m_loan (writeoff_reason_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_group_id_client_id ON m_loan (group_id, client_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_group_id ON m_loan (group_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_created_by ON m_loan (created_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_last_modified_by ON m_loan (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_loan_status_id ON m_loan (loan_status_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_expected_maturedon_date ON m_loan (expected_maturedon_date);
CREATE INDEX IF NOT EXISTS idx_m_loan_last_closed_business_date ON m_loan (last_closed_business_date);
CREATE INDEX IF NOT EXISTS idx_m_loan_overpaidon_date ON m_loan (overpaidon_date);




DROP TABLE IF EXISTS m_loan_product_payment_allocation_rule;

CREATE TABLE m_loan_product_payment_allocation_rule (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_product_id UUID NOT NULL,
  transaction_type VARCHAR(255) NOT NULL,
  allocation_types TEXT NOT NULL,
  future_installment_allocation_rule VARCHAR(255) NOT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL,
  UNIQUE (loan_product_id, transaction_type)
);

CREATE INDEX IF NOT EXISTS idx_m_loan_product_payment_allocation_rule_created_by ON m_loan_product_payment_allocation_rule (created_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_product_payment_allocation_rule_last_modified_by ON m_loan_product_payment_allocation_rule (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_product_payment_allocation_rule_loan_product_id ON m_loan_product_payment_allocation_rule (loan_product_id);




DROP TABLE IF EXISTS m_loan_rate;

CREATE TABLE m_loan_rate (
  loan_id UUID NOT NULL,
  rate_id UUID NOT NULL,
  PRIMARY KEY (loan_id, rate_id)
);

CREATE INDEX IF NOT EXISTS idx_m_loan_rate_rate_id ON m_loan_rate (rate_id);




DROP TABLE IF EXISTS m_loan_recalculation_details;

CREATE TABLE m_loan_recalculation_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  compound_type_enum SMALLINT NOT NULL,
  reschedule_strategy_enum SMALLINT NOT NULL,
  rest_frequency_type_enum SMALLINT NOT NULL,
  rest_frequency_interval SMALLINT NOT NULL DEFAULT 0,
  compounding_frequency_type_enum SMALLINT DEFAULT NULL,
  compounding_frequency_interval SMALLINT DEFAULT NULL,
  rest_frequency_nth_day_enum INTEGER DEFAULT NULL,
  rest_frequency_on_day INTEGER DEFAULT NULL,
  rest_frequency_weekday_enum INTEGER DEFAULT NULL,
  compounding_frequency_nth_day_enum INTEGER DEFAULT NULL,
  compounding_frequency_on_day INTEGER DEFAULT NULL,
  is_compounding_to_be_posted_as_transaction BOOLEAN NOT NULL DEFAULT FALSE,
  compounding_frequency_weekday_enum INTEGER DEFAULT NULL,
  allow_compounding_on_eod BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_loan_recalculation_details_loan_id ON m_loan_recalculation_details (loan_id);



DROP TABLE IF EXISTS m_loan_repayment_schedule_history;

CREATE TABLE m_loan_repayment_schedule_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  loan_reschedule_request_id UUID DEFAULT NULL,
  fromdate DATE DEFAULT NULL,
  duedate DATE NOT NULL,
  installment SMALLINT NOT NULL,
  principal_amount DECIMAL(19,6) DEFAULT NULL,
  interest_amount DECIMAL(19,6) DEFAULT NULL,
  fee_charges_amount DECIMAL(19,6) DEFAULT NULL,
  penalty_charges_amount DECIMAL(19,6) DEFAULT NULL,
  createdby_id UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  version INTEGER NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_repayment_schedule_history_loan_id ON m_loan_repayment_schedule_history (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_repayment_schedule_history_loan_reschedule_request_id ON m_loan_repayment_schedule_history (loan_reschedule_request_id);



DROP TABLE IF EXISTS m_loan_repayment_schedule;

CREATE TABLE m_loan_repayment_schedule (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  fromdate DATE DEFAULT NULL,
  duedate DATE NOT NULL,
  installment SMALLINT NOT NULL,
  principal_amount DECIMAL(19,6) DEFAULT NULL,
  principal_completed_derived DECIMAL(19,6) DEFAULT NULL,
  principal_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  interest_amount DECIMAL(19,6) DEFAULT NULL,
  interest_completed_derived DECIMAL(19,6) DEFAULT NULL,
  interest_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  interest_waived_derived DECIMAL(19,6) DEFAULT NULL,
  accrual_interest_derived DECIMAL(19,6) DEFAULT NULL,
  reschedule_interest_portion DECIMAL(19,6) DEFAULT NULL,
  fee_charges_amount DECIMAL(19,6) DEFAULT NULL,
  fee_charges_completed_derived DECIMAL(19,6) DEFAULT NULL,
  fee_charges_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  fee_charges_waived_derived DECIMAL(19,6) DEFAULT NULL,
  accrual_fee_charges_derived DECIMAL(19,6) DEFAULT NULL,
  penalty_charges_amount DECIMAL(19,6) DEFAULT NULL,
  penalty_charges_completed_derived DECIMAL(19,6) DEFAULT NULL,
  penalty_charges_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  penalty_charges_waived_derived DECIMAL(19,6) DEFAULT NULL,
  accrual_penalty_charges_derived DECIMAL(19,6) DEFAULT NULL,
  total_paid_in_advance_derived DECIMAL(19,6) DEFAULT NULL,
  total_paid_late_derived DECIMAL(19,6) DEFAULT NULL,
  completed_derived BOOLEAN NOT NULL,
  obligations_met_on_date DATE DEFAULT NULL,
  created_by UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID NOT NULL,
  recalculated_interest_component BOOLEAN NOT NULL DEFAULT FALSE,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  is_additional BOOLEAN NOT NULL DEFAULT FALSE,
  credits_amount DECIMAL(19,6) DEFAULT NULL,
  is_down_payment BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_loan_repayment_schedule_loan_id ON m_loan_repayment_schedule (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_repayment_schedule_created_by ON m_loan_repayment_schedule (created_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_repayment_schedule_last_modified_by ON m_loan_repayment_schedule (last_modified_by);




DROP TABLE IF EXISTS m_loan_reschedule_request;

CREATE TABLE m_loan_reschedule_request (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  status_enum SMALLINT NOT NULL,
  reschedule_from_installment SMALLINT NOT NULL,
  reschedule_from_date DATE NOT NULL,
  recalculate_interest BOOLEAN DEFAULT NULL,
  reschedule_reason_cv_id INTEGER DEFAULT NULL,
  reschedule_reason_comment VARCHAR(500) DEFAULT NULL,
  submitted_on_date DATE NOT NULL,
  submitted_by_user_id UUID NOT NULL,
  approved_on_date DATE DEFAULT NULL,
  approved_by_user_id UUID DEFAULT NULL,
  rejected_on_date DATE DEFAULT NULL,
  rejected_by_user_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_reschedule_request_approved_by_user_id ON m_loan_reschedule_request (approved_by_user_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_reschedule_request_loan_id ON m_loan_reschedule_request (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_reschedule_request_rejected_by_user_id ON m_loan_reschedule_request (rejected_by_user_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_reschedule_request_reschedule_reason_cv_id ON m_loan_reschedule_request (reschedule_reason_cv_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_reschedule_request_submitted_by_user_id ON m_loan_reschedule_request (submitted_by_user_id);



DROP TABLE IF EXISTS m_loan_reschedule_request_term_variations_mapping;

CREATE TABLE m_loan_reschedule_request_term_variations_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_reschedule_request_id UUID NOT NULL,
  loan_term_variations_id UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_reschedule_request_term_variations_mapping_loan_reschedule_request_id ON m_loan_reschedule_request_term_variations_mapping (loan_reschedule_request_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_reschedule_request_term_variations_mapping_loan_term_variations_id ON m_loan_reschedule_request_term_variations_mapping (loan_term_variations_id);



DROP TABLE IF EXISTS m_loan_term_variations;

CREATE TABLE m_loan_term_variations (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  term_type SMALLINT NOT NULL,
  applicable_date DATE NOT NULL,
  decimal_value DECIMAL(19,6) DEFAULT NULL,
  date_value DATE DEFAULT NULL,
  is_specific_to_installment BOOLEAN NOT NULL DEFAULT FALSE,
  applied_on_loan_status SMALLINT NOT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  parent_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_term_variations_loan_id ON m_loan_term_variations (loan_id);



DROP TABLE IF EXISTS m_loan_topup;

CREATE TABLE m_loan_topup (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  closure_loan_id UUID NOT NULL,
  account_transfer_details_id UUID DEFAULT NULL,
  topup_amount DECIMAL(19,6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_topup_account_transfer_details_id ON m_loan_topup (account_transfer_details_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_topup_closure_loan_id ON m_loan_topup (closure_loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_topup_loan_id ON m_loan_topup (loan_id);




DROP TABLE IF EXISTS m_loan_tranche_charges;

CREATE TABLE m_loan_tranche_charges (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  charge_id UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_tranche_charges_charge_id ON m_loan_tranche_charges (charge_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_tranche_charges_loan_id ON m_loan_tranche_charges (loan_id);





DROP TABLE IF EXISTS m_loan_tranche_disbursement_charge;

CREATE TABLE m_loan_tranche_disbursement_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_charge_id UUID NOT NULL,
  disbursement_detail_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_tranche_disbursement_charge_loan_charge_id ON m_loan_tranche_disbursement_charge (loan_charge_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_tranche_disbursement_charge_disbursement_detail_id ON m_loan_tranche_disbursement_charge (disbursement_detail_id);



DROP TABLE IF EXISTS m_loan_transaction;

CREATE TABLE m_loan_transaction (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_id UUID NOT NULL,
  office_id UUID NOT NULL,
  payment_detail_id UUID DEFAULT NULL,
  is_reversed BOOLEAN NOT NULL,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  transaction_type_enum SMALLINT NOT NULL,
  transaction_date DATE NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  principal_portion_derived DECIMAL(19,6) DEFAULT NULL,
  interest_portion_derived DECIMAL(19,6) DEFAULT NULL,
  fee_charges_portion_derived DECIMAL(19,6) DEFAULT NULL,
  penalty_charges_portion_derived DECIMAL(19,6) DEFAULT NULL,
  overpayment_portion_derived DECIMAL(19,6) DEFAULT NULL,
  unrecognized_income_portion DECIMAL(19,6) DEFAULT NULL,
  outstanding_loan_balance_derived DECIMAL(19,6) DEFAULT NULL,
  submitted_on_date DATE NOT NULL,
  manually_adjusted_or_reversed BOOLEAN DEFAULT FALSE,
  created_date TIMESTAMP(6) DEFAULT NULL,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  charge_refund_charge_type VARCHAR(1) DEFAULT NULL,
  reversal_external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  reversed_on_date DATE DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_loan_id ON m_loan_transaction (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_office_id ON m_loan_transaction (office_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_payment_detail_id ON m_loan_transaction (payment_detail_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_created_by ON m_loan_transaction (created_by);
CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_last_modified_by ON m_loan_transaction (last_modified_by);



DROP TABLE IF EXISTS m_loan_transaction_relation;

CREATE TABLE m_loan_transaction_relation (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  from_loan_transaction_id UUID NOT NULL,
  to_loan_transaction_id UUID DEFAULT NULL,
  relation_type_enum INTEGER NOT NULL,
  created_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID NOT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL,
  to_loan_charge_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_relation_from_loan_transaction_id ON m_loan_transaction_relation (from_loan_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_relation_to_loan_transaction_id ON m_loan_transaction_relation (to_loan_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_relation_to_loan_charge_id ON m_loan_transaction_relation (to_loan_charge_id);



DROP TABLE IF EXISTS m_loan_transaction_repayment_schedule_mapping;

CREATE TABLE m_loan_transaction_repayment_schedule_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_transaction_id UUID NOT NULL,
  loan_repayment_schedule_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  principal_portion_derived DECIMAL(19,6) DEFAULT NULL,
  interest_portion_derived DECIMAL(19,6) DEFAULT NULL,
  fee_charges_portion_derived DECIMAL(19,6) DEFAULT NULL,
  penalty_charges_portion_derived DECIMAL(19,6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_repayment_schedule_mapping_loan_transaction_id ON m_loan_transaction_repayment_schedule_mapping (loan_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_loan_transaction_repayment_schedule_mapping_loan_repayment_schedule_id ON m_loan_transaction_repayment_schedule_mapping (loan_repayment_schedule_id);



DROP TABLE IF EXISTS m_loanproduct_provisioning_entry;

CREATE TABLE m_loanproduct_provisioning_entry (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  history_id UUID NOT NULL,
  criteria_id UUID NOT NULL,
  currency_code VARCHAR(3) NOT NULL,
  office_id UUID NOT NULL,
  product_id UUID NOT NULL,
  category_id UUID NOT NULL,
  overdue_in_days BIGINT DEFAULT 0,
  reseve_amount DECIMAL(20,6) DEFAULT 0.000000,
  liability_account UUID DEFAULT NULL,
  expense_account UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_entry_category_id ON m_loanproduct_provisioning_entry (category_id);
CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_entry_criteria_id ON m_loanproduct_provisioning_entry (criteria_id);
CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_entry_expense_account ON m_loanproduct_provisioning_entry (expense_account);
CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_entry_history_id ON m_loanproduct_provisioning_entry (history_id);
CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_entry_liability_account ON m_loanproduct_provisioning_entry (liability_account);
CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_entry_office_id ON m_loanproduct_provisioning_entry (office_id);
CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_entry_product_id ON m_loanproduct_provisioning_entry (product_id);




DROP TABLE IF EXISTS m_loanproduct_provisioning_mapping;

CREATE TABLE m_loanproduct_provisioning_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  product_id UUID NOT NULL UNIQUE,
  criteria_id UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_loanproduct_provisioning_mapping_criteria_id ON m_loanproduct_provisioning_mapping (criteria_id);


DROP TABLE IF EXISTS m_mandatory_savings_schedule;

CREATE TABLE m_mandatory_savings_schedule (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_account_id UUID NOT NULL,
  fromdate DATE DEFAULT NULL,
  duedate DATE NOT NULL,
  installment SMALLINT NOT NULL,
  deposit_amount DECIMAL(19,6) DEFAULT NULL,
  deposit_amount_completed_derived DECIMAL(19,6) DEFAULT NULL,
  total_paid_in_advance_derived DECIMAL(19,6) DEFAULT NULL,
  total_paid_late_derived DECIMAL(19,6) DEFAULT NULL,
  completed_derived BOOLEAN NOT NULL,
  obligations_met_on_date DATE DEFAULT NULL,
  created_by UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_mandatory_savings_schedule_savings_account_id ON m_mandatory_savings_schedule (savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_mandatory_savings_schedule_created_by ON m_mandatory_savings_schedule (created_by);
CREATE INDEX IF NOT EXISTS idx_m_mandatory_savings_schedule_last_modified_by ON m_mandatory_savings_schedule (last_modified_by);




DROP TABLE IF EXISTS m_meeting;

CREATE TABLE m_meeting (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  calendar_instance_id UUID NOT NULL,
  meeting_date DATE NOT NULL,
  UNIQUE (calendar_instance_id, meeting_date)
);




DROP TABLE IF EXISTS m_note;

CREATE TABLE m_note (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  client_id UUID DEFAULT NULL,
  group_id UUID DEFAULT NULL,
  loan_id UUID DEFAULT NULL,
  loan_transaction_id UUID DEFAULT NULL,
  savings_account_id UUID DEFAULT NULL,
  savings_account_transaction_id UUID DEFAULT NULL,
  share_account_id UUID DEFAULT NULL,
  note_type_enum SMALLINT NOT NULL,
  note VARCHAR(1000) DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  created_by UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) DEFAULT NULL,
  last_modified_on_utc TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_note_loan_transaction_id ON m_note (loan_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_note_loan_id ON m_note (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_note_created_by ON m_note (created_by);
CREATE INDEX IF NOT EXISTS idx_m_note_client_id ON m_note (client_id);
CREATE INDEX IF NOT EXISTS idx_m_note_last_modified_by ON m_note (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_note_group_id ON m_note (group_id);
CREATE INDEX IF NOT EXISTS idx_m_note_savings_account_id ON m_note (savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_note_savings_account_transaction_id ON m_note (savings_account_transaction_id);


DROP TABLE IF EXISTS m_office;

CREATE TABLE m_office (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  parent_id UUID DEFAULT NULL,
  hierarchy VARCHAR(100) DEFAULT NULL,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  name VARCHAR(50) NOT NULL UNIQUE,
  opening_date DATE NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_office_parent_id ON m_office (parent_id);



DROP TABLE IF EXISTS m_office_transaction;

CREATE TABLE m_office_transaction (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  from_office_id UUID DEFAULT NULL,
  to_office_id UUID DEFAULT NULL,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits INTEGER NOT NULL,
  transaction_amount DECIMAL(19,6) NOT NULL,
  transaction_date DATE NOT NULL,
  description VARCHAR(100) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_office_transaction_from_office_id ON m_office_transaction (from_office_id);
CREATE INDEX IF NOT EXISTS idx_m_office_transaction_to_office_id ON m_office_transaction (to_office_id);




DROP TABLE IF EXISTS m_organisation_creditbureau;

CREATE TABLE m_organisation_creditbureau (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  alias VARCHAR(50) NOT NULL,
  creditbureau_id UUID NOT NULL,
  is_active BOOLEAN DEFAULT NULL,
  UNIQUE (alias, creditbureau_id)
);

CREATE INDEX IF NOT EXISTS idx_m_organisation_creditbureau_creditbureau_id ON m_organisation_creditbureau (creditbureau_id);



DROP TABLE IF EXISTS m_organisation_currency;

CREATE TABLE m_organisation_currency (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  code VARCHAR(3) NOT NULL,
  decimal_places SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  name VARCHAR(50) NOT NULL,
  display_symbol VARCHAR(10) DEFAULT NULL,
  internationalized_name_code VARCHAR(50) NOT NULL
);



DROP TABLE IF EXISTS m_password_validation_policy;

CREATE TABLE m_password_validation_policy (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  regex TEXT NOT NULL,
  description TEXT NOT NULL,
  active BOOLEAN NOT NULL DEFAULT FALSE,
  key VARCHAR(255) NOT NULL
);



DROP TABLE IF EXISTS m_payment_detail;

CREATE TABLE m_payment_detail (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  payment_type_id UUID NOT NULL,
  account_number VARCHAR(100) DEFAULT NULL,
  check_number VARCHAR(100) DEFAULT NULL,
  receipt_number VARCHAR(100) DEFAULT NULL,
  bank_number VARCHAR(100) DEFAULT NULL,
  routing_code VARCHAR(100) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_payment_detail_payment_type_id ON m_payment_detail (payment_type_id);


DROP TABLE IF EXISTS m_payment_type;

CREATE TABLE m_payment_type (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  value VARCHAR(100) DEFAULT NULL,
  description VARCHAR(500) DEFAULT NULL,
  is_cash_payment BOOLEAN DEFAULT FALSE,
  order_position INTEGER NOT NULL DEFAULT 0,
  code_name VARCHAR(100) DEFAULT NULL,
  is_system_defined BOOLEAN NOT NULL DEFAULT FALSE
);



DROP TABLE IF EXISTS m_permission;

CREATE TABLE m_permission (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  grouping VARCHAR(45) DEFAULT NULL,
  code VARCHAR(100) NOT NULL UNIQUE,
  entity_name VARCHAR(100) DEFAULT NULL,
  action_name VARCHAR(100) DEFAULT NULL,
  can_maker_checker BOOLEAN NOT NULL DEFAULT TRUE
);



DROP TABLE IF EXISTS m_pocket_accounts_mapping;

CREATE TABLE m_pocket_accounts_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  pocket_id UUID NOT NULL,
  account_id UUID NOT NULL,
  account_type INTEGER NOT NULL,
  account_number VARCHAR(20) NOT NULL,
  UNIQUE (pocket_id, account_id, account_type)
);

CREATE INDEX IF NOT EXISTS idx_m_pocket_accounts_mapping_pocket_id ON m_pocket_accounts_mapping (pocket_id);



DROP TABLE IF EXISTS m_pocket;

CREATE TABLE m_pocket (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  app_user_id UUID NOT NULL UNIQUE
);



DROP TABLE IF EXISTS m_portfolio_account_associations;

CREATE TABLE m_portfolio_account_associations (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_account_id UUID DEFAULT NULL,
  savings_account_id UUID DEFAULT NULL,
  linked_loan_account_id UUID DEFAULT NULL,
  linked_savings_account_id UUID DEFAULT NULL,
  association_type_enum SMALLINT NOT NULL DEFAULT 1,
  is_active BOOLEAN NOT NULL DEFAULT TRUE
);

CREATE INDEX IF NOT EXISTS idx_m_portfolio_account_associations_loan_account_id ON m_portfolio_account_associations (loan_account_id);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_account_associations_savings_account_id ON m_portfolio_account_associations (savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_account_associations_linked_loan_account_id ON m_portfolio_account_associations (linked_loan_account_id);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_account_associations_linked_savings_account_id ON m_portfolio_account_associations (linked_savings_account_id);




DROP TABLE IF EXISTS m_portfolio_command_source;

CREATE TABLE m_portfolio_command_source (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  action_name VARCHAR(50) NOT NULL,
  entity_name VARCHAR(50) NOT NULL,
  office_id UUID DEFAULT NULL,
  group_id UUID DEFAULT NULL,
  client_id UUID DEFAULT NULL,
  loan_id UUID DEFAULT NULL,
  savings_account_id UUID DEFAULT NULL,
  api_get_url VARCHAR(100) NOT NULL,
  resource_id UUID DEFAULT NULL,
  subresource_id UUID DEFAULT NULL,
  command_as_json TEXT NOT NULL,
  maker_id UUID NOT NULL,
  made_on_date TIMESTAMP(6) DEFAULT NULL,
  checker_id UUID DEFAULT NULL,
  checked_on_date TIMESTAMP(6) DEFAULT NULL,
  status SMALLINT DEFAULT NULL,
  product_id UUID DEFAULT NULL,
  transaction_id VARCHAR(100) DEFAULT NULL,
  creditbureau_id UUID DEFAULT NULL,
  organisation_creditbureau_id UUID DEFAULT NULL,
  made_on_date_utc TIMESTAMP(6) DEFAULT NULL,
  checked_on_date_utc TIMESTAMP(6) DEFAULT NULL,
  job_name VARCHAR(100) DEFAULT NULL,
  idempotency_key VARCHAR(50) NOT NULL,
  resource_external_id VARCHAR(100) DEFAULT NULL,
  subresource_external_id VARCHAR(100) DEFAULT NULL,
  result TEXT DEFAULT NULL,
  result_status_code INTEGER DEFAULT NULL,
  UNIQUE (action_name, entity_name, idempotency_key)
);

CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_checker_id ON m_portfolio_command_source (checker_id);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_maker_id ON m_portfolio_command_source (maker_id);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_action_name ON m_portfolio_command_source (action_name);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_checked_on_date ON m_portfolio_command_source (checked_on_date);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_entity_name_resource_id ON m_portfolio_command_source (entity_name, resource_id);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_made_on_date ON m_portfolio_command_source (made_on_date);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_office_id ON m_portfolio_command_source (office_id);
CREATE INDEX IF NOT EXISTS idx_m_portfolio_command_source_status ON m_portfolio_command_source (status);




DROP TABLE IF EXISTS m_product_loan_charge;

CREATE TABLE m_product_loan_charge (
  product_loan_id UUID NOT NULL,
  charge_id UUID NOT NULL,
  PRIMARY KEY (product_loan_id, charge_id)
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_charge_charge_id ON m_product_loan_charge (charge_id);



DROP TABLE IF EXISTS m_product_loan_configurable_attributes;

CREATE TABLE m_product_loan_configurable_attributes (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_product_id UUID NOT NULL,
  amortization_method_enum SMALLINT NOT NULL DEFAULT 1,
  interest_method_enum SMALLINT NOT NULL DEFAULT 1,
  loan_transaction_strategy_code SMALLINT DEFAULT NULL,
  interest_calculated_in_period_enum SMALLINT NOT NULL DEFAULT 1,
  arrearstolerance_amount BOOLEAN NOT NULL DEFAULT TRUE,
  repay_every BOOLEAN NOT NULL DEFAULT TRUE,
  moratorium BOOLEAN NOT NULL DEFAULT TRUE,
  grace_on_arrears_ageing BOOLEAN NOT NULL DEFAULT TRUE
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_configurable_attributes_loan_product_id ON m_product_loan_configurable_attributes (loan_product_id);




DROP TABLE IF EXISTS m_product_loan_floating_rates;

CREATE TABLE m_product_loan_floating_rates (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_product_id UUID NOT NULL,
  floating_rates_id UUID NOT NULL,
  interest_rate_differential DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  min_differential_lending_rate DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  default_differential_lending_rate DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  max_differential_lending_rate DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  is_floating_interest_rate_calculation_allowed BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_floating_rates_floating_rates_id ON m_product_loan_floating_rates (floating_rates_id);
CREATE INDEX IF NOT EXISTS idx_m_product_loan_floating_rates_loan_product_id ON m_product_loan_floating_rates (loan_product_id);




DROP TABLE IF EXISTS m_product_loan_guarantee_details;

CREATE TABLE m_product_loan_guarantee_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_product_id UUID NOT NULL,
  mandatory_guarantee DECIMAL(19,5) NOT NULL,
  minimum_guarantee_from_own_funds DECIMAL(19,5) DEFAULT NULL,
  minimum_guarantee_from_guarantor_funds DECIMAL(19,5) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_guarantee_details_loan_product_id ON m_product_loan_guarantee_details (loan_product_id);



DROP TABLE IF EXISTS m_product_loan;

CREATE TABLE m_product_loan (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  short_name VARCHAR(4) NOT NULL UNIQUE,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  principal_amount DECIMAL(19,6) DEFAULT NULL,
  min_principal_amount DECIMAL(19,6) DEFAULT NULL,
  max_principal_amount DECIMAL(19,6) DEFAULT NULL,
  arrearstolerance_amount DECIMAL(19,6) DEFAULT NULL,
  name VARCHAR(100) NOT NULL UNIQUE,
  description VARCHAR(500) DEFAULT NULL,
  fund_id UUID DEFAULT NULL,
  is_linked_to_floating_interest_rates BOOLEAN NOT NULL DEFAULT FALSE,
  allow_variabe_installments BOOLEAN NOT NULL DEFAULT FALSE,
  nominal_interest_rate_per_period DECIMAL(19,6) DEFAULT NULL,
  min_nominal_interest_rate_per_period DECIMAL(19,6) DEFAULT NULL,
  max_nominal_interest_rate_per_period DECIMAL(19,6) DEFAULT NULL,
  interest_period_frequency_enum SMALLINT DEFAULT NULL,
  annual_nominal_interest_rate DECIMAL(19,6) DEFAULT NULL,
  interest_method_enum SMALLINT NOT NULL,
  interest_calculated_in_period_enum SMALLINT NOT NULL DEFAULT 1,
  allow_partial_period_interest_calcualtion BOOLEAN NOT NULL DEFAULT FALSE,
  term_frequency SMALLINT NOT NULL DEFAULT 0,
  term_period_frequency_enum SMALLINT NOT NULL DEFAULT 2,
  repay_every SMALLINT NOT NULL,
  repayment_period_frequency_enum SMALLINT NOT NULL,
  number_of_repayments SMALLINT NOT NULL,
  min_number_of_repayments SMALLINT DEFAULT NULL,
  max_number_of_repayments SMALLINT DEFAULT NULL,
  grace_on_principal_periods SMALLINT DEFAULT NULL,
  recurring_moratorium_principal_periods SMALLINT DEFAULT NULL,
  grace_on_interest_periods SMALLINT DEFAULT NULL,
  grace_interest_free_periods SMALLINT DEFAULT NULL,
  amortization_method_enum SMALLINT NOT NULL,
  accounting_type SMALLINT NOT NULL,
  loan_transaction_strategy_id UUID DEFAULT NULL,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  include_in_borrower_cycle BOOLEAN NOT NULL DEFAULT FALSE,
  use_borrower_cycle BOOLEAN NOT NULL DEFAULT FALSE,
  start_date DATE DEFAULT NULL,
  close_date DATE DEFAULT NULL,
  allow_multiple_disbursals BOOLEAN NOT NULL DEFAULT FALSE,
  max_disbursals INTEGER DEFAULT NULL,
  max_outstanding_loan_balance DECIMAL(19,6) DEFAULT NULL,
  grace_on_arrears_ageing SMALLINT DEFAULT NULL,
  overdue_days_for_npa SMALLINT DEFAULT NULL,
  days_in_month_enum SMALLINT NOT NULL DEFAULT 1,
  days_in_year_enum SMALLINT NOT NULL DEFAULT 1,
  interest_recalculation_enabled BOOLEAN NOT NULL DEFAULT FALSE,
  min_days_between_disbursal_and_first_repayment INTEGER DEFAULT NULL,
  hold_guarantee_funds BOOLEAN NOT NULL DEFAULT FALSE,
  principal_threshold_for_last_installment DECIMAL(5,2) NOT NULL DEFAULT 50.00,
  account_moves_out_of_npa_only_on_arrears_completion BOOLEAN NOT NULL DEFAULT FALSE,
  can_define_fixed_emi_amount BOOLEAN NOT NULL DEFAULT FALSE,
  instalment_amount_in_multiples_of DECIMAL(19,6) DEFAULT NULL,
  can_use_for_topup BOOLEAN NOT NULL DEFAULT FALSE,
  sync_expected_with_disbursement_date BOOLEAN DEFAULT FALSE,
  is_equal_amortization BOOLEAN NOT NULL DEFAULT FALSE,
  fixed_principal_percentage_per_installment DECIMAL(5,2) DEFAULT NULL,
  disallow_expected_disbursements BOOLEAN NOT NULL DEFAULT FALSE,
  allow_approved_disbursed_amounts_over_applied BOOLEAN NOT NULL DEFAULT FALSE,
  over_applied_calculation_type VARCHAR(10) DEFAULT NULL,
  over_applied_number INTEGER DEFAULT NULL,
  delinquency_bucket_id UUID DEFAULT NULL,
  loan_transaction_strategy_code VARCHAR(100) NOT NULL DEFAULT '-',
  loan_transaction_strategy_name VARCHAR(100) NOT NULL DEFAULT '-',
  due_days_for_repayment_event INTEGER DEFAULT NULL,
  overdue_days_for_repayment_event INTEGER DEFAULT NULL,
  enable_down_payment BOOLEAN NOT NULL DEFAULT FALSE,
  disbursed_amount_percentage_for_down_payment DECIMAL(9,6) DEFAULT NULL,
  enable_installment_level_delinquency BOOLEAN NOT NULL DEFAULT FALSE,
  enable_auto_repayment_for_down_payment BOOLEAN NOT NULL DEFAULT FALSE,
  repayment_start_date_type_enum SMALLINT NOT NULL DEFAULT 1,
  disable_schedule_extension_for_down_payment BOOLEAN NOT NULL DEFAULT FALSE,
  loan_schedule_type VARCHAR(20) NOT NULL DEFAULT 'CUMULATIVE',
  loan_schedule_processing_type VARCHAR(20) NOT NULL DEFAULT 'HORIZONTAL'
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_fund_id ON m_product_loan (fund_id);
CREATE INDEX IF NOT EXISTS idx_m_product_loan_loan_transaction_strategy_id ON m_product_loan (loan_transaction_strategy_id);
CREATE INDEX IF NOT EXISTS idx_m_product_loan_delinquency_bucket_id ON m_product_loan (delinquency_bucket_id);



DROP TABLE IF EXISTS m_product_loan_rate;

CREATE TABLE m_product_loan_rate (
  product_loan_id UUID NOT NULL,
  rate_id UUID NOT NULL,
  PRIMARY KEY (product_loan_id, rate_id)
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_rate_rate_id ON m_product_loan_rate (rate_id);



DROP TABLE IF EXISTS m_product_loan_recalculation_details;

CREATE TABLE m_product_loan_recalculation_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  product_id UUID NOT NULL,
  compound_type_enum SMALLINT NOT NULL,
  reschedule_strategy_enum SMALLINT NOT NULL,
  rest_frequency_type_enum SMALLINT NOT NULL,
  rest_frequency_interval SMALLINT NOT NULL DEFAULT 0,
  arrears_based_on_original_schedule BOOLEAN NOT NULL DEFAULT FALSE,
  pre_close_interest_calculation_strategy SMALLINT NOT NULL DEFAULT 1,
  compounding_frequency_type_enum SMALLINT DEFAULT NULL,
  compounding_frequency_interval SMALLINT DEFAULT NULL,
  rest_frequency_nth_day_enum INTEGER DEFAULT NULL,
  rest_frequency_on_day INTEGER DEFAULT NULL,
  rest_frequency_weekday_enum INTEGER DEFAULT NULL,
  compounding_frequency_nth_day_enum INTEGER DEFAULT NULL,
  compounding_frequency_on_day INTEGER DEFAULT NULL,
  compounding_frequency_weekday_enum INTEGER DEFAULT NULL,
  is_compounding_to_be_posted_as_transaction BOOLEAN NOT NULL DEFAULT FALSE,
  allow_compounding_on_eod BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_recalculation_details_product_id ON m_product_loan_recalculation_details (product_id);



DROP TABLE IF EXISTS m_product_loan_variable_installment_config;

CREATE TABLE m_product_loan_variable_installment_config (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_product_id UUID NOT NULL,
  minimum_gap INTEGER NOT NULL,
  maximum_gap INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_variable_installment_config_loan_product_id ON m_product_loan_variable_installment_config (loan_product_id);



DROP TABLE IF EXISTS m_product_loan_variations_borrower_cycle;

CREATE TABLE m_product_loan_variations_borrower_cycle (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  loan_product_id UUID NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000',
  borrower_cycle_number INTEGER NOT NULL DEFAULT 0,
  value_condition INTEGER NOT NULL DEFAULT 0,
  param_type INTEGER NOT NULL DEFAULT 0,
  default_value DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  max_value DECIMAL(19,6) DEFAULT NULL,
  min_value DECIMAL(19,6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_product_loan_variations_borrower_cycle_loan_product_id ON m_product_loan_variations_borrower_cycle (loan_product_id);


DROP TABLE IF EXISTS m_product_mix;

CREATE TABLE m_product_mix (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  product_id UUID NOT NULL,
  restricted_product_id UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_product_mix_product_id ON m_product_mix (product_id);
CREATE INDEX IF NOT EXISTS idx_m_product_mix_restricted_product_id ON m_product_mix (restricted_product_id);


DROP TABLE IF EXISTS m_provision_category;

CREATE TABLE m_provision_category (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  category_name VARCHAR(100) NOT NULL UNIQUE,
  description VARCHAR(300) DEFAULT NULL
);



DROP TABLE IF EXISTS m_provisioning_criteria_definition;

CREATE TABLE m_provisioning_criteria_definition (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  criteria_id UUID NOT NULL,
  category_id UUID NOT NULL,
  min_age BIGINT NOT NULL,
  max_age BIGINT NOT NULL,
  provision_percentage DECIMAL(5,2) NOT NULL,
  liability_account UUID DEFAULT NULL,
  expense_account UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_provisioning_criteria_definition_criteria_id ON m_provisioning_criteria_definition (criteria_id);
CREATE INDEX IF NOT EXISTS idx_m_provisioning_criteria_definition_category_id ON m_provisioning_criteria_definition (category_id);
CREATE INDEX IF NOT EXISTS idx_m_provisioning_criteria_definition_liability_account ON m_provisioning_criteria_definition (liability_account);
CREATE INDEX IF NOT EXISTS idx_m_provisioning_criteria_definition_expense_account ON m_provisioning_criteria_definition (expense_account);



DROP TABLE IF EXISTS m_provisioning_criteria;

CREATE TABLE m_provisioning_criteria (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  criteria_name VARCHAR(200) NOT NULL UNIQUE,
  createdby_id UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_provisioning_criteria_createdby_id ON m_provisioning_criteria (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_provisioning_criteria_lastmodifiedby_id ON m_provisioning_criteria (lastmodifiedby_id);



DROP TABLE IF EXISTS m_provisioning_history;

CREATE TABLE m_provisioning_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  journal_entry_created BOOLEAN DEFAULT FALSE,
  createdby_id UUID DEFAULT NULL,
  created_date DATE DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  lastmodified_date DATE DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_provisioning_history_createdby_id ON m_provisioning_history (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_provisioning_history_lastmodifiedby_id ON m_provisioning_history (lastmodifiedby_id);



DROP TABLE IF EXISTS m_rate;

CREATE TABLE m_rate (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(250) NOT NULL,
  percentage DECIMAL(10,2) NOT NULL,
  active BOOLEAN DEFAULT FALSE,
  product_apply SMALLINT NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  createdby_id UUID NOT NULL,
  lastmodifiedby_id UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  approve_user UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_rate_approve_user ON m_rate (approve_user);
CREATE INDEX IF NOT EXISTS idx_m_rate_createdby_id ON m_rate (createdby_id);





DROP TABLE IF EXISTS m_repayment_with_post_dated_checks;

CREATE TABLE m_repayment_with_post_dated_checks (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  check_no VARCHAR(20) NOT NULL UNIQUE,
  amount DECIMAL(20,5) NOT NULL,
  loan_id UUID DEFAULT NULL,
  repayment_id UUID DEFAULT NULL,
  account_no BIGINT NOT NULL,
  bank_name VARCHAR(200) NOT NULL,
  repayment_date DATE NOT NULL,
  status SMALLINT DEFAULT 0
);

CREATE INDEX IF NOT EXISTS idx_m_repayment_with_post_dated_checks_loan_id ON m_repayment_with_post_dated_checks (loan_id);
CREATE INDEX IF NOT EXISTS idx_m_repayment_with_post_dated_checks_repayment_id ON m_repayment_with_post_dated_checks (repayment_id);



DROP TABLE IF EXISTS m_report_mailing_job_configuration;

CREATE TABLE m_report_mailing_job_configuration (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(50) NOT NULL UNIQUE,
  value VARCHAR(200) NOT NULL
);




DROP TABLE IF EXISTS m_report_mailing_job;

CREATE TABLE m_report_mailing_job (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) NOT NULL UNIQUE,
  description TEXT DEFAULT NULL,
  start_datetime TIMESTAMP(6) DEFAULT NULL,
  recurrence VARCHAR(100) DEFAULT NULL,
  created_date DATE NOT NULL,
  createdby_id UUID NOT NULL,
  lastmodified_date DATE DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  email_recipients TEXT NOT NULL,
  email_subject VARCHAR(100) NOT NULL,
  email_message TEXT NOT NULL,
  email_attachment_file_format VARCHAR(10) NOT NULL,
  stretchy_report_id INTEGER NOT NULL,
  stretchy_report_param_map TEXT DEFAULT NULL,
  previous_run_datetime TIMESTAMP(6) DEFAULT NULL,
  next_run_datetime TIMESTAMP(6) DEFAULT NULL,
  previous_run_status VARCHAR(10) DEFAULT NULL,
  previous_run_error_log TEXT DEFAULT NULL,
  previous_run_error_message TEXT DEFAULT NULL,
  number_of_runs INTEGER NOT NULL DEFAULT 0,
  is_active BOOLEAN NOT NULL DEFAULT FALSE,
  is_deleted BOOLEAN NOT NULL DEFAULT FALSE,
  run_as_userid UUID NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_report_mailing_job_createdby ON m_report_mailing_job (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_report_mailing_job_lastmodifiedby_id ON m_report_mailing_job (lastmodifiedby_id);
CREATE INDEX IF NOT EXISTS idx_m_report_mailing_job_run_as_userid ON m_report_mailing_job (run_as_userid);
CREATE INDEX IF NOT EXISTS idx_m_report_mailing_job_stretchy_report_id ON m_report_mailing_job (stretchy_report_id);



DROP TABLE IF EXISTS m_report_mailing_job_run_history;

CREATE TABLE m_report_mailing_job_run_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  job_id UUID NOT NULL,
  start_datetime TIMESTAMP(6) DEFAULT NULL,
  end_datetime TIMESTAMP(6) DEFAULT NULL,
  status VARCHAR(10) NOT NULL,
  error_message TEXT DEFAULT NULL,
  error_log TEXT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_report_mailing_job_run_history_job_id ON m_report_mailing_job_run_history (job_id);



DROP TABLE IF EXISTS m_role_permission;

CREATE TABLE m_role_permission (
  role_id UUID NOT NULL,
  permission_id UUID NOT NULL,
  PRIMARY KEY (role_id, permission_id)
);

CREATE INDEX IF NOT EXISTS idx_m_role_permission_permission_id ON m_role_permission (permission_id);
CREATE INDEX IF NOT EXISTS idx_m_role_permission_role_id ON m_role_permission (role_id);



DROP TABLE IF EXISTS m_role;

CREATE TABLE m_role (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) NOT NULL UNIQUE,
  description VARCHAR(500) NOT NULL,
  is_disabled BOOLEAN NOT NULL DEFAULT FALSE
);




DROP TABLE IF EXISTS m_savings_account_charge_paid_by;

CREATE TABLE m_savings_account_charge_paid_by (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_account_transaction_id UUID NOT NULL,
  savings_account_charge_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_savings_account_charge_paid_by_transaction_id ON m_savings_account_charge_paid_by (savings_account_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_charge_paid_by_charge_id ON m_savings_account_charge_paid_by (savings_account_charge_id);




DROP TABLE IF EXISTS m_savings_account_charge;

CREATE TABLE m_savings_account_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_account_id UUID NOT NULL,
  charge_id UUID NOT NULL,
  is_penalty BOOLEAN NOT NULL DEFAULT FALSE,
  charge_time_enum SMALLINT NOT NULL,
  charge_due_date DATE DEFAULT NULL,
  fee_on_month SMALLINT DEFAULT NULL,
  fee_on_day SMALLINT DEFAULT NULL,
  fee_interval SMALLINT DEFAULT NULL,
  free_withdrawal_count INTEGER DEFAULT 0,
  charge_reset_date DATE DEFAULT NULL,
  charge_calculation_enum SMALLINT NOT NULL,
  calculation_percentage DECIMAL(19,6) DEFAULT NULL,
  calculation_on_amount DECIMAL(19,6) DEFAULT NULL,
  amount DECIMAL(19,6) NOT NULL,
  amount_paid_derived DECIMAL(19,6) DEFAULT NULL,
  amount_waived_derived DECIMAL(19,6) DEFAULT NULL,
  amount_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  amount_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  is_paid_derived BOOLEAN NOT NULL DEFAULT FALSE,
  waived BOOLEAN NOT NULL DEFAULT FALSE,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  inactivated_on_date DATE DEFAULT NULL,
  created_by BIGINT NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_savings_account_charge_charge_id ON m_savings_account_charge (charge_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_charge_savings_account_id ON m_savings_account_charge (savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_charge_created_by ON m_savings_account_charge (created_by);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_charge_last_modified_by ON m_savings_account_charge (last_modified_by);




DROP TABLE IF EXISTS m_savings_account_interest_rate_chart;

CREATE TABLE m_savings_account_interest_rate_chart (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_account_id UUID NOT NULL,
  name VARCHAR(100) DEFAULT NULL,
  description VARCHAR(200) DEFAULT NULL,
  from_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  is_primary_grouping_by_amount BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_savings_account_interest_rate_chart_savings_account_id ON m_savings_account_interest_rate_chart (savings_account_id);



DROP TABLE IF EXISTS m_savings_account_interest_rate_slab;

CREATE TABLE m_savings_account_interest_rate_slab (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_account_interest_rate_chart_id UUID NOT NULL,
  description VARCHAR(200) DEFAULT NULL,
  period_type_enum SMALLINT DEFAULT NULL,
  from_period INTEGER DEFAULT NULL,
  to_period INTEGER DEFAULT NULL,
  amount_range_from DECIMAL(19,6) DEFAULT NULL,
  amount_range_to DECIMAL(19,6) DEFAULT NULL,
  annual_interest_rate DECIMAL(19,6) NOT NULL,
  currency_code VARCHAR(3) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_savings_account_interest_rate_slab_chart_id ON m_savings_account_interest_rate_slab (savings_account_interest_rate_chart_id);





DROP TABLE IF EXISTS m_savings_account;

CREATE TABLE m_savings_account (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_no VARCHAR(20) NOT NULL UNIQUE,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  client_id UUID DEFAULT NULL,
  group_id UUID DEFAULT NULL,
  gsim_id UUID DEFAULT NULL,
  product_id UUID DEFAULT NULL,
  field_officer_id UUID DEFAULT NULL,
  status_enum SMALLINT NOT NULL DEFAULT 300,
  sub_status_enum SMALLINT NOT NULL DEFAULT 0,
  account_type_enum SMALLINT NOT NULL DEFAULT 1,
  deposit_type_enum SMALLINT NOT NULL DEFAULT 100,
  submittedon_date DATE NOT NULL,
  submittedon_userid UUID DEFAULT NULL,
  approvedon_date DATE DEFAULT NULL,
  approvedon_userid UUID DEFAULT NULL,
  rejectedon_date DATE DEFAULT NULL,
  rejectedon_userid UUID DEFAULT NULL,
  withdrawnon_date DATE DEFAULT NULL,
  withdrawnon_userid UUID DEFAULT NULL,
  activatedon_date DATE DEFAULT NULL,
  activatedon_userid UUID DEFAULT NULL,
  closedon_date DATE DEFAULT NULL,
  closedon_userid UUID DEFAULT NULL,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  nominal_annual_interest_rate DECIMAL(19,6) NOT NULL,
  interest_compounding_period_enum SMALLINT NOT NULL,
  interest_posting_period_enum SMALLINT NOT NULL DEFAULT 4,
  interest_calculation_type_enum SMALLINT NOT NULL,
  interest_calculation_days_in_year_type_enum SMALLINT NOT NULL,
  min_required_opening_balance DECIMAL(19,6) DEFAULT NULL,
  lockin_period_frequency DECIMAL(19,6) DEFAULT NULL,
  lockin_period_frequency_enum SMALLINT DEFAULT NULL,
  withdrawal_fee_for_transfer BOOLEAN DEFAULT TRUE,
  allow_overdraft BOOLEAN NOT NULL DEFAULT FALSE,
  overdraft_limit DECIMAL(19,6) DEFAULT NULL,
  nominal_annual_interest_rate_overdraft DECIMAL(19,6) DEFAULT 0.000000,
  min_overdraft_for_interest_calculation DECIMAL(19,6) DEFAULT 0.000000,
  lockedin_until_date_derived DATE DEFAULT NULL,
  total_deposits_derived DECIMAL(19,6) DEFAULT NULL,
  total_withdrawals_derived DECIMAL(19,6) DEFAULT NULL,
  total_withdrawal_fees_derived DECIMAL(19,6) DEFAULT NULL,
  total_fees_charge_derived DECIMAL(19,6) DEFAULT NULL,
  total_penalty_charge_derived DECIMAL(19,6) DEFAULT NULL,
  total_annual_fees_derived DECIMAL(19,6) DEFAULT NULL,
  total_interest_earned_derived DECIMAL(19,6) DEFAULT NULL,
  total_interest_posted_derived DECIMAL(19,6) DEFAULT NULL,
  total_overdraft_interest_derived DECIMAL(19,6) DEFAULT 0.000000,
  total_withhold_tax_derived DECIMAL(19,6) DEFAULT NULL,
  account_balance_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  min_required_balance DECIMAL(19,6) DEFAULT NULL,
  enforce_min_required_balance BOOLEAN NOT NULL DEFAULT FALSE,
  min_balance_for_interest_calculation DECIMAL(19,6) DEFAULT NULL,
  start_interest_calculation_date DATE DEFAULT NULL,
  on_hold_funds_derived DECIMAL(19,6) DEFAULT NULL,
  version INTEGER NOT NULL DEFAULT 1,
  withhold_tax BOOLEAN NOT NULL DEFAULT FALSE,
  tax_group_id UUID DEFAULT NULL,
  last_interest_calculation_date DATE DEFAULT NULL,
  total_savings_amount_on_hold DECIMAL(19,6) DEFAULT NULL,
  interest_posted_till_date DATE DEFAULT NULL,
  reason_for_block VARCHAR(256) DEFAULT NULL,
  max_allowed_lien_limit DECIMAL(19,6) DEFAULT NULL,
  is_lien_transaction BOOLEAN NOT NULL DEFAULT FALSE,
  created_by UUID NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_savings_account_client_id ON m_savings_account (client_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_group_id ON m_savings_account (group_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_product_id ON m_savings_account (product_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_gsim_id ON m_savings_account (gsim_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_tax_group_id ON m_savings_account (tax_group_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_created_by ON m_savings_account (created_by);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_last_modified_by ON m_savings_account (last_modified_by);





DROP TABLE IF EXISTS m_savings_account_transaction;

CREATE TABLE m_savings_account_transaction (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_account_id UUID NOT NULL,
  office_id UUID NOT NULL,
  payment_detail_id UUID DEFAULT NULL,
  transaction_type_enum SMALLINT NOT NULL,
  is_reversed BOOLEAN NOT NULL,
  transaction_date DATE NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  overdraft_amount_derived DECIMAL(19,6) DEFAULT NULL,
  balance_end_date_derived DATE DEFAULT NULL,
  balance_number_of_days_derived INTEGER DEFAULT NULL,
  running_balance_derived DECIMAL(19,6) DEFAULT NULL,
  cumulative_balance_derived DECIMAL(19,6) DEFAULT NULL,
  created_date TIMESTAMP DEFAULT NULL,
  created_by UUID NOT NULL,
  is_manual BOOLEAN DEFAULT FALSE,
  release_id_of_hold_amount UUID DEFAULT NULL,
  is_loan_disbursement BOOLEAN DEFAULT NULL,
  ref_no VARCHAR(128) DEFAULT NULL,
  original_transaction_id UUID DEFAULT NULL,
  is_reversal BOOLEAN NOT NULL DEFAULT FALSE,
  reason_for_block VARCHAR(256) DEFAULT NULL,
  is_lien_transaction BOOLEAN NOT NULL DEFAULT FALSE,
  submitted_on_date DATE NOT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_savings_account_id ON m_savings_account_transaction (savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_office_id ON m_savings_account_transaction (office_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_payment_detail_id ON m_savings_account_transaction (payment_detail_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_created_by ON m_savings_account_transaction (created_by);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_last_modified_by ON m_savings_account_transaction (last_modified_by);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_submitted_on_date ON m_savings_account_transaction (submitted_on_date);




DROP TABLE IF EXISTS m_savings_account_transaction_tax_details;

CREATE TABLE m_savings_account_transaction_tax_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  savings_transaction_id UUID NOT NULL,
  tax_component_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_tax_details_savings_transaction_id ON m_savings_account_transaction_tax_details (savings_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_account_transaction_tax_details_tax_component_id ON m_savings_account_transaction_tax_details (tax_component_id);




DROP TABLE IF EXISTS m_savings_interest_incentives;

CREATE TABLE m_savings_interest_incentives (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  deposit_account_interest_rate_slab_id UUID NOT NULL,
  entiry_type SMALLINT NOT NULL,
  attribute_name SMALLINT NOT NULL,
  condition_type SMALLINT NOT NULL,
  attribute_value VARCHAR(50) NOT NULL,
  incentive_type SMALLINT NOT NULL,
  amount DECIMAL(19,6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_savings_interest_incentives_deposit_account_interest_rate_slab_id ON m_savings_interest_incentives (deposit_account_interest_rate_slab_id);




DROP TABLE IF EXISTS m_savings_officer_assignment_history;

CREATE TABLE m_savings_officer_assignment_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_id UUID NOT NULL,
  savings_officer_id UUID DEFAULT NULL,
  start_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  created_by UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  last_modified_by UUID NOT NULL,
  created_on_utc TIMESTAMP(6) NOT NULL,
  last_modified_on_utc TIMESTAMP(6) NOT NULL,
  CONSTRAINT fk_m_savings_officer_assignment_history_account_id FOREIGN KEY (account_id) REFERENCES m_savings_account (id),
  CONSTRAINT fk_m_savings_officer_assignment_history_savings_officer_id FOREIGN KEY (savings_officer_id) REFERENCES m_staff (id),
  CONSTRAINT fk_m_savings_officer_assignment_history_created_by FOREIGN KEY (created_by) REFERENCES m_appuser (id),
  CONSTRAINT fk_m_savings_officer_assignment_history_last_modified_by FOREIGN KEY (last_modified_by) REFERENCES m_appuser (id)
);

CREATE INDEX IF NOT EXISTS idx_m_savings_officer_assignment_history_account_id ON m_savings_officer_assignment_history (account_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_officer_assignment_history_savings_officer_id ON m_savings_officer_assignment_history (savings_officer_id);
CREATE INDEX IF NOT EXISTS idx_m_savings_officer_assignment_history_created_by ON m_savings_officer_assignment_history (created_by);
CREATE INDEX IF NOT EXISTS idx_m_savings_officer_assignment_history_last_modified_by ON m_savings_officer_assignment_history (last_modified_by);



DROP TABLE IF EXISTS m_savings_product_charge;

CREATE TABLE m_savings_product_charge (
  savings_product_id UUID NOT NULL,
  charge_id UUID NOT NULL,
  PRIMARY KEY (savings_product_id, charge_id)
);

CREATE INDEX IF NOT EXISTS idx_m_savings_product_charge_charge_id ON m_savings_product_charge (charge_id);




DROP TABLE IF EXISTS m_savings_product;

CREATE TABLE m_savings_product (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) NOT NULL UNIQUE,
  short_name VARCHAR(4) NOT NULL UNIQUE,
  description VARCHAR(500) DEFAULT NULL,
  deposit_type_enum SMALLINT NOT NULL DEFAULT 100,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  nominal_annual_interest_rate DECIMAL(19,6) NOT NULL,
  interest_compounding_period_enum SMALLINT NOT NULL,
  interest_posting_period_enum SMALLINT NOT NULL DEFAULT 4,
  interest_calculation_type_enum SMALLINT NOT NULL,
  interest_calculation_days_in_year_type_enum SMALLINT NOT NULL,
  min_required_opening_balance DECIMAL(19,6) DEFAULT NULL,
  lockin_period_frequency DECIMAL(19,6) DEFAULT NULL,
  lockin_period_frequency_enum SMALLINT DEFAULT NULL,
  accounting_type SMALLINT NOT NULL,
  withdrawal_fee_amount DECIMAL(19,6) DEFAULT NULL,
  withdrawal_fee_type_enum SMALLINT DEFAULT NULL,
  withdrawal_fee_for_transfer BOOLEAN DEFAULT TRUE,
  allow_overdraft BOOLEAN NOT NULL DEFAULT FALSE,
  overdraft_limit DECIMAL(19,6) DEFAULT NULL,
  nominal_annual_interest_rate_overdraft DECIMAL(19,6) DEFAULT 0.000000,
  min_overdraft_for_interest_calculation DECIMAL(19,6) DEFAULT 0.000000,
  min_required_balance DECIMAL(19,6) DEFAULT NULL,
  enforce_min_required_balance BOOLEAN NOT NULL DEFAULT FALSE,
  min_balance_for_interest_calculation DECIMAL(19,6) DEFAULT NULL,
  withhold_tax BOOLEAN NOT NULL DEFAULT FALSE,
  tax_group_id UUID DEFAULT NULL,
  is_dormancy_tracking_active BOOLEAN DEFAULT NULL,
  days_to_inactive INTEGER DEFAULT NULL,
  days_to_dormancy INTEGER DEFAULT NULL,
  days_to_escheat INTEGER DEFAULT NULL,
  max_allowed_lien_limit DECIMAL(19,6) DEFAULT NULL,
  is_lien_allowed BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_m_savings_product_tax_group_id ON m_savings_product (tax_group_id);



DROP TABLE IF EXISTS m_selfservice_beneficiaries_tpt;

CREATE TABLE m_selfservice_beneficiaries_tpt (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  app_user_id UUID NOT NULL,
  name VARCHAR(50) NOT NULL,
  office_id UUID NOT NULL,
  client_id UUID NOT NULL,
  account_id UUID NOT NULL,
  account_type SMALLINT NOT NULL,
  transfer_limit BIGINT DEFAULT 0,
  is_active BOOLEAN NOT NULL DEFAULT FALSE,
  UNIQUE (name, app_user_id, is_active)
);




DROP TABLE IF EXISTS m_selfservice_user_client_mapping;

CREATE TABLE m_selfservice_user_client_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  appuser_id UUID NOT NULL,
  client_id UUID NOT NULL,
  UNIQUE (appuser_id, client_id),
  UNIQUE (client_id)
);


DROP TABLE IF EXISTS m_share_account_charge_paid_by;

CREATE TABLE m_share_account_charge_paid_by (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  share_transaction_id UUID DEFAULT NULL,
  charge_transaction_id UUID DEFAULT NULL,
  amount DECIMAL(20,2) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_share_account_charge_paid_by_share_transaction_id ON m_share_account_charge_paid_by (share_transaction_id);
CREATE INDEX IF NOT EXISTS idx_m_share_account_charge_paid_by_charge_transaction_id ON m_share_account_charge_paid_by (charge_transaction_id);





DROP TABLE IF EXISTS m_share_account_charge;

CREATE TABLE m_share_account_charge (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_id UUID NOT NULL,
  charge_id UUID NOT NULL,
  charge_time_enum SMALLINT NOT NULL,
  charge_calculation_enum SMALLINT NOT NULL,
  charge_payment_mode_enum SMALLINT NOT NULL DEFAULT 0,
  calculation_percentage DECIMAL(19,6) DEFAULT NULL,
  calculation_on_amount DECIMAL(19,6) DEFAULT NULL,
  charge_amount_or_percentage DECIMAL(19,6) DEFAULT NULL,
  amount DECIMAL(19,6) NOT NULL,
  amount_paid_derived DECIMAL(19,6) DEFAULT NULL,
  amount_waived_derived DECIMAL(19,6) DEFAULT NULL,
  amount_writtenoff_derived DECIMAL(19,6) DEFAULT NULL,
  amount_outstanding_derived DECIMAL(19,6) NOT NULL DEFAULT 0.000000,
  is_paid_derived BOOLEAN NOT NULL DEFAULT FALSE,
  waived BOOLEAN NOT NULL DEFAULT FALSE,
  min_cap DECIMAL(19,6) DEFAULT NULL,
  max_cap DECIMAL(19,6) DEFAULT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE
);

CREATE INDEX IF NOT EXISTS idx_m_share_account_charge_charge_id ON m_share_account_charge (charge_id);
CREATE INDEX IF NOT EXISTS idx_m_share_account_charge_account_id ON m_share_account_charge (account_id);




DROP TABLE IF EXISTS m_share_account_dividend_details;

CREATE TABLE m_share_account_dividend_details (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  dividend_pay_out_id UUID NOT NULL,
  account_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  status SMALLINT NOT NULL,
  savings_transaction_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_share_account_dividend_details_account_id ON m_share_account_dividend_details (account_id);
CREATE INDEX IF NOT EXISTS idx_m_share_account_dividend_details_dividend_pay_out_id ON m_share_account_dividend_details (dividend_pay_out_id);



DROP TABLE IF EXISTS m_share_account;

CREATE TABLE m_share_account (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_no VARCHAR(50) NOT NULL,
  product_id UUID NOT NULL,
  client_id UUID NOT NULL,
  external_id VARCHAR(100) DEFAULT NULL,
  status_enum SMALLINT NOT NULL DEFAULT 300,
  total_approved_shares UUID DEFAULT NULL,
  total_pending_shares UUID DEFAULT NULL,
  submitted_date DATE NOT NULL,
  submitted_userid UUID DEFAULT NULL,
  approved_date DATE DEFAULT NULL,
  approved_userid UUID DEFAULT NULL,
  rejected_date DATE DEFAULT NULL,
  rejected_userid UUID DEFAULT NULL,
  activated_date DATE DEFAULT NULL,
  activated_userid UUID DEFAULT NULL,
  closed_date DATE DEFAULT NULL,
  closed_userid UUID DEFAULT NULL,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  savings_account_id UUID NOT NULL,
  minimum_active_period_frequency DECIMAL(19,6) DEFAULT NULL,
  minimum_active_period_frequency_enum SMALLINT DEFAULT NULL,
  lockin_period_frequency DECIMAL(19,6) DEFAULT NULL,
  lockin_period_frequency_enum SMALLINT DEFAULT NULL,
  allow_dividends_inactive_clients BOOLEAN DEFAULT FALSE,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_share_account_product_id ON m_share_account (product_id);
CREATE INDEX IF NOT EXISTS idx_m_share_account_savings_account_id ON m_share_account (savings_account_id);
CREATE INDEX IF NOT EXISTS idx_m_share_account_submitted_userid ON m_share_account (submitted_userid);
CREATE INDEX IF NOT EXISTS idx_m_share_account_approved_userid ON m_share_account (approved_userid);
CREATE INDEX IF NOT EXISTS idx_m_share_account_rejected_userid ON m_share_account (rejected_userid);
CREATE INDEX IF NOT EXISTS idx_m_share_account_activated_userid ON m_share_account (activated_userid);
CREATE INDEX IF NOT EXISTS idx_m_share_account_closed_userid ON m_share_account (closed_userid);
CREATE INDEX IF NOT EXISTS idx_m_share_account_lastmodifiedby_id ON m_share_account (lastmodifiedby_id);
CREATE INDEX IF NOT EXISTS idx_m_share_account_client_id ON m_share_account (client_id);



DROP TABLE IF EXISTS m_share_account_transactions;

CREATE TABLE m_share_account_transactions (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  account_id UUID NOT NULL,
  transaction_date DATE DEFAULT NULL,
  total_shares UUID DEFAULT NULL,
  unit_price DECIMAL(10,2) DEFAULT NULL,
  amount DECIMAL(20,2) DEFAULT NULL,
  charge_amount DECIMAL(20,2) DEFAULT NULL,
  amount_paid DECIMAL(20,2) DEFAULT NULL,
  status_enum SMALLINT NOT NULL DEFAULT 300,
  type_enum SMALLINT DEFAULT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE
);

CREATE INDEX IF NOT EXISTS idx_m_share_account_transactions_account_id ON m_share_account_transactions (account_id);




DROP TABLE IF EXISTS m_share_product_charge;

CREATE TABLE m_share_product_charge (
  product_id UUID NOT NULL,
  charge_id UUID NOT NULL,
  PRIMARY KEY (product_id, charge_id)
);

CREATE INDEX IF NOT EXISTS idx_m_share_product_charge_charge_id ON m_share_product_charge (charge_id);




DROP TABLE IF EXISTS m_share_product_dividend_pay_out;

CREATE TABLE m_share_product_dividend_pay_out (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  product_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  dividend_period_start_date DATE NOT NULL,
  dividend_period_end_date DATE NOT NULL,
  status SMALLINT NOT NULL,
  createdby_id UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_share_product_dividend_pay_out_createdby_id ON m_share_product_dividend_pay_out (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_share_product_dividend_pay_out_lastmodifiedby_id ON m_share_product_dividend_pay_out (lastmodifiedby_id);
CREATE INDEX IF NOT EXISTS idx_m_share_product_dividend_pay_out_product_id ON m_share_product_dividend_pay_out (product_id);



DROP TABLE IF EXISTS m_share_product_market_price;

CREATE TABLE m_share_product_market_price (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  product_id UUID NOT NULL,
  from_date DATE DEFAULT NULL,
  share_value DECIMAL(10,2) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_share_product_market_price_product_id ON m_share_product_market_price (product_id);





CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

DROP TABLE IF EXISTS m_share_product;

CREATE TABLE m_share_product (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(200) NOT NULL UNIQUE,
  short_name VARCHAR(4) NOT NULL,
  external_id VARCHAR(100) DEFAULT NULL,
  description VARCHAR(500) NOT NULL,
  start_date DATE DEFAULT NULL,
  end_date DATE DEFAULT NULL,
  currency_code VARCHAR(3) NOT NULL,
  currency_digits SMALLINT NOT NULL,
  currency_multiplesof SMALLINT DEFAULT NULL,
  total_shares BIGINT NOT NULL,
  issued_shares BIGINT DEFAULT NULL,
  totalsubscribed_shares BIGINT DEFAULT NULL,
  unit_price DECIMAL(10,2) NOT NULL,
  capital_amount DECIMAL(20,2) NOT NULL,
  minimum_client_shares BIGINT DEFAULT NULL,
  nominal_client_shares BIGINT NOT NULL,
  maximum_client_shares BIGINT DEFAULT NULL,
  minimum_active_period_frequency DECIMAL(19,6) DEFAULT NULL,
  minimum_active_period_frequency_enum SMALLINT DEFAULT NULL,
  lockin_period_frequency DECIMAL(19,6) DEFAULT NULL,
  lockin_period_frequency_enum SMALLINT DEFAULT NULL,
  allow_dividends_inactive_clients BOOLEAN DEFAULT FALSE,
  createdby_id UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  accounting_type SMALLINT NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_share_product_createdby_id ON m_share_product (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_share_product_lastmodifiedby_id ON m_share_product (lastmodifiedby_id);




DROP TABLE IF EXISTS m_staff_assignment_history;

CREATE TABLE m_staff_assignment_history (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  centre_id UUID DEFAULT NULL,
  staff_id UUID NOT NULL,
  start_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  createdby_id UUID DEFAULT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_staff_assignment_history_centre_id ON m_staff_assignment_history (centre_id);
CREATE INDEX IF NOT EXISTS idx_m_staff_assignment_history_staff_id ON m_staff_assignment_history (staff_id);
CREATE INDEX IF NOT EXISTS idx_m_staff_assignment_history_created_by ON m_staff_assignment_history (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_staff_assignment_history_last_modified_by ON m_staff_assignment_history (lastmodifiedby_id);



DROP TABLE IF EXISTS m_staff;

CREATE TABLE m_staff (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  is_loan_officer BOOLEAN NOT NULL DEFAULT FALSE,
  office_id UUID DEFAULT NULL,
  firstname VARCHAR(50) DEFAULT NULL,
  lastname VARCHAR(50) DEFAULT NULL,
  display_name VARCHAR(102) NOT NULL UNIQUE,
  mobile_no VARCHAR(50) DEFAULT NULL UNIQUE,
  external_id VARCHAR(100) DEFAULT NULL UNIQUE,
  organisational_role_enum SMALLINT DEFAULT NULL,
  organisational_role_parent_staff_id UUID DEFAULT NULL,
  is_active BOOLEAN NOT NULL DEFAULT TRUE,
  joining_date DATE DEFAULT NULL,
  image_id UUID DEFAULT NULL,
  email_address VARCHAR(150) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_staff_image_id ON m_staff (image_id);
CREATE INDEX IF NOT EXISTS idx_m_staff_office_id ON m_staff (office_id);


DROP TABLE IF EXISTS m_survey_components;

CREATE TABLE m_survey_components (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  survey_id UUID NOT NULL,
  a_key VARCHAR(32) NOT NULL,
  a_text VARCHAR(255) NOT NULL,
  description VARCHAR(4000) DEFAULT NULL,
  sequence_no INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_survey_components_survey_id ON m_survey_components (survey_id);



DROP TABLE IF EXISTS m_survey_lookup_tables;

CREATE TABLE m_survey_lookup_tables (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  survey_id UUID NOT NULL,
  a_key VARCHAR(255) NOT NULL,
  description INTEGER DEFAULT NULL,
  value_from INTEGER NOT NULL,
  value_to INTEGER NOT NULL,
  score DECIMAL(5,2) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_survey_lookup_tables_survey_id ON m_survey_lookup_tables (survey_id);



DROP TABLE IF EXISTS m_survey_questions;

CREATE TABLE m_survey_questions (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  survey_id UUID NOT NULL,
  component_key VARCHAR(32) DEFAULT NULL,
  a_key VARCHAR(32) NOT NULL,
  a_text VARCHAR(255) NOT NULL,
  description VARCHAR(4000) DEFAULT NULL,
  sequence_no INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_survey_questions_survey_id ON m_survey_questions (survey_id);



DROP TABLE IF EXISTS m_survey_responses;

CREATE TABLE m_survey_responses (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  question_id UUID NOT NULL,
  a_text VARCHAR(255) NOT NULL,
  a_value INTEGER NOT NULL,
  sequence_no INTEGER NOT NULL,
  CONSTRAINT fk_m_survey_responses_question_id FOREIGN KEY (question_id) REFERENCES m_survey_questions (id)
);

CREATE INDEX IF NOT EXISTS idx_m_survey_responses_question_id ON m_survey_responses (question_id);






DROP TABLE IF EXISTS m_survey_scorecards;

CREATE TABLE m_survey_scorecards (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  survey_id UUID NOT NULL,
  question_id UUID NOT NULL,
  response_id UUID NOT NULL,
  user_id UUID NOT NULL,
  client_id UUID NOT NULL,
  created_on TIMESTAMP(6) DEFAULT NULL,
  a_value INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_survey_scorecards_client_id ON m_survey_scorecards (client_id);
CREATE INDEX IF NOT EXISTS idx_m_survey_scorecards_question_id ON m_survey_scorecards (question_id);
CREATE INDEX IF NOT EXISTS idx_m_survey_scorecards_response_id ON m_survey_scorecards (response_id);
CREATE INDEX IF NOT EXISTS idx_m_survey_scorecards_survey_id ON m_survey_scorecards (survey_id);
CREATE INDEX IF NOT EXISTS idx_m_survey_scorecards_user_id ON m_survey_scorecards (user_id);



DROP TABLE IF EXISTS m_surveys;

CREATE TABLE m_surveys (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  a_key VARCHAR(32) NOT NULL,
  a_name VARCHAR(255) NOT NULL,
  description VARCHAR(4000) DEFAULT NULL,
  country_code VARCHAR(2) NOT NULL,
  valid_from DATE DEFAULT NULL,
  valid_to DATE DEFAULT NULL
);



DROP TABLE IF EXISTS m_tax_component;

CREATE TABLE m_tax_component (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(50) NOT NULL,
  percentage DECIMAL(19,6) NOT NULL,
  debit_account_type_enum SMALLINT DEFAULT NULL,
  debit_account_id UUID DEFAULT NULL,
  credit_account_type_enum SMALLINT DEFAULT NULL,
  credit_account_id UUID DEFAULT NULL,
  start_date DATE NOT NULL,
  createdby_id UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_tax_component_createdby ON m_tax_component (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_tax_component_credit_account_id ON m_tax_component (credit_account_id);
CREATE INDEX IF NOT EXISTS idx_m_tax_component_debit_account_id ON m_tax_component (debit_account_id);
CREATE INDEX IF NOT EXISTS idx_m_tax_component_lastmodifiedby ON m_tax_component (lastmodifiedby_id);




DROP TABLE IF EXISTS m_tax_group_mappings;

CREATE TABLE m_tax_group_mappings (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  tax_group_id UUID NOT NULL,
  tax_component_id UUID NOT NULL,
  start_date DATE NOT NULL,
  end_date DATE DEFAULT NULL,
  createdby_id UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_tax_group_mappings_createdby_id ON m_tax_group_mappings (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_tax_group_mappings_lastmodifiedby_id ON m_tax_group_mappings (lastmodifiedby_id);
CREATE INDEX IF NOT EXISTS idx_m_tax_group_mappings_tax_component_id ON m_tax_group_mappings (tax_component_id);
CREATE INDEX IF NOT EXISTS idx_m_tax_group_mappings_tax_group_id ON m_tax_group_mappings (tax_group_id);



DROP TABLE IF EXISTS m_tax_group;

CREATE TABLE m_tax_group (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(50) NOT NULL,
  createdby_id UUID NOT NULL,
  created_date TIMESTAMP(6) DEFAULT NULL,
  lastmodifiedby_id UUID NOT NULL,
  lastmodified_date TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_tax_group_createdby_id ON m_tax_group (createdby_id);
CREATE INDEX IF NOT EXISTS idx_m_tax_group_lastmodifiedby_id ON m_tax_group (lastmodifiedby_id);



DROP TABLE IF EXISTS m_tellers;

CREATE TABLE m_tellers (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  office_id UUID NOT NULL,
  debit_account_id UUID DEFAULT NULL,
  credit_account_id UUID DEFAULT NULL,
  name VARCHAR(50) NOT NULL UNIQUE,
  description VARCHAR(100) DEFAULT NULL,
  valid_from DATE DEFAULT NULL,
  valid_to DATE DEFAULT NULL,
  state SMALLINT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_tellers_credit_account_id ON m_tellers (credit_account_id);
CREATE INDEX IF NOT EXISTS idx_m_tellers_debit_account_id ON m_tellers (debit_account_id);
CREATE INDEX IF NOT EXISTS idx_m_tellers_office_id ON m_tellers (office_id);



DROP TABLE IF EXISTS m_template_m_templatemappers;

CREATE TABLE m_template_m_templatemappers (
  m_template_id UUID NOT NULL,
  mappers_id UUID NOT NULL UNIQUE
);

CREATE INDEX IF NOT EXISTS idx_m_template_m_templatemappers_template_id ON m_template_m_templatemappers (m_template_id);



DROP TABLE IF EXISTS m_template;

CREATE TABLE m_template (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(255) NOT NULL UNIQUE,
  text TEXT NOT NULL,
  entity INTEGER DEFAULT NULL,
  type INTEGER DEFAULT NULL
);



DROP TABLE IF EXISTS m_templatemappers;

CREATE TABLE m_templatemappers (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  mapperkey VARCHAR(255) DEFAULT NULL,
  mapperorder INTEGER DEFAULT NULL,
  mappervalue VARCHAR(255) DEFAULT NULL
);




DROP TABLE IF EXISTS m_trial_balance;

CREATE TABLE m_trial_balance (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  office_id UUID NOT NULL,
  account_id UUID NOT NULL,
  amount DECIMAL(19,6) NOT NULL,
  entry_date DATE NOT NULL,
  created_date DATE DEFAULT NULL,
  closing_balance DECIMAL(19,6) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_m_trial_balance_office_id ON m_trial_balance (office_id);
CREATE INDEX IF NOT EXISTS idx_m_trial_balance_account_id ON m_trial_balance (account_id);



DROP TABLE IF EXISTS m_working_days;

CREATE TABLE m_working_days (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  recurrence VARCHAR(100) DEFAULT NULL,
  repayment_rescheduling_enum SMALLINT DEFAULT NULL,
  extend_term_daily_repayments BOOLEAN DEFAULT FALSE,
  extend_term_holiday_repayment BOOLEAN NOT NULL DEFAULT FALSE
);



DROP TABLE IF EXISTS mix_taxonomy_mapping;

CREATE TABLE mix_taxonomy_mapping (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  identifier VARCHAR(50) NOT NULL DEFAULT '',
  config VARCHAR(200) DEFAULT NULL,
  last_update_date TIMESTAMP(6) DEFAULT NULL,
  currency VARCHAR(11) DEFAULT NULL
);


DROP TABLE IF EXISTS mix_taxonomy;

CREATE TABLE mix_taxonomy (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(100) DEFAULT NULL,
  namespace_id INTEGER DEFAULT NULL,
  dimension VARCHAR(100) DEFAULT NULL,
  type INTEGER DEFAULT NULL,
  description VARCHAR(1000) DEFAULT NULL,
  need_mapping BOOLEAN DEFAULT NULL
);



DROP TABLE IF EXISTS mix_xbrl_namespace;

CREATE TABLE mix_xbrl_namespace (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  prefix VARCHAR(20) NOT NULL DEFAULT '',
  url VARCHAR(100) DEFAULT NULL,
  UNIQUE (prefix)
);


DROP TABLE IF EXISTS notification_generator;

CREATE TABLE notification_generator (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  object_type TEXT DEFAULT NULL,
  object_identifier UUID DEFAULT NULL,
  action TEXT DEFAULT NULL,
  actor UUID DEFAULT NULL,
  is_system_generated BOOLEAN DEFAULT FALSE,
  notification_content TEXT DEFAULT NULL,
  created_at TIMESTAMP(6) DEFAULT NULL
);



DROP TABLE IF EXISTS notification_mapper;

CREATE TABLE notification_mapper (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  notification_id UUID DEFAULT NULL,
  user_id UUID DEFAULT NULL,
  is_read BOOLEAN DEFAULT FALSE,
  created_at TIMESTAMP(6) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_notification_mapper_notification_id ON notification_mapper (notification_id);
CREATE INDEX IF NOT EXISTS idx_notification_mapper_user_id ON notification_mapper (user_id);




DROP TABLE IF EXISTS oauth_access_token;

CREATE TABLE oauth_access_token (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  token_id VARCHAR(256) DEFAULT NULL,
  token BYTEA DEFAULT NULL,
  authentication_id VARCHAR(256) DEFAULT NULL,
  user_name VARCHAR(256) DEFAULT NULL,
  client_id VARCHAR(256) DEFAULT NULL,
  authentication BYTEA DEFAULT NULL,
  refresh_token VARCHAR(256) DEFAULT NULL
);



DROP TABLE IF EXISTS oauth_client_details;

CREATE TABLE oauth_client_details (
  client_id VARCHAR(128) NOT NULL PRIMARY KEY,
  resource_ids VARCHAR(256) DEFAULT NULL,
  client_secret VARCHAR(256) DEFAULT NULL,
  scope VARCHAR(256) DEFAULT NULL,
  authorized_grant_types VARCHAR(256) DEFAULT NULL,
  web_server_redirect_uri VARCHAR(256) DEFAULT NULL,
  authorities VARCHAR(256) DEFAULT NULL,
  access_token_validity INTEGER DEFAULT NULL,
  refresh_token_validity INTEGER DEFAULT NULL,
  additional_information VARCHAR(4096) DEFAULT NULL,
  autoapprove BOOLEAN DEFAULT FALSE
);


DROP TABLE IF EXISTS oauth_refresh_token;

CREATE TABLE oauth_refresh_token (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  token_id VARCHAR(256) DEFAULT NULL,
  token BYTEA DEFAULT NULL,
  authentication BYTEA DEFAULT NULL
);


DROP TABLE IF EXISTS ppi_likelihoods;

CREATE TABLE ppi_likelihoods (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  code VARCHAR(100) NOT NULL,
  name VARCHAR(250) NOT NULL
);



DROP TABLE IF EXISTS ppi_likelihoods_ppi;

CREATE TABLE ppi_likelihoods_ppi (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  likelihood_id UUID NOT NULL,
  ppi_name VARCHAR(250) NOT NULL,
  enabled INTEGER NOT NULL DEFAULT 100
);



DROP TABLE IF EXISTS ppi_scores;

CREATE TABLE ppi_scores (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  score_from INTEGER NOT NULL,
  score_to INTEGER NOT NULL
);


DROP TABLE IF EXISTS r_enum_value;

CREATE TABLE r_enum_value (
  enum_name VARCHAR(100) NOT NULL,
  enum_id INTEGER NOT NULL,
  enum_message_property VARCHAR(100) NOT NULL,
  enum_value VARCHAR(100) NOT NULL,
  enum_type SMALLINT NOT NULL,
  PRIMARY KEY (enum_name, enum_id),
  UNIQUE (enum_name, enum_message_property),
  UNIQUE (enum_name, enum_value)
);



DROP TABLE IF EXISTS ref_loan_transaction_processing_strategy;

CREATE TABLE ref_loan_transaction_processing_strategy (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  code VARCHAR(100) DEFAULT NULL UNIQUE,
  name VARCHAR(255) DEFAULT NULL,
  sort_order INTEGER DEFAULT NULL
);



DROP TABLE IF EXISTS request_audit_table;

CREATE TABLE request_audit_table (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  lastname VARCHAR(100) NOT NULL,
  username VARCHAR(100) NOT NULL,
  mobile_number VARCHAR(50) DEFAULT NULL,
  firstname VARCHAR(100) NOT NULL,
  authentication_token VARCHAR(100) DEFAULT NULL,
  password VARCHAR(250) NOT NULL,
  email VARCHAR(100) NOT NULL,
  client_id UUID NOT NULL,
  created_date DATE NOT NULL,
  account_number VARCHAR(100) NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_request_audit_table_client_id ON request_audit_table (client_id);



DROP TABLE IF EXISTS rpt_sequence;

CREATE TABLE rpt_sequence (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4()
);



DROP TABLE IF EXISTS scheduled_email_campaign;

CREATE TABLE scheduled_email_campaign (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  campaign_name VARCHAR(100) NOT NULL,
  campaign_type UUID NOT NULL,
  business_rule_id UUID DEFAULT NULL,
  param_value TEXT DEFAULT NULL,
  status_enum INTEGER NOT NULL,
  email_subject VARCHAR(100) NOT NULL,
  email_message TEXT NOT NULL,
  email_attachment_file_format VARCHAR(10) DEFAULT NULL,
  stretchy_report_id UUID DEFAULT NULL,
  stretchy_report_param_map TEXT DEFAULT NULL,
  closedon_date DATE DEFAULT NULL,
  closedon_userid UUID DEFAULT NULL,
  submittedon_date DATE DEFAULT NULL,
  submittedon_userid UUID DEFAULT NULL,
  approvedon_date DATE DEFAULT NULL,
  approvedon_userid UUID DEFAULT NULL,
  recurrence VARCHAR(100) DEFAULT NULL,
  next_trigger_date TIMESTAMP(6) DEFAULT NULL,
  last_trigger_date TIMESTAMP(6) DEFAULT NULL,
  recurrence_start_date TIMESTAMP(6) DEFAULT NULL,
  is_visible BOOLEAN DEFAULT TRUE,
  previous_run_error_log TEXT DEFAULT NULL,
  previous_run_error_message TEXT DEFAULT NULL,
  previous_run_status VARCHAR(10) DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_scheduled_email_campaign_stretchy_report_id ON scheduled_email_campaign (stretchy_report_id);



DROP TABLE IF EXISTS scheduled_email_configuration;

CREATE TABLE scheduled_email_configuration (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  name VARCHAR(50) NOT NULL UNIQUE,
  value VARCHAR(200) DEFAULT NULL
);





DROP TABLE IF EXISTS scheduled_email_messages_outbound;

CREATE TABLE scheduled_email_messages_outbound (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  group_id UUID DEFAULT NULL,
  client_id UUID DEFAULT NULL,
  staff_id UUID DEFAULT NULL,
  email_campaign_id UUID DEFAULT NULL,
  status_enum INTEGER NOT NULL DEFAULT 100,
  email_address VARCHAR(50) NOT NULL,
  email_subject VARCHAR(50) NOT NULL,
  message TEXT NOT NULL,
  campaign_name VARCHAR(200) DEFAULT NULL,
  submittedon_date DATE DEFAULT NULL,
  error_message TEXT DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_scheduled_email_messages_outbound_client_id ON scheduled_email_messages_outbound (client_id);
CREATE INDEX IF NOT EXISTS idx_scheduled_email_messages_outbound_group_id ON scheduled_email_messages_outbound (group_id);
CREATE INDEX IF NOT EXISTS idx_scheduled_email_messages_outbound_staff_id ON scheduled_email_messages_outbound (staff_id);
CREATE INDEX IF NOT EXISTS idx_scheduled_email_messages_outbound_email_campaign_id ON scheduled_email_messages_outbound (email_campaign_id);


DROP TABLE IF EXISTS scheduler_detail;

CREATE TABLE scheduler_detail (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  is_suspended BOOLEAN NOT NULL DEFAULT FALSE,
  execute_misfired_jobs BOOLEAN NOT NULL DEFAULT TRUE,
  reset_scheduler_on_bootup BOOLEAN NOT NULL DEFAULT TRUE
);



DROP TABLE IF EXISTS sms_campaign;

CREATE TABLE sms_campaign (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  campaign_name VARCHAR(100) NOT NULL,
  campaign_type INTEGER NOT NULL,
  campaign_trigger_type INTEGER NOT NULL,
  report_id UUID NOT NULL,
  provider_id UUID DEFAULT NULL,
  param_value TEXT DEFAULT NULL,
  status_enum INTEGER NOT NULL,
  message TEXT NOT NULL,
  submittedon_date DATE DEFAULT NULL,
  submittedon_userid UUID DEFAULT NULL,
  approvedon_date DATE DEFAULT NULL,
  approvedon_userid UUID DEFAULT NULL,
  closedon_date DATE DEFAULT NULL,
  closedon_userid UUID DEFAULT NULL,
  recurrence VARCHAR(100) DEFAULT NULL,
  next_trigger_date TIMESTAMP(6) DEFAULT NULL,
  last_trigger_date TIMESTAMP(6) DEFAULT NULL,
  recurrence_start_date TIMESTAMP(6) DEFAULT NULL,
  is_visible BOOLEAN DEFAULT TRUE,
  is_notification BOOLEAN DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_sms_campaign_report_id ON sms_campaign (report_id);




DROP TABLE IF EXISTS sms_messages_outbound;

CREATE TABLE sms_messages_outbound (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  group_id UUID DEFAULT NULL,
  client_id UUID DEFAULT NULL,
  staff_id UUID DEFAULT NULL,
  status_enum INTEGER NOT NULL DEFAULT 100,
  mobile_no VARCHAR(50) DEFAULT NULL,
  message VARCHAR(1000) NOT NULL,
  campaign_id UUID DEFAULT NULL,
  external_id VARCHAR(100) DEFAULT NULL,
  submittedon_date DATE DEFAULT NULL,
  delivered_on_date TIMESTAMP(6) DEFAULT NULL,
  is_notification BOOLEAN NOT NULL DEFAULT FALSE
);

CREATE INDEX IF NOT EXISTS idx_sms_messages_outbound_campaign_id ON sms_messages_outbound (campaign_id);
CREATE INDEX IF NOT EXISTS idx_sms_messages_outbound_client_id ON sms_messages_outbound (client_id);
CREATE INDEX IF NOT EXISTS idx_sms_messages_outbound_group_id ON sms_messages_outbound (group_id);
CREATE INDEX IF NOT EXISTS idx_sms_messages_outbound_staff_id ON sms_messages_outbound (staff_id);


DROP TABLE IF EXISTS stretchy_parameter;

CREATE TABLE stretchy_parameter (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  parameter_name VARCHAR(45) NOT NULL UNIQUE,
  parameter_variable VARCHAR(45) DEFAULT NULL,
  parameter_label VARCHAR(45) NOT NULL,
  parameter_displayType VARCHAR(45) NOT NULL,
  parameter_FormatType VARCHAR(10) NOT NULL,
  parameter_default VARCHAR(45) NOT NULL,
  special VARCHAR(1) DEFAULT NULL,
  selectOne VARCHAR(1) DEFAULT NULL,
  selectAll VARCHAR(1) DEFAULT NULL,
  parameter_sql TEXT DEFAULT NULL,
  parent_id UUID DEFAULT NULL
);

CREATE INDEX IF NOT EXISTS idx_stretchy_parameter_parent_id ON stretchy_parameter (parent_id);



DROP TABLE IF EXISTS stretchy_report_parameter;

CREATE TABLE stretchy_report_parameter (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  report_id UUID NOT NULL,
  parameter_id UUID NOT NULL,
  report_parameter_name VARCHAR(45) DEFAULT NULL,
  UNIQUE (report_id, parameter_id)
);

CREATE INDEX IF NOT EXISTS idx_stretchy_report_parameter_report_id ON stretchy_report_parameter (report_id);
CREATE INDEX IF NOT EXISTS idx_stretchy_report_parameter_parameter_id ON stretchy_report_parameter (parameter_id);


DROP TABLE IF EXISTS stretchy_report;

CREATE TABLE stretchy_report (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  report_name VARCHAR(100) NOT NULL UNIQUE,
  report_type VARCHAR(20) NOT NULL,
  report_subtype VARCHAR(20) DEFAULT NULL,
  report_category VARCHAR(45) DEFAULT NULL,
  report_sql TEXT DEFAULT NULL,
  description TEXT DEFAULT NULL,
  core_report BOOLEAN DEFAULT FALSE,
  use_report BOOLEAN DEFAULT FALSE,
  self_service_user_report BOOLEAN NOT NULL DEFAULT FALSE
);



DROP TABLE IF EXISTS twofactor_access_token;

CREATE TABLE twofactor_access_token (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  token VARCHAR(32) NOT NULL,
  appuser_id UUID NOT NULL,
  valid_from TIMESTAMP(6) DEFAULT NULL,
  valid_to TIMESTAMP(6) DEFAULT NULL,
  enabled BOOLEAN NOT NULL,
  UNIQUE (token, appuser_id)
);

CREATE INDEX IF NOT EXISTS idx_twofactor_access_token_token ON twofactor_access_token (token);
CREATE INDEX IF NOT EXISTS idx_twofactor_access_token_appuser_id ON twofactor_access_token (appuser_id);


DROP TABLE IF EXISTS twofactor_configuration;

CREATE TABLE twofactor_configuration (
  id UUID PRIMARY KEY,
  name VARCHAR(40) NOT NULL UNIQUE,
  value VARCHAR(1024) DEFAULT NULL
);



DROP TABLE IF EXISTS x_registered_table;

CREATE TABLE x_registered_table (
  registered_table_name VARCHAR(50) NOT NULL PRIMARY KEY,
  application_table_name VARCHAR(50) NOT NULL,
  entity_subtype VARCHAR(50) DEFAULT NULL,
  category INTEGER NOT NULL DEFAULT 100
);




DROP TABLE IF EXISTS x_table_column_code_mappings;

CREATE TABLE x_table_column_code_mappings (
  column_alias_name VARCHAR(50) NOT NULL PRIMARY KEY,
  code_id INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_x_table_column_code_mappings_code_id ON x_table_column_code_mappings (code_id);




















