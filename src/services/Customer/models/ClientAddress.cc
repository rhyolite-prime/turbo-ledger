/**
 *  ClientAddress.cc
 *
 *  See ClientAddress.h for the hand-authored-subset note.
 *
 */

#include "ClientAddress.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlCustomerDb;

const std::string ClientAddress::Cols::_id = "\"id\"";
const std::string ClientAddress::Cols::_business_id = "\"business_id\"";
const std::string ClientAddress::Cols::_client_id = "\"client_id\"";
const std::string ClientAddress::Cols::_street = "\"street\"";
const std::string ClientAddress::Cols::_address_line_1 = "\"address_line_1\"";
const std::string ClientAddress::Cols::_address_line_2 = "\"address_line_2\"";
const std::string ClientAddress::Cols::_city = "\"city\"";
const std::string ClientAddress::Cols::_state_or_province = "\"state_or_province\"";
const std::string ClientAddress::Cols::_country = "\"country\"";
const std::string ClientAddress::Cols::_country_code = "\"country_code\"";
const std::string ClientAddress::Cols::_address_type_id = "\"address_type_id\"";
const std::string ClientAddress::Cols::_is_active = "\"is_active\"";
const std::string ClientAddress::Cols::_created_by = "\"created_by\"";
const std::string ClientAddress::Cols::_created_at = "\"created_at\"";
const std::string ClientAddress::Cols::_updated_by = "\"updated_by\"";
const std::string ClientAddress::Cols::_updated_at = "\"updated_at\"";
const std::string ClientAddress::primaryKeyName = "id";
const bool ClientAddress::hasPrimaryKey = true;
const std::string ClientAddress::tableName = "\"client_address\"";

