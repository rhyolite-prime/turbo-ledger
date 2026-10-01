/**
 *  SharePurchaseRequest.cc
 *
 *  See SharePurchaseRequest.h for the hand-authored-subset note.
 *
 */

#include "SharePurchaseRequest.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string SharePurchaseRequest::Cols::_id = "\"id\"";
const std::string SharePurchaseRequest::Cols::_share_account_id = "\"share_account_id\"";
const std::string SharePurchaseRequest::Cols::_requested_date = "\"requested_date\"";
const std::string SharePurchaseRequest::Cols::_requested_shares = "\"requested_shares\"";
const std::string SharePurchaseRequest::Cols::_requested_price = "\"requested_price\"";
const std::string SharePurchaseRequest::Cols::_status = "\"status\"";
const std::string SharePurchaseRequest::Cols::_requested_by = "\"requested_by\"";
const std::string SharePurchaseRequest::Cols::_decided_by = "\"decided_by\"";
const std::string SharePurchaseRequest::Cols::_decided_date = "\"decided_date\"";
const std::string SharePurchaseRequest::Cols::_created_at = "\"created_at\"";
const std::string SharePurchaseRequest::primaryKeyName = "id";
const bool SharePurchaseRequest::hasPrimaryKey = true;
const std::string SharePurchaseRequest::tableName = "\"share_purchase_request\"";

