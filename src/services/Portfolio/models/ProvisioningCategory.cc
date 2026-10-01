/**
 *  ProvisioningCategory.cc
 *
 *  See ProvisioningCategory.h for the hand-authored-subset note.
 *
 */

#include "ProvisioningCategory.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ProvisioningCategory::Cols::_id = "\"id\"";
const std::string ProvisioningCategory::Cols::_category_name = "\"category_name\"";
const std::string ProvisioningCategory::Cols::_category_description = "\"category_description\"";
const std::string ProvisioningCategory::Cols::_created_at = "\"created_at\"";
const std::string ProvisioningCategory::primaryKeyName = "id";
const bool ProvisioningCategory::hasPrimaryKey = true;
const std::string ProvisioningCategory::tableName = "\"provisioning_category\"";

const std::vector<typename ProvisioningCategory::MetaData> ProvisioningCategory::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"category_name","std::string","character varying",100,0,0,1},
{"category_description","std::string","text",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ProvisioningCategory::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ProvisioningCategory::ProvisioningCategory(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["category_name"].isNull())
        {
            categoryName_=std::make_shared<std::string>(r["category_name"].as<std::string>());
        }
        if(!r["category_description"].isNull())
        {
            categoryDescription_=std::make_shared<std::string>(r["category_description"].as<std::string>());
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
            categoryName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            categoryDescription_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
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
const std::string &ProvisioningCategory::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCategory::getId() const noexcept
{
    return id_;
}
void ProvisioningCategory::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ProvisioningCategory::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ProvisioningCategory::PrimaryKeyType & ProvisioningCategory::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ProvisioningCategory::getValueOfCategoryName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(categoryName_)
        return *categoryName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCategory::getCategoryName() const noexcept
{
    return categoryName_;
}
void ProvisioningCategory::setCategoryName(const std::string &pCategoryName) noexcept
{
    categoryName_ = std::make_shared<std::string>(pCategoryName);
    dirtyFlag_[1] = true;
}
void ProvisioningCategory::setCategoryName(std::string &&pCategoryName) noexcept
{
    categoryName_ = std::make_shared<std::string>(std::move(pCategoryName));
    dirtyFlag_[1] = true;
}

const std::string &ProvisioningCategory::getValueOfCategoryDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(categoryDescription_)
        return *categoryDescription_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCategory::getCategoryDescription() const noexcept
{
    return categoryDescription_;
}
void ProvisioningCategory::setCategoryDescription(const std::string &pCategoryDescription) noexcept
{
    categoryDescription_ = std::make_shared<std::string>(pCategoryDescription);
    dirtyFlag_[2] = true;
}
void ProvisioningCategory::setCategoryDescription(std::string &&pCategoryDescription) noexcept
{
    categoryDescription_ = std::make_shared<std::string>(std::move(pCategoryDescription));
    dirtyFlag_[2] = true;
}
void ProvisioningCategory::setCategoryDescriptionToNull() noexcept
{
    categoryDescription_.reset();
    dirtyFlag_[2] = true;
}

const ::trantor::Date &ProvisioningCategory::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ProvisioningCategory::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ProvisioningCategory::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[3] = true;
}

void ProvisioningCategory::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ProvisioningCategory::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "category_name",
        "category_description",
        "created_at"
    };
    return inCols;
}

void ProvisioningCategory::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCategoryName())
        {
            binder << getValueOfCategoryName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCategoryDescription())
        {
            binder << getValueOfCategoryDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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

const std::vector<std::string> ProvisioningCategory::updateColumns() const
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

void ProvisioningCategory::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCategoryName())
        {
            binder << getValueOfCategoryName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCategoryDescription())
        {
            binder << getValueOfCategoryDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
