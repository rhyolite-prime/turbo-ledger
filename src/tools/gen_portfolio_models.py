#!/usr/bin/env python3
"""
gen_portfolio_models.py — one-off driver that calls genmodel.generate() for
every table introduced by Portfolio's Phase 6 migrations
(V001__baseline.sql's 2 ground-truth tables + V003__phase6.sql's ~40
hand-designed lending/shares tables). See genmodel.py's module docstring for
why hand-generation (vs. drogon_ctl create_model) is used in this sandbox.

Column lists below are transcribed 1:1 from the CREATE TABLE statements in
the corresponding migration files — keep them in sync if the schema changes.

Run with: python3 src/tools/gen_portfolio_models.py
"""
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
from genmodel import Column, ModelSpec, generate  # noqa: E402

NS = "TlPortfolioDb"
OUT = os.path.join(os.path.dirname(__file__), "..", "services", "Portfolio", "models")


def uuid_pk(name="id"):
    return Column(name, "uuid", pk=True, not_null=True, has_default=True)


def uuid_col(name, not_null=False):
    return Column(name, "uuid", not_null=not_null)


def varchar(name, length, not_null=False, has_default=False):
    return Column(name, "varchar", length=length, not_null=not_null, has_default=has_default)


def text(name, not_null=False):
    return Column(name, "text", not_null=not_null)


def jsonb(name, not_null=False, has_default=False):
    return Column(name, "jsonb", not_null=not_null, has_default=has_default)


def integer(name, not_null=False, has_default=False):
    return Column(name, "int", not_null=not_null, has_default=has_default)


def bigint(name, not_null=False, has_default=False):
    return Column(name, "bigint", not_null=not_null, has_default=has_default)


def boolean(name, not_null=False, has_default=False):
    return Column(name, "bool", not_null=not_null, has_default=has_default)


def numeric(name, not_null=False, has_default=False):
    return Column(name, "numeric", not_null=not_null, has_default=has_default)


def date(name, not_null=False, has_default=False):
    return Column(name, "date", not_null=not_null, has_default=has_default)


def ts(name, not_null=False, has_default=False):
    return Column(name, "timestamptz", not_null=not_null, has_default=has_default)


SPECS = []


def add(class_name, table_name, columns):
    SPECS.append(ModelSpec(class_name=class_name, table_name=table_name, namespace=NS, columns=columns))


# ---------------------------------------------------------------------------
# V001 ground-truth tables (no model existed yet for these).
# ---------------------------------------------------------------------------

add("LoanproductProvisioningEntry", "loanproduct_provisioning_entry", [
    uuid_pk(),
    uuid_col("history_id", not_null=True),
    uuid_col("criteria_id", not_null=True),
    varchar("currency_code", 3, not_null=True),
    uuid_col("office_id", not_null=True),
    uuid_col("product_id", not_null=True),
    uuid_col("category_id", not_null=True),
    bigint("overdue_in_days", has_default=True),
    numeric("reseve_amount", has_default=True),
    uuid_col("liability_account"),
    uuid_col("expense_account"),
])

add("ProvisioningHistory", "provisioning_history", [
    uuid_pk(),
    boolean("journal_entry_created", has_default=True),
    uuid_col("createdby_id"),
    date("created_date"),
    uuid_col("lastmodifiedby_id"),
    date("lastmodified_date"),
])

# ---------------------------------------------------------------------------
# V003 — loan products
# ---------------------------------------------------------------------------