const std::vector<typename SharePurchaseRequest::MetaData> SharePurchaseRequest::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"share_account_id","std::string","uuid",0,0,0,1},
{"requested_date","::trantor::Date","date",0,0,0,1},
{"requested_shares","int64_t","bigint",8,0,0,1},
{"requested_price","std::string","numeric",0,0,0,0},
{"status","int32_t","integer",4,0,0,1},
{"requested_by","std::string","uuid",0,0,0,0},
{"decided_by","std::string","uuid",0,0,0,0},
{"decided_date","::trantor::Date","date",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SharePurchaseRequest::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SharePurchaseRequest::SharePurchaseRequest(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["share_account_id"].isNull())
        {
            shareAccountId_=std::make_shared<std::string>(r["share_account_id"].as<std::string>());
        }
        if(!r["requested_date"].isNull())
        {
            auto daysStr = r["requested_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            requestedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["requested_shares"].isNull())
        {
            requestedShares_=std::make_shared<int64_t>(r["requested_shares"].as<int64_t>());
        }
        if(!r["requested_price"].isNull())
        {
            requestedPrice_=std::make_shared<std::string>(r["requested_price"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["requested_by"].isNull())
        {
            requestedBy_=std::make_shared<std::string>(r["requested_by"].as<std::string>());
        }
        if(!r["decided_by"].isNull())
        {
            decidedBy_=std::make_shared<std::string>(r["decided_by"].as<std::string>());
        }
        if(!r["decided_date"].isNull())
        {
            auto daysStr = r["decided_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            decidedDate_=std::make_shared<::trantor::Date>(t*1000000);
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
            shareAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            requestedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            requestedShares_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            requestedPrice_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            requestedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            decidedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            decidedDate_=std::make_shared<::trantor::Date>(t*1000000);
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
const std::string &SharePurchaseRequest::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SharePurchaseRequest::getId() const noexcept
{
    return id_;
}
void SharePurchaseRequest::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SharePurchaseRequest::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SharePurchaseRequest::PrimaryKeyType & SharePurchaseRequest::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SharePurchaseRequest::getValueOfShareAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareAccountId_)
        return *shareAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SharePurchaseRequest::getShareAccountId() const noexcept
{
    return shareAccountId_;
}
void SharePurchaseRequest::setShareAccountId(const std::string &pShareAccountId) noexcept
{
    shareAccountId_ = std::make_shared<std::string>(pShareAccountId);
    dirtyFlag_[1] = true;
}
void SharePurchaseRequest::setShareAccountId(std::string &&pShareAccountId) noexcept
{
    shareAccountId_ = std::make_shared<std::string>(std::move(pShareAccountId));
    dirtyFlag_[1] = true;
}

const ::trantor::Date &SharePurchaseRequest::getValueOfRequestedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(requestedDate_)
        return *requestedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SharePurchaseRequest::getRequestedDate() const noexcept
{
    return requestedDate_;
}
void SharePurchaseRequest::setRequestedDate(const ::trantor::Date &pRequestedDate) noexcept
{
    requestedDate_ = std::make_shared<::trantor::Date>(pRequestedDate);
    dirtyFlag_[2] = true;
}

const int64_t &SharePurchaseRequest::getValueOfRequestedShares() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(requestedShares_)
        return *requestedShares_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &SharePurchaseRequest::getRequestedShares() const noexcept
{
    return requestedShares_;
}
void SharePurchaseRequest::setRequestedShares(const int64_t &pRequestedShares) noexcept
{
    requestedShares_ = std::make_shared<int64_t>(pRequestedShares);
    dirtyFlag_[3] = true;
}

const std::string &SharePurchaseRequest::getValueOfRequestedPrice() const noexcept
{
    static const std::string defaultValue = std::string();
    if(requestedPrice_)
        return *requestedPrice_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SharePurchaseRequest::getRequestedPrice() const noexcept
{
    return requestedPrice_;
}
void SharePurchaseRequest::setRequestedPrice(const std::string &pRequestedPrice) noexcept
{
    requestedPrice_ = std::make_shared<std::string>(pRequestedPrice);
    dirtyFlag_[4] = true;
}
void SharePurchaseRequest::setRequestedPrice(std::string &&pRequestedPrice) noexcept
{
    requestedPrice_ = std::make_shared<std::string>(std::move(pRequestedPrice));
    dirtyFlag_[4] = true;
}
void SharePurchaseRequest::setRequestedPriceToNull() noexcept
{
    requestedPrice_.reset();
    dirtyFlag_[4] = true;
}

const int32_t &SharePurchaseRequest::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SharePurchaseRequest::getStatus() const noexcept
{
    return status_;
}
void SharePurchaseRequest::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[5] = true;
}

const std::string &SharePurchaseRequest::getValueOfRequestedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(requestedBy_)
        return *requestedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SharePurchaseRequest::getRequestedBy() const noexcept
{
    return requestedBy_;
}
void SharePurchaseRequest::setRequestedBy(const std::string &pRequestedBy) noexcept
{
    requestedBy_ = std::make_shared<std::string>(pRequestedBy);
    dirtyFlag_[6] = true;
}
void SharePurchaseRequest::setRequestedBy(std::string &&pRequestedBy) noexcept
{
    requestedBy_ = std::make_shared<std::string>(std::move(pRequestedBy));
    dirtyFlag_[6] = true;
}
void SharePurchaseRequest::setRequestedByToNull() noexcept
{
    requestedBy_.reset();
    dirtyFlag_[6] = true;
}

const std::string &SharePurchaseRequest::getValueOfDecidedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(decidedBy_)
        return *decidedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SharePurchaseRequest::getDecidedBy() const noexcept
{
    return decidedBy_;
}
void SharePurchaseRequest::setDecidedBy(const std::string &pDecidedBy) noexcept
{
    decidedBy_ = std::make_shared<std::string>(pDecidedBy);
    dirtyFlag_[7] = true;
}
void SharePurchaseRequest::setDecidedBy(std::string &&pDecidedBy) noexcept
{
    decidedBy_ = std::make_shared<std::string>(std::move(pDecidedBy));
    dirtyFlag_[7] = true;
}
void SharePurchaseRequest::setDecidedByToNull() noexcept
{
    decidedBy_.reset();
    dirtyFlag_[7] = true;
}

const ::trantor::Date &SharePurchaseRequest::getValueOfDecidedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(decidedDate_)
        return *decidedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SharePurchaseRequest::getDecidedDate() const noexcept
{
    return decidedDate_;
}
void SharePurchaseRequest::setDecidedDate(const ::trantor::Date &pDecidedDate) noexcept
{
    decidedDate_ = std::make_shared<::trantor::Date>(pDecidedDate);
    dirtyFlag_[8] = true;
}
void SharePurchaseRequest::setDecidedDateToNull() noexcept
{
    decidedDate_.reset();
    dirtyFlag_[8] = true;
}

const ::trantor::Date &SharePurchaseRequest::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SharePurchaseRequest::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SharePurchaseRequest::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[9] = true;
}

void SharePurchaseRequest::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SharePurchaseRequest::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "share_account_id",
        "requested_date",
        "requested_shares",
        "requested_price",
        "status",
        "requested_by",
        "decided_by",
        "decided_date",
        "created_at"
    };
    return inCols;
}

void SharePurchaseRequest::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareAccountId())
        {
            binder << getValueOfShareAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRequestedDate())
        {
            binder << getValueOfRequestedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRequestedShares())
        {
            binder << getValueOfRequestedShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getRequestedPrice())
        {
            binder << getValueOfRequestedPrice();
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
        if(getRequestedBy())
        {
            binder << getValueOfRequestedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getDecidedBy())
        {
            binder << getValueOfDecidedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getDecidedDate())
        {
            binder << getValueOfDecidedDate();
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

const std::vector<std::string> SharePurchaseRequest::updateColumns() const
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

void SharePurchaseRequest::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareAccountId())
        {
            binder << getValueOfShareAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRequestedDate())
        {
            binder << getValueOfRequestedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getRequestedShares())
        {
            binder << getValueOfRequestedShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getRequestedPrice())
        {
            binder << getValueOfRequestedPrice();
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
        if(getRequestedBy())
        {
            binder << getValueOfRequestedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getDecidedBy())
        {
            binder << getValueOfDecidedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getDecidedDate())
        {
            binder << getValueOfDecidedDate();
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
