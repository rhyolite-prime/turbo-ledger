/**
 *  DepositAccountTermAndPreclosure.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<DepositAccountTermAndPreclosure> usage actually needs
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

class DepositAccountTermAndPreclosure
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _savings_account_id;
        static const std::string _deposit_amount;
        static const std::string _deposit_period;
        static const std::string _deposit_period_frequency_type;
        static const std::string _maturity_amount;
        static const std::string _maturity_date;
        static const std::string _expected_firstdeposit_on_date;
        static const std::string _is_renewal_allowed;
        static const std::string _is_premature_closure_allowed;
        static const std::string _pre_closure_penal_applicable;
        static const std::string _pre_closure_penal_interest;
        static const std::string _pre_closure_penal_interest_on_type;
        static const std::string _on_account_closure_type;
        static const std::string _transfer_to_savings_account_id;
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

    explicit DepositAccountTermAndPreclosure(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    DepositAccountTermAndPreclosure() = default;

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

    /**  For column deposit_amount  */
    const std::string &getValueOfDepositAmount() const noexcept;
    const std::shared_ptr<std::string> &getDepositAmount() const noexcept;
    void setDepositAmount(const std::string &pDepositAmount) noexcept;
    void setDepositAmount(std::string &&pDepositAmount) noexcept;
    void setDepositAmountToNull() noexcept;

    /**  For column deposit_period  */
    const int32_t &getValueOfDepositPeriod() const noexcept;
    const std::shared_ptr<int32_t> &getDepositPeriod() const noexcept;
    void setDepositPeriod(const int32_t &pDepositPeriod) noexcept;
    void setDepositPeriodToNull() noexcept;

    /**  For column deposit_period_frequency_type  */
    const int32_t &getValueOfDepositPeriodFrequencyType() const noexcept;
    const std::shared_ptr<int32_t> &getDepositPeriodFrequencyType() const noexcept;
    void setDepositPeriodFrequencyType(const int32_t &pDepositPeriodFrequencyType) noexcept;
    void setDepositPeriodFrequencyTypeToNull() noexcept;

    /**  For column maturity_amount  */
    const std::string &getValueOfMaturityAmount() const noexcept;
    const std::shared_ptr<std::string> &getMaturityAmount() const noexcept;
    void setMaturityAmount(const std::string &pMaturityAmount) noexcept;
    void setMaturityAmount(std::string &&pMaturityAmount) noexcept;
    void setMaturityAmountToNull() noexcept;

    /**  For column maturity_date  */
    const ::trantor::Date &getValueOfMaturityDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getMaturityDate() const noexcept;
    void setMaturityDate(const ::trantor::Date &pMaturityDate) noexcept;
    void setMaturityDateToNull() noexcept;

    /**  For column expected_firstdeposit_on_date  */
    const ::trantor::Date &getValueOfExpectedFirstdepositOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getExpectedFirstdepositOnDate() const noexcept;
    void setExpectedFirstdepositOnDate(const ::trantor::Date &pExpectedFirstdepositOnDate) noexcept;
    void setExpectedFirstdepositOnDateToNull() noexcept;

    /**  For column is_renewal_allowed  */
    const bool &getValueOfIsRenewalAllowed() const noexcept;
    const std::shared_ptr<bool> &getIsRenewalAllowed() const noexcept;
    void setIsRenewalAllowed(const bool &pIsRenewalAllowed) noexcept;

    /**  For column is_premature_closure_allowed  */
    const bool &getValueOfIsPrematureClosureAllowed() const noexcept;
    const std::shared_ptr<bool> &getIsPrematureClosureAllowed() const noexcept;
    void setIsPrematureClosureAllowed(const bool &pIsPrematureClosureAllowed) noexcept;

    /**  For column pre_closure_penal_applicable  */
    const bool &getValueOfPreClosurePenalApplicable() const noexcept;
    const std::shared_ptr<bool> &getPreClosurePenalApplicable() const noexcept;
    void setPreClosurePenalApplicable(const bool &pPreClosurePenalApplicable) noexcept;

    /**  For column pre_closure_penal_interest  */
    const std::string &getValueOfPreClosurePenalInterest() const noexcept;
    const std::shared_ptr<std::string> &getPreClosurePenalInterest() const noexcept;
    void setPreClosurePenalInterest(const std::string &pPreClosurePenalInterest) noexcept;
    void setPreClosurePenalInterest(std::string &&pPreClosurePenalInterest) noexcept;
    void setPreClosurePenalInterestToNull() noexcept;

    /**  For column pre_closure_penal_interest_on_type  */
    const int32_t &getValueOfPreClosurePenalInterestOnType() const noexcept;
    const std::shared_ptr<int32_t> &getPreClosurePenalInterestOnType() const noexcept;
    void setPreClosurePenalInterestOnType(const int32_t &pPreClosurePenalInterestOnType) noexcept;
    void setPreClosurePenalInterestOnTypeToNull() noexcept;

    /**  For column on_account_closure_type  */
    const int32_t &getValueOfOnAccountClosureType() const noexcept;
    const std::shared_ptr<int32_t> &getOnAccountClosureType() const noexcept;
    void setOnAccountClosureType(const int32_t &pOnAccountClosureType) noexcept;
    void setOnAccountClosureTypeToNull() noexcept;

    /**  For column transfer_to_savings_account_id  */
    const std::string &getValueOfTransferToSavingsAccountId() const noexcept;
    const std::shared_ptr<std::string> &getTransferToSavingsAccountId() const noexcept;
    void setTransferToSavingsAccountId(const std::string &pTransferToSavingsAccountId) noexcept;
    void setTransferToSavingsAccountId(std::string &&pTransferToSavingsAccountId) noexcept;
    void setTransferToSavingsAccountIdToNull() noexcept;

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
    friend drogon::orm::Mapper<DepositAccountTermAndPreclosure>;
    friend drogon::orm::BaseBuilder<DepositAccountTermAndPreclosure, true, true>;
    friend drogon::orm::BaseBuilder<DepositAccountTermAndPreclosure, true, false>;
    friend drogon::orm::BaseBuilder<DepositAccountTermAndPreclosure, false, true>;
    friend drogon::orm::BaseBuilder<DepositAccountTermAndPreclosure, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<DepositAccountTermAndPreclosure>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> savingsAccountId_;
    std::shared_ptr<std::string> depositAmount_;
    std::shared_ptr<int32_t> depositPeriod_;
    std::shared_ptr<int32_t> depositPeriodFrequencyType_;
    std::shared_ptr<std::string> maturityAmount_;
    std::shared_ptr<::trantor::Date> maturityDate_;
    std::shared_ptr<::trantor::Date> expectedFirstdepositOnDate_;
    std::shared_ptr<bool> isRenewalAllowed_;
    std::shared_ptr<bool> isPrematureClosureAllowed_;
    std::shared_ptr<bool> preClosurePenalApplicable_;
    std::shared_ptr<std::string> preClosurePenalInterest_;
    std::shared_ptr<int32_t> preClosurePenalInterestOnType_;
    std::shared_ptr<int32_t> onAccountClosureType_;
    std::shared_ptr<std::string> transferToSavingsAccountId_;
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
            sql += "savings_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "deposit_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "deposit_period,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "deposit_period_frequency_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "maturity_amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "maturity_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "expected_firstdeposit_on_date,";
            ++parametersCount;
        }
        sql += "is_renewal_allowed,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        sql += "is_premature_closure_allowed,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        sql += "pre_closure_penal_applicable,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        if(dirtyFlag_[11])
        {
            sql += "pre_closure_penal_interest,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "pre_closure_penal_interest_on_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "on_account_closure_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "transfer_to_savings_account_id,";
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
