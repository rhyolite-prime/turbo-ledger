/**
 *  SavingsProduct.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<SavingsProduct> usage actually needs
 *  (row-mapping + CRUD via Mapper/CoroMapper). The Json::Value constructors,
 *  updateByJson/updateByMasqueradedJson, validateJsonFor.../validJsonOfField
 *  and toJson/toString/toMasqueradedJson methods that a live
 *  `drogon_ctl create_model` run would also emit are intentionally omitted
 *  here since nothing in this codebase calls them; regenerate with
 *  `drogon_ctl create_model` against a live DB with this table if those are
 *  ever needed.
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace TlDamDb
{

class SavingsProduct
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _deposit_type;
        static const std::string _name;
        static const std::string _short_name;
        static const std::string _description;
        static const std::string _currency_code;
        static const std::string _digits_after_decimal;
        static const std::string _in_multiples_of;
        static const std::string _nominal_annual_interest_rate;
        static const std::string _interest_compounding_period_type;
        static const std::string _interest_posting_period_type;
        static const std::string _interest_calculation_type;
        static const std::string _interest_calculation_days_in_year_type;
        static const std::string _min_required_opening_balance;
        static const std::string _lockin_period_frequency;
        static const std::string _lockin_period_frequency_type;
        static const std::string _withdrawal_fee_for_transfer;
        static const std::string _allow_overdraft;
        static const std::string _overdraft_limit;
        static const std::string _min_balance_for_interest_calculation;
        static const std::string _min_required_balance;
        static const std::string _enforce_min_required_balance;
        static const std::string _is_dormancy_tracking_active;
        static const std::string _days_to_inactive;
        static const std::string _days_to_dormancy;
        static const std::string _days_to_escheat;
        static const std::string _accounting_type;
        static const std::string _interest_rate_chart_id;
        static const std::string _pre_closure_penal_applicable;
        static const std::string _pre_closure_penal_interest;
        static const std::string _pre_closure_penal_interest_on_type;
        static const std::string _min_deposit_term;
        static const std::string _min_deposit_term_type;
        static const std::string _max_deposit_term;
        static const std::string _max_deposit_term_type;
        static const std::string _in_multiples_of_deposit_term;
        static const std::string _in_multiples_of_deposit_term_type;
        static const std::string _is_mandatory_deposit;
        static const std::string _allow_withdrawal;
        static const std::string _adjust_advance_towards_future_payments;
        static const std::string _is_active;
        static const std::string _created_by;
        static const std::string _created_at;
        static const std::string _updated_by;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit SavingsProduct(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    SavingsProduct() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column business_id  */
    const std::string &getValueOfBusinessId() const noexcept;
    const std::shared_ptr<std::string> &getBusinessId() const noexcept;
    void setBusinessId(const std::string &pBusinessId) noexcept;
    void setBusinessId(std::string &&pBusinessId) noexcept;
    void setBusinessIdToNull() noexcept;

    /**  For column deposit_type  */
    const int32_t &getValueOfDepositType() const noexcept;
    const std::shared_ptr<int32_t> &getDepositType() const noexcept;
    void setDepositType(const int32_t &pDepositType) noexcept;

    /**  For column name  */
    const std::string &getValueOfName() const noexcept;
    const std::shared_ptr<std::string> &getName() const noexcept;
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column short_name  */
    const std::string &getValueOfShortName() const noexcept;
    const std::shared_ptr<std::string> &getShortName() const noexcept;
    void setShortName(const std::string &pShortName) noexcept;
    void setShortName(std::string &&pShortName) noexcept;

    /**  For column description  */
    const std::string &getValueOfDescription() const noexcept;
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;
    void setDescriptionToNull() noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column digits_after_decimal  */
    const int32_t &getValueOfDigitsAfterDecimal() const noexcept;
    const std::shared_ptr<int32_t> &getDigitsAfterDecimal() const noexcept;
    void setDigitsAfterDecimal(const int32_t &pDigitsAfterDecimal) noexcept;

    /**  For column in_multiples_of  */
    const int32_t &getValueOfInMultiplesOf() const noexcept;
    const std::shared_ptr<int32_t> &getInMultiplesOf() const noexcept;
    void setInMultiplesOf(const int32_t &pInMultiplesOf) noexcept;

    /**  For column nominal_annual_interest_rate  */
    const std::string &getValueOfNominalAnnualInterestRate() const noexcept;
    const std::shared_ptr<std::string> &getNominalAnnualInterestRate() const noexcept;
    void setNominalAnnualInterestRate(const std::string &pNominalAnnualInterestRate) noexcept;
    void setNominalAnnualInterestRate(std::string &&pNominalAnnualInterestRate) noexcept;

    /**  For column interest_compounding_period_type  */
    const int32_t &getValueOfInterestCompoundingPeriodType() const noexcept;
    const std::shared_ptr<int32_t> &getInterestCompoundingPeriodType() const noexcept;
    void setInterestCompoundingPeriodType(const int32_t &pInterestCompoundingPeriodType) noexcept;

    /**  For column interest_posting_period_type  */
    const int32_t &getValueOfInterestPostingPeriodType() const noexcept;
    const std::shared_ptr<int32_t> &getInterestPostingPeriodType() const noexcept;
    void setInterestPostingPeriodType(const int32_t &pInterestPostingPeriodType) noexcept;

    /**  For column interest_calculation_type  */
    const int32_t &getValueOfInterestCalculationType() const noexcept;
    const std::shared_ptr<int32_t> &getInterestCalculationType() const noexcept;
    void setInterestCalculationType(const int32_t &pInterestCalculationType) noexcept;

    /**  For column interest_calculation_days_in_year_type  */
    const int32_t &getValueOfInterestCalculationDaysInYearType() const noexcept;
    const std::shared_ptr<int32_t> &getInterestCalculationDaysInYearType() const noexcept;
    void setInterestCalculationDaysInYearType(const int32_t &pInterestCalculationDaysInYearType) noexcept;

    /**  For column min_required_opening_balance  */
    const std::string &getValueOfMinRequiredOpeningBalance() const noexcept;
    const std::shared_ptr<std::string> &getMinRequiredOpeningBalance() const noexcept;
    void setMinRequiredOpeningBalance(const std::string &pMinRequiredOpeningBalance) noexcept;
    void setMinRequiredOpeningBalance(std::string &&pMinRequiredOpeningBalance) noexcept;
    void setMinRequiredOpeningBalanceToNull() noexcept;

    /**  For column lockin_period_frequency  */
    const int32_t &getValueOfLockinPeriodFrequency() const noexcept;
    const std::shared_ptr<int32_t> &getLockinPeriodFrequency() const noexcept;
    void setLockinPeriodFrequency(const int32_t &pLockinPeriodFrequency) noexcept;
    void setLockinPeriodFrequencyToNull() noexcept;

    /**  For column lockin_period_frequency_type  */
    const int32_t &getValueOfLockinPeriodFrequencyType() const noexcept;
    const std::shared_ptr<int32_t> &getLockinPeriodFrequencyType() const noexcept;
    void setLockinPeriodFrequencyType(const int32_t &pLockinPeriodFrequencyType) noexcept;
    void setLockinPeriodFrequencyTypeToNull() noexcept;

    /**  For column withdrawal_fee_for_transfer  */
    const bool &getValueOfWithdrawalFeeForTransfer() const noexcept;
    const std::shared_ptr<bool> &getWithdrawalFeeForTransfer() const noexcept;
    void setWithdrawalFeeForTransfer(const bool &pWithdrawalFeeForTransfer) noexcept;

    /**  For column allow_overdraft  */
    const bool &getValueOfAllowOverdraft() const noexcept;
    const std::shared_ptr<bool> &getAllowOverdraft() const noexcept;
    void setAllowOverdraft(const bool &pAllowOverdraft) noexcept;

    /**  For column overdraft_limit  */
    const std::string &getValueOfOverdraftLimit() const noexcept;
    const std::shared_ptr<std::string> &getOverdraftLimit() const noexcept;
    void setOverdraftLimit(const std::string &pOverdraftLimit) noexcept;
    void setOverdraftLimit(std::string &&pOverdraftLimit) noexcept;
    void setOverdraftLimitToNull() noexcept;

    /**  For column min_balance_for_interest_calculation  */
    const std::string &getValueOfMinBalanceForInterestCalculation() const noexcept;
    const std::shared_ptr<std::string> &getMinBalanceForInterestCalculation() const noexcept;
    void setMinBalanceForInterestCalculation(const std::string &pMinBalanceForInterestCalculation) noexcept;
    void setMinBalanceForInterestCalculation(std::string &&pMinBalanceForInterestCalculation) noexcept;
    void setMinBalanceForInterestCalculationToNull() noexcept;

    /**  For column min_required_balance  */
    const std::string &getValueOfMinRequiredBalance() const noexcept;
    const std::shared_ptr<std::string> &getMinRequiredBalance() const noexcept;
    void setMinRequiredBalance(const std::string &pMinRequiredBalance) noexcept;
    void setMinRequiredBalance(std::string &&pMinRequiredBalance) noexcept;
    void setMinRequiredBalanceToNull() noexcept;

    /**  For column enforce_min_required_balance  */
    const bool &getValueOfEnforceMinRequiredBalance() const noexcept;
    const std::shared_ptr<bool> &getEnforceMinRequiredBalance() const noexcept;
    void setEnforceMinRequiredBalance(const bool &pEnforceMinRequiredBalance) noexcept;

    /**  For column is_dormancy_tracking_active  */
    const bool &getValueOfIsDormancyTrackingActive() const noexcept;
    const std::shared_ptr<bool> &getIsDormancyTrackingActive() const noexcept;
    void setIsDormancyTrackingActive(const bool &pIsDormancyTrackingActive) noexcept;

    /**  For column days_to_inactive  */
    const int32_t &getValueOfDaysToInactive() const noexcept;
    const std::shared_ptr<int32_t> &getDaysToInactive() const noexcept;
    void setDaysToInactive(const int32_t &pDaysToInactive) noexcept;
    void setDaysToInactiveToNull() noexcept;

    /**  For column days_to_dormancy  */
    const int32_t &getValueOfDaysToDormancy() const noexcept;
    const std::shared_ptr<int32_t> &getDaysToDormancy() const noexcept;
    void setDaysToDormancy(const int32_t &pDaysToDormancy) noexcept;
    void setDaysToDormancyToNull() noexcept;

    /**  For column days_to_escheat  */
    const int32_t &getValueOfDaysToEscheat() const noexcept;
    const std::shared_ptr<int32_t> &getDaysToEscheat() const noexcept;
    void setDaysToEscheat(const int32_t &pDaysToEscheat) noexcept;
    void setDaysToEscheatToNull() noexcept;

    /**  For column accounting_type  */
    const int32_t &getValueOfAccountingType() const noexcept;
    const std::shared_ptr<int32_t> &getAccountingType() const noexcept;
    void setAccountingType(const int32_t &pAccountingType) noexcept;

    /**  For column interest_rate_chart_id  */
    const std::string &getValueOfInterestRateChartId() const noexcept;
    const std::shared_ptr<std::string> &getInterestRateChartId() const noexcept;
    void setInterestRateChartId(const std::string &pInterestRateChartId) noexcept;
    void setInterestRateChartId(std::string &&pInterestRateChartId) noexcept;
    void setInterestRateChartIdToNull() noexcept;

    /**  For column pre_closure_penal_applicable  */
    const bool &getValueOfPreClosurePenalApplicable() const noexcept;
    const std::shared_ptr<bool> &getPreClosurePenalApplicable() const noexcept;
    void setPreClosurePenalApplicable(const bool &pPreClosurePenalApplicable) noexcept;
    void setPreClosurePenalApplicableToNull() noexcept;

    /**  For column pre_closure_penal_interest  */
    const std::string &getValueOfPreClosurePenalInterest() const noexcept;
    const std::shared_ptr<std::string> &getPreClosurePenalInterest() const noexcept;
    void setPreClosurePenalInterest(const std::string &pPreClosurePenalInterest) noexcept;
    void setPreClosurePenalInterest(std::string &&pPreClosurePenalInterest) noexcept;
    void setPreClosurePenalInterestToNull() noexcept;

    /**  For column pre_closure_penal_interest_on_type  */
    const int32_t &getValueOfPreClosurePenalInterestOnType() const noexcept;
    const std::shared_ptr<int32_t> &getPreClosurePenalInterestOnType() const noexcept;
    void setPreClosurePenalInterestOnType(const int32_t &pPreClosurePenalInterestOnType) noexcept;
    void setPreClosurePenalInterestOnTypeToNull() noexcept;

    /**  For column min_deposit_term  */
    const int32_t &getValueOfMinDepositTerm() const noexcept;
    const std::shared_ptr<int32_t> &getMinDepositTerm() const noexcept;
    void setMinDepositTerm(const int32_t &pMinDepositTerm) noexcept;
    void setMinDepositTermToNull() noexcept;

    /**  For column min_deposit_term_type  */
    const int32_t &getValueOfMinDepositTermType() const noexcept;
    const std::shared_ptr<int32_t> &getMinDepositTermType() const noexcept;
    void setMinDepositTermType(const int32_t &pMinDepositTermType) noexcept;
    void setMinDepositTermTypeToNull() noexcept;

    /**  For column max_deposit_term  */
    const int32_t &getValueOfMaxDepositTerm() const noexcept;
    const std::shared_ptr<int32_t> &getMaxDepositTerm() const noexcept;
    void setMaxDepositTerm(const int32_t &pMaxDepositTerm) noexcept;
    void setMaxDepositTermToNull() noexcept;

    /**  For column max_deposit_term_type  */
    const int32_t &getValueOfMaxDepositTermType() const noexcept;
    const std::shared_ptr<int32_t> &getMaxDepositTermType() const noexcept;
    void setMaxDepositTermType(const int32_t &pMaxDepositTermType) noexcept;
    void setMaxDepositTermTypeToNull() noexcept;

    /**  For column in_multiples_of_deposit_term  */
    const int32_t &getValueOfInMultiplesOfDepositTerm() const noexcept;
    const std::shared_ptr<int32_t> &getInMultiplesOfDepositTerm() const noexcept;
    void setInMultiplesOfDepositTerm(const int32_t &pInMultiplesOfDepositTerm) noexcept;
    void setInMultiplesOfDepositTermToNull() noexcept;

    /**  For column in_multiples_of_deposit_term_type  */
    const int32_t &getValueOfInMultiplesOfDepositTermType() const noexcept;
    const std::shared_ptr<int32_t> &getInMultiplesOfDepositTermType() const noexcept;
    void setInMultiplesOfDepositTermType(const int32_t &pInMultiplesOfDepositTermType) noexcept;
    void setInMultiplesOfDepositTermTypeToNull() noexcept;

    /**  For column is_mandatory_deposit  */
    const bool &getValueOfIsMandatoryDeposit() const noexcept;
    const std::shared_ptr<bool> &getIsMandatoryDeposit() const noexcept;
    void setIsMandatoryDeposit(const bool &pIsMandatoryDeposit) noexcept;
    void setIsMandatoryDepositToNull() noexcept;

    /**  For column allow_withdrawal  */
    const bool &getValueOfAllowWithdrawal() const noexcept;
    const std::shared_ptr<bool> &getAllowWithdrawal() const noexcept;
    void setAllowWithdrawal(const bool &pAllowWithdrawal) noexcept;
    void setAllowWithdrawalToNull() noexcept;

    /**  For column adjust_advance_towards_future_payments  */
    const bool &getValueOfAdjustAdvanceTowardsFuturePayments() const noexcept;
    const std::shared_ptr<bool> &getAdjustAdvanceTowardsFuturePayments() const noexcept;
    void setAdjustAdvanceTowardsFuturePayments(const bool &pAdjustAdvanceTowardsFuturePayments) noexcept;
    void setAdjustAdvanceTowardsFuturePaymentsToNull() noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

    /**  For column created_by  */
    const std::string &getValueOfCreatedBy() const noexcept;
    const std::shared_ptr<std::string> &getCreatedBy() const noexcept;
    void setCreatedBy(const std::string &pCreatedBy) noexcept;
    void setCreatedBy(std::string &&pCreatedBy) noexcept;
    void setCreatedByToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_by  */
    const std::string &getValueOfUpdatedBy() const noexcept;
    const std::shared_ptr<std::string> &getUpdatedBy() const noexcept;
    void setUpdatedBy(const std::string &pUpdatedBy) noexcept;
    void setUpdatedBy(std::string &&pUpdatedBy) noexcept;
    void setUpdatedByToNull() noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 46;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<SavingsProduct>;
    friend drogon::orm::BaseBuilder<SavingsProduct, true, true>;
    friend drogon::orm::BaseBuilder<SavingsProduct, true, false>;
    friend drogon::orm::BaseBuilder<SavingsProduct, false, true>;
    friend drogon::orm::BaseBuilder<SavingsProduct, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<SavingsProduct>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<int32_t> depositType_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> shortName_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<int32_t> digitsAfterDecimal_;
    std::shared_ptr<int32_t> inMultiplesOf_;
    std::shared_ptr<std::string> nominalAnnualInterestRate_;
    std::shared_ptr<int32_t> interestCompoundingPeriodType_;
    std::shared_ptr<int32_t> interestPostingPeriodType_;
    std::shared_ptr<int32_t> interestCalculationType_;
    std::shared_ptr<int32_t> interestCalculationDaysInYearType_;
    std::shared_ptr<std::string> minRequiredOpeningBalance_;
    std::shared_ptr<int32_t> lockinPeriodFrequency_;
    std::shared_ptr<int32_t> lockinPeriodFrequencyType_;
    std::shared_ptr<bool> withdrawalFeeForTransfer_;
    std::shared_ptr<bool> allowOverdraft_;
    std::shared_ptr<std::string> overdraftLimit_;
    std::shared_ptr<std::string> minBalanceForInterestCalculation_;
    std::shared_ptr<std::string> minRequiredBalance_;
    std::shared_ptr<bool> enforceMinRequiredBalance_;
    std::shared_ptr<bool> isDormancyTrackingActive_;
    std::shared_ptr<int32_t> daysToInactive_;
    std::shared_ptr<int32_t> daysToDormancy_;
    std::shared_ptr<int32_t> daysToEscheat_;
    std::shared_ptr<int32_t> accountingType_;
    std::shared_ptr<std::string> interestRateChartId_;
    std::shared_ptr<bool> preClosurePenalApplicable_;
    std::shared_ptr<std::string> preClosurePenalInterest_;
    std::shared_ptr<int32_t> preClosurePenalInterestOnType_;
    std::shared_ptr<int32_t> minDepositTerm_;
    std::shared_ptr<int32_t> minDepositTermType_;
    std::shared_ptr<int32_t> maxDepositTerm_;
    std::shared_ptr<int32_t> maxDepositTermType_;
    std::shared_ptr<int32_t> inMultiplesOfDepositTerm_;
    std::shared_ptr<int32_t> inMultiplesOfDepositTermType_;
    std::shared_ptr<bool> isMandatoryDeposit_;
    std::shared_ptr<bool> allowWithdrawal_;
    std::shared_ptr<bool> adjustAdvanceTowardsFuturePayments_;
    std::shared_ptr<bool> isActive_;
    std::shared_ptr<std::string> createdBy_;
    std::shared_ptr<::trantor::Date> createdAt_;
    std::shared_ptr<std::string> updatedBy_;
    std::shared_ptr<::trantor::Date> updatedAt_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[46]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
        sql += "id,";
        ++parametersCount;
        if(!dirtyFlag_[0])
        {
            needSelection=true;
        }
        if(dirtyFlag_[1])
        {
            sql += "business_id,";
            ++parametersCount;
        }
        sql += "deposit_type,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        if(dirtyFlag_[3])
        {
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "short_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        sql += "digits_after_decimal,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "in_multiples_of,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        if(dirtyFlag_[9])
        {
            sql += "nominal_annual_interest_rate,";
            ++parametersCount;
        }
        sql += "interest_compounding_period_type,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "interest_posting_period_type,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        sql += "interest_calculation_type,";
        ++parametersCount;
        if(!dirtyFlag_[12])
        {
            needSelection=true;
        }
        sql += "interest_calculation_days_in_year_type,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        if(dirtyFlag_[14])
        {
            sql += "min_required_opening_balance,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "lockin_period_frequency,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "lockin_period_frequency_type,";
            ++parametersCount;
        }
        sql += "withdrawal_fee_for_transfer,";
        ++parametersCount;
        if(!dirtyFlag_[17])
        {
            needSelection=true;
        }
        sql += "allow_overdraft,";
        ++parametersCount;
        if(!dirtyFlag_[18])
        {
            needSelection=true;
        }
        if(dirtyFlag_[19])
        {
            sql += "overdraft_limit,";
            ++parametersCount;
        }
        if(dirtyFlag_[20])
        {
            sql += "min_balance_for_interest_calculation,";
            ++parametersCount;
        }
        if(dirtyFlag_[21])
        {
            sql += "min_required_balance,";
            ++parametersCount;
        }
        sql += "enforce_min_required_balance,";
        ++parametersCount;
        if(!dirtyFlag_[22])
        {
            needSelection=true;
        }
        sql += "is_dormancy_tracking_active,";
        ++parametersCount;
        if(!dirtyFlag_[23])
        {
            needSelection=true;
        }
        if(dirtyFlag_[24])
        {
            sql += "days_to_inactive,";
            ++parametersCount;
        }
        if(dirtyFlag_[25])
        {
            sql += "days_to_dormancy,";
            ++parametersCount;
        }
        if(dirtyFlag_[26])
        {
            sql += "days_to_escheat,";
            ++parametersCount;
        }
        sql += "accounting_type,";
        ++parametersCount;
        if(!dirtyFlag_[27])
        {
            needSelection=true;
        }
        if(dirtyFlag_[28])
        {
            sql += "interest_rate_chart_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[29])
        {
            sql += "pre_closure_penal_applicable,";
            ++parametersCount;
        }
        if(dirtyFlag_[30])
        {
            sql += "pre_closure_penal_interest,";
            ++parametersCount;
        }
        if(dirtyFlag_[31])
        {
            sql += "pre_closure_penal_interest_on_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[32])
        {
            sql += "min_deposit_term,";
            ++parametersCount;
        }
        if(dirtyFlag_[33])
        {
            sql += "min_deposit_term_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[34])
        {
            sql += "max_deposit_term,";
            ++parametersCount;
        }
        if(dirtyFlag_[35])
        {
            sql += "max_deposit_term_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[36])
        {
            sql += "in_multiples_of_deposit_term,";
            ++parametersCount;
        }
        if(dirtyFlag_[37])
        {
            sql += "in_multiples_of_deposit_term_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[38])
        {
            sql += "is_mandatory_deposit,";
            ++parametersCount;
        }
        if(dirtyFlag_[39])
        {
            sql += "allow_withdrawal,";
            ++parametersCount;
        }
        if(dirtyFlag_[40])
        {
            sql += "adjust_advance_towards_future_payments,";
            ++parametersCount;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[41])
        {
            needSelection=true;
        }
        if(dirtyFlag_[42])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[43])
        {
            needSelection=true;
        }
        if(dirtyFlag_[44])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[45])
        {
            needSelection=true;
        }
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        if(dirtyFlag_[0])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[1])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[2])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[4])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[5])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[6])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[7])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[8])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[11])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[12])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[13])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[14])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[16])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[17])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[18])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[19])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[20])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[21])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[22])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[23])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[24])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[25])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[26])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[27])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[28])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[29])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[30])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[31])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[32])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[33])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[34])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[35])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[36])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[37])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[38])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[39])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[40])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[41])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[42])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[43])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[44])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[45])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace TlDamDb
} // namespace drogon_model
