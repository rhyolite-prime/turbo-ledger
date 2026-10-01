/**
 *  Loan.cc
 *
 *  See Loan.h for the hand-authored-subset note.
 *
 */

#include "Loan.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string Loan::Cols::_id = "\"id\"";
const std::string Loan::Cols::_account_no = "\"account_no\"";
const std::string Loan::Cols::_external_id = "\"external_id\"";
const std::string Loan::Cols::_client_id = "\"client_id\"";
const std::string Loan::Cols::_group_id = "\"group_id\"";
const std::string Loan::Cols::_product_id = "\"product_id\"";
const std::string Loan::Cols::_loan_officer_id = "\"loan_officer_id\"";
const std::string Loan::Cols::_fund_id = "\"fund_id\"";
const std::string Loan::Cols::_loan_purpose = "\"loan_purpose\"";
const std::string Loan::Cols::_loan_type = "\"loan_type\"";
const std::string Loan::Cols::_currency_code = "\"currency_code\"";
const std::string Loan::Cols::_currency_digits = "\"currency_digits\"";
const std::string Loan::Cols::_principal_amount = "\"principal_amount\"";
const std::string Loan::Cols::_approved_principal = "\"approved_principal\"";
const std::string Loan::Cols::_net_disbursal_amount = "\"net_disbursal_amount\"";
const std::string Loan::Cols::_number_of_repayments = "\"number_of_repayments\"";
const std::string Loan::Cols::_repayment_every = "\"repayment_every\"";
const std::string Loan::Cols::_repayment_frequency_type = "\"repayment_frequency_type\"";
const std::string Loan::Cols::_interest_rate_per_period = "\"interest_rate_per_period\"";
const std::string Loan::Cols::_interest_period_frequency_type = "\"interest_period_frequency_type\"";
const std::string Loan::Cols::_annual_nominal_interest_rate = "\"annual_nominal_interest_rate\"";
const std::string Loan::Cols::_interest_method = "\"interest_method\"";
const std::string Loan::Cols::_interest_calculation_period_type = "\"interest_calculation_period_type\"";
const std::string Loan::Cols::_amortization_type = "\"amortization_type\"";
const std::string Loan::Cols::_transaction_processing_strategy = "\"transaction_processing_strategy\"";
const std::string Loan::Cols::_days_in_year_type = "\"days_in_year_type\"";
const std::string Loan::Cols::_days_in_month_type = "\"days_in_month_type\"";
const std::string Loan::Cols::_grace_on_principal_payment = "\"grace_on_principal_payment\"";
const std::string Loan::Cols::_grace_on_interest_payment = "\"grace_on_interest_payment\"";
const std::string Loan::Cols::_grace_on_interest_charged = "\"grace_on_interest_charged\"";
const std::string Loan::Cols::_grace_on_arrears_ageing = "\"grace_on_arrears_ageing\"";
const std::string Loan::Cols::_is_equal_amortization = "\"is_equal_amortization\"";
const std::string Loan::Cols::_is_floating_interest_rate = "\"is_floating_interest_rate\"";
const std::string Loan::Cols::_floating_rate_id = "\"floating_rate_id\"";
const std::string Loan::Cols::_interest_rate_differential = "\"interest_rate_differential\"";
const std::string Loan::Cols::_submitted_on_date = "\"submitted_on_date\"";
const std::string Loan::Cols::_submitted_by = "\"submitted_by\"";
const std::string Loan::Cols::_approved_on_date = "\"approved_on_date\"";
const std::string Loan::Cols::_approved_by = "\"approved_by\"";
const std::string Loan::Cols::_expected_disbursement_date = "\"expected_disbursement_date\"";
const std::string Loan::Cols::_actual_disbursement_date = "\"actual_disbursement_date\"";
const std::string Loan::Cols::_disbursed_by = "\"disbursed_by\"";
const std::string Loan::Cols::_expected_first_repayment_on_date = "\"expected_first_repayment_on_date\"";
const std::string Loan::Cols::_interest_charged_from_date = "\"interest_charged_from_date\"";
const std::string Loan::Cols::_expected_maturity_date = "\"expected_maturity_date\"";
const std::string Loan::Cols::_maturity_date = "\"maturity_date\"";
const std::string Loan::Cols::_closed_on_date = "\"closed_on_date\"";
const std::string Loan::Cols::_closed_by = "\"closed_by\"";
const std::string Loan::Cols::_rejected_on_date = "\"rejected_on_date\"";
const std::string Loan::Cols::_withdrawn_on_date = "\"withdrawn_on_date\"";
const std::string Loan::Cols::_writtenoff_on_date = "\"writtenoff_on_date\"";
const std::string Loan::Cols::_status = "\"status\"";
const std::string Loan::Cols::_sub_status = "\"sub_status\"";
const std::string Loan::Cols::_is_npa = "\"is_npa\"";
const std::string Loan::Cols::_delinquency_range_id = "\"delinquency_range_id\"";
const std::string Loan::Cols::_overdue_since_date = "\"overdue_since_date\"";
const std::string Loan::Cols::_principal_disbursed = "\"principal_disbursed\"";
const std::string Loan::Cols::_principal_paid = "\"principal_paid\"";
const std::string Loan::Cols::_principal_writtenoff = "\"principal_writtenoff\"";
const std::string Loan::Cols::_interest_charged = "\"interest_charged\"";
const std::string Loan::Cols::_interest_paid = "\"interest_paid\"";
const std::string Loan::Cols::_interest_waived = "\"interest_waived\"";
const std::string Loan::Cols::_interest_writtenoff = "\"interest_writtenoff\"";
const std::string Loan::Cols::_fee_charges_charged = "\"fee_charges_charged\"";
const std::string Loan::Cols::_fee_charges_paid = "\"fee_charges_paid\"";
const std::string Loan::Cols::_fee_charges_waived = "\"fee_charges_waived\"";
const std::string Loan::Cols::_fee_charges_writtenoff = "\"fee_charges_writtenoff\"";
const std::string Loan::Cols::_penalty_charges_charged = "\"penalty_charges_charged\"";
const std::string Loan::Cols::_penalty_charges_paid = "\"penalty_charges_paid\"";
const std::string Loan::Cols::_penalty_charges_waived = "\"penalty_charges_waived\"";
const std::string Loan::Cols::_penalty_charges_writtenoff = "\"penalty_charges_writtenoff\"";
const std::string Loan::Cols::_total_recovered = "\"total_recovered\"";
const std::string Loan::Cols::_total_overpaid = "\"total_overpaid\"";
const std::string Loan::Cols::_buydown_fee_amount = "\"buydown_fee_amount\"";
const std::string Loan::Cols::_capitalized_income_amount = "\"capitalized_income_amount\"";
const std::string Loan::Cols::_glim_parent_loan_id = "\"glim_parent_loan_id\"";
const std::string Loan::Cols::_created_at = "\"created_at\"";
const std::string Loan::Cols::_updated_at = "\"updated_at\"";
const std::string Loan::primaryKeyName = "id";
const bool Loan::hasPrimaryKey = true;
const std::string Loan::tableName = "\"loan\"";

