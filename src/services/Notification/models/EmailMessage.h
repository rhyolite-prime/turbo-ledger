/**
 *  EmailMessage.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<EmailMessage> usage actually needs
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

class EmailMessage
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _campaign_id;
        static const std::string _client_id;
        static const std::string _group_id;
        static const std::string _staff_id;
        static const std::string _email_address;
        static const std::string _email_subject;
        static const std::string _email_message;
        static const std::string _status;
        static const std::string _error_message;
        static const std::string _created_at;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit EmailMessage(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    EmailMessage() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column campaign_id  */
    const std::string &getValueOfCampaignId() const noexcept;
    const std::shared_ptr<std::string> &getCampaignId() const noexcept;
    void setCampaignId(const std::string &pCampaignId) noexcept;
    void setCampaignId(std::string &&pCampaignId) noexcept;
    void setCampaignIdToNull() noexcept;

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

    /**  For column staff_id  */
    const std::string &getValueOfStaffId() const noexcept;
    const std::shared_ptr<std::string> &getStaffId() const noexcept;
    void setStaffId(const std::string &pStaffId) noexcept;
    void setStaffId(std::string &&pStaffId) noexcept;
    void setStaffIdToNull() noexcept;

    /**  For column email_address  */
    const std::string &getValueOfEmailAddress() const noexcept;
    const std::shared_ptr<std::string> &getEmailAddress() const noexcept;
    void setEmailAddress(const std::string &pEmailAddress) noexcept;
    void setEmailAddress(std::string &&pEmailAddress) noexcept;

    /**  For column email_subject  */
    const std::string &getValueOfEmailSubject() const noexcept;
    const std::shared_ptr<std::string> &getEmailSubject() const noexcept;
    void setEmailSubject(const std::string &pEmailSubject) noexcept;
    void setEmailSubject(std::string &&pEmailSubject) noexcept;

    /**  For column email_message  */
    const std::string &getValueOfEmailMessage() const noexcept;
    const std::shared_ptr<std::string> &getEmailMessage() const noexcept;
    void setEmailMessage(const std::string &pEmailMessage) noexcept;
    void setEmailMessage(std::string &&pEmailMessage) noexcept;

    /**  For column status  */
    const std::string &getValueOfStatus() const noexcept;
    const std::shared_ptr<std::string> &getStatus() const noexcept;
    void setStatus(const std::string &pStatus) noexcept;
    void setStatus(std::string &&pStatus) noexcept;

    /**  For column error_message  */
    const std::string &getValueOfErrorMessage() const noexcept;
    const std::shared_ptr<std::string> &getErrorMessage() const noexcept;
    void setErrorMessage(const std::string &pErrorMessage) noexcept;
    void setErrorMessage(std::string &&pErrorMessage) noexcept;
    void setErrorMessageToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 12;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<EmailMessage>;
    friend drogon::orm::BaseBuilder<EmailMessage, true, true>;
    friend drogon::orm::BaseBuilder<EmailMessage, true, false>;
    friend drogon::orm::BaseBuilder<EmailMessage, false, true>;
    friend drogon::orm::BaseBuilder<EmailMessage, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<EmailMessage>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> campaignId_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> groupId_;
    std::shared_ptr<std::string> staffId_;
    std::shared_ptr<std::string> emailAddress_;
    std::shared_ptr<std::string> emailSubject_;
    std::shared_ptr<std::string> emailMessage_;
    std::shared_ptr<std::string> status_;
    std::shared_ptr<std::string> errorMessage_;
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
            sql += "campaign_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "group_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "staff_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "email_address,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "email_subject,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "email_message,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        if(dirtyFlag_[9])
        {
            sql += "error_message,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "updated_at,";
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
} // namespace TlNotificationDb
} // namespace drogon_model
