/**
 *
 *  Staff.cc
 *
 *  See Staff.h for the hand-authored-subset note.
 *
 */

#include "Staff.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlOrganizationDb;

const std::string Staff::Cols::_id = "\"id\"";
const std::string Staff::Cols::_office_id = "\"office_id\"";
const std::string Staff::Cols::_firstname = "\"firstname\"";
const std::string Staff::Cols::_lastname = "\"lastname\"";
const std::string Staff::Cols::_display_name = "\"display_name\"";
const std::string Staff::Cols::_external_id = "\"external_id\"";
const std::string Staff::Cols::_mobile_no = "\"mobile_no\"";
const std::string Staff::Cols::_is_loan_officer = "\"is_loan_officer\"";
const std::string Staff::Cols::_is_active = "\"is_active\"";
const std::string Staff::Cols::_joining_date = "\"joining_date\"";
const std::string Staff::Cols::_created_at = "\"created_at\"";
const std::string Staff::Cols::_modified_at = "\"modified_at\"";
const std::string Staff::primaryKeyName = "id";
const bool Staff::hasPrimaryKey = true;
const std::string Staff::tableName = "\"staff\"";

const std::vector<typename Staff::MetaData> Staff::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"office_id","std::string","uuid",0,0,0,1},
{"firstname","std::string","character varying",100,0,0,1},
{"lastname","std::string","character varying",100,0,0,1},
{"display_name","std::string","character varying",200,0,0,1},
{"external_id","std::string","character varying",100,0,0,0},
{"mobile_no","std::string","character varying",40,0,0,0},
{"is_loan_officer","bool","boolean",1,0,0,1},
{"is_active","bool","boolean",1,0,0,1},
{"joining_date","::trantor::Date","date",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"modified_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &Staff::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Staff::Staff(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["firstname"].isNull())
        {
            firstname_=std::make_shared<std::string>(r["firstname"].as<std::string>());
        }
        if(!r["lastname"].isNull())
        {
            lastname_=std::make_shared<std::string>(r["lastname"].as<std::string>());
        }
        if(!r["display_name"].isNull())
        {
            displayName_=std::make_shared<std::string>(r["display_name"].as<std::string>());
        }
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["mobile_no"].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r["mobile_no"].as<std::string>());
        }
        if(!r["is_loan_officer"].isNull())
        {
            isLoanOfficer_=std::make_shared<bool>(r["is_loan_officer"].as<bool>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
        if(!r["joining_date"].isNull())
        {
            auto daysStr = r["joining_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            joiningDate_=std::make_shared<::trantor::Date>(t*1000000);
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
        if(!r["modified_at"].isNull())
        {
            auto timeStr = r["modified_at"].as<std::string>();
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
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
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
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            firstname_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            lastname_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            displayName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            isLoanOfficer_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            joiningDate_=std::make_shared<::trantor::Date>(t*1000000);
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
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}

const std::string &Staff::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Staff::getId() const noexcept
{
    return id_;
}
void Staff::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Staff::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Staff::PrimaryKeyType & Staff::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Staff::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Staff::getOfficeId() const noexcept
{
    return officeId_;
}
void Staff::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[1] = true;
}
void Staff::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[1] = true;
}

const std::string &Staff::getValueOfFirstname() const noexcept
{
    static const std::string defaultValue = std::string();
    if(firstname_)
        return *firstname_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Staff::getFirstname() const noexcept
{
    return firstname_;
}
void Staff::setFirstname(const std::string &pFirstname) noexcept
{
    firstname_ = std::make_shared<std::string>(pFirstname);
    dirtyFlag_[2] = true;
}
void Staff::setFirstname(std::string &&pFirstname) noexcept
{
    firstname_ = std::make_shared<std::string>(std::move(pFirstname));
    dirtyFlag_[2] = true;
}

const std::string &Staff::getValueOfLastname() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lastname_)
        return *lastname_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Staff::getLastname() const noexcept
{
    return lastname_;
}
void Staff::setLastname(const std::string &pLastname) noexcept
{
    lastname_ = std::make_shared<std::string>(pLastname);
    dirtyFlag_[3] = true;
}
void Staff::setLastname(std::string &&pLastname) noexcept
{
    lastname_ = std::make_shared<std::string>(std::move(pLastname));
    dirtyFlag_[3] = true;
}

const std::string &Staff::getValueOfDisplayName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(displayName_)
        return *displayName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Staff::getDisplayName() const noexcept
{
    return displayName_;
}

const std::string &Staff::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Staff::getExternalId() const noexcept
{
    return externalId_;
}
void Staff::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[5] = true;
}
void Staff::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[5] = true;
}
void Staff::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[5] = true;
}

