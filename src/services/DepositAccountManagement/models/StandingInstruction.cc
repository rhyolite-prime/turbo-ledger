/**
 *  StandingInstruction.cc
 *
 *  See StandingInstruction.h for the hand-authored-subset note.
 *
 */

#include "StandingInstruction.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string StandingInstruction::Cols::_id = "\"id\"";
const std::string StandingInstruction::Cols::_business_id = "\"business_id\"";
const std::string StandingInstruction::Cols::_name = "\"name\"";
const std::string StandingInstruction::Cols::_description = "\"description\"";
const std::string StandingInstruction::Cols::_client_id = "\"client_id\"";
const std::string StandingInstruction::Cols::_from_office_id = "\"from_office_id\"";
const std::string StandingInstruction::Cols::_from_client_id = "\"from_client_id\"";
const std::string StandingInstruction::Cols::_from_account_type = "\"from_account_type\"";
const std::string StandingInstruction::Cols::_from_account_id = "\"from_account_id\"";
const std::string StandingInstruction::Cols::_to_office_id = "\"to_office_id\"";
const std::string StandingInstruction::Cols::_to_client_id = "\"to_client_id\"";
const std::string StandingInstruction::Cols::_to_account_type = "\"to_account_type\"";
const std::string StandingInstruction::Cols::_to_account_id = "\"to_account_id\"";
const std::string StandingInstruction::Cols::_instruction_type = "\"instruction_type\"";
const std::string StandingInstruction::Cols::_status = "\"status\"";
const std::string StandingInstruction::Cols::_priority = "\"priority\"";
const std::string StandingInstruction::Cols::_transfer_type = "\"transfer_type\"";
const std::string StandingInstruction::Cols::_amount = "\"amount\"";
const std::string StandingInstruction::Cols::_valid_from = "\"valid_from\"";
const std::string StandingInstruction::Cols::_valid_till = "\"valid_till\"";
const std::string StandingInstruction::Cols::_recurrence_type = "\"recurrence_type\"";
const std::string StandingInstruction::Cols::_recurrence_frequency = "\"recurrence_frequency\"";
const std::string StandingInstruction::Cols::_recurrence_interval = "\"recurrence_interval\"";
const std::string StandingInstruction::Cols::_recurrence_on_day = "\"recurrence_on_day\"";
const std::string StandingInstruction::Cols::_last_run_date = "\"last_run_date\"";
const std::string StandingInstruction::Cols::_created_by = "\"created_by\"";
const std::string StandingInstruction::Cols::_created_at = "\"created_at\"";
const std::string StandingInstruction::Cols::_updated_by = "\"updated_by\"";
const std::string StandingInstruction::Cols::_updated_at = "\"updated_at\"";
const std::string StandingInstruction::primaryKeyName = "id";
const bool StandingInstruction::hasPrimaryKey = true;
const std::string StandingInstruction::tableName = "\"standing_instruction\"";

