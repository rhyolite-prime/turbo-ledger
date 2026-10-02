/**
 *  ReportMailingJob.cc
 *
 *  See ReportMailingJob.h for the hand-authored-subset note.
 *
 */

#include "ReportMailingJob.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlNotificationDb;

const std::string ReportMailingJob::Cols::_id = "\"id\"";
const std::string ReportMailingJob::Cols::_name = "\"name\"";
const std::string ReportMailingJob::Cols::_description = "\"description\"";
const std::string ReportMailingJob::Cols::_report_name = "\"report_name\"";
const std::string ReportMailingJob::Cols::_report_params = "\"report_params\"";
const std::string ReportMailingJob::Cols::_start_date_time = "\"start_date_time\"";
const std::string ReportMailingJob::Cols::_recurrence = "\"recurrence\"";
const std::string ReportMailingJob::Cols::_email_recipients = "\"email_recipients\"";
const std::string ReportMailingJob::Cols::_email_subject = "\"email_subject\"";
const std::string ReportMailingJob::Cols::_email_message = "\"email_message\"";
const std::string ReportMailingJob::Cols::_email_attachment_file_format = "\"email_attachment_file_format\"";
const std::string ReportMailingJob::Cols::_is_active = "\"is_active\"";
const std::string ReportMailingJob::Cols::_previous_run_status = "\"previous_run_status\"";
const std::string ReportMailingJob::Cols::_previous_run_error_message = "\"previous_run_error_message\"";
const std::string ReportMailingJob::Cols::_previous_run_start_time = "\"previous_run_start_time\"";
const std::string ReportMailingJob::Cols::_previous_run_end_time = "\"previous_run_end_time\"";
const std::string ReportMailingJob::Cols::_next_run_time = "\"next_run_time\"";
const std::string ReportMailingJob::Cols::_created_at = "\"created_at\"";
const std::string ReportMailingJob::Cols::_updated_at = "\"updated_at\"";
const std::string ReportMailingJob::primaryKeyName = "id";
const bool ReportMailingJob::hasPrimaryKey = true;
const std::string ReportMailingJob::tableName = "\"report_mailing_jobs\"";

const std::vector<typename ReportMailingJob::MetaData> ReportMailingJob::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",200,0,0,1},
{"description","std::string","text",0,0,0,0},
{"report_name","std::string","character varying",200,0,0,1},
{"report_params","std::string","jsonb",0,0,0,1},
{"start_date_time","::trantor::Date","timestamp with time zone",0,0,0,1},
{"recurrence","std::string","character varying",100,0,0,0},
{"email_recipients","std::string","text",0,0,0,1},
{"email_subject","std::string","character varying",255,0,0,1},
{"email_message","std::string","text",0,0,0,0},
{"email_attachment_file_format","std::string","character varying",10,0,0,1},
{"is_active","bool","boolean",1,0,0,1},
{"previous_run_status","std::string","character varying",20,0,0,0},
{"previous_run_error_message","std::string","text",0,0,0,0},
{"previous_run_start_time","::trantor::Date","timestamp with time zone",0,0,0,0},
{"previous_run_end_time","::trantor::Date","timestamp with time zone",0,0,0,0},
{"next_run_time","::trantor::Date","timestamp with time zone",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ReportMailingJob::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ReportMailingJob::ReportMailingJob(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["report_name"].isNull())
        {
            reportName_=std::make_shared<std::string>(r["report_name"].as<std::string>());
        }
        if(!r["report_params"].isNull())
        {
            reportParams_=std::make_shared<std::string>(r["report_params"].as<std::string>());
        }
        if(!r["start_date_time"].isNull())
        {
            auto timeStr = r["start_date_time"].as<std::string>();
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
                startDateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["recurrence"].isNull())
        {
            recurrence_=std::make_shared<std::string>(r["recurrence"].as<std::string>());
        }
        if(!r["email_recipients"].isNull())
        {
            emailRecipients_=std::make_shared<std::string>(r["email_recipients"].as<std::string>());
        }
        if(!r["email_subject"].isNull())
        {
            emailSubject_=std::make_shared<std::string>(r["email_subject"].as<std::string>());
        }
        if(!r["email_message"].isNull())
        {
            emailMessage_=std::make_shared<std::string>(r["email_message"].as<std::string>());
        }
        if(!r["email_attachment_file_format"].isNull())
        {
            emailAttachmentFileFormat_=std::make_shared<std::string>(r["email_attachment_file_format"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["previous_run_status"].isNull())
        {
            previousRunStatus_=std::make_shared<std::string>(r["previous_run_status"].as<std::string>());
        }
        if(!r["previous_run_error_message"].isNull())
        {
            previousRunErrorMessage_=std::make_shared<std::string>(r["previous_run_error_message"].as<std::string>());
        }
        if(!r["previous_run_start_time"].isNull())
        {
            auto timeStr = r["previous_run_start_time"].as<std::string>();
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
                previousRunStartTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["previous_run_end_time"].isNull())
        {
            auto timeStr = r["previous_run_end_time"].as<std::string>();
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
                previousRunEndTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["next_run_time"].isNull())
        {
            auto timeStr = r["next_run_time"].as<std::string>();
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
                nextRunTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
        if(offset + 19 > r.size())
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
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            reportName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            reportParams_=std::make_shared<std::string>(r[index].as<std::string>());
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
                startDateTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            recurrence_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            emailRecipients_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            emailSubject_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            emailMessage_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            emailAttachmentFileFormat_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            previousRunStatus_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            previousRunErrorMessage_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 14;
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
                previousRunStartTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 15;
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
                previousRunEndTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 16;
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
                nextRunTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 17;
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
        index = offset + 18;
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
const std::string &ReportMailingJob::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getId() const noexcept
{
    return id_;
}
void ReportMailingJob::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ReportMailingJob::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ReportMailingJob::PrimaryKeyType & ReportMailingJob::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ReportMailingJob::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getName() const noexcept
{
    return name_;
}
void ReportMailingJob::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void ReportMailingJob::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const std::string &ReportMailingJob::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getDescription() const noexcept
{
    return description_;
}
void ReportMailingJob::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[2] = true;
}
void ReportMailingJob::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[2] = true;
}
void ReportMailingJob::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[2] = true;
}

const std::string &ReportMailingJob::getValueOfReportName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reportName_)
        return *reportName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getReportName() const noexcept
{
    return reportName_;
}
void ReportMailingJob::setReportName(const std::string &pReportName) noexcept
{
    reportName_ = std::make_shared<std::string>(pReportName);
    dirtyFlag_[3] = true;
}
void ReportMailingJob::setReportName(std::string &&pReportName) noexcept
{
    reportName_ = std::make_shared<std::string>(std::move(pReportName));
    dirtyFlag_[3] = true;
}

