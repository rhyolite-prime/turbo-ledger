/**
 *  InteropQuote.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<InteropQuote> usage actually needs
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
namespace TlInteroperationDb
{

class InteropQuote
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _transaction_code;
        static const std::string _quote_code;
        static const std::string _account_id;
        static const std::string _amount;
        static const std::string _fee_amount;
        static const std::string _currency;
        static const std::string _expiration;
        static const std::string _status;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit InteropQuote(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    InteropQuote() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column transaction_code  */
    const std::string &getValueOfTransactionCode() const noexcept;
    const std::shared_ptr<std::string> &getTransactionCode() const noexcept;
    void setTransactionCode(const std::string &pTransactionCode) noexcept;
    void setTransactionCode(std::string &&pTransactionCode) noexcept;

    /**  For column quote_code  */
    const std::string &getValueOfQuoteCode() const noexcept;
    const std::shared_ptr<std::string> &getQuoteCode() const noexcept;
    void setQuoteCode(const std::string &pQuoteCode) noexcept;
    void setQuoteCode(std::string &&pQuoteCode) noexcept;

    /**  For column account_id  */
    const std::string &getValueOfAccountId() const noexcept;
    const std::shared_ptr<std::string> &getAccountId() const noexcept;
    void setAccountId(const std::string &pAccountId) noexcept;
    void setAccountId(std::string &&pAccountId) noexcept;

    /**  For column amount  */
    const std::string &getValueOfAmount() const noexcept;
    const std::shared_ptr<std::string> &getAmount() const noexcept;
    void setAmount(const std::string &pAmount) noexcept;
    void setAmount(std::string &&pAmount) noexcept;

    /**  For column fee_amount  */
    const std::string &getValueOfFeeAmount() const noexcept;
    const std::shared_ptr<std::string> &getFeeAmount() const noexcept;
    void setFeeAmount(const std::string &pFeeAmount) noexcept;
    void setFeeAmount(std::string &&pFeeAmount) noexcept;

    /**  For column currency  */
    const std::string &getValueOfCurrency() const noexcept;
    const std::shared_ptr<std::string> &getCurrency() const noexcept;
    void setCurrency(const std::string &pCurrency) noexcept;
    void setCurrency(std::string &&pCurrency) noexcept;

    /**  For column expiration  */
    const ::trantor::Date &getValueOfExpiration() const noexcept;
    const std::shared_ptr<::trantor::Date> &getExpiration() const noexcept;
    void setExpiration(const ::trantor::Date &pExpiration) noexcept;
    void setExpirationToNull() noexcept;

    /**  For column status  */
    const std::string &getValueOfStatus() const noexcept;
    const std::shared_ptr<std::string> &getStatus() const noexcept;
    void setStatus(const std::string &pStatus) noexcept;
    void setStatus(std::string &&pStatus) noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 10;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<InteropQuote>;
    friend drogon::orm::BaseBuilder<InteropQuote, true, true>;
    friend drogon::orm::BaseBuilder<InteropQuote, true, false>;
    friend drogon::orm::BaseBuilder<InteropQuote, false, true>;
    friend drogon::orm::BaseBuilder<InteropQuote, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<InteropQuote>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> transactionCode_;
    std::shared_ptr<std::string> quoteCode_;
    std::shared_ptr<std::string> accountId_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<std::string> feeAmount_;
    std::shared_ptr<std::string> currency_;
    std::shared_ptr<::trantor::Date> expiration_;
    std::shared_ptr<std::string> status_;
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
        if(dirtyFlag_[1])
        {
            sql += "transaction_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "quote_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "amount,";
            ++parametersCount;
        }
        sql += "fee_amount,";
        ++parametersCount;
        if(!dirtyFlag_[5])
        {
            needSelection=true;
        }
        sql += "currency,";
        ++parametersCount;
        if(!dirtyFlag_[6])
        {
            needSelection=true;
        }
        if(dirtyFlag_[7])
        {
            sql += "expiration,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
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
        else
        {
            sql +="default,";
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
} // namespace TlInteroperationDb
} // namespace drogon_model
