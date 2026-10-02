/**
 *  ClientFamilyMember.cc
 *
 *  See ClientFamilyMember.h for the hand-authored-subset note.
 *
 */

#include "ClientFamilyMember.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlCustomerDb;

const std::string ClientFamilyMember::Cols::_id = "\"id\"";
const std::string ClientFamilyMember::Cols::_client_id = "\"client_id\"";
const std::string ClientFamilyMember::Cols::_firstname = "\"firstname\"";
const std::string ClientFamilyMember::Cols::_middlename = "\"middlename\"";
const std::string ClientFamilyMember::Cols::_lastname = "\"lastname\"";
const std::string ClientFamilyMember::Cols::_qualification = "\"qualification\"";
const std::string ClientFamilyMember::Cols::_mobile_number = "\"mobile_number\"";
const std::string ClientFamilyMember::Cols::_age = "\"age\"";
const std::string ClientFamilyMember::Cols::_is_dependent = "\"is_dependent\"";
const std::string ClientFamilyMember::Cols::_relationship_cv_id = "\"relationship_cv_id\"";
const std::string ClientFamilyMember::Cols::_marital_status_cv_id = "\"marital_status_cv_id\"";
const std::string ClientFamilyMember::Cols::_gender_cv_id = "\"gender_cv_id\"";
const std::string ClientFamilyMember::Cols::_date_of_birth = "\"date_of_birth\"";
const std::string ClientFamilyMember::Cols::_profession_cv_id = "\"profession_cv_id\"";
const std::string ClientFamilyMember::Cols::_created_by = "\"created_by\"";
const std::string ClientFamilyMember::Cols::_created_at = "\"created_at\"";
const std::string ClientFamilyMember::Cols::_updated_by = "\"updated_by\"";
const std::string ClientFamilyMember::Cols::_updated_at = "\"updated_at\"";
const std::string ClientFamilyMember::primaryKeyName = "id";
const bool ClientFamilyMember::hasPrimaryKey = true;
const std::string ClientFamilyMember::tableName = "\"client_family_members\"";

const std::vector<typename ClientFamilyMember::MetaData> ClientFamilyMember::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"client_id","std::string","uuid",0,0,0,1},
{"firstname","std::string","character varying",80,0,0,1},
{"middlename","std::string","character varying",80,0,0,0},
{"lastname","std::string","character varying",80,0,0,1},
{"qualification","std::string","character varying",100,0,0,0},
{"mobile_number","std::string","character varying",20,0,0,0},
{"age","int32_t","integer",4,0,0,0},
{"is_dependent","bool","boolean",1,0,0,1},
{"relationship_cv_id","std::string","uuid",0,0,0,0},
{"marital_status_cv_id","std::string","uuid",0,0,0,0},
{"gender_cv_id","std::string","uuid",0,0,0,0},
{"date_of_birth","::trantor::Date","date",0,0,0,0},
{"profession_cv_id","std::string","uuid",0,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,0},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,0}
};
const std::string &ClientFamilyMember::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ClientFamilyMember::ClientFamilyMember(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["firstname"].isNull())
        {
            firstname_=std::make_shared<std::string>(r["firstname"].as<std::string>());
        }
        if(!r["middlename"].isNull())
        {
            middlename_=std::make_shared<std::string>(r["middlename"].as<std::string>());
        }
        if(!r["lastname"].isNull())
        {
            lastname_=std::make_shared<std::string>(r["lastname"].as<std::string>());
        }
        if(!r["qualification"].isNull())
        {
            qualification_=std::make_shared<std::string>(r["qualification"].as<std::string>());
        }
        if(!r["mobile_number"].isNull())
        {
            mobileNumber_=std::make_shared<std::string>(r["mobile_number"].as<std::string>());
        }
        if(!r["age"].isNull())
        {
            age_=std::make_shared<int32_t>(r["age"].as<int32_t>());
        }
        if(!r["is_dependent"].isNull())
        {
            isDependent_=std::make_shared<bool>(r["is_dependent"].as<bool>());
        }
        if(!r["relationship_cv_id"].isNull())
        {
            relationshipCvId_=std::make_shared<std::string>(r["relationship_cv_id"].as<std::string>());
        }
        if(!r["marital_status_cv_id"].isNull())
        {
            maritalStatusCvId_=std::make_shared<std::string>(r["marital_status_cv_id"].as<std::string>());
        }
        if(!r["gender_cv_id"].isNull())
        {
            genderCvId_=std::make_shared<std::string>(r["gender_cv_id"].as<std::string>());
        }
        if(!r["date_of_birth"].isNull())
        {
            auto daysStr = r["date_of_birth"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dateOfBirth_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["profession_cv_id"].isNull())
        {
            professionCvId_=std::make_shared<std::string>(r["profession_cv_id"].as<std::string>());
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
        if(offset + 18 > r.size())
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
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            firstname_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            middlename_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            lastname_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            qualification_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            mobileNumber_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            age_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            isDependent_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            relationshipCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            maritalStatusCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            genderCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dateOfBirth_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            professionCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
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
        index = offset + 16;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 17;
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
const std::string &ClientFamilyMember::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getId() const noexcept
{
    return id_;
}
void ClientFamilyMember::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ClientFamilyMember::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ClientFamilyMember::PrimaryKeyType & ClientFamilyMember::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ClientFamilyMember::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getClientId() const noexcept
{
    return clientId_;
}
void ClientFamilyMember::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[1] = true;
}
void ClientFamilyMember::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[1] = true;
}

