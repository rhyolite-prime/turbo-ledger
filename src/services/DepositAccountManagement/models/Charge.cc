/**
 *  Charge.cc
 *
 *  See Charge.h for the hand-authored-subset note.
 *
 */

#include "Charge.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string Charge::Cols::_id = "\"id\"";
const std::string Charge::Cols::_business_id = "\"business_id\"";
const std::string Charge::Cols::_name = "\"name\"";
const std::string Charge::Cols::_currency_code = "\"currency_code\"";
const std::string Charge::Cols::_charge_applies_to = "\"charge_applies_to\"";
const std::string Charge::Cols::_charge_time_type = "\"charge_time_type\"";
const std::string Charge::Cols::_charge_calculation_type = "\"charge_calculation_type\"";
const std::string Charge::Cols::_charge_payment_mode = "\"charge_payment_mode\"";
const std::string Charge::Cols::_amount = "\"amount\"";
const std::string Charge::Cols::_fee_on_month = "\"fee_on_month\"";
const std::string Charge::Cols::_fee_on_day = "\"fee_on_day\"";
const std::string Charge::Cols::_fee_interval = "\"fee_interval\"";
const std::string Charge::Cols::_is_penalty = "\"is_penalty\"";
const std::string Charge::Cols::_is_active = "\"is_active\"";
const std::string Charge::Cols::_is_free_withdrawal = "\"is_free_withdrawal\"";
const std::string Charge::Cols::_free_withdrawal_charge_frequency = "\"free_withdrawal_charge_frequency\"";
const std::string Charge::Cols::_min_cap = "\"min_cap\"";
const std::string Charge::Cols::_max_cap = "\"max_cap\"";
const std::string Charge::Cols::_created_by = "\"created_by\"";
const std::string Charge::Cols::_created_at = "\"created_at\"";
const std::string Charge::Cols::_updated_by = "\"updated_by\"";
const std::string Charge::Cols::_updated_at = "\"updated_at\"";
const std::string Charge::primaryKeyName = "id";
const bool Charge::hasPrimaryKey = true;
const std::string Charge::tableName = "\"charge\"";

const std::vector<typename Charge::MetaData> Charge::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"name","std::string","character varying",100,0,0,1},
{"currency_code","std::string","character varying",3,0,0,1},
{"charge_applies_to","int32_t","integer",4,0,0,1},
{"charge_time_type","int32_t","integer",4,0,0,1},
{"charge_calculation_type","int32_t","integer",4,0,0,1},
{"charge_payment_mode","int32_t","integer",4,0,0,0},
{"amount","std::string","numeric",0,0,0,1},
{"fee_on_month","int32_t","integer",4,0,0,0},
{"fee_on_day","int32_t","integer",4,0,0,0},
{"fee_interval","int32_t","integer",4,0,0,0},
{"is_penalty","bool","boolean",1,0,0,1},
{"is_active","bool","boolean",1,0,0,1},
{"is_free_withdrawal","bool","boolean",1,0,0,1},
{"free_withdrawal_charge_frequency","int32_t","integer",4,0,0,0},
{"min_cap","std::string","numeric",0,0,0,0},
{"max_cap","std::string","numeric",0,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Charge::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Charge::Charge(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["charge_applies_to"].isNull())
        {
            chargeAppliesTo_=std::make_shared<int32_t>(r["charge_applies_to"].as<int32_t>());
        }
        if(!r["charge_time_type"].isNull())
        {
            chargeTimeType_=std::make_shared<int32_t>(r["charge_time_type"].as<int32_t>());
        }
        if(!r["charge_calculation_type"].isNull())
        {
            chargeCalculationType_=std::make_shared<int32_t>(r["charge_calculation_type"].as<int32_t>());
        }
        if(!r["charge_payment_mode"].isNull())
        {
            chargePaymentMode_=std::make_shared<int32_t>(r["charge_payment_mode"].as<int32_t>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["fee_on_month"].isNull())
        {
            feeOnMonth_=std::make_shared<int32_t>(r["fee_on_month"].as<int32_t>());
        }
        if(!r["fee_on_day"].isNull())
        {
            feeOnDay_=std::make_shared<int32_t>(r["fee_on_day"].as<int32_t>());
        }
        if(!r["fee_interval"].isNull())
        {
            feeInterval_=std::make_shared<int32_t>(r["fee_interval"].as<int32_t>());
        }
        if(!r["is_penalty"].isNull())
        {
            isPenalty_=std::make_shared<bool>(r["is_penalty"].as<bool>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["is_free_withdrawal"].isNull())
        {
            isFreeWithdrawal_=std::make_shared<bool>(r["is_free_withdrawal"].as<bool>());
        }
        if(!r["free_withdrawal_charge_frequency"].isNull())
        {
            freeWithdrawalChargeFrequency_=std::make_shared<int32_t>(r["free_withdrawal_charge_frequency"].as<int32_t>());
        }
        if(!r["min_cap"].isNull())
        {
            minCap_=std::make_shared<std::string>(r["min_cap"].as<std::string>());
        }
        if(!r["max_cap"].isNull())
        {
            maxCap_=std::make_shared<std::string>(r["max_cap"].as<std::string>());
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
        if(offset + 22 > r.size())
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
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            chargeAppliesTo_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            chargeTimeType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            chargeCalculationType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            chargePaymentMode_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            feeOnMonth_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            feeOnDay_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            feeInterval_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            isPenalty_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            isFreeWithdrawal_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            freeWithdrawalChargeFrequency_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            minCap_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            maxCap_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 19;
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
        index = offset + 20;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 21;
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
const std::string &Charge::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getId() const noexcept
{
    return id_;
}
void Charge::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Charge::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Charge::PrimaryKeyType & Charge::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Charge::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getBusinessId() const noexcept
{
    return businessId_;
}
void Charge::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void Charge::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void Charge::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &Charge::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getName() const noexcept
{
    return name_;
}
void Charge::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[2] = true;
}
void Charge::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[2] = true;
}

const std::string &Charge::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void Charge::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[3] = true;
}
void Charge::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[3] = true;
}

