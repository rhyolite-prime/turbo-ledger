/**
 *  DepositAccountTermAndPreclosure.cc
 *
 *  See DepositAccountTermAndPreclosure.h for the hand-authored-subset note.
 *
 */

#include "DepositAccountTermAndPreclosure.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string DepositAccountTermAndPreclosure::Cols::_id = "\"id\"";
const std::string DepositAccountTermAndPreclosure::Cols::_savings_account_id = "\"savings_account_id\"";
const std::string DepositAccountTermAndPreclosure::Cols::_deposit_amount = "\"deposit_amount\"";
const std::string DepositAccountTermAndPreclosure::Cols::_deposit_period = "\"deposit_period\"";
const std::string DepositAccountTermAndPreclosure::Cols::_deposit_period_frequency_type = "\"deposit_period_frequency_type\"";
const std::string DepositAccountTermAndPreclosure::Cols::_maturity_amount = "\"maturity_amount\"";
const std::string DepositAccountTermAndPreclosure::Cols::_maturity_date = "\"maturity_date\"";
const std::string DepositAccountTermAndPreclosure::Cols::_expected_firstdeposit_on_date = "\"expected_firstdeposit_on_date\"";
const std::string DepositAccountTermAndPreclosure::Cols::_is_renewal_allowed = "\"is_renewal_allowed\"";
const std::string DepositAccountTermAndPreclosure::Cols::_is_premature_closure_allowed = "\"is_premature_closure_allowed\"";
const std::string DepositAccountTermAndPreclosure::Cols::_pre_closure_penal_applicable = "\"pre_closure_penal_applicable\"";
const std::string DepositAccountTermAndPreclosure::Cols::_pre_closure_penal_interest = "\"pre_closure_penal_interest\"";
const std::string DepositAccountTermAndPreclosure::Cols::_pre_closure_penal_interest_on_type = "\"pre_closure_penal_interest_on_type\"";
const std::string DepositAccountTermAndPreclosure::Cols::_on_account_closure_type = "\"on_account_closure_type\"";
const std::string DepositAccountTermAndPreclosure::Cols::_transfer_to_savings_account_id = "\"transfer_to_savings_account_id\"";
const std::string DepositAccountTermAndPreclosure::Cols::_created_by = "\"created_by\"";
const std::string DepositAccountTermAndPreclosure::Cols::_created_at = "\"created_at\"";
const std::string DepositAccountTermAndPreclosure::Cols::_updated_by = "\"updated_by\"";
const std::string DepositAccountTermAndPreclosure::Cols::_updated_at = "\"updated_at\"";
const std::string DepositAccountTermAndPreclosure::primaryKeyName = "id";
const bool DepositAccountTermAndPreclosure::hasPrimaryKey = true;
const std::string DepositAccountTermAndPreclosure::tableName = "\"deposit_account_term_and_preclosure\"";

