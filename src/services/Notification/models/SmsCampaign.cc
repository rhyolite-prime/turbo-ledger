/**
 *  SmsCampaign.cc
 *
 *  See SmsCampaign.h for the hand-authored-subset note.
 *
 */

#include "SmsCampaign.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlNotificationDb;

const std::string SmsCampaign::Cols::_id = "\"id\"";
const std::string SmsCampaign::Cols::_campaign_name = "\"campaign_name\"";
const std::string SmsCampaign::Cols::_campaign_type = "\"campaign_type\"";
const std::string SmsCampaign::Cols::_message = "\"message\"";
const std::string SmsCampaign::Cols::_param_value = "\"param_value\"";
const std::string SmsCampaign::Cols::_recurrence = "\"recurrence\"";
const std::string SmsCampaign::Cols::_next_trigger_date = "\"next_trigger_date\"";
const std::string SmsCampaign::Cols::_status = "\"status\"";
const std::string SmsCampaign::Cols::_provider_id = "\"provider_id\"";
const std::string SmsCampaign::Cols::_created_at = "\"created_at\"";
const std::string SmsCampaign::Cols::_updated_at = "\"updated_at\"";
const std::string SmsCampaign::primaryKeyName = "id";
const bool SmsCampaign::hasPrimaryKey = true;
const std::string SmsCampaign::tableName = "\"sms_campaigns\"";

