/**
 *  CashierTransaction.cc
 *
 *  See CashierTransaction.h for the hand-authored-subset note.
 *
 */

#include "CashierTransaction.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlTellerDb;

const std::string CashierTransaction::Cols::_id = "\"id\"";
const std::string CashierTransaction::Cols::_cashier_id = "\"cashier_id\"";
const std::string CashierTransaction::Cols::_txn_type = "\"txn_type\"";
const std::string CashierTransaction::Cols::_txn_amount = "\"txn_amount\"";
const std::string CashierTransaction::Cols::_txn_date = "\"txn_date\"";
const std::string CashierTransaction::Cols::_currency_code = "\"currency_code\"";
const std::string CashierTransaction::Cols::_entity_id = "\"entity_id\"";
const std::string CashierTransaction::Cols::_entity_type = "\"entity_type\"";
const std::string CashierTransaction::Cols::_txn_note = "\"txn_note\"";
const std::string CashierTransaction::Cols::_created_at = "\"created_at\"";
const std::string CashierTransaction::primaryKeyName = "id";
const bool CashierTransaction::hasPrimaryKey = true;
const std::string CashierTransaction::tableName = "\"cashier_transactions\"";

const std::vector<typename CashierTransaction::MetaData> CashierTransaction::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"cashier_id","std::string","uuid",0,0,0,1},
{"txn_type","int32_t","integer",4,0,0,1},
{"txn_amount","std::string","numeric",0,0,0,1},
{"txn_date","::trantor::Date","date",0,0,0,1},
{"currency_code","std::string","character varying",3,0,0,1},
{"entity_id","std::string","uuid",0,0,0,0},
{"entity_type","std::string","character varying",50,0,0,0},
{"txn_note","std::string","text",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &CashierTransaction::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
CashierTransaction::CashierTransaction(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["cashier_id"].isNull())
        {
            cashierId_=std::make_shared<std::string>(r["cashier_id"].as<std::string>());
        }
        if(!r["txn_type"].isNull())
        {
            txnType_=std::make_shared<int32_t>(r["txn_type"].as<int32_t>());
        }
        if(!r["txn_amount"].isNull())
        {
            txnAmount_=std::make_shared<std::string>(r["txn_amount"].as<std::string>());
        }
        if(!r["txn_date"].isNull())
        {
            auto daysStr = r["txn_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            txnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["entity_id"].isNull())
        {
            entityId_=std::make_shared<std::string>(r["entity_id"].as<std::string>());
        }
        if(!r["entity_type"].isNull())
        {
            entityType_=std::make_shared<std::string>(r["entity_type"].as<std::string>());
        }
        if(!r["txn_note"].isNull())
        {
            txnNote_=std::make_shared<std::string>(r["txn_note"].as<std::string>());
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
            cashierId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            txnType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            txnAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            txnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            entityId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            entityType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            txnNote_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &CashierTransaction::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CashierTransaction::getId() const noexcept
{
    return id_;
}
void CashierTransaction::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void CashierTransaction::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename CashierTransaction::PrimaryKeyType & CashierTransaction::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &CashierTransaction::getValueOfCashierId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(cashierId_)
        return *cashierId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CashierTransaction::getCashierId() const noexcept
{
    return cashierId_;
}
void CashierTransaction::setCashierId(const std::string &pCashierId) noexcept
{
    cashierId_ = std::make_shared<std::string>(pCashierId);
    dirtyFlag_[1] = true;
}
void CashierTransaction::setCashierId(std::string &&pCashierId) noexcept
{
    cashierId_ = std::make_shared<std::string>(std::move(pCashierId));
    dirtyFlag_[1] = true;
}

const int32_t &CashierTransaction::getValueOfTxnType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(txnType_)
        return *txnType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &CashierTransaction::getTxnType() const noexcept
{
    return txnType_;
}
void CashierTransaction::setTxnType(const int32_t &pTxnType) noexcept
{
    txnType_ = std::make_shared<int32_t>(pTxnType);
    dirtyFlag_[2] = true;
}

const std::string &CashierTransaction::getValueOfTxnAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(txnAmount_)
        return *txnAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CashierTransaction::getTxnAmount() const noexcept
{
    return txnAmount_;
}
void CashierTransaction::setTxnAmount(const std::string &pTxnAmount) noexcept
{
    txnAmount_ = std::make_shared<std::string>(pTxnAmount);
    dirtyFlag_[3] = true;
}
void CashierTransaction::setTxnAmount(std::string &&pTxnAmount) noexcept
{
    txnAmount_ = std::make_shared<std::string>(std::move(pTxnAmount));
    dirtyFlag_[3] = true;
}

const ::trantor::Date &CashierTransaction::getValueOfTxnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(txnDate_)
        return *txnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &CashierTransaction::getTxnDate() const noexcept
{
    return txnDate_;
}
void CashierTransaction::setTxnDate(const ::trantor::Date &pTxnDate) noexcept
{
    txnDate_ = std::make_shared<::trantor::Date>(pTxnDate);
    dirtyFlag_[4] = true;
}

const std::string &CashierTransaction::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CashierTransaction::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void CashierTransaction::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[5] = true;
}
void CashierTransaction::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[5] = true;
}

const std::string &CashierTransaction::getValueOfEntityId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(entityId_)
        return *entityId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CashierTransaction::getEntityId() const noexcept
{
    return entityId_;
}
void CashierTransaction::setEntityId(const std::string &pEntityId) noexcept
{
    entityId_ = std::make_shared<std::string>(pEntityId);
    dirtyFlag_[6] = true;
}
void CashierTransaction::setEntityId(std::string &&pEntityId) noexcept
{
    entityId_ = std::make_shared<std::string>(std::move(pEntityId));
    dirtyFlag_[6] = true;
}
void CashierTransaction::setEntityIdToNull() noexcept
{
    entityId_.reset();
    dirtyFlag_[6] = true;
}

const std::string &CashierTransaction::getValueOfEntityType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(entityType_)
        return *entityType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CashierTransaction::getEntityType() const noexcept
{
    return entityType_;
}
void CashierTransaction::setEntityType(const std::string &pEntityType) noexcept
{
    entityType_ = std::make_shared<std::string>(pEntityType);
    dirtyFlag_[7] = true;
}
void CashierTransaction::setEntityType(std::string &&pEntityType) noexcept
{
    entityType_ = std::make_shared<std::string>(std::move(pEntityType));
    dirtyFlag_[7] = true;
}
void CashierTransaction::setEntityTypeToNull() noexcept
{
    entityType_.reset();
    dirtyFlag_[7] = true;
}

const std::string &CashierTransaction::getValueOfTxnNote() const noexcept
{
    static const std::string defaultValue = std::string();
    if(txnNote_)
        return *txnNote_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CashierTransaction::getTxnNote() const noexcept
{
    return txnNote_;
}
void CashierTransaction::setTxnNote(const std::string &pTxnNote) noexcept
{
    txnNote_ = std::make_shared<std::string>(pTxnNote);
    dirtyFlag_[8] = true;
}
void CashierTransaction::setTxnNote(std::string &&pTxnNote) noexcept
{
    txnNote_ = std::make_shared<std::string>(std::move(pTxnNote));
    dirtyFlag_[8] = true;
}
void CashierTransaction::setTxnNoteToNull() noexcept
{
    txnNote_.reset();
    dirtyFlag_[8] = true;
}

const ::trantor::Date &CashierTransaction::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &CashierTransaction::getCreatedAt() const noexcept
{
    return createdAt_;
}
void CashierTransaction::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[9] = true;
}

void CashierTransaction::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CashierTransaction::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "cashier_id",
        "txn_type",
        "txn_amount",
        "txn_date",
        "currency_code",
        "entity_id",
        "entity_type",
        "txn_note",
        "created_at"
    };
    return inCols;
}

void CashierTransaction::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCashierId())
        {
            binder << getValueOfCashierId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTxnType())
        {
            binder << getValueOfTxnType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTxnAmount())
        {
            binder << getValueOfTxnAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTxnDate())
        {
            binder << getValueOfTxnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getEntityId())
        {
            binder << getValueOfEntityId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getEntityType())
        {
            binder << getValueOfEntityType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getTxnNote())
        {
            binder << getValueOfTxnNote();
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

const std::vector<std::string> CashierTransaction::updateColumns() const
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

void CashierTransaction::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCashierId())
        {
            binder << getValueOfCashierId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTxnType())
        {
            binder << getValueOfTxnType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTxnAmount())
        {
            binder << getValueOfTxnAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTxnDate())
        {
            binder << getValueOfTxnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getEntityId())
        {
            binder << getValueOfEntityId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getEntityType())
        {
            binder << getValueOfEntityType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getTxnNote())
        {
            binder << getValueOfTxnNote();
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
