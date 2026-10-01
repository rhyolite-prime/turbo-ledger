/**
 *  LoanOwnerTransfer.cc
 *
 *  See LoanOwnerTransfer.h for the hand-authored-subset note.
 *
 */

#include "LoanOwnerTransfer.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanOwnerTransfer::Cols::_id = "\"id\"";
const std::string LoanOwnerTransfer::Cols::_external_id = "\"external_id\"";
const std::string LoanOwnerTransfer::Cols::_loan_id = "\"loan_id\"";
const std::string LoanOwnerTransfer::Cols::_owner_id = "\"owner_id\"";
const std::string LoanOwnerTransfer::Cols::_transfer_type = "\"transfer_type\"";
const std::string LoanOwnerTransfer::Cols::_status = "\"status\"";
const std::string LoanOwnerTransfer::Cols::_settlement_date = "\"settlement_date\"";
const std::string LoanOwnerTransfer::Cols::_effective_date = "\"effective_date\"";
const std::string LoanOwnerTransfer::Cols::_purchase_price_ratio = "\"purchase_price_ratio\"";
const std::string LoanOwnerTransfer::Cols::_created_by = "\"created_by\"";
const std::string LoanOwnerTransfer::Cols::_created_at = "\"created_at\"";
const std::string LoanOwnerTransfer::primaryKeyName = "id";
const bool LoanOwnerTransfer::hasPrimaryKey = true;
const std::string LoanOwnerTransfer::tableName = "\"loan_owner_transfer\"";