const std::vector<typename StandingInstruction::MetaData> StandingInstruction::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"name","std::string","character varying",100,0,0,1},
{"description","std::string","character varying",500,0,0,0},
{"client_id","std::string","uuid",0,0,0,0},
{"from_office_id","std::string","uuid",0,0,0,0},
{"from_client_id","std::string","uuid",0,0,0,0},
{"from_account_type","int32_t","integer",4,0,0,1},
{"from_account_id","std::string","uuid",0,0,0,1},
{"to_office_id","std::string","uuid",0,0,0,0},
{"to_client_id","std::string","uuid",0,0,0,0},
{"to_account_type","int32_t","integer",4,0,0,1},
{"to_account_id","std::string","uuid",0,0,0,1},
{"instruction_type","int32_t","integer",4,0,0,1},
{"status","int32_t","integer",4,0,0,1},
{"priority","int32_t","integer",4,0,0,1},
{"transfer_type","int32_t","integer",4,0,0,1},
{"amount","std::string","numeric",0,0,0,0},
{"valid_from","::trantor::Date","date",0,0,0,1},
{"valid_till","::trantor::Date","date",0,0,0,0},
{"recurrence_type","int32_t","integer",4,0,0,1},
{"recurrence_frequency","int32_t","integer",4,0,0,0},
{"recurrence_interval","int32_t","integer",4,0,0,0},
{"recurrence_on_day","int32_t","integer",4,0,0,0},
{"last_run_date","::trantor::Date","date",0,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &StandingInstruction::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
StandingInstruction::StandingInstruction(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["business_id"].isNull())
        {
            businessId_=std::make_shared<std::string>(r["business_id"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["from_office_id"].isNull())
        {
            fromOfficeId_=std::make_shared<std::string>(r["from_office_id"].as<std::string>());
        }
        if(!r["from_client_id"].isNull())
        {
            fromClientId_=std::make_shared<std::string>(r["from_client_id"].as<std::string>());
        }
        if(!r["from_account_type"].isNull())
        {
            fromAccountType_=std::make_shared<int32_t>(r["from_account_type"].as<int32_t>());
        }
        if(!r["from_account_id"].isNull())
        {
            fromAccountId_=std::make_shared<std::string>(r["from_account_id"].as<std::string>());
        }
        if(!r["to_office_id"].isNull())
        {
            toOfficeId_=std::make_shared<std::string>(r["to_office_id"].as<std::string>());
        }
        if(!r["to_client_id"].isNull())
        {
            toClientId_=std::make_shared<std::string>(r["to_client_id"].as<std::string>());
        }
        if(!r["to_account_type"].isNull())
        {
            toAccountType_=std::make_shared<int32_t>(r["to_account_type"].as<int32_t>());
        }
        if(!r["to_account_id"].isNull())
        {
            toAccountId_=std::make_shared<std::string>(r["to_account_id"].as<std::string>());
        }
        if(!r["instruction_type"].isNull())
        {
            instructionType_=std::make_shared<int32_t>(r["instruction_type"].as<int32_t>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["priority"].isNull())
        {
            priority_=std::make_shared<int32_t>(r["priority"].as<int32_t>());
        }
        if(!r["transfer_type"].isNull())
        {
            transferType_=std::make_shared<int32_t>(r["transfer_type"].as<int32_t>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["valid_from"].isNull())
        {
            auto daysStr = r["valid_from"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            validFrom_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["valid_till"].isNull())
        {
            auto daysStr = r["valid_till"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            validTill_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["recurrence_type"].isNull())
        {
            recurrenceType_=std::make_shared<int32_t>(r["recurrence_type"].as<int32_t>());
        }
        if(!r["recurrence_frequency"].isNull())
        {
            recurrenceFrequency_=std::make_shared<int32_t>(r["recurrence_frequency"].as<int32_t>());
        }
        if(!r["recurrence_interval"].isNull())
        {
            recurrenceInterval_=std::make_shared<int32_t>(r["recurrence_interval"].as<int32_t>());
        }
        if(!r["recurrence_on_day"].isNull())
        {
            recurrenceOnDay_=std::make_shared<int32_t>(r["recurrence_on_day"].as<int32_t>());
        }
        if(!r["last_run_date"].isNull())
        {
            auto daysStr = r["last_run_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            lastRunDate_=std::make_shared<::trantor::Date>(t*1000000);
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
        if(!r["updated_by"].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r["updated_by"].as<std::string>());
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
        if(offset + 29 > r.size())
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
            businessId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            fromOfficeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            fromClientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            fromAccountType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            fromAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            toOfficeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            toClientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            toAccountType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            toAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            instructionType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            priority_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            transferType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            validFrom_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            validTill_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            recurrenceType_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 21;
        if(!r[index].isNull())
        {
            recurrenceFrequency_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            recurrenceInterval_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            recurrenceOnDay_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 24;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            lastRunDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 25;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 26;
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
        index = offset + 27;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 28;
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
const std::string &StandingInstruction::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getId() const noexcept
{
    return id_;
}
void StandingInstruction::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void StandingInstruction::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename StandingInstruction::PrimaryKeyType & StandingInstruction::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &StandingInstruction::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getBusinessId() const noexcept
{
    return businessId_;
}
void StandingInstruction::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void StandingInstruction::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void StandingInstruction::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &StandingInstruction::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getName() const noexcept
{
    return name_;
}
void StandingInstruction::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[2] = true;
}
void StandingInstruction::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[2] = true;
}

const std::string &StandingInstruction::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getDescription() const noexcept
{
    return description_;
}
void StandingInstruction::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void StandingInstruction::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void StandingInstruction::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const std::string &StandingInstruction::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getClientId() const noexcept
{
    return clientId_;
}
void StandingInstruction::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[4] = true;
}
void StandingInstruction::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[4] = true;
}
void StandingInstruction::setClientIdToNull() noexcept
{
    clientId_.reset();
    dirtyFlag_[4] = true;
}

const std::string &StandingInstruction::getValueOfFromOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromOfficeId_)
        return *fromOfficeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getFromOfficeId() const noexcept
{
    return fromOfficeId_;
}
void StandingInstruction::setFromOfficeId(const std::string &pFromOfficeId) noexcept
{
    fromOfficeId_ = std::make_shared<std::string>(pFromOfficeId);
    dirtyFlag_[5] = true;
}
void StandingInstruction::setFromOfficeId(std::string &&pFromOfficeId) noexcept
{
    fromOfficeId_ = std::make_shared<std::string>(std::move(pFromOfficeId));
    dirtyFlag_[5] = true;
}
void StandingInstruction::setFromOfficeIdToNull() noexcept
{
    fromOfficeId_.reset();
    dirtyFlag_[5] = true;
}

const std::string &StandingInstruction::getValueOfFromClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromClientId_)
        return *fromClientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getFromClientId() const noexcept
{
    return fromClientId_;
}
void StandingInstruction::setFromClientId(const std::string &pFromClientId) noexcept
{
    fromClientId_ = std::make_shared<std::string>(pFromClientId);
    dirtyFlag_[6] = true;
}
void StandingInstruction::setFromClientId(std::string &&pFromClientId) noexcept
{
    fromClientId_ = std::make_shared<std::string>(std::move(pFromClientId));
    dirtyFlag_[6] = true;
}
void StandingInstruction::setFromClientIdToNull() noexcept
{
    fromClientId_.reset();
    dirtyFlag_[6] = true;
}

const int32_t &StandingInstruction::getValueOfFromAccountType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(fromAccountType_)
        return *fromAccountType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getFromAccountType() const noexcept
{
    return fromAccountType_;
}
void StandingInstruction::setFromAccountType(const int32_t &pFromAccountType) noexcept
{
    fromAccountType_ = std::make_shared<int32_t>(pFromAccountType);
    dirtyFlag_[7] = true;
}

const std::string &StandingInstruction::getValueOfFromAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fromAccountId_)
        return *fromAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getFromAccountId() const noexcept
{
    return fromAccountId_;
}
void StandingInstruction::setFromAccountId(const std::string &pFromAccountId) noexcept
{
    fromAccountId_ = std::make_shared<std::string>(pFromAccountId);
    dirtyFlag_[8] = true;
}
void StandingInstruction::setFromAccountId(std::string &&pFromAccountId) noexcept
{
    fromAccountId_ = std::make_shared<std::string>(std::move(pFromAccountId));
    dirtyFlag_[8] = true;
}

const std::string &StandingInstruction::getValueOfToOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toOfficeId_)
        return *toOfficeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getToOfficeId() const noexcept
{
    return toOfficeId_;
}
void StandingInstruction::setToOfficeId(const std::string &pToOfficeId) noexcept
{
    toOfficeId_ = std::make_shared<std::string>(pToOfficeId);
    dirtyFlag_[9] = true;
}
void StandingInstruction::setToOfficeId(std::string &&pToOfficeId) noexcept
{
    toOfficeId_ = std::make_shared<std::string>(std::move(pToOfficeId));
    dirtyFlag_[9] = true;
}
void StandingInstruction::setToOfficeIdToNull() noexcept
{
    toOfficeId_.reset();
    dirtyFlag_[9] = true;
}

const std::string &StandingInstruction::getValueOfToClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toClientId_)
        return *toClientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getToClientId() const noexcept
{
    return toClientId_;
}
void StandingInstruction::setToClientId(const std::string &pToClientId) noexcept
{
    toClientId_ = std::make_shared<std::string>(pToClientId);
    dirtyFlag_[10] = true;
}
void StandingInstruction::setToClientId(std::string &&pToClientId) noexcept
{
    toClientId_ = std::make_shared<std::string>(std::move(pToClientId));
    dirtyFlag_[10] = true;
}
void StandingInstruction::setToClientIdToNull() noexcept
{
    toClientId_.reset();
    dirtyFlag_[10] = true;
}

const int32_t &StandingInstruction::getValueOfToAccountType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(toAccountType_)
        return *toAccountType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getToAccountType() const noexcept
{
    return toAccountType_;
}
void StandingInstruction::setToAccountType(const int32_t &pToAccountType) noexcept
{
    toAccountType_ = std::make_shared<int32_t>(pToAccountType);
    dirtyFlag_[11] = true;
}

const std::string &StandingInstruction::getValueOfToAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(toAccountId_)
        return *toAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getToAccountId() const noexcept
{
    return toAccountId_;
}
void StandingInstruction::setToAccountId(const std::string &pToAccountId) noexcept
{
    toAccountId_ = std::make_shared<std::string>(pToAccountId);
    dirtyFlag_[12] = true;
}
void StandingInstruction::setToAccountId(std::string &&pToAccountId) noexcept
{
    toAccountId_ = std::make_shared<std::string>(std::move(pToAccountId));
    dirtyFlag_[12] = true;
}

const int32_t &StandingInstruction::getValueOfInstructionType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(instructionType_)
        return *instructionType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getInstructionType() const noexcept
{
    return instructionType_;
}
void StandingInstruction::setInstructionType(const int32_t &pInstructionType) noexcept
{
    instructionType_ = std::make_shared<int32_t>(pInstructionType);
    dirtyFlag_[13] = true;
}

const int32_t &StandingInstruction::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getStatus() const noexcept
{
    return status_;
}
void StandingInstruction::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[14] = true;
}

