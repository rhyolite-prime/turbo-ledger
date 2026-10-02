/**
 *  Group.cc
 *
 *  See Group.h for the hand-authored-subset note.
 *
 */

#include "Group.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlGroupDb;

const std::string Group::Cols::_id = "\"id\"";
const std::string Group::Cols::_external_id = "\"external_id\"";
const std::string Group::Cols::_status_enum = "\"status_enum\"";
const std::string Group::Cols::_activation_date = "\"activation_date\"";
const std::string Group::Cols::_office_id = "\"office_id\"";
const std::string Group::Cols::_staff_id = "\"staff_id\"";
const std::string Group::Cols::_parent_id = "\"parent_id\"";
const std::string Group::Cols::_level_id = "\"level_id\"";
const std::string Group::Cols::_display_name = "\"display_name\"";
const std::string Group::Cols::_hierarchy = "\"hierarchy\"";
const std::string Group::Cols::_closure_reason_cv_id = "\"closure_reason_cv_id\"";
const std::string Group::Cols::_closedon_date = "\"closedon_date\"";
const std::string Group::Cols::_activatedon_userid = "\"activatedon_userid\"";
const std::string Group::Cols::_submittedon_date = "\"submittedon_date\"";
const std::string Group::Cols::_submittedon_userid = "\"submittedon_userid\"";
const std::string Group::Cols::_closedon_userid = "\"closedon_userid\"";
const std::string Group::Cols::_account_no = "\"account_no\"";
const std::string Group::primaryKeyName = "id";
const bool Group::hasPrimaryKey = true;
const std::string Group::tableName = "\"groups\"";

