/**
 *  AccountTransferDetails.cc
 *
 *  See AccountTransferDetails.h for the hand-authored-subset note.
 *
 */

#include "AccountTransferDetails.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string AccountTransferDetails::Cols::_id = "\"id\"";
const std::string AccountTransferDetails::Cols::_business_id = "\"business_id\"";
const std::string AccountTransferDetails::Cols::_from_office_id = "\"from_office_id\"";
const std::string AccountTransferDetails::Cols::_from_client_id = "\"from_client_id\"";
const std::string AccountTransferDetails::Cols::_from_account_type = "\"from_account_type\"";
const std::string AccountTransferDetails::Cols::_from_account_id = "\"from_account_id\"";
const std::string AccountTransferDetails::Cols::_to_office_id = "\"to_office_id\"";
const std::string AccountTransferDetails::Cols::_to_client_id = "\"to_client_id\"";
const std::string AccountTransferDetails::Cols::_to_account_type = "\"to_account_type\"";
const std::string AccountTransferDetails::Cols::_to_account_id = "\"to_account_id\"";
const std::string AccountTransferDetails::Cols::_transfer_type = "\"transfer_type\"";
const std::string AccountTransferDetails::Cols::_created_by = "\"created_by\"";
const std::string AccountTransferDetails::Cols::_created_at = "\"created_at\"";
const std::string AccountTransferDetails::Cols::_updated_by = "\"updated_by\"";
const std::string AccountTransferDetails::Cols::_updated_at = "\"updated_at\"";
const std::string AccountTransferDetails::primaryKeyName = "id";
const bool AccountTransferDetails::hasPrimaryKey = true;
const std::string AccountTransferDetails::tableName = "\"account_transfer_details\"";

