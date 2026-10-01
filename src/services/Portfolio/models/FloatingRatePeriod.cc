/**
 *  FloatingRatePeriod.cc
 *
 *  See FloatingRatePeriod.h for the hand-authored-subset note.
 *
 */

#include "FloatingRatePeriod.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string FloatingRatePeriod::Cols::_id = "\"id\"";
const std::string FloatingRatePeriod::Cols::_floating_rate_id = "\"floating_rate_id\"";
const std::string FloatingRatePeriod::Cols::_from_date = "\"from_date\"";
const std::string FloatingRatePeriod::Cols::_interest_rate = "\"interest_rate\"";
const std::string FloatingRatePeriod::Cols::_is_differential_to_bln = "\"is_differential_to_bln\"";
const std::string FloatingRatePeriod::Cols::_bln_differential_rate = "\"bln_differential_rate\"";
const std::string FloatingRatePeriod::Cols::_is_active = "\"is_active\"";
const std::string FloatingRatePeriod::Cols::_created_by = "\"created_by\"";
const std::string FloatingRatePeriod::Cols::_created_at = "\"created_at\"";
const std::string FloatingRatePeriod::primaryKeyName = "id";
const bool FloatingRatePeriod::hasPrimaryKey = true;
const std::string FloatingRatePeriod::tableName = "\"floating_rate_period\"";

