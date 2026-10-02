/**
 *  SelfServiceUser.cc
 *
 *  See SelfServiceUser.h for the hand-authored-subset note.
 *
 */

#include "SelfServiceUser.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlSelfServiceDb;

const std::string SelfServiceUser::Cols::_id = "\"id\"";
const std::string SelfServiceUser::Cols::_identity_user_id = "\"identity_user_id\"";
const std::string SelfServiceUser::Cols::_client_id = "\"client_id\"";
const std::string SelfServiceUser::Cols::_username = "\"username\"";
const std::string SelfServiceUser::Cols::_mobile_no = "\"mobile_no\"";
const std::string SelfServiceUser::Cols::_email = "\"email\"";
const std::string SelfServiceUser::Cols::_status = "\"status\"";
const std::string SelfServiceUser::Cols::_created_at = "\"created_at\"";
const std::string SelfServiceUser::Cols::_updated_at = "\"updated_at\"";
const std::string SelfServiceUser::primaryKeyName = "id";
const bool SelfServiceUser::hasPrimaryKey = true;
const std::string SelfServiceUser::tableName = "\"self_service_users\"";

const std::vector<typename SelfServiceUser::MetaData> SelfServiceUser::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"identity_user_id","std::string","character varying",64,0,0,1},
{"client_id","std::string","character varying",64,0,0,1},
{"username","std::string","character varying",100,0,0,1},
{"mobile_no","std::string","character varying",32,0,0,0},
{"email","std::string","character varying",120,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &SelfServiceUser::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
SelfServiceUser::SelfServiceUser(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["identity_user_id"].isNull())
        {
            identityUserId_=std::make_shared<std::string>(r["identity_user_id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["username"].isNull())
        {
            username_=std::make_shared<std::string>(r["username"].as<std::string>());
        }
        if(!r["mobile_no"].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r["mobile_no"].as<std::string>());
        }
        if(!r["email"].isNull())
        {
            email_=std::make_shared<std::string>(r["email"].as<std::string>());
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
        if(!r["updated_at"].isNull())
        {
            auto timeStr = r["updated_at"].as<std::string>();
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
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
            identityUserId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            username_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            email_=std::make_shared<std::string>(r[index].as<std::string>());
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &SelfServiceUser::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceUser::getId() const noexcept
{
    return id_;
}
void SelfServiceUser::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void SelfServiceUser::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename SelfServiceUser::PrimaryKeyType & SelfServiceUser::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &SelfServiceUser::getValueOfIdentityUserId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(identityUserId_)
        return *identityUserId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceUser::getIdentityUserId() const noexcept
{
    return identityUserId_;
}
void SelfServiceUser::setIdentityUserId(const std::string &pIdentityUserId) noexcept
{
    identityUserId_ = std::make_shared<std::string>(pIdentityUserId);
    dirtyFlag_[1] = true;
}
void SelfServiceUser::setIdentityUserId(std::string &&pIdentityUserId) noexcept
{
    identityUserId_ = std::make_shared<std::string>(std::move(pIdentityUserId));
    dirtyFlag_[1] = true;
}

const std::string &SelfServiceUser::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceUser::getClientId() const noexcept
{
    return clientId_;
}
void SelfServiceUser::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[2] = true;
}
void SelfServiceUser::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[2] = true;
}

const std::string &SelfServiceUser::getValueOfUsername() const noexcept
{
    static const std::string defaultValue = std::string();
    if(username_)
        return *username_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceUser::getUsername() const noexcept
{
    return username_;
}
void SelfServiceUser::setUsername(const std::string &pUsername) noexcept
{
    username_ = std::make_shared<std::string>(pUsername);
    dirtyFlag_[3] = true;
}
void SelfServiceUser::setUsername(std::string &&pUsername) noexcept
{
    username_ = std::make_shared<std::string>(std::move(pUsername));
    dirtyFlag_[3] = true;
}

const std::string &SelfServiceUser::getValueOfMobileNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mobileNo_)
        return *mobileNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceUser::getMobileNo() const noexcept
{
    return mobileNo_;
}
void SelfServiceUser::setMobileNo(const std::string &pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(pMobileNo);
    dirtyFlag_[4] = true;
}
void SelfServiceUser::setMobileNo(std::string &&pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(std::move(pMobileNo));
    dirtyFlag_[4] = true;
}
void SelfServiceUser::setMobileNoToNull() noexcept
{
    mobileNo_.reset();
    dirtyFlag_[4] = true;
}

const std::string &SelfServiceUser::getValueOfEmail() const noexcept
{
    static const std::string defaultValue = std::string();
    if(email_)
        return *email_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceUser::getEmail() const noexcept
{
    return email_;
}
void SelfServiceUser::setEmail(const std::string &pEmail) noexcept
{
    email_ = std::make_shared<std::string>(pEmail);
    dirtyFlag_[5] = true;
}
void SelfServiceUser::setEmail(std::string &&pEmail) noexcept
{
    email_ = std::make_shared<std::string>(std::move(pEmail));
    dirtyFlag_[5] = true;
}
void SelfServiceUser::setEmailToNull() noexcept
{
    email_.reset();
    dirtyFlag_[5] = true;
}

const std::string &SelfServiceUser::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &SelfServiceUser::getStatus() const noexcept
{
    return status_;
}
void SelfServiceUser::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[6] = true;
}
void SelfServiceUser::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[6] = true;
}

const ::trantor::Date &SelfServiceUser::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SelfServiceUser::getCreatedAt() const noexcept
{
    return createdAt_;
}
void SelfServiceUser::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

const ::trantor::Date &SelfServiceUser::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &SelfServiceUser::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void SelfServiceUser::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[8] = true;
}

void SelfServiceUser::updateId(const uint64_t id)
{
}

const std::vector<std::string> &SelfServiceUser::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "identity_user_id",
        "client_id",
        "username",
        "mobile_no",
        "email",
        "status",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void SelfServiceUser::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getIdentityUserId())
        {
            binder << getValueOfIdentityUserId();
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
        if(getUsername())
        {
            binder << getValueOfUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getEmail())
        {
            binder << getValueOfEmail();
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
    if(dirtyFlag_[8])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> SelfServiceUser::updateColumns() const
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

void SelfServiceUser::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getIdentityUserId())
        {
            binder << getValueOfIdentityUserId();
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
        if(getUsername())
        {
            binder << getValueOfUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getEmail())
        {
            binder << getValueOfEmail();
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
    if(dirtyFlag_[8])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}
