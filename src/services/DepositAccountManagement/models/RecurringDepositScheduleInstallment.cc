/**
 *  RecurringDepositScheduleInstallment.cc
 *
 *  See RecurringDepositScheduleInstallment.h for the hand-authored-subset note.
 *
 */

#include "RecurringDepositScheduleInstallment.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string RecurringDepositScheduleInstallment::Cols::_id = "\"id\"";
const std::string RecurringDepositScheduleInstallment::Cols::_savings_account_id = "\"savings_account_id\"";
const std::string RecurringDepositScheduleInstallment::Cols::_installment_number = "\"installment_number\"";
const std::string RecurringDepositScheduleInstallment::Cols::_due_date = "\"due_date\"";
const std::string RecurringDepositScheduleInstallment::Cols::_deposit_amount = "\"deposit_amount\"";
const std::string RecurringDepositScheduleInstallment::Cols::_deposit_amount_completed_derived = "\"deposit_amount_completed_derived\"";
const std::string RecurringDepositScheduleInstallment::Cols::_is_obligation_met = "\"is_obligation_met\"";
const std::string RecurringDepositScheduleInstallment::Cols::_obligation_met_on_date = "\"obligation_met_on_date\"";
const std::string RecurringDepositScheduleInstallment::Cols::_created_at = "\"created_at\"";
const std::string RecurringDepositScheduleInstallment::primaryKeyName = "id";
const bool RecurringDepositScheduleInstallment::hasPrimaryKey = true;
const std::string RecurringDepositScheduleInstallment::tableName = "\"recurring_deposit_schedule_installment\"";

