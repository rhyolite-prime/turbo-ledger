/**
 *  LoanCapitalizedIncome.cc
 *
 *  See LoanCapitalizedIncome.h for the hand-authored-subset note.
 *
 */

#include "LoanCapitalizedIncome.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanCapitalizedIncome::Cols::_id = "\"id\"";
const std::string LoanCapitalizedIncome::Cols::_loan_id = "\"loan_id\"";
const std::string LoanCapitalizedIncome::Cols::_loan_transaction_id = "\"loan_transaction_id\"";
const std::string LoanCapitalizedIncome::Cols::_income_type = "\"income_type\"";
const std::string LoanCapitalizedIncome::Cols::_amount = "\"amount\"";
const std::string LoanCapitalizedIncome::Cols::_amortized_amount = "\"amortized_amount\"";
const std::string LoanCapitalizedIncome::Cols::_created_at = "\"created_at\"";
const std::string LoanCapitalizedIncome::primaryKeyName = "id";
const bool LoanCapitalizedIncome::hasPrimaryKey = true;
const std::string LoanCapitalizedIncome::tableName = "\"loan_capitalized_income\"";

const std::vector<typename LoanCapitalizedIncome::MetaData> LoanCapitalizedIncome::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"loan_transaction_id","std::string","uuid",0,0,0,0},
{"income_type","std::string","character varying",40,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"amortized_amount","std::string","numeric",0,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanCapitalizedIncome::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanCapitalizedIncome::LoanCapitalizedIncome(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["loan_transaction_id"].isNull())
        {
            loanTransactionId_=std::make_shared<std::string>(r["loan_transaction_id"].as<std::string>());
        }
        if(!r["income_type"].isNull())
        {
            incomeType_=std::make_shared<std::string>(r["income_type"].as<std::string>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["amortized_amount"].isNull())
        {
            amortizedAmount_=std::make_shared<std::string>(r["amortized_amount"].as<std::string>());
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
        if(offset + 7 > r.size())
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
            loanTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            incomeType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            amortizedAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
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
const std::string &LoanCapitalizedIncome::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCapitalizedIncome::getId() const noexcept
{
    return id_;
}
void LoanCapitalizedIncome::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanCapitalizedIncome::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanCapitalizedIncome::PrimaryKeyType & LoanCapitalizedIncome::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanCapitalizedIncome::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCapitalizedIncome::getLoanId() const noexcept
{
    return loanId_;
}
void LoanCapitalizedIncome::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanCapitalizedIncome::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanCapitalizedIncome::getValueOfLoanTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanTransactionId_)
        return *loanTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCapitalizedIncome::getLoanTransactionId() const noexcept
{
    return loanTransactionId_;
}
void LoanCapitalizedIncome::setLoanTransactionId(const std::string &pLoanTransactionId) noexcept
{
    loanTransactionId_ = std::make_shared<std::string>(pLoanTransactionId);
    dirtyFlag_[2] = true;
}
void LoanCapitalizedIncome::setLoanTransactionId(std::string &&pLoanTransactionId) noexcept
{
    loanTransactionId_ = std::make_shared<std::string>(std::move(pLoanTransactionId));
    dirtyFlag_[2] = true;
}
void LoanCapitalizedIncome::setLoanTransactionIdToNull() noexcept
{
    loanTransactionId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &LoanCapitalizedIncome::getValueOfIncomeType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(incomeType_)
        return *incomeType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCapitalizedIncome::getIncomeType() const noexcept
{
    return incomeType_;
}
void LoanCapitalizedIncome::setIncomeType(const std::string &pIncomeType) noexcept
{
    incomeType_ = std::make_shared<std::string>(pIncomeType);
    dirtyFlag_[3] = true;
}
void LoanCapitalizedIncome::setIncomeType(std::string &&pIncomeType) noexcept
{
    incomeType_ = std::make_shared<std::string>(std::move(pIncomeType));
    dirtyFlag_[3] = true;
}

const std::string &LoanCapitalizedIncome::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCapitalizedIncome::getAmount() const noexcept
{
    return amount_;
}
void LoanCapitalizedIncome::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[4] = true;
}
void LoanCapitalizedIncome::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[4] = true;
}

const std::string &LoanCapitalizedIncome::getValueOfAmortizedAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amortizedAmount_)
        return *amortizedAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanCapitalizedIncome::getAmortizedAmount() const noexcept
{
    return amortizedAmount_;
}
void LoanCapitalizedIncome::setAmortizedAmount(const std::string &pAmortizedAmount) noexcept
{
    amortizedAmount_ = std::make_shared<std::string>(pAmortizedAmount);
    dirtyFlag_[5] = true;
}
void LoanCapitalizedIncome::setAmortizedAmount(std::string &&pAmortizedAmount) noexcept
{
    amortizedAmount_ = std::make_shared<std::string>(std::move(pAmortizedAmount));
    dirtyFlag_[5] = true;
}

const ::trantor::Date &LoanCapitalizedIncome::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanCapitalizedIncome::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanCapitalizedIncome::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[6] = true;
}

void LoanCapitalizedIncome::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanCapitalizedIncome::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "loan_transaction_id",
        "income_type",
        "amount",
        "amortized_amount",
        "created_at"
    };
    return inCols;
}

void LoanCapitalizedIncome::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanTransactionId())
        {
            binder << getValueOfLoanTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getIncomeType())
        {
            binder << getValueOfIncomeType();
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
        if(getAmortizedAmount())
        {
            binder << getValueOfAmortizedAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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

const std::vector<std::string> LoanCapitalizedIncome::updateColumns() const
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
    return ret;
}

void LoanCapitalizedIncome::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanTransactionId())
        {
            binder << getValueOfLoanTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getIncomeType())
        {
            binder << getValueOfIncomeType();
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
        if(getAmortizedAmount())
        {
            binder << getValueOfAmortizedAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
