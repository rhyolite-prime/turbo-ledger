/**
 *  CreditBureauReport.cc
 *
 *  See CreditBureauReport.h for the hand-authored-subset note.
 *
 */

#include "CreditBureauReport.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string CreditBureauReport::Cols::_id = "\"id\"";
const std::string CreditBureauReport::Cols::_organisation_credit_bureau_id = "\"organisation_credit_bureau_id\"";
const std::string CreditBureauReport::Cols::_client_id = "\"client_id\"";
const std::string CreditBureauReport::Cols::_loan_id = "\"loan_id\"";
const std::string CreditBureauReport::Cols::_national_id = "\"national_id\"";
const std::string CreditBureauReport::Cols::_report_data = "\"report_data\"";
const std::string CreditBureauReport::Cols::_requested_by = "\"requested_by\"";
const std::string CreditBureauReport::Cols::_requested_on = "\"requested_on\"";
const std::string CreditBureauReport::Cols::_is_active = "\"is_active\"";
const std::string CreditBureauReport::primaryKeyName = "id";
const bool CreditBureauReport::hasPrimaryKey = true;
const std::string CreditBureauReport::tableName = "\"credit_bureau_report\"";

const std::vector<typename CreditBureauReport::MetaData> CreditBureauReport::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"organisation_credit_bureau_id","std::string","uuid",0,0,0,1},
{"client_id","std::string","uuid",0,0,0,0},
{"loan_id","std::string","uuid",0,0,0,0},
{"national_id","std::string","character varying",60,0,0,0},
{"report_data","std::string","jsonb",0,0,0,1},
{"requested_by","std::string","uuid",0,0,0,0},
{"requested_on","::trantor::Date","timestamp with time zone",0,0,0,1},
{"is_active","bool","boolean",1,0,0,1}
};
const std::string &CreditBureauReport::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
CreditBureauReport::CreditBureauReport(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["organisation_credit_bureau_id"].isNull())
        {
            organisationCreditBureauId_=std::make_shared<std::string>(r["organisation_credit_bureau_id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["loan_id"].isNull())
        {
            loanId_=std::make_shared<std::string>(r["loan_id"].as<std::string>());
        }
        if(!r["national_id"].isNull())
        {
            nationalId_=std::make_shared<std::string>(r["national_id"].as<std::string>());
        }
        if(!r["report_data"].isNull())
        {
            reportData_=std::make_shared<std::string>(r["report_data"].as<std::string>());
        }
        if(!r["requested_by"].isNull())
        {
            requestedBy_=std::make_shared<std::string>(r["requested_by"].as<std::string>());
        }
        if(!r["requested_on"].isNull())
        {
            auto timeStr = r["requested_on"].as<std::string>();
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
                requestedOn_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 9 > r.size())
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
            organisationCreditBureauId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            loanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            nationalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            reportData_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            requestedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
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
                requestedOn_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
    }

}
const std::string &CreditBureauReport::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauReport::getId() const noexcept
{
    return id_;
}
void CreditBureauReport::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void CreditBureauReport::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename CreditBureauReport::PrimaryKeyType & CreditBureauReport::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &CreditBureauReport::getValueOfOrganisationCreditBureauId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(organisationCreditBureauId_)
        return *organisationCreditBureauId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauReport::getOrganisationCreditBureauId() const noexcept
{
    return organisationCreditBureauId_;
}
void CreditBureauReport::setOrganisationCreditBureauId(const std::string &pOrganisationCreditBureauId) noexcept
{
    organisationCreditBureauId_ = std::make_shared<std::string>(pOrganisationCreditBureauId);
    dirtyFlag_[1] = true;
}
void CreditBureauReport::setOrganisationCreditBureauId(std::string &&pOrganisationCreditBureauId) noexcept
{
    organisationCreditBureauId_ = std::make_shared<std::string>(std::move(pOrganisationCreditBureauId));
    dirtyFlag_[1] = true;
}

const std::string &CreditBureauReport::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauReport::getClientId() const noexcept
{
    return clientId_;
}
void CreditBureauReport::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[2] = true;
}
void CreditBureauReport::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[2] = true;
}
void CreditBureauReport::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &CreditBureauReport::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauReport::getLoanId() const noexcept
{
    return loanId_;
}
void CreditBureauReport::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[3] = true;
}
void CreditBureauReport::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[3] = true;
}
void CreditBureauReport::setLoanIdToNull() noexcept
{
    loanId_.reset();
    dirtyFlag_[3] = true;
}

