/**
 *  GroupRole.cc
 *
 *  See GroupRole.h for the hand-authored-subset note.
 *
 */

#include "GroupRole.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlGroupDb;

const std::string GroupRole::Cols::_id = "\"id\"";
const std::string GroupRole::Cols::_client_id = "\"client_id\"";
const std::string GroupRole::Cols::_group_id = "\"group_id\"";
const std::string GroupRole::Cols::_role_cv_id = "\"role_cv_id\"";
const std::string GroupRole::primaryKeyName = "id";
const bool GroupRole::hasPrimaryKey = true;
const std::string GroupRole::tableName = "\"group_roles\"";

const std::vector<typename GroupRole::MetaData> GroupRole::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"client_id","std::string","uuid",0,0,0,0},
{"group_id","std::string","uuid",0,0,0,0},
{"role_cv_id","std::string","uuid",0,0,0,0}
};
const std::string &GroupRole::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
GroupRole::GroupRole(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["group_id"].isNull())
        {
            groupId_=std::make_shared<std::string>(r["group_id"].as<std::string>());
        }
        if(!r["role_cv_id"].isNull())
        {
            roleCvId_=std::make_shared<std::string>(r["role_cv_id"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 4 > r.size())
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
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            groupId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            roleCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &GroupRole::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &GroupRole::getId() const noexcept
{
    return id_;
}
void GroupRole::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void GroupRole::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename GroupRole::PrimaryKeyType & GroupRole::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &GroupRole::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &GroupRole::getClientId() const noexcept
{
    return clientId_;
}
void GroupRole::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[1] = true;
}
void GroupRole::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[1] = true;
}
void GroupRole::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &GroupRole::getValueOfGroupId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(groupId_)
        return *groupId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &GroupRole::getGroupId() const noexcept
{
    return groupId_;
}
void GroupRole::setGroupId(const std::string &pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(pGroupId);
    dirtyFlag_[2] = true;
}
void GroupRole::setGroupId(std::string &&pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(std::move(pGroupId));
    dirtyFlag_[2] = true;
}
void GroupRole::setGroupIdToNull() noexcept
{
    groupId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &GroupRole::getValueOfRoleCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(roleCvId_)
        return *roleCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &GroupRole::getRoleCvId() const noexcept
{
    return roleCvId_;
}
void GroupRole::setRoleCvId(const std::string &pRoleCvId) noexcept
{
    roleCvId_ = std::make_shared<std::string>(pRoleCvId);
    dirtyFlag_[3] = true;
}
void GroupRole::setRoleCvId(std::string &&pRoleCvId) noexcept
{
    roleCvId_ = std::make_shared<std::string>(std::move(pRoleCvId));
    dirtyFlag_[3] = true;
}
void GroupRole::setRoleCvIdToNull() noexcept
{
    roleCvId_.reset();
    dirtyFlag_[3] = true;
}

void GroupRole::updateId(const uint64_t id)
{
}

const std::vector<std::string> &GroupRole::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "client_id",
        "group_id",
        "role_cv_id"
    };
    return inCols;
}

void GroupRole::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRoleCvId())
        {
            binder << getValueOfRoleCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> GroupRole::updateColumns() const
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
    return ret;
}

void GroupRole::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRoleCvId())
        {
            binder << getValueOfRoleCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
