/**
 *  TptBeneficiary.cc
 *
 *  See TptBeneficiary.h for the hand-authored-subset note.
 *
 */

#include "TptBeneficiary.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlSelfServiceDb;

const std::string TptBeneficiary::Cols::_id = "\"id\"";
const std::string TptBeneficiary::Cols::_self_service_user_id = "\"self_service_user_id\"";
const std::string TptBeneficiary::Cols::_name = "\"name\"";
const std::string TptBeneficiary::Cols::_account_type = "\"account_type\"";
const std::string TptBeneficiary::Cols::_account_number = "\"account_number\"";
const std::string TptBeneficiary::Cols::_transfer_limit = "\"transfer_limit\"";
const std::string TptBeneficiary::Cols::_status = "\"status\"";
const std::string TptBeneficiary::Cols::_created_at = "\"created_at\"";
const std::string TptBeneficiary::Cols::_updated_at = "\"updated_at\"";
const std::string TptBeneficiary::primaryKeyName = "id";
const bool TptBeneficiary::hasPrimaryKey = true;
const std::string TptBeneficiary::tableName = "\"tpt_beneficiaries\"";

const std::vector<typename TptBeneficiary::MetaData> TptBeneficiary::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"self_service_user_id","std::string","character varying",64,0,0,1},
{"name","std::string","character varying",150,0,0,1},
{"account_type","std::string","character varying",20,0,0,1},
{"account_number","std::string","character varying",100,0,0,1},
{"transfer_limit","std::string","numeric",0,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &TptBeneficiary::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
TptBeneficiary::TptBeneficiary(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["self_service_user_id"].isNull())
        {
            selfServiceUserId_=std::make_shared<std::string>(r["self_service_user_id"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["account_type"].isNull())
        {
            accountType_=std::make_shared<std::string>(r["account_type"].as<std::string>());
        }
        if(!r["account_number"].isNull())
        {
            accountNumber_=std::make_shared<std::string>(r["account_number"].as<std::string>());
        }
        if(!r["transfer_limit"].isNull())
        {
            transferLimit_=std::make_shared<std::string>(r["transfer_limit"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
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
        if(offset + 9 > r.size())
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
            selfServiceUserId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            accountType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            accountNumber_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            transferLimit_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &TptBeneficiary::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TptBeneficiary::getId() const noexcept
{
    return id_;
}
void TptBeneficiary::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void TptBeneficiary::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename TptBeneficiary::PrimaryKeyType & TptBeneficiary::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &TptBeneficiary::getValueOfSelfServiceUserId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(selfServiceUserId_)
        return *selfServiceUserId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TptBeneficiary::getSelfServiceUserId() const noexcept
{
    return selfServiceUserId_;
}
void TptBeneficiary::setSelfServiceUserId(const std::string &pSelfServiceUserId) noexcept
{
    selfServiceUserId_ = std::make_shared<std::string>(pSelfServiceUserId);
    dirtyFlag_[1] = true;
}
void TptBeneficiary::setSelfServiceUserId(std::string &&pSelfServiceUserId) noexcept
{
    selfServiceUserId_ = std::make_shared<std::string>(std::move(pSelfServiceUserId));
    dirtyFlag_[1] = true;
}

const std::string &TptBeneficiary::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TptBeneficiary::getName() const noexcept
{
    return name_;
}
void TptBeneficiary::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[2] = true;
}
void TptBeneficiary::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[2] = true;
}

const std::string &TptBeneficiary::getValueOfAccountType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountType_)
        return *accountType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TptBeneficiary::getAccountType() const noexcept
{
    return accountType_;
}
void TptBeneficiary::setAccountType(const std::string &pAccountType) noexcept
{
    accountType_ = std::make_shared<std::string>(pAccountType);
    dirtyFlag_[3] = true;
}
void TptBeneficiary::setAccountType(std::string &&pAccountType) noexcept
{
    accountType_ = std::make_shared<std::string>(std::move(pAccountType));
    dirtyFlag_[3] = true;
}

const std::string &TptBeneficiary::getValueOfAccountNumber() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountNumber_)
        return *accountNumber_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TptBeneficiary::getAccountNumber() const noexcept
{
    return accountNumber_;
}
void TptBeneficiary::setAccountNumber(const std::string &pAccountNumber) noexcept
{
    accountNumber_ = std::make_shared<std::string>(pAccountNumber);
    dirtyFlag_[4] = true;
}
void TptBeneficiary::setAccountNumber(std::string &&pAccountNumber) noexcept
{
    accountNumber_ = std::make_shared<std::string>(std::move(pAccountNumber));
    dirtyFlag_[4] = true;
}

const std::string &TptBeneficiary::getValueOfTransferLimit() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transferLimit_)
        return *transferLimit_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TptBeneficiary::getTransferLimit() const noexcept
{
    return transferLimit_;
}
void TptBeneficiary::setTransferLimit(const std::string &pTransferLimit) noexcept
{
    transferLimit_ = std::make_shared<std::string>(pTransferLimit);
    dirtyFlag_[5] = true;
}
void TptBeneficiary::setTransferLimit(std::string &&pTransferLimit) noexcept
{
    transferLimit_ = std::make_shared<std::string>(std::move(pTransferLimit));
    dirtyFlag_[5] = true;
}
void TptBeneficiary::setTransferLimitToNull() noexcept
{
    transferLimit_.reset();
    dirtyFlag_[5] = true;
}

const std::string &TptBeneficiary::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &TptBeneficiary::getStatus() const noexcept
{
    return status_;
}
void TptBeneficiary::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[6] = true;
}
void TptBeneficiary::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[6] = true;
}

const ::trantor::Date &TptBeneficiary::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &TptBeneficiary::getCreatedAt() const noexcept
{
    return createdAt_;
}
void TptBeneficiary::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

const ::trantor::Date &TptBeneficiary::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &TptBeneficiary::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void TptBeneficiary::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[8] = true;
}

void TptBeneficiary::updateId(const uint64_t id)
{
}

const std::vector<std::string> &TptBeneficiary::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "self_service_user_id",
        "name",
        "account_type",
        "account_number",
        "transfer_limit",
        "status",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void TptBeneficiary::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSelfServiceUserId())
        {
            binder << getValueOfSelfServiceUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getAccountType())
        {
            binder << getValueOfAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAccountNumber())
        {
            binder << getValueOfAccountNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransferLimit())
        {
            binder << getValueOfTransferLimit();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
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
    if(dirtyFlag_[8])
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

const std::vector<std::string> TptBeneficiary::updateColumns() const
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
    return ret;
}

void TptBeneficiary::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSelfServiceUserId())
        {
            binder << getValueOfSelfServiceUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getAccountType())
        {
            binder << getValueOfAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAccountNumber())
        {
            binder << getValueOfAccountNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransferLimit())
        {
            binder << getValueOfTransferLimit();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
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
    if(dirtyFlag_[8])
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