const int32_t &Charge::getValueOfChargeAppliesTo() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(chargeAppliesTo_)
        return *chargeAppliesTo_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getChargeAppliesTo() const noexcept
{
    return chargeAppliesTo_;
}
void Charge::setChargeAppliesTo(const int32_t &pChargeAppliesTo) noexcept
{
    chargeAppliesTo_ = std::make_shared<int32_t>(pChargeAppliesTo);
    dirtyFlag_[4] = true;
}

const int32_t &Charge::getValueOfChargeTimeType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(chargeTimeType_)
        return *chargeTimeType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getChargeTimeType() const noexcept
{
    return chargeTimeType_;
}
void Charge::setChargeTimeType(const int32_t &pChargeTimeType) noexcept
{
    chargeTimeType_ = std::make_shared<int32_t>(pChargeTimeType);
    dirtyFlag_[5] = true;
}

const int32_t &Charge::getValueOfChargeCalculationType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(chargeCalculationType_)
        return *chargeCalculationType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getChargeCalculationType() const noexcept
{
    return chargeCalculationType_;
}
void Charge::setChargeCalculationType(const int32_t &pChargeCalculationType) noexcept
{
    chargeCalculationType_ = std::make_shared<int32_t>(pChargeCalculationType);
    dirtyFlag_[6] = true;
}

const int32_t &Charge::getValueOfChargePaymentMode() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(chargePaymentMode_)
        return *chargePaymentMode_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getChargePaymentMode() const noexcept
{
    return chargePaymentMode_;
}
void Charge::setChargePaymentMode(const int32_t &pChargePaymentMode) noexcept
{
    chargePaymentMode_ = std::make_shared<int32_t>(pChargePaymentMode);
    dirtyFlag_[7] = true;
}
void Charge::setChargePaymentModeToNull() noexcept
{
    chargePaymentMode_.reset();
    dirtyFlag_[7] = true;
}

const std::string &Charge::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getAmount() const noexcept
{
    return amount_;
}
void Charge::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[8] = true;
}
void Charge::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[8] = true;
}

