/**
 *  LoanOwnerTransferJournalEntry.cc
 *
 *  See LoanOwnerTransferJournalEntry.h for the hand-authored-subset note.
 *
 */

#include "LoanOwnerTransferJournalEntry.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanOwnerTransferJournalEntry::Cols::_id = "\"id\"";
const std::string LoanOwnerTransferJournalEntry::Cols::_transfer_id = "\"transfer_id\"";
const std::string LoanOwnerTransferJournalEntry::Cols::_entry_type = "\"entry_type\"";
const std::string LoanOwnerTransferJournalEntry::Cols::_amount = "\"amount\"";
const std::string LoanOwnerTransferJournalEntry::Cols::_gl_account_id = "\"gl_account_id\"";
const std::string LoanOwnerTransferJournalEntry::Cols::_created_at = "\"created_at\"";
const std::string LoanOwnerTransferJournalEntry::primaryKeyName = "id";
const bool LoanOwnerTransferJournalEntry::hasPrimaryKey = true;
const std::string LoanOwnerTransferJournalEntry::tableName = "\"loan_owner_transfer_journal_entry\"";

const std::vector<typename LoanOwnerTransferJournalEntry::MetaData> LoanOwnerTransferJournalEntry::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"transfer_id","std::string","uuid",0,0,0,1},
{"entry_type","std::string","character varying",40,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"gl_account_id","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanOwnerTransferJournalEntry::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanOwnerTransferJournalEntry::LoanOwnerTransferJournalEntry(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["transfer_id"].isNull())
        {
            transferId_=std::make_shared<std::string>(r["transfer_id"].as<std::string>());
        }
        if(!r["entry_type"].isNull())
        {
            entryType_=std::make_shared<std::string>(r["entry_type"].as<std::string>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["gl_account_id"].isNull())
        {
            glAccountId_=std::make_shared<std::string>(r["gl_account_id"].as<std::string>());
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
        if(offset + 6 > r.size())
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
            transferId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            entryType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            glAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
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
const std::string &LoanOwnerTransferJournalEntry::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransferJournalEntry::getId() const noexcept
{
    return id_;
}
void LoanOwnerTransferJournalEntry::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanOwnerTransferJournalEntry::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanOwnerTransferJournalEntry::PrimaryKeyType & LoanOwnerTransferJournalEntry::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanOwnerTransferJournalEntry::getValueOfTransferId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transferId_)
        return *transferId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransferJournalEntry::getTransferId() const noexcept
{
    return transferId_;
}
void LoanOwnerTransferJournalEntry::setTransferId(const std::string &pTransferId) noexcept
{
    transferId_ = std::make_shared<std::string>(pTransferId);
    dirtyFlag_[1] = true;
}
void LoanOwnerTransferJournalEntry::setTransferId(std::string &&pTransferId) noexcept
{
    transferId_ = std::make_shared<std::string>(std::move(pTransferId));
    dirtyFlag_[1] = true;
}

const std::string &LoanOwnerTransferJournalEntry::getValueOfEntryType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(entryType_)
        return *entryType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransferJournalEntry::getEntryType() const noexcept
{
    return entryType_;
}
void LoanOwnerTransferJournalEntry::setEntryType(const std::string &pEntryType) noexcept
{
    entryType_ = std::make_shared<std::string>(pEntryType);
    dirtyFlag_[2] = true;
}
void LoanOwnerTransferJournalEntry::setEntryType(std::string &&pEntryType) noexcept
{
    entryType_ = std::make_shared<std::string>(std::move(pEntryType));
    dirtyFlag_[2] = true;
}

const std::string &LoanOwnerTransferJournalEntry::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransferJournalEntry::getAmount() const noexcept
{
    return amount_;
}
void LoanOwnerTransferJournalEntry::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[3] = true;
}
void LoanOwnerTransferJournalEntry::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[3] = true;
}

const std::string &LoanOwnerTransferJournalEntry::getValueOfGlAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(glAccountId_)
        return *glAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransferJournalEntry::getGlAccountId() const noexcept
{
    return glAccountId_;
}
void LoanOwnerTransferJournalEntry::setGlAccountId(const std::string &pGlAccountId) noexcept
{
    glAccountId_ = std::make_shared<std::string>(pGlAccountId);
    dirtyFlag_[4] = true;
}
void LoanOwnerTransferJournalEntry::setGlAccountId(std::string &&pGlAccountId) noexcept
{
    glAccountId_ = std::make_shared<std::string>(std::move(pGlAccountId));
    dirtyFlag_[4] = true;
}
void LoanOwnerTransferJournalEntry::setGlAccountIdToNull() noexcept
{
    glAccountId_.reset();
    dirtyFlag_[4] = true;
}

const ::trantor::Date &LoanOwnerTransferJournalEntry::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanOwnerTransferJournalEntry::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanOwnerTransferJournalEntry::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

void LoanOwnerTransferJournalEntry::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanOwnerTransferJournalEntry::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "transfer_id",
        "entry_type",
        "amount",
        "gl_account_id",
        "created_at"
    };
    return inCols;
}

void LoanOwnerTransferJournalEntry::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTransferId())
        {
            binder << getValueOfTransferId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getEntryType())
        {
            binder << getValueOfEntryType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getGlAccountId())
        {
            binder << getValueOfGlAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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

const std::vector<std::string> LoanOwnerTransferJournalEntry::updateColumns() const
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
    return ret;
}

void LoanOwnerTransferJournalEntry::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTransferId())
        {
            binder << getValueOfTransferId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getEntryType())
        {
            binder << getValueOfEntryType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getGlAccountId())
        {
            binder << getValueOfGlAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
