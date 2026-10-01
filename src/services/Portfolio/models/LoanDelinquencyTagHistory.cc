/**
 *  LoanDelinquencyTagHistory.cc
 *
 *  See LoanDelinquencyTagHistory.h for the hand-authored-subset note.
 *
 */

#include "LoanDelinquencyTagHistory.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlPortfolioDb;

const std::string LoanDelinquencyTagHistory::Cols::_id = "\"id\"";
const std::string LoanDelinquencyTagHistory::Cols::_loan_id = "\"loan_id\"";
const std::string LoanDelinquencyTagHistory::Cols::_delinquency_range_id = "\"delinquency_range_id\"";
const std::string LoanDelinquencyTagHistory::Cols::_classification_date = "\"classification_date\"";
const std::string LoanDelinquencyTagHistory::Cols::_liftoff_date = "\"liftoff_date\"";
const std::string LoanDelinquencyTagHistory::Cols::_created_at = "\"created_at\"";
const std::string LoanDelinquencyTagHistory::primaryKeyName = "id";
const bool LoanDelinquencyTagHistory::hasPrimaryKey = true;
const std::string LoanDelinquencyTagHistory::tableName = "\"loan_delinquency_tag_history\"";

const std::vector<typename LoanDelinquencyTagHistory::MetaData> LoanDelinquencyTagHistory::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"loan_id","std::string","uuid",0,0,0,1},
{"delinquency_range_id","std::string","uuid",0,0,0,1},
{"classification_date","::trantor::Date","date",0,0,0,1},
{"liftoff_date","::trantor::Date","date",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,1}
};
const std::string &LoanDelinquencyTagHistory::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
LoanDelinquencyTagHistory::LoanDelinquencyTagHistory(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["loan_id"].isNull())
        {
            loanId_=std::make_shared<std::string>(r["loan_id"].as<std::string>());
        }
        if(!r["delinquency_range_id"].isNull())
        {
            delinquencyRangeId_=std::make_shared<std::string>(r["delinquency_range_id"].as<std::string>());
        }
        if(!r["classification_date"].isNull())
        {
            auto daysStr = r["classification_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            classificationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["liftoff_date"].isNull())
        {
            auto daysStr = r["liftoff_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            liftoffDate_=std::make_shared<::trantor::Date>(t*1000000);
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
            loanId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            delinquencyRangeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            classificationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            liftoffDate_=std::make_shared<::trantor::Date>(t*1000000);
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
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}
const std::string &LoanDelinquencyTagHistory::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanDelinquencyTagHistory::getId() const noexcept
{
    return id_;
}
void LoanDelinquencyTagHistory::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void LoanDelinquencyTagHistory::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename LoanDelinquencyTagHistory::PrimaryKeyType & LoanDelinquencyTagHistory::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &LoanDelinquencyTagHistory::getValueOfLoanId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(loanId_)
        return *loanId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanDelinquencyTagHistory::getLoanId() const noexcept
{
    return loanId_;
}
void LoanDelinquencyTagHistory::setLoanId(const std::string &pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(pLoanId);
    dirtyFlag_[1] = true;
}
void LoanDelinquencyTagHistory::setLoanId(std::string &&pLoanId) noexcept
{
    loanId_ = std::make_shared<std::string>(std::move(pLoanId));
    dirtyFlag_[1] = true;
}

const std::string &LoanDelinquencyTagHistory::getValueOfDelinquencyRangeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(delinquencyRangeId_)
        return *delinquencyRangeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &LoanDelinquencyTagHistory::getDelinquencyRangeId() const noexcept
{
    return delinquencyRangeId_;
}
void LoanDelinquencyTagHistory::setDelinquencyRangeId(const std::string &pDelinquencyRangeId) noexcept
{
    delinquencyRangeId_ = std::make_shared<std::string>(pDelinquencyRangeId);
    dirtyFlag_[2] = true;
}
void LoanDelinquencyTagHistory::setDelinquencyRangeId(std::string &&pDelinquencyRangeId) noexcept
{
    delinquencyRangeId_ = std::make_shared<std::string>(std::move(pDelinquencyRangeId));
    dirtyFlag_[2] = true;
}

const ::trantor::Date &LoanDelinquencyTagHistory::getValueOfClassificationDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(classificationDate_)
        return *classificationDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanDelinquencyTagHistory::getClassificationDate() const noexcept
{
    return classificationDate_;
}
void LoanDelinquencyTagHistory::setClassificationDate(const ::trantor::Date &pClassificationDate) noexcept
{
    classificationDate_ = std::make_shared<::trantor::Date>(pClassificationDate);
    dirtyFlag_[3] = true;
}

const ::trantor::Date &LoanDelinquencyTagHistory::getValueOfLiftoffDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(liftoffDate_)
        return *liftoffDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanDelinquencyTagHistory::getLiftoffDate() const noexcept
{
    return liftoffDate_;
}
void LoanDelinquencyTagHistory::setLiftoffDate(const ::trantor::Date &pLiftoffDate) noexcept
{
    liftoffDate_ = std::make_shared<::trantor::Date>(pLiftoffDate);
    dirtyFlag_[4] = true;
}
void LoanDelinquencyTagHistory::setLiftoffDateToNull() noexcept
{
    liftoffDate_.reset();
    dirtyFlag_[4] = true;
}

const ::trantor::Date &LoanDelinquencyTagHistory::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LoanDelinquencyTagHistory::getCreatedAt() const noexcept
{
    return createdAt_;
}
void LoanDelinquencyTagHistory::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[5] = true;
}

void LoanDelinquencyTagHistory::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LoanDelinquencyTagHistory::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "loan_id",
        "delinquency_range_id",
        "classification_date",
        "liftoff_date",
        "created_at"
    };
    return inCols;
}

void LoanDelinquencyTagHistory::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDelinquencyRangeId())
        {
            binder << getValueOfDelinquencyRangeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getClassificationDate())
        {
            binder << getValueOfClassificationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getLiftoffDate())
        {
            binder << getValueOfLiftoffDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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

const std::vector<std::string> LoanDelinquencyTagHistory::updateColumns() const
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

void LoanDelinquencyTagHistory::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getLoanId())
        {
            binder << getValueOfLoanId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDelinquencyRangeId())
        {
            binder << getValueOfDelinquencyRangeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getClassificationDate())
        {
            binder << getValueOfClassificationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getLiftoffDate())
        {
            binder << getValueOfLiftoffDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
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