const std::string &ReportMailingJob::getValueOfReportParams() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reportParams_)
        return *reportParams_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getReportParams() const noexcept
{
    return reportParams_;
}
void ReportMailingJob::setReportParams(const std::string &pReportParams) noexcept
{
    reportParams_ = std::make_shared<std::string>(pReportParams);
    dirtyFlag_[4] = true;
}
void ReportMailingJob::setReportParams(std::string &&pReportParams) noexcept
{
    reportParams_ = std::make_shared<std::string>(std::move(pReportParams));
    dirtyFlag_[4] = true;
}

const ::trantor::Date &ReportMailingJob::getValueOfStartDateTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDateTime_)
        return *startDateTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJob::getStartDateTime() const noexcept
{
    return startDateTime_;
}
void ReportMailingJob::setStartDateTime(const ::trantor::Date &pStartDateTime) noexcept
{
    startDateTime_ = std::make_shared<::trantor::Date>(pStartDateTime);
    dirtyFlag_[5] = true;
}

const std::string &ReportMailingJob::getValueOfRecurrence() const noexcept
{
    static const std::string defaultValue = std::string();
    if(recurrence_)
        return *recurrence_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getRecurrence() const noexcept
{
    return recurrence_;
}
void ReportMailingJob::setRecurrence(const std::string &pRecurrence) noexcept
{
    recurrence_ = std::make_shared<std::string>(pRecurrence);
    dirtyFlag_[6] = true;
}
void ReportMailingJob::setRecurrence(std::string &&pRecurrence) noexcept
{
    recurrence_ = std::make_shared<std::string>(std::move(pRecurrence));
    dirtyFlag_[6] = true;
}
void ReportMailingJob::setRecurrenceToNull() noexcept
{
    recurrence_.reset();
    dirtyFlag_[6] = true;
}

const std::string &ReportMailingJob::getValueOfEmailRecipients() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailRecipients_)
        return *emailRecipients_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getEmailRecipients() const noexcept
{
    return emailRecipients_;
}
void ReportMailingJob::setEmailRecipients(const std::string &pEmailRecipients) noexcept
{
    emailRecipients_ = std::make_shared<std::string>(pEmailRecipients);
    dirtyFlag_[7] = true;
}
void ReportMailingJob::setEmailRecipients(std::string &&pEmailRecipients) noexcept
{
    emailRecipients_ = std::make_shared<std::string>(std::move(pEmailRecipients));
    dirtyFlag_[7] = true;
}

