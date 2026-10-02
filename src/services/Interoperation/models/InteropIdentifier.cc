/**
 *  InteropIdentifier.cc
 *
 *  See InteropIdentifier.h for the hand-authored-subset note.
 *
 */

#include "InteropIdentifier.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlInteroperationDb;

const std::string InteropIdentifier::Cols::_id = "\"id\"";
const std::string InteropIdentifier::Cols::_id_type = "\"id_type\"";
const std::string InteropIdentifier::Cols::_id_value = "\"id_value\"";
const std::string InteropIdentifier::Cols::_sub_id_or_type = "\"sub_id_or_type\"";
const std::string InteropIdentifier::Cols::_account_id = "\"account_id\"";
const std::string InteropIdentifier::Cols::_account_type = "\"account_type\"";
const std::string InteropIdentifier::Cols::_created_at = "\"created_at\"";
const std::string InteropIdentifier::primaryKeyName = "id";
const bool InteropIdentifier::hasPrimaryKey = true;
const std::string InteropIdentifier::tableName = "\"interop_identifiers\"";

const std::vector<typename InteropIdentifier::MetaData> InteropIdentifier::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"id_type","std::string","character varying",50,0,0,1},
{"id_value","std::string","character varying",150,0,0,1},
{"sub_id_or_type","std::string","character varying",50,0,0,0},
{"account_id","std::string","character varying",64,0,0,1},
{"account_type","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &InteropIdentifier::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
InteropIdentifier::InteropIdentifier(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["id_type"].isNull())
        {
            idType_=std::make_shared<std::string>(r["id_type"].as<std::string>());
        }
        if(!r["id_value"].isNull())
        {
            idValue_=std::make_shared<std::string>(r["id_value"].as<std::string>());
        }
        if(!r["sub_id_or_type"].isNull())
        {
            subIdOrType_=std::make_shared<std::string>(r["sub_id_or_type"].as<std::string>());
        }
        if(!r["account_id"].isNull())
        {
            accountId_=std::make_shared<std::string>(r["account_id"].as<std::string>());
        }
        if(!r["account_type"].isNull())
        {
            accountType_=std::make_shared<std::string>(r["account_type"].as<std::string>());
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
            idType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            idValue_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            subIdOrType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            accountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            accountType_=std::make_shared<std::string>(r[index].as<std::string>());
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
    }

}
const std::string &InteropIdentifier::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropIdentifier::getId() const noexcept
{
    return id_;
}
void InteropIdentifier::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void InteropIdentifier::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename InteropIdentifier::PrimaryKeyType & InteropIdentifier::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &InteropIdentifier::getValueOfIdType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(idType_)
        return *idType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropIdentifier::getIdType() const noexcept
{
    return idType_;
}
void InteropIdentifier::setIdType(const std::string &pIdType) noexcept
{
    idType_ = std::make_shared<std::string>(pIdType);
    dirtyFlag_[1] = true;
}
void InteropIdentifier::setIdType(std::string &&pIdType) noexcept
{
    idType_ = std::make_shared<std::string>(std::move(pIdType));
    dirtyFlag_[1] = true;
}

const std::string &InteropIdentifier::getValueOfIdValue() const noexcept
{
    static const std::string defaultValue = std::string();
    if(idValue_)
        return *idValue_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropIdentifier::getIdValue() const noexcept
{
    return idValue_;
}
void InteropIdentifier::setIdValue(const std::string &pIdValue) noexcept
{
    idValue_ = std::make_shared<std::string>(pIdValue);
    dirtyFlag_[2] = true;
}
void InteropIdentifier::setIdValue(std::string &&pIdValue) noexcept
{
    idValue_ = std::make_shared<std::string>(std::move(pIdValue));
    dirtyFlag_[2] = true;
}

const std::string &InteropIdentifier::getValueOfSubIdOrType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(subIdOrType_)
        return *subIdOrType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropIdentifier::getSubIdOrType() const noexcept
{
    return subIdOrType_;
}
void InteropIdentifier::setSubIdOrType(const std::string &pSubIdOrType) noexcept
{
    subIdOrType_ = std::make_shared<std::string>(pSubIdOrType);
    dirtyFlag_[3] = true;
}
void InteropIdentifier::setSubIdOrType(std::string &&pSubIdOrType) noexcept
{
    subIdOrType_ = std::make_shared<std::string>(std::move(pSubIdOrType));
    dirtyFlag_[3] = true;
}
void InteropIdentifier::setSubIdOrTypeToNull() noexcept
{
    subIdOrType_.reset();
    dirtyFlag_[3] = true;
}

const std::string &InteropIdentifier::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropIdentifier::getAccountId() const noexcept
{
    return accountId_;
}
void InteropIdentifier::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[4] = true;
}
void InteropIdentifier::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[4] = true;
}

const std::string &InteropIdentifier::getValueOfAccountType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountType_)
        return *accountType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropIdentifier::getAccountType() const noexcept
{
    return accountType_;
}
void InteropIdentifier::setAccountType(const std::string &pAccountType) noexcept
{
    accountType_ = std::make_shared<std::string>(pAccountType);
    dirtyFlag_[5] = true;
}
void InteropIdentifier::setAccountType(std::string &&pAccountType) noexcept
{
    accountType_ = std::make_shared<std::string>(std::move(pAccountType));
    dirtyFlag_[5] = true;
}

const ::trantor::Date &InteropIdentifier::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &InteropIdentifier::getCreatedAt() const noexcept
{
    return createdAt_;
}
void InteropIdentifier::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[6] = true;
}

void InteropIdentifier::updateId(const uint64_t id)
{
}

const std::vector<std::string> &InteropIdentifier::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "id_type",
        "id_value",
        "sub_id_or_type",
        "account_id",
        "account_type",
        "created_at"
    };
    return inCols;
}

void InteropIdentifier::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getIdType())
        {
            binder << getValueOfIdType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getIdValue())
        {
            binder << getValueOfIdValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSubIdOrType())
        {
            binder << getValueOfSubIdOrType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
}

const std::vector<std::string> InteropIdentifier::updateColumns() const
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

void InteropIdentifier::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getIdType())
        {
            binder << getValueOfIdType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getIdValue())
        {
            binder << getValueOfIdValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSubIdOrType())
        {
            binder << getValueOfSubIdOrType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
}
