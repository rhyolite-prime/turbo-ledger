/**
 *  ReportMailingJobRunHistory.cc
 *
 *  See ReportMailingJobRunHistory.h for the hand-authored-subset note.
 *
 */

#include "ReportMailingJobRunHistory.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlNotificationDb;

const std::string ReportMailingJobRunHistory::Cols::_id = "\"id\"";
const std::string ReportMailingJobRunHistory::Cols::_job_id = "\"job_id\"";
const std::string ReportMailingJobRunHistory::Cols::_start_time = "\"start_time\"";
const std::string ReportMailingJobRunHistory::Cols::_end_time = "\"end_time\"";
const std::string ReportMailingJobRunHistory::Cols::_status = "\"status\"";
const std::string ReportMailingJobRunHistory::Cols::_error_message = "\"error_message\"";
const std::string ReportMailingJobRunHistory::Cols::_created_at = "\"created_at\"";
const std::string ReportMailingJobRunHistory::primaryKeyName = "id";
const bool ReportMailingJobRunHistory::hasPrimaryKey = true;
const std::string ReportMailingJobRunHistory::tableName = "\"report_mailing_job_run_history\"";

const std::vector<typename ReportMailingJobRunHistory::MetaData> ReportMailingJobRunHistory::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"job_id","std::string","uuid",0,0,0,1},
{"start_time","::trantor::Date","timestamp with time zone",0,0,0,1},
{"end_time","::trantor::Date","timestamp with time zone",0,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"error_message","std::string","text",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ReportMailingJobRunHistory::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ReportMailingJobRunHistory::ReportMailingJobRunHistory(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["job_id"].isNull())
        {
            jobId_=std::make_shared<std::string>(r["job_id"].as<std::string>());
        }
        if(!r["start_time"].isNull())
        {
            auto timeStr = r["start_time"].as<std::string>();
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
                startTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["end_time"].isNull())
        {
            auto timeStr = r["end_time"].as<std::string>();
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
                endTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
        }
        if(!r["error_message"].isNull())
        {
            errorMessage_=std::make_shared<std::string>(r["error_message"].as<std::string>());
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
            jobId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
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
                startTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 3;
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
                endTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            errorMessage_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &ReportMailingJobRunHistory::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJobRunHistory::getId() const noexcept
{
    return id_;
}
void ReportMailingJobRunHistory::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ReportMailingJobRunHistory::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ReportMailingJobRunHistory::PrimaryKeyType & ReportMailingJobRunHistory::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ReportMailingJobRunHistory::getValueOfJobId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(jobId_)
        return *jobId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJobRunHistory::getJobId() const noexcept
{
    return jobId_;
}
void ReportMailingJobRunHistory::setJobId(const std::string &pJobId) noexcept
{
    jobId_ = std::make_shared<std::string>(pJobId);
    dirtyFlag_[1] = true;
}
void ReportMailingJobRunHistory::setJobId(std::string &&pJobId) noexcept
{
    jobId_ = std::make_shared<std::string>(std::move(pJobId));
    dirtyFlag_[1] = true;
}

const ::trantor::Date &ReportMailingJobRunHistory::getValueOfStartTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startTime_)
        return *startTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJobRunHistory::getStartTime() const noexcept
{
    return startTime_;
}
void ReportMailingJobRunHistory::setStartTime(const ::trantor::Date &pStartTime) noexcept
{
    startTime_ = std::make_shared<::trantor::Date>(pStartTime);
    dirtyFlag_[2] = true;
}

const ::trantor::Date &ReportMailingJobRunHistory::getValueOfEndTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(endTime_)
        return *endTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJobRunHistory::getEndTime() const noexcept
{
    return endTime_;
}
void ReportMailingJobRunHistory::setEndTime(const ::trantor::Date &pEndTime) noexcept
{
    endTime_ = std::make_shared<::trantor::Date>(pEndTime);
    dirtyFlag_[3] = true;
}
void ReportMailingJobRunHistory::setEndTimeToNull() noexcept
{
    endTime_.reset();
    dirtyFlag_[3] = true;
}

const std::string &ReportMailingJobRunHistory::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJobRunHistory::getStatus() const noexcept
{
    return status_;
}
void ReportMailingJobRunHistory::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[4] = true;
}
void ReportMailingJobRunHistory::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[4] = true;
}

const std::string &ReportMailingJobRunHistory::getValueOfErrorMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(errorMessage_)
        return *errorMessage_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ReportMailingJobRunHistory::getErrorMessage() const noexcept
{
    return errorMessage_;
}
void ReportMailingJobRunHistory::setErrorMessage(const std::string &pErrorMessage) noexcept
{
    errorMessage_ = std::make_shared<std::string>(pErrorMessage);
    dirtyFlag_[5] = true;
}
void ReportMailingJobRunHistory::setErrorMessage(std::string &&pErrorMessage) noexcept
{
    errorMessage_ = std::make_shared<std::string>(std::move(pErrorMessage));
    dirtyFlag_[5] = true;
}
void ReportMailingJobRunHistory::setErrorMessageToNull() noexcept
{
    errorMessage_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &ReportMailingJobRunHistory::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ReportMailingJobRunHistory::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ReportMailingJobRunHistory::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[6] = true;
}

void ReportMailingJobRunHistory::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ReportMailingJobRunHistory::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "job_id",
        "start_time",
        "end_time",
        "status",
        "error_message",
        "created_at"
    };
    return inCols;
}

void ReportMailingJobRunHistory::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getJobId())
        {
            binder << getValueOfJobId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getStartTime())
        {
            binder << getValueOfStartTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getEndTime())
        {
            binder << getValueOfEndTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getErrorMessage())
        {
            binder << getValueOfErrorMessage();
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

const std::vector<std::string> ReportMailingJobRunHistory::updateColumns() const
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

void ReportMailingJobRunHistory::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getJobId())
        {
            binder << getValueOfJobId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getStartTime())
        {
            binder << getValueOfStartTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getEndTime())
        {
            binder << getValueOfEndTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getErrorMessage())
        {
            binder << getValueOfErrorMessage();
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