const std::vector<typename Loan::MetaData> Loan::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"account_no","std::string","character varying",20,0,0,1},
{"external_id","std::string","character varying",100,0,0,0},
{"client_id","std::string","uuid",0,0,0,0},
{"group_id","std::string","uuid",0,0,0,0},
{"product_id","std::string","uuid",0,0,0,1},
{"loan_officer_id","std::string","uuid",0,0,0,0},
{"fund_id","std::string","uuid",0,0,0,0},
{"loan_purpose","std::string","character varying",200,0,0,0},
{"loan_type","int32_t","integer",4,0,0,1},
{"currency_code","std::string","character varying",3,0,0,1},
{"currency_digits","int32_t","integer",4,0,0,1},
{"principal_amount","std::string","numeric",0,0,0,1},
{"approved_principal","std::string","numeric",0,0,0,0},
{"net_disbursal_amount","std::string","numeric",0,0,0,0},
{"number_of_repayments","int32_t","integer",4,0,0,1},
{"repayment_every","int32_t","integer",4,0,0,1},
{"repayment_frequency_type","int32_t","integer",4,0,0,1},
{"interest_rate_per_period","std::string","numeric",0,0,0,1},
{"interest_period_frequency_type","int32_t","integer",4,0,0,1},
{"annual_nominal_interest_rate","std::string","numeric",0,0,0,1},
{"interest_method","int32_t","integer",4,0,0,1},
{"interest_calculation_period_type","int32_t","integer",4,0,0,1},
{"amortization_type","int32_t","integer",4,0,0,1},
{"transaction_processing_strategy","std::string","character varying",40,0,0,1},
{"days_in_year_type","int32_t","integer",4,0,0,1},
{"days_in_month_type","int32_t","integer",4,0,0,1},
{"grace_on_principal_payment","int32_t","integer",4,0,0,1},
{"grace_on_interest_payment","int32_t","integer",4,0,0,1},
{"grace_on_interest_charged","int32_t","integer",4,0,0,1},
{"grace_on_arrears_ageing","int32_t","integer",4,0,0,1},
{"is_equal_amortization","bool","boolean",1,0,0,1},
{"is_floating_interest_rate","bool","boolean",1,0,0,1},
{"floating_rate_id","std::string","uuid",0,0,0,0},
{"interest_rate_differential","std::string","numeric",0,0,0,0},
{"submitted_on_date","::trantor::Date","date",0,0,0,1},
{"submitted_by","std::string","uuid",0,0,0,0},
{"approved_on_date","::trantor::Date","date",0,0,0,0},
{"approved_by","std::string","uuid",0,0,0,0},
{"expected_disbursement_date","::trantor::Date","date",0,0,0,0},
{"actual_disbursement_date","::trantor::Date","date",0,0,0,0},
{"disbursed_by","std::string","uuid",0,0,0,0},
{"expected_first_repayment_on_date","::trantor::Date","date",0,0,0,0},
{"interest_charged_from_date","::trantor::Date","date",0,0,0,0},
{"expected_maturity_date","::trantor::Date","date",0,0,0,0},
{"maturity_date","::trantor::Date","date",0,0,0,0},
{"closed_on_date","::trantor::Date","date",0,0,0,0},
{"closed_by","std::string","uuid",0,0,0,0},
{"rejected_on_date","::trantor::Date","date",0,0,0,0},
{"withdrawn_on_date","::trantor::Date","date",0,0,0,0},
{"writtenoff_on_date","::trantor::Date","date",0,0,0,0},
{"status","int32_t","integer",4,0,0,1},
{"sub_status","int32_t","integer",4,0,0,0},
{"is_npa","bool","boolean",1,0,0,1},
{"delinquency_range_id","std::string","uuid",0,0,0,0},
{"overdue_since_date","::trantor::Date","date",0,0,0,0},
{"principal_disbursed","std::string","numeric",0,0,0,1},
{"principal_paid","std::string","numeric",0,0,0,1},
{"principal_writtenoff","std::string","numeric",0,0,0,1},
{"interest_charged","std::string","numeric",0,0,0,1},
{"interest_paid","std::string","numeric",0,0,0,1},
{"interest_waived","std::string","numeric",0,0,0,1},
{"interest_writtenoff","std::string","numeric",0,0,0,1},
{"fee_charges_charged","std::string","numeric",0,0,0,1},
{"fee_charges_paid","std::string","numeric",0,0,0,1},
{"fee_charges_waived","std::string","numeric",0,0,0,1},
{"fee_charges_writtenoff","std::string","numeric",0,0,0,1},
{"penalty_charges_charged","std::string","numeric",0,0,0,1},
{"penalty_charges_paid","std::string","numeric",0,0,0,1},
{"penalty_charges_waived","std::string","numeric",0,0,0,1},
{"penalty_charges_writtenoff","std::string","numeric",0,0,0,1},
{"total_recovered","std::string","numeric",0,0,0,1},
{"total_overpaid","std::string","numeric",0,0,0,1},
{"buydown_fee_amount","std::string","numeric",0,0,0,1},
{"capitalized_income_amount","std::string","numeric",0,0,0,1},
{"glim_parent_loan_id","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Loan::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Loan::Loan(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["account_no"].isNull())
        {
            accountNo_=std::make_shared<std::string>(r["account_no"].as<std::string>());
        }
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["group_id"].isNull())
        {
            groupId_=std::make_shared<std::string>(r["group_id"].as<std::string>());
        }
        if(!r["product_id"].isNull())
        {
            productId_=std::make_shared<std::string>(r["product_id"].as<std::string>());
        }
        if(!r["loan_officer_id"].isNull())
        {
            loanOfficerId_=std::make_shared<std::string>(r["loan_officer_id"].as<std::string>());
        }
        if(!r["fund_id"].isNull())
        {
            fundId_=std::make_shared<std::string>(r["fund_id"].as<std::string>());
        }
        if(!r["loan_purpose"].isNull())
        {
            loanPurpose_=std::make_shared<std::string>(r["loan_purpose"].as<std::string>());
        }
        if(!r["loan_type"].isNull())
        {
            loanType_=std::make_shared<int32_t>(r["loan_type"].as<int32_t>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["currency_digits"].isNull())
        {
            currencyDigits_=std::make_shared<int32_t>(r["currency_digits"].as<int32_t>());
        }
        if(!r["principal_amount"].isNull())
        {
            principalAmount_=std::make_shared<std::string>(r["principal_amount"].as<std::string>());
        }
        if(!r["approved_principal"].isNull())
        {
            approvedPrincipal_=std::make_shared<std::string>(r["approved_principal"].as<std::string>());
        }
        if(!r["net_disbursal_amount"].isNull())
        {
            netDisbursalAmount_=std::make_shared<std::string>(r["net_disbursal_amount"].as<std::string>());
        }
        if(!r["number_of_repayments"].isNull())
        {
            numberOfRepayments_=std::make_shared<int32_t>(r["number_of_repayments"].as<int32_t>());
        }
        if(!r["repayment_every"].isNull())
        {
            repaymentEvery_=std::make_shared<int32_t>(r["repayment_every"].as<int32_t>());
        }
        if(!r["repayment_frequency_type"].isNull())
        {
            repaymentFrequencyType_=std::make_shared<int32_t>(r["repayment_frequency_type"].as<int32_t>());
        }
        if(!r["interest_rate_per_period"].isNull())
        {
            interestRatePerPeriod_=std::make_shared<std::string>(r["interest_rate_per_period"].as<std::string>());
        }
        if(!r["interest_period_frequency_type"].isNull())
        {
            interestPeriodFrequencyType_=std::make_shared<int32_t>(r["interest_period_frequency_type"].as<int32_t>());
        }
        if(!r["annual_nominal_interest_rate"].isNull())
        {
            annualNominalInterestRate_=std::make_shared<std::string>(r["annual_nominal_interest_rate"].as<std::string>());
        }
        if(!r["interest_method"].isNull())
        {
            interestMethod_=std::make_shared<int32_t>(r["interest_method"].as<int32_t>());
        }
        if(!r["interest_calculation_period_type"].isNull())
        {
            interestCalculationPeriodType_=std::make_shared<int32_t>(r["interest_calculation_period_type"].as<int32_t>());
        }
        if(!r["amortization_type"].isNull())
        {
            amortizationType_=std::make_shared<int32_t>(r["amortization_type"].as<int32_t>());
        }
        if(!r["transaction_processing_strategy"].isNull())
        {
            transactionProcessingStrategy_=std::make_shared<std::string>(r["transaction_processing_strategy"].as<std::string>());
        }
        if(!r["days_in_year_type"].isNull())
        {
            daysInYearType_=std::make_shared<int32_t>(r["days_in_year_type"].as<int32_t>());
        }
        if(!r["days_in_month_type"].isNull())
        {
            daysInMonthType_=std::make_shared<int32_t>(r["days_in_month_type"].as<int32_t>());
        }
        if(!r["grace_on_principal_payment"].isNull())
        {
            graceOnPrincipalPayment_=std::make_shared<int32_t>(r["grace_on_principal_payment"].as<int32_t>());
        }
        if(!r["grace_on_interest_payment"].isNull())
        {
            graceOnInterestPayment_=std::make_shared<int32_t>(r["grace_on_interest_payment"].as<int32_t>());
        }
        if(!r["grace_on_interest_charged"].isNull())
        {
            graceOnInterestCharged_=std::make_shared<int32_t>(r["grace_on_interest_charged"].as<int32_t>());
        }
        if(!r["grace_on_arrears_ageing"].isNull())
        {
            graceOnArrearsAgeing_=std::make_shared<int32_t>(r["grace_on_arrears_ageing"].as<int32_t>());
        }
        if(!r["is_equal_amortization"].isNull())
        {
            isEqualAmortization_=std::make_shared<bool>(r["is_equal_amortization"].as<bool>());
        }
        if(!r["is_floating_interest_rate"].isNull())
        {
            isFloatingInterestRate_=std::make_shared<bool>(r["is_floating_interest_rate"].as<bool>());
        }
        if(!r["floating_rate_id"].isNull())
        {
            floatingRateId_=std::make_shared<std::string>(r["floating_rate_id"].as<std::string>());
        }
        if(!r["interest_rate_differential"].isNull())
        {
            interestRateDifferential_=std::make_shared<std::string>(r["interest_rate_differential"].as<std::string>());
        }
        if(!r["submitted_on_date"].isNull())
        {
            auto daysStr = r["submitted_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["submitted_by"].isNull())
        {
            submittedBy_=std::make_shared<std::string>(r["submitted_by"].as<std::string>());
        }
        if(!r["approved_on_date"].isNull())
        {
            auto daysStr = r["approved_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            approvedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["approved_by"].isNull())
        {
            approvedBy_=std::make_shared<std::string>(r["approved_by"].as<std::string>());
        }
        if(!r["expected_disbursement_date"].isNull())
        {
            auto daysStr = r["expected_disbursement_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedDisbursementDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["actual_disbursement_date"].isNull())
        {
            auto daysStr = r["actual_disbursement_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            actualDisbursementDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["disbursed_by"].isNull())
        {
            disbursedBy_=std::make_shared<std::string>(r["disbursed_by"].as<std::string>());
        }
        if(!r["expected_first_repayment_on_date"].isNull())
        {
            auto daysStr = r["expected_first_repayment_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedFirstRepaymentOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["interest_charged_from_date"].isNull())
        {
            auto daysStr = r["interest_charged_from_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            interestChargedFromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["expected_maturity_date"].isNull())
        {
            auto daysStr = r["expected_maturity_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedMaturityDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["maturity_date"].isNull())
        {
            auto daysStr = r["maturity_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            maturityDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["closed_on_date"].isNull())
        {
            auto daysStr = r["closed_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["closed_by"].isNull())
        {
            closedBy_=std::make_shared<std::string>(r["closed_by"].as<std::string>());
        }
        if(!r["rejected_on_date"].isNull())
        {
            auto daysStr = r["rejected_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rejectedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["withdrawn_on_date"].isNull())
        {
            auto daysStr = r["withdrawn_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            withdrawnOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["writtenoff_on_date"].isNull())
        {
            auto daysStr = r["writtenoff_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            writtenoffOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["sub_status"].isNull())
        {
            subStatus_=std::make_shared<int32_t>(r["sub_status"].as<int32_t>());
        }
        if(!r["is_npa"].isNull())
        {
            isNpa_=std::make_shared<bool>(r["is_npa"].as<bool>());
        }
        if(!r["delinquency_range_id"].isNull())
        {
            delinquencyRangeId_=std::make_shared<std::string>(r["delinquency_range_id"].as<std::string>());
        }
        if(!r["overdue_since_date"].isNull())
        {
            auto daysStr = r["overdue_since_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            overdueSinceDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["principal_disbursed"].isNull())
        {
            principalDisbursed_=std::make_shared<std::string>(r["principal_disbursed"].as<std::string>());
        }
        if(!r["principal_paid"].isNull())
        {
            principalPaid_=std::make_shared<std::string>(r["principal_paid"].as<std::string>());
        }
        if(!r["principal_writtenoff"].isNull())
        {
            principalWrittenoff_=std::make_shared<std::string>(r["principal_writtenoff"].as<std::string>());
        }
        if(!r["interest_charged"].isNull())
        {
            interestCharged_=std::make_shared<std::string>(r["interest_charged"].as<std::string>());
        }
        if(!r["interest_paid"].isNull())
        {
            interestPaid_=std::make_shared<std::string>(r["interest_paid"].as<std::string>());
        }
        if(!r["interest_waived"].isNull())
        {
            interestWaived_=std::make_shared<std::string>(r["interest_waived"].as<std::string>());
        }
        if(!r["interest_writtenoff"].isNull())
        {
            interestWrittenoff_=std::make_shared<std::string>(r["interest_writtenoff"].as<std::string>());
        }
        if(!r["fee_charges_charged"].isNull())
        {
            feeChargesCharged_=std::make_shared<std::string>(r["fee_charges_charged"].as<std::string>());
        }
        if(!r["fee_charges_paid"].isNull())
        {
            feeChargesPaid_=std::make_shared<std::string>(r["fee_charges_paid"].as<std::string>());
        }
        if(!r["fee_charges_waived"].isNull())
        {
            feeChargesWaived_=std::make_shared<std::string>(r["fee_charges_waived"].as<std::string>());
        }
        if(!r["fee_charges_writtenoff"].isNull())
        {
            feeChargesWrittenoff_=std::make_shared<std::string>(r["fee_charges_writtenoff"].as<std::string>());
        }
        if(!r["penalty_charges_charged"].isNull())
        {
            penaltyChargesCharged_=std::make_shared<std::string>(r["penalty_charges_charged"].as<std::string>());
        }
        if(!r["penalty_charges_paid"].isNull())
        {
            penaltyChargesPaid_=std::make_shared<std::string>(r["penalty_charges_paid"].as<std::string>());
        }
        if(!r["penalty_charges_waived"].isNull())
        {
            penaltyChargesWaived_=std::make_shared<std::string>(r["penalty_charges_waived"].as<std::string>());
        }
        if(!r["penalty_charges_writtenoff"].isNull())
        {
            penaltyChargesWrittenoff_=std::make_shared<std::string>(r["penalty_charges_writtenoff"].as<std::string>());
        }
        if(!r["total_recovered"].isNull())
        {
            totalRecovered_=std::make_shared<std::string>(r["total_recovered"].as<std::string>());
        }
        if(!r["total_overpaid"].isNull())
        {
            totalOverpaid_=std::make_shared<std::string>(r["total_overpaid"].as<std::string>());
        }
        if(!r["buydown_fee_amount"].isNull())
        {
            buydownFeeAmount_=std::make_shared<std::string>(r["buydown_fee_amount"].as<std::string>());
        }
        if(!r["capitalized_income_amount"].isNull())
        {
            capitalizedIncomeAmount_=std::make_shared<std::string>(r["capitalized_income_amount"].as<std::string>());
        }
        if(!r["glim_parent_loan_id"].isNull())
        {
            glimParentLoanId_=std::make_shared<std::string>(r["glim_parent_loan_id"].as<std::string>());
        }
        if(!r["created_at"].isNull())
        {
            auto timeStr = r["created_at"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["updated_at"].isNull())
        {
            auto timeStr = r["updated_at"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 78 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            accountNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            groupId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            productId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            loanOfficerId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            fundId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            loanPurpose_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            loanType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            currencyDigits_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            principalAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            approvedPrincipal_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            netDisbursalAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            numberOfRepayments_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            repaymentEvery_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            repaymentFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            interestRatePerPeriod_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            interestPeriodFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            annualNominalInterestRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 21;
        if(!r[index].isNull())
        {
            interestMethod_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            interestCalculationPeriodType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            amortizationType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 24;
        if(!r[index].isNull())
        {
            transactionProcessingStrategy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 25;
        if(!r[index].isNull())
        {
            daysInYearType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 26;
        if(!r[index].isNull())
        {
            daysInMonthType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 27;
        if(!r[index].isNull())
        {
            graceOnPrincipalPayment_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 28;
        if(!r[index].isNull())
        {
            graceOnInterestPayment_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 29;
        if(!r[index].isNull())
        {
            graceOnInterestCharged_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 30;
        if(!r[index].isNull())
        {
            graceOnArrearsAgeing_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 31;
        if(!r[index].isNull())
        {
            isEqualAmortization_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 32;
        if(!r[index].isNull())
        {
            isFloatingInterestRate_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 33;
        if(!r[index].isNull())
        {
            floatingRateId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 34;
        if(!r[index].isNull())
        {
            interestRateDifferential_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 35;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 36;
        if(!r[index].isNull())
        {
            submittedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 37;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            approvedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 38;
        if(!r[index].isNull())
        {
            approvedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 39;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedDisbursementDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 40;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            actualDisbursementDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 41;
        if(!r[index].isNull())
        {
            disbursedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 42;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedFirstRepaymentOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 43;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            interestChargedFromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 44;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedMaturityDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 45;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            maturityDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 46;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 47;
        if(!r[index].isNull())
        {
            closedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 48;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rejectedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 49;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            withdrawnOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 50;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            writtenoffOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 51;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 52;
        if(!r[index].isNull())
        {
            subStatus_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 53;
        if(!r[index].isNull())
        {
            isNpa_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 54;
        if(!r[index].isNull())
        {
            delinquencyRangeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 55;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            overdueSinceDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 56;
        if(!r[index].isNull())
        {
            principalDisbursed_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 57;
        if(!r[index].isNull())
        {
            principalPaid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 58;
        if(!r[index].isNull())
        {
            principalWrittenoff_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 59;
        if(!r[index].isNull())
        {
            interestCharged_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 60;
        if(!r[index].isNull())
        {
            interestPaid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 61;
        if(!r[index].isNull())
        {
            interestWaived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 62;
        if(!r[index].isNull())
        {
            interestWrittenoff_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 63;
        if(!r[index].isNull())
        {
            feeChargesCharged_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 64;
        if(!r[index].isNull())
        {
            feeChargesPaid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 65;
        if(!r[index].isNull())
        {
            feeChargesWaived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 66;
        if(!r[index].isNull())
        {
            feeChargesWrittenoff_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 67;
        if(!r[index].isNull())
        {
            penaltyChargesCharged_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 68;
        if(!r[index].isNull())
        {
            penaltyChargesPaid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 69;
        if(!r[index].isNull())
        {
            penaltyChargesWaived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 70;
        if(!r[index].isNull())
        {
            penaltyChargesWrittenoff_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 71;
        if(!r[index].isNull())
        {
            totalRecovered_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 72;
        if(!r[index].isNull())
        {
            totalOverpaid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 73;
        if(!r[index].isNull())
        {
            buydownFeeAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 74;
        if(!r[index].isNull())
        {
            capitalizedIncomeAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 75;
        if(!r[index].isNull())
        {
            glimParentLoanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 76;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 77;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &Loan::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getId() const noexcept
{
    return id_;
}
void Loan::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Loan::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Loan::PrimaryKeyType & Loan::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Loan::getValueOfAccountNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountNo_)
        return *accountNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getAccountNo() const noexcept
{
    return accountNo_;
}
void Loan::setAccountNo(const std::string &pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(pAccountNo);
    dirtyFlag_[1] = true;
}
void Loan::setAccountNo(std::string &&pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(std::move(pAccountNo));
    dirtyFlag_[1] = true;
}

const std::string &Loan::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getExternalId() const noexcept
{
    return externalId_;
}
void Loan::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[2] = true;
}
void Loan::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[2] = true;
}
void Loan::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &Loan::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getClientId() const noexcept
{
    return clientId_;
}
void Loan::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[3] = true;
}
void Loan::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[3] = true;
}
void Loan::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[3] = true;
}

const std::string &Loan::getValueOfGroupId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(groupId_)
        return *groupId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getGroupId() const noexcept
{
    return groupId_;
}
void Loan::setGroupId(const std::string &pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(pGroupId);
    dirtyFlag_[4] = true;
}
void Loan::setGroupId(std::string &&pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(std::move(pGroupId));
    dirtyFlag_[4] = true;
}
void Loan::setGroupIdToNull() noexcept
{
    groupId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &Loan::getValueOfProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(productId_)
        return *productId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getProductId() const noexcept
{
    return productId_;
}
void Loan::setProductId(const std::string &pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(pProductId);
    dirtyFlag_[5] = true;
}
void Loan::setProductId(std::string &&pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(std::move(pProductId));
    dirtyFlag_[5] = true;
}

const std::string &Loan::getValueOfLoanOfficerId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanOfficerId_)
        return *loanOfficerId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getLoanOfficerId() const noexcept
{
    return loanOfficerId_;
}
void Loan::setLoanOfficerId(const std::string &pLoanOfficerId) noexcept
{
    loanOfficerId_ = std::make_shared<std::string>(pLoanOfficerId);
    dirtyFlag_[6] = true;
}
void Loan::setLoanOfficerId(std::string &&pLoanOfficerId) noexcept
{
    loanOfficerId_ = std::make_shared<std::string>(std::move(pLoanOfficerId));
    dirtyFlag_[6] = true;
}
void Loan::setLoanOfficerIdToNull() noexcept
{
    loanOfficerId_.reset();
    dirtyFlag_[6] = true;
}

const std::string &Loan::getValueOfFundId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fundId_)
        return *fundId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getFundId() const noexcept
{
    return fundId_;
}
void Loan::setFundId(const std::string &pFundId) noexcept
{
    fundId_ = std::make_shared<std::string>(pFundId);
    dirtyFlag_[7] = true;
}
void Loan::setFundId(std::string &&pFundId) noexcept
{
    fundId_ = std::make_shared<std::string>(std::move(pFundId));
    dirtyFlag_[7] = true;
}
void Loan::setFundIdToNull() noexcept
{
    fundId_.reset();
    dirtyFlag_[7] = true;
}

const std::string &Loan::getValueOfLoanPurpose() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanPurpose_)
        return *loanPurpose_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getLoanPurpose() const noexcept
{
    return loanPurpose_;
}
void Loan::setLoanPurpose(const std::string &pLoanPurpose) noexcept
{
    loanPurpose_ = std::make_shared<std::string>(pLoanPurpose);
    dirtyFlag_[8] = true;
}
void Loan::setLoanPurpose(std::string &&pLoanPurpose) noexcept
{
    loanPurpose_ = std::make_shared<std::string>(std::move(pLoanPurpose));
    dirtyFlag_[8] = true;
}
void Loan::setLoanPurposeToNull() noexcept
{
    loanPurpose_.reset();
    dirtyFlag_[8] = true;
}

const int32_t &Loan::getValueOfLoanType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(loanType_)
        return *loanType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getLoanType() const noexcept
{
    return loanType_;
}
void Loan::setLoanType(const int32_t &pLoanType) noexcept
{
    loanType_ = std::make_shared<int32_t>(pLoanType);
    dirtyFlag_[9] = true;
}

const std::string &Loan::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void Loan::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[10] = true;
}
void Loan::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[10] = true;
}

const int32_t &Loan::getValueOfCurrencyDigits() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(currencyDigits_)
        return *currencyDigits_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getCurrencyDigits() const noexcept
{
    return currencyDigits_;
}
void Loan::setCurrencyDigits(const int32_t &pCurrencyDigits) noexcept
{
    currencyDigits_ = std::make_shared<int32_t>(pCurrencyDigits);
    dirtyFlag_[11] = true;
}

const std::string &Loan::getValueOfPrincipalAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalAmount_)
        return *principalAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPrincipalAmount() const noexcept
{
    return principalAmount_;
}
void Loan::setPrincipalAmount(const std::string &pPrincipalAmount) noexcept
{
    principalAmount_ = std::make_shared<std::string>(pPrincipalAmount);
    dirtyFlag_[12] = true;
}
void Loan::setPrincipalAmount(std::string &&pPrincipalAmount) noexcept
{
    principalAmount_ = std::make_shared<std::string>(std::move(pPrincipalAmount));
    dirtyFlag_[12] = true;
}

const std::string &Loan::getValueOfApprovedPrincipal() const noexcept
{
    static const std::string defaultValue = std::string();
    if(approvedPrincipal_)
        return *approvedPrincipal_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getApprovedPrincipal() const noexcept
{
    return approvedPrincipal_;
}
void Loan::setApprovedPrincipal(const std::string &pApprovedPrincipal) noexcept
{
    approvedPrincipal_ = std::make_shared<std::string>(pApprovedPrincipal);
    dirtyFlag_[13] = true;
}
void Loan::setApprovedPrincipal(std::string &&pApprovedPrincipal) noexcept
{
    approvedPrincipal_ = std::make_shared<std::string>(std::move(pApprovedPrincipal));
    dirtyFlag_[13] = true;
}
void Loan::setApprovedPrincipalToNull() noexcept
{
    approvedPrincipal_.reset();
    dirtyFlag_[13] = true;
}

const std::string &Loan::getValueOfNetDisbursalAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(netDisbursalAmount_)
        return *netDisbursalAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getNetDisbursalAmount() const noexcept
{
    return netDisbursalAmount_;
}
void Loan::setNetDisbursalAmount(const std::string &pNetDisbursalAmount) noexcept
{
    netDisbursalAmount_ = std::make_shared<std::string>(pNetDisbursalAmount);
    dirtyFlag_[14] = true;
}
void Loan::setNetDisbursalAmount(std::string &&pNetDisbursalAmount) noexcept
{
    netDisbursalAmount_ = std::make_shared<std::string>(std::move(pNetDisbursalAmount));
    dirtyFlag_[14] = true;
}
void Loan::setNetDisbursalAmountToNull() noexcept
{
    netDisbursalAmount_.reset();
    dirtyFlag_[14] = true;
}

const int32_t &Loan::getValueOfNumberOfRepayments() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(numberOfRepayments_)
        return *numberOfRepayments_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getNumberOfRepayments() const noexcept
{
    return numberOfRepayments_;
}
void Loan::setNumberOfRepayments(const int32_t &pNumberOfRepayments) noexcept
{
    numberOfRepayments_ = std::make_shared<int32_t>(pNumberOfRepayments);
    dirtyFlag_[15] = true;
}

const int32_t &Loan::getValueOfRepaymentEvery() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(repaymentEvery_)
        return *repaymentEvery_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getRepaymentEvery() const noexcept
{
    return repaymentEvery_;
}
void Loan::setRepaymentEvery(const int32_t &pRepaymentEvery) noexcept
{
    repaymentEvery_ = std::make_shared<int32_t>(pRepaymentEvery);
    dirtyFlag_[16] = true;
}

const int32_t &Loan::getValueOfRepaymentFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(repaymentFrequencyType_)
        return *repaymentFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getRepaymentFrequencyType() const noexcept
{
    return repaymentFrequencyType_;
}
void Loan::setRepaymentFrequencyType(const int32_t &pRepaymentFrequencyType) noexcept
{
    repaymentFrequencyType_ = std::make_shared<int32_t>(pRepaymentFrequencyType);
    dirtyFlag_[17] = true;
}

const std::string &Loan::getValueOfInterestRatePerPeriod() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestRatePerPeriod_)
        return *interestRatePerPeriod_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getInterestRatePerPeriod() const noexcept
{
    return interestRatePerPeriod_;
}
void Loan::setInterestRatePerPeriod(const std::string &pInterestRatePerPeriod) noexcept
{
    interestRatePerPeriod_ = std::make_shared<std::string>(pInterestRatePerPeriod);
    dirtyFlag_[18] = true;
}
void Loan::setInterestRatePerPeriod(std::string &&pInterestRatePerPeriod) noexcept
{
    interestRatePerPeriod_ = std::make_shared<std::string>(std::move(pInterestRatePerPeriod));
    dirtyFlag_[18] = true;
}

const int32_t &Loan::getValueOfInterestPeriodFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestPeriodFrequencyType_)
        return *interestPeriodFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getInterestPeriodFrequencyType() const noexcept
{
    return interestPeriodFrequencyType_;
}
void Loan::setInterestPeriodFrequencyType(const int32_t &pInterestPeriodFrequencyType) noexcept
{
    interestPeriodFrequencyType_ = std::make_shared<int32_t>(pInterestPeriodFrequencyType);
    dirtyFlag_[19] = true;
}

const std::string &Loan::getValueOfAnnualNominalInterestRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(annualNominalInterestRate_)
        return *annualNominalInterestRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getAnnualNominalInterestRate() const noexcept
{
    return annualNominalInterestRate_;
}
void Loan::setAnnualNominalInterestRate(const std::string &pAnnualNominalInterestRate) noexcept
{
    annualNominalInterestRate_ = std::make_shared<std::string>(pAnnualNominalInterestRate);
    dirtyFlag_[20] = true;
}
void Loan::setAnnualNominalInterestRate(std::string &&pAnnualNominalInterestRate) noexcept
{
    annualNominalInterestRate_ = std::make_shared<std::string>(std::move(pAnnualNominalInterestRate));
    dirtyFlag_[20] = true;
}

const int32_t &Loan::getValueOfInterestMethod() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestMethod_)
        return *interestMethod_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getInterestMethod() const noexcept
{
    return interestMethod_;
}
void Loan::setInterestMethod(const int32_t &pInterestMethod) noexcept
{
    interestMethod_ = std::make_shared<int32_t>(pInterestMethod);
    dirtyFlag_[21] = true;
}

const int32_t &Loan::getValueOfInterestCalculationPeriodType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCalculationPeriodType_)
        return *interestCalculationPeriodType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getInterestCalculationPeriodType() const noexcept
{
    return interestCalculationPeriodType_;
}
void Loan::setInterestCalculationPeriodType(const int32_t &pInterestCalculationPeriodType) noexcept
{
    interestCalculationPeriodType_ = std::make_shared<int32_t>(pInterestCalculationPeriodType);
    dirtyFlag_[22] = true;
}

const int32_t &Loan::getValueOfAmortizationType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(amortizationType_)
        return *amortizationType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getAmortizationType() const noexcept
{
    return amortizationType_;
}
void Loan::setAmortizationType(const int32_t &pAmortizationType) noexcept
{
    amortizationType_ = std::make_shared<int32_t>(pAmortizationType);
    dirtyFlag_[23] = true;
}

const std::string &Loan::getValueOfTransactionProcessingStrategy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transactionProcessingStrategy_)
        return *transactionProcessingStrategy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getTransactionProcessingStrategy() const noexcept
{
    return transactionProcessingStrategy_;
}
void Loan::setTransactionProcessingStrategy(const std::string &pTransactionProcessingStrategy) noexcept
{
    transactionProcessingStrategy_ = std::make_shared<std::string>(pTransactionProcessingStrategy);
    dirtyFlag_[24] = true;
}
void Loan::setTransactionProcessingStrategy(std::string &&pTransactionProcessingStrategy) noexcept
{
    transactionProcessingStrategy_ = std::make_shared<std::string>(std::move(pTransactionProcessingStrategy));
    dirtyFlag_[24] = true;
}

const int32_t &Loan::getValueOfDaysInYearType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(daysInYearType_)
        return *daysInYearType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getDaysInYearType() const noexcept
{
    return daysInYearType_;
}
void Loan::setDaysInYearType(const int32_t &pDaysInYearType) noexcept
{
    daysInYearType_ = std::make_shared<int32_t>(pDaysInYearType);
    dirtyFlag_[25] = true;
}

const int32_t &Loan::getValueOfDaysInMonthType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(daysInMonthType_)
        return *daysInMonthType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getDaysInMonthType() const noexcept
{
    return daysInMonthType_;
}
void Loan::setDaysInMonthType(const int32_t &pDaysInMonthType) noexcept
{
    daysInMonthType_ = std::make_shared<int32_t>(pDaysInMonthType);
    dirtyFlag_[26] = true;
}

const int32_t &Loan::getValueOfGraceOnPrincipalPayment() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnPrincipalPayment_)
        return *graceOnPrincipalPayment_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getGraceOnPrincipalPayment() const noexcept
{
    return graceOnPrincipalPayment_;
}
void Loan::setGraceOnPrincipalPayment(const int32_t &pGraceOnPrincipalPayment) noexcept
{
    graceOnPrincipalPayment_ = std::make_shared<int32_t>(pGraceOnPrincipalPayment);
    dirtyFlag_[27] = true;
}

const int32_t &Loan::getValueOfGraceOnInterestPayment() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnInterestPayment_)
        return *graceOnInterestPayment_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getGraceOnInterestPayment() const noexcept
{
    return graceOnInterestPayment_;
}
void Loan::setGraceOnInterestPayment(const int32_t &pGraceOnInterestPayment) noexcept
{
    graceOnInterestPayment_ = std::make_shared<int32_t>(pGraceOnInterestPayment);
    dirtyFlag_[28] = true;
}

const int32_t &Loan::getValueOfGraceOnInterestCharged() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnInterestCharged_)
        return *graceOnInterestCharged_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getGraceOnInterestCharged() const noexcept
{
    return graceOnInterestCharged_;
}
void Loan::setGraceOnInterestCharged(const int32_t &pGraceOnInterestCharged) noexcept
{
    graceOnInterestCharged_ = std::make_shared<int32_t>(pGraceOnInterestCharged);
    dirtyFlag_[29] = true;
}

const int32_t &Loan::getValueOfGraceOnArrearsAgeing() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnArrearsAgeing_)
        return *graceOnArrearsAgeing_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getGraceOnArrearsAgeing() const noexcept
{
    return graceOnArrearsAgeing_;
}
void Loan::setGraceOnArrearsAgeing(const int32_t &pGraceOnArrearsAgeing) noexcept
{
    graceOnArrearsAgeing_ = std::make_shared<int32_t>(pGraceOnArrearsAgeing);
    dirtyFlag_[30] = true;
}

const bool &Loan::getValueOfIsEqualAmortization() const noexcept
{
    static const bool defaultValue = bool();
    if(isEqualAmortization_)
        return *isEqualAmortization_;
    return defaultValue;
}
const std::shared_ptr<bool> &Loan::getIsEqualAmortization() const noexcept
{
    return isEqualAmortization_;
}
void Loan::setIsEqualAmortization(const bool &pIsEqualAmortization) noexcept
{
    isEqualAmortization_ = std::make_shared<bool>(pIsEqualAmortization);
    dirtyFlag_[31] = true;
}

const bool &Loan::getValueOfIsFloatingInterestRate() const noexcept
{
    static const bool defaultValue = bool();
    if(isFloatingInterestRate_)
        return *isFloatingInterestRate_;
    return defaultValue;
}
const std::shared_ptr<bool> &Loan::getIsFloatingInterestRate() const noexcept
{
    return isFloatingInterestRate_;
}
void Loan::setIsFloatingInterestRate(const bool &pIsFloatingInterestRate) noexcept
{
    isFloatingInterestRate_ = std::make_shared<bool>(pIsFloatingInterestRate);
    dirtyFlag_[32] = true;
}

const std::string &Loan::getValueOfFloatingRateId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(floatingRateId_)
        return *floatingRateId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getFloatingRateId() const noexcept
{
    return floatingRateId_;
}
void Loan::setFloatingRateId(const std::string &pFloatingRateId) noexcept
{
    floatingRateId_ = std::make_shared<std::string>(pFloatingRateId);
    dirtyFlag_[33] = true;
}
void Loan::setFloatingRateId(std::string &&pFloatingRateId) noexcept
{
    floatingRateId_ = std::make_shared<std::string>(std::move(pFloatingRateId));
    dirtyFlag_[33] = true;
}
void Loan::setFloatingRateIdToNull() noexcept
{
    floatingRateId_.reset();
    dirtyFlag_[33] = true;
}

const std::string &Loan::getValueOfInterestRateDifferential() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestRateDifferential_)
        return *interestRateDifferential_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getInterestRateDifferential() const noexcept
{
    return interestRateDifferential_;
}
void Loan::setInterestRateDifferential(const std::string &pInterestRateDifferential) noexcept
{
    interestRateDifferential_ = std::make_shared<std::string>(pInterestRateDifferential);
    dirtyFlag_[34] = true;
}
void Loan::setInterestRateDifferential(std::string &&pInterestRateDifferential) noexcept
{
    interestRateDifferential_ = std::make_shared<std::string>(std::move(pInterestRateDifferential));
    dirtyFlag_[34] = true;
}
void Loan::setInterestRateDifferentialToNull() noexcept
{
    interestRateDifferential_.reset();
    dirtyFlag_[34] = true;
}

const ::trantor::Date &Loan::getValueOfSubmittedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedOnDate_)
        return *submittedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getSubmittedOnDate() const noexcept
{
    return submittedOnDate_;
}
void Loan::setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept
{
    submittedOnDate_ = std::make_shared<::trantor::Date>(pSubmittedOnDate);
    dirtyFlag_[35] = true;
}

const std::string &Loan::getValueOfSubmittedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(submittedBy_)
        return *submittedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getSubmittedBy() const noexcept
{
    return submittedBy_;
}
void Loan::setSubmittedBy(const std::string &pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(pSubmittedBy);
    dirtyFlag_[36] = true;
}
void Loan::setSubmittedBy(std::string &&pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(std::move(pSubmittedBy));
    dirtyFlag_[36] = true;
}
void Loan::setSubmittedByToNull() noexcept
{
    submittedBy_.reset();
    dirtyFlag_[36] = true;
}

const ::trantor::Date &Loan::getValueOfApprovedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(approvedOnDate_)
        return *approvedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getApprovedOnDate() const noexcept
{
    return approvedOnDate_;
}
void Loan::setApprovedOnDate(const ::trantor::Date &pApprovedOnDate) noexcept
{
    approvedOnDate_ = std::make_shared<::trantor::Date>(pApprovedOnDate);
    dirtyFlag_[37] = true;
}
void Loan::setApprovedOnDateToNull() noexcept
{
    approvedOnDate_.reset();
    dirtyFlag_[37] = true;
}

const std::string &Loan::getValueOfApprovedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(approvedBy_)
        return *approvedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getApprovedBy() const noexcept
{
    return approvedBy_;
}
void Loan::setApprovedBy(const std::string &pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(pApprovedBy);
    dirtyFlag_[38] = true;
}
void Loan::setApprovedBy(std::string &&pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(std::move(pApprovedBy));
    dirtyFlag_[38] = true;
}
void Loan::setApprovedByToNull() noexcept
{
    approvedBy_.reset();
    dirtyFlag_[38] = true;
}

const ::trantor::Date &Loan::getValueOfExpectedDisbursementDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(expectedDisbursementDate_)
        return *expectedDisbursementDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getExpectedDisbursementDate() const noexcept
{
    return expectedDisbursementDate_;
}
void Loan::setExpectedDisbursementDate(const ::trantor::Date &pExpectedDisbursementDate) noexcept
{
    expectedDisbursementDate_ = std::make_shared<::trantor::Date>(pExpectedDisbursementDate);
    dirtyFlag_[39] = true;
}
void Loan::setExpectedDisbursementDateToNull() noexcept
{
    expectedDisbursementDate_.reset();
    dirtyFlag_[39] = true;
}

const ::trantor::Date &Loan::getValueOfActualDisbursementDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(actualDisbursementDate_)
        return *actualDisbursementDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getActualDisbursementDate() const noexcept
{
    return actualDisbursementDate_;
}
void Loan::setActualDisbursementDate(const ::trantor::Date &pActualDisbursementDate) noexcept
{
    actualDisbursementDate_ = std::make_shared<::trantor::Date>(pActualDisbursementDate);
    dirtyFlag_[40] = true;
}
void Loan::setActualDisbursementDateToNull() noexcept
{
    actualDisbursementDate_.reset();
    dirtyFlag_[40] = true;
}

const std::string &Loan::getValueOfDisbursedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(disbursedBy_)
        return *disbursedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getDisbursedBy() const noexcept
{
    return disbursedBy_;
}
void Loan::setDisbursedBy(const std::string &pDisbursedBy) noexcept
{
    disbursedBy_ = std::make_shared<std::string>(pDisbursedBy);
    dirtyFlag_[41] = true;
}
void Loan::setDisbursedBy(std::string &&pDisbursedBy) noexcept
{
    disbursedBy_ = std::make_shared<std::string>(std::move(pDisbursedBy));
    dirtyFlag_[41] = true;
}
void Loan::setDisbursedByToNull() noexcept
{
    disbursedBy_.reset();
    dirtyFlag_[41] = true;
}

const ::trantor::Date &Loan::getValueOfExpectedFirstRepaymentOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(expectedFirstRepaymentOnDate_)
        return *expectedFirstRepaymentOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getExpectedFirstRepaymentOnDate() const noexcept
{
    return expectedFirstRepaymentOnDate_;
}
void Loan::setExpectedFirstRepaymentOnDate(const ::trantor::Date &pExpectedFirstRepaymentOnDate) noexcept
{
    expectedFirstRepaymentOnDate_ = std::make_shared<::trantor::Date>(pExpectedFirstRepaymentOnDate);
    dirtyFlag_[42] = true;
}
void Loan::setExpectedFirstRepaymentOnDateToNull() noexcept
{
    expectedFirstRepaymentOnDate_.reset();
    dirtyFlag_[42] = true;
}

const ::trantor::Date &Loan::getValueOfInterestChargedFromDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(interestChargedFromDate_)
        return *interestChargedFromDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getInterestChargedFromDate() const noexcept
{
    return interestChargedFromDate_;
}
void Loan::setInterestChargedFromDate(const ::trantor::Date &pInterestChargedFromDate) noexcept
{
    interestChargedFromDate_ = std::make_shared<::trantor::Date>(pInterestChargedFromDate);
    dirtyFlag_[43] = true;
}
void Loan::setInterestChargedFromDateToNull() noexcept
{
    interestChargedFromDate_.reset();
    dirtyFlag_[43] = true;
}

const ::trantor::Date &Loan::getValueOfExpectedMaturityDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(expectedMaturityDate_)
        return *expectedMaturityDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getExpectedMaturityDate() const noexcept
{
    return expectedMaturityDate_;
}
void Loan::setExpectedMaturityDate(const ::trantor::Date &pExpectedMaturityDate) noexcept
{
    expectedMaturityDate_ = std::make_shared<::trantor::Date>(pExpectedMaturityDate);
    dirtyFlag_[44] = true;
}
void Loan::setExpectedMaturityDateToNull() noexcept
{
    expectedMaturityDate_.reset();
    dirtyFlag_[44] = true;
}

const ::trantor::Date &Loan::getValueOfMaturityDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(maturityDate_)
        return *maturityDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getMaturityDate() const noexcept
{
    return maturityDate_;
}
void Loan::setMaturityDate(const ::trantor::Date &pMaturityDate) noexcept
{
    maturityDate_ = std::make_shared<::trantor::Date>(pMaturityDate);
    dirtyFlag_[45] = true;
}
void Loan::setMaturityDateToNull() noexcept
{
    maturityDate_.reset();
    dirtyFlag_[45] = true;
}

const ::trantor::Date &Loan::getValueOfClosedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(closedOnDate_)
        return *closedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getClosedOnDate() const noexcept
{
    return closedOnDate_;
}
void Loan::setClosedOnDate(const ::trantor::Date &pClosedOnDate) noexcept
{
    closedOnDate_ = std::make_shared<::trantor::Date>(pClosedOnDate);
    dirtyFlag_[46] = true;
}
void Loan::setClosedOnDateToNull() noexcept
{
    closedOnDate_.reset();
    dirtyFlag_[46] = true;
}

const std::string &Loan::getValueOfClosedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(closedBy_)
        return *closedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getClosedBy() const noexcept
{
    return closedBy_;
}
void Loan::setClosedBy(const std::string &pClosedBy) noexcept
{
    closedBy_ = std::make_shared<std::string>(pClosedBy);
    dirtyFlag_[47] = true;
}
void Loan::setClosedBy(std::string &&pClosedBy) noexcept
{
    closedBy_ = std::make_shared<std::string>(std::move(pClosedBy));
    dirtyFlag_[47] = true;
}
void Loan::setClosedByToNull() noexcept
{
    closedBy_.reset();
    dirtyFlag_[47] = true;
}

const ::trantor::Date &Loan::getValueOfRejectedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(rejectedOnDate_)
        return *rejectedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getRejectedOnDate() const noexcept
{
    return rejectedOnDate_;
}
void Loan::setRejectedOnDate(const ::trantor::Date &pRejectedOnDate) noexcept
{
    rejectedOnDate_ = std::make_shared<::trantor::Date>(pRejectedOnDate);
    dirtyFlag_[48] = true;
}
void Loan::setRejectedOnDateToNull() noexcept
{
    rejectedOnDate_.reset();
    dirtyFlag_[48] = true;
}

const ::trantor::Date &Loan::getValueOfWithdrawnOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(withdrawnOnDate_)
        return *withdrawnOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getWithdrawnOnDate() const noexcept
{
    return withdrawnOnDate_;
}
void Loan::setWithdrawnOnDate(const ::trantor::Date &pWithdrawnOnDate) noexcept
{
    withdrawnOnDate_ = std::make_shared<::trantor::Date>(pWithdrawnOnDate);
    dirtyFlag_[49] = true;
}
void Loan::setWithdrawnOnDateToNull() noexcept
{
    withdrawnOnDate_.reset();
    dirtyFlag_[49] = true;
}

const ::trantor::Date &Loan::getValueOfWrittenoffOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(writtenoffOnDate_)
        return *writtenoffOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getWrittenoffOnDate() const noexcept
{
    return writtenoffOnDate_;
}
void Loan::setWrittenoffOnDate(const ::trantor::Date &pWrittenoffOnDate) noexcept
{
    writtenoffOnDate_ = std::make_shared<::trantor::Date>(pWrittenoffOnDate);
    dirtyFlag_[50] = true;
}
void Loan::setWrittenoffOnDateToNull() noexcept
{
    writtenoffOnDate_.reset();
    dirtyFlag_[50] = true;
}

const int32_t &Loan::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getStatus() const noexcept
{
    return status_;
}
void Loan::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[51] = true;
}

const int32_t &Loan::getValueOfSubStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(subStatus_)
        return *subStatus_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Loan::getSubStatus() const noexcept
{
    return subStatus_;
}
void Loan::setSubStatus(const int32_t &pSubStatus) noexcept
{
    subStatus_ = std::make_shared<int32_t>(pSubStatus);
    dirtyFlag_[52] = true;
}
void Loan::setSubStatusToNull() noexcept
{
    subStatus_.reset();
    dirtyFlag_[52] = true;
}

const bool &Loan::getValueOfIsNpa() const noexcept
{
    static const bool defaultValue = bool();
    if(isNpa_)
        return *isNpa_;
    return defaultValue;
}
const std::shared_ptr<bool> &Loan::getIsNpa() const noexcept
{
    return isNpa_;
}
void Loan::setIsNpa(const bool &pIsNpa) noexcept
{
    isNpa_ = std::make_shared<bool>(pIsNpa);
    dirtyFlag_[53] = true;
}

const std::string &Loan::getValueOfDelinquencyRangeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(delinquencyRangeId_)
        return *delinquencyRangeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getDelinquencyRangeId() const noexcept
{
    return delinquencyRangeId_;
}
void Loan::setDelinquencyRangeId(const std::string &pDelinquencyRangeId) noexcept
{
    delinquencyRangeId_ = std::make_shared<std::string>(pDelinquencyRangeId);
    dirtyFlag_[54] = true;
}
void Loan::setDelinquencyRangeId(std::string &&pDelinquencyRangeId) noexcept
{
    delinquencyRangeId_ = std::make_shared<std::string>(std::move(pDelinquencyRangeId));
    dirtyFlag_[54] = true;
}
void Loan::setDelinquencyRangeIdToNull() noexcept
{
    delinquencyRangeId_.reset();
    dirtyFlag_[54] = true;
}

const ::trantor::Date &Loan::getValueOfOverdueSinceDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(overdueSinceDate_)
        return *overdueSinceDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getOverdueSinceDate() const noexcept
{
    return overdueSinceDate_;
}
void Loan::setOverdueSinceDate(const ::trantor::Date &pOverdueSinceDate) noexcept
{
    overdueSinceDate_ = std::make_shared<::trantor::Date>(pOverdueSinceDate);
    dirtyFlag_[55] = true;
}
void Loan::setOverdueSinceDateToNull() noexcept
{
    overdueSinceDate_.reset();
    dirtyFlag_[55] = true;
}

const std::string &Loan::getValueOfPrincipalDisbursed() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalDisbursed_)
        return *principalDisbursed_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPrincipalDisbursed() const noexcept
{
    return principalDisbursed_;
}
void Loan::setPrincipalDisbursed(const std::string &pPrincipalDisbursed) noexcept
{
    principalDisbursed_ = std::make_shared<std::string>(pPrincipalDisbursed);
    dirtyFlag_[56] = true;
}
void Loan::setPrincipalDisbursed(std::string &&pPrincipalDisbursed) noexcept
{
    principalDisbursed_ = std::make_shared<std::string>(std::move(pPrincipalDisbursed));
    dirtyFlag_[56] = true;
}

const std::string &Loan::getValueOfPrincipalPaid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalPaid_)
        return *principalPaid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPrincipalPaid() const noexcept
{
    return principalPaid_;
}
void Loan::setPrincipalPaid(const std::string &pPrincipalPaid) noexcept
{
    principalPaid_ = std::make_shared<std::string>(pPrincipalPaid);
    dirtyFlag_[57] = true;
}
void Loan::setPrincipalPaid(std::string &&pPrincipalPaid) noexcept
{
    principalPaid_ = std::make_shared<std::string>(std::move(pPrincipalPaid));
    dirtyFlag_[57] = true;
}

const std::string &Loan::getValueOfPrincipalWrittenoff() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalWrittenoff_)
        return *principalWrittenoff_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPrincipalWrittenoff() const noexcept
{
    return principalWrittenoff_;
}
void Loan::setPrincipalWrittenoff(const std::string &pPrincipalWrittenoff) noexcept
{
    principalWrittenoff_ = std::make_shared<std::string>(pPrincipalWrittenoff);
    dirtyFlag_[58] = true;
}
void Loan::setPrincipalWrittenoff(std::string &&pPrincipalWrittenoff) noexcept
{
    principalWrittenoff_ = std::make_shared<std::string>(std::move(pPrincipalWrittenoff));
    dirtyFlag_[58] = true;
}

const std::string &Loan::getValueOfInterestCharged() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestCharged_)
        return *interestCharged_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getInterestCharged() const noexcept
{
    return interestCharged_;
}
void Loan::setInterestCharged(const std::string &pInterestCharged) noexcept
{
    interestCharged_ = std::make_shared<std::string>(pInterestCharged);
    dirtyFlag_[59] = true;
}
void Loan::setInterestCharged(std::string &&pInterestCharged) noexcept
{
    interestCharged_ = std::make_shared<std::string>(std::move(pInterestCharged));
    dirtyFlag_[59] = true;
}

const std::string &Loan::getValueOfInterestPaid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestPaid_)
        return *interestPaid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getInterestPaid() const noexcept
{
    return interestPaid_;
}
void Loan::setInterestPaid(const std::string &pInterestPaid) noexcept
{
    interestPaid_ = std::make_shared<std::string>(pInterestPaid);
    dirtyFlag_[60] = true;
}
void Loan::setInterestPaid(std::string &&pInterestPaid) noexcept
{
    interestPaid_ = std::make_shared<std::string>(std::move(pInterestPaid));
    dirtyFlag_[60] = true;
}

const std::string &Loan::getValueOfInterestWaived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestWaived_)
        return *interestWaived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getInterestWaived() const noexcept
{
    return interestWaived_;
}
void Loan::setInterestWaived(const std::string &pInterestWaived) noexcept
{
    interestWaived_ = std::make_shared<std::string>(pInterestWaived);
    dirtyFlag_[61] = true;
}
void Loan::setInterestWaived(std::string &&pInterestWaived) noexcept
{
    interestWaived_ = std::make_shared<std::string>(std::move(pInterestWaived));
    dirtyFlag_[61] = true;
}

const std::string &Loan::getValueOfInterestWrittenoff() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestWrittenoff_)
        return *interestWrittenoff_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getInterestWrittenoff() const noexcept
{
    return interestWrittenoff_;
}
void Loan::setInterestWrittenoff(const std::string &pInterestWrittenoff) noexcept
{
    interestWrittenoff_ = std::make_shared<std::string>(pInterestWrittenoff);
    dirtyFlag_[62] = true;
}
void Loan::setInterestWrittenoff(std::string &&pInterestWrittenoff) noexcept
{
    interestWrittenoff_ = std::make_shared<std::string>(std::move(pInterestWrittenoff));
    dirtyFlag_[62] = true;
}

const std::string &Loan::getValueOfFeeChargesCharged() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesCharged_)
        return *feeChargesCharged_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getFeeChargesCharged() const noexcept
{
    return feeChargesCharged_;
}
void Loan::setFeeChargesCharged(const std::string &pFeeChargesCharged) noexcept
{
    feeChargesCharged_ = std::make_shared<std::string>(pFeeChargesCharged);
    dirtyFlag_[63] = true;
}
void Loan::setFeeChargesCharged(std::string &&pFeeChargesCharged) noexcept
{
    feeChargesCharged_ = std::make_shared<std::string>(std::move(pFeeChargesCharged));
    dirtyFlag_[63] = true;
}

const std::string &Loan::getValueOfFeeChargesPaid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesPaid_)
        return *feeChargesPaid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getFeeChargesPaid() const noexcept
{
    return feeChargesPaid_;
}
void Loan::setFeeChargesPaid(const std::string &pFeeChargesPaid) noexcept
{
    feeChargesPaid_ = std::make_shared<std::string>(pFeeChargesPaid);
    dirtyFlag_[64] = true;
}
void Loan::setFeeChargesPaid(std::string &&pFeeChargesPaid) noexcept
{
    feeChargesPaid_ = std::make_shared<std::string>(std::move(pFeeChargesPaid));
    dirtyFlag_[64] = true;
}

const std::string &Loan::getValueOfFeeChargesWaived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesWaived_)
        return *feeChargesWaived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getFeeChargesWaived() const noexcept
{
    return feeChargesWaived_;
}
void Loan::setFeeChargesWaived(const std::string &pFeeChargesWaived) noexcept
{
    feeChargesWaived_ = std::make_shared<std::string>(pFeeChargesWaived);
    dirtyFlag_[65] = true;
}
void Loan::setFeeChargesWaived(std::string &&pFeeChargesWaived) noexcept
{
    feeChargesWaived_ = std::make_shared<std::string>(std::move(pFeeChargesWaived));
    dirtyFlag_[65] = true;
}

const std::string &Loan::getValueOfFeeChargesWrittenoff() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesWrittenoff_)
        return *feeChargesWrittenoff_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getFeeChargesWrittenoff() const noexcept
{
    return feeChargesWrittenoff_;
}
void Loan::setFeeChargesWrittenoff(const std::string &pFeeChargesWrittenoff) noexcept
{
    feeChargesWrittenoff_ = std::make_shared<std::string>(pFeeChargesWrittenoff);
    dirtyFlag_[66] = true;
}
void Loan::setFeeChargesWrittenoff(std::string &&pFeeChargesWrittenoff) noexcept
{
    feeChargesWrittenoff_ = std::make_shared<std::string>(std::move(pFeeChargesWrittenoff));
    dirtyFlag_[66] = true;
}

const std::string &Loan::getValueOfPenaltyChargesCharged() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesCharged_)
        return *penaltyChargesCharged_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPenaltyChargesCharged() const noexcept
{
    return penaltyChargesCharged_;
}
void Loan::setPenaltyChargesCharged(const std::string &pPenaltyChargesCharged) noexcept
{
    penaltyChargesCharged_ = std::make_shared<std::string>(pPenaltyChargesCharged);
    dirtyFlag_[67] = true;
}
void Loan::setPenaltyChargesCharged(std::string &&pPenaltyChargesCharged) noexcept
{
    penaltyChargesCharged_ = std::make_shared<std::string>(std::move(pPenaltyChargesCharged));
    dirtyFlag_[67] = true;
}

const std::string &Loan::getValueOfPenaltyChargesPaid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesPaid_)
        return *penaltyChargesPaid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPenaltyChargesPaid() const noexcept
{
    return penaltyChargesPaid_;
}
void Loan::setPenaltyChargesPaid(const std::string &pPenaltyChargesPaid) noexcept
{
    penaltyChargesPaid_ = std::make_shared<std::string>(pPenaltyChargesPaid);
    dirtyFlag_[68] = true;
}
void Loan::setPenaltyChargesPaid(std::string &&pPenaltyChargesPaid) noexcept
{
    penaltyChargesPaid_ = std::make_shared<std::string>(std::move(pPenaltyChargesPaid));
    dirtyFlag_[68] = true;
}

const std::string &Loan::getValueOfPenaltyChargesWaived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesWaived_)
        return *penaltyChargesWaived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPenaltyChargesWaived() const noexcept
{
    return penaltyChargesWaived_;
}
void Loan::setPenaltyChargesWaived(const std::string &pPenaltyChargesWaived) noexcept
{
    penaltyChargesWaived_ = std::make_shared<std::string>(pPenaltyChargesWaived);
    dirtyFlag_[69] = true;
}
void Loan::setPenaltyChargesWaived(std::string &&pPenaltyChargesWaived) noexcept
{
    penaltyChargesWaived_ = std::make_shared<std::string>(std::move(pPenaltyChargesWaived));
    dirtyFlag_[69] = true;
}

const std::string &Loan::getValueOfPenaltyChargesWrittenoff() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesWrittenoff_)
        return *penaltyChargesWrittenoff_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getPenaltyChargesWrittenoff() const noexcept
{
    return penaltyChargesWrittenoff_;
}
void Loan::setPenaltyChargesWrittenoff(const std::string &pPenaltyChargesWrittenoff) noexcept
{
    penaltyChargesWrittenoff_ = std::make_shared<std::string>(pPenaltyChargesWrittenoff);
    dirtyFlag_[70] = true;
}
void Loan::setPenaltyChargesWrittenoff(std::string &&pPenaltyChargesWrittenoff) noexcept
{
    penaltyChargesWrittenoff_ = std::make_shared<std::string>(std::move(pPenaltyChargesWrittenoff));
    dirtyFlag_[70] = true;
}

const std::string &Loan::getValueOfTotalRecovered() const noexcept
{
    static const std::string defaultValue = std::string();
    if(totalRecovered_)
        return *totalRecovered_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getTotalRecovered() const noexcept
{
    return totalRecovered_;
}
void Loan::setTotalRecovered(const std::string &pTotalRecovered) noexcept
{
    totalRecovered_ = std::make_shared<std::string>(pTotalRecovered);
    dirtyFlag_[71] = true;
}
void Loan::setTotalRecovered(std::string &&pTotalRecovered) noexcept
{
    totalRecovered_ = std::make_shared<std::string>(std::move(pTotalRecovered));
    dirtyFlag_[71] = true;
}

const std::string &Loan::getValueOfTotalOverpaid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(totalOverpaid_)
        return *totalOverpaid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getTotalOverpaid() const noexcept
{
    return totalOverpaid_;
}
void Loan::setTotalOverpaid(const std::string &pTotalOverpaid) noexcept
{
    totalOverpaid_ = std::make_shared<std::string>(pTotalOverpaid);
    dirtyFlag_[72] = true;
}
void Loan::setTotalOverpaid(std::string &&pTotalOverpaid) noexcept
{
    totalOverpaid_ = std::make_shared<std::string>(std::move(pTotalOverpaid));
    dirtyFlag_[72] = true;
}

const std::string &Loan::getValueOfBuydownFeeAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(buydownFeeAmount_)
        return *buydownFeeAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getBuydownFeeAmount() const noexcept
{
    return buydownFeeAmount_;
}
void Loan::setBuydownFeeAmount(const std::string &pBuydownFeeAmount) noexcept
{
    buydownFeeAmount_ = std::make_shared<std::string>(pBuydownFeeAmount);
    dirtyFlag_[73] = true;
}
void Loan::setBuydownFeeAmount(std::string &&pBuydownFeeAmount) noexcept
{
    buydownFeeAmount_ = std::make_shared<std::string>(std::move(pBuydownFeeAmount));
    dirtyFlag_[73] = true;
}

const std::string &Loan::getValueOfCapitalizedIncomeAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(capitalizedIncomeAmount_)
        return *capitalizedIncomeAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getCapitalizedIncomeAmount() const noexcept
{
    return capitalizedIncomeAmount_;
}
void Loan::setCapitalizedIncomeAmount(const std::string &pCapitalizedIncomeAmount) noexcept
{
    capitalizedIncomeAmount_ = std::make_shared<std::string>(pCapitalizedIncomeAmount);
    dirtyFlag_[74] = true;
}
void Loan::setCapitalizedIncomeAmount(std::string &&pCapitalizedIncomeAmount) noexcept
{
    capitalizedIncomeAmount_ = std::make_shared<std::string>(std::move(pCapitalizedIncomeAmount));
    dirtyFlag_[74] = true;
}

const std::string &Loan::getValueOfGlimParentLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(glimParentLoanId_)
        return *glimParentLoanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Loan::getGlimParentLoanId() const noexcept
{
    return glimParentLoanId_;
}
void Loan::setGlimParentLoanId(const std::string &pGlimParentLoanId) noexcept
{
    glimParentLoanId_ = std::make_shared<std::string>(pGlimParentLoanId);
    dirtyFlag_[75] = true;
}
void Loan::setGlimParentLoanId(std::string &&pGlimParentLoanId) noexcept
{
    glimParentLoanId_ = std::make_shared<std::string>(std::move(pGlimParentLoanId));
    dirtyFlag_[75] = true;
}
void Loan::setGlimParentLoanIdToNull() noexcept
{
    glimParentLoanId_.reset();
    dirtyFlag_[75] = true;
}

const ::trantor::Date &Loan::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Loan::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[76] = true;
}

const ::trantor::Date &Loan::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Loan::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void Loan::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[77] = true;
}

void Loan::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Loan::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "account_no",
        "external_id",
        "client_id",
        "group_id",
        "product_id",
        "loan_officer_id",
        "fund_id",
        "loan_purpose",
        "loan_type",
        "currency_code",
        "currency_digits",
        "principal_amount",
        "approved_principal",
        "net_disbursal_amount",
        "number_of_repayments",
        "repayment_every",
        "repayment_frequency_type",
        "interest_rate_per_period",
        "interest_period_frequency_type",
        "annual_nominal_interest_rate",
        "interest_method",
        "interest_calculation_period_type",
        "amortization_type",
        "transaction_processing_strategy",
        "days_in_year_type",
        "days_in_month_type",
        "grace_on_principal_payment",
        "grace_on_interest_payment",
        "grace_on_interest_charged",
        "grace_on_arrears_ageing",
        "is_equal_amortization",
        "is_floating_interest_rate",
        "floating_rate_id",
        "interest_rate_differential",
        "submitted_on_date",
        "submitted_by",
        "approved_on_date",
        "approved_by",
        "expected_disbursement_date",
        "actual_disbursement_date",
        "disbursed_by",
        "expected_first_repayment_on_date",
        "interest_charged_from_date",
        "expected_maturity_date",
        "maturity_date",
        "closed_on_date",
        "closed_by",
        "rejected_on_date",
        "withdrawn_on_date",
        "writtenoff_on_date",
        "status",
        "sub_status",
        "is_npa",
        "delinquency_range_id",
        "overdue_since_date",
        "principal_disbursed",
        "principal_paid",
        "principal_writtenoff",
        "interest_charged",
        "interest_paid",
        "interest_waived",
        "interest_writtenoff",
        "fee_charges_charged",
        "fee_charges_paid",
        "fee_charges_waived",
        "fee_charges_writtenoff",
        "penalty_charges_charged",
        "penalty_charges_paid",
        "penalty_charges_waived",
        "penalty_charges_writtenoff",
        "total_recovered",
        "total_overpaid",
        "buydown_fee_amount",
        "capitalized_income_amount",
        "glim_parent_loan_id",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void Loan::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getProductId())
        {
            binder << getValueOfProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getLoanOfficerId())
        {
            binder << getValueOfLoanOfficerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getFundId())
        {
            binder << getValueOfFundId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getLoanPurpose())
        {
            binder << getValueOfLoanPurpose();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getLoanType())
        {
            binder << getValueOfLoanType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getCurrencyDigits())
        {
            binder << getValueOfCurrencyDigits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getPrincipalAmount())
        {
            binder << getValueOfPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getApprovedPrincipal())
        {
            binder << getValueOfApprovedPrincipal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getNetDisbursalAmount())
        {
            binder << getValueOfNetDisbursalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getNumberOfRepayments())
        {
            binder << getValueOfNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getRepaymentEvery())
        {
            binder << getValueOfRepaymentEvery();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getRepaymentFrequencyType())
        {
            binder << getValueOfRepaymentFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getInterestRatePerPeriod())
        {
            binder << getValueOfInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getInterestPeriodFrequencyType())
        {
            binder << getValueOfInterestPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getAnnualNominalInterestRate())
        {
            binder << getValueOfAnnualNominalInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getInterestMethod())
        {
            binder << getValueOfInterestMethod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getInterestCalculationPeriodType())
        {
            binder << getValueOfInterestCalculationPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getAmortizationType())
        {
            binder << getValueOfAmortizationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getTransactionProcessingStrategy())
        {
            binder << getValueOfTransactionProcessingStrategy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getDaysInYearType())
        {
            binder << getValueOfDaysInYearType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getDaysInMonthType())
        {
            binder << getValueOfDaysInMonthType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
    {
        if(getGraceOnPrincipalPayment())
        {
            binder << getValueOfGraceOnPrincipalPayment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
    {
        if(getGraceOnInterestPayment())
        {
            binder << getValueOfGraceOnInterestPayment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getGraceOnInterestCharged())
        {
            binder << getValueOfGraceOnInterestCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getGraceOnArrearsAgeing())
        {
            binder << getValueOfGraceOnArrearsAgeing();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getIsEqualAmortization())
        {
            binder << getValueOfIsEqualAmortization();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getIsFloatingInterestRate())
        {
            binder << getValueOfIsFloatingInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getFloatingRateId())
        {
            binder << getValueOfFloatingRateId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getInterestRateDifferential())
        {
            binder << getValueOfInterestRateDifferential();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
    {
        if(getSubmittedBy())
        {
            binder << getValueOfSubmittedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
    {
        if(getApprovedOnDate())
        {
            binder << getValueOfApprovedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getApprovedBy())
        {
            binder << getValueOfApprovedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getExpectedDisbursementDate())
        {
            binder << getValueOfExpectedDisbursementDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getActualDisbursementDate())
        {
            binder << getValueOfActualDisbursementDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
    {
        if(getDisbursedBy())
        {
            binder << getValueOfDisbursedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getExpectedFirstRepaymentOnDate())
        {
            binder << getValueOfExpectedFirstRepaymentOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getInterestChargedFromDate())
        {
            binder << getValueOfInterestChargedFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getExpectedMaturityDate())
        {
            binder << getValueOfExpectedMaturityDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getMaturityDate())
        {
            binder << getValueOfMaturityDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getClosedOnDate())
        {
            binder << getValueOfClosedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getClosedBy())
        {
            binder << getValueOfClosedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getRejectedOnDate())
        {
            binder << getValueOfRejectedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getWithdrawnOnDate())
        {
            binder << getValueOfWithdrawnOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getWrittenoffOnDate())
        {
            binder << getValueOfWrittenoffOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getSubStatus())
        {
            binder << getValueOfSubStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[53])
    {
        if(getIsNpa())
        {
            binder << getValueOfIsNpa();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[54])
    {
        if(getDelinquencyRangeId())
        {
            binder << getValueOfDelinquencyRangeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[55])
    {
        if(getOverdueSinceDate())
        {
            binder << getValueOfOverdueSinceDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[56])
    {
        if(getPrincipalDisbursed())
        {
            binder << getValueOfPrincipalDisbursed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[57])
    {
        if(getPrincipalPaid())
        {
            binder << getValueOfPrincipalPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[58])
    {
        if(getPrincipalWrittenoff())
        {
            binder << getValueOfPrincipalWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[59])
    {
        if(getInterestCharged())
        {
            binder << getValueOfInterestCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[60])
    {
        if(getInterestPaid())
        {
            binder << getValueOfInterestPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[61])
    {
        if(getInterestWaived())
        {
            binder << getValueOfInterestWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[62])
    {
        if(getInterestWrittenoff())
        {
            binder << getValueOfInterestWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[63])
    {
        if(getFeeChargesCharged())
        {
            binder << getValueOfFeeChargesCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[64])
    {
        if(getFeeChargesPaid())
        {
            binder << getValueOfFeeChargesPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[65])
    {
        if(getFeeChargesWaived())
        {
            binder << getValueOfFeeChargesWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[66])
    {
        if(getFeeChargesWrittenoff())
        {
            binder << getValueOfFeeChargesWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[67])
    {
        if(getPenaltyChargesCharged())
        {
            binder << getValueOfPenaltyChargesCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[68])
    {
        if(getPenaltyChargesPaid())
        {
            binder << getValueOfPenaltyChargesPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[69])
    {
        if(getPenaltyChargesWaived())
        {
            binder << getValueOfPenaltyChargesWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[70])
    {
        if(getPenaltyChargesWrittenoff())
        {
            binder << getValueOfPenaltyChargesWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[71])
    {
        if(getTotalRecovered())
        {
            binder << getValueOfTotalRecovered();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[72])
    {
        if(getTotalOverpaid())
        {
            binder << getValueOfTotalOverpaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[73])
    {
        if(getBuydownFeeAmount())
        {
            binder << getValueOfBuydownFeeAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[74])
    {
        if(getCapitalizedIncomeAmount())
        {
            binder << getValueOfCapitalizedIncomeAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[75])
    {
        if(getGlimParentLoanId())
        {
            binder << getValueOfGlimParentLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[76])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[77])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Loan::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    if(dirtyFlag_[6])
    {
        ret.push_back(getColumnName(6));
    }
    if(dirtyFlag_[7])
    {
        ret.push_back(getColumnName(7));
    }
    if(dirtyFlag_[8])
    {
        ret.push_back(getColumnName(8));
    }
    if(dirtyFlag_[9])
    {
        ret.push_back(getColumnName(9));
    }
    if(dirtyFlag_[10])
    {
        ret.push_back(getColumnName(10));
    }
    if(dirtyFlag_[11])
    {
        ret.push_back(getColumnName(11));
    }
    if(dirtyFlag_[12])
    {
        ret.push_back(getColumnName(12));
    }
    if(dirtyFlag_[13])
    {
        ret.push_back(getColumnName(13));
    }
    if(dirtyFlag_[14])
    {
        ret.push_back(getColumnName(14));
    }
    if(dirtyFlag_[15])
    {
        ret.push_back(getColumnName(15));
    }
    if(dirtyFlag_[16])
    {
        ret.push_back(getColumnName(16));
    }
    if(dirtyFlag_[17])
    {
        ret.push_back(getColumnName(17));
    }
    if(dirtyFlag_[18])
    {
        ret.push_back(getColumnName(18));
    }
    if(dirtyFlag_[19])
    {
        ret.push_back(getColumnName(19));
    }
    if(dirtyFlag_[20])
    {
        ret.push_back(getColumnName(20));
    }
    if(dirtyFlag_[21])
    {
        ret.push_back(getColumnName(21));
    }
    if(dirtyFlag_[22])
    {
        ret.push_back(getColumnName(22));
    }
    if(dirtyFlag_[23])
    {
        ret.push_back(getColumnName(23));
    }
    if(dirtyFlag_[24])
    {
        ret.push_back(getColumnName(24));
    }
    if(dirtyFlag_[25])
    {
        ret.push_back(getColumnName(25));
    }
    if(dirtyFlag_[26])
    {
        ret.push_back(getColumnName(26));
    }
    if(dirtyFlag_[27])
    {
        ret.push_back(getColumnName(27));
    }
    if(dirtyFlag_[28])
    {
        ret.push_back(getColumnName(28));
    }
    if(dirtyFlag_[29])
    {
        ret.push_back(getColumnName(29));
    }
    if(dirtyFlag_[30])
    {
        ret.push_back(getColumnName(30));
    }
    if(dirtyFlag_[31])
    {
        ret.push_back(getColumnName(31));
    }
    if(dirtyFlag_[32])
    {
        ret.push_back(getColumnName(32));
    }
    if(dirtyFlag_[33])
    {
        ret.push_back(getColumnName(33));
    }
    if(dirtyFlag_[34])
    {
        ret.push_back(getColumnName(34));
    }
    if(dirtyFlag_[35])
    {
        ret.push_back(getColumnName(35));
    }
    if(dirtyFlag_[36])
    {
        ret.push_back(getColumnName(36));
    }
    if(dirtyFlag_[37])
    {
        ret.push_back(getColumnName(37));
    }
    if(dirtyFlag_[38])
    {
        ret.push_back(getColumnName(38));
    }
    if(dirtyFlag_[39])
    {
        ret.push_back(getColumnName(39));
    }
    if(dirtyFlag_[40])
    {
        ret.push_back(getColumnName(40));
    }
    if(dirtyFlag_[41])
    {
        ret.push_back(getColumnName(41));
    }
    if(dirtyFlag_[42])
    {
        ret.push_back(getColumnName(42));
    }
    if(dirtyFlag_[43])
    {
        ret.push_back(getColumnName(43));
    }
    if(dirtyFlag_[44])
    {
        ret.push_back(getColumnName(44));
    }
    if(dirtyFlag_[45])
    {
        ret.push_back(getColumnName(45));
    }
    if(dirtyFlag_[46])
    {
        ret.push_back(getColumnName(46));
    }
    if(dirtyFlag_[47])
    {
        ret.push_back(getColumnName(47));
    }
    if(dirtyFlag_[48])
    {
        ret.push_back(getColumnName(48));
    }
    if(dirtyFlag_[49])
    {
        ret.push_back(getColumnName(49));
    }
    if(dirtyFlag_[50])
    {
        ret.push_back(getColumnName(50));
    }
    if(dirtyFlag_[51])
    {
        ret.push_back(getColumnName(51));
    }
    if(dirtyFlag_[52])
    {
        ret.push_back(getColumnName(52));
    }
    if(dirtyFlag_[53])
    {
        ret.push_back(getColumnName(53));
    }
    if(dirtyFlag_[54])
    {
        ret.push_back(getColumnName(54));
    }
    if(dirtyFlag_[55])
    {
        ret.push_back(getColumnName(55));
    }
    if(dirtyFlag_[56])
    {
        ret.push_back(getColumnName(56));
    }
    if(dirtyFlag_[57])
    {
        ret.push_back(getColumnName(57));
    }
    if(dirtyFlag_[58])
    {
        ret.push_back(getColumnName(58));
    }
    if(dirtyFlag_[59])
    {
        ret.push_back(getColumnName(59));
    }
    if(dirtyFlag_[60])
    {
        ret.push_back(getColumnName(60));
    }
    if(dirtyFlag_[61])
    {
        ret.push_back(getColumnName(61));
    }
    if(dirtyFlag_[62])
    {
        ret.push_back(getColumnName(62));
    }
    if(dirtyFlag_[63])
    {
        ret.push_back(getColumnName(63));
    }
    if(dirtyFlag_[64])
    {
        ret.push_back(getColumnName(64));
    }
    if(dirtyFlag_[65])
    {
        ret.push_back(getColumnName(65));
    }
    if(dirtyFlag_[66])
    {
        ret.push_back(getColumnName(66));
    }
    if(dirtyFlag_[67])
    {
        ret.push_back(getColumnName(67));
    }
    if(dirtyFlag_[68])
    {
        ret.push_back(getColumnName(68));
    }
    if(dirtyFlag_[69])
    {
        ret.push_back(getColumnName(69));
    }
    if(dirtyFlag_[70])
    {
        ret.push_back(getColumnName(70));
    }
    if(dirtyFlag_[71])
    {
        ret.push_back(getColumnName(71));
    }
    if(dirtyFlag_[72])
    {
        ret.push_back(getColumnName(72));
    }
    if(dirtyFlag_[73])
    {
        ret.push_back(getColumnName(73));
    }
    if(dirtyFlag_[74])
    {
        ret.push_back(getColumnName(74));
    }
    if(dirtyFlag_[75])
    {
        ret.push_back(getColumnName(75));
    }
    if(dirtyFlag_[76])
    {
        ret.push_back(getColumnName(76));
    }
    if(dirtyFlag_[77])
    {
        ret.push_back(getColumnName(77));
    }
    return ret;
}

void Loan::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getProductId())
        {
            binder << getValueOfProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getLoanOfficerId())
        {
            binder << getValueOfLoanOfficerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getFundId())
        {
            binder << getValueOfFundId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getLoanPurpose())
        {
            binder << getValueOfLoanPurpose();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getLoanType())
        {
            binder << getValueOfLoanType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getCurrencyDigits())
        {
            binder << getValueOfCurrencyDigits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getPrincipalAmount())
        {
            binder << getValueOfPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getApprovedPrincipal())
        {
            binder << getValueOfApprovedPrincipal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getNetDisbursalAmount())
        {
            binder << getValueOfNetDisbursalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getNumberOfRepayments())
        {
            binder << getValueOfNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getRepaymentEvery())
        {
            binder << getValueOfRepaymentEvery();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getRepaymentFrequencyType())
        {
            binder << getValueOfRepaymentFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getInterestRatePerPeriod())
        {
            binder << getValueOfInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getInterestPeriodFrequencyType())
        {
            binder << getValueOfInterestPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getAnnualNominalInterestRate())
        {
            binder << getValueOfAnnualNominalInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getInterestMethod())
        {
            binder << getValueOfInterestMethod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getInterestCalculationPeriodType())
        {
            binder << getValueOfInterestCalculationPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getAmortizationType())
        {
            binder << getValueOfAmortizationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getTransactionProcessingStrategy())
        {
            binder << getValueOfTransactionProcessingStrategy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getDaysInYearType())
        {
            binder << getValueOfDaysInYearType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getDaysInMonthType())
        {
            binder << getValueOfDaysInMonthType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
    {
        if(getGraceOnPrincipalPayment())
        {
            binder << getValueOfGraceOnPrincipalPayment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
    {
        if(getGraceOnInterestPayment())
        {
            binder << getValueOfGraceOnInterestPayment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getGraceOnInterestCharged())
        {
            binder << getValueOfGraceOnInterestCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getGraceOnArrearsAgeing())
        {
            binder << getValueOfGraceOnArrearsAgeing();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getIsEqualAmortization())
        {
            binder << getValueOfIsEqualAmortization();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getIsFloatingInterestRate())
        {
            binder << getValueOfIsFloatingInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getFloatingRateId())
        {
            binder << getValueOfFloatingRateId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getInterestRateDifferential())
        {
            binder << getValueOfInterestRateDifferential();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
    {
        if(getSubmittedBy())
        {
            binder << getValueOfSubmittedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
    {
        if(getApprovedOnDate())
        {
            binder << getValueOfApprovedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getApprovedBy())
        {
            binder << getValueOfApprovedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getExpectedDisbursementDate())
        {
            binder << getValueOfExpectedDisbursementDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getActualDisbursementDate())
        {
            binder << getValueOfActualDisbursementDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
    {
        if(getDisbursedBy())
        {
            binder << getValueOfDisbursedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getExpectedFirstRepaymentOnDate())
        {
            binder << getValueOfExpectedFirstRepaymentOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getInterestChargedFromDate())
        {
            binder << getValueOfInterestChargedFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getExpectedMaturityDate())
        {
            binder << getValueOfExpectedMaturityDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getMaturityDate())
        {
            binder << getValueOfMaturityDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getClosedOnDate())
        {
            binder << getValueOfClosedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getClosedBy())
        {
            binder << getValueOfClosedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getRejectedOnDate())
        {
            binder << getValueOfRejectedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getWithdrawnOnDate())
        {
            binder << getValueOfWithdrawnOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getWrittenoffOnDate())
        {
            binder << getValueOfWrittenoffOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getSubStatus())
        {
            binder << getValueOfSubStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[53])
    {
        if(getIsNpa())
        {
            binder << getValueOfIsNpa();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[54])
    {
        if(getDelinquencyRangeId())
        {
            binder << getValueOfDelinquencyRangeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[55])
    {
        if(getOverdueSinceDate())
        {
            binder << getValueOfOverdueSinceDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[56])
    {
        if(getPrincipalDisbursed())
        {
            binder << getValueOfPrincipalDisbursed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[57])
    {
        if(getPrincipalPaid())
        {
            binder << getValueOfPrincipalPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[58])
    {
        if(getPrincipalWrittenoff())
        {
            binder << getValueOfPrincipalWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[59])
    {
        if(getInterestCharged())
        {
            binder << getValueOfInterestCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[60])
    {
        if(getInterestPaid())
        {
            binder << getValueOfInterestPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[61])
    {
        if(getInterestWaived())
        {
            binder << getValueOfInterestWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[62])
    {
        if(getInterestWrittenoff())
        {
            binder << getValueOfInterestWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[63])
    {
        if(getFeeChargesCharged())
        {
            binder << getValueOfFeeChargesCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[64])
    {
        if(getFeeChargesPaid())
        {
            binder << getValueOfFeeChargesPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[65])
    {
        if(getFeeChargesWaived())
        {
            binder << getValueOfFeeChargesWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[66])
    {
        if(getFeeChargesWrittenoff())
        {
            binder << getValueOfFeeChargesWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[67])
    {
        if(getPenaltyChargesCharged())
        {
            binder << getValueOfPenaltyChargesCharged();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[68])
    {
        if(getPenaltyChargesPaid())
        {
            binder << getValueOfPenaltyChargesPaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[69])
    {
        if(getPenaltyChargesWaived())
        {
            binder << getValueOfPenaltyChargesWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[70])
    {
        if(getPenaltyChargesWrittenoff())
        {
            binder << getValueOfPenaltyChargesWrittenoff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[71])
    {
        if(getTotalRecovered())
        {
            binder << getValueOfTotalRecovered();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[72])
    {
        if(getTotalOverpaid())
        {
            binder << getValueOfTotalOverpaid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[73])
    {
        if(getBuydownFeeAmount())
        {
            binder << getValueOfBuydownFeeAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[74])
    {
        if(getCapitalizedIncomeAmount())
        {
            binder << getValueOfCapitalizedIncomeAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[75])
    {
        if(getGlimParentLoanId())
        {
            binder << getValueOfGlimParentLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[76])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[77])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}
