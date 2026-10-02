/**
 *  ProvisioningHistory.cc
 *
 *  See ProvisioningHistory.h for the hand-authored-subset note.
 *
 */

#include "ProvisioningHistory.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ProvisioningHistory::Cols::_id = "\"id\"";
const std::string ProvisioningHistory::Cols::_journal_entry_created = "\"journal_entry_created\"";
const std::string ProvisioningHistory::Cols::_createdby_id = "\"createdby_id\"";
const std::string ProvisioningHistory::Cols::_created_date = "\"created_date\"";
const std::string ProvisioningHistory::Cols::_lastmodifiedby_id = "\"lastmodifiedby_id\"";
const std::string ProvisioningHistory::Cols::_lastmodified_date = "\"lastmodified_date\"";
const std::string ProvisioningHistory::primaryKeyName = "id";
const bool ProvisioningHistory::hasPrimaryKey = true;
const std::string ProvisioningHistory::tableName = "\"provisioning_history\"";

const std::vector<typename ProvisioningHistory::MetaData> ProvisioningHistory::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"journal_entry_created","bool","boolean",1,0,0,0},
{"createdby_id","std::string","uuid",0,0,0,0},
{"created_date","::trantor::Date","date",0,0,0,0},
{"lastmodifiedby_id","std::string","uuid",0,0,0,0},
{"lastmodified_date","::trantor::Date","date",0,0,0,0}
};
const std::string &ProvisioningHistory::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ProvisioningHistory::ProvisioningHistory(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["journal_entry_created"].isNull())
        {
            journalEntryCreated_=std::make_shared<bool>(r["journal_entry_created"].as<bool>());
        }
        if(!r["createdby_id"].isNull())
        {
            createdbyId_=std::make_shared<std::string>(r["createdby_id"].as<std::string>());
        }
        if(!r["created_date"].isNull())
        {
            auto daysStr = r["created_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            createdDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["lastmodifiedby_id"].isNull())
        {
            lastmodifiedbyId_=std::make_shared<std::string>(r["lastmodifiedby_id"].as<std::string>());
        }
        if(!r["lastmodified_date"].isNull())
        {
            auto daysStr = r["lastmodified_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            lastmodifiedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 6 > r.size())
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
            journalEntryCreated_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            createdbyId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            createdDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            lastmodifiedbyId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            lastmodifiedDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
    }

}
const std::string &ProvisioningHistory::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningHistory::getId() const noexcept
{
    return id_;
}
void ProvisioningHistory::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ProvisioningHistory::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ProvisioningHistory::PrimaryKeyType & ProvisioningHistory::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const bool &ProvisioningHistory::getValueOfJournalEntryCreated() const noexcept
{
    static const bool defaultValue = bool();
    if(journalEntryCreated_)
        return *journalEntryCreated_;
    return defaultValue;
}
const std::shared_ptr<bool> &ProvisioningHistory::getJournalEntryCreated() const noexcept
{
    return journalEntryCreated_;
}
void ProvisioningHistory::setJournalEntryCreated(const bool &pJournalEntryCreated) noexcept
{
    journalEntryCreated_ = std::make_shared<bool>(pJournalEntryCreated);
    dirtyFlag_[1] = true;
}
void ProvisioningHistory::setJournalEntryCreatedToNull() noexcept
{
    journalEntryCreated_.reset();
    dirtyFlag_[1] = true;
}

const std::string &ProvisioningHistory::getValueOfCreatedbyId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdbyId_)
        return *createdbyId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningHistory::getCreatedbyId() const noexcept
{
    return createdbyId_;
}
void ProvisioningHistory::setCreatedbyId(const std::string &pCreatedbyId) noexcept
{
    createdbyId_ = std::make_shared<std::string>(pCreatedbyId);
    dirtyFlag_[2] = true;
}
void ProvisioningHistory::setCreatedbyId(std::string &&pCreatedbyId) noexcept
{
    createdbyId_ = std::make_shared<std::string>(std::move(pCreatedbyId));
    dirtyFlag_[2] = true;
}
void ProvisioningHistory::setCreatedbyIdToNull() noexcept
{
    createdbyId_.reset();
    dirtyFlag_[2] = true;
}

const ::trantor::Date &ProvisioningHistory::getValueOfCreatedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdDate_)
        return *createdDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ProvisioningHistory::getCreatedDate() const noexcept
{
    return createdDate_;
}
void ProvisioningHistory::setCreatedDate(const ::trantor::Date &pCreatedDate) noexcept
{
    createdDate_ = std::make_shared<::trantor::Date>(pCreatedDate);
    dirtyFlag_[3] = true;
}
void ProvisioningHistory::setCreatedDateToNull() noexcept
{
    createdDate_.reset();
    dirtyFlag_[3] = true;
}

const std::string &ProvisioningHistory::getValueOfLastmodifiedbyId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lastmodifiedbyId_)
        return *lastmodifiedbyId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningHistory::getLastmodifiedbyId() const noexcept
{
    return lastmodifiedbyId_;
}
void ProvisioningHistory::setLastmodifiedbyId(const std::string &pLastmodifiedbyId) noexcept
{
    lastmodifiedbyId_ = std::make_shared<std::string>(pLastmodifiedbyId);
    dirtyFlag_[4] = true;
}
void ProvisioningHistory::setLastmodifiedbyId(std::string &&pLastmodifiedbyId) noexcept
{
    lastmodifiedbyId_ = std::make_shared<std::string>(std::move(pLastmodifiedbyId));
    dirtyFlag_[4] = true;
}
void ProvisioningHistory::setLastmodifiedbyIdToNull() noexcept
{
    lastmodifiedbyId_.reset();
    dirtyFlag_[4] = true;
}

const ::trantor::Date &ProvisioningHistory::getValueOfLastmodifiedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(lastmodifiedDate_)
        return *lastmodifiedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ProvisioningHistory::getLastmodifiedDate() const noexcept
{
    return lastmodifiedDate_;
}
void ProvisioningHistory::setLastmodifiedDate(const ::trantor::Date &pLastmodifiedDate) noexcept
{
    lastmodifiedDate_ = std::make_shared<::trantor::Date>(pLastmodifiedDate);
    dirtyFlag_[5] = true;
}
void ProvisioningHistory::setLastmodifiedDateToNull() noexcept
{
    lastmodifiedDate_.reset();
    dirtyFlag_[5] = true;
}

void ProvisioningHistory::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ProvisioningHistory::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "journal_entry_created",
        "createdby_id",
        "created_date",
        "lastmodifiedby_id",
        "lastmodified_date"
    };
    return inCols;
}

void ProvisioningHistory::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getJournalEntryCreated())
        {
            binder << getValueOfJournalEntryCreated();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCreatedbyId())
        {
            binder << getValueOfCreatedbyId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getCreatedDate())
        {
            binder << getValueOfCreatedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getLastmodifiedbyId())
        {
            binder << getValueOfLastmodifiedbyId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getLastmodifiedDate())
        {
            binder << getValueOfLastmodifiedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> ProvisioningHistory::updateColumns() const
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
    return ret;
}

void ProvisioningHistory::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getJournalEntryCreated())
        {
            binder << getValueOfJournalEntryCreated();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCreatedbyId())
        {
            binder << getValueOfCreatedbyId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getCreatedDate())
        {
            binder << getValueOfCreatedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getLastmodifiedbyId())
        {
            binder << getValueOfLastmodifiedbyId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getLastmodifiedDate())
        {
            binder << getValueOfLastmodifiedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
}
