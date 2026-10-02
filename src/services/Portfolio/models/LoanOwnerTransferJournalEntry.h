/**
 *  LoanOwnerTransferJournalEntry.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<LoanOwnerTransferJournalEntry> usage actually needs
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

class LoanOwnerTransferJournalEntry
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _transfer_id;
        static const std::string _entry_type;
        static const std::string _amount;
        static const std::string _gl_account_id;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit LoanOwnerTransferJournalEntry(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    LoanOwnerTransferJournalEntry() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column transfer_id  */
    const std::string &getValueOfTransferId() const noexcept;
    const std::shared_ptr<std::string> &getTransferId() const noexcept;
    void setTransferId(const std::string &pTransferId) noexcept;
    void setTransferId(std::string &&pTransferId) noexcept;

    /**  For column entry_type  */
    const std::string &getValueOfEntryType() const noexcept;
    const std::shared_ptr<std::string> &getEntryType() const noexcept;
    void setEntryType(const std::string &pEntryType) noexcept;
    void setEntryType(std::string &&pEntryType) noexcept;

    /**  For column amount  */
    const std::string &getValueOfAmount() const noexcept;
    const std::shared_ptr<std::string> &getAmount() const noexcept;
    void setAmount(const std::string &pAmount) noexcept;
    void setAmount(std::string &&pAmount) noexcept;

    /**  For column gl_account_id  */
    const std::string &getValueOfGlAccountId() const noexcept;
    const std::shared_ptr<std::string> &getGlAccountId() const noexcept;
    void setGlAccountId(const std::string &pGlAccountId) noexcept;
    void setGlAccountId(std::string &&pGlAccountId) noexcept;
    void setGlAccountIdToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 6;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<LoanOwnerTransferJournalEntry>;
    friend drogon::orm::BaseBuilder<LoanOwnerTransferJournalEntry, true, true>;
    friend drogon::orm::BaseBuilder<LoanOwnerTransferJournalEntry, true, false>;
    friend drogon::orm::BaseBuilder<LoanOwnerTransferJournalEntry, false, true>;
    friend drogon::orm::BaseBuilder<LoanOwnerTransferJournalEntry, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<LoanOwnerTransferJournalEntry>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> transferId_;
    std::shared_ptr<std::string> entryType_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<std::string> glAccountId_;
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
    bool dirtyFlag_[6]={ false };
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
            sql += "transfer_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "entry_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "gl_account_id,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[5])
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
