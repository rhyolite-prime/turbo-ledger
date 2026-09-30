/**
 *
 *  Holiday.cc
 *
 *  See Holiday.h for the hand-authored-subset note.
 *
 */

#include "Holiday.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlOrganizationDb;

const std::string Holiday::Cols::_id = "\"id\"";
const std::string Holiday::Cols::_name = "\"name\"";
const std::string Holiday::Cols::_from_date = "\"from_date\"";
const std::string Holiday::Cols::_to_date = "\"to_date\"";
const std::string Holiday::Cols::_repayment_scheduled_to = "\"repayment_scheduled_to\"";
const std::string Holiday::Cols::_description = "\"description\"";
const std::string Holiday::Cols::_status = "\"status\"";
const std::string Holiday::Cols::_applies_to_all_offices = "\"applies_to_all_offices\"";
const std::string Holiday::Cols::_created_at = "\"created_at\"";
const std::string Holiday::Cols::_modified_at = "\"modified_at\"";
const std::string Holiday::primaryKeyName = "id";
const bool Holiday::hasPrimaryKey = true;
const std::string Holiday::tableName = "\"holiday\"";

const std::vector<typename Holiday::MetaData> Holiday::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",100,0,0,1},
{"from_date","::trantor::Date","date",0,0,0,1},
{"to_date","::trantor::Date","date",0,0,0,1},
{"repayment_scheduled_to","::trantor::Date","date",0,0,0,0},
{"description","std::string","character varying",500,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"applies_to_all_offices","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"modified_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Holiday::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Holiday::Holiday(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["from_date"].isNull())
        {
            auto daysStr = r["from_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            fromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["to_date"].isNull())
        {
            auto daysStr = r["to_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            toDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["repayment_scheduled_to"].isNull())
        {
            auto daysStr = r["repayment_scheduled_to"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            repaymentScheduledTo_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
        }
        if(!r["applies_to_all_offices"].isNull())
        {
            appliesToAllOffices_=std::make_shared<bool>(r["applies_to_all_offices"].as<bool>());
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
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            fromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            toDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            repaymentScheduledTo_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            appliesToAllOffices_=std::make_shared<bool>(r[index].as<bool>());
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
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}

const std::string &Holiday::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Holiday::getId() const noexcept
{
    return id_;
}
void Holiday::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Holiday::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Holiday::PrimaryKeyType & Holiday::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Holiday::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Holiday::getName() const noexcept
{
    return name_;
}
void Holiday::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void Holiday::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const ::trantor::Date &Holiday::getValueOfFromDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(fromDate_)
        return *fromDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Holiday::getFromDate() const noexcept
{
    return fromDate_;
}
void Holiday::setFromDate(const ::trantor::Date &pFromDate) noexcept
{
    fromDate_ = std::make_shared<::trantor::Date>(pFromDate.roundDay());
    dirtyFlag_[2] = true;
}

const ::trantor::Date &Holiday::getValueOfToDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(toDate_)
        return *toDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Holiday::getToDate() const noexcept
{
    return toDate_;
}
void Holiday::setToDate(const ::trantor::Date &pToDate) noexcept
{
    toDate_ = std::make_shared<::trantor::Date>(pToDate.roundDay());
    dirtyFlag_[3] = true;
}

const ::trantor::Date &Holiday::getValueOfRepaymentScheduledTo() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(repaymentScheduledTo_)
        return *repaymentScheduledTo_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Holiday::getRepaymentScheduledTo() const noexcept
{
    return repaymentScheduledTo_;
}
void Holiday::setRepaymentScheduledTo(const ::trantor::Date &pRepaymentScheduledTo) noexcept
{
    repaymentScheduledTo_ = std::make_shared<::trantor::Date>(pRepaymentScheduledTo.roundDay());
    dirtyFlag_[4] = true;
}
void Holiday::setRepaymentScheduledToToNull() noexcept
{
    repaymentScheduledTo_.reset();
    dirtyFlag_[4] = true;
}

const std::string &Holiday::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Holiday::getDescription() const noexcept
{
    return description_;
}
void Holiday::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[5] = true;
}
void Holiday::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[5] = true;
}
void Holiday::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[5] = true;
}

const std::string &Holiday::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Holiday::getStatus() const noexcept
{
    return status_;
}
void Holiday::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[6] = true;
}
void Holiday::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[6] = true;
}

const bool &Holiday::getValueOfAppliesToAllOffices() const noexcept
{
    static const bool defaultValue = bool();
    if(appliesToAllOffices_)
        return *appliesToAllOffices_;
    return defaultValue;
}
const std::shared_ptr<bool> &Holiday::getAppliesToAllOffices() const noexcept
{
    return appliesToAllOffices_;
}
void Holiday::setAppliesToAllOffices(const bool &pAppliesToAllOffices) noexcept
{
    appliesToAllOffices_ = std::make_shared<bool>(pAppliesToAllOffices);
    dirtyFlag_[7] = true;
}

const ::trantor::Date &Holiday::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Holiday::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Holiday::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}

const ::trantor::Date &Holiday::getValueOfModifiedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(modifiedAt_)
        return *modifiedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Holiday::getModifiedAt() const noexcept
{
    return modifiedAt_;
}
void Holiday::setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept
{
    modifiedAt_ = std::make_shared<::trantor::Date>(pModifiedAt);
    dirtyFlag_[9] = true;
}

void Holiday::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Holiday::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "from_date",
        "to_date",
        "repayment_scheduled_to",
        "description",
        "status",
        "applies_to_all_offices",
        "created_at",
        "modified_at"
    };
    return inCols;
}

void Holiday::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFromDate())
        {
            binder << getValueOfFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getToDate())
        {
            binder << getValueOfToDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getRepaymentScheduledTo())
        {
            binder << getValueOfRepaymentScheduledTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getAppliesToAllOffices())
        {
            binder << getValueOfAppliesToAllOffices();
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
    if(dirtyFlag_[9])
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

const std::vector<std::string> Holiday::updateColumns() const
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

void Holiday::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFromDate())
        {
            binder << getValueOfFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getToDate())
        {
            binder << getValueOfToDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getRepaymentScheduledTo())
        {
            binder << getValueOfRepaymentScheduledTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getAppliesToAllOffices())
        {
            binder << getValueOfAppliesToAllOffices();
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
    if(dirtyFlag_[9])
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