add("LoanProduct", "loan_product", [
    uuid_pk(),
    varchar("name", 100, not_null=True),
    varchar("short_name", 4, not_null=True),
    text("description"),
    uuid_col("fund_id"),
    varchar("currency_code", 3, not_null=True),
    integer("currency_digits", not_null=True, has_default=True),
    numeric("min_principal_amount"),
    numeric("default_principal_amount", not_null=True),
    numeric("max_principal_amount"),
    integer("min_number_of_repayments"),
    integer("default_number_of_repayments", not_null=True),
    integer("max_number_of_repayments"),
    integer("repayment_every", not_null=True, has_default=True),
    integer("repayment_frequency_type", not_null=True, has_default=True),
    numeric("min_interest_rate_per_period"),
    numeric("default_interest_rate_per_period", not_null=True),
    numeric("max_interest_rate_per_period"),
    integer("interest_period_frequency_type", not_null=True, has_default=True),
    numeric("annual_nominal_interest_rate", not_null=True),
    integer("interest_method", not_null=True, has_default=True),
    integer("interest_calculation_period_type", not_null=True, has_default=True),
    integer("amortization_type", not_null=True, has_default=True),
    varchar("transaction_processing_strategy", 40, not_null=True, has_default=True),
    integer("grace_on_principal_payment", not_null=True, has_default=True),
    integer("grace_on_interest_payment", not_null=True, has_default=True),
    integer("grace_on_interest_charged", not_null=True, has_default=True),
    integer("grace_on_arrears_ageing", not_null=True, has_default=True),
    integer("overdue_days_for_npa", not_null=True, has_default=True),
    integer("days_in_year_type", not_null=True, has_default=True),
    integer("days_in_month_type", not_null=True, has_default=True),
    integer("min_days_between_disbursal_and_first_repayment", not_null=True, has_default=True),
    boolean("allow_partial_period_interest", not_null=True, has_default=True),
    boolean("is_linked_to_floating_rate", not_null=True, has_default=True),
    uuid_col("floating_rate_id"),
    numeric("default_differential_lending_rate"),
    boolean("is_equal_amortization", not_null=True, has_default=True),
    boolean("allow_attribute_overrides", not_null=True, has_default=True),
    boolean("can_use_for_topup", not_null=True, has_default=True),
    date("close_date"),
    date("start_date"),
    uuid_col("delinquency_bucket_id"),
    integer("accounting_type", not_null=True, has_default=True),
    uuid_col("fund_source_account_id"),
    uuid_col("loan_portfolio_account_id"),
    uuid_col("interest_on_loan_account_id"),
    uuid_col("income_from_fees_account_id"),
    uuid_col("income_from_penalties_account_id"),
    uuid_col("income_from_recovery_account_id"),
    uuid_col("losses_written_off_account_id"),
    uuid_col("overpayment_liability_account_id"),
    uuid_col("interest_receivable_account_id"),
    uuid_col("fee_receivable_account_id"),
    uuid_col("penalty_receivable_account_id"),
    boolean("is_active", not_null=True, has_default=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
    uuid_col("updated_by"),
    ts("updated_at", not_null=True, has_default=True),
])

add("LoanProductCharge", "loan_product_charge", [
    uuid_pk(),
    uuid_col("loan_product_id", not_null=True),
    uuid_col("charge_id", not_null=True),
])

add("LoanProductAttribute", "loan_product_attribute", [
    uuid_pk(),
    uuid_col("loan_product_id", not_null=True),
    varchar("attribute_key", 100, not_null=True),
    text("attribute_value"),
    ts("created_at", not_null=True, has_default=True),
])

# ---------------------------------------------------------------------------
# floating rates / rates
# ---------------------------------------------------------------------------

add("FloatingRate", "floating_rate", [
    uuid_pk(),
    varchar("name", 100, not_null=True),
    boolean("is_base_lending_rate", not_null=True, has_default=True),
    boolean("is_active", not_null=True, has_default=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
    uuid_col("updated_by"),
    ts("updated_at", not_null=True, has_default=True),
])

add("FloatingRatePeriod", "floating_rate_period", [
    uuid_pk(),
    uuid_col("floating_rate_id", not_null=True),
    date("from_date", not_null=True),
    numeric("interest_rate", not_null=True),
    boolean("is_differential_to_bln", not_null=True, has_default=True),
    numeric("bln_differential_rate"),
    boolean("is_active", not_null=True, has_default=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
])

add("Rate", "rate", [
    uuid_pk(),
    varchar("name", 100, not_null=True),
    numeric("percentage", not_null=True),
    boolean("is_active", not_null=True, has_default=True),
    ts("created_at", not_null=True, has_default=True),
])

# ---------------------------------------------------------------------------
# delinquency
# ---------------------------------------------------------------------------

add("DelinquencyRange", "delinquency_range", [
    uuid_pk(),
    varchar("classification", 100, not_null=True),
    integer("min_overdue_days", not_null=True),
    integer("max_overdue_days"),
    ts("created_at", not_null=True, has_default=True),
])

add("DelinquencyBucket", "delinquency_bucket", [
    uuid_pk(),
    varchar("name", 100, not_null=True),
    ts("created_at", not_null=True, has_default=True),
])

add("DelinquencyBucketRange", "delinquency_bucket_range", [
    uuid_pk(),
    uuid_col("delinquency_bucket_id", not_null=True),
    uuid_col("delinquency_range_id", not_null=True),
])

# ---------------------------------------------------------------------------
# provisioning
# ---------------------------------------------------------------------------

add("ProvisioningCategory", "provisioning_category", [
    uuid_pk(),
    varchar("category_name", 100, not_null=True),
    text("category_description"),
    ts("created_at", not_null=True, has_default=True),
])

add("ProvisioningCriteria", "provisioning_criteria", [
    uuid_pk(),
    varchar("criteria_name", 100, not_null=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
    uuid_col("updated_by"),
    ts("updated_at", not_null=True, has_default=True),
])

add("ProvisioningCriteriaDefinition", "provisioning_criteria_definition", [
    uuid_pk(),
    uuid_col("criteria_id", not_null=True),
    uuid_col("category_id", not_null=True),
    integer("min_overdue_days", not_null=True),
    integer("max_overdue_days"),
    numeric("provisioning_percentage", not_null=True),
    uuid_col("liability_account_id"),
    uuid_col("expense_account_id"),
])

# ---------------------------------------------------------------------------
# loans
# ---------------------------------------------------------------------------

add("Loan", "loan", [
    uuid_pk(),
    varchar("account_no", 20, not_null=True),
    varchar("external_id", 100),
    uuid_col("client_id"),
    uuid_col("group_id"),
    uuid_col("product_id", not_null=True),
    uuid_col("loan_officer_id"),
    uuid_col("fund_id"),
    varchar("loan_purpose", 200),
    integer("loan_type", not_null=True, has_default=True),
    varchar("currency_code", 3, not_null=True),
    integer("currency_digits", not_null=True, has_default=True),
    numeric("principal_amount", not_null=True),
    numeric("approved_principal"),
    numeric("net_disbursal_amount"),
    integer("number_of_repayments", not_null=True),
    integer("repayment_every", not_null=True),
    integer("repayment_frequency_type", not_null=True),
    numeric("interest_rate_per_period", not_null=True),
    integer("interest_period_frequency_type", not_null=True),
    numeric("annual_nominal_interest_rate", not_null=True),
    integer("interest_method", not_null=True),
    integer("interest_calculation_period_type", not_null=True),
    integer("amortization_type", not_null=True),
    varchar("transaction_processing_strategy", 40, not_null=True),
    integer("days_in_year_type", not_null=True, has_default=True),
    integer("days_in_month_type", not_null=True, has_default=True),
    integer("grace_on_principal_payment", not_null=True, has_default=True),
    integer("grace_on_interest_payment", not_null=True, has_default=True),
    integer("grace_on_interest_charged", not_null=True, has_default=True),
    integer("grace_on_arrears_ageing", not_null=True, has_default=True),
    boolean("is_equal_amortization", not_null=True, has_default=True),
    boolean("is_floating_interest_rate", not_null=True, has_default=True),
    uuid_col("floating_rate_id"),
    numeric("interest_rate_differential"),
    date("submitted_on_date", not_null=True),
    uuid_col("submitted_by"),
    date("approved_on_date"),
    uuid_col("approved_by"),
    date("expected_disbursement_date"),
    date("actual_disbursement_date"),
    uuid_col("disbursed_by"),
    date("expected_first_repayment_on_date"),
    date("interest_charged_from_date"),
    date("expected_maturity_date"),
    date("maturity_date"),
    date("closed_on_date"),
    uuid_col("closed_by"),
    date("rejected_on_date"),
    date("withdrawn_on_date"),
    date("writtenoff_on_date"),
    integer("status", not_null=True, has_default=True),
    integer("sub_status"),
    boolean("is_npa", not_null=True, has_default=True),
    uuid_col("delinquency_range_id"),
    date("overdue_since_date"),
    numeric("principal_disbursed", not_null=True, has_default=True),
    numeric("principal_paid", not_null=True, has_default=True),
    numeric("principal_writtenoff", not_null=True, has_default=True),
    numeric("interest_charged", not_null=True, has_default=True),
    numeric("interest_paid", not_null=True, has_default=True),
    numeric("interest_waived", not_null=True, has_default=True),
    numeric("interest_writtenoff", not_null=True, has_default=True),
    numeric("fee_charges_charged", not_null=True, has_default=True),
    numeric("fee_charges_paid", not_null=True, has_default=True),
    numeric("fee_charges_waived", not_null=True, has_default=True),
    numeric("fee_charges_writtenoff", not_null=True, has_default=True),
    numeric("penalty_charges_charged", not_null=True, has_default=True),
    numeric("penalty_charges_paid", not_null=True, has_default=True),
    numeric("penalty_charges_waived", not_null=True, has_default=True),
    numeric("penalty_charges_writtenoff", not_null=True, has_default=True),
    numeric("total_recovered", not_null=True, has_default=True),
    numeric("total_overpaid", not_null=True, has_default=True),
    numeric("buydown_fee_amount", not_null=True, has_default=True),
    numeric("capitalized_income_amount", not_null=True, has_default=True),
    uuid_col("glim_parent_loan_id"),
    ts("created_at", not_null=True, has_default=True),
    ts("updated_at", not_null=True, has_default=True),
])

add("LoanProductMix", "loan_product_mix", [
    uuid_pk(),
    uuid_col("product_id", not_null=True),
    uuid_col("restricted_product_id", not_null=True),
])

add("LoanDisbursementDetail", "loan_disbursement_detail", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    date("expected_disburse_date", not_null=True),
    date("actual_disburse_date"),
    numeric("principal", not_null=True),
])

add("LoanCharge", "loan_charge", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    uuid_col("charge_id", not_null=True),
    boolean("is_penalty", not_null=True, has_default=True),
    integer("charge_time_type", not_null=True),
    integer("charge_calculation_type", not_null=True),
    date("due_date"),
    integer("installment_number"),
    numeric("amount", not_null=True),
    numeric("amount_paid_derived", not_null=True, has_default=True),
    numeric("amount_waived_derived", not_null=True, has_default=True),
    numeric("amount_writtenoff_derived", not_null=True, has_default=True),
    numeric("amount_outstanding_derived", not_null=True, has_default=True),
    boolean("is_paid_derived", not_null=True, has_default=True),
    boolean("is_waived", not_null=True, has_default=True),
    boolean("is_active", not_null=True, has_default=True),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanCollateral", "loan_collateral", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    varchar("collateral_type_id", 40, not_null=True),
    numeric("value"),
    text("description"),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanGuarantor", "loan_guarantor", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    integer("guarantor_type", not_null=True, has_default=True),
    uuid_col("client_id"),
    varchar("first_name", 100),
    varchar("last_name", 100),
    varchar("address_line_1", 200),
    varchar("city", 100),
    varchar("mobile_number", 40),
    numeric("amount"),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanRate", "loan_rate", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    uuid_col("rate_id", not_null=True),
])

add("LoanInterestPause", "loan_interest_pause", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    varchar("external_id", 100),
    date("start_date", not_null=True),
    date("end_date", not_null=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanPostdatedCheck", "loan_postdated_check", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    uuid_col("installment_id"),
    varchar("check_number", 40, not_null=True),
    varchar("bank_name", 100),
    date("check_date", not_null=True),
    numeric("amount", not_null=True),
    integer("status", not_null=True, has_default=True),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanBuydownFee", "loan_buydown_fee", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    uuid_col("loan_transaction_id"),
    numeric("amount", not_null=True),
    numeric("amortized_amount", not_null=True, has_default=True),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanCapitalizedIncome", "loan_capitalized_income", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    uuid_col("loan_transaction_id"),
    varchar("income_type", 40, not_null=True, has_default=True),
    numeric("amount", not_null=True),
    numeric("amortized_amount", not_null=True, has_default=True),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanRepaymentScheduleInstallment", "loan_repayment_schedule_installment", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    integer("installment_number", not_null=True),
    date("from_date", not_null=True),
    date("due_date", not_null=True),
    numeric("principal_amount", not_null=True),
    numeric("principal_completed_derived", not_null=True, has_default=True),
    numeric("principal_writtenoff_derived", not_null=True, has_default=True),
    numeric("interest_amount", not_null=True),
    numeric("interest_completed_derived", not_null=True, has_default=True),
    numeric("interest_waived_derived", not_null=True, has_default=True),
    numeric("interest_writtenoff_derived", not_null=True, has_default=True),
    numeric("fee_charges_amount", not_null=True, has_default=True),
    numeric("fee_charges_completed_derived", not_null=True, has_default=True),
    numeric("fee_charges_waived_derived", not_null=True, has_default=True),
    numeric("penalty_charges_amount", not_null=True, has_default=True),
    numeric("penalty_charges_completed_derived", not_null=True, has_default=True),
    numeric("penalty_charges_waived_derived", not_null=True, has_default=True),
    boolean("completed_derived", not_null=True, has_default=True),
    date("obligations_met_on_date"),
    boolean("recalculated_interest", not_null=True, has_default=True),
])

add("LoanTransaction", "loan_transaction", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    varchar("external_id", 100),
    uuid_col("office_id"),
    integer("transaction_type", not_null=True),
    date("transaction_date", not_null=True),
    numeric("amount", not_null=True),
    numeric("principal_portion", not_null=True, has_default=True),
    numeric("interest_portion", not_null=True, has_default=True),
    numeric("fee_charges_portion", not_null=True, has_default=True),
    numeric("penalty_charges_portion", not_null=True, has_default=True),
    numeric("overpayment_portion", not_null=True, has_default=True),
    numeric("outstanding_loan_balance_derived"),
    boolean("is_reversed", not_null=True, has_default=True),
    date("reversed_on_date"),
    date("submitted_on_date", not_null=True, has_default=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
])

add("RescheduleLoanRequest", "reschedule_loan_request", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    varchar("reason_code", 100, not_null=True),
    text("reason_comment"),
    integer("status", not_null=True, has_default=True),
    integer("reschedule_from_installment"),
    date("reschedule_from_date"),
    date("submitted_on_date", not_null=True),
    uuid_col("submitted_by"),
    integer("extra_terms"),
    integer("grace_on_principal"),
    integer("grace_on_interest"),
    numeric("new_interest_rate"),
    date("adjusted_due_date"),
    date("approved_on_date"),
    uuid_col("approved_by"),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanDelinquencyTagHistory", "loan_delinquency_tag_history", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    uuid_col("delinquency_range_id", not_null=True),
    date("classification_date", not_null=True),
    date("liftoff_date"),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanDelinquencyAction", "loan_delinquency_action", [
    uuid_pk(),
    uuid_col("loan_id", not_null=True),
    integer("action", not_null=True),
    date("start_date", not_null=True),
    date("end_date"),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
])

# ---------------------------------------------------------------------------
# credit bureau
# ---------------------------------------------------------------------------

add("CreditBureau", "credit_bureau", [
    uuid_pk(),
    varchar("name", 100, not_null=True),
    varchar("country", 2),
    boolean("is_active", not_null=True, has_default=True),
    ts("created_at", not_null=True, has_default=True),
])

add("OrganisationCreditBureau", "organisation_credit_bureau", [
    uuid_pk(),
    uuid_col("credit_bureau_id", not_null=True),
    varchar("alias", 100, not_null=True),
    boolean("is_active", not_null=True, has_default=True),
    ts("created_at", not_null=True, has_default=True),
])

add("CreditBureauConfiguration", "credit_bureau_configuration", [
    uuid_pk(),
    uuid_col("organisation_credit_bureau_id", not_null=True),
    varchar("config_key", 100, not_null=True),
    text("config_value"),
])

add("CreditBureauLoanProductMapping", "credit_bureau_loan_product_mapping", [
    uuid_pk(),
    uuid_col("organisation_credit_bureau_id", not_null=True),
    uuid_col("loan_product_id", not_null=True),
    boolean("is_active", not_null=True, has_default=True),
])

add("CreditBureauReport", "credit_bureau_report", [
    uuid_pk(),
    uuid_col("organisation_credit_bureau_id", not_null=True),
    uuid_col("client_id"),
    uuid_col("loan_id"),
    varchar("national_id", 60),
    jsonb("report_data", not_null=True, has_default=True),
    uuid_col("requested_by"),
    ts("requested_on", not_null=True, has_default=True),
    boolean("is_active", not_null=True, has_default=True),
])

# ---------------------------------------------------------------------------
# external asset owners
# ---------------------------------------------------------------------------

add("ExternalAssetOwner", "external_asset_owner", [
    uuid_pk(),
    varchar("external_id", 100, not_null=True),
    varchar("name", 150, not_null=True),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanOwnerTransfer", "loan_owner_transfer", [
    uuid_pk(),
    varchar("external_id", 100),
    uuid_col("loan_id", not_null=True),
    uuid_col("owner_id", not_null=True),
    integer("transfer_type", not_null=True, has_default=True),
    integer("status", not_null=True, has_default=True),
    date("settlement_date"),
    date("effective_date", not_null=True),
    numeric("purchase_price_ratio", not_null=True, has_default=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
])

add("LoanOwnerTransferJournalEntry", "loan_owner_transfer_journal_entry", [
    uuid_pk(),
    uuid_col("transfer_id", not_null=True),
    varchar("entry_type", 40, not_null=True),
    numeric("amount", not_null=True),
    uuid_col("gl_account_id"),
    ts("created_at", not_null=True, has_default=True),
])

# ---------------------------------------------------------------------------
# shares
# ---------------------------------------------------------------------------

add("ShareProduct", "share_product", [
    uuid_pk(),
    varchar("name", 100, not_null=True),
    varchar("short_name", 4, not_null=True),
    text("description"),
    varchar("currency_code", 3, not_null=True),
    integer("currency_digits", not_null=True, has_default=True),
    bigint("total_shares", not_null=True),
    bigint("total_shares_to_be_issued", not_null=True),
    numeric("nominal_price", not_null=True),
    numeric("market_price"),
    integer("share_capital_type", not_null=True, has_default=True),
    bigint("minimum_shares"),
    bigint("default_shares"),
    bigint("maximum_shares"),
    boolean("allow_dividends_for_inactive_clients", not_null=True, has_default=True),
    integer("lockin_period"),
    integer("lockin_period_frequency_type"),
    integer("accounting_type", not_null=True, has_default=True),
    uuid_col("share_reference_account_id"),
    uuid_col("share_suspense_account_id"),
    uuid_col("share_equity_account_id"),
    boolean("is_active", not_null=True, has_default=True),
    date("start_date"),
    date("close_date"),
    ts("created_at", not_null=True, has_default=True),
    ts("updated_at", not_null=True, has_default=True),
])

add("ShareProductCharge", "share_product_charge", [
    uuid_pk(),
    uuid_col("share_product_id", not_null=True),
    uuid_col("charge_id", not_null=True),
])

add("ShareProductDividend", "share_product_dividend", [
    uuid_pk(),
    uuid_col("share_product_id", not_null=True),
    date("dividend_period_start_date", not_null=True),
    date("dividend_period_end_date", not_null=True),
    numeric("dividend_amount", not_null=True),
    integer("status", not_null=True, has_default=True),
    uuid_col("created_by"),
    ts("created_at", not_null=True, has_default=True),
])

add("ShareAccount", "share_account", [
    uuid_pk(),
    varchar("account_no", 20, not_null=True),
    varchar("external_id", 100),
    uuid_col("client_id"),
    uuid_col("group_id"),
    uuid_col("product_id", not_null=True),
    varchar("currency_code", 3, not_null=True),
    date("submitted_date", not_null=True),
    uuid_col("submitted_by"),
    date("approved_date"),
    uuid_col("approved_by"),
    date("activated_date"),
    date("rejected_date"),
    date("closed_date"),
    integer("status", not_null=True, has_default=True),
    bigint("requested_shares", not_null=True),
    bigint("approved_shares", not_null=True, has_default=True),
    integer("lockin_period"),
    integer("lockin_period_frequency_type"),
    ts("created_at", not_null=True, has_default=True),
])

add("ShareAccountCharge", "share_account_charge", [
    uuid_pk(),
    uuid_col("share_account_id", not_null=True),
    uuid_col("charge_id", not_null=True),
    numeric("amount", not_null=True),
    numeric("amount_paid_derived", not_null=True, has_default=True),
    boolean("is_active", not_null=True, has_default=True),
])

add("SharePurchaseRequest", "share_purchase_request", [
    uuid_pk(),
    uuid_col("share_account_id", not_null=True),
    date("requested_date", not_null=True),
    bigint("requested_shares", not_null=True),
    numeric("requested_price"),
    integer("status", not_null=True, has_default=True),
    uuid_col("requested_by"),
    uuid_col("decided_by"),
    date("decided_date"),
    ts("created_at", not_null=True, has_default=True),
])


if __name__ == "__main__":
    os.makedirs(OUT, exist_ok=True)
    for spec in SPECS:
        generate(spec, OUT)
    print(f"\ngenerated {len(SPECS)} models into {OUT}")
