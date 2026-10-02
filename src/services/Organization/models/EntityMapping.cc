/**
 *
 *  EntityMapping.cc
 *
 *  See EntityMapping.h for the hand-authored-subset note.
 *
 */

#include "EntityMapping.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlOrganizationDb;

const std::string EntityMapping::Cols::_id = "\"id\"";
const std::string EntityMapping::Cols::_relation_id = "\"relation_id\"";
const std::string EntityMapping::Cols::_from_id = "\"from_id\"";
const std::string EntityMapping::Cols::_to_id = "\"to_id\"";
const std::string EntityMapping::Cols::_created_at = "\"created_at\"";
const std::string EntityMapping::primaryKeyName = "id";
const bool EntityMapping::hasPrimaryKey = true;
const std::string EntityMapping::tableName = "\"entity_mapping\"";

const std::vector<typename EntityMapping::MetaData> EntityMapping::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"relation_id","std::string","uuid",0,0,0,1},
{"from_id","std::string","character varying",80,0,0,1},
{"to_id","std::string","character varying",80,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &EntityMapping::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
EntityMapping::EntityMapping(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["relation_id"].isNull())
        {
            relationId_=std::make_shared<std::string>(r["relation_id"].as<std::string>());
        }
        if(!r["from_id"].isNull())
        {
            fromId_=std::make_shared<std::string>(r["from_id"].as<std::string>());
        }
        if(!r["to_id"].isNull())
        {
            toId_=std::make_shared<std::string>(r["to_id"].as<std::string>());
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
            relationId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            fromId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            toId_=std::make_shared<std::string>(r[index].as<std::string>());
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

const std::string &EntityMapping::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityMapping::getId() const noexcept
{
    return id_;
}
void EntityMapping::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void EntityMapping::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename EntityMapping::PrimaryKeyType & EntityMapping::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &EntityMapping::getValueOfRelationId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(relationId_)
        return *relationId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityMapping::getRelationId() const noexcept
{
    return relationId_;
}
void EntityMapping::setRelationId(const std::string &pRelationId) noexcept
{
    relationId_ = std::make_shared<std::string>(pRelationId);
    dirtyFlag_[1] = true;
}
void EntityMapping::setRelationId(std::string &&pRelationId) noexcept
{
    relationId_ = std::make_shared<std::string>(std::move(pRelationId));
    dirtyFlag_[1] = true;
}

const std::string &EntityMapping::getValueOfFromId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromId_)
        return *fromId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityMapping::getFromId() const noexcept
{
    return fromId_;
}
void EntityMapping::setFromId(const std::string &pFromId) noexcept
{
    fromId_ = std::make_shared<std::string>(pFromId);
    dirtyFlag_[2] = true;
}
void EntityMapping::setFromId(std::string &&pFromId) noexcept
{
    fromId_ = std::make_shared<std::string>(std::move(pFromId));
    dirtyFlag_[2] = true;
}

const std::string &EntityMapping::getValueOfToId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toId_)
        return *toId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityMapping::getToId() const noexcept
{
    return toId_;
}
void EntityMapping::setToId(const std::string &pToId) noexcept
{
    toId_ = std::make_shared<std::string>(pToId);
    dirtyFlag_[3] = true;
}
void EntityMapping::setToId(std::string &&pToId) noexcept
{
    toId_ = std::make_shared<std::string>(std::move(pToId));
    dirtyFlag_[3] = true;
}

const ::trantor::Date &EntityMapping::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &EntityMapping::getCreatedAt() const noexcept
{
    return createdAt_;
}
void EntityMapping::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[4] = true;
}

void EntityMapping::updateId(const uint64_t id)
{
}

const std::vector<std::string> &EntityMapping::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "relation_id",
        "from_id",
        "to_id",
        "created_at"
    };
    return inCols;
}

void EntityMapping::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRelationId())
        {
            binder << getValueOfRelationId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getFromId())
        {
            binder << getValueOfFromId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getToId())
        {
            binder << getValueOfToId();
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

const std::vector<std::string> EntityMapping::updateColumns() const
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

void EntityMapping::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRelationId())
        {
            binder << getValueOfRelationId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getFromId())
        {
            binder << getValueOfFromId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getToId())
        {
            binder << getValueOfToId();
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

