/**
 *  RescheduleLoanRequest.cc
 *
 *  See RescheduleLoanRequest.h for the hand-authored-subset note.
 *
 */

#include "RescheduleLoanRequest.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string RescheduleLoanRequest::Cols::_id = "\"id\"";
const std::string RescheduleLoanRequest::Cols::_loan_id = "\"loan_id\"";
const std::string RescheduleLoanRequest::Cols::_reason_code = "\"reason_code\"";
const std::string RescheduleLoanRequest::Cols::_reason_comment = "\"reason_comment\"";
const std::string RescheduleLoanRequest::Cols::_status = "\"status\"";
const std::string RescheduleLoanRequest::Cols::_reschedule_from_installment = "\"reschedule_from_installment\"";
const std::string RescheduleLoanRequest::Cols::_reschedule_from_date = "\"reschedule_from_date\"";
const std::string RescheduleLoanRequest::Cols::_submitted_on_date = "\"submitted_on_date\"";
const std::string RescheduleLoanRequest::Cols::_submitted_by = "\"submitted_by\"";
const std::string RescheduleLoanRequest::Cols::_extra_terms = "\"extra_terms\"";
const std::string RescheduleLoanRequest::Cols::_grace_on_principal = "\"grace_on_principal\"";
const std::string RescheduleLoanRequest::Cols::_grace_on_interest = "\"grace_on_interest\"";
const std::string RescheduleLoanRequest::Cols::_new_interest_rate = "\"new_interest_rate\"";
const std::string RescheduleLoanRequest::Cols::_adjusted_due_date = "\"adjusted_due_date\"";
const std::string RescheduleLoanRequest::Cols::_approved_on_date = "\"approved_on_date\"";
const std::string RescheduleLoanRequest::Cols::_approved_by = "\"approved_by\"";
const std::string RescheduleLoanRequest::Cols::_created_at = "\"created_at\"";
const std::string RescheduleLoanRequest::primaryKeyName = "id";
const bool RescheduleLoanRequest::hasPrimaryKey = true;
const std::string RescheduleLoanRequest::tableName = "\"reschedule_loan_request\"";

