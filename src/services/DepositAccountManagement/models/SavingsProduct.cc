/**
 *  SavingsProduct.cc
 *
 *  See SavingsProduct.h for the hand-authored-subset note.
 *
 */

#include "SavingsProduct.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string SavingsProduct::Cols::_id = "\"id\"";
const std::string SavingsProduct::Cols::_business_id = "\"business_id\"";
const std::string SavingsProduct::Cols::_deposit_type = "\"deposit_type\"";
const std::string SavingsProduct::Cols::_name = "\"name\"";
const std::string SavingsProduct::Cols::_short_name = "\"short_name\"";
const std::string SavingsProduct::Cols::_description = "\"description\"";
const std::string SavingsProduct::Cols::_currency_code = "\"currency_code\"";
const std::string SavingsProduct::Cols::_digits_after_decimal = "\"digits_after_decimal\"";
const std::string SavingsProduct::Cols::_in_multiples_of = "\"in_multiples_of\"";
const std::string SavingsProduct::Cols::_nominal_annual_interest_rate = "\"nominal_annual_interest_rate\"";
const std::string SavingsProduct::Cols::_interest_compounding_period_type = "\"interest_compounding_period_type\"";
const std::string SavingsProduct::Cols::_interest_posting_period_type = "\"interest_posting_period_type\"";
const std::string SavingsProduct::Cols::_interest_calculation_type = "\"interest_calculation_type\"";
const std::string SavingsProduct::Cols::_interest_calculation_days_in_year_type = "\"interest_calculation_days_in_year_type\"";
const std::string SavingsProduct::Cols::_min_required_opening_balance = "\"min_required_opening_balance\"";
const std::string SavingsProduct::Cols::_lockin_period_frequency = "\"lockin_period_frequency\"";
const std::string SavingsProduct::Cols::_lockin_period_frequency_type = "\"lockin_period_frequency_type\"";
const std::string SavingsProduct::Cols::_withdrawal_fee_for_transfer = "\"withdrawal_fee_for_transfer\"";
const std::string SavingsProduct::Cols::_allow_overdraft = "\"allow_overdraft\"";
const std::string SavingsProduct::Cols::_overdraft_limit = "\"overdraft_limit\"";
const std::string SavingsProduct::Cols::_min_balance_for_interest_calculation = "\"min_balance_for_interest_calculation\"";
const std::string SavingsProduct::Cols::_min_required_balance = "\"min_required_balance\"";
const std::string SavingsProduct::Cols::_enforce_min_required_balance = "\"enforce_min_required_balance\"";
const std::string SavingsProduct::Cols::_is_dormancy_tracking_active = "\"is_dormancy_tracking_active\"";
const std::string SavingsProduct::Cols::_days_to_inactive = "\"days_to_inactive\"";
const std::string SavingsProduct::Cols::_days_to_dormancy = "\"days_to_dormancy\"";
const std::string SavingsProduct::Cols::_days_to_escheat = "\"days_to_escheat\"";
const std::string SavingsProduct::Cols::_accounting_type = "\"accounting_type\"";
const std::string SavingsProduct::Cols::_interest_rate_chart_id = "\"interest_rate_chart_id\"";
const std::string SavingsProduct::Cols::_pre_closure_penal_applicable = "\"pre_closure_penal_applicable\"";
const std::string SavingsProduct::Cols::_pre_closure_penal_interest = "\"pre_closure_penal_interest\"";
const std::string SavingsProduct::Cols::_pre_closure_penal_interest_on_type = "\"pre_closure_penal_interest_on_type\"";
const std::string SavingsProduct::Cols::_min_deposit_term = "\"min_deposit_term\"";
const std::string SavingsProduct::Cols::_min_deposit_term_type = "\"min_deposit_term_type\"";
const std::string SavingsProduct::Cols::_max_deposit_term = "\"max_deposit_term\"";
const std::string SavingsProduct::Cols::_max_deposit_term_type = "\"max_deposit_term_type\"";
const std::string SavingsProduct::Cols::_in_multiples_of_deposit_term = "\"in_multiples_of_deposit_term\"";
const std::string SavingsProduct::Cols::_in_multiples_of_deposit_term_type = "\"in_multiples_of_deposit_term_type\"";
const std::string SavingsProduct::Cols::_is_mandatory_deposit = "\"is_mandatory_deposit\"";
const std::string SavingsProduct::Cols::_allow_withdrawal = "\"allow_withdrawal\"";
const std::string SavingsProduct::Cols::_adjust_advance_towards_future_payments = "\"adjust_advance_towards_future_payments\"";
const std::string SavingsProduct::Cols::_is_active = "\"is_active\"";
const std::string SavingsProduct::Cols::_created_by = "\"created_by\"";
const std::string SavingsProduct::Cols::_created_at = "\"created_at\"";
const std::string SavingsProduct::Cols::_updated_by = "\"updated_by\"";
const std::string SavingsProduct::Cols::_updated_at = "\"updated_at\"";
const std::string SavingsProduct::primaryKeyName = "id";
const bool SavingsProduct::hasPrimaryKey = true;
const std::string SavingsProduct::tableName = "\"savings_product\"";

