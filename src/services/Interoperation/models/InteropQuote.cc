/**
 *  InteropQuote.cc
 *
 *  See InteropQuote.h for the hand-authored-subset note.
 *
 */

#include "InteropQuote.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlInteroperationDb;

const std::string InteropQuote::Cols::_id = "\"id\"";
const std::string InteropQuote::Cols::_transaction_code = "\"transaction_code\"";
const std::string InteropQuote::Cols::_quote_code = "\"quote_code\"";
const std::string InteropQuote::Cols::_account_id = "\"account_id\"";
const std::string InteropQuote::Cols::_amount = "\"amount\"";
const std::string InteropQuote::Cols::_fee_amount = "\"fee_amount\"";
const std::string InteropQuote::Cols::_currency = "\"currency\"";
const std::string InteropQuote::Cols::_expiration = "\"expiration\"";
const std::string InteropQuote::Cols::_status = "\"status\"";
const std::string InteropQuote::Cols::_created_at = "\"created_at\"";
const std::string InteropQuote::primaryKeyName = "id";
const bool InteropQuote::hasPrimaryKey = true;
const std::string InteropQuote::tableName = "\"interop_quotes\"";

const std::vector<typename InteropQuote::MetaData> InteropQuote::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"transaction_code","std::string","character varying",64,0,0,1},
{"quote_code","std::string","character varying",64,0,0,1},
{"account_id","std::string","character varying",64,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"fee_amount","std::string","numeric",0,0,0,1},
{"currency","std::string","character varying",10,0,0,1},
{"expiration","::trantor::Date","timestamp with time zone",0,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &InteropQuote::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
InteropQuote::InteropQuote(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["quote_code"].isNull())
        {
            quoteCode_=std::make_shared<std::string>(r["quote_code"].as<std::string>());
        }
        if(!r["account_id"].isNull())
        {
            accountId_=std::make_shared<std::string>(r["account_id"].as<std::string>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["fee_amount"].isNull())
        {
            feeAmount_=std::make_shared<std::string>(r["fee_amount"].as<std::string>());
        }
        if(!r["currency"].isNull())
        {
            currency_=std::make_shared<std::string>(r["currency"].as<std::string>());
        }
        if(!r["expiration"].isNull())
        {
            auto timeStr = r["expiration"].as<std::string>();
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
                expiration_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
            transactionCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            quoteCode_=std::make_shared<std::string>(r[index].as<std::string>());
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
            feeAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            currency_=std::make_shared<std::string>(r[index].as<std::string>());
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
                expiration_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &InteropQuote::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getId() const noexcept
{
    return id_;
}
void InteropQuote::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void InteropQuote::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename InteropQuote::PrimaryKeyType & InteropQuote::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &InteropQuote::getValueOfTransactionCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transactionCode_)
        return *transactionCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getTransactionCode() const noexcept
{
    return transactionCode_;
}
void InteropQuote::setTransactionCode(const std::string &pTransactionCode) noexcept
{
    transactionCode_ = std::make_shared<std::string>(pTransactionCode);
    dirtyFlag_[1] = true;
}
void InteropQuote::setTransactionCode(std::string &&pTransactionCode) noexcept
{
    transactionCode_ = std::make_shared<std::string>(std::move(pTransactionCode));
    dirtyFlag_[1] = true;
}

const std::string &InteropQuote::getValueOfQuoteCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(quoteCode_)
        return *quoteCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getQuoteCode() const noexcept
{
    return quoteCode_;
}
void InteropQuote::setQuoteCode(const std::string &pQuoteCode) noexcept
{
    quoteCode_ = std::make_shared<std::string>(pQuoteCode);
    dirtyFlag_[2] = true;
}
void InteropQuote::setQuoteCode(std::string &&pQuoteCode) noexcept
{
    quoteCode_ = std::make_shared<std::string>(std::move(pQuoteCode));
    dirtyFlag_[2] = true;
}

const std::string &InteropQuote::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getAccountId() const noexcept
{
    return accountId_;
}
void InteropQuote::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[3] = true;
}
void InteropQuote::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[3] = true;
}

const std::string &InteropQuote::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getAmount() const noexcept
{
    return amount_;
}
void InteropQuote::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[4] = true;
}
void InteropQuote::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[4] = true;
}

const std::string &InteropQuote::getValueOfFeeAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeAmount_)
        return *feeAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getFeeAmount() const noexcept
{
    return feeAmount_;
}
void InteropQuote::setFeeAmount(const std::string &pFeeAmount) noexcept
{
    feeAmount_ = std::make_shared<std::string>(pFeeAmount);
    dirtyFlag_[5] = true;
}
void InteropQuote::setFeeAmount(std::string &&pFeeAmount) noexcept
{
    feeAmount_ = std::make_shared<std::string>(std::move(pFeeAmount));
    dirtyFlag_[5] = true;
}

const std::string &InteropQuote::getValueOfCurrency() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currency_)
        return *currency_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getCurrency() const noexcept
{
    return currency_;
}
void InteropQuote::setCurrency(const std::string &pCurrency) noexcept
{
    currency_ = std::make_shared<std::string>(pCurrency);
    dirtyFlag_[6] = true;
}
void InteropQuote::setCurrency(std::string &&pCurrency) noexcept
{
    currency_ = std::make_shared<std::string>(std::move(pCurrency));
    dirtyFlag_[6] = true;
}

const ::trantor::Date &InteropQuote::getValueOfExpiration() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(expiration_)
        return *expiration_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &InteropQuote::getExpiration() const noexcept
{
    return expiration_;
}
void InteropQuote::setExpiration(const ::trantor::Date &pExpiration) noexcept
{
    expiration_ = std::make_shared<::trantor::Date>(pExpiration);
    dirtyFlag_[7] = true;
}
void InteropQuote::setExpirationToNull() noexcept
{
    expiration_.reset();
    dirtyFlag_[7] = true;
}

const std::string &InteropQuote::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropQuote::getStatus() const noexcept
{
    return status_;
}
void InteropQuote::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[8] = true;
}
void InteropQuote::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[8] = true;
}

const ::trantor::Date &InteropQuote::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &InteropQuote::getCreatedAt() const noexcept
{
    return createdAt_;
}
void InteropQuote::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[9] = true;
}

void InteropQuote::updateId(const uint64_t id)
{
}

const std::vector<std::string> &InteropQuote::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "transaction_code",
        "quote_code",
        "account_id",
        "amount",
        "fee_amount",
        "currency",
        "expiration",
        "status",
        "created_at"
    };
    return inCols;
}

void InteropQuote::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getQuoteCode())
        {
            binder << getValueOfQuoteCode();
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
        if(getFeeAmount())
        {
            binder << getValueOfFeeAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getExpiration())
        {
            binder << getValueOfExpiration();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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

const std::vector<std::string> InteropQuote::updateColumns() const
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

void InteropQuote::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getQuoteCode())
        {
            binder << getValueOfQuoteCode();
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
        if(getFeeAmount())
        {
            binder << getValueOfFeeAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getExpiration())
        {
            binder << getValueOfExpiration();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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
