/**
 *  LoanproductProvisioningEntry.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<LoanproductProvisioningEntry> usage actually needs
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

class LoanproductProvisioningEntry
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _history_id;
        static const std::string _criteria_id;
        static const std::string _currency_code;
        static const std::string _office_id;
        static const std::string _product_id;
        static const std::string _category_id;
        static const std::string _overdue_in_days;
        static const std::string _reseve_amount;
        static const std::string _liability_account;
        static const std::string _expense_account;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit LoanproductProvisioningEntry(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    LoanproductProvisioningEntry() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column history_id  */
    const std::string &getValueOfHistoryId() const noexcept;
    const std::shared_ptr<std::string> &getHistoryId() const noexcept;
    void setHistoryId(const std::string &pHistoryId) noexcept;
    void setHistoryId(std::string &&pHistoryId) noexcept;

    /**  For column criteria_id  */
    const std::string &getValueOfCriteriaId() const noexcept;
    const std::shared_ptr<std::string> &getCriteriaId() const noexcept;
    void setCriteriaId(const std::string &pCriteriaId) noexcept;
    void setCriteriaId(std::string &&pCriteriaId) noexcept;

    /**  For column currency_code  */
    const std::string &getValueOfCurrencyCode() const noexcept;
    const std::shared_ptr<std::string> &getCurrencyCode() const noexcept;
    void setCurrencyCode(const std::string &pCurrencyCode) noexcept;
    void setCurrencyCode(std::string &&pCurrencyCode) noexcept;

    /**  For column office_id  */
    const std::string &getValueOfOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getOfficeId() const noexcept;
    void setOfficeId(const std::string &pOfficeId) noexcept;
    void setOfficeId(std::string &&pOfficeId) noexcept;

    /**  For column product_id  */
    const std::string &getValueOfProductId() const noexcept;
    const std::shared_ptr<std::string> &getProductId() const noexcept;
    void setProductId(const std::string &pProductId) noexcept;
    void setProductId(std::string &&pProductId) noexcept;

    /**  For column category_id  */
    const std::string &getValueOfCategoryId() const noexcept;
    const std::shared_ptr<std::string> &getCategoryId() const noexcept;
    void setCategoryId(const std::string &pCategoryId) noexcept;
    void setCategoryId(std::string &&pCategoryId) noexcept;

    /**  For column overdue_in_days  */
    const int64_t &getValueOfOverdueInDays() const noexcept;
    const std::shared_ptr<int64_t> &getOverdueInDays() const noexcept;
    void setOverdueInDays(const int64_t &pOverdueInDays) noexcept;
    void setOverdueInDaysToNull() noexcept;

    /**  For column reseve_amount  */
    const std::string &getValueOfReseveAmount() const noexcept;
    const std::shared_ptr<std::string> &getReseveAmount() const noexcept;
    void setReseveAmount(const std::string &pReseveAmount) noexcept;
    void setReseveAmount(std::string &&pReseveAmount) noexcept;
    void setReseveAmountToNull() noexcept;

    /**  For column liability_account  */
    const std::string &getValueOfLiabilityAccount() const noexcept;
    const std::shared_ptr<std::string> &getLiabilityAccount() const noexcept;
    void setLiabilityAccount(const std::string &pLiabilityAccount) noexcept;
    void setLiabilityAccount(std::string &&pLiabilityAccount) noexcept;
    void setLiabilityAccountToNull() noexcept;

    /**  For column expense_account  */
    const std::string &getValueOfExpenseAccount() const noexcept;
    const std::shared_ptr<std::string> &getExpenseAccount() const noexcept;
    void setExpenseAccount(const std::string &pExpenseAccount) noexcept;
    void setExpenseAccount(std::string &&pExpenseAccount) noexcept;
    void setExpenseAccountToNull() noexcept;

    static size_t getColumnNumber() noexcept {  return 11;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<LoanproductProvisioningEntry>;
    friend drogon::orm::BaseBuilder<LoanproductProvisioningEntry, true, true>;
    friend drogon::orm::BaseBuilder<LoanproductProvisioningEntry, true, false>;
    friend drogon::orm::BaseBuilder<LoanproductProvisioningEntry, false, true>;
    friend drogon::orm::BaseBuilder<LoanproductProvisioningEntry, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<LoanproductProvisioningEntry>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> historyId_;
    std::shared_ptr<std::string> criteriaId_;
    std::shared_ptr<std::string> currencyCode_;
    std::shared_ptr<std::string> officeId_;
    std::shared_ptr<std::string> productId_;
    std::shared_ptr<std::string> categoryId_;
    std::shared_ptr<int64_t> overdueInDays_;
    std::shared_ptr<std::string> reseveAmount_;
    std::shared_ptr<std::string> liabilityAccount_;
    std::shared_ptr<std::string> expenseAccount_;
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
    bool dirtyFlag_[11]={ false };
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
            sql += "history_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "criteria_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "currency_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "office_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "product_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "category_id,";
            ++parametersCount;
        }
        sql += "overdue_in_days,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "reseve_amount,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        if(dirtyFlag_[9])
        {
            sql += "liability_account,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "expense_account,";
            ++parametersCount;
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
        else
        {
            sql +="default,";
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
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
