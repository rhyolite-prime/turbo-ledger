/**
 *
 *  AccountingRuleCreditAccount.cc
 *
 *  See AccountingRuleCreditAccount.h for the hand-authored-subset note.
 *
 */

#include "AccountingRuleCreditAccount.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlAccounting;

const std::string AccountingRuleCreditAccount::Cols::_id = "\"id\"";
const std::string AccountingRuleCreditAccount::Cols::_rule_id = "\"rule_id\"";
const std::string AccountingRuleCreditAccount::Cols::_account_id = "\"account_id\"";
const std::string AccountingRuleCreditAccount::primaryKeyName = "id";
const bool AccountingRuleCreditAccount::hasPrimaryKey = true;
const std::string AccountingRuleCreditAccount::tableName = "\"accounting_rule_credit_accounts\"";

const std::vector<typename AccountingRuleCreditAccount::MetaData> AccountingRuleCreditAccount::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"rule_id","std::string","uuid",0,0,0,1},
{"account_id","std::string","uuid",0,0,0,1}
};
const std::string &AccountingRuleCreditAccount::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
AccountingRuleCreditAccount::AccountingRuleCreditAccount(const Row &r, const ssize_t indexOffset) noexcept
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
const std::string &AccountingRuleCreditAccount::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRuleCreditAccount::getId() const noexcept
{
    return id_;
}
void AccountingRuleCreditAccount::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void AccountingRuleCreditAccount::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename AccountingRuleCreditAccount::PrimaryKeyType & AccountingRuleCreditAccount::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &AccountingRuleCreditAccount::getValueOfRuleId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(ruleId_)
        return *ruleId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRuleCreditAccount::getRuleId() const noexcept
{
    return ruleId_;
}
void AccountingRuleCreditAccount::setRuleId(const std::string &pRuleId) noexcept
{
    ruleId_ = std::make_shared<std::string>(pRuleId);
    dirtyFlag_[1] = true;
}
void AccountingRuleCreditAccount::setRuleId(std::string &&pRuleId) noexcept
{
    ruleId_ = std::make_shared<std::string>(std::move(pRuleId));
    dirtyFlag_[1] = true;
}

const std::string &AccountingRuleCreditAccount::getValueOfAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountId_)
        return *accountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &AccountingRuleCreditAccount::getAccountId() const noexcept
{
    return accountId_;
}
void AccountingRuleCreditAccount::setAccountId(const std::string &pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(pAccountId);
    dirtyFlag_[2] = true;
}
void AccountingRuleCreditAccount::setAccountId(std::string &&pAccountId) noexcept
{
    accountId_ = std::make_shared<std::string>(std::move(pAccountId));
    dirtyFlag_[2] = true;
}

void AccountingRuleCreditAccount::updateId(const uint64_t id)
{
}

const std::vector<std::string> &AccountingRuleCreditAccount::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "rule_id",
        "account_id"
    };
    return inCols;
}

void AccountingRuleCreditAccount::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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

const std::vector<std::string> AccountingRuleCreditAccount::updateColumns() const
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

void AccountingRuleCreditAccount::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