const std::string &ClientFamilyMember::getValueOfFirstname() const noexcept
{
    static const std::string defaultValue = std::string();
    if(firstname_)
        return *firstname_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getFirstname() const noexcept
{
    return firstname_;
}
void ClientFamilyMember::setFirstname(const std::string &pFirstname) noexcept
{
    firstname_ = std::make_shared<std::string>(pFirstname);
    dirtyFlag_[2] = true;
}
void ClientFamilyMember::setFirstname(std::string &&pFirstname) noexcept
{
    firstname_ = std::make_shared<std::string>(std::move(pFirstname));
    dirtyFlag_[2] = true;
}

const std::string &ClientFamilyMember::getValueOfMiddlename() const noexcept
{
    static const std::string defaultValue = std::string();
    if(middlename_)
        return *middlename_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getMiddlename() const noexcept
{
    return middlename_;
}
void ClientFamilyMember::setMiddlename(const std::string &pMiddlename) noexcept
{
    middlename_ = std::make_shared<std::string>(pMiddlename);
    dirtyFlag_[3] = true;
}
void ClientFamilyMember::setMiddlename(std::string &&pMiddlename) noexcept
{
    middlename_ = std::make_shared<std::string>(std::move(pMiddlename));
    dirtyFlag_[3] = true;
}
void ClientFamilyMember::setMiddlenameToNull() noexcept
{
    middlename_.reset();
    dirtyFlag_[3] = true;
}

const std::string &ClientFamilyMember::getValueOfLastname() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lastname_)
        return *lastname_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getLastname() const noexcept
{
    return lastname_;
}
void ClientFamilyMember::setLastname(const std::string &pLastname) noexcept
{
    lastname_ = std::make_shared<std::string>(pLastname);
    dirtyFlag_[4] = true;
}
void ClientFamilyMember::setLastname(std::string &&pLastname) noexcept
{
    lastname_ = std::make_shared<std::string>(std::move(pLastname));
    dirtyFlag_[4] = true;
}

const std::string &ClientFamilyMember::getValueOfQualification() const noexcept
{
    static const std::string defaultValue = std::string();
    if(qualification_)
        return *qualification_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getQualification() const noexcept
{
    return qualification_;
}
void ClientFamilyMember::setQualification(const std::string &pQualification) noexcept
{
    qualification_ = std::make_shared<std::string>(pQualification);
    dirtyFlag_[5] = true;
}
void ClientFamilyMember::setQualification(std::string &&pQualification) noexcept
{
    qualification_ = std::make_shared<std::string>(std::move(pQualification));
    dirtyFlag_[5] = true;
}
void ClientFamilyMember::setQualificationToNull() noexcept
{
    qualification_.reset();
    dirtyFlag_[5] = true;
}

const std::string &ClientFamilyMember::getValueOfMobileNumber() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mobileNumber_)
        return *mobileNumber_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getMobileNumber() const noexcept
{
    return mobileNumber_;
}
void ClientFamilyMember::setMobileNumber(const std::string &pMobileNumber) noexcept
{
    mobileNumber_ = std::make_shared<std::string>(pMobileNumber);
    dirtyFlag_[6] = true;
}
void ClientFamilyMember::setMobileNumber(std::string &&pMobileNumber) noexcept
{
    mobileNumber_ = std::make_shared<std::string>(std::move(pMobileNumber));
    dirtyFlag_[6] = true;
}
void ClientFamilyMember::setMobileNumberToNull() noexcept
{
    mobileNumber_.reset();
    dirtyFlag_[6] = true;
}

const int32_t &ClientFamilyMember::getValueOfAge() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(age_)
        return *age_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ClientFamilyMember::getAge() const noexcept
{
    return age_;
}
void ClientFamilyMember::setAge(const int32_t &pAge) noexcept
{
    age_ = std::make_shared<int32_t>(pAge);
    dirtyFlag_[7] = true;
}
void ClientFamilyMember::setAgeToNull() noexcept
{
    age_.reset();
    dirtyFlag_[7] = true;
}

const bool &ClientFamilyMember::getValueOfIsDependent() const noexcept
{
    static const bool defaultValue = bool();
    if(isDependent_)
        return *isDependent_;
    return defaultValue;
}
const std::shared_ptr<bool> &ClientFamilyMember::getIsDependent() const noexcept
{
    return isDependent_;
}
void ClientFamilyMember::setIsDependent(const bool &pIsDependent) noexcept
{
    isDependent_ = std::make_shared<bool>(pIsDependent);
    dirtyFlag_[8] = true;
}

const std::string &ClientFamilyMember::getValueOfRelationshipCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(relationshipCvId_)
        return *relationshipCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getRelationshipCvId() const noexcept
{
    return relationshipCvId_;
}
void ClientFamilyMember::setRelationshipCvId(const std::string &pRelationshipCvId) noexcept
{
    relationshipCvId_ = std::make_shared<std::string>(pRelationshipCvId);
    dirtyFlag_[9] = true;
}
void ClientFamilyMember::setRelationshipCvId(std::string &&pRelationshipCvId) noexcept
{
    relationshipCvId_ = std::make_shared<std::string>(std::move(pRelationshipCvId));
    dirtyFlag_[9] = true;
}
void ClientFamilyMember::setRelationshipCvIdToNull() noexcept
{
    relationshipCvId_.reset();
    dirtyFlag_[9] = true;
}

const std::string &ClientFamilyMember::getValueOfMaritalStatusCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(maritalStatusCvId_)
        return *maritalStatusCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getMaritalStatusCvId() const noexcept
{
    return maritalStatusCvId_;
}
void ClientFamilyMember::setMaritalStatusCvId(const std::string &pMaritalStatusCvId) noexcept
{
    maritalStatusCvId_ = std::make_shared<std::string>(pMaritalStatusCvId);
    dirtyFlag_[10] = true;
}
void ClientFamilyMember::setMaritalStatusCvId(std::string &&pMaritalStatusCvId) noexcept
{
    maritalStatusCvId_ = std::make_shared<std::string>(std::move(pMaritalStatusCvId));
    dirtyFlag_[10] = true;
}
void ClientFamilyMember::setMaritalStatusCvIdToNull() noexcept
{
    maritalStatusCvId_.reset();
    dirtyFlag_[10] = true;
}

const std::string &ClientFamilyMember::getValueOfGenderCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(genderCvId_)
        return *genderCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getGenderCvId() const noexcept
{
    return genderCvId_;
}
void ClientFamilyMember::setGenderCvId(const std::string &pGenderCvId) noexcept
{
    genderCvId_ = std::make_shared<std::string>(pGenderCvId);
    dirtyFlag_[11] = true;
}
void ClientFamilyMember::setGenderCvId(std::string &&pGenderCvId) noexcept
{
    genderCvId_ = std::make_shared<std::string>(std::move(pGenderCvId));
    dirtyFlag_[11] = true;
}
void ClientFamilyMember::setGenderCvIdToNull() noexcept
{
    genderCvId_.reset();
    dirtyFlag_[11] = true;
}

const ::trantor::Date &ClientFamilyMember::getValueOfDateOfBirth() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dateOfBirth_)
        return *dateOfBirth_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientFamilyMember::getDateOfBirth() const noexcept
{
    return dateOfBirth_;
}
void ClientFamilyMember::setDateOfBirth(const ::trantor::Date &pDateOfBirth) noexcept
{
    dateOfBirth_ = std::make_shared<::trantor::Date>(pDateOfBirth);
    dirtyFlag_[12] = true;
}
void ClientFamilyMember::setDateOfBirthToNull() noexcept
{
    dateOfBirth_.reset();
    dirtyFlag_[12] = true;
}

