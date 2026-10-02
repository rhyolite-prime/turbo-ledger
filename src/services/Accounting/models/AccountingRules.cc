/**
 *
 *  AccountingRules.cc
 *
 *  See AccountingRules.h for the hand-patch note (debit_account_id/
 *  credit_account_id int32_t -> std::string bug fix). As with the other
 *  Phase 2/3 hand-authored models, the JSON (de)serialization methods a
 *  live drogon_ctl would also emit (toJson/toMasqueradedJson, the two
 *  Json::Value constructors, updateByJson/updateByMasqueradedJson,
 *  validateJsonForCreation/validateMasqueradedJsonForCreation/
 *  validateJsonForUpdate/validateMasqueradedJsonForUpdate/validJsonOfField)
 *  are intentionally omitted: nothing in this codebase calls them.
 *
 */

#include "AccountingRules.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlAccounting;

const std::string AccountingRules::Cols::_id = "\"id\"";
const std::string AccountingRules::Cols::_name = "\"name\"";
const std::string AccountingRules::Cols::_office_id = "\"office_id\"";
const std::string AccountingRules::Cols::_debit_account_id = "\"debit_account_id\"";
const std::string AccountingRules::Cols::_allow_multiple_debits = "\"allow_multiple_debits\"";
const std::string AccountingRules::Cols::_credit_account_id = "\"credit_account_id\"";
const std::string AccountingRules::Cols::_allow_multiple_credits = "\"allow_multiple_credits\"";
const std::string AccountingRules::Cols::_description = "\"description\"";
const std::string AccountingRules::Cols::_system_defined = "\"system_defined\"";
const std::string AccountingRules::primaryKeyName = "id";
const bool AccountingRules::hasPrimaryKey = true;
const std::string AccountingRules::tableName = "\"accounting_rules\"";

const std::vector<typename AccountingRules::MetaData> AccountingRules::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"name","std::string","character varying",100,0,0,0},
{"office_id","std::string","uuid",0,0,0,0},
{"debit_account_id","std::string","uuid",0,0,0,0},
{"allow_multiple_debits","bool","boolean",1,0,0,1},
{"credit_account_id","std::string","uuid",0,0,0,0},
{"allow_multiple_credits","bool","boolean",1,0,0,1},
{"description","std::string","character varying",500,0,0,0},
{"system_defined","bool","boolean",1,0,0,1}
};
const std::string &AccountingRules::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
AccountingRules::AccountingRules(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["debit_account_id"].isNull())
        {
            debitAccountId_=std::make_shared<std::string>(r["debit_account_id"].as<std::string>());
        }
        if(!r["allow_multiple_debits"].isNull())
        {
            allowMultipleDebits_=std::make_shared<bool>(r["allow_multiple_debits"].as<bool>());
        }
        if(!r["credit_account_id"].isNull())
        {
            creditAccountId_=std::make_shared<std::string>(r["credit_account_id"].as<std::string>());
        }
        if(!r["allow_multiple_credits"].isNull())
        {
            allowMultipleCredits_=std::make_shared<bool>(r["allow_multiple_credits"].as<bool>());
        }
        if(!r["description"].isNull())
        {
            description_=std::make_shared<std::string>(r["description"].as<std::string>());
        }
        if(!r["system_defined"].isNull())
        {
            systemDefined_=std::make_shared<bool>(r["system_defined"].as<bool>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 9 > r.size())
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
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            debitAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            allowMultipleDebits_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            creditAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            allowMultipleCredits_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            systemDefined_=std::make_shared<bool>(r[index].as<bool>());
        }
    }

}

const std::string &AccountingRules::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRules::getId() const noexcept
{
    return id_;
}
void AccountingRules::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void AccountingRules::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename AccountingRules::PrimaryKeyType & AccountingRules::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &AccountingRules::getValueOfName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRules::getName() const noexcept
{
    return name_;
}
void AccountingRules::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[1] = true;
}
void AccountingRules::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[1] = true;
}
void AccountingRules::setNameToNull() noexcept
{
    name_.reset();
    dirtyFlag_[1] = true;
}

