/**
 *
 *  ProvisioningEntryDetail.cc
 *
 *  See ProvisioningEntryDetail.h for the hand-authored-subset note.
 *
 */

#include "ProvisioningEntryDetail.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlAccounting;

const std::string ProvisioningEntryDetail::Cols::_id = "\"id\"";
const std::string ProvisioningEntryDetail::Cols::_provisioning_entry_id = "\"provisioning_entry_id\"";
const std::string ProvisioningEntryDetail::Cols::_office_id = "\"office_id\"";
const std::string ProvisioningEntryDetail::Cols::_currency_code = "\"currency_code\"";
const std::string ProvisioningEntryDetail::Cols::_gl_account_id = "\"gl_account_id\"";
const std::string ProvisioningEntryDetail::Cols::_category_name = "\"category_name\"";
const std::string ProvisioningEntryDetail::Cols::_amount = "\"amount\"";
const std::string ProvisioningEntryDetail::Cols::_created_at = "\"created_at\"";
const std::string ProvisioningEntryDetail::primaryKeyName = "id";
const bool ProvisioningEntryDetail::hasPrimaryKey = true;
const std::string ProvisioningEntryDetail::tableName = "\"provisioning_entries_detail\"";

const std::vector<typename ProvisioningEntryDetail::MetaData> ProvisioningEntryDetail::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"provisioning_entry_id","std::string","uuid",0,0,0,1},
{"office_id","std::string","uuid",0,0,0,1},
{"currency_code","std::string","character varying",3,0,0,1},
{"gl_account_id","std::string","uuid",0,0,0,1},
{"category_name","std::string","character varying",100,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ProvisioningEntryDetail::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ProvisioningEntryDetail::ProvisioningEntryDetail(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["provisioning_entry_id"].isNull())
        {
            provisioningEntryId_=std::make_shared<std::string>(r["provisioning_entry_id"].as<std::string>());
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["gl_account_id"].isNull())
        {
            glAccountId_=std::make_shared<std::string>(r["gl_account_id"].as<std::string>());
        }
        if(!r["category_name"].isNull())
        {
            categoryName_=std::make_shared<std::string>(r["category_name"].as<std::string>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
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
        if(offset + 8 > r.size())
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
            provisioningEntryId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            glAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            categoryName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
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
const std::string &ProvisioningEntryDetail::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntryDetail::getId() const noexcept
{
    return id_;
}
void ProvisioningEntryDetail::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ProvisioningEntryDetail::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ProvisioningEntryDetail::PrimaryKeyType & ProvisioningEntryDetail::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ProvisioningEntryDetail::getValueOfProvisioningEntryId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(provisioningEntryId_)
        return *provisioningEntryId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntryDetail::getProvisioningEntryId() const noexcept
{
    return provisioningEntryId_;
}
void ProvisioningEntryDetail::setProvisioningEntryId(const std::string &pProvisioningEntryId) noexcept
{
    provisioningEntryId_ = std::make_shared<std::string>(pProvisioningEntryId);
    dirtyFlag_[1] = true;
}
void ProvisioningEntryDetail::setProvisioningEntryId(std::string &&pProvisioningEntryId) noexcept
{
    provisioningEntryId_ = std::make_shared<std::string>(std::move(pProvisioningEntryId));
    dirtyFlag_[1] = true;
}

const std::string &ProvisioningEntryDetail::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntryDetail::getOfficeId() const noexcept
{
    return officeId_;
}
void ProvisioningEntryDetail::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[2] = true;
}
void ProvisioningEntryDetail::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[2] = true;
}

const std::string &ProvisioningEntryDetail::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntryDetail::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void ProvisioningEntryDetail::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[3] = true;
}
void ProvisioningEntryDetail::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[3] = true;
}

const std::string &ProvisioningEntryDetail::getValueOfGlAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(glAccountId_)
        return *glAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntryDetail::getGlAccountId() const noexcept
{
    return glAccountId_;
}
void ProvisioningEntryDetail::setGlAccountId(const std::string &pGlAccountId) noexcept
{
    glAccountId_ = std::make_shared<std::string>(pGlAccountId);
    dirtyFlag_[4] = true;
}
void ProvisioningEntryDetail::setGlAccountId(std::string &&pGlAccountId) noexcept
{
    glAccountId_ = std::make_shared<std::string>(std::move(pGlAccountId));
    dirtyFlag_[4] = true;
}

const std::string &ProvisioningEntryDetail::getValueOfCategoryName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(categoryName_)
        return *categoryName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntryDetail::getCategoryName() const noexcept
{
    return categoryName_;
}
void ProvisioningEntryDetail::setCategoryName(const std::string &pCategoryName) noexcept
{
    categoryName_ = std::make_shared<std::string>(pCategoryName);
    dirtyFlag_[5] = true;
}
void ProvisioningEntryDetail::setCategoryName(std::string &&pCategoryName) noexcept
{
    categoryName_ = std::make_shared<std::string>(std::move(pCategoryName));
    dirtyFlag_[5] = true;
}

const std::string &ProvisioningEntryDetail::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntryDetail::getAmount() const noexcept
{
    return amount_;
}
void ProvisioningEntryDetail::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[6] = true;
}
void ProvisioningEntryDetail::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[6] = true;
}

const ::trantor::Date &ProvisioningEntryDetail::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ProvisioningEntryDetail::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ProvisioningEntryDetail::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

void ProvisioningEntryDetail::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ProvisioningEntryDetail::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "provisioning_entry_id",
        "office_id",
        "currency_code",
        "gl_account_id",
        "category_name",
        "amount",
        "created_at"
    };
    return inCols;
}

void ProvisioningEntryDetail::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getProvisioningEntryId())
        {
            binder << getValueOfProvisioningEntryId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getGlAccountId())
        {
            binder << getValueOfGlAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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

const std::vector<std::string> ProvisioningEntryDetail::updateColumns() const
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
    return ret;
}

void ProvisioningEntryDetail::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getProvisioningEntryId())
        {
            binder << getValueOfProvisioningEntryId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getGlAccountId())
        {
            binder << getValueOfGlAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
