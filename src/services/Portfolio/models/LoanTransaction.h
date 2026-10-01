/**
 *  LoanTransaction.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<LoanTransaction> usage actually needs
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

class LoanTransaction
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _loan_id;
        static const std::string _external_id;
        static const std::string _office_id;
        static const std::string _transaction_type;
        static const std::string _transaction_date;
        static const std::string _amount;
        static const std::string _principal_portion;
        static const std::string _interest_portion;
        static const std::string _fee_charges_portion;
        static const std::string _penalty_charges_portion;
        static const std::string _overpayment_portion;
        static const std::string _outstanding_loan_balance_derived;
        static const std::string _is_reversed;
        static const std::string _reversed_on_date;
        static const std::string _submitted_on_date;
        static const std::string _created_by;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit LoanTransaction(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    LoanTransaction() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column loan_id  */
    const std::string &getValueOfLoanId() const noexcept;
    const std::shared_ptr<std::string> &getLoanId() const noexcept;
    void setLoanId(const std::string &pLoanId) noexcept;
    void setLoanId(std::string &&pLoanId) noexcept;

    /**  For column external_id  */
    const std::string &getValueOfExternalId() const noexcept;
    const std::shared_ptr<std::string> &getExternalId() const noexcept;
    void setExternalId(const std::string &pExternalId) noexcept;
    void setExternalId(std::string &&pExternalId) noexcept;
    void setExternalIdToNull() noexcept;

    /**  For column office_id  */
    const std::string &getValueOfOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getOfficeId() const noexcept;
    void setOfficeId(const std::string &pOfficeId) noexcept;
    void setOfficeId(std::string &&pOfficeId) noexcept;
    void setOfficeIdToNull() noexcept;

    /**  For column transaction_type  */
    const int32_t &getValueOfTransactionType() const noexcept;
    const std::shared_ptr<int32_t> &getTransactionType() const noexcept;
    void setTransactionType(const int32_t &pTransactionType) noexcept;

    /**  For column transaction_date  */
    const ::trantor::Date &getValueOfTransactionDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getTransactionDate() const noexcept;
    void setTransactionDate(const ::trantor::Date &pTransactionDate) noexcept;

    /**  For column amount  */
    const std::string &getValueOfAmount() const noexcept;
    const std::shared_ptr<std::string> &getAmount() const noexcept;
    void setAmount(const std::string &pAmount) noexcept;
    void setAmount(std::string &&pAmount) noexcept;

    /**  For column principal_portion  */
    const std::string &getValueOfPrincipalPortion() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalPortion() const noexcept;
    void setPrincipalPortion(const std::string &pPrincipalPortion) noexcept;
    void setPrincipalPortion(std::string &&pPrincipalPortion) noexcept;

    /**  For column interest_portion  */
    const std::string &getValueOfInterestPortion() const noexcept;
    const std::shared_ptr<std::string> &getInterestPortion() const noexcept;
    void setInterestPortion(const std::string &pInterestPortion) noexcept;
    void setInterestPortion(std::string &&pInterestPortion) noexcept;

    /**  For column fee_charges_portion  */
    const std::string &getValueOfFeeChargesPortion() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesPortion() const noexcept;
    void setFeeChargesPortion(const std::string &pFeeChargesPortion) noexcept;
    void setFeeChargesPortion(std::string &&pFeeChargesPortion) noexcept;

    /**  For column penalty_charges_portion  */
    const std::string &getValueOfPenaltyChargesPortion() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesPortion() const noexcept;
    void setPenaltyChargesPortion(const std::string &pPenaltyChargesPortion) noexcept;
    void setPenaltyChargesPortion(std::string &&pPenaltyChargesPortion) noexcept;

    /**  For column overpayment_portion  */
    const std::string &getValueOfOverpaymentPortion() const noexcept;
    const std::shared_ptr<std::string> &getOverpaymentPortion() const noexcept;
    void setOverpaymentPortion(const std::string &pOverpaymentPortion) noexcept;
    void setOverpaymentPortion(std::string &&pOverpaymentPortion) noexcept;

    /**  For column outstanding_loan_balance_derived  */
    const std::string &getValueOfOutstandingLoanBalanceDerived() const noexcept;
    const std::shared_ptr<std::string> &getOutstandingLoanBalanceDerived() const noexcept;
    void setOutstandingLoanBalanceDerived(const std::string &pOutstandingLoanBalanceDerived) noexcept;
    void setOutstandingLoanBalanceDerived(std::string &&pOutstandingLoanBalanceDerived) noexcept;
    void setOutstandingLoanBalanceDerivedToNull() noexcept;

    /**  For column is_reversed  */
    const bool &getValueOfIsReversed() const noexcept;
    const std::shared_ptr<bool> &getIsReversed() const noexcept;
    void setIsReversed(const bool &pIsReversed) noexcept;

    /**  For column reversed_on_date  */
    const ::trantor::Date &getValueOfReversedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getReversedOnDate() const noexcept;
    void setReversedOnDate(const ::trantor::Date &pReversedOnDate) noexcept;
    void setReversedOnDateToNull() noexcept;

    /**  For column submitted_on_date  */
    const ::trantor::Date &getValueOfSubmittedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedOnDate() const noexcept;
    void setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept;

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

    static size_t getColumnNumber() noexcept {  return 18;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<LoanTransaction>;
    friend drogon::orm::BaseBuilder<LoanTransaction, true, true>;
    friend drogon::orm::BaseBuilder<LoanTransaction, true, false>;
    friend drogon::orm::BaseBuilder<LoanTransaction, false, true>;
    friend drogon::orm::BaseBuilder<LoanTransaction, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<LoanTransaction>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> loanId_;
    std::shared_ptr<std::string> externalId_;
    std::shared_ptr<std::string> officeId_;
    std::shared_ptr<int32_t> transactionType_;
    std::shared_ptr<::trantor::Date> transactionDate_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<std::string> principalPortion_;
    std::shared_ptr<std::string> interestPortion_;
    std::shared_ptr<std::string> feeChargesPortion_;
    std::shared_ptr<std::string> penaltyChargesPortion_;
    std::shared_ptr<std::string> overpaymentPortion_;
    std::shared_ptr<std::string> outstandingLoanBalanceDerived_;
    std::shared_ptr<bool> isReversed_;
    std::shared_ptr<::trantor::Date> reversedOnDate_;
    std::shared_ptr<::trantor::Date> submittedOnDate_;
    std::shared_ptr<std::string> createdBy_;
    std::shared_ptr<::trantor::Date> createdAt_;
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
    bool dirtyFlag_[18]={ false };
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
            sql += "loan_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "external_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "office_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "transaction_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "transaction_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "amount,";
            ++parametersCount;
        }
        sql += "principal_portion,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "interest_portion,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        sql += "fee_charges_portion,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        sql += "penalty_charges_portion,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "overpayment_portion,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        if(dirtyFlag_[12])
        {
            sql += "outstanding_loan_balance_derived,";
            ++parametersCount;
        }
        sql += "is_reversed,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        if(dirtyFlag_[14])
        {
            sql += "reversed_on_date,";
            ++parametersCount;
        }
        sql += "submitted_on_date,";
        ++parametersCount;
        if(!dirtyFlag_[15])
        {
            needSelection=true;
        }
        if(dirtyFlag_[16])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[17])
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
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
