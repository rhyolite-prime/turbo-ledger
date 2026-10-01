/**
 *  LoanProduct.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<LoanProduct> usage actually needs
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
namespace TlPortfolioDb
{

class LoanProduct
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _short_name;
        static const std::string _description;
        static const std::string _fund_id;
        static const std::string _currency_code;
        static const std::string _currency_digits;
        static const std::string _min_principal_amount;
        static const std::string _default_principal_amount;
        static const std::string _max_principal_amount;
        static const std::string _min_number_of_repayments;
        static const std::string _default_number_of_repayments;
        static const std::string _max_number_of_repayments;
        static const std::string _repayment_every;
        static const std::string _repayment_frequency_type;
        static const std::string _min_interest_rate_per_period;
        static const std::string _default_interest_rate_per_period;
        static const std::string _max_interest_rate_per_period;
        static const std::string _interest_period_frequency_type;
        static const std::string _annual_nominal_interest_rate;
        static const std::string _interest_method;
        static const std::string _interest_calculation_period_type;
        static const std::string _amortization_type;
        static const std::string _transaction_processing_strategy;
        static const std::string _grace_on_principal_payment;
        static const std::string _grace_on_interest_payment;
        static const std::string _grace_on_interest_charged;
        static const std::string _grace_on_arrears_ageing;
        static const std::string _overdue_days_for_npa;
        static const std::string _days_in_year_type;
        static const std::string _days_in_month_type;
        static const std::string _min_days_between_disbursal_and_first_repayment;
        static const std::string _allow_partial_period_interest;
        static const std::string _is_linked_to_floating_rate;
        static const std::string _floating_rate_id;
        static const std::string _default_differential_lending_rate;
        static const std::string _is_equal_amortization;
        static const std::string _allow_attribute_overrides;
        static const std::string _can_use_for_topup;
        static const std::string _close_date;
        static const std::string _start_date;
        static const std::string _delinquency_bucket_id;
        static const std::string _accounting_type;
        static const std::string _fund_source_account_id;
        static const std::string _loan_portfolio_account_id;
        static const std::string _interest_on_loan_account_id;
        static const std::string _income_from_fees_account_id;
        static const std::string _income_from_penalties_account_id;
        static const std::string _income_from_recovery_account_id;
        static const std::string _losses_written_off_account_id;
        static const std::string _overpayment_liability_account_id;
        static const std::string _interest_receivable_account_id;
        static const std::string _fee_receivable_account_id;
        static const std::string _penalty_receivable_account_id;
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

    explicit LoanProduct(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    LoanProduct() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

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

    /**  For column fund_id  */
    const std::string &getValueOfFundId() const noexcept;
    const std::shared_ptr<std::string> &getFundId() const noexcept;
    void setFundId(const std::string &pFundId) noexcept;
    void setFundId(std::string &&pFundId) noexcept;
    void setFundIdToNull() noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column currency_digits  */
    const int32_t &getValueOfCurrencyDigits() const noexcept;
    const std::shared_ptr<int32_t> &getCurrencyDigits() const noexcept;
    void setCurrencyDigits(const int32_t &pCurrencyDigits) noexcept;

    /**  For column min_principal_amount  */
    const std::string &getValueOfMinPrincipalAmount() const noexcept;
    const std::shared_ptr<std::string> &getMinPrincipalAmount() const noexcept;
    void setMinPrincipalAmount(const std::string &pMinPrincipalAmount) noexcept;
    void setMinPrincipalAmount(std::string &&pMinPrincipalAmount) noexcept;
    void setMinPrincipalAmountToNull() noexcept;

    /**  For column default_principal_amount  */
    const std::string &getValueOfDefaultPrincipalAmount() const noexcept;
    const std::shared_ptr<std::string> &getDefaultPrincipalAmount() const noexcept;
    void setDefaultPrincipalAmount(const std::string &pDefaultPrincipalAmount) noexcept;
    void setDefaultPrincipalAmount(std::string &&pDefaultPrincipalAmount) noexcept;

    /**  For column max_principal_amount  */
    const std::string &getValueOfMaxPrincipalAmount() const noexcept;
    const std::shared_ptr<std::string> &getMaxPrincipalAmount() const noexcept;
    void setMaxPrincipalAmount(const std::string &pMaxPrincipalAmount) noexcept;
    void setMaxPrincipalAmount(std::string &&pMaxPrincipalAmount) noexcept;
    void setMaxPrincipalAmountToNull() noexcept;

    /**  For column min_number_of_repayments  */
    const int32_t &getValueOfMinNumberOfRepayments() const noexcept;
    const std::shared_ptr<int32_t> &getMinNumberOfRepayments() const noexcept;
    void setMinNumberOfRepayments(const int32_t &pMinNumberOfRepayments) noexcept;
    void setMinNumberOfRepaymentsToNull() noexcept;

    /**  For column default_number_of_repayments  */
    const int32_t &getValueOfDefaultNumberOfRepayments() const noexcept;
    const std::shared_ptr<int32_t> &getDefaultNumberOfRepayments() const noexcept;
    void setDefaultNumberOfRepayments(const int32_t &pDefaultNumberOfRepayments) noexcept;

    /**  For column max_number_of_repayments  */
    const int32_t &getValueOfMaxNumberOfRepayments() const noexcept;
    const std::shared_ptr<int32_t> &getMaxNumberOfRepayments() const noexcept;
    void setMaxNumberOfRepayments(const int32_t &pMaxNumberOfRepayments) noexcept;
    void setMaxNumberOfRepaymentsToNull() noexcept;

    /**  For column repayment_every  */
    const int32_t &getValueOfRepaymentEvery() const noexcept;
    const std::shared_ptr<int32_t> &getRepaymentEvery() const noexcept;
    void setRepaymentEvery(const int32_t &pRepaymentEvery) noexcept;

    /**  For column repayment_frequency_type  */
    const int32_t &getValueOfRepaymentFrequencyType() const noexcept;
    const std::shared_ptr<int32_t> &getRepaymentFrequencyType() const noexcept;
    void setRepaymentFrequencyType(const int32_t &pRepaymentFrequencyType) noexcept;

    /**  For column min_interest_rate_per_period  */
    const std::string &getValueOfMinInterestRatePerPeriod() const noexcept;
    const std::shared_ptr<std::string> &getMinInterestRatePerPeriod() const noexcept;
    void setMinInterestRatePerPeriod(const std::string &pMinInterestRatePerPeriod) noexcept;
    void setMinInterestRatePerPeriod(std::string &&pMinInterestRatePerPeriod) noexcept;
    void setMinInterestRatePerPeriodToNull() noexcept;

    /**  For column default_interest_rate_per_period  */
    const std::string &getValueOfDefaultInterestRatePerPeriod() const noexcept;
    const std::shared_ptr<std::string> &getDefaultInterestRatePerPeriod() const noexcept;
    void setDefaultInterestRatePerPeriod(const std::string &pDefaultInterestRatePerPeriod) noexcept;
    void setDefaultInterestRatePerPeriod(std::string &&pDefaultInterestRatePerPeriod) noexcept;

    /**  For column max_interest_rate_per_period  */
    const std::string &getValueOfMaxInterestRatePerPeriod() const noexcept;
    const std::shared_ptr<std::string> &getMaxInterestRatePerPeriod() const noexcept;
    void setMaxInterestRatePerPeriod(const std::string &pMaxInterestRatePerPeriod) noexcept;
    void setMaxInterestRatePerPeriod(std::string &&pMaxInterestRatePerPeriod) noexcept;
    void setMaxInterestRatePerPeriodToNull() noexcept;

    /**  For column interest_period_frequency_type  */
    const int32_t &getValueOfInterestPeriodFrequencyType() const noexcept;
    const std::shared_ptr<int32_t> &getInterestPeriodFrequencyType() const noexcept;
    void setInterestPeriodFrequencyType(const int32_t &pInterestPeriodFrequencyType) noexcept;

    /**  For column annual_nominal_interest_rate  */
    const std::string &getValueOfAnnualNominalInterestRate() const noexcept;
    const std::shared_ptr<std::string> &getAnnualNominalInterestRate() const noexcept;
    void setAnnualNominalInterestRate(const std::string &pAnnualNominalInterestRate) noexcept;
    void setAnnualNominalInterestRate(std::string &&pAnnualNominalInterestRate) noexcept;

    /**  For column interest_method  */
    const int32_t &getValueOfInterestMethod() const noexcept;
    const std::shared_ptr<int32_t> &getInterestMethod() const noexcept;
    void setInterestMethod(const int32_t &pInterestMethod) noexcept;

    /**  For column interest_calculation_period_type  */
    const int32_t &getValueOfInterestCalculationPeriodType() const noexcept;
    const std::shared_ptr<int32_t> &getInterestCalculationPeriodType() const noexcept;
    void setInterestCalculationPeriodType(const int32_t &pInterestCalculationPeriodType) noexcept;

    /**  For column amortization_type  */
    const int32_t &getValueOfAmortizationType() const noexcept;
    const std::shared_ptr<int32_t> &getAmortizationType() const noexcept;
    void setAmortizationType(const int32_t &pAmortizationType) noexcept;

    /**  For column transaction_processing_strategy  */
    const std::string &getValueOfTransactionProcessingStrategy() const noexcept;
    const std::shared_ptr<std::string> &getTransactionProcessingStrategy() const noexcept;
    void setTransactionProcessingStrategy(const std::string &pTransactionProcessingStrategy) noexcept;
    void setTransactionProcessingStrategy(std::string &&pTransactionProcessingStrategy) noexcept;

    /**  For column grace_on_principal_payment  */
    const int32_t &getValueOfGraceOnPrincipalPayment() const noexcept;
    const std::shared_ptr<int32_t> &getGraceOnPrincipalPayment() const noexcept;
    void setGraceOnPrincipalPayment(const int32_t &pGraceOnPrincipalPayment) noexcept;

    /**  For column grace_on_interest_payment  */
    const int32_t &getValueOfGraceOnInterestPayment() const noexcept;
    const std::shared_ptr<int32_t> &getGraceOnInterestPayment() const noexcept;
    void setGraceOnInterestPayment(const int32_t &pGraceOnInterestPayment) noexcept;

    /**  For column grace_on_interest_charged  */
    const int32_t &getValueOfGraceOnInterestCharged() const noexcept;
    const std::shared_ptr<int32_t> &getGraceOnInterestCharged() const noexcept;
    void setGraceOnInterestCharged(const int32_t &pGraceOnInterestCharged) noexcept;

    /**  For column grace_on_arrears_ageing  */
    const int32_t &getValueOfGraceOnArrearsAgeing() const noexcept;
    const std::shared_ptr<int32_t> &getGraceOnArrearsAgeing() const noexcept;
    void setGraceOnArrearsAgeing(const int32_t &pGraceOnArrearsAgeing) noexcept;

    /**  For column overdue_days_for_npa  */
    const int32_t &getValueOfOverdueDaysForNpa() const noexcept;
    const std::shared_ptr<int32_t> &getOverdueDaysForNpa() const noexcept;
    void setOverdueDaysForNpa(const int32_t &pOverdueDaysForNpa) noexcept;

    /**  For column days_in_year_type  */
    const int32_t &getValueOfDaysInYearType() const noexcept;
    const std::shared_ptr<int32_t> &getDaysInYearType() const noexcept;
    void setDaysInYearType(const int32_t &pDaysInYearType) noexcept;

    /**  For column days_in_month_type  */
    const int32_t &getValueOfDaysInMonthType() const noexcept;
    const std::shared_ptr<int32_t> &getDaysInMonthType() const noexcept;
    void setDaysInMonthType(const int32_t &pDaysInMonthType) noexcept;

    /**  For column min_days_between_disbursal_and_first_repayment  */
    const int32_t &getValueOfMinDaysBetweenDisbursalAndFirstRepayment() const noexcept;
    const std::shared_ptr<int32_t> &getMinDaysBetweenDisbursalAndFirstRepayment() const noexcept;
    void setMinDaysBetweenDisbursalAndFirstRepayment(const int32_t &pMinDaysBetweenDisbursalAndFirstRepayment) noexcept;

    /**  For column allow_partial_period_interest  */
    const bool &getValueOfAllowPartialPeriodInterest() const noexcept;
    const std::shared_ptr<bool> &getAllowPartialPeriodInterest() const noexcept;
    void setAllowPartialPeriodInterest(const bool &pAllowPartialPeriodInterest) noexcept;

    /**  For column is_linked_to_floating_rate  */
    const bool &getValueOfIsLinkedToFloatingRate() const noexcept;
    const std::shared_ptr<bool> &getIsLinkedToFloatingRate() const noexcept;
    void setIsLinkedToFloatingRate(const bool &pIsLinkedToFloatingRate) noexcept;

    /**  For column floating_rate_id  */
    const std::string &getValueOfFloatingRateId() const noexcept;
    const std::shared_ptr<std::string> &getFloatingRateId() const noexcept;
    void setFloatingRateId(const std::string &pFloatingRateId) noexcept;
    void setFloatingRateId(std::string &&pFloatingRateId) noexcept;
    void setFloatingRateIdToNull() noexcept;

    /**  For column default_differential_lending_rate  */
    const std::string &getValueOfDefaultDifferentialLendingRate() const noexcept;
    const std::shared_ptr<std::string> &getDefaultDifferentialLendingRate() const noexcept;
    void setDefaultDifferentialLendingRate(const std::string &pDefaultDifferentialLendingRate) noexcept;
    void setDefaultDifferentialLendingRate(std::string &&pDefaultDifferentialLendingRate) noexcept;
    void setDefaultDifferentialLendingRateToNull() noexcept;

    /**  For column is_equal_amortization  */
    const bool &getValueOfIsEqualAmortization() const noexcept;
    const std::shared_ptr<bool> &getIsEqualAmortization() const noexcept;
    void setIsEqualAmortization(const bool &pIsEqualAmortization) noexcept;

    /**  For column allow_attribute_overrides  */
    const bool &getValueOfAllowAttributeOverrides() const noexcept;
    const std::shared_ptr<bool> &getAllowAttributeOverrides() const noexcept;
    void setAllowAttributeOverrides(const bool &pAllowAttributeOverrides) noexcept;

    /**  For column can_use_for_topup  */
    const bool &getValueOfCanUseForTopup() const noexcept;
    const std::shared_ptr<bool> &getCanUseForTopup() const noexcept;
    void setCanUseForTopup(const bool &pCanUseForTopup) noexcept;

    /**  For column close_date  */
    const ::trantor::Date &getValueOfCloseDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCloseDate() const noexcept;
    void setCloseDate(const ::trantor::Date &pCloseDate) noexcept;
    void setCloseDateToNull() noexcept;

    /**  For column start_date  */
    const ::trantor::Date &getValueOfStartDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getStartDate() const noexcept;
    void setStartDate(const ::trantor::Date &pStartDate) noexcept;
    void setStartDateToNull() noexcept;

    /**  For column delinquency_bucket_id  */
    const std::string &getValueOfDelinquencyBucketId() const noexcept;
    const std::shared_ptr<std::string> &getDelinquencyBucketId() const noexcept;
    void setDelinquencyBucketId(const std::string &pDelinquencyBucketId) noexcept;
    void setDelinquencyBucketId(std::string &&pDelinquencyBucketId) noexcept;
    void setDelinquencyBucketIdToNull() noexcept;

    /**  For column accounting_type  */
    const int32_t &getValueOfAccountingType() const noexcept;
    const std::shared_ptr<int32_t> &getAccountingType() const noexcept;
    void setAccountingType(const int32_t &pAccountingType) noexcept;

    /**  For column fund_source_account_id  */
    const std::string &getValueOfFundSourceAccountId() const noexcept;
    const std::shared_ptr<std::string> &getFundSourceAccountId() const noexcept;
    void setFundSourceAccountId(const std::string &pFundSourceAccountId) noexcept;
    void setFundSourceAccountId(std::string &&pFundSourceAccountId) noexcept;
    void setFundSourceAccountIdToNull() noexcept;

    /**  For column loan_portfolio_account_id  */
    const std::string &getValueOfLoanPortfolioAccountId() const noexcept;
    const std::shared_ptr<std::string> &getLoanPortfolioAccountId() const noexcept;
    void setLoanPortfolioAccountId(const std::string &pLoanPortfolioAccountId) noexcept;
    void setLoanPortfolioAccountId(std::string &&pLoanPortfolioAccountId) noexcept;
    void setLoanPortfolioAccountIdToNull() noexcept;

    /**  For column interest_on_loan_account_id  */
    const std::string &getValueOfInterestOnLoanAccountId() const noexcept;
    const std::shared_ptr<std::string> &getInterestOnLoanAccountId() const noexcept;
    void setInterestOnLoanAccountId(const std::string &pInterestOnLoanAccountId) noexcept;
    void setInterestOnLoanAccountId(std::string &&pInterestOnLoanAccountId) noexcept;
    void setInterestOnLoanAccountIdToNull() noexcept;

    /**  For column income_from_fees_account_id  */
    const std::string &getValueOfIncomeFromFeesAccountId() const noexcept;
    const std::shared_ptr<std::string> &getIncomeFromFeesAccountId() const noexcept;
    void setIncomeFromFeesAccountId(const std::string &pIncomeFromFeesAccountId) noexcept;
    void setIncomeFromFeesAccountId(std::string &&pIncomeFromFeesAccountId) noexcept;
    void setIncomeFromFeesAccountIdToNull() noexcept;

    /**  For column income_from_penalties_account_id  */
    const std::string &getValueOfIncomeFromPenaltiesAccountId() const noexcept;
    const std::shared_ptr<std::string> &getIncomeFromPenaltiesAccountId() const noexcept;
    void setIncomeFromPenaltiesAccountId(const std::string &pIncomeFromPenaltiesAccountId) noexcept;
    void setIncomeFromPenaltiesAccountId(std::string &&pIncomeFromPenaltiesAccountId) noexcept;
    void setIncomeFromPenaltiesAccountIdToNull() noexcept;

    /**  For column income_from_recovery_account_id  */
    const std::string &getValueOfIncomeFromRecoveryAccountId() const noexcept;
    const std::shared_ptr<std::string> &getIncomeFromRecoveryAccountId() const noexcept;
    void setIncomeFromRecoveryAccountId(const std::string &pIncomeFromRecoveryAccountId) noexcept;
    void setIncomeFromRecoveryAccountId(std::string &&pIncomeFromRecoveryAccountId) noexcept;
    void setIncomeFromRecoveryAccountIdToNull() noexcept;

    /**  For column losses_written_off_account_id  */
    const std::string &getValueOfLossesWrittenOffAccountId() const noexcept;
    const std::shared_ptr<std::string> &getLossesWrittenOffAccountId() const noexcept;
    void setLossesWrittenOffAccountId(const std::string &pLossesWrittenOffAccountId) noexcept;
    void setLossesWrittenOffAccountId(std::string &&pLossesWrittenOffAccountId) noexcept;
    void setLossesWrittenOffAccountIdToNull() noexcept;

    /**  For column overpayment_liability_account_id  */
    const std::string &getValueOfOverpaymentLiabilityAccountId() const noexcept;
    const std::shared_ptr<std::string> &getOverpaymentLiabilityAccountId() const noexcept;
    void setOverpaymentLiabilityAccountId(const std::string &pOverpaymentLiabilityAccountId) noexcept;
    void setOverpaymentLiabilityAccountId(std::string &&pOverpaymentLiabilityAccountId) noexcept;
    void setOverpaymentLiabilityAccountIdToNull() noexcept;

    /**  For column interest_receivable_account_id  */
    const std::string &getValueOfInterestReceivableAccountId() const noexcept;
    const std::shared_ptr<std::string> &getInterestReceivableAccountId() const noexcept;
    void setInterestReceivableAccountId(const std::string &pInterestReceivableAccountId) noexcept;
    void setInterestReceivableAccountId(std::string &&pInterestReceivableAccountId) noexcept;
    void setInterestReceivableAccountIdToNull() noexcept;

    /**  For column fee_receivable_account_id  */
    const std::string &getValueOfFeeReceivableAccountId() const noexcept;
    const std::shared_ptr<std::string> &getFeeReceivableAccountId() const noexcept;
    void setFeeReceivableAccountId(const std::string &pFeeReceivableAccountId) noexcept;
    void setFeeReceivableAccountId(std::string &&pFeeReceivableAccountId) noexcept;
    void setFeeReceivableAccountIdToNull() noexcept;

    /**  For column penalty_receivable_account_id  */
    const std::string &getValueOfPenaltyReceivableAccountId() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyReceivableAccountId() const noexcept;
    void setPenaltyReceivableAccountId(const std::string &pPenaltyReceivableAccountId) noexcept;
    void setPenaltyReceivableAccountId(std::string &&pPenaltyReceivableAccountId) noexcept;
    void setPenaltyReceivableAccountIdToNull() noexcept;

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

    static size_t getColumnNumber() noexcept {  return 59;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<LoanProduct>;
    friend drogon::orm::BaseBuilder<LoanProduct, true, true>;
    friend drogon::orm::BaseBuilder<LoanProduct, true, false>;
    friend drogon::orm::BaseBuilder<LoanProduct, false, true>;
    friend drogon::orm::BaseBuilder<LoanProduct, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<LoanProduct>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> shortName_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<std::string> fundId_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<int32_t> currencyDigits_;
    std::shared_ptr<std::string> minPrincipalAmount_;
    std::shared_ptr<std::string> defaultPrincipalAmount_;
    std::shared_ptr<std::string> maxPrincipalAmount_;
    std::shared_ptr<int32_t> minNumberOfRepayments_;
    std::shared_ptr<int32_t> defaultNumberOfRepayments_;
    std::shared_ptr<int32_t> maxNumberOfRepayments_;
    std::shared_ptr<int32_t> repaymentEvery_;
    std::shared_ptr<int32_t> repaymentFrequencyType_;
    std::shared_ptr<std::string> minInterestRatePerPeriod_;
    std::shared_ptr<std::string> defaultInterestRatePerPeriod_;
    std::shared_ptr<std::string> maxInterestRatePerPeriod_;
    std::shared_ptr<int32_t> interestPeriodFrequencyType_;
    std::shared_ptr<std::string> annualNominalInterestRate_;
    std::shared_ptr<int32_t> interestMethod_;
    std::shared_ptr<int32_t> interestCalculationPeriodType_;
    std::shared_ptr<int32_t> amortizationType_;
    std::shared_ptr<std::string> transactionProcessingStrategy_;
    std::shared_ptr<int32_t> graceOnPrincipalPayment_;
    std::shared_ptr<int32_t> graceOnInterestPayment_;
    std::shared_ptr<int32_t> graceOnInterestCharged_;
    std::shared_ptr<int32_t> graceOnArrearsAgeing_;
    std::shared_ptr<int32_t> overdueDaysForNpa_;
    std::shared_ptr<int32_t> daysInYearType_;
    std::shared_ptr<int32_t> daysInMonthType_;
    std::shared_ptr<int32_t> minDaysBetweenDisbursalAndFirstRepayment_;
    std::shared_ptr<bool> allowPartialPeriodInterest_;
    std::shared_ptr<bool> isLinkedToFloatingRate_;
    std::shared_ptr<std::string> floatingRateId_;
    std::shared_ptr<std::string> defaultDifferentialLendingRate_;
    std::shared_ptr<bool> isEqualAmortization_;
    std::shared_ptr<bool> allowAttributeOverrides_;
    std::shared_ptr<bool> canUseForTopup_;
    std::shared_ptr<::trantor::Date> closeDate_;
    std::shared_ptr<::trantor::Date> startDate_;
    std::shared_ptr<std::string> delinquencyBucketId_;
    std::shared_ptr<int32_t> accountingType_;
    std::shared_ptr<std::string> fundSourceAccountId_;
    std::shared_ptr<std::string> loanPortfolioAccountId_;
    std::shared_ptr<std::string> interestOnLoanAccountId_;
    std::shared_ptr<std::string> incomeFromFeesAccountId_;
    std::shared_ptr<std::string> incomeFromPenaltiesAccountId_;
    std::shared_ptr<std::string> incomeFromRecoveryAccountId_;
    std::shared_ptr<std::string> lossesWrittenOffAccountId_;
    std::shared_ptr<std::string> overpaymentLiabilityAccountId_;
    std::shared_ptr<std::string> interestReceivableAccountId_;
    std::shared_ptr<std::string> feeReceivableAccountId_;
    std::shared_ptr<std::string> penaltyReceivableAccountId_;
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
    bool dirtyFlag_[59]={ false };
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
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "short_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "fund_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        sql += "currency_digits,";
        ++parametersCount;
        if(!dirtyFlag_[6])
        {
            needSelection=true;
        }
        if(dirtyFlag_[7])
        {
            sql += "min_principal_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "default_principal_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "max_principal_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "min_number_of_repayments,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "default_number_of_repayments,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "max_number_of_repayments,";
            ++parametersCount;
        }
        sql += "repayment_every,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        sql += "repayment_frequency_type,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        if(dirtyFlag_[15])
        {
            sql += "min_interest_rate_per_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "default_interest_rate_per_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[17])
        {
            sql += "max_interest_rate_per_period,";
            ++parametersCount;
        }
        sql += "interest_period_frequency_type,";
        ++parametersCount;
        if(!dirtyFlag_[18])
        {
            needSelection=true;
        }
        if(dirtyFlag_[19])
        {
            sql += "annual_nominal_interest_rate,";
            ++parametersCount;
        }
        sql += "interest_method,";
        ++parametersCount;
        if(!dirtyFlag_[20])
        {
            needSelection=true;
        }
        sql += "interest_calculation_period_type,";
        ++parametersCount;
        if(!dirtyFlag_[21])
        {
            needSelection=true;
        }
        sql += "amortization_type,";
        ++parametersCount;
        if(!dirtyFlag_[22])
        {
            needSelection=true;
        }
        sql += "transaction_processing_strategy,";
        ++parametersCount;
        if(!dirtyFlag_[23])
        {
            needSelection=true;
        }
        sql += "grace_on_principal_payment,";
        ++parametersCount;
        if(!dirtyFlag_[24])
        {
            needSelection=true;
        }
        sql += "grace_on_interest_payment,";
        ++parametersCount;
        if(!dirtyFlag_[25])
        {
            needSelection=true;
        }
        sql += "grace_on_interest_charged,";
        ++parametersCount;
        if(!dirtyFlag_[26])
        {
            needSelection=true;
        }
        sql += "grace_on_arrears_ageing,";
        ++parametersCount;
        if(!dirtyFlag_[27])
        {
            needSelection=true;
        }
        sql += "overdue_days_for_npa,";
        ++parametersCount;
        if(!dirtyFlag_[28])
        {
            needSelection=true;
        }
        sql += "days_in_year_type,";
        ++parametersCount;
        if(!dirtyFlag_[29])
        {
            needSelection=true;
        }
        sql += "days_in_month_type,";
        ++parametersCount;
        if(!dirtyFlag_[30])
        {
            needSelection=true;
        }
        sql += "min_days_between_disbursal_and_first_repayment,";
        ++parametersCount;
        if(!dirtyFlag_[31])
        {
            needSelection=true;
        }
        sql += "allow_partial_period_interest,";
        ++parametersCount;
        if(!dirtyFlag_[32])
        {
            needSelection=true;
        }
        sql += "is_linked_to_floating_rate,";
        ++parametersCount;
        if(!dirtyFlag_[33])
        {
            needSelection=true;
        }
        if(dirtyFlag_[34])
        {
            sql += "floating_rate_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[35])
        {
            sql += "default_differential_lending_rate,";
            ++parametersCount;
        }
        sql += "is_equal_amortization,";
        ++parametersCount;
        if(!dirtyFlag_[36])
        {
            needSelection=true;
        }
        sql += "allow_attribute_overrides,";
        ++parametersCount;
        if(!dirtyFlag_[37])
        {
            needSelection=true;
        }
        sql += "can_use_for_topup,";
        ++parametersCount;
        if(!dirtyFlag_[38])
        {
            needSelection=true;
        }
        if(dirtyFlag_[39])
        {
            sql += "close_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[40])
        {
            sql += "start_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[41])
        {
            sql += "delinquency_bucket_id,";
            ++parametersCount;
        }
        sql += "accounting_type,";
        ++parametersCount;
        if(!dirtyFlag_[42])
        {
            needSelection=true;
        }
        if(dirtyFlag_[43])
        {
            sql += "fund_source_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[44])
        {
            sql += "loan_portfolio_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[45])
        {
            sql += "interest_on_loan_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[46])
        {
            sql += "income_from_fees_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[47])
        {
            sql += "income_from_penalties_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[48])
        {
            sql += "income_from_recovery_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[49])
        {
            sql += "losses_written_off_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[50])
        {
            sql += "overpayment_liability_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[51])
        {
            sql += "interest_receivable_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[52])
        {
            sql += "fee_receivable_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[53])
        {
            sql += "penalty_receivable_account_id,";
            ++parametersCount;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[54])
        {
            needSelection=true;
        }
        if(dirtyFlag_[55])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[56])
        {
            needSelection=true;
        }
        if(dirtyFlag_[57])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[58])
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
        else
        {
            sql +="default,";
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
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[11])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        if(dirtyFlag_[17])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[21])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[25])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[26])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[29])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[30])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[31])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[32])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[33])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[37])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[38])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        if(dirtyFlag_[46])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        if(dirtyFlag_[49])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[50])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        if(dirtyFlag_[57])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[58])
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
} // namespace TlPortfolioDb
} // namespace drogon_model
