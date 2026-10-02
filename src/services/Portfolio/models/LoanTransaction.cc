/**
 *  LoanTransaction.cc
 *
 *  See LoanTransaction.h for the hand-authored-subset note.
 *
 */

#include "LoanTransaction.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanTransaction::Cols::_id = "\"id\"";
const std::string LoanTransaction::Cols::_loan_id = "\"loan_id\"";
const std::string LoanTransaction::Cols::_external_id = "\"external_id\"";
const std::string LoanTransaction::Cols::_office_id = "\"office_id\"";
const std::string LoanTransaction::Cols::_transaction_type = "\"transaction_type\"";
const std::string LoanTransaction::Cols::_transaction_date = "\"transaction_date\"";
const std::string LoanTransaction::Cols::_amount = "\"amount\"";
const std::string LoanTransaction::Cols::_principal_portion = "\"principal_portion\"";
const std::string LoanTransaction::Cols::_interest_portion = "\"interest_portion\"";
const std::string LoanTransaction::Cols::_fee_charges_portion = "\"fee_charges_portion\"";
const std::string LoanTransaction::Cols::_penalty_charges_portion = "\"penalty_charges_portion\"";
const std::string LoanTransaction::Cols::_overpayment_portion = "\"overpayment_portion\"";
const std::string LoanTransaction::Cols::_outstanding_loan_balance_derived = "\"outstanding_loan_balance_derived\"";
const std::string LoanTransaction::Cols::_is_reversed = "\"is_reversed\"";
const std::string LoanTransaction::Cols::_reversed_on_date = "\"reversed_on_date\"";
const std::string LoanTransaction::Cols::_submitted_on_date = "\"submitted_on_date\"";
const std::string LoanTransaction::Cols::_created_by = "\"created_by\"";
const std::string LoanTransaction::Cols::_created_at = "\"created_at\"";
const std::string LoanTransaction::primaryKeyName = "id";
const bool LoanTransaction::hasPrimaryKey = true;
const std::string LoanTransaction::tableName = "\"loan_transaction\"";

