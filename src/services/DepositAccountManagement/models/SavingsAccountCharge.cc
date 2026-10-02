/**
 *  SavingsAccountCharge.cc
 *
 *  See SavingsAccountCharge.h for the hand-authored-subset note.
 *
 */

#include "SavingsAccountCharge.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string SavingsAccountCharge::Cols::_id = "\"id\"";
const std::string SavingsAccountCharge::Cols::_business_id = "\"business_id\"";
const std::string SavingsAccountCharge::Cols::_savings_account_id = "\"savings_account_id\"";
const std::string SavingsAccountCharge::Cols::_charge_id = "\"charge_id\"";
const std::string SavingsAccountCharge::Cols::_charge_time_type = "\"charge_time_type\"";
const std::string SavingsAccountCharge::Cols::_due_date = "\"due_date\"";
const std::string SavingsAccountCharge::Cols::_fee_interval = "\"fee_interval\"";
const std::string SavingsAccountCharge::Cols::_amount = "\"amount\"";
const std::string SavingsAccountCharge::Cols::_amount_paid_derived = "\"amount_paid_derived\"";
const std::string SavingsAccountCharge::Cols::_amount_waived_derived = "\"amount_waived_derived\"";
const std::string SavingsAccountCharge::Cols::_amount_outstanding_derived = "\"amount_outstanding_derived\"";
const std::string SavingsAccountCharge::Cols::_is_paid_derived = "\"is_paid_derived\"";
const std::string SavingsAccountCharge::Cols::_is_waived = "\"is_waived\"";
const std::string SavingsAccountCharge::Cols::_is_active = "\"is_active\"";
const std::string SavingsAccountCharge::Cols::_inactivated_on_date = "\"inactivated_on_date\"";
const std::string SavingsAccountCharge::Cols::_created_by = "\"created_by\"";
const std::string SavingsAccountCharge::Cols::_created_at = "\"created_at\"";
const std::string SavingsAccountCharge::Cols::_updated_by = "\"updated_by\"";
const std::string SavingsAccountCharge::Cols::_updated_at = "\"updated_at\"";
const std::string SavingsAccountCharge::primaryKeyName = "id";
const bool SavingsAccountCharge::hasPrimaryKey = true;
const std::string SavingsAccountCharge::tableName = "\"savings_account_charge\"";

