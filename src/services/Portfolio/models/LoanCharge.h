/**
 *  LoanCharge.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<LoanCharge> usage actually needs
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

class LoanCharge
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _loan_id;
        static const std::string _charge_id;
        static const std::string _is_penalty;
        static const std::string _charge_time_type;
        static const std::string _charge_calculation_type;
        static const std::string _due_date;
        static const std::string _installment_number;
        static const std::string _amount;
        static const std::string _amount_paid_derived;
        static const std::string _amount_waived_derived;
        static const std::string _amount_writtenoff_derived;
        static const std::string _amount_outstanding_derived;
        static const std::string _is_paid_derived;
        static const std::string _is_waived;
        static const std::string _is_active;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit LoanCharge(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    LoanCharge() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column loan_id  */
    const std::string &getValueOfLoanId() const noexcept;
    const std::shared_ptr<std::string> &getLoanId() const noexcept;
    void setLoanId(const std::string &pLoanId) noexcept;
    void setLoanId(std::string &&pLoanId) noexcept;

    /**  For column charge_id  */
    const std::string &getValueOfChargeId() const noexcept;
    const std::shared_ptr<std::string> &getChargeId() const noexcept;
    void setChargeId(const std::string &pChargeId) noexcept;
    void setChargeId(std::string &&pChargeId) noexcept;

    /**  For column is_penalty  */
    const bool &getValueOfIsPenalty() const noexcept;
    const std::shared_ptr<bool> &getIsPenalty() const noexcept;
    void setIsPenalty(const bool &pIsPenalty) noexcept;

    /**  For column charge_time_type  */
    const int32_t &getValueOfChargeTimeType() const noexcept;
    const std::shared_ptr<int32_t> &getChargeTimeType() const noexcept;
    void setChargeTimeType(const int32_t &pChargeTimeType) noexcept;

    /**  For column charge_calculation_type  */
    const int32_t &getValueOfChargeCalculationType() const noexcept;
    const std::shared_ptr<int32_t> &getChargeCalculationType() const noexcept;
    void setChargeCalculationType(const int32_t &pChargeCalculationType) noexcept;

    /**  For column due_date  */
    const ::trantor::Date &getValueOfDueDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getDueDate() const noexcept;
    void setDueDate(const ::trantor::Date &pDueDate) noexcept;
    void setDueDateToNull() noexcept;

    /**  For column installment_number  */
    const int32_t &getValueOfInstallmentNumber() const noexcept;
    const std::shared_ptr<int32_t> &getInstallmentNumber() const noexcept;
    void setInstallmentNumber(const int32_t &pInstallmentNumber) noexcept;
    void setInstallmentNumberToNull() noexcept;

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

    /**  For column amount_writtenoff_derived  */
    const std::string &getValueOfAmountWrittenoffDerived() const noexcept;
    const std::shared_ptr<std::string> &getAmountWrittenoffDerived() const noexcept;
    void setAmountWrittenoffDerived(const std::string &pAmountWrittenoffDerived) noexcept;
    void setAmountWrittenoffDerived(std::string &&pAmountWrittenoffDerived) noexcept;

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

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 17;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<LoanCharge>;
    friend drogon::orm::BaseBuilder<LoanCharge, true, true>;
    friend drogon::orm::BaseBuilder<LoanCharge, true, false>;
    friend drogon::orm::BaseBuilder<LoanCharge, false, true>;
    friend drogon::orm::BaseBuilder<LoanCharge, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<LoanCharge>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> loanId_;
    std::shared_ptr<std::string> chargeId_;
    std::shared_ptr<bool> isPenalty_;
    std::shared_ptr<int32_t> chargeTimeType_;
    std::shared_ptr<int32_t> chargeCalculationType_;
    std::shared_ptr<::trantor::Date> dueDate_;
    std::shared_ptr<int32_t> installmentNumber_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<std::string> amountPaidDerived_;
    std::shared_ptr<std::string> amountWaivedDerived_;
    std::shared_ptr<std::string> amountWrittenoffDerived_;
    std::shared_ptr<std::string> amountOutstandingDerived_;
    std::shared_ptr<bool> isPaidDerived_;
    std::shared_ptr<bool> isWaived_;
    std::shared_ptr<bool> isActive_;
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
    bool dirtyFlag_[17]={ false };
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
            sql += "loan_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "charge_id,";
            ++parametersCount;
        }
        sql += "is_penalty,";
        ++parametersCount;
        if(!dirtyFlag_[3])
        {
            needSelection=true;
        }
        if(dirtyFlag_[4])
        {
            sql += "charge_time_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "charge_calculation_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "due_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "installment_number,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "amount,";
            ++parametersCount;
        }
        sql += "amount_paid_derived,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        sql += "amount_waived_derived,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "amount_writtenoff_derived,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        sql += "amount_outstanding_derived,";
        ++parametersCount;
        if(!dirtyFlag_[12])
        {
            needSelection=true;
        }
        sql += "is_paid_derived,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        sql += "is_waived,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[15])
        {
            needSelection=true;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[16])
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
