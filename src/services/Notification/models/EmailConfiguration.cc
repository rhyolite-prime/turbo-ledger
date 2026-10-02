/**
 *  EmailConfiguration.cc
 *
 *  See EmailConfiguration.h for the hand-authored-subset note.
 *
 */

#include "EmailConfiguration.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlNotificationDb;

const std::string EmailConfiguration::Cols::_id = "\"id\"";
const std::string EmailConfiguration::Cols::_smtp_host = "\"smtp_host\"";
const std::string EmailConfiguration::Cols::_smtp_port = "\"smtp_port\"";
const std::string EmailConfiguration::Cols::_smtp_username = "\"smtp_username\"";
const std::string EmailConfiguration::Cols::_smtp_password = "\"smtp_password\"";
const std::string EmailConfiguration::Cols::_from_email = "\"from_email\"";
const std::string EmailConfiguration::Cols::_from_name = "\"from_name\"";
const std::string EmailConfiguration::Cols::_use_tls = "\"use_tls\"";
const std::string EmailConfiguration::Cols::_updated_at = "\"updated_at\"";
const std::string EmailConfiguration::primaryKeyName = "id";
const bool EmailConfiguration::hasPrimaryKey = true;
const std::string EmailConfiguration::tableName = "\"email_configuration\"";