const int32_t &Charge::getValueOfFeeOnMonth() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(feeOnMonth_)
        return *feeOnMonth_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getFeeOnMonth() const noexcept
{
    return feeOnMonth_;
}
void Charge::setFeeOnMonth(const int32_t &pFeeOnMonth) noexcept
{
    feeOnMonth_ = std::make_shared<int32_t>(pFeeOnMonth);
    dirtyFlag_[9] = true;
}
void Charge::setFeeOnMonthToNull() noexcept
{
    feeOnMonth_.reset();
    dirtyFlag_[9] = true;
}

const int32_t &Charge::getValueOfFeeOnDay() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(feeOnDay_)
        return *feeOnDay_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getFeeOnDay() const noexcept
{
    return feeOnDay_;
}
void Charge::setFeeOnDay(const int32_t &pFeeOnDay) noexcept
{
    feeOnDay_ = std::make_shared<int32_t>(pFeeOnDay);
    dirtyFlag_[10] = true;
}
void Charge::setFeeOnDayToNull() noexcept
{
    feeOnDay_.reset();
    dirtyFlag_[10] = true;
}

const int32_t &Charge::getValueOfFeeInterval() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(feeInterval_)
        return *feeInterval_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getFeeInterval() const noexcept
{
    return feeInterval_;
}
void Charge::setFeeInterval(const int32_t &pFeeInterval) noexcept
{
    feeInterval_ = std::make_shared<int32_t>(pFeeInterval);
    dirtyFlag_[11] = true;
}
void Charge::setFeeIntervalToNull() noexcept
{
    feeInterval_.reset();
    dirtyFlag_[11] = true;
}

const bool &Charge::getValueOfIsPenalty() const noexcept
{
    static const bool defaultValue = bool();
    if(isPenalty_)
        return *isPenalty_;
    return defaultValue;
}
const std::shared_ptr<bool> &Charge::getIsPenalty() const noexcept
{
    return isPenalty_;
}
void Charge::setIsPenalty(const bool &pIsPenalty) noexcept
{
    isPenalty_ = std::make_shared<bool>(pIsPenalty);
    dirtyFlag_[12] = true;
}

const bool &Charge::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &Charge::getIsActive() const noexcept
{
    return isActive_;
}
void Charge::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[13] = true;
}

const bool &Charge::getValueOfIsFreeWithdrawal() const noexcept
{
    static const bool defaultValue = bool();
    if(isFreeWithdrawal_)
        return *isFreeWithdrawal_;
    return defaultValue;
}
const std::shared_ptr<bool> &Charge::getIsFreeWithdrawal() const noexcept
{
    return isFreeWithdrawal_;
}
void Charge::setIsFreeWithdrawal(const bool &pIsFreeWithdrawal) noexcept
{
    isFreeWithdrawal_ = std::make_shared<bool>(pIsFreeWithdrawal);
    dirtyFlag_[14] = true;
}

const int32_t &Charge::getValueOfFreeWithdrawalChargeFrequency() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(freeWithdrawalChargeFrequency_)
        return *freeWithdrawalChargeFrequency_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Charge::getFreeWithdrawalChargeFrequency() const noexcept
{
    return freeWithdrawalChargeFrequency_;
}
void Charge::setFreeWithdrawalChargeFrequency(const int32_t &pFreeWithdrawalChargeFrequency) noexcept
{
    freeWithdrawalChargeFrequency_ = std::make_shared<int32_t>(pFreeWithdrawalChargeFrequency);
    dirtyFlag_[15] = true;
}
void Charge::setFreeWithdrawalChargeFrequencyToNull() noexcept
{
    freeWithdrawalChargeFrequency_.reset();
    dirtyFlag_[15] = true;
}

