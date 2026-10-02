/**
 *  Pocket.cc
 *
 *  See Pocket.h for the hand-authored-subset note.
 *
 */

#include "Pocket.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlSelfServiceDb;

const std::string Pocket::Cols::_id = "\"id\"";
const std::string Pocket::Cols::_self_service_user_id = "\"self_service_user_id\"";
const std::string Pocket::Cols::_account_type = "\"account_type\"";
const std::string Pocket::Cols::_account_id = "\"account_id\"";
const std::string Pocket::Cols::_is_default = "\"is_default\"";
const std::string Pocket::Cols::_created_at = "\"created_at\"";
const std::string Pocket::primaryKeyName = "id";
const bool Pocket::hasPrimaryKey = true;
const std::string Pocket::tableName = "\"pockets\"";

const std::vector<typename Pocket::MetaData> Pocket::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"self_service_user_id","std::string","character varying",64,0,0,1},
{"account_type","std::string","character varying",20,0,0,1},
{"account_id","std::string","character varying",64,0,0,1},
{"is_default","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Pocket::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Pocket::Pocket(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["account_type"].isNull())
        {
            accountType_=std::make_shared<std::string>(r["account_type"].as<std::string>());
        }
        if(!r["account_id"].isNull())
        {
            accountId_=std::make_shared<std::string>(r["account_id"].as<std::string>());
        }
        if(!r["is_default"].isNull())
        {
            isDefault_=std::make_shared<bool>(r["is_default"].as<bool>());
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
            selfServiceUserId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            accountType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            accountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            isDefault_=std::make_shared<bool>(r[index].as<bool>());
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
const std::string &Pocket::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Pocket::getId() const noexcept
{
    return id_;
}
void Pocket::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Pocket::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Pocket::PrimaryKeyType & Pocket::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Pocket::getValueOfSelfServiceUserId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(selfServiceUserId_)
        return *selfServiceUserId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Pocket::getSelfServiceUserId() const noexcept
{
    return selfServiceUserId_;
}
void Pocket::setSelfServiceUserId(const std::string &pSelfServiceUserId) noexcept
{
    selfServiceUserId_ = std::make_shared<std::string>(pSelfServiceUserId);
    dirtyFlag_[1] = true;
}
void Pocket::setSelfServiceUserId(std::string &&pSelfServiceUserId) noexcept
{
    selfServiceUserId_ = std::make_shared<std::string>(std::move(pSelfServiceUserId));
    dirtyFlag_[1] = true;
}

const std::string &Pocket::getValueOfAccountType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountType_)
        return *accountType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Pocket::getAccountType() const noexcept
{
    return accountType_;
}
void Pocket::setAccountType(const std::string &pAccountType) noexcept
{
    accountType_ = std::make_shared<std::string>(pAccountType);
    dirtyFlag_[2] = true;
}
void Pocket::setAccountType(std::string &&pAccountType) noexcept
{
    accountType_ = std::make_shared<std::string>(std::move(pAccountType));
    dirtyFlag_[2] = true;
}

const std::string &Pocket::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Pocket::getAccountId() const noexcept
{
    return accountId_;
}
void Pocket::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[3] = true;
}
void Pocket::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[3] = true;
}

const bool &Pocket::getValueOfIsDefault() const noexcept
{
    static const bool defaultValue = bool();
    if(isDefault_)
        return *isDefault_;
    return defaultValue;
}
const std::shared_ptr<bool> &Pocket::getIsDefault() const noexcept
{
    return isDefault_;
}
void Pocket::setIsDefault(const bool &pIsDefault) noexcept
{
    isDefault_ = std::make_shared<bool>(pIsDefault);
    dirtyFlag_[4] = true;
}

const ::trantor::Date &Pocket::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Pocket::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Pocket::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

void Pocket::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Pocket::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "self_service_user_id",
        "account_type",
        "account_id",
        "is_default",
        "created_at"
    };
    return inCols;
}

void Pocket::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountType())
        {
            binder << getValueOfAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getAccountId())
        {
            binder << getValueOfAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIsDefault())
        {
            binder << getValueOfIsDefault();
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

const std::vector<std::string> Pocket::updateColumns() const
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

void Pocket::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountType())
        {
            binder << getValueOfAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getAccountId())
        {
            binder << getValueOfAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIsDefault())
        {
            binder << getValueOfIsDefault();
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
