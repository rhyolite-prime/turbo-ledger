/**
 *  LoanProduct.cc
 *
 *  See LoanProduct.h for the hand-authored-subset note.
 *
 */

#include "LoanProduct.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanProduct::Cols::_id = "\"id\"";
const std::string LoanProduct::Cols::_name = "\"name\"";
const std::string LoanProduct::Cols::_short_name = "\"short_name\"";
const std::string LoanProduct::Cols::_description = "\"description\"";
const std::string LoanProduct::Cols::_fund_id = "\"fund_id\"";
const std::string LoanProduct::Cols::_currency_code = "\"currency_code\"";
const std::string LoanProduct::Cols::_currency_digits = "\"currency_digits\"";
const std::string LoanProduct::Cols::_min_principal_amount = "\"min_principal_amount\"";
const std::string LoanProduct::Cols::_default_principal_amount = "\"default_principal_amount\"";
const std::string LoanProduct::Cols::_max_principal_amount = "\"max_principal_amount\"";
const std::string LoanProduct::Cols::_min_number_of_repayments = "\"min_number_of_repayments\"";
const std::string LoanProduct::Cols::_default_number_of_repayments = "\"default_number_of_repayments\"";
const std::string LoanProduct::Cols::_max_number_of_repayments = "\"max_number_of_repayments\"";
const std::string LoanProduct::Cols::_repayment_every = "\"repayment_every\"";
const std::string LoanProduct::Cols::_repayment_frequency_type = "\"repayment_frequency_type\"";
const std::string LoanProduct::Cols::_min_interest_rate_per_period = "\"min_interest_rate_per_period\"";
const std::string LoanProduct::Cols::_default_interest_rate_per_period = "\"default_interest_rate_per_period\"";
const std::string LoanProduct::Cols::_max_interest_rate_per_period = "\"max_interest_rate_per_period\"";
const std::string LoanProduct::Cols::_interest_period_frequency_type = "\"interest_period_frequency_type\"";
const std::string LoanProduct::Cols::_annual_nominal_interest_rate = "\"annual_nominal_interest_rate\"";
const std::string LoanProduct::Cols::_interest_method = "\"interest_method\"";
const std::string LoanProduct::Cols::_interest_calculation_period_type = "\"interest_calculation_period_type\"";
const std::string LoanProduct::Cols::_amortization_type = "\"amortization_type\"";
const std::string LoanProduct::Cols::_transaction_processing_strategy = "\"transaction_processing_strategy\"";
const std::string LoanProduct::Cols::_grace_on_principal_payment = "\"grace_on_principal_payment\"";
const std::string LoanProduct::Cols::_grace_on_interest_payment = "\"grace_on_interest_payment\"";
const std::string LoanProduct::Cols::_grace_on_interest_charged = "\"grace_on_interest_charged\"";
const std::string LoanProduct::Cols::_grace_on_arrears_ageing = "\"grace_on_arrears_ageing\"";
const std::string LoanProduct::Cols::_overdue_days_for_npa = "\"overdue_days_for_npa\"";
const std::string LoanProduct::Cols::_days_in_year_type = "\"days_in_year_type\"";
const std::string LoanProduct::Cols::_days_in_month_type = "\"days_in_month_type\"";
const std::string LoanProduct::Cols::_min_days_between_disbursal_and_first_repayment = "\"min_days_between_disbursal_and_first_repayment\"";
const std::string LoanProduct::Cols::_allow_partial_period_interest = "\"allow_partial_period_interest\"";
const std::string LoanProduct::Cols::_is_linked_to_floating_rate = "\"is_linked_to_floating_rate\"";
const std::string LoanProduct::Cols::_floating_rate_id = "\"floating_rate_id\"";
const std::string LoanProduct::Cols::_default_differential_lending_rate = "\"default_differential_lending_rate\"";
const std::string LoanProduct::Cols::_is_equal_amortization = "\"is_equal_amortization\"";
const std::string LoanProduct::Cols::_allow_attribute_overrides = "\"allow_attribute_overrides\"";
const std::string LoanProduct::Cols::_can_use_for_topup = "\"can_use_for_topup\"";
const std::string LoanProduct::Cols::_close_date = "\"close_date\"";
const std::string LoanProduct::Cols::_start_date = "\"start_date\"";
const std::string LoanProduct::Cols::_delinquency_bucket_id = "\"delinquency_bucket_id\"";
const std::string LoanProduct::Cols::_accounting_type = "\"accounting_type\"";
const std::string LoanProduct::Cols::_fund_source_account_id = "\"fund_source_account_id\"";
const std::string LoanProduct::Cols::_loan_portfolio_account_id = "\"loan_portfolio_account_id\"";
const std::string LoanProduct::Cols::_interest_on_loan_account_id = "\"interest_on_loan_account_id\"";
const std::string LoanProduct::Cols::_income_from_fees_account_id = "\"income_from_fees_account_id\"";
const std::string LoanProduct::Cols::_income_from_penalties_account_id = "\"income_from_penalties_account_id\"";
const std::string LoanProduct::Cols::_income_from_recovery_account_id = "\"income_from_recovery_account_id\"";
const std::string LoanProduct::Cols::_losses_written_off_account_id = "\"losses_written_off_account_id\"";
const std::string LoanProduct::Cols::_overpayment_liability_account_id = "\"overpayment_liability_account_id\"";
const std::string LoanProduct::Cols::_interest_receivable_account_id = "\"interest_receivable_account_id\"";
const std::string LoanProduct::Cols::_fee_receivable_account_id = "\"fee_receivable_account_id\"";
const std::string LoanProduct::Cols::_penalty_receivable_account_id = "\"penalty_receivable_account_id\"";
const std::string LoanProduct::Cols::_is_active = "\"is_active\"";
const std::string LoanProduct::Cols::_created_by = "\"created_by\"";
const std::string LoanProduct::Cols::_created_at = "\"created_at\"";
const std::string LoanProduct::Cols::_updated_by = "\"updated_by\"";
const std::string LoanProduct::Cols::_updated_at = "\"updated_at\"";
const std::string LoanProduct::primaryKeyName = "id";
const bool LoanProduct::hasPrimaryKey = true;
const std::string LoanProduct::tableName = "\"loan_product\"";

