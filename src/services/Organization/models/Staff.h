/**
 *
 *  Staff.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the
 *  subset of the API this codebase's CoroMapper<Staff> usage
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

class Staff
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _office_id;
        static const std::string _firstname;
        static const std::string _lastname;
        static const std::string _display_name;
        static const std::string _external_id;
        static const std::string _mobile_no;
        static const std::string _is_loan_officer;
        static const std::string _is_active;
        static const std::string _joining_date;
        static const std::string _created_at;
        static const std::string _modified_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Staff(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    Staff() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column office_id  */
    const std::string &getValueOfOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getOfficeId() const noexcept;
    void setOfficeId(const std::string &pOfficeId) noexcept;
    void setOfficeId(std::string &&pOfficeId) noexcept;

    /**  For column firstname  */
    const std::string &getValueOfFirstname() const noexcept;
    const std::shared_ptr<std::string> &getFirstname() const noexcept;
    void setFirstname(const std::string &pFirstname) noexcept;
    void setFirstname(std::string &&pFirstname) noexcept;

    /**  For column lastname  */
    const std::string &getValueOfLastname() const noexcept;
    const std::shared_ptr<std::string> &getLastname() const noexcept;
    void setLastname(const std::string &pLastname) noexcept;
    void setLastname(std::string &&pLastname) noexcept;

    /**  For column display_name  */
    const std::string &getValueOfDisplayName() const noexcept;
    const std::shared_ptr<std::string> &getDisplayName() const noexcept;
    ///  Column display_name is `GENERATED ALWAYS AS (...) STORED` — read only, no setter.

    /**  For column external_id  */
    const std::string &getValueOfExternalId() const noexcept;
    const std::shared_ptr<std::string> &getExternalId() const noexcept;
    void setExternalId(const std::string &pExternalId) noexcept;
    void setExternalId(std::string &&pExternalId) noexcept;
    void setExternalIdToNull() noexcept;

    /**  For column mobile_no  */
    const std::string &getValueOfMobileNo() const noexcept;
    const std::shared_ptr<std::string> &getMobileNo() const noexcept;
    void setMobileNo(const std::string &pMobileNo) noexcept;
    void setMobileNo(std::string &&pMobileNo) noexcept;
    void setMobileNoToNull() noexcept;

    /**  For column is_loan_officer  */
    const bool &getValueOfIsLoanOfficer() const noexcept;
    const std::shared_ptr<bool> &getIsLoanOfficer() const noexcept;
    void setIsLoanOfficer(const bool &pIsLoanOfficer) noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

    /**  For column joining_date  */
    const ::trantor::Date &getValueOfJoiningDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getJoiningDate() const noexcept;
    void setJoiningDate(const ::trantor::Date &pJoiningDate) noexcept;
    void setJoiningDateToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column modified_at  */
    const ::trantor::Date &getValueOfModifiedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getModifiedAt() const noexcept;
    void setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 12;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<Staff>;
    friend drogon::orm::BaseBuilder<Staff, true, true>;
    friend drogon::orm::BaseBuilder<Staff, true, false>;
    friend drogon::orm::BaseBuilder<Staff, false, true>;
    friend drogon::orm::BaseBuilder<Staff, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Staff>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> officeId_;
    std::shared_ptr<std::string> firstname_;
    std::shared_ptr<std::string> lastname_;
    std::shared_ptr<std::string> displayName_;
    std::shared_ptr<std::string> externalId_;
    std::shared_ptr<std::string> mobileNo_;
    std::shared_ptr<bool> isLoanOfficer_;
    std::shared_ptr<bool> isActive_;
    std::shared_ptr<::trantor::Date> joiningDate_;
    std::shared_ptr<::trantor::Date> createdAt_;
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
    bool dirtyFlag_[12]={ false };
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
            sql += "office_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "firstname,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "lastname,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "external_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "mobile_no,";
            ++parametersCount;
        }
        sql += "is_loan_officer,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        if(dirtyFlag_[9])
        {
            sql += "joining_date,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "modified_at,";
        ++parametersCount;
        if(!dirtyFlag_[11])
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[11])
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

