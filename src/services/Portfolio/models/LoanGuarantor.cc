/**
 *  LoanGuarantor.cc
 *
 *  See LoanGuarantor.h for the hand-authored-subset note.
 *
 */

#include "LoanGuarantor.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanGuarantor::Cols::_id = "\"id\"";
const std::string LoanGuarantor::Cols::_loan_id = "\"loan_id\"";
const std::string LoanGuarantor::Cols::_guarantor_type = "\"guarantor_type\"";
const std::string LoanGuarantor::Cols::_client_id = "\"client_id\"";
const std::string LoanGuarantor::Cols::_first_name = "\"first_name\"";
const std::string LoanGuarantor::Cols::_last_name = "\"last_name\"";
const std::string LoanGuarantor::Cols::_address_line_1 = "\"address_line_1\"";
const std::string LoanGuarantor::Cols::_city = "\"city\"";
const std::string LoanGuarantor::Cols::_mobile_number = "\"mobile_number\"";
const std::string LoanGuarantor::Cols::_amount = "\"amount\"";
const std::string LoanGuarantor::Cols::_created_at = "\"created_at\"";
const std::string LoanGuarantor::primaryKeyName = "id";
const bool LoanGuarantor::hasPrimaryKey = true;
const std::string LoanGuarantor::tableName = "\"loan_guarantor\"";

const std::vector<typename LoanGuarantor::MetaData> LoanGuarantor::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"guarantor_type","int32_t","integer",4,0,0,1},
{"client_id","std::string","uuid",0,0,0,0},
{"first_name","std::string","character varying",100,0,0,0},
{"last_name","std::string","character varying",100,0,0,0},
{"address_line_1","std::string","character varying",200,0,0,0},
{"city","std::string","character varying",100,0,0,0},
{"mobile_number","std::string","character varying",40,0,0,0},
{"amount","std::string","numeric",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanGuarantor::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanGuarantor::LoanGuarantor(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["guarantor_type"].isNull())
        {
            guarantorType_=std::make_shared<int32_t>(r["guarantor_type"].as<int32_t>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["first_name"].isNull())
        {
            firstName_=std::make_shared<std::string>(r["first_name"].as<std::string>());
        }
        if(!r["last_name"].isNull())
        {
            lastName_=std::make_shared<std::string>(r["last_name"].as<std::string>());
        }
        if(!r["address_line_1"].isNull())
        {
            addressLine1_=std::make_shared<std::string>(r["address_line_1"].as<std::string>());
        }
        if(!r["city"].isNull())
        {
            city_=std::make_shared<std::string>(r["city"].as<std::string>());
        }
        if(!r["mobile_number"].isNull())
        {
            mobileNumber_=std::make_shared<std::string>(r["mobile_number"].as<std::string>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
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
        if(offset + 11 > r.size())
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
            guarantorType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            firstName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            lastName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            addressLine1_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            city_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            mobileNumber_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
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
const std::string &LoanGuarantor::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getId() const noexcept
{
    return id_;
}
void LoanGuarantor::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanGuarantor::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanGuarantor::PrimaryKeyType & LoanGuarantor::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanGuarantor::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getLoanId() const noexcept
{
    return loanId_;
}
void LoanGuarantor::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanGuarantor::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const int32_t &LoanGuarantor::getValueOfGuarantorType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(guarantorType_)
        return *guarantorType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LoanGuarantor::getGuarantorType() const noexcept
{
    return guarantorType_;
}
void LoanGuarantor::setGuarantorType(const int32_t &pGuarantorType) noexcept
{
    guarantorType_ = std::make_shared<int32_t>(pGuarantorType);
    dirtyFlag_[2] = true;
}

const std::string &LoanGuarantor::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getClientId() const noexcept
{
    return clientId_;
}
void LoanGuarantor::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[3] = true;
}
void LoanGuarantor::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[3] = true;
}
void LoanGuarantor::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[3] = true;
}

const std::string &LoanGuarantor::getValueOfFirstName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(firstName_)
        return *firstName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getFirstName() const noexcept
{
    return firstName_;
}
void LoanGuarantor::setFirstName(const std::string &pFirstName) noexcept
{
    firstName_ = std::make_shared<std::string>(pFirstName);
    dirtyFlag_[4] = true;
}
void LoanGuarantor::setFirstName(std::string &&pFirstName) noexcept
{
    firstName_ = std::make_shared<std::string>(std::move(pFirstName));
    dirtyFlag_[4] = true;
}
void LoanGuarantor::setFirstNameToNull() noexcept
{
    firstName_.reset();
    dirtyFlag_[4] = true;
}

const std::string &LoanGuarantor::getValueOfLastName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lastName_)
        return *lastName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getLastName() const noexcept
{
    return lastName_;
}
void LoanGuarantor::setLastName(const std::string &pLastName) noexcept
{
    lastName_ = std::make_shared<std::string>(pLastName);
    dirtyFlag_[5] = true;
}
void LoanGuarantor::setLastName(std::string &&pLastName) noexcept
{
    lastName_ = std::make_shared<std::string>(std::move(pLastName));
    dirtyFlag_[5] = true;
}
void LoanGuarantor::setLastNameToNull() noexcept
{
    lastName_.reset();
    dirtyFlag_[5] = true;
}

