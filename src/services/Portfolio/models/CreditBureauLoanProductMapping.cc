/**
 *  CreditBureauLoanProductMapping.cc
 *
 *  See CreditBureauLoanProductMapping.h for the hand-authored-subset note.
 *
 */

#include "CreditBureauLoanProductMapping.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string CreditBureauLoanProductMapping::Cols::_id = "\"id\"";
const std::string CreditBureauLoanProductMapping::Cols::_organisation_credit_bureau_id = "\"organisation_credit_bureau_id\"";
const std::string CreditBureauLoanProductMapping::Cols::_loan_product_id = "\"loan_product_id\"";
const std::string CreditBureauLoanProductMapping::Cols::_is_active = "\"is_active\"";
const std::string CreditBureauLoanProductMapping::primaryKeyName = "id";
const bool CreditBureauLoanProductMapping::hasPrimaryKey = true;
const std::string CreditBureauLoanProductMapping::tableName = "\"credit_bureau_loan_product_mapping\"";

const std::vector<typename CreditBureauLoanProductMapping::MetaData> CreditBureauLoanProductMapping::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"organisation_credit_bureau_id","std::string","uuid",0,0,0,1},
{"loan_product_id","std::string","uuid",0,0,0,1},
{"is_active","bool","boolean",1,0,0,1}
};
const std::string &CreditBureauLoanProductMapping::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
CreditBureauLoanProductMapping::CreditBureauLoanProductMapping(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["organisation_credit_bureau_id"].isNull())
        {
            organisationCreditBureauId_=std::make_shared<std::string>(r["organisation_credit_bureau_id"].as<std::string>());
        }
        if(!r["loan_product_id"].isNull())
        {
            loanProductId_=std::make_shared<std::string>(r["loan_product_id"].as<std::string>());
        }
        if(!r["is_active"].isNull())
        {
            isActive_=std::make_shared<bool>(r["is_active"].as<bool>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 4 > r.size())
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
            organisationCreditBureauId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            loanProductId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            isActive_=std::make_shared<bool>(r[index].as<bool>());
        }
    }

}
const std::string &CreditBureauLoanProductMapping::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauLoanProductMapping::getId() const noexcept
{
    return id_;
}
void CreditBureauLoanProductMapping::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void CreditBureauLoanProductMapping::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename CreditBureauLoanProductMapping::PrimaryKeyType & CreditBureauLoanProductMapping::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &CreditBureauLoanProductMapping::getValueOfOrganisationCreditBureauId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(organisationCreditBureauId_)
        return *organisationCreditBureauId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauLoanProductMapping::getOrganisationCreditBureauId() const noexcept
{
    return organisationCreditBureauId_;
}
void CreditBureauLoanProductMapping::setOrganisationCreditBureauId(const std::string &pOrganisationCreditBureauId) noexcept
{
    organisationCreditBureauId_ = std::make_shared<std::string>(pOrganisationCreditBureauId);
    dirtyFlag_[1] = true;
}
void CreditBureauLoanProductMapping::setOrganisationCreditBureauId(std::string &&pOrganisationCreditBureauId) noexcept
{
    organisationCreditBureauId_ = std::make_shared<std::string>(std::move(pOrganisationCreditBureauId));
    dirtyFlag_[1] = true;
}

const std::string &CreditBureauLoanProductMapping::getValueOfLoanProductId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanProductId_)
        return *loanProductId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &CreditBureauLoanProductMapping::getLoanProductId() const noexcept
{
    return loanProductId_;
}
void CreditBureauLoanProductMapping::setLoanProductId(const std::string &pLoanProductId) noexcept
{
    loanProductId_ = std::make_shared<std::string>(pLoanProductId);
    dirtyFlag_[2] = true;
}
void CreditBureauLoanProductMapping::setLoanProductId(std::string &&pLoanProductId) noexcept
{
    loanProductId_ = std::make_shared<std::string>(std::move(pLoanProductId));
    dirtyFlag_[2] = true;
}

const bool &CreditBureauLoanProductMapping::getValueOfIsActive() const noexcept
{
    static const bool defaultValue = bool();
    if(isActive_)
        return *isActive_;
    return defaultValue;
}
const std::shared_ptr<bool> &CreditBureauLoanProductMapping::getIsActive() const noexcept
{
    return isActive_;
}
void CreditBureauLoanProductMapping::setIsActive(const bool &pIsActive) noexcept
{
    isActive_ = std::make_shared<bool>(pIsActive);
    dirtyFlag_[3] = true;
}

void CreditBureauLoanProductMapping::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CreditBureauLoanProductMapping::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "organisation_credit_bureau_id",
        "loan_product_id",
        "is_active"
    };
    return inCols;
}

void CreditBureauLoanProductMapping::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOrganisationCreditBureauId())
        {
            binder << getValueOfOrganisationCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getLoanProductId())
        {
            binder << getValueOfLoanProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
}

const std::vector<std::string> CreditBureauLoanProductMapping::updateColumns() const
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
    return ret;
}

void CreditBureauLoanProductMapping::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getOrganisationCreditBureauId())
        {
            binder << getValueOfOrganisationCreditBureauId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getLoanProductId())
        {
            binder << getValueOfLoanProductId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
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
}