const std::vector<typename ClientAddress::MetaData> ClientAddress::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"client_id","std::string","uuid",0,0,0,1},
{"street","std::string","character varying",150,0,0,0},
{"address_line_1","std::string","character varying",150,0,0,0},
{"address_line_2","std::string","character varying",150,0,0,0},
{"city","std::string","character varying",150,0,0,0},
{"state_or_province","std::string","character varying",150,0,0,0},
{"country","std::string","character varying",150,0,0,0},
{"country_code","std::string","character varying",150,0,0,0},
{"address_type_id","std::string","uuid",0,0,0,0},
{"is_active","bool","boolean",1,0,0,1},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,0},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,0}
};
const std::string &ClientAddress::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ClientAddress::ClientAddress(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["street"].isNull())
        {
            street_=std::make_shared<std::string>(r["street"].as<std::string>());
        }
        if(!r["address_line_1"].isNull())
        {
            addressLine1_=std::make_shared<std::string>(r["address_line_1"].as<std::string>());
        }
        if(!r["address_line_2"].isNull())
        {
            addressLine2_=std::make_shared<std::string>(r["address_line_2"].as<std::string>());
        }
        if(!r["city"].isNull())
        {
            city_=std::make_shared<std::string>(r["city"].as<std::string>());
        }
        if(!r["state_or_province"].isNull())
        {
            stateOrProvince_=std::make_shared<std::string>(r["state_or_province"].as<std::string>());
        }
        if(!r["country"].isNull())
        {
            country_=std::make_shared<std::string>(r["country"].as<std::string>());
        }
        if(!r["country_code"].isNull())
        {
            countryCode_=std::make_shared<std::string>(r["country_code"].as<std::string>());
        }
        if(!r["address_type_id"].isNull())
        {
            addressTypeId_=std::make_shared<std::string>(r["address_type_id"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
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
        if(offset + 16 > r.size())
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
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            street_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            addressLine1_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            addressLine2_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            city_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            stateOrProvince_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            country_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            countryCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            addressTypeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
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
        index = offset + 14;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &ClientAddress::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getId() const noexcept
{
    return id_;
}
void ClientAddress::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ClientAddress::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ClientAddress::PrimaryKeyType & ClientAddress::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ClientAddress::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getBusinessId() const noexcept
{
    return businessId_;
}
void ClientAddress::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void ClientAddress::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void ClientAddress::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &ClientAddress::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getClientId() const noexcept
{
    return clientId_;
}
void ClientAddress::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[2] = true;
}
void ClientAddress::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[2] = true;
}

const std::string &ClientAddress::getValueOfStreet() const noexcept
{
    static const std::string defaultValue = std::string();
    if(street_)
        return *street_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getStreet() const noexcept
{
    return street_;
}
void ClientAddress::setStreet(const std::string &pStreet) noexcept
{
    street_ = std::make_shared<std::string>(pStreet);
    dirtyFlag_[3] = true;
}
void ClientAddress::setStreet(std::string &&pStreet) noexcept
{
    street_ = std::make_shared<std::string>(std::move(pStreet));
    dirtyFlag_[3] = true;
}
void ClientAddress::setStreetToNull() noexcept
{
    street_.reset();
    dirtyFlag_[3] = true;
}

const std::string &ClientAddress::getValueOfAddressLine1() const noexcept
{
    static const std::string defaultValue = std::string();
    if(addressLine1_)
        return *addressLine1_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getAddressLine1() const noexcept
{
    return addressLine1_;
}
void ClientAddress::setAddressLine1(const std::string &pAddressLine1) noexcept
{
    addressLine1_ = std::make_shared<std::string>(pAddressLine1);
    dirtyFlag_[4] = true;
}
void ClientAddress::setAddressLine1(std::string &&pAddressLine1) noexcept
{
    addressLine1_ = std::make_shared<std::string>(std::move(pAddressLine1));
    dirtyFlag_[4] = true;
}
void ClientAddress::setAddressLine1ToNull() noexcept
{
    addressLine1_.reset();
    dirtyFlag_[4] = true;
}

const std::string &ClientAddress::getValueOfAddressLine2() const noexcept
{
    static const std::string defaultValue = std::string();
    if(addressLine2_)
        return *addressLine2_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getAddressLine2() const noexcept
{
    return addressLine2_;
}
void ClientAddress::setAddressLine2(const std::string &pAddressLine2) noexcept
{
    addressLine2_ = std::make_shared<std::string>(pAddressLine2);
    dirtyFlag_[5] = true;
}
void ClientAddress::setAddressLine2(std::string &&pAddressLine2) noexcept
{
    addressLine2_ = std::make_shared<std::string>(std::move(pAddressLine2));
    dirtyFlag_[5] = true;
}
void ClientAddress::setAddressLine2ToNull() noexcept
{
    addressLine2_.reset();
    dirtyFlag_[5] = true;
}

const std::string &ClientAddress::getValueOfCity() const noexcept
{
    static const std::string defaultValue = std::string();
    if(city_)
        return *city_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getCity() const noexcept
{
    return city_;
}
void ClientAddress::setCity(const std::string &pCity) noexcept
{
    city_ = std::make_shared<std::string>(pCity);
    dirtyFlag_[6] = true;
}
void ClientAddress::setCity(std::string &&pCity) noexcept
{
    city_ = std::make_shared<std::string>(std::move(pCity));
    dirtyFlag_[6] = true;
}
void ClientAddress::setCityToNull() noexcept
{
    city_.reset();
    dirtyFlag_[6] = true;
}

const std::string &ClientAddress::getValueOfStateOrProvince() const noexcept
{
    static const std::string defaultValue = std::string();
    if(stateOrProvince_)
        return *stateOrProvince_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getStateOrProvince() const noexcept
{
    return stateOrProvince_;
}
void ClientAddress::setStateOrProvince(const std::string &pStateOrProvince) noexcept
{
    stateOrProvince_ = std::make_shared<std::string>(pStateOrProvince);
    dirtyFlag_[7] = true;
}
void ClientAddress::setStateOrProvince(std::string &&pStateOrProvince) noexcept
{
    stateOrProvince_ = std::make_shared<std::string>(std::move(pStateOrProvince));
    dirtyFlag_[7] = true;
}
void ClientAddress::setStateOrProvinceToNull() noexcept
{
    stateOrProvince_.reset();
    dirtyFlag_[7] = true;
}

const std::string &ClientAddress::getValueOfCountry() const noexcept
{
    static const std::string defaultValue = std::string();
    if(country_)
        return *country_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getCountry() const noexcept
{
    return country_;
}
void ClientAddress::setCountry(const std::string &pCountry) noexcept
{
    country_ = std::make_shared<std::string>(pCountry);
    dirtyFlag_[8] = true;
}
void ClientAddress::setCountry(std::string &&pCountry) noexcept
{
    country_ = std::make_shared<std::string>(std::move(pCountry));
    dirtyFlag_[8] = true;
}
void ClientAddress::setCountryToNull() noexcept
{
    country_.reset();
    dirtyFlag_[8] = true;
}

const std::string &ClientAddress::getValueOfCountryCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(countryCode_)
        return *countryCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getCountryCode() const noexcept
{
    return countryCode_;
}
void ClientAddress::setCountryCode(const std::string &pCountryCode) noexcept
{
    countryCode_ = std::make_shared<std::string>(pCountryCode);
    dirtyFlag_[9] = true;
}
void ClientAddress::setCountryCode(std::string &&pCountryCode) noexcept
{
    countryCode_ = std::make_shared<std::string>(std::move(pCountryCode));
    dirtyFlag_[9] = true;
}
void ClientAddress::setCountryCodeToNull() noexcept
{
    countryCode_.reset();
    dirtyFlag_[9] = true;
}

const std::string &ClientAddress::getValueOfAddressTypeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(addressTypeId_)
        return *addressTypeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getAddressTypeId() const noexcept
{
    return addressTypeId_;
}
void ClientAddress::setAddressTypeId(const std::string &pAddressTypeId) noexcept
{
    addressTypeId_ = std::make_shared<std::string>(pAddressTypeId);
    dirtyFlag_[10] = true;
}
void ClientAddress::setAddressTypeId(std::string &&pAddressTypeId) noexcept
{
    addressTypeId_ = std::make_shared<std::string>(std::move(pAddressTypeId));
    dirtyFlag_[10] = true;
}
void ClientAddress::setAddressTypeIdToNull() noexcept
{
    addressTypeId_.reset();
    dirtyFlag_[10] = true;
}

const bool &ClientAddress::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &ClientAddress::getIsActive() const noexcept
{
    return isActive_;
}
void ClientAddress::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[11] = true;
}

const std::string &ClientAddress::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getCreatedBy() const noexcept
{
    return createdBy_;
}
void ClientAddress::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[12] = true;
}
void ClientAddress::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[12] = true;
}
void ClientAddress::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[12] = true;
}

const ::trantor::Date &ClientAddress::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientAddress::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ClientAddress::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[13] = true;
}
void ClientAddress::setCreatedAtToNull() noexcept
{
    createdAt_.reset();
    dirtyFlag_[13] = true;
}

const std::string &ClientAddress::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientAddress::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void ClientAddress::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[14] = true;
}
void ClientAddress::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[14] = true;
}
void ClientAddress::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[14] = true;
}