const std::vector<typename SavingsAccountCharge::MetaData> SavingsAccountCharge::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"savings_account_id","std::string","uuid",0,0,0,1},
{"charge_id","std::string","uuid",0,0,0,1},
{"charge_time_type","int32_t","integer",4,0,0,1},
{"due_date","::trantor::Date","date",0,0,0,0},
{"fee_interval","int32_t","integer",4,0,0,0},
{"amount","std::string","numeric",0,0,0,1},
{"amount_paid_derived","std::string","numeric",0,0,0,1},
{"amount_waived_derived","std::string","numeric",0,0,0,1},
{"amount_outstanding_derived","std::string","numeric",0,0,0,1},
{"is_paid_derived","bool","boolean",1,0,0,1},
{"is_waived","bool","boolean",1,0,0,1},
{"is_active","bool","boolean",1,0,0,1},
{"inactivated_on_date","::trantor::Date","date",0,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SavingsAccountCharge::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SavingsAccountCharge::SavingsAccountCharge(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["charge_id"].isNull())
        {
            chargeId_=std::make_shared<std::string>(r["charge_id"].as<std::string>());
        }
        if(!r["charge_time_type"].isNull())
        {
            chargeTimeType_=std::make_shared<int32_t>(r["charge_time_type"].as<int32_t>());
        }
        if(!r["due_date"].isNull())
        {
            auto daysStr = r["due_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["fee_interval"].isNull())
        {
            feeInterval_=std::make_shared<int32_t>(r["fee_interval"].as<int32_t>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["amount_paid_derived"].isNull())
        {
            amountPaidDerived_=std::make_shared<std::string>(r["amount_paid_derived"].as<std::string>());
        }
        if(!r["amount_waived_derived"].isNull())
        {
            amountWaivedDerived_=std::make_shared<std::string>(r["amount_waived_derived"].as<std::string>());
        }
        if(!r["amount_outstanding_derived"].isNull())
        {
            amountOutstandingDerived_=std::make_shared<std::string>(r["amount_outstanding_derived"].as<std::string>());
        }
        if(!r["is_paid_derived"].isNull())
        {
            isPaidDerived_=std::make_shared<bool>(r["is_paid_derived"].as<bool>());
        }
        if(!r["is_waived"].isNull())
        {
            isWaived_=std::make_shared<bool>(r["is_waived"].as<bool>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["inactivated_on_date"].isNull())
        {
            auto daysStr = r["inactivated_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            inactivatedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
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
        if(offset + 19 > r.size())
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
            chargeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            chargeTimeType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            feeInterval_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            amountPaidDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            amountWaivedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            amountOutstandingDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            isPaidDerived_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            isWaived_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            inactivatedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
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
        index = offset + 17;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 18;
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
const std::string &SavingsAccountCharge::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getId() const noexcept
{
    return id_;
}
void SavingsAccountCharge::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SavingsAccountCharge::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SavingsAccountCharge::PrimaryKeyType & SavingsAccountCharge::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SavingsAccountCharge::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getBusinessId() const noexcept
{
    return businessId_;
}
void SavingsAccountCharge::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void SavingsAccountCharge::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void SavingsAccountCharge::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &SavingsAccountCharge::getValueOfSavingsAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(savingsAccountId_)
        return *savingsAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getSavingsAccountId() const noexcept
{
    return savingsAccountId_;
}
void SavingsAccountCharge::setSavingsAccountId(const std::string &pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(pSavingsAccountId);
    dirtyFlag_[2] = true;
}
void SavingsAccountCharge::setSavingsAccountId(std::string &&pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(std::move(pSavingsAccountId));
    dirtyFlag_[2] = true;
}

const std::string &SavingsAccountCharge::getValueOfChargeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(chargeId_)
        return *chargeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getChargeId() const noexcept
{
    return chargeId_;
}
void SavingsAccountCharge::setChargeId(const std::string &pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(pChargeId);
    dirtyFlag_[3] = true;
}
void SavingsAccountCharge::setChargeId(std::string &&pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(std::move(pChargeId));
    dirtyFlag_[3] = true;
}

const int32_t &SavingsAccountCharge::getValueOfChargeTimeType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(chargeTimeType_)
        return *chargeTimeType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccountCharge::getChargeTimeType() const noexcept
{
    return chargeTimeType_;
}
void SavingsAccountCharge::setChargeTimeType(const int32_t &pChargeTimeType) noexcept
{
    chargeTimeType_ = std::make_shared<int32_t>(pChargeTimeType);
    dirtyFlag_[4] = true;
}

const ::trantor::Date &SavingsAccountCharge::getValueOfDueDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dueDate_)
        return *dueDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountCharge::getDueDate() const noexcept
{
    return dueDate_;
}
void SavingsAccountCharge::setDueDate(const ::trantor::Date &pDueDate) noexcept
{
    dueDate_ = std::make_shared<::trantor::Date>(pDueDate);
    dirtyFlag_[5] = true;
}
void SavingsAccountCharge::setDueDateToNull() noexcept
{
    dueDate_.reset();
    dirtyFlag_[5] = true;
}

const int32_t &SavingsAccountCharge::getValueOfFeeInterval() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(feeInterval_)
        return *feeInterval_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &SavingsAccountCharge::getFeeInterval() const noexcept
{
    return feeInterval_;
}
void SavingsAccountCharge::setFeeInterval(const int32_t &pFeeInterval) noexcept
{
    feeInterval_ = std::make_shared<int32_t>(pFeeInterval);
    dirtyFlag_[6] = true;
}
void SavingsAccountCharge::setFeeIntervalToNull() noexcept
{
    feeInterval_.reset();
    dirtyFlag_[6] = true;
}

const std::string &SavingsAccountCharge::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getAmount() const noexcept
{
    return amount_;
}
void SavingsAccountCharge::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[7] = true;
}
void SavingsAccountCharge::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[7] = true;
}

const std::string &SavingsAccountCharge::getValueOfAmountPaidDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountPaidDerived_)
        return *amountPaidDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getAmountPaidDerived() const noexcept
{
    return amountPaidDerived_;
}
void SavingsAccountCharge::setAmountPaidDerived(const std::string &pAmountPaidDerived) noexcept
{
    amountPaidDerived_ = std::make_shared<std::string>(pAmountPaidDerived);
    dirtyFlag_[8] = true;
}
void SavingsAccountCharge::setAmountPaidDerived(std::string &&pAmountPaidDerived) noexcept
{
    amountPaidDerived_ = std::make_shared<std::string>(std::move(pAmountPaidDerived));
    dirtyFlag_[8] = true;
}

const std::string &SavingsAccountCharge::getValueOfAmountWaivedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountWaivedDerived_)
        return *amountWaivedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getAmountWaivedDerived() const noexcept
{
    return amountWaivedDerived_;
}
void SavingsAccountCharge::setAmountWaivedDerived(const std::string &pAmountWaivedDerived) noexcept
{
    amountWaivedDerived_ = std::make_shared<std::string>(pAmountWaivedDerived);
    dirtyFlag_[9] = true;
}
void SavingsAccountCharge::setAmountWaivedDerived(std::string &&pAmountWaivedDerived) noexcept
{
    amountWaivedDerived_ = std::make_shared<std::string>(std::move(pAmountWaivedDerived));
    dirtyFlag_[9] = true;
}

const std::string &SavingsAccountCharge::getValueOfAmountOutstandingDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountOutstandingDerived_)
        return *amountOutstandingDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getAmountOutstandingDerived() const noexcept
{
    return amountOutstandingDerived_;
}
void SavingsAccountCharge::setAmountOutstandingDerived(const std::string &pAmountOutstandingDerived) noexcept
{
    amountOutstandingDerived_ = std::make_shared<std::string>(pAmountOutstandingDerived);
    dirtyFlag_[10] = true;
}
void SavingsAccountCharge::setAmountOutstandingDerived(std::string &&pAmountOutstandingDerived) noexcept
{
    amountOutstandingDerived_ = std::make_shared<std::string>(std::move(pAmountOutstandingDerived));
    dirtyFlag_[10] = true;
}

const bool &SavingsAccountCharge::getValueOfIsPaidDerived() const noexcept
{
    static const bool defaultValue = bool();
    if(isPaidDerived_)
        return *isPaidDerived_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccountCharge::getIsPaidDerived() const noexcept
{
    return isPaidDerived_;
}
void SavingsAccountCharge::setIsPaidDerived(const bool &pIsPaidDerived) noexcept
{
    isPaidDerived_ = std::make_shared<bool>(pIsPaidDerived);
    dirtyFlag_[11] = true;
}

const bool &SavingsAccountCharge::getValueOfIsWaived() const noexcept
{
    static const bool defaultValue = bool();
    if(isWaived_)
        return *isWaived_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccountCharge::getIsWaived() const noexcept
{
    return isWaived_;
}
void SavingsAccountCharge::setIsWaived(const bool &pIsWaived) noexcept
{
    isWaived_ = std::make_shared<bool>(pIsWaived);
    dirtyFlag_[12] = true;
}

const bool &SavingsAccountCharge::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &SavingsAccountCharge::getIsActive() const noexcept
{
    return isActive_;
}
void SavingsAccountCharge::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[13] = true;
}

const ::trantor::Date &SavingsAccountCharge::getValueOfInactivatedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(inactivatedOnDate_)
        return *inactivatedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountCharge::getInactivatedOnDate() const noexcept
{
    return inactivatedOnDate_;
}
void SavingsAccountCharge::setInactivatedOnDate(const ::trantor::Date &pInactivatedOnDate) noexcept
{
    inactivatedOnDate_ = std::make_shared<::trantor::Date>(pInactivatedOnDate);
    dirtyFlag_[14] = true;
}
void SavingsAccountCharge::setInactivatedOnDateToNull() noexcept
{
    inactivatedOnDate_.reset();
    dirtyFlag_[14] = true;
}

const std::string &SavingsAccountCharge::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getCreatedBy() const noexcept
{
    return createdBy_;
}
void SavingsAccountCharge::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[15] = true;
}
void SavingsAccountCharge::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[15] = true;
}
void SavingsAccountCharge::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[15] = true;
}

