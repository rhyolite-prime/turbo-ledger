/**
 *  LoanProductMix.cc
 *
 *  See LoanProductMix.h for the hand-authored-subset note.
 *
 */

#include "LoanProductMix.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanProductMix::Cols::_id = "\"id\"";
const std::string LoanProductMix::Cols::_product_id = "\"product_id\"";
const std::string LoanProductMix::Cols::_restricted_product_id = "\"restricted_product_id\"";
const std::string LoanProductMix::primaryKeyName = "id";
const bool LoanProductMix::hasPrimaryKey = true;
const std::string LoanProductMix::tableName = "\"loan_product_mix\"";

const std::vector<typename LoanProductMix::MetaData> LoanProductMix::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"product_id","std::string","uuid",0,0,0,1},
{"restricted_product_id","std::string","uuid",0,0,0,1}
};
const std::string &LoanProductMix::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanProductMix::LoanProductMix(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["restricted_product_id"].isNull())
        {
            restrictedProductId_=std::make_shared<std::string>(r["restricted_product_id"].as<std::string>());
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
            restrictedProductId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &LoanProductMix::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductMix::getId() const noexcept
{
    return id_;
}
void LoanProductMix::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanProductMix::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanProductMix::PrimaryKeyType & LoanProductMix::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanProductMix::getValueOfProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(productId_)
        return *productId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductMix::getProductId() const noexcept
{
    return productId_;
}
void LoanProductMix::setProductId(const std::string &pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(pProductId);
    dirtyFlag_[1] = true;
}
void LoanProductMix::setProductId(std::string &&pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(std::move(pProductId));
    dirtyFlag_[1] = true;
}

const std::string &LoanProductMix::getValueOfRestrictedProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(restrictedProductId_)
        return *restrictedProductId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanProductMix::getRestrictedProductId() const noexcept
{
    return restrictedProductId_;
}
void LoanProductMix::setRestrictedProductId(const std::string &pRestrictedProductId) noexcept
{
    restrictedProductId_ = std::make_shared<std::string>(pRestrictedProductId);
    dirtyFlag_[2] = true;
}
void LoanProductMix::setRestrictedProductId(std::string &&pRestrictedProductId) noexcept
{
    restrictedProductId_ = std::make_shared<std::string>(std::move(pRestrictedProductId));
    dirtyFlag_[2] = true;
}

void LoanProductMix::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanProductMix::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "product_id",
        "restricted_product_id"
    };
    return inCols;
}

void LoanProductMix::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRestrictedProductId())
        {
            binder << getValueOfRestrictedProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> LoanProductMix::updateColumns() const
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

void LoanProductMix::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRestrictedProductId())
        {
            binder << getValueOfRestrictedProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
