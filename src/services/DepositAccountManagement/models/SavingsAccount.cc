/**
 *  SavingsAccount.cc
 *
 *  See SavingsAccount.h for the hand-authored-subset note.
 *
 */

#include "SavingsAccount.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string SavingsAccount::Cols::_id = "\"id\"";
const std::string SavingsAccount::Cols::_business_id = "\"business_id\"";
const std::string SavingsAccount::Cols::_account_no = "\"account_no\"";
const std::string SavingsAccount::Cols::_external_id = "\"external_id\"";
const std::string SavingsAccount::Cols::_deposit_type = "\"deposit_type\"";
const std::string SavingsAccount::Cols::_client_id = "\"client_id\"";
const std::string SavingsAccount::Cols::_group_id = "\"group_id\"";
const std::string SavingsAccount::Cols::_product_id = "\"product_id\"";
const std::string SavingsAccount::Cols::_field_officer_id = "\"field_officer_id\"";
const std::string SavingsAccount::Cols::_status = "\"status\"";
const std::string SavingsAccount::Cols::_sub_status = "\"sub_status\"";
const std::string SavingsAccount::Cols::_account_type = "\"account_type\"";
const std::string SavingsAccount::Cols::_currency_code = "\"currency_code\"";
const std::string SavingsAccount::Cols::_digits_after_decimal = "\"digits_after_decimal\"";
const std::string SavingsAccount::Cols::_in_multiples_of = "\"in_multiples_of\"";
const std::string SavingsAccount::Cols::_nominal_annual_interest_rate = "\"nominal_annual_interest_rate\"";
const std::string SavingsAccount::Cols::_interest_compounding_period_type = "\"interest_compounding_period_type\"";
const std::string SavingsAccount::Cols::_interest_posting_period_type = "\"interest_posting_period_type\"";
const std::string SavingsAccount::Cols::_interest_calculation_type = "\"interest_calculation_type\"";
const std::string SavingsAccount::Cols::_interest_calculation_days_in_year_type = "\"interest_calculation_days_in_year_type\"";
const std::string SavingsAccount::Cols::_min_required_opening_balance = "\"min_required_opening_balance\"";
const std::string SavingsAccount::Cols::_lockin_period_frequency = "\"lockin_period_frequency\"";
const std::string SavingsAccount::Cols::_lockin_period_frequency_type = "\"lockin_period_frequency_type\"";
const std::string SavingsAccount::Cols::_withdrawal_fee_for_transfer = "\"withdrawal_fee_for_transfer\"";
const std::string SavingsAccount::Cols::_allow_overdraft = "\"allow_overdraft\"";
const std::string SavingsAccount::Cols::_overdraft_limit = "\"overdraft_limit\"";
const std::string SavingsAccount::Cols::_min_balance_for_interest_calculation = "\"min_balance_for_interest_calculation\"";
const std::string SavingsAccount::Cols::_min_required_balance = "\"min_required_balance\"";
const std::string SavingsAccount::Cols::_enforce_min_required_balance = "\"enforce_min_required_balance\"";
const std::string SavingsAccount::Cols::_submitted_on_date = "\"submitted_on_date\"";
const std::string SavingsAccount::Cols::_submitted_by = "\"submitted_by\"";
const std::string SavingsAccount::Cols::_approved_on_date = "\"approved_on_date\"";
const std::string SavingsAccount::Cols::_approved_by = "\"approved_by\"";
const std::string SavingsAccount::Cols::_activated_on_date = "\"activated_on_date\"";
const std::string SavingsAccount::Cols::_activated_by = "\"activated_by\"";
const std::string SavingsAccount::Cols::_rejected_on_date = "\"rejected_on_date\"";
const std::string SavingsAccount::Cols::_rejected_by = "\"rejected_by\"";
const std::string SavingsAccount::Cols::_withdrawn_on_date = "\"withdrawn_on_date\"";
const std::string SavingsAccount::Cols::_withdrawn_by = "\"withdrawn_by\"";
const std::string SavingsAccount::Cols::_closed_on_date = "\"closed_on_date\"";
const std::string SavingsAccount::Cols::_closed_by = "\"closed_by\"";
const std::string SavingsAccount::Cols::_account_balance_derived = "\"account_balance_derived\"";
const std::string SavingsAccount::Cols::_total_deposits_derived = "\"total_deposits_derived\"";
const std::string SavingsAccount::Cols::_total_withdrawals_derived = "\"total_withdrawals_derived\"";
const std::string SavingsAccount::Cols::_total_interest_posted_derived = "\"total_interest_posted_derived\"";
const std::string SavingsAccount::Cols::_total_fee_charge_derived = "\"total_fee_charge_derived\"";
const std::string SavingsAccount::Cols::_total_withdrawal_fee_derived = "\"total_withdrawal_fee_derived\"";
const std::string SavingsAccount::Cols::_last_interest_calculation_date = "\"last_interest_calculation_date\"";
const std::string SavingsAccount::Cols::_is_credit_blocked = "\"is_credit_blocked\"";
const std::string SavingsAccount::Cols::_is_debit_blocked = "\"is_debit_blocked\"";
const std::string SavingsAccount::Cols::_is_interest_blocked = "\"is_interest_blocked\"";
const std::string SavingsAccount::Cols::_parent_account_id = "\"parent_account_id\"";
const std::string SavingsAccount::Cols::_is_gsim_parent = "\"is_gsim_parent\"";
const std::string SavingsAccount::Cols::_created_by = "\"created_by\"";
const std::string SavingsAccount::Cols::_created_at = "\"created_at\"";
const std::string SavingsAccount::Cols::_updated_by = "\"updated_by\"";
const std::string SavingsAccount::Cols::_updated_at = "\"updated_at\"";
const std::string SavingsAccount::primaryKeyName = "id";
const bool SavingsAccount::hasPrimaryKey = true;
const std::string SavingsAccount::tableName = "\"savings_account\"";

