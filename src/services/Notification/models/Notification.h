/**
 *  Notification.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<Notification> usage actually needs
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

class Notification
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _user_id;
        static const std::string _actor_id;
        static const std::string _object_type;
        static const std::string _object_id;
        static const std::string _action;
        static const std::string _content;
        static const std::string _is_read;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit Notification(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    Notification() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column user_id  */
    const std::string &getValueOfUserId() const noexcept;
    const std::shared_ptr<std::string> &getUserId() const noexcept;
    void setUserId(const std::string &pUserId) noexcept;
    void setUserId(std::string &&pUserId) noexcept;

    /**  For column actor_id  */
    const std::string &getValueOfActorId() const noexcept;
    const std::shared_ptr<std::string> &getActorId() const noexcept;
    void setActorId(const std::string &pActorId) noexcept;
    void setActorId(std::string &&pActorId) noexcept;
    void setActorIdToNull() noexcept;

    /**  For column object_type  */
    const std::string &getValueOfObjectType() const noexcept;
    const std::shared_ptr<std::string> &getObjectType() const noexcept;
    void setObjectType(const std::string &pObjectType) noexcept;
    void setObjectType(std::string &&pObjectType) noexcept;

    /**  For column object_id  */
    const std::string &getValueOfObjectId() const noexcept;
    const std::shared_ptr<std::string> &getObjectId() const noexcept;
    void setObjectId(const std::string &pObjectId) noexcept;
    void setObjectId(std::string &&pObjectId) noexcept;
    void setObjectIdToNull() noexcept;

    /**  For column action  */
    const std::string &getValueOfAction() const noexcept;
    const std::shared_ptr<std::string> &getAction() const noexcept;
    void setAction(const std::string &pAction) noexcept;
    void setAction(std::string &&pAction) noexcept;

    /**  For column content  */
    const std::string &getValueOfContent() const noexcept;
    const std::shared_ptr<std::string> &getContent() const noexcept;
    void setContent(const std::string &pContent) noexcept;
    void setContent(std::string &&pContent) noexcept;

    /**  For column is_read  */
    const bool &getValueOfIsRead() const noexcept;
    const std::shared_ptr<bool> &getIsRead() const noexcept;
    void setIsRead(const bool &pIsRead) noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<Notification>;
    friend drogon::orm::BaseBuilder<Notification, true, true>;
    friend drogon::orm::BaseBuilder<Notification, true, false>;
    friend drogon::orm::BaseBuilder<Notification, false, true>;
    friend drogon::orm::BaseBuilder<Notification, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Notification>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> userId_;
    std::shared_ptr<std::string> actorId_;
    std::shared_ptr<std::string> objectType_;
    std::shared_ptr<std::string> objectId_;
    std::shared_ptr<std::string> action_;
    std::shared_ptr<std::string> content_;
    std::shared_ptr<bool> isRead_;
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
            sql += "user_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "actor_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "object_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "object_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "action,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "content,";
            ++parametersCount;
        }
        sql += "is_read,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
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
