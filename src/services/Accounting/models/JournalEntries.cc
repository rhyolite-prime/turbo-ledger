/**
 *
 *  JournalEntries.cc
 *
 *  See JournalEntries.h for the hand-authored-subset note (Phase 3 adds
 *  entry_seq/entry_hash/prev_hash for the hash chain; JSON (de)serialization
 *  methods are intentionally omitted, matching every other Accounting and
 *  Organization model).
 *
 */

#include "JournalEntries.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlAccounting;

const std::string JournalEntries::Cols::_id = "\"id\"";
const std::string JournalEntries::Cols::_account_id = "\"account_id\"";
const std::string JournalEntries::Cols::_office_id = "\"office_id\"";
const std::string JournalEntries::Cols::_reversal_id = "\"reversal_id\"";
const std::string JournalEntries::Cols::_currency_code = "\"currency_code\"";
const std::string JournalEntries::Cols::_transaction_id = "\"transaction_id\"";
const std::string JournalEntries::Cols::_loan_transaction_id = "\"loan_transaction_id\"";
const std::string JournalEntries::Cols::_savings_transaction_id = "\"savings_transaction_id\"";
const std::string JournalEntries::Cols::_client_transaction_id = "\"client_transaction_id\"";
const std::string JournalEntries::Cols::_reversed = "\"reversed\"";
const std::string JournalEntries::Cols::_ref_num = "\"ref_num\"";
const std::string JournalEntries::Cols::_manual_entry = "\"manual_entry\"";
const std::string JournalEntries::Cols::_entry_date = "\"entry_date\"";
const std::string JournalEntries::Cols::_type_enum = "\"type_enum\"";
const std::string JournalEntries::Cols::_amount = "\"amount\"";
const std::string JournalEntries::Cols::_description = "\"description\"";
const std::string JournalEntries::Cols::_entity_type_enum = "\"entity_type_enum\"";
const std::string JournalEntries::Cols::_entity_id = "\"entity_id\"";
const std::string JournalEntries::Cols::_created_by = "\"created_by\"";
const std::string JournalEntries::Cols::_last_modified_by = "\"last_modified_by\"";
const std::string JournalEntries::Cols::_created_date = "\"created_date\"";
const std::string JournalEntries::Cols::_lastmodified_date = "\"lastmodified_date\"";
const std::string JournalEntries::Cols::_is_running_balance_calculated = "\"is_running_balance_calculated\"";
const std::string JournalEntries::Cols::_office_running_balance = "\"office_running_balance\"";
const std::string JournalEntries::Cols::_organization_running_balance = "\"organization_running_balance\"";
const std::string JournalEntries::Cols::_payment_details_id = "\"payment_details_id\"";
const std::string JournalEntries::Cols::_share_transaction_id = "\"share_transaction_id\"";
const std::string JournalEntries::Cols::_transaction_date = "\"transaction_date\"";
const std::string JournalEntries::Cols::_created_on_utc = "\"created_on_utc\"";
const std::string JournalEntries::Cols::_last_modified_on_utc = "\"last_modified_on_utc\"";
const std::string JournalEntries::Cols::_submitted_on_date = "\"submitted_on_date\"";
const std::string JournalEntries::Cols::_entry_seq = "\"entry_seq\"";
const std::string JournalEntries::Cols::_entry_hash = "\"entry_hash\"";
const std::string JournalEntries::Cols::_prev_hash = "\"prev_hash\"";
const std::string JournalEntries::primaryKeyName = "id";
const bool JournalEntries::hasPrimaryKey = true;
const std::string JournalEntries::tableName = "\"journal_entries\"";

