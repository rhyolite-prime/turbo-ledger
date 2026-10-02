/**
 *  JobBusinessStep.cc
 *
 *  See JobBusinessStep.h for the hand-authored-subset note.
 *
 */

#include "JobBusinessStep.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlHeartBeatDb;

const std::string JobBusinessStep::Cols::_id = "\"id\"";
const std::string JobBusinessStep::Cols::_job_id = "\"job_id\"";
const std::string JobBusinessStep::Cols::_step_name = "\"step_name\"";
const std::string JobBusinessStep::Cols::_step_order = "\"step_order\"";
const std::string JobBusinessStep::Cols::_is_enabled = "\"is_enabled\"";
const std::string JobBusinessStep::Cols::_created_at = "\"created_at\"";
const std::string JobBusinessStep::Cols::_updated_at = "\"updated_at\"";
const std::string JobBusinessStep::primaryKeyName = "id";
const bool JobBusinessStep::hasPrimaryKey = true;
const std::string JobBusinessStep::tableName = "\"job_business_steps\"";

const std::vector<typename JobBusinessStep::MetaData> JobBusinessStep::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"job_id","std::string","uuid",0,0,0,1},
{"step_name","std::string","character varying",200,0,0,1},
{"step_order","int32_t","integer",4,0,0,1},
{"is_enabled","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &JobBusinessStep::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
JobBusinessStep::JobBusinessStep(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["step_name"].isNull())
        {
            stepName_=std::make_shared<std::string>(r["step_name"].as<std::string>());
        }
        if(!r["step_order"].isNull())
        {
            stepOrder_=std::make_shared<int32_t>(r["step_order"].as<int32_t>());
        }
        if(!r["is_enabled"].isNull())
        {
            isEnabled_=std::make_shared<bool>(r["is_enabled"].as<bool>());
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
            stepName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            stepOrder_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            isEnabled_=std::make_shared<bool>(r[index].as<bool>());
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &JobBusinessStep::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobBusinessStep::getId() const noexcept
{
    return id_;
}
void JobBusinessStep::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void JobBusinessStep::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename JobBusinessStep::PrimaryKeyType & JobBusinessStep::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &JobBusinessStep::getValueOfJobId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(jobId_)
        return *jobId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobBusinessStep::getJobId() const noexcept
{
    return jobId_;
}
void JobBusinessStep::setJobId(const std::string &pJobId) noexcept
{
    jobId_ = std::make_shared<std::string>(pJobId);
    dirtyFlag_[1] = true;
}
void JobBusinessStep::setJobId(std::string &&pJobId) noexcept
{
    jobId_ = std::make_shared<std::string>(std::move(pJobId));
    dirtyFlag_[1] = true;
}

const std::string &JobBusinessStep::getValueOfStepName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(stepName_)
        return *stepName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JobBusinessStep::getStepName() const noexcept
{
    return stepName_;
}
void JobBusinessStep::setStepName(const std::string &pStepName) noexcept
{
    stepName_ = std::make_shared<std::string>(pStepName);
    dirtyFlag_[2] = true;
}
void JobBusinessStep::setStepName(std::string &&pStepName) noexcept
{
    stepName_ = std::make_shared<std::string>(std::move(pStepName));
    dirtyFlag_[2] = true;
}

const int32_t &JobBusinessStep::getValueOfStepOrder() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(stepOrder_)
        return *stepOrder_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &JobBusinessStep::getStepOrder() const noexcept
{
    return stepOrder_;
}
void JobBusinessStep::setStepOrder(const int32_t &pStepOrder) noexcept
{
    stepOrder_ = std::make_shared<int32_t>(pStepOrder);
    dirtyFlag_[3] = true;
}

const bool &JobBusinessStep::getValueOfIsEnabled() const noexcept
{
    static const bool defaultValue = bool();
    if(isEnabled_)
        return *isEnabled_;
    return defaultValue;
}
const std::shared_ptr<bool> &JobBusinessStep::getIsEnabled() const noexcept
{
    return isEnabled_;
}
void JobBusinessStep::setIsEnabled(const bool &pIsEnabled) noexcept
{
    isEnabled_ = std::make_shared<bool>(pIsEnabled);
    dirtyFlag_[4] = true;
}

const ::trantor::Date &JobBusinessStep::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JobBusinessStep::getCreatedAt() const noexcept
{
    return createdAt_;
}
void JobBusinessStep::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

const ::trantor::Date &JobBusinessStep::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JobBusinessStep::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void JobBusinessStep::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[6] = true;
}

void JobBusinessStep::updateId(const uint64_t id)
{
}

const std::vector<std::string> &JobBusinessStep::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "job_id",
        "step_name",
        "step_order",
        "is_enabled",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void JobBusinessStep::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getStepName())
        {
            binder << getValueOfStepName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getStepOrder())
        {
            binder << getValueOfStepOrder();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIsEnabled())
        {
            binder << getValueOfIsEnabled();
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
    if(dirtyFlag_[6])
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

const std::vector<std::string> JobBusinessStep::updateColumns() const
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

void JobBusinessStep::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getStepName())
        {
            binder << getValueOfStepName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getStepOrder())
        {
            binder << getValueOfStepOrder();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIsEnabled())
        {
            binder << getValueOfIsEnabled();
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
    if(dirtyFlag_[6])
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
