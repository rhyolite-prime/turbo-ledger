/**
 *  Job.cc
 *
 *  See Job.h for the hand-authored-subset note.
 *
 */

#include "Job.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlHeartBeatDb;

const std::string Job::Cols::_id = "\"id\"";
const std::string Job::Cols::_short_name = "\"short_name\"";
const std::string Job::Cols::_display_name = "\"display_name\"";
const std::string Job::Cols::_description = "\"description\"";
const std::string Job::Cols::_cron_expression = "\"cron_expression\"";
const std::string Job::Cols::_is_active = "\"is_active\"";
const std::string Job::Cols::_is_misfired = "\"is_misfired\"";
const std::string Job::Cols::_created_at = "\"created_at\"";
const std::string Job::Cols::_updated_at = "\"updated_at\"";
const std::string Job::primaryKeyName = "id";
const bool Job::hasPrimaryKey = true;
const std::string Job::tableName = "\"jobs\"";

const std::vector<typename Job::MetaData> Job::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"short_name","std::string","character varying",100,0,0,1},
{"display_name","std::string","character varying",200,0,0,1},
{"description","std::string","text",0,0,0,0},
{"cron_expression","std::string","character varying",100,0,0,0},
{"is_active","bool","boolean",1,0,0,1},
{"is_misfired","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Job::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Job::Job(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["short_name"].isNull())
        {
            shortName_=std::make_shared<std::string>(r["short_name"].as<std::string>());
        }
        if(!r["display_name"].isNull())
        {
            displayName_=std::make_shared<std::string>(r["display_name"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["cron_expression"].isNull())
        {
            cronExpression_=std::make_shared<std::string>(r["cron_expression"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["is_misfired"].isNull())
        {
            isMisfired_=std::make_shared<bool>(r["is_misfired"].as<bool>());
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
            shortName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            displayName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            cronExpression_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            isMisfired_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 7;
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &Job::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Job::getId() const noexcept
{
    return id_;
}
void Job::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Job::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Job::PrimaryKeyType & Job::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Job::getValueOfShortName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shortName_)
        return *shortName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Job::getShortName() const noexcept
{
    return shortName_;
}
void Job::setShortName(const std::string &pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(pShortName);
    dirtyFlag_[1] = true;
}
void Job::setShortName(std::string &&pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(std::move(pShortName));
    dirtyFlag_[1] = true;
}

const std::string &Job::getValueOfDisplayName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(displayName_)
        return *displayName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Job::getDisplayName() const noexcept
{
    return displayName_;
}
void Job::setDisplayName(const std::string &pDisplayName) noexcept
{
    displayName_ = std::make_shared<std::string>(pDisplayName);
    dirtyFlag_[2] = true;
}
void Job::setDisplayName(std::string &&pDisplayName) noexcept
{
    displayName_ = std::make_shared<std::string>(std::move(pDisplayName));
    dirtyFlag_[2] = true;
}

const std::string &Job::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Job::getDescription() const noexcept
{
    return description_;
}
void Job::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void Job::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void Job::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const std::string &Job::getValueOfCronExpression() const noexcept
{
    static const std::string defaultValue = std::string();
    if(cronExpression_)
        return *cronExpression_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Job::getCronExpression() const noexcept
{
    return cronExpression_;
}
void Job::setCronExpression(const std::string &pCronExpression) noexcept
{
    cronExpression_ = std::make_shared<std::string>(pCronExpression);
    dirtyFlag_[4] = true;
}
void Job::setCronExpression(std::string &&pCronExpression) noexcept
{
    cronExpression_ = std::make_shared<std::string>(std::move(pCronExpression));
    dirtyFlag_[4] = true;
}
void Job::setCronExpressionToNull() noexcept
{
    cronExpression_.reset();
    dirtyFlag_[4] = true;
}

const bool &Job::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &Job::getIsActive() const noexcept
{
    return isActive_;
}
void Job::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[5] = true;
}

const bool &Job::getValueOfIsMisfired() const noexcept
{
    static const bool defaultValue = bool();
    if(isMisfired_)
        return *isMisfired_;
    return defaultValue;
}
const std::shared_ptr<bool> &Job::getIsMisfired() const noexcept
{
    return isMisfired_;
}
void Job::setIsMisfired(const bool &pIsMisfired) noexcept
{
    isMisfired_ = std::make_shared<bool>(pIsMisfired);
    dirtyFlag_[6] = true;
}

const ::trantor::Date &Job::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Job::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Job::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

const ::trantor::Date &Job::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Job::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void Job::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[8] = true;
}

void Job::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Job::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "short_name",
        "display_name",
        "description",
        "cron_expression",
        "is_active",
        "is_misfired",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void Job::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShortName())
        {
            binder << getValueOfShortName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDisplayName())
        {
            binder << getValueOfDisplayName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getCronExpression())
        {
            binder << getValueOfCronExpression();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getIsMisfired())
        {
            binder << getValueOfIsMisfired();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
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

const std::vector<std::string> Job::updateColumns() const
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

void Job::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShortName())
        {
            binder << getValueOfShortName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDisplayName())
        {
            binder << getValueOfDisplayName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getCronExpression())
        {
            binder << getValueOfCronExpression();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getIsMisfired())
        {
            binder << getValueOfIsMisfired();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
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
