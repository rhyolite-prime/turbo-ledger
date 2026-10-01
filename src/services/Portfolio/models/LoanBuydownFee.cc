/**
 *  LoanBuydownFee.cc
 *
 *  See LoanBuydownFee.h for the hand-authored-subset note.
 *
 */

#include "LoanBuydownFee.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanBuydownFee::Cols::_id = "\"id\"";
const std::string LoanBuydownFee::Cols::_loan_id = "\"loan_id\"";
const std::string LoanBuydownFee::Cols::_loan_transaction_id = "\"loan_transaction_id\"";
const std::string LoanBuydownFee::Cols::_amount = "\"amount\"";
const std::string LoanBuydownFee::Cols::_amortized_amount = "\"amortized_amount\"";
const std::string LoanBuydownFee::Cols::_created_at = "\"created_at\"";
const std::string LoanBuydownFee::primaryKeyName = "id";
const bool LoanBuydownFee::hasPrimaryKey = true;
const std::string LoanBuydownFee::tableName = "\"loan_buydown_fee\"";

const std::vector<typename LoanBuydownFee::MetaData> LoanBuydownFee::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"loan_transaction_id","std::string","uuid",0,0,0,0},
{"amount","std::string","numeric",0,0,0,1},
{"amortized_amount","std::string","numeric",0,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanBuydownFee::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanBuydownFee::LoanBuydownFee(const Row &r, const ssize_t indexOffset) noexcept
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
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            amortizedAmount_=std::make_shared<std::string>(r[index].as<std::string>());
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
const std::string &LoanBuydownFee::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanBuydownFee::getId() const noexcept
{
    return id_;
}
void LoanBuydownFee::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanBuydownFee::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanBuydownFee::PrimaryKeyType & LoanBuydownFee::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanBuydownFee::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanBuydownFee::getLoanId() const noexcept
{
    return loanId_;
}
void LoanBuydownFee::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanBuydownFee::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanBuydownFee::getValueOfLoanTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanTransactionId_)
        return *loanTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanBuydownFee::getLoanTransactionId() const noexcept
{
    return loanTransactionId_;
}
void LoanBuydownFee::setLoanTransactionId(const std::string &pLoanTransactionId) noexcept
{
    loanTransactionId_ = std::make_shared<std::string>(pLoanTransactionId);
    dirtyFlag_[2] = true;
}
void LoanBuydownFee::setLoanTransactionId(std::string &&pLoanTransactionId) noexcept
{
    loanTransactionId_ = std::make_shared<std::string>(std::move(pLoanTransactionId));
    dirtyFlag_[2] = true;
}
void LoanBuydownFee::setLoanTransactionIdToNull() noexcept
{
    loanTransactionId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &LoanBuydownFee::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanBuydownFee::getAmount() const noexcept
{
    return amount_;
}
void LoanBuydownFee::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[3] = true;
}
void LoanBuydownFee::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[3] = true;
}

const std::string &LoanBuydownFee::getValueOfAmortizedAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amortizedAmount_)
        return *amortizedAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanBuydownFee::getAmortizedAmount() const noexcept
{
    return amortizedAmount_;
}
void LoanBuydownFee::setAmortizedAmount(const std::string &pAmortizedAmount) noexcept
{
    amortizedAmount_ = std::make_shared<std::string>(pAmortizedAmount);
    dirtyFlag_[4] = true;
}
void LoanBuydownFee::setAmortizedAmount(std::string &&pAmortizedAmount) noexcept
{
    amortizedAmount_ = std::make_shared<std::string>(std::move(pAmortizedAmount));
    dirtyFlag_[4] = true;
}

const ::trantor::Date &LoanBuydownFee::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanBuydownFee::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanBuydownFee::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

void LoanBuydownFee::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanBuydownFee::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "loan_transaction_id",
        "amount",
        "amortized_amount",
        "created_at"
    };
    return inCols;
}

void LoanBuydownFee::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAmortizedAmount())
        {
            binder << getValueOfAmortizedAmount();
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

const std::vector<std::string> LoanBuydownFee::updateColumns() const
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

void LoanBuydownFee::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAmortizedAmount())
        {
            binder << getValueOfAmortizedAmount();
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