const int32_t &StandingInstruction::getValueOfPriority() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(priority_)
        return *priority_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getPriority() const noexcept
{
    return priority_;
}
void StandingInstruction::setPriority(const int32_t &pPriority) noexcept
{
    priority_ = std::make_shared<int32_t>(pPriority);
    dirtyFlag_[15] = true;
}

const int32_t &StandingInstruction::getValueOfTransferType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(transferType_)
        return *transferType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getTransferType() const noexcept
{
    return transferType_;
}
void StandingInstruction::setTransferType(const int32_t &pTransferType) noexcept
{
    transferType_ = std::make_shared<int32_t>(pTransferType);
    dirtyFlag_[16] = true;
}

const std::string &StandingInstruction::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getAmount() const noexcept
{
    return amount_;
}
void StandingInstruction::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[17] = true;
}
void StandingInstruction::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[17] = true;
}
void StandingInstruction::setAmountToNull() noexcept
{
    amount_.reset();
    dirtyFlag_[17] = true;
}

const ::trantor::Date &StandingInstruction::getValueOfValidFrom() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(validFrom_)
        return *validFrom_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &StandingInstruction::getValidFrom() const noexcept
{
    return validFrom_;
}
void StandingInstruction::setValidFrom(const ::trantor::Date &pValidFrom) noexcept
{
    validFrom_ = std::make_shared<::trantor::Date>(pValidFrom);
    dirtyFlag_[18] = true;
}

