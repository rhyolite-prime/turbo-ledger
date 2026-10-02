/**
 *  LoanRate.cc
 *
 *  See LoanRate.h for the hand-authored-subset note.
 *
 */

#include "LoanRate.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanRate::Cols::_id = "\"id\"";
const std::string LoanRate::Cols::_loan_id = "\"loan_id\"";
const std::string LoanRate::Cols::_rate_id = "\"rate_id\"";
const std::string LoanRate::primaryKeyName = "id";
const bool LoanRate::hasPrimaryKey = true;
const std::string LoanRate::tableName = "\"loan_rate\"";

const std::vector<typename LoanRate::MetaData> LoanRate::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"rate_id","std::string","uuid",0,0,0,1}
};
const std::string &LoanRate::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanRate::LoanRate(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["rate_id"].isNull())
        {
            rateId_=std::make_shared<std::string>(r["rate_id"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
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
            rateId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &LoanRate::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRate::getId() const noexcept
{
    return id_;
}
void LoanRate::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanRate::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanRate::PrimaryKeyType & LoanRate::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanRate::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRate::getLoanId() const noexcept
{
    return loanId_;
}
void LoanRate::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanRate::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanRate::getValueOfRateId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(rateId_)
        return *rateId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRate::getRateId() const noexcept
{
    return rateId_;
}
void LoanRate::setRateId(const std::string &pRateId) noexcept
{
    rateId_ = std::make_shared<std::string>(pRateId);
    dirtyFlag_[2] = true;
}
void LoanRate::setRateId(std::string &&pRateId) noexcept
{
    rateId_ = std::make_shared<std::string>(std::move(pRateId));
    dirtyFlag_[2] = true;
}

void LoanRate::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanRate::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "rate_id"
    };
    return inCols;
}

void LoanRate::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRateId())
        {
            binder << getValueOfRateId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> LoanRate::updateColumns() const
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
    return ret;
}

void LoanRate::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRateId())
        {
            binder << getValueOfRateId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
