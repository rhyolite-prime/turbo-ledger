/**
 *  Teller.cc
 *
 *  See Teller.h for the hand-authored-subset note.
 *
 */

#include "Teller.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlTellerDb;

const std::string Teller::Cols::_id = "\"id\"";
const std::string Teller::Cols::_office_id = "\"office_id\"";
const std::string Teller::Cols::_name = "\"name\"";
const std::string Teller::Cols::_description = "\"description\"";
const std::string Teller::Cols::_status_enum = "\"status_enum\"";
const std::string Teller::Cols::_start_date = "\"start_date\"";
const std::string Teller::Cols::_end_date = "\"end_date\"";
const std::string Teller::Cols::_created_at = "\"created_at\"";
const std::string Teller::primaryKeyName = "id";
const bool Teller::hasPrimaryKey = true;
const std::string Teller::tableName = "\"tellers\"";

const std::vector<typename Teller::MetaData> Teller::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"office_id","std::string","uuid",0,0,0,1},
{"name","std::string","character varying",100,0,0,1},
{"description","std::string","text",0,0,0,0},
{"status_enum","int32_t","integer",4,0,0,1},
{"start_date","::trantor::Date","date",0,0,0,1},
{"end_date","::trantor::Date","date",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Teller::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Teller::Teller(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["status_enum"].isNull())
        {
            statusEnum_=std::make_shared<int32_t>(r["status_enum"].as<int32_t>());
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
        if(offset + 8 > r.size())
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
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            statusEnum_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            endDate_=std::make_shared<::trantor::Date>(t*1000000);
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
    }

}
const std::string &Teller::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Teller::getId() const noexcept
{
    return id_;
}
void Teller::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Teller::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Teller::PrimaryKeyType & Teller::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Teller::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Teller::getOfficeId() const noexcept
{
    return officeId_;
}
void Teller::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[1] = true;
}
void Teller::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[1] = true;
}

const std::string &Teller::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Teller::getName() const noexcept
{
    return name_;
}
void Teller::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[2] = true;
}
void Teller::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[2] = true;
}

const std::string &Teller::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Teller::getDescription() const noexcept
{
    return description_;
}
void Teller::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void Teller::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void Teller::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &Teller::getValueOfStatusEnum() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(statusEnum_)
        return *statusEnum_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Teller::getStatusEnum() const noexcept
{
    return statusEnum_;
}
void Teller::setStatusEnum(const int32_t &pStatusEnum) noexcept
{
    statusEnum_ = std::make_shared<int32_t>(pStatusEnum);
    dirtyFlag_[4] = true;
}

const ::trantor::Date &Teller::getValueOfStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDate_)
        return *startDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Teller::getStartDate() const noexcept
{
    return startDate_;
}
void Teller::setStartDate(const ::trantor::Date &pStartDate) noexcept
{
    startDate_ = std::make_shared<::trantor::Date>(pStartDate);
    dirtyFlag_[5] = true;
}

const ::trantor::Date &Teller::getValueOfEndDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(endDate_)
        return *endDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Teller::getEndDate() const noexcept
{
    return endDate_;
}
void Teller::setEndDate(const ::trantor::Date &pEndDate) noexcept
{
    endDate_ = std::make_shared<::trantor::Date>(pEndDate);
    dirtyFlag_[6] = true;
}
void Teller::setEndDateToNull() noexcept
{
    endDate_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &Teller::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Teller::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Teller::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

void Teller::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Teller::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "office_id",
        "name",
        "description",
        "status_enum",
        "start_date",
        "end_date",
        "created_at"
    };
    return inCols;
}

void Teller::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
        if(getStatusEnum())
        {
            binder << getValueOfStatusEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
}

const std::vector<std::string> Teller::updateColumns() const
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
    return ret;
}

void Teller::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
        if(getStatusEnum())
        {
            binder << getValueOfStatusEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
}