const std::vector<typename JournalEntries::MetaData> JournalEntries::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"account_id","std::string","uuid",0,0,0,1},
{"office_id","std::string","uuid",0,0,0,1},
{"reversal_id","std::string","uuid",0,0,0,0},
{"currency_code","std::string","character varying",3,0,0,1},
{"transaction_id","std::string","character varying",50,0,0,1},
{"loan_transaction_id","std::string","uuid",0,0,0,0},
{"savings_transaction_id","std::string","uuid",0,0,0,0},
{"client_transaction_id","std::string","uuid",0,0,0,0},
{"reversed","bool","boolean",1,0,0,1},
{"ref_num","std::string","character varying",100,0,0,0},
{"manual_entry","bool","boolean",1,0,0,1},
{"entry_date","::trantor::Date","date",0,0,0,1},
{"type_enum","short","smallint",2,0,0,1},
{"amount","std::string","numeric",0,0,0,1},
{"description","std::string","character varying",500,0,0,0},
{"entity_type_enum","short","smallint",2,0,0,0},
{"entity_id","std::string","uuid",0,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"last_modified_by","std::string","uuid",0,0,0,0},
{"created_date","::trantor::Date","timestamp without time zone",0,0,0,0},
{"lastmodified_date","::trantor::Date","timestamp without time zone",0,0,0,0},
{"is_running_balance_calculated","bool","boolean",1,0,0,1},
{"office_running_balance","std::string","numeric",0,0,0,1},
{"organization_running_balance","std::string","numeric",0,0,0,1},
{"payment_details_id","std::string","uuid",0,0,0,0},
{"share_transaction_id","std::string","uuid",0,0,0,0},
{"transaction_date","::trantor::Date","date",0,0,0,0},
{"created_on_utc","::trantor::Date","timestamp without time zone",0,0,0,0},
{"last_modified_on_utc","::trantor::Date","timestamp without time zone",0,0,0,0},
{"submitted_on_date","::trantor::Date","date",0,0,0,1},
{"entry_seq","int64_t","bigint",0,1,0,1},
{"entry_hash","std::string","character varying",64,0,0,0},
{"prev_hash","std::string","character varying",64,0,0,0}
};
const std::string &JournalEntries::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
JournalEntries::JournalEntries(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["account_id"].isNull())
        {
            accountId_=std::make_shared<std::string>(r["account_id"].as<std::string>());
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["reversal_id"].isNull())
        {
            reversalId_=std::make_shared<std::string>(r["reversal_id"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["transaction_id"].isNull())
        {
            transactionId_=std::make_shared<std::string>(r["transaction_id"].as<std::string>());
        }
        if(!r["loan_transaction_id"].isNull())
        {
            loanTransactionId_=std::make_shared<std::string>(r["loan_transaction_id"].as<std::string>());
        }
        if(!r["savings_transaction_id"].isNull())
        {
            savingsTransactionId_=std::make_shared<std::string>(r["savings_transaction_id"].as<std::string>());
        }
        if(!r["client_transaction_id"].isNull())
        {
            clientTransactionId_=std::make_shared<std::string>(r["client_transaction_id"].as<std::string>());
        }
        if(!r["reversed"].isNull())
        {
            reversed_=std::make_shared<bool>(r["reversed"].as<bool>());
        }
        if(!r["ref_num"].isNull())
        {
            refNum_=std::make_shared<std::string>(r["ref_num"].as<std::string>());
        }
        if(!r["manual_entry"].isNull())
        {
            manualEntry_=std::make_shared<bool>(r["manual_entry"].as<bool>());
        }
        if(!r["entry_date"].isNull())
        {
            auto daysStr = r["entry_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            entryDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["type_enum"].isNull())
        {
            typeEnum_=std::make_shared<short>(r["type_enum"].as<short>());
        }
        if(!r["amount"].isNull())
        {
            amount_=std::make_shared<std::string>(r["amount"].as<std::string>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["entity_type_enum"].isNull())
        {
            entityTypeEnum_=std::make_shared<short>(r["entity_type_enum"].as<short>());
        }
        if(!r["entity_id"].isNull())
        {
            entityId_=std::make_shared<std::string>(r["entity_id"].as<std::string>());
        }
        if(!r["created_by"].isNull())
        {
            createdBy_=std::make_shared<std::string>(r["created_by"].as<std::string>());
        }
        if(!r["last_modified_by"].isNull())
        {
            lastModifiedBy_=std::make_shared<std::string>(r["last_modified_by"].as<std::string>());
        }
        if(!r["created_date"].isNull())
        {
            auto timeStr = r["created_date"].as<std::string>();
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
                createdDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["lastmodified_date"].isNull())
        {
            auto timeStr = r["lastmodified_date"].as<std::string>();
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
                lastmodifiedDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["is_running_balance_calculated"].isNull())
        {
            isRunningBalanceCalculated_=std::make_shared<bool>(r["is_running_balance_calculated"].as<bool>());
        }
        if(!r["office_running_balance"].isNull())
        {
            officeRunningBalance_=std::make_shared<std::string>(r["office_running_balance"].as<std::string>());
        }
        if(!r["organization_running_balance"].isNull())
        {
            organizationRunningBalance_=std::make_shared<std::string>(r["organization_running_balance"].as<std::string>());
        }
        if(!r["payment_details_id"].isNull())
        {
            paymentDetailsId_=std::make_shared<std::string>(r["payment_details_id"].as<std::string>());
        }
        if(!r["share_transaction_id"].isNull())
        {
            shareTransactionId_=std::make_shared<std::string>(r["share_transaction_id"].as<std::string>());
        }
        if(!r["transaction_date"].isNull())
        {
            auto daysStr = r["transaction_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            transactionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["created_on_utc"].isNull())
        {
            auto timeStr = r["created_on_utc"].as<std::string>();
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
                createdOnUtc_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["last_modified_on_utc"].isNull())
        {
            auto timeStr = r["last_modified_on_utc"].as<std::string>();
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
                lastModifiedOnUtc_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["submitted_on_date"].isNull())
        {
            auto daysStr = r["submitted_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["entry_seq"].isNull())
        {
            entrySeq_=std::make_shared<int64_t>(r["entry_seq"].as<int64_t>());
        }
        if(!r["entry_hash"].isNull())
        {
            entryHash_=std::make_shared<std::string>(r["entry_hash"].as<std::string>());
        }
        if(!r["prev_hash"].isNull())
        {
            prevHash_=std::make_shared<std::string>(r["prev_hash"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 34 > r.size())
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
            accountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            reversalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            transactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            loanTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            savingsTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            clientTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            reversed_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            refNum_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            manualEntry_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            entryDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            typeEnum_=std::make_shared<short>(r[index].as<short>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            amount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            entityTypeEnum_=std::make_shared<short>(r[index].as<short>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            entityId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            lastModifiedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 20;
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
                createdDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 21;
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
                lastmodifiedDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            isRunningBalanceCalculated_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            officeRunningBalance_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 24;
        if(!r[index].isNull())
        {
            organizationRunningBalance_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 25;
        if(!r[index].isNull())
        {
            paymentDetailsId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 26;
        if(!r[index].isNull())
        {
            shareTransactionId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 27;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            transactionDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 28;
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
                createdOnUtc_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 29;
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
                lastModifiedOnUtc_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 30;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 31;
        if(!r[index].isNull())
        {
            entrySeq_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 32;
        if(!r[index].isNull())
        {
            entryHash_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 33;
        if(!r[index].isNull())
        {
            prevHash_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

const std::string &JournalEntries::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getId() const noexcept
{
    return id_;
}
void JournalEntries::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void JournalEntries::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename JournalEntries::PrimaryKeyType & JournalEntries::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &JournalEntries::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getAccountId() const noexcept
{
    return accountId_;
}
void JournalEntries::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[1] = true;
}
void JournalEntries::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[1] = true;
}

const std::string &JournalEntries::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getOfficeId() const noexcept
{
    return officeId_;
}
void JournalEntries::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[2] = true;
}
void JournalEntries::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[2] = true;
}

const std::string &JournalEntries::getValueOfReversalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reversalId_)
        return *reversalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getReversalId() const noexcept
{
    return reversalId_;
}
void JournalEntries::setReversalId(const std::string &pReversalId) noexcept
{
    reversalId_ = std::make_shared<std::string>(pReversalId);
    dirtyFlag_[3] = true;
}
void JournalEntries::setReversalId(std::string &&pReversalId) noexcept
{
    reversalId_ = std::make_shared<std::string>(std::move(pReversalId));
    dirtyFlag_[3] = true;
}
void JournalEntries::setReversalIdToNull() noexcept
{
    reversalId_.reset();
    dirtyFlag_[3] = true;
}

const std::string &JournalEntries::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void JournalEntries::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[4] = true;
}
void JournalEntries::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[4] = true;
}

const std::string &JournalEntries::getValueOfTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transactionId_)
        return *transactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getTransactionId() const noexcept
{
    return transactionId_;
}
void JournalEntries::setTransactionId(const std::string &pTransactionId) noexcept
{
    transactionId_ = std::make_shared<std::string>(pTransactionId);
    dirtyFlag_[5] = true;
}
void JournalEntries::setTransactionId(std::string &&pTransactionId) noexcept
{
    transactionId_ = std::make_shared<std::string>(std::move(pTransactionId));
    dirtyFlag_[5] = true;
}

const std::string &JournalEntries::getValueOfLoanTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanTransactionId_)
        return *loanTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getLoanTransactionId() const noexcept
{
    return loanTransactionId_;
}
void JournalEntries::setLoanTransactionId(const std::string &pLoanTransactionId) noexcept
{
    loanTransactionId_ = std::make_shared<std::string>(pLoanTransactionId);
    dirtyFlag_[6] = true;
}
void JournalEntries::setLoanTransactionId(std::string &&pLoanTransactionId) noexcept
{
    loanTransactionId_ = std::make_shared<std::string>(std::move(pLoanTransactionId));
    dirtyFlag_[6] = true;
}
void JournalEntries::setLoanTransactionIdToNull() noexcept
{
    loanTransactionId_.reset();
    dirtyFlag_[6] = true;
}

const std::string &JournalEntries::getValueOfSavingsTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(savingsTransactionId_)
        return *savingsTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getSavingsTransactionId() const noexcept
{
    return savingsTransactionId_;
}
void JournalEntries::setSavingsTransactionId(const std::string &pSavingsTransactionId) noexcept
{
    savingsTransactionId_ = std::make_shared<std::string>(pSavingsTransactionId);
    dirtyFlag_[7] = true;
}
void JournalEntries::setSavingsTransactionId(std::string &&pSavingsTransactionId) noexcept
{
    savingsTransactionId_ = std::make_shared<std::string>(std::move(pSavingsTransactionId));
    dirtyFlag_[7] = true;
}
void JournalEntries::setSavingsTransactionIdToNull() noexcept
{
    savingsTransactionId_.reset();
    dirtyFlag_[7] = true;
}

const std::string &JournalEntries::getValueOfClientTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientTransactionId_)
        return *clientTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getClientTransactionId() const noexcept
{
    return clientTransactionId_;
}
void JournalEntries::setClientTransactionId(const std::string &pClientTransactionId) noexcept
{
    clientTransactionId_ = std::make_shared<std::string>(pClientTransactionId);
    dirtyFlag_[8] = true;
}
void JournalEntries::setClientTransactionId(std::string &&pClientTransactionId) noexcept
{
    clientTransactionId_ = std::make_shared<std::string>(std::move(pClientTransactionId));
    dirtyFlag_[8] = true;
}
void JournalEntries::setClientTransactionIdToNull() noexcept
{
    clientTransactionId_.reset();
    dirtyFlag_[8] = true;
}

const bool &JournalEntries::getValueOfReversed() const noexcept
{
    static const bool defaultValue = bool();
    if(reversed_)
        return *reversed_;
    return defaultValue;
}
const std::shared_ptr<bool> &JournalEntries::getReversed() const noexcept
{
    return reversed_;
}
void JournalEntries::setReversed(const bool &pReversed) noexcept
{
    reversed_ = std::make_shared<bool>(pReversed);
    dirtyFlag_[9] = true;
}

const std::string &JournalEntries::getValueOfRefNum() const noexcept
{
    static const std::string defaultValue = std::string();
    if(refNum_)
        return *refNum_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getRefNum() const noexcept
{
    return refNum_;
}
void JournalEntries::setRefNum(const std::string &pRefNum) noexcept
{
    refNum_ = std::make_shared<std::string>(pRefNum);
    dirtyFlag_[10] = true;
}
void JournalEntries::setRefNum(std::string &&pRefNum) noexcept
{
    refNum_ = std::make_shared<std::string>(std::move(pRefNum));
    dirtyFlag_[10] = true;
}
void JournalEntries::setRefNumToNull() noexcept
{
    refNum_.reset();
    dirtyFlag_[10] = true;
}

const bool &JournalEntries::getValueOfManualEntry() const noexcept
{
    static const bool defaultValue = bool();
    if(manualEntry_)
        return *manualEntry_;
    return defaultValue;
}
const std::shared_ptr<bool> &JournalEntries::getManualEntry() const noexcept
{
    return manualEntry_;
}
void JournalEntries::setManualEntry(const bool &pManualEntry) noexcept
{
    manualEntry_ = std::make_shared<bool>(pManualEntry);
    dirtyFlag_[11] = true;
}

const ::trantor::Date &JournalEntries::getValueOfEntryDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(entryDate_)
        return *entryDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JournalEntries::getEntryDate() const noexcept
{
    return entryDate_;
}
void JournalEntries::setEntryDate(const ::trantor::Date &pEntryDate) noexcept
{
    entryDate_ = std::make_shared<::trantor::Date>(pEntryDate.roundDay());
    dirtyFlag_[12] = true;
}

const short &JournalEntries::getValueOfTypeEnum() const noexcept
{
    static const short defaultValue = short();
    if(typeEnum_)
        return *typeEnum_;
    return defaultValue;
}
const std::shared_ptr<short> &JournalEntries::getTypeEnum() const noexcept
{
    return typeEnum_;
}
void JournalEntries::setTypeEnum(const short &pTypeEnum) noexcept
{
    typeEnum_ = std::make_shared<short>(pTypeEnum);
    dirtyFlag_[13] = true;
}

const std::string &JournalEntries::getValueOfAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(amount_)
        return *amount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getAmount() const noexcept
{
    return amount_;
}
void JournalEntries::setAmount(const std::string &pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(pAmount);
    dirtyFlag_[14] = true;
}
void JournalEntries::setAmount(std::string &&pAmount) noexcept
{
    amount_ = std::make_shared<std::string>(std::move(pAmount));
    dirtyFlag_[14] = true;
}

const std::string &JournalEntries::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getDescription() const noexcept
{
    return description_;
}
void JournalEntries::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[15] = true;
}
void JournalEntries::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[15] = true;
}
void JournalEntries::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[15] = true;
}

const short &JournalEntries::getValueOfEntityTypeEnum() const noexcept
{
    static const short defaultValue = short();
    if(entityTypeEnum_)
        return *entityTypeEnum_;
    return defaultValue;
}
const std::shared_ptr<short> &JournalEntries::getEntityTypeEnum() const noexcept
{
    return entityTypeEnum_;
}
void JournalEntries::setEntityTypeEnum(const short &pEntityTypeEnum) noexcept
{
    entityTypeEnum_ = std::make_shared<short>(pEntityTypeEnum);
    dirtyFlag_[16] = true;
}
void JournalEntries::setEntityTypeEnumToNull() noexcept
{
    entityTypeEnum_.reset();
    dirtyFlag_[16] = true;
}

const std::string &JournalEntries::getValueOfEntityId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(entityId_)
        return *entityId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getEntityId() const noexcept
{
    return entityId_;
}
void JournalEntries::setEntityId(const std::string &pEntityId) noexcept
{
    entityId_ = std::make_shared<std::string>(pEntityId);
    dirtyFlag_[17] = true;
}
void JournalEntries::setEntityId(std::string &&pEntityId) noexcept
{
    entityId_ = std::make_shared<std::string>(std::move(pEntityId));
    dirtyFlag_[17] = true;
}
void JournalEntries::setEntityIdToNull() noexcept
{
    entityId_.reset();
    dirtyFlag_[17] = true;
}

const std::string &JournalEntries::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getCreatedBy() const noexcept
{
    return createdBy_;
}
void JournalEntries::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[18] = true;
}
void JournalEntries::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[18] = true;
}
void JournalEntries::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[18] = true;
}

const std::string &JournalEntries::getValueOfLastModifiedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lastModifiedBy_)
        return *lastModifiedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getLastModifiedBy() const noexcept
{
    return lastModifiedBy_;
}
void JournalEntries::setLastModifiedBy(const std::string &pLastModifiedBy) noexcept
{
    lastModifiedBy_ = std::make_shared<std::string>(pLastModifiedBy);
    dirtyFlag_[19] = true;
}
void JournalEntries::setLastModifiedBy(std::string &&pLastModifiedBy) noexcept
{
    lastModifiedBy_ = std::make_shared<std::string>(std::move(pLastModifiedBy));
    dirtyFlag_[19] = true;
}
void JournalEntries::setLastModifiedByToNull() noexcept
{
    lastModifiedBy_.reset();
    dirtyFlag_[19] = true;
}

const ::trantor::Date &JournalEntries::getValueOfCreatedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdDate_)
        return *createdDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JournalEntries::getCreatedDate() const noexcept
{
    return createdDate_;
}
void JournalEntries::setCreatedDate(const ::trantor::Date &pCreatedDate) noexcept
{
    createdDate_ = std::make_shared<::trantor::Date>(pCreatedDate);
    dirtyFlag_[20] = true;
}
void JournalEntries::setCreatedDateToNull() noexcept
{
    createdDate_.reset();
    dirtyFlag_[20] = true;
}

const ::trantor::Date &JournalEntries::getValueOfLastmodifiedDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(lastmodifiedDate_)
        return *lastmodifiedDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JournalEntries::getLastmodifiedDate() const noexcept
{
    return lastmodifiedDate_;
}
void JournalEntries::setLastmodifiedDate(const ::trantor::Date &pLastmodifiedDate) noexcept
{
    lastmodifiedDate_ = std::make_shared<::trantor::Date>(pLastmodifiedDate);
    dirtyFlag_[21] = true;
}
void JournalEntries::setLastmodifiedDateToNull() noexcept
{
    lastmodifiedDate_.reset();
    dirtyFlag_[21] = true;
}

const bool &JournalEntries::getValueOfIsRunningBalanceCalculated() const noexcept
{
    static const bool defaultValue = bool();
    if(isRunningBalanceCalculated_)
        return *isRunningBalanceCalculated_;
    return defaultValue;
}
const std::shared_ptr<bool> &JournalEntries::getIsRunningBalanceCalculated() const noexcept
{
    return isRunningBalanceCalculated_;
}
void JournalEntries::setIsRunningBalanceCalculated(const bool &pIsRunningBalanceCalculated) noexcept
{
    isRunningBalanceCalculated_ = std::make_shared<bool>(pIsRunningBalanceCalculated);
    dirtyFlag_[22] = true;
}

const std::string &JournalEntries::getValueOfOfficeRunningBalance() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeRunningBalance_)
        return *officeRunningBalance_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getOfficeRunningBalance() const noexcept
{
    return officeRunningBalance_;
}
void JournalEntries::setOfficeRunningBalance(const std::string &pOfficeRunningBalance) noexcept
{
    officeRunningBalance_ = std::make_shared<std::string>(pOfficeRunningBalance);
    dirtyFlag_[23] = true;
}
void JournalEntries::setOfficeRunningBalance(std::string &&pOfficeRunningBalance) noexcept
{
    officeRunningBalance_ = std::make_shared<std::string>(std::move(pOfficeRunningBalance));
    dirtyFlag_[23] = true;
}

const std::string &JournalEntries::getValueOfOrganizationRunningBalance() const noexcept
{
    static const std::string defaultValue = std::string();
    if(organizationRunningBalance_)
        return *organizationRunningBalance_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getOrganizationRunningBalance() const noexcept
{
    return organizationRunningBalance_;
}
void JournalEntries::setOrganizationRunningBalance(const std::string &pOrganizationRunningBalance) noexcept
{
    organizationRunningBalance_ = std::make_shared<std::string>(pOrganizationRunningBalance);
    dirtyFlag_[24] = true;
}
void JournalEntries::setOrganizationRunningBalance(std::string &&pOrganizationRunningBalance) noexcept
{
    organizationRunningBalance_ = std::make_shared<std::string>(std::move(pOrganizationRunningBalance));
    dirtyFlag_[24] = true;
}

const std::string &JournalEntries::getValueOfPaymentDetailsId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(paymentDetailsId_)
        return *paymentDetailsId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getPaymentDetailsId() const noexcept
{
    return paymentDetailsId_;
}
void JournalEntries::setPaymentDetailsId(const std::string &pPaymentDetailsId) noexcept
{
    paymentDetailsId_ = std::make_shared<std::string>(pPaymentDetailsId);
    dirtyFlag_[25] = true;
}
void JournalEntries::setPaymentDetailsId(std::string &&pPaymentDetailsId) noexcept
{
    paymentDetailsId_ = std::make_shared<std::string>(std::move(pPaymentDetailsId));
    dirtyFlag_[25] = true;
}
void JournalEntries::setPaymentDetailsIdToNull() noexcept
{
    paymentDetailsId_.reset();
    dirtyFlag_[25] = true;
}

const std::string &JournalEntries::getValueOfShareTransactionId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(shareTransactionId_)
        return *shareTransactionId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getShareTransactionId() const noexcept
{
    return shareTransactionId_;
}
void JournalEntries::setShareTransactionId(const std::string &pShareTransactionId) noexcept
{
    shareTransactionId_ = std::make_shared<std::string>(pShareTransactionId);
    dirtyFlag_[26] = true;
}
void JournalEntries::setShareTransactionId(std::string &&pShareTransactionId) noexcept
{
    shareTransactionId_ = std::make_shared<std::string>(std::move(pShareTransactionId));
    dirtyFlag_[26] = true;
}
void JournalEntries::setShareTransactionIdToNull() noexcept
{
    shareTransactionId_.reset();
    dirtyFlag_[26] = true;
}

const ::trantor::Date &JournalEntries::getValueOfTransactionDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(transactionDate_)
        return *transactionDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JournalEntries::getTransactionDate() const noexcept
{
    return transactionDate_;
}
void JournalEntries::setTransactionDate(const ::trantor::Date &pTransactionDate) noexcept
{
    transactionDate_ = std::make_shared<::trantor::Date>(pTransactionDate.roundDay());
    dirtyFlag_[27] = true;
}
void JournalEntries::setTransactionDateToNull() noexcept
{
    transactionDate_.reset();
    dirtyFlag_[27] = true;
}

const ::trantor::Date &JournalEntries::getValueOfCreatedOnUtc() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdOnUtc_)
        return *createdOnUtc_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JournalEntries::getCreatedOnUtc() const noexcept
{
    return createdOnUtc_;
}
void JournalEntries::setCreatedOnUtc(const ::trantor::Date &pCreatedOnUtc) noexcept
{
    createdOnUtc_ = std::make_shared<::trantor::Date>(pCreatedOnUtc);
    dirtyFlag_[28] = true;
}
void JournalEntries::setCreatedOnUtcToNull() noexcept
{
    createdOnUtc_.reset();
    dirtyFlag_[28] = true;
}

const ::trantor::Date &JournalEntries::getValueOfLastModifiedOnUtc() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(lastModifiedOnUtc_)
        return *lastModifiedOnUtc_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JournalEntries::getLastModifiedOnUtc() const noexcept
{
    return lastModifiedOnUtc_;
}
void JournalEntries::setLastModifiedOnUtc(const ::trantor::Date &pLastModifiedOnUtc) noexcept
{
    lastModifiedOnUtc_ = std::make_shared<::trantor::Date>(pLastModifiedOnUtc);
    dirtyFlag_[29] = true;
}
void JournalEntries::setLastModifiedOnUtcToNull() noexcept
{
    lastModifiedOnUtc_.reset();
    dirtyFlag_[29] = true;
}

const ::trantor::Date &JournalEntries::getValueOfSubmittedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedOnDate_)
        return *submittedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &JournalEntries::getSubmittedOnDate() const noexcept
{
    return submittedOnDate_;
}
void JournalEntries::setSubmittedOnDate(const ::trantor::Date &pSubmittedOnDate) noexcept
{
    submittedOnDate_ = std::make_shared<::trantor::Date>(pSubmittedOnDate.roundDay());
    dirtyFlag_[30] = true;
}