const std::string &ReportMailingJob::getValueOfEmailSubject() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailSubject_)
        return *emailSubject_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getEmailSubject() const noexcept
{
    return emailSubject_;
}
void ReportMailingJob::setEmailSubject(const std::string &pEmailSubject) noexcept
{
    emailSubject_ = std::make_shared<std::string>(pEmailSubject);
    dirtyFlag_[8] = true;
}
void ReportMailingJob::setEmailSubject(std::string &&pEmailSubject) noexcept
{
    emailSubject_ = std::make_shared<std::string>(std::move(pEmailSubject));
    dirtyFlag_[8] = true;
}

const std::string &ReportMailingJob::getValueOfEmailMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailMessage_)
        return *emailMessage_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getEmailMessage() const noexcept
{
    return emailMessage_;
}
void ReportMailingJob::setEmailMessage(const std::string &pEmailMessage) noexcept
{
    emailMessage_ = std::make_shared<std::string>(pEmailMessage);
    dirtyFlag_[9] = true;
}
void ReportMailingJob::setEmailMessage(std::string &&pEmailMessage) noexcept
{
    emailMessage_ = std::make_shared<std::string>(std::move(pEmailMessage));
    dirtyFlag_[9] = true;
}
void ReportMailingJob::setEmailMessageToNull() noexcept
{
    emailMessage_.reset();
    dirtyFlag_[9] = true;
}

const std::string &ReportMailingJob::getValueOfEmailAttachmentFileFormat() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailAttachmentFileFormat_)
        return *emailAttachmentFileFormat_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getEmailAttachmentFileFormat() const noexcept
{
    return emailAttachmentFileFormat_;
}
void ReportMailingJob::setEmailAttachmentFileFormat(const std::string &pEmailAttachmentFileFormat) noexcept
{
    emailAttachmentFileFormat_ = std::make_shared<std::string>(pEmailAttachmentFileFormat);
    dirtyFlag_[10] = true;
}
void ReportMailingJob::setEmailAttachmentFileFormat(std::string &&pEmailAttachmentFileFormat) noexcept
{
    emailAttachmentFileFormat_ = std::make_shared<std::string>(std::move(pEmailAttachmentFileFormat));
    dirtyFlag_[10] = true;
}

const bool &ReportMailingJob::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &ReportMailingJob::getIsActive() const noexcept
{
    return isActive_;
}
void ReportMailingJob::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[11] = true;
}

const std::string &ReportMailingJob::getValueOfPreviousRunStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(previousRunStatus_)
        return *previousRunStatus_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getPreviousRunStatus() const noexcept
{
    return previousRunStatus_;
}
void ReportMailingJob::setPreviousRunStatus(const std::string &pPreviousRunStatus) noexcept
{
    previousRunStatus_ = std::make_shared<std::string>(pPreviousRunStatus);
    dirtyFlag_[12] = true;
}
void ReportMailingJob::setPreviousRunStatus(std::string &&pPreviousRunStatus) noexcept
{
    previousRunStatus_ = std::make_shared<std::string>(std::move(pPreviousRunStatus));
    dirtyFlag_[12] = true;
}
void ReportMailingJob::setPreviousRunStatusToNull() noexcept
{
    previousRunStatus_.reset();
    dirtyFlag_[12] = true;
}

const std::string &ReportMailingJob::getValueOfPreviousRunErrorMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(previousRunErrorMessage_)
        return *previousRunErrorMessage_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJob::getPreviousRunErrorMessage() const noexcept
{
    return previousRunErrorMessage_;
}
void ReportMailingJob::setPreviousRunErrorMessage(const std::string &pPreviousRunErrorMessage) noexcept
{
    previousRunErrorMessage_ = std::make_shared<std::string>(pPreviousRunErrorMessage);
    dirtyFlag_[13] = true;
}
void ReportMailingJob::setPreviousRunErrorMessage(std::string &&pPreviousRunErrorMessage) noexcept
{
    previousRunErrorMessage_ = std::make_shared<std::string>(std::move(pPreviousRunErrorMessage));
    dirtyFlag_[13] = true;
}
void ReportMailingJob::setPreviousRunErrorMessageToNull() noexcept
{
    previousRunErrorMessage_.reset();
    dirtyFlag_[13] = true;
}

const ::trantor::Date &ReportMailingJob::getValueOfPreviousRunStartTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(previousRunStartTime_)
        return *previousRunStartTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJob::getPreviousRunStartTime() const noexcept
{
    return previousRunStartTime_;
}
void ReportMailingJob::setPreviousRunStartTime(const ::trantor::Date &pPreviousRunStartTime) noexcept
{
    previousRunStartTime_ = std::make_shared<::trantor::Date>(pPreviousRunStartTime);
    dirtyFlag_[14] = true;
}
void ReportMailingJob::setPreviousRunStartTimeToNull() noexcept
{
    previousRunStartTime_.reset();
    dirtyFlag_[14] = true;
}

