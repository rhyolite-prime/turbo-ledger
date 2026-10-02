/**
 *  SavingsAccountTransaction.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<SavingsAccountTransaction> usage actually needs
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

class SavingsAccountTransaction
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _savings_account_id;
        static const std::string _transaction_type;
        static const std::string _transaction_date;
        static const std::string _amount;
        static const std::string _running_balance_derived;
        static const std::string _overdraft_amount_derived;
        static const std::string _is_reversed;
        static const std::string _is_hold_transaction;
        static const std::string _release_id_of_hold;
        static const std::string _payment_detail_id;
        static const std::string _submitted_on_date;
        static const std::string _description;
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

    explicit SavingsAccountTransaction(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    SavingsAccountTransaction() = default;

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

    /**  For column savings_account_id  */
    const std::string &getValueOfSavingsAccountId() const noexcept;
    const std::shared_ptr<std::string> &getSavingsAccountId() const noexcept;
    void setSavingsAccountId(const std::string &pSavingsAccountId) noexcept;
    void setSavingsAccountId(std::string &&pSavingsAccountId) noexcept;

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

    /**  For column running_balance_derived  */
    const std::string &getValueOfRunningBalanceDerived() const noexcept;
    const std::shared_ptr<std::string> &getRunningBalanceDerived() const noexcept;
    void setRunningBalanceDerived(const std::string &pRunningBalanceDerived) noexcept;
    void setRunningBalanceDerived(std::string &&pRunningBalanceDerived) noexcept;

    /**  For column overdraft_amount_derived  */
    const std::string &getValueOfOverdraftAmountDerived() const noexcept;
    const std::shared_ptr<std::string> &getOverdraftAmountDerived() const noexcept;
    void setOverdraftAmountDerived(const std::string &pOverdraftAmountDerived) noexcept;
    void setOverdraftAmountDerived(std::string &&pOverdraftAmountDerived) noexcept;

    /**  For column is_reversed  */
    const bool &getValueOfIsReversed() const noexcept;
    const std::shared_ptr<bool> &getIsReversed() const noexcept;
    void setIsReversed(const bool &pIsReversed) noexcept;

    /**  For column is_hold_transaction  */
    const bool &getValueOfIsHoldTransaction() const noexcept;
    const std::shared_ptr<bool> &getIsHoldTransaction() const noexcept;
    void setIsHoldTransaction(const bool &pIsHoldTransaction) noexcept;

    /**  For column release_id_of_hold  */
    const std::string &getValueOfReleaseIdOfHold() const noexcept;
    const std::shared_ptr<std::string> &getReleaseIdOfHold() const noexcept;
    void setReleaseIdOfHold(const std::string &pReleaseIdOfHold) noexcept;
    void setReleaseIdOfHold(std::string &&pReleaseIdOfHold) noexcept;
    void setReleaseIdOfHoldToNull() noexcept;

    /**  For column payment_detail_id  */
    const std::string &getValueOfPaymentDetailId() const noexcept;
    const std::shared_ptr<std::string> &getPaymentDetailId() const noexcept;
    void setPaymentDetailId(const std::string &pPaymentDetailId) noexcept;
    void setPaymentDetailId(std::string &&pPaymentDetailId) noexcept;
    void setPaymentDetailIdToNull() noexcept;

    /**  For column submitted_on_date  */
    const ::trantor::Date &getValueOfSubmittedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedOnDate() const noexcept;
    void setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept;

    /**  For column description  */
    const std::string &getValueOfDescription() const noexcept;
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;
    void setDescriptionToNull() noexcept;

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

    static size_t getColumnNumber() noexcept {  return 18;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<SavingsAccountTransaction>;
    friend drogon::orm::BaseBuilder<SavingsAccountTransaction, true, true>;
    friend drogon::orm::BaseBuilder<SavingsAccountTransaction, true, false>;
    friend drogon::orm::BaseBuilder<SavingsAccountTransaction, false, true>;
    friend drogon::orm::BaseBuilder<SavingsAccountTransaction, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<SavingsAccountTransaction>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> savingsAccountId_;
    std::shared_ptr<int32_t> transactionType_;
    std::shared_ptr<::trantor::Date> transactionDate_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<std::string> runningBalanceDerived_;
    std::shared_ptr<std::string> overdraftAmountDerived_;
    std::shared_ptr<bool> isReversed_;
    std::shared_ptr<bool> isHoldTransaction_;
    std::shared_ptr<std::string> releaseIdOfHold_;
    std::shared_ptr<std::string> paymentDetailId_;
    std::shared_ptr<::trantor::Date> submittedOnDate_;
    std::shared_ptr<std::string> description_;
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
            sql += "business_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "savings_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "transaction_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "transaction_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "running_balance_derived,";
            ++parametersCount;
        }
        sql += "overdraft_amount_derived,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "is_reversed,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        sql += "is_hold_transaction,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        if(dirtyFlag_[10])
        {
            sql += "release_id_of_hold,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "payment_detail_id,";
            ++parametersCount;
        }
        sql += "submitted_on_date,";
        ++parametersCount;
        if(!dirtyFlag_[12])
        {
            needSelection=true;
        }
        if(dirtyFlag_[13])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[15])
        {
            needSelection=true;
        }
        if(dirtyFlag_[16])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
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
        else
        {
            sql +="default,";
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
} // namespace TlDamDb
} // namespace drogon_model
