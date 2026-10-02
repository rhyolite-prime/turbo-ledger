/**
 *  EmailMessage.cc
 *
 *  See EmailMessage.h for the hand-authored-subset note.
 *
 */

#include "EmailMessage.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlNotificationDb;

const std::string EmailMessage::Cols::_id = "\"id\"";
const std::string EmailMessage::Cols::_campaign_id = "\"campaign_id\"";
const std::string EmailMessage::Cols::_client_id = "\"client_id\"";
const std::string EmailMessage::Cols::_group_id = "\"group_id\"";
const std::string EmailMessage::Cols::_staff_id = "\"staff_id\"";
const std::string EmailMessage::Cols::_email_address = "\"email_address\"";
const std::string EmailMessage::Cols::_email_subject = "\"email_subject\"";
const std::string EmailMessage::Cols::_email_message = "\"email_message\"";
const std::string EmailMessage::Cols::_status = "\"status\"";
const std::string EmailMessage::Cols::_error_message = "\"error_message\"";
const std::string EmailMessage::Cols::_created_at = "\"created_at\"";
const std::string EmailMessage::Cols::_updated_at = "\"updated_at\"";
const std::string EmailMessage::primaryKeyName = "id";
const bool EmailMessage::hasPrimaryKey = true;
const std::string EmailMessage::tableName = "\"email_messages\"";

const std::vector<typename EmailMessage::MetaData> EmailMessage::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"campaign_id","std::string","uuid",0,0,0,0},
{"client_id","std::string","character varying",64,0,0,0},
{"group_id","std::string","character varying",64,0,0,0},
{"staff_id","std::string","character varying",64,0,0,0},
{"email_address","std::string","character varying",255,0,0,1},
{"email_subject","std::string","character varying",255,0,0,1},
{"email_message","std::string","text",0,0,0,1},
{"status","std::string","character varying",20,0,0,1},
{"error_message","std::string","text",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &EmailMessage::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
EmailMessage::EmailMessage(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["campaign_id"].isNull())
        {
            campaignId_=std::make_shared<std::string>(r["campaign_id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["group_id"].isNull())
        {
            groupId_=std::make_shared<std::string>(r["group_id"].as<std::string>());
        }
        if(!r["staff_id"].isNull())
        {
            staffId_=std::make_shared<std::string>(r["staff_id"].as<std::string>());
        }
        if(!r["email_address"].isNull())
        {
            emailAddress_=std::make_shared<std::string>(r["email_address"].as<std::string>());
        }
        if(!r["email_subject"].isNull())
        {
            emailSubject_=std::make_shared<std::string>(r["email_subject"].as<std::string>());
        }
        if(!r["email_message"].isNull())
        {
            emailMessage_=std::make_shared<std::string>(r["email_message"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
        }
        if(!r["error_message"].isNull())
        {
            errorMessage_=std::make_shared<std::string>(r["error_message"].as<std::string>());
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
        if(offset + 12 > r.size())
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
            campaignId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            groupId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            staffId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            emailAddress_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            emailSubject_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            emailMessage_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            errorMessage_=std::make_shared<std::string>(r[index].as<std::string>());
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
        index = offset + 11;
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
const std::string &EmailMessage::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getId() const noexcept
{
    return id_;
}
void EmailMessage::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void EmailMessage::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename EmailMessage::PrimaryKeyType & EmailMessage::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &EmailMessage::getValueOfCampaignId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(campaignId_)
        return *campaignId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getCampaignId() const noexcept
{
    return campaignId_;
}
void EmailMessage::setCampaignId(const std::string &pCampaignId) noexcept
{
    campaignId_ = std::make_shared<std::string>(pCampaignId);
    dirtyFlag_[1] = true;
}
void EmailMessage::setCampaignId(std::string &&pCampaignId) noexcept
{
    campaignId_ = std::make_shared<std::string>(std::move(pCampaignId));
    dirtyFlag_[1] = true;
}
void EmailMessage::setCampaignIdToNull() noexcept
{
    campaignId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &EmailMessage::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getClientId() const noexcept
{
    return clientId_;
}
void EmailMessage::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[2] = true;
}
void EmailMessage::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[2] = true;
}
void EmailMessage::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &EmailMessage::getValueOfGroupId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(groupId_)
        return *groupId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getGroupId() const noexcept
{
    return groupId_;
}
void EmailMessage::setGroupId(const std::string &pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(pGroupId);
    dirtyFlag_[3] = true;
}
void EmailMessage::setGroupId(std::string &&pGroupId) noexcept
{
    groupId_ = std::make_shared<std::string>(std::move(pGroupId));
    dirtyFlag_[3] = true;
}
void EmailMessage::setGroupIdToNull() noexcept
{
    groupId_.reset();
    dirtyFlag_[3] = true;
}

const std::string &EmailMessage::getValueOfStaffId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(staffId_)
        return *staffId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getStaffId() const noexcept
{
    return staffId_;
}
void EmailMessage::setStaffId(const std::string &pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(pStaffId);
    dirtyFlag_[4] = true;
}
void EmailMessage::setStaffId(std::string &&pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(std::move(pStaffId));
    dirtyFlag_[4] = true;
}
void EmailMessage::setStaffIdToNull() noexcept
{
    staffId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &EmailMessage::getValueOfEmailAddress() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailAddress_)
        return *emailAddress_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getEmailAddress() const noexcept
{
    return emailAddress_;
}
void EmailMessage::setEmailAddress(const std::string &pEmailAddress) noexcept
{
    emailAddress_ = std::make_shared<std::string>(pEmailAddress);
    dirtyFlag_[5] = true;
}
void EmailMessage::setEmailAddress(std::string &&pEmailAddress) noexcept
{
    emailAddress_ = std::make_shared<std::string>(std::move(pEmailAddress));
    dirtyFlag_[5] = true;
}

const std::string &EmailMessage::getValueOfEmailSubject() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailSubject_)
        return *emailSubject_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getEmailSubject() const noexcept
{
    return emailSubject_;
}
void EmailMessage::setEmailSubject(const std::string &pEmailSubject) noexcept
{
    emailSubject_ = std::make_shared<std::string>(pEmailSubject);
    dirtyFlag_[6] = true;
}
void EmailMessage::setEmailSubject(std::string &&pEmailSubject) noexcept
{
    emailSubject_ = std::make_shared<std::string>(std::move(pEmailSubject));
    dirtyFlag_[6] = true;
}

const std::string &EmailMessage::getValueOfEmailMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailMessage_)
        return *emailMessage_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getEmailMessage() const noexcept
{
    return emailMessage_;
}
void EmailMessage::setEmailMessage(const std::string &pEmailMessage) noexcept
{
    emailMessage_ = std::make_shared<std::string>(pEmailMessage);
    dirtyFlag_[7] = true;
}
void EmailMessage::setEmailMessage(std::string &&pEmailMessage) noexcept
{
    emailMessage_ = std::make_shared<std::string>(std::move(pEmailMessage));
    dirtyFlag_[7] = true;
}

const std::string &EmailMessage::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getStatus() const noexcept
{
    return status_;
}
void EmailMessage::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[8] = true;
}
void EmailMessage::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[8] = true;
}

const std::string &EmailMessage::getValueOfErrorMessage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(errorMessage_)
        return *errorMessage_;
    return defaultValue;
}
const std::shared_ptr<std::string> &EmailMessage::getErrorMessage() const noexcept
{
    return errorMessage_;
}
void EmailMessage::setErrorMessage(const std::string &pErrorMessage) noexcept
{
    errorMessage_ = std::make_shared<std::string>(pErrorMessage);
    dirtyFlag_[9] = true;
}
void EmailMessage::setErrorMessage(std::string &&pErrorMessage) noexcept
{
    errorMessage_ = std::make_shared<std::string>(std::move(pErrorMessage));
    dirtyFlag_[9] = true;
}
void EmailMessage::setErrorMessageToNull() noexcept
{
    errorMessage_.reset();
    dirtyFlag_[9] = true;
}

const ::trantor::Date &EmailMessage::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &EmailMessage::getCreatedAt() const noexcept
{
    return createdAt_;
}
void EmailMessage::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[10] = true;
}

