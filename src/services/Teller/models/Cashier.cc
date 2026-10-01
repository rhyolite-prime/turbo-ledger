/**
 *  Cashier.cc
 *
 *  See Cashier.h for the hand-authored-subset note.
 *
 */

#include "Cashier.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlTellerDb;

const std::string Cashier::Cols::_id = "\"id\"";
const std::string Cashier::Cols::_teller_id = "\"teller_id\"";
const std::string Cashier::Cols::_staff_id = "\"staff_id\"";
const std::string Cashier::Cols::_description = "\"description\"";
const std::string Cashier::Cols::_start_date = "\"start_date\"";
const std::string Cashier::Cols::_end_date = "\"end_date\"";
const std::string Cashier::Cols::_is_full_day = "\"is_full_day\"";
const std::string Cashier::Cols::_start_time = "\"start_time\"";
const std::string Cashier::Cols::_end_time = "\"end_time\"";
const std::string Cashier::Cols::_created_at = "\"created_at\"";
const std::string Cashier::primaryKeyName = "id";
const bool Cashier::hasPrimaryKey = true;
const std::string Cashier::tableName = "\"cashiers\"";

const std::vector<typename Cashier::MetaData> Cashier::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"teller_id","std::string","uuid",0,0,0,1},
{"staff_id","std::string","uuid",0,0,0,1},
{"description","std::string","text",0,0,0,0},
{"start_date","::trantor::Date","date",0,0,0,1},
{"end_date","::trantor::Date","date",0,0,0,0},
{"is_full_day","bool","boolean",1,0,0,1},
{"start_time","std::string","character varying",8,0,0,0},
{"end_time","std::string","character varying",8,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Cashier::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Cashier::Cashier(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["teller_id"].isNull())
        {
            tellerId_=std::make_shared<std::string>(r["teller_id"].as<std::string>());
        }
        if(!r["staff_id"].isNull())
        {
            staffId_=std::make_shared<std::string>(r["staff_id"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["start_date"].isNull())
        {
            auto daysStr = r["start_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["end_date"].isNull())
        {
            auto daysStr = r["end_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            endDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["is_full_day"].isNull())
        {
            isFullDay_=std::make_shared<bool>(r["is_full_day"].as<bool>());
        }
        if(!r["start_time"].isNull())
        {
            startTime_=std::make_shared<std::string>(r["start_time"].as<std::string>());
        }
        if(!r["end_time"].isNull())
        {
            endTime_=std::make_shared<std::string>(r["end_time"].as<std::string>());
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
        if(offset + 10 > r.size())
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
            tellerId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            staffId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            endDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            isFullDay_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            startTime_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            endTime_=std::make_shared<std::string>(r[index].as<std::string>());
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
    }

}
const std::string &Cashier::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Cashier::getId() const noexcept
{
    return id_;
}
void Cashier::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Cashier::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Cashier::PrimaryKeyType & Cashier::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Cashier::getValueOfTellerId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(tellerId_)
        return *tellerId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Cashier::getTellerId() const noexcept
{
    return tellerId_;
}
void Cashier::setTellerId(const std::string &pTellerId) noexcept
{
    tellerId_ = std::make_shared<std::string>(pTellerId);
    dirtyFlag_[1] = true;
}
void Cashier::setTellerId(std::string &&pTellerId) noexcept
{
    tellerId_ = std::make_shared<std::string>(std::move(pTellerId));
    dirtyFlag_[1] = true;
}

const std::string &Cashier::getValueOfStaffId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(staffId_)
        return *staffId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Cashier::getStaffId() const noexcept
{
    return staffId_;
}
void Cashier::setStaffId(const std::string &pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(pStaffId);
    dirtyFlag_[2] = true;
}
void Cashier::setStaffId(std::string &&pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(std::move(pStaffId));
    dirtyFlag_[2] = true;
}

const std::string &Cashier::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Cashier::getDescription() const noexcept
{
    return description_;
}
void Cashier::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void Cashier::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void Cashier::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const ::trantor::Date &Cashier::getValueOfStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDate_)
        return *startDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Cashier::getStartDate() const noexcept
{
    return startDate_;
}
void Cashier::setStartDate(const ::trantor::Date &pStartDate) noexcept
{
    startDate_ = std::make_shared<::trantor::Date>(pStartDate);
    dirtyFlag_[4] = true;
}

const ::trantor::Date &Cashier::getValueOfEndDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(endDate_)
        return *endDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Cashier::getEndDate() const noexcept
{
    return endDate_;
}
void Cashier::setEndDate(const ::trantor::Date &pEndDate) noexcept
{
    endDate_ = std::make_shared<::trantor::Date>(pEndDate);
    dirtyFlag_[5] = true;
}
void Cashier::setEndDateToNull() noexcept
{
    endDate_.reset();
    dirtyFlag_[5] = true;
}

const bool &Cashier::getValueOfIsFullDay() const noexcept
{
    static const bool defaultValue = bool();
    if(isFullDay_)
        return *isFullDay_;
    return defaultValue;
}
const std::shared_ptr<bool> &Cashier::getIsFullDay() const noexcept
{
    return isFullDay_;
}
void Cashier::setIsFullDay(const bool &pIsFullDay) noexcept
{
    isFullDay_ = std::make_shared<bool>(pIsFullDay);
    dirtyFlag_[6] = true;
}

const std::string &Cashier::getValueOfStartTime() const noexcept
{
    static const std::string defaultValue = std::string();
    if(startTime_)
        return *startTime_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Cashier::getStartTime() const noexcept
{
    return startTime_;
}
void Cashier::setStartTime(const std::string &pStartTime) noexcept
{
    startTime_ = std::make_shared<std::string>(pStartTime);
    dirtyFlag_[7] = true;
}
void Cashier::setStartTime(std::string &&pStartTime) noexcept
{
    startTime_ = std::make_shared<std::string>(std::move(pStartTime));
    dirtyFlag_[7] = true;
}
void Cashier::setStartTimeToNull() noexcept
{
    startTime_.reset();
    dirtyFlag_[7] = true;
}

const std::string &Cashier::getValueOfEndTime() const noexcept
{
    static const std::string defaultValue = std::string();
    if(endTime_)
        return *endTime_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Cashier::getEndTime() const noexcept
{
    return endTime_;
}
void Cashier::setEndTime(const std::string &pEndTime) noexcept
{
    endTime_ = std::make_shared<std::string>(pEndTime);
    dirtyFlag_[8] = true;
}
void Cashier::setEndTime(std::string &&pEndTime) noexcept
{
    endTime_ = std::make_shared<std::string>(std::move(pEndTime));
    dirtyFlag_[8] = true;
}
void Cashier::setEndTimeToNull() noexcept
{
    endTime_.reset();
    dirtyFlag_[8] = true;
}

const ::trantor::Date &Cashier::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Cashier::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Cashier::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[9] = true;
}

void Cashier::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Cashier::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "teller_id",
        "staff_id",
        "description",
        "start_date",
        "end_date",
        "is_full_day",
        "start_time",
        "end_time",
        "created_at"
    };
    return inCols;
}

void Cashier::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTellerId())
        {
            binder << getValueOfTellerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getStaffId())
        {
            binder << getValueOfStaffId();
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
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getEndDate())
        {
            binder << getValueOfEndDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getIsFullDay())
        {
            binder << getValueOfIsFullDay();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
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
}

const std::vector<std::string> Cashier::updateColumns() const
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
    return ret;
}

void Cashier::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTellerId())
        {
            binder << getValueOfTellerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getStaffId())
        {
            binder << getValueOfStaffId();
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
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getEndDate())
        {
            binder << getValueOfEndDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getIsFullDay())
        {
            binder << getValueOfIsFullDay();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
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
}
