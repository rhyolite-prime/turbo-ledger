/**
 *
 *  TaxComponent.cc
 *
 *  See TaxComponent.h for the hand-authored-subset note.
 *
 */

#include "TaxComponent.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlOrganizationDb;

const std::string TaxComponent::Cols::_id = "\"id\"";
const std::string TaxComponent::Cols::_name = "\"name\"";
const std::string TaxComponent::Cols::_percentage = "\"percentage\"";
const std::string TaxComponent::Cols::_start_date = "\"start_date\"";
const std::string TaxComponent::Cols::_debit_account_id = "\"debit_account_id\"";
const std::string TaxComponent::Cols::_credit_account_id = "\"credit_account_id\"";
const std::string TaxComponent::Cols::_created_at = "\"created_at\"";
const std::string TaxComponent::Cols::_modified_at = "\"modified_at\"";
const std::string TaxComponent::primaryKeyName = "id";
const bool TaxComponent::hasPrimaryKey = true;
const std::string TaxComponent::tableName = "\"tax_component\"";

const std::vector<typename TaxComponent::MetaData> TaxComponent::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",100,0,0,1},
{"percentage","std::string","numeric",0,0,0,1},
{"start_date","::trantor::Date","date",0,0,0,1},
{"debit_account_id","std::string","character varying",80,0,0,0},
{"credit_account_id","std::string","character varying",80,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"modified_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &TaxComponent::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
TaxComponent::TaxComponent(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["percentage"].isNull())
        {
            percentage_=std::make_shared<std::string>(r["percentage"].as<std::string>());
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
        if(!r["debit_account_id"].isNull())
        {
            debitAccountId_=std::make_shared<std::string>(r["debit_account_id"].as<std::string>());
        }
        if(!r["credit_account_id"].isNull())
        {
            creditAccountId_=std::make_shared<std::string>(r["credit_account_id"].as<std::string>());
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
        if(!r["modified_at"].isNull())
        {
            auto timeStr = r["modified_at"].as<std::string>();
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
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
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
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            percentage_=std::make_shared<std::string>(r[index].as<std::string>());
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
        index = offset + 4;
        if(!r[index].isNull())
        {
            debitAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            creditAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
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
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}

const std::string &TaxComponent::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxComponent::getId() const noexcept
{
    return id_;
}
void TaxComponent::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void TaxComponent::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename TaxComponent::PrimaryKeyType & TaxComponent::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &TaxComponent::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxComponent::getName() const noexcept
{
    return name_;
}
void TaxComponent::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void TaxComponent::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const std::string &TaxComponent::getValueOfPercentage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(percentage_)
        return *percentage_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxComponent::getPercentage() const noexcept
{
    return percentage_;
}
void TaxComponent::setPercentage(const std::string &pPercentage) noexcept
{
    percentage_ = std::make_shared<std::string>(pPercentage);
    dirtyFlag_[2] = true;
}
void TaxComponent::setPercentage(std::string &&pPercentage) noexcept
{
    percentage_ = std::make_shared<std::string>(std::move(pPercentage));
    dirtyFlag_[2] = true;
}

const ::trantor::Date &TaxComponent::getValueOfStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDate_)
        return *startDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &TaxComponent::getStartDate() const noexcept
{
    return startDate_;
}
void TaxComponent::setStartDate(const ::trantor::Date &pStartDate) noexcept
{
    startDate_ = std::make_shared<::trantor::Date>(pStartDate.roundDay());
    dirtyFlag_[3] = true;
}

const std::string &TaxComponent::getValueOfDebitAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(debitAccountId_)
        return *debitAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxComponent::getDebitAccountId() const noexcept
{
    return debitAccountId_;
}
void TaxComponent::setDebitAccountId(const std::string &pDebitAccountId) noexcept
{
    debitAccountId_ = std::make_shared<std::string>(pDebitAccountId);
    dirtyFlag_[4] = true;
}
void TaxComponent::setDebitAccountId(std::string &&pDebitAccountId) noexcept
{
    debitAccountId_ = std::make_shared<std::string>(std::move(pDebitAccountId));
    dirtyFlag_[4] = true;
}
void TaxComponent::setDebitAccountIdToNull() noexcept
{
    debitAccountId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &TaxComponent::getValueOfCreditAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(creditAccountId_)
        return *creditAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TaxComponent::getCreditAccountId() const noexcept
{
    return creditAccountId_;
}
void TaxComponent::setCreditAccountId(const std::string &pCreditAccountId) noexcept
{
    creditAccountId_ = std::make_shared<std::string>(pCreditAccountId);
    dirtyFlag_[5] = true;
}
void TaxComponent::setCreditAccountId(std::string &&pCreditAccountId) noexcept
{
    creditAccountId_ = std::make_shared<std::string>(std::move(pCreditAccountId));
    dirtyFlag_[5] = true;
}
void TaxComponent::setCreditAccountIdToNull() noexcept
{
    creditAccountId_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &TaxComponent::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &TaxComponent::getCreatedAt() const noexcept
{
    return createdAt_;
}
void TaxComponent::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[6] = true;
}

const ::trantor::Date &TaxComponent::getValueOfModifiedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(modifiedAt_)
        return *modifiedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &TaxComponent::getModifiedAt() const noexcept
{
    return modifiedAt_;
}
void TaxComponent::setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept
{
    modifiedAt_ = std::make_shared<::trantor::Date>(pModifiedAt);
    dirtyFlag_[7] = true;
}

void TaxComponent::updateId(const uint64_t id)
{
}

const std::vector<std::string> &TaxComponent::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "percentage",
        "start_date",
        "debit_account_id",
        "credit_account_id",
        "created_at",
        "modified_at"
    };
    return inCols;
}

void TaxComponent::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getPercentage())
        {
            binder << getValueOfPercentage();
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
    if(dirtyFlag_[4])
    {
        if(getDebitAccountId())
        {
            binder << getValueOfDebitAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreditAccountId())
        {
            binder << getValueOfCreditAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> TaxComponent::updateColumns() const
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

void TaxComponent::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getPercentage())
        {
            binder << getValueOfPercentage();
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
    if(dirtyFlag_[4])
    {
        if(getDebitAccountId())
        {
            binder << getValueOfDebitAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreditAccountId())
        {
            binder << getValueOfCreditAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