const std::vector<typename EmailConfiguration::MetaData> EmailConfiguration::metaData_={
{"id","int32_t","integer",4,0,1,1},
{"smtp_host","std::string","character varying",255,0,0,0},
{"smtp_port","int32_t","integer",4,0,0,1},
{"smtp_username","std::string","character varying",255,0,0,0},
{"smtp_password","std::string","character varying",255,0,0,0},
{"from_email","std::string","character varying",255,0,0,0},
{"from_name","std::string","character varying",255,0,0,0},
{"use_tls","bool","boolean",1,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &EmailConfiguration::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
EmailConfiguration::EmailConfiguration(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["smtp_host"].isNull())
        {
            smtpHost_=std::make_shared<std::string>(r["smtp_host"].as<std::string>());
        }
        if(!r["smtp_port"].isNull())
        {
            smtpPort_=std::make_shared<int32_t>(r["smtp_port"].as<int32_t>());
        }
        if(!r["smtp_username"].isNull())
        {
            smtpUsername_=std::make_shared<std::string>(r["smtp_username"].as<std::string>());
        }
        if(!r["smtp_password"].isNull())
        {
            smtpPassword_=std::make_shared<std::string>(r["smtp_password"].as<std::string>());
        }
        if(!r["from_email"].isNull())
        {
            fromEmail_=std::make_shared<std::string>(r["from_email"].as<std::string>());
        }
        if(!r["from_name"].isNull())
        {
            fromName_=std::make_shared<std::string>(r["from_name"].as<std::string>());
        }
        if(!r["use_tls"].isNull())
        {
            useTls_=std::make_shared<bool>(r["use_tls"].as<bool>());
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
            id_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            smtpHost_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            smtpPort_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            smtpUsername_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            smtpPassword_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            fromEmail_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            fromName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            useTls_=std::make_shared<bool>(r[index].as<bool>());
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
const int32_t &EmailConfiguration::getValueOfId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &EmailConfiguration::getId() const noexcept
{
    return id_;
}
void EmailConfiguration::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename EmailConfiguration::PrimaryKeyType & EmailConfiguration::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &EmailConfiguration::getValueOfSmtpHost() const noexcept
{
    static const std::string defaultValue = std::string();
    if(smtpHost_)
        return *smtpHost_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailConfiguration::getSmtpHost() const noexcept
{
    return smtpHost_;
}
void EmailConfiguration::setSmtpHost(const std::string &pSmtpHost) noexcept
{
    smtpHost_ = std::make_shared<std::string>(pSmtpHost);
    dirtyFlag_[1] = true;
}
void EmailConfiguration::setSmtpHost(std::string &&pSmtpHost) noexcept
{
    smtpHost_ = std::make_shared<std::string>(std::move(pSmtpHost));
    dirtyFlag_[1] = true;
}
void EmailConfiguration::setSmtpHostToNull() noexcept
{
    smtpHost_.reset();
    dirtyFlag_[1] = true;
}

const int32_t &EmailConfiguration::getValueOfSmtpPort() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(smtpPort_)
        return *smtpPort_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &EmailConfiguration::getSmtpPort() const noexcept
{
    return smtpPort_;
}
void EmailConfiguration::setSmtpPort(const int32_t &pSmtpPort) noexcept
{
    smtpPort_ = std::make_shared<int32_t>(pSmtpPort);
    dirtyFlag_[2] = true;
}

const std::string &EmailConfiguration::getValueOfSmtpUsername() const noexcept
{
    static const std::string defaultValue = std::string();
    if(smtpUsername_)
        return *smtpUsername_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailConfiguration::getSmtpUsername() const noexcept
{
    return smtpUsername_;
}
void EmailConfiguration::setSmtpUsername(const std::string &pSmtpUsername) noexcept
{
    smtpUsername_ = std::make_shared<std::string>(pSmtpUsername);
    dirtyFlag_[3] = true;
}
void EmailConfiguration::setSmtpUsername(std::string &&pSmtpUsername) noexcept
{
    smtpUsername_ = std::make_shared<std::string>(std::move(pSmtpUsername));
    dirtyFlag_[3] = true;
}
void EmailConfiguration::setSmtpUsernameToNull() noexcept
{
    smtpUsername_.reset();
    dirtyFlag_[3] = true;
}

const std::string &EmailConfiguration::getValueOfSmtpPassword() const noexcept
{
    static const std::string defaultValue = std::string();
    if(smtpPassword_)
        return *smtpPassword_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailConfiguration::getSmtpPassword() const noexcept
{
    return smtpPassword_;
}
void EmailConfiguration::setSmtpPassword(const std::string &pSmtpPassword) noexcept
{
    smtpPassword_ = std::make_shared<std::string>(pSmtpPassword);
    dirtyFlag_[4] = true;
}
void EmailConfiguration::setSmtpPassword(std::string &&pSmtpPassword) noexcept
{
    smtpPassword_ = std::make_shared<std::string>(std::move(pSmtpPassword));
    dirtyFlag_[4] = true;
}
void EmailConfiguration::setSmtpPasswordToNull() noexcept
{
    smtpPassword_.reset();
    dirtyFlag_[4] = true;
}

const std::string &EmailConfiguration::getValueOfFromEmail() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromEmail_)
        return *fromEmail_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailConfiguration::getFromEmail() const noexcept
{
    return fromEmail_;
}
void EmailConfiguration::setFromEmail(const std::string &pFromEmail) noexcept
{
    fromEmail_ = std::make_shared<std::string>(pFromEmail);
    dirtyFlag_[5] = true;
}
void EmailConfiguration::setFromEmail(std::string &&pFromEmail) noexcept
{
    fromEmail_ = std::make_shared<std::string>(std::move(pFromEmail));
    dirtyFlag_[5] = true;
}
void EmailConfiguration::setFromEmailToNull() noexcept
{
    fromEmail_.reset();
    dirtyFlag_[5] = true;
}

const std::string &EmailConfiguration::getValueOfFromName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromName_)
        return *fromName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailConfiguration::getFromName() const noexcept
{
    return fromName_;
}
void EmailConfiguration::setFromName(const std::string &pFromName) noexcept
{
    fromName_ = std::make_shared<std::string>(pFromName);
    dirtyFlag_[6] = true;
}
void EmailConfiguration::setFromName(std::string &&pFromName) noexcept
{
    fromName_ = std::make_shared<std::string>(std::move(pFromName));
    dirtyFlag_[6] = true;
}
void EmailConfiguration::setFromNameToNull() noexcept
{
    fromName_.reset();
    dirtyFlag_[6] = true;
}

const bool &EmailConfiguration::getValueOfUseTls() const noexcept
{
    static const bool defaultValue = bool();
    if(useTls_)
        return *useTls_;
    return defaultValue;
}
const std::shared_ptr<bool> &EmailConfiguration::getUseTls() const noexcept
{
    return useTls_;
}
void EmailConfiguration::setUseTls(const bool &pUseTls) noexcept
{
    useTls_ = std::make_shared<bool>(pUseTls);
    dirtyFlag_[7] = true;
}

const ::trantor::Date &EmailConfiguration::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &EmailConfiguration::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void EmailConfiguration::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[8] = true;
}

void EmailConfiguration::updateId(const uint64_t id)
{
}

const std::vector<std::string> &EmailConfiguration::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "smtp_host",
        "smtp_port",
        "smtp_username",
        "smtp_password",
        "from_email",
        "from_name",
        "use_tls",
        "updated_at"
    };
    return inCols;
}

void EmailConfiguration::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSmtpHost())
        {
            binder << getValueOfSmtpHost();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getSmtpPort())
        {
            binder << getValueOfSmtpPort();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSmtpUsername())
        {
            binder << getValueOfSmtpUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getSmtpPassword())
        {
            binder << getValueOfSmtpPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getFromEmail())
        {
            binder << getValueOfFromEmail();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getFromName())
        {
            binder << getValueOfFromName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getUseTls())
        {
            binder << getValueOfUseTls();
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

const std::vector<std::string> EmailConfiguration::updateColumns() const
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

void EmailConfiguration::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSmtpHost())
        {
            binder << getValueOfSmtpHost();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getSmtpPort())
        {
            binder << getValueOfSmtpPort();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSmtpUsername())
        {
            binder << getValueOfSmtpUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getSmtpPassword())
        {
            binder << getValueOfSmtpPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getFromEmail())
        {
            binder << getValueOfFromEmail();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getFromName())
        {
            binder << getValueOfFromName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getUseTls())
        {
            binder << getValueOfUseTls();
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
