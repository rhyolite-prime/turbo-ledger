/**
 *  SmsCampaign.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<SmsCampaign> usage actually needs
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
namespace TlNotificationDb
{

class SmsCampaign
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _campaign_name;
        static const std::string _campaign_type;
        static const std::string _message;
        static const std::string _param_value;
        static const std::string _recurrence;
        static const std::string _next_trigger_date;
        static const std::string _status;
        static const std::string _provider_id;
        static const std::string _created_at;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit SmsCampaign(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    SmsCampaign() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column campaign_name  */
    const std::string &getValueOfCampaignName() const noexcept;
    const std::shared_ptr<std::string> &getCampaignName() const noexcept;
    void setCampaignName(const std::string &pCampaignName) noexcept;
    void setCampaignName(std::string &&pCampaignName) noexcept;

    /**  For column campaign_type  */
    const std::string &getValueOfCampaignType() const noexcept;
    const std::shared_ptr<std::string> &getCampaignType() const noexcept;
    void setCampaignType(const std::string &pCampaignType) noexcept;
    void setCampaignType(std::string &&pCampaignType) noexcept;

    /**  For column message  */
    const std::string &getValueOfMessage() const noexcept;
    const std::shared_ptr<std::string> &getMessage() const noexcept;
    void setMessage(const std::string &pMessage) noexcept;
    void setMessage(std::string &&pMessage) noexcept;

    /**  For column param_value  */
    const std::string &getValueOfParamValue() const noexcept;
    const std::shared_ptr<std::string> &getParamValue() const noexcept;
    void setParamValue(const std::string &pParamValue) noexcept;
    void setParamValue(std::string &&pParamValue) noexcept;

    /**  For column recurrence  */
    const std::string &getValueOfRecurrence() const noexcept;
    const std::shared_ptr<std::string> &getRecurrence() const noexcept;
    void setRecurrence(const std::string &pRecurrence) noexcept;
    void setRecurrence(std::string &&pRecurrence) noexcept;
    void setRecurrenceToNull() noexcept;

    /**  For column next_trigger_date  */
    const ::trantor::Date &getValueOfNextTriggerDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getNextTriggerDate() const noexcept;
    void setNextTriggerDate(const ::trantor::Date &pNextTriggerDate) noexcept;
    void setNextTriggerDateToNull() noexcept;

    /**  For column status  */
    const std::string &getValueOfStatus() const noexcept;
    const std::shared_ptr<std::string> &getStatus() const noexcept;
    void setStatus(const std::string &pStatus) noexcept;
    void setStatus(std::string &&pStatus) noexcept;

    /**  For column provider_id  */
    const std::string &getValueOfProviderId() const noexcept;
    const std::shared_ptr<std::string> &getProviderId() const noexcept;
    void setProviderId(const std::string &pProviderId) noexcept;
    void setProviderId(std::string &&pProviderId) noexcept;
    void setProviderIdToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 11;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<SmsCampaign>;
    friend drogon::orm::BaseBuilder<SmsCampaign, true, true>;
    friend drogon::orm::BaseBuilder<SmsCampaign, true, false>;
    friend drogon::orm::BaseBuilder<SmsCampaign, false, true>;
    friend drogon::orm::BaseBuilder<SmsCampaign, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<SmsCampaign>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> campaignName_;
    std::shared_ptr<std::string> campaignType_;
    std::shared_ptr<std::string> message_;
    std::shared_ptr<std::string> paramValue_;
    std::shared_ptr<std::string> recurrence_;
    std::shared_ptr<::trantor::Date> nextTriggerDate_;
    std::shared_ptr<std::string> status_;
    std::shared_ptr<std::string> providerId_;
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
    bool dirtyFlag_[11]={ false };
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
            sql += "campaign_name,";
            ++parametersCount;
        }
        sql += "campaign_type,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        if(dirtyFlag_[3])
        {
            sql += "message,";
            ++parametersCount;
        }
        sql += "param_value,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        if(dirtyFlag_[5])
        {
            sql += "recurrence,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "next_trigger_date,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        if(dirtyFlag_[8])
        {
            sql += "provider_id,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[10])
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
} // namespace TlNotificationDb
} // namespace drogon_model
