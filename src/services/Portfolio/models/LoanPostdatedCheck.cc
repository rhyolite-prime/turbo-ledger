/**
 *  LoanPostdatedCheck.cc
 *
 *  See LoanPostdatedCheck.h for the hand-authored-subset note.
 *
 */

#include "LoanPostdatedCheck.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanPostdatedCheck::Cols::_id = "\"id\"";
const std::string LoanPostdatedCheck::Cols::_loan_id = "\"loan_id\"";
const std::string LoanPostdatedCheck::Cols::_installment_id = "\"installment_id\"";
const std::string LoanPostdatedCheck::Cols::_check_number = "\"check_number\"";
const std::string LoanPostdatedCheck::Cols::_bank_name = "\"bank_name\"";
const std::string LoanPostdatedCheck::Cols::_check_date = "\"check_date\"";
const std::string LoanPostdatedCheck::Cols::_amount = "\"amount\"";
const std::string LoanPostdatedCheck::Cols::_status = "\"status\"";
const std::string LoanPostdatedCheck::Cols::_created_at = "\"created_at\"";
const std::string LoanPostdatedCheck::primaryKeyName = "id";
const bool LoanPostdatedCheck::hasPrimaryKey = true;
const std::string LoanPostdatedCheck::tableName = "\"loan_postdated_check\"";

const std::vector<typename LoanPostdatedCheck::MetaData> LoanPostdatedCheck::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"installment_id","std::string","uuid",0,0,0,0},
{"check_number","std::string","character varying",40,0,0,1},
{"bank_name","std::string","character varying",100,0,0,0},
{"check_date","::trantor::Date","date",0,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"status","int32_t","integer",4,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanPostdatedCheck::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanPostdatedCheck::LoanPostdatedCheck(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["installment_id"].isNull())
        {
            installmentId_=std::make_shared<std::string>(r["installment_id"].as<std::string>());
        }
        if(!r["check_number"].isNull())
        {
            checkNumber_=std::make_shared<std::string>(r["check_number"].as<std::string>());
        }
        if(!r["bank_name"].isNull())
        {
            bankName_=std::make_shared<std::string>(r["bank_name"].as<std::string>());
        }
        if(!r["check_date"].isNull())
        {
            auto daysStr = r["check_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            checkDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
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
            loanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            installmentId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            checkNumber_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            bankName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            checkDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 8;
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
const std::string &LoanPostdatedCheck::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanPostdatedCheck::getId() const noexcept
{
    return id_;
}
void LoanPostdatedCheck::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanPostdatedCheck::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanPostdatedCheck::PrimaryKeyType & LoanPostdatedCheck::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanPostdatedCheck::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanPostdatedCheck::getLoanId() const noexcept
{
    return loanId_;
}
void LoanPostdatedCheck::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanPostdatedCheck::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanPostdatedCheck::getValueOfInstallmentId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(installmentId_)
        return *installmentId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanPostdatedCheck::getInstallmentId() const noexcept
{
    return installmentId_;
}
void LoanPostdatedCheck::setInstallmentId(const std::string &pInstallmentId) noexcept
{
    installmentId_ = std::make_shared<std::string>(pInstallmentId);
    dirtyFlag_[2] = true;
}
void LoanPostdatedCheck::setInstallmentId(std::string &&pInstallmentId) noexcept
{
    installmentId_ = std::make_shared<std::string>(std::move(pInstallmentId));
    dirtyFlag_[2] = true;
}
void LoanPostdatedCheck::setInstallmentIdToNull() noexcept
{
    installmentId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &LoanPostdatedCheck::getValueOfCheckNumber() const noexcept
{
    static const std::string defaultValue = std::string();
    if(checkNumber_)
        return *checkNumber_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanPostdatedCheck::getCheckNumber() const noexcept
{
    return checkNumber_;
}
void LoanPostdatedCheck::setCheckNumber(const std::string &pCheckNumber) noexcept
{
    checkNumber_ = std::make_shared<std::string>(pCheckNumber);
    dirtyFlag_[3] = true;
}
void LoanPostdatedCheck::setCheckNumber(std::string &&pCheckNumber) noexcept
{
    checkNumber_ = std::make_shared<std::string>(std::move(pCheckNumber));
    dirtyFlag_[3] = true;
}

const std::string &LoanPostdatedCheck::getValueOfBankName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(bankName_)
        return *bankName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanPostdatedCheck::getBankName() const noexcept
{
    return bankName_;
}
void LoanPostdatedCheck::setBankName(const std::string &pBankName) noexcept
{
    bankName_ = std::make_shared<std::string>(pBankName);
    dirtyFlag_[4] = true;
}
void LoanPostdatedCheck::setBankName(std::string &&pBankName) noexcept
{
    bankName_ = std::make_shared<std::string>(std::move(pBankName));
    dirtyFlag_[4] = true;
}
void LoanPostdatedCheck::setBankNameToNull() noexcept
{
    bankName_.reset();
    dirtyFlag_[4] = true;
}

const ::trantor::Date &LoanPostdatedCheck::getValueOfCheckDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(checkDate_)
        return *checkDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanPostdatedCheck::getCheckDate() const noexcept
{
    return checkDate_;
}
void LoanPostdatedCheck::setCheckDate(const ::trantor::Date &pCheckDate) noexcept
{
    checkDate_ = std::make_shared<::trantor::Date>(pCheckDate);
    dirtyFlag_[5] = true;
}

const std::string &LoanPostdatedCheck::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanPostdatedCheck::getAmount() const noexcept
{
    return amount_;
}
void LoanPostdatedCheck::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[6] = true;
}
void LoanPostdatedCheck::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[6] = true;
}

const int32_t &LoanPostdatedCheck::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanPostdatedCheck::getStatus() const noexcept
{
    return status_;
}
void LoanPostdatedCheck::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[7] = true;
}

const ::trantor::Date &LoanPostdatedCheck::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanPostdatedCheck::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanPostdatedCheck::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[8] = true;
}

void LoanPostdatedCheck::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanPostdatedCheck::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "installment_id",
        "check_number",
        "bank_name",
        "check_date",
        "amount",
        "status",
        "created_at"
    };
    return inCols;
}

void LoanPostdatedCheck::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getInstallmentId())
        {
            binder << getValueOfInstallmentId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getCheckNumber())
        {
            binder << getValueOfCheckNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getBankName())
        {
            binder << getValueOfBankName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCheckDate())
        {
            binder << getValueOfCheckDate();
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
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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

const std::vector<std::string> LoanPostdatedCheck::updateColumns() const
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

void LoanPostdatedCheck::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getInstallmentId())
        {
            binder << getValueOfInstallmentId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getCheckNumber())
        {
            binder << getValueOfCheckNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getBankName())
        {
            binder << getValueOfBankName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCheckDate())
        {
            binder << getValueOfCheckDate();
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
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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
