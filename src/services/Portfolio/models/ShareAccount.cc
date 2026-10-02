/**
 *  ShareAccount.cc
 *
 *  See ShareAccount.h for the hand-authored-subset note.
 *
 */

#include "ShareAccount.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ShareAccount::Cols::_id = "\"id\"";
const std::string ShareAccount::Cols::_account_no = "\"account_no\"";
const std::string ShareAccount::Cols::_external_id = "\"external_id\"";
const std::string ShareAccount::Cols::_client_id = "\"client_id\"";
const std::string ShareAccount::Cols::_group_id = "\"group_id\"";
const std::string ShareAccount::Cols::_product_id = "\"product_id\"";
const std::string ShareAccount::Cols::_currency_code = "\"currency_code\"";
const std::string ShareAccount::Cols::_submitted_date = "\"submitted_date\"";
const std::string ShareAccount::Cols::_submitted_by = "\"submitted_by\"";
const std::string ShareAccount::Cols::_approved_date = "\"approved_date\"";
const std::string ShareAccount::Cols::_approved_by = "\"approved_by\"";
const std::string ShareAccount::Cols::_activated_date = "\"activated_date\"";
const std::string ShareAccount::Cols::_rejected_date = "\"rejected_date\"";
const std::string ShareAccount::Cols::_closed_date = "\"closed_date\"";
const std::string ShareAccount::Cols::_status = "\"status\"";
const std::string ShareAccount::Cols::_requested_shares = "\"requested_shares\"";
const std::string ShareAccount::Cols::_approved_shares = "\"approved_shares\"";
const std::string ShareAccount::Cols::_lockin_period = "\"lockin_period\"";
const std::string ShareAccount::Cols::_lockin_period_frequency_type = "\"lockin_period_frequency_type\"";
const std::string ShareAccount::Cols::_created_at = "\"created_at\"";
const std::string ShareAccount::primaryKeyName = "id";
const bool ShareAccount::hasPrimaryKey = true;
const std::string ShareAccount::tableName = "\"share_account\"";