const std::string &CreditBureauReport::getValueOfNationalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(nationalId_)
        return *nationalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauReport::getNationalId() const noexcept
{
    return nationalId_;
}
void CreditBureauReport::setNationalId(const std::string &pNationalId) noexcept
{
    nationalId_ = std::make_shared<std::string>(pNationalId);
    dirtyFlag_[4] = true;
}
void CreditBureauReport::setNationalId(std::string &&pNationalId) noexcept
{
    nationalId_ = std::make_shared<std::string>(std::move(pNationalId));
    dirtyFlag_[4] = true;
}
void CreditBureauReport::setNationalIdToNull() noexcept
{
    nationalId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &CreditBureauReport::getValueOfReportData() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reportData_)
        return *reportData_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauReport::getReportData() const noexcept
{
    return reportData_;
}
void CreditBureauReport::setReportData(const std::string &pReportData) noexcept
{
    reportData_ = std::make_shared<std::string>(pReportData);
    dirtyFlag_[5] = true;
}
void CreditBureauReport::setReportData(std::string &&pReportData) noexcept
{
    reportData_ = std::make_shared<std::string>(std::move(pReportData));
    dirtyFlag_[5] = true;
}

const std::string &CreditBureauReport::getValueOfRequestedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(requestedBy_)
        return *requestedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauReport::getRequestedBy() const noexcept
{
    return requestedBy_;
}
void CreditBureauReport::setRequestedBy(const std::string &pRequestedBy) noexcept
{
    requestedBy_ = std::make_shared<std::string>(pRequestedBy);
    dirtyFlag_[6] = true;
}
void CreditBureauReport::setRequestedBy(std::string &&pRequestedBy) noexcept
{
    requestedBy_ = std::make_shared<std::string>(std::move(pRequestedBy));
    dirtyFlag_[6] = true;
}
void CreditBureauReport::setRequestedByToNull() noexcept
{
    requestedBy_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &CreditBureauReport::getValueOfRequestedOn() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(requestedOn_)
        return *requestedOn_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &CreditBureauReport::getRequestedOn() const noexcept
{
    return requestedOn_;
}
void CreditBureauReport::setRequestedOn(const ::trantor::Date &pRequestedOn) noexcept
{
    requestedOn_ = std::make_shared<::trantor::Date>(pRequestedOn);
    dirtyFlag_[7] = true;
}

const bool &CreditBureauReport::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &CreditBureauReport::getIsActive() const noexcept
{
    return isActive_;
}
void CreditBureauReport::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[8] = true;
}

void CreditBureauReport::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CreditBureauReport::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "organisation_credit_bureau_id",
        "client_id",
        "loan_id",
        "national_id",
        "report_data",
        "requested_by",
        "requested_on",
        "is_active"
    };
    return inCols;
}

void CreditBureauReport::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOrganisationCreditBureauId())
        {
            binder << getValueOfOrganisationCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getNationalId())
        {
            binder << getValueOfNationalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getReportData())
        {
            binder << getValueOfReportData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getRequestedBy())
        {
            binder << getValueOfRequestedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getRequestedOn())
        {
            binder << getValueOfRequestedOn();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> CreditBureauReport::updateColumns() const
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
    return ret;
}

void CreditBureauReport::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOrganisationCreditBureauId())
        {
            binder << getValueOfOrganisationCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getClientId())
        {
            binder << getValueOfClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getNationalId())
        {
            binder << getValueOfNationalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getReportData())
        {
            binder << getValueOfReportData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getRequestedBy())
        {
            binder << getValueOfRequestedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getRequestedOn())
        {
            binder << getValueOfRequestedOn();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
}
