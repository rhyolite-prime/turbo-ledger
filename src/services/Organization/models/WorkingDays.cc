/**
 *
 *  WorkingDays.cc
 *
 *  See WorkingDays.h for the hand-authored-subset note.
 *
 */

#include "WorkingDays.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlOrganizationDb;

const std::string WorkingDays::Cols::_id = "\"id\"";
const std::string WorkingDays::Cols::_working_days = "\"working_days\"";
const std::string WorkingDays::Cols::_repayment_rescheduling_type = "\"repayment_rescheduling_type\"";
const std::string WorkingDays::Cols::_extend_term_for_daily_repayments = "\"extend_term_for_daily_repayments\"";
const std::string WorkingDays::Cols::_modified_at = "\"modified_at\"";
const std::string WorkingDays::primaryKeyName = "id";
const bool WorkingDays::hasPrimaryKey = true;
const std::string WorkingDays::tableName = "\"working_days\"";

const std::vector<typename WorkingDays::MetaData> WorkingDays::metaData_={
{"id","int32_t","integer",4,0,1,1},
{"working_days","std::string","character varying",40,0,0,1},
{"repayment_rescheduling_type","std::string","character varying",30,0,0,1},
{"extend_term_for_daily_repayments","bool","boolean",1,0,0,1},
{"modified_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &WorkingDays::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
WorkingDays::WorkingDays(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["working_days"].isNull())
        {
            workingDays_=std::make_shared<std::string>(r["working_days"].as<std::string>());
        }
        if(!r["repayment_rescheduling_type"].isNull())
        {
            repaymentReschedulingType_=std::make_shared<std::string>(r["repayment_rescheduling_type"].as<std::string>());
        }
        if(!r["extend_term_for_daily_repayments"].isNull())
        {
            extendTermForDailyRepayments_=std::make_shared<bool>(r["extend_term_for_daily_repayments"].as<bool>());
        }
        if(!r["modified_at"].isNull())
        {
            auto timeStr = r["modified_at"].as<std::string>();
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
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
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
            id_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            workingDays_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            repaymentReschedulingType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            extendTermForDailyRepayments_=std::make_shared<bool>(r[index].as<bool>());
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
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}

const int32_t &WorkingDays::getValueOfId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &WorkingDays::getId() const noexcept
{
    return id_;
}
void WorkingDays::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename WorkingDays::PrimaryKeyType & WorkingDays::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &WorkingDays::getValueOfWorkingDays() const noexcept
{
    static const std::string defaultValue = std::string();
    if(workingDays_)
        return *workingDays_;
    return defaultValue;
}
const std::shared_ptr<std::string> &WorkingDays::getWorkingDays() const noexcept
{
    return workingDays_;
}
void WorkingDays::setWorkingDays(const std::string &pWorkingDays) noexcept
{
    workingDays_ = std::make_shared<std::string>(pWorkingDays);
    dirtyFlag_[1] = true;
}
void WorkingDays::setWorkingDays(std::string &&pWorkingDays) noexcept
{
    workingDays_ = std::make_shared<std::string>(std::move(pWorkingDays));
    dirtyFlag_[1] = true;
}

const std::string &WorkingDays::getValueOfRepaymentReschedulingType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(repaymentReschedulingType_)
        return *repaymentReschedulingType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &WorkingDays::getRepaymentReschedulingType() const noexcept
{
    return repaymentReschedulingType_;
}
void WorkingDays::setRepaymentReschedulingType(const std::string &pRepaymentReschedulingType) noexcept
{
    repaymentReschedulingType_ = std::make_shared<std::string>(pRepaymentReschedulingType);
    dirtyFlag_[2] = true;
}
void WorkingDays::setRepaymentReschedulingType(std::string &&pRepaymentReschedulingType) noexcept
{
    repaymentReschedulingType_ = std::make_shared<std::string>(std::move(pRepaymentReschedulingType));
    dirtyFlag_[2] = true;
}

const bool &WorkingDays::getValueOfExtendTermForDailyRepayments() const noexcept
{
    static const bool defaultValue = bool();
    if(extendTermForDailyRepayments_)
        return *extendTermForDailyRepayments_;
    return defaultValue;
}
const std::shared_ptr<bool> &WorkingDays::getExtendTermForDailyRepayments() const noexcept
{
    return extendTermForDailyRepayments_;
}
void WorkingDays::setExtendTermForDailyRepayments(const bool &pExtendTermForDailyRepayments) noexcept
{
    extendTermForDailyRepayments_ = std::make_shared<bool>(pExtendTermForDailyRepayments);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &WorkingDays::getValueOfModifiedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(modifiedAt_)
        return *modifiedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &WorkingDays::getModifiedAt() const noexcept
{
    return modifiedAt_;
}
void WorkingDays::setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept
{
    modifiedAt_ = std::make_shared<::trantor::Date>(pModifiedAt);
    dirtyFlag_[4] = true;
}

void WorkingDays::updateId(const uint64_t id)
{
}

const std::vector<std::string> &WorkingDays::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "working_days",
        "repayment_rescheduling_type",
        "extend_term_for_daily_repayments",
        "modified_at"
    };
    return inCols;
}

void WorkingDays::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getWorkingDays())
        {
            binder << getValueOfWorkingDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRepaymentReschedulingType())
        {
            binder << getValueOfRepaymentReschedulingType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getExtendTermForDailyRepayments())
        {
            binder << getValueOfExtendTermForDailyRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> WorkingDays::updateColumns() const
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

void WorkingDays::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getWorkingDays())
        {
            binder << getValueOfWorkingDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRepaymentReschedulingType())
        {
            binder << getValueOfRepaymentReschedulingType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getExtendTermForDailyRepayments())
        {
            binder << getValueOfExtendTermForDailyRepayments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

