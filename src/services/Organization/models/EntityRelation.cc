/**
 *
 *  EntityRelation.cc
 *
 *  See EntityRelation.h for the hand-authored-subset note.
 *
 */

#include "EntityRelation.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlOrganizationDb;

const std::string EntityRelation::Cols::_id = "\"id\"";
const std::string EntityRelation::Cols::_code_from = "\"code_from\"";
const std::string EntityRelation::Cols::_code_to = "\"code_to\"";
const std::string EntityRelation::Cols::_mapping_types = "\"mapping_types\"";
const std::string EntityRelation::primaryKeyName = "id";
const bool EntityRelation::hasPrimaryKey = true;
const std::string EntityRelation::tableName = "\"entity_relation\"";

const std::vector<typename EntityRelation::MetaData> EntityRelation::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"code_from","std::string","character varying",100,0,0,1},
{"code_to","std::string","character varying",100,0,0,1},
{"mapping_types","std::string","character varying",40,0,0,1}
};
const std::string &EntityRelation::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
EntityRelation::EntityRelation(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["code_from"].isNull())
        {
            codeFrom_=std::make_shared<std::string>(r["code_from"].as<std::string>());
        }
        if(!r["code_to"].isNull())
        {
            codeTo_=std::make_shared<std::string>(r["code_to"].as<std::string>());
        }
        if(!r["mapping_types"].isNull())
        {
            mappingTypes_=std::make_shared<std::string>(r["mapping_types"].as<std::string>());
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
            codeFrom_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            codeTo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            mappingTypes_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

const std::string &EntityRelation::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityRelation::getId() const noexcept
{
    return id_;
}
void EntityRelation::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void EntityRelation::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename EntityRelation::PrimaryKeyType & EntityRelation::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &EntityRelation::getValueOfCodeFrom() const noexcept
{
    static const std::string defaultValue = std::string();
    if(codeFrom_)
        return *codeFrom_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityRelation::getCodeFrom() const noexcept
{
    return codeFrom_;
}
void EntityRelation::setCodeFrom(const std::string &pCodeFrom) noexcept
{
    codeFrom_ = std::make_shared<std::string>(pCodeFrom);
    dirtyFlag_[1] = true;
}
void EntityRelation::setCodeFrom(std::string &&pCodeFrom) noexcept
{
    codeFrom_ = std::make_shared<std::string>(std::move(pCodeFrom));
    dirtyFlag_[1] = true;
}

const std::string &EntityRelation::getValueOfCodeTo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(codeTo_)
        return *codeTo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityRelation::getCodeTo() const noexcept
{
    return codeTo_;
}
void EntityRelation::setCodeTo(const std::string &pCodeTo) noexcept
{
    codeTo_ = std::make_shared<std::string>(pCodeTo);
    dirtyFlag_[2] = true;
}
void EntityRelation::setCodeTo(std::string &&pCodeTo) noexcept
{
    codeTo_ = std::make_shared<std::string>(std::move(pCodeTo));
    dirtyFlag_[2] = true;
}

const std::string &EntityRelation::getValueOfMappingTypes() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mappingTypes_)
        return *mappingTypes_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EntityRelation::getMappingTypes() const noexcept
{
    return mappingTypes_;
}
void EntityRelation::setMappingTypes(const std::string &pMappingTypes) noexcept
{
    mappingTypes_ = std::make_shared<std::string>(pMappingTypes);
    dirtyFlag_[3] = true;
}
void EntityRelation::setMappingTypes(std::string &&pMappingTypes) noexcept
{
    mappingTypes_ = std::make_shared<std::string>(std::move(pMappingTypes));
    dirtyFlag_[3] = true;
}

void EntityRelation::updateId(const uint64_t id)
{
}

const std::vector<std::string> &EntityRelation::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "code_from",
        "code_to",
        "mapping_types"
    };
    return inCols;
}

void EntityRelation::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCodeFrom())
        {
            binder << getValueOfCodeFrom();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCodeTo())
        {
            binder << getValueOfCodeTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMappingTypes())
        {
            binder << getValueOfMappingTypes();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> EntityRelation::updateColumns() const
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

void EntityRelation::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCodeFrom())
        {
            binder << getValueOfCodeFrom();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCodeTo())
        {
            binder << getValueOfCodeTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMappingTypes())
        {
            binder << getValueOfMappingTypes();
        }
        else
        {
            binder << nullptr;
        }
    }
}