const std::vector<typename FloatingRatePeriod::MetaData> FloatingRatePeriod::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"floating_rate_id","std::string","uuid",0,0,0,1},
{"from_date","::trantor::Date","date",0,0,0,1},
{"interest_rate","std::string","numeric",0,0,0,1},
{"is_differential_to_bln","bool","boolean",1,0,0,1},
{"bln_differential_rate","std::string","numeric",0,0,0,0},
{"is_active","bool","boolean",1,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &FloatingRatePeriod::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
FloatingRatePeriod::FloatingRatePeriod(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["floating_rate_id"].isNull())
        {
            floatingRateId_=std::make_shared<std::string>(r["floating_rate_id"].as<std::string>());
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
        if(!r["interest_rate"].isNull())
        {
            interestRate_=std::make_shared<std::string>(r["interest_rate"].as<std::string>());
        }
        if(!r["is_differential_to_bln"].isNull())
        {
            isDifferentialToBln_=std::make_shared<bool>(r["is_differential_to_bln"].as<bool>());
        }
        if(!r["bln_differential_rate"].isNull())
        {
            blnDifferentialRate_=std::make_shared<std::string>(r["bln_differential_rate"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["created_by"].isNull())
        {
            createdBy_=std::make_shared<std::string>(r["created_by"].as<std::string>());
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
            floatingRateId_=std::make_shared<std::string>(r[index].as<std::string>());
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
            interestRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            isDifferentialToBln_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            blnDifferentialRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &FloatingRatePeriod::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &FloatingRatePeriod::getId() const noexcept
{
    return id_;
}
void FloatingRatePeriod::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void FloatingRatePeriod::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename FloatingRatePeriod::PrimaryKeyType & FloatingRatePeriod::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &FloatingRatePeriod::getValueOfFloatingRateId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(floatingRateId_)
        return *floatingRateId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &FloatingRatePeriod::getFloatingRateId() const noexcept
{
    return floatingRateId_;
}
void FloatingRatePeriod::setFloatingRateId(const std::string &pFloatingRateId) noexcept
{
    floatingRateId_ = std::make_shared<std::string>(pFloatingRateId);
    dirtyFlag_[1] = true;
}
void FloatingRatePeriod::setFloatingRateId(std::string &&pFloatingRateId) noexcept
{
    floatingRateId_ = std::make_shared<std::string>(std::move(pFloatingRateId));
    dirtyFlag_[1] = true;
}

const ::trantor::Date &FloatingRatePeriod::getValueOfFromDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(fromDate_)
        return *fromDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &FloatingRatePeriod::getFromDate() const noexcept
{
    return fromDate_;
}
void FloatingRatePeriod::setFromDate(const ::trantor::Date &pFromDate) noexcept
{
    fromDate_ = std::make_shared<::trantor::Date>(pFromDate);
    dirtyFlag_[2] = true;
}

const std::string &FloatingRatePeriod::getValueOfInterestRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestRate_)
        return *interestRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &FloatingRatePeriod::getInterestRate() const noexcept
{
    return interestRate_;
}
void FloatingRatePeriod::setInterestRate(const std::string &pInterestRate) noexcept
{
    interestRate_ = std::make_shared<std::string>(pInterestRate);
    dirtyFlag_[3] = true;
}
void FloatingRatePeriod::setInterestRate(std::string &&pInterestRate) noexcept
{
    interestRate_ = std::make_shared<std::string>(std::move(pInterestRate));
    dirtyFlag_[3] = true;
}

const bool &FloatingRatePeriod::getValueOfIsDifferentialToBln() const noexcept
{
    static const bool defaultValue = bool();
    if(isDifferentialToBln_)
        return *isDifferentialToBln_;
    return defaultValue;
}
const std::shared_ptr<bool> &FloatingRatePeriod::getIsDifferentialToBln() const noexcept
{
    return isDifferentialToBln_;
}
void FloatingRatePeriod::setIsDifferentialToBln(const bool &pIsDifferentialToBln) noexcept
{
    isDifferentialToBln_ = std::make_shared<bool>(pIsDifferentialToBln);
    dirtyFlag_[4] = true;
}

const std::string &FloatingRatePeriod::getValueOfBlnDifferentialRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(blnDifferentialRate_)
        return *blnDifferentialRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &FloatingRatePeriod::getBlnDifferentialRate() const noexcept
{
    return blnDifferentialRate_;
}
void FloatingRatePeriod::setBlnDifferentialRate(const std::string &pBlnDifferentialRate) noexcept
{
    blnDifferentialRate_ = std::make_shared<std::string>(pBlnDifferentialRate);
    dirtyFlag_[5] = true;
}
void FloatingRatePeriod::setBlnDifferentialRate(std::string &&pBlnDifferentialRate) noexcept
{
    blnDifferentialRate_ = std::make_shared<std::string>(std::move(pBlnDifferentialRate));
    dirtyFlag_[5] = true;
}
void FloatingRatePeriod::setBlnDifferentialRateToNull() noexcept
{
    blnDifferentialRate_.reset();
    dirtyFlag_[5] = true;
}

const bool &FloatingRatePeriod::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &FloatingRatePeriod::getIsActive() const noexcept
{
    return isActive_;
}
void FloatingRatePeriod::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[6] = true;
}

const std::string &FloatingRatePeriod::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &FloatingRatePeriod::getCreatedBy() const noexcept
{
    return createdBy_;
}
void FloatingRatePeriod::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[7] = true;
}
void FloatingRatePeriod::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[7] = true;
}
void FloatingRatePeriod::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[7] = true;
}

const ::trantor::Date &FloatingRatePeriod::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &FloatingRatePeriod::getCreatedAt() const noexcept
{
    return createdAt_;
}
void FloatingRatePeriod::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}

void FloatingRatePeriod::updateId(const uint64_t id)
{
}

const std::vector<std::string> &FloatingRatePeriod::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "floating_rate_id",
        "from_date",
        "interest_rate",
        "is_differential_to_bln",
        "bln_differential_rate",
        "is_active",
        "created_by",
        "created_at"
    };
    return inCols;
}

void FloatingRatePeriod::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFloatingRateId())
        {
            binder << getValueOfFloatingRateId();
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
        if(getInterestRate())
        {
            binder << getValueOfInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIsDifferentialToBln())
        {
            binder << getValueOfIsDifferentialToBln();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getBlnDifferentialRate())
        {
            binder << getValueOfBlnDifferentialRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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

const std::vector<std::string> FloatingRatePeriod::updateColumns() const
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

void FloatingRatePeriod::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFloatingRateId())
        {
            binder << getValueOfFloatingRateId();
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
        if(getInterestRate())
        {
            binder << getValueOfInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIsDifferentialToBln())
        {
            binder << getValueOfIsDifferentialToBln();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getBlnDifferentialRate())
        {
            binder << getValueOfBlnDifferentialRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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