const std::vector<typename Group::MetaData> Group::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"external_id","std::string","character varying",100,0,0,0},
{"status_enum","int32_t","integer",4,0,0,1},
{"activation_date","::trantor::Date","date",0,0,0,0},
{"office_id","std::string","uuid",0,0,0,1},
{"staff_id","std::string","uuid",0,0,0,1},
{"parent_id","std::string","uuid",0,0,0,1},
{"level_id","std::string","uuid",0,0,0,1},
{"display_name","std::string","character varying",100,0,0,1},
{"hierarchy","std::string","character varying",100,0,0,0},
{"closure_reason_cv_id","std::string","uuid",0,0,0,1},
{"closedon_date","::trantor::Date","date",0,0,0,0},
{"activatedon_userid","std::string","uuid",0,0,0,1},
{"submittedon_date","::trantor::Date","date",0,0,0,0},
{"submittedon_userid","std::string","uuid",0,0,0,1},
{"closedon_userid","std::string","uuid",0,0,0,1},
{"account_no","std::string","character varying",20,0,0,1}
};
const std::string &Group::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Group::Group(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["status_enum"].isNull())
        {
            statusEnum_=std::make_shared<int32_t>(r["status_enum"].as<int32_t>());
        }
        if(!r["activation_date"].isNull())
        {
            auto daysStr = r["activation_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["staff_id"].isNull())
        {
            staffId_=std::make_shared<std::string>(r["staff_id"].as<std::string>());
        }
        if(!r["parent_id"].isNull())
        {
            parentId_=std::make_shared<std::string>(r["parent_id"].as<std::string>());
        }
        if(!r["level_id"].isNull())
        {
            levelId_=std::make_shared<std::string>(r["level_id"].as<std::string>());
        }
        if(!r["display_name"].isNull())
        {
            displayName_=std::make_shared<std::string>(r["display_name"].as<std::string>());
        }
        if(!r["hierarchy"].isNull())
        {
            hierarchy_=std::make_shared<std::string>(r["hierarchy"].as<std::string>());
        }
        if(!r["closure_reason_cv_id"].isNull())
        {
            closureReasonCvId_=std::make_shared<std::string>(r["closure_reason_cv_id"].as<std::string>());
        }
        if(!r["closedon_date"].isNull())
        {
            auto daysStr = r["closedon_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["activatedon_userid"].isNull())
        {
            activatedonUserid_=std::make_shared<std::string>(r["activatedon_userid"].as<std::string>());
        }
        if(!r["submittedon_date"].isNull())
        {
            auto daysStr = r["submittedon_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["submittedon_userid"].isNull())
        {
            submittedonUserid_=std::make_shared<std::string>(r["submittedon_userid"].as<std::string>());
        }
        if(!r["closedon_userid"].isNull())
        {
            closedonUserid_=std::make_shared<std::string>(r["closedon_userid"].as<std::string>());
        }
        if(!r["account_no"].isNull())
        {
            accountNo_=std::make_shared<std::string>(r["account_no"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 17 > r.size())
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
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            statusEnum_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            staffId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            parentId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            levelId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            displayName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            hierarchy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            closureReasonCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            activatedonUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            submittedonUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            closedonUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            accountNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &Group::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getId() const noexcept
{
    return id_;
}
void Group::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Group::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Group::PrimaryKeyType & Group::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Group::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getExternalId() const noexcept
{
    return externalId_;
}
void Group::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[1] = true;
}
void Group::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[1] = true;
}
void Group::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[1] = true;
}

const int32_t &Group::getValueOfStatusEnum() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(statusEnum_)
        return *statusEnum_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Group::getStatusEnum() const noexcept
{
    return statusEnum_;
}
void Group::setStatusEnum(const int32_t &pStatusEnum) noexcept
{
    statusEnum_ = std::make_shared<int32_t>(pStatusEnum);
    dirtyFlag_[2] = true;
}

const ::trantor::Date &Group::getValueOfActivationDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(activationDate_)
        return *activationDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Group::getActivationDate() const noexcept
{
    return activationDate_;
}
void Group::setActivationDate(const ::trantor::Date &pActivationDate) noexcept
{
    activationDate_ = std::make_shared<::trantor::Date>(pActivationDate);
    dirtyFlag_[3] = true;
}
void Group::setActivationDateToNull() noexcept
{
    activationDate_.reset();
    dirtyFlag_[3] = true;
}

const std::string &Group::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getOfficeId() const noexcept
{
    return officeId_;
}
void Group::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[4] = true;
}
void Group::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[4] = true;
}

const std::string &Group::getValueOfStaffId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(staffId_)
        return *staffId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getStaffId() const noexcept
{
    return staffId_;
}
void Group::setStaffId(const std::string &pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(pStaffId);
    dirtyFlag_[5] = true;
}
void Group::setStaffId(std::string &&pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(std::move(pStaffId));
    dirtyFlag_[5] = true;
}

const std::string &Group::getValueOfParentId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(parentId_)
        return *parentId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getParentId() const noexcept
{
    return parentId_;
}
void Group::setParentId(const std::string &pParentId) noexcept
{
    parentId_ = std::make_shared<std::string>(pParentId);
    dirtyFlag_[6] = true;
}
void Group::setParentId(std::string &&pParentId) noexcept
{
    parentId_ = std::make_shared<std::string>(std::move(pParentId));
    dirtyFlag_[6] = true;
}

const std::string &Group::getValueOfLevelId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(levelId_)
        return *levelId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getLevelId() const noexcept
{
    return levelId_;
}
void Group::setLevelId(const std::string &pLevelId) noexcept
{
    levelId_ = std::make_shared<std::string>(pLevelId);
    dirtyFlag_[7] = true;
}
void Group::setLevelId(std::string &&pLevelId) noexcept
{
    levelId_ = std::make_shared<std::string>(std::move(pLevelId));
    dirtyFlag_[7] = true;
}

const std::string &Group::getValueOfDisplayName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(displayName_)
        return *displayName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getDisplayName() const noexcept
{
    return displayName_;
}
void Group::setDisplayName(const std::string &pDisplayName) noexcept
{
    displayName_ = std::make_shared<std::string>(pDisplayName);
    dirtyFlag_[8] = true;
}
void Group::setDisplayName(std::string &&pDisplayName) noexcept
{
    displayName_ = std::make_shared<std::string>(std::move(pDisplayName));
    dirtyFlag_[8] = true;
}

const std::string &Group::getValueOfHierarchy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(hierarchy_)
        return *hierarchy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getHierarchy() const noexcept
{
    return hierarchy_;
}
void Group::setHierarchy(const std::string &pHierarchy) noexcept
{
    hierarchy_ = std::make_shared<std::string>(pHierarchy);
    dirtyFlag_[9] = true;
}
void Group::setHierarchy(std::string &&pHierarchy) noexcept
{
    hierarchy_ = std::make_shared<std::string>(std::move(pHierarchy));
    dirtyFlag_[9] = true;
}
void Group::setHierarchyToNull() noexcept
{
    hierarchy_.reset();
    dirtyFlag_[9] = true;
}

const std::string &Group::getValueOfClosureReasonCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(closureReasonCvId_)
        return *closureReasonCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getClosureReasonCvId() const noexcept
{
    return closureReasonCvId_;
}
void Group::setClosureReasonCvId(const std::string &pClosureReasonCvId) noexcept
{
    closureReasonCvId_ = std::make_shared<std::string>(pClosureReasonCvId);
    dirtyFlag_[10] = true;
}
void Group::setClosureReasonCvId(std::string &&pClosureReasonCvId) noexcept
{
    closureReasonCvId_ = std::make_shared<std::string>(std::move(pClosureReasonCvId));
    dirtyFlag_[10] = true;
}

const ::trantor::Date &Group::getValueOfClosedonDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(closedonDate_)
        return *closedonDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Group::getClosedonDate() const noexcept
{
    return closedonDate_;
}
void Group::setClosedonDate(const ::trantor::Date &pClosedonDate) noexcept
{
    closedonDate_ = std::make_shared<::trantor::Date>(pClosedonDate);
    dirtyFlag_[11] = true;
}
void Group::setClosedonDateToNull() noexcept
{
    closedonDate_.reset();
    dirtyFlag_[11] = true;
}

const std::string &Group::getValueOfActivatedonUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(activatedonUserid_)
        return *activatedonUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getActivatedonUserid() const noexcept
{
    return activatedonUserid_;
}
void Group::setActivatedonUserid(const std::string &pActivatedonUserid) noexcept
{
    activatedonUserid_ = std::make_shared<std::string>(pActivatedonUserid);
    dirtyFlag_[12] = true;
}
void Group::setActivatedonUserid(std::string &&pActivatedonUserid) noexcept
{
    activatedonUserid_ = std::make_shared<std::string>(std::move(pActivatedonUserid));
    dirtyFlag_[12] = true;
}

const ::trantor::Date &Group::getValueOfSubmittedonDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedonDate_)
        return *submittedonDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Group::getSubmittedonDate() const noexcept
{
    return submittedonDate_;
}
void Group::setSubmittedonDate(const ::trantor::Date &pSubmittedonDate) noexcept
{
    submittedonDate_ = std::make_shared<::trantor::Date>(pSubmittedonDate);
    dirtyFlag_[13] = true;
}
void Group::setSubmittedonDateToNull() noexcept
{
    submittedonDate_.reset();
    dirtyFlag_[13] = true;
}

const std::string &Group::getValueOfSubmittedonUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(submittedonUserid_)
        return *submittedonUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getSubmittedonUserid() const noexcept
{
    return submittedonUserid_;
}
void Group::setSubmittedonUserid(const std::string &pSubmittedonUserid) noexcept
{
    submittedonUserid_ = std::make_shared<std::string>(pSubmittedonUserid);
    dirtyFlag_[14] = true;
}
void Group::setSubmittedonUserid(std::string &&pSubmittedonUserid) noexcept
{
    submittedonUserid_ = std::make_shared<std::string>(std::move(pSubmittedonUserid));
    dirtyFlag_[14] = true;
}

const std::string &Group::getValueOfClosedonUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(closedonUserid_)
        return *closedonUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getClosedonUserid() const noexcept
{
    return closedonUserid_;
}
void Group::setClosedonUserid(const std::string &pClosedonUserid) noexcept
{
    closedonUserid_ = std::make_shared<std::string>(pClosedonUserid);
    dirtyFlag_[15] = true;
}
void Group::setClosedonUserid(std::string &&pClosedonUserid) noexcept
{
    closedonUserid_ = std::make_shared<std::string>(std::move(pClosedonUserid));
    dirtyFlag_[15] = true;
}

const std::string &Group::getValueOfAccountNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountNo_)
        return *accountNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Group::getAccountNo() const noexcept
{
    return accountNo_;
}
void Group::setAccountNo(const std::string &pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(pAccountNo);
    dirtyFlag_[16] = true;
}
void Group::setAccountNo(std::string &&pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(std::move(pAccountNo));
    dirtyFlag_[16] = true;
}

void Group::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Group::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "external_id",
        "status_enum",
        "activation_date",
        "office_id",
        "staff_id",
        "parent_id",
        "level_id",
        "display_name",
        "hierarchy",
        "closure_reason_cv_id",
        "closedon_date",
        "activatedon_userid",
        "submittedon_date",
        "submittedon_userid",
        "closedon_userid",
        "account_no"
    };
    return inCols;
}

