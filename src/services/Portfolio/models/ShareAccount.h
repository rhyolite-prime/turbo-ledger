/**
 *  ShareAccount.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<ShareAccount> usage actually needs
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

class ShareAccount
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
        static const std::string _currency_code;
        static const std::string _submitted_date;
        static const std::string _submitted_by;
        static const std::string _approved_date;
        static const std::string _approved_by;
        static const std::string _activated_date;
        static const std::string _rejected_date;
        static const std::string _closed_date;
        static const std::string _status;
        static const std::string _requested_shares;
        static const std::string _approved_shares;
        static const std::string _lockin_period;
        static const std::string _lockin_period_frequency_type;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit ShareAccount(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    ShareAccount() = default;

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

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column submitted_date  */
    const ::trantor::Date &getValueOfSubmittedDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedDate() const noexcept;
    void setSubmittedDate(const ::trantor::Date &pSubmittedDate) noexcept;

    /**  For column submitted_by  */
    const std::string &getValueOfSubmittedBy() const noexcept;
    const std::shared_ptr<std::string> &getSubmittedBy() const noexcept;
    void setSubmittedBy(const std::string &pSubmittedBy) noexcept;
    void setSubmittedBy(std::string &&pSubmittedBy) noexcept;
    void setSubmittedByToNull() noexcept;

    /**  For column approved_date  */
    const ::trantor::Date &getValueOfApprovedDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getApprovedDate() const noexcept;
    void setApprovedDate(const ::trantor::Date &pApprovedDate) noexcept;
    void setApprovedDateToNull() noexcept;

    /**  For column approved_by  */
    const std::string &getValueOfApprovedBy() const noexcept;
    const std::shared_ptr<std::string> &getApprovedBy() const noexcept;
    void setApprovedBy(const std::string &pApprovedBy) noexcept;
    void setApprovedBy(std::string &&pApprovedBy) noexcept;
    void setApprovedByToNull() noexcept;

    /**  For column activated_date  */
    const ::trantor::Date &getValueOfActivatedDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getActivatedDate() const noexcept;
    void setActivatedDate(const ::trantor::Date &pActivatedDate) noexcept;
    void setActivatedDateToNull() noexcept;

    /**  For column rejected_date  */
    const ::trantor::Date &getValueOfRejectedDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getRejectedDate() const noexcept;
    void setRejectedDate(const ::trantor::Date &pRejectedDate) noexcept;
    void setRejectedDateToNull() noexcept;

    /**  For column closed_date  */
    const ::trantor::Date &getValueOfClosedDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getClosedDate() const noexcept;
    void setClosedDate(const ::trantor::Date &pClosedDate) noexcept;
    void setClosedDateToNull() noexcept;

    /**  For column status  */
    const int32_t &getValueOfStatus() const noexcept;
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column requested_shares  */
    const int64_t &getValueOfRequestedShares() const noexcept;
    const std::shared_ptr<int64_t> &getRequestedShares() const noexcept;
    void setRequestedShares(const int64_t &pRequestedShares) noexcept;

    /**  For column approved_shares  */
    const int64_t &getValueOfApprovedShares() const noexcept;
    const std::shared_ptr<int64_t> &getApprovedShares() const noexcept;
    void setApprovedShares(const int64_t &pApprovedShares) noexcept;

    /**  For column lockin_period  */
    const int32_t &getValueOfLockinPeriod() const noexcept;
    const std::shared_ptr<int32_t> &getLockinPeriod() const noexcept;
    void setLockinPeriod(const int32_t &pLockinPeriod) noexcept;
    void setLockinPeriodToNull() noexcept;

    /**  For column lockin_period_frequency_type  */
    const int32_t &getValueOfLockinPeriodFrequencyType() const noexcept;
    const std::shared_ptr<int32_t> &getLockinPeriodFrequencyType() const noexcept;
    void setLockinPeriodFrequencyType(const int32_t &pLockinPeriodFrequencyType) noexcept;
    void setLockinPeriodFrequencyTypeToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 20;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<ShareAccount>;
    friend drogon::orm::BaseBuilder<ShareAccount, true, true>;
    friend drogon::orm::BaseBuilder<ShareAccount, true, false>;
    friend drogon::orm::BaseBuilder<ShareAccount, false, true>;
    friend drogon::orm::BaseBuilder<ShareAccount, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<ShareAccount>;
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
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<::trantor::Date> submittedDate_;
    std::shared_ptr<std::string> submittedBy_;
    std::shared_ptr<::trantor::Date> approvedDate_;
    std::shared_ptr<std::string> approvedBy_;
    std::shared_ptr<::trantor::Date> activatedDate_;
    std::shared_ptr<::trantor::Date> rejectedDate_;
    std::shared_ptr<::trantor::Date> closedDate_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<int64_t> requestedShares_;
    std::shared_ptr<int64_t> approvedShares_;
    std::shared_ptr<int32_t> lockinPeriod_;
    std::shared_ptr<int32_t> lockinPeriodFrequencyType_;
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
    bool dirtyFlag_[20]={ false };
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
            sql += "currency_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "submitted_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "submitted_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "approved_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "approved_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "activated_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "rejected_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "closed_date,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        if(dirtyFlag_[15])
        {
            sql += "requested_shares,";
            ++parametersCount;
        }
        sql += "approved_shares,";
        ++parametersCount;
        if(!dirtyFlag_[16])
        {
            needSelection=true;
        }
        if(dirtyFlag_[17])
        {
            sql += "lockin_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[18])
        {
            sql += "lockin_period_frequency_type,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[19])
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
