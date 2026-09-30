/**
 *
 *  WorkingDays.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the
 *  subset of the API this codebase's CoroMapper<WorkingDays> usage
 *  actually needs (row-mapping + CRUD via Mapper/CoroMapper). The
 *  Json::Value constructors, updateByJson/updateByMasqueradedJson,
 *  validateJsonFor.../validJsonOfField and toJson/toString/toMasqueradedJson
 *  methods that a live `drogon_ctl create_model` run would also emit are
 *  intentionally omitted here since nothing in this codebase calls them;
 *  regenerate with `drogon_ctl create_model` against a live DB with this
 *  table if those are ever needed.
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
namespace TlOrganizationDb
{

class WorkingDays
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _working_days;
        static const std::string _repayment_rescheduling_type;
        static const std::string _extend_term_for_daily_repayments;
        static const std::string _modified_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = int32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit WorkingDays(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    WorkingDays() = default;

    /**  For column id  */
    const int32_t &getValueOfId() const noexcept;
    const std::shared_ptr<int32_t> &getId() const noexcept;
    void setId(const int32_t &pId) noexcept;

    /**  For column working_days  */
    const std::string &getValueOfWorkingDays() const noexcept;
    const std::shared_ptr<std::string> &getWorkingDays() const noexcept;
    void setWorkingDays(const std::string &pWorkingDays) noexcept;
    void setWorkingDays(std::string &&pWorkingDays) noexcept;

    /**  For column repayment_rescheduling_type  */
    const std::string &getValueOfRepaymentReschedulingType() const noexcept;
    const std::shared_ptr<std::string> &getRepaymentReschedulingType() const noexcept;
    void setRepaymentReschedulingType(const std::string &pRepaymentReschedulingType) noexcept;
    void setRepaymentReschedulingType(std::string &&pRepaymentReschedulingType) noexcept;

    /**  For column extend_term_for_daily_repayments  */
    const bool &getValueOfExtendTermForDailyRepayments() const noexcept;
    const std::shared_ptr<bool> &getExtendTermForDailyRepayments() const noexcept;
    void setExtendTermForDailyRepayments(const bool &pExtendTermForDailyRepayments) noexcept;

    /**  For column modified_at  */
    const ::trantor::Date &getValueOfModifiedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getModifiedAt() const noexcept;
    void setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 5;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<WorkingDays>;
    friend drogon::orm::BaseBuilder<WorkingDays, true, true>;
    friend drogon::orm::BaseBuilder<WorkingDays, true, false>;
    friend drogon::orm::BaseBuilder<WorkingDays, false, true>;
    friend drogon::orm::BaseBuilder<WorkingDays, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<WorkingDays>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> id_;
    std::shared_ptr<std::string> workingDays_;
    std::shared_ptr<std::string> repaymentReschedulingType_;
    std::shared_ptr<bool> extendTermForDailyRepayments_;
    std::shared_ptr<::trantor::Date> modifiedAt_;
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
    bool dirtyFlag_[5]={ false };
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
        sql += "working_days,";
        ++parametersCount;
        if(!dirtyFlag_[1])
        {
            needSelection=true;
        }
        sql += "repayment_rescheduling_type,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        sql += "extend_term_for_daily_repayments,";
        ++parametersCount;
        if(!dirtyFlag_[3])
        {
            needSelection=true;
        }
        sql += "modified_at,";
        ++parametersCount;
        if(!dirtyFlag_[4])
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
} // namespace TlOrganizationDb
} // namespace drogon_model