const int64_t &JournalEntries::getValueOfEntrySeq() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(entrySeq_)
        return *entrySeq_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &JournalEntries::getEntrySeq() const noexcept
{
    return entrySeq_;
}
void JournalEntries::setEntrySeq(const int64_t &pEntrySeq) noexcept
{
    entrySeq_ = std::make_shared<int64_t>(pEntrySeq);
    dirtyFlag_[31] = true;
}

const std::string &JournalEntries::getValueOfEntryHash() const noexcept
{
    static const std::string defaultValue = std::string();
    if(entryHash_)
        return *entryHash_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getEntryHash() const noexcept
{
    return entryHash_;
}
void JournalEntries::setEntryHash(const std::string &pEntryHash) noexcept
{
    entryHash_ = std::make_shared<std::string>(pEntryHash);
    dirtyFlag_[32] = true;
}
void JournalEntries::setEntryHash(std::string &&pEntryHash) noexcept
{
    entryHash_ = std::make_shared<std::string>(std::move(pEntryHash));
    dirtyFlag_[32] = true;
}
void JournalEntries::setEntryHashToNull() noexcept
{
    entryHash_.reset();
    dirtyFlag_[32] = true;
}

const std::string &JournalEntries::getValueOfPrevHash() const noexcept
{
    static const std::string defaultValue = std::string();
    if(prevHash_)
        return *prevHash_;
    return defaultValue;
}
const std::shared_ptr<std::string> &JournalEntries::getPrevHash() const noexcept
{
    return prevHash_;
}
void JournalEntries::setPrevHash(const std::string &pPrevHash) noexcept
{
    prevHash_ = std::make_shared<std::string>(pPrevHash);
    dirtyFlag_[33] = true;
}
void JournalEntries::setPrevHash(std::string &&pPrevHash) noexcept
{
    prevHash_ = std::make_shared<std::string>(std::move(pPrevHash));
    dirtyFlag_[33] = true;
}
void JournalEntries::setPrevHashToNull() noexcept
{
    prevHash_.reset();
    dirtyFlag_[33] = true;
}

void JournalEntries::updateId(const uint64_t id)
{
}

const std::vector<std::string> &JournalEntries::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "account_id",
        "office_id",
        "reversal_id",
        "currency_code",
        "transaction_id",
        "loan_transaction_id",
        "savings_transaction_id",
        "client_transaction_id",
        "reversed",
        "ref_num",
        "manual_entry",
        "entry_date",
        "type_enum",
        "amount",
        "description",
        "entity_type_enum",
        "entity_id",
        "created_by",
        "last_modified_by",
        "created_date",
        "lastmodified_date",
        "is_running_balance_calculated",
        "office_running_balance",
        "organization_running_balance",
        "payment_details_id",
        "share_transaction_id",
        "transaction_date",
        "created_on_utc",
        "last_modified_on_utc",
        "submitted_on_date",
        "entry_seq",
        "entry_hash",
        "prev_hash"
    };
    return inCols;
}

