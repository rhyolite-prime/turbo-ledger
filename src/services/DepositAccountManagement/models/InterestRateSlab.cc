/**
 *  InterestRateSlab.cc
 *
 *  See InterestRateSlab.h for the hand-authored-subset note.
 *
 */

#include "InterestRateSlab.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string InterestRateSlab::Cols::_id = "\"id\"";
const std::string InterestRateSlab::Cols::_business_id = "\"business_id\"";
const std::string InterestRateSlab::Cols::_chart_id = "\"chart_id\"";
const std::string InterestRateSlab::Cols::_description = "\"description\"";
const std::string InterestRateSlab::Cols::_period_type = "\"period_type\"";
const std::string InterestRateSlab::Cols::_from_period = "\"from_period\"";
const std::string InterestRateSlab::Cols::_to_period = "\"to_period\"";
const std::string InterestRateSlab::Cols::_amount_range_from = "\"amount_range_from\"";
const std::string InterestRateSlab::Cols::_amount_range_to = "\"amount_range_to\"";
const std::string InterestRateSlab::Cols::_annual_interest_rate = "\"annual_interest_rate\"";
const std::string InterestRateSlab::Cols::_currency_code = "\"currency_code\"";
const std::string InterestRateSlab::Cols::_created_by = "\"created_by\"";
const std::string InterestRateSlab::Cols::_created_at = "\"created_at\"";
const std::string InterestRateSlab::Cols::_updated_by = "\"updated_by\"";
const std::string InterestRateSlab::Cols::_updated_at = "\"updated_at\"";
const std::string InterestRateSlab::primaryKeyName = "id";
const bool InterestRateSlab::hasPrimaryKey = true;
const std::string InterestRateSlab::tableName = "\"interest_rate_slab\"";

const std::vector<typename InterestRateSlab::MetaData> InterestRateSlab::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"chart_id","std::string","uuid",0,0,0,1},
{"description","std::string","character varying",500,0,0,0},
{"period_type","int32_t","integer",4,0,0,0},
{"from_period","int32_t","integer",4,0,0,0},
{"to_period","int32_t","integer",4,0,0,0},
{"amount_range_from","std::string","numeric",0,0,0,0},
{"amount_range_to","std::string","numeric",0,0,0,0},
{"annual_interest_rate","std::string","numeric",0,0,0,1},
{"currency_code","std::string","character varying",3,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &InterestRateSlab::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
InterestRateSlab::InterestRateSlab(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["business_id"].isNull())
        {
            businessId_=std::make_shared<std::string>(r["business_id"].as<std::string>());
        }
        if(!r["chart_id"].isNull())
        {
            chartId_=std::make_shared<std::string>(r["chart_id"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["period_type"].isNull())
        {
            periodType_=std::make_shared<int32_t>(r["period_type"].as<int32_t>());
        }
        if(!r["from_period"].isNull())
        {
            fromPeriod_=std::make_shared<int32_t>(r["from_period"].as<int32_t>());
        }
        if(!r["to_period"].isNull())
        {
            toPeriod_=std::make_shared<int32_t>(r["to_period"].as<int32_t>());
        }
        if(!r["amount_range_from"].isNull())
        {
            amountRangeFrom_=std::make_shared<std::string>(r["amount_range_from"].as<std::string>());
        }
        if(!r["amount_range_to"].isNull())
        {
            amountRangeTo_=std::make_shared<std::string>(r["amount_range_to"].as<std::string>());
        }
        if(!r["annual_interest_rate"].isNull())
        {
            annualInterestRate_=std::make_shared<std::string>(r["annual_interest_rate"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
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
        if(!r["updated_by"].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r["updated_by"].as<std::string>());
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
        if(offset + 15 > r.size())
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
            businessId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            chartId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            periodType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            fromPeriod_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            toPeriod_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            amountRangeFrom_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            amountRangeTo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            annualInterestRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
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
        index = offset + 13;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &InterestRateSlab::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getId() const noexcept
{
    return id_;
}
void InterestRateSlab::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void InterestRateSlab::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename InterestRateSlab::PrimaryKeyType & InterestRateSlab::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &InterestRateSlab::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getBusinessId() const noexcept
{
    return businessId_;
}
void InterestRateSlab::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void InterestRateSlab::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void InterestRateSlab::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &InterestRateSlab::getValueOfChartId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(chartId_)
        return *chartId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getChartId() const noexcept
{
    return chartId_;
}
void InterestRateSlab::setChartId(const std::string &pChartId) noexcept
{
    chartId_ = std::make_shared<std::string>(pChartId);
    dirtyFlag_[2] = true;
}
void InterestRateSlab::setChartId(std::string &&pChartId) noexcept
{
    chartId_ = std::make_shared<std::string>(std::move(pChartId));
    dirtyFlag_[2] = true;
}

const std::string &InterestRateSlab::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getDescription() const noexcept
{
    return description_;
}
void InterestRateSlab::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void InterestRateSlab::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void InterestRateSlab::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &InterestRateSlab::getValueOfPeriodType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(periodType_)
        return *periodType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &InterestRateSlab::getPeriodType() const noexcept
{
    return periodType_;
}
void InterestRateSlab::setPeriodType(const int32_t &pPeriodType) noexcept
{
    periodType_ = std::make_shared<int32_t>(pPeriodType);
    dirtyFlag_[4] = true;
}
void InterestRateSlab::setPeriodTypeToNull() noexcept
{
    periodType_.reset();
    dirtyFlag_[4] = true;
}

const int32_t &InterestRateSlab::getValueOfFromPeriod() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(fromPeriod_)
        return *fromPeriod_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &InterestRateSlab::getFromPeriod() const noexcept
{
    return fromPeriod_;
}
void InterestRateSlab::setFromPeriod(const int32_t &pFromPeriod) noexcept
{
    fromPeriod_ = std::make_shared<int32_t>(pFromPeriod);
    dirtyFlag_[5] = true;
}
void InterestRateSlab::setFromPeriodToNull() noexcept
{
    fromPeriod_.reset();
    dirtyFlag_[5] = true;
}

const int32_t &InterestRateSlab::getValueOfToPeriod() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(toPeriod_)
        return *toPeriod_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &InterestRateSlab::getToPeriod() const noexcept
{
    return toPeriod_;
}
void InterestRateSlab::setToPeriod(const int32_t &pToPeriod) noexcept
{
    toPeriod_ = std::make_shared<int32_t>(pToPeriod);
    dirtyFlag_[6] = true;
}
void InterestRateSlab::setToPeriodToNull() noexcept
{
    toPeriod_.reset();
    dirtyFlag_[6] = true;
}

const std::string &InterestRateSlab::getValueOfAmountRangeFrom() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountRangeFrom_)
        return *amountRangeFrom_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getAmountRangeFrom() const noexcept
{
    return amountRangeFrom_;
}
void InterestRateSlab::setAmountRangeFrom(const std::string &pAmountRangeFrom) noexcept
{
    amountRangeFrom_ = std::make_shared<std::string>(pAmountRangeFrom);
    dirtyFlag_[7] = true;
}
void InterestRateSlab::setAmountRangeFrom(std::string &&pAmountRangeFrom) noexcept
{
    amountRangeFrom_ = std::make_shared<std::string>(std::move(pAmountRangeFrom));
    dirtyFlag_[7] = true;
}
void InterestRateSlab::setAmountRangeFromToNull() noexcept
{
    amountRangeFrom_.reset();
    dirtyFlag_[7] = true;
}

const std::string &InterestRateSlab::getValueOfAmountRangeTo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountRangeTo_)
        return *amountRangeTo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getAmountRangeTo() const noexcept
{
    return amountRangeTo_;
}
void InterestRateSlab::setAmountRangeTo(const std::string &pAmountRangeTo) noexcept
{
    amountRangeTo_ = std::make_shared<std::string>(pAmountRangeTo);
    dirtyFlag_[8] = true;
}
void InterestRateSlab::setAmountRangeTo(std::string &&pAmountRangeTo) noexcept
{
    amountRangeTo_ = std::make_shared<std::string>(std::move(pAmountRangeTo));
    dirtyFlag_[8] = true;
}
void InterestRateSlab::setAmountRangeToToNull() noexcept
{
    amountRangeTo_.reset();
    dirtyFlag_[8] = true;
}

const std::string &InterestRateSlab::getValueOfAnnualInterestRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(annualInterestRate_)
        return *annualInterestRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getAnnualInterestRate() const noexcept
{
    return annualInterestRate_;
}
void InterestRateSlab::setAnnualInterestRate(const std::string &pAnnualInterestRate) noexcept
{
    annualInterestRate_ = std::make_shared<std::string>(pAnnualInterestRate);
    dirtyFlag_[9] = true;
}
void InterestRateSlab::setAnnualInterestRate(std::string &&pAnnualInterestRate) noexcept
{
    annualInterestRate_ = std::make_shared<std::string>(std::move(pAnnualInterestRate));
    dirtyFlag_[9] = true;
}

const std::string &InterestRateSlab::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void InterestRateSlab::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[10] = true;
}
void InterestRateSlab::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[10] = true;
}

const std::string &InterestRateSlab::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getCreatedBy() const noexcept
{
    return createdBy_;
}
void InterestRateSlab::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[11] = true;
}
void InterestRateSlab::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[11] = true;
}
void InterestRateSlab::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[11] = true;
}

