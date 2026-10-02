/**
 *
 *  TaxGroupMapping.cc
 *
 *  See TaxGroupMapping.h for the hand-authored-subset note.
 *
 */

#include "TaxGroupMapping.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlOrganizationDb;

const std::string TaxGroupMapping::Cols::_id = "\"id\"";
const std::string TaxGroupMapping::Cols::_tax_group_id = "\"tax_group_id\"";
const std::string TaxGroupMapping::Cols::_tax_component_id = "\"tax_component_id\"";
const std::string TaxGroupMapping::Cols::_start_date = "\"start_date\"";
const std::string TaxGroupMapping::primaryKeyName = "id";
const bool TaxGroupMapping::hasPrimaryKey = true;
const std::string TaxGroupMapping::tableName = "\"tax_group_mapping\"";

const std::vector<typename TaxGroupMapping::MetaData> TaxGroupMapping::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"tax_group_id","std::string","uuid",0,0,0,1},
{"tax_component_id","std::string","uuid",0,0,0,1},
{"start_date","::trantor::Date","date",0,0,0,1}
};
const std::string &TaxGroupMapping::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
TaxGroupMapping::TaxGroupMapping(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["tax_group_id"].isNull())
        {
            taxGroupId_=std::make_shared<std::string>(r["tax_group_id"].as<std::string>());
        }
        if(!r["tax_component_id"].isNull())
        {
            taxComponentId_=std::make_shared<std::string>(r["tax_component_id"].as<std::string>());
        }
        if(!r["start_date"].isNull())
        {
            auto daysStr = r["start_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
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
            taxGroupId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            taxComponentId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
    }

}

const std::string &TaxGroupMapping::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxGroupMapping::getId() const noexcept
{
    return id_;
}
void TaxGroupMapping::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void TaxGroupMapping::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename TaxGroupMapping::PrimaryKeyType & TaxGroupMapping::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &TaxGroupMapping::getValueOfTaxGroupId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(taxGroupId_)
        return *taxGroupId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxGroupMapping::getTaxGroupId() const noexcept
{
    return taxGroupId_;
}
void TaxGroupMapping::setTaxGroupId(const std::string &pTaxGroupId) noexcept
{
    taxGroupId_ = std::make_shared<std::string>(pTaxGroupId);
    dirtyFlag_[1] = true;
}
void TaxGroupMapping::setTaxGroupId(std::string &&pTaxGroupId) noexcept
{
    taxGroupId_ = std::make_shared<std::string>(std::move(pTaxGroupId));
    dirtyFlag_[1] = true;
}

const std::string &TaxGroupMapping::getValueOfTaxComponentId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(taxComponentId_)
        return *taxComponentId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxGroupMapping::getTaxComponentId() const noexcept
{
    return taxComponentId_;
}
void TaxGroupMapping::setTaxComponentId(const std::string &pTaxComponentId) noexcept
{
    taxComponentId_ = std::make_shared<std::string>(pTaxComponentId);
    dirtyFlag_[2] = true;
}
void TaxGroupMapping::setTaxComponentId(std::string &&pTaxComponentId) noexcept
{
    taxComponentId_ = std::make_shared<std::string>(std::move(pTaxComponentId));
    dirtyFlag_[2] = true;
}

const ::trantor::Date &TaxGroupMapping::getValueOfStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDate_)
        return *startDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &TaxGroupMapping::getStartDate() const noexcept
{
    return startDate_;
}
void TaxGroupMapping::setStartDate(const ::trantor::Date &pStartDate) noexcept
{
    startDate_ = std::make_shared<::trantor::Date>(pStartDate.roundDay());
    dirtyFlag_[3] = true;
}

void TaxGroupMapping::updateId(const uint64_t id)
{
}

const std::vector<std::string> &TaxGroupMapping::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "tax_group_id",
        "tax_component_id",
        "start_date"
    };
    return inCols;
}

void TaxGroupMapping::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTaxGroupId())
        {
            binder << getValueOfTaxGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTaxComponentId())
        {
            binder << getValueOfTaxComponentId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> TaxGroupMapping::updateColumns() const
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

void TaxGroupMapping::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTaxGroupId())
        {
            binder << getValueOfTaxGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTaxComponentId())
        {
            binder << getValueOfTaxComponentId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
}