void JournalEntries::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountId())
        {
            binder << getValueOfAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getReversalId())
        {
            binder << getValueOfReversalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransactionId())
        {
            binder << getValueOfTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getLoanTransactionId())
        {
            binder << getValueOfLoanTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getSavingsTransactionId())
        {
            binder << getValueOfSavingsTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getClientTransactionId())
        {
            binder << getValueOfClientTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getReversed())
        {
            binder << getValueOfReversed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getRefNum())
        {
            binder << getValueOfRefNum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getManualEntry())
        {
            binder << getValueOfManualEntry();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getEntryDate())
        {
            binder << getValueOfEntryDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getTypeEnum())
        {
            binder << getValueOfTypeEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getEntityTypeEnum())
        {
            binder << getValueOfEntityTypeEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getEntityId())
        {
            binder << getValueOfEntityId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
    {
        if(getLastModifiedBy())
        {
            binder << getValueOfLastModifiedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
    {
        if(getLastmodifiedDate())
        {
            binder << getValueOfLastmodifiedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getIsRunningBalanceCalculated())
        {
            binder << getValueOfIsRunningBalanceCalculated();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getOfficeRunningBalance())
        {
            binder << getValueOfOfficeRunningBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getOrganizationRunningBalance())
        {
            binder << getValueOfOrganizationRunningBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getPaymentDetailsId())
        {
            binder << getValueOfPaymentDetailsId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getShareTransactionId())
        {
            binder << getValueOfShareTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
    {
        if(getTransactionDate())
        {
            binder << getValueOfTransactionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
    {
        if(getCreatedOnUtc())
        {
            binder << getValueOfCreatedOnUtc();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getLastModifiedOnUtc())
        {
            binder << getValueOfLastModifiedOnUtc();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getEntrySeq())
        {
            binder << getValueOfEntrySeq();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getEntryHash())
        {
            binder << getValueOfEntryHash();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getPrevHash())
        {
            binder << getValueOfPrevHash();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> JournalEntries::updateColumns() const
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
    if(dirtyFlag_[18])
    {
        ret.push_back(getColumnName(18));
    }
    if(dirtyFlag_[19])
    {
        ret.push_back(getColumnName(19));
    }
    if(dirtyFlag_[20])
    {
        ret.push_back(getColumnName(20));
    }
    if(dirtyFlag_[21])
    {
        ret.push_back(getColumnName(21));
    }
    if(dirtyFlag_[22])
    {
        ret.push_back(getColumnName(22));
    }
    if(dirtyFlag_[23])
    {
        ret.push_back(getColumnName(23));
    }
    if(dirtyFlag_[24])
    {
        ret.push_back(getColumnName(24));
    }
    if(dirtyFlag_[25])
    {
        ret.push_back(getColumnName(25));
    }
    if(dirtyFlag_[26])
    {
        ret.push_back(getColumnName(26));
    }
    if(dirtyFlag_[27])
    {
        ret.push_back(getColumnName(27));
    }
    if(dirtyFlag_[28])
    {
        ret.push_back(getColumnName(28));
    }
    if(dirtyFlag_[29])
    {
        ret.push_back(getColumnName(29));
    }
    if(dirtyFlag_[30])
    {
        ret.push_back(getColumnName(30));
    }
    if(dirtyFlag_[31])
    {
        ret.push_back(getColumnName(31));
    }
    if(dirtyFlag_[32])
    {
        ret.push_back(getColumnName(32));
    }
    if(dirtyFlag_[33])
    {
        ret.push_back(getColumnName(33));
    }
    return ret;
}

void JournalEntries::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAccountId())
        {
            binder << getValueOfAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getReversalId())
        {
            binder << getValueOfReversalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getCurrencyCode())
        {
            binder << getValueOfCurrencyCode();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getTransactionId())
        {
            binder << getValueOfTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getLoanTransactionId())
        {
            binder << getValueOfLoanTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getSavingsTransactionId())
        {
            binder << getValueOfSavingsTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getClientTransactionId())
        {
            binder << getValueOfClientTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getReversed())
        {
            binder << getValueOfReversed();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getRefNum())
        {
            binder << getValueOfRefNum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getManualEntry())
        {
            binder << getValueOfManualEntry();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getEntryDate())
        {
            binder << getValueOfEntryDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getTypeEnum())
        {
            binder << getValueOfTypeEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
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
    if(dirtyFlag_[15])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getEntityTypeEnum())
        {
            binder << getValueOfEntityTypeEnum();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getEntityId())
        {
            binder << getValueOfEntityId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
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
    if(dirtyFlag_[19])
    {
        if(getLastModifiedBy())
        {
            binder << getValueOfLastModifiedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
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
    if(dirtyFlag_[21])
    {
        if(getLastmodifiedDate())
        {
            binder << getValueOfLastmodifiedDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getIsRunningBalanceCalculated())
        {
            binder << getValueOfIsRunningBalanceCalculated();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getOfficeRunningBalance())
        {
            binder << getValueOfOfficeRunningBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getOrganizationRunningBalance())
        {
            binder << getValueOfOrganizationRunningBalance();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getPaymentDetailsId())
        {
            binder << getValueOfPaymentDetailsId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getShareTransactionId())
        {
            binder << getValueOfShareTransactionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
    {
        if(getTransactionDate())
        {
            binder << getValueOfTransactionDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
    {
        if(getCreatedOnUtc())
        {
            binder << getValueOfCreatedOnUtc();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getLastModifiedOnUtc())
        {
            binder << getValueOfLastModifiedOnUtc();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getSubmittedOnDate())
        {
            binder << getValueOfSubmittedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getEntrySeq())
        {
            binder << getValueOfEntrySeq();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getEntryHash())
        {
            binder << getValueOfEntryHash();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getPrevHash())
        {
            binder << getValueOfPrevHash();
        }
        else
        {
            binder << nullptr;
        }
    }
}