const ::trantor::Date &StandingInstruction::getValueOfValidTill() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(validTill_)
        return *validTill_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &StandingInstruction::getValidTill() const noexcept
{
    return validTill_;
}
void StandingInstruction::setValidTill(const ::trantor::Date &pValidTill) noexcept
{
    validTill_ = std::make_shared<::trantor::Date>(pValidTill);
    dirtyFlag_[19] = true;
}
void StandingInstruction::setValidTillToNull() noexcept
{
    validTill_.reset();
    dirtyFlag_[19] = true;
}

const int32_t &StandingInstruction::getValueOfRecurrenceType() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(recurrenceType_)
        return *recurrenceType_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getRecurrenceType() const noexcept
{
    return recurrenceType_;
}
void StandingInstruction::setRecurrenceType(const int32_t &pRecurrenceType) noexcept
{
    recurrenceType_ = std::make_shared<int32_t>(pRecurrenceType);
    dirtyFlag_[20] = true;
}

const int32_t &StandingInstruction::getValueOfRecurrenceFrequency() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(recurrenceFrequency_)
        return *recurrenceFrequency_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getRecurrenceFrequency() const noexcept
{
    return recurrenceFrequency_;
}
void StandingInstruction::setRecurrenceFrequency(const int32_t &pRecurrenceFrequency) noexcept
{
    recurrenceFrequency_ = std::make_shared<int32_t>(pRecurrenceFrequency);
    dirtyFlag_[21] = true;
}
void StandingInstruction::setRecurrenceFrequencyToNull() noexcept
{
    recurrenceFrequency_.reset();
    dirtyFlag_[21] = true;
}

