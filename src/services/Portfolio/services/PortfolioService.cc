#include "PortfolioService.h"

#include <drogon/orm/CoroMapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <map>
#include <sstream>

#include "turbo/Ids.h"
#include "turbo/Money.h"
#include "turbo/Outbox.h"
#include "turbo/Pagination.h"
#include "turbo/TenantDb.h"

#include "models/CreditBureau.h"
#include "models/CreditBureauConfiguration.h"
#include "models/CreditBureauLoanProductMapping.h"
#include "models/CreditBureauReport.h"
#include "models/DelinquencyBucket.h"
#include "models/DelinquencyBucketRange.h"
#include "models/DelinquencyRange.h"
#include "models/ExternalAssetOwner.h"
#include "models/FloatingRate.h"
#include "models/FloatingRatePeriod.h"
#include "models/Loan.h"
#include "models/LoanBuydownFee.h"
#include "models/LoanCapitalizedIncome.h"
#include "models/LoanCharge.h"
#include "models/LoanCollateral.h"
#include "models/LoanDelinquencyAction.h"
#include "models/LoanDelinquencyTagHistory.h"
#include "models/LoanDisbursementDetail.h"
#include "models/LoanGuarantor.h"
#include "models/LoanInterestPause.h"
#include "models/LoanOwnerTransfer.h"
#include "models/LoanOwnerTransferJournalEntry.h"
#include "models/LoanPostdatedCheck.h"
#include "models/LoanProduct.h"
#include "models/LoanProductAttribute.h"
#include "models/LoanProductCharge.h"
#include "models/LoanProductMix.h"
#include "models/LoanRepaymentScheduleInstallment.h"
#include "models/LoanTransaction.h"
#include "models/LoanproductProvisioningEntry.h"
#include "models/OrganisationCreditBureau.h"
#include "models/ProvisioningCategory.h"
#include "models/ProvisioningCriteria.h"
#include "models/ProvisioningCriteriaDefinition.h"
#include "models/ProvisioningHistory.h"
#include "models/Rate.h"
#include "models/RescheduleLoanRequest.h"
#include "models/ShareAccount.h"
#include "models/ShareAccountCharge.h"
#include "models/ShareProduct.h"
#include "models/ShareProductCharge.h"
#include "models/ShareProductDividend.h"
#include "models/SharePurchaseRequest.h"

using drogon::orm::CompareOperator;
using drogon::orm::Criteria;
using drogon::orm::DrogonDbException;
using drogon::orm::SortOrder;
using drogon::orm::UnexpectedRows;
using trantor::Date;

namespace turbo_ledger_portfolio {

namespace m = drogon_model::TlPortfolioDb;
template <typename T>
using Mapper = drogon::orm::CoroMapper<T>;

// -----------------------------------------------------------------------------
// NOTE on ORM coverage: every table here is a hand-authored model generated
// by src/tools/gen_portfolio_models.py (which drives genmodel.py — see that
// file's docstring) against the hand-designed V003__phase6.sql schema (plus
// the two genuine ground-truth tables from V001__baseline.sql). There is no
// raw SQL in this file; all access goes through CoroMapper<Model>.
// -----------------------------------------------------------------------------

namespace {

constexpr const char *kZeroUuid = "00000000-0000-0000-0000-000000000000";

Date dateOr(const std::string &text, const Date &fallback) {
    if (text.empty()) return fallback;
    return Date::fromDbStringLocal(text.size() == 10 ? text + " 00:00:00" : text);
}
std::string dateStr(const Date &d) { return d.toDbStringLocal().substr(0, 10); }

std::string jsonCompact(const Json::Value &v) {
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    return Json::writeString(builder, v);
}
Json::Value parseJsonOrEmpty(const std::string &text, Json::ValueType fallbackType = Json::objectValue) {
    Json::Value out(fallbackType);
    if (text.empty()) return out;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream stream(text);
    Json::Value parsed;
    if (Json::parseFromStream(builder, stream, &parsed, &errs)) return parsed;
    return out;
}

std::string asStringOr(const Json::Value &v, const char *key, const std::string &fallback = "") {
    return v.isMember(key) && !v[key].isNull() ? v[key].asString() : fallback;
}
bool asBoolOr(const Json::Value &v, const char *key, bool fallback) {
    if (!v.isMember(key) || v[key].isNull()) return fallback;
    if (v[key].isBool()) return v[key].asBool();
    if (v[key].isString()) return v[key].asString() == "true";
    return fallback;
}
int asIntOr(const Json::Value &v, const char *key, int fallback) {
    return v.isMember(key) && v[key].isNumeric() ? v[key].asInt() : fallback;
}
long long asInt64Or(const Json::Value &v, const char *key, long long fallback) {
    return v.isMember(key) && v[key].isNumeric() ? v[key].asInt64() : fallback;
}
double asDoubleOr(const Json::Value &v, const char *key, double fallback) {
    if (!v.isMember(key) || v[key].isNull()) return fallback;
    if (v[key].isNumeric()) return v[key].asDouble();
    if (v[key].isString()) {
        try {
            return std::stod(v[key].asString());
        } catch (...) {
            return fallback;
        }
    }
    return fallback;
}
std::string userIdOr(const turbo::RequestContext &ctx) {
    return ctx.userId.empty() ? kZeroUuid : ctx.userId;
}
Json::Value moneyJson(const std::string &dbNumeric) {
    if (dbNumeric.empty()) return Json::Value();
    auto parsed = turbo::Money::parse(dbNumeric);
    return parsed ? Json::Value(parsed->toString(false)) : Json::Value(dbNumeric);
}
turbo::Money moneyOr(const Json::Value &v, const char *key, turbo::Money fallback = turbo::Money()) {
    if (!v.isMember(key) || v[key].isNull()) return fallback;
    std::string text = v[key].isString() ? v[key].asString() : v[key].asString();
    auto parsed = turbo::Money::parse(text);
    return parsed ? *parsed : fallback;
}
std::string numericStr(double value) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%.6f", value);
    return std::string(buf);
}

// loan.status
constexpr int kLSubmitted = kLoanStatusSubmittedAndPendingApproval;
constexpr int kLApproved = kLoanStatusApproved;
constexpr int kLActive = kLoanStatusActive;
constexpr int kLWithdrawn = kLoanStatusWithdrawnByClient;
constexpr int kLRejected = kLoanStatusRejected;
constexpr int kLClosed = kLoanStatusClosedObligationsMet;
constexpr int kLClosedWrittenOff = kLoanStatusClosedWrittenOff;
constexpr int kLClosedReschedule = kLoanStatusClosedReschedule;
constexpr int kLOverpaid = kLoanStatusOverpaid;

// loan_transaction.transaction_type
constexpr int kTxnDisbursement = 1;
constexpr int kTxnRepayment = 2;
constexpr int kTxnWaiveInterest = 4;
constexpr int kTxnWriteOff = 6;
constexpr int kTxnRecovery = 8;
constexpr int kTxnWaiveCharges = 9;
constexpr int kTxnChargePayment = 15;
constexpr int kTxnRefund = 16;
constexpr int kTxnRefundActiveLoan = 17;
constexpr int kTxnIncomePosting = 18;
constexpr int kTxnChargeOff = 19;
constexpr int kTxnReAge = 20;
constexpr int kTxnReAmortize = 21;
constexpr int kTxnMerchantIssuedRefund = 22;
constexpr int kTxnPayoutRefund = 23;
constexpr int kTxnGoodwillCredit = 24;
constexpr int kTxnChargeRefund = 25;
constexpr int kTxnChargeAdjustment = 26;
constexpr int kTxnCapitalizedIncome = 29;
constexpr int kTxnCapitalizedIncomeAmortization = 30;
constexpr int kTxnBuyDownFee = 32;
constexpr int kTxnBuyDownFeeAmortization = 33;

// loan_charge.charge_time_type
constexpr int kChargeTimeDisbursement = 1;
constexpr int kChargeTimeSpecifiedDueDate = 2;
constexpr int kChargeTimeInstallmentFee = 8;
constexpr int kChargeTimeOverdueInstallment = 9;

}  // namespace

drogon::orm::DbClientPtr PortfolioService::db() { return drogon::app().getDbClient(); }

