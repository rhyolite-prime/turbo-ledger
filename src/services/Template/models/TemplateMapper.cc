/**
 *  TemplateMapper.cc
 *
 *  See TemplateMapper.h for the hand-authored-subset note.
 *
 */

#include "TemplateMapper.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlTemplateDb;

const std::string TemplateMapper::Cols::_id = "\"id\"";
const std::string TemplateMapper::Cols::_template_id = "\"template_id\"";
const std::string TemplateMapper::Cols::_mapper_key = "\"mapper_key\"";
const std::string TemplateMapper::Cols::_mapper_order = "\"mapper_order\"";
const std::string TemplateMapper::Cols::_created_at = "\"created_at\"";
const std::string TemplateMapper::primaryKeyName = "id";
const bool TemplateMapper::hasPrimaryKey = true;
const std::string TemplateMapper::tableName = "\"template_mappers\"";

const std::vector<typename TemplateMapper::MetaData> TemplateMapper::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"template_id","std::string","uuid",0,0,0,1},
{"mapper_key","std::string","character varying",100,0,0,1},
{"mapper_order","int32_t","integer",4,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &TemplateMapper::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
TemplateMapper::TemplateMapper(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["template_id"].isNull())
        {
            templateId_=std::make_shared<std::string>(r["template_id"].as<std::string>());
        }
        if(!r["mapper_key"].isNull())
        {
            mapperKey_=std::make_shared<std::string>(r["mapper_key"].as<std::string>());
        }
        if(!r["mapper_order"].isNull())
        {
            mapperOrder_=std::make_shared<int32_t>(r["mapper_order"].as<int32_t>());
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
            templateId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            mapperKey_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            mapperOrder_=std::make_shared<int32_t>(r[index].as<int32_t>());
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
const std::string &TemplateMapper::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TemplateMapper::getId() const noexcept
{
    return id_;
}
void TemplateMapper::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void TemplateMapper::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename TemplateMapper::PrimaryKeyType & TemplateMapper::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &TemplateMapper::getValueOfTemplateId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(templateId_)
        return *templateId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TemplateMapper::getTemplateId() const noexcept
{
    return templateId_;
}
void TemplateMapper::setTemplateId(const std::string &pTemplateId) noexcept
{
    templateId_ = std::make_shared<std::string>(pTemplateId);
    dirtyFlag_[1] = true;
}
void TemplateMapper::setTemplateId(std::string &&pTemplateId) noexcept
{
    templateId_ = std::make_shared<std::string>(std::move(pTemplateId));
    dirtyFlag_[1] = true;
}

const std::string &TemplateMapper::getValueOfMapperKey() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mapperKey_)
        return *mapperKey_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TemplateMapper::getMapperKey() const noexcept
{
    return mapperKey_;
}
void TemplateMapper::setMapperKey(const std::string &pMapperKey) noexcept
{
    mapperKey_ = std::make_shared<std::string>(pMapperKey);
    dirtyFlag_[2] = true;
}
void TemplateMapper::setMapperKey(std::string &&pMapperKey) noexcept
{
    mapperKey_ = std::make_shared<std::string>(std::move(pMapperKey));
    dirtyFlag_[2] = true;
}

const int32_t &TemplateMapper::getValueOfMapperOrder() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(mapperOrder_)
        return *mapperOrder_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &TemplateMapper::getMapperOrder() const noexcept
{
    return mapperOrder_;
}
void TemplateMapper::setMapperOrder(const int32_t &pMapperOrder) noexcept
{
    mapperOrder_ = std::make_shared<int32_t>(pMapperOrder);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &TemplateMapper::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &TemplateMapper::getCreatedAt() const noexcept
{
    return createdAt_;
}
void TemplateMapper::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[4] = true;
}

void TemplateMapper::updateId(const uint64_t id)
{
}

const std::vector<std::string> &TemplateMapper::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "template_id",
        "mapper_key",
        "mapper_order",
        "created_at"
    };
    return inCols;
}

void TemplateMapper::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTemplateId())
        {
            binder << getValueOfTemplateId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getMapperKey())
        {
            binder << getValueOfMapperKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMapperOrder())
        {
            binder << getValueOfMapperOrder();
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

const std::vector<std::string> TemplateMapper::updateColumns() const
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

void TemplateMapper::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTemplateId())
        {
            binder << getValueOfTemplateId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getMapperKey())
        {
            binder << getValueOfMapperKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMapperOrder())
        {
            binder << getValueOfMapperOrder();
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
