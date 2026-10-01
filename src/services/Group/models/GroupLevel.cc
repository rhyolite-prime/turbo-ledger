/**
 *  GroupLevel.cc
 *
 *  See GroupLevel.h for the hand-authored-subset note.
 *
 */

#include "GroupLevel.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlGroupDb;

const std::string GroupLevel::Cols::_id = "\"id\"";
const std::string GroupLevel::Cols::_parent_level_id = "\"parent_level_id\"";
const std::string GroupLevel::Cols::_level_name = "\"level_name\"";
const std::string GroupLevel::Cols::_super_parent = "\"super_parent\"";
const std::string GroupLevel::Cols::_created_at = "\"created_at\"";
const std::string GroupLevel::primaryKeyName = "id";
const bool GroupLevel::hasPrimaryKey = true;
const std::string GroupLevel::tableName = "\"group_levels\"";

const std::vector<typename GroupLevel::MetaData> GroupLevel::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"parent_level_id","std::string","uuid",0,0,0,0},
{"level_name","std::string","character varying",50,0,0,1},
{"super_parent","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &GroupLevel::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
GroupLevel::GroupLevel(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["parent_level_id"].isNull())
        {
            parentLevelId_=std::make_shared<std::string>(r["parent_level_id"].as<std::string>());
        }
        if(!r["level_name"].isNull())
        {
            levelName_=std::make_shared<std::string>(r["level_name"].as<std::string>());
        }
        if(!r["super_parent"].isNull())
        {
            superParent_=std::make_shared<bool>(r["super_parent"].as<bool>());
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
        if(offset + 5 > r.size())
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
            parentLevelId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            levelName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            superParent_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 4;
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
const std::string &GroupLevel::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &GroupLevel::getId() const noexcept
{
    return id_;
}
void GroupLevel::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void GroupLevel::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename GroupLevel::PrimaryKeyType & GroupLevel::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &GroupLevel::getValueOfParentLevelId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(parentLevelId_)
        return *parentLevelId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &GroupLevel::getParentLevelId() const noexcept
{
    return parentLevelId_;
}
void GroupLevel::setParentLevelId(const std::string &pParentLevelId) noexcept
{
    parentLevelId_ = std::make_shared<std::string>(pParentLevelId);
    dirtyFlag_[1] = true;
}
void GroupLevel::setParentLevelId(std::string &&pParentLevelId) noexcept
{
    parentLevelId_ = std::make_shared<std::string>(std::move(pParentLevelId));
    dirtyFlag_[1] = true;
}
void GroupLevel::setParentLevelIdToNull() noexcept
{
    parentLevelId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &GroupLevel::getValueOfLevelName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(levelName_)
        return *levelName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &GroupLevel::getLevelName() const noexcept
{
    return levelName_;
}
void GroupLevel::setLevelName(const std::string &pLevelName) noexcept
{
    levelName_ = std::make_shared<std::string>(pLevelName);
    dirtyFlag_[2] = true;
}
void GroupLevel::setLevelName(std::string &&pLevelName) noexcept
{
    levelName_ = std::make_shared<std::string>(std::move(pLevelName));
    dirtyFlag_[2] = true;
}

const bool &GroupLevel::getValueOfSuperParent() const noexcept
{
    static const bool defaultValue = bool();
    if(superParent_)
        return *superParent_;
    return defaultValue;
}
const std::shared_ptr<bool> &GroupLevel::getSuperParent() const noexcept
{
    return superParent_;
}
void GroupLevel::setSuperParent(const bool &pSuperParent) noexcept
{
    superParent_ = std::make_shared<bool>(pSuperParent);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &GroupLevel::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &GroupLevel::getCreatedAt() const noexcept
{
    return createdAt_;
}
void GroupLevel::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[4] = true;
}

void GroupLevel::updateId(const uint64_t id)
{
}

const std::vector<std::string> &GroupLevel::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "parent_level_id",
        "level_name",
        "super_parent",
        "created_at"
    };
    return inCols;
}

void GroupLevel::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getParentLevelId())
        {
            binder << getValueOfParentLevelId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getLevelName())
        {
            binder << getValueOfLevelName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSuperParent())
        {
            binder << getValueOfSuperParent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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

const std::vector<std::string> GroupLevel::updateColumns() const
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
    return ret;
}

void GroupLevel::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getParentLevelId())
        {
            binder << getValueOfParentLevelId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getLevelName())
        {
            binder << getValueOfLevelName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSuperParent())
        {
            binder << getValueOfSuperParent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
