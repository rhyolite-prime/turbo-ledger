/**
 *  ReportMailingJob.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<ReportMailingJob> usage actually needs
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
namespace TlNotificationDb
{

class ReportMailingJob
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _description;
        static const std::string _report_name;
        static const std::string _report_params;
        static const std::string _start_date_time;
        static const std::string _recurrence;
        static const std::string _email_recipients;
        static const std::string _email_subject;
        static const std::string _email_message;
        static const std::string _email_attachment_file_format;
        static const std::string _is_active;
        static const std::string _previous_run_status;
        static const std::string _previous_run_error_message;
        static const std::string _previous_run_start_time;
        static const std::string _previous_run_end_time;
        static const std::string _next_run_time;
        static const std::string _created_at;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit ReportMailingJob(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    ReportMailingJob() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

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

    /**  For column report_name  */
    const std::string &getValueOfReportName() const noexcept;
    const std::shared_ptr<std::string> &getReportName() const noexcept;
    void setReportName(const std::string &pReportName) noexcept;
    void setReportName(std::string &&pReportName) noexcept;

    /**  For column report_params  */
    const std::string &getValueOfReportParams() const noexcept;
    const std::shared_ptr<std::string> &getReportParams() const noexcept;
    void setReportParams(const std::string &pReportParams) noexcept;
    void setReportParams(std::string &&pReportParams) noexcept;

    /**  For column start_date_time  */
    const ::trantor::Date &getValueOfStartDateTime() const noexcept;
    const std::shared_ptr<::trantor::Date> &getStartDateTime() const noexcept;
    void setStartDateTime(const ::trantor::Date &pStartDateTime) noexcept;

    /**  For column recurrence  */
    const std::string &getValueOfRecurrence() const noexcept;
    const std::shared_ptr<std::string> &getRecurrence() const noexcept;
    void setRecurrence(const std::string &pRecurrence) noexcept;
    void setRecurrence(std::string &&pRecurrence) noexcept;
    void setRecurrenceToNull() noexcept;

    /**  For column email_recipients  */
    const std::string &getValueOfEmailRecipients() const noexcept;
    const std::shared_ptr<std::string> &getEmailRecipients() const noexcept;
    void setEmailRecipients(const std::string &pEmailRecipients) noexcept;
    void setEmailRecipients(std::string &&pEmailRecipients) noexcept;

    /**  For column email_subject  */
    const std::string &getValueOfEmailSubject() const noexcept;
    const std::shared_ptr<std::string> &getEmailSubject() const noexcept;
    void setEmailSubject(const std::string &pEmailSubject) noexcept;
    void setEmailSubject(std::string &&pEmailSubject) noexcept;

    /**  For column email_message  */
    const std::string &getValueOfEmailMessage() const noexcept;
    const std::shared_ptr<std::string> &getEmailMessage() const noexcept;
    void setEmailMessage(const std::string &pEmailMessage) noexcept;
    void setEmailMessage(std::string &&pEmailMessage) noexcept;
    void setEmailMessageToNull() noexcept;

    /**  For column email_attachment_file_format  */
    const std::string &getValueOfEmailAttachmentFileFormat() const noexcept;
    const std::shared_ptr<std::string> &getEmailAttachmentFileFormat() const noexcept;
    void setEmailAttachmentFileFormat(const std::string &pEmailAttachmentFileFormat) noexcept;
    void setEmailAttachmentFileFormat(std::string &&pEmailAttachmentFileFormat) noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

    /**  For column previous_run_status  */
    const std::string &getValueOfPreviousRunStatus() const noexcept;
    const std::shared_ptr<std::string> &getPreviousRunStatus() const noexcept;
    void setPreviousRunStatus(const std::string &pPreviousRunStatus) noexcept;
    void setPreviousRunStatus(std::string &&pPreviousRunStatus) noexcept;
    void setPreviousRunStatusToNull() noexcept;

    /**  For column previous_run_error_message  */
    const std::string &getValueOfPreviousRunErrorMessage() const noexcept;
    const std::shared_ptr<std::string> &getPreviousRunErrorMessage() const noexcept;
    void setPreviousRunErrorMessage(const std::string &pPreviousRunErrorMessage) noexcept;
    void setPreviousRunErrorMessage(std::string &&pPreviousRunErrorMessage) noexcept;
    void setPreviousRunErrorMessageToNull() noexcept;

    /**  For column previous_run_start_time  */
    const ::trantor::Date &getValueOfPreviousRunStartTime() const noexcept;
    const std::shared_ptr<::trantor::Date> &getPreviousRunStartTime() const noexcept;
    void setPreviousRunStartTime(const ::trantor::Date &pPreviousRunStartTime) noexcept;
    void setPreviousRunStartTimeToNull() noexcept;

    /**  For column previous_run_end_time  */
    const ::trantor::Date &getValueOfPreviousRunEndTime() const noexcept;
    const std::shared_ptr<::trantor::Date> &getPreviousRunEndTime() const noexcept;
    void setPreviousRunEndTime(const ::trantor::Date &pPreviousRunEndTime) noexcept;
    void setPreviousRunEndTimeToNull() noexcept;

    /**  For column next_run_time  */
    const ::trantor::Date &getValueOfNextRunTime() const noexcept;
    const std::shared_ptr<::trantor::Date> &getNextRunTime() const noexcept;
    void setNextRunTime(const ::trantor::Date &pNextRunTime) noexcept;
    void setNextRunTimeToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    static size_t getColumnNumber() noexcept {  return 19;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<ReportMailingJob>;
    friend drogon::orm::BaseBuilder<ReportMailingJob, true, true>;
    friend drogon::orm::BaseBuilder<ReportMailingJob, true, false>;
    friend drogon::orm::BaseBuilder<ReportMailingJob, false, true>;
    friend drogon::orm::BaseBuilder<ReportMailingJob, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<ReportMailingJob>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<std::string> reportName_;
    std::shared_ptr<std::string> reportParams_;
    std::shared_ptr<::trantor::Date> startDateTime_;
    std::shared_ptr<std::string> recurrence_;
    std::shared_ptr<std::string> emailRecipients_;
    std::shared_ptr<std::string> emailSubject_;
    std::shared_ptr<std::string> emailMessage_;
    std::shared_ptr<std::string> emailAttachmentFileFormat_;
    std::shared_ptr<bool> isActive_;
    std::shared_ptr<std::string> previousRunStatus_;
    std::shared_ptr<std::string> previousRunErrorMessage_;
    std::shared_ptr<::trantor::Date> previousRunStartTime_;
    std::shared_ptr<::trantor::Date> previousRunEndTime_;
    std::shared_ptr<::trantor::Date> nextRunTime_;
    std::shared_ptr<::trantor::Date> createdAt_;
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
            sql += "name,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "description,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "report_name,";
            ++parametersCount;
        }
        sql += "report_params,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        if(dirtyFlag_[5])
        {
            sql += "start_date_time,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "recurrence,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "email_recipients,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "email_subject,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "email_message,";
            ++parametersCount;
        }
        sql += "email_attachment_file_format,";
        ++parametersCount;
        if(!dirtyFlag_[10])
        {
            needSelection=true;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        if(dirtyFlag_[12])
        {
            sql += "previous_run_status,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "previous_run_error_message,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "previous_run_start_time,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "previous_run_end_time,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "next_run_time,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[17])
        {
            needSelection=true;
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
} // namespace TlNotificationDb
} // namespace drogon_model