void Group::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getStatusEnum())
        {
            binder << getValueOfStatusEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getActivationDate())
        {
            binder << getValueOfActivationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getParentId())
        {
            binder << getValueOfParentId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getLevelId())
        {
            binder << getValueOfLevelId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getDisplayName())
        {
            binder << getValueOfDisplayName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getHierarchy())
        {
            binder << getValueOfHierarchy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getClosureReasonCvId())
        {
            binder << getValueOfClosureReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getClosedonDate())
        {
            binder << getValueOfClosedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getActivatedonUserid())
        {
            binder << getValueOfActivatedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getSubmittedonDate())
        {
            binder << getValueOfSubmittedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getSubmittedonUserid())
        {
            binder << getValueOfSubmittedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getClosedonUserid())
        {
            binder << getValueOfClosedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Group::updateColumns() const
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
    return ret;
}

void Group::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getStatusEnum())
        {
            binder << getValueOfStatusEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getActivationDate())
        {
            binder << getValueOfActivationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
    {
        if(getParentId())
        {
            binder << getValueOfParentId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getLevelId())
        {
            binder << getValueOfLevelId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getDisplayName())
        {
            binder << getValueOfDisplayName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getHierarchy())
        {
            binder << getValueOfHierarchy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getClosureReasonCvId())
        {
            binder << getValueOfClosureReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getClosedonDate())
        {
            binder << getValueOfClosedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getActivatedonUserid())
        {
            binder << getValueOfActivatedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getSubmittedonDate())
        {
            binder << getValueOfSubmittedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getSubmittedonUserid())
        {
            binder << getValueOfSubmittedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getClosedonUserid())
        {
            binder << getValueOfClosedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
}
