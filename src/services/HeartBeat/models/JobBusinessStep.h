/**
 *  JobBusinessStep.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<JobBusinessStep> usage actually needs
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

class JobBusinessStep
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _job_id;
        static const std::string _step_name;
        static const std::string _step_order;
        static const std::string _is_enabled;
        static const std::string _created_at;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit JobBusinessStep(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    JobBusinessStep() = default;

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

    /**  For column step_name  */
    const std::string &getValueOfStepName() const noexcept;
    const std::shared_ptr<std::string> &getStepName() const noexcept;
    void setStepName(const std::string &pStepName) noexcept;
    void setStepName(std::string &&pStepName) noexcept;

    /**  For column step_order  */
    const int32_t &getValueOfStepOrder() const noexcept;
    const std::shared_ptr<int32_t> &getStepOrder() const noexcept;
    void setStepOrder(const int32_t &pStepOrder) noexcept;

    /**  For column is_enabled  */
    const bool &getValueOfIsEnabled() const noexcept;
    const std::shared_ptr<bool> &getIsEnabled() const noexcept;
    void setIsEnabled(const bool &pIsEnabled) noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 7;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<JobBusinessStep>;
    friend drogon::orm::BaseBuilder<JobBusinessStep, true, true>;
    friend drogon::orm::BaseBuilder<JobBusinessStep, true, false>;
    friend drogon::orm::BaseBuilder<JobBusinessStep, false, true>;
    friend drogon::orm::BaseBuilder<JobBusinessStep, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<JobBusinessStep>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> jobId_;
    std::shared_ptr<std::string> stepName_;
    std::shared_ptr<int32_t> stepOrder_;
    std::shared_ptr<bool> isEnabled_;
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
    bool dirtyFlag_[7]={ false };
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
            sql += "step_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "step_order,";
            ++parametersCount;
        }
        sql += "is_enabled,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[5])
        {
            needSelection=true;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[6])
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
        else
        {
            sql +="default,";
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
