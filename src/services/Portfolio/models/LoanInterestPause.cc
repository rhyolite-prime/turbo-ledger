/**
 *  LoanInterestPause.cc
 *
 *  See LoanInterestPause.h for the hand-authored-subset note.
 *
 */

#include "LoanInterestPause.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanInterestPause::Cols::_id = "\"id\"";
const std::string LoanInterestPause::Cols::_loan_id = "\"loan_id\"";
const std::string LoanInterestPause::Cols::_external_id = "\"external_id\"";
const std::string LoanInterestPause::Cols::_start_date = "\"start_date\"";
const std::string LoanInterestPause::Cols::_end_date = "\"end_date\"";
const std::string LoanInterestPause::Cols::_created_by = "\"created_by\"";
const std::string LoanInterestPause::Cols::_created_at = "\"created_at\"";
const std::string LoanInterestPause::primaryKeyName = "id";
const bool LoanInterestPause::hasPrimaryKey = true;
const std::string LoanInterestPause::tableName = "\"loan_interest_pause\"";

const std::vector<typename LoanInterestPause::MetaData> LoanInterestPause::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"external_id","std::string","character varying",100,0,0,0},
{"start_date","::trantor::Date","date",0,0,0,1},
{"end_date","::trantor::Date","date",0,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanInterestPause::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanInterestPause::LoanInterestPause(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["start_date"].isNull())
        {
            auto daysStr = r["start_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["end_date"].isNull())
        {
            auto daysStr = r["end_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            endDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["created_by"].isNull())
        {
            createdBy_=std::make_shared<std::string>(r["created_by"].as<std::string>());
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
        if(offset + 7 > r.size())
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
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            startDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            endDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
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
const std::string &LoanInterestPause::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanInterestPause::getId() const noexcept
{
    return id_;
}
void LoanInterestPause::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanInterestPause::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanInterestPause::PrimaryKeyType & LoanInterestPause::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanInterestPause::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanInterestPause::getLoanId() const noexcept
{
    return loanId_;
}
void LoanInterestPause::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanInterestPause::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanInterestPause::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanInterestPause::getExternalId() const noexcept
{
    return externalId_;
}
void LoanInterestPause::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[2] = true;
}
void LoanInterestPause::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[2] = true;
}
void LoanInterestPause::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[2] = true;
}

const ::trantor::Date &LoanInterestPause::getValueOfStartDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(startDate_)
        return *startDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanInterestPause::getStartDate() const noexcept
{
    return startDate_;
}
void LoanInterestPause::setStartDate(const ::trantor::Date &pStartDate) noexcept
{
    startDate_ = std::make_shared<::trantor::Date>(pStartDate);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &LoanInterestPause::getValueOfEndDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(endDate_)
        return *endDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanInterestPause::getEndDate() const noexcept
{
    return endDate_;
}
void LoanInterestPause::setEndDate(const ::trantor::Date &pEndDate) noexcept
{
    endDate_ = std::make_shared<::trantor::Date>(pEndDate);
    dirtyFlag_[4] = true;
}

const std::string &LoanInterestPause::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanInterestPause::getCreatedBy() const noexcept
{
    return createdBy_;
}
void LoanInterestPause::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[5] = true;
}
void LoanInterestPause::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[5] = true;
}
void LoanInterestPause::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &LoanInterestPause::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanInterestPause::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanInterestPause::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[6] = true;
}

void LoanInterestPause::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanInterestPause::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "external_id",
        "start_date",
        "end_date",
        "created_by",
        "created_at"
    };
    return inCols;
}

void LoanInterestPause::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getEndDate())
        {
            binder << getValueOfEndDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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

const std::vector<std::string> LoanInterestPause::updateColumns() const
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
    return ret;
}

void LoanInterestPause::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getStartDate())
        {
            binder << getValueOfStartDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getEndDate())
        {
            binder << getValueOfEndDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
