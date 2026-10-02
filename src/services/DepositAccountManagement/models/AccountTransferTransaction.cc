/**
 *  AccountTransferTransaction.cc
 *
 *  See AccountTransferTransaction.h for the hand-authored-subset note.
 *
 */

#include "AccountTransferTransaction.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string AccountTransferTransaction::Cols::_id = "\"id\"";
const std::string AccountTransferTransaction::Cols::_business_id = "\"business_id\"";
const std::string AccountTransferTransaction::Cols::_account_transfer_details_id = "\"account_transfer_details_id\"";
const std::string AccountTransferTransaction::Cols::_from_transaction_id = "\"from_transaction_id\"";
const std::string AccountTransferTransaction::Cols::_to_transaction_id = "\"to_transaction_id\"";
const std::string AccountTransferTransaction::Cols::_transaction_date = "\"transaction_date\"";
const std::string AccountTransferTransaction::Cols::_transaction_amount = "\"transaction_amount\"";
const std::string AccountTransferTransaction::Cols::_description = "\"description\"";
const std::string AccountTransferTransaction::Cols::_is_reversed = "\"is_reversed\"";
const std::string AccountTransferTransaction::Cols::_created_by = "\"created_by\"";
const std::string AccountTransferTransaction::Cols::_created_at = "\"created_at\"";
const std::string AccountTransferTransaction::Cols::_updated_by = "\"updated_by\"";
const std::string AccountTransferTransaction::Cols::_updated_at = "\"updated_at\"";
const std::string AccountTransferTransaction::primaryKeyName = "id";
const bool AccountTransferTransaction::hasPrimaryKey = true;
const std::string AccountTransferTransaction::tableName = "\"account_transfer_transaction\"";

const std::vector<typename AccountTransferTransaction::MetaData> AccountTransferTransaction::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"account_transfer_details_id","std::string","uuid",0,0,0,1},
{"from_transaction_id","std::string","uuid",0,0,0,0},
{"to_transaction_id","std::string","uuid",0,0,0,0},
{"transaction_date","::trantor::Date","date",0,0,0,1},
{"transaction_amount","std::string","numeric",0,0,0,1},
{"description","std::string","character varying",500,0,0,0},
{"is_reversed","bool","boolean",1,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &AccountTransferTransaction::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
AccountTransferTransaction::AccountTransferTransaction(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["account_transfer_details_id"].isNull())
        {
            accountTransferDetailsId_=std::make_shared<std::string>(r["account_transfer_details_id"].as<std::string>());
        }
        if(!r["from_transaction_id"].isNull())
        {
            fromTransactionId_=std::make_shared<std::string>(r["from_transaction_id"].as<std::string>());
        }
        if(!r["to_transaction_id"].isNull())
        {
            toTransactionId_=std::make_shared<std::string>(r["to_transaction_id"].as<std::string>());
        }
        if(!r["transaction_date"].isNull())
        {
            auto daysStr = r["transaction_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            transactionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["transaction_amount"].isNull())
        {
            transactionAmount_=std::make_shared<std::string>(r["transaction_amount"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["is_reversed"].isNull())
        {
            isReversed_=std::make_shared<bool>(r["is_reversed"].as<bool>());
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
        if(offset + 13 > r.size())
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
            accountTransferDetailsId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            fromTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            toTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            transactionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            transactionAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            isReversed_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
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
        index = offset + 11;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &AccountTransferTransaction::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getId() const noexcept
{
    return id_;
}
void AccountTransferTransaction::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void AccountTransferTransaction::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename AccountTransferTransaction::PrimaryKeyType & AccountTransferTransaction::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &AccountTransferTransaction::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getBusinessId() const noexcept
{
    return businessId_;
}
void AccountTransferTransaction::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void AccountTransferTransaction::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void AccountTransferTransaction::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &AccountTransferTransaction::getValueOfAccountTransferDetailsId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountTransferDetailsId_)
        return *accountTransferDetailsId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getAccountTransferDetailsId() const noexcept
{
    return accountTransferDetailsId_;
}
void AccountTransferTransaction::setAccountTransferDetailsId(const std::string &pAccountTransferDetailsId) noexcept
{
    accountTransferDetailsId_ = std::make_shared<std::string>(pAccountTransferDetailsId);
    dirtyFlag_[2] = true;
}
void AccountTransferTransaction::setAccountTransferDetailsId(std::string &&pAccountTransferDetailsId) noexcept
{
    accountTransferDetailsId_ = std::make_shared<std::string>(std::move(pAccountTransferDetailsId));
    dirtyFlag_[2] = true;
}

const std::string &AccountTransferTransaction::getValueOfFromTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromTransactionId_)
        return *fromTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getFromTransactionId() const noexcept
{
    return fromTransactionId_;
}
void AccountTransferTransaction::setFromTransactionId(const std::string &pFromTransactionId) noexcept
{
    fromTransactionId_ = std::make_shared<std::string>(pFromTransactionId);
    dirtyFlag_[3] = true;
}
void AccountTransferTransaction::setFromTransactionId(std::string &&pFromTransactionId) noexcept
{
    fromTransactionId_ = std::make_shared<std::string>(std::move(pFromTransactionId));
    dirtyFlag_[3] = true;
}
void AccountTransferTransaction::setFromTransactionIdToNull() noexcept
{
    fromTransactionId_.reset();
    dirtyFlag_[3] = true;
}

const std::string &AccountTransferTransaction::getValueOfToTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toTransactionId_)
        return *toTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getToTransactionId() const noexcept
{
    return toTransactionId_;
}
void AccountTransferTransaction::setToTransactionId(const std::string &pToTransactionId) noexcept
{
    toTransactionId_ = std::make_shared<std::string>(pToTransactionId);
    dirtyFlag_[4] = true;
}
void AccountTransferTransaction::setToTransactionId(std::string &&pToTransactionId) noexcept
{
    toTransactionId_ = std::make_shared<std::string>(std::move(pToTransactionId));
    dirtyFlag_[4] = true;
}
void AccountTransferTransaction::setToTransactionIdToNull() noexcept
{
    toTransactionId_.reset();
    dirtyFlag_[4] = true;
}

const ::trantor::Date &AccountTransferTransaction::getValueOfTransactionDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(transactionDate_)
        return *transactionDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &AccountTransferTransaction::getTransactionDate() const noexcept
{
    return transactionDate_;
}
void AccountTransferTransaction::setTransactionDate(const ::trantor::Date &pTransactionDate) noexcept
{
    transactionDate_ = std::make_shared<::trantor::Date>(pTransactionDate);
    dirtyFlag_[5] = true;
}

const std::string &AccountTransferTransaction::getValueOfTransactionAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transactionAmount_)
        return *transactionAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getTransactionAmount() const noexcept
{
    return transactionAmount_;
}
void AccountTransferTransaction::setTransactionAmount(const std::string &pTransactionAmount) noexcept
{
    transactionAmount_ = std::make_shared<std::string>(pTransactionAmount);
    dirtyFlag_[6] = true;
}
void AccountTransferTransaction::setTransactionAmount(std::string &&pTransactionAmount) noexcept
{
    transactionAmount_ = std::make_shared<std::string>(std::move(pTransactionAmount));
    dirtyFlag_[6] = true;
}

const std::string &AccountTransferTransaction::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getDescription() const noexcept
{
    return description_;
}
void AccountTransferTransaction::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[7] = true;
}
void AccountTransferTransaction::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[7] = true;
}
void AccountTransferTransaction::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[7] = true;
}

