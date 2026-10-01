/**
 *  StandingInstructionHistory.cc
 *
 *  See StandingInstructionHistory.h for the hand-authored-subset note.
 *
 */

#include "StandingInstructionHistory.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlDamDb;

const std::string StandingInstructionHistory::Cols::_id = "\"id\"";
const std::string StandingInstructionHistory::Cols::_standing_instruction_id = "\"standing_instruction_id\"";
const std::string StandingInstructionHistory::Cols::_status = "\"status\"";
const std::string StandingInstructionHistory::Cols::_amount = "\"amount\"";
const std::string StandingInstructionHistory::Cols::_execution_date = "\"execution_date\"";
const std::string StandingInstructionHistory::Cols::_error_log = "\"error_log\"";
const std::string StandingInstructionHistory::Cols::_account_transfer_transaction_id = "\"account_transfer_transaction_id\"";
const std::string StandingInstructionHistory::Cols::_created_at = "\"created_at\"";
const std::string StandingInstructionHistory::primaryKeyName = "id";
const bool StandingInstructionHistory::hasPrimaryKey = true;
const std::string StandingInstructionHistory::tableName = "\"standing_instruction_history\"";

const std::vector<typename StandingInstructionHistory::MetaData> StandingInstructionHistory::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"standing_instruction_id","std::string","uuid",0,0,0,1},
{"status","int32_t","integer",4,0,0,1},
{"amount","std::string","numeric",0,0,0,0},
{"execution_date","::trantor::Date","date",0,0,0,1},
{"error_log","std::string","character varying",1000,0,0,0},
{"account_transfer_transaction_id","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &StandingInstructionHistory::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
StandingInstructionHistory::StandingInstructionHistory(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["standing_instruction_id"].isNull())
        {
            standingInstructionId_=std::make_shared<std::string>(r["standing_instruction_id"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["execution_date"].isNull())
        {
            auto daysStr = r["execution_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            executionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["error_log"].isNull())
        {
            errorLog_=std::make_shared<std::string>(r["error_log"].as<std::string>());
        }
        if(!r["account_transfer_transaction_id"].isNull())
        {
            accountTransferTransactionId_=std::make_shared<std::string>(r["account_transfer_transaction_id"].as<std::string>());
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
            standingInstructionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            executionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            errorLog_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            accountTransferTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
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
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &StandingInstructionHistory::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstructionHistory::getId() const noexcept
{
    return id_;
}
void StandingInstructionHistory::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void StandingInstructionHistory::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename StandingInstructionHistory::PrimaryKeyType & StandingInstructionHistory::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &StandingInstructionHistory::getValueOfStandingInstructionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(standingInstructionId_)
        return *standingInstructionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstructionHistory::getStandingInstructionId() const noexcept
{
    return standingInstructionId_;
}
void StandingInstructionHistory::setStandingInstructionId(const std::string &pStandingInstructionId) noexcept
{
    standingInstructionId_ = std::make_shared<std::string>(pStandingInstructionId);
    dirtyFlag_[1] = true;
}
void StandingInstructionHistory::setStandingInstructionId(std::string &&pStandingInstructionId) noexcept
{
    standingInstructionId_ = std::make_shared<std::string>(std::move(pStandingInstructionId));
    dirtyFlag_[1] = true;
}

const int32_t &StandingInstructionHistory::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &StandingInstructionHistory::getStatus() const noexcept
{
    return status_;
}
void StandingInstructionHistory::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[2] = true;
}

const std::string &StandingInstructionHistory::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstructionHistory::getAmount() const noexcept
{
    return amount_;
}
void StandingInstructionHistory::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[3] = true;
}
void StandingInstructionHistory::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[3] = true;
}
void StandingInstructionHistory::setAmountToNull() noexcept
{
    amount_.reset();
    dirtyFlag_[3] = true;
}

const ::trantor::Date &StandingInstructionHistory::getValueOfExecutionDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(executionDate_)
        return *executionDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &StandingInstructionHistory::getExecutionDate() const noexcept
{
    return executionDate_;
}
void StandingInstructionHistory::setExecutionDate(const ::trantor::Date &pExecutionDate) noexcept
{
    executionDate_ = std::make_shared<::trantor::Date>(pExecutionDate);
    dirtyFlag_[4] = true;
}

const std::string &StandingInstructionHistory::getValueOfErrorLog() const noexcept
{
    static const std::string defaultValue = std::string();
    if(errorLog_)
        return *errorLog_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstructionHistory::getErrorLog() const noexcept
{
    return errorLog_;
}
void StandingInstructionHistory::setErrorLog(const std::string &pErrorLog) noexcept
{
    errorLog_ = std::make_shared<std::string>(pErrorLog);
    dirtyFlag_[5] = true;
}
void StandingInstructionHistory::setErrorLog(std::string &&pErrorLog) noexcept
{
    errorLog_ = std::make_shared<std::string>(std::move(pErrorLog));
    dirtyFlag_[5] = true;
}
void StandingInstructionHistory::setErrorLogToNull() noexcept
{
    errorLog_.reset();
    dirtyFlag_[5] = true;
}

const std::string &StandingInstructionHistory::getValueOfAccountTransferTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountTransferTransactionId_)
        return *accountTransferTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &StandingInstructionHistory::getAccountTransferTransactionId() const noexcept
{
    return accountTransferTransactionId_;
}
void StandingInstructionHistory::setAccountTransferTransactionId(const std::string &pAccountTransferTransactionId) noexcept
{
    accountTransferTransactionId_ = std::make_shared<std::string>(pAccountTransferTransactionId);
    dirtyFlag_[6] = true;
}
void StandingInstructionHistory::setAccountTransferTransactionId(std::string &&pAccountTransferTransactionId) noexcept
{
    accountTransferTransactionId_ = std::make_shared<std::string>(std::move(pAccountTransferTransactionId));
    dirtyFlag_[6] = true;
}
void StandingInstructionHistory::setAccountTransferTransactionIdToNull() noexcept
{
    accountTransferTransactionId_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &StandingInstructionHistory::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &StandingInstructionHistory::getCreatedAt() const noexcept
{
    return createdAt_;
}
void StandingInstructionHistory::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[7] = true;
}

void StandingInstructionHistory::updateId(const uint64_t id)
{
}

const std::vector<std::string> &StandingInstructionHistory::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "standing_instruction_id",
        "status",
        "amount",
        "execution_date",
        "error_log",
        "account_transfer_transaction_id",
        "created_at"
    };
    return inCols;
}

void StandingInstructionHistory::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getStandingInstructionId())
        {
            binder << getValueOfStandingInstructionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getExecutionDate())
        {
            binder << getValueOfExecutionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getErrorLog())
        {
            binder << getValueOfErrorLog();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAccountTransferTransactionId())
        {
            binder << getValueOfAccountTransferTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
}

const std::vector<std::string> StandingInstructionHistory::updateColumns() const
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

void StandingInstructionHistory::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getStandingInstructionId())
        {
            binder << getValueOfStandingInstructionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getAmount())
        {
            binder << getValueOfAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getExecutionDate())
        {
            binder << getValueOfExecutionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getErrorLog())
        {
            binder << getValueOfErrorLog();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAccountTransferTransactionId())
        {
            binder << getValueOfAccountTransferTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
}
