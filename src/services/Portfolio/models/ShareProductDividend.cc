/**
 *  ShareProductDividend.cc
 *
 *  See ShareProductDividend.h for the hand-authored-subset note.
 *
 */

#include "ShareProductDividend.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ShareProductDividend::Cols::_id = "\"id\"";
const std::string ShareProductDividend::Cols::_share_product_id = "\"share_product_id\"";
const std::string ShareProductDividend::Cols::_dividend_period_start_date = "\"dividend_period_start_date\"";
const std::string ShareProductDividend::Cols::_dividend_period_end_date = "\"dividend_period_end_date\"";
const std::string ShareProductDividend::Cols::_dividend_amount = "\"dividend_amount\"";
const std::string ShareProductDividend::Cols::_status = "\"status\"";
const std::string ShareProductDividend::Cols::_created_by = "\"created_by\"";
const std::string ShareProductDividend::Cols::_created_at = "\"created_at\"";
const std::string ShareProductDividend::primaryKeyName = "id";
const bool ShareProductDividend::hasPrimaryKey = true;
const std::string ShareProductDividend::tableName = "\"share_product_dividend\"";

const std::vector<typename ShareProductDividend::MetaData> ShareProductDividend::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"share_product_id","std::string","uuid",0,0,0,1},
{"dividend_period_start_date","::trantor::Date","date",0,0,0,1},
{"dividend_period_end_date","::trantor::Date","date",0,0,0,1},
{"dividend_amount","std::string","numeric",0,0,0,1},
{"status","int32_t","integer",4,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ShareProductDividend::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ShareProductDividend::ShareProductDividend(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["share_product_id"].isNull())
        {
            shareProductId_=std::make_shared<std::string>(r["share_product_id"].as<std::string>());
        }
        if(!r["dividend_period_start_date"].isNull())
        {
            auto daysStr = r["dividend_period_start_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dividendPeriodStartDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["dividend_period_end_date"].isNull())
        {
            auto daysStr = r["dividend_period_end_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dividendPeriodEndDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["dividend_amount"].isNull())
        {
            dividendAmount_=std::make_shared<std::string>(r["dividend_amount"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
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
            shareProductId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dividendPeriodStartDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dividendPeriodEndDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            dividendAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &ShareProductDividend::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProductDividend::getId() const noexcept
{
    return id_;
}
void ShareProductDividend::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ShareProductDividend::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ShareProductDividend::PrimaryKeyType & ShareProductDividend::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ShareProductDividend::getValueOfShareProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareProductId_)
        return *shareProductId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProductDividend::getShareProductId() const noexcept
{
    return shareProductId_;
}
void ShareProductDividend::setShareProductId(const std::string &pShareProductId) noexcept
{
    shareProductId_ = std::make_shared<std::string>(pShareProductId);
    dirtyFlag_[1] = true;
}
void ShareProductDividend::setShareProductId(std::string &&pShareProductId) noexcept
{
    shareProductId_ = std::make_shared<std::string>(std::move(pShareProductId));
    dirtyFlag_[1] = true;
}

const ::trantor::Date &ShareProductDividend::getValueOfDividendPeriodStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dividendPeriodStartDate_)
        return *dividendPeriodStartDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareProductDividend::getDividendPeriodStartDate() const noexcept
{
    return dividendPeriodStartDate_;
}
void ShareProductDividend::setDividendPeriodStartDate(const ::trantor::Date &pDividendPeriodStartDate) noexcept
{
    dividendPeriodStartDate_ = std::make_shared<::trantor::Date>(pDividendPeriodStartDate);
    dirtyFlag_[2] = true;
}

const ::trantor::Date &ShareProductDividend::getValueOfDividendPeriodEndDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dividendPeriodEndDate_)
        return *dividendPeriodEndDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareProductDividend::getDividendPeriodEndDate() const noexcept
{
    return dividendPeriodEndDate_;
}
void ShareProductDividend::setDividendPeriodEndDate(const ::trantor::Date &pDividendPeriodEndDate) noexcept
{
    dividendPeriodEndDate_ = std::make_shared<::trantor::Date>(pDividendPeriodEndDate);
    dirtyFlag_[3] = true;
}

const std::string &ShareProductDividend::getValueOfDividendAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(dividendAmount_)
        return *dividendAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProductDividend::getDividendAmount() const noexcept
{
    return dividendAmount_;
}
void ShareProductDividend::setDividendAmount(const std::string &pDividendAmount) noexcept
{
    dividendAmount_ = std::make_shared<std::string>(pDividendAmount);
    dirtyFlag_[4] = true;
}
void ShareProductDividend::setDividendAmount(std::string &&pDividendAmount) noexcept
{
    dividendAmount_ = std::make_shared<std::string>(std::move(pDividendAmount));
    dirtyFlag_[4] = true;
}

const int32_t &ShareProductDividend::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareProductDividend::getStatus() const noexcept
{
    return status_;
}
void ShareProductDividend::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[5] = true;
}

const std::string &ShareProductDividend::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProductDividend::getCreatedBy() const noexcept
{
    return createdBy_;
}
void ShareProductDividend::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[6] = true;
}
void ShareProductDividend::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[6] = true;
}
void ShareProductDividend::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &ShareProductDividend::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareProductDividend::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ShareProductDividend::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

void ShareProductDividend::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ShareProductDividend::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "share_product_id",
        "dividend_period_start_date",
        "dividend_period_end_date",
        "dividend_amount",
        "status",
        "created_by",
        "created_at"
    };
    return inCols;
}

void ShareProductDividend::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareProductId())
        {
            binder << getValueOfShareProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDividendPeriodStartDate())
        {
            binder << getValueOfDividendPeriodStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDividendPeriodEndDate())
        {
            binder << getValueOfDividendPeriodEndDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDividendAmount())
        {
            binder << getValueOfDividendAmount();
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
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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

const std::vector<std::string> ShareProductDividend::updateColumns() const
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

void ShareProductDividend::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareProductId())
        {
            binder << getValueOfShareProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDividendPeriodStartDate())
        {
            binder << getValueOfDividendPeriodStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDividendPeriodEndDate())
        {
            binder << getValueOfDividendPeriodEndDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDividendAmount())
        {
            binder << getValueOfDividendAmount();
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
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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
