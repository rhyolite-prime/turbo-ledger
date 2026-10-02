/**
 *  SavingsAccount.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<SavingsAccount> usage actually needs
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

class SavingsAccount
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _account_no;
        static const std::string _external_id;
        static const std::string _deposit_type;
        static const std::string _client_id;
        static const std::string _group_id;
        static const std::string _product_id;
        static const std::string _field_officer_id;
        static const std::string _status;
        static const std::string _sub_status;
        static const std::string _account_type;
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
        static const std::string _submitted_on_date;
        static const std::string _submitted_by;
        static const std::string _approved_on_date;
        static const std::string _approved_by;
        static const std::string _activated_on_date;
        static const std::string _activated_by;
        static const std::string _rejected_on_date;
        static const std::string _rejected_by;
        static const std::string _withdrawn_on_date;
        static const std::string _withdrawn_by;
        static const std::string _closed_on_date;
        static const std::string _closed_by;
        static const std::string _account_balance_derived;
        static const std::string _total_deposits_derived;
        static const std::string _total_withdrawals_derived;
        static const std::string _total_interest_posted_derived;
        static const std::string _total_fee_charge_derived;
        static const std::string _total_withdrawal_fee_derived;
        static const std::string _last_interest_calculation_date;
        static const std::string _is_credit_blocked;
        static const std::string _is_debit_blocked;
        static const std::string _is_interest_blocked;
        static const std::string _parent_account_id;
        static const std::string _is_gsim_parent;
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

    explicit SavingsAccount(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    SavingsAccount() = default;

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

    /**  For column account_no  */
    const std::string &getValueOfAccountNo() const noexcept;
    const std::shared_ptr<std::string> &getAccountNo() const noexcept;
    void setAccountNo(const std::string &pAccountNo) noexcept;
    void setAccountNo(std::string &&pAccountNo) noexcept;
    void setAccountNoToNull() noexcept;

    /**  For column external_id  */
    const std::string &getValueOfExternalId() const noexcept;
    const std::shared_ptr<std::string> &getExternalId() const noexcept;
    void setExternalId(const std::string &pExternalId) noexcept;
    void setExternalId(std::string &&pExternalId) noexcept;
    void setExternalIdToNull() noexcept;

    /**  For column deposit_type  */
    const int32_t &getValueOfDepositType() const noexcept;
    const std::shared_ptr<int32_t> &getDepositType() const noexcept;
    void setDepositType(const int32_t &pDepositType) noexcept;

    /**  For column client_id  */
    const std::string &getValueOfClientId() const noexcept;
    const std::shared_ptr<std::string> &getClientId() const noexcept;
    void setClientId(const std::string &pClientId) noexcept;
    void setClientId(std::string &&pClientId) noexcept;
    void setClientIdToNull() noexcept;

    /**  For column group_id  */
    const std::string &getValueOfGroupId() const noexcept;
    const std::shared_ptr<std::string> &getGroupId() const noexcept;
    void setGroupId(const std::string &pGroupId) noexcept;
    void setGroupId(std::string &&pGroupId) noexcept;
    void setGroupIdToNull() noexcept;

    /**  For column product_id  */
    const std::string &getValueOfProductId() const noexcept;
    const std::shared_ptr<std::string> &getProductId() const noexcept;
    void setProductId(const std::string &pProductId) noexcept;
    void setProductId(std::string &&pProductId) noexcept;

    /**  For column field_officer_id  */
    const std::string &getValueOfFieldOfficerId() const noexcept;
    const std::shared_ptr<std::string> &getFieldOfficerId() const noexcept;
    void setFieldOfficerId(const std::string &pFieldOfficerId) noexcept;
    void setFieldOfficerId(std::string &&pFieldOfficerId) noexcept;
    void setFieldOfficerIdToNull() noexcept;

    /**  For column status  */
    const int32_t &getValueOfStatus() const noexcept;
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column sub_status  */
    const int32_t &getValueOfSubStatus() const noexcept;
    const std::shared_ptr<int32_t> &getSubStatus() const noexcept;
    void setSubStatus(const int32_t &pSubStatus) noexcept;

    /**  For column account_type  */
    const int32_t &getValueOfAccountType() const noexcept;
    const std::shared_ptr<int32_t> &getAccountType() const noexcept;
    void setAccountType(const int32_t &pAccountType) noexcept;

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

    /**  For column submitted_on_date  */
    const ::trantor::Date &getValueOfSubmittedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedOnDate() const noexcept;
    void setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept;
    void setSubmittedOnDateToNull() noexcept;

    /**  For column submitted_by  */
    const std::string &getValueOfSubmittedBy() const noexcept;
    const std::shared_ptr<std::string> &getSubmittedBy() const noexcept;
    void setSubmittedBy(const std::string &pSubmittedBy) noexcept;
    void setSubmittedBy(std::string &&pSubmittedBy) noexcept;
    void setSubmittedByToNull() noexcept;

    /**  For column approved_on_date  */
    const ::trantor::Date &getValueOfApprovedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getApprovedOnDate() const noexcept;
    void setApprovedOnDate(const ::trantor::Date &pApprovedOnDate) noexcept;
    void setApprovedOnDateToNull() noexcept;

    /**  For column approved_by  */
    const std::string &getValueOfApprovedBy() const noexcept;
    const std::shared_ptr<std::string> &getApprovedBy() const noexcept;
    void setApprovedBy(const std::string &pApprovedBy) noexcept;
    void setApprovedBy(std::string &&pApprovedBy) noexcept;
    void setApprovedByToNull() noexcept;

    /**  For column activated_on_date  */
    const ::trantor::Date &getValueOfActivatedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getActivatedOnDate() const noexcept;
    void setActivatedOnDate(const ::trantor::Date &pActivatedOnDate) noexcept;
    void setActivatedOnDateToNull() noexcept;

    /**  For column activated_by  */
    const std::string &getValueOfActivatedBy() const noexcept;
    const std::shared_ptr<std::string> &getActivatedBy() const noexcept;
    void setActivatedBy(const std::string &pActivatedBy) noexcept;
    void setActivatedBy(std::string &&pActivatedBy) noexcept;
    void setActivatedByToNull() noexcept;

    /**  For column rejected_on_date  */
    const ::trantor::Date &getValueOfRejectedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getRejectedOnDate() const noexcept;
    void setRejectedOnDate(const ::trantor::Date &pRejectedOnDate) noexcept;
    void setRejectedOnDateToNull() noexcept;

    /**  For column rejected_by  */
    const std::string &getValueOfRejectedBy() const noexcept;
    const std::shared_ptr<std::string> &getRejectedBy() const noexcept;
    void setRejectedBy(const std::string &pRejectedBy) noexcept;
    void setRejectedBy(std::string &&pRejectedBy) noexcept;
    void setRejectedByToNull() noexcept;

    /**  For column withdrawn_on_date  */
    const ::trantor::Date &getValueOfWithdrawnOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getWithdrawnOnDate() const noexcept;
    void setWithdrawnOnDate(const ::trantor::Date &pWithdrawnOnDate) noexcept;
    void setWithdrawnOnDateToNull() noexcept;

    /**  For column withdrawn_by  */
    const std::string &getValueOfWithdrawnBy() const noexcept;
    const std::shared_ptr<std::string> &getWithdrawnBy() const noexcept;
    void setWithdrawnBy(const std::string &pWithdrawnBy) noexcept;
    void setWithdrawnBy(std::string &&pWithdrawnBy) noexcept;
    void setWithdrawnByToNull() noexcept;

    /**  For column closed_on_date  */
    const ::trantor::Date &getValueOfClosedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getClosedOnDate() const noexcept;
    void setClosedOnDate(const ::trantor::Date &pClosedOnDate) noexcept;
    void setClosedOnDateToNull() noexcept;

    /**  For column closed_by  */
    const std::string &getValueOfClosedBy() const noexcept;
    const std::shared_ptr<std::string> &getClosedBy() const noexcept;
    void setClosedBy(const std::string &pClosedBy) noexcept;
    void setClosedBy(std::string &&pClosedBy) noexcept;
    void setClosedByToNull() noexcept;

    /**  For column account_balance_derived  */
    const std::string &getValueOfAccountBalanceDerived() const noexcept;
    const std::shared_ptr<std::string> &getAccountBalanceDerived() const noexcept;
    void setAccountBalanceDerived(const std::string &pAccountBalanceDerived) noexcept;
    void setAccountBalanceDerived(std::string &&pAccountBalanceDerived) noexcept;

    /**  For column total_deposits_derived  */
    const std::string &getValueOfTotalDepositsDerived() const noexcept;
    const std::shared_ptr<std::string> &getTotalDepositsDerived() const noexcept;
    void setTotalDepositsDerived(const std::string &pTotalDepositsDerived) noexcept;
    void setTotalDepositsDerived(std::string &&pTotalDepositsDerived) noexcept;

    /**  For column total_withdrawals_derived  */
    const std::string &getValueOfTotalWithdrawalsDerived() const noexcept;
    const std::shared_ptr<std::string> &getTotalWithdrawalsDerived() const noexcept;
    void setTotalWithdrawalsDerived(const std::string &pTotalWithdrawalsDerived) noexcept;
    void setTotalWithdrawalsDerived(std::string &&pTotalWithdrawalsDerived) noexcept;

    /**  For column total_interest_posted_derived  */
    const std::string &getValueOfTotalInterestPostedDerived() const noexcept;
    const std::shared_ptr<std::string> &getTotalInterestPostedDerived() const noexcept;
    void setTotalInterestPostedDerived(const std::string &pTotalInterestPostedDerived) noexcept;
    void setTotalInterestPostedDerived(std::string &&pTotalInterestPostedDerived) noexcept;

    /**  For column total_fee_charge_derived  */
    const std::string &getValueOfTotalFeeChargeDerived() const noexcept;
    const std::shared_ptr<std::string> &getTotalFeeChargeDerived() const noexcept;
    void setTotalFeeChargeDerived(const std::string &pTotalFeeChargeDerived) noexcept;
    void setTotalFeeChargeDerived(std::string &&pTotalFeeChargeDerived) noexcept;

    /**  For column total_withdrawal_fee_derived  */
    const std::string &getValueOfTotalWithdrawalFeeDerived() const noexcept;
    const std::shared_ptr<std::string> &getTotalWithdrawalFeeDerived() const noexcept;
    void setTotalWithdrawalFeeDerived(const std::string &pTotalWithdrawalFeeDerived) noexcept;
    void setTotalWithdrawalFeeDerived(std::string &&pTotalWithdrawalFeeDerived) noexcept;

    /**  For column last_interest_calculation_date  */
    const ::trantor::Date &getValueOfLastInterestCalculationDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getLastInterestCalculationDate() const noexcept;
    void setLastInterestCalculationDate(const ::trantor::Date &pLastInterestCalculationDate) noexcept;
    void setLastInterestCalculationDateToNull() noexcept;

    /**  For column is_credit_blocked  */
    const bool &getValueOfIsCreditBlocked() const noexcept;
    const std::shared_ptr<bool> &getIsCreditBlocked() const noexcept;
    void setIsCreditBlocked(const bool &pIsCreditBlocked) noexcept;

    /**  For column is_debit_blocked  */
    const bool &getValueOfIsDebitBlocked() const noexcept;
    const std::shared_ptr<bool> &getIsDebitBlocked() const noexcept;
    void setIsDebitBlocked(const bool &pIsDebitBlocked) noexcept;

    /**  For column is_interest_blocked  */
    const bool &getValueOfIsInterestBlocked() const noexcept;
    const std::shared_ptr<bool> &getIsInterestBlocked() const noexcept;
    void setIsInterestBlocked(const bool &pIsInterestBlocked) noexcept;

    /**  For column parent_account_id  */
    const std::string &getValueOfParentAccountId() const noexcept;
    const std::shared_ptr<std::string> &getParentAccountId() const noexcept;
    void setParentAccountId(const std::string &pParentAccountId) noexcept;
    void setParentAccountId(std::string &&pParentAccountId) noexcept;
    void setParentAccountIdToNull() noexcept;

    /**  For column is_gsim_parent  */
    const bool &getValueOfIsGsimParent() const noexcept;
    const std::shared_ptr<bool> &getIsGsimParent() const noexcept;
    void setIsGsimParent(const bool &pIsGsimParent) noexcept;

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

    static size_t getColumnNumber() noexcept {  return 57;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<SavingsAccount>;
    friend drogon::orm::BaseBuilder<SavingsAccount, true, true>;
    friend drogon::orm::BaseBuilder<SavingsAccount, true, false>;
    friend drogon::orm::BaseBuilder<SavingsAccount, false, true>;
    friend drogon::orm::BaseBuilder<SavingsAccount, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<SavingsAccount>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> accountNo_;
    std::shared_ptr<std::string> externalId_;
    std::shared_ptr<int32_t> depositType_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> groupId_;
    std::shared_ptr<std::string> productId_;
    std::shared_ptr<std::string> fieldOfficerId_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<int32_t> subStatus_;
    std::shared_ptr<int32_t> accountType_;
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
    std::shared_ptr<::trantor::Date> submittedOnDate_;
    std::shared_ptr<std::string> submittedBy_;
    std::shared_ptr<::trantor::Date> approvedOnDate_;
    std::shared_ptr<std::string> approvedBy_;
    std::shared_ptr<::trantor::Date> activatedOnDate_;
    std::shared_ptr<std::string> activatedBy_;
    std::shared_ptr<::trantor::Date> rejectedOnDate_;
    std::shared_ptr<std::string> rejectedBy_;
    std::shared_ptr<::trantor::Date> withdrawnOnDate_;
    std::shared_ptr<std::string> withdrawnBy_;
    std::shared_ptr<::trantor::Date> closedOnDate_;
    std::shared_ptr<std::string> closedBy_;
    std::shared_ptr<std::string> accountBalanceDerived_;
    std::shared_ptr<std::string> totalDepositsDerived_;
    std::shared_ptr<std::string> totalWithdrawalsDerived_;
    std::shared_ptr<std::string> totalInterestPostedDerived_;
    std::shared_ptr<std::string> totalFeeChargeDerived_;
    std::shared_ptr<std::string> totalWithdrawalFeeDerived_;
    std::shared_ptr<::trantor::Date> lastInterestCalculationDate_;
    std::shared_ptr<bool> isCreditBlocked_;
    std::shared_ptr<bool> isDebitBlocked_;
    std::shared_ptr<bool> isInterestBlocked_;
    std::shared_ptr<std::string> parentAccountId_;
    std::shared_ptr<bool> isGsimParent_;
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
    bool dirtyFlag_[57]={ false };
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
        if(dirtyFlag_[2])
        {
            sql += "account_no,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "external_id,";
            ++parametersCount;
        }
        sql += "deposit_type,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        if(dirtyFlag_[5])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "group_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "product_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "field_officer_id,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        sql += "sub_status,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "account_type,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        if(dirtyFlag_[12])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        sql += "digits_after_decimal,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        sql += "in_multiples_of,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        if(dirtyFlag_[15])
        {
            sql += "nominal_annual_interest_rate,";
            ++parametersCount;
        }
        sql += "interest_compounding_period_type,";
        ++parametersCount;
        if(!dirtyFlag_[16])
        {
            needSelection=true;
        }
        sql += "interest_posting_period_type,";
        ++parametersCount;
        if(!dirtyFlag_[17])
        {
            needSelection=true;
        }
        sql += "interest_calculation_type,";
        ++parametersCount;
        if(!dirtyFlag_[18])
        {
            needSelection=true;
        }
        sql += "interest_calculation_days_in_year_type,";
        ++parametersCount;
        if(!dirtyFlag_[19])
        {
            needSelection=true;
        }
        if(dirtyFlag_[20])
        {
            sql += "min_required_opening_balance,";
            ++parametersCount;
        }
        if(dirtyFlag_[21])
        {
            sql += "lockin_period_frequency,";
            ++parametersCount;
        }
        if(dirtyFlag_[22])
        {
            sql += "lockin_period_frequency_type,";
            ++parametersCount;
        }
        sql += "withdrawal_fee_for_transfer,";
        ++parametersCount;
        if(!dirtyFlag_[23])
        {
            needSelection=true;
        }
        sql += "allow_overdraft,";
        ++parametersCount;
        if(!dirtyFlag_[24])
        {
            needSelection=true;
        }
        if(dirtyFlag_[25])
        {
            sql += "overdraft_limit,";
            ++parametersCount;
        }
        if(dirtyFlag_[26])
        {
            sql += "min_balance_for_interest_calculation,";
            ++parametersCount;
        }
        if(dirtyFlag_[27])
        {
            sql += "min_required_balance,";
            ++parametersCount;
        }
        sql += "enforce_min_required_balance,";
        ++parametersCount;
        if(!dirtyFlag_[28])
        {
            needSelection=true;
        }
        if(dirtyFlag_[29])
        {
            sql += "submitted_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[30])
        {
            sql += "submitted_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[31])
        {
            sql += "approved_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[32])
        {
            sql += "approved_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[33])
        {
            sql += "activated_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[34])
        {
            sql += "activated_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[35])
        {
            sql += "rejected_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[36])
        {
            sql += "rejected_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[37])
        {
            sql += "withdrawn_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[38])
        {
            sql += "withdrawn_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[39])
        {
            sql += "closed_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[40])
        {
            sql += "closed_by,";
            ++parametersCount;
        }
        sql += "account_balance_derived,";
        ++parametersCount;
        if(!dirtyFlag_[41])
        {
            needSelection=true;
        }
        sql += "total_deposits_derived,";
        ++parametersCount;
        if(!dirtyFlag_[42])
        {
            needSelection=true;
        }
        sql += "total_withdrawals_derived,";
        ++parametersCount;
        if(!dirtyFlag_[43])
        {
            needSelection=true;
        }
        sql += "total_interest_posted_derived,";
        ++parametersCount;
        if(!dirtyFlag_[44])
        {
            needSelection=true;
        }
        sql += "total_fee_charge_derived,";
        ++parametersCount;
        if(!dirtyFlag_[45])
        {
            needSelection=true;
        }
        sql += "total_withdrawal_fee_derived,";
        ++parametersCount;
        if(!dirtyFlag_[46])
        {
            needSelection=true;
        }
        if(dirtyFlag_[47])
        {
            sql += "last_interest_calculation_date,";
            ++parametersCount;
        }
        sql += "is_credit_blocked,";
        ++parametersCount;
        if(!dirtyFlag_[48])
        {
            needSelection=true;
        }
        sql += "is_debit_blocked,";
        ++parametersCount;
        if(!dirtyFlag_[49])
        {
            needSelection=true;
        }
        sql += "is_interest_blocked,";
        ++parametersCount;
        if(!dirtyFlag_[50])
        {
            needSelection=true;
        }
        if(dirtyFlag_[51])
        {
            sql += "parent_account_id,";
            ++parametersCount;
        }
        sql += "is_gsim_parent,";
        ++parametersCount;
        if(!dirtyFlag_[52])
        {
            needSelection=true;
        }
        if(dirtyFlag_[53])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[54])
        {
            needSelection=true;
        }
        if(dirtyFlag_[55])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[56])
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
        else
        {
            sql +="default,";
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
        if(dirtyFlag_[8])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        if(dirtyFlag_[28])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        if(dirtyFlag_[46])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[47])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[48])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[49])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[50])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[51])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[52])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[53])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[54])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[55])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[56])
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