const std::vector<typename LoanProduct::MetaData> LoanProduct::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",100,0,0,1},
{"short_name","std::string","character varying",4,0,0,1},
{"description","std::string","text",0,0,0,0},
{"fund_id","std::string","uuid",0,0,0,0},
{"currency_code","std::string","character varying",3,0,0,1},
{"currency_digits","int32_t","integer",4,0,0,1},
{"min_principal_amount","std::string","numeric",0,0,0,0},
{"default_principal_amount","std::string","numeric",0,0,0,1},
{"max_principal_amount","std::string","numeric",0,0,0,0},
{"min_number_of_repayments","int32_t","integer",4,0,0,0},
{"default_number_of_repayments","int32_t","integer",4,0,0,1},
{"max_number_of_repayments","int32_t","integer",4,0,0,0},
{"repayment_every","int32_t","integer",4,0,0,1},
{"repayment_frequency_type","int32_t","integer",4,0,0,1},
{"min_interest_rate_per_period","std::string","numeric",0,0,0,0},
{"default_interest_rate_per_period","std::string","numeric",0,0,0,1},
{"max_interest_rate_per_period","std::string","numeric",0,0,0,0},
{"interest_period_frequency_type","int32_t","integer",4,0,0,1},
{"annual_nominal_interest_rate","std::string","numeric",0,0,0,1},
{"interest_method","int32_t","integer",4,0,0,1},
{"interest_calculation_period_type","int32_t","integer",4,0,0,1},
{"amortization_type","int32_t","integer",4,0,0,1},
{"transaction_processing_strategy","std::string","character varying",40,0,0,1},
{"grace_on_principal_payment","int32_t","integer",4,0,0,1},
{"grace_on_interest_payment","int32_t","integer",4,0,0,1},
{"grace_on_interest_charged","int32_t","integer",4,0,0,1},
{"grace_on_arrears_ageing","int32_t","integer",4,0,0,1},
{"overdue_days_for_npa","int32_t","integer",4,0,0,1},
{"days_in_year_type","int32_t","integer",4,0,0,1},
{"days_in_month_type","int32_t","integer",4,0,0,1},
{"min_days_between_disbursal_and_first_repayment","int32_t","integer",4,0,0,1},
{"allow_partial_period_interest","bool","boolean",1,0,0,1},
{"is_linked_to_floating_rate","bool","boolean",1,0,0,1},
{"floating_rate_id","std::string","uuid",0,0,0,0},
{"default_differential_lending_rate","std::string","numeric",0,0,0,0},
{"is_equal_amortization","bool","boolean",1,0,0,1},
{"allow_attribute_overrides","bool","boolean",1,0,0,1},
{"can_use_for_topup","bool","boolean",1,0,0,1},
{"close_date","::trantor::Date","date",0,0,0,0},
{"start_date","::trantor::Date","date",0,0,0,0},
{"delinquency_bucket_id","std::string","uuid",0,0,0,0},
{"accounting_type","int32_t","integer",4,0,0,1},
{"fund_source_account_id","std::string","uuid",0,0,0,0},
{"loan_portfolio_account_id","std::string","uuid",0,0,0,0},
{"interest_on_loan_account_id","std::string","uuid",0,0,0,0},
{"income_from_fees_account_id","std::string","uuid",0,0,0,0},
{"income_from_penalties_account_id","std::string","uuid",0,0,0,0},
{"income_from_recovery_account_id","std::string","uuid",0,0,0,0},
{"losses_written_off_account_id","std::string","uuid",0,0,0,0},
{"overpayment_liability_account_id","std::string","uuid",0,0,0,0},
{"interest_receivable_account_id","std::string","uuid",0,0,0,0},
{"fee_receivable_account_id","std::string","uuid",0,0,0,0},
{"penalty_receivable_account_id","std::string","uuid",0,0,0,0},
{"is_active","bool","boolean",1,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanProduct::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanProduct::LoanProduct(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["short_name"].isNull())
        {
            shortName_=std::make_shared<std::string>(r["short_name"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["fund_id"].isNull())
        {
            fundId_=std::make_shared<std::string>(r["fund_id"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["currency_digits"].isNull())
        {
            currencyDigits_=std::make_shared<int32_t>(r["currency_digits"].as<int32_t>());
        }
        if(!r["min_principal_amount"].isNull())
        {
            minPrincipalAmount_=std::make_shared<std::string>(r["min_principal_amount"].as<std::string>());
        }
        if(!r["default_principal_amount"].isNull())
        {
            defaultPrincipalAmount_=std::make_shared<std::string>(r["default_principal_amount"].as<std::string>());
        }
        if(!r["max_principal_amount"].isNull())
        {
            maxPrincipalAmount_=std::make_shared<std::string>(r["max_principal_amount"].as<std::string>());
        }
        if(!r["min_number_of_repayments"].isNull())
        {
            minNumberOfRepayments_=std::make_shared<int32_t>(r["min_number_of_repayments"].as<int32_t>());
        }
        if(!r["default_number_of_repayments"].isNull())
        {
            defaultNumberOfRepayments_=std::make_shared<int32_t>(r["default_number_of_repayments"].as<int32_t>());
        }
        if(!r["max_number_of_repayments"].isNull())
        {
            maxNumberOfRepayments_=std::make_shared<int32_t>(r["max_number_of_repayments"].as<int32_t>());
        }
        if(!r["repayment_every"].isNull())
        {
            repaymentEvery_=std::make_shared<int32_t>(r["repayment_every"].as<int32_t>());
        }
        if(!r["repayment_frequency_type"].isNull())
        {
            repaymentFrequencyType_=std::make_shared<int32_t>(r["repayment_frequency_type"].as<int32_t>());
        }
        if(!r["min_interest_rate_per_period"].isNull())
        {
            minInterestRatePerPeriod_=std::make_shared<std::string>(r["min_interest_rate_per_period"].as<std::string>());
        }
        if(!r["default_interest_rate_per_period"].isNull())
        {
            defaultInterestRatePerPeriod_=std::make_shared<std::string>(r["default_interest_rate_per_period"].as<std::string>());
        }
        if(!r["max_interest_rate_per_period"].isNull())
        {
            maxInterestRatePerPeriod_=std::make_shared<std::string>(r["max_interest_rate_per_period"].as<std::string>());
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
        if(!r["overdue_days_for_npa"].isNull())
        {
            overdueDaysForNpa_=std::make_shared<int32_t>(r["overdue_days_for_npa"].as<int32_t>());
        }
        if(!r["days_in_year_type"].isNull())
        {
            daysInYearType_=std::make_shared<int32_t>(r["days_in_year_type"].as<int32_t>());
        }
        if(!r["days_in_month_type"].isNull())
        {
            daysInMonthType_=std::make_shared<int32_t>(r["days_in_month_type"].as<int32_t>());
        }
        if(!r["min_days_between_disbursal_and_first_repayment"].isNull())
        {
            minDaysBetweenDisbursalAndFirstRepayment_=std::make_shared<int32_t>(r["min_days_between_disbursal_and_first_repayment"].as<int32_t>());
        }
        if(!r["allow_partial_period_interest"].isNull())
        {
            allowPartialPeriodInterest_=std::make_shared<bool>(r["allow_partial_period_interest"].as<bool>());
        }
        if(!r["is_linked_to_floating_rate"].isNull())
        {
            isLinkedToFloatingRate_=std::make_shared<bool>(r["is_linked_to_floating_rate"].as<bool>());
        }
        if(!r["floating_rate_id"].isNull())
        {
            floatingRateId_=std::make_shared<std::string>(r["floating_rate_id"].as<std::string>());
        }
        if(!r["default_differential_lending_rate"].isNull())
        {
            defaultDifferentialLendingRate_=std::make_shared<std::string>(r["default_differential_lending_rate"].as<std::string>());
        }
        if(!r["is_equal_amortization"].isNull())
        {
            isEqualAmortization_=std::make_shared<bool>(r["is_equal_amortization"].as<bool>());
        }
        if(!r["allow_attribute_overrides"].isNull())
        {
            allowAttributeOverrides_=std::make_shared<bool>(r["allow_attribute_overrides"].as<bool>());
        }
        if(!r["can_use_for_topup"].isNull())
        {
            canUseForTopup_=std::make_shared<bool>(r["can_use_for_topup"].as<bool>());
        }
        if(!r["close_date"].isNull())
        {
            auto daysStr = r["close_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closeDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["start_date"].isNull())
        {
            auto daysStr = r["start_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["delinquency_bucket_id"].isNull())
        {
            delinquencyBucketId_=std::make_shared<std::string>(r["delinquency_bucket_id"].as<std::string>());
        }
        if(!r["accounting_type"].isNull())
        {
            accountingType_=std::make_shared<int32_t>(r["accounting_type"].as<int32_t>());
        }
        if(!r["fund_source_account_id"].isNull())
        {
            fundSourceAccountId_=std::make_shared<std::string>(r["fund_source_account_id"].as<std::string>());
        }
        if(!r["loan_portfolio_account_id"].isNull())
        {
            loanPortfolioAccountId_=std::make_shared<std::string>(r["loan_portfolio_account_id"].as<std::string>());
        }
        if(!r["interest_on_loan_account_id"].isNull())
        {
            interestOnLoanAccountId_=std::make_shared<std::string>(r["interest_on_loan_account_id"].as<std::string>());
        }
        if(!r["income_from_fees_account_id"].isNull())
        {
            incomeFromFeesAccountId_=std::make_shared<std::string>(r["income_from_fees_account_id"].as<std::string>());
        }
        if(!r["income_from_penalties_account_id"].isNull())
        {
            incomeFromPenaltiesAccountId_=std::make_shared<std::string>(r["income_from_penalties_account_id"].as<std::string>());
        }
        if(!r["income_from_recovery_account_id"].isNull())
        {
            incomeFromRecoveryAccountId_=std::make_shared<std::string>(r["income_from_recovery_account_id"].as<std::string>());
        }
        if(!r["losses_written_off_account_id"].isNull())
        {
            lossesWrittenOffAccountId_=std::make_shared<std::string>(r["losses_written_off_account_id"].as<std::string>());
        }
        if(!r["overpayment_liability_account_id"].isNull())
        {
            overpaymentLiabilityAccountId_=std::make_shared<std::string>(r["overpayment_liability_account_id"].as<std::string>());
        }
        if(!r["interest_receivable_account_id"].isNull())
        {
            interestReceivableAccountId_=std::make_shared<std::string>(r["interest_receivable_account_id"].as<std::string>());
        }
        if(!r["fee_receivable_account_id"].isNull())
        {
            feeReceivableAccountId_=std::make_shared<std::string>(r["fee_receivable_account_id"].as<std::string>());
        }
        if(!r["penalty_receivable_account_id"].isNull())
        {
            penaltyReceivableAccountId_=std::make_shared<std::string>(r["penalty_receivable_account_id"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["created_by"].isNull())
        {
            createdBy_=std::make_shared<std::string>(r["created_by"].as<std::string>());
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
        if(!r["updated_by"].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r["updated_by"].as<std::string>());
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
        if(offset + 59 > r.size())
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
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            shortName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            fundId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            currencyDigits_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            minPrincipalAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            defaultPrincipalAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            maxPrincipalAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            minNumberOfRepayments_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            defaultNumberOfRepayments_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            maxNumberOfRepayments_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            repaymentEvery_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            repaymentFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            minInterestRatePerPeriod_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            defaultInterestRatePerPeriod_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            maxInterestRatePerPeriod_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            interestPeriodFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            annualNominalInterestRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            interestMethod_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 21;
        if(!r[index].isNull())
        {
            interestCalculationPeriodType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            amortizationType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            transactionProcessingStrategy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 24;
        if(!r[index].isNull())
        {
            graceOnPrincipalPayment_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 25;
        if(!r[index].isNull())
        {
            graceOnInterestPayment_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 26;
        if(!r[index].isNull())
        {
            graceOnInterestCharged_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 27;
        if(!r[index].isNull())
        {
            graceOnArrearsAgeing_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 28;
        if(!r[index].isNull())
        {
            overdueDaysForNpa_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 29;
        if(!r[index].isNull())
        {
            daysInYearType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 30;
        if(!r[index].isNull())
        {
            daysInMonthType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 31;
        if(!r[index].isNull())
        {
            minDaysBetweenDisbursalAndFirstRepayment_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 32;
        if(!r[index].isNull())
        {
            allowPartialPeriodInterest_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 33;
        if(!r[index].isNull())
        {
            isLinkedToFloatingRate_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 34;
        if(!r[index].isNull())
        {
            floatingRateId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 35;
        if(!r[index].isNull())
        {
            defaultDifferentialLendingRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 36;
        if(!r[index].isNull())
        {
            isEqualAmortization_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 37;
        if(!r[index].isNull())
        {
            allowAttributeOverrides_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 38;
        if(!r[index].isNull())
        {
            canUseForTopup_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 39;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closeDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 40;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 41;
        if(!r[index].isNull())
        {
            delinquencyBucketId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 42;
        if(!r[index].isNull())
        {
            accountingType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 43;
        if(!r[index].isNull())
        {
            fundSourceAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 44;
        if(!r[index].isNull())
        {
            loanPortfolioAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 45;
        if(!r[index].isNull())
        {
            interestOnLoanAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 46;
        if(!r[index].isNull())
        {
            incomeFromFeesAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 47;
        if(!r[index].isNull())
        {
            incomeFromPenaltiesAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 48;
        if(!r[index].isNull())
        {
            incomeFromRecoveryAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 49;
        if(!r[index].isNull())
        {
            lossesWrittenOffAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 50;
        if(!r[index].isNull())
        {
            overpaymentLiabilityAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 51;
        if(!r[index].isNull())
        {
            interestReceivableAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 52;
        if(!r[index].isNull())
        {
            feeReceivableAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 53;
        if(!r[index].isNull())
        {
            penaltyReceivableAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 54;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 55;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 56;
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
        index = offset + 57;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 58;
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
const std::string &LoanProduct::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getId() const noexcept
{
    return id_;
}
void LoanProduct::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanProduct::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanProduct::PrimaryKeyType & LoanProduct::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanProduct::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getName() const noexcept
{
    return name_;
}
void LoanProduct::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void LoanProduct::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const std::string &LoanProduct::getValueOfShortName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shortName_)
        return *shortName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getShortName() const noexcept
{
    return shortName_;
}
void LoanProduct::setShortName(const std::string &pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(pShortName);
    dirtyFlag_[2] = true;
}
void LoanProduct::setShortName(std::string &&pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(std::move(pShortName));
    dirtyFlag_[2] = true;
}

const std::string &LoanProduct::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getDescription() const noexcept
{
    return description_;
}
void LoanProduct::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void LoanProduct::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void LoanProduct::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const std::string &LoanProduct::getValueOfFundId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fundId_)
        return *fundId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getFundId() const noexcept
{
    return fundId_;
}
void LoanProduct::setFundId(const std::string &pFundId) noexcept
{
    fundId_ = std::make_shared<std::string>(pFundId);
    dirtyFlag_[4] = true;
}
void LoanProduct::setFundId(std::string &&pFundId) noexcept
{
    fundId_ = std::make_shared<std::string>(std::move(pFundId));
    dirtyFlag_[4] = true;
}
void LoanProduct::setFundIdToNull() noexcept
{
    fundId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &LoanProduct::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void LoanProduct::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[5] = true;
}
void LoanProduct::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[5] = true;
}

const int32_t &LoanProduct::getValueOfCurrencyDigits() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(currencyDigits_)
        return *currencyDigits_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getCurrencyDigits() const noexcept
{
    return currencyDigits_;
}
void LoanProduct::setCurrencyDigits(const int32_t &pCurrencyDigits) noexcept
{
    currencyDigits_ = std::make_shared<int32_t>(pCurrencyDigits);
    dirtyFlag_[6] = true;
}

const std::string &LoanProduct::getValueOfMinPrincipalAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minPrincipalAmount_)
        return *minPrincipalAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getMinPrincipalAmount() const noexcept
{
    return minPrincipalAmount_;
}
void LoanProduct::setMinPrincipalAmount(const std::string &pMinPrincipalAmount) noexcept
{
    minPrincipalAmount_ = std::make_shared<std::string>(pMinPrincipalAmount);
    dirtyFlag_[7] = true;
}
void LoanProduct::setMinPrincipalAmount(std::string &&pMinPrincipalAmount) noexcept
{
    minPrincipalAmount_ = std::make_shared<std::string>(std::move(pMinPrincipalAmount));
    dirtyFlag_[7] = true;
}
void LoanProduct::setMinPrincipalAmountToNull() noexcept
{
    minPrincipalAmount_.reset();
    dirtyFlag_[7] = true;
}

const std::string &LoanProduct::getValueOfDefaultPrincipalAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(defaultPrincipalAmount_)
        return *defaultPrincipalAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getDefaultPrincipalAmount() const noexcept
{
    return defaultPrincipalAmount_;
}
void LoanProduct::setDefaultPrincipalAmount(const std::string &pDefaultPrincipalAmount) noexcept
{
    defaultPrincipalAmount_ = std::make_shared<std::string>(pDefaultPrincipalAmount);
    dirtyFlag_[8] = true;
}
void LoanProduct::setDefaultPrincipalAmount(std::string &&pDefaultPrincipalAmount) noexcept
{
    defaultPrincipalAmount_ = std::make_shared<std::string>(std::move(pDefaultPrincipalAmount));
    dirtyFlag_[8] = true;
}

const std::string &LoanProduct::getValueOfMaxPrincipalAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(maxPrincipalAmount_)
        return *maxPrincipalAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getMaxPrincipalAmount() const noexcept
{
    return maxPrincipalAmount_;
}
void LoanProduct::setMaxPrincipalAmount(const std::string &pMaxPrincipalAmount) noexcept
{
    maxPrincipalAmount_ = std::make_shared<std::string>(pMaxPrincipalAmount);
    dirtyFlag_[9] = true;
}
void LoanProduct::setMaxPrincipalAmount(std::string &&pMaxPrincipalAmount) noexcept
{
    maxPrincipalAmount_ = std::make_shared<std::string>(std::move(pMaxPrincipalAmount));
    dirtyFlag_[9] = true;
}
void LoanProduct::setMaxPrincipalAmountToNull() noexcept
{
    maxPrincipalAmount_.reset();
    dirtyFlag_[9] = true;
}

const int32_t &LoanProduct::getValueOfMinNumberOfRepayments() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(minNumberOfRepayments_)
        return *minNumberOfRepayments_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getMinNumberOfRepayments() const noexcept
{
    return minNumberOfRepayments_;
}
void LoanProduct::setMinNumberOfRepayments(const int32_t &pMinNumberOfRepayments) noexcept
{
    minNumberOfRepayments_ = std::make_shared<int32_t>(pMinNumberOfRepayments);
    dirtyFlag_[10] = true;
}
void LoanProduct::setMinNumberOfRepaymentsToNull() noexcept
{
    minNumberOfRepayments_.reset();
    dirtyFlag_[10] = true;
}

const int32_t &LoanProduct::getValueOfDefaultNumberOfRepayments() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(defaultNumberOfRepayments_)
        return *defaultNumberOfRepayments_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getDefaultNumberOfRepayments() const noexcept
{
    return defaultNumberOfRepayments_;
}
void LoanProduct::setDefaultNumberOfRepayments(const int32_t &pDefaultNumberOfRepayments) noexcept
{
    defaultNumberOfRepayments_ = std::make_shared<int32_t>(pDefaultNumberOfRepayments);
    dirtyFlag_[11] = true;
}

const int32_t &LoanProduct::getValueOfMaxNumberOfRepayments() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(maxNumberOfRepayments_)
        return *maxNumberOfRepayments_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getMaxNumberOfRepayments() const noexcept
{
    return maxNumberOfRepayments_;
}
void LoanProduct::setMaxNumberOfRepayments(const int32_t &pMaxNumberOfRepayments) noexcept
{
    maxNumberOfRepayments_ = std::make_shared<int32_t>(pMaxNumberOfRepayments);
    dirtyFlag_[12] = true;
}
void LoanProduct::setMaxNumberOfRepaymentsToNull() noexcept
{
    maxNumberOfRepayments_.reset();
    dirtyFlag_[12] = true;
}

const int32_t &LoanProduct::getValueOfRepaymentEvery() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(repaymentEvery_)
        return *repaymentEvery_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getRepaymentEvery() const noexcept
{
    return repaymentEvery_;
}
void LoanProduct::setRepaymentEvery(const int32_t &pRepaymentEvery) noexcept
{
    repaymentEvery_ = std::make_shared<int32_t>(pRepaymentEvery);
    dirtyFlag_[13] = true;
}

const int32_t &LoanProduct::getValueOfRepaymentFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(repaymentFrequencyType_)
        return *repaymentFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getRepaymentFrequencyType() const noexcept
{
    return repaymentFrequencyType_;
}
void LoanProduct::setRepaymentFrequencyType(const int32_t &pRepaymentFrequencyType) noexcept
{
    repaymentFrequencyType_ = std::make_shared<int32_t>(pRepaymentFrequencyType);
    dirtyFlag_[14] = true;
}

const std::string &LoanProduct::getValueOfMinInterestRatePerPeriod() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minInterestRatePerPeriod_)
        return *minInterestRatePerPeriod_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getMinInterestRatePerPeriod() const noexcept
{
    return minInterestRatePerPeriod_;
}
void LoanProduct::setMinInterestRatePerPeriod(const std::string &pMinInterestRatePerPeriod) noexcept
{
    minInterestRatePerPeriod_ = std::make_shared<std::string>(pMinInterestRatePerPeriod);
    dirtyFlag_[15] = true;
}
void LoanProduct::setMinInterestRatePerPeriod(std::string &&pMinInterestRatePerPeriod) noexcept
{
    minInterestRatePerPeriod_ = std::make_shared<std::string>(std::move(pMinInterestRatePerPeriod));
    dirtyFlag_[15] = true;
}
void LoanProduct::setMinInterestRatePerPeriodToNull() noexcept
{
    minInterestRatePerPeriod_.reset();
    dirtyFlag_[15] = true;
}

const std::string &LoanProduct::getValueOfDefaultInterestRatePerPeriod() const noexcept
{
    static const std::string defaultValue = std::string();
    if(defaultInterestRatePerPeriod_)
        return *defaultInterestRatePerPeriod_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getDefaultInterestRatePerPeriod() const noexcept
{
    return defaultInterestRatePerPeriod_;
}
void LoanProduct::setDefaultInterestRatePerPeriod(const std::string &pDefaultInterestRatePerPeriod) noexcept
{
    defaultInterestRatePerPeriod_ = std::make_shared<std::string>(pDefaultInterestRatePerPeriod);
    dirtyFlag_[16] = true;
}
void LoanProduct::setDefaultInterestRatePerPeriod(std::string &&pDefaultInterestRatePerPeriod) noexcept
{
    defaultInterestRatePerPeriod_ = std::make_shared<std::string>(std::move(pDefaultInterestRatePerPeriod));
    dirtyFlag_[16] = true;
}

const std::string &LoanProduct::getValueOfMaxInterestRatePerPeriod() const noexcept
{
    static const std::string defaultValue = std::string();
    if(maxInterestRatePerPeriod_)
        return *maxInterestRatePerPeriod_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getMaxInterestRatePerPeriod() const noexcept
{
    return maxInterestRatePerPeriod_;
}
void LoanProduct::setMaxInterestRatePerPeriod(const std::string &pMaxInterestRatePerPeriod) noexcept
{
    maxInterestRatePerPeriod_ = std::make_shared<std::string>(pMaxInterestRatePerPeriod);
    dirtyFlag_[17] = true;
}
void LoanProduct::setMaxInterestRatePerPeriod(std::string &&pMaxInterestRatePerPeriod) noexcept
{
    maxInterestRatePerPeriod_ = std::make_shared<std::string>(std::move(pMaxInterestRatePerPeriod));
    dirtyFlag_[17] = true;
}
void LoanProduct::setMaxInterestRatePerPeriodToNull() noexcept
{
    maxInterestRatePerPeriod_.reset();
    dirtyFlag_[17] = true;
}

const int32_t &LoanProduct::getValueOfInterestPeriodFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestPeriodFrequencyType_)
        return *interestPeriodFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getInterestPeriodFrequencyType() const noexcept
{
    return interestPeriodFrequencyType_;
}
void LoanProduct::setInterestPeriodFrequencyType(const int32_t &pInterestPeriodFrequencyType) noexcept
{
    interestPeriodFrequencyType_ = std::make_shared<int32_t>(pInterestPeriodFrequencyType);
    dirtyFlag_[18] = true;
}

const std::string &LoanProduct::getValueOfAnnualNominalInterestRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(annualNominalInterestRate_)
        return *annualNominalInterestRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getAnnualNominalInterestRate() const noexcept
{
    return annualNominalInterestRate_;
}
void LoanProduct::setAnnualNominalInterestRate(const std::string &pAnnualNominalInterestRate) noexcept
{
    annualNominalInterestRate_ = std::make_shared<std::string>(pAnnualNominalInterestRate);
    dirtyFlag_[19] = true;
}
void LoanProduct::setAnnualNominalInterestRate(std::string &&pAnnualNominalInterestRate) noexcept
{
    annualNominalInterestRate_ = std::make_shared<std::string>(std::move(pAnnualNominalInterestRate));
    dirtyFlag_[19] = true;
}

const int32_t &LoanProduct::getValueOfInterestMethod() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestMethod_)
        return *interestMethod_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getInterestMethod() const noexcept
{
    return interestMethod_;
}
void LoanProduct::setInterestMethod(const int32_t &pInterestMethod) noexcept
{
    interestMethod_ = std::make_shared<int32_t>(pInterestMethod);
    dirtyFlag_[20] = true;
}

const int32_t &LoanProduct::getValueOfInterestCalculationPeriodType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCalculationPeriodType_)
        return *interestCalculationPeriodType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getInterestCalculationPeriodType() const noexcept
{
    return interestCalculationPeriodType_;
}
void LoanProduct::setInterestCalculationPeriodType(const int32_t &pInterestCalculationPeriodType) noexcept
{
    interestCalculationPeriodType_ = std::make_shared<int32_t>(pInterestCalculationPeriodType);
    dirtyFlag_[21] = true;
}

const int32_t &LoanProduct::getValueOfAmortizationType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(amortizationType_)
        return *amortizationType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getAmortizationType() const noexcept
{
    return amortizationType_;
}
void LoanProduct::setAmortizationType(const int32_t &pAmortizationType) noexcept
{
    amortizationType_ = std::make_shared<int32_t>(pAmortizationType);
    dirtyFlag_[22] = true;
}

const std::string &LoanProduct::getValueOfTransactionProcessingStrategy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transactionProcessingStrategy_)
        return *transactionProcessingStrategy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getTransactionProcessingStrategy() const noexcept
{
    return transactionProcessingStrategy_;
}
void LoanProduct::setTransactionProcessingStrategy(const std::string &pTransactionProcessingStrategy) noexcept
{
    transactionProcessingStrategy_ = std::make_shared<std::string>(pTransactionProcessingStrategy);
    dirtyFlag_[23] = true;
}
void LoanProduct::setTransactionProcessingStrategy(std::string &&pTransactionProcessingStrategy) noexcept
{
    transactionProcessingStrategy_ = std::make_shared<std::string>(std::move(pTransactionProcessingStrategy));
    dirtyFlag_[23] = true;
}

const int32_t &LoanProduct::getValueOfGraceOnPrincipalPayment() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnPrincipalPayment_)
        return *graceOnPrincipalPayment_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getGraceOnPrincipalPayment() const noexcept
{
    return graceOnPrincipalPayment_;
}
void LoanProduct::setGraceOnPrincipalPayment(const int32_t &pGraceOnPrincipalPayment) noexcept
{
    graceOnPrincipalPayment_ = std::make_shared<int32_t>(pGraceOnPrincipalPayment);
    dirtyFlag_[24] = true;
}

const int32_t &LoanProduct::getValueOfGraceOnInterestPayment() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnInterestPayment_)
        return *graceOnInterestPayment_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getGraceOnInterestPayment() const noexcept
{
    return graceOnInterestPayment_;
}
void LoanProduct::setGraceOnInterestPayment(const int32_t &pGraceOnInterestPayment) noexcept
{
    graceOnInterestPayment_ = std::make_shared<int32_t>(pGraceOnInterestPayment);
    dirtyFlag_[25] = true;
}

const int32_t &LoanProduct::getValueOfGraceOnInterestCharged() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnInterestCharged_)
        return *graceOnInterestCharged_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getGraceOnInterestCharged() const noexcept
{
    return graceOnInterestCharged_;
}
void LoanProduct::setGraceOnInterestCharged(const int32_t &pGraceOnInterestCharged) noexcept
{
    graceOnInterestCharged_ = std::make_shared<int32_t>(pGraceOnInterestCharged);
    dirtyFlag_[26] = true;
}

const int32_t &LoanProduct::getValueOfGraceOnArrearsAgeing() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnArrearsAgeing_)
        return *graceOnArrearsAgeing_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getGraceOnArrearsAgeing() const noexcept
{
    return graceOnArrearsAgeing_;
}
void LoanProduct::setGraceOnArrearsAgeing(const int32_t &pGraceOnArrearsAgeing) noexcept
{
    graceOnArrearsAgeing_ = std::make_shared<int32_t>(pGraceOnArrearsAgeing);
    dirtyFlag_[27] = true;
}

const int32_t &LoanProduct::getValueOfOverdueDaysForNpa() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(overdueDaysForNpa_)
        return *overdueDaysForNpa_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getOverdueDaysForNpa() const noexcept
{
    return overdueDaysForNpa_;
}
void LoanProduct::setOverdueDaysForNpa(const int32_t &pOverdueDaysForNpa) noexcept
{
    overdueDaysForNpa_ = std::make_shared<int32_t>(pOverdueDaysForNpa);
    dirtyFlag_[28] = true;
}

const int32_t &LoanProduct::getValueOfDaysInYearType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(daysInYearType_)
        return *daysInYearType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getDaysInYearType() const noexcept
{
    return daysInYearType_;
}
void LoanProduct::setDaysInYearType(const int32_t &pDaysInYearType) noexcept
{
    daysInYearType_ = std::make_shared<int32_t>(pDaysInYearType);
    dirtyFlag_[29] = true;
}

const int32_t &LoanProduct::getValueOfDaysInMonthType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(daysInMonthType_)
        return *daysInMonthType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getDaysInMonthType() const noexcept
{
    return daysInMonthType_;
}
void LoanProduct::setDaysInMonthType(const int32_t &pDaysInMonthType) noexcept
{
    daysInMonthType_ = std::make_shared<int32_t>(pDaysInMonthType);
    dirtyFlag_[30] = true;
}

const int32_t &LoanProduct::getValueOfMinDaysBetweenDisbursalAndFirstRepayment() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(minDaysBetweenDisbursalAndFirstRepayment_)
        return *minDaysBetweenDisbursalAndFirstRepayment_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getMinDaysBetweenDisbursalAndFirstRepayment() const noexcept
{
    return minDaysBetweenDisbursalAndFirstRepayment_;
}
void LoanProduct::setMinDaysBetweenDisbursalAndFirstRepayment(const int32_t &pMinDaysBetweenDisbursalAndFirstRepayment) noexcept
{
    minDaysBetweenDisbursalAndFirstRepayment_ = std::make_shared<int32_t>(pMinDaysBetweenDisbursalAndFirstRepayment);
    dirtyFlag_[31] = true;
}

const bool &LoanProduct::getValueOfAllowPartialPeriodInterest() const noexcept
{
    static const bool defaultValue = bool();
    if(allowPartialPeriodInterest_)
        return *allowPartialPeriodInterest_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanProduct::getAllowPartialPeriodInterest() const noexcept
{
    return allowPartialPeriodInterest_;
}
void LoanProduct::setAllowPartialPeriodInterest(const bool &pAllowPartialPeriodInterest) noexcept
{
    allowPartialPeriodInterest_ = std::make_shared<bool>(pAllowPartialPeriodInterest);
    dirtyFlag_[32] = true;
}

const bool &LoanProduct::getValueOfIsLinkedToFloatingRate() const noexcept
{
    static const bool defaultValue = bool();
    if(isLinkedToFloatingRate_)
        return *isLinkedToFloatingRate_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanProduct::getIsLinkedToFloatingRate() const noexcept
{
    return isLinkedToFloatingRate_;
}
void LoanProduct::setIsLinkedToFloatingRate(const bool &pIsLinkedToFloatingRate) noexcept
{
    isLinkedToFloatingRate_ = std::make_shared<bool>(pIsLinkedToFloatingRate);
    dirtyFlag_[33] = true;
}

const std::string &LoanProduct::getValueOfFloatingRateId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(floatingRateId_)
        return *floatingRateId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getFloatingRateId() const noexcept
{
    return floatingRateId_;
}
void LoanProduct::setFloatingRateId(const std::string &pFloatingRateId) noexcept
{
    floatingRateId_ = std::make_shared<std::string>(pFloatingRateId);
    dirtyFlag_[34] = true;
}
void LoanProduct::setFloatingRateId(std::string &&pFloatingRateId) noexcept
{
    floatingRateId_ = std::make_shared<std::string>(std::move(pFloatingRateId));
    dirtyFlag_[34] = true;
}
void LoanProduct::setFloatingRateIdToNull() noexcept
{
    floatingRateId_.reset();
    dirtyFlag_[34] = true;
}

const std::string &LoanProduct::getValueOfDefaultDifferentialLendingRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(defaultDifferentialLendingRate_)
        return *defaultDifferentialLendingRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getDefaultDifferentialLendingRate() const noexcept
{
    return defaultDifferentialLendingRate_;
}
void LoanProduct::setDefaultDifferentialLendingRate(const std::string &pDefaultDifferentialLendingRate) noexcept
{
    defaultDifferentialLendingRate_ = std::make_shared<std::string>(pDefaultDifferentialLendingRate);
    dirtyFlag_[35] = true;
}
void LoanProduct::setDefaultDifferentialLendingRate(std::string &&pDefaultDifferentialLendingRate) noexcept
{
    defaultDifferentialLendingRate_ = std::make_shared<std::string>(std::move(pDefaultDifferentialLendingRate));
    dirtyFlag_[35] = true;
}
void LoanProduct::setDefaultDifferentialLendingRateToNull() noexcept
{
    defaultDifferentialLendingRate_.reset();
    dirtyFlag_[35] = true;
}

const bool &LoanProduct::getValueOfIsEqualAmortization() const noexcept
{
    static const bool defaultValue = bool();
    if(isEqualAmortization_)
        return *isEqualAmortization_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanProduct::getIsEqualAmortization() const noexcept
{
    return isEqualAmortization_;
}
void LoanProduct::setIsEqualAmortization(const bool &pIsEqualAmortization) noexcept
{
    isEqualAmortization_ = std::make_shared<bool>(pIsEqualAmortization);
    dirtyFlag_[36] = true;
}

const bool &LoanProduct::getValueOfAllowAttributeOverrides() const noexcept
{
    static const bool defaultValue = bool();
    if(allowAttributeOverrides_)
        return *allowAttributeOverrides_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanProduct::getAllowAttributeOverrides() const noexcept
{
    return allowAttributeOverrides_;
}
void LoanProduct::setAllowAttributeOverrides(const bool &pAllowAttributeOverrides) noexcept
{
    allowAttributeOverrides_ = std::make_shared<bool>(pAllowAttributeOverrides);
    dirtyFlag_[37] = true;
}

const bool &LoanProduct::getValueOfCanUseForTopup() const noexcept
{
    static const bool defaultValue = bool();
    if(canUseForTopup_)
        return *canUseForTopup_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanProduct::getCanUseForTopup() const noexcept
{
    return canUseForTopup_;
}
void LoanProduct::setCanUseForTopup(const bool &pCanUseForTopup) noexcept
{
    canUseForTopup_ = std::make_shared<bool>(pCanUseForTopup);
    dirtyFlag_[38] = true;
}

const ::trantor::Date &LoanProduct::getValueOfCloseDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(closeDate_)
        return *closeDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanProduct::getCloseDate() const noexcept
{
    return closeDate_;
}
void LoanProduct::setCloseDate(const ::trantor::Date &pCloseDate) noexcept
{
    closeDate_ = std::make_shared<::trantor::Date>(pCloseDate);
    dirtyFlag_[39] = true;
}
void LoanProduct::setCloseDateToNull() noexcept
{
    closeDate_.reset();
    dirtyFlag_[39] = true;
}

const ::trantor::Date &LoanProduct::getValueOfStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDate_)
        return *startDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanProduct::getStartDate() const noexcept
{
    return startDate_;
}
void LoanProduct::setStartDate(const ::trantor::Date &pStartDate) noexcept
{
    startDate_ = std::make_shared<::trantor::Date>(pStartDate);
    dirtyFlag_[40] = true;
}
void LoanProduct::setStartDateToNull() noexcept
{
    startDate_.reset();
    dirtyFlag_[40] = true;
}

const std::string &LoanProduct::getValueOfDelinquencyBucketId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(delinquencyBucketId_)
        return *delinquencyBucketId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getDelinquencyBucketId() const noexcept
{
    return delinquencyBucketId_;
}
void LoanProduct::setDelinquencyBucketId(const std::string &pDelinquencyBucketId) noexcept
{
    delinquencyBucketId_ = std::make_shared<std::string>(pDelinquencyBucketId);
    dirtyFlag_[41] = true;
}
void LoanProduct::setDelinquencyBucketId(std::string &&pDelinquencyBucketId) noexcept
{
    delinquencyBucketId_ = std::make_shared<std::string>(std::move(pDelinquencyBucketId));
    dirtyFlag_[41] = true;
}
void LoanProduct::setDelinquencyBucketIdToNull() noexcept
{
    delinquencyBucketId_.reset();
    dirtyFlag_[41] = true;
}

const int32_t &LoanProduct::getValueOfAccountingType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(accountingType_)
        return *accountingType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanProduct::getAccountingType() const noexcept
{
    return accountingType_;
}
void LoanProduct::setAccountingType(const int32_t &pAccountingType) noexcept
{
    accountingType_ = std::make_shared<int32_t>(pAccountingType);
    dirtyFlag_[42] = true;
}

const std::string &LoanProduct::getValueOfFundSourceAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fundSourceAccountId_)
        return *fundSourceAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getFundSourceAccountId() const noexcept
{
    return fundSourceAccountId_;
}
void LoanProduct::setFundSourceAccountId(const std::string &pFundSourceAccountId) noexcept
{
    fundSourceAccountId_ = std::make_shared<std::string>(pFundSourceAccountId);
    dirtyFlag_[43] = true;
}
void LoanProduct::setFundSourceAccountId(std::string &&pFundSourceAccountId) noexcept
{
    fundSourceAccountId_ = std::make_shared<std::string>(std::move(pFundSourceAccountId));
    dirtyFlag_[43] = true;
}
void LoanProduct::setFundSourceAccountIdToNull() noexcept
{
    fundSourceAccountId_.reset();
    dirtyFlag_[43] = true;
}

const std::string &LoanProduct::getValueOfLoanPortfolioAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanPortfolioAccountId_)
        return *loanPortfolioAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getLoanPortfolioAccountId() const noexcept
{
    return loanPortfolioAccountId_;
}
void LoanProduct::setLoanPortfolioAccountId(const std::string &pLoanPortfolioAccountId) noexcept
{
    loanPortfolioAccountId_ = std::make_shared<std::string>(pLoanPortfolioAccountId);
    dirtyFlag_[44] = true;
}
void LoanProduct::setLoanPortfolioAccountId(std::string &&pLoanPortfolioAccountId) noexcept
{
    loanPortfolioAccountId_ = std::make_shared<std::string>(std::move(pLoanPortfolioAccountId));
    dirtyFlag_[44] = true;
}
void LoanProduct::setLoanPortfolioAccountIdToNull() noexcept
{
    loanPortfolioAccountId_.reset();
    dirtyFlag_[44] = true;
}

const std::string &LoanProduct::getValueOfInterestOnLoanAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestOnLoanAccountId_)
        return *interestOnLoanAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getInterestOnLoanAccountId() const noexcept
{
    return interestOnLoanAccountId_;
}
void LoanProduct::setInterestOnLoanAccountId(const std::string &pInterestOnLoanAccountId) noexcept
{
    interestOnLoanAccountId_ = std::make_shared<std::string>(pInterestOnLoanAccountId);
    dirtyFlag_[45] = true;
}
void LoanProduct::setInterestOnLoanAccountId(std::string &&pInterestOnLoanAccountId) noexcept
{
    interestOnLoanAccountId_ = std::make_shared<std::string>(std::move(pInterestOnLoanAccountId));
    dirtyFlag_[45] = true;
}
void LoanProduct::setInterestOnLoanAccountIdToNull() noexcept
{
    interestOnLoanAccountId_.reset();
    dirtyFlag_[45] = true;
}

const std::string &LoanProduct::getValueOfIncomeFromFeesAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(incomeFromFeesAccountId_)
        return *incomeFromFeesAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getIncomeFromFeesAccountId() const noexcept
{
    return incomeFromFeesAccountId_;
}
void LoanProduct::setIncomeFromFeesAccountId(const std::string &pIncomeFromFeesAccountId) noexcept
{
    incomeFromFeesAccountId_ = std::make_shared<std::string>(pIncomeFromFeesAccountId);
    dirtyFlag_[46] = true;
}
void LoanProduct::setIncomeFromFeesAccountId(std::string &&pIncomeFromFeesAccountId) noexcept
{
    incomeFromFeesAccountId_ = std::make_shared<std::string>(std::move(pIncomeFromFeesAccountId));
    dirtyFlag_[46] = true;
}
void LoanProduct::setIncomeFromFeesAccountIdToNull() noexcept
{
    incomeFromFeesAccountId_.reset();
    dirtyFlag_[46] = true;
}

const std::string &LoanProduct::getValueOfIncomeFromPenaltiesAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(incomeFromPenaltiesAccountId_)
        return *incomeFromPenaltiesAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getIncomeFromPenaltiesAccountId() const noexcept
{
    return incomeFromPenaltiesAccountId_;
}
void LoanProduct::setIncomeFromPenaltiesAccountId(const std::string &pIncomeFromPenaltiesAccountId) noexcept
{
    incomeFromPenaltiesAccountId_ = std::make_shared<std::string>(pIncomeFromPenaltiesAccountId);
    dirtyFlag_[47] = true;
}
void LoanProduct::setIncomeFromPenaltiesAccountId(std::string &&pIncomeFromPenaltiesAccountId) noexcept
{
    incomeFromPenaltiesAccountId_ = std::make_shared<std::string>(std::move(pIncomeFromPenaltiesAccountId));
    dirtyFlag_[47] = true;
}
void LoanProduct::setIncomeFromPenaltiesAccountIdToNull() noexcept
{
    incomeFromPenaltiesAccountId_.reset();
    dirtyFlag_[47] = true;
}

const std::string &LoanProduct::getValueOfIncomeFromRecoveryAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(incomeFromRecoveryAccountId_)
        return *incomeFromRecoveryAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getIncomeFromRecoveryAccountId() const noexcept
{
    return incomeFromRecoveryAccountId_;
}
void LoanProduct::setIncomeFromRecoveryAccountId(const std::string &pIncomeFromRecoveryAccountId) noexcept
{
    incomeFromRecoveryAccountId_ = std::make_shared<std::string>(pIncomeFromRecoveryAccountId);
    dirtyFlag_[48] = true;
}
void LoanProduct::setIncomeFromRecoveryAccountId(std::string &&pIncomeFromRecoveryAccountId) noexcept
{
    incomeFromRecoveryAccountId_ = std::make_shared<std::string>(std::move(pIncomeFromRecoveryAccountId));
    dirtyFlag_[48] = true;
}
void LoanProduct::setIncomeFromRecoveryAccountIdToNull() noexcept
{
    incomeFromRecoveryAccountId_.reset();
    dirtyFlag_[48] = true;
}

const std::string &LoanProduct::getValueOfLossesWrittenOffAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lossesWrittenOffAccountId_)
        return *lossesWrittenOffAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getLossesWrittenOffAccountId() const noexcept
{
    return lossesWrittenOffAccountId_;
}
void LoanProduct::setLossesWrittenOffAccountId(const std::string &pLossesWrittenOffAccountId) noexcept
{
    lossesWrittenOffAccountId_ = std::make_shared<std::string>(pLossesWrittenOffAccountId);
    dirtyFlag_[49] = true;
}
void LoanProduct::setLossesWrittenOffAccountId(std::string &&pLossesWrittenOffAccountId) noexcept
{
    lossesWrittenOffAccountId_ = std::make_shared<std::string>(std::move(pLossesWrittenOffAccountId));
    dirtyFlag_[49] = true;
}
void LoanProduct::setLossesWrittenOffAccountIdToNull() noexcept
{
    lossesWrittenOffAccountId_.reset();
    dirtyFlag_[49] = true;
}

const std::string &LoanProduct::getValueOfOverpaymentLiabilityAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(overpaymentLiabilityAccountId_)
        return *overpaymentLiabilityAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getOverpaymentLiabilityAccountId() const noexcept
{
    return overpaymentLiabilityAccountId_;
}
void LoanProduct::setOverpaymentLiabilityAccountId(const std::string &pOverpaymentLiabilityAccountId) noexcept
{
    overpaymentLiabilityAccountId_ = std::make_shared<std::string>(pOverpaymentLiabilityAccountId);
    dirtyFlag_[50] = true;
}
void LoanProduct::setOverpaymentLiabilityAccountId(std::string &&pOverpaymentLiabilityAccountId) noexcept
{
    overpaymentLiabilityAccountId_ = std::make_shared<std::string>(std::move(pOverpaymentLiabilityAccountId));
    dirtyFlag_[50] = true;
}
void LoanProduct::setOverpaymentLiabilityAccountIdToNull() noexcept
{
    overpaymentLiabilityAccountId_.reset();
    dirtyFlag_[50] = true;
}

const std::string &LoanProduct::getValueOfInterestReceivableAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestReceivableAccountId_)
        return *interestReceivableAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getInterestReceivableAccountId() const noexcept
{
    return interestReceivableAccountId_;
}
void LoanProduct::setInterestReceivableAccountId(const std::string &pInterestReceivableAccountId) noexcept
{
    interestReceivableAccountId_ = std::make_shared<std::string>(pInterestReceivableAccountId);
    dirtyFlag_[51] = true;
}
void LoanProduct::setInterestReceivableAccountId(std::string &&pInterestReceivableAccountId) noexcept
{
    interestReceivableAccountId_ = std::make_shared<std::string>(std::move(pInterestReceivableAccountId));
    dirtyFlag_[51] = true;
}
void LoanProduct::setInterestReceivableAccountIdToNull() noexcept
{
    interestReceivableAccountId_.reset();
    dirtyFlag_[51] = true;
}

const std::string &LoanProduct::getValueOfFeeReceivableAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeReceivableAccountId_)
        return *feeReceivableAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getFeeReceivableAccountId() const noexcept
{
    return feeReceivableAccountId_;
}
void LoanProduct::setFeeReceivableAccountId(const std::string &pFeeReceivableAccountId) noexcept
{
    feeReceivableAccountId_ = std::make_shared<std::string>(pFeeReceivableAccountId);
    dirtyFlag_[52] = true;
}
void LoanProduct::setFeeReceivableAccountId(std::string &&pFeeReceivableAccountId) noexcept
{
    feeReceivableAccountId_ = std::make_shared<std::string>(std::move(pFeeReceivableAccountId));
    dirtyFlag_[52] = true;
}
void LoanProduct::setFeeReceivableAccountIdToNull() noexcept
{
    feeReceivableAccountId_.reset();
    dirtyFlag_[52] = true;
}

const std::string &LoanProduct::getValueOfPenaltyReceivableAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyReceivableAccountId_)
        return *penaltyReceivableAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getPenaltyReceivableAccountId() const noexcept
{
    return penaltyReceivableAccountId_;
}
void LoanProduct::setPenaltyReceivableAccountId(const std::string &pPenaltyReceivableAccountId) noexcept
{
    penaltyReceivableAccountId_ = std::make_shared<std::string>(pPenaltyReceivableAccountId);
    dirtyFlag_[53] = true;
}
void LoanProduct::setPenaltyReceivableAccountId(std::string &&pPenaltyReceivableAccountId) noexcept
{
    penaltyReceivableAccountId_ = std::make_shared<std::string>(std::move(pPenaltyReceivableAccountId));
    dirtyFlag_[53] = true;
}
void LoanProduct::setPenaltyReceivableAccountIdToNull() noexcept
{
    penaltyReceivableAccountId_.reset();
    dirtyFlag_[53] = true;
}

const bool &LoanProduct::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanProduct::getIsActive() const noexcept
{
    return isActive_;
}
void LoanProduct::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[54] = true;
}

const std::string &LoanProduct::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getCreatedBy() const noexcept
{
    return createdBy_;
}
void LoanProduct::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[55] = true;
}
void LoanProduct::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[55] = true;
}
void LoanProduct::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[55] = true;
}

const ::trantor::Date &LoanProduct::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanProduct::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanProduct::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[56] = true;
}

const std::string &LoanProduct::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProduct::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void LoanProduct::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[57] = true;
}
void LoanProduct::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[57] = true;
}
void LoanProduct::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[57] = true;
}

const ::trantor::Date &LoanProduct::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanProduct::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void LoanProduct::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[58] = true;
}

void LoanProduct::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanProduct::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "short_name",
        "description",
        "fund_id",
        "currency_code",
        "currency_digits",
        "min_principal_amount",
        "default_principal_amount",
        "max_principal_amount",
        "min_number_of_repayments",
        "default_number_of_repayments",
        "max_number_of_repayments",
        "repayment_every",
        "repayment_frequency_type",
        "min_interest_rate_per_period",
        "default_interest_rate_per_period",
        "max_interest_rate_per_period",
        "interest_period_frequency_type",
        "annual_nominal_interest_rate",
        "interest_method",
        "interest_calculation_period_type",
        "amortization_type",
        "transaction_processing_strategy",
        "grace_on_principal_payment",
        "grace_on_interest_payment",
        "grace_on_interest_charged",
        "grace_on_arrears_ageing",
        "overdue_days_for_npa",
        "days_in_year_type",
        "days_in_month_type",
        "min_days_between_disbursal_and_first_repayment",
        "allow_partial_period_interest",
        "is_linked_to_floating_rate",
        "floating_rate_id",
        "default_differential_lending_rate",
        "is_equal_amortization",
        "allow_attribute_overrides",
        "can_use_for_topup",
        "close_date",
        "start_date",
        "delinquency_bucket_id",
        "accounting_type",
        "fund_source_account_id",
        "loan_portfolio_account_id",
        "interest_on_loan_account_id",
        "income_from_fees_account_id",
        "income_from_penalties_account_id",
        "income_from_recovery_account_id",
        "losses_written_off_account_id",
        "overpayment_liability_account_id",
        "interest_receivable_account_id",
        "fee_receivable_account_id",
        "penalty_receivable_account_id",
        "is_active",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void LoanProduct::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getShortName())
        {
            binder << getValueOfShortName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getMinPrincipalAmount())
        {
            binder << getValueOfMinPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getDefaultPrincipalAmount())
        {
            binder << getValueOfDefaultPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getMaxPrincipalAmount())
        {
            binder << getValueOfMaxPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getMinNumberOfRepayments())
        {
            binder << getValueOfMinNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getDefaultNumberOfRepayments())
        {
            binder << getValueOfDefaultNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getMaxNumberOfRepayments())
        {
            binder << getValueOfMaxNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getMinInterestRatePerPeriod())
        {
            binder << getValueOfMinInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getDefaultInterestRatePerPeriod())
        {
            binder << getValueOfDefaultInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getMaxInterestRatePerPeriod())
        {
            binder << getValueOfMaxInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
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
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
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
    if(dirtyFlag_[22])
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
    if(dirtyFlag_[23])
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
    if(dirtyFlag_[24])
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
    if(dirtyFlag_[25])
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
    if(dirtyFlag_[26])
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
    if(dirtyFlag_[27])
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
    if(dirtyFlag_[28])
    {
        if(getOverdueDaysForNpa())
        {
            binder << getValueOfOverdueDaysForNpa();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
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
    if(dirtyFlag_[30])
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
    if(dirtyFlag_[31])
    {
        if(getMinDaysBetweenDisbursalAndFirstRepayment())
        {
            binder << getValueOfMinDaysBetweenDisbursalAndFirstRepayment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getAllowPartialPeriodInterest())
        {
            binder << getValueOfAllowPartialPeriodInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getIsLinkedToFloatingRate())
        {
            binder << getValueOfIsLinkedToFloatingRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
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
    if(dirtyFlag_[35])
    {
        if(getDefaultDifferentialLendingRate())
        {
            binder << getValueOfDefaultDifferentialLendingRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
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
    if(dirtyFlag_[37])
    {
        if(getAllowAttributeOverrides())
        {
            binder << getValueOfAllowAttributeOverrides();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getCanUseForTopup())
        {
            binder << getValueOfCanUseForTopup();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getCloseDate())
        {
            binder << getValueOfCloseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
    {
        if(getDelinquencyBucketId())
        {
            binder << getValueOfDelinquencyBucketId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getAccountingType())
        {
            binder << getValueOfAccountingType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getFundSourceAccountId())
        {
            binder << getValueOfFundSourceAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getLoanPortfolioAccountId())
        {
            binder << getValueOfLoanPortfolioAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getInterestOnLoanAccountId())
        {
            binder << getValueOfInterestOnLoanAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getIncomeFromFeesAccountId())
        {
            binder << getValueOfIncomeFromFeesAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getIncomeFromPenaltiesAccountId())
        {
            binder << getValueOfIncomeFromPenaltiesAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getIncomeFromRecoveryAccountId())
        {
            binder << getValueOfIncomeFromRecoveryAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getLossesWrittenOffAccountId())
        {
            binder << getValueOfLossesWrittenOffAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getOverpaymentLiabilityAccountId())
        {
            binder << getValueOfOverpaymentLiabilityAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getInterestReceivableAccountId())
        {
            binder << getValueOfInterestReceivableAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getFeeReceivableAccountId())
        {
            binder << getValueOfFeeReceivableAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[53])
    {
        if(getPenaltyReceivableAccountId())
        {
            binder << getValueOfPenaltyReceivableAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[54])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[55])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[56])
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
    if(dirtyFlag_[57])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[58])
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

const std::vector<std::string> LoanProduct::updateColumns() const
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
    return ret;
}

void LoanProduct::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getShortName())
        {
            binder << getValueOfShortName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getMinPrincipalAmount())
        {
            binder << getValueOfMinPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getDefaultPrincipalAmount())
        {
            binder << getValueOfDefaultPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getMaxPrincipalAmount())
        {
            binder << getValueOfMaxPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getMinNumberOfRepayments())
        {
            binder << getValueOfMinNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getDefaultNumberOfRepayments())
        {
            binder << getValueOfDefaultNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getMaxNumberOfRepayments())
        {
            binder << getValueOfMaxNumberOfRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getMinInterestRatePerPeriod())
        {
            binder << getValueOfMinInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getDefaultInterestRatePerPeriod())
        {
            binder << getValueOfDefaultInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getMaxInterestRatePerPeriod())
        {
            binder << getValueOfMaxInterestRatePerPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
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
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
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
    if(dirtyFlag_[22])
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
    if(dirtyFlag_[23])
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
    if(dirtyFlag_[24])
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
    if(dirtyFlag_[25])
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
    if(dirtyFlag_[26])
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
    if(dirtyFlag_[27])
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
    if(dirtyFlag_[28])
    {
        if(getOverdueDaysForNpa())
        {
            binder << getValueOfOverdueDaysForNpa();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
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
    if(dirtyFlag_[30])
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
    if(dirtyFlag_[31])
    {
        if(getMinDaysBetweenDisbursalAndFirstRepayment())
        {
            binder << getValueOfMinDaysBetweenDisbursalAndFirstRepayment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getAllowPartialPeriodInterest())
        {
            binder << getValueOfAllowPartialPeriodInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getIsLinkedToFloatingRate())
        {
            binder << getValueOfIsLinkedToFloatingRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
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
    if(dirtyFlag_[35])
    {
        if(getDefaultDifferentialLendingRate())
        {
            binder << getValueOfDefaultDifferentialLendingRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
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
    if(dirtyFlag_[37])
    {
        if(getAllowAttributeOverrides())
        {
            binder << getValueOfAllowAttributeOverrides();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getCanUseForTopup())
        {
            binder << getValueOfCanUseForTopup();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getCloseDate())
        {
            binder << getValueOfCloseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
    {
        if(getDelinquencyBucketId())
        {
            binder << getValueOfDelinquencyBucketId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getAccountingType())
        {
            binder << getValueOfAccountingType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getFundSourceAccountId())
        {
            binder << getValueOfFundSourceAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getLoanPortfolioAccountId())
        {
            binder << getValueOfLoanPortfolioAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getInterestOnLoanAccountId())
        {
            binder << getValueOfInterestOnLoanAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getIncomeFromFeesAccountId())
        {
            binder << getValueOfIncomeFromFeesAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getIncomeFromPenaltiesAccountId())
        {
            binder << getValueOfIncomeFromPenaltiesAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getIncomeFromRecoveryAccountId())
        {
            binder << getValueOfIncomeFromRecoveryAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getLossesWrittenOffAccountId())
        {
            binder << getValueOfLossesWrittenOffAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getOverpaymentLiabilityAccountId())
        {
            binder << getValueOfOverpaymentLiabilityAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getInterestReceivableAccountId())
        {
            binder << getValueOfInterestReceivableAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getFeeReceivableAccountId())
        {
            binder << getValueOfFeeReceivableAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[53])
    {
        if(getPenaltyReceivableAccountId())
        {
            binder << getValueOfPenaltyReceivableAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[54])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[55])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[56])
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
    if(dirtyFlag_[57])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[58])
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