void PortfolioService::requirePermission(const turbo::RequestContext &ctx, const std::string &code) {
    if (!ctx.hasPermission(code))
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

// =====================================================================
// loan products
// =====================================================================

drogon::Task<Json::Value> PortfolioService::loanProductToJson(Txn txn, const std::string &id) {
    auto p = co_await Mapper<m::LoanProduct>(txn).findByPrimaryKey(id);
    Json::Value j;
    j["id"] = p.getValueOfId();
    j["name"] = p.getValueOfName();
    j["shortName"] = p.getValueOfShortName();
    if (p.getDescription()) j["description"] = p.getValueOfDescription();
    j["currencyCode"] = p.getValueOfCurrencyCode();
    j["currencyDigits"] = p.getValueOfCurrencyDigits();
    if (p.getMinPrincipalAmount()) j["minPrincipal"] = moneyJson(p.getValueOfMinPrincipalAmount());
    j["principal"] = moneyJson(p.getValueOfDefaultPrincipalAmount());
    if (p.getMaxPrincipalAmount()) j["maxPrincipal"] = moneyJson(p.getValueOfMaxPrincipalAmount());
    if (p.getMinNumberOfRepayments()) j["minNumberOfRepayments"] = p.getValueOfMinNumberOfRepayments();
    j["numberOfRepayments"] = p.getValueOfDefaultNumberOfRepayments();
    if (p.getMaxNumberOfRepayments()) j["maxNumberOfRepayments"] = p.getValueOfMaxNumberOfRepayments();
    j["repaymentEvery"] = p.getValueOfRepaymentEvery();
    j["repaymentFrequencyType"] = p.getValueOfRepaymentFrequencyType();
    j["interestRatePerPeriod"] = moneyJson(p.getValueOfDefaultInterestRatePerPeriod());
    j["interestPeriodFrequencyType"] = p.getValueOfInterestPeriodFrequencyType();
    j["annualNominalInterestRate"] = moneyJson(p.getValueOfAnnualNominalInterestRate());
    j["interestMethod"] = p.getValueOfInterestMethod();
    j["interestCalculationPeriodType"] = p.getValueOfInterestCalculationPeriodType();
    j["amortizationType"] = p.getValueOfAmortizationType();
    j["transactionProcessingStrategyCode"] = p.getValueOfTransactionProcessingStrategy();
    j["graceOnPrincipalPayment"] = p.getValueOfGraceOnPrincipalPayment();
    j["graceOnInterestPayment"] = p.getValueOfGraceOnInterestPayment();
    j["graceOnInterestCharged"] = p.getValueOfGraceOnInterestCharged();
    j["graceOnArrearsAgeing"] = p.getValueOfGraceOnArrearsAgeing();
    j["overdueDaysForNPA"] = p.getValueOfOverdueDaysForNpa();
    j["daysInYearType"] = p.getValueOfDaysInYearType();
    j["daysInMonthType"] = p.getValueOfDaysInMonthType();
    j["isLinkedToFloatingInterestRate"] = p.getValueOfIsLinkedToFloatingRate();
    if (p.getFloatingRateId()) j["floatingRateId"] = p.getValueOfFloatingRateId();
    j["isEqualAmortization"] = p.getValueOfIsEqualAmortization();
    j["canUseForTopup"] = p.getValueOfCanUseForTopup();
    if (p.getDelinquencyBucketId()) j["delinquencyBucketId"] = p.getValueOfDelinquencyBucketId();
    j["accountingType"] = p.getValueOfAccountingType();
    j["active"] = p.getValueOfIsActive();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::listLoanProducts(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::LoanProduct> mapper(txn);
    mapper.orderBy(m::LoanProduct::Cols::_name);
    auto rows = co_await mapper.findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await loanProductToJson(txn, r.getValueOfId()));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getLoanProduct(const turbo::RequestContext &ctx,
                                                           std::string id) {
    requirePermission(ctx, "READ_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return co_await loanProductToJson(txn, id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan product not found",
                       "error.msg.loanproduct.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::getLoanProductByExternalId(
    const turbo::RequestContext &ctx, std::string externalId) {
    requirePermission(ctx, "READ_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::LoanProduct> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::LoanProduct::Cols::_short_name, externalId));
    // loan_product has no external_id column; short_name doubles as the
    // human-stable external key for this lookup (products are few and
    // short_name is already unique/required, matching Fineract's own use of
    // short_name as a stable business key for products).
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Loan product not found",
                       "error.msg.loanproduct.not.found");
    co_return co_await loanProductToJson(txn, rows.front().getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::createLoanProduct(const turbo::RequestContext &ctx,
                                                              Json::Value body) {
    requirePermission(ctx, "CREATE_LOANPRODUCT");
    const auto name = asStringOr(body, "name");
    const auto shortName = asStringOr(body, "shortName");
    if (name.empty() || shortName.empty())
        throw ApiError(drogon::k400BadRequest, "name and shortName are required",
                       "error.msg.loanproduct.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanProduct row;
    row.setName(name);
    row.setShortName(shortName);
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    row.setCurrencyCode(asStringOr(body, "currencyCode", "USD"));
    row.setCurrencyDigits(asIntOr(body, "digitsAfterDecimal", 2));
    if (body.isMember("minPrincipal"))
        row.setMinPrincipalAmount(moneyOr(body, "minPrincipal").toString(false));
    row.setDefaultPrincipalAmount(moneyOr(body, "principal").toString(false));
    if (body.isMember("maxPrincipal"))
        row.setMaxPrincipalAmount(moneyOr(body, "maxPrincipal").toString(false));
    if (body.isMember("minNumberOfRepayments"))
        row.setMinNumberOfRepayments(asIntOr(body, "minNumberOfRepayments", 1));
    row.setDefaultNumberOfRepayments(asIntOr(body, "numberOfRepayments", 12));
    if (body.isMember("maxNumberOfRepayments"))
        row.setMaxNumberOfRepayments(asIntOr(body, "maxNumberOfRepayments", 12));
    row.setRepaymentEvery(asIntOr(body, "repaymentEvery", 1));
    row.setRepaymentFrequencyType(asIntOr(body, "repaymentFrequencyType", 2));
    row.setDefaultInterestRatePerPeriod(numericStr(asDoubleOr(body, "interestRatePerPeriod", 0)));
    row.setInterestPeriodFrequencyType(asIntOr(body, "interestRateFrequencyType", 3));
    row.setAnnualNominalInterestRate(numericStr(asDoubleOr(body, "annualNominalInterestRate", 0)));
    row.setInterestMethod(asIntOr(body, "interestType", 0));
    row.setInterestCalculationPeriodType(asIntOr(body, "interestCalculationPeriodType", 1));
    row.setAmortizationType(asIntOr(body, "amortizationType", 1));
    row.setTransactionProcessingStrategy(
        asStringOr(body, "transactionProcessingStrategyCode", "mifos-standard-strategy"));
    row.setGraceOnPrincipalPayment(asIntOr(body, "graceOnPrincipalPayment", 0));
    row.setGraceOnInterestPayment(asIntOr(body, "graceOnInterestPayment", 0));
    row.setGraceOnInterestCharged(asIntOr(body, "graceOnInterestCharged", 0));
    row.setGraceOnArrearsAgeing(asIntOr(body, "graceOnArrearsAgeing", 0));
    row.setOverdueDaysForNpa(asIntOr(body, "overdueDaysForNPA", 90));
    row.setDaysInYearType(asIntOr(body, "daysInYearType", 365));
    row.setDaysInMonthType(asIntOr(body, "daysInMonthType", 30));
    row.setMinDaysBetweenDisbursalAndFirstRepayment(
        asIntOr(body, "minDaysBetweenDisbursalAndFirstRepayment", 0));
    row.setAllowPartialPeriodInterest(asBoolOr(body, "allowPartialPeriodInterestCalcualtion", true));
    row.setIsLinkedToFloatingRate(asBoolOr(body, "isLinkedToFloatingInterestRate", false));
    if (body.isMember("floatingRatesId")) row.setFloatingRateId(asStringOr(body, "floatingRatesId"));
    row.setIsEqualAmortization(asBoolOr(body, "isEqualAmortization", false));
    row.setAllowAttributeOverrides(asBoolOr(body, "allowAttributeOverrides", true));
    row.setCanUseForTopup(asBoolOr(body, "canUseForTopup", false));
    if (body.isMember("delinquencyBucketId"))
        row.setDelinquencyBucketId(asStringOr(body, "delinquencyBucketId"));
    row.setAccountingType(asIntOr(body, "accountingRule", 1));
    row.setIsActive(true);
    row.setCreatedBy(userIdOr(ctx));
    row.setUpdatedBy(userIdOr(ctx));
    try {
        row = co_await Mapper<m::LoanProduct>(txn).insert(row);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "Loan product short name already exists",
                       "error.msg.loanproduct.duplicate.shortName");
    }
    if (body.isMember("charges") && body["charges"].isArray()) {
        for (const auto &c : body["charges"]) {
            m::LoanProductCharge lpc;
            lpc.setLoanProductId(row.getValueOfId());
            lpc.setChargeId(c.isObject() ? asStringOr(c, "id") : c.asString());
            co_await Mapper<m::LoanProductCharge>(txn).insert(lpc);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loanproduct", row.getValueOfId(),
                                       "loanproduct.created", body);
    co_return co_await loanProductToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateLoanProduct(const turbo::RequestContext &ctx,
                                                              std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanProduct row;
    try {
        row = co_await Mapper<m::LoanProduct>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan product not found",
                       "error.msg.loanproduct.not.found");
    }
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    if (body.isMember("minPrincipal"))
        row.setMinPrincipalAmount(moneyOr(body, "minPrincipal").toString(false));
    if (body.isMember("principal"))
        row.setDefaultPrincipalAmount(moneyOr(body, "principal").toString(false));
    if (body.isMember("maxPrincipal"))
        row.setMaxPrincipalAmount(moneyOr(body, "maxPrincipal").toString(false));
    if (body.isMember("numberOfRepayments"))
        row.setDefaultNumberOfRepayments(asIntOr(body, "numberOfRepayments", 12));
    if (body.isMember("repaymentEvery")) row.setRepaymentEvery(asIntOr(body, "repaymentEvery", 1));
    if (body.isMember("interestRatePerPeriod"))
        row.setDefaultInterestRatePerPeriod(numericStr(asDoubleOr(body, "interestRatePerPeriod", 0)));
    if (body.isMember("annualNominalInterestRate"))
        row.setAnnualNominalInterestRate(numericStr(asDoubleOr(body, "annualNominalInterestRate", 0)));
    if (body.isMember("interestType")) row.setInterestMethod(asIntOr(body, "interestType", 0));
    if (body.isMember("amortizationType")) row.setAmortizationType(asIntOr(body, "amortizationType", 1));
    if (body.isMember("overdueDaysForNPA"))
        row.setOverdueDaysForNpa(asIntOr(body, "overdueDaysForNPA", 90));
    if (body.isMember("delinquencyBucketId"))
        row.setDelinquencyBucketId(asStringOr(body, "delinquencyBucketId"));
    if (body.isMember("active")) row.setIsActive(asBoolOr(body, "active", true));
    row.setUpdatedBy(userIdOr(ctx));
    co_await Mapper<m::LoanProduct>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loanproduct", id, "loanproduct.updated", body);
    co_return co_await loanProductToJson(txn, id);
}

drogon::Task<Json::Value> PortfolioService::updateLoanProductByExternalId(
    const turbo::RequestContext &ctx, std::string externalId, Json::Value body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::LoanProduct>(txn).findBy(
        Criteria(m::LoanProduct::Cols::_short_name, externalId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Loan product not found",
                       "error.msg.loanproduct.not.found");
    co_return co_await updateLoanProduct(ctx, rows.front().getValueOfId(), std::move(body));
}

Json::Value PortfolioService::loanProductTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["currencyOptions"] = Json::Value(Json::arrayValue);
    t["amortizationTypeOptions"] = Json::Value(Json::arrayValue);
    t["interestTypeOptions"] = Json::Value(Json::arrayValue);
    t["interestCalculationPeriodTypeOptions"] = Json::Value(Json::arrayValue);
    t["repaymentFrequencyTypeOptions"] = Json::Value(Json::arrayValue);
    t["transactionProcessingStrategyOptions"] = Json::Value(Json::arrayValue);
    t["daysInYearTypeOptions"] = Json::Value(Json::arrayValue);
    t["daysInMonthTypeOptions"] = Json::Value(Json::arrayValue);
    return t;
}

drogon::Task<Json::Value> PortfolioService::listProductMix(const turbo::RequestContext &ctx,
                                                           std::string productId) {
    requirePermission(ctx, "READ_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::LoanProductMix>(txn).findBy(
        Criteria(m::LoanProductMix::Cols::_product_id, productId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(r.getValueOfRestrictedProductId());
    Json::Value j;
    j["productId"] = productId;
    j["restrictedProductIds"] = items;
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::createProductMix(const turbo::RequestContext &ctx,
                                                             std::string productId,
                                                             Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    if (body.isMember("restrictedProducts") && body["restrictedProducts"].isArray()) {
        for (const auto &rp : body["restrictedProducts"]) {
            m::LoanProductMix mix;
            mix.setProductId(productId);
            mix.setRestrictedProductId(rp.isObject() ? asStringOr(rp, "id") : rp.asString());
            co_await Mapper<m::LoanProductMix>(txn).insert(mix);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loanproductmix", productId,
                                       "loanproductmix.created", body);
    co_return co_await listProductMix(ctx, productId);
}

drogon::Task<Json::Value> PortfolioService::updateProductMix(const turbo::RequestContext &ctx,
                                                             std::string productId,
                                                             Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await Mapper<m::LoanProductMix>(txn).deleteBy(
        Criteria(m::LoanProductMix::Cols::_product_id, productId));
    co_return co_await createProductMix(ctx, productId, std::move(body));
}

drogon::Task<void> PortfolioService::deleteProductMix(const turbo::RequestContext &ctx,
                                                      std::string productId) {
    requirePermission(ctx, "UPDATE_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await Mapper<m::LoanProductMix>(txn).deleteBy(
        Criteria(m::LoanProductMix::Cols::_product_id, productId));
    co_await turbo::outbox::writeEvent(txn, ctx, "loanproductmix", productId,
                                       "loanproductmix.deleted", Json::Value());
}

// =====================================================================
// floating rates + rates
// =====================================================================

drogon::Task<Json::Value> PortfolioService::listFloatingRates(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_FLOATINGRATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::FloatingRate>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        j["isBaseLendingRate"] = r.getValueOfIsBaseLendingRate();
        j["isActive"] = r.getValueOfIsActive();
        auto periods = co_await Mapper<m::FloatingRatePeriod>(txn).findBy(
            Criteria(m::FloatingRatePeriod::Cols::_floating_rate_id, r.getValueOfId()));
        Json::Value ps(Json::arrayValue);
        for (const auto &p : periods) {
            Json::Value pj;
            pj["id"] = p.getValueOfId();
            pj["fromDate"] = dateStr(p.getValueOfFromDate());
            pj["interestRate"] = moneyJson(p.getValueOfInterestRate());
            pj["isDifferentialToBLR"] = p.getValueOfIsDifferentialToBln();
            ps.append(pj);
        }
        j["ratePeriods"] = ps;
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getFloatingRate(const turbo::RequestContext &ctx,
                                                            std::string id) {
    requirePermission(ctx, "READ_FLOATINGRATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto r = co_await Mapper<m::FloatingRate>(txn).findByPrimaryKey(id);
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        j["isBaseLendingRate"] = r.getValueOfIsBaseLendingRate();
        j["isActive"] = r.getValueOfIsActive();
        co_return j;
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Floating rate not found",
                       "error.msg.floatingrate.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createFloatingRate(const turbo::RequestContext &ctx,
                                                               Json::Value body) {
    requirePermission(ctx, "CREATE_FLOATINGRATE");
    const auto name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "name is required", "error.msg.floatingrate.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::FloatingRate row;
    row.setName(name);
    row.setIsBaseLendingRate(asBoolOr(body, "isBaseLendingRate", false));
    row.setIsActive(asBoolOr(body, "isActive", true));
    row.setCreatedBy(userIdOr(ctx));
    row.setUpdatedBy(userIdOr(ctx));
    row = co_await Mapper<m::FloatingRate>(txn).insert(row);
    if (body.isMember("ratePeriods") && body["ratePeriods"].isArray()) {
        for (const auto &rp : body["ratePeriods"]) {
            m::FloatingRatePeriod period;
            period.setFloatingRateId(row.getValueOfId());
            period.setFromDate(dateOr(asStringOr(rp, "fromDate"), Date::now()));
            period.setInterestRate(numericStr(asDoubleOr(rp, "interestRate", 0)));
            period.setIsDifferentialToBln(asBoolOr(rp, "isDifferentialToBLR", false));
            period.setIsActive(true);
            period.setCreatedBy(userIdOr(ctx));
            co_await Mapper<m::FloatingRatePeriod>(txn).insert(period);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "floatingrate", row.getValueOfId(),
                                       "floatingrate.created", body);
    co_return co_await getFloatingRate(ctx, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateFloatingRate(const turbo::RequestContext &ctx,
                                                               std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_FLOATINGRATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::FloatingRate row;
    try {
        row = co_await Mapper<m::FloatingRate>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Floating rate not found",
                       "error.msg.floatingrate.not.found");
    }
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("isActive")) row.setIsActive(asBoolOr(body, "isActive", true));
    row.setUpdatedBy(userIdOr(ctx));
    co_await Mapper<m::FloatingRate>(txn).update(row);
    if (body.isMember("ratePeriods") && body["ratePeriods"].isArray()) {
        for (const auto &rp : body["ratePeriods"]) {
            m::FloatingRatePeriod period;
            period.setFloatingRateId(id);
            period.setFromDate(dateOr(asStringOr(rp, "fromDate"), Date::now()));
            period.setInterestRate(numericStr(asDoubleOr(rp, "interestRate", 0)));
            period.setIsDifferentialToBln(asBoolOr(rp, "isDifferentialToBLR", false));
            period.setIsActive(true);
            period.setCreatedBy(userIdOr(ctx));
            co_await Mapper<m::FloatingRatePeriod>(txn).insert(period);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "floatingrate", id, "floatingrate.updated", body);
    co_return co_await getFloatingRate(ctx, id);
}

drogon::Task<Json::Value> PortfolioService::listRates(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_RATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Rate>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        j["percentage"] = moneyJson(r.getValueOfPercentage());
        j["active"] = r.getValueOfIsActive();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getRate(const turbo::RequestContext &ctx, std::string id) {
    requirePermission(ctx, "READ_RATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto r = co_await Mapper<m::Rate>(txn).findByPrimaryKey(id);
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        j["percentage"] = moneyJson(r.getValueOfPercentage());
        j["active"] = r.getValueOfIsActive();
        co_return j;
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Rate not found", "error.msg.rate.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createRate(const turbo::RequestContext &ctx,
                                                       Json::Value body) {
    requirePermission(ctx, "CREATE_RATE");
    const auto name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "name is required", "error.msg.rate.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::Rate row;
    row.setName(name);
    row.setPercentage(numericStr(asDoubleOr(body, "percentage", 0)));
    row.setIsActive(asBoolOr(body, "active", true));
    row = co_await Mapper<m::Rate>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "rate", row.getValueOfId(), "rate.created", body);
    co_return co_await getRate(ctx, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateRate(const turbo::RequestContext &ctx,
                                                       std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_RATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::Rate row;
    try {
        row = co_await Mapper<m::Rate>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Rate not found", "error.msg.rate.not.found");
    }
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("percentage")) row.setPercentage(numericStr(asDoubleOr(body, "percentage", 0)));
    if (body.isMember("active")) row.setIsActive(asBoolOr(body, "active", true));
    co_await Mapper<m::Rate>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "rate", id, "rate.updated", body);
    co_return co_await getRate(ctx, id);
}

// =====================================================================
// delinquency buckets + ranges
// =====================================================================

drogon::Task<Json::Value> PortfolioService::listDelinquencyBuckets(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_DELINQUENCY_BUCKET");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::DelinquencyBucket>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await getDelinquencyBucket(ctx, r.getValueOfId()));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getDelinquencyBucket(const turbo::RequestContext &ctx,
                                                                 std::string id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::DelinquencyBucket r;
    try {
        r = co_await Mapper<m::DelinquencyBucket>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Delinquency bucket not found",
                       "error.msg.delinquencybucket.not.found");
    }
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["name"] = r.getValueOfName();
    auto ranges = co_await Mapper<m::DelinquencyBucketRange>(txn).findBy(
        Criteria(m::DelinquencyBucketRange::Cols::_delinquency_bucket_id, id));
    Json::Value rs(Json::arrayValue);
    for (const auto &br : ranges) {
        auto range = co_await Mapper<m::DelinquencyRange>(txn).findByPrimaryKey(
            br.getValueOfDelinquencyRangeId());
        Json::Value rj;
        rj["id"] = range.getValueOfId();
        rj["classification"] = range.getValueOfClassification();
        rj["minimumAgeDays"] = range.getValueOfMinOverdueDays();
        if (range.getMaxOverdueDays()) rj["maximumAgeDays"] = range.getValueOfMaxOverdueDays();
        rs.append(rj);
    }
    j["ranges"] = rs;
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::createDelinquencyBucket(const turbo::RequestContext &ctx,
                                                                   Json::Value body) {
    requirePermission(ctx, "CREATE_DELINQUENCY_BUCKET");
    const auto name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "name is required",
                       "error.msg.delinquencybucket.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::DelinquencyBucket row;
    row.setName(name);
    row = co_await Mapper<m::DelinquencyBucket>(txn).insert(row);
    if (body.isMember("ranges") && body["ranges"].isArray()) {
        for (const auto &rid : body["ranges"]) {
            m::DelinquencyBucketRange br;
            br.setDelinquencyBucketId(row.getValueOfId());
            br.setDelinquencyRangeId(rid.isObject() ? asStringOr(rid, "id") : rid.asString());
            co_await Mapper<m::DelinquencyBucketRange>(txn).insert(br);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "delinquencybucket", row.getValueOfId(),
                                       "delinquencybucket.created", body);
    co_return co_await getDelinquencyBucket(ctx, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateDelinquencyBucket(const turbo::RequestContext &ctx,
                                                                   std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_DELINQUENCY_BUCKET");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::DelinquencyBucket row;
    try {
        row = co_await Mapper<m::DelinquencyBucket>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Delinquency bucket not found",
                       "error.msg.delinquencybucket.not.found");
    }
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    co_await Mapper<m::DelinquencyBucket>(txn).update(row);
    if (body.isMember("ranges") && body["ranges"].isArray()) {
        co_await Mapper<m::DelinquencyBucketRange>(txn).deleteBy(
            Criteria(m::DelinquencyBucketRange::Cols::_delinquency_bucket_id, id));
        for (const auto &rid : body["ranges"]) {
            m::DelinquencyBucketRange br;
            br.setDelinquencyBucketId(id);
            br.setDelinquencyRangeId(rid.isObject() ? asStringOr(rid, "id") : rid.asString());
            co_await Mapper<m::DelinquencyBucketRange>(txn).insert(br);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "delinquencybucket", id,
                                       "delinquencybucket.updated", body);
    co_return co_await getDelinquencyBucket(ctx, id);
}

drogon::Task<void> PortfolioService::deleteDelinquencyBucket(const turbo::RequestContext &ctx,
                                                             std::string id) {
    requirePermission(ctx, "DELETE_DELINQUENCY_BUCKET");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await Mapper<m::DelinquencyBucketRange>(txn).deleteBy(
        Criteria(m::DelinquencyBucketRange::Cols::_delinquency_bucket_id, id));
    try {
        co_await Mapper<m::DelinquencyBucket>(txn).deleteByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Delinquency bucket not found",
                       "error.msg.delinquencybucket.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "delinquencybucket", id,
                                       "delinquencybucket.deleted", Json::Value());
}

drogon::Task<Json::Value> PortfolioService::listDelinquencyRanges(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_DELINQUENCY_BUCKET");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::DelinquencyRange> mapper(txn);
    mapper.orderBy(m::DelinquencyRange::Cols::_min_overdue_days);
    auto rows = co_await mapper.findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["classification"] = r.getValueOfClassification();
        j["minimumAgeDays"] = r.getValueOfMinOverdueDays();
        if (r.getMaxOverdueDays()) j["maximumAgeDays"] = r.getValueOfMaxOverdueDays();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getDelinquencyRange(const turbo::RequestContext &ctx,
                                                                std::string id) {
    requirePermission(ctx, "READ_DELINQUENCY_BUCKET");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto r = co_await Mapper<m::DelinquencyRange>(txn).findByPrimaryKey(id);
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["classification"] = r.getValueOfClassification();
        j["minimumAgeDays"] = r.getValueOfMinOverdueDays();
        if (r.getMaxOverdueDays()) j["maximumAgeDays"] = r.getValueOfMaxOverdueDays();
        co_return j;
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Delinquency range not found",
                       "error.msg.delinquencyrange.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createDelinquencyRange(const turbo::RequestContext &ctx,
                                                                   Json::Value body) {
    requirePermission(ctx, "CREATE_DELINQUENCY_BUCKET");
    const auto classification = asStringOr(body, "classification");
    if (classification.empty())
        throw ApiError(drogon::k400BadRequest, "classification is required",
                       "error.msg.delinquencyrange.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::DelinquencyRange row;
    row.setClassification(classification);
    row.setMinOverdueDays(asIntOr(body, "minimumAgeDays", 1));
    if (body.isMember("maximumAgeDays")) row.setMaxOverdueDays(asIntOr(body, "maximumAgeDays", 0));
    try {
        row = co_await Mapper<m::DelinquencyRange>(txn).insert(row);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "Delinquency range classification already exists",
                       "error.msg.delinquencyrange.duplicate");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "delinquencyrange", row.getValueOfId(),
                                       "delinquencyrange.created", body);
    co_return co_await getDelinquencyRange(ctx, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateDelinquencyRange(const turbo::RequestContext &ctx,
                                                                   std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_DELINQUENCY_BUCKET");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::DelinquencyRange row;
    try {
        row = co_await Mapper<m::DelinquencyRange>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Delinquency range not found",
                       "error.msg.delinquencyrange.not.found");
    }
    if (body.isMember("classification")) row.setClassification(asStringOr(body, "classification"));
    if (body.isMember("minimumAgeDays")) row.setMinOverdueDays(asIntOr(body, "minimumAgeDays", 1));
    if (body.isMember("maximumAgeDays")) row.setMaxOverdueDays(asIntOr(body, "maximumAgeDays", 0));
    co_await Mapper<m::DelinquencyRange>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "delinquencyrange", id,
                                       "delinquencyrange.updated", body);
    co_return co_await getDelinquencyRange(ctx, id);
}

drogon::Task<void> PortfolioService::deleteDelinquencyRange(const turbo::RequestContext &ctx,
                                                            std::string id) {
    requirePermission(ctx, "DELETE_DELINQUENCY_BUCKET");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::DelinquencyRange>(txn).deleteByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Delinquency range not found",
                       "error.msg.delinquencyrange.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "delinquencyrange", id,
                                       "delinquencyrange.deleted", Json::Value());
}

// =====================================================================
// provisioning category + criteria
// =====================================================================

drogon::Task<Json::Value> PortfolioService::listProvisioningCategories(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_PROVISIONCATEGORY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::ProvisioningCategory>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["categoryName"] = r.getValueOfCategoryName();
        if (r.getCategoryDescription()) j["categoryDescription"] = r.getValueOfCategoryDescription();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::createProvisioningCategory(
    const turbo::RequestContext &ctx, Json::Value body) {
    requirePermission(ctx, "CREATE_PROVISIONCATEGORY");
    const auto name = asStringOr(body, "categoryName");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "categoryName is required",
                       "error.msg.provisioningcategory.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ProvisioningCategory row;
    row.setCategoryName(name);
    if (body.isMember("categoryDescription"))
        row.setCategoryDescription(asStringOr(body, "categoryDescription"));
    try {
        row = co_await Mapper<m::ProvisioningCategory>(txn).insert(row);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "Provisioning category already exists",
                       "error.msg.provisioningcategory.duplicate");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningcategory", row.getValueOfId(),
                                       "provisioningcategory.created", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["categoryName"] = row.getValueOfCategoryName();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::updateProvisioningCategory(
    const turbo::RequestContext &ctx, std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_PROVISIONCATEGORY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ProvisioningCategory row;
    try {
        row = co_await Mapper<m::ProvisioningCategory>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Provisioning category not found",
                       "error.msg.provisioningcategory.not.found");
    }
    if (body.isMember("categoryName")) row.setCategoryName(asStringOr(body, "categoryName"));
    if (body.isMember("categoryDescription"))
        row.setCategoryDescription(asStringOr(body, "categoryDescription"));
    co_await Mapper<m::ProvisioningCategory>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningcategory", id,
                                       "provisioningcategory.updated", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["categoryName"] = row.getValueOfCategoryName();
    co_return j;
}

drogon::Task<void> PortfolioService::deleteProvisioningCategory(const turbo::RequestContext &ctx,
                                                                std::string id) {
    requirePermission(ctx, "DELETE_PROVISIONCATEGORY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::ProvisioningCategory>(txn).deleteByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Provisioning category not found",
                       "error.msg.provisioningcategory.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningcategory", id,
                                       "provisioningcategory.deleted", Json::Value());
}

drogon::Task<Json::Value> PortfolioService::listProvisioningCriteria(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_PROVISIONCRITERIA");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::ProvisioningCriteria>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await getProvisioningCriteria(ctx, r.getValueOfId()));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getProvisioningCriteria(const turbo::RequestContext &ctx,
                                                                    std::string id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ProvisioningCriteria r;
    try {
        r = co_await Mapper<m::ProvisioningCriteria>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Provisioning criteria not found",
                       "error.msg.provisioningcriteria.not.found");
    }
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["criteriaName"] = r.getValueOfCriteriaName();
    auto defs = co_await Mapper<m::ProvisioningCriteriaDefinition>(txn).findBy(
        Criteria(m::ProvisioningCriteriaDefinition::Cols::_criteria_id, id));
    Json::Value ds(Json::arrayValue);
    for (const auto &d : defs) {
        Json::Value dj;
        dj["id"] = d.getValueOfId();
        dj["categoryId"] = d.getValueOfCategoryId();
        dj["minAge"] = d.getValueOfMinOverdueDays();
        if (d.getMaxOverdueDays()) dj["maxAge"] = d.getValueOfMaxOverdueDays();
        dj["provisioningPercentage"] = moneyJson(d.getValueOfProvisioningPercentage());
        if (d.getLiabilityAccountId()) dj["liabilityAccount"] = d.getValueOfLiabilityAccountId();
        if (d.getExpenseAccountId()) dj["expenseAccount"] = d.getValueOfExpenseAccountId();
        ds.append(dj);
    }
    j["definitions"] = ds;
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::createProvisioningCriteria(
    const turbo::RequestContext &ctx, Json::Value body) {
    requirePermission(ctx, "CREATE_PROVISIONCRITERIA");
    const auto name = asStringOr(body, "criteriaName");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "criteriaName is required",
                       "error.msg.provisioningcriteria.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ProvisioningCriteria row;
    row.setCriteriaName(name);
    row.setCreatedBy(userIdOr(ctx));
    row.setUpdatedBy(userIdOr(ctx));
    try {
        row = co_await Mapper<m::ProvisioningCriteria>(txn).insert(row);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "Provisioning criteria already exists",
                       "error.msg.provisioningcriteria.duplicate");
    }
    if (body.isMember("definitions") && body["definitions"].isArray()) {
        for (const auto &d : body["definitions"]) {
            m::ProvisioningCriteriaDefinition def;
            def.setCriteriaId(row.getValueOfId());
            def.setCategoryId(asStringOr(d, "categoryId"));
            def.setMinOverdueDays(asIntOr(d, "minAge", 1));
            if (d.isMember("maxAge")) def.setMaxOverdueDays(asIntOr(d, "maxAge", 0));
            def.setProvisioningPercentage(numericStr(asDoubleOr(d, "provisioningPercentage", 0)));
            if (d.isMember("liabilityAccount")) def.setLiabilityAccountId(asStringOr(d, "liabilityAccount"));
            if (d.isMember("expenseAccount")) def.setExpenseAccountId(asStringOr(d, "expenseAccount"));
            co_await Mapper<m::ProvisioningCriteriaDefinition>(txn).insert(def);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningcriteria", row.getValueOfId(),
                                       "provisioningcriteria.created", body);
    co_return co_await getProvisioningCriteria(ctx, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateProvisioningCriteria(
    const turbo::RequestContext &ctx, std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_PROVISIONCRITERIA");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ProvisioningCriteria row;
    try {
        row = co_await Mapper<m::ProvisioningCriteria>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Provisioning criteria not found",
                       "error.msg.provisioningcriteria.not.found");
    }
    if (body.isMember("criteriaName")) row.setCriteriaName(asStringOr(body, "criteriaName"));
    row.setUpdatedBy(userIdOr(ctx));
    co_await Mapper<m::ProvisioningCriteria>(txn).update(row);
    if (body.isMember("definitions") && body["definitions"].isArray()) {
        co_await Mapper<m::ProvisioningCriteriaDefinition>(txn).deleteBy(
            Criteria(m::ProvisioningCriteriaDefinition::Cols::_criteria_id, id));
        for (const auto &d : body["definitions"]) {
            m::ProvisioningCriteriaDefinition def;
            def.setCriteriaId(id);
            def.setCategoryId(asStringOr(d, "categoryId"));
            def.setMinOverdueDays(asIntOr(d, "minAge", 1));
            if (d.isMember("maxAge")) def.setMaxOverdueDays(asIntOr(d, "maxAge", 0));
            def.setProvisioningPercentage(numericStr(asDoubleOr(d, "provisioningPercentage", 0)));
            if (d.isMember("liabilityAccount")) def.setLiabilityAccountId(asStringOr(d, "liabilityAccount"));
            if (d.isMember("expenseAccount")) def.setExpenseAccountId(asStringOr(d, "expenseAccount"));
            co_await Mapper<m::ProvisioningCriteriaDefinition>(txn).insert(def);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningcriteria", id,
                                       "provisioningcriteria.updated", body);
    co_return co_await getProvisioningCriteria(ctx, id);
}

drogon::Task<void> PortfolioService::deleteProvisioningCriteria(const turbo::RequestContext &ctx,
                                                                std::string id) {
    requirePermission(ctx, "DELETE_PROVISIONCRITERIA");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await Mapper<m::ProvisioningCriteriaDefinition>(txn).deleteBy(
        Criteria(m::ProvisioningCriteriaDefinition::Cols::_criteria_id, id));
    try {
        co_await Mapper<m::ProvisioningCriteria>(txn).deleteByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Provisioning criteria not found",
                       "error.msg.provisioningcriteria.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningcriteria", id,
                                       "provisioningcriteria.deleted", Json::Value());
}

Json::Value PortfolioService::provisioningCriteriaTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["criteriaFieldConfig"] = Json::Value(Json::arrayValue);
    return t;
}

// Walks every active, non-NPA-already-flagged loan, classifies delinquency
// from its oldest unpaid installment's overdue days, then computes
// provisioning reserve lines per (office/currency/product/category) from
// the loan product's configured provisioning criteria. Persists reserve
// lines into the ground-truth loanproduct_provisioning_entry +
// provisioning_history tables, and emits a single aggregated outbox event
// shaped like Accounting's POST /provisioningentries body — see this
// service's own header note and AccountingService::createProvisioningEntry.
drogon::Task<Json::Value> PortfolioService::runDelinquencyAndProvisioningJob(
    const turbo::RequestContext &ctx, const std::string &asOfDateIn) {
    requirePermission(ctx, "CREATE_PROVISIONCRITERIA");
    const std::string asOfDate = asOfDateIn.empty() ? dateStr(Date::now()) : asOfDateIn;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);

    auto activeLoans = co_await Mapper<m::Loan>(txn).findBy(Criteria(m::Loan::Cols::_status, kLActive));

    int taggedCount = 0;
    // key: criteria_id|product_id|category_id -> reserve amount micros
    std::map<std::string, long long> reserveByKey;
    std::map<std::string, std::string> liabilityByCategory;
    std::map<std::string, std::string> expenseByCategory;
    std::string currencyCode = "USD";

    for (const auto &loan : activeLoans) {
        auto changed = co_await classifyLoanDelinquency(txn, loan.getValueOfId(), asOfDate);
        if (!changed.empty()) ++taggedCount;
        currencyCode = loan.getValueOfCurrencyCode();

        // Provisioning: find the loan's oldest unpaid installment overdue
        // days, match against the product's provisioning criteria (via the
        // product's delinquency bucket's ranges mapped to criteria
        // definitions' min/max overdue days), and accrue a reserve on the
        // outstanding principal.
        auto product = co_await Mapper<m::LoanProduct>(txn).findByPrimaryKey(loan.getValueOfProductId());
        if (!product.getDelinquencyBucketId()) continue;

        auto installments = co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).findBy(
            Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, loan.getValueOfId()));
        int maxOverdueDays = 0;
        Date now = dateOr(asOfDate, Date::now());
        for (const auto &inst : installments) {
            if (inst.getValueOfCompletedDerived()) continue;
            auto due = inst.getValueOfDueDate();
            if (due.microSecondsSinceEpoch() < now.microSecondsSinceEpoch()) {
                int days = static_cast<int>((now.microSecondsSinceEpoch() -
                                             due.microSecondsSinceEpoch()) /
                                            (86400LL * 1000000LL));
                maxOverdueDays = std::max(maxOverdueDays, days);
            }
        }
        if (maxOverdueDays <= 0) continue;

        // Find any provisioning criteria whose definitions bracket
        // maxOverdueDays (first match wins; a tenant typically configures
        // one global criteria).
        auto allCriteria = co_await Mapper<m::ProvisioningCriteria>(txn).findAll();
        for (const auto &crit : allCriteria) {
            auto defs = co_await Mapper<m::ProvisioningCriteriaDefinition>(txn).findBy(
                Criteria(m::ProvisioningCriteriaDefinition::Cols::_criteria_id, crit.getValueOfId()));
            for (const auto &def : defs) {
                bool inRange = maxOverdueDays >= def.getValueOfMinOverdueDays() &&
                               (!def.getMaxOverdueDays() ||
                                maxOverdueDays <= def.getValueOfMaxOverdueDays());
                if (!inRange) continue;
                auto outstanding = turbo::Money::parse(loan.getValueOfPrincipalDisbursed());
                auto paid = turbo::Money::parse(loan.getValueOfPrincipalPaid());
                if (!outstanding) continue;
                turbo::Money balance = paid ? (*outstanding - *paid) : *outstanding;
                if (balance.isNegative() || balance.isZero()) continue;
                double pct = 0;
                try {
                    pct = std::stod(def.getValueOfProvisioningPercentage());
                } catch (...) {
                }
                turbo::Money reserve = balance.timesRatio(static_cast<int64_t>(pct * 100), 10000);
                const std::string key = crit.getValueOfId() + "|" + loan.getValueOfProductId() + "|" +
                                        def.getValueOfCategoryId();
                reserveByKey[key] += reserve.micros();
                if (def.getLiabilityAccountId())
                    liabilityByCategory[def.getValueOfCategoryId()] = def.getValueOfLiabilityAccountId();
                if (def.getExpenseAccountId())
                    expenseByCategory[def.getValueOfCategoryId()] = def.getValueOfExpenseAccountId();
            }
        }
    }

    // Persist a provisioning_history run + one loanproduct_provisioning_entry
    // row per (product, category) bucket — the ground-truth schema.
    m::ProvisioningHistory history;
    history.setJournalEntryCreated(false);
    history.setCreatedbyId(userIdOr(ctx));
    history.setCreatedDate(dateOr(asOfDate, Date::now()));
    history = co_await Mapper<m::ProvisioningHistory>(txn).insert(history);

    Json::Value entries(Json::arrayValue);
    for (const auto &[key, micros] : reserveByKey) {
        const auto sep1 = key.find('|');
        const auto sep2 = key.find('|', sep1 + 1);
        const std::string criteriaId = key.substr(0, sep1);
        const std::string productId = key.substr(sep1 + 1, sep2 - sep1 - 1);
        const std::string categoryId = key.substr(sep2 + 1);
        auto reserveMoney = turbo::Money::fromMicros(micros);

        m::LoanproductProvisioningEntry entry;
        entry.setHistoryId(history.getValueOfId());
        entry.setCriteriaId(criteriaId);
        entry.setCurrencyCode(currencyCode);
        entry.setOfficeId(kZeroUuid);  // office-level breakdown not tracked per-loan in this phase
        entry.setProductId(productId);
        entry.setCategoryId(categoryId);
        entry.setReseveAmount(reserveMoney.toString(false));
        if (liabilityByCategory.count(categoryId)) entry.setLiabilityAccount(liabilityByCategory[categoryId]);
        if (expenseByCategory.count(categoryId)) entry.setExpenseAccount(expenseByCategory[categoryId]);
        co_await Mapper<m::LoanproductProvisioningEntry>(txn).insert(entry);

        Json::Value line;
        line["officeId"] = kZeroUuid;
        line["currencyCode"] = currencyCode;
        line["glAccountId"] = liabilityByCategory.count(categoryId) ? liabilityByCategory[categoryId] : "";
        line["categoryName"] = categoryId;
        line["amount"] = reserveMoney.toString(false);
        entries.append(line);
    }

    Json::Value accountingPayload;
    accountingPayload["date"] = asOfDate;
    accountingPayload["comments"] = "Auto-generated by Portfolio's provisioning job";
    accountingPayload["entries"] = entries;
    accountingPayload["createjournalentries"] = true;
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningrun", history.getValueOfId(),
                                       "provisioningrun.computed", accountingPayload);

    Json::Value result;
    result["asOfDate"] = asOfDate;
    result["loansClassified"] = static_cast<int>(activeLoans.size());
    result["loansTagged"] = taggedCount;
    result["provisioningHistoryId"] = history.getValueOfId();
    result["provisioningLines"] = entries;
    co_return result;
}

// =====================================================================
// amortization engine
//
// Pure, DB-free date/decimal arithmetic (Howard Hinnant's civil_from_days /
// days_from_civil algorithms for proleptic-Gregorian day numbers) so this
// code is directly hand-verifiable without a live database or Drogon
// runtime. See IMPLEMENTATION_PLAN.md's Phase 6 entry for the worked
// reference cases this was checked against.
//
// Day-count convention: a single nominal periodic rate is derived once from
// the product's annualRatePercent and the configured days-in-year/
// days-in-month convention (30/360 when daysInMonthType=30, nominal
// calendar-unit counts for weeks/days), then held constant across every
// installment — matching Fineract's own declining-balance/flat EMI formula,
// which does not re-derive the periodic rate from actual variable-length
// calendar periods. This is a disclosed simplification vs. full Fineract's
// actual/365 day-by-day accrual variants.
// =====================================================================

namespace {

struct Civil {
    int y, m, d;
};

long long daysFromCivil(int y, int m, int d) {
    y -= m <= 2;
    const long long era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);
    const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + static_cast<long long>(doe) - 719468;
}

Civil civilFromDays(long long z) {
    z += 719468;
    const long long era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = static_cast<unsigned>(z - era * 146097);
    const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    const long long y = static_cast<long long>(yoe) + era * 400;
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    const unsigned mp = (5 * doy + 2) / 153;
    const unsigned d = doy - (153 * mp + 2) / 5 + 1;
    const unsigned m = mp + (mp < 10 ? 3 : -9);
    return Civil{static_cast<int>(y + (m <= 2)), static_cast<int>(m), static_cast<int>(d)};
}

Civil parseIsoDate(const std::string &s) {
    Civil c{1970, 1, 1};
    if (s.size() >= 10) {
        c.y = std::stoi(s.substr(0, 4));
        c.m = std::stoi(s.substr(5, 2));
        c.d = std::stoi(s.substr(8, 2));
    }
    return c;
}

std::string formatIsoDate(const Civil &c) {
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", c.y, c.m, c.d);
    return std::string(buf);
}

Civil addDaysToCivil(const Civil &c, long long days) {
    return civilFromDays(daysFromCivil(c.y, c.m, c.d) + days);
}

Civil addMonthsToCivil(const Civil &c, int months) {
    long long totalMonths = (c.y * 12LL + (c.m - 1)) + months;
    long long y = totalMonths >= 0 ? totalMonths / 12 : -((-totalMonths + 11) / 12);
    int m = static_cast<int>(totalMonths - y * 12) + 1;
    // Clamp day to the target month's length (Fineract behaviour: 31 Jan +1mo -> 28/29 Feb).
    int day = c.d;
    for (int attempt = 0; attempt < 4; ++attempt) {
        long long nextMonthFirstDay =
            daysFromCivil(static_cast<int>(y + (m == 12 ? 1 : 0)), m == 12 ? 1 : m + 1, 1);
        long long thisMonthFirstDay = daysFromCivil(static_cast<int>(y), m, 1);
        int daysInMonth = static_cast<int>(nextMonthFirstDay - thisMonthFirstDay);
        if (day <= daysInMonth) break;
        day = daysInMonth;
    }
    return Civil{static_cast<int>(y), m, day};
}

/// frequencyType: 0=days, 1=weeks, 2=months.
Civil addPeriod(const Civil &c, int everyN, int frequencyType) {
    if (frequencyType == 2) return addMonthsToCivil(c, everyN);
    if (frequencyType == 1) return addDaysToCivil(c, 7LL * everyN);
    return addDaysToCivil(c, everyN);
}

}  // namespace

std::vector<PortfolioService::ScheduleInstallment> PortfolioService::buildAmortizationSchedule(
    const std::string &disbursementDate, double principal, double annualRatePercent,
    int numberOfRepayments, int repaymentEveryNDays, int repaymentFrequencyType, int interestMethod,
    int daysInYearType, int daysInMonthType, int graceOnPrincipal, int graceOnInterest) {
    std::vector<ScheduleInstallment> schedule;
    if (numberOfRepayments <= 0) return schedule;

    // Nominal period length in days for periodic-rate derivation.
    double nominalPeriodDays;
    if (repaymentFrequencyType == 2) {
        nominalPeriodDays = (daysInMonthType == 30 ? 30.0 : 30.4375) * repaymentEveryNDays;
    } else if (repaymentFrequencyType == 1) {
        nominalPeriodDays = 7.0 * repaymentEveryNDays;
    } else {
        nominalPeriodDays = 1.0 * repaymentEveryNDays;
    }
    const double daysInYear = daysInYearType > 0 ? daysInYearType : 365.0;
    const double r = (annualRatePercent / 100.0) * (nominalPeriodDays / daysInYear);

    const int n = numberOfRepayments;
    const int gp = std::clamp(graceOnPrincipal, 0, n - 1);
    const int gi = std::clamp(graceOnInterest, 0, n);

    double remainingPrincipal = principal;
    double principalSumSoFar = 0.0;
    Civil cursor = parseIsoDate(disbursementDate);

    // EMI for the post-grace amortizing periods (declining balance only).
    const int amortizingPeriods = std::max(1, n - gp);
    double emi;
    if (interestMethod == 0) {  // declining balance, equal installment
        emi = (r > 1e-12) ? principal * r / (1.0 - std::pow(1.0 + r, -amortizingPeriods))
                          : principal / amortizingPeriods;
    } else {  // flat
        emi = 0.0;  // computed per-period below for flat method
    }

    for (int i = 1; i <= n; ++i) {
        Civil fromCivil = cursor;
        Civil dueCivil = addPeriod(cursor, repaymentEveryNDays, repaymentFrequencyType);
        cursor = dueCivil;

        double interestDue = 0.0;
        double principalDue = 0.0;

        if (interestMethod == 0) {
            // Declining balance: interest on the *current* remaining
            // balance; principal deferred entirely during the principal
            // grace window (balance does not amortize), then the EMI is
            // recomputed once (above) over the remaining periods.
            interestDue = remainingPrincipal * r;
            if (i <= gp) {
                principalDue = 0.0;
            } else if (i == n) {
                principalDue = principal - principalSumSoFar;  // close out rounding residue
            } else {
                principalDue = emi - interestDue;
                if (principalDue < 0) principalDue = 0;
                if (principalDue > remainingPrincipal) principalDue = remainingPrincipal;
            }
        } else {
            // Flat: interest flat on the original principal every period;
            // principal evenly spread over the non-grace periods.
            interestDue = principal * r;
            if (i <= gp) {
                principalDue = 0.0;
            } else if (i == n) {
                principalDue = principal - principalSumSoFar;
            } else {
                principalDue = principal / amortizingPeriods;
            }
        }

        if (i <= gi) interestDue = 0.0;  // interest-payment grace (disclosed simplification)

        remainingPrincipal -= principalDue;
        principalSumSoFar += principalDue;

        ScheduleInstallment inst;
        inst.number = i;
        inst.fromDate = formatIsoDate(fromCivil);
        inst.dueDate = formatIsoDate(dueCivil);
        inst.principal = numericStr(principalDue);
        inst.interest = numericStr(std::max(0.0, interestDue));
        schedule.push_back(inst);
    }
    return schedule;
}

drogon::Task<void> PortfolioService::persistSchedule(
    Txn txn, const std::string &loanId, const std::vector<ScheduleInstallment> &schedule) {
    co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).deleteBy(
        Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, loanId));
    for (const auto &s : schedule) {
        m::LoanRepaymentScheduleInstallment row;
        row.setLoanId(loanId);
        row.setInstallmentNumber(s.number);
        row.setFromDate(dateOr(s.fromDate, Date::now()));
        row.setDueDate(dateOr(s.dueDate, Date::now()));
        row.setPrincipalAmount(s.principal);
        row.setInterestAmount(s.interest);
        co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).insert(row);
    }
}

// =====================================================================
// loans — id resolution + JSON projection
// =====================================================================

drogon::Task<std::string> PortfolioService::resolveLoanId(Txn txn, const std::string &idOrExternalId,
                                                          bool byExternalId) {
    if (!byExternalId) co_return idOrExternalId;
    auto rows = co_await Mapper<m::Loan>(txn).findBy(
        Criteria(m::Loan::Cols::_external_id, idOrExternalId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Loan not found", "error.msg.loan.not.found");
    co_return rows.front().getValueOfId();
}

drogon::Task<std::string> PortfolioService::resolveLoanChargeId(Txn txn, const std::string &loanId,
                                                                const std::string &idOrExternalId,
                                                                bool byExternalId) {
    if (!byExternalId) co_return idOrExternalId;
    // loan_charge has no external_id column in this schema's charge table;
    // charges are addressed by their own id either way — the
    // external-id-mirror route still resolves (loan side already resolved),
    // so we simply treat the supplied value as the charge id.
    co_return idOrExternalId;
}

drogon::Task<std::string> PortfolioService::resolveLoanTransactionId(
    Txn txn, const std::string &loanId, const std::string &idOrExternalId, bool byExternalId) {
    if (!byExternalId) co_return idOrExternalId;
    auto rows = co_await Mapper<m::LoanTransaction>(txn).findBy(
        Criteria(m::LoanTransaction::Cols::_external_id, idOrExternalId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Loan transaction not found",
                       "error.msg.loantransaction.not.found");
    co_return rows.front().getValueOfId();
}

drogon::Task<Json::Value> PortfolioService::loanToJson(Txn txn, const std::string &id) {
    auto l = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    Json::Value j;
    j["id"] = l.getValueOfId();
    j["accountNo"] = l.getValueOfAccountNo();
    if (l.getExternalId()) j["externalId"] = l.getValueOfExternalId();
    if (l.getClientId()) j["clientId"] = l.getValueOfClientId();
    if (l.getGroupId()) j["groupId"] = l.getValueOfGroupId();
    j["productId"] = l.getValueOfProductId();
    if (l.getLoanOfficerId()) j["loanOfficerId"] = l.getValueOfLoanOfficerId();
    j["loanType"] = l.getValueOfLoanType();
    j["currencyCode"] = l.getValueOfCurrencyCode();
    j["principal"] = moneyJson(l.getValueOfPrincipalAmount());
    if (l.getApprovedPrincipal()) j["approvedPrincipal"] = moneyJson(l.getValueOfApprovedPrincipal());
    j["numberOfRepayments"] = l.getValueOfNumberOfRepayments();
    j["repaymentEvery"] = l.getValueOfRepaymentEvery();
    j["repaymentFrequencyType"] = l.getValueOfRepaymentFrequencyType();
    j["interestRatePerPeriod"] = moneyJson(l.getValueOfInterestRatePerPeriod());
    j["annualNominalInterestRate"] = moneyJson(l.getValueOfAnnualNominalInterestRate());
    j["interestMethod"] = l.getValueOfInterestMethod();
    j["amortizationType"] = l.getValueOfAmortizationType();
    j["daysInYearType"] = l.getValueOfDaysInYearType();
    j["daysInMonthType"] = l.getValueOfDaysInMonthType();
    j["graceOnPrincipalPayment"] = l.getValueOfGraceOnPrincipalPayment();
    j["graceOnInterestPayment"] = l.getValueOfGraceOnInterestPayment();
    j["submittedOnDate"] = dateStr(l.getValueOfSubmittedOnDate());
    if (l.getApprovedOnDate()) j["approvedOnDate"] = dateStr(l.getValueOfApprovedOnDate());
    if (l.getExpectedDisbursementDate())
        j["expectedDisbursementDate"] = dateStr(l.getValueOfExpectedDisbursementDate());
    if (l.getActualDisbursementDate())
        j["actualDisbursementDate"] = dateStr(l.getValueOfActualDisbursementDate());
    if (l.getExpectedMaturityDate())
        j["expectedMaturityDate"] = dateStr(l.getValueOfExpectedMaturityDate());
    if (l.getClosedOnDate()) j["closedOnDate"] = dateStr(l.getValueOfClosedOnDate());
    j["status"] = l.getValueOfStatus();
    if (l.getSubStatus()) j["subStatus"] = l.getValueOfSubStatus();
    j["isNpa"] = l.getValueOfIsNpa();
    if (l.getDelinquencyRangeId()) j["delinquencyRangeId"] = l.getValueOfDelinquencyRangeId();
    j["summary"]["principalDisbursed"] = moneyJson(l.getValueOfPrincipalDisbursed());
    j["summary"]["principalPaid"] = moneyJson(l.getValueOfPrincipalPaid());
    j["summary"]["principalWrittenOff"] = moneyJson(l.getValueOfPrincipalWrittenoff());
    j["summary"]["interestCharged"] = moneyJson(l.getValueOfInterestCharged());
    j["summary"]["interestPaid"] = moneyJson(l.getValueOfInterestPaid());
    j["summary"]["interestWaived"] = moneyJson(l.getValueOfInterestWaived());
    j["summary"]["feeChargesCharged"] = moneyJson(l.getValueOfFeeChargesCharged());
    j["summary"]["feeChargesPaid"] = moneyJson(l.getValueOfFeeChargesPaid());
    j["summary"]["penaltyChargesCharged"] = moneyJson(l.getValueOfPenaltyChargesCharged());
    j["summary"]["penaltyChargesPaid"] = moneyJson(l.getValueOfPenaltyChargesPaid());
    j["summary"]["totalOverpaid"] = moneyJson(l.getValueOfTotalOverpaid());
    if (l.getGlimParentLoanId()) j["glimParentLoanId"] = l.getValueOfGlimParentLoanId();

    auto installments = co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).findBy(
        Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, id));
    std::sort(installments.begin(), installments.end(), [](const auto &a, const auto &b) {
        return a.getValueOfInstallmentNumber() < b.getValueOfInstallmentNumber();
    });
    Json::Value periods(Json::arrayValue);
    for (const auto &inst : installments) {
        Json::Value pj;
        pj["period"] = inst.getValueOfInstallmentNumber();
        pj["fromDate"] = dateStr(inst.getValueOfFromDate());
        pj["dueDate"] = dateStr(inst.getValueOfDueDate());
        pj["principalDue"] = moneyJson(inst.getValueOfPrincipalAmount());
        pj["principalPaid"] = moneyJson(inst.getValueOfPrincipalCompletedDerived());
        pj["interestDue"] = moneyJson(inst.getValueOfInterestAmount());
        pj["interestPaid"] = moneyJson(inst.getValueOfInterestCompletedDerived());
        pj["complete"] = inst.getValueOfCompletedDerived();
        periods.append(pj);
    }
    j["repaymentSchedule"]["periods"] = periods;
    co_return j;
}

drogon::Task<std::string> PortfolioService::generateLoanAccountNumber(Txn txn) {
    // Fineract-style: a zero-padded sequence; uniqueness is still enforced
    // by the DB unique constraint, with a retry on the (rare, concurrent)
    // collision case left to the caller's insert try/catch.
    auto count = co_await Mapper<m::Loan>(txn).count();
    char buf[24];
    std::snprintf(buf, sizeof(buf), "LN%010lld", static_cast<long long>(count + 1));
    co_return std::string(buf);
}

drogon::Task<std::string> PortfolioService::generateShareAccountNumber(Txn txn) {
    auto count = co_await Mapper<m::ShareAccount>(txn).count();
    char buf[24];
    std::snprintf(buf, sizeof(buf), "SH%010lld", static_cast<long long>(count + 1));
    co_return std::string(buf);
}

drogon::Task<Json::Value> PortfolioService::listLoans(const turbo::RequestContext &ctx,
                                                      const std::string &clientId,
                                                      const std::string &status, int offset,
                                                      int limit) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Loan> mapper(txn);
    Criteria crit;
    if (!clientId.empty()) crit = Criteria(m::Loan::Cols::_client_id, clientId);
    if (!status.empty()) {
        Criteria statusCrit(m::Loan::Cols::_status, std::stoi(status));
        crit = crit ? (crit && statusCrit) : statusCrit;
    }
    const auto total = crit ? co_await mapper.count(crit) : co_await mapper.count();
    mapper.limit(limit > 0 ? limit : 50).offset(offset);
    auto rows = crit ? co_await mapper.findBy(crit) : co_await mapper.findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await loanToJson(txn, r.getValueOfId()));
    co_return turbo::pagedResult(total, items);
}

drogon::Task<Json::Value> PortfolioService::getLoan(const turbo::RequestContext &ctx,
                                                    std::string idOrExternalId, bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
        co_return co_await loanToJson(txn, id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan not found", "error.msg.loan.not.found");
    }
}

Json::Value PortfolioService::calculateLoanSchedule(const turbo::RequestContext &ctx,
                                                    const Json::Value &body) {
    const double principal = asDoubleOr(body, "principal", 0);
    const double rate = asDoubleOr(body, "interestRatePerPeriod", 0);
    const int n = asIntOr(body, "numberOfRepayments", 12);
    const int every = asIntOr(body, "repaymentEvery", 1);
    const int freqType = asIntOr(body, "repaymentFrequencyType", 2);
    const int interestMethod = asIntOr(body, "interestType", 0);
    const int daysInYear = asIntOr(body, "daysInYearType", 365);
    const int daysInMonth = asIntOr(body, "daysInMonthType", 30);
    const int gp = asIntOr(body, "graceOnPrincipalPayment", 0);
    const int gi = asIntOr(body, "graceOnInterestPayment", 0);
    const auto disbDate = asStringOr(body, "expectedDisbursementDate", dateStr(Date::now()));

    auto schedule = buildAmortizationSchedule(disbDate, principal, rate, n, every, freqType,
                                              interestMethod, daysInYear, daysInMonth, gp, gi);
    Json::Value periods(Json::arrayValue);
    turbo::Money totalPrincipal, totalInterest;
    for (const auto &s : schedule) {
        Json::Value pj;
        pj["period"] = s.number;
        pj["fromDate"] = s.fromDate;
        pj["dueDate"] = s.dueDate;
        pj["principalDue"] = moneyJson(s.principal);
        pj["interestDue"] = moneyJson(s.interest);
        periods.append(pj);
        if (auto p = turbo::Money::parse(s.principal)) totalPrincipal += *p;
        if (auto i = turbo::Money::parse(s.interest)) totalInterest += *i;
    }
    Json::Value j;
    j["currency"]["code"] = asStringOr(body, "currencyCode", "USD");
    j["periods"] = periods;
    j["totalPrincipalDisbursed"] = totalPrincipal.toString(false);
    j["totalInterestCharged"] = totalInterest.toString(false);
    j["totalRepaymentExpected"] = (totalPrincipal + totalInterest).toString(false);
    return j;
}

drogon::Task<Json::Value> PortfolioService::createLoan(const turbo::RequestContext &ctx,
                                                       Json::Value body) {
    requirePermission(ctx, "CREATE_LOAN");
    const auto productId = asStringOr(body, "productId");
    if (productId.empty())
        throw ApiError(drogon::k400BadRequest, "productId is required", "error.msg.loan.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanProduct product;
    try {
        product = co_await Mapper<m::LoanProduct>(txn).findByPrimaryKey(productId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k400BadRequest, "Unknown loan product",
                       "error.msg.loan.product.not.found");
    }

    m::Loan row;
    row.setAccountNo(co_await generateLoanAccountNumber(txn));
    if (body.isMember("externalId")) row.setExternalId(asStringOr(body, "externalId"));
    if (body.isMember("clientId")) row.setClientId(asStringOr(body, "clientId"));
    if (body.isMember("groupId")) row.setGroupId(asStringOr(body, "groupId"));
    row.setProductId(productId);
    if (body.isMember("loanOfficerId")) row.setLoanOfficerId(asStringOr(body, "loanOfficerId"));
    if (body.isMember("fundId")) row.setFundId(asStringOr(body, "fundId"));
    if (body.isMember("loanPurpose")) row.setLoanPurpose(asStringOr(body, "loanPurpose"));
    row.setLoanType(asIntOr(body, "loanType", 1));
    row.setCurrencyCode(product.getValueOfCurrencyCode());
    row.setCurrencyDigits(product.getValueOfCurrencyDigits());
    row.setPrincipalAmount(moneyOr(body, "principal", turbo::Money::parse(
                                                           product.getValueOfDefaultPrincipalAmount())
                                                           .value_or(turbo::Money()))
                               .toString(false));
    row.setNumberOfRepayments(asIntOr(body, "numberOfRepayments",
                                      product.getValueOfDefaultNumberOfRepayments()));
    row.setRepaymentEvery(asIntOr(body, "repaymentEvery", product.getValueOfRepaymentEvery()));
    row.setRepaymentFrequencyType(
        asIntOr(body, "repaymentFrequencyType", product.getValueOfRepaymentFrequencyType()));
    row.setInterestRatePerPeriod(numericStr(asDoubleOr(
        body, "interestRatePerPeriod",
        std::stod(product.getValueOfDefaultInterestRatePerPeriod()))));
    row.setInterestPeriodFrequencyType(
        asIntOr(body, "interestRateFrequencyType", product.getValueOfInterestPeriodFrequencyType()));
    row.setAnnualNominalInterestRate(numericStr(asDoubleOr(
        body, "annualNominalInterestRate", std::stod(product.getValueOfAnnualNominalInterestRate()))));
    row.setInterestMethod(asIntOr(body, "interestType", product.getValueOfInterestMethod()));
    row.setInterestCalculationPeriodType(
        asIntOr(body, "interestCalculationPeriodType", product.getValueOfInterestCalculationPeriodType()));
    row.setAmortizationType(asIntOr(body, "amortizationType", product.getValueOfAmortizationType()));
    row.setTransactionProcessingStrategy(asStringOr(body, "transactionProcessingStrategyCode",
                                                    product.getValueOfTransactionProcessingStrategy()));
    row.setDaysInYearType(asIntOr(body, "daysInYearType", product.getValueOfDaysInYearType()));
    row.setDaysInMonthType(asIntOr(body, "daysInMonthType", product.getValueOfDaysInMonthType()));
    row.setGraceOnPrincipalPayment(
        asIntOr(body, "graceOnPrincipalPayment", product.getValueOfGraceOnPrincipalPayment()));
    row.setGraceOnInterestPayment(
        asIntOr(body, "graceOnInterestPayment", product.getValueOfGraceOnInterestPayment()));
    row.setGraceOnInterestCharged(
        asIntOr(body, "graceOnInterestCharged", product.getValueOfGraceOnInterestCharged()));
    row.setGraceOnArrearsAgeing(asIntOr(body, "graceOnArrearsAgeing", product.getValueOfGraceOnArrearsAgeing()));
    row.setIsEqualAmortization(asBoolOr(body, "isEqualAmortization", product.getValueOfIsEqualAmortization()));
    row.setIsFloatingInterestRate(asBoolOr(body, "isFloatingInterestRate", false));
    if (body.isMember("interestRateDifferential"))
        row.setInterestRateDifferential(numericStr(asDoubleOr(body, "interestRateDifferential", 0)));
    const auto submittedOn = asStringOr(body, "submittedOnDate", dateStr(Date::now()));
    row.setSubmittedOnDate(dateOr(submittedOn, Date::now()));
    row.setSubmittedBy(userIdOr(ctx));
    if (body.isMember("expectedDisbursementDate"))
        row.setExpectedDisbursementDate(dateOr(asStringOr(body, "expectedDisbursementDate"), Date::now()));
    if (body.isMember("glimParentLoanId")) row.setGlimParentLoanId(asStringOr(body, "glimParentLoanId"));
    row.setStatus(kLSubmitted);
    row.setIsNpa(false);

    try {
        row = co_await Mapper<m::Loan>(txn).insert(row);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "Loan external id already exists",
                       "error.msg.loan.duplicate.externalId");
    }

    if (body.isMember("charges") && body["charges"].isArray()) {
        for (const auto &c : body["charges"]) {
            m::LoanCharge ch;
            ch.setLoanId(row.getValueOfId());
            ch.setChargeId(asStringOr(c, "chargeId"));
            ch.setIsPenalty(asBoolOr(c, "penalty", false));
            ch.setChargeTimeType(asIntOr(c, "chargeTimeType", kChargeTimeDisbursement));
            ch.setChargeCalculationType(asIntOr(c, "chargeCalculationType", 1));
            if (c.isMember("dueDate")) ch.setDueDate(dateOr(asStringOr(c, "dueDate"), Date::now()));
            ch.setAmount(moneyOr(c, "amount").toString(false));
            ch.setAmountOutstandingDerived(moneyOr(c, "amount").toString(false));
            co_await Mapper<m::LoanCharge>(txn).insert(ch);
        }
    }
    if (body.isMember("collateral") && body["collateral"].isArray()) {
        for (const auto &col : body["collateral"]) {
            m::LoanCollateral lc;
            lc.setLoanId(row.getValueOfId());
            lc.setCollateralTypeId(asStringOr(col, "type"));
            if (col.isMember("value")) lc.setValue(moneyOr(col, "value").toString(false));
            if (col.isMember("description")) lc.setDescription(asStringOr(col, "description"));
            co_await Mapper<m::LoanCollateral>(txn).insert(lc);
        }
    }

    co_await turbo::outbox::writeEvent(txn, ctx, "loan", row.getValueOfId(), "loan.submitted", body);
    co_return co_await loanToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateLoan(const turbo::RequestContext &ctx,
                                                       std::string idOrExternalId, bool byExternalId,
                                                       Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::Loan row;
    try {
        row = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan not found", "error.msg.loan.not.found");
    }
    if (row.getValueOfStatus() != kLSubmitted)
        throw ApiError(drogon::k409Conflict, "Only loans pending approval can be modified",
                       "error.msg.loan.invalid.status.transition");
    if (body.isMember("principal")) row.setPrincipalAmount(moneyOr(body, "principal").toString(false));
    if (body.isMember("numberOfRepayments"))
        row.setNumberOfRepayments(asIntOr(body, "numberOfRepayments", row.getValueOfNumberOfRepayments()));
    if (body.isMember("interestRatePerPeriod"))
        row.setInterestRatePerPeriod(numericStr(asDoubleOr(body, "interestRatePerPeriod", 0)));
    if (body.isMember("loanOfficerId")) row.setLoanOfficerId(asStringOr(body, "loanOfficerId"));
    if (body.isMember("expectedDisbursementDate"))
        row.setExpectedDisbursementDate(dateOr(asStringOr(body, "expectedDisbursementDate"), Date::now()));
    co_await Mapper<m::Loan>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.updated", body);
    co_return co_await loanToJson(txn, id);
}

drogon::Task<void> PortfolioService::deleteLoan(const turbo::RequestContext &ctx,
                                               std::string idOrExternalId, bool byExternalId) {
    requirePermission(ctx, "DELETE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::Loan row;
    try {
        row = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan not found", "error.msg.loan.not.found");
    }
    if (row.getValueOfStatus() != kLSubmitted)
        throw ApiError(drogon::k409Conflict, "Only loans pending approval can be deleted",
                       "error.msg.loan.invalid.status.transition");
    co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).deleteBy(
        Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, id));
    co_await Mapper<m::LoanCharge>(txn).deleteBy(Criteria(m::LoanCharge::Cols::_loan_id, id));
    co_await Mapper<m::LoanCollateral>(txn).deleteBy(Criteria(m::LoanCollateral::Cols::_loan_id, id));
    co_await Mapper<m::LoanGuarantor>(txn).deleteBy(Criteria(m::LoanGuarantor::Cols::_loan_id, id));
    co_await Mapper<m::Loan>(txn).deleteByPrimaryKey(id);
    co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.deleted", Json::Value());
}

Json::Value PortfolioService::loanTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["loanTypeOptions"] = Json::Value(Json::arrayValue);
    t["amortizationTypeOptions"] = Json::Value(Json::arrayValue);
    t["interestTypeOptions"] = Json::Value(Json::arrayValue);
    t["transactionProcessingStrategyOptions"] = Json::Value(Json::arrayValue);
    t["loanProductOptions"] = Json::Value(Json::arrayValue);
    return t;
}

// =====================================================================
// loan lifecycle command handler
// =====================================================================

drogon::Task<Json::Value> PortfolioService::handleLoanCommand(const turbo::RequestContext &ctx,
                                                              std::string idOrExternalId,
                                                              bool byExternalId, std::string command,
                                                              Json::Value body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::Loan row;
    try {
        row = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan not found", "error.msg.loan.not.found");
    }

    auto requireStatus = [&](int expected, const char *what) {
        if (row.getValueOfStatus() != expected)
            throw ApiError(drogon::k409Conflict, std::string("Loan is not ") + what,
                           "error.msg.loan.invalid.status.transition");
    };

    if (command == "approve") {
        requirePermission(ctx, "APPROVE_LOAN");
        requireStatus(kLSubmitted, "pending approval");
        row.setStatus(kLApproved);
        row.setApprovedOnDate(dateOr(asStringOr(body, "approvedOnDate"), Date::now()));
        row.setApprovedBy(userIdOr(ctx));
        if (body.isMember("approvedLoanAmount"))
            row.setApprovedPrincipal(moneyOr(body, "approvedLoanAmount").toString(false));
        else
            row.setApprovedPrincipal(row.getValueOfPrincipalAmount());
        if (body.isMember("expectedDisbursementDate"))
            row.setExpectedDisbursementDate(dateOr(asStringOr(body, "expectedDisbursementDate"), Date::now()));
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.approved", body);
    } else if (command == "reject") {
        requirePermission(ctx, "REJECT_LOAN");
        requireStatus(kLSubmitted, "pending approval");
        row.setStatus(kLRejected);
        row.setRejectedOnDate(dateOr(asStringOr(body, "rejectedOnDate"), Date::now()));
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.rejected", body);
    } else if (command == "withdrawnByApplicant") {
        requirePermission(ctx, "WITHDRAW_LOAN");
        requireStatus(kLSubmitted, "pending approval");
        row.setStatus(kLWithdrawn);
        row.setWithdrawnOnDate(dateOr(asStringOr(body, "withdrawnOnDate"), Date::now()));
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.withdrawn", body);
    } else if (command == "undoApproval") {
        requirePermission(ctx, "APPROVE_LOAN");
        requireStatus(kLApproved, "approved");
        row.setStatus(kLSubmitted);
        row.setApprovedOnDateToNull();
        row.setApprovedByToNull();
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.approval.undone", body);
    } else if (command == "assignLoanOfficer") {
        requirePermission(ctx, "ASSIGNSTAFF_LOAN");
        row.setLoanOfficerId(asStringOr(body, "loanOfficerId"));
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.officer.assigned", body);
    } else if (command == "unassignLoanOfficer") {
        requirePermission(ctx, "ASSIGNSTAFF_LOAN");
        row.setLoanOfficerIdToNull();
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.officer.unassigned", body);
    } else if (command == "disburse" || command == "disburseToSavings") {
        requirePermission(ctx, "DISBURSE_LOAN");
        requireStatus(kLApproved, "approved");
        const auto principal = body.isMember("transactionAmount")
                                   ? moneyOr(body, "transactionAmount")
                                   : turbo::Money::parse(row.getValueOfApprovedPrincipal())
                                         .value_or(turbo::Money::parse(row.getValueOfPrincipalAmount())
                                                       .value_or(turbo::Money()));
        const auto disbDate = asStringOr(body, "actualDisbursementDate", dateStr(Date::now()));
        row.setStatus(kLActive);
        row.setActualDisbursementDate(dateOr(disbDate, Date::now()));
        row.setDisbursedBy(userIdOr(ctx));
        row.setPrincipalAmount(principal.toString(false));
        row.setNetDisbursalAmount(principal.toString(false));
        row.setPrincipalDisbursed(principal.toString(false));
        row.setInterestChargedFromDate(dateOr(disbDate, Date::now()));

        // Schedule is built from the loan's annual nominal rate (always
        // expressed annually in this schema), not the periodic-rate field
        // (which mirrors Fineract's UI-facing "rate per period" display
        // value and is not used for the amortization math itself).
        auto schedule = buildAmortizationSchedule(
            disbDate, std::stod(principal.toString(false)),
            std::stod(row.getValueOfAnnualNominalInterestRate()), row.getValueOfNumberOfRepayments(),
            row.getValueOfRepaymentEvery(), row.getValueOfRepaymentFrequencyType(),
            row.getValueOfInterestMethod(), row.getValueOfDaysInYearType(),
            row.getValueOfDaysInMonthType(), row.getValueOfGraceOnPrincipalPayment(),
            row.getValueOfGraceOnInterestPayment());
        co_await persistSchedule(txn, id, schedule);

        turbo::Money totalInterest;
        std::string maturity;
        for (const auto &s : schedule) {
            if (auto i = turbo::Money::parse(s.interest)) totalInterest += *i;
            maturity = s.dueDate;
        }
        row.setInterestCharged(totalInterest.toString(false));
        if (!maturity.empty()) {
            row.setExpectedMaturityDate(dateOr(maturity, Date::now()));
            row.setMaturityDate(dateOr(maturity, Date::now()));
        }
        co_await Mapper<m::Loan>(txn).update(row);

        m::LoanTransaction txnRow;
        txnRow.setLoanId(id);
        txnRow.setTransactionType(kTxnDisbursement);
        txnRow.setTransactionDate(dateOr(disbDate, Date::now()));
        txnRow.setAmount(principal.toString(false));
        txnRow.setPrincipalPortion(principal.toString(false));
        txnRow.setCreatedBy(userIdOr(ctx));
        co_await Mapper<m::LoanTransaction>(txn).insert(txnRow);

        Json::Value glEvent;
        glEvent["loanId"] = id;
        glEvent["productId"] = row.getValueOfProductId();
        glEvent["amount"] = principal.toString(false);
        glEvent["transactionDate"] = disbDate;
        glEvent["glUsage"] = "loan.disbursement";
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.disbursed", glEvent);
    } else if (command == "undoDisbursal") {
        requirePermission(ctx, "DISBURSE_LOAN");
        requireStatus(kLActive, "active");
        auto txns = co_await Mapper<m::LoanTransaction>(txn).findBy(
            Criteria(m::LoanTransaction::Cols::_loan_id, id));
        for (const auto &t : txns) {
            if (t.getValueOfTransactionType() != kTxnDisbursement)
                throw ApiError(drogon::k409Conflict,
                               "Cannot undo disbursal after other transactions were posted",
                               "error.msg.loan.undodisbursal.not.allowed");
        }
        co_await Mapper<m::LoanTransaction>(txn).deleteBy(Criteria(m::LoanTransaction::Cols::_loan_id, id));
        co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).deleteBy(
            Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, id));
        row.setStatus(kLApproved);
        row.setActualDisbursementDateToNull();
        row.setPrincipalDisbursed("0.000000");
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.disbursal.undone", body);
    } else if (command == "close") {
        requirePermission(ctx, "CLOSE_LOAN");
        requireStatus(kLActive, "active");
        auto disbursed = turbo::Money::parse(row.getValueOfPrincipalDisbursed()).value_or(turbo::Money());
        auto paid = turbo::Money::parse(row.getValueOfPrincipalPaid()).value_or(turbo::Money());
        if (paid < disbursed)
            throw ApiError(drogon::k409Conflict,
                           "Loan still has an outstanding balance; use foreclosure or write-off",
                           "error.msg.loan.close.outstanding.balance");
        row.setStatus(kLClosed);
        row.setClosedOnDate(dateOr(asStringOr(body, "closedOnDate"), Date::now()));
        row.setClosedBy(userIdOr(ctx));
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.closed", body);
    } else if (command == "closeAsRescheduled") {
        requirePermission(ctx, "CLOSE_LOAN");
        requireStatus(kLActive, "active");
        row.setStatus(kLClosedReschedule);
        row.setClosedOnDate(dateOr(asStringOr(body, "closedOnDate"), Date::now()));
        row.setClosedBy(userIdOr(ctx));
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.closed.rescheduled", body);
    } else if (command == "writeoff" || command == "chargeOff") {
        requirePermission(ctx, "WRITEOFF_LOAN");
        requireStatus(kLActive, "active");
        auto disbursed = turbo::Money::parse(row.getValueOfPrincipalDisbursed()).value_or(turbo::Money());
        auto paid = turbo::Money::parse(row.getValueOfPrincipalPaid()).value_or(turbo::Money());
        auto outstandingPrincipal = disbursed - paid;
        auto interestCharged = turbo::Money::parse(row.getValueOfInterestCharged()).value_or(turbo::Money());
        auto interestPaid = turbo::Money::parse(row.getValueOfInterestPaid()).value_or(turbo::Money());
        auto outstandingInterest = interestCharged - interestPaid;
        row.setStatus(kLClosedWrittenOff);
        row.setWrittenoffOnDate(dateOr(asStringOr(body, "transactionDate"), Date::now()));
        row.setClosedOnDate(dateOr(asStringOr(body, "transactionDate"), Date::now()));
        row.setClosedBy(userIdOr(ctx));
        row.setPrincipalWrittenoff(outstandingPrincipal.toString(false));
        row.setInterestWrittenoff(outstandingInterest.toString(false));
        co_await Mapper<m::Loan>(txn).update(row);

        m::LoanTransaction txnRow;
        txnRow.setLoanId(id);
        txnRow.setTransactionType(command == "chargeOff" ? kTxnChargeOff : kTxnWriteOff);
        txnRow.setTransactionDate(dateOr(asStringOr(body, "transactionDate"), Date::now()));
        txnRow.setAmount((outstandingPrincipal + outstandingInterest).toString(false));
        txnRow.setPrincipalPortion(outstandingPrincipal.toString(false));
        txnRow.setInterestPortion(outstandingInterest.toString(false));
        txnRow.setCreatedBy(userIdOr(ctx));
        co_await Mapper<m::LoanTransaction>(txn).insert(txnRow);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.writtenoff", body);
    } else if (command == "recoverGuarantees") {
        requirePermission(ctx, "UPDATE_LOAN");
        auto guarantors = co_await Mapper<m::LoanGuarantor>(txn).findBy(
            Criteria(m::LoanGuarantor::Cols::_loan_id, id));
        turbo::Money total;
        for (const auto &g : guarantors) {
            if (g.getAmount()) {
                if (auto amt = turbo::Money::parse(g.getValueOfAmount())) total += *amt;
            }
        }
        row.setTotalRecovered(
            (turbo::Money::parse(row.getValueOfTotalRecovered()).value_or(turbo::Money()) + total)
                .toString(false));
        co_await Mapper<m::Loan>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.guarantees.recovered", body);
    } else {
        throw ApiError(drogon::k400BadRequest, "Unknown loan command: " + command,
                       "error.msg.loan.command.unknown");
    }
    co_return co_await loanToJson(txn, id);
}

drogon::Task<Json::Value> PortfolioService::getApprovedAmountHistory(const turbo::RequestContext &ctx,
                                                                     std::string idOrExternalId,
                                                                     bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto row = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    Json::Value j(Json::arrayValue);
    Json::Value entry;
    entry["loanId"] = id;
    entry["approvedAmount"] = row.getApprovedPrincipal() ? moneyJson(row.getValueOfApprovedPrincipal())
                                                         : moneyJson(row.getValueOfPrincipalAmount());
    if (row.getApprovedOnDate()) entry["approvedOnDate"] = dateStr(row.getValueOfApprovedOnDate());
    j.append(entry);
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::updateApprovedAmount(const turbo::RequestContext &ctx,
                                                                 std::string idOrExternalId,
                                                                 bool byExternalId, Json::Value body) {
    requirePermission(ctx, "APPROVE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto row = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    row.setApprovedPrincipal(moneyOr(body, "approvedLoanAmount").toString(false));
    co_await Mapper<m::Loan>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.approvedamount.updated", body);
    co_return co_await loanToJson(txn, id);
}

drogon::Task<Json::Value> PortfolioService::updateAvailableDisbursementAmount(
    const turbo::RequestContext &ctx, std::string idOrExternalId, bool byExternalId,
    Json::Value body) {
    requirePermission(ctx, "DISBURSE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto row = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    row.setNetDisbursalAmount(moneyOr(body, "availableDisbursementAmount").toString(false));
    co_await Mapper<m::Loan>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.availabledisbursement.updated", body);
    co_return co_await loanToJson(txn, id);
}

drogon::Task<Json::Value> PortfolioService::recalculateLoanSchedule(const turbo::RequestContext &ctx,
                                                                    std::string idOrExternalId,
                                                                    bool byExternalId,
                                                                    Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto id = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto row = co_await Mapper<m::Loan>(txn).findByPrimaryKey(id);
    const auto fromDate = asStringOr(
        body, "fromDate", row.getActualDisbursementDate() ? dateStr(row.getValueOfActualDisbursementDate())
                                                          : dateStr(Date::now()));
    auto schedule = buildAmortizationSchedule(
        fromDate, std::stod(row.getValueOfPrincipalAmount()),
        std::stod(row.getValueOfAnnualNominalInterestRate()), row.getValueOfNumberOfRepayments(),
        row.getValueOfRepaymentEvery(), row.getValueOfRepaymentFrequencyType(),
        row.getValueOfInterestMethod(), row.getValueOfDaysInYearType(), row.getValueOfDaysInMonthType(),
        row.getValueOfGraceOnPrincipalPayment(), row.getValueOfGraceOnInterestPayment());
    co_await persistSchedule(txn, id, schedule);
    co_await turbo::outbox::writeEvent(txn, ctx, "loan", id, "loan.schedule.recalculated", body);
    co_return co_await loanToJson(txn, id);
}

// =====================================================================
// repayment allocation + delinquency classification
// =====================================================================

drogon::Task<PortfolioService::Allocation> PortfolioService::allocateRepayment(
    Txn txn, const std::string &loanId, const std::string &amountStr) {
    auto amount = turbo::Money::parse(amountStr).value_or(turbo::Money());
    Allocation alloc;
    turbo::Money principalAlloc, interestAlloc, feesAlloc, penaltiesAlloc;

    auto installments = co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).findBy(
        Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, loanId));
    std::sort(installments.begin(), installments.end(), [](const auto &a, const auto &b) {
        return a.getValueOfInstallmentNumber() < b.getValueOfInstallmentNumber();
    });

    turbo::Money remaining = amount;
    // mifos-standard-strategy: within each installment in due-date order,
    // pay penalties, then fees, then interest, then principal; move to the
    // next installment once the current one is fully settled.
    for (auto &inst : installments) {
        if (remaining.isZero() || remaining.isNegative()) break;
        auto interestDue = turbo::Money::parse(inst.getValueOfInterestAmount()).value_or(turbo::Money());
        auto interestPaid =
            turbo::Money::parse(inst.getValueOfInterestCompletedDerived()).value_or(turbo::Money());
        auto interestOutstanding = interestDue - interestPaid;
        auto principalDue = turbo::Money::parse(inst.getValueOfPrincipalAmount()).value_or(turbo::Money());
        auto principalPaid =
            turbo::Money::parse(inst.getValueOfPrincipalCompletedDerived()).value_or(turbo::Money());
        auto principalOutstanding = principalDue - principalPaid;

        if (interestOutstanding.isNegative()) interestOutstanding = turbo::Money();
        if (principalOutstanding.isNegative()) principalOutstanding = turbo::Money();
        if (interestOutstanding.isZero() && principalOutstanding.isZero()) continue;

        turbo::Money payInterest =
            remaining < interestOutstanding ? remaining : interestOutstanding;
        remaining -= payInterest;
        interestPaid += payInterest;
        interestAlloc += payInterest;

        turbo::Money payPrincipal =
            remaining < principalOutstanding ? remaining : principalOutstanding;
        remaining -= payPrincipal;
        principalPaid += payPrincipal;
        principalAlloc += payPrincipal;

        inst.setInterestCompletedDerived(interestPaid.toString(false));
        inst.setPrincipalCompletedDerived(principalPaid.toString(false));
        inst.setCompletedDerived(interestPaid >= interestDue && principalPaid >= principalDue);
        if (inst.getValueOfCompletedDerived()) inst.setObligationsMetOnDate(Date::now());
        co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).update(inst);
    }

    alloc.principal = principalAlloc.toString(false);
    alloc.interest = interestAlloc.toString(false);
    alloc.fees = feesAlloc.toString(false);
    alloc.penalties = penaltiesAlloc.toString(false);

    auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
    loan.setPrincipalPaid(
        (turbo::Money::parse(loan.getValueOfPrincipalPaid()).value_or(turbo::Money()) + principalAlloc)
            .toString(false));
    loan.setInterestPaid(
        (turbo::Money::parse(loan.getValueOfInterestPaid()).value_or(turbo::Money()) + interestAlloc)
            .toString(false));
    bool overpaid = !remaining.isZero() && !remaining.isNegative();
    if (overpaid) {
        // overpayment: amount exceeds the full outstanding obligation.
        loan.setTotalOverpaid(
            (turbo::Money::parse(loan.getValueOfTotalOverpaid()).value_or(turbo::Money()) + remaining)
                .toString(false));
    }

    // A loan is fully settled once every installment's principal+interest
    // obligation is met, not merely when principal-paid reaches
    // principal-disbursed (interest/fees/penalties may still be
    // outstanding on the final installment). Recompute from the
    // (already-updated-in-memory) installment list rather than trusting a
    // single aggregate comparison.
    turbo::Money openObligation;
    for (const auto &inst : installments) {
        auto pDue = turbo::Money::parse(inst.getValueOfPrincipalAmount()).value_or(turbo::Money());
        auto pPaid = turbo::Money::parse(inst.getValueOfPrincipalCompletedDerived()).value_or(turbo::Money());
        auto iDue = turbo::Money::parse(inst.getValueOfInterestAmount()).value_or(turbo::Money());
        auto iPaid = turbo::Money::parse(inst.getValueOfInterestCompletedDerived()).value_or(turbo::Money());
        if (pDue > pPaid) openObligation += (pDue - pPaid);
        if (iDue > iPaid) openObligation += (iDue - iPaid);
    }
    bool disbursed = !turbo::Money::parse(loan.getValueOfPrincipalDisbursed())
                          .value_or(turbo::Money())
                          .isZero();
    if (disbursed && openObligation.isZero()) {
        loan.setStatus(overpaid ? kLOverpaid : kLClosed);
        if (loan.getValueOfStatus() == kLClosed) loan.setClosedOnDate(Date::now());
    }
    co_await Mapper<m::Loan>(txn).update(loan);
    co_return alloc;
}

drogon::Task<std::string> PortfolioService::classifyLoanDelinquency(Txn txn,
                                                                    const std::string &loanId,
                                                                    const std::string &asOfDate) {
    auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
    if (loan.getValueOfStatus() != kLActive) co_return "";
    auto product = co_await Mapper<m::LoanProduct>(txn).findByPrimaryKey(loan.getValueOfProductId());

    auto installments = co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).findBy(
        Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, loanId));
    const Date now = dateOr(asOfDate, Date::now());
    int overdueDays = 0;
    for (const auto &inst : installments) {
        if (inst.getValueOfCompletedDerived()) continue;
        if (inst.getValueOfDueDate().microSecondsSinceEpoch() < now.microSecondsSinceEpoch()) {
            int days = static_cast<int>(
                (now.microSecondsSinceEpoch() - inst.getValueOfDueDate().microSecondsSinceEpoch()) /
                (86400LL * 1000000LL));
            overdueDays = std::max(overdueDays, days);
        }
    }

    bool wasNpa = loan.getValueOfIsNpa();
    bool isNpa = overdueDays >= product.getValueOfOverdueDaysForNpa();
    std::string newRangeId;

    if (product.getDelinquencyBucketId()) {
        auto bucketRanges = co_await Mapper<m::DelinquencyBucketRange>(txn).findBy(
            Criteria(m::DelinquencyBucketRange::Cols::_delinquency_bucket_id,
                    product.getValueOfDelinquencyBucketId()));
        for (const auto &br : bucketRanges) {
            auto range = co_await Mapper<m::DelinquencyRange>(txn).findByPrimaryKey(
                br.getValueOfDelinquencyRangeId());
            bool inRange = overdueDays >= range.getValueOfMinOverdueDays() &&
                           (!range.getMaxOverdueDays() || overdueDays <= range.getValueOfMaxOverdueDays());
            if (inRange) {
                newRangeId = range.getValueOfId();
                break;
            }
        }
    }

    const std::string prevRangeId = loan.getDelinquencyRangeId() ? loan.getValueOfDelinquencyRangeId() : "";
    if (newRangeId == prevRangeId && isNpa == wasNpa) co_return "";

    if (!prevRangeId.empty() && prevRangeId != newRangeId) {
        // Close out the previous tag period.
        auto history = co_await Mapper<m::LoanDelinquencyTagHistory>(txn).findBy(
            Criteria(m::LoanDelinquencyTagHistory::Cols::_loan_id, loanId));
        for (auto &h : history) {
            if (h.getValueOfDelinquencyRangeId() == prevRangeId && !h.getLiftoffDate()) {
                h.setLiftoffDate(now);
                co_await Mapper<m::LoanDelinquencyTagHistory>(txn).update(h);
            }
        }
    }
    if (!newRangeId.empty() && newRangeId != prevRangeId) {
        m::LoanDelinquencyTagHistory tag;
        tag.setLoanId(loanId);
        tag.setDelinquencyRangeId(newRangeId);
        tag.setClassificationDate(now);
        co_await Mapper<m::LoanDelinquencyTagHistory>(txn).insert(tag);
    }

    loan.setIsNpa(isNpa);
    if (!newRangeId.empty())
        loan.setDelinquencyRangeId(newRangeId);
    if (overdueDays > 0 && !loan.getOverdueSinceDate())
        loan.setOverdueSinceDate(now);
    else if (overdueDays == 0)
        loan.setOverdueSinceDateToNull();
    co_await Mapper<m::Loan>(txn).update(loan);
    co_return newRangeId;
}

// =====================================================================
// loan charges
// =====================================================================

drogon::Task<Json::Value> PortfolioService::loanChargeToJson(Txn txn, const std::string &id) {
    auto c = co_await Mapper<m::LoanCharge>(txn).findByPrimaryKey(id);
    Json::Value j;
    j["id"] = c.getValueOfId();
    j["loanId"] = c.getValueOfLoanId();
    j["chargeId"] = c.getValueOfChargeId();
    j["penalty"] = c.getValueOfIsPenalty();
    j["chargeTimeType"] = c.getValueOfChargeTimeType();
    j["chargeCalculationType"] = c.getValueOfChargeCalculationType();
    if (c.getDueDate()) j["dueDate"] = dateStr(c.getValueOfDueDate());
    if (c.getInstallmentNumber()) j["installmentNumber"] = c.getValueOfInstallmentNumber();
    j["amount"] = moneyJson(c.getValueOfAmount());
    j["amountPaid"] = moneyJson(c.getValueOfAmountPaidDerived());
    j["amountWaived"] = moneyJson(c.getValueOfAmountWaivedDerived());
    j["amountOutstanding"] = moneyJson(c.getValueOfAmountOutstandingDerived());
    j["paid"] = c.getValueOfIsPaidDerived();
    j["waived"] = c.getValueOfIsWaived();
    j["active"] = c.getValueOfIsActive();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::listLoanCharges(const turbo::RequestContext &ctx,
                                                           std::string idOrExternalId,
                                                           bool byExternalId) {
    requirePermission(ctx, "READ_LOANCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanCharge>(txn).findBy(Criteria(m::LoanCharge::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await loanChargeToJson(txn, r.getValueOfId()));
    co_return items;
}

Json::Value PortfolioService::loanChargeTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["chargeOptions"] = Json::Value(Json::arrayValue);
    return t;
}

drogon::Task<Json::Value> PortfolioService::getLoanCharge(const turbo::RequestContext &ctx,
                                                          std::string idOrExternalId, bool byExternalId,
                                                          std::string chargeIdOrExternalId,
                                                          bool chargeByExternalId) {
    requirePermission(ctx, "READ_LOANCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto chargeId = co_await resolveLoanChargeId(txn, loanId, chargeIdOrExternalId, chargeByExternalId);
    try {
        co_return co_await loanChargeToJson(txn, chargeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan charge not found", "error.msg.loancharge.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createLoanCharge(const turbo::RequestContext &ctx,
                                                             std::string idOrExternalId,
                                                             bool byExternalId, Json::Value body) {
    requirePermission(ctx, "CREATE_LOANCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::LoanCharge row;
    row.setLoanId(loanId);
    row.setChargeId(asStringOr(body, "chargeId"));
    row.setIsPenalty(asBoolOr(body, "penalty", false));
    row.setChargeTimeType(asIntOr(body, "chargeTimeType", kChargeTimeSpecifiedDueDate));
    row.setChargeCalculationType(asIntOr(body, "chargeCalculationType", 1));
    if (body.isMember("dueDate")) row.setDueDate(dateOr(asStringOr(body, "dueDate"), Date::now()));
    if (body.isMember("installmentNumber")) row.setInstallmentNumber(asIntOr(body, "installmentNumber", 0));
    auto amt = moneyOr(body, "amount");
    row.setAmount(amt.toString(false));
    row.setAmountOutstandingDerived(amt.toString(false));
    row = co_await Mapper<m::LoanCharge>(txn).insert(row);

    auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
    auto field = row.getValueOfIsPenalty() ? turbo::Money::parse(loan.getValueOfPenaltyChargesCharged())
                                           : turbo::Money::parse(loan.getValueOfFeeChargesCharged());
    auto updated = (field.value_or(turbo::Money()) + amt).toString(false);
    if (row.getValueOfIsPenalty())
        loan.setPenaltyChargesCharged(updated);
    else
        loan.setFeeChargesCharged(updated);
    co_await Mapper<m::Loan>(txn).update(loan);

    co_await turbo::outbox::writeEvent(txn, ctx, "loancharge", row.getValueOfId(), "loancharge.created",
                                       body);
    co_return co_await loanChargeToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> PortfolioService::updateLoanCharge(const turbo::RequestContext &ctx,
                                                             std::string idOrExternalId,
                                                             bool byExternalId,
                                                             std::string chargeIdOrExternalId,
                                                             bool chargeByExternalId, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto chargeId = co_await resolveLoanChargeId(txn, loanId, chargeIdOrExternalId, chargeByExternalId);
    m::LoanCharge row;
    try {
        row = co_await Mapper<m::LoanCharge>(txn).findByPrimaryKey(chargeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan charge not found", "error.msg.loancharge.not.found");
    }
    if (body.isMember("amount")) {
        auto amt = moneyOr(body, "amount");
        row.setAmount(amt.toString(false));
        row.setAmountOutstandingDerived(
            (amt - turbo::Money::parse(row.getValueOfAmountPaidDerived()).value_or(turbo::Money()))
                .toString(false));
    }
    if (body.isMember("dueDate")) row.setDueDate(dateOr(asStringOr(body, "dueDate"), Date::now()));
    co_await Mapper<m::LoanCharge>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loancharge", chargeId, "loancharge.updated", body);
    co_return co_await loanChargeToJson(txn, chargeId);
}

drogon::Task<Json::Value> PortfolioService::handleLoanChargeCommand(
    const turbo::RequestContext &ctx, std::string idOrExternalId, bool byExternalId,
    std::string chargeIdOrExternalId, bool chargeByExternalId, std::string command,
    Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto chargeId = co_await resolveLoanChargeId(txn, loanId, chargeIdOrExternalId, chargeByExternalId);
    m::LoanCharge row;
    try {
        row = co_await Mapper<m::LoanCharge>(txn).findByPrimaryKey(chargeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan charge not found", "error.msg.loancharge.not.found");
    }
    auto outstanding = turbo::Money::parse(row.getValueOfAmountOutstandingDerived()).value_or(turbo::Money());
    if (command == "pay") {
        auto payAmount = body.isMember("amount") ? moneyOr(body, "amount") : outstanding;
        row.setAmountPaidDerived(
            (turbo::Money::parse(row.getValueOfAmountPaidDerived()).value_or(turbo::Money()) + payAmount)
                .toString(false));
        row.setAmountOutstandingDerived((outstanding - payAmount).toString(false));
        row.setIsPaidDerived(outstanding <= payAmount);

        m::LoanTransaction t;
        t.setLoanId(loanId);
        t.setTransactionType(kTxnChargePayment);
        t.setTransactionDate(dateOr(asStringOr(body, "transactionDate"), Date::now()));
        t.setAmount(payAmount.toString(false));
        if (row.getValueOfIsPenalty())
            t.setPenaltyChargesPortion(payAmount.toString(false));
        else
            t.setFeeChargesPortion(payAmount.toString(false));
        t.setCreatedBy(userIdOr(ctx));
        co_await Mapper<m::LoanTransaction>(txn).insert(t);
    } else if (command == "waive") {
        row.setAmountWaivedDerived(
            (turbo::Money::parse(row.getValueOfAmountWaivedDerived()).value_or(turbo::Money()) + outstanding)
                .toString(false));
        row.setAmountOutstandingDerived("0.000000");
        row.setIsWaived(true);
    } else if (command == "adjustment" || command == "adjust") {
        row.setAmount(moneyOr(body, "amount", turbo::Money::parse(row.getValueOfAmount()).value_or(turbo::Money()))
                         .toString(false));
    } else {
        throw ApiError(drogon::k400BadRequest, "Unknown loan charge command: " + command,
                       "error.msg.loancharge.command.unknown");
    }
    co_await Mapper<m::LoanCharge>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loancharge", chargeId, "loancharge." + command, body);
    co_return co_await loanChargeToJson(txn, chargeId);
}

drogon::Task<void> PortfolioService::deleteLoanCharge(const turbo::RequestContext &ctx,
                                                     std::string idOrExternalId, bool byExternalId,
                                                     std::string chargeIdOrExternalId,
                                                     bool chargeByExternalId) {
    requirePermission(ctx, "DELETE_LOANCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto chargeId = co_await resolveLoanChargeId(txn, loanId, chargeIdOrExternalId, chargeByExternalId);
    try {
        co_await Mapper<m::LoanCharge>(txn).deleteByPrimaryKey(chargeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan charge not found", "error.msg.loancharge.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loancharge", chargeId, "loancharge.deleted",
                                       Json::Value());
}

// =====================================================================
// loan collaterals + guarantors + disbursement details
// =====================================================================

namespace {
Json::Value collateralJson(const m::LoanCollateral &c) {
    Json::Value j;
    j["id"] = c.getValueOfId();
    j["loanId"] = c.getValueOfLoanId();
    j["type"] = c.getValueOfCollateralTypeId();
    if (c.getValue()) j["value"] = moneyJson(c.getValueOfValue());
    if (c.getDescription()) j["description"] = c.getValueOfDescription();
    return j;
}
Json::Value guarantorJson(const m::LoanGuarantor &g) {
    Json::Value j;
    j["id"] = g.getValueOfId();
    j["loanId"] = g.getValueOfLoanId();
    j["guarantorType"] = g.getValueOfGuarantorType();
    if (g.getClientId()) j["clientId"] = g.getValueOfClientId();
    if (g.getFirstName()) j["firstname"] = g.getValueOfFirstName();
    if (g.getLastName()) j["lastname"] = g.getValueOfLastName();
    if (g.getAddressLine1()) j["addressLine1"] = g.getValueOfAddressLine1();
    if (g.getCity()) j["city"] = g.getValueOfCity();
    if (g.getMobileNumber()) j["mobileNumber"] = g.getValueOfMobileNumber();
    if (g.getAmount()) j["amount"] = moneyJson(g.getValueOfAmount());
    return j;
}
Json::Value disbursementJson(const m::LoanDisbursementDetail &d) {
    Json::Value j;
    j["id"] = d.getValueOfId();
    j["loanId"] = d.getValueOfLoanId();
    j["expectedDisbursementDate"] = dateStr(d.getValueOfExpectedDisburseDate());
    if (d.getActualDisburseDate()) j["actualDisbursementDate"] = dateStr(d.getValueOfActualDisburseDate());
    j["principal"] = moneyJson(d.getValueOfPrincipal());
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listLoanCollaterals(const turbo::RequestContext &ctx,
                                                                std::string idOrExternalId,
                                                                bool byExternalId) {
    requirePermission(ctx, "READ_LOANCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows =
        co_await Mapper<m::LoanCollateral>(txn).findBy(Criteria(m::LoanCollateral::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(collateralJson(r));
    co_return items;
}

Json::Value PortfolioService::loanCollateralTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["collateralOptions"] = Json::Value(Json::arrayValue);
    return t;
}

drogon::Task<Json::Value> PortfolioService::getLoanCollateral(const turbo::RequestContext &ctx,
                                                              std::string idOrExternalId,
                                                              bool byExternalId,
                                                              std::string collateralId) {
    requirePermission(ctx, "READ_LOANCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return collateralJson(co_await Mapper<m::LoanCollateral>(txn).findByPrimaryKey(collateralId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan collateral not found",
                       "error.msg.loancollateral.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createLoanCollateral(const turbo::RequestContext &ctx,
                                                                 std::string idOrExternalId,
                                                                 bool byExternalId, Json::Value body) {
    requirePermission(ctx, "CREATE_LOANCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::LoanCollateral row;
    row.setLoanId(loanId);
    row.setCollateralTypeId(asStringOr(body, "type"));
    if (body.isMember("value")) row.setValue(moneyOr(body, "value").toString(false));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    row = co_await Mapper<m::LoanCollateral>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loancollateral", row.getValueOfId(),
                                       "loancollateral.created", body);
    co_return collateralJson(row);
}

drogon::Task<Json::Value> PortfolioService::updateLoanCollateral(const turbo::RequestContext &ctx,
                                                                 std::string idOrExternalId,
                                                                 bool byExternalId,
                                                                 std::string collateralId,
                                                                 Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanCollateral row;
    try {
        row = co_await Mapper<m::LoanCollateral>(txn).findByPrimaryKey(collateralId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan collateral not found",
                       "error.msg.loancollateral.not.found");
    }
    if (body.isMember("value")) row.setValue(moneyOr(body, "value").toString(false));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    co_await Mapper<m::LoanCollateral>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loancollateral", collateralId,
                                       "loancollateral.updated", body);
    co_return collateralJson(row);
}

drogon::Task<void> PortfolioService::deleteLoanCollateral(const turbo::RequestContext &ctx,
                                                         std::string collateralId) {
    requirePermission(ctx, "DELETE_LOANCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::LoanCollateral>(txn).deleteByPrimaryKey(collateralId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan collateral not found",
                       "error.msg.loancollateral.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loancollateral", collateralId,
                                       "loancollateral.deleted", Json::Value());
}

drogon::Task<Json::Value> PortfolioService::getLoanCollateralManagement(
    const turbo::RequestContext &ctx, std::string collateralId) {
    co_return co_await getLoanCollateral(ctx, "", false, collateralId);
}

drogon::Task<Json::Value> PortfolioService::listLoanGuarantors(const turbo::RequestContext &ctx,
                                                              std::string idOrExternalId,
                                                              bool byExternalId) {
    requirePermission(ctx, "READ_LOANGUARANTOR");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows =
        co_await Mapper<m::LoanGuarantor>(txn).findBy(Criteria(m::LoanGuarantor::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(guarantorJson(r));
    co_return items;
}

Json::Value PortfolioService::loanGuarantorTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["guarantorTypeOptions"] = Json::Value(Json::arrayValue);
    return t;
}

drogon::Task<Json::Value> PortfolioService::getLoanGuarantor(const turbo::RequestContext &ctx,
                                                             std::string idOrExternalId,
                                                             bool byExternalId,
                                                             std::string guarantorId) {
    requirePermission(ctx, "READ_LOANGUARANTOR");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return guarantorJson(co_await Mapper<m::LoanGuarantor>(txn).findByPrimaryKey(guarantorId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan guarantor not found",
                       "error.msg.loanguarantor.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createLoanGuarantor(const turbo::RequestContext &ctx,
                                                                std::string idOrExternalId,
                                                                bool byExternalId, Json::Value body) {
    requirePermission(ctx, "CREATE_LOANGUARANTOR");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::LoanGuarantor row;
    row.setLoanId(loanId);
    row.setGuarantorType(asIntOr(body, "guarantorType", 1));
    if (body.isMember("clientId")) row.setClientId(asStringOr(body, "clientId"));
    if (body.isMember("firstname")) row.setFirstName(asStringOr(body, "firstname"));
    if (body.isMember("lastname")) row.setLastName(asStringOr(body, "lastname"));
    if (body.isMember("addressLine1")) row.setAddressLine1(asStringOr(body, "addressLine1"));
    if (body.isMember("city")) row.setCity(asStringOr(body, "city"));
    if (body.isMember("mobileNumber")) row.setMobileNumber(asStringOr(body, "mobileNumber"));
    if (body.isMember("amount")) row.setAmount(moneyOr(body, "amount").toString(false));
    row = co_await Mapper<m::LoanGuarantor>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loanguarantor", row.getValueOfId(),
                                       "loanguarantor.created", body);
    co_return guarantorJson(row);
}

drogon::Task<Json::Value> PortfolioService::updateLoanGuarantor(const turbo::RequestContext &ctx,
                                                                std::string idOrExternalId,
                                                                bool byExternalId,
                                                                std::string guarantorId,
                                                                Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANGUARANTOR");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanGuarantor row;
    try {
        row = co_await Mapper<m::LoanGuarantor>(txn).findByPrimaryKey(guarantorId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan guarantor not found",
                       "error.msg.loanguarantor.not.found");
    }
    if (body.isMember("firstname")) row.setFirstName(asStringOr(body, "firstname"));
    if (body.isMember("lastname")) row.setLastName(asStringOr(body, "lastname"));
    if (body.isMember("amount")) row.setAmount(moneyOr(body, "amount").toString(false));
    co_await Mapper<m::LoanGuarantor>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loanguarantor", guarantorId, "loanguarantor.updated",
                                       body);
    co_return guarantorJson(row);
}

drogon::Task<void> PortfolioService::deleteLoanGuarantor(const turbo::RequestContext &ctx,
                                                        std::string idOrExternalId, bool byExternalId,
                                                        std::string guarantorId) {
    requirePermission(ctx, "DELETE_LOANGUARANTOR");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::LoanGuarantor>(txn).deleteByPrimaryKey(guarantorId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan guarantor not found",
                       "error.msg.loanguarantor.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loanguarantor", guarantorId, "loanguarantor.deleted",
                                       Json::Value());
}

drogon::Task<Json::Value> PortfolioService::getLoanDisbursementDetail(const turbo::RequestContext &ctx,
                                                                      std::string idOrExternalId,
                                                                      bool byExternalId,
                                                                      std::string disbursementId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return disbursementJson(
            co_await Mapper<m::LoanDisbursementDetail>(txn).findByPrimaryKey(disbursementId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Disbursement detail not found",
                       "error.msg.loandisbursement.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::updateLoanDisbursementDate(
    const turbo::RequestContext &ctx, std::string idOrExternalId, bool byExternalId,
    std::string disbursementId, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanDisbursementDetail row;
    try {
        row = co_await Mapper<m::LoanDisbursementDetail>(txn).findByPrimaryKey(disbursementId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Disbursement detail not found",
                       "error.msg.loandisbursement.not.found");
    }
    if (body.isMember("expectedDisbursementDate"))
        row.setExpectedDisburseDate(dateOr(asStringOr(body, "expectedDisbursementDate"), Date::now()));
    if (body.isMember("principal")) row.setPrincipal(moneyOr(body, "principal").toString(false));
    co_await Mapper<m::LoanDisbursementDetail>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loandisbursement", disbursementId,
                                       "loandisbursement.updated", body);
    co_return disbursementJson(row);
}

drogon::Task<Json::Value> PortfolioService::editLoanDisbursements(const turbo::RequestContext &ctx,
                                                                  std::string idOrExternalId,
                                                                  bool byExternalId, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    if (body.isMember("disbursementDataId") && body.isMember("_delete")) {
        co_await Mapper<m::LoanDisbursementDetail>(txn).deleteByPrimaryKey(
            asStringOr(body, "disbursementDataId"));
    } else if (body.isMember("disbursementData") && body["disbursementData"].isArray()) {
        for (const auto &d : body["disbursementData"]) {
            m::LoanDisbursementDetail det;
            det.setLoanId(loanId);
            det.setExpectedDisburseDate(dateOr(asStringOr(d, "expectedDisbursementDate"), Date::now()));
            det.setPrincipal(moneyOr(d, "principal").toString(false));
            co_await Mapper<m::LoanDisbursementDetail>(txn).insert(det);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loandisbursement", loanId, "loandisbursement.edited",
                                       body);
    auto rows = co_await Mapper<m::LoanDisbursementDetail>(txn).findBy(
        Criteria(m::LoanDisbursementDetail::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(disbursementJson(r));
    co_return items;
}

// =====================================================================
// interest pauses, postdated checks, buydown fees, capitalized income,
// delinquency sub-resources
// =====================================================================

namespace {
Json::Value interestPauseJson(const m::LoanInterestPause &p) {
    Json::Value j;
    j["id"] = p.getValueOfId();
    j["loanId"] = p.getValueOfLoanId();
    if (p.getExternalId()) j["externalId"] = p.getValueOfExternalId();
    j["startDate"] = dateStr(p.getValueOfStartDate());
    j["endDate"] = dateStr(p.getValueOfEndDate());
    return j;
}
Json::Value postdatedCheckJson(const m::LoanPostdatedCheck &c) {
    Json::Value j;
    j["id"] = c.getValueOfId();
    j["loanId"] = c.getValueOfLoanId();
    if (c.getInstallmentId()) j["installmentId"] = c.getValueOfInstallmentId();
    j["checkNumber"] = c.getValueOfCheckNumber();
    if (c.getBankName()) j["bankName"] = c.getValueOfBankName();
    j["checkDate"] = dateStr(c.getValueOfCheckDate());
    j["amount"] = moneyJson(c.getValueOfAmount());
    j["status"] = c.getValueOfStatus();
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listInterestPauses(const turbo::RequestContext &ctx,
                                                               std::string idOrExternalId,
                                                               bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanInterestPause>(txn).findBy(
        Criteria(m::LoanInterestPause::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(interestPauseJson(r));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::createInterestPause(const turbo::RequestContext &ctx,
                                                                std::string idOrExternalId,
                                                                bool byExternalId, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::LoanInterestPause row;
    row.setLoanId(loanId);
    if (body.isMember("externalId")) row.setExternalId(asStringOr(body, "externalId"));
    row.setStartDate(dateOr(asStringOr(body, "startDate"), Date::now()));
    row.setEndDate(dateOr(asStringOr(body, "endDate"), Date::now()));
    row.setCreatedBy(userIdOr(ctx));
    row = co_await Mapper<m::LoanInterestPause>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loaninterestpause", row.getValueOfId(),
                                       "loaninterestpause.created", body);
    co_return interestPauseJson(row);
}

drogon::Task<Json::Value> PortfolioService::updateInterestPause(const turbo::RequestContext &ctx,
                                                                std::string idOrExternalId,
                                                                bool byExternalId,
                                                                std::string variationId,
                                                                Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanInterestPause row;
    try {
        row = co_await Mapper<m::LoanInterestPause>(txn).findByPrimaryKey(variationId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Interest pause not found",
                       "error.msg.loaninterestpause.not.found");
    }
    if (body.isMember("startDate")) row.setStartDate(dateOr(asStringOr(body, "startDate"), Date::now()));
    if (body.isMember("endDate")) row.setEndDate(dateOr(asStringOr(body, "endDate"), Date::now()));
    co_await Mapper<m::LoanInterestPause>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loaninterestpause", variationId,
                                       "loaninterestpause.updated", body);
    co_return interestPauseJson(row);
}

drogon::Task<void> PortfolioService::deleteInterestPause(const turbo::RequestContext &ctx,
                                                        std::string idOrExternalId, bool byExternalId,
                                                        std::string variationId) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::LoanInterestPause>(txn).deleteByPrimaryKey(variationId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Interest pause not found",
                       "error.msg.loaninterestpause.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loaninterestpause", variationId,
                                       "loaninterestpause.deleted", Json::Value());
}

drogon::Task<Json::Value> PortfolioService::listPostdatedChecks(const turbo::RequestContext &ctx,
                                                                std::string idOrExternalId,
                                                                bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanPostdatedCheck>(txn).findBy(
        Criteria(m::LoanPostdatedCheck::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(postdatedCheckJson(r));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getPostdatedCheck(const turbo::RequestContext &ctx,
                                                              std::string idOrExternalId,
                                                              bool byExternalId,
                                                              std::string installmentOrCheckId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return postdatedCheckJson(
            co_await Mapper<m::LoanPostdatedCheck>(txn).findByPrimaryKey(installmentOrCheckId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Post-dated check not found",
                       "error.msg.postdatedcheck.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createPostdatedCheck(const turbo::RequestContext &ctx,
                                                                 std::string idOrExternalId,
                                                                 bool byExternalId, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::LoanPostdatedCheck row;
    row.setLoanId(loanId);
    if (body.isMember("installmentId")) row.setInstallmentId(asStringOr(body, "installmentId"));
    row.setCheckNumber(asStringOr(body, "checkNumber"));
    if (body.isMember("bankName")) row.setBankName(asStringOr(body, "bankName"));
    row.setCheckDate(dateOr(asStringOr(body, "checkDate"), Date::now()));
    row.setAmount(moneyOr(body, "amount").toString(false));
    row.setStatus(asIntOr(body, "status", 1));
    row = co_await Mapper<m::LoanPostdatedCheck>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "postdatedcheck", row.getValueOfId(),
                                       "postdatedcheck.created", body);
    co_return postdatedCheckJson(row);
}

drogon::Task<Json::Value> PortfolioService::updatePostdatedCheck(const turbo::RequestContext &ctx,
                                                                 std::string checkId,
                                                                 Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanPostdatedCheck row;
    try {
        row = co_await Mapper<m::LoanPostdatedCheck>(txn).findByPrimaryKey(checkId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Post-dated check not found",
                       "error.msg.postdatedcheck.not.found");
    }
    if (body.isMember("status")) row.setStatus(asIntOr(body, "status", row.getValueOfStatus()));
    if (body.isMember("amount")) row.setAmount(moneyOr(body, "amount").toString(false));
    co_await Mapper<m::LoanPostdatedCheck>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "postdatedcheck", checkId, "postdatedcheck.updated",
                                       body);
    co_return postdatedCheckJson(row);
}

drogon::Task<void> PortfolioService::deletePostdatedCheck(const turbo::RequestContext &ctx,
                                                         std::string checkId) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::LoanPostdatedCheck>(txn).deleteByPrimaryKey(checkId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Post-dated check not found",
                       "error.msg.postdatedcheck.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "postdatedcheck", checkId, "postdatedcheck.deleted",
                                       Json::Value());
}

drogon::Task<Json::Value> PortfolioService::listBuydownFees(const turbo::RequestContext &ctx,
                                                           std::string idOrExternalId,
                                                           bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanBuydownFee>(txn).findBy(
        Criteria(m::LoanBuydownFee::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["loanId"] = r.getValueOfLoanId();
        if (r.getLoanTransactionId()) j["loanTransactionId"] = r.getValueOfLoanTransactionId();
        j["amount"] = moneyJson(r.getValueOfAmount());
        j["amortizedAmount"] = moneyJson(r.getValueOfAmortizedAmount());
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getBuydownFee(const turbo::RequestContext &ctx,
                                                          std::string idOrExternalId,
                                                          bool byExternalId,
                                                          std::string txnIdOrExternalId,
                                                          bool txnByExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto loanTxnId = co_await resolveLoanTransactionId(txn, loanId, txnIdOrExternalId, txnByExternalId);
    auto rows = co_await Mapper<m::LoanBuydownFee>(txn).findBy(
        Criteria(m::LoanBuydownFee::Cols::_loan_transaction_id, loanTxnId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Buydown fee not found", "error.msg.buydownfee.not.found");
    const auto &r = rows.front();
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["loanId"] = r.getValueOfLoanId();
    j["amount"] = moneyJson(r.getValueOfAmount());
    j["amortizedAmount"] = moneyJson(r.getValueOfAmortizedAmount());
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::listCapitalizedIncome(const turbo::RequestContext &ctx,
                                                                  std::string idOrExternalId,
                                                                  bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanCapitalizedIncome>(txn).findBy(
        Criteria(m::LoanCapitalizedIncome::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["loanId"] = r.getValueOfLoanId();
        j["incomeType"] = r.getValueOfIncomeType();
        j["amount"] = moneyJson(r.getValueOfAmount());
        j["amortizedAmount"] = moneyJson(r.getValueOfAmortizedAmount());
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getCapitalizedIncome(const turbo::RequestContext &ctx,
                                                                 std::string idOrExternalId,
                                                                 bool byExternalId,
                                                                 std::string txnIdOrExternalId,
                                                                 bool txnByExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto loanTxnId = co_await resolveLoanTransactionId(txn, loanId, txnIdOrExternalId, txnByExternalId);
    auto rows = co_await Mapper<m::LoanCapitalizedIncome>(txn).findBy(
        Criteria(m::LoanCapitalizedIncome::Cols::_loan_transaction_id, loanTxnId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Capitalized income not found",
                       "error.msg.capitalizedincome.not.found");
    const auto &r = rows.front();
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["loanId"] = r.getValueOfLoanId();
    j["amount"] = moneyJson(r.getValueOfAmount());
    j["amortizedAmount"] = moneyJson(r.getValueOfAmortizedAmount());
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::listDelinquencyActions(const turbo::RequestContext &ctx,
                                                                   std::string idOrExternalId,
                                                                   bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanDelinquencyAction>(txn).findBy(
        Criteria(m::LoanDelinquencyAction::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["action"] = r.getValueOfAction();
        j["startDate"] = dateStr(r.getValueOfStartDate());
        if (r.getEndDate()) j["endDate"] = dateStr(r.getValueOfEndDate());
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::createDelinquencyAction(const turbo::RequestContext &ctx,
                                                                    std::string idOrExternalId,
                                                                    bool byExternalId,
                                                                    Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    m::LoanDelinquencyAction row;
    row.setLoanId(loanId);
    row.setAction(asIntOr(body, "action", 1));
    row.setStartDate(dateOr(asStringOr(body, "startDate"), Date::now()));
    if (body.isMember("endDate")) row.setEndDate(dateOr(asStringOr(body, "endDate"), Date::now()));
    row.setCreatedBy(userIdOr(ctx));
    row = co_await Mapper<m::LoanDelinquencyAction>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loandelinquencyaction", row.getValueOfId(),
                                       "loandelinquencyaction.created", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["action"] = row.getValueOfAction();
    j["startDate"] = dateStr(row.getValueOfStartDate());
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::listDelinquencyTagHistory(const turbo::RequestContext &ctx,
                                                                      std::string idOrExternalId,
                                                                      bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanDelinquencyTagHistory>(txn).findBy(
        Criteria(m::LoanDelinquencyTagHistory::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["delinquencyRangeId"] = r.getValueOfDelinquencyRangeId();
        j["classificationDate"] = dateStr(r.getValueOfClassificationDate());
        if (r.getLiftoffDate()) j["liftoffDate"] = dateStr(r.getValueOfLiftoffDate());
        items.append(j);
    }
    co_return items;
}

// =====================================================================
// loan transactions
// =====================================================================

namespace {
Json::Value loanTxnJson(const m::LoanTransaction &t) {
    Json::Value j;
    j["id"] = t.getValueOfId();
    j["loanId"] = t.getValueOfLoanId();
    if (t.getExternalId()) j["externalId"] = t.getValueOfExternalId();
    j["type"] = t.getValueOfTransactionType();
    j["date"] = dateStr(t.getValueOfTransactionDate());
    j["amount"] = moneyJson(t.getValueOfAmount());
    j["principalPortion"] = moneyJson(t.getValueOfPrincipalPortion());
    j["interestPortion"] = moneyJson(t.getValueOfInterestPortion());
    j["feeChargesPortion"] = moneyJson(t.getValueOfFeeChargesPortion());
    j["penaltyChargesPortion"] = moneyJson(t.getValueOfPenaltyChargesPortion());
    j["overpaymentPortion"] = moneyJson(t.getValueOfOverpaymentPortion());
    j["reversed"] = t.getValueOfIsReversed();
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::loanTransactionToJson(Txn txn, const std::string &id) {
    co_return loanTxnJson(co_await Mapper<m::LoanTransaction>(txn).findByPrimaryKey(id));
}

drogon::Task<Json::Value> PortfolioService::listLoanTransactions(const turbo::RequestContext &ctx,
                                                                 std::string idOrExternalId,
                                                                 bool byExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto rows = co_await Mapper<m::LoanTransaction>(txn).orderBy(m::LoanTransaction::Cols::_transaction_date)
                    .findBy(Criteria(m::LoanTransaction::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(loanTxnJson(r));
    co_return items;
}

Json::Value PortfolioService::loanTransactionTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["transactionDate"] = dateStr(Date::now());
    return t;
}

drogon::Task<Json::Value> PortfolioService::getLoanTransaction(const turbo::RequestContext &ctx,
                                                               std::string idOrExternalId,
                                                               bool byExternalId,
                                                               std::string txnIdOrExternalId,
                                                               bool txnByExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto loanTxnId = co_await resolveLoanTransactionId(txn, loanId, txnIdOrExternalId, txnByExternalId);
    try {
        co_return loanTxnJson(co_await Mapper<m::LoanTransaction>(txn).findByPrimaryKey(loanTxnId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan transaction not found",
                       "error.msg.loantransaction.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createLoanTransaction(const turbo::RequestContext &ctx,
                                                                  std::string idOrExternalId,
                                                                  bool byExternalId, std::string command,
                                                                  Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
    if (loan.getValueOfStatus() != kLActive)
        throw ApiError(drogon::k403Forbidden, "Loan must be active for this transaction",
                       "error.msg.loan.not.active");

    auto txnDate = dateOr(asStringOr(body, "transactionDate"), Date::now());
    auto amount = moneyOr(body, "transactionAmount", moneyOr(body, "amount"));

    auto emitEvent = [&](const m::LoanTransaction &t, const char *suffix) -> drogon::Task<void> {
        Json::Value evt = body;
        evt["loanId"] = loanId;
        evt["amount"] = t.getValueOfAmount();
        co_await turbo::outbox::writeEvent(txn, ctx, "loantransaction", t.getValueOfId(),
                                           std::string("loantransaction.") + suffix, evt);
    };

    if (command == "repayment" || command == "merchantIssuedRefund" || command == "payoutRefund" ||
        command == "goodwillCredit" || command == "recoveryPayment") {
        int type = command == "repayment"            ? kTxnRepayment
                   : command == "merchantIssuedRefund" ? kTxnMerchantIssuedRefund
                   : command == "payoutRefund"          ? kTxnPayoutRefund
                   : command == "goodwillCredit"         ? kTxnGoodwillCredit
                                                          : kTxnRecovery;
        auto alloc = co_await allocateRepayment(txn, loanId, amount.toString(false));
        m::LoanTransaction t;
        t.setLoanId(loanId);
        t.setTransactionType(type);
        t.setTransactionDate(txnDate);
        t.setAmount(amount.toString(false));
        t.setPrincipalPortion(alloc.principal);
        t.setInterestPortion(alloc.interest);
        t.setFeeChargesPortion(alloc.fees);
        t.setPenaltyChargesPortion(alloc.penalties);
        t.setCreatedBy(userIdOr(ctx));
        t = co_await Mapper<m::LoanTransaction>(txn).insert(t);
        if (command == "recoveryPayment") {
            auto reloaded = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
            reloaded.setTotalRecovered(
                (turbo::Money::parse(reloaded.getValueOfTotalRecovered()).value_or(turbo::Money()) + amount)
                    .toString(false));
            co_await Mapper<m::Loan>(txn).update(reloaded);
        }
        co_await classifyLoanDelinquency(txn, loanId, dateStr(txnDate));
        co_await emitEvent(t, "created");
        co_return loanTxnJson(t);
    } else if (command == "waiveInterest") {
        auto installments = co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).findBy(
            Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, loanId));
        std::sort(installments.begin(), installments.end(), [](const auto &a, const auto &b) {
            return a.getValueOfInstallmentNumber() < b.getValueOfInstallmentNumber();
        });
        turbo::Money remaining = amount;
        turbo::Money waived;
        for (auto &inst : installments) {
            if (remaining.isZero() || remaining.isNegative()) break;
            auto due = turbo::Money::parse(inst.getValueOfInterestAmount()).value_or(turbo::Money());
            auto paid =
                turbo::Money::parse(inst.getValueOfInterestCompletedDerived()).value_or(turbo::Money());
            auto outstanding = due - paid;
            if (outstanding.isNegative() || outstanding.isZero()) continue;
            auto portion = remaining < outstanding ? remaining : outstanding;
            remaining -= portion;
            waived += portion;
            inst.setInterestCompletedDerived((paid + portion).toString(false));
            co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).update(inst);
        }
        loan.setInterestWaived(
            (turbo::Money::parse(loan.getValueOfInterestWaived()).value_or(turbo::Money()) + waived)
                .toString(false));
        co_await Mapper<m::Loan>(txn).update(loan);

        m::LoanTransaction t;
        t.setLoanId(loanId);
        t.setTransactionType(kTxnWaiveInterest);
        t.setTransactionDate(txnDate);
        t.setAmount(waived.toString(false));
        t.setInterestPortion(waived.toString(false));
        t.setCreatedBy(userIdOr(ctx));
        t = co_await Mapper<m::LoanTransaction>(txn).insert(t);
        co_await emitEvent(t, "created");
        co_return loanTxnJson(t);
    } else if (command == "foreclosure" || command == "close") {
        // Pay off the full remaining principal+interest obligation as of
        // txnDate, then close the loan. Simplification vs. Fineract: we do
        // not pro-rate interest down to the exact foreclosure date (that
        // requires a full re-amortization against actual elapsed days,
        // which `recalculateLoanSchedule` already does on demand) — a
        // caller wanting an exact pro-rated foreclosure amount should call
        // recalculateLoanSchedule first, then foreclose.
        auto installments = co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).findBy(
            Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, loanId));
        turbo::Money totalOutstanding;
        for (const auto &inst : installments) {
            auto pDue = turbo::Money::parse(inst.getValueOfPrincipalAmount()).value_or(turbo::Money());
            auto pPaid =
                turbo::Money::parse(inst.getValueOfPrincipalCompletedDerived()).value_or(turbo::Money());
            auto iDue = turbo::Money::parse(inst.getValueOfInterestAmount()).value_or(turbo::Money());
            auto iPaid =
                turbo::Money::parse(inst.getValueOfInterestCompletedDerived()).value_or(turbo::Money());
            if (pDue > pPaid) totalOutstanding += (pDue - pPaid);
            if (iDue > iPaid) totalOutstanding += (iDue - iPaid);
        }
        auto alloc = co_await allocateRepayment(txn, loanId, totalOutstanding.toString(false));
        m::LoanTransaction t;
        t.setLoanId(loanId);
        t.setTransactionType(kTxnRepayment);
        t.setTransactionDate(txnDate);
        t.setAmount(totalOutstanding.toString(false));
        t.setPrincipalPortion(alloc.principal);
        t.setInterestPortion(alloc.interest);
        t.setCreatedBy(userIdOr(ctx));
        t = co_await Mapper<m::LoanTransaction>(txn).insert(t);
        auto reloaded = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
        reloaded.setStatus(kLClosed);
        reloaded.setClosedOnDate(txnDate);
        co_await Mapper<m::Loan>(txn).update(reloaded);
        co_await emitEvent(t, "created");
        co_return loanTxnJson(t);
    } else if (command == "chargeOff") {
        co_return co_await handleLoanCommand(ctx, idOrExternalId, byExternalId, "chargeOff", body);
    } else if (command == "reAmortize") {
        co_await recalculateLoanSchedule(ctx, idOrExternalId, byExternalId, body);
        m::LoanTransaction t;
        t.setLoanId(loanId);
        t.setTransactionType(kTxnReAmortize);
        t.setTransactionDate(txnDate);
        t.setAmount("0.000000");
        t.setCreatedBy(userIdOr(ctx));
        t = co_await Mapper<m::LoanTransaction>(txn).insert(t);
        co_await emitEvent(t, "created");
        co_return loanTxnJson(t);
    } else if (command == "reAge") {
        // Simplified reAge: Fineract's reAge consolidates arrears into a
        // fresh schedule starting from the reAge date. We implement the
        // observable delinquency-management effect — clearing the current
        // overdue/NPA classification as of the reAge date — without
        // reshaping the installment schedule itself; a true reAge would
        // additionally rebuild the remaining installments around the
        // consolidated arrears amount.
        loan.setOverdueSinceDateToNull();
        loan.setIsNpa(false);
        co_await Mapper<m::Loan>(txn).update(loan);
        m::LoanTransaction t;
        t.setLoanId(loanId);
        t.setTransactionType(kTxnReAge);
        t.setTransactionDate(txnDate);
        t.setAmount("0.000000");
        t.setCreatedBy(userIdOr(ctx));
        t = co_await Mapper<m::LoanTransaction>(txn).insert(t);
        co_await emitEvent(t, "created");
        co_return loanTxnJson(t);
    } else if (command == "capitalizedIncome" || command == "buyDownFee") {
        m::LoanTransaction t;
        t.setLoanId(loanId);
        t.setTransactionType(command == "capitalizedIncome" ? kTxnCapitalizedIncome : kTxnBuyDownFee);
        t.setTransactionDate(txnDate);
        t.setAmount(amount.toString(false));
        t.setCreatedBy(userIdOr(ctx));
        t = co_await Mapper<m::LoanTransaction>(txn).insert(t);
        if (command == "capitalizedIncome") {
            m::LoanCapitalizedIncome inc;
            inc.setLoanId(loanId);
            inc.setLoanTransactionId(t.getValueOfId());
            inc.setIncomeType(asStringOr(body, "incomeType", "fee"));
            inc.setAmount(amount.toString(false));
            inc.setAmortizedAmount("0.000000");
            co_await Mapper<m::LoanCapitalizedIncome>(txn).insert(inc);
            loan.setCapitalizedIncomeAmount(
                (turbo::Money::parse(loan.getValueOfCapitalizedIncomeAmount()).value_or(turbo::Money()) +
                 amount)
                    .toString(false));
        } else {
            m::LoanBuydownFee fee;
            fee.setLoanId(loanId);
            fee.setLoanTransactionId(t.getValueOfId());
            fee.setAmount(amount.toString(false));
            fee.setAmortizedAmount("0.000000");
            co_await Mapper<m::LoanBuydownFee>(txn).insert(fee);
            loan.setBuydownFeeAmount(
                (turbo::Money::parse(loan.getValueOfBuydownFeeAmount()).value_or(turbo::Money()) + amount)
                    .toString(false));
        }
        co_await Mapper<m::Loan>(txn).update(loan);
        co_await emitEvent(t, "created");
        co_return loanTxnJson(t);
    }
    throw ApiError(drogon::k400BadRequest, "Unknown loan transaction command: " + command,
                   "error.msg.loantransaction.command.unknown");
}

drogon::Task<void> PortfolioService::replayLoanTransactions(Txn txn, const std::string &loanId) {
    auto installments = co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).findBy(
        Criteria(m::LoanRepaymentScheduleInstallment::Cols::_loan_id, loanId));
    for (auto &inst : installments) {
        inst.setPrincipalCompletedDerived("0.000000");
        inst.setInterestCompletedDerived("0.000000");
        inst.setCompletedDerived(false);
        co_await Mapper<m::LoanRepaymentScheduleInstallment>(txn).update(inst);
    }
    auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
    loan.setPrincipalPaid("0.000000");
    loan.setInterestPaid("0.000000");
    loan.setTotalOverpaid("0.000000");
    if (loan.getValueOfStatus() == kLClosed || loan.getValueOfStatus() == kLOverpaid)
        loan.setStatus(kLActive);
    co_await Mapper<m::Loan>(txn).update(loan);

    auto rows = co_await Mapper<m::LoanTransaction>(txn)
                    .orderBy(m::LoanTransaction::Cols::_transaction_date)
                    .findBy(Criteria(m::LoanTransaction::Cols::_loan_id, loanId));
    for (const auto &t : rows) {
        if (t.getValueOfIsReversed()) continue;
        int type = t.getValueOfTransactionType();
        if (type == kTxnRepayment || type == kTxnMerchantIssuedRefund || type == kTxnPayoutRefund ||
            type == kTxnGoodwillCredit || type == kTxnRecovery) {
            co_await allocateRepayment(txn, loanId, t.getValueOfAmount());
        }
    }
}

drogon::Task<Json::Value> PortfolioService::adjustLoanTransaction(const turbo::RequestContext &ctx,
                                                                  std::string idOrExternalId,
                                                                  bool byExternalId,
                                                                  std::string txnIdOrExternalId,
                                                                  bool txnByExternalId, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto loanTxnId = co_await resolveLoanTransactionId(txn, loanId, txnIdOrExternalId, txnByExternalId);
    m::LoanTransaction row;
    try {
        row = co_await Mapper<m::LoanTransaction>(txn).findByPrimaryKey(loanTxnId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan transaction not found",
                       "error.msg.loantransaction.not.found");
    }
    row.setIsReversed(true);
    row.setReversedOnDate(Date::now());
    co_await Mapper<m::LoanTransaction>(txn).update(row);

    m::LoanTransaction replacement;
    bool createdReplacement = false;
    if (body.isMember("transactionAmount") || body.isMember("transactionDate")) {
        auto amount = moneyOr(body, "transactionAmount",
                              turbo::Money::parse(row.getValueOfAmount()).value_or(turbo::Money()));
        replacement.setLoanId(loanId);
        replacement.setTransactionType(row.getValueOfTransactionType());
        replacement.setTransactionDate(dateOr(asStringOr(body, "transactionDate"),
                                              row.getValueOfTransactionDate()));
        replacement.setAmount(amount.toString(false));
        replacement.setCreatedBy(userIdOr(ctx));
        replacement = co_await Mapper<m::LoanTransaction>(txn).insert(replacement);
        createdReplacement = true;
    }
    co_await replayLoanTransactions(txn, loanId);
    co_await classifyLoanDelinquency(txn, loanId, dateStr(Date::now()));
    co_await turbo::outbox::writeEvent(txn, ctx, "loantransaction", loanTxnId, "loantransaction.adjusted",
                                       body);
    co_return loanTxnJson(createdReplacement ? replacement : row);
}

drogon::Task<Json::Value> PortfolioService::undoWaiveChargeTransaction(const turbo::RequestContext &ctx,
                                                                       std::string idOrExternalId,
                                                                       bool byExternalId,
                                                                       std::string txnIdOrExternalId,
                                                                       bool txnByExternalId) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, idOrExternalId, byExternalId);
    auto loanTxnId = co_await resolveLoanTransactionId(txn, loanId, txnIdOrExternalId, txnByExternalId);
    m::LoanTransaction row;
    try {
        row = co_await Mapper<m::LoanTransaction>(txn).findByPrimaryKey(loanTxnId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan transaction not found",
                       "error.msg.loantransaction.not.found");
    }
    row.setIsReversed(true);
    row.setReversedOnDate(Date::now());
    co_await Mapper<m::LoanTransaction>(txn).update(row);
    if (row.getValueOfTransactionType() == kTxnWaiveInterest) {
        auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanId);
        loan.setInterestWaived((turbo::Money::parse(loan.getValueOfInterestWaived()).value_or(turbo::Money()) -
                                turbo::Money::parse(row.getValueOfInterestPortion()).value_or(turbo::Money()))
                                   .toString(false));
        co_await Mapper<m::Loan>(txn).update(loan);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loantransaction", loanTxnId,
                                       "loantransaction.undo-waive-charge", Json::Value());
    co_return loanTxnJson(row);
}

// =====================================================================
// loan reassignment, GLIM, COB catch-up (honest scoping — see notes)
// =====================================================================

Json::Value PortfolioService::loanReassignmentTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["loanOfficerOptions"] = Json::Value(Json::arrayValue);
    return t;
}

drogon::Task<Json::Value> PortfolioService::reassignLoans(const turbo::RequestContext &ctx,
                                                          Json::Value body) {
    requirePermission(ctx, "ASSIGNSTAFF_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto fromLoanOfficerId = asStringOr(body, "fromLoanOfficerId");
    auto toLoanOfficerId = asStringOr(body, "toLoanOfficerId");
    if (fromLoanOfficerId.empty() || toLoanOfficerId.empty())
        throw ApiError(drogon::k400BadRequest, "fromLoanOfficerId and toLoanOfficerId are required",
                       "error.msg.loanreassignment.required.fields");
    int count = 0;
    if (body.isMember("loans") && body["loans"].isArray()) {
        for (const auto &loanRef : body["loans"]) {
            auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(loanRef.asString());
            loan.setLoanOfficerId(toLoanOfficerId);
            co_await Mapper<m::Loan>(txn).update(loan);
            ++count;
        }
    } else {
        auto loans = co_await Mapper<m::Loan>(txn).findBy(
            Criteria(m::Loan::Cols::_loan_officer_id, fromLoanOfficerId));
        for (auto &loan : loans) {
            loan.setLoanOfficerId(toLoanOfficerId);
            co_await Mapper<m::Loan>(txn).update(loan);
            ++count;
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "loanreassignment", toLoanOfficerId,
                                       "loanreassignment.done", body);
    Json::Value out;
    out["fromLoanOfficerId"] = fromLoanOfficerId;
    out["toLoanOfficerId"] = toLoanOfficerId;
    out["reassignedCount"] = count;
    co_return out;
}

drogon::Task<Json::Value> PortfolioService::getGlimAccount(const turbo::RequestContext &ctx,
                                                           std::string glimId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto parent = co_await Mapper<m::Loan>(txn).findByPrimaryKey(glimId);
    auto members = co_await Mapper<m::Loan>(txn).findBy(Criteria(m::Loan::Cols::_glim_parent_loan_id, glimId));
    Json::Value j = co_await loanToJson(txn, glimId);
    Json::Value memberLoans(Json::arrayValue);
    for (const auto &mLoan : members) memberLoans.append(co_await loanToJson(txn, mLoan.getValueOfId()));
    j["memberLoans"] = memberLoans;
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::handleGlimCommand(const turbo::RequestContext &ctx,
                                                              std::string glimId, std::string command,
                                                              Json::Value body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto members = co_await Mapper<m::Loan>(txn).findBy(Criteria(m::Loan::Cols::_glim_parent_loan_id, glimId));
    // GLIM member loans are driven through the exact same lifecycle state
    // machine as any individual loan (handleLoanCommand) — we simply fan
    // the same command out to the parent and every member.
    co_await handleLoanCommand(ctx, glimId, false, command, body);
    for (const auto &mLoan : members) {
        co_await handleLoanCommand(ctx, mLoan.getValueOfId(), false, command, body);
    }
    co_return co_await getGlimAccount(ctx, glimId);
}

namespace {
// In-process flag only — a real COB implementation would use a durable
// per-tenant job-run row (mirroring Fineract's m_job / COB business-date
// tables) so catch-up status survives a process restart and is visible
// across instances. This is an honest simplification: COB here means "run
// the delinquency/provisioning batch synchronously for any loans whose
// overdue classification may be stale", not a full business-date-rollover
// scheduler with per-loan locking.
bool g_cobRunning = false;
}  // namespace

drogon::Task<Json::Value> PortfolioService::runLoanCobCatchUp(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "UPDATE_LOAN");
    g_cobRunning = true;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto today = dateStr(Date::now());
    auto loans = co_await Mapper<m::Loan>(txn).findBy(Criteria(m::Loan::Cols::_status, kLActive));
    int processed = 0;
    for (const auto &loan : loans) {
        co_await classifyLoanDelinquency(txn, loan.getValueOfId(), today);
        ++processed;
    }
    g_cobRunning = false;
    Json::Value out;
    out["businessDate"] = today;
    out["loansProcessed"] = processed;
    co_return out;
}

Json::Value PortfolioService::isCobCatchUpRunning(const turbo::RequestContext &ctx) {
    Json::Value j;
    j["running"] = g_cobRunning;
    return j;
}

Json::Value PortfolioService::listLockedLoans(const turbo::RequestContext &ctx) {
    // No per-loan COB lock table exists (see g_cobRunning note above); a
    // loan is only ever "locked" for the instant of its own classification
    // update inside runLoanCobCatchUp, which is not independently
    // observable from outside that call. Always returns empty.
    return Json::Value(Json::arrayValue);
}

Json::Value PortfolioService::oldestCobClosedLoan(const turbo::RequestContext &ctx) {
    Json::Value j;
    j["businessDate"] = dateStr(Date::now());
    return j;
}

// =====================================================================
// reschedule loans
// =====================================================================

namespace {
Json::Value rescheduleRequestJson(const m::RescheduleLoanRequest &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["loanId"] = r.getValueOfLoanId();
    j["reasonCode"] = r.getValueOfReasonCode();
    if (r.getReasonComment()) j["reasonComment"] = r.getValueOfReasonComment();
    j["status"] = r.getValueOfStatus();
    if (r.getRescheduleFromInstallment()) j["rescheduleFromInstallment"] = r.getValueOfRescheduleFromInstallment();
    if (r.getRescheduleFromDate()) j["rescheduleFromDate"] = dateStr(r.getValueOfRescheduleFromDate());
    j["submittedOnDate"] = dateStr(r.getValueOfSubmittedOnDate());
    if (r.getExtraTerms()) j["extraTerms"] = r.getValueOfExtraTerms();
    if (r.getGraceOnPrincipal()) j["graceOnPrincipal"] = r.getValueOfGraceOnPrincipal();
    if (r.getGraceOnInterest()) j["graceOnInterest"] = r.getValueOfGraceOnInterest();
    if (r.getNewInterestRate()) j["newInterestRate"] = r.getValueOfNewInterestRate();
    if (r.getAdjustedDueDate()) j["adjustedDueDate"] = dateStr(r.getValueOfAdjustedDueDate());
    if (r.getApprovedOnDate()) j["approvedOnDate"] = dateStr(r.getValueOfApprovedOnDate());
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listRescheduleRequests(const turbo::RequestContext &ctx,
                                                                   const std::string &loanId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Json::Value items(Json::arrayValue);
    if (loanId.empty()) {
        auto rows = co_await Mapper<m::RescheduleLoanRequest>(txn).findAll();
        for (const auto &r : rows) items.append(rescheduleRequestJson(r));
    } else {
        auto rows = co_await Mapper<m::RescheduleLoanRequest>(txn).findBy(
            Criteria(m::RescheduleLoanRequest::Cols::_loan_id, loanId));
        for (const auto &r : rows) items.append(rescheduleRequestJson(r));
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::rescheduleRequestToJson(Txn txn, const std::string &id) {
    co_return rescheduleRequestJson(co_await Mapper<m::RescheduleLoanRequest>(txn).findByPrimaryKey(id));
}

drogon::Task<Json::Value> PortfolioService::getRescheduleRequest(const turbo::RequestContext &ctx,
                                                                 std::string id) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return rescheduleRequestJson(co_await Mapper<m::RescheduleLoanRequest>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Reschedule request not found",
                       "error.msg.rescheduleloan.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createRescheduleRequest(const turbo::RequestContext &ctx,
                                                                    Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, asStringOr(body, "loanId"), false);
    m::RescheduleLoanRequest row;
    row.setLoanId(loanId);
    row.setReasonCode(asStringOr(body, "rescheduleReasonCode", asStringOr(body, "rescheduleReasonId")));
    if (body.isMember("rescheduleReasonComment"))
        row.setReasonComment(asStringOr(body, "rescheduleReasonComment"));
    row.setStatus(100);  // pending-approval
    if (body.isMember("rescheduleFromDate"))
        row.setRescheduleFromDate(dateOr(asStringOr(body, "rescheduleFromDate"), Date::now()));
    row.setSubmittedOnDate(dateOr(asStringOr(body, "submittedOnDate"), Date::now()));
    row.setSubmittedBy(userIdOr(ctx));
    if (body.isMember("extraTerms")) row.setExtraTerms(asIntOr(body, "extraTerms", 0));
    if (body.isMember("graceOnPrincipal")) row.setGraceOnPrincipal(asIntOr(body, "graceOnPrincipal", 0));
    if (body.isMember("graceOnInterest")) row.setGraceOnInterest(asIntOr(body, "graceOnInterest", 0));
    if (body.isMember("newInterestRate")) row.setNewInterestRate(asStringOr(body, "newInterestRate"));
    if (body.isMember("adjustedDueDate"))
        row.setAdjustedDueDate(dateOr(asStringOr(body, "adjustedDueDate"), Date::now()));
    row = co_await Mapper<m::RescheduleLoanRequest>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "rescheduleloan", row.getValueOfId(),
                                       "rescheduleloan.created", body);
    co_return rescheduleRequestJson(row);
}

drogon::Task<Json::Value> PortfolioService::handleRescheduleCommand(const turbo::RequestContext &ctx,
                                                                    std::string id, std::string command,
                                                                    Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::RescheduleLoanRequest row;
    try {
        row = co_await Mapper<m::RescheduleLoanRequest>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Reschedule request not found",
                       "error.msg.rescheduleloan.not.found");
    }
    if (command == "reject") {
        row.setStatus(300);
        co_await Mapper<m::RescheduleLoanRequest>(txn).update(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "rescheduleloan", id, "rescheduleloan.rejected", body);
        co_return rescheduleRequestJson(row);
    }
    if (command != "approve")
        throw ApiError(drogon::k400BadRequest, "Unknown reschedule command: " + command,
                       "error.msg.rescheduleloan.command.unknown");

    row.setStatus(200);
    row.setApprovedOnDate(dateOr(asStringOr(body, "approvedOnDate"), Date::now()));
    row.setApprovedBy(userIdOr(ctx));
    co_await Mapper<m::RescheduleLoanRequest>(txn).update(row);

    // Apply the reschedule terms to the loan and rebuild its schedule.
    auto loan = co_await Mapper<m::Loan>(txn).findByPrimaryKey(row.getValueOfLoanId());
    if (row.getExtraTerms())
        loan.setNumberOfRepayments(loan.getValueOfNumberOfRepayments() + row.getValueOfExtraTerms());
    if (row.getNewInterestRate()) loan.setAnnualNominalInterestRate(row.getValueOfNewInterestRate());
    co_await Mapper<m::Loan>(txn).update(loan);
    Json::Value recalcBody;
    if (row.getGraceOnPrincipal()) recalcBody["graceOnPrincipalPayment"] = row.getValueOfGraceOnPrincipal();
    if (row.getGraceOnInterest()) recalcBody["graceOnInterestPayment"] = row.getValueOfGraceOnInterest();
    co_await recalculateLoanSchedule(ctx, row.getValueOfLoanId(), false, recalcBody);

    co_await turbo::outbox::writeEvent(txn, ctx, "rescheduleloan", id, "rescheduleloan.approved", body);
    co_return rescheduleRequestJson(row);
}

Json::Value PortfolioService::rescheduleTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["rescheduleReasonOptions"] = Json::Value(Json::arrayValue);
    return t;
}

// =====================================================================
// shares: products + product dividends + accounts
// =====================================================================

namespace {
Json::Value shareProductJson(const m::ShareProduct &p) {
    Json::Value j;
    j["id"] = p.getValueOfId();
    j["name"] = p.getValueOfName();
    j["shortName"] = p.getValueOfShortName();
    if (p.getDescription()) j["description"] = p.getValueOfDescription();
    j["currencyCode"] = p.getValueOfCurrencyCode();
    j["currencyDigits"] = p.getValueOfCurrencyDigits();
    j["totalShares"] = static_cast<Json::Int64>(p.getValueOfTotalShares());
    j["totalSharesToBeIssued"] = static_cast<Json::Int64>(p.getValueOfTotalSharesToBeIssued());
    j["nominalPrice"] = moneyJson(p.getValueOfNominalPrice());
    if (p.getMarketPrice()) j["marketPrice"] = moneyJson(p.getValueOfMarketPrice());
    j["shareCapitalType"] = p.getValueOfShareCapitalType();
    j["minimumShares"] = static_cast<Json::Int64>(p.getValueOfMinimumShares());
    j["defaultShares"] = static_cast<Json::Int64>(p.getValueOfDefaultShares());
    j["maximumShares"] = static_cast<Json::Int64>(p.getValueOfMaximumShares());
    j["allowDividendsForInactiveClients"] = p.getValueOfAllowDividendsForInactiveClients();
    if (p.getLockinPeriod()) j["lockinPeriod"] = p.getValueOfLockinPeriod();
    if (p.getLockinPeriodFrequencyType()) j["lockinPeriodFrequencyType"] = p.getValueOfLockinPeriodFrequencyType();
    j["accountingType"] = p.getValueOfAccountingType();
    j["active"] = p.getValueOfIsActive();
    j["startDate"] = dateStr(p.getValueOfStartDate());
    if (p.getCloseDate()) j["closeDate"] = dateStr(p.getValueOfCloseDate());
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listShareProducts(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::ShareProduct>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(shareProductJson(r));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::shareProductToJson(Txn txn, const std::string &id) {
    co_return shareProductJson(co_await Mapper<m::ShareProduct>(txn).findByPrimaryKey(id));
}

drogon::Task<Json::Value> PortfolioService::getShareProduct(const turbo::RequestContext &ctx,
                                                            std::string id) {
    requirePermission(ctx, "READ_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return shareProductJson(co_await Mapper<m::ShareProduct>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Share product not found", "error.msg.shareproduct.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createShareProduct(const turbo::RequestContext &ctx,
                                                               Json::Value body) {
    requirePermission(ctx, "CREATE_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ShareProduct row;
    row.setName(asStringOr(body, "name"));
    row.setShortName(asStringOr(body, "shortName"));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    row.setCurrencyCode(asStringOr(body, "currencyCode", "USD"));
    row.setCurrencyDigits(asIntOr(body, "digitsAfterDecimal", 2));
    row.setTotalShares(static_cast<int64_t>(asIntOr(body, "totalShares", 0)));
    row.setTotalSharesToBeIssued(static_cast<int64_t>(asIntOr(body, "sharesIssued", 0)));
    row.setNominalPrice(moneyOr(body, "nominalPrice").toString(false));
    if (body.isMember("marketPrice")) row.setMarketPrice(moneyOr(body, "marketPrice").toString(false));
    row.setShareCapitalType(asIntOr(body, "shareCapitalType", 1));
    row.setMinimumShares(static_cast<int64_t>(asIntOr(body, "minimumShares", 1)));
    row.setDefaultShares(static_cast<int64_t>(asIntOr(body, "nominalShares", 1)));
    row.setMaximumShares(static_cast<int64_t>(asIntOr(body, "maximumShares", 0)));
    row.setAllowDividendsForInactiveClients(asBoolOr(body, "allowDividendCalculationForInactiveClients", false));
    if (body.isMember("lockinPeriod")) row.setLockinPeriod(asIntOr(body, "lockinPeriod", 0));
    if (body.isMember("lockinPeriodFrequencyType"))
        row.setLockinPeriodFrequencyType(asIntOr(body, "lockinPeriodFrequencyType", 0));
    row.setAccountingType(asIntOr(body, "accountingRule", 1));
    row.setIsActive(true);
    row.setStartDate(dateOr(asStringOr(body, "startDate"), Date::now()));
    if (body.isMember("closeDate")) row.setCloseDate(dateOr(asStringOr(body, "closeDate"), Date::now()));
    row = co_await Mapper<m::ShareProduct>(txn).insert(row);

    if (body.isMember("charges") && body["charges"].isArray()) {
        for (const auto &c : body["charges"]) {
            m::ShareProductCharge pc;
            pc.setShareProductId(row.getValueOfId());
            pc.setChargeId(c.isObject() ? asStringOr(c, "id") : c.asString());
            co_await Mapper<m::ShareProductCharge>(txn).insert(pc);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "shareproduct", row.getValueOfId(),
                                       "shareproduct.created", body);
    co_return shareProductJson(row);
}

drogon::Task<Json::Value> PortfolioService::updateShareProduct(const turbo::RequestContext &ctx,
                                                               std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ShareProduct row;
    try {
        row = co_await Mapper<m::ShareProduct>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Share product not found", "error.msg.shareproduct.not.found");
    }
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    if (body.isMember("nominalPrice")) row.setNominalPrice(moneyOr(body, "nominalPrice").toString(false));
    if (body.isMember("marketPrice")) row.setMarketPrice(moneyOr(body, "marketPrice").toString(false));
    if (body.isMember("totalShares")) row.setTotalShares(static_cast<int64_t>(asIntOr(body, "totalShares", 0)));
    co_await Mapper<m::ShareProduct>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "shareproduct", id, "shareproduct.updated", body);
    co_return shareProductJson(row);
}

Json::Value PortfolioService::shareProductTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["chargeOptions"] = Json::Value(Json::arrayValue);
    t["currencyOptions"] = Json::Value(Json::arrayValue);
    return t;
}

drogon::Task<Json::Value> PortfolioService::handleShareProductCommand(const turbo::RequestContext &ctx,
                                                                      std::string id, std::string command,
                                                                      Json::Value body) {
    requirePermission(ctx, "UPDATE_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ShareProduct row;
    try {
        row = co_await Mapper<m::ShareProduct>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Share product not found", "error.msg.shareproduct.not.found");
    }
    if (command == "activate") {
        row.setIsActive(true);
    } else if (command == "close") {
        row.setIsActive(false);
        row.setCloseDate(dateOr(asStringOr(body, "closeDate"), Date::now()));
    } else {
        throw ApiError(drogon::k400BadRequest, "Unknown share product command: " + command,
                       "error.msg.shareproduct.command.unknown");
    }
    co_await Mapper<m::ShareProduct>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "shareproduct", id, "shareproduct." + command, body);
    co_return shareProductJson(row);
}

namespace {
Json::Value shareDividendJson(const m::ShareProductDividend &d) {
    Json::Value j;
    j["id"] = d.getValueOfId();
    j["shareProductId"] = d.getValueOfShareProductId();
    j["dividendPeriodStartDate"] = dateStr(d.getValueOfDividendPeriodStartDate());
    j["dividendPeriodEndDate"] = dateStr(d.getValueOfDividendPeriodEndDate());
    j["amount"] = moneyJson(d.getValueOfDividendAmount());
    j["status"] = d.getValueOfStatus();
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listShareProductDividends(const turbo::RequestContext &ctx,
                                                                      std::string productId) {
    requirePermission(ctx, "READ_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::ShareProductDividend>(txn).findBy(
        Criteria(m::ShareProductDividend::Cols::_share_product_id, productId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(shareDividendJson(r));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getShareProductDividend(const turbo::RequestContext &ctx,
                                                                    std::string productId,
                                                                    std::string dividendId) {
    requirePermission(ctx, "READ_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return shareDividendJson(
            co_await Mapper<m::ShareProductDividend>(txn).findByPrimaryKey(dividendId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Dividend not found", "error.msg.sharedividend.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createShareProductDividend(const turbo::RequestContext &ctx,
                                                                       std::string productId,
                                                                       Json::Value body) {
    requirePermission(ctx, "UPDATE_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ShareProductDividend row;
    row.setShareProductId(productId);
    row.setDividendPeriodStartDate(dateOr(asStringOr(body, "dividendPeriodStartDate"), Date::now()));
    row.setDividendPeriodEndDate(dateOr(asStringOr(body, "dividendPeriodEndDate"), Date::now()));
    row.setDividendAmount(moneyOr(body, "amount", moneyOr(body, "dividendAmount")).toString(false));
    row.setStatus(100);
    row.setCreatedBy(userIdOr(ctx));
    row = co_await Mapper<m::ShareProductDividend>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "sharedividend", row.getValueOfId(),
                                       "sharedividend.created", body);
    co_return shareDividendJson(row);
}

drogon::Task<Json::Value> PortfolioService::updateShareProductDividend(const turbo::RequestContext &ctx,
                                                                       std::string productId,
                                                                       std::string dividendId,
                                                                       Json::Value body) {
    requirePermission(ctx, "UPDATE_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ShareProductDividend row;
    try {
        row = co_await Mapper<m::ShareProductDividend>(txn).findByPrimaryKey(dividendId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Dividend not found", "error.msg.sharedividend.not.found");
    }
    if (body.isMember("amount")) row.setDividendAmount(moneyOr(body, "amount").toString(false));
    if (body.isMember("status")) row.setStatus(asIntOr(body, "status", row.getValueOfStatus()));
    co_await Mapper<m::ShareProductDividend>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "sharedividend", dividendId, "sharedividend.updated", body);
    co_return shareDividendJson(row);
}

drogon::Task<void> PortfolioService::deleteShareProductDividend(const turbo::RequestContext &ctx,
                                                                std::string productId,
                                                                std::string dividendId) {
    requirePermission(ctx, "UPDATE_SHAREPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::ShareProductDividend>(txn).deleteByPrimaryKey(dividendId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Dividend not found", "error.msg.sharedividend.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "sharedividend", dividendId, "sharedividend.deleted",
                                       Json::Value());
}

// ---- share accounts --------------------------------------------------------

namespace {
constexpr int kShareSubmitted = 100;
constexpr int kShareApproved = 200;
constexpr int kShareActive = 300;
constexpr int kShareRejected = 400;
constexpr int kShareClosed = 600;

Json::Value shareAccountJson(const m::ShareAccount &a) {
    Json::Value j;
    j["id"] = a.getValueOfId();
    j["accountNo"] = a.getValueOfAccountNo();
    if (a.getExternalId()) j["externalId"] = a.getValueOfExternalId();
    if (a.getClientId()) j["clientId"] = a.getValueOfClientId();
    if (a.getGroupId()) j["groupId"] = a.getValueOfGroupId();
    j["productId"] = a.getValueOfProductId();
    j["currencyCode"] = a.getValueOfCurrencyCode();
    j["submittedDate"] = dateStr(a.getValueOfSubmittedDate());
    if (a.getApprovedDate()) j["approvedDate"] = dateStr(a.getValueOfApprovedDate());
    if (a.getActivatedDate()) j["activatedDate"] = dateStr(a.getValueOfActivatedDate());
    if (a.getClosedDate()) j["closedDate"] = dateStr(a.getValueOfClosedDate());
    j["status"] = a.getValueOfStatus();
    j["requestedShares"] = static_cast<Json::Int64>(a.getValueOfRequestedShares());
    if (a.getApprovedShares()) j["approvedShares"] = static_cast<Json::Int64>(a.getValueOfApprovedShares());
    if (a.getLockinPeriod()) j["lockinPeriod"] = a.getValueOfLockinPeriod();
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listShareAccounts(const turbo::RequestContext &ctx,
                                                              const std::string &clientId) {
    requirePermission(ctx, "READ_SHAREACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Json::Value items(Json::arrayValue);
    if (clientId.empty()) {
        auto rows = co_await Mapper<m::ShareAccount>(txn).findAll();
        for (const auto &r : rows) items.append(shareAccountJson(r));
    } else {
        auto rows =
            co_await Mapper<m::ShareAccount>(txn).findBy(Criteria(m::ShareAccount::Cols::_client_id, clientId));
        for (const auto &r : rows) items.append(shareAccountJson(r));
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::shareAccountToJson(Txn txn, const std::string &id) {
    co_return shareAccountJson(co_await Mapper<m::ShareAccount>(txn).findByPrimaryKey(id));
}

drogon::Task<Json::Value> PortfolioService::getShareAccount(const turbo::RequestContext &ctx,
                                                            std::string id) {
    requirePermission(ctx, "READ_SHAREACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return shareAccountJson(co_await Mapper<m::ShareAccount>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Share account not found", "error.msg.shareaccount.not.found");
    }
}

drogon::Task<Json::Value> PortfolioService::createShareAccount(const turbo::RequestContext &ctx,
                                                               Json::Value body) {
    requirePermission(ctx, "CREATE_SHAREACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto product = co_await Mapper<m::ShareProduct>(txn).findByPrimaryKey(asStringOr(body, "productId"));
    m::ShareAccount row;
    row.setAccountNo(co_await generateShareAccountNumber(txn));
    if (body.isMember("externalId")) row.setExternalId(asStringOr(body, "externalId"));
    if (body.isMember("clientId")) row.setClientId(asStringOr(body, "clientId"));
    if (body.isMember("groupId")) row.setGroupId(asStringOr(body, "groupId"));
    row.setProductId(product.getValueOfId());
    row.setCurrencyCode(product.getValueOfCurrencyCode());
    row.setSubmittedDate(dateOr(asStringOr(body, "submittedDate"), Date::now()));
    row.setSubmittedBy(userIdOr(ctx));
    row.setStatus(kShareSubmitted);
    row.setRequestedShares(static_cast<int64_t>(
        asIntOr(body, "requestedShares", static_cast<int>(product.getValueOfDefaultShares()))));
    row.setApprovedShares(0);
    row.setLockinPeriod(asIntOr(body, "lockinPeriod", product.getValueOfLockinPeriod()));
    row.setLockinPeriodFrequencyType(
        asIntOr(body, "lockinPeriodFrequencyType", product.getValueOfLockinPeriodFrequencyType()));
    row = co_await Mapper<m::ShareAccount>(txn).insert(row);

    if (body.isMember("charges") && body["charges"].isArray()) {
        for (const auto &c : body["charges"]) {
            m::ShareAccountCharge ch;
            ch.setShareAccountId(row.getValueOfId());
            ch.setChargeId(c.isObject() ? asStringOr(c, "chargeId") : c.asString());
            ch.setAmount(c.isObject() ? moneyOr(c, "amount").toString(false) : "0.000000");
            ch.setAmountPaidDerived("0.000000");
            ch.setIsActive(true);
            co_await Mapper<m::ShareAccountCharge>(txn).insert(ch);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "shareaccount", row.getValueOfId(),
                                       "shareaccount.created", body);
    co_return shareAccountJson(row);
}

drogon::Task<Json::Value> PortfolioService::updateShareAccount(const turbo::RequestContext &ctx,
                                                               std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_SHAREACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ShareAccount row;
    try {
        row = co_await Mapper<m::ShareAccount>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Share account not found", "error.msg.shareaccount.not.found");
    }
    if (row.getValueOfStatus() != kShareSubmitted)
        throw ApiError(drogon::k403Forbidden, "Only submitted-and-pending-approval share accounts can be edited",
                       "error.msg.shareaccount.not.in.submitted.state");
    if (body.isMember("requestedShares"))
        row.setRequestedShares(static_cast<int64_t>(asIntOr(body, "requestedShares", 0)));
    co_await Mapper<m::ShareAccount>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "shareaccount", id, "shareaccount.updated", body);
    co_return shareAccountJson(row);
}

Json::Value PortfolioService::shareAccountTemplate(const turbo::RequestContext &ctx) {
    Json::Value t;
    t["productOptions"] = Json::Value(Json::arrayValue);
    return t;
}

drogon::Task<Json::Value> PortfolioService::handleShareAccountCommand(const turbo::RequestContext &ctx,
                                                                      std::string id, std::string command,
                                                                      Json::Value body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ShareAccount row;
    try {
        row = co_await Mapper<m::ShareAccount>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Share account not found", "error.msg.shareaccount.not.found");
    }
    if (command == "approve") {
        requirePermission(ctx, "APPROVE_SHAREACCOUNT");
        row.setStatus(kShareApproved);
        row.setApprovedDate(dateOr(asStringOr(body, "approvedDate"), Date::now()));
        row.setApprovedBy(userIdOr(ctx));
        row.setApprovedShares(static_cast<int64_t>(
            asIntOr(body, "approvedShares", static_cast<int>(row.getValueOfRequestedShares()))));
    } else if (command == "undoApproval") {
        requirePermission(ctx, "APPROVE_SHAREACCOUNT");
        row.setStatus(kShareSubmitted);
    } else if (command == "reject") {
        requirePermission(ctx, "APPROVE_SHAREACCOUNT");
        row.setStatus(kShareRejected);
        row.setRejectedDate(dateOr(asStringOr(body, "rejectedDate"), Date::now()));
    } else if (command == "activate") {
        requirePermission(ctx, "ACTIVATE_SHAREACCOUNT");
        row.setStatus(kShareActive);
        row.setActivatedDate(dateOr(asStringOr(body, "activatedDate"), Date::now()));
    } else if (command == "close") {
        requirePermission(ctx, "CLOSE_SHAREACCOUNT");
        row.setStatus(kShareClosed);
        row.setClosedDate(dateOr(asStringOr(body, "closedDate"), Date::now()));
    } else if (command == "applyadditionalshares") {
        requirePermission(ctx, "UPDATE_SHAREACCOUNT");
        m::SharePurchaseRequest req;
        req.setShareAccountId(id);
        req.setRequestedDate(dateOr(asStringOr(body, "requestedDate"), Date::now()));
        req.setRequestedShares(static_cast<int64_t>(asIntOr(body, "requestedShares", 0)));
        auto product = co_await Mapper<m::ShareProduct>(txn).findByPrimaryKey(row.getValueOfProductId());
        req.setRequestedPrice(product.getValueOfNominalPrice());
        req.setStatus(100);
        req.setRequestedBy(userIdOr(ctx));
        req = co_await Mapper<m::SharePurchaseRequest>(txn).insert(req);
        co_await turbo::outbox::writeEvent(txn, ctx, "sharepurchaserequest", req.getValueOfId(),
                                           "sharepurchaserequest.created", body);
        co_return shareAccountJson(row);
    } else if (command == "approveadditionalshares" || command == "rejectadditionalshares") {
        requirePermission(ctx, "APPROVE_SHAREACCOUNT");
        auto requestId = asStringOr(body, "requestId");
        Json::Value out(Json::arrayValue);
        auto applyToRequest = [&](m::SharePurchaseRequest req) -> drogon::Task<void> {
            req.setStatus(command == "approveadditionalshares" ? 200 : 300);
            req.setDecidedBy(userIdOr(ctx));
            req.setDecidedDate(Date::now());
            co_await Mapper<m::SharePurchaseRequest>(txn).update(req);
            if (command == "approveadditionalshares") {
                row.setApprovedShares(row.getValueOfApprovedShares() + req.getValueOfRequestedShares());
                co_await Mapper<m::ShareAccount>(txn).update(row);
            }
        };
        if (!requestId.empty()) {
            co_await applyToRequest(co_await Mapper<m::SharePurchaseRequest>(txn).findByPrimaryKey(requestId));
        } else {
            auto pending = co_await Mapper<m::SharePurchaseRequest>(txn).findBy(
                Criteria(m::SharePurchaseRequest::Cols::_share_account_id, id) &&
                Criteria(m::SharePurchaseRequest::Cols::_status, 100));
            for (auto &req : pending) co_await applyToRequest(req);
        }
        co_await turbo::outbox::writeEvent(txn, ctx, "shareaccount", id, "shareaccount." + command, body);
        co_return shareAccountJson(row);
    } else if (command == "redeemshares") {
        requirePermission(ctx, "UPDATE_SHAREACCOUNT");
        auto redeemed = asIntOr(body, "sharesToBeRedeemed", 0);
        row.setApprovedShares(std::max<int64_t>(0, row.getValueOfApprovedShares() - redeemed));
    } else {
        throw ApiError(drogon::k400BadRequest, "Unknown share account command: " + command,
                       "error.msg.shareaccount.command.unknown");
    }
    co_await Mapper<m::ShareAccount>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "shareaccount", id, "shareaccount." + command, body);
    co_return shareAccountJson(row);
}

// =====================================================================
// external-asset-owners (loan sales / transfers)
// =====================================================================

namespace {
// Local status/type codes for loan_owner_transfer — not drawn from any
// Fineract enum (Fineract's EAO module uses string statuses); kept as
// small integers here to match this table's int32 status/transfer_type
// columns. transferType: 1=sale (transfer of ownership), 2=buyback.
constexpr int kTransferPending = 1;
constexpr int kTransferActive = 2;
constexpr int kTransferCancelled = 3;
constexpr int kTransferCompleted = 4;
constexpr int kTransferTypeSale = 1;
constexpr int kTransferTypeBuyback = 2;

Json::Value ownerTransferJson(const m::LoanOwnerTransfer &t) {
    Json::Value j;
    j["id"] = t.getValueOfId();
    if (t.getExternalId()) j["externalId"] = t.getValueOfExternalId();
    j["loanId"] = t.getValueOfLoanId();
    j["ownerId"] = t.getValueOfOwnerId();
    j["transferType"] = t.getValueOfTransferType();
    j["status"] = t.getValueOfStatus();
    if (t.getSettlementDate()) j["settlementDate"] = dateStr(t.getValueOfSettlementDate());
    j["effectiveDate"] = dateStr(t.getValueOfEffectiveDate());
    if (t.getPurchasePriceRatio()) j["purchasePriceRatio"] = t.getValueOfPurchasePriceRatio();
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listAssetOwnerTransfers(const turbo::RequestContext &ctx,
                                                                    const std::string &loanId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await Mapper<m::LoanOwnerTransfer>(txn).findBy(Criteria(m::LoanOwnerTransfer::Cols::_loan_id, loanId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(ownerTransferJson(r));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::searchAssetOwnerTransfers(const turbo::RequestContext &ctx,
                                                                      Json::Value body) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    std::vector<m::LoanOwnerTransfer> rows;
    if (body.isMember("loanId")) {
        rows = co_await Mapper<m::LoanOwnerTransfer>(txn).findBy(
            Criteria(m::LoanOwnerTransfer::Cols::_loan_id, asStringOr(body, "loanId")));
    } else if (body.isMember("ownerId")) {
        rows = co_await Mapper<m::LoanOwnerTransfer>(txn).findBy(
            Criteria(m::LoanOwnerTransfer::Cols::_owner_id, asStringOr(body, "ownerId")));
    } else {
        rows = co_await Mapper<m::LoanOwnerTransfer>(txn).findAll();
    }
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(ownerTransferJson(r));
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::assetOwnerTransferToJson(Txn txn, const std::string &id) {
    co_return ownerTransferJson(co_await Mapper<m::LoanOwnerTransfer>(txn).findByPrimaryKey(id));
}

drogon::Task<Json::Value> PortfolioService::getActiveAssetOwnerTransfer(const turbo::RequestContext &ctx,
                                                                        const std::string &loanId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await Mapper<m::LoanOwnerTransfer>(txn).findBy(Criteria(m::LoanOwnerTransfer::Cols::_loan_id, loanId) &&
                                                          Criteria(m::LoanOwnerTransfer::Cols::_status,
                                                                   kTransferActive));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "No active transfer for loan",
                       "error.msg.assetownertransfer.not.found");
    co_return ownerTransferJson(rows.front());
}

drogon::Task<Json::Value> PortfolioService::createAssetOwnerTransfer(const turbo::RequestContext &ctx,
                                                                     std::string loanIdOrExternalId,
                                                                     bool byExternalId, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto loanId = co_await resolveLoanId(txn, loanIdOrExternalId, byExternalId);
    m::LoanOwnerTransfer row;
    if (body.isMember("externalId")) row.setExternalId(asStringOr(body, "externalId"));
    row.setLoanId(loanId);
    row.setOwnerId(asStringOr(body, "ownerExternalId", asStringOr(body, "ownerId")));
    row.setTransferType(kTransferTypeSale);
    row.setStatus(kTransferPending);
    if (body.isMember("settlementDate"))
        row.setSettlementDate(dateOr(asStringOr(body, "settlementDate"), Date::now()));
    row.setEffectiveDate(dateOr(asStringOr(body, "effectiveDate"), Date::now()));
    if (body.isMember("purchasePriceRatio")) row.setPurchasePriceRatio(asStringOr(body, "purchasePriceRatio"));
    row.setCreatedBy(userIdOr(ctx));
    row = co_await Mapper<m::LoanOwnerTransfer>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loanownertransfer", row.getValueOfId(),
                                       "loanownertransfer.created", body);
    co_return ownerTransferJson(row);
}

drogon::Task<Json::Value> PortfolioService::handleAssetOwnerTransferCommand(
    const turbo::RequestContext &ctx, std::string transferId, std::string command, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanOwnerTransfer row;
    try {
        row = co_await Mapper<m::LoanOwnerTransfer>(txn).findByPrimaryKey(transferId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Transfer not found", "error.msg.assetownertransfer.not.found");
    }
    if (command == "cancel") {
        row.setStatus(kTransferCancelled);
    } else if (command == "buyback") {
        row.setStatus(kTransferCompleted);
        m::LoanOwnerTransfer buyback;
        buyback.setLoanId(row.getValueOfLoanId());
        buyback.setOwnerId(row.getValueOfOwnerId());
        buyback.setTransferType(kTransferTypeBuyback);
        buyback.setStatus(kTransferCompleted);
        buyback.setEffectiveDate(dateOr(asStringOr(body, "effectiveDate"), Date::now()));
        buyback.setCreatedBy(userIdOr(ctx));
        co_await Mapper<m::LoanOwnerTransfer>(txn).insert(buyback);
    } else {
        throw ApiError(drogon::k400BadRequest, "Unknown transfer command: " + command,
                       "error.msg.assetownertransfer.command.unknown");
    }
    co_await Mapper<m::LoanOwnerTransfer>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loanownertransfer", transferId,
                                       "loanownertransfer." + command, body);
    co_return ownerTransferJson(row);
}

drogon::Task<Json::Value> PortfolioService::listTransferJournalEntries(const turbo::RequestContext &ctx,
                                                                       std::string transferId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::LoanOwnerTransferJournalEntry>(txn).findBy(
        Criteria(m::LoanOwnerTransferJournalEntry::Cols::_transfer_id, transferId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["transferId"] = r.getValueOfTransferId();
        j["entryType"] = r.getValueOfEntryType();
        j["amount"] = moneyJson(r.getValueOfAmount());
        if (r.getGlAccountId()) j["glAccountId"] = r.getValueOfGlAccountId();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::listOwnerJournalEntries(const turbo::RequestContext &ctx,
                                                                    std::string ownerExternalId) {
    requirePermission(ctx, "READ_LOAN");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto transfers = co_await Mapper<m::LoanOwnerTransfer>(txn).findBy(
        Criteria(m::LoanOwnerTransfer::Cols::_owner_id, ownerExternalId));
    Json::Value items(Json::arrayValue);
    for (const auto &t : transfers) {
        auto rows = co_await Mapper<m::LoanOwnerTransferJournalEntry>(txn).findBy(
            Criteria(m::LoanOwnerTransferJournalEntry::Cols::_transfer_id, t.getValueOfId()));
        for (const auto &r : rows) {
            Json::Value j;
            j["id"] = r.getValueOfId();
            j["transferId"] = r.getValueOfTransferId();
            j["entryType"] = r.getValueOfEntryType();
            j["amount"] = moneyJson(r.getValueOfAmount());
            items.append(j);
        }
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::listLoanProductAttributes(const turbo::RequestContext &ctx,
                                                                      std::string loanProductId) {
    requirePermission(ctx, "READ_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::LoanProductAttribute>(txn).findBy(
        Criteria(m::LoanProductAttribute::Cols::_loan_product_id, loanProductId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["key"] = r.getValueOfAttributeKey();
        j["value"] = r.getValueOfAttributeValue();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::createLoanProductAttribute(const turbo::RequestContext &ctx,
                                                                       std::string loanProductId,
                                                                       Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanProductAttribute row;
    row.setLoanProductId(loanProductId);
    row.setAttributeKey(asStringOr(body, "key"));
    row.setAttributeValue(asStringOr(body, "value"));
    row = co_await Mapper<m::LoanProductAttribute>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loanproductattribute", row.getValueOfId(),
                                       "loanproductattribute.created", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["key"] = row.getValueOfAttributeKey();
    j["value"] = row.getValueOfAttributeValue();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::updateLoanProductAttribute(const turbo::RequestContext &ctx,
                                                                       std::string loanProductId,
                                                                       std::string id, Json::Value body) {
    requirePermission(ctx, "UPDATE_LOANPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::LoanProductAttribute row;
    try {
        row = co_await Mapper<m::LoanProductAttribute>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Loan product attribute not found",
                       "error.msg.loanproductattribute.not.found");
    }
    if (body.isMember("value")) row.setAttributeValue(asStringOr(body, "value"));
    co_await Mapper<m::LoanProductAttribute>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "loanproductattribute", id,
                                       "loanproductattribute.updated", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["key"] = row.getValueOfAttributeKey();
    j["value"] = row.getValueOfAttributeValue();
    co_return j;
}

// =====================================================================
// credit bureau configuration + integration
//
// Ships with exactly one CreditBureauProvider implementation: a
// deterministic "sandbox" provider that synthesizes a report from the
// requested national ID (no external network call — this sandbox has no
// outbound network access and real bureaus require paid, jurisdiction-
// specific contracts). It is wired in so the full configuration ->
// fetch -> save pipeline is real and testable end-to-end; swapping in a
// genuine bureau integration later only requires replacing
// fetchFromProvider's body with an HTTP client call.
// =====================================================================

namespace {
Json::Value fetchFromProvider(const std::string &nationalId, const std::string &clientId) {
    // Deterministic synthetic report: a hash of the national id feeds a
    // small score/tradeline model so the same id always reproduces the
    // same report (useful for integration tests) without calling out to
    // any real bureau.
    std::hash<std::string> hasher;
    auto h = hasher(nationalId);
    int score = 300 + static_cast<int>(h % 551);  // 300..850 like a FICO-style band
    Json::Value j;
    j["provider"] = "sandbox";
    j["nationalId"] = nationalId;
    if (!clientId.empty()) j["clientId"] = clientId;
    j["score"] = score;
    j["asOfDate"] = dateStr(Date::now());
    Json::Value tradelines(Json::arrayValue);
    Json::Value t1;
    t1["type"] = "loan";
    t1["status"] = score > 600 ? "current" : "delinquent";
    tradelines.append(t1);
    j["tradelines"] = tradelines;
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::listCreditBureaus(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CreditBureau>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        j["country"] = r.getValueOfCountry();
        j["active"] = r.getValueOfIsActive();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::listOrganisationCreditBureaus(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::OrganisationCreditBureau>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["creditBureauId"] = r.getValueOfCreditBureauId();
        j["alias"] = r.getValueOfAlias();
        j["active"] = r.getValueOfIsActive();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::addOrganisationCreditBureau(const turbo::RequestContext &ctx,
                                                                       std::string creditBureauId,
                                                                       Json::Value body) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::OrganisationCreditBureau row;
    row.setCreditBureauId(creditBureauId);
    row.setAlias(asStringOr(body, "alias", creditBureauId));
    row.setIsActive(asBoolOr(body, "isActive", true));
    row = co_await Mapper<m::OrganisationCreditBureau>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "organisationcreditbureau", row.getValueOfId(),
                                       "organisationcreditbureau.created", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["creditBureauId"] = row.getValueOfCreditBureauId();
    j["alias"] = row.getValueOfAlias();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::updateOrganisationCreditBureau(const turbo::RequestContext &ctx,
                                                                          Json::Value body) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::OrganisationCreditBureau row;
    try {
        row = co_await Mapper<m::OrganisationCreditBureau>(txn).findByPrimaryKey(asStringOr(body, "id"));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Organisation credit bureau not found",
                       "error.msg.organisationcreditbureau.not.found");
    }
    if (body.isMember("alias")) row.setAlias(asStringOr(body, "alias"));
    if (body.isMember("isActive")) row.setIsActive(asBoolOr(body, "isActive", true));
    co_await Mapper<m::OrganisationCreditBureau>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "organisationcreditbureau", row.getValueOfId(),
                                       "organisationcreditbureau.updated", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["alias"] = row.getValueOfAlias();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::getCreditBureauConfiguration(
    const turbo::RequestContext &ctx, std::string organisationCreditBureauId) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CreditBureauConfiguration>(txn).findBy(
        Criteria(m::CreditBureauConfiguration::Cols::_organisation_credit_bureau_id,
                 organisationCreditBureauId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["key"] = r.getValueOfConfigKey();
        j["value"] = r.getValueOfConfigValue();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::createCreditBureauConfiguration(
    const turbo::RequestContext &ctx, std::string creditBureauId, Json::Value body) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    // `creditBureauId` here is actually the path's organisationCreditBureauId
    // (Fineract's route nests configuration under the org-bureau mapping).
    m::CreditBureauConfiguration row;
    row.setOrganisationCreditBureauId(creditBureauId);
    row.setConfigKey(asStringOr(body, "key"));
    row.setConfigValue(asStringOr(body, "value"));
    row = co_await Mapper<m::CreditBureauConfiguration>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "creditbureauconfiguration", row.getValueOfId(),
                                       "creditbureauconfiguration.created", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["key"] = row.getValueOfConfigKey();
    j["value"] = row.getValueOfConfigValue();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::updateCreditBureauConfiguration(
    const turbo::RequestContext &ctx, std::string configurationId, Json::Value body) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::CreditBureauConfiguration row;
    try {
        row = co_await Mapper<m::CreditBureauConfiguration>(txn).findByPrimaryKey(configurationId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Credit bureau configuration not found",
                       "error.msg.creditbureauconfiguration.not.found");
    }
    if (body.isMember("value")) row.setConfigValue(asStringOr(body, "value"));
    co_await Mapper<m::CreditBureauConfiguration>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "creditbureauconfiguration", configurationId,
                                       "creditbureauconfiguration.updated", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["key"] = row.getValueOfConfigKey();
    j["value"] = row.getValueOfConfigValue();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::listCreditBureauLoanProducts(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::LoanProduct>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::getCreditBureauMappingByLoanProduct(
    const turbo::RequestContext &ctx, std::string loanProductId) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CreditBureauLoanProductMapping>(txn).findBy(
        Criteria(m::CreditBureauLoanProductMapping::Cols::_loan_product_id, loanProductId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["organisationCreditBureauId"] = r.getValueOfOrganisationCreditBureauId();
        j["active"] = r.getValueOfIsActive();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::listCreditBureauMappings(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CreditBureauLoanProductMapping>(txn).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["loanProductId"] = r.getValueOfLoanProductId();
        j["organisationCreditBureauId"] = r.getValueOfOrganisationCreditBureauId();
        j["active"] = r.getValueOfIsActive();
        items.append(j);
    }
    co_return items;
}

drogon::Task<Json::Value> PortfolioService::createCreditBureauMapping(const turbo::RequestContext &ctx,
                                                                      std::string organisationCreditBureauId,
                                                                      Json::Value body) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::CreditBureauLoanProductMapping row;
    row.setOrganisationCreditBureauId(organisationCreditBureauId);
    row.setLoanProductId(asStringOr(body, "loanProductId"));
    row.setIsActive(asBoolOr(body, "isActive", true));
    row = co_await Mapper<m::CreditBureauLoanProductMapping>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "creditbureauloanproductmapping", row.getValueOfId(),
                                       "creditbureauloanproductmapping.created", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["loanProductId"] = row.getValueOfLoanProductId();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::updateCreditBureauMapping(const turbo::RequestContext &ctx,
                                                                      Json::Value body) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::CreditBureauLoanProductMapping row;
    try {
        row = co_await Mapper<m::CreditBureauLoanProductMapping>(txn).findByPrimaryKey(asStringOr(body, "id"));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Credit bureau mapping not found",
                       "error.msg.creditbureauloanproductmapping.not.found");
    }
    if (body.isMember("isActive")) row.setIsActive(asBoolOr(body, "isActive", true));
    co_await Mapper<m::CreditBureauLoanProductMapping>(txn).update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "creditbureauloanproductmapping", row.getValueOfId(),
                                       "creditbureauloanproductmapping.updated", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::fetchCreditReport(const turbo::RequestContext &ctx,
                                                              Json::Value body) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto nationalId = asStringOr(body, "nationalId");
    if (nationalId.empty())
        throw ApiError(drogon::k400BadRequest, "nationalId is required",
                       "error.msg.creditbureaureport.nationalid.required");
    co_return fetchFromProvider(nationalId, asStringOr(body, "clientId"));
}

drogon::Task<Json::Value> PortfolioService::saveCreditReport(const turbo::RequestContext &ctx,
                                                             Json::Value body) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::CreditBureauReport row;
    row.setOrganisationCreditBureauId(asStringOr(body, "organisationCreditBureauId"));
    if (body.isMember("clientId")) row.setClientId(asStringOr(body, "clientId"));
    if (body.isMember("loanId")) row.setLoanId(asStringOr(body, "loanId"));
    row.setNationalId(asStringOr(body, "nationalId"));
    row.setReportData(body.isMember("reportData") ? jsonCompact(body["reportData"]) : jsonCompact(body));
    row.setRequestedBy(userIdOr(ctx));
    row.setRequestedOn(Date::now());
    row.setIsActive(true);
    row = co_await Mapper<m::CreditBureauReport>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "creditbureaureport", row.getValueOfId(),
                                       "creditbureaureport.saved", body);
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["nationalId"] = row.getValueOfNationalId();
    co_return j;
}

drogon::Task<Json::Value> PortfolioService::addCreditReport(const turbo::RequestContext &ctx,
                                                            Json::Value body) {
    auto report = co_await fetchCreditReport(ctx, body);
    Json::Value saveBody = body;
    saveBody["reportData"] = report;
    co_return co_await saveCreditReport(ctx, saveBody);
}

namespace {
Json::Value creditBureauReportJson(const m::CreditBureauReport &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["organisationCreditBureauId"] = r.getValueOfOrganisationCreditBureauId();
    if (r.getClientId()) j["clientId"] = r.getValueOfClientId();
    if (r.getLoanId()) j["loanId"] = r.getValueOfLoanId();
    j["nationalId"] = r.getValueOfNationalId();
    j["requestedOn"] = dateStr(r.getValueOfRequestedOn());
    j["reportData"] = parseJsonOrEmpty(r.getValueOfReportData());
    return j;
}
}  // namespace

drogon::Task<Json::Value> PortfolioService::creditBureauReportToJson(Txn txn, const std::string &id) {
    co_return creditBureauReportJson(co_await Mapper<m::CreditBureauReport>(txn).findByPrimaryKey(id));
}

drogon::Task<Json::Value> PortfolioService::getSavedCreditReport(const turbo::RequestContext &ctx,
                                                                 std::string creditBureauId,
                                                                 const Json::Value &query) {
    requirePermission(ctx, "READ_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CreditBureauReport>(txn).findBy(
        Criteria(m::CreditBureauReport::Cols::_organisation_credit_bureau_id, creditBureauId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        if (!r.getValueOfIsActive()) continue;
        items.append(creditBureauReportJson(r));
    }
    co_return items;
}

drogon::Task<void> PortfolioService::deleteCreditReport(const turbo::RequestContext &ctx,
                                                       std::string creditBureauId,
                                                       const Json::Value &query) {
    requirePermission(ctx, "UPDATE_CREDITBUREAU");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CreditBureauReport>(txn).findBy(
        Criteria(m::CreditBureauReport::Cols::_organisation_credit_bureau_id, creditBureauId));
    for (auto &r : rows) {
        r.setIsActive(false);
        co_await Mapper<m::CreditBureauReport>(txn).update(r);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "creditbureaureport", creditBureauId,
                                       "creditbureaureport.deleted", Json::Value());
}

}  // namespace turbo_ledger_portfolio
