/**
 *  CreditBureauReport.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<CreditBureauReport> usage actually needs
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

class CreditBureauReport
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _organisation_credit_bureau_id;
        static const std::string _client_id;
        static const std::string _loan_id;
        static const std::string _national_id;
        static const std::string _report_data;
        static const std::string _requested_by;
        static const std::string _requested_on;
        static const std::string _is_active;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit CreditBureauReport(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    CreditBureauReport() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column organisation_credit_bureau_id  */
    const std::string &getValueOfOrganisationCreditBureauId() const noexcept;
    const std::shared_ptr<std::string> &getOrganisationCreditBureauId() const noexcept;
    void setOrganisationCreditBureauId(const std::string &pOrganisationCreditBureauId) noexcept;
    void setOrganisationCreditBureauId(std::string &&pOrganisationCreditBureauId) noexcept;

    /**  For column client_id  */
    const std::string &getValueOfClientId() const noexcept;
    const std::shared_ptr<std::string> &getClientId() const noexcept;
    void setClientId(const std::string &pClientId) noexcept;
    void setClientId(std::string &&pClientId) noexcept;
    void setClientIdToNull() noexcept;

    /**  For column loan_id  */
    const std::string &getValueOfLoanId() const noexcept;
    const std::shared_ptr<std::string> &getLoanId() const noexcept;
    void setLoanId(const std::string &pLoanId) noexcept;
    void setLoanId(std::string &&pLoanId) noexcept;
    void setLoanIdToNull() noexcept;

    /**  For column national_id  */
    const std::string &getValueOfNationalId() const noexcept;
    const std::shared_ptr<std::string> &getNationalId() const noexcept;
    void setNationalId(const std::string &pNationalId) noexcept;
    void setNationalId(std::string &&pNationalId) noexcept;
    void setNationalIdToNull() noexcept;

    /**  For column report_data  */
    const std::string &getValueOfReportData() const noexcept;
    const std::shared_ptr<std::string> &getReportData() const noexcept;
    void setReportData(const std::string &pReportData) noexcept;
    void setReportData(std::string &&pReportData) noexcept;

    /**  For column requested_by  */
    const std::string &getValueOfRequestedBy() const noexcept;
    const std::shared_ptr<std::string> &getRequestedBy() const noexcept;
    void setRequestedBy(const std::string &pRequestedBy) noexcept;
    void setRequestedBy(std::string &&pRequestedBy) noexcept;
    void setRequestedByToNull() noexcept;

    /**  For column requested_on  */
    const ::trantor::Date &getValueOfRequestedOn() const noexcept;
    const std::shared_ptr<::trantor::Date> &getRequestedOn() const noexcept;
    void setRequestedOn(const ::trantor::Date &pRequestedOn) noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<CreditBureauReport>;
    friend drogon::orm::BaseBuilder<CreditBureauReport, true, true>;
    friend drogon::orm::BaseBuilder<CreditBureauReport, true, false>;
    friend drogon::orm::BaseBuilder<CreditBureauReport, false, true>;
    friend drogon::orm::BaseBuilder<CreditBureauReport, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<CreditBureauReport>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> organisationCreditBureauId_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> loanId_;
    std::shared_ptr<std::string> nationalId_;
    std::shared_ptr<std::string> reportData_;
    std::shared_ptr<std::string> requestedBy_;
    std::shared_ptr<::trantor::Date> requestedOn_;
    std::shared_ptr<bool> isActive_;
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
            sql += "organisation_credit_bureau_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "loan_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "national_id,";
            ++parametersCount;
        }
        sql += "report_data,";
        ++parametersCount;
        if(!dirtyFlag_[5])
        {
            needSelection=true;
        }
        if(dirtyFlag_[6])
        {
            sql += "requested_by,";
            ++parametersCount;
        }
        sql += "requested_on,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "is_active,";
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
