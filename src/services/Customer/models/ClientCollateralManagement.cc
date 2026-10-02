/**
 *  ClientCollateralManagement.cc
 *
 *  See ClientCollateralManagement.h for the hand-authored-subset note.
 *
 */

#include "ClientCollateralManagement.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlCustomerDb;

const std::string ClientCollateralManagement::Cols::_id = "\"id\"";
const std::string ClientCollateralManagement::Cols::_business_id = "\"business_id\"";
const std::string ClientCollateralManagement::Cols::_quantity = "\"quantity\"";
const std::string ClientCollateralManagement::Cols::_client_id = "\"client_id\"";
const std::string ClientCollateralManagement::Cols::_collateral_id = "\"collateral_id\"";
const std::string ClientCollateralManagement::Cols::_created_by = "\"created_by\"";
const std::string ClientCollateralManagement::Cols::_created_at = "\"created_at\"";
const std::string ClientCollateralManagement::Cols::_updated_by = "\"updated_by\"";
const std::string ClientCollateralManagement::Cols::_updated_at = "\"updated_at\"";
const std::string ClientCollateralManagement::primaryKeyName = "id";
const bool ClientCollateralManagement::hasPrimaryKey = true;
const std::string ClientCollateralManagement::tableName = "\"client_collateral_management\"";

const std::vector<typename ClientCollateralManagement::MetaData> ClientCollateralManagement::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"quantity","std::string","numeric",0,0,0,1},
{"client_id","std::string","uuid",0,0,0,1},
{"collateral_id","std::string","uuid",0,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,0},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,0}
};
const std::string &ClientCollateralManagement::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ClientCollateralManagement::ClientCollateralManagement(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["business_id"].isNull())
        {
            businessId_=std::make_shared<std::string>(r["business_id"].as<std::string>());
        }
        if(!r["quantity"].isNull())
        {
            quantity_=std::make_shared<std::string>(r["quantity"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["collateral_id"].isNull())
        {
            collateralId_=std::make_shared<std::string>(r["collateral_id"].as<std::string>());
        }
        if(!r["created_by"].isNull())
        {
            createdBy_=std::make_shared<std::string>(r["created_by"].as<std::string>());
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
        if(!r["updated_by"].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r["updated_by"].as<std::string>());
        }
        if(!r["updated_at"].isNull())
        {
            auto timeStr = r["updated_at"].as<std::string>();
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 9 > r.size())
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
            businessId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            quantity_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            collateralId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
        index = offset + 7;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &ClientCollateralManagement::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientCollateralManagement::getId() const noexcept
{
    return id_;
}
void ClientCollateralManagement::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ClientCollateralManagement::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ClientCollateralManagement::PrimaryKeyType & ClientCollateralManagement::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ClientCollateralManagement::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientCollateralManagement::getBusinessId() const noexcept
{
    return businessId_;
}
void ClientCollateralManagement::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void ClientCollateralManagement::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void ClientCollateralManagement::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &ClientCollateralManagement::getValueOfQuantity() const noexcept
{
    static const std::string defaultValue = std::string();
    if(quantity_)
        return *quantity_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientCollateralManagement::getQuantity() const noexcept
{
    return quantity_;
}
void ClientCollateralManagement::setQuantity(const std::string &pQuantity) noexcept
{
    quantity_ = std::make_shared<std::string>(pQuantity);
    dirtyFlag_[2] = true;
}
void ClientCollateralManagement::setQuantity(std::string &&pQuantity) noexcept
{
    quantity_ = std::make_shared<std::string>(std::move(pQuantity));
    dirtyFlag_[2] = true;
}

const std::string &ClientCollateralManagement::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientCollateralManagement::getClientId() const noexcept
{
    return clientId_;
}
void ClientCollateralManagement::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[3] = true;
}
void ClientCollateralManagement::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[3] = true;
}

const std::string &ClientCollateralManagement::getValueOfCollateralId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(collateralId_)
        return *collateralId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientCollateralManagement::getCollateralId() const noexcept
{
    return collateralId_;
}
void ClientCollateralManagement::setCollateralId(const std::string &pCollateralId) noexcept
{
    collateralId_ = std::make_shared<std::string>(pCollateralId);
    dirtyFlag_[4] = true;
}
void ClientCollateralManagement::setCollateralId(std::string &&pCollateralId) noexcept
{
    collateralId_ = std::make_shared<std::string>(std::move(pCollateralId));
    dirtyFlag_[4] = true;
}

const std::string &ClientCollateralManagement::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientCollateralManagement::getCreatedBy() const noexcept
{
    return createdBy_;
}
void ClientCollateralManagement::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[5] = true;
}
void ClientCollateralManagement::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[5] = true;
}
void ClientCollateralManagement::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &ClientCollateralManagement::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientCollateralManagement::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ClientCollateralManagement::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[6] = true;
}
void ClientCollateralManagement::setCreatedAtToNull() noexcept
{
    createdAt_.reset();
    dirtyFlag_[6] = true;
}

const std::string &ClientCollateralManagement::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientCollateralManagement::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void ClientCollateralManagement::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[7] = true;
}
void ClientCollateralManagement::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[7] = true;
}
void ClientCollateralManagement::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[7] = true;
}

const ::trantor::Date &ClientCollateralManagement::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientCollateralManagement::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void ClientCollateralManagement::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[8] = true;
}
void ClientCollateralManagement::setUpdatedAtToNull() noexcept
{
    updatedAt_.reset();
    dirtyFlag_[8] = true;
}

void ClientCollateralManagement::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ClientCollateralManagement::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "quantity",
        "client_id",
        "collateral_id",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void ClientCollateralManagement::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getQuantity())
        {
            binder << getValueOfQuantity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getCollateralId())
        {
            binder << getValueOfCollateralId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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
    if(dirtyFlag_[7])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> ClientCollateralManagement::updateColumns() const
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
    return ret;
}

void ClientCollateralManagement::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getQuantity())
        {
            binder << getValueOfQuantity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getCollateralId())
        {
            binder << getValueOfCollateralId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
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
    if(dirtyFlag_[7])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}