const int32_t &StandingInstruction::getValueOfRecurrenceInterval() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(recurrenceInterval_)
        return *recurrenceInterval_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getRecurrenceInterval() const noexcept
{
    return recurrenceInterval_;
}
void StandingInstruction::setRecurrenceInterval(const int32_t &pRecurrenceInterval) noexcept
{
    recurrenceInterval_ = std::make_shared<int32_t>(pRecurrenceInterval);
    dirtyFlag_[22] = true;
}
void StandingInstruction::setRecurrenceIntervalToNull() noexcept
{
    recurrenceInterval_.reset();
    dirtyFlag_[22] = true;
}

const int32_t &StandingInstruction::getValueOfRecurrenceOnDay() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(recurrenceOnDay_)
        return *recurrenceOnDay_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstruction::getRecurrenceOnDay() const noexcept
{
    return recurrenceOnDay_;
}
void StandingInstruction::setRecurrenceOnDay(const int32_t &pRecurrenceOnDay) noexcept
{
    recurrenceOnDay_ = std::make_shared<int32_t>(pRecurrenceOnDay);
    dirtyFlag_[23] = true;
}
void StandingInstruction::setRecurrenceOnDayToNull() noexcept
{
    recurrenceOnDay_.reset();
    dirtyFlag_[23] = true;
}

const ::trantor::Date &StandingInstruction::getValueOfLastRunDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(lastRunDate_)
        return *lastRunDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &StandingInstruction::getLastRunDate() const noexcept
{
    return lastRunDate_;
}
void StandingInstruction::setLastRunDate(const ::trantor::Date &pLastRunDate) noexcept
{
    lastRunDate_ = std::make_shared<::trantor::Date>(pLastRunDate);
    dirtyFlag_[24] = true;
}
void StandingInstruction::setLastRunDateToNull() noexcept
{
    lastRunDate_.reset();
    dirtyFlag_[24] = true;
}

const std::string &StandingInstruction::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getCreatedBy() const noexcept
{
    return createdBy_;
}
void StandingInstruction::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[25] = true;
}
void StandingInstruction::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[25] = true;
}
void StandingInstruction::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[25] = true;
}

const ::trantor::Date &StandingInstruction::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &StandingInstruction::getCreatedAt() const noexcept
{
    return createdAt_;
}
void StandingInstruction::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[26] = true;
}

const std::string &StandingInstruction::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstruction::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void StandingInstruction::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[27] = true;
}
void StandingInstruction::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[27] = true;
}
void StandingInstruction::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[27] = true;
}

const ::trantor::Date &StandingInstruction::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &StandingInstruction::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void StandingInstruction::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[28] = true;
}

void StandingInstruction::updateId(const uint64_t id)
{
}