const std::vector<typename RecurringDepositScheduleInstallment::MetaData> RecurringDepositScheduleInstallment::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"savings_account_id","std::string","uuid",0,0,0,1},
{"installment_number","int32_t","integer",4,0,0,1},
{"due_date","::trantor::Date","date",0,0,0,1},
{"deposit_amount","std::string","numeric",0,0,0,1},
{"deposit_amount_completed_derived","std::string","numeric",0,0,0,1},
{"is_obligation_met","bool","boolean",1,0,0,1},
{"obligation_met_on_date","::trantor::Date","date",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &RecurringDepositScheduleInstallment::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
RecurringDepositScheduleInstallment::RecurringDepositScheduleInstallment(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["installment_number"].isNull())
        {
            installmentNumber_=std::make_shared<int32_t>(r["installment_number"].as<int32_t>());
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
        if(!r["deposit_amount"].isNull())
        {
            depositAmount_=std::make_shared<std::string>(r["deposit_amount"].as<std::string>());
        }
        if(!r["deposit_amount_completed_derived"].isNull())
        {
            depositAmountCompletedDerived_=std::make_shared<std::string>(r["deposit_amount_completed_derived"].as<std::string>());
        }
        if(!r["is_obligation_met"].isNull())
        {
            isObligationMet_=std::make_shared<bool>(r["is_obligation_met"].as<bool>());
        }
        if(!r["obligation_met_on_date"].isNull())
        {
            auto daysStr = r["obligation_met_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            obligationMetOnDate_=std::make_shared<::trantor::Date>(t*1000000);
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
            savingsAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            installmentNumber_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            depositAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            depositAmountCompletedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            isObligationMet_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            obligationMetOnDate_=std::make_shared<::trantor::Date>(t*1000000);
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
const std::string &RecurringDepositScheduleInstallment::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RecurringDepositScheduleInstallment::getId() const noexcept
{
    return id_;
}
void RecurringDepositScheduleInstallment::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void RecurringDepositScheduleInstallment::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename RecurringDepositScheduleInstallment::PrimaryKeyType & RecurringDepositScheduleInstallment::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &RecurringDepositScheduleInstallment::getValueOfSavingsAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(savingsAccountId_)
        return *savingsAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RecurringDepositScheduleInstallment::getSavingsAccountId() const noexcept
{
    return savingsAccountId_;
}
void RecurringDepositScheduleInstallment::setSavingsAccountId(const std::string &pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(pSavingsAccountId);
    dirtyFlag_[1] = true;
}
void RecurringDepositScheduleInstallment::setSavingsAccountId(std::string &&pSavingsAccountId) noexcept
{
    savingsAccountId_ = std::make_shared<std::string>(std::move(pSavingsAccountId));
    dirtyFlag_[1] = true;
}

const int32_t &RecurringDepositScheduleInstallment::getValueOfInstallmentNumber() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(installmentNumber_)
        return *installmentNumber_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RecurringDepositScheduleInstallment::getInstallmentNumber() const noexcept
{
    return installmentNumber_;
}
void RecurringDepositScheduleInstallment::setInstallmentNumber(const int32_t &pInstallmentNumber) noexcept
{
    installmentNumber_ = std::make_shared<int32_t>(pInstallmentNumber);
    dirtyFlag_[2] = true;
}

const ::trantor::Date &RecurringDepositScheduleInstallment::getValueOfDueDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dueDate_)
        return *dueDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RecurringDepositScheduleInstallment::getDueDate() const noexcept
{
    return dueDate_;
}
void RecurringDepositScheduleInstallment::setDueDate(const ::trantor::Date &pDueDate) noexcept
{
    dueDate_ = std::make_shared<::trantor::Date>(pDueDate);
    dirtyFlag_[3] = true;
}

const std::string &RecurringDepositScheduleInstallment::getValueOfDepositAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(depositAmount_)
        return *depositAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RecurringDepositScheduleInstallment::getDepositAmount() const noexcept
{
    return depositAmount_;
}
void RecurringDepositScheduleInstallment::setDepositAmount(const std::string &pDepositAmount) noexcept
{
    depositAmount_ = std::make_shared<std::string>(pDepositAmount);
    dirtyFlag_[4] = true;
}
void RecurringDepositScheduleInstallment::setDepositAmount(std::string &&pDepositAmount) noexcept
{
    depositAmount_ = std::make_shared<std::string>(std::move(pDepositAmount));
    dirtyFlag_[4] = true;
}

const std::string &RecurringDepositScheduleInstallment::getValueOfDepositAmountCompletedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(depositAmountCompletedDerived_)
        return *depositAmountCompletedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RecurringDepositScheduleInstallment::getDepositAmountCompletedDerived() const noexcept
{
    return depositAmountCompletedDerived_;
}
void RecurringDepositScheduleInstallment::setDepositAmountCompletedDerived(const std::string &pDepositAmountCompletedDerived) noexcept
{
    depositAmountCompletedDerived_ = std::make_shared<std::string>(pDepositAmountCompletedDerived);
    dirtyFlag_[5] = true;
}
void RecurringDepositScheduleInstallment::setDepositAmountCompletedDerived(std::string &&pDepositAmountCompletedDerived) noexcept
{
    depositAmountCompletedDerived_ = std::make_shared<std::string>(std::move(pDepositAmountCompletedDerived));
    dirtyFlag_[5] = true;
}

const bool &RecurringDepositScheduleInstallment::getValueOfIsObligationMet() const noexcept
{
    static const bool defaultValue = bool();
    if(isObligationMet_)
        return *isObligationMet_;
    return defaultValue;
}
const std::shared_ptr<bool> &RecurringDepositScheduleInstallment::getIsObligationMet() const noexcept
{
    return isObligationMet_;
}
void RecurringDepositScheduleInstallment::setIsObligationMet(const bool &pIsObligationMet) noexcept
{
    isObligationMet_ = std::make_shared<bool>(pIsObligationMet);
    dirtyFlag_[6] = true;
}

const ::trantor::Date &RecurringDepositScheduleInstallment::getValueOfObligationMetOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(obligationMetOnDate_)
        return *obligationMetOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RecurringDepositScheduleInstallment::getObligationMetOnDate() const noexcept
{
    return obligationMetOnDate_;
}
void RecurringDepositScheduleInstallment::setObligationMetOnDate(const ::trantor::Date &pObligationMetOnDate) noexcept
{
    obligationMetOnDate_ = std::make_shared<::trantor::Date>(pObligationMetOnDate);
    dirtyFlag_[7] = true;
}
void RecurringDepositScheduleInstallment::setObligationMetOnDateToNull() noexcept
{
    obligationMetOnDate_.reset();
    dirtyFlag_[7] = true;
}

const ::trantor::Date &RecurringDepositScheduleInstallment::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RecurringDepositScheduleInstallment::getCreatedAt() const noexcept
{
    return createdAt_;
}
void RecurringDepositScheduleInstallment::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}

void RecurringDepositScheduleInstallment::updateId(const uint64_t id)
{
}

const std::vector<std::string> &RecurringDepositScheduleInstallment::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "savings_account_id",
        "installment_number",
        "due_date",
        "deposit_amount",
        "deposit_amount_completed_derived",
        "is_obligation_met",
        "obligation_met_on_date",
        "created_at"
    };
    return inCols;
}

void RecurringDepositScheduleInstallment::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getInstallmentNumber())
        {
            binder << getValueOfInstallmentNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getDepositAmountCompletedDerived())
        {
            binder << getValueOfDepositAmountCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getIsObligationMet())
        {
            binder << getValueOfIsObligationMet();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getObligationMetOnDate())
        {
            binder << getValueOfObligationMetOnDate();
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

const std::vector<std::string> RecurringDepositScheduleInstallment::updateColumns() const
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

void RecurringDepositScheduleInstallment::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getInstallmentNumber())
        {
            binder << getValueOfInstallmentNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getDepositAmountCompletedDerived())
        {
            binder << getValueOfDepositAmountCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getIsObligationMet())
        {
            binder << getValueOfIsObligationMet();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getObligationMetOnDate())
        {
            binder << getValueOfObligationMetOnDate();
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
