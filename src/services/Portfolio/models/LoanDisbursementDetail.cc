/**
 *  LoanDisbursementDetail.cc
 *
 *  See LoanDisbursementDetail.h for the hand-authored-subset note.
 *
 */

#include "LoanDisbursementDetail.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanDisbursementDetail::Cols::_id = "\"id\"";
const std::string LoanDisbursementDetail::Cols::_loan_id = "\"loan_id\"";
const std::string LoanDisbursementDetail::Cols::_expected_disburse_date = "\"expected_disburse_date\"";
const std::string LoanDisbursementDetail::Cols::_actual_disburse_date = "\"actual_disburse_date\"";
const std::string LoanDisbursementDetail::Cols::_principal = "\"principal\"";
const std::string LoanDisbursementDetail::primaryKeyName = "id";
const bool LoanDisbursementDetail::hasPrimaryKey = true;
const std::string LoanDisbursementDetail::tableName = "\"loan_disbursement_detail\"";

const std::vector<typename LoanDisbursementDetail::MetaData> LoanDisbursementDetail::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"expected_disburse_date","::trantor::Date","date",0,0,0,1},
{"actual_disburse_date","::trantor::Date","date",0,0,0,0},
{"principal","std::string","numeric",0,0,0,1}
};
const std::string &LoanDisbursementDetail::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanDisbursementDetail::LoanDisbursementDetail(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["expected_disburse_date"].isNull())
        {
            auto daysStr = r["expected_disburse_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedDisburseDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["actual_disburse_date"].isNull())
        {
            auto daysStr = r["actual_disburse_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            actualDisburseDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["principal"].isNull())
        {
            principal_=std::make_shared<std::string>(r["principal"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 5 > r.size())
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
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            expectedDisburseDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            actualDisburseDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            principal_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &LoanDisbursementDetail::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanDisbursementDetail::getId() const noexcept
{
    return id_;
}
void LoanDisbursementDetail::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanDisbursementDetail::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanDisbursementDetail::PrimaryKeyType & LoanDisbursementDetail::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanDisbursementDetail::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanDisbursementDetail::getLoanId() const noexcept
{
    return loanId_;
}
void LoanDisbursementDetail::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanDisbursementDetail::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const ::trantor::Date &LoanDisbursementDetail::getValueOfExpectedDisburseDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(expectedDisburseDate_)
        return *expectedDisburseDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanDisbursementDetail::getExpectedDisburseDate() const noexcept
{
    return expectedDisburseDate_;
}
void LoanDisbursementDetail::setExpectedDisburseDate(const ::trantor::Date &pExpectedDisburseDate) noexcept
{
    expectedDisburseDate_ = std::make_shared<::trantor::Date>(pExpectedDisburseDate);
    dirtyFlag_[2] = true;
}

const ::trantor::Date &LoanDisbursementDetail::getValueOfActualDisburseDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(actualDisburseDate_)
        return *actualDisburseDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanDisbursementDetail::getActualDisburseDate() const noexcept
{
    return actualDisburseDate_;
}
void LoanDisbursementDetail::setActualDisburseDate(const ::trantor::Date &pActualDisburseDate) noexcept
{
    actualDisburseDate_ = std::make_shared<::trantor::Date>(pActualDisburseDate);
    dirtyFlag_[3] = true;
}
void LoanDisbursementDetail::setActualDisburseDateToNull() noexcept
{
    actualDisburseDate_.reset();
    dirtyFlag_[3] = true;
}

const std::string &LoanDisbursementDetail::getValueOfPrincipal() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principal_)
        return *principal_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanDisbursementDetail::getPrincipal() const noexcept
{
    return principal_;
}
void LoanDisbursementDetail::setPrincipal(const std::string &pPrincipal) noexcept
{
    principal_ = std::make_shared<std::string>(pPrincipal);
    dirtyFlag_[4] = true;
}
void LoanDisbursementDetail::setPrincipal(std::string &&pPrincipal) noexcept
{
    principal_ = std::make_shared<std::string>(std::move(pPrincipal));
    dirtyFlag_[4] = true;
}

void LoanDisbursementDetail::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanDisbursementDetail::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "expected_disburse_date",
        "actual_disburse_date",
        "principal"
    };
    return inCols;
}

void LoanDisbursementDetail::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExpectedDisburseDate())
        {
            binder << getValueOfExpectedDisburseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getActualDisburseDate())
        {
            binder << getValueOfActualDisburseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getPrincipal())
        {
            binder << getValueOfPrincipal();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> LoanDisbursementDetail::updateColumns() const
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
    return ret;
}

void LoanDisbursementDetail::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExpectedDisburseDate())
        {
            binder << getValueOfExpectedDisburseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getActualDisburseDate())
        {
            binder << getValueOfActualDisburseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getPrincipal())
        {
            binder << getValueOfPrincipal();
        }
        else
        {
            binder << nullptr;
        }
    }
}
