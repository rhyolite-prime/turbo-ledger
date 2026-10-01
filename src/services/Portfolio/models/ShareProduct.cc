/**
 *  ShareProduct.cc
 *
 *  See ShareProduct.h for the hand-authored-subset note.
 *
 */

#include "ShareProduct.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ShareProduct::Cols::_id = "\"id\"";
const std::string ShareProduct::Cols::_name = "\"name\"";
const std::string ShareProduct::Cols::_short_name = "\"short_name\"";
const std::string ShareProduct::Cols::_description = "\"description\"";
const std::string ShareProduct::Cols::_currency_code = "\"currency_code\"";
const std::string ShareProduct::Cols::_currency_digits = "\"currency_digits\"";
const std::string ShareProduct::Cols::_total_shares = "\"total_shares\"";
const std::string ShareProduct::Cols::_total_shares_to_be_issued = "\"total_shares_to_be_issued\"";
const std::string ShareProduct::Cols::_nominal_price = "\"nominal_price\"";
const std::string ShareProduct::Cols::_market_price = "\"market_price\"";
const std::string ShareProduct::Cols::_share_capital_type = "\"share_capital_type\"";
const std::string ShareProduct::Cols::_minimum_shares = "\"minimum_shares\"";
const std::string ShareProduct::Cols::_default_shares = "\"default_shares\"";
const std::string ShareProduct::Cols::_maximum_shares = "\"maximum_shares\"";
const std::string ShareProduct::Cols::_allow_dividends_for_inactive_clients = "\"allow_dividends_for_inactive_clients\"";
const std::string ShareProduct::Cols::_lockin_period = "\"lockin_period\"";
const std::string ShareProduct::Cols::_lockin_period_frequency_type = "\"lockin_period_frequency_type\"";
const std::string ShareProduct::Cols::_accounting_type = "\"accounting_type\"";
const std::string ShareProduct::Cols::_share_reference_account_id = "\"share_reference_account_id\"";
const std::string ShareProduct::Cols::_share_suspense_account_id = "\"share_suspense_account_id\"";
const std::string ShareProduct::Cols::_share_equity_account_id = "\"share_equity_account_id\"";
const std::string ShareProduct::Cols::_is_active = "\"is_active\"";
const std::string ShareProduct::Cols::_start_date = "\"start_date\"";
const std::string ShareProduct::Cols::_close_date = "\"close_date\"";
const std::string ShareProduct::Cols::_created_at = "\"created_at\"";
const std::string ShareProduct::Cols::_updated_at = "\"updated_at\"";
const std::string ShareProduct::primaryKeyName = "id";
const bool ShareProduct::hasPrimaryKey = true;
const std::string ShareProduct::tableName = "\"share_product\"";

