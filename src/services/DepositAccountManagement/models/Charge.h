/**
 *  Charge.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<Charge> usage actually needs
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

class Charge
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _name;
        static const std::string _currency_code;
        static const std::string _charge_applies_to;
        static const std::string _charge_time_type;
        static const std::string _charge_calculation_type;
        static const std::string _charge_payment_mode;
        static const std::string _amount;
        static const std::string _fee_on_month;
        static const std::string _fee_on_day;
        static const std::string _fee_interval;
        static const std::string _is_penalty;
        static const std::string _is_active;
        static const std::string _is_free_withdrawal;
        static const std::string _free_withdrawal_charge_frequency;
        static const std::string _min_cap;
        static const std::string _max_cap;
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

    explicit Charge(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    Charge() = default;

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

    /**  For column name  */
    const std::string &getValueOfName() const noexcept;
    const std::shared_ptr<std::string> &getName() const noexcept;
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column charge_applies_to  */
    const int32_t &getValueOfChargeAppliesTo() const noexcept;
    const std::shared_ptr<int32_t> &getChargeAppliesTo() const noexcept;
    void setChargeAppliesTo(const int32_t &pChargeAppliesTo) noexcept;

    /**  For column charge_time_type  */
    const int32_t &getValueOfChargeTimeType() const noexcept;
    const std::shared_ptr<int32_t> &getChargeTimeType() const noexcept;
    void setChargeTimeType(const int32_t &pChargeTimeType) noexcept;

    /**  For column charge_calculation_type  */
    const int32_t &getValueOfChargeCalculationType() const noexcept;
    const std::shared_ptr<int32_t> &getChargeCalculationType() const noexcept;
    void setChargeCalculationType(const int32_t &pChargeCalculationType) noexcept;

    /**  For column charge_payment_mode  */
    const int32_t &getValueOfChargePaymentMode() const noexcept;
    const std::shared_ptr<int32_t> &getChargePaymentMode() const noexcept;
    void setChargePaymentMode(const int32_t &pChargePaymentMode) noexcept;
    void setChargePaymentModeToNull() noexcept;

    /**  For column amount  */
    const std::string &getValueOfAmount() const noexcept;
    const std::shared_ptr<std::string> &getAmount() const noexcept;
    void setAmount(const std::string &pAmount) noexcept;
    void setAmount(std::string &&pAmount) noexcept;

    /**  For column fee_on_month  */
    const int32_t &getValueOfFeeOnMonth() const noexcept;
    const std::shared_ptr<int32_t> &getFeeOnMonth() const noexcept;
    void setFeeOnMonth(const int32_t &pFeeOnMonth) noexcept;
    void setFeeOnMonthToNull() noexcept;

    /**  For column fee_on_day  */
    const int32_t &getValueOfFeeOnDay() const noexcept;
    const std::shared_ptr<int32_t> &getFeeOnDay() const noexcept;
    void setFeeOnDay(const int32_t &pFeeOnDay) noexcept;
    void setFeeOnDayToNull() noexcept;

    /**  For column fee_interval  */
    const int32_t &getValueOfFeeInterval() const noexcept;
    const std::shared_ptr<int32_t> &getFeeInterval() const noexcept;
    void setFeeInterval(const int32_t &pFeeInterval) noexcept;
    void setFeeIntervalToNull() noexcept;

    /**  For column is_penalty  */
    const bool &getValueOfIsPenalty() const noexcept;
    const std::shared_ptr<bool> &getIsPenalty() const noexcept;
    void setIsPenalty(const bool &pIsPenalty) noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

    /**  For column is_free_withdrawal  */
    const bool &getValueOfIsFreeWithdrawal() const noexcept;
    const std::shared_ptr<bool> &getIsFreeWithdrawal() const noexcept;
    void setIsFreeWithdrawal(const bool &pIsFreeWithdrawal) noexcept;

    /**  For column free_withdrawal_charge_frequency  */
    const int32_t &getValueOfFreeWithdrawalChargeFrequency() const noexcept;
    const std::shared_ptr<int32_t> &getFreeWithdrawalChargeFrequency() const noexcept;
    void setFreeWithdrawalChargeFrequency(const int32_t &pFreeWithdrawalChargeFrequency) noexcept;
    void setFreeWithdrawalChargeFrequencyToNull() noexcept;

    /**  For column min_cap  */
    const std::string &getValueOfMinCap() const noexcept;
    const std::shared_ptr<std::string> &getMinCap() const noexcept;
    void setMinCap(const std::string &pMinCap) noexcept;
    void setMinCap(std::string &&pMinCap) noexcept;
    void setMinCapToNull() noexcept;

    /**  For column max_cap  */
    const std::string &getValueOfMaxCap() const noexcept;
    const std::shared_ptr<std::string> &getMaxCap() const noexcept;
    void setMaxCap(const std::string &pMaxCap) noexcept;
    void setMaxCap(std::string &&pMaxCap) noexcept;
    void setMaxCapToNull() noexcept;

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

    static size_t getColumnNumber() noexcept {  return 22;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<Charge>;
    friend drogon::orm::BaseBuilder<Charge, true, true>;
    friend drogon::orm::BaseBuilder<Charge, true, false>;
    friend drogon::orm::BaseBuilder<Charge, false, true>;
    friend drogon::orm::BaseBuilder<Charge, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Charge>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<int32_t> chargeAppliesTo_;
    std::shared_ptr<int32_t> chargeTimeType_;
    std::shared_ptr<int32_t> chargeCalculationType_;
    std::shared_ptr<int32_t> chargePaymentMode_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<int32_t> feeOnMonth_;
    std::shared_ptr<int32_t> feeOnDay_;
    std::shared_ptr<int32_t> feeInterval_;
    std::shared_ptr<bool> isPenalty_;
    std::shared_ptr<bool> isActive_;
    std::shared_ptr<bool> isFreeWithdrawal_;
    std::shared_ptr<int32_t> freeWithdrawalChargeFrequency_;
    std::shared_ptr<std::string> minCap_;
    std::shared_ptr<std::string> maxCap_;
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
    bool dirtyFlag_[22]={ false };
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
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        sql += "charge_applies_to,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        if(dirtyFlag_[5])
        {
            sql += "charge_time_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "charge_calculation_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "charge_payment_mode,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "fee_on_month,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "fee_on_day,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "fee_interval,";
            ++parametersCount;
        }
        sql += "is_penalty,";
        ++parametersCount;
        if(!dirtyFlag_[12])
        {
            needSelection=true;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        sql += "is_free_withdrawal,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        if(dirtyFlag_[15])
        {
            sql += "free_withdrawal_charge_frequency,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "min_cap,";
            ++parametersCount;
        }
        if(dirtyFlag_[17])
        {
            sql += "max_cap,";
            ++parametersCount;
        }
        if(dirtyFlag_[18])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[19])
        {
            needSelection=true;
        }
        if(dirtyFlag_[20])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[21])
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
