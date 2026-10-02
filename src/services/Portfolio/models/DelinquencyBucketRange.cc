/**
 *  DelinquencyBucketRange.cc
 *
 *  See DelinquencyBucketRange.h for the hand-authored-subset note.
 *
 */

#include "DelinquencyBucketRange.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string DelinquencyBucketRange::Cols::_id = "\"id\"";
const std::string DelinquencyBucketRange::Cols::_delinquency_bucket_id = "\"delinquency_bucket_id\"";
const std::string DelinquencyBucketRange::Cols::_delinquency_range_id = "\"delinquency_range_id\"";
const std::string DelinquencyBucketRange::primaryKeyName = "id";
const bool DelinquencyBucketRange::hasPrimaryKey = true;
const std::string DelinquencyBucketRange::tableName = "\"delinquency_bucket_range\"";

const std::vector<typename DelinquencyBucketRange::MetaData> DelinquencyBucketRange::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"delinquency_bucket_id","std::string","uuid",0,0,0,1},
{"delinquency_range_id","std::string","uuid",0,0,0,1}
};
const std::string &DelinquencyBucketRange::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
DelinquencyBucketRange::DelinquencyBucketRange(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["delinquency_bucket_id"].isNull())
        {
            delinquencyBucketId_=std::make_shared<std::string>(r["delinquency_bucket_id"].as<std::string>());
        }
        if(!r["delinquency_range_id"].isNull())
        {
            delinquencyRangeId_=std::make_shared<std::string>(r["delinquency_range_id"].as<std::string>());
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
            delinquencyBucketId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            delinquencyRangeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &DelinquencyBucketRange::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DelinquencyBucketRange::getId() const noexcept
{
    return id_;
}
void DelinquencyBucketRange::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void DelinquencyBucketRange::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename DelinquencyBucketRange::PrimaryKeyType & DelinquencyBucketRange::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &DelinquencyBucketRange::getValueOfDelinquencyBucketId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(delinquencyBucketId_)
        return *delinquencyBucketId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DelinquencyBucketRange::getDelinquencyBucketId() const noexcept
{
    return delinquencyBucketId_;
}
void DelinquencyBucketRange::setDelinquencyBucketId(const std::string &pDelinquencyBucketId) noexcept
{
    delinquencyBucketId_ = std::make_shared<std::string>(pDelinquencyBucketId);
    dirtyFlag_[1] = true;
}
void DelinquencyBucketRange::setDelinquencyBucketId(std::string &&pDelinquencyBucketId) noexcept
{
    delinquencyBucketId_ = std::make_shared<std::string>(std::move(pDelinquencyBucketId));
    dirtyFlag_[1] = true;
}

const std::string &DelinquencyBucketRange::getValueOfDelinquencyRangeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(delinquencyRangeId_)
        return *delinquencyRangeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DelinquencyBucketRange::getDelinquencyRangeId() const noexcept
{
    return delinquencyRangeId_;
}
void DelinquencyBucketRange::setDelinquencyRangeId(const std::string &pDelinquencyRangeId) noexcept
{
    delinquencyRangeId_ = std::make_shared<std::string>(pDelinquencyRangeId);
    dirtyFlag_[2] = true;
}
void DelinquencyBucketRange::setDelinquencyRangeId(std::string &&pDelinquencyRangeId) noexcept
{
    delinquencyRangeId_ = std::make_shared<std::string>(std::move(pDelinquencyRangeId));
    dirtyFlag_[2] = true;
}

void DelinquencyBucketRange::updateId(const uint64_t id)
{
}

const std::vector<std::string> &DelinquencyBucketRange::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "delinquency_bucket_id",
        "delinquency_range_id"
    };
    return inCols;
}

void DelinquencyBucketRange::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getDelinquencyBucketId())
        {
            binder << getValueOfDelinquencyBucketId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDelinquencyRangeId())
        {
            binder << getValueOfDelinquencyRangeId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> DelinquencyBucketRange::updateColumns() const
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

void DelinquencyBucketRange::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getDelinquencyBucketId())
        {
            binder << getValueOfDelinquencyBucketId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDelinquencyRangeId())
        {
            binder << getValueOfDelinquencyRangeId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