const ::trantor::Date &InterestRateSlab::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &InterestRateSlab::getCreatedAt() const noexcept
{
    return createdAt_;
}
void InterestRateSlab::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[12] = true;
}

const std::string &InterestRateSlab::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InterestRateSlab::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void InterestRateSlab::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[13] = true;
}
void InterestRateSlab::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[13] = true;
}
void InterestRateSlab::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[13] = true;
}

const ::trantor::Date &InterestRateSlab::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &InterestRateSlab::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void InterestRateSlab::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[14] = true;
}

void InterestRateSlab::updateId(const uint64_t id)
{
}

const std::vector<std::string> &InterestRateSlab::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "chart_id",
        "description",
        "period_type",
        "from_period",
        "to_period",
        "amount_range_from",
        "amount_range_to",
        "annual_interest_rate",
        "currency_code",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void InterestRateSlab::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getChartId())
        {
            binder << getValueOfChartId();
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
        if(getPeriodType())
        {
            binder << getValueOfPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getFromPeriod())
        {
            binder << getValueOfFromPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getToPeriod())
        {
            binder << getValueOfToPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getAmountRangeFrom())
        {
            binder << getValueOfAmountRangeFrom();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getAmountRangeTo())
        {
            binder << getValueOfAmountRangeTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getAnnualInterestRate())
        {
            binder << getValueOfAnnualInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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

const std::vector<std::string> InterestRateSlab::updateColumns() const
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
    return ret;
}

void InterestRateSlab::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getChartId())
        {
            binder << getValueOfChartId();
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
        if(getPeriodType())
        {
            binder << getValueOfPeriodType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getFromPeriod())
        {
            binder << getValueOfFromPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getToPeriod())
        {
            binder << getValueOfToPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getAmountRangeFrom())
        {
            binder << getValueOfAmountRangeFrom();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getAmountRangeTo())
        {
            binder << getValueOfAmountRangeTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getAnnualInterestRate())
        {
            binder << getValueOfAnnualInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
