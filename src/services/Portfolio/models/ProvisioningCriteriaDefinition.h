/**
 *  ProvisioningCriteriaDefinition.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<ProvisioningCriteriaDefinition> usage actually needs
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

class ProvisioningCriteriaDefinition
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _criteria_id;
        static const std::string _category_id;
        static const std::string _min_overdue_days;
        static const std::string _max_overdue_days;
        static const std::string _provisioning_percentage;
        static const std::string _liability_account_id;
        static const std::string _expense_account_id;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit ProvisioningCriteriaDefinition(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    ProvisioningCriteriaDefinition() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column criteria_id  */
    const std::string &getValueOfCriteriaId() const noexcept;
    const std::shared_ptr<std::string> &getCriteriaId() const noexcept;
    void setCriteriaId(const std::string &pCriteriaId) noexcept;
    void setCriteriaId(std::string &&pCriteriaId) noexcept;

    /**  For column category_id  */
    const std::string &getValueOfCategoryId() const noexcept;
    const std::shared_ptr<std::string> &getCategoryId() const noexcept;
    void setCategoryId(const std::string &pCategoryId) noexcept;
    void setCategoryId(std::string &&pCategoryId) noexcept;

    /**  For column min_overdue_days  */
    const int32_t &getValueOfMinOverdueDays() const noexcept;
    const std::shared_ptr<int32_t> &getMinOverdueDays() const noexcept;
    void setMinOverdueDays(const int32_t &pMinOverdueDays) noexcept;

    /**  For column max_overdue_days  */
    const int32_t &getValueOfMaxOverdueDays() const noexcept;
    const std::shared_ptr<int32_t> &getMaxOverdueDays() const noexcept;
    void setMaxOverdueDays(const int32_t &pMaxOverdueDays) noexcept;
    void setMaxOverdueDaysToNull() noexcept;

    /**  For column provisioning_percentage  */
    const std::string &getValueOfProvisioningPercentage() const noexcept;
    const std::shared_ptr<std::string> &getProvisioningPercentage() const noexcept;
    void setProvisioningPercentage(const std::string &pProvisioningPercentage) noexcept;
    void setProvisioningPercentage(std::string &&pProvisioningPercentage) noexcept;

    /**  For column liability_account_id  */
    const std::string &getValueOfLiabilityAccountId() const noexcept;
    const std::shared_ptr<std::string> &getLiabilityAccountId() const noexcept;
    void setLiabilityAccountId(const std::string &pLiabilityAccountId) noexcept;
    void setLiabilityAccountId(std::string &&pLiabilityAccountId) noexcept;
    void setLiabilityAccountIdToNull() noexcept;

    /**  For column expense_account_id  */
    const std::string &getValueOfExpenseAccountId() const noexcept;
    const std::shared_ptr<std::string> &getExpenseAccountId() const noexcept;
    void setExpenseAccountId(const std::string &pExpenseAccountId) noexcept;
    void setExpenseAccountId(std::string &&pExpenseAccountId) noexcept;
    void setExpenseAccountIdToNull() noexcept;

    static size_t getColumnNumber() noexcept {  return 8;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<ProvisioningCriteriaDefinition>;
    friend drogon::orm::BaseBuilder<ProvisioningCriteriaDefinition, true, true>;
    friend drogon::orm::BaseBuilder<ProvisioningCriteriaDefinition, true, false>;
    friend drogon::orm::BaseBuilder<ProvisioningCriteriaDefinition, false, true>;
    friend drogon::orm::BaseBuilder<ProvisioningCriteriaDefinition, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<ProvisioningCriteriaDefinition>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> criteriaId_;
    std::shared_ptr<std::string> categoryId_;
    std::shared_ptr<int32_t> minOverdueDays_;
    std::shared_ptr<int32_t> maxOverdueDays_;
    std::shared_ptr<std::string> provisioningPercentage_;
    std::shared_ptr<std::string> liabilityAccountId_;
    std::shared_ptr<std::string> expenseAccountId_;
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
    bool dirtyFlag_[8]={ false };
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
            sql += "criteria_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "category_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "min_overdue_days,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "max_overdue_days,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "provisioning_percentage,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "liability_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "expense_account_id,";
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
