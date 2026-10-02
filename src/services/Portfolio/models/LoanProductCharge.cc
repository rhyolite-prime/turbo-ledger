/**
 *  LoanProductCharge.cc
 *
 *  See LoanProductCharge.h for the hand-authored-subset note.
 *
 */

#include "LoanProductCharge.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanProductCharge::Cols::_id = "\"id\"";
const std::string LoanProductCharge::Cols::_loan_product_id = "\"loan_product_id\"";
const std::string LoanProductCharge::Cols::_charge_id = "\"charge_id\"";
const std::string LoanProductCharge::primaryKeyName = "id";
const bool LoanProductCharge::hasPrimaryKey = true;
const std::string LoanProductCharge::tableName = "\"loan_product_charge\"";

const std::vector<typename LoanProductCharge::MetaData> LoanProductCharge::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_product_id","std::string","uuid",0,0,0,1},
{"charge_id","std::string","uuid",0,0,0,1}
};
const std::string &LoanProductCharge::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanProductCharge::LoanProductCharge(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["loan_product_id"].isNull())
        {
            loanProductId_=std::make_shared<std::string>(r["loan_product_id"].as<std::string>());
        }
        if(!r["charge_id"].isNull())
        {
            chargeId_=std::make_shared<std::string>(r["charge_id"].as<std::string>());
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
            loanProductId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            chargeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &LoanProductCharge::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductCharge::getId() const noexcept
{
    return id_;
}
void LoanProductCharge::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanProductCharge::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanProductCharge::PrimaryKeyType & LoanProductCharge::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanProductCharge::getValueOfLoanProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanProductId_)
        return *loanProductId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductCharge::getLoanProductId() const noexcept
{
    return loanProductId_;
}
void LoanProductCharge::setLoanProductId(const std::string &pLoanProductId) noexcept
{
    loanProductId_ = std::make_shared<std::string>(pLoanProductId);
    dirtyFlag_[1] = true;
}
void LoanProductCharge::setLoanProductId(std::string &&pLoanProductId) noexcept
{
    loanProductId_ = std::make_shared<std::string>(std::move(pLoanProductId));
    dirtyFlag_[1] = true;
}

const std::string &LoanProductCharge::getValueOfChargeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(chargeId_)
        return *chargeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductCharge::getChargeId() const noexcept
{
    return chargeId_;
}
void LoanProductCharge::setChargeId(const std::string &pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(pChargeId);
    dirtyFlag_[2] = true;
}
void LoanProductCharge::setChargeId(std::string &&pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(std::move(pChargeId));
    dirtyFlag_[2] = true;
}

void LoanProductCharge::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanProductCharge::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_product_id",
        "charge_id"
    };
    return inCols;
}

void LoanProductCharge::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanProductId())
        {
            binder << getValueOfLoanProductId();
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
}

const std::vector<std::string> LoanProductCharge::updateColumns() const
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

void LoanProductCharge::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanProductId())
        {
            binder << getValueOfLoanProductId();
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
}
