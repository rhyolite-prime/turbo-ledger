/**
 *
 *  ProvisioningEntry.cc
 *
 *  See ProvisioningEntry.h for the hand-authored-subset note.
 *
 */

#include "ProvisioningEntry.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlAccounting;

const std::string ProvisioningEntry::Cols::_id = "\"id\"";
const std::string ProvisioningEntry::Cols::_created_date = "\"created_date\"";
const std::string ProvisioningEntry::Cols::_comments = "\"comments\"";
const std::string ProvisioningEntry::Cols::_journal_entry_created = "\"journal_entry_created\"";
const std::string ProvisioningEntry::Cols::_created_by = "\"created_by\"";
const std::string ProvisioningEntry::Cols::_created_at = "\"created_at\"";
const std::string ProvisioningEntry::Cols::_updated_at = "\"updated_at\"";
const std::string ProvisioningEntry::primaryKeyName = "id";
const bool ProvisioningEntry::hasPrimaryKey = true;
const std::string ProvisioningEntry::tableName = "\"provisioning_entries\"";

const std::vector<typename ProvisioningEntry::MetaData> ProvisioningEntry::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"created_date","::trantor::Date","date",0,0,0,1},
{"comments","std::string","character varying",500,0,0,0},
{"journal_entry_created","bool","boolean",1,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ProvisioningEntry::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ProvisioningEntry::ProvisioningEntry(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
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
        if(!r["comments"].isNull())
        {
            comments_=std::make_shared<std::string>(r["comments"].as<std::string>());
        }
        if(!r["journal_entry_created"].isNull())
        {
            journalEntryCreated_=std::make_shared<bool>(r["journal_entry_created"].as<bool>());
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
        if(offset + 7 > r.size())
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
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            createdDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            comments_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            journalEntryCreated_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
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
        index = offset + 6;
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
const std::string &ProvisioningEntry::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntry::getId() const noexcept
{
    return id_;
}
void ProvisioningEntry::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ProvisioningEntry::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ProvisioningEntry::PrimaryKeyType & ProvisioningEntry::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const ::trantor::Date &ProvisioningEntry::getValueOfCreatedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdDate_)
        return *createdDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ProvisioningEntry::getCreatedDate() const noexcept
{
    return createdDate_;
}
void ProvisioningEntry::setCreatedDate(const ::trantor::Date &pCreatedDate) noexcept
{
    createdDate_ = std::make_shared<::trantor::Date>(pCreatedDate);
    dirtyFlag_[1] = true;
}

const std::string &ProvisioningEntry::getValueOfComments() const noexcept
{
    static const std::string defaultValue = std::string();
    if(comments_)
        return *comments_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntry::getComments() const noexcept
{
    return comments_;
}
void ProvisioningEntry::setComments(const std::string &pComments) noexcept
{
    comments_ = std::make_shared<std::string>(pComments);
    dirtyFlag_[2] = true;
}
void ProvisioningEntry::setComments(std::string &&pComments) noexcept
{
    comments_ = std::make_shared<std::string>(std::move(pComments));
    dirtyFlag_[2] = true;
}
void ProvisioningEntry::setCommentsToNull() noexcept
{
    comments_.reset();
    dirtyFlag_[2] = true;
}

const bool &ProvisioningEntry::getValueOfJournalEntryCreated() const noexcept
{
    static const bool defaultValue = bool();
    if(journalEntryCreated_)
        return *journalEntryCreated_;
    return defaultValue;
}
const std::shared_ptr<bool> &ProvisioningEntry::getJournalEntryCreated() const noexcept
{
    return journalEntryCreated_;
}
void ProvisioningEntry::setJournalEntryCreated(const bool &pJournalEntryCreated) noexcept
{
    journalEntryCreated_ = std::make_shared<bool>(pJournalEntryCreated);
    dirtyFlag_[3] = true;
}

const std::string &ProvisioningEntry::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningEntry::getCreatedBy() const noexcept
{
    return createdBy_;
}
void ProvisioningEntry::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[4] = true;
}
void ProvisioningEntry::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[4] = true;
}
void ProvisioningEntry::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[4] = true;
}

const ::trantor::Date &ProvisioningEntry::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ProvisioningEntry::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ProvisioningEntry::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

const ::trantor::Date &ProvisioningEntry::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ProvisioningEntry::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void ProvisioningEntry::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[6] = true;
}

void ProvisioningEntry::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ProvisioningEntry::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "created_date",
        "comments",
        "journal_entry_created",
        "created_by",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void ProvisioningEntry::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCreatedDate())
        {
            binder << getValueOfCreatedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getComments())
        {
            binder << getValueOfComments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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

const std::vector<std::string> ProvisioningEntry::updateColumns() const
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
    return ret;
}

void ProvisioningEntry::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCreatedDate())
        {
            binder << getValueOfCreatedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getComments())
        {
            binder << getValueOfComments();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
