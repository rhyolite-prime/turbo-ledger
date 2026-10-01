/**
 *  LoanproductProvisioningEntry.cc
 *
 *  See LoanproductProvisioningEntry.h for the hand-authored-subset note.
 *
 */

#include "LoanproductProvisioningEntry.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanproductProvisioningEntry::Cols::_id = "\"id\"";
const std::string LoanproductProvisioningEntry::Cols::_history_id = "\"history_id\"";
const std::string LoanproductProvisioningEntry::Cols::_criteria_id = "\"criteria_id\"";
const std::string LoanproductProvisioningEntry::Cols::_currency_code = "\"currency_code\"";
const std::string LoanproductProvisioningEntry::Cols::_office_id = "\"office_id\"";
const std::string LoanproductProvisioningEntry::Cols::_product_id = "\"product_id\"";
const std::string LoanproductProvisioningEntry::Cols::_category_id = "\"category_id\"";
const std::string LoanproductProvisioningEntry::Cols::_overdue_in_days = "\"overdue_in_days\"";
const std::string LoanproductProvisioningEntry::Cols::_reseve_amount = "\"reseve_amount\"";
const std::string LoanproductProvisioningEntry::Cols::_liability_account = "\"liability_account\"";
const std::string LoanproductProvisioningEntry::Cols::_expense_account = "\"expense_account\"";
const std::string LoanproductProvisioningEntry::primaryKeyName = "id";
const bool LoanproductProvisioningEntry::hasPrimaryKey = true;
const std::string LoanproductProvisioningEntry::tableName = "\"loanproduct_provisioning_entry\"";

