/**
 *  InterestRateSlab.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<InterestRateSlab> usage actually needs
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
namespace TlDamDb
{

class InterestRateSlab
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _chart_id;
        static const std::string _description;
        static const std::string _period_type;
        static const std::string _from_period;
        static const std::string _to_period;
        static const std::string _amount_range_from;
        static const std::string _amount_range_to;
        static const std::string _annual_interest_rate;
        static const std::string _currency_code;
        static const std::string _created_by;
        static const std::string _created_at;
        static const std::string _updated_by;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit InterestRateSlab(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    InterestRateSlab() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column business_id  */
    const std::string &getValueOfBusinessId() const noexcept;
    const std::shared_ptr<std::string> &getBusinessId() const noexcept;
    void setBusinessId(const std::string &pBusinessId) noexcept;
    void setBusinessId(std::string &&pBusinessId) noexcept;
    void setBusinessIdToNull() noexcept;

    /**  For column chart_id  */
    const std::string &getValueOfChartId() const noexcept;
    const std::shared_ptr<std::string> &getChartId() const noexcept;
    void setChartId(const std::string &pChartId) noexcept;
    void setChartId(std::string &&pChartId) noexcept;

    /**  For column description  */
    const std::string &getValueOfDescription() const noexcept;
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;
    void setDescriptionToNull() noexcept;

    /**  For column period_type  */
    const int32_t &getValueOfPeriodType() const noexcept;
    const std::shared_ptr<int32_t> &getPeriodType() const noexcept;
    void setPeriodType(const int32_t &pPeriodType) noexcept;
    void setPeriodTypeToNull() noexcept;

    /**  For column from_period  */
    const int32_t &getValueOfFromPeriod() const noexcept;
    const std::shared_ptr<int32_t> &getFromPeriod() const noexcept;
    void setFromPeriod(const int32_t &pFromPeriod) noexcept;
    void setFromPeriodToNull() noexcept;

    /**  For column to_period  */
    const int32_t &getValueOfToPeriod() const noexcept;
    const std::shared_ptr<int32_t> &getToPeriod() const noexcept;
    void setToPeriod(const int32_t &pToPeriod) noexcept;
    void setToPeriodToNull() noexcept;

    /**  For column amount_range_from  */
    const std::string &getValueOfAmountRangeFrom() const noexcept;
    const std::shared_ptr<std::string> &getAmountRangeFrom() const noexcept;
    void setAmountRangeFrom(const std::string &pAmountRangeFrom) noexcept;
    void setAmountRangeFrom(std::string &&pAmountRangeFrom) noexcept;
    void setAmountRangeFromToNull() noexcept;

    /**  For column amount_range_to  */
    const std::string &getValueOfAmountRangeTo() const noexcept;
    const std::shared_ptr<std::string> &getAmountRangeTo() const noexcept;
    void setAmountRangeTo(const std::string &pAmountRangeTo) noexcept;
    void setAmountRangeTo(std::string &&pAmountRangeTo) noexcept;
    void setAmountRangeToToNull() noexcept;

    /**  For column annual_interest_rate  */
    const std::string &getValueOfAnnualInterestRate() const noexcept;
    const std::shared_ptr<std::string> &getAnnualInterestRate() const noexcept;
    void setAnnualInterestRate(const std::string &pAnnualInterestRate) noexcept;
    void setAnnualInterestRate(std::string &&pAnnualInterestRate) noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column created_by  */
    const std::string &getValueOfCreatedBy() const noexcept;
    const std::shared_ptr<std::string> &getCreatedBy() const noexcept;
    void setCreatedBy(const std::string &pCreatedBy) noexcept;
    void setCreatedBy(std::string &&pCreatedBy) noexcept;
    void setCreatedByToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_by  */
    const std::string &getValueOfUpdatedBy() const noexcept;
    const std::shared_ptr<std::string> &getUpdatedBy() const noexcept;
    void setUpdatedBy(const std::string &pUpdatedBy) noexcept;
    void setUpdatedBy(std::string &&pUpdatedBy) noexcept;
    void setUpdatedByToNull() noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 15;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<InterestRateSlab>;
    friend drogon::orm::BaseBuilder<InterestRateSlab, true, true>;
    friend drogon::orm::BaseBuilder<InterestRateSlab, true, false>;
    friend drogon::orm::BaseBuilder<InterestRateSlab, false, true>;
    friend drogon::orm::BaseBuilder<InterestRateSlab, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<InterestRateSlab>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> chartId_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<int32_t> periodType_;
    std::shared_ptr<int32_t> fromPeriod_;
    std::shared_ptr<int32_t> toPeriod_;
    std::shared_ptr<std::string> amountRangeFrom_;
    std::shared_ptr<std::string> amountRangeTo_;
    std::shared_ptr<std::string> annualInterestRate_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<std::string> createdBy_;
    std::shared_ptr<::trantor::Date> createdAt_;
    std::shared_ptr<std::string> updatedBy_;
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
    bool dirtyFlag_[15]={ false };
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
            sql += "business_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "chart_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "period_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "from_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "to_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "amount_range_from,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "amount_range_to,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "annual_interest_rate,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[12])
        {
            needSelection=true;
        }
        if(dirtyFlag_[13])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[14])
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
        else
        {
            sql +="default,";
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
} // namespace TlDamDb
} // namespace drogon_model