const std::string &ClientFamilyMember::getValueOfProfessionCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(professionCvId_)
        return *professionCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getProfessionCvId() const noexcept
{
    return professionCvId_;
}
void ClientFamilyMember::setProfessionCvId(const std::string &pProfessionCvId) noexcept
{
    professionCvId_ = std::make_shared<std::string>(pProfessionCvId);
    dirtyFlag_[13] = true;
}
void ClientFamilyMember::setProfessionCvId(std::string &&pProfessionCvId) noexcept
{
    professionCvId_ = std::make_shared<std::string>(std::move(pProfessionCvId));
    dirtyFlag_[13] = true;
}
void ClientFamilyMember::setProfessionCvIdToNull() noexcept
{
    professionCvId_.reset();
    dirtyFlag_[13] = true;
}

const std::string &ClientFamilyMember::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getCreatedBy() const noexcept
{
    return createdBy_;
}
void ClientFamilyMember::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[14] = true;
}
void ClientFamilyMember::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[14] = true;
}
void ClientFamilyMember::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[14] = true;
}

const ::trantor::Date &ClientFamilyMember::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientFamilyMember::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ClientFamilyMember::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[15] = true;
}
void ClientFamilyMember::setCreatedAtToNull() noexcept
{
    createdAt_.reset();
    dirtyFlag_[15] = true;
}

