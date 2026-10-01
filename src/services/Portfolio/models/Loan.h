/**
 *  Loan.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<Loan> usage actually needs
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

class Loan
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _account_no;
        static const std::string _external_id;
        static const std::string _client_id;
        static const std::string _group_id;
        static const std::string _product_id;
        static const std::string _loan_officer_id;
        static const std::string _fund_id;
        static const std::string _loan_purpose;
        static const std::string _loan_type;
        static const std::string _currency_code;
        static const std::string _currency_digits;
        static const std::string _principal_amount;
        static const std::string _approved_principal;
        static const std::string _net_disbursal_amount;
        static const std::string _number_of_repayments;
        static const std::string _repayment_every;
        static const std::string _repayment_frequency_type;
        static const std::string _interest_rate_per_period;
        static const std::string _interest_period_frequency_type;
        static const std::string _annual_nominal_interest_rate;
        static const std::string _interest_method;
        static const std::string _interest_calculation_period_type;
        static const std::string _amortization_type;
        static const std::string _transaction_processing_strategy;
        static const std::string _days_in_year_type;
        static const std::string _days_in_month_type;
        static const std::string _grace_on_principal_payment;
        static const std::string _grace_on_interest_payment;
        static const std::string _grace_on_interest_charged;
        static const std::string _grace_on_arrears_ageing;
        static const std::string _is_equal_amortization;
        static const std::string _is_floating_interest_rate;
        static const std::string _floating_rate_id;
        static const std::string _interest_rate_differential;
        static const std::string _submitted_on_date;
        static const std::string _submitted_by;
        static const std::string _approved_on_date;
        static const std::string _approved_by;
        static const std::string _expected_disbursement_date;
        static const std::string _actual_disbursement_date;
        static const std::string _disbursed_by;
        static const std::string _expected_first_repayment_on_date;
        static const std::string _interest_charged_from_date;
        static const std::string _expected_maturity_date;
        static const std::string _maturity_date;
        static const std::string _closed_on_date;
        static const std::string _closed_by;
        static const std::string _rejected_on_date;
        static const std::string _withdrawn_on_date;
        static const std::string _writtenoff_on_date;
        static const std::string _status;
        static const std::string _sub_status;
        static const std::string _is_npa;
        static const std::string _delinquency_range_id;
        static const std::string _overdue_since_date;
        static const std::string _principal_disbursed;
        static const std::string _principal_paid;
        static const std::string _principal_writtenoff;
        static const std::string _interest_charged;
        static const std::string _interest_paid;
        static const std::string _interest_waived;
        static const std::string _interest_writtenoff;
        static const std::string _fee_charges_charged;
        static const std::string _fee_charges_paid;
        static const std::string _fee_charges_waived;
        static const std::string _fee_charges_writtenoff;
        static const std::string _penalty_charges_charged;
        static const std::string _penalty_charges_paid;
        static const std::string _penalty_charges_waived;
        static const std::string _penalty_charges_writtenoff;
        static const std::string _total_recovered;
        static const std::string _total_overpaid;
        static const std::string _buydown_fee_amount;
        static const std::string _capitalized_income_amount;
        static const std::string _glim_parent_loan_id;
        static const std::string _created_at;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit Loan(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    Loan() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column account_no  */
    const std::string &getValueOfAccountNo() const noexcept;
    const std::shared_ptr<std::string> &getAccountNo() const noexcept;
    void setAccountNo(const std::string &pAccountNo) noexcept;
    void setAccountNo(std::string &&pAccountNo) noexcept;

    /**  For column external_id  */
    const std::string &getValueOfExternalId() const noexcept;
    const std::shared_ptr<std::string> &getExternalId() const noexcept;
    void setExternalId(const std::string &pExternalId) noexcept;
    void setExternalId(std::string &&pExternalId) noexcept;
    void setExternalIdToNull() noexcept;

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

    /**  For column loan_officer_id  */
    const std::string &getValueOfLoanOfficerId() const noexcept;
    const std::shared_ptr<std::string> &getLoanOfficerId() const noexcept;
    void setLoanOfficerId(const std::string &pLoanOfficerId) noexcept;
    void setLoanOfficerId(std::string &&pLoanOfficerId) noexcept;
    void setLoanOfficerIdToNull() noexcept;

    /**  For column fund_id  */
    const std::string &getValueOfFundId() const noexcept;
    const std::shared_ptr<std::string> &getFundId() const noexcept;
    void setFundId(const std::string &pFundId) noexcept;
    void setFundId(std::string &&pFundId) noexcept;
    void setFundIdToNull() noexcept;

    /**  For column loan_purpose  */
    const std::string &getValueOfLoanPurpose() const noexcept;
    const std::shared_ptr<std::string> &getLoanPurpose() const noexcept;
    void setLoanPurpose(const std::string &pLoanPurpose) noexcept;
    void setLoanPurpose(std::string &&pLoanPurpose) noexcept;
    void setLoanPurposeToNull() noexcept;

    /**  For column loan_type  */
    const int32_t &getValueOfLoanType() const noexcept;
    const std::shared_ptr<int32_t> &getLoanType() const noexcept;
    void setLoanType(const int32_t &pLoanType) noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column currency_digits  */
    const int32_t &getValueOfCurrencyDigits() const noexcept;
    const std::shared_ptr<int32_t> &getCurrencyDigits() const noexcept;
    void setCurrencyDigits(const int32_t &pCurrencyDigits) noexcept;

    /**  For column principal_amount  */
    const std::string &getValueOfPrincipalAmount() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalAmount() const noexcept;
    void setPrincipalAmount(const std::string &pPrincipalAmount) noexcept;
    void setPrincipalAmount(std::string &&pPrincipalAmount) noexcept;

    /**  For column approved_principal  */
    const std::string &getValueOfApprovedPrincipal() const noexcept;
    const std::shared_ptr<std::string> &getApprovedPrincipal() const noexcept;
    void setApprovedPrincipal(const std::string &pApprovedPrincipal) noexcept;
    void setApprovedPrincipal(std::string &&pApprovedPrincipal) noexcept;
    void setApprovedPrincipalToNull() noexcept;

    /**  For column net_disbursal_amount  */
    const std::string &getValueOfNetDisbursalAmount() const noexcept;
    const std::shared_ptr<std::string> &getNetDisbursalAmount() const noexcept;
    void setNetDisbursalAmount(const std::string &pNetDisbursalAmount) noexcept;
    void setNetDisbursalAmount(std::string &&pNetDisbursalAmount) noexcept;
    void setNetDisbursalAmountToNull() noexcept;

    /**  For column number_of_repayments  */
    const int32_t &getValueOfNumberOfRepayments() const noexcept;
    const std::shared_ptr<int32_t> &getNumberOfRepayments() const noexcept;
    void setNumberOfRepayments(const int32_t &pNumberOfRepayments) noexcept;

    /**  For column repayment_every  */
    const int32_t &getValueOfRepaymentEvery() const noexcept;
    const std::shared_ptr<int32_t> &getRepaymentEvery() const noexcept;
    void setRepaymentEvery(const int32_t &pRepaymentEvery) noexcept;

    /**  For column repayment_frequency_type  */
    const int32_t &getValueOfRepaymentFrequencyType() const noexcept;
    const std::shared_ptr<int32_t> &getRepaymentFrequencyType() const noexcept;
    void setRepaymentFrequencyType(const int32_t &pRepaymentFrequencyType) noexcept;

    /**  For column interest_rate_per_period  */
    const std::string &getValueOfInterestRatePerPeriod() const noexcept;
    const std::shared_ptr<std::string> &getInterestRatePerPeriod() const noexcept;
    void setInterestRatePerPeriod(const std::string &pInterestRatePerPeriod) noexcept;
    void setInterestRatePerPeriod(std::string &&pInterestRatePerPeriod) noexcept;

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

    /**  For column days_in_year_type  */
    const int32_t &getValueOfDaysInYearType() const noexcept;
    const std::shared_ptr<int32_t> &getDaysInYearType() const noexcept;
    void setDaysInYearType(const int32_t &pDaysInYearType) noexcept;

    /**  For column days_in_month_type  */
    const int32_t &getValueOfDaysInMonthType() const noexcept;
    const std::shared_ptr<int32_t> &getDaysInMonthType() const noexcept;
    void setDaysInMonthType(const int32_t &pDaysInMonthType) noexcept;

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

    /**  For column is_equal_amortization  */
    const bool &getValueOfIsEqualAmortization() const noexcept;
    const std::shared_ptr<bool> &getIsEqualAmortization() const noexcept;
    void setIsEqualAmortization(const bool &pIsEqualAmortization) noexcept;

    /**  For column is_floating_interest_rate  */
    const bool &getValueOfIsFloatingInterestRate() const noexcept;
    const std::shared_ptr<bool> &getIsFloatingInterestRate() const noexcept;
    void setIsFloatingInterestRate(const bool &pIsFloatingInterestRate) noexcept;

    /**  For column floating_rate_id  */
    const std::string &getValueOfFloatingRateId() const noexcept;
    const std::shared_ptr<std::string> &getFloatingRateId() const noexcept;
    void setFloatingRateId(const std::string &pFloatingRateId) noexcept;
    void setFloatingRateId(std::string &&pFloatingRateId) noexcept;
    void setFloatingRateIdToNull() noexcept;

    /**  For column interest_rate_differential  */
    const std::string &getValueOfInterestRateDifferential() const noexcept;
    const std::shared_ptr<std::string> &getInterestRateDifferential() const noexcept;
    void setInterestRateDifferential(const std::string &pInterestRateDifferential) noexcept;
    void setInterestRateDifferential(std::string &&pInterestRateDifferential) noexcept;
    void setInterestRateDifferentialToNull() noexcept;

    /**  For column submitted_on_date  */
    const ::trantor::Date &getValueOfSubmittedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedOnDate() const noexcept;
    void setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept;

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

    /**  For column expected_disbursement_date  */
    const ::trantor::Date &getValueOfExpectedDisbursementDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getExpectedDisbursementDate() const noexcept;
    void setExpectedDisbursementDate(const ::trantor::Date &pExpectedDisbursementDate) noexcept;
    void setExpectedDisbursementDateToNull() noexcept;

    /**  For column actual_disbursement_date  */
    const ::trantor::Date &getValueOfActualDisbursementDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getActualDisbursementDate() const noexcept;
    void setActualDisbursementDate(const ::trantor::Date &pActualDisbursementDate) noexcept;
    void setActualDisbursementDateToNull() noexcept;

    /**  For column disbursed_by  */
    const std::string &getValueOfDisbursedBy() const noexcept;
    const std::shared_ptr<std::string> &getDisbursedBy() const noexcept;
    void setDisbursedBy(const std::string &pDisbursedBy) noexcept;
    void setDisbursedBy(std::string &&pDisbursedBy) noexcept;
    void setDisbursedByToNull() noexcept;

    /**  For column expected_first_repayment_on_date  */
    const ::trantor::Date &getValueOfExpectedFirstRepaymentOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getExpectedFirstRepaymentOnDate() const noexcept;
    void setExpectedFirstRepaymentOnDate(const ::trantor::Date &pExpectedFirstRepaymentOnDate) noexcept;
    void setExpectedFirstRepaymentOnDateToNull() noexcept;

    /**  For column interest_charged_from_date  */
    const ::trantor::Date &getValueOfInterestChargedFromDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getInterestChargedFromDate() const noexcept;
    void setInterestChargedFromDate(const ::trantor::Date &pInterestChargedFromDate) noexcept;
    void setInterestChargedFromDateToNull() noexcept;

    /**  For column expected_maturity_date  */
    const ::trantor::Date &getValueOfExpectedMaturityDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getExpectedMaturityDate() const noexcept;
    void setExpectedMaturityDate(const ::trantor::Date &pExpectedMaturityDate) noexcept;
    void setExpectedMaturityDateToNull() noexcept;

    /**  For column maturity_date  */
    const ::trantor::Date &getValueOfMaturityDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getMaturityDate() const noexcept;
    void setMaturityDate(const ::trantor::Date &pMaturityDate) noexcept;
    void setMaturityDateToNull() noexcept;

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

    /**  For column rejected_on_date  */
    const ::trantor::Date &getValueOfRejectedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getRejectedOnDate() const noexcept;
    void setRejectedOnDate(const ::trantor::Date &pRejectedOnDate) noexcept;
    void setRejectedOnDateToNull() noexcept;

    /**  For column withdrawn_on_date  */
    const ::trantor::Date &getValueOfWithdrawnOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getWithdrawnOnDate() const noexcept;
    void setWithdrawnOnDate(const ::trantor::Date &pWithdrawnOnDate) noexcept;
    void setWithdrawnOnDateToNull() noexcept;

    /**  For column writtenoff_on_date  */
    const ::trantor::Date &getValueOfWrittenoffOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getWrittenoffOnDate() const noexcept;
    void setWrittenoffOnDate(const ::trantor::Date &pWrittenoffOnDate) noexcept;
    void setWrittenoffOnDateToNull() noexcept;

    /**  For column status  */
    const int32_t &getValueOfStatus() const noexcept;
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column sub_status  */
    const int32_t &getValueOfSubStatus() const noexcept;
    const std::shared_ptr<int32_t> &getSubStatus() const noexcept;
    void setSubStatus(const int32_t &pSubStatus) noexcept;
    void setSubStatusToNull() noexcept;

    /**  For column is_npa  */
    const bool &getValueOfIsNpa() const noexcept;
    const std::shared_ptr<bool> &getIsNpa() const noexcept;
    void setIsNpa(const bool &pIsNpa) noexcept;

    /**  For column delinquency_range_id  */
    const std::string &getValueOfDelinquencyRangeId() const noexcept;
    const std::shared_ptr<std::string> &getDelinquencyRangeId() const noexcept;
    void setDelinquencyRangeId(const std::string &pDelinquencyRangeId) noexcept;
    void setDelinquencyRangeId(std::string &&pDelinquencyRangeId) noexcept;
    void setDelinquencyRangeIdToNull() noexcept;

    /**  For column overdue_since_date  */
    const ::trantor::Date &getValueOfOverdueSinceDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getOverdueSinceDate() const noexcept;
    void setOverdueSinceDate(const ::trantor::Date &pOverdueSinceDate) noexcept;
    void setOverdueSinceDateToNull() noexcept;

    /**  For column principal_disbursed  */
    const std::string &getValueOfPrincipalDisbursed() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalDisbursed() const noexcept;
    void setPrincipalDisbursed(const std::string &pPrincipalDisbursed) noexcept;
    void setPrincipalDisbursed(std::string &&pPrincipalDisbursed) noexcept;

    /**  For column principal_paid  */
    const std::string &getValueOfPrincipalPaid() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalPaid() const noexcept;
    void setPrincipalPaid(const std::string &pPrincipalPaid) noexcept;
    void setPrincipalPaid(std::string &&pPrincipalPaid) noexcept;

    /**  For column principal_writtenoff  */
    const std::string &getValueOfPrincipalWrittenoff() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalWrittenoff() const noexcept;
    void setPrincipalWrittenoff(const std::string &pPrincipalWrittenoff) noexcept;
    void setPrincipalWrittenoff(std::string &&pPrincipalWrittenoff) noexcept;

    /**  For column interest_charged  */
    const std::string &getValueOfInterestCharged() const noexcept;
    const std::shared_ptr<std::string> &getInterestCharged() const noexcept;
    void setInterestCharged(const std::string &pInterestCharged) noexcept;
    void setInterestCharged(std::string &&pInterestCharged) noexcept;

    /**  For column interest_paid  */
    const std::string &getValueOfInterestPaid() const noexcept;
    const std::shared_ptr<std::string> &getInterestPaid() const noexcept;
    void setInterestPaid(const std::string &pInterestPaid) noexcept;
    void setInterestPaid(std::string &&pInterestPaid) noexcept;

    /**  For column interest_waived  */
    const std::string &getValueOfInterestWaived() const noexcept;
    const std::shared_ptr<std::string> &getInterestWaived() const noexcept;
    void setInterestWaived(const std::string &pInterestWaived) noexcept;
    void setInterestWaived(std::string &&pInterestWaived) noexcept;

    /**  For column interest_writtenoff  */
    const std::string &getValueOfInterestWrittenoff() const noexcept;
    const std::shared_ptr<std::string> &getInterestWrittenoff() const noexcept;
    void setInterestWrittenoff(const std::string &pInterestWrittenoff) noexcept;
    void setInterestWrittenoff(std::string &&pInterestWrittenoff) noexcept;

    /**  For column fee_charges_charged  */
    const std::string &getValueOfFeeChargesCharged() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesCharged() const noexcept;
    void setFeeChargesCharged(const std::string &pFeeChargesCharged) noexcept;
    void setFeeChargesCharged(std::string &&pFeeChargesCharged) noexcept;

    /**  For column fee_charges_paid  */
    const std::string &getValueOfFeeChargesPaid() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesPaid() const noexcept;
    void setFeeChargesPaid(const std::string &pFeeChargesPaid) noexcept;
    void setFeeChargesPaid(std::string &&pFeeChargesPaid) noexcept;

    /**  For column fee_charges_waived  */
    const std::string &getValueOfFeeChargesWaived() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesWaived() const noexcept;
    void setFeeChargesWaived(const std::string &pFeeChargesWaived) noexcept;
    void setFeeChargesWaived(std::string &&pFeeChargesWaived) noexcept;

    /**  For column fee_charges_writtenoff  */
    const std::string &getValueOfFeeChargesWrittenoff() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesWrittenoff() const noexcept;
    void setFeeChargesWrittenoff(const std::string &pFeeChargesWrittenoff) noexcept;
    void setFeeChargesWrittenoff(std::string &&pFeeChargesWrittenoff) noexcept;

    /**  For column penalty_charges_charged  */
    const std::string &getValueOfPenaltyChargesCharged() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesCharged() const noexcept;
    void setPenaltyChargesCharged(const std::string &pPenaltyChargesCharged) noexcept;
    void setPenaltyChargesCharged(std::string &&pPenaltyChargesCharged) noexcept;

    /**  For column penalty_charges_paid  */
    const std::string &getValueOfPenaltyChargesPaid() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesPaid() const noexcept;
    void setPenaltyChargesPaid(const std::string &pPenaltyChargesPaid) noexcept;
    void setPenaltyChargesPaid(std::string &&pPenaltyChargesPaid) noexcept;

    /**  For column penalty_charges_waived  */
    const std::string &getValueOfPenaltyChargesWaived() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesWaived() const noexcept;
    void setPenaltyChargesWaived(const std::string &pPenaltyChargesWaived) noexcept;
    void setPenaltyChargesWaived(std::string &&pPenaltyChargesWaived) noexcept;

    /**  For column penalty_charges_writtenoff  */
    const std::string &getValueOfPenaltyChargesWrittenoff() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesWrittenoff() const noexcept;
    void setPenaltyChargesWrittenoff(const std::string &pPenaltyChargesWrittenoff) noexcept;
    void setPenaltyChargesWrittenoff(std::string &&pPenaltyChargesWrittenoff) noexcept;

    /**  For column total_recovered  */
    const std::string &getValueOfTotalRecovered() const noexcept;
    const std::shared_ptr<std::string> &getTotalRecovered() const noexcept;
    void setTotalRecovered(const std::string &pTotalRecovered) noexcept;
    void setTotalRecovered(std::string &&pTotalRecovered) noexcept;

    /**  For column total_overpaid  */
    const std::string &getValueOfTotalOverpaid() const noexcept;
    const std::shared_ptr<std::string> &getTotalOverpaid() const noexcept;
    void setTotalOverpaid(const std::string &pTotalOverpaid) noexcept;
    void setTotalOverpaid(std::string &&pTotalOverpaid) noexcept;

    /**  For column buydown_fee_amount  */
    const std::string &getValueOfBuydownFeeAmount() const noexcept;
    const std::shared_ptr<std::string> &getBuydownFeeAmount() const noexcept;
    void setBuydownFeeAmount(const std::string &pBuydownFeeAmount) noexcept;
    void setBuydownFeeAmount(std::string &&pBuydownFeeAmount) noexcept;

    /**  For column capitalized_income_amount  */
    const std::string &getValueOfCapitalizedIncomeAmount() const noexcept;
    const std::shared_ptr<std::string> &getCapitalizedIncomeAmount() const noexcept;
    void setCapitalizedIncomeAmount(const std::string &pCapitalizedIncomeAmount) noexcept;
    void setCapitalizedIncomeAmount(std::string &&pCapitalizedIncomeAmount) noexcept;

    /**  For column glim_parent_loan_id  */
    const std::string &getValueOfGlimParentLoanId() const noexcept;
    const std::shared_ptr<std::string> &getGlimParentLoanId() const noexcept;
    void setGlimParentLoanId(const std::string &pGlimParentLoanId) noexcept;
    void setGlimParentLoanId(std::string &&pGlimParentLoanId) noexcept;
    void setGlimParentLoanIdToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 78;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<Loan>;
    friend drogon::orm::BaseBuilder<Loan, true, true>;
    friend drogon::orm::BaseBuilder<Loan, true, false>;
    friend drogon::orm::BaseBuilder<Loan, false, true>;
    friend drogon::orm::BaseBuilder<Loan, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Loan>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> accountNo_;
    std::shared_ptr<std::string> externalId_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> groupId_;
    std::shared_ptr<std::string> productId_;
    std::shared_ptr<std::string> loanOfficerId_;
    std::shared_ptr<std::string> fundId_;
    std::shared_ptr<std::string> loanPurpose_;
    std::shared_ptr<int32_t> loanType_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<int32_t> currencyDigits_;
    std::shared_ptr<std::string> principalAmount_;
    std::shared_ptr<std::string> approvedPrincipal_;
    std::shared_ptr<std::string> netDisbursalAmount_;
    std::shared_ptr<int32_t> numberOfRepayments_;
    std::shared_ptr<int32_t> repaymentEvery_;
    std::shared_ptr<int32_t> repaymentFrequencyType_;
    std::shared_ptr<std::string> interestRatePerPeriod_;
    std::shared_ptr<int32_t> interestPeriodFrequencyType_;
    std::shared_ptr<std::string> annualNominalInterestRate_;
    std::shared_ptr<int32_t> interestMethod_;
    std::shared_ptr<int32_t> interestCalculationPeriodType_;
    std::shared_ptr<int32_t> amortizationType_;
    std::shared_ptr<std::string> transactionProcessingStrategy_;
    std::shared_ptr<int32_t> daysInYearType_;
    std::shared_ptr<int32_t> daysInMonthType_;
    std::shared_ptr<int32_t> graceOnPrincipalPayment_;
    std::shared_ptr<int32_t> graceOnInterestPayment_;
    std::shared_ptr<int32_t> graceOnInterestCharged_;
    std::shared_ptr<int32_t> graceOnArrearsAgeing_;
    std::shared_ptr<bool> isEqualAmortization_;
    std::shared_ptr<bool> isFloatingInterestRate_;
    std::shared_ptr<std::string> floatingRateId_;
    std::shared_ptr<std::string> interestRateDifferential_;
    std::shared_ptr<::trantor::Date> submittedOnDate_;
    std::shared_ptr<std::string> submittedBy_;
    std::shared_ptr<::trantor::Date> approvedOnDate_;
    std::shared_ptr<std::string> approvedBy_;
    std::shared_ptr<::trantor::Date> expectedDisbursementDate_;
    std::shared_ptr<::trantor::Date> actualDisbursementDate_;
    std::shared_ptr<std::string> disbursedBy_;
    std::shared_ptr<::trantor::Date> expectedFirstRepaymentOnDate_;
    std::shared_ptr<::trantor::Date> interestChargedFromDate_;
    std::shared_ptr<::trantor::Date> expectedMaturityDate_;
    std::shared_ptr<::trantor::Date> maturityDate_;
    std::shared_ptr<::trantor::Date> closedOnDate_;
    std::shared_ptr<std::string> closedBy_;
    std::shared_ptr<::trantor::Date> rejectedOnDate_;
    std::shared_ptr<::trantor::Date> withdrawnOnDate_;
    std::shared_ptr<::trantor::Date> writtenoffOnDate_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<int32_t> subStatus_;
    std::shared_ptr<bool> isNpa_;
    std::shared_ptr<std::string> delinquencyRangeId_;
    std::shared_ptr<::trantor::Date> overdueSinceDate_;
    std::shared_ptr<std::string> principalDisbursed_;
    std::shared_ptr<std::string> principalPaid_;
    std::shared_ptr<std::string> principalWrittenoff_;
    std::shared_ptr<std::string> interestCharged_;
    std::shared_ptr<std::string> interestPaid_;
    std::shared_ptr<std::string> interestWaived_;
    std::shared_ptr<std::string> interestWrittenoff_;
    std::shared_ptr<std::string> feeChargesCharged_;
    std::shared_ptr<std::string> feeChargesPaid_;
    std::shared_ptr<std::string> feeChargesWaived_;
    std::shared_ptr<std::string> feeChargesWrittenoff_;
    std::shared_ptr<std::string> penaltyChargesCharged_;
    std::shared_ptr<std::string> penaltyChargesPaid_;
    std::shared_ptr<std::string> penaltyChargesWaived_;
    std::shared_ptr<std::string> penaltyChargesWrittenoff_;
    std::shared_ptr<std::string> totalRecovered_;
    std::shared_ptr<std::string> totalOverpaid_;
    std::shared_ptr<std::string> buydownFeeAmount_;
    std::shared_ptr<std::string> capitalizedIncomeAmount_;
    std::shared_ptr<std::string> glimParentLoanId_;
    std::shared_ptr<::trantor::Date> createdAt_;
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
    bool dirtyFlag_[78]={ false };
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
            sql += "account_no,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "external_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "group_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "product_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "loan_officer_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "fund_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "loan_purpose,";
            ++parametersCount;
        }
        sql += "loan_type,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        if(dirtyFlag_[10])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        sql += "currency_digits,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        if(dirtyFlag_[12])
        {
            sql += "principal_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "approved_principal,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "net_disbursal_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "number_of_repayments,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "repayment_every,";
            ++parametersCount;
        }
        if(dirtyFlag_[17])
        {
            sql += "repayment_frequency_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[18])
        {
            sql += "interest_rate_per_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[19])
        {
            sql += "interest_period_frequency_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[20])
        {
            sql += "annual_nominal_interest_rate,";
            ++parametersCount;
        }
        if(dirtyFlag_[21])
        {
            sql += "interest_method,";
            ++parametersCount;
        }
        if(dirtyFlag_[22])
        {
            sql += "interest_calculation_period_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[23])
        {
            sql += "amortization_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[24])
        {
            sql += "transaction_processing_strategy,";
            ++parametersCount;
        }
        sql += "days_in_year_type,";
        ++parametersCount;
        if(!dirtyFlag_[25])
        {
            needSelection=true;
        }
        sql += "days_in_month_type,";
        ++parametersCount;
        if(!dirtyFlag_[26])
        {
            needSelection=true;
        }
        sql += "grace_on_principal_payment,";
        ++parametersCount;
        if(!dirtyFlag_[27])
        {
            needSelection=true;
        }
        sql += "grace_on_interest_payment,";
        ++parametersCount;
        if(!dirtyFlag_[28])
        {
            needSelection=true;
        }
        sql += "grace_on_interest_charged,";
        ++parametersCount;
        if(!dirtyFlag_[29])
        {
            needSelection=true;
        }
        sql += "grace_on_arrears_ageing,";
        ++parametersCount;
        if(!dirtyFlag_[30])
        {
            needSelection=true;
        }
        sql += "is_equal_amortization,";
        ++parametersCount;
        if(!dirtyFlag_[31])
        {
            needSelection=true;
        }
        sql += "is_floating_interest_rate,";
        ++parametersCount;
        if(!dirtyFlag_[32])
        {
            needSelection=true;
        }
        if(dirtyFlag_[33])
        {
            sql += "floating_rate_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[34])
        {
            sql += "interest_rate_differential,";
            ++parametersCount;
        }
        if(dirtyFlag_[35])
        {
            sql += "submitted_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[36])
        {
            sql += "submitted_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[37])
        {
            sql += "approved_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[38])
        {
            sql += "approved_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[39])
        {
            sql += "expected_disbursement_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[40])
        {
            sql += "actual_disbursement_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[41])
        {
            sql += "disbursed_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[42])
        {
            sql += "expected_first_repayment_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[43])
        {
            sql += "interest_charged_from_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[44])
        {
            sql += "expected_maturity_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[45])
        {
            sql += "maturity_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[46])
        {
            sql += "closed_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[47])
        {
            sql += "closed_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[48])
        {
            sql += "rejected_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[49])
        {
            sql += "withdrawn_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[50])
        {
            sql += "writtenoff_on_date,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[51])
        {
            needSelection=true;
        }
        if(dirtyFlag_[52])
        {
            sql += "sub_status,";
            ++parametersCount;
        }
        sql += "is_npa,";
        ++parametersCount;
        if(!dirtyFlag_[53])
        {
            needSelection=true;
        }
        if(dirtyFlag_[54])
        {
            sql += "delinquency_range_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[55])
        {
            sql += "overdue_since_date,";
            ++parametersCount;
        }
        sql += "principal_disbursed,";
        ++parametersCount;
        if(!dirtyFlag_[56])
        {
            needSelection=true;
        }
        sql += "principal_paid,";
        ++parametersCount;
        if(!dirtyFlag_[57])
        {
            needSelection=true;
        }
        sql += "principal_writtenoff,";
        ++parametersCount;
        if(!dirtyFlag_[58])
        {
            needSelection=true;
        }
        sql += "interest_charged,";
        ++parametersCount;
        if(!dirtyFlag_[59])
        {
            needSelection=true;
        }
        sql += "interest_paid,";
        ++parametersCount;
        if(!dirtyFlag_[60])
        {
            needSelection=true;
        }
        sql += "interest_waived,";
        ++parametersCount;
        if(!dirtyFlag_[61])
        {
            needSelection=true;
        }
        sql += "interest_writtenoff,";
        ++parametersCount;
        if(!dirtyFlag_[62])
        {
            needSelection=true;
        }
        sql += "fee_charges_charged,";
        ++parametersCount;
        if(!dirtyFlag_[63])
        {
            needSelection=true;
        }
        sql += "fee_charges_paid,";
        ++parametersCount;
        if(!dirtyFlag_[64])
        {
            needSelection=true;
        }
        sql += "fee_charges_waived,";
        ++parametersCount;
        if(!dirtyFlag_[65])
        {
            needSelection=true;
        }
        sql += "fee_charges_writtenoff,";
        ++parametersCount;
        if(!dirtyFlag_[66])
        {
            needSelection=true;
        }
        sql += "penalty_charges_charged,";
        ++parametersCount;
        if(!dirtyFlag_[67])
        {
            needSelection=true;
        }
        sql += "penalty_charges_paid,";
        ++parametersCount;
        if(!dirtyFlag_[68])
        {
            needSelection=true;
        }
        sql += "penalty_charges_waived,";
        ++parametersCount;
        if(!dirtyFlag_[69])
        {
            needSelection=true;
        }
        sql += "penalty_charges_writtenoff,";
        ++parametersCount;
        if(!dirtyFlag_[70])
        {
            needSelection=true;
        }
        sql += "total_recovered,";
        ++parametersCount;
        if(!dirtyFlag_[71])
        {
            needSelection=true;
        }
        sql += "total_overpaid,";
        ++parametersCount;
        if(!dirtyFlag_[72])
        {
            needSelection=true;
        }
        sql += "buydown_fee_amount,";
        ++parametersCount;
        if(!dirtyFlag_[73])
        {
            needSelection=true;
        }
        sql += "capitalized_income_amount,";
        ++parametersCount;
        if(!dirtyFlag_[74])
        {
            needSelection=true;
        }
        if(dirtyFlag_[75])
        {
            sql += "glim_parent_loan_id,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[76])
        {
            needSelection=true;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[77])
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
        if(dirtyFlag_[18])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        if(dirtyFlag_[23])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[54])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        else
        {
            sql +="default,";
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
        if(dirtyFlag_[59])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[60])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[61])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[62])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[63])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[64])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[65])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[66])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[67])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[68])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[69])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[70])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[71])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[72])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[73])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[74])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[75])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[76])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[77])
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