const std::string &LoanGuarantor::getValueOfAddressLine1() const noexcept
{
    static const std::string defaultValue = std::string();
    if(addressLine1_)
        return *addressLine1_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getAddressLine1() const noexcept
{
    return addressLine1_;
}
void LoanGuarantor::setAddressLine1(const std::string &pAddressLine1) noexcept
{
    addressLine1_ = std::make_shared<std::string>(pAddressLine1);
    dirtyFlag_[6] = true;
}
void LoanGuarantor::setAddressLine1(std::string &&pAddressLine1) noexcept
{
    addressLine1_ = std::make_shared<std::string>(std::move(pAddressLine1));
    dirtyFlag_[6] = true;
}
void LoanGuarantor::setAddressLine1ToNull() noexcept
{
    addressLine1_.reset();
    dirtyFlag_[6] = true;
}

const std::string &LoanGuarantor::getValueOfCity() const noexcept
{
    static const std::string defaultValue = std::string();
    if(city_)
        return *city_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getCity() const noexcept
{
    return city_;
}
void LoanGuarantor::setCity(const std::string &pCity) noexcept
{
    city_ = std::make_shared<std::string>(pCity);
    dirtyFlag_[7] = true;
}
void LoanGuarantor::setCity(std::string &&pCity) noexcept
{
    city_ = std::make_shared<std::string>(std::move(pCity));
    dirtyFlag_[7] = true;
}
void LoanGuarantor::setCityToNull() noexcept
{
    city_.reset();
    dirtyFlag_[7] = true;
}

const std::string &LoanGuarantor::getValueOfMobileNumber() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mobileNumber_)
        return *mobileNumber_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getMobileNumber() const noexcept
{
    return mobileNumber_;
}
void LoanGuarantor::setMobileNumber(const std::string &pMobileNumber) noexcept
{
    mobileNumber_ = std::make_shared<std::string>(pMobileNumber);
    dirtyFlag_[8] = true;
}
void LoanGuarantor::setMobileNumber(std::string &&pMobileNumber) noexcept
{
    mobileNumber_ = std::make_shared<std::string>(std::move(pMobileNumber));
    dirtyFlag_[8] = true;
}
void LoanGuarantor::setMobileNumberToNull() noexcept
{
    mobileNumber_.reset();
    dirtyFlag_[8] = true;
}

const std::string &LoanGuarantor::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanGuarantor::getAmount() const noexcept
{
    return amount_;
}
void LoanGuarantor::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[9] = true;
}
void LoanGuarantor::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[9] = true;
}
void LoanGuarantor::setAmountToNull() noexcept
{
    amount_.reset();
    dirtyFlag_[9] = true;
}

const ::trantor::Date &LoanGuarantor::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanGuarantor::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanGuarantor::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[10] = true;
}

void LoanGuarantor::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanGuarantor::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "guarantor_type",
        "client_id",
        "first_name",
        "last_name",
        "address_line_1",
        "city",
        "mobile_number",
        "amount",
        "created_at"
    };
    return inCols;
}

void LoanGuarantor::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getGuarantorType())
        {
            binder << getValueOfGuarantorType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getFirstName())
        {
            binder << getValueOfFirstName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getLastName())
        {
            binder << getValueOfLastName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAddressLine1())
        {
            binder << getValueOfAddressLine1();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getCity())
        {
            binder << getValueOfCity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getMobileNumber())
        {
            binder << getValueOfMobileNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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

const std::vector<std::string> LoanGuarantor::updateColumns() const
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
    return ret;
}

void LoanGuarantor::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getGuarantorType())
        {
            binder << getValueOfGuarantorType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
    {
        if(getFirstName())
        {
            binder << getValueOfFirstName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getLastName())
        {
            binder << getValueOfLastName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAddressLine1())
        {
            binder << getValueOfAddressLine1();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getCity())
        {
            binder << getValueOfCity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getMobileNumber())
        {
            binder << getValueOfMobileNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
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
    if(dirtyFlag_[10])
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
