/**
 *  CreditBureauConfiguration.cc
 *
 *  See CreditBureauConfiguration.h for the hand-authored-subset note.
 *
 */

#include "CreditBureauConfiguration.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string CreditBureauConfiguration::Cols::_id = "\"id\"";
const std::string CreditBureauConfiguration::Cols::_organisation_credit_bureau_id = "\"organisation_credit_bureau_id\"";
const std::string CreditBureauConfiguration::Cols::_config_key = "\"config_key\"";
const std::string CreditBureauConfiguration::Cols::_config_value = "\"config_value\"";
const std::string CreditBureauConfiguration::primaryKeyName = "id";
const bool CreditBureauConfiguration::hasPrimaryKey = true;
const std::string CreditBureauConfiguration::tableName = "\"credit_bureau_configuration\"";

const std::vector<typename CreditBureauConfiguration::MetaData> CreditBureauConfiguration::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"organisation_credit_bureau_id","std::string","uuid",0,0,0,1},
{"config_key","std::string","character varying",100,0,0,1},
{"config_value","std::string","text",0,0,0,0}
};
const std::string &CreditBureauConfiguration::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
CreditBureauConfiguration::CreditBureauConfiguration(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["organisation_credit_bureau_id"].isNull())
        {
            organisationCreditBureauId_=std::make_shared<std::string>(r["organisation_credit_bureau_id"].as<std::string>());
        }
        if(!r["config_key"].isNull())
        {
            configKey_=std::make_shared<std::string>(r["config_key"].as<std::string>());
        }
        if(!r["config_value"].isNull())
        {
            configValue_=std::make_shared<std::string>(r["config_value"].as<std::string>());
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
            organisationCreditBureauId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            configKey_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            configValue_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &CreditBureauConfiguration::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauConfiguration::getId() const noexcept
{
    return id_;
}
void CreditBureauConfiguration::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void CreditBureauConfiguration::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename CreditBureauConfiguration::PrimaryKeyType & CreditBureauConfiguration::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &CreditBureauConfiguration::getValueOfOrganisationCreditBureauId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(organisationCreditBureauId_)
        return *organisationCreditBureauId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauConfiguration::getOrganisationCreditBureauId() const noexcept
{
    return organisationCreditBureauId_;
}
void CreditBureauConfiguration::setOrganisationCreditBureauId(const std::string &pOrganisationCreditBureauId) noexcept
{
    organisationCreditBureauId_ = std::make_shared<std::string>(pOrganisationCreditBureauId);
    dirtyFlag_[1] = true;
}
void CreditBureauConfiguration::setOrganisationCreditBureauId(std::string &&pOrganisationCreditBureauId) noexcept
{
    organisationCreditBureauId_ = std::make_shared<std::string>(std::move(pOrganisationCreditBureauId));
    dirtyFlag_[1] = true;
}

const std::string &CreditBureauConfiguration::getValueOfConfigKey() const noexcept
{
    static const std::string defaultValue = std::string();
    if(configKey_)
        return *configKey_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauConfiguration::getConfigKey() const noexcept
{
    return configKey_;
}
void CreditBureauConfiguration::setConfigKey(const std::string &pConfigKey) noexcept
{
    configKey_ = std::make_shared<std::string>(pConfigKey);
    dirtyFlag_[2] = true;
}
void CreditBureauConfiguration::setConfigKey(std::string &&pConfigKey) noexcept
{
    configKey_ = std::make_shared<std::string>(std::move(pConfigKey));
    dirtyFlag_[2] = true;
}

const std::string &CreditBureauConfiguration::getValueOfConfigValue() const noexcept
{
    static const std::string defaultValue = std::string();
    if(configValue_)
        return *configValue_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauConfiguration::getConfigValue() const noexcept
{
    return configValue_;
}
void CreditBureauConfiguration::setConfigValue(const std::string &pConfigValue) noexcept
{
    configValue_ = std::make_shared<std::string>(pConfigValue);
    dirtyFlag_[3] = true;
}
void CreditBureauConfiguration::setConfigValue(std::string &&pConfigValue) noexcept
{
    configValue_ = std::make_shared<std::string>(std::move(pConfigValue));
    dirtyFlag_[3] = true;
}
void CreditBureauConfiguration::setConfigValueToNull() noexcept
{
    configValue_.reset();
    dirtyFlag_[3] = true;
}

void CreditBureauConfiguration::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CreditBureauConfiguration::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "organisation_credit_bureau_id",
        "config_key",
        "config_value"
    };
    return inCols;
}

void CreditBureauConfiguration::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOrganisationCreditBureauId())
        {
            binder << getValueOfOrganisationCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getConfigKey())
        {
            binder << getValueOfConfigKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getConfigValue())
        {
            binder << getValueOfConfigValue();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> CreditBureauConfiguration::updateColumns() const
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

void CreditBureauConfiguration::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOrganisationCreditBureauId())
        {
            binder << getValueOfOrganisationCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getConfigKey())
        {
            binder << getValueOfConfigKey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getConfigValue())
        {
            binder << getValueOfConfigValue();
        }
        else
        {
            binder << nullptr;
        }
    }
}
