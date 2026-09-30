/**
 *
 *  AccountingRuleDebitAccount.cc
 *
 *  See AccountingRuleDebitAccount.h for the hand-authored-subset note.
 *
 */

#include "AccountingRuleDebitAccount.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlAccounting;

const std::string AccountingRuleDebitAccount::Cols::_id = "\"id\"";
const std::string AccountingRuleDebitAccount::Cols::_rule_id = "\"rule_id\"";
const std::string AccountingRuleDebitAccount::Cols::_account_id = "\"account_id\"";
const std::string AccountingRuleDebitAccount::primaryKeyName = "id";
const bool AccountingRuleDebitAccount::hasPrimaryKey = true;
const std::string AccountingRuleDebitAccount::tableName = "\"accounting_rule_debit_accounts\"";

const std::vector<typename AccountingRuleDebitAccount::MetaData> AccountingRuleDebitAccount::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"rule_id","std::string","uuid",0,0,0,1},
{"account_id","std::string","uuid",0,0,0,1}
};
const std::string &AccountingRuleDebitAccount::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
AccountingRuleDebitAccount::AccountingRuleDebitAccount(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["rule_id"].isNull())
        {
            ruleId_=std::make_shared<std::string>(r["rule_id"].as<std::string>());
        }
        if(!r["account_id"].isNull())
        {
            accountId_=std::make_shared<std::string>(r["account_id"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
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
            ruleId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            accountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &AccountingRuleDebitAccount::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRuleDebitAccount::getId() const noexcept
{
    return id_;
}
void AccountingRuleDebitAccount::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void AccountingRuleDebitAccount::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename AccountingRuleDebitAccount::PrimaryKeyType & AccountingRuleDebitAccount::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &AccountingRuleDebitAccount::getValueOfRuleId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(ruleId_)
        return *ruleId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRuleDebitAccount::getRuleId() const noexcept
{
    return ruleId_;
}
void AccountingRuleDebitAccount::setRuleId(const std::string &pRuleId) noexcept
{
    ruleId_ = std::make_shared<std::string>(pRuleId);
    dirtyFlag_[1] = true;
}
void AccountingRuleDebitAccount::setRuleId(std::string &&pRuleId) noexcept
{
    ruleId_ = std::make_shared<std::string>(std::move(pRuleId));
    dirtyFlag_[1] = true;
}

const std::string &AccountingRuleDebitAccount::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRuleDebitAccount::getAccountId() const noexcept
{
    return accountId_;
}
void AccountingRuleDebitAccount::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[2] = true;
}
void AccountingRuleDebitAccount::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[2] = true;
}

void AccountingRuleDebitAccount::updateId(const uint64_t id)
{
}

const std::vector<std::string> &AccountingRuleDebitAccount::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "rule_id",
        "account_id"
    };
    return inCols;
}

void AccountingRuleDebitAccount::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRuleId())
        {
            binder << getValueOfRuleId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
}

const std::vector<std::string> AccountingRuleDebitAccount::updateColumns() const
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
    return ret;
}

void AccountingRuleDebitAccount::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getRuleId())
        {
            binder << getValueOfRuleId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
}
