/**
 *  LoanRepaymentScheduleInstallment.cc
 *
 *  See LoanRepaymentScheduleInstallment.h for the hand-authored-subset note.
 *
 */

#include "LoanRepaymentScheduleInstallment.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanRepaymentScheduleInstallment::Cols::_id = "\"id\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_loan_id = "\"loan_id\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_installment_number = "\"installment_number\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_from_date = "\"from_date\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_due_date = "\"due_date\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_principal_amount = "\"principal_amount\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_principal_completed_derived = "\"principal_completed_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_principal_writtenoff_derived = "\"principal_writtenoff_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_interest_amount = "\"interest_amount\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_interest_completed_derived = "\"interest_completed_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_interest_waived_derived = "\"interest_waived_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_interest_writtenoff_derived = "\"interest_writtenoff_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_fee_charges_amount = "\"fee_charges_amount\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_fee_charges_completed_derived = "\"fee_charges_completed_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_fee_charges_waived_derived = "\"fee_charges_waived_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_penalty_charges_amount = "\"penalty_charges_amount\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_penalty_charges_completed_derived = "\"penalty_charges_completed_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_penalty_charges_waived_derived = "\"penalty_charges_waived_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_completed_derived = "\"completed_derived\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_obligations_met_on_date = "\"obligations_met_on_date\"";
const std::string LoanRepaymentScheduleInstallment::Cols::_recalculated_interest = "\"recalculated_interest\"";
const std::string LoanRepaymentScheduleInstallment::primaryKeyName = "id";
const bool LoanRepaymentScheduleInstallment::hasPrimaryKey = true;
const std::string LoanRepaymentScheduleInstallment::tableName = "\"loan_repayment_schedule_installment\"";