const std::vector<typename SavingsAccount::MetaData> SavingsAccount::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"account_no","std::string","character varying",20,0,0,0},
{"external_id","std::string","character varying",100,0,0,0},
{"deposit_type","int32_t","integer",4,0,0,1},
{"client_id","std::string","uuid",0,0,0,0},
{"group_id","std::string","uuid",0,0,0,0},
{"product_id","std::string","uuid",0,0,0,1},
{"field_officer_id","std::string","uuid",0,0,0,0},
{"status","int32_t","integer",4,0,0,1},
{"sub_status","int32_t","integer",4,0,0,1},
{"account_type","int32_t","integer",4,0,0,1},
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
{"submitted_on_date","::trantor::Date","date",0,0,0,0},
{"submitted_by","std::string","uuid",0,0,0,0},
{"approved_on_date","::trantor::Date","date",0,0,0,0},
{"approved_by","std::string","uuid",0,0,0,0},
{"activated_on_date","::trantor::Date","date",0,0,0,0},
{"activated_by","std::string","uuid",0,0,0,0},
{"rejected_on_date","::trantor::Date","date",0,0,0,0},
{"rejected_by","std::string","uuid",0,0,0,0},
{"withdrawn_on_date","::trantor::Date","date",0,0,0,0},
{"withdrawn_by","std::string","uuid",0,0,0,0},
{"closed_on_date","::trantor::Date","date",0,0,0,0},
{"closed_by","std::string","uuid",0,0,0,0},
{"account_balance_derived","std::string","numeric",0,0,0,1},
{"total_deposits_derived","std::string","numeric",0,0,0,1},
{"total_withdrawals_derived","std::string","numeric",0,0,0,1},
{"total_interest_posted_derived","std::string","numeric",0,0,0,1},
{"total_fee_charge_derived","std::string","numeric",0,0,0,1},
{"total_withdrawal_fee_derived","std::string","numeric",0,0,0,1},
{"last_interest_calculation_date","::trantor::Date","date",0,0,0,0},
{"is_credit_blocked","bool","boolean",1,0,0,1},
{"is_debit_blocked","bool","boolean",1,0,0,1},
{"is_interest_blocked","bool","boolean",1,0,0,1},
{"parent_account_id","std::string","uuid",0,0,0,0},
{"is_gsim_parent","bool","boolean",1,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SavingsAccount::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SavingsAccount::SavingsAccount(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["account_no"].isNull())
        {
            accountNo_=std::make_shared<std::string>(r["account_no"].as<std::string>());
        }
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["deposit_type"].isNull())
        {
            depositType_=std::make_shared<int32_t>(r["deposit_type"].as<int32_t>());
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
        if(!r["field_officer_id"].isNull())
        {
            fieldOfficerId_=std::make_shared<std::string>(r["field_officer_id"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["sub_status"].isNull())
        {
            subStatus_=std::make_shared<int32_t>(r["sub_status"].as<int32_t>());
        }
        if(!r["account_type"].isNull())
        {
            accountType_=std::make_shared<int32_t>(r["account_type"].as<int32_t>());
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
        if(!r["activated_on_date"].isNull())
        {
            auto daysStr = r["activated_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activatedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["activated_by"].isNull())
        {
            activatedBy_=std::make_shared<std::string>(r["activated_by"].as<std::string>());
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
        if(!r["rejected_by"].isNull())
        {
            rejectedBy_=std::make_shared<std::string>(r["rejected_by"].as<std::string>());
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
        if(!r["withdrawn_by"].isNull())
        {
            withdrawnBy_=std::make_shared<std::string>(r["withdrawn_by"].as<std::string>());
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
        if(!r["account_balance_derived"].isNull())
        {
            accountBalanceDerived_=std::make_shared<std::string>(r["account_balance_derived"].as<std::string>());
        }
        if(!r["total_deposits_derived"].isNull())
        {
            totalDepositsDerived_=std::make_shared<std::string>(r["total_deposits_derived"].as<std::string>());
        }
        if(!r["total_withdrawals_derived"].isNull())
        {
            totalWithdrawalsDerived_=std::make_shared<std::string>(r["total_withdrawals_derived"].as<std::string>());
        }
        if(!r["total_interest_posted_derived"].isNull())
        {
            totalInterestPostedDerived_=std::make_shared<std::string>(r["total_interest_posted_derived"].as<std::string>());
        }
        if(!r["total_fee_charge_derived"].isNull())
        {
            totalFeeChargeDerived_=std::make_shared<std::string>(r["total_fee_charge_derived"].as<std::string>());
        }
        if(!r["total_withdrawal_fee_derived"].isNull())
        {
            totalWithdrawalFeeDerived_=std::make_shared<std::string>(r["total_withdrawal_fee_derived"].as<std::string>());
        }
        if(!r["last_interest_calculation_date"].isNull())
        {
            auto daysStr = r["last_interest_calculation_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            lastInterestCalculationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["is_credit_blocked"].isNull())
        {
            isCreditBlocked_=std::make_shared<bool>(r["is_credit_blocked"].as<bool>());
        }
        if(!r["is_debit_blocked"].isNull())
        {
            isDebitBlocked_=std::make_shared<bool>(r["is_debit_blocked"].as<bool>());
        }
        if(!r["is_interest_blocked"].isNull())
        {
            isInterestBlocked_=std::make_shared<bool>(r["is_interest_blocked"].as<bool>());
        }
        if(!r["parent_account_id"].isNull())
        {
            parentAccountId_=std::make_shared<std::string>(r["parent_account_id"].as<std::string>());
        }
        if(!r["is_gsim_parent"].isNull())
        {
            isGsimParent_=std::make_shared<bool>(r["is_gsim_parent"].as<bool>());
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
        if(offset + 57 > r.size())
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
            accountNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            depositType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            groupId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            productId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            fieldOfficerId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            subStatus_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            accountType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            digitsAfterDecimal_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            inMultiplesOf_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            nominalAnnualInterestRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            interestCompoundingPeriodType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            interestPostingPeriodType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            interestCalculationType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            interestCalculationDaysInYearType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            minRequiredOpeningBalance_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 21;
        if(!r[index].isNull())
        {
            lockinPeriodFrequency_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            lockinPeriodFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            withdrawalFeeForTransfer_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 24;
        if(!r[index].isNull())
        {
            allowOverdraft_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 25;
        if(!r[index].isNull())
        {
            overdraftLimit_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 26;
        if(!r[index].isNull())
        {
            minBalanceForInterestCalculation_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 27;
        if(!r[index].isNull())
        {
            minRequiredBalance_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 28;
        if(!r[index].isNull())
        {
            enforceMinRequiredBalance_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 29;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 30;
        if(!r[index].isNull())
        {
            submittedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 31;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            approvedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 32;
        if(!r[index].isNull())
        {
            approvedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 33;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activatedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 34;
        if(!r[index].isNull())
        {
            activatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 35;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rejectedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 36;
        if(!r[index].isNull())
        {
            rejectedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 37;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            withdrawnOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 38;
        if(!r[index].isNull())
        {
            withdrawnBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 39;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 40;
        if(!r[index].isNull())
        {
            closedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 41;
        if(!r[index].isNull())
        {
            accountBalanceDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 42;
        if(!r[index].isNull())
        {
            totalDepositsDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 43;
        if(!r[index].isNull())
        {
            totalWithdrawalsDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 44;
        if(!r[index].isNull())
        {
            totalInterestPostedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 45;
        if(!r[index].isNull())
        {
            totalFeeChargeDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 46;
        if(!r[index].isNull())
        {
            totalWithdrawalFeeDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 47;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            lastInterestCalculationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 48;
        if(!r[index].isNull())
        {
            isCreditBlocked_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 49;
        if(!r[index].isNull())
        {
            isDebitBlocked_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 50;
        if(!r[index].isNull())
        {
            isInterestBlocked_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 51;
        if(!r[index].isNull())
        {
            parentAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 52;
        if(!r[index].isNull())
        {
            isGsimParent_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 53;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 54;
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
        index = offset + 55;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &SavingsAccount::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getId() const noexcept
{
    return id_;
}
void SavingsAccount::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SavingsAccount::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SavingsAccount::PrimaryKeyType & SavingsAccount::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SavingsAccount::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getBusinessId() const noexcept
{
    return businessId_;
}
void SavingsAccount::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void SavingsAccount::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void SavingsAccount::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &SavingsAccount::getValueOfAccountNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountNo_)
        return *accountNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getAccountNo() const noexcept
{
    return accountNo_;
}
void SavingsAccount::setAccountNo(const std::string &pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(pAccountNo);
    dirtyFlag_[2] = true;
}
void SavingsAccount::setAccountNo(std::string &&pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(std::move(pAccountNo));
    dirtyFlag_[2] = true;
}
void SavingsAccount::setAccountNoToNull() noexcept
{
    accountNo_.reset();
    dirtyFlag_[2] = true;
}

const std::string &SavingsAccount::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getExternalId() const noexcept
{
    return externalId_;
}
void SavingsAccount::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[3] = true;
}
void SavingsAccount::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[3] = true;
}
void SavingsAccount::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &SavingsAccount::getValueOfDepositType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(depositType_)
        return *depositType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getDepositType() const noexcept
{
    return depositType_;
}
void SavingsAccount::setDepositType(const int32_t &pDepositType) noexcept
{
    depositType_ = std::make_shared<int32_t>(pDepositType);
    dirtyFlag_[4] = true;
}

const std::string &SavingsAccount::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getClientId() const noexcept
{
    return clientId_;
}
void SavingsAccount::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[5] = true;
}
void SavingsAccount::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[5] = true;
}
void SavingsAccount::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[5] = true;
}

const std::string &SavingsAccount::getValueOfGroupId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(groupId_)
        return *groupId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getGroupId() const noexcept
{
    return groupId_;
}
void SavingsAccount::setGroupId(const std::string &pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(pGroupId);
    dirtyFlag_[6] = true;
}
void SavingsAccount::setGroupId(std::string &&pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(std::move(pGroupId));
    dirtyFlag_[6] = true;
}
void SavingsAccount::setGroupIdToNull() noexcept
{
    groupId_.reset();
    dirtyFlag_[6] = true;
}

const std::string &SavingsAccount::getValueOfProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(productId_)
        return *productId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getProductId() const noexcept
{
    return productId_;
}
void SavingsAccount::setProductId(const std::string &pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(pProductId);
    dirtyFlag_[7] = true;
}
void SavingsAccount::setProductId(std::string &&pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(std::move(pProductId));
    dirtyFlag_[7] = true;
}

const std::string &SavingsAccount::getValueOfFieldOfficerId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fieldOfficerId_)
        return *fieldOfficerId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getFieldOfficerId() const noexcept
{
    return fieldOfficerId_;
}
void SavingsAccount::setFieldOfficerId(const std::string &pFieldOfficerId) noexcept
{
    fieldOfficerId_ = std::make_shared<std::string>(pFieldOfficerId);
    dirtyFlag_[8] = true;
}
void SavingsAccount::setFieldOfficerId(std::string &&pFieldOfficerId) noexcept
{
    fieldOfficerId_ = std::make_shared<std::string>(std::move(pFieldOfficerId));
    dirtyFlag_[8] = true;
}
void SavingsAccount::setFieldOfficerIdToNull() noexcept
{
    fieldOfficerId_.reset();
    dirtyFlag_[8] = true;
}

const int32_t &SavingsAccount::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getStatus() const noexcept
{
    return status_;
}
void SavingsAccount::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[9] = true;
}

const int32_t &SavingsAccount::getValueOfSubStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(subStatus_)
        return *subStatus_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getSubStatus() const noexcept
{
    return subStatus_;
}
void SavingsAccount::setSubStatus(const int32_t &pSubStatus) noexcept
{
    subStatus_ = std::make_shared<int32_t>(pSubStatus);
    dirtyFlag_[10] = true;
}

const int32_t &SavingsAccount::getValueOfAccountType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(accountType_)
        return *accountType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getAccountType() const noexcept
{
    return accountType_;
}
void SavingsAccount::setAccountType(const int32_t &pAccountType) noexcept
{
    accountType_ = std::make_shared<int32_t>(pAccountType);
    dirtyFlag_[11] = true;
}

const std::string &SavingsAccount::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void SavingsAccount::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[12] = true;
}
void SavingsAccount::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[12] = true;
}

const int32_t &SavingsAccount::getValueOfDigitsAfterDecimal() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(digitsAfterDecimal_)
        return *digitsAfterDecimal_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getDigitsAfterDecimal() const noexcept
{
    return digitsAfterDecimal_;
}
void SavingsAccount::setDigitsAfterDecimal(const int32_t &pDigitsAfterDecimal) noexcept
{
    digitsAfterDecimal_ = std::make_shared<int32_t>(pDigitsAfterDecimal);
    dirtyFlag_[13] = true;
}

const int32_t &SavingsAccount::getValueOfInMultiplesOf() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(inMultiplesOf_)
        return *inMultiplesOf_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getInMultiplesOf() const noexcept
{
    return inMultiplesOf_;
}
void SavingsAccount::setInMultiplesOf(const int32_t &pInMultiplesOf) noexcept
{
    inMultiplesOf_ = std::make_shared<int32_t>(pInMultiplesOf);
    dirtyFlag_[14] = true;
}

const std::string &SavingsAccount::getValueOfNominalAnnualInterestRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(nominalAnnualInterestRate_)
        return *nominalAnnualInterestRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getNominalAnnualInterestRate() const noexcept
{
    return nominalAnnualInterestRate_;
}
void SavingsAccount::setNominalAnnualInterestRate(const std::string &pNominalAnnualInterestRate) noexcept
{
    nominalAnnualInterestRate_ = std::make_shared<std::string>(pNominalAnnualInterestRate);
    dirtyFlag_[15] = true;
}
void SavingsAccount::setNominalAnnualInterestRate(std::string &&pNominalAnnualInterestRate) noexcept
{
    nominalAnnualInterestRate_ = std::make_shared<std::string>(std::move(pNominalAnnualInterestRate));
    dirtyFlag_[15] = true;
}

const int32_t &SavingsAccount::getValueOfInterestCompoundingPeriodType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCompoundingPeriodType_)
        return *interestCompoundingPeriodType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getInterestCompoundingPeriodType() const noexcept
{
    return interestCompoundingPeriodType_;
}
void SavingsAccount::setInterestCompoundingPeriodType(const int32_t &pInterestCompoundingPeriodType) noexcept
{
    interestCompoundingPeriodType_ = std::make_shared<int32_t>(pInterestCompoundingPeriodType);
    dirtyFlag_[16] = true;
}

const int32_t &SavingsAccount::getValueOfInterestPostingPeriodType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestPostingPeriodType_)
        return *interestPostingPeriodType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getInterestPostingPeriodType() const noexcept
{
    return interestPostingPeriodType_;
}
void SavingsAccount::setInterestPostingPeriodType(const int32_t &pInterestPostingPeriodType) noexcept
{
    interestPostingPeriodType_ = std::make_shared<int32_t>(pInterestPostingPeriodType);
    dirtyFlag_[17] = true;
}

const int32_t &SavingsAccount::getValueOfInterestCalculationType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCalculationType_)
        return *interestCalculationType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getInterestCalculationType() const noexcept
{
    return interestCalculationType_;
}
void SavingsAccount::setInterestCalculationType(const int32_t &pInterestCalculationType) noexcept
{
    interestCalculationType_ = std::make_shared<int32_t>(pInterestCalculationType);
    dirtyFlag_[18] = true;
}

const int32_t &SavingsAccount::getValueOfInterestCalculationDaysInYearType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(interestCalculationDaysInYearType_)
        return *interestCalculationDaysInYearType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getInterestCalculationDaysInYearType() const noexcept
{
    return interestCalculationDaysInYearType_;
}
void SavingsAccount::setInterestCalculationDaysInYearType(const int32_t &pInterestCalculationDaysInYearType) noexcept
{
    interestCalculationDaysInYearType_ = std::make_shared<int32_t>(pInterestCalculationDaysInYearType);
    dirtyFlag_[19] = true;
}

const std::string &SavingsAccount::getValueOfMinRequiredOpeningBalance() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minRequiredOpeningBalance_)
        return *minRequiredOpeningBalance_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getMinRequiredOpeningBalance() const noexcept
{
    return minRequiredOpeningBalance_;
}
void SavingsAccount::setMinRequiredOpeningBalance(const std::string &pMinRequiredOpeningBalance) noexcept
{
    minRequiredOpeningBalance_ = std::make_shared<std::string>(pMinRequiredOpeningBalance);
    dirtyFlag_[20] = true;
}
void SavingsAccount::setMinRequiredOpeningBalance(std::string &&pMinRequiredOpeningBalance) noexcept
{
    minRequiredOpeningBalance_ = std::make_shared<std::string>(std::move(pMinRequiredOpeningBalance));
    dirtyFlag_[20] = true;
}
void SavingsAccount::setMinRequiredOpeningBalanceToNull() noexcept
{
    minRequiredOpeningBalance_.reset();
    dirtyFlag_[20] = true;
}

const int32_t &SavingsAccount::getValueOfLockinPeriodFrequency() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriodFrequency_)
        return *lockinPeriodFrequency_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getLockinPeriodFrequency() const noexcept
{
    return lockinPeriodFrequency_;
}
void SavingsAccount::setLockinPeriodFrequency(const int32_t &pLockinPeriodFrequency) noexcept
{
    lockinPeriodFrequency_ = std::make_shared<int32_t>(pLockinPeriodFrequency);
    dirtyFlag_[21] = true;
}
void SavingsAccount::setLockinPeriodFrequencyToNull() noexcept
{
    lockinPeriodFrequency_.reset();
    dirtyFlag_[21] = true;
}

const int32_t &SavingsAccount::getValueOfLockinPeriodFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriodFrequencyType_)
        return *lockinPeriodFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccount::getLockinPeriodFrequencyType() const noexcept
{
    return lockinPeriodFrequencyType_;
}
void SavingsAccount::setLockinPeriodFrequencyType(const int32_t &pLockinPeriodFrequencyType) noexcept
{
    lockinPeriodFrequencyType_ = std::make_shared<int32_t>(pLockinPeriodFrequencyType);
    dirtyFlag_[22] = true;
}
void SavingsAccount::setLockinPeriodFrequencyTypeToNull() noexcept
{
    lockinPeriodFrequencyType_.reset();
    dirtyFlag_[22] = true;
}

const bool &SavingsAccount::getValueOfWithdrawalFeeForTransfer() const noexcept
{
    static const bool defaultValue = bool();
    if(withdrawalFeeForTransfer_)
        return *withdrawalFeeForTransfer_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccount::getWithdrawalFeeForTransfer() const noexcept
{
    return withdrawalFeeForTransfer_;
}
void SavingsAccount::setWithdrawalFeeForTransfer(const bool &pWithdrawalFeeForTransfer) noexcept
{
    withdrawalFeeForTransfer_ = std::make_shared<bool>(pWithdrawalFeeForTransfer);
    dirtyFlag_[23] = true;
}

const bool &SavingsAccount::getValueOfAllowOverdraft() const noexcept
{
    static const bool defaultValue = bool();
    if(allowOverdraft_)
        return *allowOverdraft_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccount::getAllowOverdraft() const noexcept
{
    return allowOverdraft_;
}
void SavingsAccount::setAllowOverdraft(const bool &pAllowOverdraft) noexcept
{
    allowOverdraft_ = std::make_shared<bool>(pAllowOverdraft);
    dirtyFlag_[24] = true;
}

const std::string &SavingsAccount::getValueOfOverdraftLimit() const noexcept
{
    static const std::string defaultValue = std::string();
    if(overdraftLimit_)
        return *overdraftLimit_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getOverdraftLimit() const noexcept
{
    return overdraftLimit_;
}
void SavingsAccount::setOverdraftLimit(const std::string &pOverdraftLimit) noexcept
{
    overdraftLimit_ = std::make_shared<std::string>(pOverdraftLimit);
    dirtyFlag_[25] = true;
}
void SavingsAccount::setOverdraftLimit(std::string &&pOverdraftLimit) noexcept
{
    overdraftLimit_ = std::make_shared<std::string>(std::move(pOverdraftLimit));
    dirtyFlag_[25] = true;
}
void SavingsAccount::setOverdraftLimitToNull() noexcept
{
    overdraftLimit_.reset();
    dirtyFlag_[25] = true;
}

const std::string &SavingsAccount::getValueOfMinBalanceForInterestCalculation() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minBalanceForInterestCalculation_)
        return *minBalanceForInterestCalculation_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getMinBalanceForInterestCalculation() const noexcept
{
    return minBalanceForInterestCalculation_;
}
void SavingsAccount::setMinBalanceForInterestCalculation(const std::string &pMinBalanceForInterestCalculation) noexcept
{
    minBalanceForInterestCalculation_ = std::make_shared<std::string>(pMinBalanceForInterestCalculation);
    dirtyFlag_[26] = true;
}
void SavingsAccount::setMinBalanceForInterestCalculation(std::string &&pMinBalanceForInterestCalculation) noexcept
{
    minBalanceForInterestCalculation_ = std::make_shared<std::string>(std::move(pMinBalanceForInterestCalculation));
    dirtyFlag_[26] = true;
}
void SavingsAccount::setMinBalanceForInterestCalculationToNull() noexcept
{
    minBalanceForInterestCalculation_.reset();
    dirtyFlag_[26] = true;
}

const std::string &SavingsAccount::getValueOfMinRequiredBalance() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minRequiredBalance_)
        return *minRequiredBalance_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getMinRequiredBalance() const noexcept
{
    return minRequiredBalance_;
}
void SavingsAccount::setMinRequiredBalance(const std::string &pMinRequiredBalance) noexcept
{
    minRequiredBalance_ = std::make_shared<std::string>(pMinRequiredBalance);
    dirtyFlag_[27] = true;
}
void SavingsAccount::setMinRequiredBalance(std::string &&pMinRequiredBalance) noexcept
{
    minRequiredBalance_ = std::make_shared<std::string>(std::move(pMinRequiredBalance));
    dirtyFlag_[27] = true;
}
void SavingsAccount::setMinRequiredBalanceToNull() noexcept
{
    minRequiredBalance_.reset();
    dirtyFlag_[27] = true;
}

const bool &SavingsAccount::getValueOfEnforceMinRequiredBalance() const noexcept
{
    static const bool defaultValue = bool();
    if(enforceMinRequiredBalance_)
        return *enforceMinRequiredBalance_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccount::getEnforceMinRequiredBalance() const noexcept
{
    return enforceMinRequiredBalance_;
}
void SavingsAccount::setEnforceMinRequiredBalance(const bool &pEnforceMinRequiredBalance) noexcept
{
    enforceMinRequiredBalance_ = std::make_shared<bool>(pEnforceMinRequiredBalance);
    dirtyFlag_[28] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfSubmittedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedOnDate_)
        return *submittedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getSubmittedOnDate() const noexcept
{
    return submittedOnDate_;
}
void SavingsAccount::setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept
{
    submittedOnDate_ = std::make_shared<::trantor::Date>(pSubmittedOnDate);
    dirtyFlag_[29] = true;
}
void SavingsAccount::setSubmittedOnDateToNull() noexcept
{
    submittedOnDate_.reset();
    dirtyFlag_[29] = true;
}

const std::string &SavingsAccount::getValueOfSubmittedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(submittedBy_)
        return *submittedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getSubmittedBy() const noexcept
{
    return submittedBy_;
}
void SavingsAccount::setSubmittedBy(const std::string &pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(pSubmittedBy);
    dirtyFlag_[30] = true;
}
void SavingsAccount::setSubmittedBy(std::string &&pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(std::move(pSubmittedBy));
    dirtyFlag_[30] = true;
}
void SavingsAccount::setSubmittedByToNull() noexcept
{
    submittedBy_.reset();
    dirtyFlag_[30] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfApprovedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(approvedOnDate_)
        return *approvedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getApprovedOnDate() const noexcept
{
    return approvedOnDate_;
}
void SavingsAccount::setApprovedOnDate(const ::trantor::Date &pApprovedOnDate) noexcept
{
    approvedOnDate_ = std::make_shared<::trantor::Date>(pApprovedOnDate);
    dirtyFlag_[31] = true;
}
void SavingsAccount::setApprovedOnDateToNull() noexcept
{
    approvedOnDate_.reset();
    dirtyFlag_[31] = true;
}

const std::string &SavingsAccount::getValueOfApprovedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(approvedBy_)
        return *approvedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getApprovedBy() const noexcept
{
    return approvedBy_;
}
void SavingsAccount::setApprovedBy(const std::string &pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(pApprovedBy);
    dirtyFlag_[32] = true;
}
void SavingsAccount::setApprovedBy(std::string &&pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(std::move(pApprovedBy));
    dirtyFlag_[32] = true;
}
void SavingsAccount::setApprovedByToNull() noexcept
{
    approvedBy_.reset();
    dirtyFlag_[32] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfActivatedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(activatedOnDate_)
        return *activatedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getActivatedOnDate() const noexcept
{
    return activatedOnDate_;
}
void SavingsAccount::setActivatedOnDate(const ::trantor::Date &pActivatedOnDate) noexcept
{
    activatedOnDate_ = std::make_shared<::trantor::Date>(pActivatedOnDate);
    dirtyFlag_[33] = true;
}
void SavingsAccount::setActivatedOnDateToNull() noexcept
{
    activatedOnDate_.reset();
    dirtyFlag_[33] = true;
}

const std::string &SavingsAccount::getValueOfActivatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(activatedBy_)
        return *activatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getActivatedBy() const noexcept
{
    return activatedBy_;
}
void SavingsAccount::setActivatedBy(const std::string &pActivatedBy) noexcept
{
    activatedBy_ = std::make_shared<std::string>(pActivatedBy);
    dirtyFlag_[34] = true;
}
void SavingsAccount::setActivatedBy(std::string &&pActivatedBy) noexcept
{
    activatedBy_ = std::make_shared<std::string>(std::move(pActivatedBy));
    dirtyFlag_[34] = true;
}
void SavingsAccount::setActivatedByToNull() noexcept
{
    activatedBy_.reset();
    dirtyFlag_[34] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfRejectedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(rejectedOnDate_)
        return *rejectedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getRejectedOnDate() const noexcept
{
    return rejectedOnDate_;
}
void SavingsAccount::setRejectedOnDate(const ::trantor::Date &pRejectedOnDate) noexcept
{
    rejectedOnDate_ = std::make_shared<::trantor::Date>(pRejectedOnDate);
    dirtyFlag_[35] = true;
}
void SavingsAccount::setRejectedOnDateToNull() noexcept
{
    rejectedOnDate_.reset();
    dirtyFlag_[35] = true;
}

const std::string &SavingsAccount::getValueOfRejectedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(rejectedBy_)
        return *rejectedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getRejectedBy() const noexcept
{
    return rejectedBy_;
}
void SavingsAccount::setRejectedBy(const std::string &pRejectedBy) noexcept
{
    rejectedBy_ = std::make_shared<std::string>(pRejectedBy);
    dirtyFlag_[36] = true;
}
void SavingsAccount::setRejectedBy(std::string &&pRejectedBy) noexcept
{
    rejectedBy_ = std::make_shared<std::string>(std::move(pRejectedBy));
    dirtyFlag_[36] = true;
}
void SavingsAccount::setRejectedByToNull() noexcept
{
    rejectedBy_.reset();
    dirtyFlag_[36] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfWithdrawnOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(withdrawnOnDate_)
        return *withdrawnOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getWithdrawnOnDate() const noexcept
{
    return withdrawnOnDate_;
}
void SavingsAccount::setWithdrawnOnDate(const ::trantor::Date &pWithdrawnOnDate) noexcept
{
    withdrawnOnDate_ = std::make_shared<::trantor::Date>(pWithdrawnOnDate);
    dirtyFlag_[37] = true;
}
void SavingsAccount::setWithdrawnOnDateToNull() noexcept
{
    withdrawnOnDate_.reset();
    dirtyFlag_[37] = true;
}

const std::string &SavingsAccount::getValueOfWithdrawnBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(withdrawnBy_)
        return *withdrawnBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getWithdrawnBy() const noexcept
{
    return withdrawnBy_;
}
void SavingsAccount::setWithdrawnBy(const std::string &pWithdrawnBy) noexcept
{
    withdrawnBy_ = std::make_shared<std::string>(pWithdrawnBy);
    dirtyFlag_[38] = true;
}
void SavingsAccount::setWithdrawnBy(std::string &&pWithdrawnBy) noexcept
{
    withdrawnBy_ = std::make_shared<std::string>(std::move(pWithdrawnBy));
    dirtyFlag_[38] = true;
}
void SavingsAccount::setWithdrawnByToNull() noexcept
{
    withdrawnBy_.reset();
    dirtyFlag_[38] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfClosedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(closedOnDate_)
        return *closedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getClosedOnDate() const noexcept
{
    return closedOnDate_;
}
void SavingsAccount::setClosedOnDate(const ::trantor::Date &pClosedOnDate) noexcept
{
    closedOnDate_ = std::make_shared<::trantor::Date>(pClosedOnDate);
    dirtyFlag_[39] = true;
}
void SavingsAccount::setClosedOnDateToNull() noexcept
{
    closedOnDate_.reset();
    dirtyFlag_[39] = true;
}

const std::string &SavingsAccount::getValueOfClosedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(closedBy_)
        return *closedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getClosedBy() const noexcept
{
    return closedBy_;
}
void SavingsAccount::setClosedBy(const std::string &pClosedBy) noexcept
{
    closedBy_ = std::make_shared<std::string>(pClosedBy);
    dirtyFlag_[40] = true;
}
void SavingsAccount::setClosedBy(std::string &&pClosedBy) noexcept
{
    closedBy_ = std::make_shared<std::string>(std::move(pClosedBy));
    dirtyFlag_[40] = true;
}
void SavingsAccount::setClosedByToNull() noexcept
{
    closedBy_.reset();
    dirtyFlag_[40] = true;
}

const std::string &SavingsAccount::getValueOfAccountBalanceDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountBalanceDerived_)
        return *accountBalanceDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getAccountBalanceDerived() const noexcept
{
    return accountBalanceDerived_;
}
void SavingsAccount::setAccountBalanceDerived(const std::string &pAccountBalanceDerived) noexcept
{
    accountBalanceDerived_ = std::make_shared<std::string>(pAccountBalanceDerived);
    dirtyFlag_[41] = true;
}
void SavingsAccount::setAccountBalanceDerived(std::string &&pAccountBalanceDerived) noexcept
{
    accountBalanceDerived_ = std::make_shared<std::string>(std::move(pAccountBalanceDerived));
    dirtyFlag_[41] = true;
}

const std::string &SavingsAccount::getValueOfTotalDepositsDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(totalDepositsDerived_)
        return *totalDepositsDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getTotalDepositsDerived() const noexcept
{
    return totalDepositsDerived_;
}
void SavingsAccount::setTotalDepositsDerived(const std::string &pTotalDepositsDerived) noexcept
{
    totalDepositsDerived_ = std::make_shared<std::string>(pTotalDepositsDerived);
    dirtyFlag_[42] = true;
}
void SavingsAccount::setTotalDepositsDerived(std::string &&pTotalDepositsDerived) noexcept
{
    totalDepositsDerived_ = std::make_shared<std::string>(std::move(pTotalDepositsDerived));
    dirtyFlag_[42] = true;
}

const std::string &SavingsAccount::getValueOfTotalWithdrawalsDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(totalWithdrawalsDerived_)
        return *totalWithdrawalsDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getTotalWithdrawalsDerived() const noexcept
{
    return totalWithdrawalsDerived_;
}
void SavingsAccount::setTotalWithdrawalsDerived(const std::string &pTotalWithdrawalsDerived) noexcept
{
    totalWithdrawalsDerived_ = std::make_shared<std::string>(pTotalWithdrawalsDerived);
    dirtyFlag_[43] = true;
}
void SavingsAccount::setTotalWithdrawalsDerived(std::string &&pTotalWithdrawalsDerived) noexcept
{
    totalWithdrawalsDerived_ = std::make_shared<std::string>(std::move(pTotalWithdrawalsDerived));
    dirtyFlag_[43] = true;
}

const std::string &SavingsAccount::getValueOfTotalInterestPostedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(totalInterestPostedDerived_)
        return *totalInterestPostedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getTotalInterestPostedDerived() const noexcept
{
    return totalInterestPostedDerived_;
}
void SavingsAccount::setTotalInterestPostedDerived(const std::string &pTotalInterestPostedDerived) noexcept
{
    totalInterestPostedDerived_ = std::make_shared<std::string>(pTotalInterestPostedDerived);
    dirtyFlag_[44] = true;
}
void SavingsAccount::setTotalInterestPostedDerived(std::string &&pTotalInterestPostedDerived) noexcept
{
    totalInterestPostedDerived_ = std::make_shared<std::string>(std::move(pTotalInterestPostedDerived));
    dirtyFlag_[44] = true;
}

const std::string &SavingsAccount::getValueOfTotalFeeChargeDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(totalFeeChargeDerived_)
        return *totalFeeChargeDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getTotalFeeChargeDerived() const noexcept
{
    return totalFeeChargeDerived_;
}
void SavingsAccount::setTotalFeeChargeDerived(const std::string &pTotalFeeChargeDerived) noexcept
{
    totalFeeChargeDerived_ = std::make_shared<std::string>(pTotalFeeChargeDerived);
    dirtyFlag_[45] = true;
}
void SavingsAccount::setTotalFeeChargeDerived(std::string &&pTotalFeeChargeDerived) noexcept
{
    totalFeeChargeDerived_ = std::make_shared<std::string>(std::move(pTotalFeeChargeDerived));
    dirtyFlag_[45] = true;
}

const std::string &SavingsAccount::getValueOfTotalWithdrawalFeeDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(totalWithdrawalFeeDerived_)
        return *totalWithdrawalFeeDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getTotalWithdrawalFeeDerived() const noexcept
{
    return totalWithdrawalFeeDerived_;
}
void SavingsAccount::setTotalWithdrawalFeeDerived(const std::string &pTotalWithdrawalFeeDerived) noexcept
{
    totalWithdrawalFeeDerived_ = std::make_shared<std::string>(pTotalWithdrawalFeeDerived);
    dirtyFlag_[46] = true;
}
void SavingsAccount::setTotalWithdrawalFeeDerived(std::string &&pTotalWithdrawalFeeDerived) noexcept
{
    totalWithdrawalFeeDerived_ = std::make_shared<std::string>(std::move(pTotalWithdrawalFeeDerived));
    dirtyFlag_[46] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfLastInterestCalculationDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(lastInterestCalculationDate_)
        return *lastInterestCalculationDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getLastInterestCalculationDate() const noexcept
{
    return lastInterestCalculationDate_;
}
void SavingsAccount::setLastInterestCalculationDate(const ::trantor::Date &pLastInterestCalculationDate) noexcept
{
    lastInterestCalculationDate_ = std::make_shared<::trantor::Date>(pLastInterestCalculationDate);
    dirtyFlag_[47] = true;
}
void SavingsAccount::setLastInterestCalculationDateToNull() noexcept
{
    lastInterestCalculationDate_.reset();
    dirtyFlag_[47] = true;
}

const bool &SavingsAccount::getValueOfIsCreditBlocked() const noexcept
{
    static const bool defaultValue = bool();
    if(isCreditBlocked_)
        return *isCreditBlocked_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccount::getIsCreditBlocked() const noexcept
{
    return isCreditBlocked_;
}
void SavingsAccount::setIsCreditBlocked(const bool &pIsCreditBlocked) noexcept
{
    isCreditBlocked_ = std::make_shared<bool>(pIsCreditBlocked);
    dirtyFlag_[48] = true;
}

const bool &SavingsAccount::getValueOfIsDebitBlocked() const noexcept
{
    static const bool defaultValue = bool();
    if(isDebitBlocked_)
        return *isDebitBlocked_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccount::getIsDebitBlocked() const noexcept
{
    return isDebitBlocked_;
}
void SavingsAccount::setIsDebitBlocked(const bool &pIsDebitBlocked) noexcept
{
    isDebitBlocked_ = std::make_shared<bool>(pIsDebitBlocked);
    dirtyFlag_[49] = true;
}

const bool &SavingsAccount::getValueOfIsInterestBlocked() const noexcept
{
    static const bool defaultValue = bool();
    if(isInterestBlocked_)
        return *isInterestBlocked_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccount::getIsInterestBlocked() const noexcept
{
    return isInterestBlocked_;
}
void SavingsAccount::setIsInterestBlocked(const bool &pIsInterestBlocked) noexcept
{
    isInterestBlocked_ = std::make_shared<bool>(pIsInterestBlocked);
    dirtyFlag_[50] = true;
}

const std::string &SavingsAccount::getValueOfParentAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(parentAccountId_)
        return *parentAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getParentAccountId() const noexcept
{
    return parentAccountId_;
}
void SavingsAccount::setParentAccountId(const std::string &pParentAccountId) noexcept
{
    parentAccountId_ = std::make_shared<std::string>(pParentAccountId);
    dirtyFlag_[51] = true;
}
void SavingsAccount::setParentAccountId(std::string &&pParentAccountId) noexcept
{
    parentAccountId_ = std::make_shared<std::string>(std::move(pParentAccountId));
    dirtyFlag_[51] = true;
}
void SavingsAccount::setParentAccountIdToNull() noexcept
{
    parentAccountId_.reset();
    dirtyFlag_[51] = true;
}

const bool &SavingsAccount::getValueOfIsGsimParent() const noexcept
{
    static const bool defaultValue = bool();
    if(isGsimParent_)
        return *isGsimParent_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccount::getIsGsimParent() const noexcept
{
    return isGsimParent_;
}
void SavingsAccount::setIsGsimParent(const bool &pIsGsimParent) noexcept
{
    isGsimParent_ = std::make_shared<bool>(pIsGsimParent);
    dirtyFlag_[52] = true;
}

const std::string &SavingsAccount::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getCreatedBy() const noexcept
{
    return createdBy_;
}
void SavingsAccount::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[53] = true;
}
void SavingsAccount::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[53] = true;
}
void SavingsAccount::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[53] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SavingsAccount::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[54] = true;
}

const std::string &SavingsAccount::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccount::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void SavingsAccount::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[55] = true;
}
void SavingsAccount::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[55] = true;
}
void SavingsAccount::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[55] = true;
}

const ::trantor::Date &SavingsAccount::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccount::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void SavingsAccount::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[56] = true;
}

void SavingsAccount::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SavingsAccount::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "account_no",
        "external_id",
        "deposit_type",
        "client_id",
        "group_id",
        "product_id",
        "field_officer_id",
        "status",
        "sub_status",
        "account_type",
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
        "submitted_on_date",
        "submitted_by",
        "approved_on_date",
        "approved_by",
        "activated_on_date",
        "activated_by",
        "rejected_on_date",
        "rejected_by",
        "withdrawn_on_date",
        "withdrawn_by",
        "closed_on_date",
        "closed_by",
        "account_balance_derived",
        "total_deposits_derived",
        "total_withdrawals_derived",
        "total_interest_posted_derived",
        "total_fee_charge_derived",
        "total_withdrawal_fee_derived",
        "last_interest_calculation_date",
        "is_credit_blocked",
        "is_debit_blocked",
        "is_interest_blocked",
        "parent_account_id",
        "is_gsim_parent",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void SavingsAccount::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getFieldOfficerId())
        {
            binder << getValueOfFieldOfficerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
    {
        if(getAccountType())
        {
            binder << getValueOfAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
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
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
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
    if(dirtyFlag_[22])
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
    if(dirtyFlag_[23])
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
    if(dirtyFlag_[24])
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
    if(dirtyFlag_[25])
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
    if(dirtyFlag_[26])
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
    if(dirtyFlag_[27])
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
    if(dirtyFlag_[28])
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
    if(dirtyFlag_[29])
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
    if(dirtyFlag_[30])
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
    if(dirtyFlag_[31])
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
    if(dirtyFlag_[32])
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
    if(dirtyFlag_[33])
    {
        if(getActivatedOnDate())
        {
            binder << getValueOfActivatedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getActivatedBy())
        {
            binder << getValueOfActivatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
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
    if(dirtyFlag_[36])
    {
        if(getRejectedBy())
        {
            binder << getValueOfRejectedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
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
    if(dirtyFlag_[38])
    {
        if(getWithdrawnBy())
        {
            binder << getValueOfWithdrawnBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
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
    if(dirtyFlag_[40])
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
    if(dirtyFlag_[41])
    {
        if(getAccountBalanceDerived())
        {
            binder << getValueOfAccountBalanceDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getTotalDepositsDerived())
        {
            binder << getValueOfTotalDepositsDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getTotalWithdrawalsDerived())
        {
            binder << getValueOfTotalWithdrawalsDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getTotalInterestPostedDerived())
        {
            binder << getValueOfTotalInterestPostedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getTotalFeeChargeDerived())
        {
            binder << getValueOfTotalFeeChargeDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getTotalWithdrawalFeeDerived())
        {
            binder << getValueOfTotalWithdrawalFeeDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getLastInterestCalculationDate())
        {
            binder << getValueOfLastInterestCalculationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getIsCreditBlocked())
        {
            binder << getValueOfIsCreditBlocked();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getIsDebitBlocked())
        {
            binder << getValueOfIsDebitBlocked();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getIsInterestBlocked())
        {
            binder << getValueOfIsInterestBlocked();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getParentAccountId())
        {
            binder << getValueOfParentAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getIsGsimParent())
        {
            binder << getValueOfIsGsimParent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[53])
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
    if(dirtyFlag_[54])
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
    if(dirtyFlag_[55])
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
    if(dirtyFlag_[56])
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

const std::vector<std::string> SavingsAccount::updateColumns() const
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
    return ret;
}

void SavingsAccount::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getFieldOfficerId())
        {
            binder << getValueOfFieldOfficerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
    {
        if(getAccountType())
        {
            binder << getValueOfAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
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
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
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
    if(dirtyFlag_[22])
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
    if(dirtyFlag_[23])
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
    if(dirtyFlag_[24])
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
    if(dirtyFlag_[25])
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
    if(dirtyFlag_[26])
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
    if(dirtyFlag_[27])
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
    if(dirtyFlag_[28])
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
    if(dirtyFlag_[29])
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
    if(dirtyFlag_[30])
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
    if(dirtyFlag_[31])
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
    if(dirtyFlag_[32])
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
    if(dirtyFlag_[33])
    {
        if(getActivatedOnDate())
        {
            binder << getValueOfActivatedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getActivatedBy())
        {
            binder << getValueOfActivatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
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
    if(dirtyFlag_[36])
    {
        if(getRejectedBy())
        {
            binder << getValueOfRejectedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
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
    if(dirtyFlag_[38])
    {
        if(getWithdrawnBy())
        {
            binder << getValueOfWithdrawnBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
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
    if(dirtyFlag_[40])
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
    if(dirtyFlag_[41])
    {
        if(getAccountBalanceDerived())
        {
            binder << getValueOfAccountBalanceDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getTotalDepositsDerived())
        {
            binder << getValueOfTotalDepositsDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getTotalWithdrawalsDerived())
        {
            binder << getValueOfTotalWithdrawalsDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getTotalInterestPostedDerived())
        {
            binder << getValueOfTotalInterestPostedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getTotalFeeChargeDerived())
        {
            binder << getValueOfTotalFeeChargeDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getTotalWithdrawalFeeDerived())
        {
            binder << getValueOfTotalWithdrawalFeeDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getLastInterestCalculationDate())
        {
            binder << getValueOfLastInterestCalculationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getIsCreditBlocked())
        {
            binder << getValueOfIsCreditBlocked();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getIsDebitBlocked())
        {
            binder << getValueOfIsDebitBlocked();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getIsInterestBlocked())
        {
            binder << getValueOfIsInterestBlocked();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getParentAccountId())
        {
            binder << getValueOfParentAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getIsGsimParent())
        {
            binder << getValueOfIsGsimParent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[53])
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
    if(dirtyFlag_[54])
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
    if(dirtyFlag_[55])
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
    if(dirtyFlag_[56])
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
