/**
 *  Cashier.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<Cashier> usage actually needs
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

class Cashier
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _teller_id;
        static const std::string _staff_id;
        static const std::string _description;
        static const std::string _start_date;
        static const std::string _end_date;
        static const std::string _is_full_day;
        static const std::string _start_time;
        static const std::string _end_time;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit Cashier(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    Cashier() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column teller_id  */
    const std::string &getValueOfTellerId() const noexcept;
    const std::shared_ptr<std::string> &getTellerId() const noexcept;
    void setTellerId(const std::string &pTellerId) noexcept;
    void setTellerId(std::string &&pTellerId) noexcept;

    /**  For column staff_id  */
    const std::string &getValueOfStaffId() const noexcept;
    const std::shared_ptr<std::string> &getStaffId() const noexcept;
    void setStaffId(const std::string &pStaffId) noexcept;
    void setStaffId(std::string &&pStaffId) noexcept;

    /**  For column description  */
    const std::string &getValueOfDescription() const noexcept;
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;
    void setDescriptionToNull() noexcept;

    /**  For column start_date  */
    const ::trantor::Date &getValueOfStartDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getStartDate() const noexcept;
    void setStartDate(const ::trantor::Date &pStartDate) noexcept;

    /**  For column end_date  */
    const ::trantor::Date &getValueOfEndDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getEndDate() const noexcept;
    void setEndDate(const ::trantor::Date &pEndDate) noexcept;
    void setEndDateToNull() noexcept;

    /**  For column is_full_day  */
    const bool &getValueOfIsFullDay() const noexcept;
    const std::shared_ptr<bool> &getIsFullDay() const noexcept;
    void setIsFullDay(const bool &pIsFullDay) noexcept;

    /**  For column start_time  */
    const std::string &getValueOfStartTime() const noexcept;
    const std::shared_ptr<std::string> &getStartTime() const noexcept;
    void setStartTime(const std::string &pStartTime) noexcept;
    void setStartTime(std::string &&pStartTime) noexcept;
    void setStartTimeToNull() noexcept;

    /**  For column end_time  */
    const std::string &getValueOfEndTime() const noexcept;
    const std::shared_ptr<std::string> &getEndTime() const noexcept;
    void setEndTime(const std::string &pEndTime) noexcept;
    void setEndTime(std::string &&pEndTime) noexcept;
    void setEndTimeToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 10;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<Cashier>;
    friend drogon::orm::BaseBuilder<Cashier, true, true>;
    friend drogon::orm::BaseBuilder<Cashier, true, false>;
    friend drogon::orm::BaseBuilder<Cashier, false, true>;
    friend drogon::orm::BaseBuilder<Cashier, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Cashier>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> tellerId_;
    std::shared_ptr<std::string> staffId_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<::trantor::Date> startDate_;
    std::shared_ptr<::trantor::Date> endDate_;
    std::shared_ptr<bool> isFullDay_;
    std::shared_ptr<std::string> startTime_;
    std::shared_ptr<std::string> endTime_;
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
        sql += "teller_id,";
        ++parametersCount;
        if(!dirtyFlag_[1])
        {
            needSelection=true;
        }
        sql += "staff_id,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        if(dirtyFlag_[3])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "start_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "end_date,";
            ++parametersCount;
        }
        sql += "is_full_day,";
        ++parametersCount;
        if(!dirtyFlag_[6])
        {
            needSelection=true;
        }
        if(dirtyFlag_[7])
        {
            sql += "start_time,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "end_time,";
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
