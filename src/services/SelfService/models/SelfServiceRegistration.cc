/**
 *  SelfServiceRegistration.cc
 *
 *  See SelfServiceRegistration.h for the hand-authored-subset note.
 *
 */

#include "SelfServiceRegistration.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlSelfServiceDb;

const std::string SelfServiceRegistration::Cols::_id = "\"id\"";
const std::string SelfServiceRegistration::Cols::_first_name = "\"first_name\"";
const std::string SelfServiceRegistration::Cols::_last_name = "\"last_name\"";
const std::string SelfServiceRegistration::Cols::_mobile_no = "\"mobile_no\"";
const std::string SelfServiceRegistration::Cols::_account_number = "\"account_number\"";
const std::string SelfServiceRegistration::Cols::_authentication_mode = "\"authentication_mode\"";
const std::string SelfServiceRegistration::Cols::_status = "\"status\"";
const std::string SelfServiceRegistration::Cols::_created_at = "\"created_at\"";
const std::string SelfServiceRegistration::primaryKeyName = "id";
const bool SelfServiceRegistration::hasPrimaryKey = true;
const std::string SelfServiceRegistration::tableName = "\"self_service_registrations\"";

const std::vector<typename SelfServiceRegistration::MetaData> SelfServiceRegistration::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"first_name","std::string","character varying",100,0,0,1},
{"last_name","std::string","character varying",100,0,0,1},
{"mobile_no","std::string","character varying",32,0,0,1},
{"account_number","std::string","character varying",100,0,0,0},
{"authentication_mode","std::string","character varying",20,0,0,1},
{"status","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SelfServiceRegistration::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SelfServiceRegistration::SelfServiceRegistration(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["first_name"].isNull())
        {
            firstName_=std::make_shared<std::string>(r["first_name"].as<std::string>());
        }
        if(!r["last_name"].isNull())
        {
            lastName_=std::make_shared<std::string>(r["last_name"].as<std::string>());
        }
        if(!r["mobile_no"].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r["mobile_no"].as<std::string>());
        }
        if(!r["account_number"].isNull())
        {
            accountNumber_=std::make_shared<std::string>(r["account_number"].as<std::string>());
        }
        if(!r["authentication_mode"].isNull())
        {
            authenticationMode_=std::make_shared<std::string>(r["authentication_mode"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
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
        if(offset + 8 > r.size())
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
            firstName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            lastName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            accountNumber_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            authenticationMode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
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
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &SelfServiceRegistration::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceRegistration::getId() const noexcept
{
    return id_;
}
void SelfServiceRegistration::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SelfServiceRegistration::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SelfServiceRegistration::PrimaryKeyType & SelfServiceRegistration::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SelfServiceRegistration::getValueOfFirstName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(firstName_)
        return *firstName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceRegistration::getFirstName() const noexcept
{
    return firstName_;
}
void SelfServiceRegistration::setFirstName(const std::string &pFirstName) noexcept
{
    firstName_ = std::make_shared<std::string>(pFirstName);
    dirtyFlag_[1] = true;
}
void SelfServiceRegistration::setFirstName(std::string &&pFirstName) noexcept
{
    firstName_ = std::make_shared<std::string>(std::move(pFirstName));
    dirtyFlag_[1] = true;
}

const std::string &SelfServiceRegistration::getValueOfLastName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lastName_)
        return *lastName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceRegistration::getLastName() const noexcept
{
    return lastName_;
}
void SelfServiceRegistration::setLastName(const std::string &pLastName) noexcept
{
    lastName_ = std::make_shared<std::string>(pLastName);
    dirtyFlag_[2] = true;
}
void SelfServiceRegistration::setLastName(std::string &&pLastName) noexcept
{
    lastName_ = std::make_shared<std::string>(std::move(pLastName));
    dirtyFlag_[2] = true;
}

const std::string &SelfServiceRegistration::getValueOfMobileNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mobileNo_)
        return *mobileNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceRegistration::getMobileNo() const noexcept
{
    return mobileNo_;
}
void SelfServiceRegistration::setMobileNo(const std::string &pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(pMobileNo);
    dirtyFlag_[3] = true;
}
void SelfServiceRegistration::setMobileNo(std::string &&pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(std::move(pMobileNo));
    dirtyFlag_[3] = true;
}

const std::string &SelfServiceRegistration::getValueOfAccountNumber() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountNumber_)
        return *accountNumber_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceRegistration::getAccountNumber() const noexcept
{
    return accountNumber_;
}
void SelfServiceRegistration::setAccountNumber(const std::string &pAccountNumber) noexcept
{
    accountNumber_ = std::make_shared<std::string>(pAccountNumber);
    dirtyFlag_[4] = true;
}
void SelfServiceRegistration::setAccountNumber(std::string &&pAccountNumber) noexcept
{
    accountNumber_ = std::make_shared<std::string>(std::move(pAccountNumber));
    dirtyFlag_[4] = true;
}
void SelfServiceRegistration::setAccountNumberToNull() noexcept
{
    accountNumber_.reset();
    dirtyFlag_[4] = true;
}

const std::string &SelfServiceRegistration::getValueOfAuthenticationMode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(authenticationMode_)
        return *authenticationMode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceRegistration::getAuthenticationMode() const noexcept
{
    return authenticationMode_;
}
void SelfServiceRegistration::setAuthenticationMode(const std::string &pAuthenticationMode) noexcept
{
    authenticationMode_ = std::make_shared<std::string>(pAuthenticationMode);
    dirtyFlag_[5] = true;
}
void SelfServiceRegistration::setAuthenticationMode(std::string &&pAuthenticationMode) noexcept
{
    authenticationMode_ = std::make_shared<std::string>(std::move(pAuthenticationMode));
    dirtyFlag_[5] = true;
}

const std::string &SelfServiceRegistration::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceRegistration::getStatus() const noexcept
{
    return status_;
}
void SelfServiceRegistration::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[6] = true;
}
void SelfServiceRegistration::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[6] = true;
}

const ::trantor::Date &SelfServiceRegistration::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SelfServiceRegistration::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SelfServiceRegistration::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

void SelfServiceRegistration::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SelfServiceRegistration::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "first_name",
        "last_name",
        "mobile_no",
        "account_number",
        "authentication_mode",
        "status",
        "created_at"
    };
    return inCols;
}

void SelfServiceRegistration::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFirstName())
        {
            binder << getValueOfFirstName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getMobileNo())
        {
            binder << getValueOfMobileNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAccountNumber())
        {
            binder << getValueOfAccountNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getAuthenticationMode())
        {
            binder << getValueOfAuthenticationMode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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

const std::vector<std::string> SelfServiceRegistration::updateColumns() const
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
    return ret;
}

void SelfServiceRegistration::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getFirstName())
        {
            binder << getValueOfFirstName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getMobileNo())
        {
            binder << getValueOfMobileNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAccountNumber())
        {
            binder << getValueOfAccountNumber();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getAuthenticationMode())
        {
            binder << getValueOfAuthenticationMode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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