const std::vector<typename LoanproductProvisioningEntry::MetaData> LoanproductProvisioningEntry::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"history_id","std::string","uuid",0,0,0,1},
{"criteria_id","std::string","uuid",0,0,0,1},
{"currency_code","std::string","character varying",3,0,0,1},
{"office_id","std::string","uuid",0,0,0,1},
{"product_id","std::string","uuid",0,0,0,1},
{"category_id","std::string","uuid",0,0,0,1},
{"overdue_in_days","int64_t","bigint",8,0,0,0},
{"reseve_amount","std::string","numeric",0,0,0,0},
{"liability_account","std::string","uuid",0,0,0,0},
{"expense_account","std::string","uuid",0,0,0,0}
};
const std::string &LoanproductProvisioningEntry::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanproductProvisioningEntry::LoanproductProvisioningEntry(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["history_id"].isNull())
        {
            historyId_=std::make_shared<std::string>(r["history_id"].as<std::string>());
        }
        if(!r["criteria_id"].isNull())
        {
            criteriaId_=std::make_shared<std::string>(r["criteria_id"].as<std::string>());
        }
        if(!r["currency_code"].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r["currency_code"].as<std::string>());
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["product_id"].isNull())
        {
            productId_=std::make_shared<std::string>(r["product_id"].as<std::string>());
        }
        if(!r["category_id"].isNull())
        {
            categoryId_=std::make_shared<std::string>(r["category_id"].as<std::string>());
        }
        if(!r["overdue_in_days"].isNull())
        {
            overdueInDays_=std::make_shared<int64_t>(r["overdue_in_days"].as<int64_t>());
        }
        if(!r["reseve_amount"].isNull())
        {
            reseveAmount_=std::make_shared<std::string>(r["reseve_amount"].as<std::string>());
        }
        if(!r["liability_account"].isNull())
        {
            liabilityAccount_=std::make_shared<std::string>(r["liability_account"].as<std::string>());
        }
        if(!r["expense_account"].isNull())
        {
            expenseAccount_=std::make_shared<std::string>(r["expense_account"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 11 > r.size())
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
            historyId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            criteriaId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            currencyCode_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            productId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            categoryId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            overdueInDays_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            reseveAmount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            liabilityAccount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            expenseAccount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}
const std::string &LoanproductProvisioningEntry::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getId() const noexcept
{
    return id_;
}
void LoanproductProvisioningEntry::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanproductProvisioningEntry::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanproductProvisioningEntry::PrimaryKeyType & LoanproductProvisioningEntry::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanproductProvisioningEntry::getValueOfHistoryId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(historyId_)
        return *historyId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getHistoryId() const noexcept
{
    return historyId_;
}
void LoanproductProvisioningEntry::setHistoryId(const std::string &pHistoryId) noexcept
{
    historyId_ = std::make_shared<std::string>(pHistoryId);
    dirtyFlag_[1] = true;
}
void LoanproductProvisioningEntry::setHistoryId(std::string &&pHistoryId) noexcept
{
    historyId_ = std::make_shared<std::string>(std::move(pHistoryId));
    dirtyFlag_[1] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfCriteriaId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(criteriaId_)
        return *criteriaId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getCriteriaId() const noexcept
{
    return criteriaId_;
}
void LoanproductProvisioningEntry::setCriteriaId(const std::string &pCriteriaId) noexcept
{
    criteriaId_ = std::make_shared<std::string>(pCriteriaId);
    dirtyFlag_[2] = true;
}
void LoanproductProvisioningEntry::setCriteriaId(std::string &&pCriteriaId) noexcept
{
    criteriaId_ = std::make_shared<std::string>(std::move(pCriteriaId));
    dirtyFlag_[2] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfCurrencyCode() const noexcept
{
    static const std::string defaultValue = std::string();
    if(currencyCode_)
        return *currencyCode_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getCurrencyCode() const noexcept
{
    return currencyCode_;
}
void LoanproductProvisioningEntry::setCurrencyCode(const std::string &pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(pCurrencyCode);
    dirtyFlag_[3] = true;
}
void LoanproductProvisioningEntry::setCurrencyCode(std::string &&pCurrencyCode) noexcept
{
    currencyCode_ = std::make_shared<std::string>(std::move(pCurrencyCode));
    dirtyFlag_[3] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getOfficeId() const noexcept
{
    return officeId_;
}
void LoanproductProvisioningEntry::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[4] = true;
}
void LoanproductProvisioningEntry::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[4] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(productId_)
        return *productId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getProductId() const noexcept
{
    return productId_;
}
void LoanproductProvisioningEntry::setProductId(const std::string &pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(pProductId);
    dirtyFlag_[5] = true;
}
void LoanproductProvisioningEntry::setProductId(std::string &&pProductId) noexcept
{
    productId_ = std::make_shared<std::string>(std::move(pProductId));
    dirtyFlag_[5] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfCategoryId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(categoryId_)
        return *categoryId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getCategoryId() const noexcept
{
    return categoryId_;
}
void LoanproductProvisioningEntry::setCategoryId(const std::string &pCategoryId) noexcept
{
    categoryId_ = std::make_shared<std::string>(pCategoryId);
    dirtyFlag_[6] = true;
}
void LoanproductProvisioningEntry::setCategoryId(std::string &&pCategoryId) noexcept
{
    categoryId_ = std::make_shared<std::string>(std::move(pCategoryId));
    dirtyFlag_[6] = true;
}

const int64_t &LoanproductProvisioningEntry::getValueOfOverdueInDays() const noexcept
{
    static const int64_t defaultValue = int64_t();
    if(overdueInDays_)
        return *overdueInDays_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &LoanproductProvisioningEntry::getOverdueInDays() const noexcept
{
    return overdueInDays_;
}
void LoanproductProvisioningEntry::setOverdueInDays(const int64_t &pOverdueInDays) noexcept
{
    overdueInDays_ = std::make_shared<int64_t>(pOverdueInDays);
    dirtyFlag_[7] = true;
}
void LoanproductProvisioningEntry::setOverdueInDaysToNull() noexcept
{
    overdueInDays_.reset();
    dirtyFlag_[7] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfReseveAmount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reseveAmount_)
        return *reseveAmount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getReseveAmount() const noexcept
{
    return reseveAmount_;
}
void LoanproductProvisioningEntry::setReseveAmount(const std::string &pReseveAmount) noexcept
{
    reseveAmount_ = std::make_shared<std::string>(pReseveAmount);
    dirtyFlag_[8] = true;
}
void LoanproductProvisioningEntry::setReseveAmount(std::string &&pReseveAmount) noexcept
{
    reseveAmount_ = std::make_shared<std::string>(std::move(pReseveAmount));
    dirtyFlag_[8] = true;
}
void LoanproductProvisioningEntry::setReseveAmountToNull() noexcept
{
    reseveAmount_.reset();
    dirtyFlag_[8] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfLiabilityAccount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(liabilityAccount_)
        return *liabilityAccount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getLiabilityAccount() const noexcept
{
    return liabilityAccount_;
}
void LoanproductProvisioningEntry::setLiabilityAccount(const std::string &pLiabilityAccount) noexcept
{
    liabilityAccount_ = std::make_shared<std::string>(pLiabilityAccount);
    dirtyFlag_[9] = true;
}
void LoanproductProvisioningEntry::setLiabilityAccount(std::string &&pLiabilityAccount) noexcept
{
    liabilityAccount_ = std::make_shared<std::string>(std::move(pLiabilityAccount));
    dirtyFlag_[9] = true;
}
void LoanproductProvisioningEntry::setLiabilityAccountToNull() noexcept
{
    liabilityAccount_.reset();
    dirtyFlag_[9] = true;
}

const std::string &LoanproductProvisioningEntry::getValueOfExpenseAccount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(expenseAccount_)
        return *expenseAccount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanproductProvisioningEntry::getExpenseAccount() const noexcept
{
    return expenseAccount_;
}
void LoanproductProvisioningEntry::setExpenseAccount(const std::string &pExpenseAccount) noexcept
{
    expenseAccount_ = std::make_shared<std::string>(pExpenseAccount);
    dirtyFlag_[10] = true;
}
void LoanproductProvisioningEntry::setExpenseAccount(std::string &&pExpenseAccount) noexcept
{
    expenseAccount_ = std::make_shared<std::string>(std::move(pExpenseAccount));
    dirtyFlag_[10] = true;
}
void LoanproductProvisioningEntry::setExpenseAccountToNull() noexcept
{
    expenseAccount_.reset();
    dirtyFlag_[10] = true;
}

void LoanproductProvisioningEntry::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanproductProvisioningEntry::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "history_id",
        "criteria_id",
        "currency_code",
        "office_id",
        "product_id",
        "category_id",
        "overdue_in_days",
        "reseve_amount",
        "liability_account",
        "expense_account"
    };
    return inCols;
}

void LoanproductProvisioningEntry::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getHistoryId())
        {
            binder << getValueOfHistoryId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getProductId())
        {
            binder << getValueOfProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getOverdueInDays())
        {
            binder << getValueOfOverdueInDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getReseveAmount())
        {
            binder << getValueOfReseveAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getLiabilityAccount())
        {
            binder << getValueOfLiabilityAccount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getExpenseAccount())
        {
            binder << getValueOfExpenseAccount();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> LoanproductProvisioningEntry::updateColumns() const
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
    return ret;
}

void LoanproductProvisioningEntry::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getHistoryId())
        {
            binder << getValueOfHistoryId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
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
    if(dirtyFlag_[4])
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
    if(dirtyFlag_[5])
    {
        if(getProductId())
        {
            binder << getValueOfProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
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
    if(dirtyFlag_[7])
    {
        if(getOverdueInDays())
        {
            binder << getValueOfOverdueInDays();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getReseveAmount())
        {
            binder << getValueOfReseveAmount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getLiabilityAccount())
        {
            binder << getValueOfLiabilityAccount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getExpenseAccount())
        {
            binder << getValueOfExpenseAccount();
        }
        else
        {
            binder << nullptr;
        }
    }
}