const std::vector<typename RescheduleLoanRequest::MetaData> RescheduleLoanRequest::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"reason_code","std::string","character varying",100,0,0,1},
{"reason_comment","std::string","text",0,0,0,0},
{"status","int32_t","integer",4,0,0,1},
{"reschedule_from_installment","int32_t","integer",4,0,0,0},
{"reschedule_from_date","::trantor::Date","date",0,0,0,0},
{"submitted_on_date","::trantor::Date","date",0,0,0,1},
{"submitted_by","std::string","uuid",0,0,0,0},
{"extra_terms","int32_t","integer",4,0,0,0},
{"grace_on_principal","int32_t","integer",4,0,0,0},
{"grace_on_interest","int32_t","integer",4,0,0,0},
{"new_interest_rate","std::string","numeric",0,0,0,0},
{"adjusted_due_date","::trantor::Date","date",0,0,0,0},
{"approved_on_date","::trantor::Date","date",0,0,0,0},
{"approved_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &RescheduleLoanRequest::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
RescheduleLoanRequest::RescheduleLoanRequest(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["loan_id"].isNull())
        {
            loanId_=std::make_shared<std::string>(r["loan_id"].as<std::string>());
        }
        if(!r["reason_code"].isNull())
        {
            reasonCode_=std::make_shared<std::string>(r["reason_code"].as<std::string>());
        }
        if(!r["reason_comment"].isNull())
        {
            reasonComment_=std::make_shared<std::string>(r["reason_comment"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["reschedule_from_installment"].isNull())
        {
            rescheduleFromInstallment_=std::make_shared<int32_t>(r["reschedule_from_installment"].as<int32_t>());
        }
        if(!r["reschedule_from_date"].isNull())
        {
            auto daysStr = r["reschedule_from_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rescheduleFromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["submitted_on_date"].isNull())
        {
            auto daysStr = r["submitted_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["submitted_by"].isNull())
        {
            submittedBy_=std::make_shared<std::string>(r["submitted_by"].as<std::string>());
        }
        if(!r["extra_terms"].isNull())
        {
            extraTerms_=std::make_shared<int32_t>(r["extra_terms"].as<int32_t>());
        }
        if(!r["grace_on_principal"].isNull())
        {
            graceOnPrincipal_=std::make_shared<int32_t>(r["grace_on_principal"].as<int32_t>());
        }
        if(!r["grace_on_interest"].isNull())
        {
            graceOnInterest_=std::make_shared<int32_t>(r["grace_on_interest"].as<int32_t>());
        }
        if(!r["new_interest_rate"].isNull())
        {
            newInterestRate_=std::make_shared<std::string>(r["new_interest_rate"].as<std::string>());
        }
        if(!r["adjusted_due_date"].isNull())
        {
            auto daysStr = r["adjusted_due_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            adjustedDueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["approved_on_date"].isNull())
        {
            auto daysStr = r["approved_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            approvedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["approved_by"].isNull())
        {
            approvedBy_=std::make_shared<std::string>(r["approved_by"].as<std::string>());
        }
        if(!r["created_at"].isNull())
        {
            auto timeStr = r["created_at"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 17 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            loanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            reasonCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            reasonComment_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            rescheduleFromInstallment_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rescheduleFromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            submittedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            extraTerms_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            graceOnPrincipal_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            graceOnInterest_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            newInterestRate_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            adjustedDueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            approvedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            approvedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &RescheduleLoanRequest::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RescheduleLoanRequest::getId() const noexcept
{
    return id_;
}
void RescheduleLoanRequest::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void RescheduleLoanRequest::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename RescheduleLoanRequest::PrimaryKeyType & RescheduleLoanRequest::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &RescheduleLoanRequest::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RescheduleLoanRequest::getLoanId() const noexcept
{
    return loanId_;
}
void RescheduleLoanRequest::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void RescheduleLoanRequest::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &RescheduleLoanRequest::getValueOfReasonCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reasonCode_)
        return *reasonCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RescheduleLoanRequest::getReasonCode() const noexcept
{
    return reasonCode_;
}
void RescheduleLoanRequest::setReasonCode(const std::string &pReasonCode) noexcept
{
    reasonCode_ = std::make_shared<std::string>(pReasonCode);
    dirtyFlag_[2] = true;
}
void RescheduleLoanRequest::setReasonCode(std::string &&pReasonCode) noexcept
{
    reasonCode_ = std::make_shared<std::string>(std::move(pReasonCode));
    dirtyFlag_[2] = true;
}

const std::string &RescheduleLoanRequest::getValueOfReasonComment() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reasonComment_)
        return *reasonComment_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RescheduleLoanRequest::getReasonComment() const noexcept
{
    return reasonComment_;
}
void RescheduleLoanRequest::setReasonComment(const std::string &pReasonComment) noexcept
{
    reasonComment_ = std::make_shared<std::string>(pReasonComment);
    dirtyFlag_[3] = true;
}
void RescheduleLoanRequest::setReasonComment(std::string &&pReasonComment) noexcept
{
    reasonComment_ = std::make_shared<std::string>(std::move(pReasonComment));
    dirtyFlag_[3] = true;
}
void RescheduleLoanRequest::setReasonCommentToNull() noexcept
{
    reasonComment_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &RescheduleLoanRequest::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RescheduleLoanRequest::getStatus() const noexcept
{
    return status_;
}
void RescheduleLoanRequest::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[4] = true;
}

const int32_t &RescheduleLoanRequest::getValueOfRescheduleFromInstallment() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(rescheduleFromInstallment_)
        return *rescheduleFromInstallment_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RescheduleLoanRequest::getRescheduleFromInstallment() const noexcept
{
    return rescheduleFromInstallment_;
}
void RescheduleLoanRequest::setRescheduleFromInstallment(const int32_t &pRescheduleFromInstallment) noexcept
{
    rescheduleFromInstallment_ = std::make_shared<int32_t>(pRescheduleFromInstallment);
    dirtyFlag_[5] = true;
}
void RescheduleLoanRequest::setRescheduleFromInstallmentToNull() noexcept
{
    rescheduleFromInstallment_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &RescheduleLoanRequest::getValueOfRescheduleFromDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(rescheduleFromDate_)
        return *rescheduleFromDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RescheduleLoanRequest::getRescheduleFromDate() const noexcept
{
    return rescheduleFromDate_;
}
void RescheduleLoanRequest::setRescheduleFromDate(const ::trantor::Date &pRescheduleFromDate) noexcept
{
    rescheduleFromDate_ = std::make_shared<::trantor::Date>(pRescheduleFromDate);
    dirtyFlag_[6] = true;
}
void RescheduleLoanRequest::setRescheduleFromDateToNull() noexcept
{
    rescheduleFromDate_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &RescheduleLoanRequest::getValueOfSubmittedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedOnDate_)
        return *submittedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RescheduleLoanRequest::getSubmittedOnDate() const noexcept
{
    return submittedOnDate_;
}
void RescheduleLoanRequest::setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept
{
    submittedOnDate_ = std::make_shared<::trantor::Date>(pSubmittedOnDate);
    dirtyFlag_[7] = true;
}

const std::string &RescheduleLoanRequest::getValueOfSubmittedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(submittedBy_)
        return *submittedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RescheduleLoanRequest::getSubmittedBy() const noexcept
{
    return submittedBy_;
}
void RescheduleLoanRequest::setSubmittedBy(const std::string &pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(pSubmittedBy);
    dirtyFlag_[8] = true;
}
void RescheduleLoanRequest::setSubmittedBy(std::string &&pSubmittedBy) noexcept
{
    submittedBy_ = std::make_shared<std::string>(std::move(pSubmittedBy));
    dirtyFlag_[8] = true;
}
void RescheduleLoanRequest::setSubmittedByToNull() noexcept
{
    submittedBy_.reset();
    dirtyFlag_[8] = true;
}

const int32_t &RescheduleLoanRequest::getValueOfExtraTerms() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(extraTerms_)
        return *extraTerms_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RescheduleLoanRequest::getExtraTerms() const noexcept
{
    return extraTerms_;
}
void RescheduleLoanRequest::setExtraTerms(const int32_t &pExtraTerms) noexcept
{
    extraTerms_ = std::make_shared<int32_t>(pExtraTerms);
    dirtyFlag_[9] = true;
}
void RescheduleLoanRequest::setExtraTermsToNull() noexcept
{
    extraTerms_.reset();
    dirtyFlag_[9] = true;
}

const int32_t &RescheduleLoanRequest::getValueOfGraceOnPrincipal() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnPrincipal_)
        return *graceOnPrincipal_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RescheduleLoanRequest::getGraceOnPrincipal() const noexcept
{
    return graceOnPrincipal_;
}
void RescheduleLoanRequest::setGraceOnPrincipal(const int32_t &pGraceOnPrincipal) noexcept
{
    graceOnPrincipal_ = std::make_shared<int32_t>(pGraceOnPrincipal);
    dirtyFlag_[10] = true;
}
void RescheduleLoanRequest::setGraceOnPrincipalToNull() noexcept
{
    graceOnPrincipal_.reset();
    dirtyFlag_[10] = true;
}

const int32_t &RescheduleLoanRequest::getValueOfGraceOnInterest() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(graceOnInterest_)
        return *graceOnInterest_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RescheduleLoanRequest::getGraceOnInterest() const noexcept
{
    return graceOnInterest_;
}
void RescheduleLoanRequest::setGraceOnInterest(const int32_t &pGraceOnInterest) noexcept
{
    graceOnInterest_ = std::make_shared<int32_t>(pGraceOnInterest);
    dirtyFlag_[11] = true;
}
void RescheduleLoanRequest::setGraceOnInterestToNull() noexcept
{
    graceOnInterest_.reset();
    dirtyFlag_[11] = true;
}

const std::string &RescheduleLoanRequest::getValueOfNewInterestRate() const noexcept
{
    static const std::string defaultValue = std::string();
    if(newInterestRate_)
        return *newInterestRate_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RescheduleLoanRequest::getNewInterestRate() const noexcept
{
    return newInterestRate_;
}
void RescheduleLoanRequest::setNewInterestRate(const std::string &pNewInterestRate) noexcept
{
    newInterestRate_ = std::make_shared<std::string>(pNewInterestRate);
    dirtyFlag_[12] = true;
}
void RescheduleLoanRequest::setNewInterestRate(std::string &&pNewInterestRate) noexcept
{
    newInterestRate_ = std::make_shared<std::string>(std::move(pNewInterestRate));
    dirtyFlag_[12] = true;
}
void RescheduleLoanRequest::setNewInterestRateToNull() noexcept
{
    newInterestRate_.reset();
    dirtyFlag_[12] = true;
}

const ::trantor::Date &RescheduleLoanRequest::getValueOfAdjustedDueDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(adjustedDueDate_)
        return *adjustedDueDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RescheduleLoanRequest::getAdjustedDueDate() const noexcept
{
    return adjustedDueDate_;
}
void RescheduleLoanRequest::setAdjustedDueDate(const ::trantor::Date &pAdjustedDueDate) noexcept
{
    adjustedDueDate_ = std::make_shared<::trantor::Date>(pAdjustedDueDate);
    dirtyFlag_[13] = true;
}
void RescheduleLoanRequest::setAdjustedDueDateToNull() noexcept
{
    adjustedDueDate_.reset();
    dirtyFlag_[13] = true;
}

const ::trantor::Date &RescheduleLoanRequest::getValueOfApprovedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(approvedOnDate_)
        return *approvedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RescheduleLoanRequest::getApprovedOnDate() const noexcept
{
    return approvedOnDate_;
}
void RescheduleLoanRequest::setApprovedOnDate(const ::trantor::Date &pApprovedOnDate) noexcept
{
    approvedOnDate_ = std::make_shared<::trantor::Date>(pApprovedOnDate);
    dirtyFlag_[14] = true;
}
void RescheduleLoanRequest::setApprovedOnDateToNull() noexcept
{
    approvedOnDate_.reset();
    dirtyFlag_[14] = true;
}

const std::string &RescheduleLoanRequest::getValueOfApprovedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(approvedBy_)
        return *approvedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &RescheduleLoanRequest::getApprovedBy() const noexcept
{
    return approvedBy_;
}
void RescheduleLoanRequest::setApprovedBy(const std::string &pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(pApprovedBy);
    dirtyFlag_[15] = true;
}
void RescheduleLoanRequest::setApprovedBy(std::string &&pApprovedBy) noexcept
{
    approvedBy_ = std::make_shared<std::string>(std::move(pApprovedBy));
    dirtyFlag_[15] = true;
}
void RescheduleLoanRequest::setApprovedByToNull() noexcept
{
    approvedBy_.reset();
    dirtyFlag_[15] = true;
}

const ::trantor::Date &RescheduleLoanRequest::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RescheduleLoanRequest::getCreatedAt() const noexcept
{
    return createdAt_;
}
void RescheduleLoanRequest::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[16] = true;
}

void RescheduleLoanRequest::updateId(const uint64_t id)
{
}

const std::vector<std::string> &RescheduleLoanRequest::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "reason_code",
        "reason_comment",
        "status",
        "reschedule_from_installment",
        "reschedule_from_date",
        "submitted_on_date",
        "submitted_by",
        "extra_terms",
        "grace_on_principal",
        "grace_on_interest",
        "new_interest_rate",
        "adjusted_due_date",
        "approved_on_date",
        "approved_by",
        "created_at"
    };
    return inCols;
}

void RescheduleLoanRequest::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getReasonCode())
        {
            binder << getValueOfReasonCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getReasonComment())
        {
            binder << getValueOfReasonComment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getRescheduleFromInstallment())
        {
            binder << getValueOfRescheduleFromInstallment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getRescheduleFromDate())
        {
            binder << getValueOfRescheduleFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getSubmittedBy())
        {
            binder << getValueOfSubmittedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getExtraTerms())
        {
            binder << getValueOfExtraTerms();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getGraceOnPrincipal())
        {
            binder << getValueOfGraceOnPrincipal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getGraceOnInterest())
        {
            binder << getValueOfGraceOnInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getNewInterestRate())
        {
            binder << getValueOfNewInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getAdjustedDueDate())
        {
            binder << getValueOfAdjustedDueDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getApprovedOnDate())
        {
            binder << getValueOfApprovedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getApprovedBy())
        {
            binder << getValueOfApprovedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> RescheduleLoanRequest::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    if(dirtyFlag_[6])
    {
        ret.push_back(getColumnName(6));
    }
    if(dirtyFlag_[7])
    {
        ret.push_back(getColumnName(7));
    }
    if(dirtyFlag_[8])
    {
        ret.push_back(getColumnName(8));
    }
    if(dirtyFlag_[9])
    {
        ret.push_back(getColumnName(9));
    }
    if(dirtyFlag_[10])
    {
        ret.push_back(getColumnName(10));
    }
    if(dirtyFlag_[11])
    {
        ret.push_back(getColumnName(11));
    }
    if(dirtyFlag_[12])
    {
        ret.push_back(getColumnName(12));
    }
    if(dirtyFlag_[13])
    {
        ret.push_back(getColumnName(13));
    }
    if(dirtyFlag_[14])
    {
        ret.push_back(getColumnName(14));
    }
    if(dirtyFlag_[15])
    {
        ret.push_back(getColumnName(15));
    }
    if(dirtyFlag_[16])
    {
        ret.push_back(getColumnName(16));
    }
    return ret;
}

void RescheduleLoanRequest::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getReasonCode())
        {
            binder << getValueOfReasonCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getReasonComment())
        {
            binder << getValueOfReasonComment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getRescheduleFromInstallment())
        {
            binder << getValueOfRescheduleFromInstallment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getRescheduleFromDate())
        {
            binder << getValueOfRescheduleFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getSubmittedBy())
        {
            binder << getValueOfSubmittedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getExtraTerms())
        {
            binder << getValueOfExtraTerms();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getGraceOnPrincipal())
        {
            binder << getValueOfGraceOnPrincipal();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getGraceOnInterest())
        {
            binder << getValueOfGraceOnInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getNewInterestRate())
        {
            binder << getValueOfNewInterestRate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getAdjustedDueDate())
        {
            binder << getValueOfAdjustedDueDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getApprovedOnDate())
        {
            binder << getValueOfApprovedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getApprovedBy())
        {
            binder << getValueOfApprovedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}
