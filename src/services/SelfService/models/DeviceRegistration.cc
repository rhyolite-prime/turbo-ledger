/**
 *  DeviceRegistration.cc
 *
 *  See DeviceRegistration.h for the hand-authored-subset note.
 *
 */

#include "DeviceRegistration.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlSelfServiceDb;

const std::string DeviceRegistration::Cols::_id = "\"id\"";
const std::string DeviceRegistration::Cols::_self_service_user_id = "\"self_service_user_id\"";
const std::string DeviceRegistration::Cols::_client_id = "\"client_id\"";
const std::string DeviceRegistration::Cols::_device_id = "\"device_id\"";
const std::string DeviceRegistration::Cols::_device_name = "\"device_name\"";
const std::string DeviceRegistration::Cols::_status = "\"status\"";
const std::string DeviceRegistration::Cols::_created_at = "\"created_at\"";
const std::string DeviceRegistration::Cols::_updated_at = "\"updated_at\"";
const std::string DeviceRegistration::primaryKeyName = "id";
const bool DeviceRegistration::hasPrimaryKey = true;
const std::string DeviceRegistration::tableName = "\"device_registrations\"";

const std::vector<typename DeviceRegistration::MetaData> DeviceRegistration::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"self_service_user_id","std::string","character varying",64,0,0,1},
{"client_id","std::string","character varying",64,0,0,1},
{"device_id","std::string","character varying",150,0,0,1},
{"device_name","std::string","character varying",150,0,0,0},
{"status","std::string","character varying",20,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &DeviceRegistration::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
DeviceRegistration::DeviceRegistration(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["self_service_user_id"].isNull())
        {
            selfServiceUserId_=std::make_shared<std::string>(r["self_service_user_id"].as<std::string>());
        }
        if(!r["client_id"].isNull())
        {
            clientId_=std::make_shared<std::string>(r["client_id"].as<std::string>());
        }
        if(!r["device_id"].isNull())
        {
            deviceId_=std::make_shared<std::string>(r["device_id"].as<std::string>());
        }
        if(!r["device_name"].isNull())
        {
            deviceName_=std::make_shared<std::string>(r["device_name"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<std::string>(r["status"].as<std::string>());
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
        if(offset + 8 > r.size())
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
            selfServiceUserId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            deviceId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            deviceName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            status_=std::make_shared<std::string>(r[index].as<std::string>());
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
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 7;
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
const std::string &DeviceRegistration::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DeviceRegistration::getId() const noexcept
{
    return id_;
}
void DeviceRegistration::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void DeviceRegistration::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename DeviceRegistration::PrimaryKeyType & DeviceRegistration::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &DeviceRegistration::getValueOfSelfServiceUserId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(selfServiceUserId_)
        return *selfServiceUserId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DeviceRegistration::getSelfServiceUserId() const noexcept
{
    return selfServiceUserId_;
}
void DeviceRegistration::setSelfServiceUserId(const std::string &pSelfServiceUserId) noexcept
{
    selfServiceUserId_ = std::make_shared<std::string>(pSelfServiceUserId);
    dirtyFlag_[1] = true;
}
void DeviceRegistration::setSelfServiceUserId(std::string &&pSelfServiceUserId) noexcept
{
    selfServiceUserId_ = std::make_shared<std::string>(std::move(pSelfServiceUserId));
    dirtyFlag_[1] = true;
}

const std::string &DeviceRegistration::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DeviceRegistration::getClientId() const noexcept
{
    return clientId_;
}
void DeviceRegistration::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[2] = true;
}
void DeviceRegistration::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[2] = true;
}

const std::string &DeviceRegistration::getValueOfDeviceId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(deviceId_)
        return *deviceId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DeviceRegistration::getDeviceId() const noexcept
{
    return deviceId_;
}
void DeviceRegistration::setDeviceId(const std::string &pDeviceId) noexcept
{
    deviceId_ = std::make_shared<std::string>(pDeviceId);
    dirtyFlag_[3] = true;
}
void DeviceRegistration::setDeviceId(std::string &&pDeviceId) noexcept
{
    deviceId_ = std::make_shared<std::string>(std::move(pDeviceId));
    dirtyFlag_[3] = true;
}

const std::string &DeviceRegistration::getValueOfDeviceName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(deviceName_)
        return *deviceName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DeviceRegistration::getDeviceName() const noexcept
{
    return deviceName_;
}
void DeviceRegistration::setDeviceName(const std::string &pDeviceName) noexcept
{
    deviceName_ = std::make_shared<std::string>(pDeviceName);
    dirtyFlag_[4] = true;
}
void DeviceRegistration::setDeviceName(std::string &&pDeviceName) noexcept
{
    deviceName_ = std::make_shared<std::string>(std::move(pDeviceName));
    dirtyFlag_[4] = true;
}
void DeviceRegistration::setDeviceNameToNull() noexcept
{
    deviceName_.reset();
    dirtyFlag_[4] = true;
}

const std::string &DeviceRegistration::getValueOfStatus() const noexcept
{
    static const std::string defaultValue = std::string();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<std::string> &DeviceRegistration::getStatus() const noexcept
{
    return status_;
}
void DeviceRegistration::setStatus(const std::string &pStatus) noexcept
{
    status_ = std::make_shared<std::string>(pStatus);
    dirtyFlag_[5] = true;
}
void DeviceRegistration::setStatus(std::string &&pStatus) noexcept
{
    status_ = std::make_shared<std::string>(std::move(pStatus));
    dirtyFlag_[5] = true;
}

const ::trantor::Date &DeviceRegistration::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &DeviceRegistration::getCreatedAt() const noexcept
{
    return createdAt_;
}
void DeviceRegistration::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[6] = true;
}

const ::trantor::Date &DeviceRegistration::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &DeviceRegistration::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void DeviceRegistration::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[7] = true;
}

void DeviceRegistration::updateId(const uint64_t id)
{
}

const std::vector<std::string> &DeviceRegistration::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "self_service_user_id",
        "client_id",
        "device_id",
        "device_name",
        "status",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void DeviceRegistration::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSelfServiceUserId())
        {
            binder << getValueOfSelfServiceUserId();
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
        if(getDeviceId())
        {
            binder << getValueOfDeviceId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDeviceName())
        {
            binder << getValueOfDeviceName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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

const std::vector<std::string> DeviceRegistration::updateColumns() const
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
    return ret;
}

void DeviceRegistration::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getSelfServiceUserId())
        {
            binder << getValueOfSelfServiceUserId();
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
        if(getDeviceId())
        {
            binder << getValueOfDeviceId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDeviceName())
        {
            binder << getValueOfDeviceName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
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
