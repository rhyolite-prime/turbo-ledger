/**
 *  SavingsProductCharge.cc
 *
 *  See SavingsProductCharge.h for the hand-authored-subset note.
 *
 */

#include "SavingsProductCharge.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string SavingsProductCharge::Cols::_id = "\"id\"";
const std::string SavingsProductCharge::Cols::_product_id = "\"product_id\"";
const std::string SavingsProductCharge::Cols::_charge_id = "\"charge_id\"";
const std::string SavingsProductCharge::primaryKeyName = "id";
const bool SavingsProductCharge::hasPrimaryKey = true;
const std::string SavingsProductCharge::tableName = "\"savings_product_charge\"";

const std::vector<typename SavingsProductCharge::MetaData> SavingsProductCharge::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"product_id","std::string","uuid",0,0,0,1},
{"charge_id","std::string","uuid",0,0,0,1}
};
const std::string &SavingsProductCharge::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SavingsProductCharge::SavingsProductCharge(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["product_id"].isNull())
        {
            productId_=std::make_shared<std::string>(r["product_id"].as<std::string>());
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
            productId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            chargeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &SavingsProductCharge::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProductCharge::getId() const noexcept
{
    return id_;
}
void SavingsProductCharge::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SavingsProductCharge::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SavingsProductCharge::PrimaryKeyType & SavingsProductCharge::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SavingsProductCharge::getValueOfProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(productId_)
        return *productId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProductCharge::getProductId() const noexcept
{
    return productId_;
}
void SavingsProductCharge::setProductId(const std::string &pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(pProductId);
    dirtyFlag_[1] = true;
}
void SavingsProductCharge::setProductId(std::string &&pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(std::move(pProductId));
    dirtyFlag_[1] = true;
}

const std::string &SavingsProductCharge::getValueOfChargeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(chargeId_)
        return *chargeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SavingsProductCharge::getChargeId() const noexcept
{
    return chargeId_;
}
void SavingsProductCharge::setChargeId(const std::string &pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(pChargeId);
    dirtyFlag_[2] = true;
}
void SavingsProductCharge::setChargeId(std::string &&pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(std::move(pChargeId));
    dirtyFlag_[2] = true;
}

void SavingsProductCharge::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SavingsProductCharge::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "product_id",
        "charge_id"
    };
    return inCols;
}

void SavingsProductCharge::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getProductId())
        {
            binder << getValueOfProductId();
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

const std::vector<std::string> SavingsProductCharge::updateColumns() const
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

void SavingsProductCharge::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getProductId())
        {
            binder << getValueOfProductId();
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