const std::string &Charge::getValueOfMinCap() const noexcept
{
    static const std::string defaultValue = std::string();
    if(minCap_)
        return *minCap_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getMinCap() const noexcept
{
    return minCap_;
}
void Charge::setMinCap(const std::string &pMinCap) noexcept
{
    minCap_ = std::make_shared<std::string>(pMinCap);
    dirtyFlag_[16] = true;
}
void Charge::setMinCap(std::string &&pMinCap) noexcept
{
    minCap_ = std::make_shared<std::string>(std::move(pMinCap));
    dirtyFlag_[16] = true;
}
void Charge::setMinCapToNull() noexcept
{
    minCap_.reset();
    dirtyFlag_[16] = true;
}

const std::string &Charge::getValueOfMaxCap() const noexcept
{
    static const std::string defaultValue = std::string();
    if(maxCap_)
        return *maxCap_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getMaxCap() const noexcept
{
    return maxCap_;
}
void Charge::setMaxCap(const std::string &pMaxCap) noexcept
{
    maxCap_ = std::make_shared<std::string>(pMaxCap);
    dirtyFlag_[17] = true;
}
void Charge::setMaxCap(std::string &&pMaxCap) noexcept
{
    maxCap_ = std::make_shared<std::string>(std::move(pMaxCap));
    dirtyFlag_[17] = true;
}
void Charge::setMaxCapToNull() noexcept
{
    maxCap_.reset();
    dirtyFlag_[17] = true;
}

const std::string &Charge::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getCreatedBy() const noexcept
{
    return createdBy_;
}
void Charge::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[18] = true;
}
void Charge::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[18] = true;
}
void Charge::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[18] = true;
}

const ::trantor::Date &Charge::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Charge::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Charge::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[19] = true;
}

const std::string &Charge::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Charge::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void Charge::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[20] = true;
}
void Charge::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[20] = true;
}
void Charge::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[20] = true;
}

const ::trantor::Date &Charge::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Charge::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void Charge::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[21] = true;
}

void Charge::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Charge::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "name",
        "currency_code",
        "charge_applies_to",
        "charge_time_type",
        "charge_calculation_type",
        "charge_payment_mode",
        "amount",
        "fee_on_month",
        "fee_on_day",
        "fee_interval",
        "is_penalty",
        "is_active",
        "is_free_withdrawal",
        "free_withdrawal_charge_frequency",
        "min_cap",
        "max_cap",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void Charge::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getChargeAppliesTo())
        {
            binder << getValueOfChargeAppliesTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getChargeCalculationType())
        {
            binder << getValueOfChargeCalculationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getChargePaymentMode())
        {
            binder << getValueOfChargePaymentMode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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
    if(dirtyFlag_[9])
    {
        if(getFeeOnMonth())
        {
            binder << getValueOfFeeOnMonth();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getFeeOnDay())
        {
            binder << getValueOfFeeOnDay();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
    {
        if(getIsPenalty())
        {
            binder << getValueOfIsPenalty();
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
        if(getIsFreeWithdrawal())
        {
            binder << getValueOfIsFreeWithdrawal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getFreeWithdrawalChargeFrequency())
        {
            binder << getValueOfFreeWithdrawalChargeFrequency();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getMinCap())
        {
            binder << getValueOfMinCap();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getMaxCap())
        {
            binder << getValueOfMaxCap();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
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
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
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

const std::vector<std::string> Charge::updateColumns() const
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
    if(dirtyFlag_[19])
    {
        ret.push_back(getColumnName(19));
    }
    if(dirtyFlag_[20])
    {
        ret.push_back(getColumnName(20));
    }
    if(dirtyFlag_[21])
    {
        ret.push_back(getColumnName(21));
    }
    return ret;
}

void Charge::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getChargeAppliesTo())
        {
            binder << getValueOfChargeAppliesTo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getChargeCalculationType())
        {
            binder << getValueOfChargeCalculationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getChargePaymentMode())
        {
            binder << getValueOfChargePaymentMode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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
    if(dirtyFlag_[9])
    {
        if(getFeeOnMonth())
        {
            binder << getValueOfFeeOnMonth();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getFeeOnDay())
        {
            binder << getValueOfFeeOnDay();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
    {
        if(getIsPenalty())
        {
            binder << getValueOfIsPenalty();
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
        if(getIsFreeWithdrawal())
        {
            binder << getValueOfIsFreeWithdrawal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getFreeWithdrawalChargeFrequency())
        {
            binder << getValueOfFreeWithdrawalChargeFrequency();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getMinCap())
        {
            binder << getValueOfMinCap();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getMaxCap())
        {
            binder << getValueOfMaxCap();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
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
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
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