const std::vector<typename AccountTransferDetails::MetaData> AccountTransferDetails::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"from_office_id","std::string","uuid",0,0,0,0},
{"from_client_id","std::string","uuid",0,0,0,0},
{"from_account_type","int32_t","integer",4,0,0,1},
{"from_account_id","std::string","uuid",0,0,0,1},
{"to_office_id","std::string","uuid",0,0,0,0},
{"to_client_id","std::string","uuid",0,0,0,0},
{"to_account_type","int32_t","integer",4,0,0,1},
{"to_account_id","std::string","uuid",0,0,0,1},
{"transfer_type","int32_t","integer",4,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &AccountTransferDetails::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
AccountTransferDetails::AccountTransferDetails(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["from_office_id"].isNull())
        {
            fromOfficeId_=std::make_shared<std::string>(r["from_office_id"].as<std::string>());
        }
        if(!r["from_client_id"].isNull())
        {
            fromClientId_=std::make_shared<std::string>(r["from_client_id"].as<std::string>());
        }
        if(!r["from_account_type"].isNull())
        {
            fromAccountType_=std::make_shared<int32_t>(r["from_account_type"].as<int32_t>());
        }
        if(!r["from_account_id"].isNull())
        {
            fromAccountId_=std::make_shared<std::string>(r["from_account_id"].as<std::string>());
        }
        if(!r["to_office_id"].isNull())
        {
            toOfficeId_=std::make_shared<std::string>(r["to_office_id"].as<std::string>());
        }
        if(!r["to_client_id"].isNull())
        {
            toClientId_=std::make_shared<std::string>(r["to_client_id"].as<std::string>());
        }
        if(!r["to_account_type"].isNull())
        {
            toAccountType_=std::make_shared<int32_t>(r["to_account_type"].as<int32_t>());
        }
        if(!r["to_account_id"].isNull())
        {
            toAccountId_=std::make_shared<std::string>(r["to_account_id"].as<std::string>());
        }
        if(!r["transfer_type"].isNull())
        {
            transferType_=std::make_shared<int32_t>(r["transfer_type"].as<int32_t>());
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
        if(offset + 15 > r.size())
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
            fromOfficeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            fromClientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            fromAccountType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            fromAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            toOfficeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            toClientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            toAccountType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            toAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            transferType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
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
        index = offset + 13;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 14;
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
const std::string &AccountTransferDetails::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getId() const noexcept
{
    return id_;
}
void AccountTransferDetails::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void AccountTransferDetails::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename AccountTransferDetails::PrimaryKeyType & AccountTransferDetails::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &AccountTransferDetails::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getBusinessId() const noexcept
{
    return businessId_;
}
void AccountTransferDetails::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void AccountTransferDetails::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void AccountTransferDetails::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &AccountTransferDetails::getValueOfFromOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromOfficeId_)
        return *fromOfficeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getFromOfficeId() const noexcept
{
    return fromOfficeId_;
}
void AccountTransferDetails::setFromOfficeId(const std::string &pFromOfficeId) noexcept
{
    fromOfficeId_ = std::make_shared<std::string>(pFromOfficeId);
    dirtyFlag_[2] = true;
}
void AccountTransferDetails::setFromOfficeId(std::string &&pFromOfficeId) noexcept
{
    fromOfficeId_ = std::make_shared<std::string>(std::move(pFromOfficeId));
    dirtyFlag_[2] = true;
}
void AccountTransferDetails::setFromOfficeIdToNull() noexcept
{
    fromOfficeId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &AccountTransferDetails::getValueOfFromClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromClientId_)
        return *fromClientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getFromClientId() const noexcept
{
    return fromClientId_;
}
void AccountTransferDetails::setFromClientId(const std::string &pFromClientId) noexcept
{
    fromClientId_ = std::make_shared<std::string>(pFromClientId);
    dirtyFlag_[3] = true;
}
void AccountTransferDetails::setFromClientId(std::string &&pFromClientId) noexcept
{
    fromClientId_ = std::make_shared<std::string>(std::move(pFromClientId));
    dirtyFlag_[3] = true;
}
void AccountTransferDetails::setFromClientIdToNull() noexcept
{
    fromClientId_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &AccountTransferDetails::getValueOfFromAccountType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(fromAccountType_)
        return *fromAccountType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &AccountTransferDetails::getFromAccountType() const noexcept
{
    return fromAccountType_;
}
void AccountTransferDetails::setFromAccountType(const int32_t &pFromAccountType) noexcept
{
    fromAccountType_ = std::make_shared<int32_t>(pFromAccountType);
    dirtyFlag_[4] = true;
}

const std::string &AccountTransferDetails::getValueOfFromAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromAccountId_)
        return *fromAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getFromAccountId() const noexcept
{
    return fromAccountId_;
}
void AccountTransferDetails::setFromAccountId(const std::string &pFromAccountId) noexcept
{
    fromAccountId_ = std::make_shared<std::string>(pFromAccountId);
    dirtyFlag_[5] = true;
}
void AccountTransferDetails::setFromAccountId(std::string &&pFromAccountId) noexcept
{
    fromAccountId_ = std::make_shared<std::string>(std::move(pFromAccountId));
    dirtyFlag_[5] = true;
}

const std::string &AccountTransferDetails::getValueOfToOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toOfficeId_)
        return *toOfficeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getToOfficeId() const noexcept
{
    return toOfficeId_;
}
void AccountTransferDetails::setToOfficeId(const std::string &pToOfficeId) noexcept
{
    toOfficeId_ = std::make_shared<std::string>(pToOfficeId);
    dirtyFlag_[6] = true;
}
void AccountTransferDetails::setToOfficeId(std::string &&pToOfficeId) noexcept
{
    toOfficeId_ = std::make_shared<std::string>(std::move(pToOfficeId));
    dirtyFlag_[6] = true;
}
void AccountTransferDetails::setToOfficeIdToNull() noexcept
{
    toOfficeId_.reset();
    dirtyFlag_[6] = true;
}

const std::string &AccountTransferDetails::getValueOfToClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toClientId_)
        return *toClientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getToClientId() const noexcept
{
    return toClientId_;
}
void AccountTransferDetails::setToClientId(const std::string &pToClientId) noexcept
{
    toClientId_ = std::make_shared<std::string>(pToClientId);
    dirtyFlag_[7] = true;
}
void AccountTransferDetails::setToClientId(std::string &&pToClientId) noexcept
{
    toClientId_ = std::make_shared<std::string>(std::move(pToClientId));
    dirtyFlag_[7] = true;
}
void AccountTransferDetails::setToClientIdToNull() noexcept
{
    toClientId_.reset();
    dirtyFlag_[7] = true;
}