const std::vector<typename ShareProduct::MetaData> ShareProduct::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",100,0,0,1},
{"short_name","std::string","character varying",4,0,0,1},
{"description","std::string","text",0,0,0,0},
{"currency_code","std::string","character varying",3,0,0,1},
{"currency_digits","int32_t","integer",4,0,0,1},
{"total_shares","int64_t","bigint",8,0,0,1},
{"total_shares_to_be_issued","int64_t","bigint",8,0,0,1},
{"nominal_price","std::string","numeric",0,0,0,1},
{"market_price","std::string","numeric",0,0,0,0},
{"share_capital_type","int32_t","integer",4,0,0,1},
{"minimum_shares","int64_t","bigint",8,0,0,0},
{"default_shares","int64_t","bigint",8,0,0,0},
{"maximum_shares","int64_t","bigint",8,0,0,0},
{"allow_dividends_for_inactive_clients","bool","boolean",1,0,0,1},
{"lockin_period","int32_t","integer",4,0,0,0},
{"lockin_period_frequency_type","int32_t","integer",4,0,0,0},
{"accounting_type","int32_t","integer",4,0,0,1},
{"share_reference_account_id","std::string","uuid",0,0,0,0},
{"share_suspense_account_id","std::string","uuid",0,0,0,0},
{"share_equity_account_id","std::string","uuid",0,0,0,0},
{"is_active","bool","boolean",1,0,0,1},
{"start_date","::trantor::Date","date",0,0,0,0},
{"close_date","::trantor::Date","date",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ShareProduct::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ShareProduct::ShareProduct(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["short_name"].isNull())
        {
            shortName_=std::make_shared<std::string>(r["short_name"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["currency_digits"].isNull())
        {
            currencyDigits_=std::make_shared<int32_t>(r["currency_digits"].as<int32_t>());
        }
        if(!r["total_shares"].isNull())
        {
            totalShares_=std::make_shared<int64_t>(r["total_shares"].as<int64_t>());
        }
        if(!r["total_shares_to_be_issued"].isNull())
        {
            totalSharesToBeIssued_=std::make_shared<int64_t>(r["total_shares_to_be_issued"].as<int64_t>());
        }
        if(!r["nominal_price"].isNull())
        {
            nominalPrice_=std::make_shared<std::string>(r["nominal_price"].as<std::string>());
        }
        if(!r["market_price"].isNull())
        {
            marketPrice_=std::make_shared<std::string>(r["market_price"].as<std::string>());
        }
        if(!r["share_capital_type"].isNull())
        {
            shareCapitalType_=std::make_shared<int32_t>(r["share_capital_type"].as<int32_t>());
        }
        if(!r["minimum_shares"].isNull())
        {
            minimumShares_=std::make_shared<int64_t>(r["minimum_shares"].as<int64_t>());
        }
        if(!r["default_shares"].isNull())
        {
            defaultShares_=std::make_shared<int64_t>(r["default_shares"].as<int64_t>());
        }
        if(!r["maximum_shares"].isNull())
        {
            maximumShares_=std::make_shared<int64_t>(r["maximum_shares"].as<int64_t>());
        }
        if(!r["allow_dividends_for_inactive_clients"].isNull())
        {
            allowDividendsForInactiveClients_=std::make_shared<bool>(r["allow_dividends_for_inactive_clients"].as<bool>());
        }
        if(!r["lockin_period"].isNull())
        {
            lockinPeriod_=std::make_shared<int32_t>(r["lockin_period"].as<int32_t>());
        }
        if(!r["lockin_period_frequency_type"].isNull())
        {
            lockinPeriodFrequencyType_=std::make_shared<int32_t>(r["lockin_period_frequency_type"].as<int32_t>());
        }
        if(!r["accounting_type"].isNull())
        {
            accountingType_=std::make_shared<int32_t>(r["accounting_type"].as<int32_t>());
        }
        if(!r["share_reference_account_id"].isNull())
        {
            shareReferenceAccountId_=std::make_shared<std::string>(r["share_reference_account_id"].as<std::string>());
        }
        if(!r["share_suspense_account_id"].isNull())
        {
            shareSuspenseAccountId_=std::make_shared<std::string>(r["share_suspense_account_id"].as<std::string>());
        }
        if(!r["share_equity_account_id"].isNull())
        {
            shareEquityAccountId_=std::make_shared<std::string>(r["share_equity_account_id"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["start_date"].isNull())
        {
            auto daysStr = r["start_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["close_date"].isNull())
        {
            auto daysStr = r["close_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closeDate_=std::make_shared<::trantor::Date>(t*1000000);
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
        if(offset + 26 > r.size())
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
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            shortName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            currencyDigits_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            totalShares_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            totalSharesToBeIssued_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            nominalPrice_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            marketPrice_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            shareCapitalType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            minimumShares_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            defaultShares_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            maximumShares_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            allowDividendsForInactiveClients_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            lockinPeriod_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            lockinPeriodFrequencyType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            accountingType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            shareReferenceAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            shareSuspenseAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            shareEquityAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 21;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closeDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 24;
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
        index = offset + 25;
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
const std::string &ShareProduct::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getId() const noexcept
{
    return id_;
}
void ShareProduct::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ShareProduct::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ShareProduct::PrimaryKeyType & ShareProduct::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ShareProduct::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getName() const noexcept
{
    return name_;
}
void ShareProduct::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void ShareProduct::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}

const std::string &ShareProduct::getValueOfShortName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shortName_)
        return *shortName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getShortName() const noexcept
{
    return shortName_;
}
void ShareProduct::setShortName(const std::string &pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(pShortName);
    dirtyFlag_[2] = true;
}
void ShareProduct::setShortName(std::string &&pShortName) noexcept
{
    shortName_ = std::make_shared<std::string>(std::move(pShortName));
    dirtyFlag_[2] = true;
}

const std::string &ShareProduct::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getDescription() const noexcept
{
    return description_;
}
void ShareProduct::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void ShareProduct::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void ShareProduct::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const std::string &ShareProduct::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void ShareProduct::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[4] = true;
}
void ShareProduct::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[4] = true;
}

const int32_t &ShareProduct::getValueOfCurrencyDigits() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(currencyDigits_)
        return *currencyDigits_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareProduct::getCurrencyDigits() const noexcept
{
    return currencyDigits_;
}
void ShareProduct::setCurrencyDigits(const int32_t &pCurrencyDigits) noexcept
{
    currencyDigits_ = std::make_shared<int32_t>(pCurrencyDigits);
    dirtyFlag_[5] = true;
}

const int64_t &ShareProduct::getValueOfTotalShares() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(totalShares_)
        return *totalShares_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &ShareProduct::getTotalShares() const noexcept
{
    return totalShares_;
}
void ShareProduct::setTotalShares(const int64_t &pTotalShares) noexcept
{
    totalShares_ = std::make_shared<int64_t>(pTotalShares);
    dirtyFlag_[6] = true;
}

const int64_t &ShareProduct::getValueOfTotalSharesToBeIssued() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(totalSharesToBeIssued_)
        return *totalSharesToBeIssued_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &ShareProduct::getTotalSharesToBeIssued() const noexcept
{
    return totalSharesToBeIssued_;
}
void ShareProduct::setTotalSharesToBeIssued(const int64_t &pTotalSharesToBeIssued) noexcept
{
    totalSharesToBeIssued_ = std::make_shared<int64_t>(pTotalSharesToBeIssued);
    dirtyFlag_[7] = true;
}

const std::string &ShareProduct::getValueOfNominalPrice() const noexcept
{
    static const std::string defaultValue = std::string();
    if(nominalPrice_)
        return *nominalPrice_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getNominalPrice() const noexcept
{
    return nominalPrice_;
}
void ShareProduct::setNominalPrice(const std::string &pNominalPrice) noexcept
{
    nominalPrice_ = std::make_shared<std::string>(pNominalPrice);
    dirtyFlag_[8] = true;
}
void ShareProduct::setNominalPrice(std::string &&pNominalPrice) noexcept
{
    nominalPrice_ = std::make_shared<std::string>(std::move(pNominalPrice));
    dirtyFlag_[8] = true;
}

const std::string &ShareProduct::getValueOfMarketPrice() const noexcept
{
    static const std::string defaultValue = std::string();
    if(marketPrice_)
        return *marketPrice_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getMarketPrice() const noexcept
{
    return marketPrice_;
}
void ShareProduct::setMarketPrice(const std::string &pMarketPrice) noexcept
{
    marketPrice_ = std::make_shared<std::string>(pMarketPrice);
    dirtyFlag_[9] = true;
}
void ShareProduct::setMarketPrice(std::string &&pMarketPrice) noexcept
{
    marketPrice_ = std::make_shared<std::string>(std::move(pMarketPrice));
    dirtyFlag_[9] = true;
}
void ShareProduct::setMarketPriceToNull() noexcept
{
    marketPrice_.reset();
    dirtyFlag_[9] = true;
}

const int32_t &ShareProduct::getValueOfShareCapitalType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(shareCapitalType_)
        return *shareCapitalType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareProduct::getShareCapitalType() const noexcept
{
    return shareCapitalType_;
}
void ShareProduct::setShareCapitalType(const int32_t &pShareCapitalType) noexcept
{
    shareCapitalType_ = std::make_shared<int32_t>(pShareCapitalType);
    dirtyFlag_[10] = true;
}

const int64_t &ShareProduct::getValueOfMinimumShares() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(minimumShares_)
        return *minimumShares_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &ShareProduct::getMinimumShares() const noexcept
{
    return minimumShares_;
}
void ShareProduct::setMinimumShares(const int64_t &pMinimumShares) noexcept
{
    minimumShares_ = std::make_shared<int64_t>(pMinimumShares);
    dirtyFlag_[11] = true;
}
void ShareProduct::setMinimumSharesToNull() noexcept
{
    minimumShares_.reset();
    dirtyFlag_[11] = true;
}

const int64_t &ShareProduct::getValueOfDefaultShares() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(defaultShares_)
        return *defaultShares_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &ShareProduct::getDefaultShares() const noexcept
{
    return defaultShares_;
}
void ShareProduct::setDefaultShares(const int64_t &pDefaultShares) noexcept
{
    defaultShares_ = std::make_shared<int64_t>(pDefaultShares);
    dirtyFlag_[12] = true;
}
void ShareProduct::setDefaultSharesToNull() noexcept
{
    defaultShares_.reset();
    dirtyFlag_[12] = true;
}

const int64_t &ShareProduct::getValueOfMaximumShares() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(maximumShares_)
        return *maximumShares_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &ShareProduct::getMaximumShares() const noexcept
{
    return maximumShares_;
}
void ShareProduct::setMaximumShares(const int64_t &pMaximumShares) noexcept
{
    maximumShares_ = std::make_shared<int64_t>(pMaximumShares);
    dirtyFlag_[13] = true;
}
void ShareProduct::setMaximumSharesToNull() noexcept
{
    maximumShares_.reset();
    dirtyFlag_[13] = true;
}

const bool &ShareProduct::getValueOfAllowDividendsForInactiveClients() const noexcept
{
    static const bool defaultValue = bool();
    if(allowDividendsForInactiveClients_)
        return *allowDividendsForInactiveClients_;
    return defaultValue;
}
const std::shared_ptr<bool> &ShareProduct::getAllowDividendsForInactiveClients() const noexcept
{
    return allowDividendsForInactiveClients_;
}
void ShareProduct::setAllowDividendsForInactiveClients(const bool &pAllowDividendsForInactiveClients) noexcept
{
    allowDividendsForInactiveClients_ = std::make_shared<bool>(pAllowDividendsForInactiveClients);
    dirtyFlag_[14] = true;
}

const int32_t &ShareProduct::getValueOfLockinPeriod() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriod_)
        return *lockinPeriod_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareProduct::getLockinPeriod() const noexcept
{
    return lockinPeriod_;
}
void ShareProduct::setLockinPeriod(const int32_t &pLockinPeriod) noexcept
{
    lockinPeriod_ = std::make_shared<int32_t>(pLockinPeriod);
    dirtyFlag_[15] = true;
}
void ShareProduct::setLockinPeriodToNull() noexcept
{
    lockinPeriod_.reset();
    dirtyFlag_[15] = true;
}

const int32_t &ShareProduct::getValueOfLockinPeriodFrequencyType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(lockinPeriodFrequencyType_)
        return *lockinPeriodFrequencyType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareProduct::getLockinPeriodFrequencyType() const noexcept
{
    return lockinPeriodFrequencyType_;
}
void ShareProduct::setLockinPeriodFrequencyType(const int32_t &pLockinPeriodFrequencyType) noexcept
{
    lockinPeriodFrequencyType_ = std::make_shared<int32_t>(pLockinPeriodFrequencyType);
    dirtyFlag_[16] = true;
}
void ShareProduct::setLockinPeriodFrequencyTypeToNull() noexcept
{
    lockinPeriodFrequencyType_.reset();
    dirtyFlag_[16] = true;
}

const int32_t &ShareProduct::getValueOfAccountingType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(accountingType_)
        return *accountingType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ShareProduct::getAccountingType() const noexcept
{
    return accountingType_;
}
void ShareProduct::setAccountingType(const int32_t &pAccountingType) noexcept
{
    accountingType_ = std::make_shared<int32_t>(pAccountingType);
    dirtyFlag_[17] = true;
}

const std::string &ShareProduct::getValueOfShareReferenceAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareReferenceAccountId_)
        return *shareReferenceAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getShareReferenceAccountId() const noexcept
{
    return shareReferenceAccountId_;
}
void ShareProduct::setShareReferenceAccountId(const std::string &pShareReferenceAccountId) noexcept
{
    shareReferenceAccountId_ = std::make_shared<std::string>(pShareReferenceAccountId);
    dirtyFlag_[18] = true;
}
void ShareProduct::setShareReferenceAccountId(std::string &&pShareReferenceAccountId) noexcept
{
    shareReferenceAccountId_ = std::make_shared<std::string>(std::move(pShareReferenceAccountId));
    dirtyFlag_[18] = true;
}
void ShareProduct::setShareReferenceAccountIdToNull() noexcept
{
    shareReferenceAccountId_.reset();
    dirtyFlag_[18] = true;
}

const std::string &ShareProduct::getValueOfShareSuspenseAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareSuspenseAccountId_)
        return *shareSuspenseAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getShareSuspenseAccountId() const noexcept
{
    return shareSuspenseAccountId_;
}
void ShareProduct::setShareSuspenseAccountId(const std::string &pShareSuspenseAccountId) noexcept
{
    shareSuspenseAccountId_ = std::make_shared<std::string>(pShareSuspenseAccountId);
    dirtyFlag_[19] = true;
}
void ShareProduct::setShareSuspenseAccountId(std::string &&pShareSuspenseAccountId) noexcept
{
    shareSuspenseAccountId_ = std::make_shared<std::string>(std::move(pShareSuspenseAccountId));
    dirtyFlag_[19] = true;
}
void ShareProduct::setShareSuspenseAccountIdToNull() noexcept
{
    shareSuspenseAccountId_.reset();
    dirtyFlag_[19] = true;
}

const std::string &ShareProduct::getValueOfShareEquityAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareEquityAccountId_)
        return *shareEquityAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ShareProduct::getShareEquityAccountId() const noexcept
{
    return shareEquityAccountId_;
}
void ShareProduct::setShareEquityAccountId(const std::string &pShareEquityAccountId) noexcept
{
    shareEquityAccountId_ = std::make_shared<std::string>(pShareEquityAccountId);
    dirtyFlag_[20] = true;
}
void ShareProduct::setShareEquityAccountId(std::string &&pShareEquityAccountId) noexcept
{
    shareEquityAccountId_ = std::make_shared<std::string>(std::move(pShareEquityAccountId));
    dirtyFlag_[20] = true;
}
void ShareProduct::setShareEquityAccountIdToNull() noexcept
{
    shareEquityAccountId_.reset();
    dirtyFlag_[20] = true;
}

const bool &ShareProduct::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &ShareProduct::getIsActive() const noexcept
{
    return isActive_;
}
void ShareProduct::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[21] = true;
}

const ::trantor::Date &ShareProduct::getValueOfStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDate_)
        return *startDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareProduct::getStartDate() const noexcept
{
    return startDate_;
}
void ShareProduct::setStartDate(const ::trantor::Date &pStartDate) noexcept
{
    startDate_ = std::make_shared<::trantor::Date>(pStartDate);
    dirtyFlag_[22] = true;
}
void ShareProduct::setStartDateToNull() noexcept
{
    startDate_.reset();
    dirtyFlag_[22] = true;
}

const ::trantor::Date &ShareProduct::getValueOfCloseDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(closeDate_)
        return *closeDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareProduct::getCloseDate() const noexcept
{
    return closeDate_;
}
void ShareProduct::setCloseDate(const ::trantor::Date &pCloseDate) noexcept
{
    closeDate_ = std::make_shared<::trantor::Date>(pCloseDate);
    dirtyFlag_[23] = true;
}
void ShareProduct::setCloseDateToNull() noexcept
{
    closeDate_.reset();
    dirtyFlag_[23] = true;
}

const ::trantor::Date &ShareProduct::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareProduct::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ShareProduct::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[24] = true;
}

