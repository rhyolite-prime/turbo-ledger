/**
 *  OrganisationCreditBureau.cc
 *
 *  See OrganisationCreditBureau.h for the hand-authored-subset note.
 *
 */

#include "OrganisationCreditBureau.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string OrganisationCreditBureau::Cols::_id = "\"id\"";
const std::string OrganisationCreditBureau::Cols::_credit_bureau_id = "\"credit_bureau_id\"";
const std::string OrganisationCreditBureau::Cols::_alias = "\"alias\"";
const std::string OrganisationCreditBureau::Cols::_is_active = "\"is_active\"";
const std::string OrganisationCreditBureau::Cols::_created_at = "\"created_at\"";
const std::string OrganisationCreditBureau::primaryKeyName = "id";
const bool OrganisationCreditBureau::hasPrimaryKey = true;
const std::string OrganisationCreditBureau::tableName = "\"organisation_credit_bureau\"";

const std::vector<typename OrganisationCreditBureau::MetaData> OrganisationCreditBureau::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"credit_bureau_id","std::string","uuid",0,0,0,1},
{"alias","std::string","character varying",100,0,0,1},
{"is_active","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &OrganisationCreditBureau::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
OrganisationCreditBureau::OrganisationCreditBureau(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["credit_bureau_id"].isNull())
        {
            creditBureauId_=std::make_shared<std::string>(r["credit_bureau_id"].as<std::string>());
        }
        if(!r["alias"].isNull())
        {
            alias_=std::make_shared<std::string>(r["alias"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
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
            creditBureauId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            alias_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
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
const std::string &OrganisationCreditBureau::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &OrganisationCreditBureau::getId() const noexcept
{
    return id_;
}
void OrganisationCreditBureau::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void OrganisationCreditBureau::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename OrganisationCreditBureau::PrimaryKeyType & OrganisationCreditBureau::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &OrganisationCreditBureau::getValueOfCreditBureauId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(creditBureauId_)
        return *creditBureauId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &OrganisationCreditBureau::getCreditBureauId() const noexcept
{
    return creditBureauId_;
}
void OrganisationCreditBureau::setCreditBureauId(const std::string &pCreditBureauId) noexcept
{
    creditBureauId_ = std::make_shared<std::string>(pCreditBureauId);
    dirtyFlag_[1] = true;
}
void OrganisationCreditBureau::setCreditBureauId(std::string &&pCreditBureauId) noexcept
{
    creditBureauId_ = std::make_shared<std::string>(std::move(pCreditBureauId));
    dirtyFlag_[1] = true;
}

const std::string &OrganisationCreditBureau::getValueOfAlias() const noexcept
{
    static const std::string defaultValue = std::string();
    if(alias_)
        return *alias_;
    return defaultValue;
}
const std::shared_ptr<std::string> &OrganisationCreditBureau::getAlias() const noexcept
{
    return alias_;
}
void OrganisationCreditBureau::setAlias(const std::string &pAlias) noexcept
{
    alias_ = std::make_shared<std::string>(pAlias);
    dirtyFlag_[2] = true;
}
void OrganisationCreditBureau::setAlias(std::string &&pAlias) noexcept
{
    alias_ = std::make_shared<std::string>(std::move(pAlias));
    dirtyFlag_[2] = true;
}

const bool &OrganisationCreditBureau::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &OrganisationCreditBureau::getIsActive() const noexcept
{
    return isActive_;
}
void OrganisationCreditBureau::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &OrganisationCreditBureau::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &OrganisationCreditBureau::getCreatedAt() const noexcept
{
    return createdAt_;
}
void OrganisationCreditBureau::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[4] = true;
}

void OrganisationCreditBureau::updateId(const uint64_t id)
{
}

const std::vector<std::string> &OrganisationCreditBureau::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "credit_bureau_id",
        "alias",
        "is_active",
        "created_at"
    };
    return inCols;
}

void OrganisationCreditBureau::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCreditBureauId())
        {
            binder << getValueOfCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getAlias())
        {
            binder << getValueOfAlias();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
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

const std::vector<std::string> OrganisationCreditBureau::updateColumns() const
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

void OrganisationCreditBureau::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCreditBureauId())
        {
            binder << getValueOfCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getAlias())
        {
            binder << getValueOfAlias();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
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
