/**
 *  ProvisioningCriteriaDefinition.cc
 *
 *  See ProvisioningCriteriaDefinition.h for the hand-authored-subset note.
 *
 */

#include "ProvisioningCriteriaDefinition.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string ProvisioningCriteriaDefinition::Cols::_id = "\"id\"";
const std::string ProvisioningCriteriaDefinition::Cols::_criteria_id = "\"criteria_id\"";
const std::string ProvisioningCriteriaDefinition::Cols::_category_id = "\"category_id\"";
const std::string ProvisioningCriteriaDefinition::Cols::_min_overdue_days = "\"min_overdue_days\"";
const std::string ProvisioningCriteriaDefinition::Cols::_max_overdue_days = "\"max_overdue_days\"";
const std::string ProvisioningCriteriaDefinition::Cols::_provisioning_percentage = "\"provisioning_percentage\"";
const std::string ProvisioningCriteriaDefinition::Cols::_liability_account_id = "\"liability_account_id\"";
const std::string ProvisioningCriteriaDefinition::Cols::_expense_account_id = "\"expense_account_id\"";
const std::string ProvisioningCriteriaDefinition::primaryKeyName = "id";
const bool ProvisioningCriteriaDefinition::hasPrimaryKey = true;
const std::string ProvisioningCriteriaDefinition::tableName = "\"provisioning_criteria_definition\"";