const std::vector<typename ShareAccount::MetaData> ShareAccount::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"account_no","std::string","character varying",20,0,0,1},
{"external_id","std::string","character varying",100,0,0,0},
{"client_id","std::string","uuid",0,0,0,0},
{"group_id","std::string","uuid",0,0,0,0},
{"product_id","std::string","uuid",0,0,0,1},
{"currency_code","std::string","character varying",3,0,0,1},
{"submitted_date","::trantor::Date","date",0,0,0,1},
{"submitted_by","std::string","uuid",0,0,0,0},
{"approved_date","::trantor::Date","date",0,0,0,0},
{"approved_by","std::string","uuid",0,0,0,0},
{"activated_date","::trantor::Date","date",0,0,0,0},
{"rejected_date","::trantor::Date","date",0,0,0,0},
{"closed_date","::trantor::Date","date",0,0,0,0},
{"status","int32_t","integer",4,0,0,1},
{"requested_shares","int64_t","bigint",8,0,0,1},
{"approved_shares","int64_t","bigint",8,0,0,1},
{"lockin_period","int32_t","integer",4,0,0,0},
{"lockin_period_frequency_type","int32_t","integer",4,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ShareAccount::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ShareAccount::ShareAccount(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["account_no"].isNull())
        {
            accountNo_=std::make_shared<std::string>(r["account_no"].as<std::string>());
        }
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["group_id"].isNull())
        {
            groupId_=std::make_shared<std::string>(r["group_id"].as<std::string>());
        }
        if(!r["product_id"].isNull())
        {
            productId_=std::make_shared<std::string>(r["product_id"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["submitted_date"].isNull())
        {
            auto daysStr = r["submitted_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["submitted_by"].isNull())
        {
            submittedBy_=std::make_shared<std::string>(r["submitted_by"].as<std::string>());
        }
        if(!r["approved_date"].isNull())
        {
            auto daysStr = r["approved_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            approvedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["approved_by"].isNull())
        {
            approvedBy_=std::make_shared<std::string>(r["approved_by"].as<std::string>());
        }
        if(!r["activated_date"].isNull())
        {
            auto daysStr = r["activated_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activatedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["rejected_date"].isNull())
        {
            auto daysStr = r["rejected_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rejectedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["closed_date"].isNull())
        {
            auto daysStr = r["closed_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["requested_shares"].isNull())
        {
            requestedShares_=std::make_shared<int64_t>(r["requested_shares"].as<int64_t>());
        }
        if(!r["approved_shares"].isNull())
        {
            approvedShares_=std::make_shared<int64_t>(r["approved_shares"].as<int64_t>());
        }
        if(!r["lockin_period"].isNull())
        {
            lockinPeriod_=std::make_shared<int32_t>(r["lockin_period"].as<int32_t>());
        }
        if(!r["lockin_period_frequency_type"].isNull())
        {
            lockinPeriodFrequencyType_=std::make_shared<int32_t>(r["lockin_period_frequency_type"].as<int32_t>());
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
        if(offset + 20 > r.size())
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
            accountNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            groupId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            productId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            submittedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            approvedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            approvedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activatedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rejectedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            requestedShares_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            approvedShares_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            lockinPeriod_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            lockinPeriodFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 19;
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
const std::string &ShareAccount::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getId() const noexcept
{
    return id_;
}
void ShareAccount::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ShareAccount::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ShareAccount::PrimaryKeyType & ShareAccount::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ShareAccount::getValueOfAccountNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountNo_)
        return *accountNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getAccountNo() const noexcept
{
    return accountNo_;
}
void ShareAccount::setAccountNo(const std::string &pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(pAccountNo);
    dirtyFlag_[1] = true;
}
void ShareAccount::setAccountNo(std::string &&pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(std::move(pAccountNo));
    dirtyFlag_[1] = true;
}

const std::string &ShareAccount::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getExternalId() const noexcept
{
    return externalId_;
}
void ShareAccount::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[2] = true;
}
void ShareAccount::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[2] = true;
}
void ShareAccount::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &ShareAccount::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getClientId() const noexcept
{
    return clientId_;
}
void ShareAccount::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[3] = true;
}
void ShareAccount::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[3] = true;
}
void ShareAccount::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[3] = true;
}

const std::string &ShareAccount::getValueOfGroupId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(groupId_)
        return *groupId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getGroupId() const noexcept
{
    return groupId_;
}
void ShareAccount::setGroupId(const std::string &pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(pGroupId);
    dirtyFlag_[4] = true;
}
void ShareAccount::setGroupId(std::string &&pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(std::move(pGroupId));
    dirtyFlag_[4] = true;
}
void ShareAccount::setGroupIdToNull() noexcept
{
    groupId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &ShareAccount::getValueOfProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(productId_)
        return *productId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getProductId() const noexcept
{
    return productId_;
}
void ShareAccount::setProductId(const std::string &pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(pProductId);
    dirtyFlag_[5] = true;
}
void ShareAccount::setProductId(std::string &&pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(std::move(pProductId));
    dirtyFlag_[5] = true;
}

const std::string &ShareAccount::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void ShareAccount::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[6] = true;
}
void ShareAccount::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[6] = true;
}

const ::trantor::Date &ShareAccount::getValueOfSubmittedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedDate_)
        return *submittedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareAccount::getSubmittedDate() const noexcept
{
    return submittedDate_;
}
void ShareAccount::setSubmittedDate(const ::trantor::Date &pSubmittedDate) noexcept
{
    submittedDate_ = std::make_shared<::trantor::Date>(pSubmittedDate);
    dirtyFlag_[7] = true;
}

const std::string &ShareAccount::getValueOfSubmittedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(submittedBy_)
        return *submittedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getSubmittedBy() const noexcept
{
    return submittedBy_;
}
void ShareAccount::setSubmittedBy(const std::string &pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(pSubmittedBy);
    dirtyFlag_[8] = true;
}
void ShareAccount::setSubmittedBy(std::string &&pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(std::move(pSubmittedBy));
    dirtyFlag_[8] = true;
}
void ShareAccount::setSubmittedByToNull() noexcept
{
    submittedBy_.reset();
    dirtyFlag_[8] = true;
}

const ::trantor::Date &ShareAccount::getValueOfApprovedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(approvedDate_)
        return *approvedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareAccount::getApprovedDate() const noexcept
{
    return approvedDate_;
}
void ShareAccount::setApprovedDate(const ::trantor::Date &pApprovedDate) noexcept
{
    approvedDate_ = std::make_shared<::trantor::Date>(pApprovedDate);
    dirtyFlag_[9] = true;
}
void ShareAccount::setApprovedDateToNull() noexcept
{
    approvedDate_.reset();
    dirtyFlag_[9] = true;
}

const std::string &ShareAccount::getValueOfApprovedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(approvedBy_)
        return *approvedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareAccount::getApprovedBy() const noexcept
{
    return approvedBy_;
}
void ShareAccount::setApprovedBy(const std::string &pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(pApprovedBy);
    dirtyFlag_[10] = true;
}
void ShareAccount::setApprovedBy(std::string &&pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(std::move(pApprovedBy));
    dirtyFlag_[10] = true;
}
void ShareAccount::setApprovedByToNull() noexcept
{
    approvedBy_.reset();
    dirtyFlag_[10] = true;
}

const ::trantor::Date &ShareAccount::getValueOfActivatedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(activatedDate_)
        return *activatedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareAccount::getActivatedDate() const noexcept
{
    return activatedDate_;
}
void ShareAccount::setActivatedDate(const ::trantor::Date &pActivatedDate) noexcept
{
    activatedDate_ = std::make_shared<::trantor::Date>(pActivatedDate);
    dirtyFlag_[11] = true;
}
void ShareAccount::setActivatedDateToNull() noexcept
{
    activatedDate_.reset();
    dirtyFlag_[11] = true;
}

const ::trantor::Date &ShareAccount::getValueOfRejectedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(rejectedDate_)
        return *rejectedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareAccount::getRejectedDate() const noexcept
{
    return rejectedDate_;
}
void ShareAccount::setRejectedDate(const ::trantor::Date &pRejectedDate) noexcept
{
    rejectedDate_ = std::make_shared<::trantor::Date>(pRejectedDate);
    dirtyFlag_[12] = true;
}
void ShareAccount::setRejectedDateToNull() noexcept
{
    rejectedDate_.reset();
    dirtyFlag_[12] = true;
}

const ::trantor::Date &ShareAccount::getValueOfClosedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(closedDate_)
        return *closedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareAccount::getClosedDate() const noexcept
{
    return closedDate_;
}
void ShareAccount::setClosedDate(const ::trantor::Date &pClosedDate) noexcept
{
    closedDate_ = std::make_shared<::trantor::Date>(pClosedDate);
    dirtyFlag_[13] = true;
}
void ShareAccount::setClosedDateToNull() noexcept
{
    closedDate_.reset();
    dirtyFlag_[13] = true;
}

const int32_t &ShareAccount::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareAccount::getStatus() const noexcept
{
    return status_;
}
void ShareAccount::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[14] = true;
}

const int64_t &ShareAccount::getValueOfRequestedShares() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(requestedShares_)
        return *requestedShares_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &ShareAccount::getRequestedShares() const noexcept
{
    return requestedShares_;
}
void ShareAccount::setRequestedShares(const int64_t &pRequestedShares) noexcept
{
    requestedShares_ = std::make_shared<int64_t>(pRequestedShares);
    dirtyFlag_[15] = true;
}

const int64_t &ShareAccount::getValueOfApprovedShares() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(approvedShares_)
        return *approvedShares_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &ShareAccount::getApprovedShares() const noexcept
{
    return approvedShares_;
}
void ShareAccount::setApprovedShares(const int64_t &pApprovedShares) noexcept
{
    approvedShares_ = std::make_shared<int64_t>(pApprovedShares);
    dirtyFlag_[16] = true;
}

const int32_t &ShareAccount::getValueOfLockinPeriod() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriod_)
        return *lockinPeriod_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareAccount::getLockinPeriod() const noexcept
{
    return lockinPeriod_;
}
void ShareAccount::setLockinPeriod(const int32_t &pLockinPeriod) noexcept
{
    lockinPeriod_ = std::make_shared<int32_t>(pLockinPeriod);
    dirtyFlag_[17] = true;
}
void ShareAccount::setLockinPeriodToNull() noexcept
{
    lockinPeriod_.reset();
    dirtyFlag_[17] = true;
}

const int32_t &ShareAccount::getValueOfLockinPeriodFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriodFrequencyType_)
        return *lockinPeriodFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareAccount::getLockinPeriodFrequencyType() const noexcept
{
    return lockinPeriodFrequencyType_;
}
void ShareAccount::setLockinPeriodFrequencyType(const int32_t &pLockinPeriodFrequencyType) noexcept
{
    lockinPeriodFrequencyType_ = std::make_shared<int32_t>(pLockinPeriodFrequencyType);
    dirtyFlag_[18] = true;
}
void ShareAccount::setLockinPeriodFrequencyTypeToNull() noexcept
{
    lockinPeriodFrequencyType_.reset();
    dirtyFlag_[18] = true;
}

const ::trantor::Date &ShareAccount::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareAccount::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ShareAccount::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[19] = true;
}

void ShareAccount::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ShareAccount::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "account_no",
        "external_id",
        "client_id",
        "group_id",
        "product_id",
        "currency_code",
        "submitted_date",
        "submitted_by",
        "approved_date",
        "approved_by",
        "activated_date",
        "rejected_date",
        "closed_date",
        "status",
        "requested_shares",
        "approved_shares",
        "lockin_period",
        "lockin_period_frequency_type",
        "created_at"
    };
    return inCols;
}