const std::string &ClientFamilyMember::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientFamilyMember::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void ClientFamilyMember::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[16] = true;
}
void ClientFamilyMember::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[16] = true;
}
void ClientFamilyMember::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[16] = true;
}

const ::trantor::Date &ClientFamilyMember::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientFamilyMember::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void ClientFamilyMember::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[17] = true;
}
void ClientFamilyMember::setUpdatedAtToNull() noexcept
{
    updatedAt_.reset();
    dirtyFlag_[17] = true;
}

void ClientFamilyMember::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ClientFamilyMember::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "client_id",
        "firstname",
        "middlename",
        "lastname",
        "qualification",
        "mobile_number",
        "age",
        "is_dependent",
        "relationship_cv_id",
        "marital_status_cv_id",
        "gender_cv_id",
        "date_of_birth",
        "profession_cv_id",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void ClientFamilyMember::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getClientId())
        {
            binder << getValueOfClientId();
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
        if(getMiddlename())
        {
            binder << getValueOfMiddlename();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
        if(getQualification())
        {
            binder << getValueOfQualification();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getAge())
        {
            binder << getValueOfAge();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsDependent())
        {
            binder << getValueOfIsDependent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getRelationshipCvId())
        {
            binder << getValueOfRelationshipCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getMaritalStatusCvId())
        {
            binder << getValueOfMaritalStatusCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getGenderCvId())
        {
            binder << getValueOfGenderCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getDateOfBirth())
        {
            binder << getValueOfDateOfBirth();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getProfessionCvId())
        {
            binder << getValueOfProfessionCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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

const std::vector<std::string> ClientFamilyMember::updateColumns() const
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
    return ret;
}

void ClientFamilyMember::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getClientId())
        {
            binder << getValueOfClientId();
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
        if(getMiddlename())
        {
            binder << getValueOfMiddlename();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
        if(getQualification())
        {
            binder << getValueOfQualification();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getAge())
        {
            binder << getValueOfAge();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getIsDependent())
        {
            binder << getValueOfIsDependent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getRelationshipCvId())
        {
            binder << getValueOfRelationshipCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getMaritalStatusCvId())
        {
            binder << getValueOfMaritalStatusCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getGenderCvId())
        {
            binder << getValueOfGenderCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getDateOfBirth())
        {
            binder << getValueOfDateOfBirth();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getProfessionCvId())
        {
            binder << getValueOfProfessionCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
    if(dirtyFlag_[16])
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
    if(dirtyFlag_[17])
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
