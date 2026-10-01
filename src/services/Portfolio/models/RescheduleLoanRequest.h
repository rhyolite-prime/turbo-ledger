/**
 *  RescheduleLoanRequest.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<RescheduleLoanRequest> usage actually needs
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

class RescheduleLoanRequest
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _loan_id;
        static const std::string _reason_code;
        static const std::string _reason_comment;
        static const std::string _status;
        static const std::string _reschedule_from_installment;
        static const std::string _reschedule_from_date;
        static const std::string _submitted_on_date;
        static const std::string _submitted_by;
        static const std::string _extra_terms;
        static const std::string _grace_on_principal;
        static const std::string _grace_on_interest;
        static const std::string _new_interest_rate;
        static const std::string _adjusted_due_date;
        static const std::string _approved_on_date;
        static const std::string _approved_by;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit RescheduleLoanRequest(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    RescheduleLoanRequest() = default;

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

    /**  For column reason_code  */
    const std::string &getValueOfReasonCode() const noexcept;
    const std::shared_ptr<std::string> &getReasonCode() const noexcept;
    void setReasonCode(const std::string &pReasonCode) noexcept;
    void setReasonCode(std::string &&pReasonCode) noexcept;

    /**  For column reason_comment  */
    const std::string &getValueOfReasonComment() const noexcept;
    const std::shared_ptr<std::string> &getReasonComment() const noexcept;
    void setReasonComment(const std::string &pReasonComment) noexcept;
    void setReasonComment(std::string &&pReasonComment) noexcept;
    void setReasonCommentToNull() noexcept;

    /**  For column status  */
    const int32_t &getValueOfStatus() const noexcept;
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column reschedule_from_installment  */
    const int32_t &getValueOfRescheduleFromInstallment() const noexcept;
    const std::shared_ptr<int32_t> &getRescheduleFromInstallment() const noexcept;
    void setRescheduleFromInstallment(const int32_t &pRescheduleFromInstallment) noexcept;
    void setRescheduleFromInstallmentToNull() noexcept;

    /**  For column reschedule_from_date  */
    const ::trantor::Date &getValueOfRescheduleFromDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getRescheduleFromDate() const noexcept;
    void setRescheduleFromDate(const ::trantor::Date &pRescheduleFromDate) noexcept;
    void setRescheduleFromDateToNull() noexcept;

    /**  For column submitted_on_date  */
    const ::trantor::Date &getValueOfSubmittedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedOnDate() const noexcept;
    void setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept;

    /**  For column submitted_by  */
    const std::string &getValueOfSubmittedBy() const noexcept;
    const std::shared_ptr<std::string> &getSubmittedBy() const noexcept;
    void setSubmittedBy(const std::string &pSubmittedBy) noexcept;
    void setSubmittedBy(std::string &&pSubmittedBy) noexcept;
    void setSubmittedByToNull() noexcept;

    /**  For column extra_terms  */
    const int32_t &getValueOfExtraTerms() const noexcept;
    const std::shared_ptr<int32_t> &getExtraTerms() const noexcept;
    void setExtraTerms(const int32_t &pExtraTerms) noexcept;
    void setExtraTermsToNull() noexcept;

    /**  For column grace_on_principal  */
    const int32_t &getValueOfGraceOnPrincipal() const noexcept;
    const std::shared_ptr<int32_t> &getGraceOnPrincipal() const noexcept;
    void setGraceOnPrincipal(const int32_t &pGraceOnPrincipal) noexcept;
    void setGraceOnPrincipalToNull() noexcept;

    /**  For column grace_on_interest  */
    const int32_t &getValueOfGraceOnInterest() const noexcept;
    const std::shared_ptr<int32_t> &getGraceOnInterest() const noexcept;
    void setGraceOnInterest(const int32_t &pGraceOnInterest) noexcept;
    void setGraceOnInterestToNull() noexcept;

    /**  For column new_interest_rate  */
    const std::string &getValueOfNewInterestRate() const noexcept;
    const std::shared_ptr<std::string> &getNewInterestRate() const noexcept;
    void setNewInterestRate(const std::string &pNewInterestRate) noexcept;
    void setNewInterestRate(std::string &&pNewInterestRate) noexcept;
    void setNewInterestRateToNull() noexcept;

    /**  For column adjusted_due_date  */
    const ::trantor::Date &getValueOfAdjustedDueDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getAdjustedDueDate() const noexcept;
    void setAdjustedDueDate(const ::trantor::Date &pAdjustedDueDate) noexcept;
    void setAdjustedDueDateToNull() noexcept;

    /**  For column approved_on_date  */
    const ::trantor::Date &getValueOfApprovedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getApprovedOnDate() const noexcept;
    void setApprovedOnDate(const ::trantor::Date &pApprovedOnDate) noexcept;
    void setApprovedOnDateToNull() noexcept;

    /**  For column approved_by  */
    const std::string &getValueOfApprovedBy() const noexcept;
    const std::shared_ptr<std::string> &getApprovedBy() const noexcept;
    void setApprovedBy(const std::string &pApprovedBy) noexcept;
    void setApprovedBy(std::string &&pApprovedBy) noexcept;
    void setApprovedByToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 17;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<RescheduleLoanRequest>;
    friend drogon::orm::BaseBuilder<RescheduleLoanRequest, true, true>;
    friend drogon::orm::BaseBuilder<RescheduleLoanRequest, true, false>;
    friend drogon::orm::BaseBuilder<RescheduleLoanRequest, false, true>;
    friend drogon::orm::BaseBuilder<RescheduleLoanRequest, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<RescheduleLoanRequest>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> loanId_;
    std::shared_ptr<std::string> reasonCode_;
    std::shared_ptr<std::string> reasonComment_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<int32_t> rescheduleFromInstallment_;
    std::shared_ptr<::trantor::Date> rescheduleFromDate_;
    std::shared_ptr<::trantor::Date> submittedOnDate_;
    std::shared_ptr<std::string> submittedBy_;
    std::shared_ptr<int32_t> extraTerms_;
    std::shared_ptr<int32_t> graceOnPrincipal_;
    std::shared_ptr<int32_t> graceOnInterest_;
    std::shared_ptr<std::string> newInterestRate_;
    std::shared_ptr<::trantor::Date> adjustedDueDate_;
    std::shared_ptr<::trantor::Date> approvedOnDate_;
    std::shared_ptr<std::string> approvedBy_;
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
            sql += "reason_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "reason_comment,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        if(dirtyFlag_[5])
        {
            sql += "reschedule_from_installment,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "reschedule_from_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "submitted_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "submitted_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "extra_terms,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "grace_on_principal,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "grace_on_interest,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "new_interest_rate,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "adjusted_due_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "approved_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "approved_by,";
            ++parametersCount;
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
