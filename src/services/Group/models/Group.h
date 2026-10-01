/**
 *  Group.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<Group> usage actually needs
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
namespace TlGroupDb
{

class Group
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _external_id;
        static const std::string _status_enum;
        static const std::string _activation_date;
        static const std::string _office_id;
        static const std::string _staff_id;
        static const std::string _parent_id;
        static const std::string _level_id;
        static const std::string _display_name;
        static const std::string _hierarchy;
        static const std::string _closure_reason_cv_id;
        static const std::string _closedon_date;
        static const std::string _activatedon_userid;
        static const std::string _submittedon_date;
        static const std::string _submittedon_userid;
        static const std::string _closedon_userid;
        static const std::string _account_no;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit Group(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    Group() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column external_id  */
    const std::string &getValueOfExternalId() const noexcept;
    const std::shared_ptr<std::string> &getExternalId() const noexcept;
    void setExternalId(const std::string &pExternalId) noexcept;
    void setExternalId(std::string &&pExternalId) noexcept;
    void setExternalIdToNull() noexcept;

    /**  For column status_enum  */
    const int32_t &getValueOfStatusEnum() const noexcept;
    const std::shared_ptr<int32_t> &getStatusEnum() const noexcept;
    void setStatusEnum(const int32_t &pStatusEnum) noexcept;

    /**  For column activation_date  */
    const ::trantor::Date &getValueOfActivationDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getActivationDate() const noexcept;
    void setActivationDate(const ::trantor::Date &pActivationDate) noexcept;
    void setActivationDateToNull() noexcept;

    /**  For column office_id  */
    const std::string &getValueOfOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getOfficeId() const noexcept;
    void setOfficeId(const std::string &pOfficeId) noexcept;
    void setOfficeId(std::string &&pOfficeId) noexcept;

    /**  For column staff_id  */
    const std::string &getValueOfStaffId() const noexcept;
    const std::shared_ptr<std::string> &getStaffId() const noexcept;
    void setStaffId(const std::string &pStaffId) noexcept;
    void setStaffId(std::string &&pStaffId) noexcept;

    /**  For column parent_id  */
    const std::string &getValueOfParentId() const noexcept;
    const std::shared_ptr<std::string> &getParentId() const noexcept;
    void setParentId(const std::string &pParentId) noexcept;
    void setParentId(std::string &&pParentId) noexcept;

    /**  For column level_id  */
    const std::string &getValueOfLevelId() const noexcept;
    const std::shared_ptr<std::string> &getLevelId() const noexcept;
    void setLevelId(const std::string &pLevelId) noexcept;
    void setLevelId(std::string &&pLevelId) noexcept;

    /**  For column display_name  */
    const std::string &getValueOfDisplayName() const noexcept;
    const std::shared_ptr<std::string> &getDisplayName() const noexcept;
    void setDisplayName(const std::string &pDisplayName) noexcept;
    void setDisplayName(std::string &&pDisplayName) noexcept;

    /**  For column hierarchy  */
    const std::string &getValueOfHierarchy() const noexcept;
    const std::shared_ptr<std::string> &getHierarchy() const noexcept;
    void setHierarchy(const std::string &pHierarchy) noexcept;
    void setHierarchy(std::string &&pHierarchy) noexcept;
    void setHierarchyToNull() noexcept;

    /**  For column closure_reason_cv_id  */
    const std::string &getValueOfClosureReasonCvId() const noexcept;
    const std::shared_ptr<std::string> &getClosureReasonCvId() const noexcept;
    void setClosureReasonCvId(const std::string &pClosureReasonCvId) noexcept;
    void setClosureReasonCvId(std::string &&pClosureReasonCvId) noexcept;

    /**  For column closedon_date  */
    const ::trantor::Date &getValueOfClosedonDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getClosedonDate() const noexcept;
    void setClosedonDate(const ::trantor::Date &pClosedonDate) noexcept;
    void setClosedonDateToNull() noexcept;

    /**  For column activatedon_userid  */
    const std::string &getValueOfActivatedonUserid() const noexcept;
    const std::shared_ptr<std::string> &getActivatedonUserid() const noexcept;
    void setActivatedonUserid(const std::string &pActivatedonUserid) noexcept;
    void setActivatedonUserid(std::string &&pActivatedonUserid) noexcept;

    /**  For column submittedon_date  */
    const ::trantor::Date &getValueOfSubmittedonDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedonDate() const noexcept;
    void setSubmittedonDate(const ::trantor::Date &pSubmittedonDate) noexcept;
    void setSubmittedonDateToNull() noexcept;

    /**  For column submittedon_userid  */
    const std::string &getValueOfSubmittedonUserid() const noexcept;
    const std::shared_ptr<std::string> &getSubmittedonUserid() const noexcept;
    void setSubmittedonUserid(const std::string &pSubmittedonUserid) noexcept;
    void setSubmittedonUserid(std::string &&pSubmittedonUserid) noexcept;

    /**  For column closedon_userid  */
    const std::string &getValueOfClosedonUserid() const noexcept;
    const std::shared_ptr<std::string> &getClosedonUserid() const noexcept;
    void setClosedonUserid(const std::string &pClosedonUserid) noexcept;
    void setClosedonUserid(std::string &&pClosedonUserid) noexcept;

    /**  For column account_no  */
    const std::string &getValueOfAccountNo() const noexcept;
    const std::shared_ptr<std::string> &getAccountNo() const noexcept;
    void setAccountNo(const std::string &pAccountNo) noexcept;
    void setAccountNo(std::string &&pAccountNo) noexcept;

    static size_t getColumnNumber() noexcept {  return 17;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<Group>;
    friend drogon::orm::BaseBuilder<Group, true, true>;
    friend drogon::orm::BaseBuilder<Group, true, false>;
    friend drogon::orm::BaseBuilder<Group, false, true>;
    friend drogon::orm::BaseBuilder<Group, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Group>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> externalId_;
    std::shared_ptr<int32_t> statusEnum_;
    std::shared_ptr<::trantor::Date> activationDate_;
    std::shared_ptr<std::string> officeId_;
    std::shared_ptr<std::string> staffId_;
    std::shared_ptr<std::string> parentId_;
    std::shared_ptr<std::string> levelId_;
    std::shared_ptr<std::string> displayName_;
    std::shared_ptr<std::string> hierarchy_;
    std::shared_ptr<std::string> closureReasonCvId_;
    std::shared_ptr<::trantor::Date> closedonDate_;
    std::shared_ptr<std::string> activatedonUserid_;
    std::shared_ptr<::trantor::Date> submittedonDate_;
    std::shared_ptr<std::string> submittedonUserid_;
    std::shared_ptr<std::string> closedonUserid_;
    std::shared_ptr<std::string> accountNo_;
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
    bool dirtyFlag_[17]={ false };
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
            sql += "external_id,";
            ++parametersCount;
        }
        sql += "status_enum,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        if(dirtyFlag_[3])
        {
            sql += "activation_date,";
            ++parametersCount;
        }
        sql += "office_id,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        sql += "staff_id,";
        ++parametersCount;
        if(!dirtyFlag_[5])
        {
            needSelection=true;
        }
        sql += "parent_id,";
        ++parametersCount;
        if(!dirtyFlag_[6])
        {
            needSelection=true;
        }
        sql += "level_id,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        if(dirtyFlag_[8])
        {
            sql += "display_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "hierarchy,";
            ++parametersCount;
        }
        sql += "closure_reason_cv_id,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        if(dirtyFlag_[11])
        {
            sql += "closedon_date,";
            ++parametersCount;
        }
        sql += "activatedon_userid,";
        ++parametersCount;
        if(!dirtyFlag_[12])
        {
            needSelection=true;
        }
        if(dirtyFlag_[13])
        {
            sql += "submittedon_date,";
            ++parametersCount;
        }
        sql += "submittedon_userid,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        sql += "closedon_userid,";
        ++parametersCount;
        if(!dirtyFlag_[15])
        {
            needSelection=true;
        }
        if(dirtyFlag_[16])
        {
            sql += "account_no,";
            ++parametersCount;
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
        if(dirtyFlag_[12])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[16])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
} // namespace TlGroupDb
} // namespace drogon_model
