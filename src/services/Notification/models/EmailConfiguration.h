/**
 *  EmailConfiguration.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<EmailConfiguration> usage actually needs
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

class EmailConfiguration
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _smtp_host;
        static const std::string _smtp_port;
        static const std::string _smtp_username;
        static const std::string _smtp_password;
        static const std::string _from_email;
        static const std::string _from_name;
        static const std::string _use_tls;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = int32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit EmailConfiguration(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    EmailConfiguration() = default;

    /**  For column id  */
    const int32_t &getValueOfId() const noexcept;
    const std::shared_ptr<int32_t> &getId() const noexcept;
    void setId(const int32_t &pId) noexcept;

    /**  For column smtp_host  */
    const std::string &getValueOfSmtpHost() const noexcept;
    const std::shared_ptr<std::string> &getSmtpHost() const noexcept;
    void setSmtpHost(const std::string &pSmtpHost) noexcept;
    void setSmtpHost(std::string &&pSmtpHost) noexcept;
    void setSmtpHostToNull() noexcept;

    /**  For column smtp_port  */
    const int32_t &getValueOfSmtpPort() const noexcept;
    const std::shared_ptr<int32_t> &getSmtpPort() const noexcept;
    void setSmtpPort(const int32_t &pSmtpPort) noexcept;

    /**  For column smtp_username  */
    const std::string &getValueOfSmtpUsername() const noexcept;
    const std::shared_ptr<std::string> &getSmtpUsername() const noexcept;
    void setSmtpUsername(const std::string &pSmtpUsername) noexcept;
    void setSmtpUsername(std::string &&pSmtpUsername) noexcept;
    void setSmtpUsernameToNull() noexcept;

    /**  For column smtp_password  */
    const std::string &getValueOfSmtpPassword() const noexcept;
    const std::shared_ptr<std::string> &getSmtpPassword() const noexcept;
    void setSmtpPassword(const std::string &pSmtpPassword) noexcept;
    void setSmtpPassword(std::string &&pSmtpPassword) noexcept;
    void setSmtpPasswordToNull() noexcept;

    /**  For column from_email  */
    const std::string &getValueOfFromEmail() const noexcept;
    const std::shared_ptr<std::string> &getFromEmail() const noexcept;
    void setFromEmail(const std::string &pFromEmail) noexcept;
    void setFromEmail(std::string &&pFromEmail) noexcept;
    void setFromEmailToNull() noexcept;

    /**  For column from_name  */
    const std::string &getValueOfFromName() const noexcept;
    const std::shared_ptr<std::string> &getFromName() const noexcept;
    void setFromName(const std::string &pFromName) noexcept;
    void setFromName(std::string &&pFromName) noexcept;
    void setFromNameToNull() noexcept;

    /**  For column use_tls  */
    const bool &getValueOfUseTls() const noexcept;
    const std::shared_ptr<bool> &getUseTls() const noexcept;
    void setUseTls(const bool &pUseTls) noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<EmailConfiguration>;
    friend drogon::orm::BaseBuilder<EmailConfiguration, true, true>;
    friend drogon::orm::BaseBuilder<EmailConfiguration, true, false>;
    friend drogon::orm::BaseBuilder<EmailConfiguration, false, true>;
    friend drogon::orm::BaseBuilder<EmailConfiguration, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<EmailConfiguration>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> id_;
    std::shared_ptr<std::string> smtpHost_;
    std::shared_ptr<int32_t> smtpPort_;
    std::shared_ptr<std::string> smtpUsername_;
    std::shared_ptr<std::string> smtpPassword_;
    std::shared_ptr<std::string> fromEmail_;
    std::shared_ptr<std::string> fromName_;
    std::shared_ptr<bool> useTls_;
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
            sql += "smtp_host,";
            ++parametersCount;
        }
        sql += "smtp_port,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        if(dirtyFlag_[3])
        {
            sql += "smtp_username,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "smtp_password,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "from_email,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "from_name,";
            ++parametersCount;
        }
        sql += "use_tls,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "updated_at,";
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