const ::trantor::Date &ShareProduct::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ShareProduct::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void ShareProduct::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[25] = true;
}

void ShareProduct::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ShareProduct::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "short_name",
        "description",
        "currency_code",
        "currency_digits",
        "total_shares",
        "total_shares_to_be_issued",
        "nominal_price",
        "market_price",
        "share_capital_type",
        "minimum_shares",
        "default_shares",
        "maximum_shares",
        "allow_dividends_for_inactive_clients",
        "lockin_period",
        "lockin_period_frequency_type",
        "accounting_type",
        "share_reference_account_id",
        "share_suspense_account_id",
        "share_equity_account_id",
        "is_active",
        "start_date",
        "close_date",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void ShareProduct::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getShortName())
        {
            binder << getValueOfShortName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getCurrencyDigits())
        {
            binder << getValueOfCurrencyDigits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getTotalShares())
        {
            binder << getValueOfTotalShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getTotalSharesToBeIssued())
        {
            binder << getValueOfTotalSharesToBeIssued();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getNominalPrice())
        {
            binder << getValueOfNominalPrice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getMarketPrice())
        {
            binder << getValueOfMarketPrice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getShareCapitalType())
        {
            binder << getValueOfShareCapitalType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getMinimumShares())
        {
            binder << getValueOfMinimumShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getDefaultShares())
        {
            binder << getValueOfDefaultShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getMaximumShares())
        {
            binder << getValueOfMaximumShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getAllowDividendsForInactiveClients())
        {
            binder << getValueOfAllowDividendsForInactiveClients();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
    {
        if(getAccountingType())
        {
            binder << getValueOfAccountingType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getShareReferenceAccountId())
        {
            binder << getValueOfShareReferenceAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getShareSuspenseAccountId())
        {
            binder << getValueOfShareSuspenseAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getShareEquityAccountId())
        {
            binder << getValueOfShareEquityAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
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
    if(dirtyFlag_[22])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getCloseDate())
        {
            binder << getValueOfCloseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
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
    if(dirtyFlag_[25])
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

const std::vector<std::string> ShareProduct::updateColumns() const
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
    if(dirtyFlag_[20])
    {
        ret.push_back(getColumnName(20));
    }
    if(dirtyFlag_[21])
    {
        ret.push_back(getColumnName(21));
    }
    if(dirtyFlag_[22])
    {
        ret.push_back(getColumnName(22));
    }
    if(dirtyFlag_[23])
    {
        ret.push_back(getColumnName(23));
    }
    if(dirtyFlag_[24])
    {
        ret.push_back(getColumnName(24));
    }
    if(dirtyFlag_[25])
    {
        ret.push_back(getColumnName(25));
    }
    return ret;
}

void ShareProduct::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getShortName())
        {
            binder << getValueOfShortName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getCurrencyDigits())
        {
            binder << getValueOfCurrencyDigits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getTotalShares())
        {
            binder << getValueOfTotalShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getTotalSharesToBeIssued())
        {
            binder << getValueOfTotalSharesToBeIssued();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getNominalPrice())
        {
            binder << getValueOfNominalPrice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getMarketPrice())
        {
            binder << getValueOfMarketPrice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getShareCapitalType())
        {
            binder << getValueOfShareCapitalType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getMinimumShares())
        {
            binder << getValueOfMinimumShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getDefaultShares())
        {
            binder << getValueOfDefaultShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getMaximumShares())
        {
            binder << getValueOfMaximumShares();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getAllowDividendsForInactiveClients())
        {
            binder << getValueOfAllowDividendsForInactiveClients();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
    {
        if(getAccountingType())
        {
            binder << getValueOfAccountingType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getShareReferenceAccountId())
        {
            binder << getValueOfShareReferenceAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getShareSuspenseAccountId())
        {
            binder << getValueOfShareSuspenseAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getShareEquityAccountId())
        {
            binder << getValueOfShareEquityAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
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
    if(dirtyFlag_[22])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getCloseDate())
        {
            binder << getValueOfCloseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
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
    if(dirtyFlag_[25])
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