const std::vector<typename SmsCampaign::MetaData> SmsCampaign::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"campaign_name","std::string","character varying",200,0,0,1},
{"campaign_type","std::string","character varying",20,0,0,1},
{"message","std::string","text",0,0,0,1},
{"param_value","std::string","jsonb",0,0,0,1},
{"recurrence","std::string","character varying",100,0,0,0},
{"next_trigger_date","::trantor::Date","timestamp with time zone",0,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"provider_id","std::string","character varying",100,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SmsCampaign::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SmsCampaign::SmsCampaign(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["campaign_name"].isNull())
        {
            campaignName_=std::make_shared<std::string>(r["campaign_name"].as<std::string>());
        }
        if(!r["campaign_type"].isNull())
        {
            campaignType_=std::make_shared<std::string>(r["campaign_type"].as<std::string>());
        }
        if(!r["message"].isNull())
        {
            message_=std::make_shared<std::string>(r["message"].as<std::string>());
        }
        if(!r["param_value"].isNull())
        {
            paramValue_=std::make_shared<std::string>(r["param_value"].as<std::string>());
        }
        if(!r["recurrence"].isNull())
        {
            recurrence_=std::make_shared<std::string>(r["recurrence"].as<std::string>());
        }
        if(!r["next_trigger_date"].isNull())
        {
            auto timeStr = r["next_trigger_date"].as<std::string>();
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
                nextTriggerDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
        }
        if(!r["provider_id"].isNull())
        {
            providerId_=std::make_shared<std::string>(r["provider_id"].as<std::string>());
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
            campaignName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            campaignType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            message_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            paramValue_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            recurrence_=std::make_shared<std::string>(r[index].as<std::string>());
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
                nextTriggerDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            providerId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
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
const std::string &SmsCampaign::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getId() const noexcept
{
    return id_;
}
void SmsCampaign::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SmsCampaign::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SmsCampaign::PrimaryKeyType & SmsCampaign::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SmsCampaign::getValueOfCampaignName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(campaignName_)
        return *campaignName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getCampaignName() const noexcept
{
    return campaignName_;
}
void SmsCampaign::setCampaignName(const std::string &pCampaignName) noexcept
{
    campaignName_ = std::make_shared<std::string>(pCampaignName);
    dirtyFlag_[1] = true;
}
void SmsCampaign::setCampaignName(std::string &&pCampaignName) noexcept
{
    campaignName_ = std::make_shared<std::string>(std::move(pCampaignName));
    dirtyFlag_[1] = true;
}

const std::string &SmsCampaign::getValueOfCampaignType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(campaignType_)
        return *campaignType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getCampaignType() const noexcept
{
    return campaignType_;
}
void SmsCampaign::setCampaignType(const std::string &pCampaignType) noexcept
{
    campaignType_ = std::make_shared<std::string>(pCampaignType);
    dirtyFlag_[2] = true;
}
void SmsCampaign::setCampaignType(std::string &&pCampaignType) noexcept
{
    campaignType_ = std::make_shared<std::string>(std::move(pCampaignType));
    dirtyFlag_[2] = true;
}

const std::string &SmsCampaign::getValueOfMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(message_)
        return *message_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getMessage() const noexcept
{
    return message_;
}
void SmsCampaign::setMessage(const std::string &pMessage) noexcept
{
    message_ = std::make_shared<std::string>(pMessage);
    dirtyFlag_[3] = true;
}
void SmsCampaign::setMessage(std::string &&pMessage) noexcept
{
    message_ = std::make_shared<std::string>(std::move(pMessage));
    dirtyFlag_[3] = true;
}

const std::string &SmsCampaign::getValueOfParamValue() const noexcept
{
    static const std::string defaultValue = std::string();
    if(paramValue_)
        return *paramValue_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getParamValue() const noexcept
{
    return paramValue_;
}
void SmsCampaign::setParamValue(const std::string &pParamValue) noexcept
{
    paramValue_ = std::make_shared<std::string>(pParamValue);
    dirtyFlag_[4] = true;
}
void SmsCampaign::setParamValue(std::string &&pParamValue) noexcept
{
    paramValue_ = std::make_shared<std::string>(std::move(pParamValue));
    dirtyFlag_[4] = true;
}

const std::string &SmsCampaign::getValueOfRecurrence() const noexcept
{
    static const std::string defaultValue = std::string();
    if(recurrence_)
        return *recurrence_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getRecurrence() const noexcept
{
    return recurrence_;
}
void SmsCampaign::setRecurrence(const std::string &pRecurrence) noexcept
{
    recurrence_ = std::make_shared<std::string>(pRecurrence);
    dirtyFlag_[5] = true;
}
void SmsCampaign::setRecurrence(std::string &&pRecurrence) noexcept
{
    recurrence_ = std::make_shared<std::string>(std::move(pRecurrence));
    dirtyFlag_[5] = true;
}
void SmsCampaign::setRecurrenceToNull() noexcept
{
    recurrence_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &SmsCampaign::getValueOfNextTriggerDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(nextTriggerDate_)
        return *nextTriggerDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SmsCampaign::getNextTriggerDate() const noexcept
{
    return nextTriggerDate_;
}
void SmsCampaign::setNextTriggerDate(const ::trantor::Date &pNextTriggerDate) noexcept
{
    nextTriggerDate_ = std::make_shared<::trantor::Date>(pNextTriggerDate);
    dirtyFlag_[6] = true;
}
void SmsCampaign::setNextTriggerDateToNull() noexcept
{
    nextTriggerDate_.reset();
    dirtyFlag_[6] = true;
}

const std::string &SmsCampaign::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getStatus() const noexcept
{
    return status_;
}
void SmsCampaign::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[7] = true;
}
void SmsCampaign::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[7] = true;
}

const std::string &SmsCampaign::getValueOfProviderId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(providerId_)
        return *providerId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SmsCampaign::getProviderId() const noexcept
{
    return providerId_;
}
void SmsCampaign::setProviderId(const std::string &pProviderId) noexcept
{
    providerId_ = std::make_shared<std::string>(pProviderId);
    dirtyFlag_[8] = true;
}
void SmsCampaign::setProviderId(std::string &&pProviderId) noexcept
{
    providerId_ = std::make_shared<std::string>(std::move(pProviderId));
    dirtyFlag_[8] = true;
}
void SmsCampaign::setProviderIdToNull() noexcept
{
    providerId_.reset();
    dirtyFlag_[8] = true;
}

const ::trantor::Date &SmsCampaign::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SmsCampaign::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SmsCampaign::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[9] = true;
}

const ::trantor::Date &SmsCampaign::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SmsCampaign::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void SmsCampaign::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[10] = true;
}

void SmsCampaign::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SmsCampaign::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "campaign_name",
        "campaign_type",
        "message",
        "param_value",
        "recurrence",
        "next_trigger_date",
        "status",
        "provider_id",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void SmsCampaign::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCampaignName())
        {
            binder << getValueOfCampaignName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCampaignType())
        {
            binder << getValueOfCampaignType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMessage())
        {
            binder << getValueOfMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getParamValue())
        {
            binder << getValueOfParamValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getRecurrence())
        {
            binder << getValueOfRecurrence();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getNextTriggerDate())
        {
            binder << getValueOfNextTriggerDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getProviderId())
        {
            binder << getValueOfProviderId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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

const std::vector<std::string> SmsCampaign::updateColumns() const
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

void SmsCampaign::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCampaignName())
        {
            binder << getValueOfCampaignName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCampaignType())
        {
            binder << getValueOfCampaignType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMessage())
        {
            binder << getValueOfMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getParamValue())
        {
            binder << getValueOfParamValue();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getRecurrence())
        {
            binder << getValueOfRecurrence();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getNextTriggerDate())
        {
            binder << getValueOfNextTriggerDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getProviderId())
        {
            binder << getValueOfProviderId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
