/**
 *  Notification.cc
 *
 *  See Notification.h for the hand-authored-subset note.
 *
 */

#include "Notification.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlNotificationDb;

const std::string Notification::Cols::_id = "\"id\"";
const std::string Notification::Cols::_user_id = "\"user_id\"";
const std::string Notification::Cols::_actor_id = "\"actor_id\"";
const std::string Notification::Cols::_object_type = "\"object_type\"";
const std::string Notification::Cols::_object_id = "\"object_id\"";
const std::string Notification::Cols::_action = "\"action\"";
const std::string Notification::Cols::_content = "\"content\"";
const std::string Notification::Cols::_is_read = "\"is_read\"";
const std::string Notification::Cols::_created_at = "\"created_at\"";
const std::string Notification::primaryKeyName = "id";
const bool Notification::hasPrimaryKey = true;
const std::string Notification::tableName = "\"notifications\"";

const std::vector<typename Notification::MetaData> Notification::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"user_id","std::string","character varying",64,0,0,1},
{"actor_id","std::string","character varying",64,0,0,0},
{"object_type","std::string","character varying",50,0,0,1},
{"object_id","std::string","character varying",64,0,0,0},
{"action","std::string","character varying",50,0,0,1},
{"content","std::string","text",0,0,0,1},
{"is_read","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Notification::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Notification::Notification(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["user_id"].isNull())
        {
            userId_=std::make_shared<std::string>(r["user_id"].as<std::string>());
        }
        if(!r["actor_id"].isNull())
        {
            actorId_=std::make_shared<std::string>(r["actor_id"].as<std::string>());
        }
        if(!r["object_type"].isNull())
        {
            objectType_=std::make_shared<std::string>(r["object_type"].as<std::string>());
        }
        if(!r["object_id"].isNull())
        {
            objectId_=std::make_shared<std::string>(r["object_id"].as<std::string>());
        }
        if(!r["action"].isNull())
        {
            action_=std::make_shared<std::string>(r["action"].as<std::string>());
        }
        if(!r["content"].isNull())
        {
            content_=std::make_shared<std::string>(r["content"].as<std::string>());
        }
        if(!r["is_read"].isNull())
        {
            isRead_=std::make_shared<bool>(r["is_read"].as<bool>());
        }
        if(!r["created_at"].isNull())
        {
            auto timeStr = r["created_at"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 9 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            userId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            actorId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            objectType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            objectId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            action_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            content_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            isRead_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &Notification::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Notification::getId() const noexcept
{
    return id_;
}
void Notification::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Notification::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Notification::PrimaryKeyType & Notification::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Notification::getValueOfUserId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(userId_)
        return *userId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Notification::getUserId() const noexcept
{
    return userId_;
}
void Notification::setUserId(const std::string &pUserId) noexcept
{
    userId_ = std::make_shared<std::string>(pUserId);
    dirtyFlag_[1] = true;
}
void Notification::setUserId(std::string &&pUserId) noexcept
{
    userId_ = std::make_shared<std::string>(std::move(pUserId));
    dirtyFlag_[1] = true;
}

const std::string &Notification::getValueOfActorId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(actorId_)
        return *actorId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Notification::getActorId() const noexcept
{
    return actorId_;
}
void Notification::setActorId(const std::string &pActorId) noexcept
{
    actorId_ = std::make_shared<std::string>(pActorId);
    dirtyFlag_[2] = true;
}
void Notification::setActorId(std::string &&pActorId) noexcept
{
    actorId_ = std::make_shared<std::string>(std::move(pActorId));
    dirtyFlag_[2] = true;
}
void Notification::setActorIdToNull() noexcept
{
    actorId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &Notification::getValueOfObjectType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(objectType_)
        return *objectType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Notification::getObjectType() const noexcept
{
    return objectType_;
}
void Notification::setObjectType(const std::string &pObjectType) noexcept
{
    objectType_ = std::make_shared<std::string>(pObjectType);
    dirtyFlag_[3] = true;
}
void Notification::setObjectType(std::string &&pObjectType) noexcept
{
    objectType_ = std::make_shared<std::string>(std::move(pObjectType));
    dirtyFlag_[3] = true;
}

const std::string &Notification::getValueOfObjectId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(objectId_)
        return *objectId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Notification::getObjectId() const noexcept
{
    return objectId_;
}
void Notification::setObjectId(const std::string &pObjectId) noexcept
{
    objectId_ = std::make_shared<std::string>(pObjectId);
    dirtyFlag_[4] = true;
}
void Notification::setObjectId(std::string &&pObjectId) noexcept
{
    objectId_ = std::make_shared<std::string>(std::move(pObjectId));
    dirtyFlag_[4] = true;
}
void Notification::setObjectIdToNull() noexcept
{
    objectId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &Notification::getValueOfAction() const noexcept
{
    static const std::string defaultValue = std::string();
    if(action_)
        return *action_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Notification::getAction() const noexcept
{
    return action_;
}
void Notification::setAction(const std::string &pAction) noexcept
{
    action_ = std::make_shared<std::string>(pAction);
    dirtyFlag_[5] = true;
}
void Notification::setAction(std::string &&pAction) noexcept
{
    action_ = std::make_shared<std::string>(std::move(pAction));
    dirtyFlag_[5] = true;
}

const std::string &Notification::getValueOfContent() const noexcept
{
    static const std::string defaultValue = std::string();
    if(content_)
        return *content_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Notification::getContent() const noexcept
{
    return content_;
}
void Notification::setContent(const std::string &pContent) noexcept
{
    content_ = std::make_shared<std::string>(pContent);
    dirtyFlag_[6] = true;
}
void Notification::setContent(std::string &&pContent) noexcept
{
    content_ = std::make_shared<std::string>(std::move(pContent));
    dirtyFlag_[6] = true;
}

const bool &Notification::getValueOfIsRead() const noexcept
{
    static const bool defaultValue = bool();
    if(isRead_)
        return *isRead_;
    return defaultValue;
}
const std::shared_ptr<bool> &Notification::getIsRead() const noexcept
{
    return isRead_;
}
void Notification::setIsRead(const bool &pIsRead) noexcept
{
    isRead_ = std::make_shared<bool>(pIsRead);
    dirtyFlag_[7] = true;
}

const ::trantor::Date &Notification::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Notification::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Notification::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}

void Notification::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Notification::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "user_id",
        "actor_id",
        "object_type",
        "object_id",
        "action",
        "content",
        "is_read",
        "created_at"
    };
    return inCols;
}

void Notification::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getUserId())
        {
            binder << getValueOfUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getActorId())
        {
            binder << getValueOfActorId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getObjectType())
        {
            binder << getValueOfObjectType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getObjectId())
        {
            binder << getValueOfObjectId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getAction())
        {
            binder << getValueOfAction();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getContent())
        {
            binder << getValueOfContent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getIsRead())
        {
            binder << getValueOfIsRead();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Notification::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    if(dirtyFlag_[6])
    {
        ret.push_back(getColumnName(6));
    }
    if(dirtyFlag_[7])
    {
        ret.push_back(getColumnName(7));
    }
    if(dirtyFlag_[8])
    {
        ret.push_back(getColumnName(8));
    }
    return ret;
}

void Notification::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getUserId())
        {
            binder << getValueOfUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getActorId())
        {
            binder << getValueOfActorId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getObjectType())
        {
            binder << getValueOfObjectType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getObjectId())
        {
            binder << getValueOfObjectId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getAction())
        {
            binder << getValueOfAction();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getContent())
        {
            binder << getValueOfContent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getIsRead())
        {
            binder << getValueOfIsRead();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}
