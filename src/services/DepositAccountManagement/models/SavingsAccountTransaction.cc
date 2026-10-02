/**
 *  SavingsAccountTransaction.cc
 *
 *  See SavingsAccountTransaction.h for the hand-authored-subset note.
 *
 */

#include "SavingsAccountTransaction.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string SavingsAccountTransaction::Cols::_id = "\"id\"";
const std::string SavingsAccountTransaction::Cols::_business_id = "\"business_id\"";
const std::string SavingsAccountTransaction::Cols::_savings_account_id = "\"savings_account_id\"";
const std::string SavingsAccountTransaction::Cols::_transaction_type = "\"transaction_type\"";
const std::string SavingsAccountTransaction::Cols::_transaction_date = "\"transaction_date\"";
const std::string SavingsAccountTransaction::Cols::_amount = "\"amount\"";
const std::string SavingsAccountTransaction::Cols::_running_balance_derived = "\"running_balance_derived\"";
const std::string SavingsAccountTransaction::Cols::_overdraft_amount_derived = "\"overdraft_amount_derived\"";
const std::string SavingsAccountTransaction::Cols::_is_reversed = "\"is_reversed\"";
const std::string SavingsAccountTransaction::Cols::_is_hold_transaction = "\"is_hold_transaction\"";
const std::string SavingsAccountTransaction::Cols::_release_id_of_hold = "\"release_id_of_hold\"";
const std::string SavingsAccountTransaction::Cols::_payment_detail_id = "\"payment_detail_id\"";
const std::string SavingsAccountTransaction::Cols::_submitted_on_date = "\"submitted_on_date\"";
const std::string SavingsAccountTransaction::Cols::_description = "\"description\"";
const std::string SavingsAccountTransaction::Cols::_created_by = "\"created_by\"";
const std::string SavingsAccountTransaction::Cols::_created_at = "\"created_at\"";
const std::string SavingsAccountTransaction::Cols::_updated_by = "\"updated_by\"";
const std::string SavingsAccountTransaction::Cols::_updated_at = "\"updated_at\"";
const std::string SavingsAccountTransaction::primaryKeyName = "id";
const bool SavingsAccountTransaction::hasPrimaryKey = true;
const std::string SavingsAccountTransaction::tableName = "\"savings_account_transaction\"";