const std::string &AccountingRules::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRules::getOfficeId() const noexcept
{
    return officeId_;
}
void AccountingRules::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[2] = true;
}
void AccountingRules::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[2] = true;
}
void AccountingRules::setOfficeIdToNull() noexcept
{
    officeId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &AccountingRules::getValueOfDebitAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(debitAccountId_)
        return *debitAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRules::getDebitAccountId() const noexcept
{
    return debitAccountId_;
}
void AccountingRules::setDebitAccountId(const std::string &pDebitAccountId) noexcept
{
    debitAccountId_ = std::make_shared<std::string>(pDebitAccountId);
    dirtyFlag_[3] = true;
}
void AccountingRules::setDebitAccountId(std::string &&pDebitAccountId) noexcept
{
    debitAccountId_ = std::make_shared<std::string>(std::move(pDebitAccountId));
    dirtyFlag_[3] = true;
}
void AccountingRules::setDebitAccountIdToNull() noexcept
{
    debitAccountId_.reset();
    dirtyFlag_[3] = true;
}

const bool &AccountingRules::getValueOfAllowMultipleDebits() const noexcept
{
    static const bool defaultValue = bool();
    if(allowMultipleDebits_)
        return *allowMultipleDebits_;
    return defaultValue;
}
const std::shared_ptr<bool> &AccountingRules::getAllowMultipleDebits() const noexcept
{
    return allowMultipleDebits_;
}
void AccountingRules::setAllowMultipleDebits(const bool &pAllowMultipleDebits) noexcept
{
    allowMultipleDebits_ = std::make_shared<bool>(pAllowMultipleDebits);
    dirtyFlag_[4] = true;
}

const std::string &AccountingRules::getValueOfCreditAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(creditAccountId_)
        return *creditAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRules::getCreditAccountId() const noexcept
{
    return creditAccountId_;
}
void AccountingRules::setCreditAccountId(const std::string &pCreditAccountId) noexcept
{
    creditAccountId_ = std::make_shared<std::string>(pCreditAccountId);
    dirtyFlag_[5] = true;
}
void AccountingRules::setCreditAccountId(std::string &&pCreditAccountId) noexcept
{
    creditAccountId_ = std::make_shared<std::string>(std::move(pCreditAccountId));
    dirtyFlag_[5] = true;
}
void AccountingRules::setCreditAccountIdToNull() noexcept
{
    creditAccountId_.reset();
    dirtyFlag_[5] = true;
}

const bool &AccountingRules::getValueOfAllowMultipleCredits() const noexcept
{
    static const bool defaultValue = bool();
    if(allowMultipleCredits_)
        return *allowMultipleCredits_;
    return defaultValue;
}
const std::shared_ptr<bool> &AccountingRules::getAllowMultipleCredits() const noexcept
{
    return allowMultipleCredits_;
}
void AccountingRules::setAllowMultipleCredits(const bool &pAllowMultipleCredits) noexcept
{
    allowMultipleCredits_ = std::make_shared<bool>(pAllowMultipleCredits);
    dirtyFlag_[6] = true;
}

const std::string &AccountingRules::getValueOfDescription() const noexcept
{
    static const std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRules::getDescription() const noexcept
{
    return description_;
}
void AccountingRules::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[7] = true;
}
void AccountingRules::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[7] = true;
}
void AccountingRules::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[7] = true;
}

const bool &AccountingRules::getValueOfSystemDefined() const noexcept
{
    static const bool defaultValue = bool();
    if(systemDefined_)
        return *systemDefined_;
    return defaultValue;
}
const std::shared_ptr<bool> &AccountingRules::getSystemDefined() const noexcept
{
    return systemDefined_;
}
void AccountingRules::setSystemDefined(const bool &pSystemDefined) noexcept
{
    systemDefined_ = std::make_shared<bool>(pSystemDefined);
    dirtyFlag_[8] = true;
}

void AccountingRules::updateId(const uint64_t id)
{
}

const std::vector<std::string> &AccountingRules::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "name",
        "office_id",
        "debit_account_id",
        "allow_multiple_debits",
        "credit_account_id",
        "allow_multiple_credits",
        "description",
        "system_defined"
    };
    return inCols;
}

void AccountingRules::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
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
        if(getDebitAccountId())
        {
            binder << getValueOfDebitAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAllowMultipleDebits())
        {
            binder << getValueOfAllowMultipleDebits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreditAccountId())
        {
            binder << getValueOfCreditAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAllowMultipleCredits())
        {
            binder << getValueOfAllowMultipleCredits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getSystemDefined())
        {
            binder << getValueOfSystemDefined();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> AccountingRules::updateColumns() const
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
    return ret;
}

void AccountingRules::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
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
        if(getDebitAccountId())
        {
            binder << getValueOfDebitAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getAllowMultipleDebits())
        {
            binder << getValueOfAllowMultipleDebits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getCreditAccountId())
        {
            binder << getValueOfCreditAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getAllowMultipleCredits())
        {
            binder << getValueOfAllowMultipleCredits();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
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
    if(dirtyFlag_[8])
    {
        if(getSystemDefined())
        {
            binder << getValueOfSystemDefined();
        }
        else
        {
            binder << nullptr;
        }
    }
}