const std::vector<typename SavingsProduct::MetaData> SavingsProduct::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"deposit_type","int32_t","integer",4,0,0,1},
{"name","std::string","character varying",100,0,0,1},
{"short_name","std::string","character varying",4,0,0,1},
{"description","std::string","character varying",500,0,0,0},
{"currency_code","std::string","character varying",3,0,0,1},
{"digits_after_decimal","int32_t","integer",4,0,0,1},
{"in_multiples_of","int32_t","integer",4,0,0,1},
{"nominal_annual_interest_rate","std::string","numeric",0,0,0,1},
{"interest_compounding_period_type","int32_t","integer",4,0,0,1},
{"interest_posting_period_type","int32_t","integer",4,0,0,1},
{"interest_calculation_type","int32_t","integer",4,0,0,1},
{"interest_calculation_days_in_year_type","int32_t","integer",4,0,0,1},
{"min_required_opening_balance","std::string","numeric",0,0,0,0},
{"lockin_period_frequency","int32_t","integer",4,0,0,0},
{"lockin_period_frequency_type","int32_t","integer",4,0,0,0},
{"withdrawal_fee_for_transfer","bool","boolean",1,0,0,1},
{"allow_overdraft","bool","boolean",1,0,0,1},
{"overdraft_limit","std::string","numeric",0,0,0,0},
{"min_balance_for_interest_calculation","std::string","numeric",0,0,0,0},
{"min_required_balance","std::string","numeric",0,0,0,0},
{"enforce_min_required_balance","bool","boolean",1,0,0,1},
{"is_dormancy_tracking_active","bool","boolean",1,0,0,1},
{"days_to_inactive","int32_t","integer",4,0,0,0},
{"days_to_dormancy","int32_t","integer",4,0,0,0},
{"days_to_escheat","int32_t","integer",4,0,0,0},
{"accounting_type","int32_t","integer",4,0,0,1},
{"interest_rate_chart_id","std::string","uuid",0,0,0,0},
{"pre_closure_penal_applicable","bool","boolean",1,0,0,0},
{"pre_closure_penal_interest","std::string","numeric",0,0,0,0},
{"pre_closure_penal_interest_on_type","int32_t","integer",4,0,0,0},
{"min_deposit_term","int32_t","integer",4,0,0,0},
{"min_deposit_term_type","int32_t","integer",4,0,0,0},
{"max_deposit_term","int32_t","integer",4,0,0,0},
{"max_deposit_term_type","int32_t","integer",4,0,0,0},
{"in_multiples_of_deposit_term","int32_t","integer",4,0,0,0},
{"in_multiples_of_deposit_term_type","int32_t","integer",4,0,0,0},
{"is_mandatory_deposit","bool","boolean",1,0,0,0},
{"allow_withdrawal","bool","boolean",1,0,0,0},
{"adjust_advance_towards_future_payments","bool","boolean",1,0,0,0},
{"is_active","bool","boolean",1,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SavingsProduct::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SavingsProduct::SavingsProduct(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["business_id"].isNull())
        {
            businessId_=std::make_shared<std::string>(r["business_id"].as<std::string>());
        }
        if(!r["deposit_type"].isNull())
        {
            depositType_=std::make_shared<int32_t>(r["deposit_type"].as<int32_t>());
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
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["digits_after_decimal"].isNull())
        {
            digitsAfterDecimal_=std::make_shared<int32_t>(r["digits_after_decimal"].as<int32_t>());
        }
        if(!r["in_multiples_of"].isNull())
        {
            inMultiplesOf_=std::make_shared<int32_t>(r["in_multiples_of"].as<int32_t>());
        }
        if(!r["nominal_annual_interest_rate"].isNull())
        {
            nominalAnnualInterestRate_=std::make_shared<std::string>(r["nominal_annual_interest_rate"].as<std::string>());
        }
        if(!r["interest_compounding_period_type"].isNull())
        {
            interestCompoundingPeriodType_=std::make_shared<int32_t>(r["interest_compounding_period_type"].as<int32_t>());
        }
        if(!r["interest_posting_period_type"].isNull())
        {
            interestPostingPeriodType_=std::make_shared<int32_t>(r["interest_posting_period_type"].as<int32_t>());
        }
        if(!r["interest_calculation_type"].isNull())
        {
            interestCalculationType_=std::make_shared<int32_t>(r["interest_calculation_type"].as<int32_t>());
        }
        if(!r["interest_calculation_days_in_year_type"].isNull())
        {
            interestCalculationDaysInYearType_=std::make_shared<int32_t>(r["interest_calculation_days_in_year_type"].as<int32_t>());
        }
        if(!r["min_required_opening_balance"].isNull())
        {
            minRequiredOpeningBalance_=std::make_shared<std::string>(r["min_required_opening_balance"].as<std::string>());
        }
        if(!r["lockin_period_frequency"].isNull())
        {
            lockinPeriodFrequency_=std::make_shared<int32_t>(r["lockin_period_frequency"].as<int32_t>());
        }
        if(!r["lockin_period_frequency_type"].isNull())
        {
            lockinPeriodFrequencyType_=std::make_shared<int32_t>(r["lockin_period_frequency_type"].as<int32_t>());
        }
        if(!r["withdrawal_fee_for_transfer"].isNull())
        {
            withdrawalFeeForTransfer_=std::make_shared<bool>(r["withdrawal_fee_for_transfer"].as<bool>());
        }
        if(!r["allow_overdraft"].isNull())
        {
            allowOverdraft_=std::make_shared<bool>(r["allow_overdraft"].as<bool>());
        }
        if(!r["overdraft_limit"].isNull())
        {
            overdraftLimit_=std::make_shared<std::string>(r["overdraft_limit"].as<std::string>());
        }
        if(!r["min_balance_for_interest_calculation"].isNull())
        {
            minBalanceForInterestCalculation_=std::make_shared<std::string>(r["min_balance_for_interest_calculation"].as<std::string>());
        }
        if(!r["min_required_balance"].isNull())
        {
            minRequiredBalance_=std::make_shared<std::string>(r["min_required_balance"].as<std::string>());
        }
        if(!r["enforce_min_required_balance"].isNull())
        {
            enforceMinRequiredBalance_=std::make_shared<bool>(r["enforce_min_required_balance"].as<bool>());
        }
        if(!r["is_dormancy_tracking_active"].isNull())
        {
            isDormancyTrackingActive_=std::make_shared<bool>(r["is_dormancy_tracking_active"].as<bool>());
        }
        if(!r["days_to_inactive"].isNull())
        {
            daysToInactive_=std::make_shared<int32_t>(r["days_to_inactive"].as<int32_t>());
        }
        if(!r["days_to_dormancy"].isNull())
        {
            daysToDormancy_=std::make_shared<int32_t>(r["days_to_dormancy"].as<int32_t>());
        }
        if(!r["days_to_escheat"].isNull())
        {
            daysToEscheat_=std::make_shared<int32_t>(r["days_to_escheat"].as<int32_t>());
        }
        if(!r["accounting_type"].isNull())
        {
            accountingType_=std::make_shared<int32_t>(r["accounting_type"].as<int32_t>());
        }
        if(!r["interest_rate_chart_id"].isNull())
        {
            interestRateChartId_=std::make_shared<std::string>(r["interest_rate_chart_id"].as<std::string>());
        }
        if(!r["pre_closure_penal_applicable"].isNull())
        {
            preClosurePenalApplicable_=std::make_shared<bool>(r["pre_closure_penal_applicable"].as<bool>());
        }
        if(!r["pre_closure_penal_interest"].isNull())
        {
            preClosurePenalInterest_=std::make_shared<std::string>(r["pre_closure_penal_interest"].as<std::string>());
        }
        if(!r["pre_closure_penal_interest_on_type"].isNull())
        {
            preClosurePenalInterestOnType_=std::make_shared<int32_t>(r["pre_closure_penal_interest_on_type"].as<int32_t>());
        }
        if(!r["min_deposit_term"].isNull())
        {
            minDepositTerm_=std::make_shared<int32_t>(r["min_deposit_term"].as<int32_t>());
        }
        if(!r["min_deposit_term_type"].isNull())
        {
            minDepositTermType_=std::make_shared<int32_t>(r["min_deposit_term_type"].as<int32_t>());
        }
        if(!r["max_deposit_term"].isNull())
        {
            maxDepositTerm_=std::make_shared<int32_t>(r["max_deposit_term"].as<int32_t>());
        }
        if(!r["max_deposit_term_type"].isNull())
        {
            maxDepositTermType_=std::make_shared<int32_t>(r["max_deposit_term_type"].as<int32_t>());
        }
        if(!r["in_multiples_of_deposit_term"].isNull())
        {
            inMultiplesOfDepositTerm_=std::make_shared<int32_t>(r["in_multiples_of_deposit_term"].as<int32_t>());
        }
        if(!r["in_multiples_of_deposit_term_type"].isNull())
        {
            inMultiplesOfDepositTermType_=std::make_shared<int32_t>(r["in_multiples_of_deposit_term_type"].as<int32_t>());
        }
        if(!r["is_mandatory_deposit"].isNull())
        {
            isMandatoryDeposit_=std::make_shared<bool>(r["is_mandatory_deposit"].as<bool>());
        }
        if(!r["allow_withdrawal"].isNull())
        {
            allowWithdrawal_=std::make_shared<bool>(r["allow_withdrawal"].as<bool>());
        }
        if(!r["adjust_advance_towards_future_payments"].isNull())
        {
            adjustAdvanceTowardsFuturePayments_=std::make_shared<bool>(r["adjust_advance_towards_future_payments"].as<bool>());
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
        if(offset + 46 > r.size())
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
            businessId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            depositType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            shortName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            digitsAfterDecimal_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            inMultiplesOf_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            nominalAnnualInterestRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            interestCompoundingPeriodType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            interestPostingPeriodType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            interestCalculationType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            interestCalculationDaysInYearType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            minRequiredOpeningBalance_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            lockinPeriodFrequency_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            lockinPeriodFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            withdrawalFeeForTransfer_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            allowOverdraft_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            overdraftLimit_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            minBalanceForInterestCalculation_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 21;
        if(!r[index].isNull())
        {
            minRequiredBalance_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            enforceMinRequiredBalance_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            isDormancyTrackingActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 24;
        if(!r[index].isNull())
        {
            daysToInactive_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 25;
        if(!r[index].isNull())
        {
            daysToDormancy_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 26;
        if(!r[index].isNull())
        {
            daysToEscheat_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 27;
        if(!r[index].isNull())
        {
            accountingType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 28;
        if(!r[index].isNull())
        {
            interestRateChartId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 29;
        if(!r[index].isNull())
        {
            preClosurePenalApplicable_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 30;
        if(!r[index].isNull())
        {
            preClosurePenalInterest_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 31;
        if(!r[index].isNull())
        {
            preClosurePenalInterestOnType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 32;
        if(!r[index].isNull())
        {
            minDepositTerm_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 33;
        if(!r[index].isNull())
        {
            minDepositTermType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 34;
        if(!r[index].isNull())
        {
            maxDepositTerm_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 35;
        if(!r[index].isNull())
        {
            maxDepositTermType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 36;
        if(!r[index].isNull())
        {
            inMultiplesOfDepositTerm_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 37;
        if(!r[index].isNull())
        {
            inMultiplesOfDepositTermType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 38;
        if(!r[index].isNull())
        {
            isMandatoryDeposit_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 39;
        if(!r[index].isNull())
        {
            allowWithdrawal_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 40;
        if(!r[index].isNull())
        {
            adjustAdvanceTowardsFuturePayments_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 41;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 42;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 43;
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
        index = offset + 44;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 45;
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
const std::string &SavingsProduct::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getId() const noexcept
{
    return id_;
}
void SavingsProduct::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SavingsProduct::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SavingsProduct::PrimaryKeyType & SavingsProduct::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SavingsProduct::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getBusinessId() const noexcept
{
    return businessId_;
}
void SavingsProduct::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void SavingsProduct::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void SavingsProduct::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const int32_t &SavingsProduct::getValueOfDepositType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(depositType_)
        return *depositType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getDepositType() const noexcept
{
    return depositType_;
}
void SavingsProduct::setDepositType(const int32_t &pDepositType) noexcept
{
    depositType_ = std::make_shared<int32_t>(pDepositType);
    dirtyFlag_[2] = true;
}

const std::string &SavingsProduct::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getName() const noexcept
{
    return name_;
}
void SavingsProduct::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[3] = true;
}
void SavingsProduct::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[3] = true;
}

const std::string &SavingsProduct::getValueOfShortName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shortName_)
        return *shortName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getShortName() const noexcept
{
    return shortName_;
}
void SavingsProduct::setShortName(const std::string &pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(pShortName);
    dirtyFlag_[4] = true;
}
void SavingsProduct::setShortName(std::string &&pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(std::move(pShortName));
    dirtyFlag_[4] = true;
}

const std::string &SavingsProduct::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getDescription() const noexcept
{
    return description_;
}
void SavingsProduct::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[5] = true;
}
void SavingsProduct::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[5] = true;
}
void SavingsProduct::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[5] = true;
}

const std::string &SavingsProduct::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void SavingsProduct::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[6] = true;
}
void SavingsProduct::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[6] = true;
}

const int32_t &SavingsProduct::getValueOfDigitsAfterDecimal() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(digitsAfterDecimal_)
        return *digitsAfterDecimal_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getDigitsAfterDecimal() const noexcept
{
    return digitsAfterDecimal_;
}
void SavingsProduct::setDigitsAfterDecimal(const int32_t &pDigitsAfterDecimal) noexcept
{
    digitsAfterDecimal_ = std::make_shared<int32_t>(pDigitsAfterDecimal);
    dirtyFlag_[7] = true;
}

const int32_t &SavingsProduct::getValueOfInMultiplesOf() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(inMultiplesOf_)
        return *inMultiplesOf_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getInMultiplesOf() const noexcept
{
    return inMultiplesOf_;
}
void SavingsProduct::setInMultiplesOf(const int32_t &pInMultiplesOf) noexcept
{
    inMultiplesOf_ = std::make_shared<int32_t>(pInMultiplesOf);
    dirtyFlag_[8] = true;
}

const std::string &SavingsProduct::getValueOfNominalAnnualInterestRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(nominalAnnualInterestRate_)
        return *nominalAnnualInterestRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getNominalAnnualInterestRate() const noexcept
{
    return nominalAnnualInterestRate_;
}
void SavingsProduct::setNominalAnnualInterestRate(const std::string &pNominalAnnualInterestRate) noexcept
{
    nominalAnnualInterestRate_ = std::make_shared<std::string>(pNominalAnnualInterestRate);
    dirtyFlag_[9] = true;
}
void SavingsProduct::setNominalAnnualInterestRate(std::string &&pNominalAnnualInterestRate) noexcept
{
    nominalAnnualInterestRate_ = std::make_shared<std::string>(std::move(pNominalAnnualInterestRate));
    dirtyFlag_[9] = true;
}

const int32_t &SavingsProduct::getValueOfInterestCompoundingPeriodType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCompoundingPeriodType_)
        return *interestCompoundingPeriodType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getInterestCompoundingPeriodType() const noexcept
{
    return interestCompoundingPeriodType_;
}
void SavingsProduct::setInterestCompoundingPeriodType(const int32_t &pInterestCompoundingPeriodType) noexcept
{
    interestCompoundingPeriodType_ = std::make_shared<int32_t>(pInterestCompoundingPeriodType);
    dirtyFlag_[10] = true;
}

const int32_t &SavingsProduct::getValueOfInterestPostingPeriodType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestPostingPeriodType_)
        return *interestPostingPeriodType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getInterestPostingPeriodType() const noexcept
{
    return interestPostingPeriodType_;
}
void SavingsProduct::setInterestPostingPeriodType(const int32_t &pInterestPostingPeriodType) noexcept
{
    interestPostingPeriodType_ = std::make_shared<int32_t>(pInterestPostingPeriodType);
    dirtyFlag_[11] = true;
}

const int32_t &SavingsProduct::getValueOfInterestCalculationType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCalculationType_)
        return *interestCalculationType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getInterestCalculationType() const noexcept
{
    return interestCalculationType_;
}
void SavingsProduct::setInterestCalculationType(const int32_t &pInterestCalculationType) noexcept
{
    interestCalculationType_ = std::make_shared<int32_t>(pInterestCalculationType);
    dirtyFlag_[12] = true;
}

const int32_t &SavingsProduct::getValueOfInterestCalculationDaysInYearType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCalculationDaysInYearType_)
        return *interestCalculationDaysInYearType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getInterestCalculationDaysInYearType() const noexcept
{
    return interestCalculationDaysInYearType_;
}
void SavingsProduct::setInterestCalculationDaysInYearType(const int32_t &pInterestCalculationDaysInYearType) noexcept
{
    interestCalculationDaysInYearType_ = std::make_shared<int32_t>(pInterestCalculationDaysInYearType);
    dirtyFlag_[13] = true;
}

const std::string &SavingsProduct::getValueOfMinRequiredOpeningBalance() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minRequiredOpeningBalance_)
        return *minRequiredOpeningBalance_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getMinRequiredOpeningBalance() const noexcept
{
    return minRequiredOpeningBalance_;
}
void SavingsProduct::setMinRequiredOpeningBalance(const std::string &pMinRequiredOpeningBalance) noexcept
{
    minRequiredOpeningBalance_ = std::make_shared<std::string>(pMinRequiredOpeningBalance);
    dirtyFlag_[14] = true;
}
void SavingsProduct::setMinRequiredOpeningBalance(std::string &&pMinRequiredOpeningBalance) noexcept
{
    minRequiredOpeningBalance_ = std::make_shared<std::string>(std::move(pMinRequiredOpeningBalance));
    dirtyFlag_[14] = true;
}
void SavingsProduct::setMinRequiredOpeningBalanceToNull() noexcept
{
    minRequiredOpeningBalance_.reset();
    dirtyFlag_[14] = true;
}

const int32_t &SavingsProduct::getValueOfLockinPeriodFrequency() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriodFrequency_)
        return *lockinPeriodFrequency_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getLockinPeriodFrequency() const noexcept
{
    return lockinPeriodFrequency_;
}
void SavingsProduct::setLockinPeriodFrequency(const int32_t &pLockinPeriodFrequency) noexcept
{
    lockinPeriodFrequency_ = std::make_shared<int32_t>(pLockinPeriodFrequency);
    dirtyFlag_[15] = true;
}
void SavingsProduct::setLockinPeriodFrequencyToNull() noexcept
{
    lockinPeriodFrequency_.reset();
    dirtyFlag_[15] = true;
}

const int32_t &SavingsProduct::getValueOfLockinPeriodFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriodFrequencyType_)
        return *lockinPeriodFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getLockinPeriodFrequencyType() const noexcept
{
    return lockinPeriodFrequencyType_;
}
void SavingsProduct::setLockinPeriodFrequencyType(const int32_t &pLockinPeriodFrequencyType) noexcept
{
    lockinPeriodFrequencyType_ = std::make_shared<int32_t>(pLockinPeriodFrequencyType);
    dirtyFlag_[16] = true;
}
void SavingsProduct::setLockinPeriodFrequencyTypeToNull() noexcept
{
    lockinPeriodFrequencyType_.reset();
    dirtyFlag_[16] = true;
}

const bool &SavingsProduct::getValueOfWithdrawalFeeForTransfer() const noexcept
{
    static const bool defaultValue = bool();
    if(withdrawalFeeForTransfer_)
        return *withdrawalFeeForTransfer_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getWithdrawalFeeForTransfer() const noexcept
{
    return withdrawalFeeForTransfer_;
}
void SavingsProduct::setWithdrawalFeeForTransfer(const bool &pWithdrawalFeeForTransfer) noexcept
{
    withdrawalFeeForTransfer_ = std::make_shared<bool>(pWithdrawalFeeForTransfer);
    dirtyFlag_[17] = true;
}

const bool &SavingsProduct::getValueOfAllowOverdraft() const noexcept
{
    static const bool defaultValue = bool();
    if(allowOverdraft_)
        return *allowOverdraft_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getAllowOverdraft() const noexcept
{
    return allowOverdraft_;
}
void SavingsProduct::setAllowOverdraft(const bool &pAllowOverdraft) noexcept
{
    allowOverdraft_ = std::make_shared<bool>(pAllowOverdraft);
    dirtyFlag_[18] = true;
}

const std::string &SavingsProduct::getValueOfOverdraftLimit() const noexcept
{
    static const std::string defaultValue = std::string();
    if(overdraftLimit_)
        return *overdraftLimit_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getOverdraftLimit() const noexcept
{
    return overdraftLimit_;
}
void SavingsProduct::setOverdraftLimit(const std::string &pOverdraftLimit) noexcept
{
    overdraftLimit_ = std::make_shared<std::string>(pOverdraftLimit);
    dirtyFlag_[19] = true;
}
void SavingsProduct::setOverdraftLimit(std::string &&pOverdraftLimit) noexcept
{
    overdraftLimit_ = std::make_shared<std::string>(std::move(pOverdraftLimit));
    dirtyFlag_[19] = true;
}
void SavingsProduct::setOverdraftLimitToNull() noexcept
{
    overdraftLimit_.reset();
    dirtyFlag_[19] = true;
}

const std::string &SavingsProduct::getValueOfMinBalanceForInterestCalculation() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minBalanceForInterestCalculation_)
        return *minBalanceForInterestCalculation_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getMinBalanceForInterestCalculation() const noexcept
{
    return minBalanceForInterestCalculation_;
}
void SavingsProduct::setMinBalanceForInterestCalculation(const std::string &pMinBalanceForInterestCalculation) noexcept
{
    minBalanceForInterestCalculation_ = std::make_shared<std::string>(pMinBalanceForInterestCalculation);
    dirtyFlag_[20] = true;
}
void SavingsProduct::setMinBalanceForInterestCalculation(std::string &&pMinBalanceForInterestCalculation) noexcept
{
    minBalanceForInterestCalculation_ = std::make_shared<std::string>(std::move(pMinBalanceForInterestCalculation));
    dirtyFlag_[20] = true;
}
void SavingsProduct::setMinBalanceForInterestCalculationToNull() noexcept
{
    minBalanceForInterestCalculation_.reset();
    dirtyFlag_[20] = true;
}

const std::string &SavingsProduct::getValueOfMinRequiredBalance() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minRequiredBalance_)
        return *minRequiredBalance_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getMinRequiredBalance() const noexcept
{
    return minRequiredBalance_;
}
void SavingsProduct::setMinRequiredBalance(const std::string &pMinRequiredBalance) noexcept
{
    minRequiredBalance_ = std::make_shared<std::string>(pMinRequiredBalance);
    dirtyFlag_[21] = true;
}
void SavingsProduct::setMinRequiredBalance(std::string &&pMinRequiredBalance) noexcept
{
    minRequiredBalance_ = std::make_shared<std::string>(std::move(pMinRequiredBalance));
    dirtyFlag_[21] = true;
}
void SavingsProduct::setMinRequiredBalanceToNull() noexcept
{
    minRequiredBalance_.reset();
    dirtyFlag_[21] = true;
}

const bool &SavingsProduct::getValueOfEnforceMinRequiredBalance() const noexcept
{
    static const bool defaultValue = bool();
    if(enforceMinRequiredBalance_)
        return *enforceMinRequiredBalance_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getEnforceMinRequiredBalance() const noexcept
{
    return enforceMinRequiredBalance_;
}
void SavingsProduct::setEnforceMinRequiredBalance(const bool &pEnforceMinRequiredBalance) noexcept
{
    enforceMinRequiredBalance_ = std::make_shared<bool>(pEnforceMinRequiredBalance);
    dirtyFlag_[22] = true;
}

const bool &SavingsProduct::getValueOfIsDormancyTrackingActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isDormancyTrackingActive_)
        return *isDormancyTrackingActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getIsDormancyTrackingActive() const noexcept
{
    return isDormancyTrackingActive_;
}
void SavingsProduct::setIsDormancyTrackingActive(const bool &pIsDormancyTrackingActive) noexcept
{
    isDormancyTrackingActive_ = std::make_shared<bool>(pIsDormancyTrackingActive);
    dirtyFlag_[23] = true;
}

const int32_t &SavingsProduct::getValueOfDaysToInactive() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(daysToInactive_)
        return *daysToInactive_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getDaysToInactive() const noexcept
{
    return daysToInactive_;
}
void SavingsProduct::setDaysToInactive(const int32_t &pDaysToInactive) noexcept
{
    daysToInactive_ = std::make_shared<int32_t>(pDaysToInactive);
    dirtyFlag_[24] = true;
}
void SavingsProduct::setDaysToInactiveToNull() noexcept
{
    daysToInactive_.reset();
    dirtyFlag_[24] = true;
}

const int32_t &SavingsProduct::getValueOfDaysToDormancy() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(daysToDormancy_)
        return *daysToDormancy_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getDaysToDormancy() const noexcept
{
    return daysToDormancy_;
}
void SavingsProduct::setDaysToDormancy(const int32_t &pDaysToDormancy) noexcept
{
    daysToDormancy_ = std::make_shared<int32_t>(pDaysToDormancy);
    dirtyFlag_[25] = true;
}
void SavingsProduct::setDaysToDormancyToNull() noexcept
{
    daysToDormancy_.reset();
    dirtyFlag_[25] = true;
}

const int32_t &SavingsProduct::getValueOfDaysToEscheat() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(daysToEscheat_)
        return *daysToEscheat_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getDaysToEscheat() const noexcept
{
    return daysToEscheat_;
}
void SavingsProduct::setDaysToEscheat(const int32_t &pDaysToEscheat) noexcept
{
    daysToEscheat_ = std::make_shared<int32_t>(pDaysToEscheat);
    dirtyFlag_[26] = true;
}
void SavingsProduct::setDaysToEscheatToNull() noexcept
{
    daysToEscheat_.reset();
    dirtyFlag_[26] = true;
}

const int32_t &SavingsProduct::getValueOfAccountingType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(accountingType_)
        return *accountingType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getAccountingType() const noexcept
{
    return accountingType_;
}
void SavingsProduct::setAccountingType(const int32_t &pAccountingType) noexcept
{
    accountingType_ = std::make_shared<int32_t>(pAccountingType);
    dirtyFlag_[27] = true;
}

const std::string &SavingsProduct::getValueOfInterestRateChartId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestRateChartId_)
        return *interestRateChartId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getInterestRateChartId() const noexcept
{
    return interestRateChartId_;
}
void SavingsProduct::setInterestRateChartId(const std::string &pInterestRateChartId) noexcept
{
    interestRateChartId_ = std::make_shared<std::string>(pInterestRateChartId);
    dirtyFlag_[28] = true;
}
void SavingsProduct::setInterestRateChartId(std::string &&pInterestRateChartId) noexcept
{
    interestRateChartId_ = std::make_shared<std::string>(std::move(pInterestRateChartId));
    dirtyFlag_[28] = true;
}
void SavingsProduct::setInterestRateChartIdToNull() noexcept
{
    interestRateChartId_.reset();
    dirtyFlag_[28] = true;
}

const bool &SavingsProduct::getValueOfPreClosurePenalApplicable() const noexcept
{
    static const bool defaultValue = bool();
    if(preClosurePenalApplicable_)
        return *preClosurePenalApplicable_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getPreClosurePenalApplicable() const noexcept
{
    return preClosurePenalApplicable_;
}
void SavingsProduct::setPreClosurePenalApplicable(const bool &pPreClosurePenalApplicable) noexcept
{
    preClosurePenalApplicable_ = std::make_shared<bool>(pPreClosurePenalApplicable);
    dirtyFlag_[29] = true;
}
void SavingsProduct::setPreClosurePenalApplicableToNull() noexcept
{
    preClosurePenalApplicable_.reset();
    dirtyFlag_[29] = true;
}

const std::string &SavingsProduct::getValueOfPreClosurePenalInterest() const noexcept
{
    static const std::string defaultValue = std::string();
    if(preClosurePenalInterest_)
        return *preClosurePenalInterest_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getPreClosurePenalInterest() const noexcept
{
    return preClosurePenalInterest_;
}
void SavingsProduct::setPreClosurePenalInterest(const std::string &pPreClosurePenalInterest) noexcept
{
    preClosurePenalInterest_ = std::make_shared<std::string>(pPreClosurePenalInterest);
    dirtyFlag_[30] = true;
}
void SavingsProduct::setPreClosurePenalInterest(std::string &&pPreClosurePenalInterest) noexcept
{
    preClosurePenalInterest_ = std::make_shared<std::string>(std::move(pPreClosurePenalInterest));
    dirtyFlag_[30] = true;
}
void SavingsProduct::setPreClosurePenalInterestToNull() noexcept
{
    preClosurePenalInterest_.reset();
    dirtyFlag_[30] = true;
}

const int32_t &SavingsProduct::getValueOfPreClosurePenalInterestOnType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(preClosurePenalInterestOnType_)
        return *preClosurePenalInterestOnType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getPreClosurePenalInterestOnType() const noexcept
{
    return preClosurePenalInterestOnType_;
}
void SavingsProduct::setPreClosurePenalInterestOnType(const int32_t &pPreClosurePenalInterestOnType) noexcept
{
    preClosurePenalInterestOnType_ = std::make_shared<int32_t>(pPreClosurePenalInterestOnType);
    dirtyFlag_[31] = true;
}
void SavingsProduct::setPreClosurePenalInterestOnTypeToNull() noexcept
{
    preClosurePenalInterestOnType_.reset();
    dirtyFlag_[31] = true;
}

const int32_t &SavingsProduct::getValueOfMinDepositTerm() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(minDepositTerm_)
        return *minDepositTerm_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getMinDepositTerm() const noexcept
{
    return minDepositTerm_;
}
void SavingsProduct::setMinDepositTerm(const int32_t &pMinDepositTerm) noexcept
{
    minDepositTerm_ = std::make_shared<int32_t>(pMinDepositTerm);
    dirtyFlag_[32] = true;
}
void SavingsProduct::setMinDepositTermToNull() noexcept
{
    minDepositTerm_.reset();
    dirtyFlag_[32] = true;
}

const int32_t &SavingsProduct::getValueOfMinDepositTermType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(minDepositTermType_)
        return *minDepositTermType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getMinDepositTermType() const noexcept
{
    return minDepositTermType_;
}
void SavingsProduct::setMinDepositTermType(const int32_t &pMinDepositTermType) noexcept
{
    minDepositTermType_ = std::make_shared<int32_t>(pMinDepositTermType);
    dirtyFlag_[33] = true;
}
void SavingsProduct::setMinDepositTermTypeToNull() noexcept
{
    minDepositTermType_.reset();
    dirtyFlag_[33] = true;
}

const int32_t &SavingsProduct::getValueOfMaxDepositTerm() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(maxDepositTerm_)
        return *maxDepositTerm_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getMaxDepositTerm() const noexcept
{
    return maxDepositTerm_;
}
void SavingsProduct::setMaxDepositTerm(const int32_t &pMaxDepositTerm) noexcept
{
    maxDepositTerm_ = std::make_shared<int32_t>(pMaxDepositTerm);
    dirtyFlag_[34] = true;
}
void SavingsProduct::setMaxDepositTermToNull() noexcept
{
    maxDepositTerm_.reset();
    dirtyFlag_[34] = true;
}

const int32_t &SavingsProduct::getValueOfMaxDepositTermType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(maxDepositTermType_)
        return *maxDepositTermType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getMaxDepositTermType() const noexcept
{
    return maxDepositTermType_;
}
void SavingsProduct::setMaxDepositTermType(const int32_t &pMaxDepositTermType) noexcept
{
    maxDepositTermType_ = std::make_shared<int32_t>(pMaxDepositTermType);
    dirtyFlag_[35] = true;
}
void SavingsProduct::setMaxDepositTermTypeToNull() noexcept
{
    maxDepositTermType_.reset();
    dirtyFlag_[35] = true;
}

const int32_t &SavingsProduct::getValueOfInMultiplesOfDepositTerm() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(inMultiplesOfDepositTerm_)
        return *inMultiplesOfDepositTerm_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getInMultiplesOfDepositTerm() const noexcept
{
    return inMultiplesOfDepositTerm_;
}
void SavingsProduct::setInMultiplesOfDepositTerm(const int32_t &pInMultiplesOfDepositTerm) noexcept
{
    inMultiplesOfDepositTerm_ = std::make_shared<int32_t>(pInMultiplesOfDepositTerm);
    dirtyFlag_[36] = true;
}
void SavingsProduct::setInMultiplesOfDepositTermToNull() noexcept
{
    inMultiplesOfDepositTerm_.reset();
    dirtyFlag_[36] = true;
}

const int32_t &SavingsProduct::getValueOfInMultiplesOfDepositTermType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(inMultiplesOfDepositTermType_)
        return *inMultiplesOfDepositTermType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsProduct::getInMultiplesOfDepositTermType() const noexcept
{
    return inMultiplesOfDepositTermType_;
}
void SavingsProduct::setInMultiplesOfDepositTermType(const int32_t &pInMultiplesOfDepositTermType) noexcept
{
    inMultiplesOfDepositTermType_ = std::make_shared<int32_t>(pInMultiplesOfDepositTermType);
    dirtyFlag_[37] = true;
}
void SavingsProduct::setInMultiplesOfDepositTermTypeToNull() noexcept
{
    inMultiplesOfDepositTermType_.reset();
    dirtyFlag_[37] = true;
}

const bool &SavingsProduct::getValueOfIsMandatoryDeposit() const noexcept
{
    static const bool defaultValue = bool();
    if(isMandatoryDeposit_)
        return *isMandatoryDeposit_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getIsMandatoryDeposit() const noexcept
{
    return isMandatoryDeposit_;
}
void SavingsProduct::setIsMandatoryDeposit(const bool &pIsMandatoryDeposit) noexcept
{
    isMandatoryDeposit_ = std::make_shared<bool>(pIsMandatoryDeposit);
    dirtyFlag_[38] = true;
}
void SavingsProduct::setIsMandatoryDepositToNull() noexcept
{
    isMandatoryDeposit_.reset();
    dirtyFlag_[38] = true;
}

const bool &SavingsProduct::getValueOfAllowWithdrawal() const noexcept
{
    static const bool defaultValue = bool();
    if(allowWithdrawal_)
        return *allowWithdrawal_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getAllowWithdrawal() const noexcept
{
    return allowWithdrawal_;
}
void SavingsProduct::setAllowWithdrawal(const bool &pAllowWithdrawal) noexcept
{
    allowWithdrawal_ = std::make_shared<bool>(pAllowWithdrawal);
    dirtyFlag_[39] = true;
}
void SavingsProduct::setAllowWithdrawalToNull() noexcept
{
    allowWithdrawal_.reset();
    dirtyFlag_[39] = true;
}

const bool &SavingsProduct::getValueOfAdjustAdvanceTowardsFuturePayments() const noexcept
{
    static const bool defaultValue = bool();
    if(adjustAdvanceTowardsFuturePayments_)
        return *adjustAdvanceTowardsFuturePayments_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getAdjustAdvanceTowardsFuturePayments() const noexcept
{
    return adjustAdvanceTowardsFuturePayments_;
}
void SavingsProduct::setAdjustAdvanceTowardsFuturePayments(const bool &pAdjustAdvanceTowardsFuturePayments) noexcept
{
    adjustAdvanceTowardsFuturePayments_ = std::make_shared<bool>(pAdjustAdvanceTowardsFuturePayments);
    dirtyFlag_[40] = true;
}
void SavingsProduct::setAdjustAdvanceTowardsFuturePaymentsToNull() noexcept
{
    adjustAdvanceTowardsFuturePayments_.reset();
    dirtyFlag_[40] = true;
}

const bool &SavingsProduct::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsProduct::getIsActive() const noexcept
{
    return isActive_;
}
void SavingsProduct::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[41] = true;
}

const std::string &SavingsProduct::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getCreatedBy() const noexcept
{
    return createdBy_;
}
void SavingsProduct::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[42] = true;
}
void SavingsProduct::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[42] = true;
}
void SavingsProduct::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[42] = true;
}

const ::trantor::Date &SavingsProduct::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsProduct::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SavingsProduct::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[43] = true;
}

const std::string &SavingsProduct::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProduct::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void SavingsProduct::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[44] = true;
}
void SavingsProduct::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[44] = true;
}
void SavingsProduct::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[44] = true;
}

const ::trantor::Date &SavingsProduct::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsProduct::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void SavingsProduct::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[45] = true;
}

void SavingsProduct::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SavingsProduct::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "deposit_type",
        "name",
        "short_name",
        "description",
        "currency_code",
        "digits_after_decimal",
        "in_multiples_of",
        "nominal_annual_interest_rate",
        "interest_compounding_period_type",
        "interest_posting_period_type",
        "interest_calculation_type",
        "interest_calculation_days_in_year_type",
        "min_required_opening_balance",
        "lockin_period_frequency",
        "lockin_period_frequency_type",
        "withdrawal_fee_for_transfer",
        "allow_overdraft",
        "overdraft_limit",
        "min_balance_for_interest_calculation",
        "min_required_balance",
        "enforce_min_required_balance",
        "is_dormancy_tracking_active",
        "days_to_inactive",
        "days_to_dormancy",
        "days_to_escheat",
        "accounting_type",
        "interest_rate_chart_id",
        "pre_closure_penal_applicable",
        "pre_closure_penal_interest",
        "pre_closure_penal_interest_on_type",
        "min_deposit_term",
        "min_deposit_term_type",
        "max_deposit_term",
        "max_deposit_term_type",
        "in_multiples_of_deposit_term",
        "in_multiples_of_deposit_term_type",
        "is_mandatory_deposit",
        "allow_withdrawal",
        "adjust_advance_towards_future_payments",
        "is_active",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void SavingsProduct::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDepositType())
        {
            binder << getValueOfDepositType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getDigitsAfterDecimal())
        {
            binder << getValueOfDigitsAfterDecimal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getInMultiplesOf())
        {
            binder << getValueOfInMultiplesOf();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getNominalAnnualInterestRate())
        {
            binder << getValueOfNominalAnnualInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getInterestCompoundingPeriodType())
        {
            binder << getValueOfInterestCompoundingPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getInterestPostingPeriodType())
        {
            binder << getValueOfInterestPostingPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getInterestCalculationType())
        {
            binder << getValueOfInterestCalculationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getInterestCalculationDaysInYearType())
        {
            binder << getValueOfInterestCalculationDaysInYearType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getMinRequiredOpeningBalance())
        {
            binder << getValueOfMinRequiredOpeningBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getLockinPeriodFrequency())
        {
            binder << getValueOfLockinPeriodFrequency();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getLockinPeriodFrequencyType())
        {
            binder << getValueOfLockinPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getWithdrawalFeeForTransfer())
        {
            binder << getValueOfWithdrawalFeeForTransfer();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getAllowOverdraft())
        {
            binder << getValueOfAllowOverdraft();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getOverdraftLimit())
        {
            binder << getValueOfOverdraftLimit();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getMinBalanceForInterestCalculation())
        {
            binder << getValueOfMinBalanceForInterestCalculation();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getMinRequiredBalance())
        {
            binder << getValueOfMinRequiredBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getEnforceMinRequiredBalance())
        {
            binder << getValueOfEnforceMinRequiredBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getIsDormancyTrackingActive())
        {
            binder << getValueOfIsDormancyTrackingActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getDaysToInactive())
        {
            binder << getValueOfDaysToInactive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getDaysToDormancy())
        {
            binder << getValueOfDaysToDormancy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getDaysToEscheat())
        {
            binder << getValueOfDaysToEscheat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
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
    if(dirtyFlag_[28])
    {
        if(getInterestRateChartId())
        {
            binder << getValueOfInterestRateChartId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getPreClosurePenalApplicable())
        {
            binder << getValueOfPreClosurePenalApplicable();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getPreClosurePenalInterest())
        {
            binder << getValueOfPreClosurePenalInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getPreClosurePenalInterestOnType())
        {
            binder << getValueOfPreClosurePenalInterestOnType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getMinDepositTerm())
        {
            binder << getValueOfMinDepositTerm();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getMinDepositTermType())
        {
            binder << getValueOfMinDepositTermType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getMaxDepositTerm())
        {
            binder << getValueOfMaxDepositTerm();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
    {
        if(getMaxDepositTermType())
        {
            binder << getValueOfMaxDepositTermType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
    {
        if(getInMultiplesOfDepositTerm())
        {
            binder << getValueOfInMultiplesOfDepositTerm();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
    {
        if(getInMultiplesOfDepositTermType())
        {
            binder << getValueOfInMultiplesOfDepositTermType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getIsMandatoryDeposit())
        {
            binder << getValueOfIsMandatoryDeposit();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getAllowWithdrawal())
        {
            binder << getValueOfAllowWithdrawal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getAdjustAdvanceTowardsFuturePayments())
        {
            binder << getValueOfAdjustAdvanceTowardsFuturePayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
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
    if(dirtyFlag_[42])
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
    if(dirtyFlag_[43])
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
    if(dirtyFlag_[44])
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
    if(dirtyFlag_[45])
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

const std::vector<std::string> SavingsProduct::updateColumns() const
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
    return ret;
}

void SavingsProduct::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDepositType())
        {
            binder << getValueOfDepositType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getDigitsAfterDecimal())
        {
            binder << getValueOfDigitsAfterDecimal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getInMultiplesOf())
        {
            binder << getValueOfInMultiplesOf();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getNominalAnnualInterestRate())
        {
            binder << getValueOfNominalAnnualInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getInterestCompoundingPeriodType())
        {
            binder << getValueOfInterestCompoundingPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getInterestPostingPeriodType())
        {
            binder << getValueOfInterestPostingPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getInterestCalculationType())
        {
            binder << getValueOfInterestCalculationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getInterestCalculationDaysInYearType())
        {
            binder << getValueOfInterestCalculationDaysInYearType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getMinRequiredOpeningBalance())
        {
            binder << getValueOfMinRequiredOpeningBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getLockinPeriodFrequency())
        {
            binder << getValueOfLockinPeriodFrequency();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getLockinPeriodFrequencyType())
        {
            binder << getValueOfLockinPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getWithdrawalFeeForTransfer())
        {
            binder << getValueOfWithdrawalFeeForTransfer();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getAllowOverdraft())
        {
            binder << getValueOfAllowOverdraft();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getOverdraftLimit())
        {
            binder << getValueOfOverdraftLimit();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getMinBalanceForInterestCalculation())
        {
            binder << getValueOfMinBalanceForInterestCalculation();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getMinRequiredBalance())
        {
            binder << getValueOfMinRequiredBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getEnforceMinRequiredBalance())
        {
            binder << getValueOfEnforceMinRequiredBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getIsDormancyTrackingActive())
        {
            binder << getValueOfIsDormancyTrackingActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getDaysToInactive())
        {
            binder << getValueOfDaysToInactive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getDaysToDormancy())
        {
            binder << getValueOfDaysToDormancy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getDaysToEscheat())
        {
            binder << getValueOfDaysToEscheat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
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
    if(dirtyFlag_[28])
    {
        if(getInterestRateChartId())
        {
            binder << getValueOfInterestRateChartId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getPreClosurePenalApplicable())
        {
            binder << getValueOfPreClosurePenalApplicable();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getPreClosurePenalInterest())
        {
            binder << getValueOfPreClosurePenalInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getPreClosurePenalInterestOnType())
        {
            binder << getValueOfPreClosurePenalInterestOnType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getMinDepositTerm())
        {
            binder << getValueOfMinDepositTerm();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getMinDepositTermType())
        {
            binder << getValueOfMinDepositTermType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getMaxDepositTerm())
        {
            binder << getValueOfMaxDepositTerm();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
    {
        if(getMaxDepositTermType())
        {
            binder << getValueOfMaxDepositTermType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
    {
        if(getInMultiplesOfDepositTerm())
        {
            binder << getValueOfInMultiplesOfDepositTerm();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
    {
        if(getInMultiplesOfDepositTermType())
        {
            binder << getValueOfInMultiplesOfDepositTermType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getIsMandatoryDeposit())
        {
            binder << getValueOfIsMandatoryDeposit();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getAllowWithdrawal())
        {
            binder << getValueOfAllowWithdrawal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getAdjustAdvanceTowardsFuturePayments())
        {
            binder << getValueOfAdjustAdvanceTowardsFuturePayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
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
    if(dirtyFlag_[42])
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
    if(dirtyFlag_[43])
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
    if(dirtyFlag_[44])
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
    if(dirtyFlag_[45])
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
