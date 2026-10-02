/**
 *  Template.cc
 *
 *  See Template.h for the hand-authored-subset note.
 *
 */

#include "Template.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlTemplateDb;

const std::string Template::Cols::_id = "\"id\"";
const std::string Template::Cols::_name = "\"name\"";
const std::string Template::Cols::_text = "\"text\"";
const std::string Template::Cols::_entity = "\"entity\"";
const std::string Template::Cols::_template_type = "\"template_type\"";
const std::string Template::Cols::_created_at = "\"created_at\"";
const std::string Template::Cols::_updated_at = "\"updated_at\"";
const std::string Template::primaryKeyName = "id";
const bool Template::hasPrimaryKey = true;
const std::string Template::tableName = "\"templates\"";

const std::vector<typename Template::MetaData> Template::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",200,0,0,1},
{"text","std::string","text",0,0,0,1},
{"entity","std::string","character varying",100,0,0,1},
{"template_type","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Template::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Template::Template(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["text"].isNull())
        {
            text_=std::make_shared<std::string>(r["text"].as<std::string>());
        }
        if(!r["entity"].isNull())
        {
            entity_=std::make_shared<std::string>(r["entity"].as<std::string>());
        }
        if(!r["template_type"].isNull())
        {
            templateType_=std::make_shared<std::string>(r["template_type"].as<std::string>());
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
        if(!r["updated_at"].isNull())
        {
            auto timeStr = r["updated_at"].as<std::string>();
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 7 > r.size())
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
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            text_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            entity_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            templateType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
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
        index = offset + 6;
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &Template::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Template::getId() const noexcept
{
    return id_;
}
void Template::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Template::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Template::PrimaryKeyType & Template::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Template::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Template::getName() const noexcept
{
    return name_;
}
void Template::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void Template::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const std::string &Template::getValueOfText() const noexcept
{
    static const std::string defaultValue = std::string();
    if(text_)
        return *text_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Template::getText() const noexcept
{
    return text_;
}
void Template::setText(const std::string &pText) noexcept
{
    text_ = std::make_shared<std::string>(pText);
    dirtyFlag_[2] = true;
}
void Template::setText(std::string &&pText) noexcept
{
    text_ = std::make_shared<std::string>(std::move(pText));
    dirtyFlag_[2] = true;
}

const std::string &Template::getValueOfEntity() const noexcept
{
    static const std::string defaultValue = std::string();
    if(entity_)
        return *entity_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Template::getEntity() const noexcept
{
    return entity_;
}
void Template::setEntity(const std::string &pEntity) noexcept
{
    entity_ = std::make_shared<std::string>(pEntity);
    dirtyFlag_[3] = true;
}
void Template::setEntity(std::string &&pEntity) noexcept
{
    entity_ = std::make_shared<std::string>(std::move(pEntity));
    dirtyFlag_[3] = true;
}

const std::string &Template::getValueOfTemplateType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(templateType_)
        return *templateType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Template::getTemplateType() const noexcept
{
    return templateType_;
}
void Template::setTemplateType(const std::string &pTemplateType) noexcept
{
    templateType_ = std::make_shared<std::string>(pTemplateType);
    dirtyFlag_[4] = true;
}
void Template::setTemplateType(std::string &&pTemplateType) noexcept
{
    templateType_ = std::make_shared<std::string>(std::move(pTemplateType));
    dirtyFlag_[4] = true;
}

const ::trantor::Date &Template::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Template::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Template::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

const ::trantor::Date &Template::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Template::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void Template::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[6] = true;
}

void Template::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Template::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "text",
        "entity",
        "template_type",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void Template::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getText())
        {
            binder << getValueOfText();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getEntity())
        {
            binder << getValueOfEntity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTemplateType())
        {
            binder << getValueOfTemplateType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Template::updateColumns() const
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
    return ret;
}

void Template::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getText())
        {
            binder << getValueOfText();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getEntity())
        {
            binder << getValueOfEntity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTemplateType())
        {
            binder << getValueOfTemplateType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}