const std::vector<typename LoanTransaction::MetaData> LoanTransaction::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"external_id","std::string","character varying",100,0,0,0},
{"office_id","std::string","uuid",0,0,0,0},
{"transaction_type","int32_t","integer",4,0,0,1},
{"transaction_date","::trantor::Date","date",0,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"principal_portion","std::string","numeric",0,0,0,1},
{"interest_portion","std::string","numeric",0,0,0,1},
{"fee_charges_portion","std::string","numeric",0,0,0,1},
{"penalty_charges_portion","std::string","numeric",0,0,0,1},
{"overpayment_portion","std::string","numeric",0,0,0,1},
{"outstanding_loan_balance_derived","std::string","numeric",0,0,0,0},
{"is_reversed","bool","boolean",1,0,0,1},
{"reversed_on_date","::trantor::Date","date",0,0,0,0},
{"submitted_on_date","::trantor::Date","date",0,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanTransaction::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanTransaction::LoanTransaction(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["transaction_type"].isNull())
        {
            transactionType_=std::make_shared<int32_t>(r["transaction_type"].as<int32_t>());
        }
        if(!r["transaction_date"].isNull())
        {
            auto daysStr = r["transaction_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            transactionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["principal_portion"].isNull())
        {
            principalPortion_=std::make_shared<std::string>(r["principal_portion"].as<std::string>());
        }
        if(!r["interest_portion"].isNull())
        {
            interestPortion_=std::make_shared<std::string>(r["interest_portion"].as<std::string>());
        }
        if(!r["fee_charges_portion"].isNull())
        {
            feeChargesPortion_=std::make_shared<std::string>(r["fee_charges_portion"].as<std::string>());
        }
        if(!r["penalty_charges_portion"].isNull())
        {
            penaltyChargesPortion_=std::make_shared<std::string>(r["penalty_charges_portion"].as<std::string>());
        }
        if(!r["overpayment_portion"].isNull())
        {
            overpaymentPortion_=std::make_shared<std::string>(r["overpayment_portion"].as<std::string>());
        }
        if(!r["outstanding_loan_balance_derived"].isNull())
        {
            outstandingLoanBalanceDerived_=std::make_shared<std::string>(r["outstanding_loan_balance_derived"].as<std::string>());
        }
        if(!r["is_reversed"].isNull())
        {
            isReversed_=std::make_shared<bool>(r["is_reversed"].as<bool>());
        }
        if(!r["reversed_on_date"].isNull())
        {
            auto daysStr = r["reversed_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            reversedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
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
        if(offset + 18 > r.size())
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
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            transactionType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            transactionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            principalPortion_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            interestPortion_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            feeChargesPortion_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            penaltyChargesPortion_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            overpaymentPortion_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            outstandingLoanBalanceDerived_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            isReversed_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            reversedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 17;
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
const std::string &LoanTransaction::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getId() const noexcept
{
    return id_;
}
void LoanTransaction::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanTransaction::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanTransaction::PrimaryKeyType & LoanTransaction::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanTransaction::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getLoanId() const noexcept
{
    return loanId_;
}
void LoanTransaction::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanTransaction::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanTransaction::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getExternalId() const noexcept
{
    return externalId_;
}
void LoanTransaction::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[2] = true;
}
void LoanTransaction::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[2] = true;
}
void LoanTransaction::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &LoanTransaction::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getOfficeId() const noexcept
{
    return officeId_;
}
void LoanTransaction::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[3] = true;
}
void LoanTransaction::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[3] = true;
}
void LoanTransaction::setOfficeIdToNull() noexcept
{
    officeId_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &LoanTransaction::getValueOfTransactionType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(transactionType_)
        return *transactionType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanTransaction::getTransactionType() const noexcept
{
    return transactionType_;
}
void LoanTransaction::setTransactionType(const int32_t &pTransactionType) noexcept
{
    transactionType_ = std::make_shared<int32_t>(pTransactionType);
    dirtyFlag_[4] = true;
}

const ::trantor::Date &LoanTransaction::getValueOfTransactionDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(transactionDate_)
        return *transactionDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanTransaction::getTransactionDate() const noexcept
{
    return transactionDate_;
}
void LoanTransaction::setTransactionDate(const ::trantor::Date &pTransactionDate) noexcept
{
    transactionDate_ = std::make_shared<::trantor::Date>(pTransactionDate);
    dirtyFlag_[5] = true;
}

const std::string &LoanTransaction::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getAmount() const noexcept
{
    return amount_;
}
void LoanTransaction::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[6] = true;
}
void LoanTransaction::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[6] = true;
}

