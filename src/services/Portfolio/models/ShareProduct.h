/**
 *  ShareProduct.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<ShareProduct> usage actually needs
 *  (row-mapping + CRUD via Mapper/CoroMapper). The Json::Value constructors,
 *  updateByJson/updateByMasqueradedJson, validateJsonFor.../validJsonOfField
 *  and toJson/toString/toMasqueradedJson methods that a live
 *  `drogon_ctl create_model` run would also emit are intentionally omitted
 *  here since nothing in this codebase calls them; regenerate with
 *  `drogon_ctl create_model` against a live DB with this table if those are
 *  ever needed.
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace TlPortfolioDb
{

class ShareProduct
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _short_name;
        static const std::string _description;
        static const std::string _currency_code;
        static const std::string _currency_digits;
        static const std::string _total_shares;
        static const std::string _total_shares_to_be_issued;
        static const std::string _nominal_price;
        static const std::string _market_price;
        static const std::string _share_capital_type;
        static const std::string _minimum_shares;
        static const std::string _default_shares;
        static const std::string _maximum_shares;
        static const std::string _allow_dividends_for_inactive_clients;
        static const std::string _lockin_period;
        static const std::string _lockin_period_frequency_type;
        static const std::string _accounting_type;
        static const std::string _share_reference_account_id;
        static const std::string _share_suspense_account_id;
        static const std::string _share_equity_account_id;
        static const std::string _is_active;
        static const std::string _start_date;
        static const std::string _close_date;
        static const std::string _created_at;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit ShareProduct(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    ShareProduct() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column name  */
    const std::string &getValueOfName() const noexcept;
    const std::shared_ptr<std::string> &getName() const noexcept;
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column short_name  */
    const std::string &getValueOfShortName() const noexcept;
    const std::shared_ptr<std::string> &getShortName() const noexcept;
    void setShortName(const std::string &pShortName) noexcept;
    void setShortName(std::string &&pShortName) noexcept;

    /**  For column description  */
    const std::string &getValueOfDescription() const noexcept;
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;
    void setDescriptionToNull() noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column currency_digits  */
    const int32_t &getValueOfCurrencyDigits() const noexcept;
    const std::shared_ptr<int32_t> &getCurrencyDigits() const noexcept;
    void setCurrencyDigits(const int32_t &pCurrencyDigits) noexcept;

    /**  For column total_shares  */
    const int64_t &getValueOfTotalShares() const noexcept;
    const std::shared_ptr<int64_t> &getTotalShares() const noexcept;
    void setTotalShares(const int64_t &pTotalShares) noexcept;

    /**  For column total_shares_to_be_issued  */
    const int64_t &getValueOfTotalSharesToBeIssued() const noexcept;
    const std::shared_ptr<int64_t> &getTotalSharesToBeIssued() const noexcept;
    void setTotalSharesToBeIssued(const int64_t &pTotalSharesToBeIssued) noexcept;

    /**  For column nominal_price  */
    const std::string &getValueOfNominalPrice() const noexcept;
    const std::shared_ptr<std::string> &getNominalPrice() const noexcept;
    void setNominalPrice(const std::string &pNominalPrice) noexcept;
    void setNominalPrice(std::string &&pNominalPrice) noexcept;

    /**  For column market_price  */
    const std::string &getValueOfMarketPrice() const noexcept;
    const std::shared_ptr<std::string> &getMarketPrice() const noexcept;
    void setMarketPrice(const std::string &pMarketPrice) noexcept;
    void setMarketPrice(std::string &&pMarketPrice) noexcept;
    void setMarketPriceToNull() noexcept;

    /**  For column share_capital_type  */
    const int32_t &getValueOfShareCapitalType() const noexcept;
    const std::shared_ptr<int32_t> &getShareCapitalType() const noexcept;
    void setShareCapitalType(const int32_t &pShareCapitalType) noexcept;

    /**  For column minimum_shares  */
    const int64_t &getValueOfMinimumShares() const noexcept;
    const std::shared_ptr<int64_t> &getMinimumShares() const noexcept;
    void setMinimumShares(const int64_t &pMinimumShares) noexcept;
    void setMinimumSharesToNull() noexcept;

    /**  For column default_shares  */
    const int64_t &getValueOfDefaultShares() const noexcept;
    const std::shared_ptr<int64_t> &getDefaultShares() const noexcept;
    void setDefaultShares(const int64_t &pDefaultShares) noexcept;
    void setDefaultSharesToNull() noexcept;

    /**  For column maximum_shares  */
    const int64_t &getValueOfMaximumShares() const noexcept;
    const std::shared_ptr<int64_t> &getMaximumShares() const noexcept;
    void setMaximumShares(const int64_t &pMaximumShares) noexcept;
    void setMaximumSharesToNull() noexcept;

    /**  For column allow_dividends_for_inactive_clients  */
    const bool &getValueOfAllowDividendsForInactiveClients() const noexcept;
    const std::shared_ptr<bool> &getAllowDividendsForInactiveClients() const noexcept;
    void setAllowDividendsForInactiveClients(const bool &pAllowDividendsForInactiveClients) noexcept;

    /**  For column lockin_period  */
    const int32_t &getValueOfLockinPeriod() const noexcept;
    const std::shared_ptr<int32_t> &getLockinPeriod() const noexcept;
    void setLockinPeriod(const int32_t &pLockinPeriod) noexcept;
    void setLockinPeriodToNull() noexcept;

    /**  For column lockin_period_frequency_type  */
    const int32_t &getValueOfLockinPeriodFrequencyType() const noexcept;
    const std::shared_ptr<int32_t> &getLockinPeriodFrequencyType() const noexcept;
    void setLockinPeriodFrequencyType(const int32_t &pLockinPeriodFrequencyType) noexcept;
    void setLockinPeriodFrequencyTypeToNull() noexcept;

    /**  For column accounting_type  */
    const int32_t &getValueOfAccountingType() const noexcept;
    const std::shared_ptr<int32_t> &getAccountingType() const noexcept;
    void setAccountingType(const int32_t &pAccountingType) noexcept;

    /**  For column share_reference_account_id  */
    const std::string &getValueOfShareReferenceAccountId() const noexcept;
    const std::shared_ptr<std::string> &getShareReferenceAccountId() const noexcept;
    void setShareReferenceAccountId(const std::string &pShareReferenceAccountId) noexcept;
    void setShareReferenceAccountId(std::string &&pShareReferenceAccountId) noexcept;
    void setShareReferenceAccountIdToNull() noexcept;

    /**  For column share_suspense_account_id  */
    const std::string &getValueOfShareSuspenseAccountId() const noexcept;
    const std::shared_ptr<std::string> &getShareSuspenseAccountId() const noexcept;
    void setShareSuspenseAccountId(const std::string &pShareSuspenseAccountId) noexcept;
    void setShareSuspenseAccountId(std::string &&pShareSuspenseAccountId) noexcept;
    void setShareSuspenseAccountIdToNull() noexcept;

    /**  For column share_equity_account_id  */
    const std::string &getValueOfShareEquityAccountId() const noexcept;
    const std::shared_ptr<std::string> &getShareEquityAccountId() const noexcept;
    void setShareEquityAccountId(const std::string &pShareEquityAccountId) noexcept;
    void setShareEquityAccountId(std::string &&pShareEquityAccountId) noexcept;
    void setShareEquityAccountIdToNull() noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

    /**  For column start_date  */
    const ::trantor::Date &getValueOfStartDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getStartDate() const noexcept;
    void setStartDate(const ::trantor::Date &pStartDate) noexcept;
    void setStartDateToNull() noexcept;

    /**  For column close_date  */
    const ::trantor::Date &getValueOfCloseDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCloseDate() const noexcept;
    void setCloseDate(const ::trantor::Date &pCloseDate) noexcept;
    void setCloseDateToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 26;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<ShareProduct>;
    friend drogon::orm::BaseBuilder<ShareProduct, true, true>;
    friend drogon::orm::BaseBuilder<ShareProduct, true, false>;
    friend drogon::orm::BaseBuilder<ShareProduct, false, true>;
    friend drogon::orm::BaseBuilder<ShareProduct, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<ShareProduct>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> shortName_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<int32_t> currencyDigits_;
    std::shared_ptr<int64_t> totalShares_;
    std::shared_ptr<int64_t> totalSharesToBeIssued_;
    std::shared_ptr<std::string> nominalPrice_;
    std::shared_ptr<std::string> marketPrice_;
    std::shared_ptr<int32_t> shareCapitalType_;
    std::shared_ptr<int64_t> minimumShares_;
    std::shared_ptr<int64_t> defaultShares_;
    std::shared_ptr<int64_t> maximumShares_;
    std::shared_ptr<bool> allowDividendsForInactiveClients_;
    std::shared_ptr<int32_t> lockinPeriod_;
    std::shared_ptr<int32_t> lockinPeriodFrequencyType_;
    std::shared_ptr<int32_t> accountingType_;
    std::shared_ptr<std::string> shareReferenceAccountId_;
    std::shared_ptr<std::string> shareSuspenseAccountId_;
    std::shared_ptr<std::string> shareEquityAccountId_;
    std::shared_ptr<bool> isActive_;
    std::shared_ptr<::trantor::Date> startDate_;
    std::shared_ptr<::trantor::Date> closeDate_;
    std::shared_ptr<::trantor::Date> createdAt_;
    std::shared_ptr<::trantor::Date> updatedAt_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[26]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
        sql += "id,";
        ++parametersCount;
        if(!dirtyFlag_[0])
        {
            needSelection=true;
        }
        if(dirtyFlag_[1])
        {
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "short_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        sql += "currency_digits,";
        ++parametersCount;
        if(!dirtyFlag_[5])
        {
            needSelection=true;
        }
        if(dirtyFlag_[6])
        {
            sql += "total_shares,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "total_shares_to_be_issued,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "nominal_price,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "market_price,";
            ++parametersCount;
        }
        sql += "share_capital_type,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        if(dirtyFlag_[11])
        {
            sql += "minimum_shares,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "default_shares,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "maximum_shares,";
            ++parametersCount;
        }
        sql += "allow_dividends_for_inactive_clients,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        if(dirtyFlag_[15])
        {
            sql += "lockin_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "lockin_period_frequency_type,";
            ++parametersCount;
        }
        sql += "accounting_type,";
        ++parametersCount;
        if(!dirtyFlag_[17])
        {
            needSelection=true;
        }
        if(dirtyFlag_[18])
        {
            sql += "share_reference_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[19])
        {
            sql += "share_suspense_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[20])
        {
            sql += "share_equity_account_id,";
            ++parametersCount;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[21])
        {
            needSelection=true;
        }
        if(dirtyFlag_[22])
        {
            sql += "start_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[23])
        {
            sql += "close_date,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[24])
        {
            needSelection=true;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[25])
        {
            needSelection=true;
        }
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        if(dirtyFlag_[0])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[1])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[2])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[4])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[5])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[6])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[7])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[8])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[11])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[12])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[13])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[14])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[16])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[17])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[18])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[19])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[20])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[21])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[22])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[23])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[24])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[25])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace TlPortfolioDb
} // namespace drogon_model
