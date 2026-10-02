/**
 *  LoanCharge.cc
 *
 *  See LoanCharge.h for the hand-authored-subset note.
 *
 */

#include "LoanCharge.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanCharge::Cols::_id = "\"id\"";
const std::string LoanCharge::Cols::_loan_id = "\"loan_id\"";
const std::string LoanCharge::Cols::_charge_id = "\"charge_id\"";
const std::string LoanCharge::Cols::_is_penalty = "\"is_penalty\"";
const std::string LoanCharge::Cols::_charge_time_type = "\"charge_time_type\"";
const std::string LoanCharge::Cols::_charge_calculation_type = "\"charge_calculation_type\"";
const std::string LoanCharge::Cols::_due_date = "\"due_date\"";
const std::string LoanCharge::Cols::_installment_number = "\"installment_number\"";
const std::string LoanCharge::Cols::_amount = "\"amount\"";
const std::string LoanCharge::Cols::_amount_paid_derived = "\"amount_paid_derived\"";
const std::string LoanCharge::Cols::_amount_waived_derived = "\"amount_waived_derived\"";
const std::string LoanCharge::Cols::_amount_writtenoff_derived = "\"amount_writtenoff_derived\"";
const std::string LoanCharge::Cols::_amount_outstanding_derived = "\"amount_outstanding_derived\"";
const std::string LoanCharge::Cols::_is_paid_derived = "\"is_paid_derived\"";
const std::string LoanCharge::Cols::_is_waived = "\"is_waived\"";
const std::string LoanCharge::Cols::_is_active = "\"is_active\"";
const std::string LoanCharge::Cols::_created_at = "\"created_at\"";
const std::string LoanCharge::primaryKeyName = "id";
const bool LoanCharge::hasPrimaryKey = true;
const std::string LoanCharge::tableName = "\"loan_charge\"";

