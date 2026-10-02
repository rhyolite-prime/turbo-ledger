/**
 *  SavingsAccountCharge.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<SavingsAccountCharge> usage actually needs
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

class SavingsAccountCharge
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _savings_account_id;
        static const std::string _charge_id;
        static const std::string _charge_time_type;
        static const std::string _due_date;
        static const std::string _fee_interval;
        static const std::string _amount;
        static const std::string _amount_paid_derived;
        static const std::string _amount_waived_derived;
        static const std::string _amount_outstanding_derived;
        static const std::string _is_paid_derived;
        static const std::string _is_waived;
        static const std::string _is_active;
        static const std::string _inactivated_on_date;
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

    explicit SavingsAccountCharge(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    SavingsAccountCharge() = default;

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

    /**  For column savings_account_id  */
    const std::string &getValueOfSavingsAccountId() const noexcept;
    const std::shared_ptr<std::string> &getSavingsAccountId() const noexcept;
    void setSavingsAccountId(const std::string &pSavingsAccountId) noexcept;
    void setSavingsAccountId(std::string &&pSavingsAccountId) noexcept;

    /**  For column charge_id  */
    const std::string &getValueOfChargeId() const noexcept;
    const std::shared_ptr<std::string> &getChargeId() const noexcept;
    void setChargeId(const std::string &pChargeId) noexcept;
    void setChargeId(std::string &&pChargeId) noexcept;

    /**  For column charge_time_type  */
    const int32_t &getValueOfChargeTimeType() const noexcept;
    const std::shared_ptr<int32_t> &getChargeTimeType() const noexcept;
    void setChargeTimeType(const int32_t &pChargeTimeType) noexcept;

    /**  For column due_date  */
    const ::trantor::Date &getValueOfDueDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getDueDate() const noexcept;
    void setDueDate(const ::trantor::Date &pDueDate) noexcept;
    void setDueDateToNull() noexcept;

    /**  For column fee_interval  */
    const int32_t &getValueOfFeeInterval() const noexcept;
    const std::shared_ptr<int32_t> &getFeeInterval() const noexcept;
    void setFeeInterval(const int32_t &pFeeInterval) noexcept;
    void setFeeIntervalToNull() noexcept;

    /**  For column amount  */
    const std::string &getValueOfAmount() const noexcept;
    const std::shared_ptr<std::string> &getAmount() const noexcept;
    void setAmount(const std::string &pAmount) noexcept;
    void setAmount(std::string &&pAmount) noexcept;

    /**  For column amount_paid_derived  */
    const std::string &getValueOfAmountPaidDerived() const noexcept;
    const std::shared_ptr<std::string> &getAmountPaidDerived() const noexcept;
    void setAmountPaidDerived(const std::string &pAmountPaidDerived) noexcept;
    void setAmountPaidDerived(std::string &&pAmountPaidDerived) noexcept;

    /**  For column amount_waived_derived  */
    const std::string &getValueOfAmountWaivedDerived() const noexcept;
    const std::shared_ptr<std::string> &getAmountWaivedDerived() const noexcept;
    void setAmountWaivedDerived(const std::string &pAmountWaivedDerived) noexcept;
    void setAmountWaivedDerived(std::string &&pAmountWaivedDerived) noexcept;

    /**  For column amount_outstanding_derived  */
    const std::string &getValueOfAmountOutstandingDerived() const noexcept;
    const std::shared_ptr<std::string> &getAmountOutstandingDerived() const noexcept;
    void setAmountOutstandingDerived(const std::string &pAmountOutstandingDerived) noexcept;
    void setAmountOutstandingDerived(std::string &&pAmountOutstandingDerived) noexcept;

    /**  For column is_paid_derived  */
    const bool &getValueOfIsPaidDerived() const noexcept;
    const std::shared_ptr<bool> &getIsPaidDerived() const noexcept;
    void setIsPaidDerived(const bool &pIsPaidDerived) noexcept;

    /**  For column is_waived  */
    const bool &getValueOfIsWaived() const noexcept;
    const std::shared_ptr<bool> &getIsWaived() const noexcept;
    void setIsWaived(const bool &pIsWaived) noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

    /**  For column inactivated_on_date  */
    const ::trantor::Date &getValueOfInactivatedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getInactivatedOnDate() const noexcept;
    void setInactivatedOnDate(const ::trantor::Date &pInactivatedOnDate) noexcept;
    void setInactivatedOnDateToNull() noexcept;

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

    static size_t getColumnNumber() noexcept {  return 19;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<SavingsAccountCharge>;
    friend drogon::orm::BaseBuilder<SavingsAccountCharge, true, true>;
    friend drogon::orm::BaseBuilder<SavingsAccountCharge, true, false>;
    friend drogon::orm::BaseBuilder<SavingsAccountCharge, false, true>;
    friend drogon::orm::BaseBuilder<SavingsAccountCharge, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<SavingsAccountCharge>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> savingsAccountId_;
    std::shared_ptr<std::string> chargeId_;
    std::shared_ptr<int32_t> chargeTimeType_;
    std::shared_ptr<::trantor::Date> dueDate_;
    std::shared_ptr<int32_t> feeInterval_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<std::string> amountPaidDerived_;
    std::shared_ptr<std::string> amountWaivedDerived_;
    std::shared_ptr<std::string> amountOutstandingDerived_;
    std::shared_ptr<bool> isPaidDerived_;
    std::shared_ptr<bool> isWaived_;
    std::shared_ptr<bool> isActive_;
    std::shared_ptr<::trantor::Date> inactivatedOnDate_;
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
    bool dirtyFlag_[19]={ false };
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
            sql += "savings_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "charge_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "charge_time_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "due_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "fee_interval,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "amount,";
            ++parametersCount;
        }
        sql += "amount_paid_derived,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        sql += "amount_waived_derived,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        sql += "amount_outstanding_derived,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "is_paid_derived,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        sql += "is_waived,";
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
        if(dirtyFlag_[14])
        {
            sql += "inactivated_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[16])
        {
            needSelection=true;
        }
        if(dirtyFlag_[17])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[18])
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
