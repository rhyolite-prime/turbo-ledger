/**
 *  ShareProductCharge.cc
 *
 *  See ShareProductCharge.h for the hand-authored-subset note.
 *
 */

#include "ShareProductCharge.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ShareProductCharge::Cols::_id = "\"id\"";
const std::string ShareProductCharge::Cols::_share_product_id = "\"share_product_id\"";
const std::string ShareProductCharge::Cols::_charge_id = "\"charge_id\"";
const std::string ShareProductCharge::primaryKeyName = "id";
const bool ShareProductCharge::hasPrimaryKey = true;
const std::string ShareProductCharge::tableName = "\"share_product_charge\"";

const std::vector<typename ShareProductCharge::MetaData> ShareProductCharge::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"share_product_id","std::string","uuid",0,0,0,1},
{"charge_id","std::string","uuid",0,0,0,1}
};
const std::string &ShareProductCharge::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ShareProductCharge::ShareProductCharge(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["share_product_id"].isNull())
        {
            shareProductId_=std::make_shared<std::string>(r["share_product_id"].as<std::string>());
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
            shareProductId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            chargeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &ShareProductCharge::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProductCharge::getId() const noexcept
{
    return id_;
}
void ShareProductCharge::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ShareProductCharge::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ShareProductCharge::PrimaryKeyType & ShareProductCharge::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ShareProductCharge::getValueOfShareProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareProductId_)
        return *shareProductId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProductCharge::getShareProductId() const noexcept
{
    return shareProductId_;
}
void ShareProductCharge::setShareProductId(const std::string &pShareProductId) noexcept
{
    shareProductId_ = std::make_shared<std::string>(pShareProductId);
    dirtyFlag_[1] = true;
}
void ShareProductCharge::setShareProductId(std::string &&pShareProductId) noexcept
{
    shareProductId_ = std::make_shared<std::string>(std::move(pShareProductId));
    dirtyFlag_[1] = true;
}

const std::string &ShareProductCharge::getValueOfChargeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(chargeId_)
        return *chargeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProductCharge::getChargeId() const noexcept
{
    return chargeId_;
}
void ShareProductCharge::setChargeId(const std::string &pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(pChargeId);
    dirtyFlag_[2] = true;
}
void ShareProductCharge::setChargeId(std::string &&pChargeId) noexcept
{
    chargeId_ = std::make_shared<std::string>(std::move(pChargeId));
    dirtyFlag_[2] = true;
}

void ShareProductCharge::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ShareProductCharge::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "share_product_id",
        "charge_id"
    };
    return inCols;
}

void ShareProductCharge::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareProductId())
        {
            binder << getValueOfShareProductId();
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

const std::vector<std::string> ShareProductCharge::updateColumns() const
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

void ShareProductCharge::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getShareProductId())
        {
            binder << getValueOfShareProductId();
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