const std::vector<typename SavingsAccountTransaction::MetaData> SavingsAccountTransaction::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"savings_account_id","std::string","uuid",0,0,0,1},
{"transaction_type","int32_t","integer",4,0,0,1},
{"transaction_date","::trantor::Date","date",0,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"running_balance_derived","std::string","numeric",0,0,0,1},
{"overdraft_amount_derived","std::string","numeric",0,0,0,1},
{"is_reversed","bool","boolean",1,0,0,1},
{"is_hold_transaction","bool","boolean",1,0,0,1},
{"release_id_of_hold","std::string","uuid",0,0,0,0},
{"payment_detail_id","std::string","uuid",0,0,0,0},
{"submitted_on_date","::trantor::Date","date",0,0,0,1},
{"description","std::string","character varying",500,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SavingsAccountTransaction::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SavingsAccountTransaction::SavingsAccountTransaction(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["savings_account_id"].isNull())
        {
            savingsAccountId_=std::make_shared<std::string>(r["savings_account_id"].as<std::string>());
        }
        if(!r["transaction_type"].isNull())
        {
            transactionType_=std::make_shared<int32_t>(r["transaction_type"].as<int32_t>());
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
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["running_balance_derived"].isNull())
        {
            runningBalanceDerived_=std::make_shared<std::string>(r["running_balance_derived"].as<std::string>());
        }
        if(!r["overdraft_amount_derived"].isNull())
        {
            overdraftAmountDerived_=std::make_shared<std::string>(r["overdraft_amount_derived"].as<std::string>());
        }
        if(!r["is_reversed"].isNull())
        {
            isReversed_=std::make_shared<bool>(r["is_reversed"].as<bool>());
        }
        if(!r["is_hold_transaction"].isNull())
        {
            isHoldTransaction_=std::make_shared<bool>(r["is_hold_transaction"].as<bool>());
        }
        if(!r["release_id_of_hold"].isNull())
        {
            releaseIdOfHold_=std::make_shared<std::string>(r["release_id_of_hold"].as<std::string>());
        }
        if(!r["payment_detail_id"].isNull())
        {
            paymentDetailId_=std::make_shared<std::string>(r["payment_detail_id"].as<std::string>());
        }
        if(!r["submitted_on_date"].isNull())
        {
            auto daysStr = r["submitted_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
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
        if(offset + 18 > r.size())
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
            savingsAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            transactionType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            transactionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            runningBalanceDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            overdraftAmountDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            isReversed_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            isHoldTransaction_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            releaseIdOfHold_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            paymentDetailId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
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
        index = offset + 16;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 17;
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
const std::string &SavingsAccountTransaction::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getId() const noexcept
{
    return id_;
}
void SavingsAccountTransaction::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SavingsAccountTransaction::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SavingsAccountTransaction::PrimaryKeyType & SavingsAccountTransaction::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SavingsAccountTransaction::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getBusinessId() const noexcept
{
    return businessId_;
}
void SavingsAccountTransaction::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void SavingsAccountTransaction::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void SavingsAccountTransaction::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &SavingsAccountTransaction::getValueOfSavingsAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(savingsAccountId_)
        return *savingsAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getSavingsAccountId() const noexcept
{
    return savingsAccountId_;
}
void SavingsAccountTransaction::setSavingsAccountId(const std::string &pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(pSavingsAccountId);
    dirtyFlag_[2] = true;
}
void SavingsAccountTransaction::setSavingsAccountId(std::string &&pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(std::move(pSavingsAccountId));
    dirtyFlag_[2] = true;
}

const int32_t &SavingsAccountTransaction::getValueOfTransactionType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(transactionType_)
        return *transactionType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccountTransaction::getTransactionType() const noexcept
{
    return transactionType_;
}
void SavingsAccountTransaction::setTransactionType(const int32_t &pTransactionType) noexcept
{
    transactionType_ = std::make_shared<int32_t>(pTransactionType);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &SavingsAccountTransaction::getValueOfTransactionDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(transactionDate_)
        return *transactionDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountTransaction::getTransactionDate() const noexcept
{
    return transactionDate_;
}
void SavingsAccountTransaction::setTransactionDate(const ::trantor::Date &pTransactionDate) noexcept
{
    transactionDate_ = std::make_shared<::trantor::Date>(pTransactionDate);
    dirtyFlag_[4] = true;
}

const std::string &SavingsAccountTransaction::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getAmount() const noexcept
{
    return amount_;
}
void SavingsAccountTransaction::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[5] = true;
}
void SavingsAccountTransaction::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[5] = true;
}

const std::string &SavingsAccountTransaction::getValueOfRunningBalanceDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(runningBalanceDerived_)
        return *runningBalanceDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getRunningBalanceDerived() const noexcept
{
    return runningBalanceDerived_;
}
void SavingsAccountTransaction::setRunningBalanceDerived(const std::string &pRunningBalanceDerived) noexcept
{
    runningBalanceDerived_ = std::make_shared<std::string>(pRunningBalanceDerived);
    dirtyFlag_[6] = true;
}
void SavingsAccountTransaction::setRunningBalanceDerived(std::string &&pRunningBalanceDerived) noexcept
{
    runningBalanceDerived_ = std::make_shared<std::string>(std::move(pRunningBalanceDerived));
    dirtyFlag_[6] = true;
}

const std::string &SavingsAccountTransaction::getValueOfOverdraftAmountDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(overdraftAmountDerived_)
        return *overdraftAmountDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getOverdraftAmountDerived() const noexcept
{
    return overdraftAmountDerived_;
}
void SavingsAccountTransaction::setOverdraftAmountDerived(const std::string &pOverdraftAmountDerived) noexcept
{
    overdraftAmountDerived_ = std::make_shared<std::string>(pOverdraftAmountDerived);
    dirtyFlag_[7] = true;
}
void SavingsAccountTransaction::setOverdraftAmountDerived(std::string &&pOverdraftAmountDerived) noexcept
{
    overdraftAmountDerived_ = std::make_shared<std::string>(std::move(pOverdraftAmountDerived));
    dirtyFlag_[7] = true;
}

const bool &SavingsAccountTransaction::getValueOfIsReversed() const noexcept
{
    static const bool defaultValue = bool();
    if(isReversed_)
        return *isReversed_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccountTransaction::getIsReversed() const noexcept
{
    return isReversed_;
}
void SavingsAccountTransaction::setIsReversed(const bool &pIsReversed) noexcept
{
    isReversed_ = std::make_shared<bool>(pIsReversed);
    dirtyFlag_[8] = true;
}

const bool &SavingsAccountTransaction::getValueOfIsHoldTransaction() const noexcept
{
    static const bool defaultValue = bool();
    if(isHoldTransaction_)
        return *isHoldTransaction_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccountTransaction::getIsHoldTransaction() const noexcept
{
    return isHoldTransaction_;
}
void SavingsAccountTransaction::setIsHoldTransaction(const bool &pIsHoldTransaction) noexcept
{
    isHoldTransaction_ = std::make_shared<bool>(pIsHoldTransaction);
    dirtyFlag_[9] = true;
}

const std::string &SavingsAccountTransaction::getValueOfReleaseIdOfHold() const noexcept
{
    static const std::string defaultValue = std::string();
    if(releaseIdOfHold_)
        return *releaseIdOfHold_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getReleaseIdOfHold() const noexcept
{
    return releaseIdOfHold_;
}
void SavingsAccountTransaction::setReleaseIdOfHold(const std::string &pReleaseIdOfHold) noexcept
{
    releaseIdOfHold_ = std::make_shared<std::string>(pReleaseIdOfHold);
    dirtyFlag_[10] = true;
}
void SavingsAccountTransaction::setReleaseIdOfHold(std::string &&pReleaseIdOfHold) noexcept
{
    releaseIdOfHold_ = std::make_shared<std::string>(std::move(pReleaseIdOfHold));
    dirtyFlag_[10] = true;
}
void SavingsAccountTransaction::setReleaseIdOfHoldToNull() noexcept
{
    releaseIdOfHold_.reset();
    dirtyFlag_[10] = true;
}

const std::string &SavingsAccountTransaction::getValueOfPaymentDetailId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(paymentDetailId_)
        return *paymentDetailId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getPaymentDetailId() const noexcept
{
    return paymentDetailId_;
}
void SavingsAccountTransaction::setPaymentDetailId(const std::string &pPaymentDetailId) noexcept
{
    paymentDetailId_ = std::make_shared<std::string>(pPaymentDetailId);
    dirtyFlag_[11] = true;
}
void SavingsAccountTransaction::setPaymentDetailId(std::string &&pPaymentDetailId) noexcept
{
    paymentDetailId_ = std::make_shared<std::string>(std::move(pPaymentDetailId));
    dirtyFlag_[11] = true;
}
void SavingsAccountTransaction::setPaymentDetailIdToNull() noexcept
{
    paymentDetailId_.reset();
    dirtyFlag_[11] = true;
}

const ::trantor::Date &SavingsAccountTransaction::getValueOfSubmittedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedOnDate_)
        return *submittedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountTransaction::getSubmittedOnDate() const noexcept
{
    return submittedOnDate_;
}
void SavingsAccountTransaction::setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept
{
    submittedOnDate_ = std::make_shared<::trantor::Date>(pSubmittedOnDate);
    dirtyFlag_[12] = true;
}

const std::string &SavingsAccountTransaction::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getDescription() const noexcept
{
    return description_;
}
void SavingsAccountTransaction::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[13] = true;
}
void SavingsAccountTransaction::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[13] = true;
}
void SavingsAccountTransaction::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[13] = true;
}

const std::string &SavingsAccountTransaction::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getCreatedBy() const noexcept
{
    return createdBy_;
}
void SavingsAccountTransaction::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[14] = true;
}
void SavingsAccountTransaction::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[14] = true;
}
void SavingsAccountTransaction::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[14] = true;
}

