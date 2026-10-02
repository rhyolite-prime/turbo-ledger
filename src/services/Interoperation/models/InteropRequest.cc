/**
 *  InteropRequest.cc
 *
 *  See InteropRequest.h for the hand-authored-subset note.
 *
 */

#include "InteropRequest.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlInteroperationDb;

const std::string InteropRequest::Cols::_id = "\"id\"";
const std::string InteropRequest::Cols::_transaction_code = "\"transaction_code\"";
const std::string InteropRequest::Cols::_request_code = "\"request_code\"";
const std::string InteropRequest::Cols::_account_id = "\"account_id\"";
const std::string InteropRequest::Cols::_amount = "\"amount\"";
const std::string InteropRequest::Cols::_currency = "\"currency\"";
const std::string InteropRequest::Cols::_status = "\"status\"";
const std::string InteropRequest::Cols::_created_at = "\"created_at\"";
const std::string InteropRequest::primaryKeyName = "id";
const bool InteropRequest::hasPrimaryKey = true;
const std::string InteropRequest::tableName = "\"interop_requests\"";

const std::vector<typename InteropRequest::MetaData> InteropRequest::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"transaction_code","std::string","character varying",64,0,0,1},
{"request_code","std::string","character varying",64,0,0,1},
{"account_id","std::string","character varying",64,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"currency","std::string","character varying",10,0,0,1},
{"status","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &InteropRequest::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
InteropRequest::InteropRequest(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["transaction_code"].isNull())
        {
            transactionCode_=std::make_shared<std::string>(r["transaction_code"].as<std::string>());
        }
        if(!r["request_code"].isNull())
        {
            requestCode_=std::make_shared<std::string>(r["request_code"].as<std::string>());
        }
        if(!r["account_id"].isNull())
        {
            accountId_=std::make_shared<std::string>(r["account_id"].as<std::string>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["currency"].isNull())
        {
            currency_=std::make_shared<std::string>(r["currency"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
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
            transactionCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            requestCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            accountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            currency_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &InteropRequest::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropRequest::getId() const noexcept
{
    return id_;
}
void InteropRequest::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void InteropRequest::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename InteropRequest::PrimaryKeyType & InteropRequest::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &InteropRequest::getValueOfTransactionCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transactionCode_)
        return *transactionCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropRequest::getTransactionCode() const noexcept
{
    return transactionCode_;
}
void InteropRequest::setTransactionCode(const std::string &pTransactionCode) noexcept
{
    transactionCode_ = std::make_shared<std::string>(pTransactionCode);
    dirtyFlag_[1] = true;
}
void InteropRequest::setTransactionCode(std::string &&pTransactionCode) noexcept
{
    transactionCode_ = std::make_shared<std::string>(std::move(pTransactionCode));
    dirtyFlag_[1] = true;
}

const std::string &InteropRequest::getValueOfRequestCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(requestCode_)
        return *requestCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropRequest::getRequestCode() const noexcept
{
    return requestCode_;
}
void InteropRequest::setRequestCode(const std::string &pRequestCode) noexcept
{
    requestCode_ = std::make_shared<std::string>(pRequestCode);
    dirtyFlag_[2] = true;
}
void InteropRequest::setRequestCode(std::string &&pRequestCode) noexcept
{
    requestCode_ = std::make_shared<std::string>(std::move(pRequestCode));
    dirtyFlag_[2] = true;
}

const std::string &InteropRequest::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropRequest::getAccountId() const noexcept
{
    return accountId_;
}
void InteropRequest::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[3] = true;
}
void InteropRequest::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[3] = true;
}

const std::string &InteropRequest::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropRequest::getAmount() const noexcept
{
    return amount_;
}
void InteropRequest::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[4] = true;
}
void InteropRequest::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[4] = true;
}

const std::string &InteropRequest::getValueOfCurrency() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currency_)
        return *currency_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropRequest::getCurrency() const noexcept
{
    return currency_;
}
void InteropRequest::setCurrency(const std::string &pCurrency) noexcept
{
    currency_ = std::make_shared<std::string>(pCurrency);
    dirtyFlag_[5] = true;
}
void InteropRequest::setCurrency(std::string &&pCurrency) noexcept
{
    currency_ = std::make_shared<std::string>(std::move(pCurrency));
    dirtyFlag_[5] = true;
}

const std::string &InteropRequest::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropRequest::getStatus() const noexcept
{
    return status_;
}
void InteropRequest::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[6] = true;
}
void InteropRequest::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[6] = true;
}

const ::trantor::Date &InteropRequest::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &InteropRequest::getCreatedAt() const noexcept
{
    return createdAt_;
}
void InteropRequest::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

void InteropRequest::updateId(const uint64_t id)
{
}

const std::vector<std::string> &InteropRequest::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "transaction_code",
        "request_code",
        "account_id",
        "amount",
        "currency",
        "status",
        "created_at"
    };
    return inCols;
}

void InteropRequest::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTransactionCode())
        {
            binder << getValueOfTransactionCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRequestCode())
        {
            binder << getValueOfRequestCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getAccountId())
        {
            binder << getValueOfAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCurrency())
        {
            binder << getValueOfCurrency();
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

const std::vector<std::string> InteropRequest::updateColumns() const
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

void InteropRequest::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTransactionCode())
        {
            binder << getValueOfTransactionCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getRequestCode())
        {
            binder << getValueOfRequestCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getAccountId())
        {
            binder << getValueOfAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCurrency())
        {
            binder << getValueOfCurrency();
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