const std::vector<typename LoanCharge::MetaData> LoanCharge::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"charge_id","std::string","uuid",0,0,0,1},
{"is_penalty","bool","boolean",1,0,0,1},
{"charge_time_type","int32_t","integer",4,0,0,1},
{"charge_calculation_type","int32_t","integer",4,0,0,1},
{"due_date","::trantor::Date","date",0,0,0,0},
{"installment_number","int32_t","integer",4,0,0,0},
{"amount","std::string","numeric",0,0,0,1},
{"amount_paid_derived","std::string","numeric",0,0,0,1},
{"amount_waived_derived","std::string","numeric",0,0,0,1},
{"amount_writtenoff_derived","std::string","numeric",0,0,0,1},
{"amount_outstanding_derived","std::string","numeric",0,0,0,1},
{"is_paid_derived","bool","boolean",1,0,0,1},
{"is_waived","bool","boolean",1,0,0,1},
{"is_active","bool","boolean",1,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanCharge::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanCharge::LoanCharge(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["loan_id"].isNull())
        {
            loanId_=std::make_shared<std::string>(r["loan_id"].as<std::string>());
        }
        if(!r["charge_id"].isNull())
        {
            chargeId_=std::make_shared<std::string>(r["charge_id"].as<std::string>());
        }
        if(!r["is_penalty"].isNull())
        {
            isPenalty_=std::make_shared<bool>(r["is_penalty"].as<bool>());
        }
        if(!r["charge_time_type"].isNull())
        {
            chargeTimeType_=std::make_shared<int32_t>(r["charge_time_type"].as<int32_t>());
        }
        if(!r["charge_calculation_type"].isNull())
        {
            chargeCalculationType_=std::make_shared<int32_t>(r["charge_calculation_type"].as<int32_t>());
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
        if(!r["installment_number"].isNull())
        {
            installmentNumber_=std::make_shared<int32_t>(r["installment_number"].as<int32_t>());
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
        if(!r["amount_writtenoff_derived"].isNull())
        {
            amountWrittenoffDerived_=std::make_shared<std::string>(r["amount_writtenoff_derived"].as<std::string>());
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
        if(offset + 17 > r.size())
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
            loanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            chargeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            isPenalty_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            chargeTimeType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            chargeCalculationType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            installmentNumber_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            amountPaidDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            amountWaivedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            amountWrittenoffDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            amountOutstandingDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            isPaidDerived_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            isWaived_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
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
    }

}
const std::string &LoanCharge::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getId() const noexcept
{
    return id_;
}
void LoanCharge::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanCharge::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanCharge::PrimaryKeyType & LoanCharge::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanCharge::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getLoanId() const noexcept
{
    return loanId_;
}
void LoanCharge::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanCharge::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanCharge::getValueOfChargeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(chargeId_)
        return *chargeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getChargeId() const noexcept
{
    return chargeId_;
}
void LoanCharge::setChargeId(const std::string &pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(pChargeId);
    dirtyFlag_[2] = true;
}
void LoanCharge::setChargeId(std::string &&pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(std::move(pChargeId));
    dirtyFlag_[2] = true;
}

const bool &LoanCharge::getValueOfIsPenalty() const noexcept
{
    static const bool defaultValue = bool();
    if(isPenalty_)
        return *isPenalty_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanCharge::getIsPenalty() const noexcept
{
    return isPenalty_;
}
void LoanCharge::setIsPenalty(const bool &pIsPenalty) noexcept
{
    isPenalty_ = std::make_shared<bool>(pIsPenalty);
    dirtyFlag_[3] = true;
}

const int32_t &LoanCharge::getValueOfChargeTimeType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(chargeTimeType_)
        return *chargeTimeType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanCharge::getChargeTimeType() const noexcept
{
    return chargeTimeType_;
}
void LoanCharge::setChargeTimeType(const int32_t &pChargeTimeType) noexcept
{
    chargeTimeType_ = std::make_shared<int32_t>(pChargeTimeType);
    dirtyFlag_[4] = true;
}

const int32_t &LoanCharge::getValueOfChargeCalculationType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(chargeCalculationType_)
        return *chargeCalculationType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanCharge::getChargeCalculationType() const noexcept
{
    return chargeCalculationType_;
}
void LoanCharge::setChargeCalculationType(const int32_t &pChargeCalculationType) noexcept
{
    chargeCalculationType_ = std::make_shared<int32_t>(pChargeCalculationType);
    dirtyFlag_[5] = true;
}

const ::trantor::Date &LoanCharge::getValueOfDueDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dueDate_)
        return *dueDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanCharge::getDueDate() const noexcept
{
    return dueDate_;
}
void LoanCharge::setDueDate(const ::trantor::Date &pDueDate) noexcept
{
    dueDate_ = std::make_shared<::trantor::Date>(pDueDate);
    dirtyFlag_[6] = true;
}
void LoanCharge::setDueDateToNull() noexcept
{
    dueDate_.reset();
    dirtyFlag_[6] = true;
}

const int32_t &LoanCharge::getValueOfInstallmentNumber() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(installmentNumber_)
        return *installmentNumber_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanCharge::getInstallmentNumber() const noexcept
{
    return installmentNumber_;
}
void LoanCharge::setInstallmentNumber(const int32_t &pInstallmentNumber) noexcept
{
    installmentNumber_ = std::make_shared<int32_t>(pInstallmentNumber);
    dirtyFlag_[7] = true;
}
void LoanCharge::setInstallmentNumberToNull() noexcept
{
    installmentNumber_.reset();
    dirtyFlag_[7] = true;
}

const std::string &LoanCharge::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getAmount() const noexcept
{
    return amount_;
}
void LoanCharge::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[8] = true;
}
void LoanCharge::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[8] = true;
}

const std::string &LoanCharge::getValueOfAmountPaidDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountPaidDerived_)
        return *amountPaidDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getAmountPaidDerived() const noexcept
{
    return amountPaidDerived_;
}
void LoanCharge::setAmountPaidDerived(const std::string &pAmountPaidDerived) noexcept
{
    amountPaidDerived_ = std::make_shared<std::string>(pAmountPaidDerived);
    dirtyFlag_[9] = true;
}
void LoanCharge::setAmountPaidDerived(std::string &&pAmountPaidDerived) noexcept
{
    amountPaidDerived_ = std::make_shared<std::string>(std::move(pAmountPaidDerived));
    dirtyFlag_[9] = true;
}