const std::vector<typename LoanOwnerTransfer::MetaData> LoanOwnerTransfer::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"external_id","std::string","character varying",100,0,0,0},
{"loan_id","std::string","uuid",0,0,0,1},
{"owner_id","std::string","uuid",0,0,0,1},
{"transfer_type","int32_t","integer",4,0,0,1},
{"status","int32_t","integer",4,0,0,1},
{"settlement_date","::trantor::Date","date",0,0,0,0},
{"effective_date","::trantor::Date","date",0,0,0,1},
{"purchase_price_ratio","std::string","numeric",0,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanOwnerTransfer::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanOwnerTransfer::LoanOwnerTransfer(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["loan_id"].isNull())
        {
            loanId_=std::make_shared<std::string>(r["loan_id"].as<std::string>());
        }
        if(!r["owner_id"].isNull())
        {
            ownerId_=std::make_shared<std::string>(r["owner_id"].as<std::string>());
        }
        if(!r["transfer_type"].isNull())
        {
            transferType_=std::make_shared<int32_t>(r["transfer_type"].as<int32_t>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["settlement_date"].isNull())
        {
            auto daysStr = r["settlement_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            settlementDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["effective_date"].isNull())
        {
            auto daysStr = r["effective_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            effectiveDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["purchase_price_ratio"].isNull())
        {
            purchasePriceRatio_=std::make_shared<std::string>(r["purchase_price_ratio"].as<std::string>());
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
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 11 > r.size())
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
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            loanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            ownerId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            transferType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            settlementDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            effectiveDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            purchasePriceRatio_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
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
const std::string &LoanOwnerTransfer::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransfer::getId() const noexcept
{
    return id_;
}
void LoanOwnerTransfer::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanOwnerTransfer::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanOwnerTransfer::PrimaryKeyType & LoanOwnerTransfer::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanOwnerTransfer::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransfer::getExternalId() const noexcept
{
    return externalId_;
}
void LoanOwnerTransfer::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[1] = true;
}
void LoanOwnerTransfer::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[1] = true;
}
void LoanOwnerTransfer::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &LoanOwnerTransfer::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransfer::getLoanId() const noexcept
{
    return loanId_;
}
void LoanOwnerTransfer::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[2] = true;
}
void LoanOwnerTransfer::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[2] = true;
}

const std::string &LoanOwnerTransfer::getValueOfOwnerId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(ownerId_)
        return *ownerId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransfer::getOwnerId() const noexcept
{
    return ownerId_;
}
void LoanOwnerTransfer::setOwnerId(const std::string &pOwnerId) noexcept
{
    ownerId_ = std::make_shared<std::string>(pOwnerId);
    dirtyFlag_[3] = true;
}
void LoanOwnerTransfer::setOwnerId(std::string &&pOwnerId) noexcept
{
    ownerId_ = std::make_shared<std::string>(std::move(pOwnerId));
    dirtyFlag_[3] = true;
}

const int32_t &LoanOwnerTransfer::getValueOfTransferType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(transferType_)
        return *transferType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanOwnerTransfer::getTransferType() const noexcept
{
    return transferType_;
}
void LoanOwnerTransfer::setTransferType(const int32_t &pTransferType) noexcept
{
    transferType_ = std::make_shared<int32_t>(pTransferType);
    dirtyFlag_[4] = true;
}

const int32_t &LoanOwnerTransfer::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanOwnerTransfer::getStatus() const noexcept
{
    return status_;
}
void LoanOwnerTransfer::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[5] = true;
}

const ::trantor::Date &LoanOwnerTransfer::getValueOfSettlementDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(settlementDate_)
        return *settlementDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanOwnerTransfer::getSettlementDate() const noexcept
{
    return settlementDate_;
}
void LoanOwnerTransfer::setSettlementDate(const ::trantor::Date &pSettlementDate) noexcept
{
    settlementDate_ = std::make_shared<::trantor::Date>(pSettlementDate);
    dirtyFlag_[6] = true;
}
void LoanOwnerTransfer::setSettlementDateToNull() noexcept
{
    settlementDate_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &LoanOwnerTransfer::getValueOfEffectiveDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(effectiveDate_)
        return *effectiveDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanOwnerTransfer::getEffectiveDate() const noexcept
{
    return effectiveDate_;
}
void LoanOwnerTransfer::setEffectiveDate(const ::trantor::Date &pEffectiveDate) noexcept
{
    effectiveDate_ = std::make_shared<::trantor::Date>(pEffectiveDate);
    dirtyFlag_[7] = true;
}

const std::string &LoanOwnerTransfer::getValueOfPurchasePriceRatio() const noexcept
{
    static const std::string defaultValue = std::string();
    if(purchasePriceRatio_)
        return *purchasePriceRatio_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransfer::getPurchasePriceRatio() const noexcept
{
    return purchasePriceRatio_;
}
void LoanOwnerTransfer::setPurchasePriceRatio(const std::string &pPurchasePriceRatio) noexcept
{
    purchasePriceRatio_ = std::make_shared<std::string>(pPurchasePriceRatio);
    dirtyFlag_[8] = true;
}
void LoanOwnerTransfer::setPurchasePriceRatio(std::string &&pPurchasePriceRatio) noexcept
{
    purchasePriceRatio_ = std::make_shared<std::string>(std::move(pPurchasePriceRatio));
    dirtyFlag_[8] = true;
}

const std::string &LoanOwnerTransfer::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanOwnerTransfer::getCreatedBy() const noexcept
{
    return createdBy_;
}
void LoanOwnerTransfer::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[9] = true;
}
void LoanOwnerTransfer::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[9] = true;
}
void LoanOwnerTransfer::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[9] = true;
}

const ::trantor::Date &LoanOwnerTransfer::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanOwnerTransfer::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanOwnerTransfer::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[10] = true;
}

void LoanOwnerTransfer::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanOwnerTransfer::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "external_id",
        "loan_id",
        "owner_id",
        "transfer_type",
        "status",
        "settlement_date",
        "effective_date",
        "purchase_price_ratio",
        "created_by",
        "created_at"
    };
    return inCols;
}

void LoanOwnerTransfer::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getOwnerId())
        {
            binder << getValueOfOwnerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getSettlementDate())
        {
            binder << getValueOfSettlementDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getEffectiveDate())
        {
            binder << getValueOfEffectiveDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getPurchasePriceRatio())
        {
            binder << getValueOfPurchasePriceRatio();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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

const std::vector<std::string> LoanOwnerTransfer::updateColumns() const
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
    return ret;
}

void LoanOwnerTransfer::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getOwnerId())
        {
            binder << getValueOfOwnerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getSettlementDate())
        {
            binder << getValueOfSettlementDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getEffectiveDate())
        {
            binder << getValueOfEffectiveDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getPurchasePriceRatio())
        {
            binder << getValueOfPurchasePriceRatio();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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
