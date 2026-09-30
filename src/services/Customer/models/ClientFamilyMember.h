/**
 *  ClientFamilyMember.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<ClientFamilyMember> usage actually needs
 *  (row-mapping + CRUD via Mapper/CoroMapper). The Json::Value constructors,
 *  updateByJson/updateByMasqueradedJson, validateJsonFor.../validJsonOfField
 *  and toJson/toString/toMasqueradedJson methods that a live
 *  `drogon_ctl create_model` run would also emit are intentionally omitted
 *  here since nothing in this codebase calls them; regenerate with
 *  `drogon_ctl create_model` against a live DB with this table if those are
 *  ever needed.
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace TlCustomerDb
{

class ClientFamilyMember
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _client_id;
        static const std::string _firstname;
        static const std::string _middlename;
        static const std::string _lastname;
        static const std::string _qualification;
        static const std::string _mobile_number;
        static const std::string _age;
        static const std::string _is_dependent;
        static const std::string _relationship_cv_id;
        static const std::string _marital_status_cv_id;
        static const std::string _gender_cv_id;
        static const std::string _date_of_birth;
        static const std::string _profession_cv_id;
        static const std::string _created_by;
        static const std::string _created_at;
        static const std::string _updated_by;
        static const std::string _updated_at;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit ClientFamilyMember(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    ClientFamilyMember() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column client_id  */
    const std::string &getValueOfClientId() const noexcept;
    const std::shared_ptr<std::string> &getClientId() const noexcept;
    void setClientId(const std::string &pClientId) noexcept;
    void setClientId(std::string &&pClientId) noexcept;

    /**  For column firstname  */
    const std::string &getValueOfFirstname() const noexcept;
    const std::shared_ptr<std::string> &getFirstname() const noexcept;
    void setFirstname(const std::string &pFirstname) noexcept;
    void setFirstname(std::string &&pFirstname) noexcept;

    /**  For column middlename  */
    const std::string &getValueOfMiddlename() const noexcept;
    const std::shared_ptr<std::string> &getMiddlename() const noexcept;
    void setMiddlename(const std::string &pMiddlename) noexcept;
    void setMiddlename(std::string &&pMiddlename) noexcept;
    void setMiddlenameToNull() noexcept;

    /**  For column lastname  */
    const std::string &getValueOfLastname() const noexcept;
    const std::shared_ptr<std::string> &getLastname() const noexcept;
    void setLastname(const std::string &pLastname) noexcept;
    void setLastname(std::string &&pLastname) noexcept;

    /**  For column qualification  */
    const std::string &getValueOfQualification() const noexcept;
    const std::shared_ptr<std::string> &getQualification() const noexcept;
    void setQualification(const std::string &pQualification) noexcept;
    void setQualification(std::string &&pQualification) noexcept;
    void setQualificationToNull() noexcept;

    /**  For column mobile_number  */
    const std::string &getValueOfMobileNumber() const noexcept;
    const std::shared_ptr<std::string> &getMobileNumber() const noexcept;
    void setMobileNumber(const std::string &pMobileNumber) noexcept;
    void setMobileNumber(std::string &&pMobileNumber) noexcept;
    void setMobileNumberToNull() noexcept;

    /**  For column age  */
    const int32_t &getValueOfAge() const noexcept;
    const std::shared_ptr<int32_t> &getAge() const noexcept;
    void setAge(const int32_t &pAge) noexcept;
    void setAgeToNull() noexcept;

    /**  For column is_dependent  */
    const bool &getValueOfIsDependent() const noexcept;
    const std::shared_ptr<bool> &getIsDependent() const noexcept;
    void setIsDependent(const bool &pIsDependent) noexcept;

    /**  For column relationship_cv_id  */
    const std::string &getValueOfRelationshipCvId() const noexcept;
    const std::shared_ptr<std::string> &getRelationshipCvId() const noexcept;
    void setRelationshipCvId(const std::string &pRelationshipCvId) noexcept;
    void setRelationshipCvId(std::string &&pRelationshipCvId) noexcept;
    void setRelationshipCvIdToNull() noexcept;

    /**  For column marital_status_cv_id  */
    const std::string &getValueOfMaritalStatusCvId() const noexcept;
    const std::shared_ptr<std::string> &getMaritalStatusCvId() const noexcept;
    void setMaritalStatusCvId(const std::string &pMaritalStatusCvId) noexcept;
    void setMaritalStatusCvId(std::string &&pMaritalStatusCvId) noexcept;
    void setMaritalStatusCvIdToNull() noexcept;

    /**  For column gender_cv_id  */
    const std::string &getValueOfGenderCvId() const noexcept;
    const std::shared_ptr<std::string> &getGenderCvId() const noexcept;
    void setGenderCvId(const std::string &pGenderCvId) noexcept;
    void setGenderCvId(std::string &&pGenderCvId) noexcept;
    void setGenderCvIdToNull() noexcept;

    /**  For column date_of_birth  */
    const ::trantor::Date &getValueOfDateOfBirth() const noexcept;
    const std::shared_ptr<::trantor::Date> &getDateOfBirth() const noexcept;
    void setDateOfBirth(const ::trantor::Date &pDateOfBirth) noexcept;
    void setDateOfBirthToNull() noexcept;

    /**  For column profession_cv_id  */
    const std::string &getValueOfProfessionCvId() const noexcept;
    const std::shared_ptr<std::string> &getProfessionCvId() const noexcept;
    void setProfessionCvId(const std::string &pProfessionCvId) noexcept;
    void setProfessionCvId(std::string &&pProfessionCvId) noexcept;
    void setProfessionCvIdToNull() noexcept;

    /**  For column created_by  */
    const std::string &getValueOfCreatedBy() const noexcept;
    const std::shared_ptr<std::string> &getCreatedBy() const noexcept;
    void setCreatedBy(const std::string &pCreatedBy) noexcept;
    void setCreatedBy(std::string &&pCreatedBy) noexcept;
    void setCreatedByToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;
    void setCreatedAtToNull() noexcept;

    /**  For column updated_by  */
    const std::string &getValueOfUpdatedBy() const noexcept;
    const std::shared_ptr<std::string> &getUpdatedBy() const noexcept;
    void setUpdatedBy(const std::string &pUpdatedBy) noexcept;
    void setUpdatedBy(std::string &&pUpdatedBy) noexcept;
    void setUpdatedByToNull() noexcept;

    /**  For column updated_at  */
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;
    void setUpdatedAtToNull() noexcept;

    static size_t getColumnNumber() noexcept {  return 18;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<ClientFamilyMember>;
    friend drogon::orm::BaseBuilder<ClientFamilyMember, true, true>;
    friend drogon::orm::BaseBuilder<ClientFamilyMember, true, false>;
    friend drogon::orm::BaseBuilder<ClientFamilyMember, false, true>;
    friend drogon::orm::BaseBuilder<ClientFamilyMember, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<ClientFamilyMember>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> firstname_;
    std::shared_ptr<std::string> middlename_;
    std::shared_ptr<std::string> lastname_;
    std::shared_ptr<std::string> qualification_;
    std::shared_ptr<std::string> mobileNumber_;
    std::shared_ptr<int32_t> age_;
    std::shared_ptr<bool> isDependent_;
    std::shared_ptr<std::string> relationshipCvId_;
    std::shared_ptr<std::string> maritalStatusCvId_;
    std::shared_ptr<std::string> genderCvId_;
    std::shared_ptr<::trantor::Date> dateOfBirth_;
    std::shared_ptr<std::string> professionCvId_;
    std::shared_ptr<std::string> createdBy_;
    std::shared_ptr<::trantor::Date> createdAt_;
    std::shared_ptr<std::string> updatedBy_;
    std::shared_ptr<::trantor::Date> updatedAt_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[18]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
        sql += "id,";
        ++parametersCount;
        if(!dirtyFlag_[0])
        {
            needSelection=true;
        }
        if(dirtyFlag_[1])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "firstname,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "middlename,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "lastname,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "qualification,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "mobile_number,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "age,";
            ++parametersCount;
        }
        sql += "is_dependent,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        if(dirtyFlag_[9])
        {
            sql += "relationship_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "marital_status_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "gender_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "date_of_birth,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "profession_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[15])
        {
            needSelection=true;
        }
        if(dirtyFlag_[16])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[17])
        {
            needSelection=true;
        }
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        if(dirtyFlag_[0])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[1])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[2])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[4])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[5])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[6])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[7])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[8])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[11])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[12])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[13])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[14])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[16])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[17])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace TlCustomerDb
} // namespace drogon_model