const std::vector<typename DepositAccountTermAndPreclosure::MetaData> DepositAccountTermAndPreclosure::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"savings_account_id","std::string","uuid",0,0,0,1},
{"deposit_amount","std::string","numeric",0,0,0,0},
{"deposit_period","int32_t","integer",4,0,0,0},
{"deposit_period_frequency_type","int32_t","integer",4,0,0,0},
{"maturity_amount","std::string","numeric",0,0,0,0},
{"maturity_date","::trantor::Date","date",0,0,0,0},
{"expected_firstdeposit_on_date","::trantor::Date","date",0,0,0,0},
{"is_renewal_allowed","bool","boolean",1,0,0,1},
{"is_premature_closure_allowed","bool","boolean",1,0,0,1},
{"pre_closure_penal_applicable","bool","boolean",1,0,0,1},
{"pre_closure_penal_interest","std::string","numeric",0,0,0,0},
{"pre_closure_penal_interest_on_type","int32_t","integer",4,0,0,0},
{"on_account_closure_type","int32_t","integer",4,0,0,0},
{"transfer_to_savings_account_id","std::string","uuid",0,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &DepositAccountTermAndPreclosure::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
DepositAccountTermAndPreclosure::DepositAccountTermAndPreclosure(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["savings_account_id"].isNull())
        {
            savingsAccountId_=std::make_shared<std::string>(r["savings_account_id"].as<std::string>());
        }
        if(!r["deposit_amount"].isNull())
        {
            depositAmount_=std::make_shared<std::string>(r["deposit_amount"].as<std::string>());
        }
        if(!r["deposit_period"].isNull())
        {
            depositPeriod_=std::make_shared<int32_t>(r["deposit_period"].as<int32_t>());
        }
        if(!r["deposit_period_frequency_type"].isNull())
        {
            depositPeriodFrequencyType_=std::make_shared<int32_t>(r["deposit_period_frequency_type"].as<int32_t>());
        }
        if(!r["maturity_amount"].isNull())
        {
            maturityAmount_=std::make_shared<std::string>(r["maturity_amount"].as<std::string>());
        }
        if(!r["maturity_date"].isNull())
        {
            auto daysStr = r["maturity_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            maturityDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["expected_firstdeposit_on_date"].isNull())
        {
            auto daysStr = r["expected_firstdeposit_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedFirstdepositOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["is_renewal_allowed"].isNull())
        {
            isRenewalAllowed_=std::make_shared<bool>(r["is_renewal_allowed"].as<bool>());
        }
        if(!r["is_premature_closure_allowed"].isNull())
        {
            isPrematureClosureAllowed_=std::make_shared<bool>(r["is_premature_closure_allowed"].as<bool>());
        }
        if(!r["pre_closure_penal_applicable"].isNull())
        {
            preClosurePenalApplicable_=std::make_shared<bool>(r["pre_closure_penal_applicable"].as<bool>());
        }
        if(!r["pre_closure_penal_interest"].isNull())
        {
            preClosurePenalInterest_=std::make_shared<std::string>(r["pre_closure_penal_interest"].as<std::string>());
        }
        if(!r["pre_closure_penal_interest_on_type"].isNull())
        {
            preClosurePenalInterestOnType_=std::make_shared<int32_t>(r["pre_closure_penal_interest_on_type"].as<int32_t>());
        }
        if(!r["on_account_closure_type"].isNull())
        {
            onAccountClosureType_=std::make_shared<int32_t>(r["on_account_closure_type"].as<int32_t>());
        }
        if(!r["transfer_to_savings_account_id"].isNull())
        {
            transferToSavingsAccountId_=std::make_shared<std::string>(r["transfer_to_savings_account_id"].as<std::string>());
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
            savingsAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            depositAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            depositPeriod_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            depositPeriodFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            maturityAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            maturityDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedFirstdepositOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            isRenewalAllowed_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            isPrematureClosureAllowed_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            preClosurePenalApplicable_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            preClosurePenalInterest_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            preClosurePenalInterestOnType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            onAccountClosureType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            transferToSavingsAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &DepositAccountTermAndPreclosure::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getId() const noexcept
{
    return id_;
}
void DepositAccountTermAndPreclosure::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void DepositAccountTermAndPreclosure::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename DepositAccountTermAndPreclosure::PrimaryKeyType & DepositAccountTermAndPreclosure::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &DepositAccountTermAndPreclosure::getValueOfSavingsAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(savingsAccountId_)
        return *savingsAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getSavingsAccountId() const noexcept
{
    return savingsAccountId_;
}
void DepositAccountTermAndPreclosure::setSavingsAccountId(const std::string &pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(pSavingsAccountId);
    dirtyFlag_[1] = true;
}
void DepositAccountTermAndPreclosure::setSavingsAccountId(std::string &&pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(std::move(pSavingsAccountId));
    dirtyFlag_[1] = true;
}

const std::string &DepositAccountTermAndPreclosure::getValueOfDepositAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(depositAmount_)
        return *depositAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getDepositAmount() const noexcept
{
    return depositAmount_;
}
void DepositAccountTermAndPreclosure::setDepositAmount(const std::string &pDepositAmount) noexcept
{
    depositAmount_ = std::make_shared<std::string>(pDepositAmount);
    dirtyFlag_[2] = true;
}
void DepositAccountTermAndPreclosure::setDepositAmount(std::string &&pDepositAmount) noexcept
{
    depositAmount_ = std::make_shared<std::string>(std::move(pDepositAmount));
    dirtyFlag_[2] = true;
}
void DepositAccountTermAndPreclosure::setDepositAmountToNull() noexcept
{
    depositAmount_.reset();
    dirtyFlag_[2] = true;
}

const int32_t &DepositAccountTermAndPreclosure::getValueOfDepositPeriod() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(depositPeriod_)
        return *depositPeriod_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &DepositAccountTermAndPreclosure::getDepositPeriod() const noexcept
{
    return depositPeriod_;
}
void DepositAccountTermAndPreclosure::setDepositPeriod(const int32_t &pDepositPeriod) noexcept
{
    depositPeriod_ = std::make_shared<int32_t>(pDepositPeriod);
    dirtyFlag_[3] = true;
}
void DepositAccountTermAndPreclosure::setDepositPeriodToNull() noexcept
{
    depositPeriod_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &DepositAccountTermAndPreclosure::getValueOfDepositPeriodFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(depositPeriodFrequencyType_)
        return *depositPeriodFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &DepositAccountTermAndPreclosure::getDepositPeriodFrequencyType() const noexcept
{
    return depositPeriodFrequencyType_;
}
void DepositAccountTermAndPreclosure::setDepositPeriodFrequencyType(const int32_t &pDepositPeriodFrequencyType) noexcept
{
    depositPeriodFrequencyType_ = std::make_shared<int32_t>(pDepositPeriodFrequencyType);
    dirtyFlag_[4] = true;
}
void DepositAccountTermAndPreclosure::setDepositPeriodFrequencyTypeToNull() noexcept
{
    depositPeriodFrequencyType_.reset();
    dirtyFlag_[4] = true;
}

const std::string &DepositAccountTermAndPreclosure::getValueOfMaturityAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(maturityAmount_)
        return *maturityAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getMaturityAmount() const noexcept
{
    return maturityAmount_;
}
void DepositAccountTermAndPreclosure::setMaturityAmount(const std::string &pMaturityAmount) noexcept
{
    maturityAmount_ = std::make_shared<std::string>(pMaturityAmount);
    dirtyFlag_[5] = true;
}
void DepositAccountTermAndPreclosure::setMaturityAmount(std::string &&pMaturityAmount) noexcept
{
    maturityAmount_ = std::make_shared<std::string>(std::move(pMaturityAmount));
    dirtyFlag_[5] = true;
}
void DepositAccountTermAndPreclosure::setMaturityAmountToNull() noexcept
{
    maturityAmount_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &DepositAccountTermAndPreclosure::getValueOfMaturityDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(maturityDate_)
        return *maturityDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &DepositAccountTermAndPreclosure::getMaturityDate() const noexcept
{
    return maturityDate_;
}
void DepositAccountTermAndPreclosure::setMaturityDate(const ::trantor::Date &pMaturityDate) noexcept
{
    maturityDate_ = std::make_shared<::trantor::Date>(pMaturityDate);
    dirtyFlag_[6] = true;
}
void DepositAccountTermAndPreclosure::setMaturityDateToNull() noexcept
{
    maturityDate_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &DepositAccountTermAndPreclosure::getValueOfExpectedFirstdepositOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(expectedFirstdepositOnDate_)
        return *expectedFirstdepositOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &DepositAccountTermAndPreclosure::getExpectedFirstdepositOnDate() const noexcept
{
    return expectedFirstdepositOnDate_;
}
void DepositAccountTermAndPreclosure::setExpectedFirstdepositOnDate(const ::trantor::Date &pExpectedFirstdepositOnDate) noexcept
{
    expectedFirstdepositOnDate_ = std::make_shared<::trantor::Date>(pExpectedFirstdepositOnDate);
    dirtyFlag_[7] = true;
}
void DepositAccountTermAndPreclosure::setExpectedFirstdepositOnDateToNull() noexcept
{
    expectedFirstdepositOnDate_.reset();
    dirtyFlag_[7] = true;
}

const bool &DepositAccountTermAndPreclosure::getValueOfIsRenewalAllowed() const noexcept
{
    static const bool defaultValue = bool();
    if(isRenewalAllowed_)
        return *isRenewalAllowed_;
    return defaultValue;
}
const std::shared_ptr<bool> &DepositAccountTermAndPreclosure::getIsRenewalAllowed() const noexcept
{
    return isRenewalAllowed_;
}
void DepositAccountTermAndPreclosure::setIsRenewalAllowed(const bool &pIsRenewalAllowed) noexcept
{
    isRenewalAllowed_ = std::make_shared<bool>(pIsRenewalAllowed);
    dirtyFlag_[8] = true;
}

const bool &DepositAccountTermAndPreclosure::getValueOfIsPrematureClosureAllowed() const noexcept
{
    static const bool defaultValue = bool();
    if(isPrematureClosureAllowed_)
        return *isPrematureClosureAllowed_;
    return defaultValue;
}
const std::shared_ptr<bool> &DepositAccountTermAndPreclosure::getIsPrematureClosureAllowed() const noexcept
{
    return isPrematureClosureAllowed_;
}
void DepositAccountTermAndPreclosure::setIsPrematureClosureAllowed(const bool &pIsPrematureClosureAllowed) noexcept
{
    isPrematureClosureAllowed_ = std::make_shared<bool>(pIsPrematureClosureAllowed);
    dirtyFlag_[9] = true;
}

const bool &DepositAccountTermAndPreclosure::getValueOfPreClosurePenalApplicable() const noexcept
{
    static const bool defaultValue = bool();
    if(preClosurePenalApplicable_)
        return *preClosurePenalApplicable_;
    return defaultValue;
}
const std::shared_ptr<bool> &DepositAccountTermAndPreclosure::getPreClosurePenalApplicable() const noexcept
{
    return preClosurePenalApplicable_;
}
void DepositAccountTermAndPreclosure::setPreClosurePenalApplicable(const bool &pPreClosurePenalApplicable) noexcept
{
    preClosurePenalApplicable_ = std::make_shared<bool>(pPreClosurePenalApplicable);
    dirtyFlag_[10] = true;
}

const std::string &DepositAccountTermAndPreclosure::getValueOfPreClosurePenalInterest() const noexcept
{
    static const std::string defaultValue = std::string();
    if(preClosurePenalInterest_)
        return *preClosurePenalInterest_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getPreClosurePenalInterest() const noexcept
{
    return preClosurePenalInterest_;
}
void DepositAccountTermAndPreclosure::setPreClosurePenalInterest(const std::string &pPreClosurePenalInterest) noexcept
{
    preClosurePenalInterest_ = std::make_shared<std::string>(pPreClosurePenalInterest);
    dirtyFlag_[11] = true;
}
void DepositAccountTermAndPreclosure::setPreClosurePenalInterest(std::string &&pPreClosurePenalInterest) noexcept
{
    preClosurePenalInterest_ = std::make_shared<std::string>(std::move(pPreClosurePenalInterest));
    dirtyFlag_[11] = true;
}
void DepositAccountTermAndPreclosure::setPreClosurePenalInterestToNull() noexcept
{
    preClosurePenalInterest_.reset();
    dirtyFlag_[11] = true;
}

const int32_t &DepositAccountTermAndPreclosure::getValueOfPreClosurePenalInterestOnType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(preClosurePenalInterestOnType_)
        return *preClosurePenalInterestOnType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &DepositAccountTermAndPreclosure::getPreClosurePenalInterestOnType() const noexcept
{
    return preClosurePenalInterestOnType_;
}
void DepositAccountTermAndPreclosure::setPreClosurePenalInterestOnType(const int32_t &pPreClosurePenalInterestOnType) noexcept
{
    preClosurePenalInterestOnType_ = std::make_shared<int32_t>(pPreClosurePenalInterestOnType);
    dirtyFlag_[12] = true;
}
void DepositAccountTermAndPreclosure::setPreClosurePenalInterestOnTypeToNull() noexcept
{
    preClosurePenalInterestOnType_.reset();
    dirtyFlag_[12] = true;
}

const int32_t &DepositAccountTermAndPreclosure::getValueOfOnAccountClosureType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(onAccountClosureType_)
        return *onAccountClosureType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &DepositAccountTermAndPreclosure::getOnAccountClosureType() const noexcept
{
    return onAccountClosureType_;
}
void DepositAccountTermAndPreclosure::setOnAccountClosureType(const int32_t &pOnAccountClosureType) noexcept
{
    onAccountClosureType_ = std::make_shared<int32_t>(pOnAccountClosureType);
    dirtyFlag_[13] = true;
}
void DepositAccountTermAndPreclosure::setOnAccountClosureTypeToNull() noexcept
{
    onAccountClosureType_.reset();
    dirtyFlag_[13] = true;
}

const std::string &DepositAccountTermAndPreclosure::getValueOfTransferToSavingsAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transferToSavingsAccountId_)
        return *transferToSavingsAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getTransferToSavingsAccountId() const noexcept
{
    return transferToSavingsAccountId_;
}
void DepositAccountTermAndPreclosure::setTransferToSavingsAccountId(const std::string &pTransferToSavingsAccountId) noexcept
{
    transferToSavingsAccountId_ = std::make_shared<std::string>(pTransferToSavingsAccountId);
    dirtyFlag_[14] = true;
}
void DepositAccountTermAndPreclosure::setTransferToSavingsAccountId(std::string &&pTransferToSavingsAccountId) noexcept
{
    transferToSavingsAccountId_ = std::make_shared<std::string>(std::move(pTransferToSavingsAccountId));
    dirtyFlag_[14] = true;
}
void DepositAccountTermAndPreclosure::setTransferToSavingsAccountIdToNull() noexcept
{
    transferToSavingsAccountId_.reset();
    dirtyFlag_[14] = true;
}

const std::string &DepositAccountTermAndPreclosure::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getCreatedBy() const noexcept
{
    return createdBy_;
}
void DepositAccountTermAndPreclosure::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[15] = true;
}
void DepositAccountTermAndPreclosure::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[15] = true;
}
void DepositAccountTermAndPreclosure::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[15] = true;
}

const ::trantor::Date &DepositAccountTermAndPreclosure::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &DepositAccountTermAndPreclosure::getCreatedAt() const noexcept
{
    return createdAt_;
}
void DepositAccountTermAndPreclosure::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[16] = true;
}

const std::string &DepositAccountTermAndPreclosure::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DepositAccountTermAndPreclosure::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void DepositAccountTermAndPreclosure::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[17] = true;
}
void DepositAccountTermAndPreclosure::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[17] = true;
}
void DepositAccountTermAndPreclosure::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[17] = true;
}

const ::trantor::Date &DepositAccountTermAndPreclosure::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &DepositAccountTermAndPreclosure::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void DepositAccountTermAndPreclosure::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[18] = true;
}

void DepositAccountTermAndPreclosure::updateId(const uint64_t id)
{
}

const std::vector<std::string> &DepositAccountTermAndPreclosure::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "savings_account_id",
        "deposit_amount",
        "deposit_period",
        "deposit_period_frequency_type",
        "maturity_amount",
        "maturity_date",
        "expected_firstdeposit_on_date",
        "is_renewal_allowed",
        "is_premature_closure_allowed",
        "pre_closure_penal_applicable",
        "pre_closure_penal_interest",
        "pre_closure_penal_interest_on_type",
        "on_account_closure_type",
        "transfer_to_savings_account_id",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void DepositAccountTermAndPreclosure::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSavingsAccountId())
        {
            binder << getValueOfSavingsAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDepositAmount())
        {
            binder << getValueOfDepositAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDepositPeriod())
        {
            binder << getValueOfDepositPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDepositPeriodFrequencyType())
        {
            binder << getValueOfDepositPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getMaturityAmount())
        {
            binder << getValueOfMaturityAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getMaturityDate())
        {
            binder << getValueOfMaturityDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getExpectedFirstdepositOnDate())
        {
            binder << getValueOfExpectedFirstdepositOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsRenewalAllowed())
        {
            binder << getValueOfIsRenewalAllowed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getIsPrematureClosureAllowed())
        {
            binder << getValueOfIsPrematureClosureAllowed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getPreClosurePenalApplicable())
        {
            binder << getValueOfPreClosurePenalApplicable();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getPreClosurePenalInterest())
        {
            binder << getValueOfPreClosurePenalInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getPreClosurePenalInterestOnType())
        {
            binder << getValueOfPreClosurePenalInterestOnType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getOnAccountClosureType())
        {
            binder << getValueOfOnAccountClosureType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getTransferToSavingsAccountId())
        {
            binder << getValueOfTransferToSavingsAccountId();
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

const std::vector<std::string> DepositAccountTermAndPreclosure::updateColumns() const
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

void DepositAccountTermAndPreclosure::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSavingsAccountId())
        {
            binder << getValueOfSavingsAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDepositAmount())
        {
            binder << getValueOfDepositAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDepositPeriod())
        {
            binder << getValueOfDepositPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDepositPeriodFrequencyType())
        {
            binder << getValueOfDepositPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getMaturityAmount())
        {
            binder << getValueOfMaturityAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getMaturityDate())
        {
            binder << getValueOfMaturityDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getExpectedFirstdepositOnDate())
        {
            binder << getValueOfExpectedFirstdepositOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsRenewalAllowed())
        {
            binder << getValueOfIsRenewalAllowed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getIsPrematureClosureAllowed())
        {
            binder << getValueOfIsPrematureClosureAllowed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getPreClosurePenalApplicable())
        {
            binder << getValueOfPreClosurePenalApplicable();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getPreClosurePenalInterest())
        {
            binder << getValueOfPreClosurePenalInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getPreClosurePenalInterestOnType())
        {
            binder << getValueOfPreClosurePenalInterestOnType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getOnAccountClosureType())
        {
            binder << getValueOfOnAccountClosureType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getTransferToSavingsAccountId())
        {
            binder << getValueOfTransferToSavingsAccountId();
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