const std::string &Staff::getValueOfMobileNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mobileNo_)
        return *mobileNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Staff::getMobileNo() const noexcept
{
    return mobileNo_;
}
void Staff::setMobileNo(const std::string &pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(pMobileNo);
    dirtyFlag_[6] = true;
}
void Staff::setMobileNo(std::string &&pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(std::move(pMobileNo));
    dirtyFlag_[6] = true;
}
void Staff::setMobileNoToNull() noexcept
{
    mobileNo_.reset();
    dirtyFlag_[6] = true;
}

const bool &Staff::getValueOfIsLoanOfficer() const noexcept
{
    static const bool defaultValue = bool();
    if(isLoanOfficer_)
        return *isLoanOfficer_;
    return defaultValue;
}
const std::shared_ptr<bool> &Staff::getIsLoanOfficer() const noexcept
{
    return isLoanOfficer_;
}
void Staff::setIsLoanOfficer(const bool &pIsLoanOfficer) noexcept
{
    isLoanOfficer_ = std::make_shared<bool>(pIsLoanOfficer);
    dirtyFlag_[7] = true;
}

const bool &Staff::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &Staff::getIsActive() const noexcept
{
    return isActive_;
}
void Staff::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[8] = true;
}

const ::trantor::Date &Staff::getValueOfJoiningDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(joiningDate_)
        return *joiningDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Staff::getJoiningDate() const noexcept
{
    return joiningDate_;
}
void Staff::setJoiningDate(const ::trantor::Date &pJoiningDate) noexcept
{
    joiningDate_ = std::make_shared<::trantor::Date>(pJoiningDate.roundDay());
    dirtyFlag_[9] = true;
}
void Staff::setJoiningDateToNull() noexcept
{
    joiningDate_.reset();
    dirtyFlag_[9] = true;
}

const ::trantor::Date &Staff::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Staff::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Staff::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[10] = true;
}

const ::trantor::Date &Staff::getValueOfModifiedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(modifiedAt_)
        return *modifiedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Staff::getModifiedAt() const noexcept
{
    return modifiedAt_;
}
void Staff::setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept
{
    modifiedAt_ = std::make_shared<::trantor::Date>(pModifiedAt);
    dirtyFlag_[11] = true;
}

void Staff::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Staff::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "office_id",
        "firstname",
        "lastname",
        "external_id",
        "mobile_no",
        "is_loan_officer",
        "is_active",
        "joining_date",
        "created_at",
        "modified_at"
    };
    return inCols;
}

void Staff::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getFirstname())
        {
            binder << getValueOfFirstname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getLastname())
        {
            binder << getValueOfLastname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getIsLoanOfficer())
        {
            binder << getValueOfIsLoanOfficer();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getJoiningDate())
        {
            binder << getValueOfJoiningDate();
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
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Staff::updateColumns() const
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

void Staff::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getFirstname())
        {
            binder << getValueOfFirstname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getLastname())
        {
            binder << getValueOfLastname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getIsLoanOfficer())
        {
            binder << getValueOfIsLoanOfficer();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsActive())
        {
            binder << getValueOfIsActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getJoiningDate())
        {
            binder << getValueOfJoiningDate();
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
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}