const bool &AccountTransferTransaction::getValueOfIsReversed() const noexcept
{
    static const bool defaultValue = bool();
    if(isReversed_)
        return *isReversed_;
    return defaultValue;
}
const std::shared_ptr<bool> &AccountTransferTransaction::getIsReversed() const noexcept
{
    return isReversed_;
}
void AccountTransferTransaction::setIsReversed(const bool &pIsReversed) noexcept
{
    isReversed_ = std::make_shared<bool>(pIsReversed);
    dirtyFlag_[8] = true;
}

const std::string &AccountTransferTransaction::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getCreatedBy() const noexcept
{
    return createdBy_;
}
void AccountTransferTransaction::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[9] = true;
}
void AccountTransferTransaction::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[9] = true;
}
void AccountTransferTransaction::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[9] = true;
}

const ::trantor::Date &AccountTransferTransaction::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &AccountTransferTransaction::getCreatedAt() const noexcept
{
    return createdAt_;
}
void AccountTransferTransaction::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[10] = true;
}

const std::string &AccountTransferTransaction::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferTransaction::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void AccountTransferTransaction::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[11] = true;
}
void AccountTransferTransaction::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[11] = true;
}
void AccountTransferTransaction::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[11] = true;
}

const ::trantor::Date &AccountTransferTransaction::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &AccountTransferTransaction::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void AccountTransferTransaction::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[12] = true;
}

void AccountTransferTransaction::updateId(const uint64_t id)
{
}

const std::vector<std::string> &AccountTransferTransaction::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "account_transfer_details_id",
        "from_transaction_id",
        "to_transaction_id",
        "transaction_date",
        "transaction_amount",
        "description",
        "is_reversed",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void AccountTransferTransaction::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountTransferDetailsId())
        {
            binder << getValueOfAccountTransferDetailsId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromTransactionId())
        {
            binder << getValueOfFromTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getToTransactionId())
        {
            binder << getValueOfToTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransactionDate())
        {
            binder << getValueOfTransactionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getTransactionAmount())
        {
            binder << getValueOfTransactionAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getIsReversed())
        {
            binder << getValueOfIsReversed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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

const std::vector<std::string> AccountTransferTransaction::updateColumns() const
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
    return ret;
}

void AccountTransferTransaction::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountTransferDetailsId())
        {
            binder << getValueOfAccountTransferDetailsId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromTransactionId())
        {
            binder << getValueOfFromTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getToTransactionId())
        {
            binder << getValueOfToTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransactionDate())
        {
            binder << getValueOfTransactionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getTransactionAmount())
        {
            binder << getValueOfTransactionAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getIsReversed())
        {
            binder << getValueOfIsReversed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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