const std::string &LoanCharge::getValueOfAmountWaivedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountWaivedDerived_)
        return *amountWaivedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getAmountWaivedDerived() const noexcept
{
    return amountWaivedDerived_;
}
void LoanCharge::setAmountWaivedDerived(const std::string &pAmountWaivedDerived) noexcept
{
    amountWaivedDerived_ = std::make_shared<std::string>(pAmountWaivedDerived);
    dirtyFlag_[10] = true;
}
void LoanCharge::setAmountWaivedDerived(std::string &&pAmountWaivedDerived) noexcept
{
    amountWaivedDerived_ = std::make_shared<std::string>(std::move(pAmountWaivedDerived));
    dirtyFlag_[10] = true;
}

const std::string &LoanCharge::getValueOfAmountWrittenoffDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountWrittenoffDerived_)
        return *amountWrittenoffDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getAmountWrittenoffDerived() const noexcept
{
    return amountWrittenoffDerived_;
}
void LoanCharge::setAmountWrittenoffDerived(const std::string &pAmountWrittenoffDerived) noexcept
{
    amountWrittenoffDerived_ = std::make_shared<std::string>(pAmountWrittenoffDerived);
    dirtyFlag_[11] = true;
}
void LoanCharge::setAmountWrittenoffDerived(std::string &&pAmountWrittenoffDerived) noexcept
{
    amountWrittenoffDerived_ = std::make_shared<std::string>(std::move(pAmountWrittenoffDerived));
    dirtyFlag_[11] = true;
}

const std::string &LoanCharge::getValueOfAmountOutstandingDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountOutstandingDerived_)
        return *amountOutstandingDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCharge::getAmountOutstandingDerived() const noexcept
{
    return amountOutstandingDerived_;
}
void LoanCharge::setAmountOutstandingDerived(const std::string &pAmountOutstandingDerived) noexcept
{
    amountOutstandingDerived_ = std::make_shared<std::string>(pAmountOutstandingDerived);
    dirtyFlag_[12] = true;
}
void LoanCharge::setAmountOutstandingDerived(std::string &&pAmountOutstandingDerived) noexcept
{
    amountOutstandingDerived_ = std::make_shared<std::string>(std::move(pAmountOutstandingDerived));
    dirtyFlag_[12] = true;
}

const bool &LoanCharge::getValueOfIsPaidDerived() const noexcept
{
    static const bool defaultValue = bool();
    if(isPaidDerived_)
        return *isPaidDerived_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanCharge::getIsPaidDerived() const noexcept
{
    return isPaidDerived_;
}
void LoanCharge::setIsPaidDerived(const bool &pIsPaidDerived) noexcept
{
    isPaidDerived_ = std::make_shared<bool>(pIsPaidDerived);
    dirtyFlag_[13] = true;
}

const bool &LoanCharge::getValueOfIsWaived() const noexcept
{
    static const bool defaultValue = bool();
    if(isWaived_)
        return *isWaived_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanCharge::getIsWaived() const noexcept
{
    return isWaived_;
}
void LoanCharge::setIsWaived(const bool &pIsWaived) noexcept
{
    isWaived_ = std::make_shared<bool>(pIsWaived);
    dirtyFlag_[14] = true;
}

const bool &LoanCharge::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanCharge::getIsActive() const noexcept
{
    return isActive_;
}
void LoanCharge::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[15] = true;
}

const ::trantor::Date &LoanCharge::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanCharge::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanCharge::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[16] = true;
}

void LoanCharge::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanCharge::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "charge_id",
        "is_penalty",
        "charge_time_type",
        "charge_calculation_type",
        "due_date",
        "installment_number",
        "amount",
        "amount_paid_derived",
        "amount_waived_derived",
        "amount_writtenoff_derived",
        "amount_outstanding_derived",
        "is_paid_derived",
        "is_waived",
        "is_active",
        "created_at"
    };
    return inCols;
}

void LoanCharge::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
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
        if(getChargeCalculationType())
        {
            binder << getValueOfChargeCalculationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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
        if(getAmountPaidDerived())
        {
            binder << getValueOfAmountPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
    {
        if(getAmountWrittenoffDerived())
        {
            binder << getValueOfAmountWrittenoffDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
}

const std::vector<std::string> LoanCharge::updateColumns() const
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
    return ret;
}

void LoanCharge::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
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
        if(getChargeCalculationType())
        {
            binder << getValueOfChargeCalculationType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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
        if(getAmountPaidDerived())
        {
            binder << getValueOfAmountPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
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
    if(dirtyFlag_[11])
    {
        if(getAmountWrittenoffDerived())
        {
            binder << getValueOfAmountWrittenoffDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
}
