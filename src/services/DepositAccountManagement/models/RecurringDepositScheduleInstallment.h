/**
 *  RecurringDepositScheduleInstallment.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<RecurringDepositScheduleInstallment> usage actually needs
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

class RecurringDepositScheduleInstallment
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _savings_account_id;
        static const std::string _installment_number;
        static const std::string _due_date;
        static const std::string _deposit_amount;
        static const std::string _deposit_amount_completed_derived;
        static const std::string _is_obligation_met;
        static const std::string _obligation_met_on_date;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit RecurringDepositScheduleInstallment(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    RecurringDepositScheduleInstallment() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column savings_account_id  */
    const std::string &getValueOfSavingsAccountId() const noexcept;
    const std::shared_ptr<std::string> &getSavingsAccountId() const noexcept;
    void setSavingsAccountId(const std::string &pSavingsAccountId) noexcept;
    void setSavingsAccountId(std::string &&pSavingsAccountId) noexcept;

    /**  For column installment_number  */
    const int32_t &getValueOfInstallmentNumber() const noexcept;
    const std::shared_ptr<int32_t> &getInstallmentNumber() const noexcept;
    void setInstallmentNumber(const int32_t &pInstallmentNumber) noexcept;

    /**  For column due_date  */
    const ::trantor::Date &getValueOfDueDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getDueDate() const noexcept;
    void setDueDate(const ::trantor::Date &pDueDate) noexcept;

    /**  For column deposit_amount  */
    const std::string &getValueOfDepositAmount() const noexcept;
    const std::shared_ptr<std::string> &getDepositAmount() const noexcept;
    void setDepositAmount(const std::string &pDepositAmount) noexcept;
    void setDepositAmount(std::string &&pDepositAmount) noexcept;

    /**  For column deposit_amount_completed_derived  */
    const std::string &getValueOfDepositAmountCompletedDerived() const noexcept;
    const std::shared_ptr<std::string> &getDepositAmountCompletedDerived() const noexcept;
    void setDepositAmountCompletedDerived(const std::string &pDepositAmountCompletedDerived) noexcept;
    void setDepositAmountCompletedDerived(std::string &&pDepositAmountCompletedDerived) noexcept;

    /**  For column is_obligation_met  */
    const bool &getValueOfIsObligationMet() const noexcept;
    const std::shared_ptr<bool> &getIsObligationMet() const noexcept;
    void setIsObligationMet(const bool &pIsObligationMet) noexcept;

    /**  For column obligation_met_on_date  */
    const ::trantor::Date &getValueOfObligationMetOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getObligationMetOnDate() const noexcept;
    void setObligationMetOnDate(const ::trantor::Date &pObligationMetOnDate) noexcept;
    void setObligationMetOnDateToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<RecurringDepositScheduleInstallment>;
    friend drogon::orm::BaseBuilder<RecurringDepositScheduleInstallment, true, true>;
    friend drogon::orm::BaseBuilder<RecurringDepositScheduleInstallment, true, false>;
    friend drogon::orm::BaseBuilder<RecurringDepositScheduleInstallment, false, true>;
    friend drogon::orm::BaseBuilder<RecurringDepositScheduleInstallment, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<RecurringDepositScheduleInstallment>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> savingsAccountId_;
    std::shared_ptr<int32_t> installmentNumber_;
    std::shared_ptr<::trantor::Date> dueDate_;
    std::shared_ptr<std::string> depositAmount_;
    std::shared_ptr<std::string> depositAmountCompletedDerived_;
    std::shared_ptr<bool> isObligationMet_;
    std::shared_ptr<::trantor::Date> obligationMetOnDate_;
    std::shared_ptr<::trantor::Date> createdAt_;
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
    bool dirtyFlag_[9]={ false };
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
            sql += "savings_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "installment_number,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "due_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "deposit_amount,";
            ++parametersCount;
        }
        sql += "deposit_amount_completed_derived,";
        ++parametersCount;
        if(!dirtyFlag_[5])
        {
            needSelection=true;
        }
        sql += "is_obligation_met,";
        ++parametersCount;
        if(!dirtyFlag_[6])
        {
            needSelection=true;
        }
        if(dirtyFlag_[7])
        {
            sql += "obligation_met_on_date,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[8])
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
        else
        {
            sql +="default,";
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
