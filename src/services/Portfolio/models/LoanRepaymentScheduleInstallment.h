/**
 *  LoanRepaymentScheduleInstallment.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<LoanRepaymentScheduleInstallment> usage actually needs
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

class LoanRepaymentScheduleInstallment
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _loan_id;
        static const std::string _installment_number;
        static const std::string _from_date;
        static const std::string _due_date;
        static const std::string _principal_amount;
        static const std::string _principal_completed_derived;
        static const std::string _principal_writtenoff_derived;
        static const std::string _interest_amount;
        static const std::string _interest_completed_derived;
        static const std::string _interest_waived_derived;
        static const std::string _interest_writtenoff_derived;
        static const std::string _fee_charges_amount;
        static const std::string _fee_charges_completed_derived;
        static const std::string _fee_charges_waived_derived;
        static const std::string _penalty_charges_amount;
        static const std::string _penalty_charges_completed_derived;
        static const std::string _penalty_charges_waived_derived;
        static const std::string _completed_derived;
        static const std::string _obligations_met_on_date;
        static const std::string _recalculated_interest;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit LoanRepaymentScheduleInstallment(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    LoanRepaymentScheduleInstallment() = default;

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

    /**  For column installment_number  */
    const int32_t &getValueOfInstallmentNumber() const noexcept;
    const std::shared_ptr<int32_t> &getInstallmentNumber() const noexcept;
    void setInstallmentNumber(const int32_t &pInstallmentNumber) noexcept;

    /**  For column from_date  */
    const ::trantor::Date &getValueOfFromDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getFromDate() const noexcept;
    void setFromDate(const ::trantor::Date &pFromDate) noexcept;

    /**  For column due_date  */
    const ::trantor::Date &getValueOfDueDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getDueDate() const noexcept;
    void setDueDate(const ::trantor::Date &pDueDate) noexcept;

    /**  For column principal_amount  */
    const std::string &getValueOfPrincipalAmount() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalAmount() const noexcept;
    void setPrincipalAmount(const std::string &pPrincipalAmount) noexcept;
    void setPrincipalAmount(std::string &&pPrincipalAmount) noexcept;

    /**  For column principal_completed_derived  */
    const std::string &getValueOfPrincipalCompletedDerived() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalCompletedDerived() const noexcept;
    void setPrincipalCompletedDerived(const std::string &pPrincipalCompletedDerived) noexcept;
    void setPrincipalCompletedDerived(std::string &&pPrincipalCompletedDerived) noexcept;

    /**  For column principal_writtenoff_derived  */
    const std::string &getValueOfPrincipalWrittenoffDerived() const noexcept;
    const std::shared_ptr<std::string> &getPrincipalWrittenoffDerived() const noexcept;
    void setPrincipalWrittenoffDerived(const std::string &pPrincipalWrittenoffDerived) noexcept;
    void setPrincipalWrittenoffDerived(std::string &&pPrincipalWrittenoffDerived) noexcept;

    /**  For column interest_amount  */
    const std::string &getValueOfInterestAmount() const noexcept;
    const std::shared_ptr<std::string> &getInterestAmount() const noexcept;
    void setInterestAmount(const std::string &pInterestAmount) noexcept;
    void setInterestAmount(std::string &&pInterestAmount) noexcept;

    /**  For column interest_completed_derived  */
    const std::string &getValueOfInterestCompletedDerived() const noexcept;
    const std::shared_ptr<std::string> &getInterestCompletedDerived() const noexcept;
    void setInterestCompletedDerived(const std::string &pInterestCompletedDerived) noexcept;
    void setInterestCompletedDerived(std::string &&pInterestCompletedDerived) noexcept;

    /**  For column interest_waived_derived  */
    const std::string &getValueOfInterestWaivedDerived() const noexcept;
    const std::shared_ptr<std::string> &getInterestWaivedDerived() const noexcept;
    void setInterestWaivedDerived(const std::string &pInterestWaivedDerived) noexcept;
    void setInterestWaivedDerived(std::string &&pInterestWaivedDerived) noexcept;

    /**  For column interest_writtenoff_derived  */
    const std::string &getValueOfInterestWrittenoffDerived() const noexcept;
    const std::shared_ptr<std::string> &getInterestWrittenoffDerived() const noexcept;
    void setInterestWrittenoffDerived(const std::string &pInterestWrittenoffDerived) noexcept;
    void setInterestWrittenoffDerived(std::string &&pInterestWrittenoffDerived) noexcept;

    /**  For column fee_charges_amount  */
    const std::string &getValueOfFeeChargesAmount() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesAmount() const noexcept;
    void setFeeChargesAmount(const std::string &pFeeChargesAmount) noexcept;
    void setFeeChargesAmount(std::string &&pFeeChargesAmount) noexcept;

    /**  For column fee_charges_completed_derived  */
    const std::string &getValueOfFeeChargesCompletedDerived() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesCompletedDerived() const noexcept;
    void setFeeChargesCompletedDerived(const std::string &pFeeChargesCompletedDerived) noexcept;
    void setFeeChargesCompletedDerived(std::string &&pFeeChargesCompletedDerived) noexcept;

    /**  For column fee_charges_waived_derived  */
    const std::string &getValueOfFeeChargesWaivedDerived() const noexcept;
    const std::shared_ptr<std::string> &getFeeChargesWaivedDerived() const noexcept;
    void setFeeChargesWaivedDerived(const std::string &pFeeChargesWaivedDerived) noexcept;
    void setFeeChargesWaivedDerived(std::string &&pFeeChargesWaivedDerived) noexcept;

    /**  For column penalty_charges_amount  */
    const std::string &getValueOfPenaltyChargesAmount() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesAmount() const noexcept;
    void setPenaltyChargesAmount(const std::string &pPenaltyChargesAmount) noexcept;
    void setPenaltyChargesAmount(std::string &&pPenaltyChargesAmount) noexcept;

    /**  For column penalty_charges_completed_derived  */
    const std::string &getValueOfPenaltyChargesCompletedDerived() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesCompletedDerived() const noexcept;
    void setPenaltyChargesCompletedDerived(const std::string &pPenaltyChargesCompletedDerived) noexcept;
    void setPenaltyChargesCompletedDerived(std::string &&pPenaltyChargesCompletedDerived) noexcept;

    /**  For column penalty_charges_waived_derived  */
    const std::string &getValueOfPenaltyChargesWaivedDerived() const noexcept;
    const std::shared_ptr<std::string> &getPenaltyChargesWaivedDerived() const noexcept;
    void setPenaltyChargesWaivedDerived(const std::string &pPenaltyChargesWaivedDerived) noexcept;
    void setPenaltyChargesWaivedDerived(std::string &&pPenaltyChargesWaivedDerived) noexcept;

    /**  For column completed_derived  */
    const bool &getValueOfCompletedDerived() const noexcept;
    const std::shared_ptr<bool> &getCompletedDerived() const noexcept;
    void setCompletedDerived(const bool &pCompletedDerived) noexcept;

    /**  For column obligations_met_on_date  */
    const ::trantor::Date &getValueOfObligationsMetOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getObligationsMetOnDate() const noexcept;
    void setObligationsMetOnDate(const ::trantor::Date &pObligationsMetOnDate) noexcept;
    void setObligationsMetOnDateToNull() noexcept;

    /**  For column recalculated_interest  */
    const bool &getValueOfRecalculatedInterest() const noexcept;
    const std::shared_ptr<bool> &getRecalculatedInterest() const noexcept;
    void setRecalculatedInterest(const bool &pRecalculatedInterest) noexcept;

    static size_t getColumnNumber() noexcept {  return 21;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<LoanRepaymentScheduleInstallment>;
    friend drogon::orm::BaseBuilder<LoanRepaymentScheduleInstallment, true, true>;
    friend drogon::orm::BaseBuilder<LoanRepaymentScheduleInstallment, true, false>;
    friend drogon::orm::BaseBuilder<LoanRepaymentScheduleInstallment, false, true>;
    friend drogon::orm::BaseBuilder<LoanRepaymentScheduleInstallment, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<LoanRepaymentScheduleInstallment>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> loanId_;
    std::shared_ptr<int32_t> installmentNumber_;
    std::shared_ptr<::trantor::Date> fromDate_;
    std::shared_ptr<::trantor::Date> dueDate_;
    std::shared_ptr<std::string> principalAmount_;
    std::shared_ptr<std::string> principalCompletedDerived_;
    std::shared_ptr<std::string> principalWrittenoffDerived_;
    std::shared_ptr<std::string> interestAmount_;
    std::shared_ptr<std::string> interestCompletedDerived_;
    std::shared_ptr<std::string> interestWaivedDerived_;
    std::shared_ptr<std::string> interestWrittenoffDerived_;
    std::shared_ptr<std::string> feeChargesAmount_;
    std::shared_ptr<std::string> feeChargesCompletedDerived_;
    std::shared_ptr<std::string> feeChargesWaivedDerived_;
    std::shared_ptr<std::string> penaltyChargesAmount_;
    std::shared_ptr<std::string> penaltyChargesCompletedDerived_;
    std::shared_ptr<std::string> penaltyChargesWaivedDerived_;
    std::shared_ptr<bool> completedDerived_;
    std::shared_ptr<::trantor::Date> obligationsMetOnDate_;
    std::shared_ptr<bool> recalculatedInterest_;
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
    bool dirtyFlag_[21]={ false };
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
            sql += "installment_number,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "from_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "due_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "principal_amount,";
            ++parametersCount;
        }
        sql += "principal_completed_derived,";
        ++parametersCount;
        if(!dirtyFlag_[6])
        {
            needSelection=true;
        }
        sql += "principal_writtenoff_derived,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        if(dirtyFlag_[8])
        {
            sql += "interest_amount,";
            ++parametersCount;
        }
        sql += "interest_completed_derived,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        sql += "interest_waived_derived,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "interest_writtenoff_derived,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        sql += "fee_charges_amount,";
        ++parametersCount;
        if(!dirtyFlag_[12])
        {
            needSelection=true;
        }
        sql += "fee_charges_completed_derived,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        sql += "fee_charges_waived_derived,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        sql += "penalty_charges_amount,";
        ++parametersCount;
        if(!dirtyFlag_[15])
        {
            needSelection=true;
        }
        sql += "penalty_charges_completed_derived,";
        ++parametersCount;
        if(!dirtyFlag_[16])
        {
            needSelection=true;
        }
        sql += "penalty_charges_waived_derived,";
        ++parametersCount;
        if(!dirtyFlag_[17])
        {
            needSelection=true;
        }
        sql += "completed_derived,";
        ++parametersCount;
        if(!dirtyFlag_[18])
        {
            needSelection=true;
        }
        if(dirtyFlag_[19])
        {
            sql += "obligations_met_on_date,";
            ++parametersCount;
        }
        sql += "recalculated_interest,";
        ++parametersCount;
        if(!dirtyFlag_[20])
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
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[7])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
