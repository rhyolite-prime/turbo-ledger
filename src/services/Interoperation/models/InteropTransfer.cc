/**
 *  InteropTransfer.cc
 *
 *  See InteropTransfer.h for the hand-authored-subset note.
 *
 */

#include "InteropTransfer.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlInteroperationDb;

const std::string InteropTransfer::Cols::_id = "\"id\"";
const std::string InteropTransfer::Cols::_transaction_code = "\"transaction_code\"";
const std::string InteropTransfer::Cols::_transfer_code = "\"transfer_code\"";
const std::string InteropTransfer::Cols::_account_id = "\"account_id\"";
const std::string InteropTransfer::Cols::_amount = "\"amount\"";
const std::string InteropTransfer::Cols::_currency = "\"currency\"";
const std::string InteropTransfer::Cols::_transfer_action = "\"transfer_action\"";
const std::string InteropTransfer::Cols::_status = "\"status\"";
const std::string InteropTransfer::Cols::_created_at = "\"created_at\"";
const std::string InteropTransfer::primaryKeyName = "id";
const bool InteropTransfer::hasPrimaryKey = true;
const std::string InteropTransfer::tableName = "\"interop_transfers\"";

const std::vector<typename InteropTransfer::MetaData> InteropTransfer::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"transaction_code","std::string","character varying",64,0,0,1},
{"transfer_code","std::string","character varying",64,0,0,1},
{"account_id","std::string","character varying",64,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"currency","std::string","character varying",10,0,0,1},
{"transfer_action","std::string","character varying",20,0,0,1},
{"status","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &InteropTransfer::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
InteropTransfer::InteropTransfer(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["transfer_code"].isNull())
        {
            transferCode_=std::make_shared<std::string>(r["transfer_code"].as<std::string>());
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
        if(!r["transfer_action"].isNull())
        {
            transferAction_=std::make_shared<std::string>(r["transfer_action"].as<std::string>());
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
            transactionCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            transferCode_=std::make_shared<std::string>(r[index].as<std::string>());
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
            transferAction_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &InteropTransfer::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getId() const noexcept
{
    return id_;
}
void InteropTransfer::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void InteropTransfer::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename InteropTransfer::PrimaryKeyType & InteropTransfer::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &InteropTransfer::getValueOfTransactionCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transactionCode_)
        return *transactionCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getTransactionCode() const noexcept
{
    return transactionCode_;
}
void InteropTransfer::setTransactionCode(const std::string &pTransactionCode) noexcept
{
    transactionCode_ = std::make_shared<std::string>(pTransactionCode);
    dirtyFlag_[1] = true;
}
void InteropTransfer::setTransactionCode(std::string &&pTransactionCode) noexcept
{
    transactionCode_ = std::make_shared<std::string>(std::move(pTransactionCode));
    dirtyFlag_[1] = true;
}

const std::string &InteropTransfer::getValueOfTransferCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transferCode_)
        return *transferCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getTransferCode() const noexcept
{
    return transferCode_;
}
void InteropTransfer::setTransferCode(const std::string &pTransferCode) noexcept
{
    transferCode_ = std::make_shared<std::string>(pTransferCode);
    dirtyFlag_[2] = true;
}
void InteropTransfer::setTransferCode(std::string &&pTransferCode) noexcept
{
    transferCode_ = std::make_shared<std::string>(std::move(pTransferCode));
    dirtyFlag_[2] = true;
}

const std::string &InteropTransfer::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getAccountId() const noexcept
{
    return accountId_;
}
void InteropTransfer::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[3] = true;
}
void InteropTransfer::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[3] = true;
}

const std::string &InteropTransfer::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getAmount() const noexcept
{
    return amount_;
}
void InteropTransfer::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[4] = true;
}
void InteropTransfer::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[4] = true;
}

const std::string &InteropTransfer::getValueOfCurrency() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currency_)
        return *currency_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getCurrency() const noexcept
{
    return currency_;
}
void InteropTransfer::setCurrency(const std::string &pCurrency) noexcept
{
    currency_ = std::make_shared<std::string>(pCurrency);
    dirtyFlag_[5] = true;
}
void InteropTransfer::setCurrency(std::string &&pCurrency) noexcept
{
    currency_ = std::make_shared<std::string>(std::move(pCurrency));
    dirtyFlag_[5] = true;
}

const std::string &InteropTransfer::getValueOfTransferAction() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transferAction_)
        return *transferAction_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getTransferAction() const noexcept
{
    return transferAction_;
}
void InteropTransfer::setTransferAction(const std::string &pTransferAction) noexcept
{
    transferAction_ = std::make_shared<std::string>(pTransferAction);
    dirtyFlag_[6] = true;
}
void InteropTransfer::setTransferAction(std::string &&pTransferAction) noexcept
{
    transferAction_ = std::make_shared<std::string>(std::move(pTransferAction));
    dirtyFlag_[6] = true;
}

const std::string &InteropTransfer::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &InteropTransfer::getStatus() const noexcept
{
    return status_;
}
void InteropTransfer::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[7] = true;
}
void InteropTransfer::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[7] = true;
}

const ::trantor::Date &InteropTransfer::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &InteropTransfer::getCreatedAt() const noexcept
{
    return createdAt_;
}
void InteropTransfer::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}

void InteropTransfer::updateId(const uint64_t id)
{
}

const std::vector<std::string> &InteropTransfer::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "transaction_code",
        "transfer_code",
        "account_id",
        "amount",
        "currency",
        "transfer_action",
        "status",
        "created_at"
    };
    return inCols;
}

void InteropTransfer::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTransferCode())
        {
            binder << getValueOfTransferCode();
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
        if(getTransferAction())
        {
            binder << getValueOfTransferAction();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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

const std::vector<std::string> InteropTransfer::updateColumns() const
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

void InteropTransfer::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTransferCode())
        {
            binder << getValueOfTransferCode();
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
        if(getTransferAction())
        {
            binder << getValueOfTransferAction();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
