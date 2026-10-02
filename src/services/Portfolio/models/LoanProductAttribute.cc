/**
 *  LoanProductAttribute.cc
 *
 *  See LoanProductAttribute.h for the hand-authored-subset note.
 *
 */

#include "LoanProductAttribute.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanProductAttribute::Cols::_id = "\"id\"";
const std::string LoanProductAttribute::Cols::_loan_product_id = "\"loan_product_id\"";
const std::string LoanProductAttribute::Cols::_attribute_key = "\"attribute_key\"";
const std::string LoanProductAttribute::Cols::_attribute_value = "\"attribute_value\"";
const std::string LoanProductAttribute::Cols::_created_at = "\"created_at\"";
const std::string LoanProductAttribute::primaryKeyName = "id";
const bool LoanProductAttribute::hasPrimaryKey = true;
const std::string LoanProductAttribute::tableName = "\"loan_product_attribute\"";

const std::vector<typename LoanProductAttribute::MetaData> LoanProductAttribute::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_product_id","std::string","uuid",0,0,0,1},
{"attribute_key","std::string","character varying",100,0,0,1},
{"attribute_value","std::string","text",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanProductAttribute::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanProductAttribute::LoanProductAttribute(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["loan_product_id"].isNull())
        {
            loanProductId_=std::make_shared<std::string>(r["loan_product_id"].as<std::string>());
        }
        if(!r["attribute_key"].isNull())
        {
            attributeKey_=std::make_shared<std::string>(r["attribute_key"].as<std::string>());
        }
        if(!r["attribute_value"].isNull())
        {
            attributeValue_=std::make_shared<std::string>(r["attribute_value"].as<std::string>());
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
            loanProductId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            attributeKey_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            attributeValue_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &LoanProductAttribute::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductAttribute::getId() const noexcept
{
    return id_;
}
void LoanProductAttribute::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanProductAttribute::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanProductAttribute::PrimaryKeyType & LoanProductAttribute::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanProductAttribute::getValueOfLoanProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanProductId_)
        return *loanProductId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductAttribute::getLoanProductId() const noexcept
{
    return loanProductId_;
}
void LoanProductAttribute::setLoanProductId(const std::string &pLoanProductId) noexcept
{
    loanProductId_ = std::make_shared<std::string>(pLoanProductId);
    dirtyFlag_[1] = true;
}
void LoanProductAttribute::setLoanProductId(std::string &&pLoanProductId) noexcept
{
    loanProductId_ = std::make_shared<std::string>(std::move(pLoanProductId));
    dirtyFlag_[1] = true;
}

const std::string &LoanProductAttribute::getValueOfAttributeKey() const noexcept
{
    static const std::string defaultValue = std::string();
    if(attributeKey_)
        return *attributeKey_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductAttribute::getAttributeKey() const noexcept
{
    return attributeKey_;
}
void LoanProductAttribute::setAttributeKey(const std::string &pAttributeKey) noexcept
{
    attributeKey_ = std::make_shared<std::string>(pAttributeKey);
    dirtyFlag_[2] = true;
}
void LoanProductAttribute::setAttributeKey(std::string &&pAttributeKey) noexcept
{
    attributeKey_ = std::make_shared<std::string>(std::move(pAttributeKey));
    dirtyFlag_[2] = true;
}

const std::string &LoanProductAttribute::getValueOfAttributeValue() const noexcept
{
    static const std::string defaultValue = std::string();
    if(attributeValue_)
        return *attributeValue_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductAttribute::getAttributeValue() const noexcept
{
    return attributeValue_;
}
void LoanProductAttribute::setAttributeValue(const std::string &pAttributeValue) noexcept
{
    attributeValue_ = std::make_shared<std::string>(pAttributeValue);
    dirtyFlag_[3] = true;
}
void LoanProductAttribute::setAttributeValue(std::string &&pAttributeValue) noexcept
{
    attributeValue_ = std::make_shared<std::string>(std::move(pAttributeValue));
    dirtyFlag_[3] = true;
}
void LoanProductAttribute::setAttributeValueToNull() noexcept
{
    attributeValue_.reset();
    dirtyFlag_[3] = true;
}

const ::trantor::Date &LoanProductAttribute::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanProductAttribute::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanProductAttribute::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[4] = true;
}

void LoanProductAttribute::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanProductAttribute::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_product_id",
        "attribute_key",
        "attribute_value",
        "created_at"
    };
    return inCols;
}

void LoanProductAttribute::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanProductId())
        {
            binder << getValueOfLoanProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getAttributeKey())
        {
            binder << getValueOfAttributeKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getAttributeValue())
        {
            binder << getValueOfAttributeValue();
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

const std::vector<std::string> LoanProductAttribute::updateColumns() const
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

void LoanProductAttribute::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanProductId())
        {
            binder << getValueOfLoanProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getAttributeKey())
        {
            binder << getValueOfAttributeKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getAttributeValue())
        {
            binder << getValueOfAttributeValue();
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
