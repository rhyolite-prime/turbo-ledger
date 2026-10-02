/**
 *  JobRunHistory.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<JobRunHistory> usage actually needs
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
namespace TlHeartBeatDb
{

class JobRunHistory
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _job_id;
        static const std::string _version;
        static const std::string _start_time;
        static const std::string _end_time;
        static const std::string _status;
        static const std::string _trigger_type;
        static const std::string _error_log;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit JobRunHistory(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    JobRunHistory() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column job_id  */
    const std::string &getValueOfJobId() const noexcept;
    const std::shared_ptr<std::string> &getJobId() const noexcept;
    void setJobId(const std::string &pJobId) noexcept;
    void setJobId(std::string &&pJobId) noexcept;

    /**  For column version  */
    const int64_t &getValueOfVersion() const noexcept;
    const std::shared_ptr<int64_t> &getVersion() const noexcept;
    void setVersion(const int64_t &pVersion) noexcept;

    /**  For column start_time  */
    const ::trantor::Date &getValueOfStartTime() const noexcept;
    const std::shared_ptr<::trantor::Date> &getStartTime() const noexcept;
    void setStartTime(const ::trantor::Date &pStartTime) noexcept;

    /**  For column end_time  */
    const ::trantor::Date &getValueOfEndTime() const noexcept;
    const std::shared_ptr<::trantor::Date> &getEndTime() const noexcept;
    void setEndTime(const ::trantor::Date &pEndTime) noexcept;
    void setEndTimeToNull() noexcept;

    /**  For column status  */
    const std::string &getValueOfStatus() const noexcept;
    const std::shared_ptr<std::string> &getStatus() const noexcept;
    void setStatus(const std::string &pStatus) noexcept;
    void setStatus(std::string &&pStatus) noexcept;

    /**  For column trigger_type  */
    const std::string &getValueOfTriggerType() const noexcept;
    const std::shared_ptr<std::string> &getTriggerType() const noexcept;
    void setTriggerType(const std::string &pTriggerType) noexcept;
    void setTriggerType(std::string &&pTriggerType) noexcept;

    /**  For column error_log  */
    const std::string &getValueOfErrorLog() const noexcept;
    const std::shared_ptr<std::string> &getErrorLog() const noexcept;
    void setErrorLog(const std::string &pErrorLog) noexcept;
    void setErrorLog(std::string &&pErrorLog) noexcept;
    void setErrorLogToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<JobRunHistory>;
    friend drogon::orm::BaseBuilder<JobRunHistory, true, true>;
    friend drogon::orm::BaseBuilder<JobRunHistory, true, false>;
    friend drogon::orm::BaseBuilder<JobRunHistory, false, true>;
    friend drogon::orm::BaseBuilder<JobRunHistory, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<JobRunHistory>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> jobId_;
    std::shared_ptr<int64_t> version_;
    std::shared_ptr<::trantor::Date> startTime_;
    std::shared_ptr<::trantor::Date> endTime_;
    std::shared_ptr<std::string> status_;
    std::shared_ptr<std::string> triggerType_;
    std::shared_ptr<std::string> errorLog_;
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
    bool dirtyFlag_[9]={ false };
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
            sql += "job_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "version,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "start_time,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "end_time,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "status,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "trigger_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "error_log,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[8])
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
} // namespace TlHeartBeatDb
} // namespace drogon_model