const ::trantor::Date &EmailMessage::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &EmailMessage::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void EmailMessage::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[11] = true;
}

void EmailMessage::updateId(const uint64_t id)
{
}

const std::vector<std::string> &EmailMessage::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "campaign_id",
        "client_id",
        "group_id",
        "staff_id",
        "email_address",
        "email_subject",
        "email_message",
        "status",
        "error_message",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void EmailMessage::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCampaignId())
        {
            binder << getValueOfCampaignId();
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
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getStaffId())
        {
            binder << getValueOfStaffId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getEmailAddress())
        {
            binder << getValueOfEmailAddress();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getEmailSubject())
        {
            binder << getValueOfEmailSubject();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getEmailMessage())
        {
            binder << getValueOfEmailMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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
    if(dirtyFlag_[9])
    {
        if(getErrorMessage())
        {
            binder << getValueOfErrorMessage();
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
    if(dirtyFlag_[11])
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

const std::vector<std::string> EmailMessage::updateColumns() const
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
    return ret;
}

void EmailMessage::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCampaignId())
        {
            binder << getValueOfCampaignId();
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
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getStaffId())
        {
            binder << getValueOfStaffId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getEmailAddress())
        {
            binder << getValueOfEmailAddress();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getEmailSubject())
        {
            binder << getValueOfEmailSubject();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getEmailMessage())
        {
            binder << getValueOfEmailMessage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
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
    if(dirtyFlag_[9])
    {
        if(getErrorMessage())
        {
            binder << getValueOfErrorMessage();
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
    if(dirtyFlag_[11])
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
