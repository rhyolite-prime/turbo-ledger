/**
 *  ShareAccountCharge.cc
 *
 *  See ShareAccountCharge.h for the hand-authored-subset note.
 *
 */

#include "ShareAccountCharge.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ShareAccountCharge::Cols::_id = "\"id\"";
const std::string ShareAccountCharge::Cols::_share_account_id = "\"share_account_id\"";
const std::string ShareAccountCharge::Cols::_charge_id = "\"charge_id\"";
const std::string ShareAccountCharge::Cols::_amount = "\"amount\"";
const std::string ShareAccountCharge::Cols::_amount_paid_derived = "\"amount_paid_derived\"";
const std::string ShareAccountCharge::Cols::_is_active = "\"is_active\"";
const std::string ShareAccountCharge::primaryKeyName = "id";
const bool ShareAccountCharge::hasPrimaryKey = true;
const std::string ShareAccountCharge::tableName = "\"share_account_charge\"";

const std::vector<typename ShareAccountCharge::MetaData> ShareAccountCharge::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"share_account_id","std::string","uuid",0,0,0,1},
{"charge_id","std::string","uuid",0,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"amount_paid_derived","std::string","numeric",0,0,0,1},
{"is_active","bool","boolean",1,0,0,1}
};
const std::string &ShareAccountCharge::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ShareAccountCharge::ShareAccountCharge(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["share_account_id"].isNull())
        {
            shareAccountId_=std::make_shared<std::string>(r["share_account_id"].as<std::string>());
        }
        if(!r["charge_id"].isNull())
        {
            chargeId_=std::make_shared<std::string>(r["charge_id"].as<std::string>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["amount_paid_derived"].isNull())
        {
            amountPaidDerived_=std::make_shared<std::string>(r["amount_paid_derived"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
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
            shareAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            chargeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            amountPaidDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
    }

}
const std::string &ShareAccountCharge::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccountCharge::getId() const noexcept
{
    return id_;
}
void ShareAccountCharge::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ShareAccountCharge::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ShareAccountCharge::PrimaryKeyType & ShareAccountCharge::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ShareAccountCharge::getValueOfShareAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareAccountId_)
        return *shareAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccountCharge::getShareAccountId() const noexcept
{
    return shareAccountId_;
}
void ShareAccountCharge::setShareAccountId(const std::string &pShareAccountId) noexcept
{
    shareAccountId_ = std::make_shared<std::string>(pShareAccountId);
    dirtyFlag_[1] = true;
}
void ShareAccountCharge::setShareAccountId(std::string &&pShareAccountId) noexcept
{
    shareAccountId_ = std::make_shared<std::string>(std::move(pShareAccountId));
    dirtyFlag_[1] = true;
}

const std::string &ShareAccountCharge::getValueOfChargeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(chargeId_)
        return *chargeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccountCharge::getChargeId() const noexcept
{
    return chargeId_;
}
void ShareAccountCharge::setChargeId(const std::string &pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(pChargeId);
    dirtyFlag_[2] = true;
}
void ShareAccountCharge::setChargeId(std::string &&pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(std::move(pChargeId));
    dirtyFlag_[2] = true;
}

const std::string &ShareAccountCharge::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccountCharge::getAmount() const noexcept
{
    return amount_;
}
void ShareAccountCharge::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[3] = true;
}
void ShareAccountCharge::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[3] = true;
}

const std::string &ShareAccountCharge::getValueOfAmountPaidDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amountPaidDerived_)
        return *amountPaidDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccountCharge::getAmountPaidDerived() const noexcept
{
    return amountPaidDerived_;
}
void ShareAccountCharge::setAmountPaidDerived(const std::string &pAmountPaidDerived) noexcept
{
    amountPaidDerived_ = std::make_shared<std::string>(pAmountPaidDerived);
    dirtyFlag_[4] = true;
}
void ShareAccountCharge::setAmountPaidDerived(std::string &&pAmountPaidDerived) noexcept
{
    amountPaidDerived_ = std::make_shared<std::string>(std::move(pAmountPaidDerived));
    dirtyFlag_[4] = true;
}

const bool &ShareAccountCharge::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &ShareAccountCharge::getIsActive() const noexcept
{
    return isActive_;
}
void ShareAccountCharge::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[5] = true;
}

void ShareAccountCharge::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ShareAccountCharge::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "share_account_id",
        "charge_id",
        "amount",
        "amount_paid_derived",
        "is_active"
    };
    return inCols;
}

void ShareAccountCharge::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareAccountId())
        {
            binder << getValueOfShareAccountId();
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
        if(getAmountPaidDerived())
        {
            binder << getValueOfAmountPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
}

const std::vector<std::string> ShareAccountCharge::updateColumns() const
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

void ShareAccountCharge::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareAccountId())
        {
            binder << getValueOfShareAccountId();
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
        if(getAmountPaidDerived())
        {
            binder << getValueOfAmountPaidDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
}