const std::string &LoanTransaction::getValueOfPrincipalPortion() const noexcept
{
    static const std::string defaultValue = std::string();
    if(principalPortion_)
        return *principalPortion_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getPrincipalPortion() const noexcept
{
    return principalPortion_;
}
void LoanTransaction::setPrincipalPortion(const std::string &pPrincipalPortion) noexcept
{
    principalPortion_ = std::make_shared<std::string>(pPrincipalPortion);
    dirtyFlag_[7] = true;
}
void LoanTransaction::setPrincipalPortion(std::string &&pPrincipalPortion) noexcept
{
    principalPortion_ = std::make_shared<std::string>(std::move(pPrincipalPortion));
    dirtyFlag_[7] = true;
}

const std::string &LoanTransaction::getValueOfInterestPortion() const noexcept
{
    static const std::string defaultValue = std::string();
    if(interestPortion_)
        return *interestPortion_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getInterestPortion() const noexcept
{
    return interestPortion_;
}
void LoanTransaction::setInterestPortion(const std::string &pInterestPortion) noexcept
{
    interestPortion_ = std::make_shared<std::string>(pInterestPortion);
    dirtyFlag_[8] = true;
}
void LoanTransaction::setInterestPortion(std::string &&pInterestPortion) noexcept
{
    interestPortion_ = std::make_shared<std::string>(std::move(pInterestPortion));
    dirtyFlag_[8] = true;
}

const std::string &LoanTransaction::getValueOfFeeChargesPortion() const noexcept
{
    static const std::string defaultValue = std::string();
    if(feeChargesPortion_)
        return *feeChargesPortion_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getFeeChargesPortion() const noexcept
{
    return feeChargesPortion_;
}
void LoanTransaction::setFeeChargesPortion(const std::string &pFeeChargesPortion) noexcept
{
    feeChargesPortion_ = std::make_shared<std::string>(pFeeChargesPortion);
    dirtyFlag_[9] = true;
}
void LoanTransaction::setFeeChargesPortion(std::string &&pFeeChargesPortion) noexcept
{
    feeChargesPortion_ = std::make_shared<std::string>(std::move(pFeeChargesPortion));
    dirtyFlag_[9] = true;
}

const std::string &LoanTransaction::getValueOfPenaltyChargesPortion() const noexcept
{
    static const std::string defaultValue = std::string();
    if(penaltyChargesPortion_)
        return *penaltyChargesPortion_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getPenaltyChargesPortion() const noexcept
{
    return penaltyChargesPortion_;
}
void LoanTransaction::setPenaltyChargesPortion(const std::string &pPenaltyChargesPortion) noexcept
{
    penaltyChargesPortion_ = std::make_shared<std::string>(pPenaltyChargesPortion);
    dirtyFlag_[10] = true;
}
void LoanTransaction::setPenaltyChargesPortion(std::string &&pPenaltyChargesPortion) noexcept
{
    penaltyChargesPortion_ = std::make_shared<std::string>(std::move(pPenaltyChargesPortion));
    dirtyFlag_[10] = true;
}

const std::string &LoanTransaction::getValueOfOverpaymentPortion() const noexcept
{
    static const std::string defaultValue = std::string();
    if(overpaymentPortion_)
        return *overpaymentPortion_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getOverpaymentPortion() const noexcept
{
    return overpaymentPortion_;
}
void LoanTransaction::setOverpaymentPortion(const std::string &pOverpaymentPortion) noexcept
{
    overpaymentPortion_ = std::make_shared<std::string>(pOverpaymentPortion);
    dirtyFlag_[11] = true;
}
void LoanTransaction::setOverpaymentPortion(std::string &&pOverpaymentPortion) noexcept
{
    overpaymentPortion_ = std::make_shared<std::string>(std::move(pOverpaymentPortion));
    dirtyFlag_[11] = true;
}

const std::string &LoanTransaction::getValueOfOutstandingLoanBalanceDerived() const noexcept
{
    static const std::string defaultValue = std::string();
    if(outstandingLoanBalanceDerived_)
        return *outstandingLoanBalanceDerived_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getOutstandingLoanBalanceDerived() const noexcept
{
    return outstandingLoanBalanceDerived_;
}
void LoanTransaction::setOutstandingLoanBalanceDerived(const std::string &pOutstandingLoanBalanceDerived) noexcept
{
    outstandingLoanBalanceDerived_ = std::make_shared<std::string>(pOutstandingLoanBalanceDerived);
    dirtyFlag_[12] = true;
}
void LoanTransaction::setOutstandingLoanBalanceDerived(std::string &&pOutstandingLoanBalanceDerived) noexcept
{
    outstandingLoanBalanceDerived_ = std::make_shared<std::string>(std::move(pOutstandingLoanBalanceDerived));
    dirtyFlag_[12] = true;
}
void LoanTransaction::setOutstandingLoanBalanceDerivedToNull() noexcept
{
    outstandingLoanBalanceDerived_.reset();
    dirtyFlag_[12] = true;
}

const bool &LoanTransaction::getValueOfIsReversed() const noexcept
{
    static const bool defaultValue = bool();
    if(isReversed_)
        return *isReversed_;
    return defaultValue;
}
const std::shared_ptr<bool> &LoanTransaction::getIsReversed() const noexcept
{
    return isReversed_;
}
void LoanTransaction::setIsReversed(const bool &pIsReversed) noexcept
{
    isReversed_ = std::make_shared<bool>(pIsReversed);
    dirtyFlag_[13] = true;
}

const ::trantor::Date &LoanTransaction::getValueOfReversedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(reversedOnDate_)
        return *reversedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanTransaction::getReversedOnDate() const noexcept
{
    return reversedOnDate_;
}
void LoanTransaction::setReversedOnDate(const ::trantor::Date &pReversedOnDate) noexcept
{
    reversedOnDate_ = std::make_shared<::trantor::Date>(pReversedOnDate);
    dirtyFlag_[14] = true;
}
void LoanTransaction::setReversedOnDateToNull() noexcept
{
    reversedOnDate_.reset();
    dirtyFlag_[14] = true;
}

const ::trantor::Date &LoanTransaction::getValueOfSubmittedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedOnDate_)
        return *submittedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanTransaction::getSubmittedOnDate() const noexcept
{
    return submittedOnDate_;
}
void LoanTransaction::setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept
{
    submittedOnDate_ = std::make_shared<::trantor::Date>(pSubmittedOnDate);
    dirtyFlag_[15] = true;
}

const std::string &LoanTransaction::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanTransaction::getCreatedBy() const noexcept
{
    return createdBy_;
}
void LoanTransaction::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[16] = true;
}
void LoanTransaction::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[16] = true;
}
void LoanTransaction::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[16] = true;
}

const ::trantor::Date &LoanTransaction::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanTransaction::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanTransaction::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[17] = true;
}

void LoanTransaction::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanTransaction::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "external_id",
        "office_id",
        "transaction_type",
        "transaction_date",
        "amount",
        "principal_portion",
        "interest_portion",
        "fee_charges_portion",
        "penalty_charges_portion",
        "overpayment_portion",
        "outstanding_loan_balance_derived",
        "is_reversed",
        "reversed_on_date",
        "submitted_on_date",
        "created_by",
        "created_at"
    };
    return inCols;
}