const std::vector<std::string> &StandingInstruction::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "name",
        "description",
        "client_id",
        "from_office_id",
        "from_client_id",
        "from_account_type",
        "from_account_id",
        "to_office_id",
        "to_client_id",
        "to_account_type",
        "to_account_id",
        "instruction_type",
        "status",
        "priority",
        "transfer_type",
        "amount",
        "valid_from",
        "valid_till",
        "recurrence_type",
        "recurrence_frequency",
        "recurrence_interval",
        "recurrence_on_day",
        "last_run_date",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void StandingInstruction::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getFromOfficeId())
        {
            binder << getValueOfFromOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getFromClientId())
        {
            binder << getValueOfFromClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getFromAccountType())
        {
            binder << getValueOfFromAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getFromAccountId())
        {
            binder << getValueOfFromAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getToOfficeId())
        {
            binder << getValueOfToOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getToClientId())
        {
            binder << getValueOfToClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getToAccountType())
        {
            binder << getValueOfToAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getToAccountId())
        {
            binder << getValueOfToAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getInstructionType())
        {
            binder << getValueOfInstructionType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getPriority())
        {
            binder << getValueOfPriority();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getTransferType())
        {
            binder << getValueOfTransferType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
    {
        if(getValidFrom())
        {
            binder << getValueOfValidFrom();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getValidTill())
        {
            binder << getValueOfValidTill();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getRecurrenceType())
        {
            binder << getValueOfRecurrenceType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getRecurrenceFrequency())
        {
            binder << getValueOfRecurrenceFrequency();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getRecurrenceInterval())
        {
            binder << getValueOfRecurrenceInterval();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getRecurrenceOnDay())
        {
            binder << getValueOfRecurrenceOnDay();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getLastRunDate())
        {
            binder << getValueOfLastRunDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
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
    if(dirtyFlag_[26])
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
    if(dirtyFlag_[27])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
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

const std::vector<std::string> StandingInstruction::updateColumns() const
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
    if(dirtyFlag_[21])
    {
        ret.push_back(getColumnName(21));
    }
    if(dirtyFlag_[22])
    {
        ret.push_back(getColumnName(22));
    }
    if(dirtyFlag_[23])
    {
        ret.push_back(getColumnName(23));
    }
    if(dirtyFlag_[24])
    {
        ret.push_back(getColumnName(24));
    }
    if(dirtyFlag_[25])
    {
        ret.push_back(getColumnName(25));
    }
    if(dirtyFlag_[26])
    {
        ret.push_back(getColumnName(26));
    }
    if(dirtyFlag_[27])
    {
        ret.push_back(getColumnName(27));
    }
    if(dirtyFlag_[28])
    {
        ret.push_back(getColumnName(28));
    }
    return ret;
}

void StandingInstruction::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getFromOfficeId())
        {
            binder << getValueOfFromOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getFromClientId())
        {
            binder << getValueOfFromClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getFromAccountType())
        {
            binder << getValueOfFromAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getFromAccountId())
        {
            binder << getValueOfFromAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getToOfficeId())
        {
            binder << getValueOfToOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getToClientId())
        {
            binder << getValueOfToClientId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getToAccountType())
        {
            binder << getValueOfToAccountType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getToAccountId())
        {
            binder << getValueOfToAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getInstructionType())
        {
            binder << getValueOfInstructionType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getPriority())
        {
            binder << getValueOfPriority();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getTransferType())
        {
            binder << getValueOfTransferType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
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
    if(dirtyFlag_[18])
    {
        if(getValidFrom())
        {
            binder << getValueOfValidFrom();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getValidTill())
        {
            binder << getValueOfValidTill();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getRecurrenceType())
        {
            binder << getValueOfRecurrenceType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getRecurrenceFrequency())
        {
            binder << getValueOfRecurrenceFrequency();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getRecurrenceInterval())
        {
            binder << getValueOfRecurrenceInterval();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getRecurrenceOnDay())
        {
            binder << getValueOfRecurrenceOnDay();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getLastRunDate())
        {
            binder << getValueOfLastRunDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
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
    if(dirtyFlag_[26])
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
    if(dirtyFlag_[27])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
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
