/**
 *  CollateralManagement.cc
 *
 *  See CollateralManagement.h for the hand-authored-subset note.
 *
 */

#include "CollateralManagement.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlCustomerDb;

const std::string CollateralManagement::Cols::_id = "\"id\"";
const std::string CollateralManagement::Cols::_name = "\"name\"";
const std::string CollateralManagement::Cols::_quality = "\"quality\"";
const std::string CollateralManagement::Cols::_base_price = "\"base_price\"";
const std::string CollateralManagement::Cols::_currency_code = "\"currency_code\"";
const std::string CollateralManagement::Cols::_pct_to_base = "\"pct_to_base\"";
const std::string CollateralManagement::Cols::_unit_type = "\"unit_type\"";
const std::string CollateralManagement::Cols::_created_by = "\"created_by\"";
const std::string CollateralManagement::Cols::_created_at = "\"created_at\"";
const std::string CollateralManagement::Cols::_updated_by = "\"updated_by\"";
const std::string CollateralManagement::Cols::_updated_at = "\"updated_at\"";
const std::string CollateralManagement::primaryKeyName = "id";
const bool CollateralManagement::hasPrimaryKey = true;
const std::string CollateralManagement::tableName = "\"collateral_management\"";

const std::vector<typename CollateralManagement::MetaData> CollateralManagement::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",200,0,0,1},
{"quality","std::string","character varying",200,0,0,0},
{"base_price","std::string","numeric",0,0,0,0},
{"currency_code","std::string","character varying",3,0,0,0},
{"pct_to_base","std::string","numeric",0,0,0,0},
{"unit_type","std::string","character varying",200,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,0},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,0}
};
const std::string &CollateralManagement::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
CollateralManagement::CollateralManagement(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["quality"].isNull())
        {
            quality_=std::make_shared<std::string>(r["quality"].as<std::string>());
        }
        if(!r["base_price"].isNull())
        {
            basePrice_=std::make_shared<std::string>(r["base_price"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["pct_to_base"].isNull())
        {
            pctToBase_=std::make_shared<std::string>(r["pct_to_base"].as<std::string>());
        }
        if(!r["unit_type"].isNull())
        {
            unitType_=std::make_shared<std::string>(r["unit_type"].as<std::string>());
        }
        if(!r["created_by"].isNull())
        {
            createdBy_=std::make_shared<std::string>(r["created_by"].as<std::string>());
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
        if(!r["updated_by"].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r["updated_by"].as<std::string>());
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
        if(offset + 11 > r.size())
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
            quality_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            basePrice_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            pctToBase_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            unitType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
        index = offset + 9;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
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
const std::string &CollateralManagement::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getId() const noexcept
{
    return id_;
}
void CollateralManagement::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void CollateralManagement::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename CollateralManagement::PrimaryKeyType & CollateralManagement::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &CollateralManagement::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getName() const noexcept
{
    return name_;
}
void CollateralManagement::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void CollateralManagement::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const std::string &CollateralManagement::getValueOfQuality() const noexcept
{
    static const std::string defaultValue = std::string();
    if(quality_)
        return *quality_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getQuality() const noexcept
{
    return quality_;
}
void CollateralManagement::setQuality(const std::string &pQuality) noexcept
{
    quality_ = std::make_shared<std::string>(pQuality);
    dirtyFlag_[2] = true;
}
void CollateralManagement::setQuality(std::string &&pQuality) noexcept
{
    quality_ = std::make_shared<std::string>(std::move(pQuality));
    dirtyFlag_[2] = true;
}
void CollateralManagement::setQualityToNull() noexcept
{
    quality_.reset();
    dirtyFlag_[2] = true;
}

const std::string &CollateralManagement::getValueOfBasePrice() const noexcept
{
    static const std::string defaultValue = std::string();
    if(basePrice_)
        return *basePrice_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getBasePrice() const noexcept
{
    return basePrice_;
}
void CollateralManagement::setBasePrice(const std::string &pBasePrice) noexcept
{
    basePrice_ = std::make_shared<std::string>(pBasePrice);
    dirtyFlag_[3] = true;
}
void CollateralManagement::setBasePrice(std::string &&pBasePrice) noexcept
{
    basePrice_ = std::make_shared<std::string>(std::move(pBasePrice));
    dirtyFlag_[3] = true;
}
void CollateralManagement::setBasePriceToNull() noexcept
{
    basePrice_.reset();
    dirtyFlag_[3] = true;
}

const std::string &CollateralManagement::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void CollateralManagement::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[4] = true;
}
void CollateralManagement::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[4] = true;
}
void CollateralManagement::setCurrencyCodeToNull() noexcept
{
    currencyCode_.reset();
    dirtyFlag_[4] = true;
}

const std::string &CollateralManagement::getValueOfPctToBase() const noexcept
{
    static const std::string defaultValue = std::string();
    if(pctToBase_)
        return *pctToBase_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getPctToBase() const noexcept
{
    return pctToBase_;
}
void CollateralManagement::setPctToBase(const std::string &pPctToBase) noexcept
{
    pctToBase_ = std::make_shared<std::string>(pPctToBase);
    dirtyFlag_[5] = true;
}
void CollateralManagement::setPctToBase(std::string &&pPctToBase) noexcept
{
    pctToBase_ = std::make_shared<std::string>(std::move(pPctToBase));
    dirtyFlag_[5] = true;
}
void CollateralManagement::setPctToBaseToNull() noexcept
{
    pctToBase_.reset();
    dirtyFlag_[5] = true;
}

const std::string &CollateralManagement::getValueOfUnitType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(unitType_)
        return *unitType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getUnitType() const noexcept
{
    return unitType_;
}
void CollateralManagement::setUnitType(const std::string &pUnitType) noexcept
{
    unitType_ = std::make_shared<std::string>(pUnitType);
    dirtyFlag_[6] = true;
}
void CollateralManagement::setUnitType(std::string &&pUnitType) noexcept
{
    unitType_ = std::make_shared<std::string>(std::move(pUnitType));
    dirtyFlag_[6] = true;
}
void CollateralManagement::setUnitTypeToNull() noexcept
{
    unitType_.reset();
    dirtyFlag_[6] = true;
}

const std::string &CollateralManagement::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getCreatedBy() const noexcept
{
    return createdBy_;
}
void CollateralManagement::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[7] = true;
}
void CollateralManagement::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[7] = true;
}
void CollateralManagement::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[7] = true;
}

const ::trantor::Date &CollateralManagement::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &CollateralManagement::getCreatedAt() const noexcept
{
    return createdAt_;
}
void CollateralManagement::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}
void CollateralManagement::setCreatedAtToNull() noexcept
{
    createdAt_.reset();
    dirtyFlag_[8] = true;
}