void LoanTransaction::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTransactionType())
        {
            binder << getValueOfTransactionType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransactionDate())
        {
            binder << getValueOfTransactionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getPrincipalPortion())
        {
            binder << getValueOfPrincipalPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getInterestPortion())
        {
            binder << getValueOfInterestPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getFeeChargesPortion())
        {
            binder << getValueOfFeeChargesPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getPenaltyChargesPortion())
        {
            binder << getValueOfPenaltyChargesPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getOverpaymentPortion())
        {
            binder << getValueOfOverpaymentPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getOutstandingLoanBalanceDerived())
        {
            binder << getValueOfOutstandingLoanBalanceDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getIsReversed())
        {
            binder << getValueOfIsReversed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getReversedOnDate())
        {
            binder << getValueOfReversedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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

const std::vector<std::string> LoanTransaction::updateColumns() const
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
    return ret;
}

void LoanTransaction::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTransactionType())
        {
            binder << getValueOfTransactionType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransactionDate())
        {
            binder << getValueOfTransactionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getPrincipalPortion())
        {
            binder << getValueOfPrincipalPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getInterestPortion())
        {
            binder << getValueOfInterestPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getFeeChargesPortion())
        {
            binder << getValueOfFeeChargesPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getPenaltyChargesPortion())
        {
            binder << getValueOfPenaltyChargesPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getOverpaymentPortion())
        {
            binder << getValueOfOverpaymentPortion();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getOutstandingLoanBalanceDerived())
        {
            binder << getValueOfOutstandingLoanBalanceDerived();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getIsReversed())
        {
            binder << getValueOfIsReversed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getReversedOnDate())
        {
            binder << getValueOfReversedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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
