/**
 *  JobRunHistory.cc
 *
 *  See JobRunHistory.h for the hand-authored-subset note.
 *
 */

#include "JobRunHistory.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlHeartBeatDb;

const std::string JobRunHistory::Cols::_id = "\"id\"";
const std::string JobRunHistory::Cols::_job_id = "\"job_id\"";
const std::string JobRunHistory::Cols::_version = "\"version\"";
const std::string JobRunHistory::Cols::_start_time = "\"start_time\"";
const std::string JobRunHistory::Cols::_end_time = "\"end_time\"";
const std::string JobRunHistory::Cols::_status = "\"status\"";
const std::string JobRunHistory::Cols::_trigger_type = "\"trigger_type\"";
const std::string JobRunHistory::Cols::_error_log = "\"error_log\"";
const std::string JobRunHistory::Cols::_created_at = "\"created_at\"";
const std::string JobRunHistory::primaryKeyName = "id";
const bool JobRunHistory::hasPrimaryKey = true;
const std::string JobRunHistory::tableName = "\"job_run_history\"";

const std::vector<typename JobRunHistory::MetaData> JobRunHistory::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"job_id","std::string","uuid",0,0,0,1},
{"version","int64_t","bigint",8,0,0,1},
{"start_time","::trantor::Date","timestamp with time zone",0,0,0,1},
{"end_time","::trantor::Date","timestamp with time zone",0,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"trigger_type","std::string","character varying",20,0,0,1},
{"error_log","std::string","text",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &JobRunHistory::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
JobRunHistory::JobRunHistory(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["version"].isNull())
        {
            version_=std::make_shared<int64_t>(r["version"].as<int64_t>());
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
        if(!r["trigger_type"].isNull())
        {
            triggerType_=std::make_shared<std::string>(r["trigger_type"].as<std::string>());
        }
        if(!r["error_log"].isNull())
        {
            errorLog_=std::make_shared<std::string>(r["error_log"].as<std::string>());
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
            jobId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            version_=std::make_shared<int64_t>(r[index].as<int64_t>());
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
                startTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
                endTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            triggerType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            errorLog_=std::make_shared<std::string>(r[index].as<std::string>());
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
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &JobRunHistory::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobRunHistory::getId() const noexcept
{
    return id_;
}
void JobRunHistory::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void JobRunHistory::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename JobRunHistory::PrimaryKeyType & JobRunHistory::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &JobRunHistory::getValueOfJobId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(jobId_)
        return *jobId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobRunHistory::getJobId() const noexcept
{
    return jobId_;
}
void JobRunHistory::setJobId(const std::string &pJobId) noexcept
{
    jobId_ = std::make_shared<std::string>(pJobId);
    dirtyFlag_[1] = true;
}
void JobRunHistory::setJobId(std::string &&pJobId) noexcept
{
    jobId_ = std::make_shared<std::string>(std::move(pJobId));
    dirtyFlag_[1] = true;
}

const int64_t &JobRunHistory::getValueOfVersion() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(version_)
        return *version_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &JobRunHistory::getVersion() const noexcept
{
    return version_;
}
void JobRunHistory::setVersion(const int64_t &pVersion) noexcept
{
    version_ = std::make_shared<int64_t>(pVersion);
    dirtyFlag_[2] = true;
}

const ::trantor::Date &JobRunHistory::getValueOfStartTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startTime_)
        return *startTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JobRunHistory::getStartTime() const noexcept
{
    return startTime_;
}
void JobRunHistory::setStartTime(const ::trantor::Date &pStartTime) noexcept
{
    startTime_ = std::make_shared<::trantor::Date>(pStartTime);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &JobRunHistory::getValueOfEndTime() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(endTime_)
        return *endTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JobRunHistory::getEndTime() const noexcept
{
    return endTime_;
}
void JobRunHistory::setEndTime(const ::trantor::Date &pEndTime) noexcept
{
    endTime_ = std::make_shared<::trantor::Date>(pEndTime);
    dirtyFlag_[4] = true;
}
void JobRunHistory::setEndTimeToNull() noexcept
{
    endTime_.reset();
    dirtyFlag_[4] = true;
}

const std::string &JobRunHistory::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobRunHistory::getStatus() const noexcept
{
    return status_;
}
void JobRunHistory::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[5] = true;
}
void JobRunHistory::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[5] = true;
}

const std::string &JobRunHistory::getValueOfTriggerType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(triggerType_)
        return *triggerType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobRunHistory::getTriggerType() const noexcept
{
    return triggerType_;
}
void JobRunHistory::setTriggerType(const std::string &pTriggerType) noexcept
{
    triggerType_ = std::make_shared<std::string>(pTriggerType);
    dirtyFlag_[6] = true;
}
void JobRunHistory::setTriggerType(std::string &&pTriggerType) noexcept
{
    triggerType_ = std::make_shared<std::string>(std::move(pTriggerType));
    dirtyFlag_[6] = true;
}

const std::string &JobRunHistory::getValueOfErrorLog() const noexcept
{
    static const std::string defaultValue = std::string();
    if(errorLog_)
        return *errorLog_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobRunHistory::getErrorLog() const noexcept
{
    return errorLog_;
}
void JobRunHistory::setErrorLog(const std::string &pErrorLog) noexcept
{
    errorLog_ = std::make_shared<std::string>(pErrorLog);
    dirtyFlag_[7] = true;
}
void JobRunHistory::setErrorLog(std::string &&pErrorLog) noexcept
{
    errorLog_ = std::make_shared<std::string>(std::move(pErrorLog));
    dirtyFlag_[7] = true;
}
void JobRunHistory::setErrorLogToNull() noexcept
{
    errorLog_.reset();
    dirtyFlag_[7] = true;
}

const ::trantor::Date &JobRunHistory::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JobRunHistory::getCreatedAt() const noexcept
{
    return createdAt_;
}
void JobRunHistory::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}

void JobRunHistory::updateId(const uint64_t id)
{
}

const std::vector<std::string> &JobRunHistory::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "job_id",
        "version",
        "start_time",
        "end_time",
        "status",
        "trigger_type",
        "error_log",
        "created_at"
    };
    return inCols;
}

void JobRunHistory::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getVersion())
        {
            binder << getValueOfVersion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getTriggerType())
        {
            binder << getValueOfTriggerType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getErrorLog())
        {
            binder << getValueOfErrorLog();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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

const std::vector<std::string> JobRunHistory::updateColumns() const
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

void JobRunHistory::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getVersion())
        {
            binder << getValueOfVersion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getTriggerType())
        {
            binder << getValueOfTriggerType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getErrorLog())
        {
            binder << getValueOfErrorLog();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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