void ShareAccount::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getSubmittedDate())
        {
            binder << getValueOfSubmittedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getSubmittedBy())
        {
            binder << getValueOfSubmittedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getApprovedDate())
        {
            binder << getValueOfApprovedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getApprovedBy())
        {
            binder << getValueOfApprovedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getActivatedDate())
        {
            binder << getValueOfActivatedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getRejectedDate())
        {
            binder << getValueOfRejectedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getClosedDate())
        {
            binder << getValueOfClosedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getRequestedShares())
        {
            binder << getValueOfRequestedShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getApprovedShares())
        {
            binder << getValueOfApprovedShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getLockinPeriod())
        {
            binder << getValueOfLockinPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getLockinPeriodFrequencyType())
        {
            binder << getValueOfLockinPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
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

const std::vector<std::string> ShareAccount::updateColumns() const
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
    if(dirtyFlag_[15])
    {
        ret.push_back(getColumnName(15));
    }
    if(dirtyFlag_[16])
    {
        ret.push_back(getColumnName(16));
    }
    if(dirtyFlag_[17])
    {
        ret.push_back(getColumnName(17));
    }
    if(dirtyFlag_[18])
    {
        ret.push_back(getColumnName(18));
    }
    if(dirtyFlag_[19])
    {
        ret.push_back(getColumnName(19));
    }
    return ret;
}

void ShareAccount::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getSubmittedDate())
        {
            binder << getValueOfSubmittedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getSubmittedBy())
        {
            binder << getValueOfSubmittedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getApprovedDate())
        {
            binder << getValueOfApprovedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getApprovedBy())
        {
            binder << getValueOfApprovedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getActivatedDate())
        {
            binder << getValueOfActivatedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getRejectedDate())
        {
            binder << getValueOfRejectedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getClosedDate())
        {
            binder << getValueOfClosedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getRequestedShares())
        {
            binder << getValueOfRequestedShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getApprovedShares())
        {
            binder << getValueOfApprovedShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getLockinPeriod())
        {
            binder << getValueOfLockinPeriod();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getLockinPeriodFrequencyType())
        {
            binder << getValueOfLockinPeriodFrequencyType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
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