const ::trantor::Date &ClientAddress::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientAddress::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void ClientAddress::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[15] = true;
}
void ClientAddress::setUpdatedAtToNull() noexcept
{
    updatedAt_.reset();
    dirtyFlag_[15] = true;
}

void ClientAddress::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ClientAddress::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "client_id",
        "street",
        "address_line_1",
        "address_line_2",
        "city",
        "state_or_province",
        "country",
        "country_code",
        "address_type_id",
        "is_active",
        "created_by",
        "created_at",
        "updated_by",
        "updated_at"
    };
    return inCols;
}

void ClientAddress::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getStreet())
        {
            binder << getValueOfStreet();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAddressLine1())
        {
            binder << getValueOfAddressLine1();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getAddressLine2())
        {
            binder << getValueOfAddressLine2();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getCity())
        {
            binder << getValueOfCity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getStateOrProvince())
        {
            binder << getValueOfStateOrProvince();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getCountry())
        {
            binder << getValueOfCountry();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getCountryCode())
        {
            binder << getValueOfCountryCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getAddressTypeId())
        {
            binder << getValueOfAddressTypeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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

const std::vector<std::string> ClientAddress::updateColumns() const
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
    return ret;
}

void ClientAddress::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getStreet())
        {
            binder << getValueOfStreet();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAddressLine1())
        {
            binder << getValueOfAddressLine1();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getAddressLine2())
        {
            binder << getValueOfAddressLine2();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getCity())
        {
            binder << getValueOfCity();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getStateOrProvince())
        {
            binder << getValueOfStateOrProvince();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getCountry())
        {
            binder << getValueOfCountry();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getCountryCode())
        {
            binder << getValueOfCountryCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getAddressTypeId())
        {
            binder << getValueOfAddressTypeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
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
    if(dirtyFlag_[12])
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
    if(dirtyFlag_[13])
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
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
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
