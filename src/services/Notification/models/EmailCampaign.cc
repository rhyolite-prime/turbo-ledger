/**
 *  EmailCampaign.cc
 *
 *  See EmailCampaign.h for the hand-authored-subset note.
 *
 */

#include "EmailCampaign.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlNotificationDb;

const std::string EmailCampaign::Cols::_id = "\"id\"";
const std::string EmailCampaign::Cols::_campaign_name = "\"campaign_name\"";
const std::string EmailCampaign::Cols::_subject = "\"subject\"";
const std::string EmailCampaign::Cols::_message = "\"message\"";
const std::string EmailCampaign::Cols::_param_value = "\"param_value\"";
const std::string EmailCampaign::Cols::_recurrence = "\"recurrence\"";
const std::string EmailCampaign::Cols::_next_trigger_date = "\"next_trigger_date\"";
const std::string EmailCampaign::Cols::_status = "\"status\"";
const std::string EmailCampaign::Cols::_attachment_file_format = "\"attachment_file_format\"";
const std::string EmailCampaign::Cols::_stretchy_report_name = "\"stretchy_report_name\"";
const std::string EmailCampaign::Cols::_created_at = "\"created_at\"";
const std::string EmailCampaign::Cols::_updated_at = "\"updated_at\"";
const std::string EmailCampaign::primaryKeyName = "id";
const bool EmailCampaign::hasPrimaryKey = true;
const std::string EmailCampaign::tableName = "\"email_campaigns\"";

