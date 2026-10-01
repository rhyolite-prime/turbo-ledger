/**
 *  LoanCollateral.cc
 *
 *  See LoanCollateral.h for the hand-authored-subset note.
 *
 */

#include "LoanCollateral.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanCollateral::Cols::_id = "\"id\"";
const std::string LoanCollateral::Cols::_loan_id = "\"loan_id\"";
const std::string LoanCollateral::Cols::_collateral_type_id = "\"collateral_type_id\"";
const std::string LoanCollateral::Cols::_value = "\"value\"";
const std::string LoanCollateral::Cols::_description = "\"description\"";
const std::string LoanCollateral::Cols::_created_at = "\"created_at\"";
const std::string LoanCollateral::primaryKeyName = "id";
const bool LoanCollateral::hasPrimaryKey = true;
const std::string LoanCollateral::tableName = "\"loan_collateral\"";

const std::vector<typename LoanCollateral::MetaData> LoanCollateral::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"collateral_type_id","std::string","character varying",40,0,0,1},
{"value","std::string","numeric",0,0,0,0},
{"description","std::string","text",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanCollateral::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanCollateral::LoanCollateral(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["loan_id"].isNull())
        {
            loanId_=std::make_shared<std::string>(r["loan_id"].as<std::string>());
        }
        if(!r["collateral_type_id"].isNull())
        {
            collateralTypeId_=std::make_shared<std::string>(r["collateral_type_id"].as<std::string>());
        }
        if(!r["value"].isNull())
        {
            value_=std::make_shared<std::string>(r["value"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
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
        if(offset + 6 > r.size())
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
            loanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            collateralTypeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            value_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
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
    }

}
const std::string &LoanCollateral::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCollateral::getId() const noexcept
{
    return id_;
}
void LoanCollateral::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanCollateral::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanCollateral::PrimaryKeyType & LoanCollateral::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanCollateral::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCollateral::getLoanId() const noexcept
{
    return loanId_;
}
void LoanCollateral::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanCollateral::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanCollateral::getValueOfCollateralTypeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(collateralTypeId_)
        return *collateralTypeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCollateral::getCollateralTypeId() const noexcept
{
    return collateralTypeId_;
}
void LoanCollateral::setCollateralTypeId(const std::string &pCollateralTypeId) noexcept
{
    collateralTypeId_ = std::make_shared<std::string>(pCollateralTypeId);
    dirtyFlag_[2] = true;
}
void LoanCollateral::setCollateralTypeId(std::string &&pCollateralTypeId) noexcept
{
    collateralTypeId_ = std::make_shared<std::string>(std::move(pCollateralTypeId));
    dirtyFlag_[2] = true;
}

const std::string &LoanCollateral::getValueOfValue() const noexcept
{
    static const std::string defaultValue = std::string();
    if(value_)
        return *value_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCollateral::getValue() const noexcept
{
    return value_;
}
void LoanCollateral::setValue(const std::string &pValue) noexcept
{
    value_ = std::make_shared<std::string>(pValue);
    dirtyFlag_[3] = true;
}
void LoanCollateral::setValue(std::string &&pValue) noexcept
{
    value_ = std::make_shared<std::string>(std::move(pValue));
    dirtyFlag_[3] = true;
}
void LoanCollateral::setValueToNull() noexcept
{
    value_.reset();
    dirtyFlag_[3] = true;
}

const std::string &LoanCollateral::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCollateral::getDescription() const noexcept
{
    return description_;
}
void LoanCollateral::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[4] = true;
}
void LoanCollateral::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[4] = true;
}
void LoanCollateral::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[4] = true;
}

const ::trantor::Date &LoanCollateral::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanCollateral::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanCollateral::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

void LoanCollateral::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanCollateral::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "collateral_type_id",
        "value",
        "description",
        "created_at"
    };
    return inCols;
}

void LoanCollateral::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCollateralTypeId())
        {
            binder << getValueOfCollateralTypeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getValue())
        {
            binder << getValueOfValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
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
}

const std::vector<std::string> LoanCollateral::updateColumns() const
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
    return ret;
}

void LoanCollateral::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCollateralTypeId())
        {
            binder << getValueOfCollateralTypeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getValue())
        {
            binder << getValueOfValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
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
}