const std::string &CollateralManagement::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CollateralManagement::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void CollateralManagement::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[9] = true;
}
void CollateralManagement::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[9] = true;
}
void CollateralManagement::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[9] = true;
}

const ::trantor::Date &CollateralManagement::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &CollateralManagement::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void CollateralManagement::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[10] = true;
}
void CollateralManagement::setUpdatedAtToNull() noexcept
{
    updatedAt_.reset();
    dirtyFlag_[10] = true;
}

void CollateralManagement::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CollateralManagement::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "quality",
        "base_price",
        "currency_code",
        "pct_to_base",
        "unit_type",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void CollateralManagement::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getQuality())
        {
            binder << getValueOfQuality();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getBasePrice())
        {
            binder << getValueOfBasePrice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getPctToBase())
        {
            binder << getValueOfPctToBase();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getUnitType())
        {
            binder << getValueOfUnitType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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
    if(dirtyFlag_[9])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
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

const std::vector<std::string> CollateralManagement::updateColumns() const
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
    if(dirtyFlag_[9])
    {
        ret.push_back(getColumnName(9));
    }
    if(dirtyFlag_[10])
    {
        ret.push_back(getColumnName(10));
    }
    return ret;
}

void CollateralManagement::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getQuality())
        {
            binder << getValueOfQuality();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getBasePrice())
        {
            binder << getValueOfBasePrice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getPctToBase())
        {
            binder << getValueOfPctToBase();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getUnitType())
        {
            binder << getValueOfUnitType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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
    if(dirtyFlag_[9])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
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
