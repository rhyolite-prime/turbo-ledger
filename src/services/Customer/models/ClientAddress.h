/**
 *  ClientAddress.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<ClientAddress> usage actually needs
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

class ClientAddress
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _client_id;
        static const std::string _street;
        static const std::string _address_line_1;
        static const std::string _address_line_2;
        static const std::string _city;
        static const std::string _state_or_province;
        static const std::string _country;
        static const std::string _country_code;
        static const std::string _address_type_id;
        static const std::string _is_active;
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

    explicit ClientAddress(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    ClientAddress() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column business_id  */
    const std::string &getValueOfBusinessId() const noexcept;
    const std::shared_ptr<std::string> &getBusinessId() const noexcept;
    void setBusinessId(const std::string &pBusinessId) noexcept;
    void setBusinessId(std::string &&pBusinessId) noexcept;
    void setBusinessIdToNull() noexcept;

    /**  For column client_id  */
    const std::string &getValueOfClientId() const noexcept;
    const std::shared_ptr<std::string> &getClientId() const noexcept;
    void setClientId(const std::string &pClientId) noexcept;
    void setClientId(std::string &&pClientId) noexcept;

    /**  For column street  */
    const std::string &getValueOfStreet() const noexcept;
    const std::shared_ptr<std::string> &getStreet() const noexcept;
    void setStreet(const std::string &pStreet) noexcept;
    void setStreet(std::string &&pStreet) noexcept;
    void setStreetToNull() noexcept;

    /**  For column address_line_1  */
    const std::string &getValueOfAddressLine1() const noexcept;
    const std::shared_ptr<std::string> &getAddressLine1() const noexcept;
    void setAddressLine1(const std::string &pAddressLine1) noexcept;
    void setAddressLine1(std::string &&pAddressLine1) noexcept;
    void setAddressLine1ToNull() noexcept;

    /**  For column address_line_2  */
    const std::string &getValueOfAddressLine2() const noexcept;
    const std::shared_ptr<std::string> &getAddressLine2() const noexcept;
    void setAddressLine2(const std::string &pAddressLine2) noexcept;
    void setAddressLine2(std::string &&pAddressLine2) noexcept;
    void setAddressLine2ToNull() noexcept;

    /**  For column city  */
    const std::string &getValueOfCity() const noexcept;
    const std::shared_ptr<std::string> &getCity() const noexcept;
    void setCity(const std::string &pCity) noexcept;
    void setCity(std::string &&pCity) noexcept;
    void setCityToNull() noexcept;

    /**  For column state_or_province  */
    const std::string &getValueOfStateOrProvince() const noexcept;
    const std::shared_ptr<std::string> &getStateOrProvince() const noexcept;
    void setStateOrProvince(const std::string &pStateOrProvince) noexcept;
    void setStateOrProvince(std::string &&pStateOrProvince) noexcept;
    void setStateOrProvinceToNull() noexcept;

    /**  For column country  */
    const std::string &getValueOfCountry() const noexcept;
    const std::shared_ptr<std::string> &getCountry() const noexcept;
    void setCountry(const std::string &pCountry) noexcept;
    void setCountry(std::string &&pCountry) noexcept;
    void setCountryToNull() noexcept;

    /**  For column country_code  */
    const std::string &getValueOfCountryCode() const noexcept;
    const std::shared_ptr<std::string> &getCountryCode() const noexcept;
    void setCountryCode(const std::string &pCountryCode) noexcept;
    void setCountryCode(std::string &&pCountryCode) noexcept;
    void setCountryCodeToNull() noexcept;

    /**  For column address_type_id  */
    const std::string &getValueOfAddressTypeId() const noexcept;
    const std::shared_ptr<std::string> &getAddressTypeId() const noexcept;
    void setAddressTypeId(const std::string &pAddressTypeId) noexcept;
    void setAddressTypeId(std::string &&pAddressTypeId) noexcept;
    void setAddressTypeIdToNull() noexcept;

    /**  For column is_active  */
    const bool &getValueOfIsActive() const noexcept;
    const std::shared_ptr<bool> &getIsActive() const noexcept;
    void setIsActive(const bool &pIsActive) noexcept;

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

    static size_t getColumnNumber() noexcept {  return 16;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<ClientAddress>;
    friend drogon::orm::BaseBuilder<ClientAddress, true, true>;
    friend drogon::orm::BaseBuilder<ClientAddress, true, false>;
    friend drogon::orm::BaseBuilder<ClientAddress, false, true>;
    friend drogon::orm::BaseBuilder<ClientAddress, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<ClientAddress>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> clientId_;
    std::shared_ptr<std::string> street_;
    std::shared_ptr<std::string> addressLine1_;
    std::shared_ptr<std::string> addressLine2_;
    std::shared_ptr<std::string> city_;
    std::shared_ptr<std::string> stateOrProvince_;
    std::shared_ptr<std::string> country_;
    std::shared_ptr<std::string> countryCode_;
    std::shared_ptr<std::string> addressTypeId_;
    std::shared_ptr<bool> isActive_;
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
    bool dirtyFlag_[16]={ false };
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
            sql += "business_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "client_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "street,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "address_line_1,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "address_line_2,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "city,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "state_or_province,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "country,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "country_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "address_type_id,";
            ++parametersCount;
        }
        sql += "is_active,";
        ++parametersCount;
        if(!dirtyFlag_[11])
        {
            needSelection=true;
        }
        if(dirtyFlag_[12])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[13])
        {
            needSelection=true;
        }
        if(dirtyFlag_[14])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        sql += "updated_at,";
        ++parametersCount;
        if(!dirtyFlag_[15])
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
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
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