const ::trantor::Date &SavingsAccountTransaction::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountTransaction::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SavingsAccountTransaction::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[15] = true;
}

const std::string &SavingsAccountTransaction::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountTransaction::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void SavingsAccountTransaction::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[16] = true;
}
void SavingsAccountTransaction::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[16] = true;
}
void SavingsAccountTransaction::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[16] = true;
}

const ::trantor::Date &SavingsAccountTransaction::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountTransaction::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void SavingsAccountTransaction::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[17] = true;
}

void SavingsAccountTransaction::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SavingsAccountTransaction::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "savings_account_id",
        "transaction_type",
        "transaction_date",
        "amount",
        "running_balance_derived",
        "overdraft_amount_derived",
        "is_reversed",
        "is_hold_transaction",
        "release_id_of_hold",
        "payment_detail_id",
        "submitted_on_date",
        "description",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void SavingsAccountTransaction::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSavingsAccountId())
        {
            binder << getValueOfSavingsAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTransactionType())
        {
            binder << getValueOfTransactionType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getRunningBalanceDerived())
        {
            binder << getValueOfRunningBalanceDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getOverdraftAmountDerived())
        {
            binder << getValueOfOverdraftAmountDerived();
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
        if(getIsHoldTransaction())
        {
            binder << getValueOfIsHoldTransaction();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getReleaseIdOfHold())
        {
            binder << getValueOfReleaseIdOfHold();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getPaymentDetailId())
        {
            binder << getValueOfPaymentDetailId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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

const std::vector<std::string> SavingsAccountTransaction::updateColumns() const
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
    if(dirtyFlag_[15])
    {
        ret.push_back(getColumnName(15));
    }
    if(dirtyFlag_[16])
    {
        ret.push_back(getColumnName(16));
    }
    if(dirtyFlag_[17])
    {
        ret.push_back(getColumnName(17));
    }
    return ret;
}

void SavingsAccountTransaction::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSavingsAccountId())
        {
            binder << getValueOfSavingsAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTransactionType())
        {
            binder << getValueOfTransactionType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getRunningBalanceDerived())
        {
            binder << getValueOfRunningBalanceDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getOverdraftAmountDerived())
        {
            binder << getValueOfOverdraftAmountDerived();
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
        if(getIsHoldTransaction())
        {
            binder << getValueOfIsHoldTransaction();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getReleaseIdOfHold())
        {
            binder << getValueOfReleaseIdOfHold();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getPaymentDetailId())
        {
            binder << getValueOfPaymentDetailId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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