const int32_t &AccountTransferDetails::getValueOfToAccountType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(toAccountType_)
        return *toAccountType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &AccountTransferDetails::getToAccountType() const noexcept
{
    return toAccountType_;
}
void AccountTransferDetails::setToAccountType(const int32_t &pToAccountType) noexcept
{
    toAccountType_ = std::make_shared<int32_t>(pToAccountType);
    dirtyFlag_[8] = true;
}

const std::string &AccountTransferDetails::getValueOfToAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toAccountId_)
        return *toAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getToAccountId() const noexcept
{
    return toAccountId_;
}
void AccountTransferDetails::setToAccountId(const std::string &pToAccountId) noexcept
{
    toAccountId_ = std::make_shared<std::string>(pToAccountId);
    dirtyFlag_[9] = true;
}
void AccountTransferDetails::setToAccountId(std::string &&pToAccountId) noexcept
{
    toAccountId_ = std::make_shared<std::string>(std::move(pToAccountId));
    dirtyFlag_[9] = true;
}

const int32_t &AccountTransferDetails::getValueOfTransferType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(transferType_)
        return *transferType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &AccountTransferDetails::getTransferType() const noexcept
{
    return transferType_;
}
void AccountTransferDetails::setTransferType(const int32_t &pTransferType) noexcept
{
    transferType_ = std::make_shared<int32_t>(pTransferType);
    dirtyFlag_[10] = true;
}

const std::string &AccountTransferDetails::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getCreatedBy() const noexcept
{
    return createdBy_;
}
void AccountTransferDetails::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[11] = true;
}
void AccountTransferDetails::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[11] = true;
}
void AccountTransferDetails::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[11] = true;
}

const ::trantor::Date &AccountTransferDetails::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &AccountTransferDetails::getCreatedAt() const noexcept
{
    return createdAt_;
}
void AccountTransferDetails::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[12] = true;
}

const std::string &AccountTransferDetails::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountTransferDetails::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void AccountTransferDetails::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[13] = true;
}
void AccountTransferDetails::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[13] = true;
}
void AccountTransferDetails::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[13] = true;
}

const ::trantor::Date &AccountTransferDetails::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &AccountTransferDetails::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void AccountTransferDetails::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[14] = true;
}

void AccountTransferDetails::updateId(const uint64_t id)
{
}

const std::vector<std::string> &AccountTransferDetails::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "from_office_id",
        "from_client_id",
        "from_account_type",
        "from_account_id",
        "to_office_id",
        "to_client_id",
        "to_account_type",
        "to_account_id",
        "transfer_type",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void AccountTransferDetails::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFromOfficeId())
        {
            binder << getValueOfFromOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromClientId())
        {
            binder << getValueOfFromClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getFromAccountType())
        {
            binder << getValueOfFromAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getFromAccountId())
        {
            binder << getValueOfFromAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getToOfficeId())
        {
            binder << getValueOfToOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getToClientId())
        {
            binder << getValueOfToClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getToAccountType())
        {
            binder << getValueOfToAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getToAccountId())
        {
            binder << getValueOfToAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getTransferType())
        {
            binder << getValueOfTransferType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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

const std::vector<std::string> AccountTransferDetails::updateColumns() const
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
    if(dirtyFlag_[9])
    {
        ret.push_back(getColumnName(9));
    }
    if(dirtyFlag_[10])
    {
        ret.push_back(getColumnName(10));
    }
    if(dirtyFlag_[11])
    {
        ret.push_back(getColumnName(11));
    }
    if(dirtyFlag_[12])
    {
        ret.push_back(getColumnName(12));
    }
    if(dirtyFlag_[13])
    {
        ret.push_back(getColumnName(13));
    }
    if(dirtyFlag_[14])
    {
        ret.push_back(getColumnName(14));
    }
    return ret;
}

void AccountTransferDetails::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFromOfficeId())
        {
            binder << getValueOfFromOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromClientId())
        {
            binder << getValueOfFromClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getFromAccountType())
        {
            binder << getValueOfFromAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getFromAccountId())
        {
            binder << getValueOfFromAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getToOfficeId())
        {
            binder << getValueOfToOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getToClientId())
        {
            binder << getValueOfToClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getToAccountType())
        {
            binder << getValueOfToAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getToAccountId())
        {
            binder << getValueOfToAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getTransferType())
        {
            binder << getValueOfTransferType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
