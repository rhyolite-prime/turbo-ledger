/**
 *  LoanGuarantor.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<LoanGuarantor> usage actually needs
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

class LoanGuarantor
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _loan_id;
        static const std::string _guarantor_type;
        static const std::string _client_id;
        static const std::string _first_name;
        static const std::string _last_name;
        static const std::string _address_line_1;
        static const std::string _city;
        static const std::string _mobile_number;
        static const std::string _amount;
        static const std::string _created_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit LoanGuarantor(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    LoanGuarantor() = default;

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

    /**  For column guarantor_type  */
    const int32_t &getValueOfGuarantorType() const noexcept;
    const std::shared_ptr<int32_t> &getGuarantorType() const noexcept;
    void setGuarantorType(const int32_t &pGuarantorType) noexcept;

    /**  For column client_id  */
    const std::string &getValueOfClientId() const noexcept;
    const std::shared_ptr<std::string> &getClientId() const noexcept;
    void setClientId(const std::string &pClientId) noexcept;
    void setClientId(std::string &&pClientId) noexcept;
    void setClientIdToNull() noexcept;

    /**  For column first_name  */
    const std::string &getValueOfFirstName() const noexcept;
    const std::shared_ptr<std::string> &getFirstName() const noexcept;
    void setFirstName(const std::string &pFirstName) noexcept;
    void setFirstName(std::string &&pFirstName) noexcept;
    void setFirstNameToNull() noexcept;

    /**  For column last_name  */
    const std::string &getValueOfLastName() const noexcept;
    const std::shared_ptr<std::string> &getLastName() const noexcept;
    void setLastName(const std::string &pLastName) noexcept;
    void setLastName(std::string &&pLastName) noexcept;
    void setLastNameToNull() noexcept;

    /**  For column address_line_1  */
    const std::string &getValueOfAddressLine1() const noexcept;
    const std::shared_ptr<std::string> &getAddressLine1() const noexcept;
    void setAddressLine1(const std::string &pAddressLine1) noexcept;
    void setAddressLine1(std::string &&pAddressLine1) noexcept;
    void setAddressLine1ToNull() noexcept;

    /**  For column city  */
    const std::string &getValueOfCity() const noexcept;
    const std::shared_ptr<std::string> &getCity() const noexcept;
    void setCity(const std::string &pCity) noexcept;
    void setCity(std::string &&pCity) noexcept;
    void setCityToNull() noexcept;

    /**  For column mobile_number  */
    const std::string &getValueOfMobileNumber() const noexcept;
    const std::shared_ptr<std::string> &getMobileNumber() const noexcept;
    void setMobileNumber(const std::string &pMobileNumber) noexcept;
    void setMobileNumber(std::string &&pMobileNumber) noexcept;
    void setMobileNumberToNull() noexcept;

    /**  For column amount  */
    const std::string &getValueOfAmount() const noexcept;
    const std::shared_ptr<std::string> &getAmount() const noexcept;
    void setAmount(const std::string &pAmount) noexcept;
    void setAmount(std::string &&pAmount) noexcept;
    void setAmountToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 11;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<LoanGuarantor>;
    friend drogon::orm::BaseBuilder<LoanGuarantor, true, true>;
    friend drogon::orm::BaseBuilder<LoanGuarantor, true, false>;
    friend drogon::orm::BaseBuilder<LoanGuarantor, false, true>;
    friend drogon::orm::BaseBuilder<LoanGuarantor, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<LoanGuarantor>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> loanId_;
    std::shared_ptr<int32_t> guarantorType_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> firstName_;
    std::shared_ptr<std::string> lastName_;
    std::shared_ptr<std::string> addressLine1_;
    std::shared_ptr<std::string> city_;
    std::shared_ptr<std::string> mobileNumber_;
    std::shared_ptr<std::string> amount_;
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
            sql += "loan_id,";
            ++parametersCount;
        }
        sql += "guarantor_type,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        if(dirtyFlag_[3])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "first_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "last_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "address_line_1,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "city,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "mobile_number,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "amount,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[10])
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
        else
        {
            sql +="default,";
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