const std::vector<typename ProvisioningCriteriaDefinition::MetaData> ProvisioningCriteriaDefinition::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"criteria_id","std::string","uuid",0,0,0,1},
{"category_id","std::string","uuid",0,0,0,1},
{"min_overdue_days","int32_t","integer",4,0,0,1},
{"max_overdue_days","int32_t","integer",4,0,0,0},
{"provisioning_percentage","std::string","numeric",0,0,0,1},
{"liability_account_id","std::string","uuid",0,0,0,0},
{"expense_account_id","std::string","uuid",0,0,0,0}
};
const std::string &ProvisioningCriteriaDefinition::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
ProvisioningCriteriaDefinition::ProvisioningCriteriaDefinition(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["criteria_id"].isNull())
        {
            criteriaId_=std::make_shared<std::string>(r["criteria_id"].as<std::string>());
        }
        if(!r["category_id"].isNull())
        {
            categoryId_=std::make_shared<std::string>(r["category_id"].as<std::string>());
        }
        if(!r["min_overdue_days"].isNull())
        {
            minOverdueDays_=std::make_shared<int32_t>(r["min_overdue_days"].as<int32_t>());
        }
        if(!r["max_overdue_days"].isNull())
        {
            maxOverdueDays_=std::make_shared<int32_t>(r["max_overdue_days"].as<int32_t>());
        }
        if(!r["provisioning_percentage"].isNull())
        {
            provisioningPercentage_=std::make_shared<std::string>(r["provisioning_percentage"].as<std::string>());
        }
        if(!r["liability_account_id"].isNull())
        {
            liabilityAccountId_=std::make_shared<std::string>(r["liability_account_id"].as<std::string>());
        }
        if(!r["expense_account_id"].isNull())
        {
            expenseAccountId_=std::make_shared<std::string>(r["expense_account_id"].as<std::string>());
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
            criteriaId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            categoryId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            minOverdueDays_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            maxOverdueDays_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            provisioningPercentage_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            liabilityAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            expenseAccountId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &ProvisioningCriteriaDefinition::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCriteriaDefinition::getId() const noexcept
{
    return id_;
}
void ProvisioningCriteriaDefinition::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void ProvisioningCriteriaDefinition::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename ProvisioningCriteriaDefinition::PrimaryKeyType & ProvisioningCriteriaDefinition::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &ProvisioningCriteriaDefinition::getValueOfCriteriaId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(criteriaId_)
        return *criteriaId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCriteriaDefinition::getCriteriaId() const noexcept
{
    return criteriaId_;
}
void ProvisioningCriteriaDefinition::setCriteriaId(const std::string &pCriteriaId) noexcept
{
    criteriaId_ = std::make_shared<std::string>(pCriteriaId);
    dirtyFlag_[1] = true;
}
void ProvisioningCriteriaDefinition::setCriteriaId(std::string &&pCriteriaId) noexcept
{
    criteriaId_ = std::make_shared<std::string>(std::move(pCriteriaId));
    dirtyFlag_[1] = true;
}

const std::string &ProvisioningCriteriaDefinition::getValueOfCategoryId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(categoryId_)
        return *categoryId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCriteriaDefinition::getCategoryId() const noexcept
{
    return categoryId_;
}
void ProvisioningCriteriaDefinition::setCategoryId(const std::string &pCategoryId) noexcept
{
    categoryId_ = std::make_shared<std::string>(pCategoryId);
    dirtyFlag_[2] = true;
}
void ProvisioningCriteriaDefinition::setCategoryId(std::string &&pCategoryId) noexcept
{
    categoryId_ = std::make_shared<std::string>(std::move(pCategoryId));
    dirtyFlag_[2] = true;
}

const int32_t &ProvisioningCriteriaDefinition::getValueOfMinOverdueDays() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(minOverdueDays_)
        return *minOverdueDays_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ProvisioningCriteriaDefinition::getMinOverdueDays() const noexcept
{
    return minOverdueDays_;
}
void ProvisioningCriteriaDefinition::setMinOverdueDays(const int32_t &pMinOverdueDays) noexcept
{
    minOverdueDays_ = std::make_shared<int32_t>(pMinOverdueDays);
    dirtyFlag_[3] = true;
}

const int32_t &ProvisioningCriteriaDefinition::getValueOfMaxOverdueDays() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(maxOverdueDays_)
        return *maxOverdueDays_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ProvisioningCriteriaDefinition::getMaxOverdueDays() const noexcept
{
    return maxOverdueDays_;
}
void ProvisioningCriteriaDefinition::setMaxOverdueDays(const int32_t &pMaxOverdueDays) noexcept
{
    maxOverdueDays_ = std::make_shared<int32_t>(pMaxOverdueDays);
    dirtyFlag_[4] = true;
}
void ProvisioningCriteriaDefinition::setMaxOverdueDaysToNull() noexcept
{
    maxOverdueDays_.reset();
    dirtyFlag_[4] = true;
}

const std::string &ProvisioningCriteriaDefinition::getValueOfProvisioningPercentage() const noexcept
{
    static const std::string defaultValue = std::string();
    if(provisioningPercentage_)
        return *provisioningPercentage_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCriteriaDefinition::getProvisioningPercentage() const noexcept
{
    return provisioningPercentage_;
}
void ProvisioningCriteriaDefinition::setProvisioningPercentage(const std::string &pProvisioningPercentage) noexcept
{
    provisioningPercentage_ = std::make_shared<std::string>(pProvisioningPercentage);
    dirtyFlag_[5] = true;
}
void ProvisioningCriteriaDefinition::setProvisioningPercentage(std::string &&pProvisioningPercentage) noexcept
{
    provisioningPercentage_ = std::make_shared<std::string>(std::move(pProvisioningPercentage));
    dirtyFlag_[5] = true;
}

const std::string &ProvisioningCriteriaDefinition::getValueOfLiabilityAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(liabilityAccountId_)
        return *liabilityAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCriteriaDefinition::getLiabilityAccountId() const noexcept
{
    return liabilityAccountId_;
}
void ProvisioningCriteriaDefinition::setLiabilityAccountId(const std::string &pLiabilityAccountId) noexcept
{
    liabilityAccountId_ = std::make_shared<std::string>(pLiabilityAccountId);
    dirtyFlag_[6] = true;
}
void ProvisioningCriteriaDefinition::setLiabilityAccountId(std::string &&pLiabilityAccountId) noexcept
{
    liabilityAccountId_ = std::make_shared<std::string>(std::move(pLiabilityAccountId));
    dirtyFlag_[6] = true;
}
void ProvisioningCriteriaDefinition::setLiabilityAccountIdToNull() noexcept
{
    liabilityAccountId_.reset();
    dirtyFlag_[6] = true;
}

const std::string &ProvisioningCriteriaDefinition::getValueOfExpenseAccountId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(expenseAccountId_)
        return *expenseAccountId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &ProvisioningCriteriaDefinition::getExpenseAccountId() const noexcept
{
    return expenseAccountId_;
}
void ProvisioningCriteriaDefinition::setExpenseAccountId(const std::string &pExpenseAccountId) noexcept
{
    expenseAccountId_ = std::make_shared<std::string>(pExpenseAccountId);
    dirtyFlag_[7] = true;
}
void ProvisioningCriteriaDefinition::setExpenseAccountId(std::string &&pExpenseAccountId) noexcept
{
    expenseAccountId_ = std::make_shared<std::string>(std::move(pExpenseAccountId));
    dirtyFlag_[7] = true;
}
void ProvisioningCriteriaDefinition::setExpenseAccountIdToNull() noexcept
{
    expenseAccountId_.reset();
    dirtyFlag_[7] = true;
}

void ProvisioningCriteriaDefinition::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ProvisioningCriteriaDefinition::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "criteria_id",
        "category_id",
        "min_overdue_days",
        "max_overdue_days",
        "provisioning_percentage",
        "liability_account_id",
        "expense_account_id"
    };
    return inCols;
}

void ProvisioningCriteriaDefinition::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCriteriaId())
        {
            binder << getValueOfCriteriaId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCategoryId())
        {
            binder << getValueOfCategoryId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMinOverdueDays())
        {
            binder << getValueOfMinOverdueDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getMaxOverdueDays())
        {
            binder << getValueOfMaxOverdueDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getProvisioningPercentage())
        {
            binder << getValueOfProvisioningPercentage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getLiabilityAccountId())
        {
            binder << getValueOfLiabilityAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getExpenseAccountId())
        {
            binder << getValueOfExpenseAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> ProvisioningCriteriaDefinition::updateColumns() const
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

void ProvisioningCriteriaDefinition::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getCriteriaId())
        {
            binder << getValueOfCriteriaId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCategoryId())
        {
            binder << getValueOfCategoryId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getMinOverdueDays())
        {
            binder << getValueOfMinOverdueDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getMaxOverdueDays())
        {
            binder << getValueOfMaxOverdueDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getProvisioningPercentage())
        {
            binder << getValueOfProvisioningPercentage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getLiabilityAccountId())
        {
            binder << getValueOfLiabilityAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getExpenseAccountId())
        {
            binder << getValueOfExpenseAccountId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