const ::trantor::Date &SavingsAccountCharge::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountCharge::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SavingsAccountCharge::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[16] = true;
}

const std::string &SavingsAccountCharge::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsAccountCharge::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void SavingsAccountCharge::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[17] = true;
}
void SavingsAccountCharge::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[17] = true;
}
void SavingsAccountCharge::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[17] = true;
}

const ::trantor::Date &SavingsAccountCharge::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SavingsAccountCharge::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void SavingsAccountCharge::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[18] = true;
}

void SavingsAccountCharge::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SavingsAccountCharge::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "savings_account_id",
        "charge_id",
        "charge_time_type",
        "due_date",
        "fee_interval",
        "amount",
        "amount_paid_derived",
        "amount_waived_derived",
        "amount_outstanding_derived",
        "is_paid_derived",
        "is_waived",
        "is_active",
        "inactivated_on_date",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void SavingsAccountCharge::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getChargeId())
        {
            binder << getValueOfChargeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getChargeTimeType())
        {
            binder << getValueOfChargeTimeType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getDueDate())
        {
            binder << getValueOfDueDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getFeeInterval())
        {
            binder << getValueOfFeeInterval();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getAmountPaidDerived())
        {
            binder << getValueOfAmountPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getAmountWaivedDerived())
        {
            binder << getValueOfAmountWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getAmountOutstandingDerived())
        {
            binder << getValueOfAmountOutstandingDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getIsPaidDerived())
        {
            binder << getValueOfIsPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getIsWaived())
        {
            binder << getValueOfIsWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getInactivatedOnDate())
        {
            binder << getValueOfInactivatedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
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

const std::vector<std::string> SavingsAccountCharge::updateColumns() const
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
    if(dirtyFlag_[18])
    {
        ret.push_back(getColumnName(18));
    }
    return ret;
}

void SavingsAccountCharge::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getChargeId())
        {
            binder << getValueOfChargeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getChargeTimeType())
        {
            binder << getValueOfChargeTimeType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getDueDate())
        {
            binder << getValueOfDueDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getFeeInterval())
        {
            binder << getValueOfFeeInterval();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getAmountPaidDerived())
        {
            binder << getValueOfAmountPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getAmountWaivedDerived())
        {
            binder << getValueOfAmountWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getAmountOutstandingDerived())
        {
            binder << getValueOfAmountOutstandingDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getIsPaidDerived())
        {
            binder << getValueOfIsPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getIsWaived())
        {
            binder << getValueOfIsWaived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getInactivatedOnDate())
        {
            binder << getValueOfInactivatedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
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
