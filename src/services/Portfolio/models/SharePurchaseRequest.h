/**
 *  SharePurchaseRequest.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<SharePurchaseRequest> usage actually needs
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

class SharePurchaseRequest
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _share_account_id;
        static const std::string _requested_date;
        static const std::string _requested_shares;
        static const std::string _requested_price;
        static const std::string _status;
        static const std::string _requested_by;
        static const std::string _decided_by;
        static const std::string _decided_date;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit SharePurchaseRequest(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    SharePurchaseRequest() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column share_account_id  */
    const std::string &getValueOfShareAccountId() const noexcept;
    const std::shared_ptr<std::string> &getShareAccountId() const noexcept;
    void setShareAccountId(const std::string &pShareAccountId) noexcept;
    void setShareAccountId(std::string &&pShareAccountId) noexcept;

    /**  For column requested_date  */
    const ::trantor::Date &getValueOfRequestedDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getRequestedDate() const noexcept;
    void setRequestedDate(const ::trantor::Date &pRequestedDate) noexcept;

    /**  For column requested_shares  */
    const int64_t &getValueOfRequestedShares() const noexcept;
    const std::shared_ptr<int64_t> &getRequestedShares() const noexcept;
    void setRequestedShares(const int64_t &pRequestedShares) noexcept;

    /**  For column requested_price  */
    const std::string &getValueOfRequestedPrice() const noexcept;
    const std::shared_ptr<std::string> &getRequestedPrice() const noexcept;
    void setRequestedPrice(const std::string &pRequestedPrice) noexcept;
    void setRequestedPrice(std::string &&pRequestedPrice) noexcept;
    void setRequestedPriceToNull() noexcept;

    /**  For column status  */
    const int32_t &getValueOfStatus() const noexcept;
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column requested_by  */
    const std::string &getValueOfRequestedBy() const noexcept;
    const std::shared_ptr<std::string> &getRequestedBy() const noexcept;
    void setRequestedBy(const std::string &pRequestedBy) noexcept;
    void setRequestedBy(std::string &&pRequestedBy) noexcept;
    void setRequestedByToNull() noexcept;

    /**  For column decided_by  */
    const std::string &getValueOfDecidedBy() const noexcept;
    const std::shared_ptr<std::string> &getDecidedBy() const noexcept;
    void setDecidedBy(const std::string &pDecidedBy) noexcept;
    void setDecidedBy(std::string &&pDecidedBy) noexcept;
    void setDecidedByToNull() noexcept;

    /**  For column decided_date  */
    const ::trantor::Date &getValueOfDecidedDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getDecidedDate() const noexcept;
    void setDecidedDate(const ::trantor::Date &pDecidedDate) noexcept;
    void setDecidedDateToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 10;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<SharePurchaseRequest>;
    friend drogon::orm::BaseBuilder<SharePurchaseRequest, true, true>;
    friend drogon::orm::BaseBuilder<SharePurchaseRequest, true, false>;
    friend drogon::orm::BaseBuilder<SharePurchaseRequest, false, true>;
    friend drogon::orm::BaseBuilder<SharePurchaseRequest, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<SharePurchaseRequest>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> shareAccountId_;
    std::shared_ptr<::trantor::Date> requestedDate_;
    std::shared_ptr<int64_t> requestedShares_;
    std::shared_ptr<std::string> requestedPrice_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<std::string> requestedBy_;
    std::shared_ptr<std::string> decidedBy_;
    std::shared_ptr<::trantor::Date> decidedDate_;
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
            sql += "share_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "requested_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "requested_shares,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "requested_price,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[5])
        {
            needSelection=true;
        }
        if(dirtyFlag_[6])
        {
            sql += "requested_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "decided_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "decided_date,";
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
} // namespace TlPortfolioDb
} // namespace drogon_model