const std::vector<typename LoanRepaymentScheduleInstallment::MetaData> LoanRepaymentScheduleInstallment::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"installment_number","int32_t","integer",4,0,0,1},
{"from_date","::trantor::Date","date",0,0,0,1},
{"due_date","::trantor::Date","date",0,0,0,1},
{"principal_amount","std::string","numeric",0,0,0,1},
{"principal_completed_derived","std::string","numeric",0,0,0,1},
{"principal_writtenoff_derived","std::string","numeric",0,0,0,1},
{"interest_amount","std::string","numeric",0,0,0,1},
{"interest_completed_derived","std::string","numeric",0,0,0,1},
{"interest_waived_derived","std::string","numeric",0,0,0,1},
{"interest_writtenoff_derived","std::string","numeric",0,0,0,1},
{"fee_charges_amount","std::string","numeric",0,0,0,1},
{"fee_charges_completed_derived","std::string","numeric",0,0,0,1},
{"fee_charges_waived_derived","std::string","numeric",0,0,0,1},
{"penalty_charges_amount","std::string","numeric",0,0,0,1},
{"penalty_charges_completed_derived","std::string","numeric",0,0,0,1},
{"penalty_charges_waived_derived","std::string","numeric",0,0,0,1},
{"completed_derived","bool","boolean",1,0,0,1},
{"obligations_met_on_date","::trantor::Date","date",0,0,0,0},
{"recalculated_interest","bool","boolean",1,0,0,1}
};
const std::string &LoanRepaymentScheduleInstallment::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanRepaymentScheduleInstallment::LoanRepaymentScheduleInstallment(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["installment_number"].isNull())
        {
            installmentNumber_=std::make_shared<int32_t>(r["installment_number"].as<int32_t>());
        }
        if(!r["from_date"].isNull())
        {
            auto daysStr = r["from_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            fromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["due_date"].isNull())
        {
            auto daysStr = r["due_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["principal_amount"].isNull())
        {
            principalAmount_=std::make_shared<std::string>(r["principal_amount"].as<std::string>());
        }
        if(!r["principal_completed_derived"].isNull())
        {
            principalCompletedDerived_=std::make_shared<std::string>(r["principal_completed_derived"].as<std::string>());
        }
        if(!r["principal_writtenoff_derived"].isNull())
        {
            principalWrittenoffDerived_=std::make_shared<std::string>(r["principal_writtenoff_derived"].as<std::string>());
        }
        if(!r["interest_amount"].isNull())
        {
            interestAmount_=std::make_shared<std::string>(r["interest_amount"].as<std::string>());
        }
        if(!r["interest_completed_derived"].isNull())
        {
            interestCompletedDerived_=std::make_shared<std::string>(r["interest_completed_derived"].as<std::string>());
        }
        if(!r["interest_waived_derived"].isNull())
        {
            interestWaivedDerived_=std::make_shared<std::string>(r["interest_waived_derived"].as<std::string>());
        }
        if(!r["interest_writtenoff_derived"].isNull())
        {
            interestWrittenoffDerived_=std::make_shared<std::string>(r["interest_writtenoff_derived"].as<std::string>());
        }
        if(!r["fee_charges_amount"].isNull())
        {
            feeChargesAmount_=std::make_shared<std::string>(r["fee_charges_amount"].as<std::string>());
        }
        if(!r["fee_charges_completed_derived"].isNull())
        {
            feeChargesCompletedDerived_=std::make_shared<std::string>(r["fee_charges_completed_derived"].as<std::string>());
        }
        if(!r["fee_charges_waived_derived"].isNull())
        {
            feeChargesWaivedDerived_=std::make_shared<std::string>(r["fee_charges_waived_derived"].as<std::string>());
        }
        if(!r["penalty_charges_amount"].isNull())
        {
            penaltyChargesAmount_=std::make_shared<std::string>(r["penalty_charges_amount"].as<std::string>());
        }
        if(!r["penalty_charges_completed_derived"].isNull())
        {
            penaltyChargesCompletedDerived_=std::make_shared<std::string>(r["penalty_charges_completed_derived"].as<std::string>());
        }
        if(!r["penalty_charges_waived_derived"].isNull())
        {
            penaltyChargesWaivedDerived_=std::make_shared<std::string>(r["penalty_charges_waived_derived"].as<std::string>());
        }
        if(!r["completed_derived"].isNull())
        {
            completedDerived_=std::make_shared<bool>(r["completed_derived"].as<bool>());
        }
        if(!r["obligations_met_on_date"].isNull())
        {
            auto daysStr = r["obligations_met_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            obligationsMetOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["recalculated_interest"].isNull())
        {
            recalculatedInterest_=std::make_shared<bool>(r["recalculated_interest"].as<bool>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 21 > r.size())
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
            installmentNumber_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            fromDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dueDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            principalAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            principalCompletedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            principalWrittenoffDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            interestAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            interestCompletedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            interestWaivedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            interestWrittenoffDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            feeChargesAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            feeChargesCompletedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            feeChargesWaivedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            penaltyChargesAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            penaltyChargesCompletedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            penaltyChargesWaivedDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            completedDerived_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            obligationsMetOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            recalculatedInterest_=std::make_shared<bool>(r[index].as<bool>());
        }
    }

}
const std::string &LoanRepaymentScheduleInstallment::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getId() const noexcept
{
    return id_;
}
void LoanRepaymentScheduleInstallment::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanRepaymentScheduleInstallment::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanRepaymentScheduleInstallment::PrimaryKeyType & LoanRepaymentScheduleInstallment::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getLoanId() const noexcept
{
    return loanId_;
}
void LoanRepaymentScheduleInstallment::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanRepaymentScheduleInstallment::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const int32_t &LoanRepaymentScheduleInstallment::getValueOfInstallmentNumber() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(installmentNumber_)
        return *installmentNumber_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanRepaymentScheduleInstallment::getInstallmentNumber() const noexcept
{
    return installmentNumber_;
}
void LoanRepaymentScheduleInstallment::setInstallmentNumber(const int32_t &pInstallmentNumber) noexcept
{
    installmentNumber_ = std::make_shared<int32_t>(pInstallmentNumber);
    dirtyFlag_[2] = true;
}

const ::trantor::Date &LoanRepaymentScheduleInstallment::getValueOfFromDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(fromDate_)
        return *fromDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanRepaymentScheduleInstallment::getFromDate() const noexcept
{
    return fromDate_;
}
void LoanRepaymentScheduleInstallment::setFromDate(const ::trantor::Date &pFromDate) noexcept
{
    fromDate_ = std::make_shared<::trantor::Date>(pFromDate);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &LoanRepaymentScheduleInstallment::getValueOfDueDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dueDate_)
        return *dueDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanRepaymentScheduleInstallment::getDueDate() const noexcept
{
    return dueDate_;
}
void LoanRepaymentScheduleInstallment::setDueDate(const ::trantor::Date &pDueDate) noexcept
{
    dueDate_ = std::make_shared<::trantor::Date>(pDueDate);
    dirtyFlag_[4] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfPrincipalAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalAmount_)
        return *principalAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getPrincipalAmount() const noexcept
{
    return principalAmount_;
}
void LoanRepaymentScheduleInstallment::setPrincipalAmount(const std::string &pPrincipalAmount) noexcept
{
    principalAmount_ = std::make_shared<std::string>(pPrincipalAmount);
    dirtyFlag_[5] = true;
}
void LoanRepaymentScheduleInstallment::setPrincipalAmount(std::string &&pPrincipalAmount) noexcept
{
    principalAmount_ = std::make_shared<std::string>(std::move(pPrincipalAmount));
    dirtyFlag_[5] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfPrincipalCompletedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalCompletedDerived_)
        return *principalCompletedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getPrincipalCompletedDerived() const noexcept
{
    return principalCompletedDerived_;
}
void LoanRepaymentScheduleInstallment::setPrincipalCompletedDerived(const std::string &pPrincipalCompletedDerived) noexcept
{
    principalCompletedDerived_ = std::make_shared<std::string>(pPrincipalCompletedDerived);
    dirtyFlag_[6] = true;
}
void LoanRepaymentScheduleInstallment::setPrincipalCompletedDerived(std::string &&pPrincipalCompletedDerived) noexcept
{
    principalCompletedDerived_ = std::make_shared<std::string>(std::move(pPrincipalCompletedDerived));
    dirtyFlag_[6] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfPrincipalWrittenoffDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalWrittenoffDerived_)
        return *principalWrittenoffDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getPrincipalWrittenoffDerived() const noexcept
{
    return principalWrittenoffDerived_;
}
void LoanRepaymentScheduleInstallment::setPrincipalWrittenoffDerived(const std::string &pPrincipalWrittenoffDerived) noexcept
{
    principalWrittenoffDerived_ = std::make_shared<std::string>(pPrincipalWrittenoffDerived);
    dirtyFlag_[7] = true;
}
void LoanRepaymentScheduleInstallment::setPrincipalWrittenoffDerived(std::string &&pPrincipalWrittenoffDerived) noexcept
{
    principalWrittenoffDerived_ = std::make_shared<std::string>(std::move(pPrincipalWrittenoffDerived));
    dirtyFlag_[7] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfInterestAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestAmount_)
        return *interestAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getInterestAmount() const noexcept
{
    return interestAmount_;
}
void LoanRepaymentScheduleInstallment::setInterestAmount(const std::string &pInterestAmount) noexcept
{
    interestAmount_ = std::make_shared<std::string>(pInterestAmount);
    dirtyFlag_[8] = true;
}
void LoanRepaymentScheduleInstallment::setInterestAmount(std::string &&pInterestAmount) noexcept
{
    interestAmount_ = std::make_shared<std::string>(std::move(pInterestAmount));
    dirtyFlag_[8] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfInterestCompletedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestCompletedDerived_)
        return *interestCompletedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getInterestCompletedDerived() const noexcept
{
    return interestCompletedDerived_;
}
void LoanRepaymentScheduleInstallment::setInterestCompletedDerived(const std::string &pInterestCompletedDerived) noexcept
{
    interestCompletedDerived_ = std::make_shared<std::string>(pInterestCompletedDerived);
    dirtyFlag_[9] = true;
}
void LoanRepaymentScheduleInstallment::setInterestCompletedDerived(std::string &&pInterestCompletedDerived) noexcept
{
    interestCompletedDerived_ = std::make_shared<std::string>(std::move(pInterestCompletedDerived));
    dirtyFlag_[9] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfInterestWaivedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestWaivedDerived_)
        return *interestWaivedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getInterestWaivedDerived() const noexcept
{
    return interestWaivedDerived_;
}
void LoanRepaymentScheduleInstallment::setInterestWaivedDerived(const std::string &pInterestWaivedDerived) noexcept
{
    interestWaivedDerived_ = std::make_shared<std::string>(pInterestWaivedDerived);
    dirtyFlag_[10] = true;
}
void LoanRepaymentScheduleInstallment::setInterestWaivedDerived(std::string &&pInterestWaivedDerived) noexcept
{
    interestWaivedDerived_ = std::make_shared<std::string>(std::move(pInterestWaivedDerived));
    dirtyFlag_[10] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfInterestWrittenoffDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestWrittenoffDerived_)
        return *interestWrittenoffDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getInterestWrittenoffDerived() const noexcept
{
    return interestWrittenoffDerived_;
}
void LoanRepaymentScheduleInstallment::setInterestWrittenoffDerived(const std::string &pInterestWrittenoffDerived) noexcept
{
    interestWrittenoffDerived_ = std::make_shared<std::string>(pInterestWrittenoffDerived);
    dirtyFlag_[11] = true;
}
void LoanRepaymentScheduleInstallment::setInterestWrittenoffDerived(std::string &&pInterestWrittenoffDerived) noexcept
{
    interestWrittenoffDerived_ = std::make_shared<std::string>(std::move(pInterestWrittenoffDerived));
    dirtyFlag_[11] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfFeeChargesAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesAmount_)
        return *feeChargesAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getFeeChargesAmount() const noexcept
{
    return feeChargesAmount_;
}
void LoanRepaymentScheduleInstallment::setFeeChargesAmount(const std::string &pFeeChargesAmount) noexcept
{
    feeChargesAmount_ = std::make_shared<std::string>(pFeeChargesAmount);
    dirtyFlag_[12] = true;
}
void LoanRepaymentScheduleInstallment::setFeeChargesAmount(std::string &&pFeeChargesAmount) noexcept
{
    feeChargesAmount_ = std::make_shared<std::string>(std::move(pFeeChargesAmount));
    dirtyFlag_[12] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfFeeChargesCompletedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesCompletedDerived_)
        return *feeChargesCompletedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getFeeChargesCompletedDerived() const noexcept
{
    return feeChargesCompletedDerived_;
}
void LoanRepaymentScheduleInstallment::setFeeChargesCompletedDerived(const std::string &pFeeChargesCompletedDerived) noexcept
{
    feeChargesCompletedDerived_ = std::make_shared<std::string>(pFeeChargesCompletedDerived);
    dirtyFlag_[13] = true;
}
void LoanRepaymentScheduleInstallment::setFeeChargesCompletedDerived(std::string &&pFeeChargesCompletedDerived) noexcept
{
    feeChargesCompletedDerived_ = std::make_shared<std::string>(std::move(pFeeChargesCompletedDerived));
    dirtyFlag_[13] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfFeeChargesWaivedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesWaivedDerived_)
        return *feeChargesWaivedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getFeeChargesWaivedDerived() const noexcept
{
    return feeChargesWaivedDerived_;
}
void LoanRepaymentScheduleInstallment::setFeeChargesWaivedDerived(const std::string &pFeeChargesWaivedDerived) noexcept
{
    feeChargesWaivedDerived_ = std::make_shared<std::string>(pFeeChargesWaivedDerived);
    dirtyFlag_[14] = true;
}
void LoanRepaymentScheduleInstallment::setFeeChargesWaivedDerived(std::string &&pFeeChargesWaivedDerived) noexcept
{
    feeChargesWaivedDerived_ = std::make_shared<std::string>(std::move(pFeeChargesWaivedDerived));
    dirtyFlag_[14] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfPenaltyChargesAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesAmount_)
        return *penaltyChargesAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getPenaltyChargesAmount() const noexcept
{
    return penaltyChargesAmount_;
}
void LoanRepaymentScheduleInstallment::setPenaltyChargesAmount(const std::string &pPenaltyChargesAmount) noexcept
{
    penaltyChargesAmount_ = std::make_shared<std::string>(pPenaltyChargesAmount);
    dirtyFlag_[15] = true;
}
void LoanRepaymentScheduleInstallment::setPenaltyChargesAmount(std::string &&pPenaltyChargesAmount) noexcept
{
    penaltyChargesAmount_ = std::make_shared<std::string>(std::move(pPenaltyChargesAmount));
    dirtyFlag_[15] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfPenaltyChargesCompletedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesCompletedDerived_)
        return *penaltyChargesCompletedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getPenaltyChargesCompletedDerived() const noexcept
{
    return penaltyChargesCompletedDerived_;
}
void LoanRepaymentScheduleInstallment::setPenaltyChargesCompletedDerived(const std::string &pPenaltyChargesCompletedDerived) noexcept
{
    penaltyChargesCompletedDerived_ = std::make_shared<std::string>(pPenaltyChargesCompletedDerived);
    dirtyFlag_[16] = true;
}
void LoanRepaymentScheduleInstallment::setPenaltyChargesCompletedDerived(std::string &&pPenaltyChargesCompletedDerived) noexcept
{
    penaltyChargesCompletedDerived_ = std::make_shared<std::string>(std::move(pPenaltyChargesCompletedDerived));
    dirtyFlag_[16] = true;
}

const std::string &LoanRepaymentScheduleInstallment::getValueOfPenaltyChargesWaivedDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesWaivedDerived_)
        return *penaltyChargesWaivedDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanRepaymentScheduleInstallment::getPenaltyChargesWaivedDerived() const noexcept
{
    return penaltyChargesWaivedDerived_;
}
void LoanRepaymentScheduleInstallment::setPenaltyChargesWaivedDerived(const std::string &pPenaltyChargesWaivedDerived) noexcept
{
    penaltyChargesWaivedDerived_ = std::make_shared<std::string>(pPenaltyChargesWaivedDerived);
    dirtyFlag_[17] = true;
}
void LoanRepaymentScheduleInstallment::setPenaltyChargesWaivedDerived(std::string &&pPenaltyChargesWaivedDerived) noexcept
{
    penaltyChargesWaivedDerived_ = std::make_shared<std::string>(std::move(pPenaltyChargesWaivedDerived));
    dirtyFlag_[17] = true;
}

const bool &LoanRepaymentScheduleInstallment::getValueOfCompletedDerived() const noexcept
{
    static const bool defaultValue = bool();
    if(completedDerived_)
        return *completedDerived_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanRepaymentScheduleInstallment::getCompletedDerived() const noexcept
{
    return completedDerived_;
}
void LoanRepaymentScheduleInstallment::setCompletedDerived(const bool &pCompletedDerived) noexcept
{
    completedDerived_ = std::make_shared<bool>(pCompletedDerived);
    dirtyFlag_[18] = true;
}

const ::trantor::Date &LoanRepaymentScheduleInstallment::getValueOfObligationsMetOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(obligationsMetOnDate_)
        return *obligationsMetOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanRepaymentScheduleInstallment::getObligationsMetOnDate() const noexcept
{
    return obligationsMetOnDate_;
}
void LoanRepaymentScheduleInstallment::setObligationsMetOnDate(const ::trantor::Date &pObligationsMetOnDate) noexcept
{
    obligationsMetOnDate_ = std::make_shared<::trantor::Date>(pObligationsMetOnDate);
    dirtyFlag_[19] = true;
}
void LoanRepaymentScheduleInstallment::setObligationsMetOnDateToNull() noexcept
{
    obligationsMetOnDate_.reset();
    dirtyFlag_[19] = true;
}

const bool &LoanRepaymentScheduleInstallment::getValueOfRecalculatedInterest() const noexcept
{
    static const bool defaultValue = bool();
    if(recalculatedInterest_)
        return *recalculatedInterest_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanRepaymentScheduleInstallment::getRecalculatedInterest() const noexcept
{
    return recalculatedInterest_;
}
void LoanRepaymentScheduleInstallment::setRecalculatedInterest(const bool &pRecalculatedInterest) noexcept
{
    recalculatedInterest_ = std::make_shared<bool>(pRecalculatedInterest);
    dirtyFlag_[20] = true;
}

void LoanRepaymentScheduleInstallment::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanRepaymentScheduleInstallment::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "installment_number",
        "from_date",
        "due_date",
        "principal_amount",
        "principal_completed_derived",
        "principal_writtenoff_derived",
        "interest_amount",
        "interest_completed_derived",
        "interest_waived_derived",
        "interest_writtenoff_derived",
        "fee_charges_amount",
        "fee_charges_completed_derived",
        "fee_charges_waived_derived",
        "penalty_charges_amount",
        "penalty_charges_completed_derived",
        "penalty_charges_waived_derived",
        "completed_derived",
        "obligations_met_on_date",
        "recalculated_interest"
    };
    return inCols;
}

void LoanRepaymentScheduleInstallment::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getInstallmentNumber())
        {
            binder << getValueOfInstallmentNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromDate())
        {
            binder << getValueOfFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDueDate())
        {
            binder << getValueOfDueDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getPrincipalAmount())
        {
            binder << getValueOfPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getPrincipalCompletedDerived())
        {
            binder << getValueOfPrincipalCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getPrincipalWrittenoffDerived())
        {
            binder << getValueOfPrincipalWrittenoffDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getInterestAmount())
        {
            binder << getValueOfInterestAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getInterestCompletedDerived())
        {
            binder << getValueOfInterestCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getInterestWaivedDerived())
        {
            binder << getValueOfInterestWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getInterestWrittenoffDerived())
        {
            binder << getValueOfInterestWrittenoffDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getFeeChargesAmount())
        {
            binder << getValueOfFeeChargesAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getFeeChargesCompletedDerived())
        {
            binder << getValueOfFeeChargesCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getFeeChargesWaivedDerived())
        {
            binder << getValueOfFeeChargesWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getPenaltyChargesAmount())
        {
            binder << getValueOfPenaltyChargesAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getPenaltyChargesCompletedDerived())
        {
            binder << getValueOfPenaltyChargesCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getPenaltyChargesWaivedDerived())
        {
            binder << getValueOfPenaltyChargesWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getCompletedDerived())
        {
            binder << getValueOfCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getObligationsMetOnDate())
        {
            binder << getValueOfObligationsMetOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getRecalculatedInterest())
        {
            binder << getValueOfRecalculatedInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> LoanRepaymentScheduleInstallment::updateColumns() const
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
    if(dirtyFlag_[17])
    {
        ret.push_back(getColumnName(17));
    }
    if(dirtyFlag_[18])
    {
        ret.push_back(getColumnName(18));
    }
    if(dirtyFlag_[19])
    {
        ret.push_back(getColumnName(19));
    }
    if(dirtyFlag_[20])
    {
        ret.push_back(getColumnName(20));
    }
    return ret;
}

void LoanRepaymentScheduleInstallment::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getInstallmentNumber())
        {
            binder << getValueOfInstallmentNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getFromDate())
        {
            binder << getValueOfFromDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDueDate())
        {
            binder << getValueOfDueDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getPrincipalAmount())
        {
            binder << getValueOfPrincipalAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getPrincipalCompletedDerived())
        {
            binder << getValueOfPrincipalCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getPrincipalWrittenoffDerived())
        {
            binder << getValueOfPrincipalWrittenoffDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getInterestAmount())
        {
            binder << getValueOfInterestAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getInterestCompletedDerived())
        {
            binder << getValueOfInterestCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getInterestWaivedDerived())
        {
            binder << getValueOfInterestWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getInterestWrittenoffDerived())
        {
            binder << getValueOfInterestWrittenoffDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getFeeChargesAmount())
        {
            binder << getValueOfFeeChargesAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getFeeChargesCompletedDerived())
        {
            binder << getValueOfFeeChargesCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getFeeChargesWaivedDerived())
        {
            binder << getValueOfFeeChargesWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getPenaltyChargesAmount())
        {
            binder << getValueOfPenaltyChargesAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getPenaltyChargesCompletedDerived())
        {
            binder << getValueOfPenaltyChargesCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getPenaltyChargesWaivedDerived())
        {
            binder << getValueOfPenaltyChargesWaivedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getCompletedDerived())
        {
            binder << getValueOfCompletedDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getObligationsMetOnDate())
        {
            binder << getValueOfObligationsMetOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getRecalculatedInterest())
        {
            binder << getValueOfRecalculatedInterest();
        }
        else
        {
            binder << nullptr;
        }
    }
}
