/**
 *  StandingInstruction.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<StandingInstruction> usage actually needs
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

class StandingInstruction
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _name;
        static const std::string _description;
        static const std::string _client_id;
        static const std::string _from_office_id;
        static const std::string _from_client_id;
        static const std::string _from_account_type;
        static const std::string _from_account_id;
        static const std::string _to_office_id;
        static const std::string _to_client_id;
        static const std::string _to_account_type;
        static const std::string _to_account_id;
        static const std::string _instruction_type;
        static const std::string _status;
        static const std::string _priority;
        static const std::string _transfer_type;
        static const std::string _amount;
        static const std::string _valid_from;
        static const std::string _valid_till;
        static const std::string _recurrence_type;
        static const std::string _recurrence_frequency;
        static const std::string _recurrence_interval;
        static const std::string _recurrence_on_day;
        static const std::string _last_run_date;
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

    explicit StandingInstruction(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    StandingInstruction() = default;

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

    /**  For column name  */
    const std::string &getValueOfName() const noexcept;
    const std::shared_ptr<std::string> &getName() const noexcept;
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column description  */
    const std::string &getValueOfDescription() const noexcept;
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;
    void setDescriptionToNull() noexcept;

    /**  For column client_id  */
    const std::string &getValueOfClientId() const noexcept;
    const std::shared_ptr<std::string> &getClientId() const noexcept;
    void setClientId(const std::string &pClientId) noexcept;
    void setClientId(std::string &&pClientId) noexcept;
    void setClientIdToNull() noexcept;

    /**  For column from_office_id  */
    const std::string &getValueOfFromOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getFromOfficeId() const noexcept;
    void setFromOfficeId(const std::string &pFromOfficeId) noexcept;
    void setFromOfficeId(std::string &&pFromOfficeId) noexcept;
    void setFromOfficeIdToNull() noexcept;

    /**  For column from_client_id  */
    const std::string &getValueOfFromClientId() const noexcept;
    const std::shared_ptr<std::string> &getFromClientId() const noexcept;
    void setFromClientId(const std::string &pFromClientId) noexcept;
    void setFromClientId(std::string &&pFromClientId) noexcept;
    void setFromClientIdToNull() noexcept;

    /**  For column from_account_type  */
    const int32_t &getValueOfFromAccountType() const noexcept;
    const std::shared_ptr<int32_t> &getFromAccountType() const noexcept;
    void setFromAccountType(const int32_t &pFromAccountType) noexcept;

    /**  For column from_account_id  */
    const std::string &getValueOfFromAccountId() const noexcept;
    const std::shared_ptr<std::string> &getFromAccountId() const noexcept;
    void setFromAccountId(const std::string &pFromAccountId) noexcept;
    void setFromAccountId(std::string &&pFromAccountId) noexcept;

    /**  For column to_office_id  */
    const std::string &getValueOfToOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getToOfficeId() const noexcept;
    void setToOfficeId(const std::string &pToOfficeId) noexcept;
    void setToOfficeId(std::string &&pToOfficeId) noexcept;
    void setToOfficeIdToNull() noexcept;

    /**  For column to_client_id  */
    const std::string &getValueOfToClientId() const noexcept;
    const std::shared_ptr<std::string> &getToClientId() const noexcept;
    void setToClientId(const std::string &pToClientId) noexcept;
    void setToClientId(std::string &&pToClientId) noexcept;
    void setToClientIdToNull() noexcept;

    /**  For column to_account_type  */
    const int32_t &getValueOfToAccountType() const noexcept;
    const std::shared_ptr<int32_t> &getToAccountType() const noexcept;
    void setToAccountType(const int32_t &pToAccountType) noexcept;

    /**  For column to_account_id  */
    const std::string &getValueOfToAccountId() const noexcept;
    const std::shared_ptr<std::string> &getToAccountId() const noexcept;
    void setToAccountId(const std::string &pToAccountId) noexcept;
    void setToAccountId(std::string &&pToAccountId) noexcept;

    /**  For column instruction_type  */
    const int32_t &getValueOfInstructionType() const noexcept;
    const std::shared_ptr<int32_t> &getInstructionType() const noexcept;
    void setInstructionType(const int32_t &pInstructionType) noexcept;

    /**  For column status  */
    const int32_t &getValueOfStatus() const noexcept;
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column priority  */
    const int32_t &getValueOfPriority() const noexcept;
    const std::shared_ptr<int32_t> &getPriority() const noexcept;
    void setPriority(const int32_t &pPriority) noexcept;

    /**  For column transfer_type  */
    const int32_t &getValueOfTransferType() const noexcept;
    const std::shared_ptr<int32_t> &getTransferType() const noexcept;
    void setTransferType(const int32_t &pTransferType) noexcept;

    /**  For column amount  */
    const std::string &getValueOfAmount() const noexcept;
    const std::shared_ptr<std::string> &getAmount() const noexcept;
    void setAmount(const std::string &pAmount) noexcept;
    void setAmount(std::string &&pAmount) noexcept;
    void setAmountToNull() noexcept;

    /**  For column valid_from  */
    const ::trantor::Date &getValueOfValidFrom() const noexcept;
    const std::shared_ptr<::trantor::Date> &getValidFrom() const noexcept;
    void setValidFrom(const ::trantor::Date &pValidFrom) noexcept;

    /**  For column valid_till  */
    const ::trantor::Date &getValueOfValidTill() const noexcept;
    const std::shared_ptr<::trantor::Date> &getValidTill() const noexcept;
    void setValidTill(const ::trantor::Date &pValidTill) noexcept;
    void setValidTillToNull() noexcept;

    /**  For column recurrence_type  */
    const int32_t &getValueOfRecurrenceType() const noexcept;
    const std::shared_ptr<int32_t> &getRecurrenceType() const noexcept;
    void setRecurrenceType(const int32_t &pRecurrenceType) noexcept;

    /**  For column recurrence_frequency  */
    const int32_t &getValueOfRecurrenceFrequency() const noexcept;
    const std::shared_ptr<int32_t> &getRecurrenceFrequency() const noexcept;
    void setRecurrenceFrequency(const int32_t &pRecurrenceFrequency) noexcept;
    void setRecurrenceFrequencyToNull() noexcept;

    /**  For column recurrence_interval  */
    const int32_t &getValueOfRecurrenceInterval() const noexcept;
    const std::shared_ptr<int32_t> &getRecurrenceInterval() const noexcept;
    void setRecurrenceInterval(const int32_t &pRecurrenceInterval) noexcept;
    void setRecurrenceIntervalToNull() noexcept;

    /**  For column recurrence_on_day  */
    const int32_t &getValueOfRecurrenceOnDay() const noexcept;
    const std::shared_ptr<int32_t> &getRecurrenceOnDay() const noexcept;
    void setRecurrenceOnDay(const int32_t &pRecurrenceOnDay) noexcept;
    void setRecurrenceOnDayToNull() noexcept;

    /**  For column last_run_date  */
    const ::trantor::Date &getValueOfLastRunDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getLastRunDate() const noexcept;
    void setLastRunDate(const ::trantor::Date &pLastRunDate) noexcept;
    void setLastRunDateToNull() noexcept;

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

    static size_t getColumnNumber() noexcept {  return 29;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<StandingInstruction>;
    friend drogon::orm::BaseBuilder<StandingInstruction, true, true>;
    friend drogon::orm::BaseBuilder<StandingInstruction, true, false>;
    friend drogon::orm::BaseBuilder<StandingInstruction, false, true>;
    friend drogon::orm::BaseBuilder<StandingInstruction, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<StandingInstruction>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> fromOfficeId_;
    std::shared_ptr<std::string> fromClientId_;
    std::shared_ptr<int32_t> fromAccountType_;
    std::shared_ptr<std::string> fromAccountId_;
    std::shared_ptr<std::string> toOfficeId_;
    std::shared_ptr<std::string> toClientId_;
    std::shared_ptr<int32_t> toAccountType_;
    std::shared_ptr<std::string> toAccountId_;
    std::shared_ptr<int32_t> instructionType_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<int32_t> priority_;
    std::shared_ptr<int32_t> transferType_;
    std::shared_ptr<std::string> amount_;
    std::shared_ptr<::trantor::Date> validFrom_;
    std::shared_ptr<::trantor::Date> validTill_;
    std::shared_ptr<int32_t> recurrenceType_;
    std::shared_ptr<int32_t> recurrenceFrequency_;
    std::shared_ptr<int32_t> recurrenceInterval_;
    std::shared_ptr<int32_t> recurrenceOnDay_;
    std::shared_ptr<::trantor::Date> lastRunDate_;
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
    bool dirtyFlag_[29]={ false };
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
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "from_office_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "from_client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "from_account_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "from_account_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "to_office_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "to_client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "to_account_type,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "to_account_id,";
            ++parametersCount;
        }
        sql += "instruction_type,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[14])
        {
            needSelection=true;
        }
        sql += "priority,";
        ++parametersCount;
        if(!dirtyFlag_[15])
        {
            needSelection=true;
        }
        sql += "transfer_type,";
        ++parametersCount;
        if(!dirtyFlag_[16])
        {
            needSelection=true;
        }
        if(dirtyFlag_[17])
        {
            sql += "amount,";
            ++parametersCount;
        }
        if(dirtyFlag_[18])
        {
            sql += "valid_from,";
            ++parametersCount;
        }
        if(dirtyFlag_[19])
        {
            sql += "valid_till,";
            ++parametersCount;
        }
        sql += "recurrence_type,";
        ++parametersCount;
        if(!dirtyFlag_[20])
        {
            needSelection=true;
        }
        if(dirtyFlag_[21])
        {
            sql += "recurrence_frequency,";
            ++parametersCount;
        }
        if(dirtyFlag_[22])
        {
            sql += "recurrence_interval,";
            ++parametersCount;
        }
        if(dirtyFlag_[23])
        {
            sql += "recurrence_on_day,";
            ++parametersCount;
        }
        if(dirtyFlag_[24])
        {
            sql += "last_run_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[25])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[26])
        {
            needSelection=true;
        }
        if(dirtyFlag_[27])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[28])
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
        if(dirtyFlag_[18])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
        if(dirtyFlag_[21])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[22])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[23])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[24])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[25])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[26])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[27])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[28])
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