const ::trantor::Date &ReportMailingJob::getValueOfPreviousRunEndTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(previousRunEndTime_)
        return *previousRunEndTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJob::getPreviousRunEndTime() const noexcept
{
    return previousRunEndTime_;
}
void ReportMailingJob::setPreviousRunEndTime(const ::trantor::Date &pPreviousRunEndTime) noexcept
{
    previousRunEndTime_ = std::make_shared<::trantor::Date>(pPreviousRunEndTime);
    dirtyFlag_[15] = true;
}
void ReportMailingJob::setPreviousRunEndTimeToNull() noexcept
{
    previousRunEndTime_.reset();
    dirtyFlag_[15] = true;
}

const ::trantor::Date &ReportMailingJob::getValueOfNextRunTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(nextRunTime_)
        return *nextRunTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJob::getNextRunTime() const noexcept
{
    return nextRunTime_;
}
void ReportMailingJob::setNextRunTime(const ::trantor::Date &pNextRunTime) noexcept
{
    nextRunTime_ = std::make_shared<::trantor::Date>(pNextRunTime);
    dirtyFlag_[16] = true;
}
void ReportMailingJob::setNextRunTimeToNull() noexcept
{
    nextRunTime_.reset();
    dirtyFlag_[16] = true;
}

const ::trantor::Date &ReportMailingJob::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJob::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ReportMailingJob::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[17] = true;
}

const ::trantor::Date &ReportMailingJob::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJob::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void ReportMailingJob::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[18] = true;
}

void ReportMailingJob::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ReportMailingJob::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "description",
        "report_name",
        "report_params",
        "start_date_time",
        "recurrence",
        "email_recipients",
        "email_subject",
        "email_message",
        "email_attachment_file_format",
        "is_active",
        "previous_run_status",
        "previous_run_error_message",
        "previous_run_start_time",
        "previous_run_end_time",
        "next_run_time",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void ReportMailingJob::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getReportName())
        {
            binder << getValueOfReportName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getReportParams())
        {
            binder << getValueOfReportParams();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getStartDateTime())
        {
            binder << getValueOfStartDateTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getEmailRecipients())
        {
            binder << getValueOfEmailRecipients();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getEmailSubject())
        {
            binder << getValueOfEmailSubject();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getEmailMessage())
        {
            binder << getValueOfEmailMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getEmailAttachmentFileFormat())
        {
            binder << getValueOfEmailAttachmentFileFormat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
    {
        if(getPreviousRunStatus())
        {
            binder << getValueOfPreviousRunStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getPreviousRunErrorMessage())
        {
            binder << getValueOfPreviousRunErrorMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getPreviousRunStartTime())
        {
            binder << getValueOfPreviousRunStartTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getPreviousRunEndTime())
        {
            binder << getValueOfPreviousRunEndTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getNextRunTime())
        {
            binder << getValueOfNextRunTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
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

const std::vector<std::string> ReportMailingJob::updateColumns() const
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
    if(dirtyFlag_[12])
    {
        ret.push_back(getColumnName(12));
    }
    if(dirtyFlag_[13])
    {
        ret.push_back(getColumnName(13));
    }
    if(dirtyFlag_[14])
    {
        ret.push_back(getColumnName(14));
    }
    if(dirtyFlag_[15])
    {
        ret.push_back(getColumnName(15));
    }
    if(dirtyFlag_[16])
    {
        ret.push_back(getColumnName(16));
    }
    if(dirtyFlag_[17])
    {
        ret.push_back(getColumnName(17));
    }
    if(dirtyFlag_[18])
    {
        ret.push_back(getColumnName(18));
    }
    return ret;
}

void ReportMailingJob::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getReportName())
        {
            binder << getValueOfReportName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getReportParams())
        {
            binder << getValueOfReportParams();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getStartDateTime())
        {
            binder << getValueOfStartDateTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getEmailRecipients())
        {
            binder << getValueOfEmailRecipients();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getEmailSubject())
        {
            binder << getValueOfEmailSubject();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getEmailMessage())
        {
            binder << getValueOfEmailMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getEmailAttachmentFileFormat())
        {
            binder << getValueOfEmailAttachmentFileFormat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
    {
        if(getPreviousRunStatus())
        {
            binder << getValueOfPreviousRunStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getPreviousRunErrorMessage())
        {
            binder << getValueOfPreviousRunErrorMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getPreviousRunStartTime())
        {
            binder << getValueOfPreviousRunStartTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getPreviousRunEndTime())
        {
            binder << getValueOfPreviousRunEndTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getNextRunTime())
        {
            binder << getValueOfNextRunTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
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