const std::vector<typename EmailCampaign::MetaData> EmailCampaign::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"campaign_name","std::string","character varying",200,0,0,1},
{"subject","std::string","character varying",255,0,0,1},
{"message","std::string","text",0,0,0,1},
{"param_value","std::string","jsonb",0,0,0,1},
{"recurrence","std::string","character varying",100,0,0,0},
{"next_trigger_date","::trantor::Date","timestamp with time zone",0,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"attachment_file_format","std::string","character varying",10,0,0,0},
{"stretchy_report_name","std::string","character varying",200,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &EmailCampaign::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
EmailCampaign::EmailCampaign(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["subject"].isNull())
        {
            subject_=std::make_shared<std::string>(r["subject"].as<std::string>());
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
        if(!r["attachment_file_format"].isNull())
        {
            attachmentFileFormat_=std::make_shared<std::string>(r["attachment_file_format"].as<std::string>());
        }
        if(!r["stretchy_report_name"].isNull())
        {
            stretchyReportName_=std::make_shared<std::string>(r["stretchy_report_name"].as<std::string>());
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
        if(offset + 12 > r.size())
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
            subject_=std::make_shared<std::string>(r[index].as<std::string>());
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
            attachmentFileFormat_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            stretchyReportName_=std::make_shared<std::string>(r[index].as<std::string>());
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
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 11;
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
const std::string &EmailCampaign::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getId() const noexcept
{
    return id_;
}
void EmailCampaign::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void EmailCampaign::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename EmailCampaign::PrimaryKeyType & EmailCampaign::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &EmailCampaign::getValueOfCampaignName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(campaignName_)
        return *campaignName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getCampaignName() const noexcept
{
    return campaignName_;
}
void EmailCampaign::setCampaignName(const std::string &pCampaignName) noexcept
{
    campaignName_ = std::make_shared<std::string>(pCampaignName);
    dirtyFlag_[1] = true;
}
void EmailCampaign::setCampaignName(std::string &&pCampaignName) noexcept
{
    campaignName_ = std::make_shared<std::string>(std::move(pCampaignName));
    dirtyFlag_[1] = true;
}

const std::string &EmailCampaign::getValueOfSubject() const noexcept
{
    static const std::string defaultValue = std::string();
    if(subject_)
        return *subject_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getSubject() const noexcept
{
    return subject_;
}
void EmailCampaign::setSubject(const std::string &pSubject) noexcept
{
    subject_ = std::make_shared<std::string>(pSubject);
    dirtyFlag_[2] = true;
}
void EmailCampaign::setSubject(std::string &&pSubject) noexcept
{
    subject_ = std::make_shared<std::string>(std::move(pSubject));
    dirtyFlag_[2] = true;
}

const std::string &EmailCampaign::getValueOfMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(message_)
        return *message_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getMessage() const noexcept
{
    return message_;
}
void EmailCampaign::setMessage(const std::string &pMessage) noexcept
{
    message_ = std::make_shared<std::string>(pMessage);
    dirtyFlag_[3] = true;
}
void EmailCampaign::setMessage(std::string &&pMessage) noexcept
{
    message_ = std::make_shared<std::string>(std::move(pMessage));
    dirtyFlag_[3] = true;
}

const std::string &EmailCampaign::getValueOfParamValue() const noexcept
{
    static const std::string defaultValue = std::string();
    if(paramValue_)
        return *paramValue_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getParamValue() const noexcept
{
    return paramValue_;
}
void EmailCampaign::setParamValue(const std::string &pParamValue) noexcept
{
    paramValue_ = std::make_shared<std::string>(pParamValue);
    dirtyFlag_[4] = true;
}
void EmailCampaign::setParamValue(std::string &&pParamValue) noexcept
{
    paramValue_ = std::make_shared<std::string>(std::move(pParamValue));
    dirtyFlag_[4] = true;
}

const std::string &EmailCampaign::getValueOfRecurrence() const noexcept
{
    static const std::string defaultValue = std::string();
    if(recurrence_)
        return *recurrence_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getRecurrence() const noexcept
{
    return recurrence_;
}
void EmailCampaign::setRecurrence(const std::string &pRecurrence) noexcept
{
    recurrence_ = std::make_shared<std::string>(pRecurrence);
    dirtyFlag_[5] = true;
}
void EmailCampaign::setRecurrence(std::string &&pRecurrence) noexcept
{
    recurrence_ = std::make_shared<std::string>(std::move(pRecurrence));
    dirtyFlag_[5] = true;
}
void EmailCampaign::setRecurrenceToNull() noexcept
{
    recurrence_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &EmailCampaign::getValueOfNextTriggerDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(nextTriggerDate_)
        return *nextTriggerDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &EmailCampaign::getNextTriggerDate() const noexcept
{
    return nextTriggerDate_;
}
void EmailCampaign::setNextTriggerDate(const ::trantor::Date &pNextTriggerDate) noexcept
{
    nextTriggerDate_ = std::make_shared<::trantor::Date>(pNextTriggerDate);
    dirtyFlag_[6] = true;
}
void EmailCampaign::setNextTriggerDateToNull() noexcept
{
    nextTriggerDate_.reset();
    dirtyFlag_[6] = true;
}

const std::string &EmailCampaign::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getStatus() const noexcept
{
    return status_;
}
void EmailCampaign::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[7] = true;
}
void EmailCampaign::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[7] = true;
}

const std::string &EmailCampaign::getValueOfAttachmentFileFormat() const noexcept
{
    static const std::string defaultValue = std::string();
    if(attachmentFileFormat_)
        return *attachmentFileFormat_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getAttachmentFileFormat() const noexcept
{
    return attachmentFileFormat_;
}
void EmailCampaign::setAttachmentFileFormat(const std::string &pAttachmentFileFormat) noexcept
{
    attachmentFileFormat_ = std::make_shared<std::string>(pAttachmentFileFormat);
    dirtyFlag_[8] = true;
}
void EmailCampaign::setAttachmentFileFormat(std::string &&pAttachmentFileFormat) noexcept
{
    attachmentFileFormat_ = std::make_shared<std::string>(std::move(pAttachmentFileFormat));
    dirtyFlag_[8] = true;
}
void EmailCampaign::setAttachmentFileFormatToNull() noexcept
{
    attachmentFileFormat_.reset();
    dirtyFlag_[8] = true;
}

const std::string &EmailCampaign::getValueOfStretchyReportName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(stretchyReportName_)
        return *stretchyReportName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailCampaign::getStretchyReportName() const noexcept
{
    return stretchyReportName_;
}
void EmailCampaign::setStretchyReportName(const std::string &pStretchyReportName) noexcept
{
    stretchyReportName_ = std::make_shared<std::string>(pStretchyReportName);
    dirtyFlag_[9] = true;
}
void EmailCampaign::setStretchyReportName(std::string &&pStretchyReportName) noexcept
{
    stretchyReportName_ = std::make_shared<std::string>(std::move(pStretchyReportName));
    dirtyFlag_[9] = true;
}
void EmailCampaign::setStretchyReportNameToNull() noexcept
{
    stretchyReportName_.reset();
    dirtyFlag_[9] = true;
}

const ::trantor::Date &EmailCampaign::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &EmailCampaign::getCreatedAt() const noexcept
{
    return createdAt_;
}
void EmailCampaign::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[10] = true;
}

const ::trantor::Date &EmailCampaign::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &EmailCampaign::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void EmailCampaign::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[11] = true;
}

void EmailCampaign::updateId(const uint64_t id)
{
}

const std::vector<std::string> &EmailCampaign::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "campaign_name",
        "subject",
        "message",
        "param_value",
        "recurrence",
        "next_trigger_date",
        "status",
        "attachment_file_format",
        "stretchy_report_name",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void EmailCampaign::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSubject())
        {
            binder << getValueOfSubject();
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
        if(getAttachmentFileFormat())
        {
            binder << getValueOfAttachmentFileFormat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getStretchyReportName())
        {
            binder << getValueOfStretchyReportName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
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

const std::vector<std::string> EmailCampaign::updateColumns() const
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
    if(dirtyFlag_[11])
    {
        ret.push_back(getColumnName(11));
    }
    return ret;
}

void EmailCampaign::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSubject())
        {
            binder << getValueOfSubject();
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
        if(getAttachmentFileFormat())
        {
            binder << getValueOfAttachmentFileFormat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getStretchyReportName())
        {
            binder << getValueOfStretchyReportName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
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
