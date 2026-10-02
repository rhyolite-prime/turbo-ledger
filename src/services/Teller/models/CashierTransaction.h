/**
 *  CashierTransaction.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<CashierTransaction> usage actually needs
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
namespace TlTellerDb
{

class CashierTransaction
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _cashier_id;
        static const std::string _txn_type;
        static const std::string _txn_amount;
        static const std::string _txn_date;
        static const std::string _currency_code;
        static const std::string _entity_id;
        static const std::string _entity_type;
        static const std::string _txn_note;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit CashierTransaction(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    CashierTransaction() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column cashier_id  */
    const std::string &getValueOfCashierId() const noexcept;
    const std::shared_ptr<std::string> &getCashierId() const noexcept;
    void setCashierId(const std::string &pCashierId) noexcept;
    void setCashierId(std::string &&pCashierId) noexcept;

    /**  For column txn_type  */
    const int32_t &getValueOfTxnType() const noexcept;
    const std::shared_ptr<int32_t> &getTxnType() const noexcept;
    void setTxnType(const int32_t &pTxnType) noexcept;

    /**  For column txn_amount  */
    const std::string &getValueOfTxnAmount() const noexcept;
    const std::shared_ptr<std::string> &getTxnAmount() const noexcept;
    void setTxnAmount(const std::string &pTxnAmount) noexcept;
    void setTxnAmount(std::string &&pTxnAmount) noexcept;

    /**  For column txn_date  */
    const ::trantor::Date &getValueOfTxnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getTxnDate() const noexcept;
    void setTxnDate(const ::trantor::Date &pTxnDate) noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column entity_id  */
    const std::string &getValueOfEntityId() const noexcept;
    const std::shared_ptr<std::string> &getEntityId() const noexcept;
    void setEntityId(const std::string &pEntityId) noexcept;
    void setEntityId(std::string &&pEntityId) noexcept;
    void setEntityIdToNull() noexcept;

    /**  For column entity_type  */
    const std::string &getValueOfEntityType() const noexcept;
    const std::shared_ptr<std::string> &getEntityType() const noexcept;
    void setEntityType(const std::string &pEntityType) noexcept;
    void setEntityType(std::string &&pEntityType) noexcept;
    void setEntityTypeToNull() noexcept;

    /**  For column txn_note  */
    const std::string &getValueOfTxnNote() const noexcept;
    const std::shared_ptr<std::string> &getTxnNote() const noexcept;
    void setTxnNote(const std::string &pTxnNote) noexcept;
    void setTxnNote(std::string &&pTxnNote) noexcept;
    void setTxnNoteToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 10;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<CashierTransaction>;
    friend drogon::orm::BaseBuilder<CashierTransaction, true, true>;
    friend drogon::orm::BaseBuilder<CashierTransaction, true, false>;
    friend drogon::orm::BaseBuilder<CashierTransaction, false, true>;
    friend drogon::orm::BaseBuilder<CashierTransaction, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<CashierTransaction>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> cashierId_;
    std::shared_ptr<int32_t> txnType_;
    std::shared_ptr<std::string> txnAmount_;
    std::shared_ptr<::trantor::Date> txnDate_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<std::string> entityId_;
    std::shared_ptr<std::string> entityType_;
    std::shared_ptr<std::string> txnNote_;
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
    bool dirtyFlag_[10]={ false };
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
        sql += "cashier_id,";
        ++parametersCount;
        if(!dirtyFlag_[1])
        {
            needSelection=true;
        }
        if(dirtyFlag_[2])
        {
            sql += "txn_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "txn_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "txn_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "entity_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "entity_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "txn_note,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[9])
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
        else
        {
            sql +="default,";
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
} // namespace TlTellerDb
} // namespace drogon_model
