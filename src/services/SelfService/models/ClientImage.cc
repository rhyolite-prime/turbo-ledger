/**
 *  ClientImage.cc
 *
 *  See ClientImage.h for the hand-authored-subset note.
 *
 */

#include "ClientImage.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlSelfServiceDb;

const std::string ClientImage::Cols::_id = "\"id\"";
const std::string ClientImage::Cols::_client_id = "\"client_id\"";
const std::string ClientImage::Cols::_content_type = "\"content_type\"";
const std::string ClientImage::Cols::_image_data = "\"image_data\"";
const std::string ClientImage::Cols::_created_at = "\"created_at\"";
const std::string ClientImage::Cols::_updated_at = "\"updated_at\"";
const std::string ClientImage::primaryKeyName = "id";
const bool ClientImage::hasPrimaryKey = true;
const std::string ClientImage::tableName = "\"client_images\"";

const std::vector<typename ClientImage::MetaData> ClientImage::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"client_id","std::string","character varying",64,0,0,1},
{"content_type","std::string","character varying",100,0,0,1},
{"image_data","std::string","text",0,0,0,1},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &ClientImage::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ClientImage::ClientImage(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["content_type"].isNull())
        {
            contentType_=std::make_shared<std::string>(r["content_type"].as<std::string>());
        }
        if(!r["image_data"].isNull())
        {
            imageData_=std::make_shared<std::string>(r["image_data"].as<std::string>());
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
            clientId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            contentType_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            imageData_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
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
                updatedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &ClientImage::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientImage::getId() const noexcept
{
    return id_;
}
void ClientImage::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ClientImage::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ClientImage::PrimaryKeyType & ClientImage::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ClientImage::getValueOfClientId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientId_)
        return *clientId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientImage::getClientId() const noexcept
{
    return clientId_;
}
void ClientImage::setClientId(const std::string &pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(pClientId);
    dirtyFlag_[1] = true;
}
void ClientImage::setClientId(std::string &&pClientId) noexcept
{
    clientId_ = std::make_shared<std::string>(std::move(pClientId));
    dirtyFlag_[1] = true;
}

const std::string &ClientImage::getValueOfContentType() const noexcept
{
    static const std::string defaultValue = std::string();
    if(contentType_)
        return *contentType_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientImage::getContentType() const noexcept
{
    return contentType_;
}
void ClientImage::setContentType(const std::string &pContentType) noexcept
{
    contentType_ = std::make_shared<std::string>(pContentType);
    dirtyFlag_[2] = true;
}
void ClientImage::setContentType(std::string &&pContentType) noexcept
{
    contentType_ = std::make_shared<std::string>(std::move(pContentType));
    dirtyFlag_[2] = true;
}

const std::string &ClientImage::getValueOfImageData() const noexcept
{
    static const std::string defaultValue = std::string();
    if(imageData_)
        return *imageData_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ClientImage::getImageData() const noexcept
{
    return imageData_;
}
void ClientImage::setImageData(const std::string &pImageData) noexcept
{
    imageData_ = std::make_shared<std::string>(pImageData);
    dirtyFlag_[3] = true;
}
void ClientImage::setImageData(std::string &&pImageData) noexcept
{
    imageData_ = std::make_shared<std::string>(std::move(pImageData));
    dirtyFlag_[3] = true;
}

const ::trantor::Date &ClientImage::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientImage::getCreatedAt() const noexcept
{
    return createdAt_;
}
void ClientImage::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[4] = true;
}

const ::trantor::Date &ClientImage::getValueOfUpdatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedAt_)
        return *updatedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &ClientImage::getUpdatedAt() const noexcept
{
    return updatedAt_;
}
void ClientImage::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    updatedAt_ = std::make_shared<::trantor::Date>(pUpdatedAt);
    dirtyFlag_[5] = true;
}

void ClientImage::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ClientImage::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "client_id",
        "content_type",
        "image_data",
        "created_at",
        "updated_at"
    };
    return inCols;
}

void ClientImage::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getContentType())
        {
            binder << getValueOfContentType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getImageData())
        {
            binder << getValueOfImageData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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

const std::vector<std::string> ClientImage::updateColumns() const
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

void ClientImage::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getContentType())
        {
            binder << getValueOfContentType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getImageData())
        {
            binder << getValueOfImageData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
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
