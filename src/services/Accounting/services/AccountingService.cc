#include "AccountingService.h"

#include <openssl/evp.h>

#include <drogon/orm/CoroMapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>

#include <cstdio>
#include <map>
#include <set>

#include "turbo/Ids.h"
#include "turbo/Money.h"
#include "turbo/Outbox.h"
#include "turbo/Pagination.h"
#include "turbo/TenantDb.h"

#include "models/AccountingRuleCreditAccounts.h"
#include "models/AccountingRuleDebitAccounts.h"
#include "models/AccountingRules.h"
#include "models/Accounts.h"
#include "models/FinancialActivityAccounts.h"
#include "models/GlClosure.h"
#include "models/JournalEntries.h"
#include "models/ProvisioningEntries.h"
#include "models/ProvisioningEntriesDetail.h"

using drogon::orm::CompareOperator;
using drogon::orm::Criteria;
using drogon::orm::DrogonDbException;
using drogon::orm::SortOrder;
using drogon::orm::UnexpectedRows;
using trantor::Date;

namespace turbo_ledger_accounting {

namespace m = drogon_model::TlAccounting;
template <typename T>
using Mapper = drogon::orm::CoroMapper<T>;

namespace {

constexpr const char *kZeroUuid = "00000000-0000-0000-0000-000000000000";

// GL account classification (accounts.classification) — Fineract's
// GLAccountType enum. Determines the debit/credit sign convention for
// running balances in updateRunningBalance().
constexpr int kClassificationAsset = 1;
constexpr int kClassificationLiability = 2;
constexpr int kClassificationEquity = 3;
constexpr int kClassificationIncome = 4;
constexpr int kClassificationExpense = 5;

// GL account usage (accounts.account_usage) — Fineract's GLAccountUsage enum.
constexpr int kUsageDetail = 1;   // postable leaf account
constexpr int kUsageHeader = 2;   // non-postable grouping account

// journal_entries.type_enum — Fineract's JournalEntryType enum.
constexpr int kTypeCredit = 1;
constexpr int kTypeDebit = 2;

// journal_entries.entity_type_enum — local to this service until Portfolio
// (Phase 6+) introduces a shared entity-type catalog. loan/savings/client/
// share transactions already have their own dedicated FK columns on this
// table; these three values only tag entries this service itself originates.
constexpr int kEntityTypeManual = 1;
constexpr int kEntityTypeProvisioning = 2;
constexpr int kEntityTypeAccrual = 3;

// ---------------------------------------------------------------------------
// NOTE on ORM coverage: every resource in this file goes through
// CoroMapper<Model>. `Accounts`, `FinancialActivityAccounts`, `GlClosure`
// are untouched, genuine drogon_ctl output (generated against the V001
// baseline, which already covers every column these two resources need).
// `AccountingRules` is genuine drogon_ctl output hand-patched only to fix a
// real bug (debit_account_id/credit_account_id were int32_t but should be
// uuid/std::string — see the header comment on AccountingRules.h).
// `JournalEntries` is genuine drogon_ctl output hand-patched to add the
// Phase 3 hash-chain columns (entry_seq/entry_hash/prev_hash — see the
// header comment on JournalEntries.h). `AccountingRuleDebitAccounts` and
// `AccountingRuleCreditAccounts` are genuine drogon_ctl output (regenerated
// against the live V003 tables, which is also why they're named after
// their plural table names rather than the earlier hand-authored
// singular-named stand-ins). `ProvisioningEntry` and
// `ProvisioningEntryDetail` are still hand-authored from scratch (new V003
// tables) in the same drogon_ctl-shape-matching style established in
// Phase 2 (see each model's own header comment for exactly what's omitted
// and why) — a live `drogon_ctl create_model` run against these tables
// never produced output here because V003 failed before creating them
// (see the migration's REFERENCING-clause bug, fixed in this same commit).
//
// The only raw SQL in this file is a single `SELECT pg_advisory_xact_lock`
// statement in lockJournalChain() — Postgres advisory locks have no table
// and therefore no possible ORM model; this is the same class of narrow,
// structural exception as Organization's holiday_office composite-key
// lookups and SystemConfig's dynamic `dt_<name>` datatables engine.
// ---------------------------------------------------------------------------

Date dateOr(const std::string &text, const Date &fallback) {
    if (text.empty()) return fallback;
    return Date::fromDbStringLocal(text);
}
std::string dateStr(const Date &d) { return d.toDbStringLocal(); }

std::string asStringOr(const Json::Value &v, const char *key, const std::string &fallback = "") {
    return v.isMember(key) && !v[key].isNull() ? v[key].asString() : fallback;
}

bool asBoolOr(const Json::Value &v, const char *key, bool fallback) {
    return v.isMember(key) && v[key].isBool() ? v[key].asBool() : fallback;
}

int asIntOr(const Json::Value &v, const char *key, int fallback) {
    return v.isMember(key) && v[key].isNumeric() ? v[key].asInt() : fallback;
}

/// sha256(text), lowercase hex, 64 chars.
std::string sha256Hex(const std::string &text) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digestLen = 0;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, text.data(), text.size());
    EVP_DigestFinal_ex(ctx, digest, &digestLen);
    EVP_MD_CTX_free(ctx);
    static const char *hex = "0123456789abcdef";
    std::string out;
    out.reserve(digestLen * 2);
    for (unsigned int i = 0; i < digestLen; ++i) {
        out.push_back(hex[(digest[i] >> 4) & 0xF]);
        out.push_back(hex[digest[i] & 0xF]);
    }
    return out;
}

Json::Value moneyJson(const std::string &dbNumeric) {
    auto parsed = turbo::Money::parse(dbNumeric);
    return parsed ? Json::Value(parsed->toString(false)) : Json::Value(dbNumeric);
}

}  // namespace

drogon::orm::DbClientPtr AccountingService::db() { return drogon::app().getDbClient(); }

void AccountingService::requirePermission(const turbo::RequestContext &ctx, const std::string &code) {
    if (!ctx.hasPermission(code))
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

// ---------------------------------------------------------------------------
// glaccounts
// ---------------------------------------------------------------------------

namespace {
Json::Value classificationOptions() {
    Json::Value arr(Json::arrayValue);
    auto add = [&](int id, const char *code, const char *value) {
        Json::Value o;
        o["id"] = id;
        o["code"] = code;
        o["value"] = value;
        arr.append(o);
    };
    add(kClassificationAsset, "accountType.asset", "ASSET");
    add(kClassificationLiability, "accountType.liability", "LIABILITY");
    add(kClassificationEquity, "accountType.equity", "EQUITY");
    add(kClassificationIncome, "accountType.income", "INCOME");
    add(kClassificationExpense, "accountType.expense", "EXPENSE");
    return arr;
}
Json::Value usageOptions() {
    Json::Value arr(Json::arrayValue);
    auto add = [&](int id, const char *code, const char *value) {
        Json::Value o;
        o["id"] = id;
        o["code"] = code;
        o["value"] = value;
        arr.append(o);
    };
    add(kUsageDetail, "accountUsage.detail", "DETAIL");
    add(kUsageHeader, "accountUsage.header", "HEADER");
    return arr;
}
const char *classificationLabel(int c) {
    switch (c) {
        case kClassificationAsset: return "ASSET";
        case kClassificationLiability: return "LIABILITY";
        case kClassificationEquity: return "EQUITY";
        case kClassificationIncome: return "INCOME";
        case kClassificationExpense: return "EXPENSE";
        default: return "UNKNOWN";
    }
}
const char *usageLabel(int u) { return u == kUsageHeader ? "HEADER" : "DETAIL"; }

Json::Value glAccountJson(const m::Accounts &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getValueOfName();
    j["glCode"] = row.getValueOfGlCode();
    j["disabled"] = row.getValueOfDisabled();
    j["manualEntriesAllowed"] = row.getValueOfManualJournalEntriesAllowed();
    j["type"] = row.getValueOfClassification();
    j["typeLabel"] = classificationLabel(row.getValueOfClassification());
    j["usage"] = row.getValueOfAccountUsage();
    j["usageLabel"] = usageLabel(row.getValueOfAccountUsage());
    j["description"] = row.getDescription() ? row.getValueOfDescription() : "";
    j["hierarchy"] = row.getHierarchy() ? row.getValueOfHierarchy() : "";
    const auto parentId = row.getValueOfParentId();
    if (parentId != kZeroUuid) j["parentId"] = parentId;
    if (row.getTagId()) j["tagId"] = row.getValueOfTagId();
    return j;
}
}  // namespace

drogon::Task<Json::Value> AccountingService::glAccountToJson(Txn txn, const std::string &id) {
    Mapper<m::Accounts> mapper(txn);
    m::Accounts row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "GL account not found",
                       "error.msg.glaccount.not.found");
    }
    Json::Value j = glAccountJson(row);
    const auto parentId = row.getValueOfParentId();
    if (parentId != kZeroUuid) {
        try {
            auto prow = co_await mapper.findByPrimaryKey(parentId);
            j["parentName"] = prow.getValueOfName();
        } catch (const UnexpectedRows &) {
        }
    }
    co_return j;
}

drogon::Task<Json::Value> AccountingService::listGlAccounts(const turbo::RequestContext &ctx,
                                                            const std::string &manualEntriesAllowed,
                                                            const std::string &disabled,
                                                            const std::string &usage,
                                                            const std::string &classification) {
    requirePermission(ctx, "READ_GLACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Accounts> mapper(txn);
    mapper.orderBy(m::Accounts::Cols::_hierarchy).orderBy(m::Accounts::Cols::_name);
    Criteria crit;
    auto addBool = [&](const char *key, const std::string &text, const std::string &col) {
        if (text.empty()) return;
        Criteria c(col, text == "true" || text == "1");
        crit = crit ? (crit && c) : c;
        (void)key;
    };
    addBool("manualEntriesAllowed", manualEntriesAllowed,
            m::Accounts::Cols::_manual_journal_entries_allowed);
    addBool("disabled", disabled, m::Accounts::Cols::_disabled);
    if (!usage.empty()) {
        Criteria c(m::Accounts::Cols::_account_usage, std::stoi(usage));
        crit = crit ? (crit && c) : c;
    }
    if (!classification.empty()) {
        Criteria c(m::Accounts::Cols::_classification, std::stoi(classification));
        crit = crit ? (crit && c) : c;
    }
    auto rows = crit ? co_await mapper.findBy(crit) : co_await mapper.findAll();
    Json::Value out(Json::arrayValue);
    for (const auto &r : rows) out.append(glAccountJson(r));
    co_return out;
}

drogon::Task<Json::Value> AccountingService::getGlAccount(const turbo::RequestContext &ctx,
                                                          const std::string &id) {
    requirePermission(ctx, "READ_GLACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await glAccountToJson(txn, id);
}

drogon::Task<Json::Value> AccountingService::createGlAccount(const turbo::RequestContext &ctx,
                                                             const Json::Value &body) {
    requirePermission(ctx, "CREATE_GLACCOUNT");
    const auto name = asStringOr(body, "name");
    const auto glCode = asStringOr(body, "glCode");
    const int classification = asIntOr(body, "type", 0);
    const int usage = asIntOr(body, "usage", kUsageDetail);
    if (name.empty() || glCode.empty() || classification < kClassificationAsset ||
        classification > kClassificationExpense)
        throw ApiError(drogon::k400BadRequest, "name, glCode and a valid type are required",
                       "error.msg.glaccount.invalid");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Accounts> mapper(txn);

    std::string parentId = asStringOr(body, "parentId", kZeroUuid);
    std::string hierarchy;
    if (parentId != kZeroUuid) {
        try {
            auto prow = co_await mapper.findByPrimaryKey(parentId);
            if (prow.getValueOfAccountUsage() != kUsageHeader)
                throw ApiError(drogon::k400BadRequest, "Parent account must be a HEADER account",
                               "error.msg.glaccount.parent.not.header");
            hierarchy = (prow.getHierarchy() ? prow.getValueOfHierarchy() : "");
        } catch (const UnexpectedRows &) {
            throw ApiError(drogon::k404NotFound, "Parent GL account not found",
                           "error.msg.glaccount.parent.not.found");
        }
    }

    m::Accounts row;
    row.setName(name);
    row.setGlCode(glCode);
    row.setParentId(parentId);
    row.setClassification(classification);
    row.setAccountUsage(usage);
    row.setDisabled(asBoolOr(body, "disabled", false));
    row.setManualJournalEntriesAllowed(asBoolOr(body, "manualEntriesAllowed", true));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    if (body.isMember("tagId") && !body["tagId"].isNull()) row.setTagId(asStringOr(body, "tagId"));

    try {
        row = co_await mapper.insert(row);
    } catch (const DrogonDbException &e) {
        throw ApiError(drogon::k400BadRequest,
                       std::string("Could not create GL account: ") + e.base().what(),
                       "error.msg.glaccount.duplicate.glCode");
    }
    hierarchy += "." + row.getValueOfId() + ".";
    row.setHierarchy(hierarchy);
    co_await mapper.update(row);

    co_await turbo::outbox::writeEvent(txn, ctx, "glaccount", row.getValueOfId(), "glaccount.created",
                                       glAccountJson(row));
    co_return co_await glAccountToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> AccountingService::updateGlAccount(const turbo::RequestContext &ctx,
                                                             const std::string &id,
                                                             const Json::Value &body) {
    requirePermission(ctx, "UPDATE_GLACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Accounts> mapper(txn);
    m::Accounts row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "GL account not found",
                       "error.msg.glaccount.not.found");
    }
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    if (body.isMember("manualEntriesAllowed"))
        row.setManualJournalEntriesAllowed(asBoolOr(body, "manualEntriesAllowed", true));
    if (body.isMember("disabled")) row.setDisabled(asBoolOr(body, "disabled", false));
    if (body.isMember("tagId") && !body["tagId"].isNull()) row.setTagId(asStringOr(body, "tagId"));
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "glaccount", id, "glaccount.updated", body);
    co_return co_await glAccountToJson(txn, id);
}

drogon::Task<void> AccountingService::deleteGlAccount(const turbo::RequestContext &ctx,
                                                       const std::string &id) {
    requirePermission(ctx, "DELETE_GLACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Accounts> mapper(txn);
    try {
        co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "GL account not found",
                       "error.msg.glaccount.not.found");
    }
    const auto usedCount =
        co_await Mapper<m::JournalEntries>(txn).count(Criteria(m::JournalEntries::Cols::_account_id, id));
    if (usedCount > 0)
        throw ApiError(drogon::k409Conflict, "Cannot delete a GL account that has journal entries",
                       "error.msg.glaccount.gl.account.has.transactions");
    const auto childCount =
        co_await Mapper<m::Accounts>(txn).count(Criteria(m::Accounts::Cols::_parent_id, id));
    if (childCount > 0)
        throw ApiError(drogon::k409Conflict, "Cannot delete a GL account that has child accounts",
                       "error.msg.glaccount.has.children");
    co_await mapper.deleteByPrimaryKey(id);
    co_await turbo::outbox::writeEvent(txn, ctx, "glaccount", id, "glaccount.deleted", Json::Value());
}

Json::Value AccountingService::glAccountTemplate(const turbo::RequestContext &) {
    Json::Value out;
    out["accountTypeOptions"] = classificationOptions();
    out["usageOptions"] = usageOptions();
    return out;
}

// ---------------------------------------------------------------------------
// glclosures
// ---------------------------------------------------------------------------

namespace {
Json::Value glClosureJson(const m::GlClosure &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["officeId"] = row.getOfficeId() ? row.getValueOfOfficeId() : "";
    j["closingDate"] = dateStr(row.getValueOfClosingDate());
    j["deleted"] = row.getValueOfIsDeleted();
    j["comments"] = row.getComments() ? row.getValueOfComments() : "";
    return j;
}
}  // namespace

drogon::Task<Json::Value> AccountingService::glClosureToJson(Txn txn, const std::string &id) {
    Mapper<m::GlClosure> mapper(txn);
    m::GlClosure row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Accounting closure not found",
                       "error.msg.glclosure.not.found");
    }
    co_return glClosureJson(row);
}

drogon::Task<Json::Value> AccountingService::listGlClosures(const turbo::RequestContext &ctx,
                                                            const std::string &officeId) {
    requirePermission(ctx, "READ_GLCLOSURE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::GlClosure> mapper(txn);
    mapper.orderBy(m::GlClosure::Cols::_closing_date, SortOrder::DESC);
    auto crit = Criteria(m::GlClosure::Cols::_is_deleted, false);
    if (!officeId.empty()) crit = crit && Criteria(m::GlClosure::Cols::_office_id, officeId);
    auto rows = co_await mapper.findBy(crit);
    Json::Value out(Json::arrayValue);
    for (const auto &r : rows) out.append(glClosureJson(r));
    co_return out;
}

drogon::Task<Json::Value> AccountingService::getGlClosure(const turbo::RequestContext &ctx,
                                                          const std::string &id) {
    requirePermission(ctx, "READ_GLCLOSURE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await glClosureToJson(txn, id);
}

drogon::Task<Json::Value> AccountingService::createGlClosure(const turbo::RequestContext &ctx,
                                                             const Json::Value &body) {
    requirePermission(ctx, "CREATE_GLCLOSURE");
    const auto officeId = asStringOr(body, "officeId");
    const auto closingDateText = asStringOr(body, "closingDate");
    if (officeId.empty() || closingDateText.empty())
        throw ApiError(drogon::k400BadRequest, "officeId and closingDate are required",
                       "error.msg.glclosure.invalid");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::GlClosure> mapper(txn);
    auto existing = co_await mapper.findBy(Criteria(m::GlClosure::Cols::_office_id, officeId) &&
                                           Criteria(m::GlClosure::Cols::_is_deleted, false) &&
                                           Criteria(m::GlClosure::Cols::_closing_date,
                                                    CompareOperator::GE, closingDateText));
    if (!existing.empty())
        throw ApiError(drogon::k409Conflict,
                       "A closure on or after this date already exists for this office",
                       "error.msg.glclosure.duplicate");

    m::GlClosure row;
    row.setOfficeId(officeId);
    row.setClosingDate(dateOr(closingDateText, Date()));
    row.setIsDeleted(false);
    if (body.isMember("comments")) row.setComments(asStringOr(body, "comments"));
    row = co_await mapper.insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "glclosure", row.getValueOfId(), "glclosure.created",
                                       glClosureJson(row));
    co_return glClosureJson(row);
}

drogon::Task<Json::Value> AccountingService::updateGlClosure(const turbo::RequestContext &ctx,
                                                             const std::string &id,
                                                             const Json::Value &body) {
    requirePermission(ctx, "UPDATE_GLCLOSURE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::GlClosure> mapper(txn);
    m::GlClosure row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Accounting closure not found",
                       "error.msg.glclosure.not.found");
    }
    // Fineract only allows editing the comments of an existing closure — the
    // closing date/office are immutable once other postings may already
    // depend on them being blocked.
    if (body.isMember("comments")) row.setComments(asStringOr(body, "comments"));
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "glclosure", id, "glclosure.updated", body);
    co_return glClosureJson(row);
}

drogon::Task<void> AccountingService::deleteGlClosure(const turbo::RequestContext &ctx,
                                                       const std::string &id) {
    requirePermission(ctx, "DELETE_GLCLOSURE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::GlClosure> mapper(txn);
    m::GlClosure row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Accounting closure not found",
                       "error.msg.glclosure.not.found");
    }
    // Only the most recent (latest closing_date) non-deleted closure for the
    // office may be removed — matches Fineract, and prevents silently
    // re-opening an earlier period while a later closure still references it
    // as "already closed up to here".
    auto later = co_await Mapper<m::GlClosure>(txn).count(
        Criteria(m::GlClosure::Cols::_office_id, row.getValueOfOfficeId()) &&
        Criteria(m::GlClosure::Cols::_is_deleted, false) &&
        Criteria(m::GlClosure::Cols::_closing_date, CompareOperator::GT,
                 dateStr(row.getValueOfClosingDate())));
    if (later > 0)
        throw ApiError(drogon::k409Conflict,
                       "Only the most recent accounting closure for an office can be deleted",
                       "error.msg.glclosure.not.latest");
    row.setIsDeleted(true);
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "glclosure", id, "glclosure.deleted", Json::Value());
}

// ---------------------------------------------------------------------------
// accountingrules
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> AccountingService::accountingRuleToJson(Txn txn, const std::string &id) {
    Mapper<m::AccountingRules> mapper(txn);
    m::AccountingRules row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Accounting rule not found",
                       "error.msg.accountingrule.not.found");
    }
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getName() ? row.getValueOfName() : "";
    j["officeId"] = row.getOfficeId() ? row.getValueOfOfficeId() : "";
    j["description"] = row.getDescription() ? row.getValueOfDescription() : "";
    j["systemDefined"] = row.getValueOfSystemDefined();
    j["allowMultipleDebits"] = row.getValueOfAllowMultipleDebits();
    j["allowMultipleCredits"] = row.getValueOfAllowMultipleCredits();
    if (row.getDebitAccountId()) j["debitAccountId"] = row.getValueOfDebitAccountId();
    if (row.getCreditAccountId()) j["creditAccountId"] = row.getValueOfCreditAccountId();

    Json::Value debitAccounts(Json::arrayValue);
    for (const auto &r : co_await Mapper<m::AccountingRuleDebitAccounts>(txn).findBy(
             Criteria(m::AccountingRuleDebitAccounts::Cols::_rule_id, id)))
        debitAccounts.append(r.getValueOfAccountId());
    j["debitAccounts"] = debitAccounts;

    Json::Value creditAccounts(Json::arrayValue);
    for (const auto &r : co_await Mapper<m::AccountingRuleCreditAccounts>(txn).findBy(
             Criteria(m::AccountingRuleCreditAccounts::Cols::_rule_id, id)))
        creditAccounts.append(r.getValueOfAccountId());
    j["creditAccounts"] = creditAccounts;
    co_return j;
}

drogon::Task<Json::Value> AccountingService::listAccountingRules(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_ACCOUNTINGRULE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::AccountingRules>(txn).orderBy(m::AccountingRules::Cols::_name).findAll();
    Json::Value out(Json::arrayValue);
    for (const auto &r : rows) out.append(co_await accountingRuleToJson(txn, r.getValueOfId()));
    co_return out;
}

drogon::Task<Json::Value> AccountingService::getAccountingRule(const turbo::RequestContext &ctx,
                                                               const std::string &id) {
    requirePermission(ctx, "READ_ACCOUNTINGRULE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await accountingRuleToJson(txn, id);
}

drogon::Task<Json::Value> AccountingService::createAccountingRule(const turbo::RequestContext &ctx,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "CREATE_ACCOUNTINGRULE");
    const auto name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "name is required", "error.msg.accountingrule.invalid");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::AccountingRules> mapper(txn);
    m::AccountingRules row;
    row.setName(name);
    if (body.isMember("officeId") && !body["officeId"].isNull()) row.setOfficeId(asStringOr(body, "officeId"));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    row.setSystemDefined(false);
    bool allowMultiDebits = asBoolOr(body, "allowMultipleDebits", false);
    bool allowMultiCredits = asBoolOr(body, "allowMultipleCredits", false);
    row.setAllowMultipleDebits(allowMultiDebits);
    row.setAllowMultipleCredits(allowMultiCredits);
    if (body.isMember("debitAccountId") && !body["debitAccountId"].isNull())
        row.setDebitAccountId(asStringOr(body, "debitAccountId"));
    if (body.isMember("creditAccountId") && !body["creditAccountId"].isNull())
        row.setCreditAccountId(asStringOr(body, "creditAccountId"));

    try {
        row = co_await mapper.insert(row);
    } catch (const DrogonDbException &e) {
        throw ApiError(drogon::k400BadRequest,
                       std::string("Could not create accounting rule: ") + e.base().what(),
                       "error.msg.accountingrule.duplicate.name");
    }

    if (allowMultiDebits && body.isMember("debitAccounts") && body["debitAccounts"].isArray()) {
        for (const auto &accId : body["debitAccounts"]) {
            m::AccountingRuleDebitAccounts link;
            link.setRuleId(row.getValueOfId());
            link.setAccountId(accId.asString());
            co_await Mapper<m::AccountingRuleDebitAccounts>(txn).insert(link);
        }
    }
    if (allowMultiCredits && body.isMember("creditAccounts") && body["creditAccounts"].isArray()) {
        for (const auto &accId : body["creditAccounts"]) {
            m::AccountingRuleCreditAccounts link;
            link.setRuleId(row.getValueOfId());
            link.setAccountId(accId.asString());
            co_await Mapper<m::AccountingRuleCreditAccounts>(txn).insert(link);
        }
    }

    co_await turbo::outbox::writeEvent(txn, ctx, "accountingrule", row.getValueOfId(),
                                       "accountingrule.created", body);
    co_return co_await accountingRuleToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> AccountingService::updateAccountingRule(const turbo::RequestContext &ctx,
                                                                  const std::string &id,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_ACCOUNTINGRULE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::AccountingRules> mapper(txn);
    m::AccountingRules row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Accounting rule not found",
                       "error.msg.accountingrule.not.found");
    }
    if (row.getValueOfSystemDefined())
        throw ApiError(drogon::k409Conflict, "System-defined accounting rules cannot be modified",
                       "error.msg.accountingrule.system.defined");
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    if (body.isMember("debitAccountId")) row.setDebitAccountId(asStringOr(body, "debitAccountId"));
    if (body.isMember("creditAccountId")) row.setCreditAccountId(asStringOr(body, "creditAccountId"));
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "accountingrule", id, "accountingrule.updated", body);
    co_return co_await accountingRuleToJson(txn, id);
}

drogon::Task<void> AccountingService::deleteAccountingRule(const turbo::RequestContext &ctx,
                                                           const std::string &id) {
    requirePermission(ctx, "DELETE_ACCOUNTINGRULE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::AccountingRules> mapper(txn);
    m::AccountingRules row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Accounting rule not found",
                       "error.msg.accountingrule.not.found");
    }
    if (row.getValueOfSystemDefined())
        throw ApiError(drogon::k409Conflict, "System-defined accounting rules cannot be deleted",
                       "error.msg.accountingrule.system.defined");
    co_await Mapper<m::AccountingRuleDebitAccounts>(txn).deleteBy(
        Criteria(m::AccountingRuleDebitAccounts::Cols::_rule_id, id));
    co_await Mapper<m::AccountingRuleCreditAccounts>(txn).deleteBy(
        Criteria(m::AccountingRuleCreditAccounts::Cols::_rule_id, id));
    co_await mapper.deleteByPrimaryKey(id);
    co_await turbo::outbox::writeEvent(txn, ctx, "accountingrule", id, "accountingrule.deleted",
                                       Json::Value());
}

drogon::Task<Json::Value> AccountingService::accountingRuleTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_ACCOUNTINGRULE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Accounts>(txn)
                    .orderBy(m::Accounts::Cols::_name)
                    .findBy(Criteria(m::Accounts::Cols::_disabled, false) &&
                            Criteria(m::Accounts::Cols::_account_usage, kUsageDetail));
    Json::Value accounts(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value a;
        a["id"] = r.getValueOfId();
        a["name"] = r.getValueOfName();
        a["glCode"] = r.getValueOfGlCode();
        accounts.append(a);
    }
    Json::Value out;
    out["allowedAccounts"] = accounts;
    co_return out;
}

// ---------------------------------------------------------------------------
// financialactivityaccounts
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> AccountingService::financialActivityAccountToJson(Txn txn,
                                                                            const std::string &id) {
    Mapper<m::FinancialActivityAccounts> mapper(txn);
    m::FinancialActivityAccounts row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Financial activity mapping not found",
                       "error.msg.financialactivityaccount.not.found");
    }
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["glAccountId"] = row.getValueOfGlAccountId();
    j["financialActivityType"] = row.getValueOfFinancialActivityType();
    try {
        auto acc = co_await Mapper<m::Accounts>(txn).findByPrimaryKey(row.getValueOfGlAccountId());
        j["glAccountName"] = acc.getValueOfName();
        j["glCode"] = acc.getValueOfGlCode();
    } catch (const UnexpectedRows &) {
    }
    co_return j;
}

drogon::Task<Json::Value> AccountingService::listFinancialActivityAccounts(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_FINANCIALACTIVITYACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::FinancialActivityAccounts>(txn).findAll();
    Json::Value out(Json::arrayValue);
    for (const auto &r : rows)
        out.append(co_await financialActivityAccountToJson(txn, r.getValueOfId()));
    co_return out;
}

drogon::Task<Json::Value> AccountingService::getFinancialActivityAccount(
    const turbo::RequestContext &ctx, const std::string &id) {
    requirePermission(ctx, "READ_FINANCIALACTIVITYACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await financialActivityAccountToJson(txn, id);
}

drogon::Task<Json::Value> AccountingService::createFinancialActivityAccount(
    const turbo::RequestContext &ctx, const Json::Value &body) {
    requirePermission(ctx, "CREATE_FINANCIALACTIVITYACCOUNT");
    const auto glAccountId = asStringOr(body, "glAccountId");
    const int activityType = asIntOr(body, "financialActivityType", -1);
    if (glAccountId.empty() || activityType < 0)
        throw ApiError(drogon::k400BadRequest, "glAccountId and financialActivityType are required",
                       "error.msg.financialactivityaccount.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::Accounts>(txn).findByPrimaryKey(glAccountId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "GL account not found",
                       "error.msg.glaccount.not.found");
    }
    m::FinancialActivityAccounts row;
    row.setGlAccountId(glAccountId);
    row.setFinancialActivityType(activityType);
    try {
        row = co_await Mapper<m::FinancialActivityAccounts>(txn).insert(row);
    } catch (const DrogonDbException &e) {
        throw ApiError(drogon::k409Conflict,
                       std::string("Could not create mapping: ") + e.base().what(),
                       "error.msg.financialactivityaccount.duplicate");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "financialactivityaccount", row.getValueOfId(),
                                       "financialactivityaccount.created", body);
    co_return co_await financialActivityAccountToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> AccountingService::updateFinancialActivityAccount(
    const turbo::RequestContext &ctx, const std::string &id, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_FINANCIALACTIVITYACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::FinancialActivityAccounts> mapper(txn);
    m::FinancialActivityAccounts row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Financial activity mapping not found",
                       "error.msg.financialactivityaccount.not.found");
    }
    if (body.isMember("glAccountId")) {
        const auto glAccountId = asStringOr(body, "glAccountId");
        try {
            co_await Mapper<m::Accounts>(txn).findByPrimaryKey(glAccountId);
        } catch (const UnexpectedRows &) {
            throw ApiError(drogon::k404NotFound, "GL account not found",
                           "error.msg.glaccount.not.found");
        }
        row.setGlAccountId(glAccountId);
    }
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "financialactivityaccount", id,
                                       "financialactivityaccount.updated", body);
    co_return co_await financialActivityAccountToJson(txn, id);
}

drogon::Task<void> AccountingService::deleteFinancialActivityAccount(const turbo::RequestContext &ctx,
                                                                     const std::string &id) {
    requirePermission(ctx, "DELETE_FINANCIALACTIVITYACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::FinancialActivityAccounts> mapper(txn);
    try {
        co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Financial activity mapping not found",
                       "error.msg.financialactivityaccount.not.found");
    }
    co_await mapper.deleteByPrimaryKey(id);
    co_await turbo::outbox::writeEvent(txn, ctx, "financialactivityaccount", id,
                                       "financialactivityaccount.deleted", Json::Value());
}

drogon::Task<Json::Value> AccountingService::financialActivityAccountTemplate(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_FINANCIALACTIVITYACCOUNT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Accounts>(txn)
                    .orderBy(m::Accounts::Cols::_name)
                    .findBy(Criteria(m::Accounts::Cols::_disabled, false));
    Json::Value accounts(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value a;
        a["id"] = r.getValueOfId();
        a["name"] = r.getValueOfName();
        accounts.append(a);
    }
    Json::Value out;
    out["allowedAccounts"] = accounts;
    // Fineract's FinancialActivity enum (1=ASSET_TRANSFER, 2=OPENING_BALANCES_TRANSFER_CONTRA,
    // 100=PAYABLE_DIVIDENDS, ... ); we surface a minimal, extensible set here.
    Json::Value activities(Json::arrayValue);
    auto add = [&](int id, const char *value) {
        Json::Value a;
        a["id"] = id;
        a["value"] = value;
        activities.append(a);
    };
    add(1, "Asset Transfer");
    add(2, "Opening Balances Transfer Contra");
    add(100, "Payable Dividends");
    out["financialActivityOptions"] = activities;
    co_return out;
}

// ---------------------------------------------------------------------------
// journalentries — ledger correctness core.
// ---------------------------------------------------------------------------

drogon::Task<void> AccountingService::lockJournalChain(Txn txn) {
    // Postgres advisory locks have no table, so no ORM model can express
    // this — the one narrow, structural raw-SQL exception in this file (see
    // the header comment above). Scoped to (fixed namespace, current tenant
    // schema) so concurrent postings for *different* tenants never block
    // each other; within one tenant, this serializes hash-chain extension so
    // it can never fork under concurrent requests.
    co_await txn->execSqlCoro(
        "SELECT pg_advisory_xact_lock(hashtext('tl_journal_chain'), hashtext(current_schema()))");
}

drogon::Task<std::string> AccountingService::currentChainHead(Txn txn) {
    auto rows = co_await Mapper<m::JournalEntries>(txn)
                    .orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC)
                    .limit(1)
                    .findAll();
    if (rows.empty() || !rows[0].getEntryHash()) co_return std::string();
    co_return rows[0].getValueOfEntryHash();
}

std::string AccountingService::computeEntryHash(const std::string &prevHash,
                                                const std::string &transactionId,
                                                const std::string &accountId,
                                                const std::string &officeId,
                                                const std::string &currencyCode, int typeEnum,
                                                const std::string &amount, const std::string &entryDate,
                                                const std::string &description) {
    std::string canonical = prevHash;
    canonical += '|';
    canonical += transactionId;
    canonical += '|';
    canonical += accountId;
    canonical += '|';
    canonical += officeId;
    canonical += '|';
    canonical += currencyCode;
    canonical += '|';
    canonical += std::to_string(typeEnum);
    canonical += '|';
    canonical += amount;
    canonical += '|';
    canonical += entryDate;
    canonical += '|';
    canonical += description;
    return sha256Hex(canonical);
}

drogon::Task<void> AccountingService::assertNotClosed(Txn txn, const std::string &officeId,
                                                      const std::string &entryDate) {
    // Blocks postings on/before an office's closure date. Real Fineract also
    // inherits closures from parent offices; Office/hierarchy data lives in
    // the Organization service's own database, and this codebase has no
    // internal cross-service lookup client yet, so only closures recorded
    // directly against `officeId` are enforced here. Extending this to walk
    // the office hierarchy is deferred until such a client exists (or the
    // gateway-signed TL-Context is extended to carry the caller's office
    // hierarchy path).
    auto count = co_await Mapper<m::GlClosure>(txn).count(
        Criteria(m::GlClosure::Cols::_office_id, officeId) &&
        Criteria(m::GlClosure::Cols::_is_deleted, false) &&
        Criteria(m::GlClosure::Cols::_closing_date, CompareOperator::GE, entryDate));
    if (count > 0)
        throw ApiError(drogon::k409Conflict,
                       "This office is closed for accounting on or after " + entryDate,
                       "error.msg.glclosure.accounting.closed");
}

drogon::Task<std::string> AccountingService::postLeg(
    Txn txn, const turbo::RequestContext &ctx, const std::string &transactionId,
    const std::string &officeId, const std::string &accountId, const std::string &currencyCode,
    int typeEnum, const std::string &amount, const std::string &entryDate,
    const std::string &transactionDate, const std::string &description, const std::string &refNum,
    bool manualEntry, const std::string &reversalId, std::string &prevHash) {
    m::Accounts account;
    try {
        account = co_await Mapper<m::Accounts>(txn).findByPrimaryKey(accountId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "GL account not found: " + accountId,
                       "error.msg.glaccount.not.found");
    }
    if (account.getValueOfDisabled())
        throw ApiError(drogon::k400BadRequest, "GL account is disabled: " + accountId,
                       "error.msg.glaccount.disabled");
    if (account.getValueOfAccountUsage() != kUsageDetail)
        throw ApiError(drogon::k400BadRequest,
                       "Cannot post to a HEADER (non-postable) GL account: " + accountId,
                       "error.msg.glaccount.not.postable");
    if (manualEntry && !account.getValueOfManualJournalEntriesAllowed())
        throw ApiError(drogon::k400BadRequest,
                       "Manual journal entries are not allowed for this GL account: " + accountId,
                       "error.msg.glaccount.manual.entries.not.allowed");

    // Running balance: ASSET/EXPENSE accounts increase on DEBIT; LIABILITY/
    // EQUITY/INCOME accounts increase on CREDIT (Fineract's convention).
    const bool debitIncreases = account.getValueOfClassification() == kClassificationAsset ||
                                account.getValueOfClassification() == kClassificationExpense;
    const bool isDebit = typeEnum == kTypeDebit;
    const bool increases = isDebit == debitIncreases;
    auto delta = *turbo::Money::parse(amount);
    if (!increases) delta = -delta;

    auto officePrior = co_await Mapper<m::JournalEntries>(txn)
                           .orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC)
                           .limit(1)
                           .findBy(Criteria(m::JournalEntries::Cols::_account_id, accountId) &&
                                   Criteria(m::JournalEntries::Cols::_office_id, officeId));
    auto orgPrior = co_await Mapper<m::JournalEntries>(txn)
                        .orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC)
                        .limit(1)
                        .findBy(Criteria(m::JournalEntries::Cols::_account_id, accountId));
    auto officeBalance = officePrior.empty() ? turbo::Money::fromUnits(0)
                                             : *turbo::Money::parse(officePrior[0].getValueOfOfficeRunningBalance());
    auto orgBalance = orgPrior.empty()
                          ? turbo::Money::fromUnits(0)
                          : *turbo::Money::parse(orgPrior[0].getValueOfOrganizationRunningBalance());
    officeBalance += delta;
    orgBalance += delta;

    const std::string hash = computeEntryHash(prevHash, transactionId, accountId, officeId,
                                              currencyCode, typeEnum, amount, entryDate, description);

    m::JournalEntries row;
    row.setAccountId(accountId);
    row.setOfficeId(officeId);
    row.setCurrencyCode(currencyCode);
    row.setTransactionId(transactionId);
    row.setReversed(false);
    row.setManualEntry(manualEntry);
    row.setEntryDate(dateOr(entryDate, Date()));
    row.setTypeEnum(static_cast<short>(typeEnum));
    row.setAmount(amount);
    if (!description.empty()) row.setDescription(description);
    row.setEntityTypeEnum(static_cast<short>(kEntityTypeManual));
    if (!refNum.empty()) row.setRefNum(refNum);
    if (!ctx.userId.empty()) row.setCreatedBy(ctx.userId);
    row.setIsRunningBalanceCalculated(true);
    row.setOfficeRunningBalance(officeBalance.toString(false));
    row.setOrganizationRunningBalance(orgBalance.toString(false));
    row.setTransactionDate(dateOr(transactionDate.empty() ? entryDate : transactionDate, Date()));
    row.setSubmittedOnDate(Date());
    row.setEntryHash(hash);
    if (!prevHash.empty()) row.setPrevHash(prevHash);
    if (!reversalId.empty()) row.setReversalId(reversalId);

    row = co_await Mapper<m::JournalEntries>(txn).insert(row);
    prevHash = hash;
    co_return row.getValueOfId();
}

namespace {
Json::Value journalEntryTypeJson(int typeEnum) {
    Json::Value t;
    t["id"] = typeEnum;
    t["code"] = typeEnum == kTypeDebit ? "journalEntryType.debit" : "journalEntryType.credit";
    t["value"] = typeEnum == kTypeDebit ? "DEBIT" : "CREDIT";
    return t;
}
}  // namespace

drogon::Task<Json::Value> AccountingService::journalEntryToJson(Txn txn, const std::string &id) {
    Mapper<m::JournalEntries> mapper(txn);
    m::JournalEntries row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Journal entry not found",
                       "error.msg.journalentry.not.found");
    }
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["officeId"] = row.getValueOfOfficeId();
    j["glAccountId"] = row.getValueOfAccountId();
    j["transactionId"] = row.getValueOfTransactionId();
    j["reversed"] = row.getValueOfReversed();
    if (row.getReversalId()) j["reversalId"] = row.getValueOfReversalId();
    j["manualEntry"] = row.getValueOfManualEntry();
    j["transactionDate"] = row.getTransactionDate() ? dateStr(row.getValueOfTransactionDate()) : "";
    j["entryDate"] = dateStr(row.getValueOfEntryDate());
    j["type"] = journalEntryTypeJson(row.getValueOfTypeEnum());
    j["amount"] = moneyJson(row.getValueOfAmount());
    j["currencyCode"] = row.getValueOfCurrencyCode();
    j["description"] = row.getDescription() ? row.getValueOfDescription() : "";
    if (row.getRefNum()) j["referenceNumber"] = row.getValueOfRefNum();
    j["officeRunningBalance"] = moneyJson(row.getValueOfOfficeRunningBalance());
    j["organizationRunningBalance"] = moneyJson(row.getValueOfOrganizationRunningBalance());
    j["submittedOnDate"] = row.getSubmittedOnDate() ? dateStr(row.getValueOfSubmittedOnDate()) : "";
    if (row.getEntryHash()) j["entryHash"] = row.getValueOfEntryHash();
    if (row.getPrevHash()) j["prevHash"] = row.getValueOfPrevHash();
    try {
        auto acc = co_await Mapper<m::Accounts>(txn).findByPrimaryKey(row.getValueOfAccountId());
        j["glAccountName"] = acc.getValueOfName();
        j["glAccountCode"] = acc.getValueOfGlCode();
    } catch (const UnexpectedRows &) {
    }
    co_return j;
}

drogon::Task<Json::Value> AccountingService::createJournalEntries(const turbo::RequestContext &ctx,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "CREATE_JOURNALENTRY");
    const auto officeId = asStringOr(body, "officeId");
    const auto transactionDate = asStringOr(body, "transactionDate");
    const auto currencyCode = asStringOr(body, "currencyCode");
    const auto comments = asStringOr(body, "comments");
    const auto referenceNumber = asStringOr(body, "referenceNumber");
    if (officeId.empty() || transactionDate.empty() || currencyCode.empty())
        throw ApiError(drogon::k400BadRequest, "officeId, transactionDate and currencyCode are required",
                       "error.msg.journalentry.invalid");
    if (!body.isMember("credits") || !body["credits"].isArray() || body["credits"].empty() ||
        !body.isMember("debits") || !body["debits"].isArray() || body["debits"].empty())
        throw ApiError(drogon::k400BadRequest, "At least one credit and one debit leg are required",
                       "error.msg.journalentry.no.entries");

    auto sumLegs = [](const Json::Value &legs) {
        turbo::Money total = turbo::Money::fromUnits(0);
        for (const auto &leg : legs) {
            auto amt = turbo::Money::parse(asStringOr(leg, "amount"));
            if (!amt || amt->isZero() || amt->isNegative())
                throw ApiError(drogon::k400BadRequest, "Every leg amount must be a positive number",
                               "error.msg.journalentry.invalid.amount");
            if (asStringOr(leg, "glAccountId").empty())
                throw ApiError(drogon::k400BadRequest, "Every leg requires a glAccountId",
                               "error.msg.journalentry.invalid");
            total += *amt;
        }
        return total;
    };
    const auto creditTotal = sumLegs(body["credits"]);
    const auto debitTotal = sumLegs(body["debits"]);
    if (creditTotal != debitTotal)
        throw ApiError(drogon::k400BadRequest,
                       "Total debits (" + debitTotal.toString() + ") must equal total credits (" +
                           creditTotal.toString() + ")",
                       "error.msg.journalentry.not.balanced");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await assertNotClosed(txn, officeId, transactionDate);
        co_await lockJournalChain(txn);
        std::string prevHash = co_await currentChainHead(txn);
        const std::string transactionId = turbo::ids::newUuid();
        const bool manualEntry = asBoolOr(body, "manualEntry", true);

        std::vector<std::string> insertedIds;
        for (const auto &leg : body["credits"]) {
            auto id = co_await postLeg(txn, ctx, transactionId, officeId, asStringOr(leg, "glAccountId"),
                                       currencyCode, kTypeCredit, asStringOr(leg, "amount"),
                                       transactionDate, transactionDate,
                                       asStringOr(leg, "comments", comments), referenceNumber,
                                       manualEntry, "", prevHash);
            insertedIds.push_back(id);
        }
        for (const auto &leg : body["debits"]) {
            auto id = co_await postLeg(txn, ctx, transactionId, officeId, asStringOr(leg, "glAccountId"),
                                       currencyCode, kTypeDebit, asStringOr(leg, "amount"),
                                       transactionDate, transactionDate,
                                       asStringOr(leg, "comments", comments), referenceNumber,
                                       manualEntry, "", prevHash);
            insertedIds.push_back(id);
        }

        Json::Value evt;
        evt["transactionId"] = transactionId;
        evt["officeId"] = officeId;
        evt["legCount"] = static_cast<int>(insertedIds.size());
        co_await turbo::outbox::writeEvent(txn, ctx, "journalentry", transactionId,
                                           "journalentry.created", evt);

        Json::Value out;
        out["transactionId"] = transactionId;
        out["officeId"] = officeId;
        Json::Value entries(Json::arrayValue);
        for (const auto &id : insertedIds) entries.append(co_await journalEntryToJson(txn, id));
        out["entries"] = entries;
        co_return out;
    } catch (...) {
        txn->rollback();
        throw;
    }
}

drogon::Task<Json::Value> AccountingService::searchJournalEntries(
    const turbo::RequestContext &ctx, const std::string &officeId, const std::string &glAccountId,
    const std::string &manualEntriesOnly, const std::string &fromDate, const std::string &toDate,
    const std::string &transactionId, int offset, int limit) {
    requirePermission(ctx, "READ_JOURNALENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::JournalEntries> mapper(txn);
    Criteria crit;
    auto add = [&](Criteria c) { crit = crit ? (crit && c) : c; };
    if (!officeId.empty()) add(Criteria(m::JournalEntries::Cols::_office_id, officeId));
    if (!glAccountId.empty()) add(Criteria(m::JournalEntries::Cols::_account_id, glAccountId));
    if (!transactionId.empty()) add(Criteria(m::JournalEntries::Cols::_transaction_id, transactionId));
    if (manualEntriesOnly == "true") add(Criteria(m::JournalEntries::Cols::_manual_entry, true));
    if (!fromDate.empty())
        add(Criteria(m::JournalEntries::Cols::_entry_date, CompareOperator::GE, fromDate));
    if (!toDate.empty())
        add(Criteria(m::JournalEntries::Cols::_entry_date, CompareOperator::LE, toDate));

    const auto total = crit ? co_await mapper.count(crit) : co_await mapper.count();
    mapper.orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC).limit(limit).offset(offset);
    auto rows = crit ? co_await mapper.findBy(crit) : co_await mapper.findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await journalEntryToJson(txn, r.getValueOfId()));
    co_return turbo::pagedResult(static_cast<std::int64_t>(total), items);
}

drogon::Task<Json::Value> AccountingService::getJournalEntry(const turbo::RequestContext &ctx,
                                                             const std::string &id) {
    requirePermission(ctx, "READ_JOURNALENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await journalEntryToJson(txn, id);
}

drogon::Task<Json::Value> AccountingService::getOpeningBalance(const turbo::RequestContext &ctx,
                                                               const std::string &officeId,
                                                               const std::string &currencyCode) {
    requirePermission(ctx, "READ_JOURNALENTRY");
    if (officeId.empty() || currencyCode.empty())
        throw ApiError(drogon::k400BadRequest, "officeId and currencyCode are required",
                       "error.msg.journalentry.invalid");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    // "Opening balance" entries are ordinary manual journal entries dated at
    // (or marked as) the office's ledger start; Fineract identifies them via
    // a dedicated flag on m_journal_entry. This schema has no such flag yet,
    // so — until Portfolio/Phase 6 needs a real opening-balance workflow —
    // this returns the current balance-sheet accounts (ASSET/LIABILITY/
    // EQUITY) with their latest office running balance for the office,
    // which is the information Fineract's opening-balance editor screen
    // actually needs to pre-populate.
    auto accounts = co_await Mapper<m::Accounts>(txn)
                        .orderBy(m::Accounts::Cols::_name)
                        .findBy(Criteria(m::Accounts::Cols::_account_usage, kUsageDetail));
    Json::Value glAccountBalances(Json::arrayValue);
    for (const auto &acc : accounts) {
        if (acc.getValueOfClassification() != kClassificationAsset &&
            acc.getValueOfClassification() != kClassificationLiability &&
            acc.getValueOfClassification() != kClassificationEquity)
            continue;
        auto rows =
            co_await Mapper<m::JournalEntries>(txn)
                .orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC)
                .limit(1)
                .findBy(Criteria(m::JournalEntries::Cols::_account_id, acc.getValueOfId()) &&
                        Criteria(m::JournalEntries::Cols::_office_id, officeId) &&
                        Criteria(m::JournalEntries::Cols::_currency_code, currencyCode));
        Json::Value j;
        j["glAccountId"] = acc.getValueOfId();
        j["glAccountName"] = acc.getValueOfName();
        j["glCode"] = acc.getValueOfGlCode();
        j["organizationRunningBalance"] =
            rows.empty() ? Json::Value("0.000000") : moneyJson(rows[0].getValueOfOfficeRunningBalance());
        glAccountBalances.append(j);
    }
    Json::Value out;
    out["officeId"] = officeId;
    out["currencyCode"] = currencyCode;
    out["glAccountBalances"] = glAccountBalances;
    co_return out;
}

drogon::Task<Json::Value> AccountingService::getProvisioningJournalEntries(
    const turbo::RequestContext &ctx, int offset, int limit) {
    requirePermission(ctx, "READ_JOURNALENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::JournalEntries> mapper(txn);
    auto crit = Criteria(m::JournalEntries::Cols::_entity_type_enum, kEntityTypeProvisioning);
    const auto total = co_await mapper.count(crit);
    mapper.orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC).limit(limit).offset(offset);
    auto rows = co_await mapper.findBy(crit);
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await journalEntryToJson(txn, r.getValueOfId()));
    co_return turbo::pagedResult(static_cast<std::int64_t>(total), items);
}

drogon::Task<Json::Value> AccountingService::journalEntryTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_JOURNALENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Accounts>(txn)
                    .orderBy(m::Accounts::Cols::_name)
                    .findBy(Criteria(m::Accounts::Cols::_disabled, false) &&
                            Criteria(m::Accounts::Cols::_account_usage, kUsageDetail) &&
                            Criteria(m::Accounts::Cols::_manual_journal_entries_allowed, true));
    Json::Value accounts(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value a;
        a["id"] = r.getValueOfId();
        a["name"] = r.getValueOfName();
        a["glCode"] = r.getValueOfGlCode();
        a["type"] = r.getValueOfClassification();
        accounts.append(a);
    }
    Json::Value out;
    out["glAccountOptions"] = accounts;
    Json::Value types(Json::arrayValue);
    types.append(journalEntryTypeJson(kTypeDebit));
    types.append(journalEntryTypeJson(kTypeCredit));
    out["journalEntryTypeOptions"] = types;
    co_return out;
}

drogon::Task<Json::Value> AccountingService::reverseJournalTransaction(
    const turbo::RequestContext &ctx, const std::string &transactionId, const Json::Value &body) {
    requirePermission(ctx, "CREATE_JOURNALENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto legs = co_await Mapper<m::JournalEntries>(txn)
                        .orderBy(m::JournalEntries::Cols::_entry_seq)
                        .findBy(Criteria(m::JournalEntries::Cols::_transaction_id, transactionId));
        if (legs.empty())
            throw ApiError(drogon::k404NotFound, "Journal transaction not found",
                           "error.msg.journalentry.not.found");
        if (legs[0].getValueOfReversed())
            throw ApiError(drogon::k409Conflict, "This transaction has already been reversed",
                           "error.msg.journalentry.already.reversed");

        const std::string comments = asStringOr(body, "comments", "Reversal entry");
        co_await lockJournalChain(txn);
        std::string prevHash = co_await currentChainHead(txn);
        const std::string reversalTransactionId = turbo::ids::newUuid();
        std::vector<std::string> reversalIds;
        for (const auto &leg : legs) {
            // Equal amount, opposite type — a CREDIT leg is reversed by a
            // DEBIT of the same amount on the same account/office, and vice
            // versa, so the transaction stays balanced.
            const int reversedType =
                leg.getValueOfTypeEnum() == kTypeDebit ? kTypeCredit : kTypeDebit;
            auto id = co_await postLeg(txn, ctx, reversalTransactionId, leg.getValueOfOfficeId(),
                                       leg.getValueOfAccountId(), leg.getValueOfCurrencyCode(),
                                       reversedType, leg.getValueOfAmount(),
                                       dateStr(leg.getValueOfEntryDate()),
                                       dateStr(leg.getValueOfEntryDate()), comments, "",
                                       leg.getValueOfManualEntry(), leg.getValueOfId(), prevHash);
            reversalIds.push_back(id);
        }
        // Mark every original leg reversed, linking to the first reversal leg.
        for (auto leg : legs) {
            leg.setReversed(true);
            leg.setReversalId(reversalIds.front());
            co_await Mapper<m::JournalEntries>(txn).update(leg);
        }

        Json::Value evt;
        evt["originalTransactionId"] = transactionId;
        evt["reversalTransactionId"] = reversalTransactionId;
        co_await turbo::outbox::writeEvent(txn, ctx, "journalentry", reversalTransactionId,
                                           "journalentry.reversed", evt);

        Json::Value out;
        out["transactionId"] = transactionId;
        out["reversalTransactionId"] = reversalTransactionId;
        Json::Value entries(Json::arrayValue);
        for (const auto &id : reversalIds) entries.append(co_await journalEntryToJson(txn, id));
        out["entries"] = entries;
        co_return out;
    } catch (...) {
        txn->rollback();
        throw;
    }
}

drogon::Task<Json::Value> AccountingService::recalculateRunningBalances(
    const turbo::RequestContext &ctx, const std::string &transactionId) {
    requirePermission(ctx, "UPDATE_JOURNALENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto seedLegs = co_await Mapper<m::JournalEntries>(txn).findBy(
            Criteria(m::JournalEntries::Cols::_transaction_id, transactionId));
        if (seedLegs.empty())
            throw ApiError(drogon::k404NotFound, "Journal transaction not found",
                           "error.msg.journalentry.not.found");
        const auto fromSeq = seedLegs.front().getValueOfEntrySeq();

        auto legs = co_await Mapper<m::JournalEntries>(txn)
                        .orderBy(m::JournalEntries::Cols::_entry_seq)
                        .findBy(Criteria(m::JournalEntries::Cols::_entry_seq, CompareOperator::GE,
                                        fromSeq));

        std::map<std::pair<std::string, std::string>, turbo::Money> officeBalances;
        std::map<std::string, turbo::Money> orgBalances;
        int updated = 0;
        for (auto &leg : legs) {
            auto acc = co_await Mapper<m::Accounts>(txn).findByPrimaryKey(leg.getValueOfAccountId());
            const bool debitIncreases = acc.getValueOfClassification() == kClassificationAsset ||
                                        acc.getValueOfClassification() == kClassificationExpense;
            const bool isDebit = leg.getValueOfTypeEnum() == kTypeDebit;
            auto delta = *turbo::Money::parse(leg.getValueOfAmount());
            if (isDebit != debitIncreases) delta = -delta;

            const auto officeKey = std::make_pair(leg.getValueOfAccountId(), leg.getValueOfOfficeId());
            if (!officeBalances.count(officeKey)) {
                auto prior = co_await Mapper<m::JournalEntries>(txn)
                                 .orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC)
                                 .limit(1)
                                 .findBy(Criteria(m::JournalEntries::Cols::_account_id,
                                                 leg.getValueOfAccountId()) &&
                                        Criteria(m::JournalEntries::Cols::_office_id,
                                                 leg.getValueOfOfficeId()) &&
                                        Criteria(m::JournalEntries::Cols::_entry_seq,
                                                 CompareOperator::LT, leg.getValueOfEntrySeq()));
                officeBalances[officeKey] = prior.empty()
                                                ? turbo::Money::fromUnits(0)
                                                : *turbo::Money::parse(
                                                      prior[0].getValueOfOfficeRunningBalance());
            }
            if (!orgBalances.count(leg.getValueOfAccountId())) {
                auto prior = co_await Mapper<m::JournalEntries>(txn)
                                 .orderBy(m::JournalEntries::Cols::_entry_seq, SortOrder::DESC)
                                 .limit(1)
                                 .findBy(Criteria(m::JournalEntries::Cols::_account_id,
                                                 leg.getValueOfAccountId()) &&
                                        Criteria(m::JournalEntries::Cols::_entry_seq,
                                                 CompareOperator::LT, leg.getValueOfEntrySeq()));
                orgBalances[leg.getValueOfAccountId()] =
                    prior.empty() ? turbo::Money::fromUnits(0)
                                  : *turbo::Money::parse(prior[0].getValueOfOrganizationRunningBalance());
            }
            officeBalances[officeKey] += delta;
            orgBalances[leg.getValueOfAccountId()] += delta;

            leg.setOfficeRunningBalance(officeBalances[officeKey].toString(false));
            leg.setOrganizationRunningBalance(orgBalances[leg.getValueOfAccountId()].toString(false));
            leg.setIsRunningBalanceCalculated(true);
            co_await Mapper<m::JournalEntries>(txn).update(leg);
            ++updated;
        }
        Json::Value out;
        out["transactionId"] = transactionId;
        out["entriesRecalculated"] = updated;
        co_return out;
    } catch (...) {
        txn->rollback();
        throw;
    }
}

// ---------------------------------------------------------------------------
// provisioningentries
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> AccountingService::provisioningEntryToJson(Txn txn, const std::string &id) {
    Mapper<m::ProvisioningEntries> mapper(txn);
    m::ProvisioningEntries row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Provisioning entry not found",
                       "error.msg.provisioningentry.not.found");
    }
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["createdDate"] = dateStr(row.getValueOfCreatedDate());
    j["comments"] = row.getComments() ? row.getValueOfComments() : "";
    j["journalEntryCreated"] = row.getValueOfJournalEntryCreated();

    auto details = co_await Mapper<m::ProvisioningEntriesDetail>(txn).findBy(
        Criteria(m::ProvisioningEntriesDetail::Cols::_provisioning_entry_id, id));
    turbo::Money total = turbo::Money::fromUnits(0);
    Json::Value lines(Json::arrayValue);
    for (const auto &d : details) {
        Json::Value l;
        l["id"] = d.getValueOfId();
        l["officeId"] = d.getValueOfOfficeId();
        l["currencyCode"] = d.getValueOfCurrencyCode();
        l["glAccountId"] = d.getValueOfGlAccountId();
        l["categoryName"] = d.getValueOfCategoryName();
        l["amount"] = moneyJson(d.getValueOfAmount());
        lines.append(l);
        if (auto amt = turbo::Money::parse(d.getValueOfAmount())) total += *amt;
    }
    j["totalAmountReserved"] = total.toString(false);
    j["entries"] = lines;
    co_return j;
}

drogon::Task<Json::Value> AccountingService::listProvisioningEntries(const turbo::RequestContext &ctx,
                                                                     int offset, int limit) {
    requirePermission(ctx, "READ_PROVISIONINGENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ProvisioningEntries> mapper(txn);
    const auto total = co_await mapper.count();
    mapper.orderBy(m::ProvisioningEntries::Cols::_created_date, SortOrder::DESC)
        .limit(limit)
        .offset(offset);
    auto rows = co_await mapper.findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(co_await provisioningEntryToJson(txn, r.getValueOfId()));
    co_return turbo::pagedResult(static_cast<std::int64_t>(total), items);
}

drogon::Task<Json::Value> AccountingService::getProvisioningEntry(const turbo::RequestContext &ctx,
                                                                  const std::string &id) {
    requirePermission(ctx, "READ_PROVISIONINGENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await provisioningEntryToJson(txn, id);
}

drogon::Task<Json::Value> AccountingService::createProvisioningEntry(const turbo::RequestContext &ctx,
                                                                     const Json::Value &body) {
    requirePermission(ctx, "CREATE_PROVISIONINGENTRY");
    const auto createdDate = asStringOr(body, "date");
    if (createdDate.empty())
        throw ApiError(drogon::k400BadRequest, "date is required",
                       "error.msg.provisioningentry.invalid");
    // Full criteria-driven computation (walking overdue loans against
    // product/category rules) belongs to Portfolio, which does not exist
    // yet — see IMPLEMENTATION_PLAN.md's Phase 6 scope and the note on the
    // provisioning_entries* tables in V003__phase3_ledger.sql. Until then, a
    // provisioning entry's line items are supplied directly by the caller;
    // this delivers the ledger side (persistence + balanced journal
    // posting) that will be unchanged once an automatic criteria engine
    // supplies those same lines instead of a human.
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ProvisioningEntries row;
    row.setCreatedDate(dateOr(createdDate, Date()));
    if (body.isMember("comments")) row.setComments(asStringOr(body, "comments"));
    row.setJournalEntryCreated(false);
    if (!ctx.userId.empty()) row.setCreatedBy(ctx.userId);
    row = co_await Mapper<m::ProvisioningEntries>(txn).insert(row);

    if (body.isMember("entries") && body["entries"].isArray()) {
        for (const auto &line : body["entries"]) {
            m::ProvisioningEntriesDetail detail;
            detail.setProvisioningEntryId(row.getValueOfId());
            detail.setOfficeId(asStringOr(line, "officeId"));
            detail.setCurrencyCode(asStringOr(line, "currencyCode"));
            detail.setGlAccountId(asStringOr(line, "glAccountId"));
            detail.setCategoryName(asStringOr(line, "categoryName", "General provisioning"));
            auto amt = turbo::Money::parse(asStringOr(line, "amount"));
            if (!amt) throw ApiError(drogon::k400BadRequest, "Invalid provisioning line amount",
                                     "error.msg.provisioningentry.invalid.amount");
            detail.setAmount(amt->toString(false));
            co_await Mapper<m::ProvisioningEntriesDetail>(txn).insert(detail);
        }
    }

    if (asBoolOr(body, "createjournalentries", false)) {
        co_await createProvisioningJournalEntries(row.getValueOfId(), ctx, txn);
    }

    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningentry", row.getValueOfId(),
                                       "provisioningentry.created", body);
    co_return co_await provisioningEntryToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> AccountingService::recreateProvisioningEntry(
    const turbo::RequestContext &ctx, const std::string &id) {
    requirePermission(ctx, "CREATE_PROVISIONINGENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::ProvisioningEntries row;
    try {
        row = co_await Mapper<m::ProvisioningEntries>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Provisioning entry not found",
                       "error.msg.provisioningentry.not.found");
    }
    if (row.getValueOfJournalEntryCreated())
        throw ApiError(drogon::k409Conflict,
                       "Journal entries were already created for this provisioning entry",
                       "error.msg.provisioningentry.already.journalized");
    co_await createProvisioningJournalEntries(id, ctx, txn);
    co_await turbo::outbox::writeEvent(txn, ctx, "provisioningentry", id,
                                       "provisioningentry.recreated", Json::Value());
    co_return co_await provisioningEntryToJson(txn, id);
}

drogon::Task<Json::Value> AccountingService::listProvisioningEntryDetails(
    const turbo::RequestContext &ctx, const std::string &provisioningEntryId, int offset, int limit) {
    requirePermission(ctx, "READ_PROVISIONINGENTRY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ProvisioningEntriesDetail> mapper(txn);
    Criteria crit;
    if (!provisioningEntryId.empty())
        crit = Criteria(m::ProvisioningEntriesDetail::Cols::_provisioning_entry_id, provisioningEntryId);
    const auto total = crit ? co_await mapper.count(crit) : co_await mapper.count();
    mapper.limit(limit).offset(offset);
    auto rows = crit ? co_await mapper.findBy(crit) : co_await mapper.findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &d : rows) {
        Json::Value l;
        l["id"] = d.getValueOfId();
        l["provisioningEntryId"] = d.getValueOfProvisioningEntryId();
        l["officeId"] = d.getValueOfOfficeId();
        l["currencyCode"] = d.getValueOfCurrencyCode();
        l["glAccountId"] = d.getValueOfGlAccountId();
        l["categoryName"] = d.getValueOfCategoryName();
        l["amount"] = moneyJson(d.getValueOfAmount());
        items.append(l);
    }
    co_return turbo::pagedResult(static_cast<std::int64_t>(total), items);
}

drogon::Task<void> AccountingService::createProvisioningJournalEntriesImpl(
    const std::string &provisioningEntryId, const turbo::RequestContext &ctx, Txn txn) {
    auto details = co_await Mapper<m::ProvisioningEntriesDetail>(txn).findBy(
        Criteria(m::ProvisioningEntriesDetail::Cols::_provisioning_entry_id, provisioningEntryId));
    if (details.empty()) co_return;

    // A provisioning batch debits a "provisioning expense" account and
    // credits a "loan loss reserve" (contra-asset) account for each line —
    // both derived from financial_activity_accounts. Until Portfolio wires
    // up per-product provisioning categories, this posts one balanced
    // transaction per office+currency, aggregating that scope's lines.
    auto expenseMapping = co_await Mapper<m::FinancialActivityAccounts>(txn).findBy(
        Criteria(m::FinancialActivityAccounts::Cols::_financial_activity_type, 100));
    if (expenseMapping.empty())
        throw ApiError(drogon::k409Conflict,
                       "No financial activity mapping configured for provisioning (type 100)",
                       "error.msg.provisioningentry.no.mapping");
    const std::string expenseAccountId = expenseMapping[0].getValueOfGlAccountId();

    auto row = co_await Mapper<m::ProvisioningEntries>(txn).findByPrimaryKey(provisioningEntryId);
    const std::string entryDate = dateStr(row.getValueOfCreatedDate());

    std::map<std::pair<std::string, std::string>, turbo::Money> byOfficeCurrency;
    for (const auto &d : details) {
        auto amt = turbo::Money::parse(d.getValueOfAmount());
        if (!amt) continue;
        byOfficeCurrency[{d.getValueOfOfficeId(), d.getValueOfCurrencyCode()}] += *amt;
    }

    co_await lockJournalChain(txn);
    std::string prevHash = co_await currentChainHead(txn);
    for (const auto &[officeCurrency, total] : byOfficeCurrency) {
        const auto &[officeId, currencyCode] = officeCurrency;
        co_await assertNotClosed(txn, officeId, entryDate);
        const std::string transactionId = turbo::ids::newUuid();
        // debit the expense account, credit each line's category account.
        auto debitId = co_await postLeg(txn, ctx, transactionId, officeId, expenseAccountId,
                                        currencyCode, kTypeDebit, total.toString(false), entryDate,
                                        entryDate, "Loan loss provisioning", "", false, "", prevHash);
        (void)debitId;
        for (const auto &d : details) {
            if (d.getValueOfOfficeId() != officeId || d.getValueOfCurrencyCode() != currencyCode)
                continue;
            co_await postLeg(txn, ctx, transactionId, officeId, d.getValueOfGlAccountId(), currencyCode,
                             kTypeCredit, d.getValueOfAmount(), entryDate, entryDate,
                             d.getValueOfCategoryName(), "", false, "", prevHash);
        }
        // Tag every leg of this transaction as provisioning-originated.
        auto legs = co_await Mapper<m::JournalEntries>(txn).findBy(
            Criteria(m::JournalEntries::Cols::_transaction_id, transactionId));
        for (auto leg : legs) {
            leg.setEntityTypeEnum(static_cast<short>(kEntityTypeProvisioning));
            leg.setEntityId(provisioningEntryId);
            co_await Mapper<m::JournalEntries>(txn).update(leg);
        }
    }

    row.setJournalEntryCreated(true);
    co_await Mapper<m::ProvisioningEntries>(txn).update(row);
}

drogon::Task<void> AccountingService::createProvisioningJournalEntries(
    const std::string &provisioningEntryId, const turbo::RequestContext &ctx, Txn txn) {
    try {
        co_await createProvisioningJournalEntriesImpl(provisioningEntryId, ctx, txn);
    } catch (...) {
        txn->rollback();
        throw;
    }
}

// ---------------------------------------------------------------------------
// runaccruals
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> AccountingService::runPeriodicAccrualAccounting(
    const turbo::RequestContext &ctx, const Json::Value &body) {
    requirePermission(ctx, "CREATE_JOURNALENTRY");
    // Fineract's periodic accrual job walks every loan/savings product with
    // accrual accounting enabled and posts interest-receivable/income
    // entries for the period elapsed. That requires Portfolio (loans),
    // which does not exist yet (see IMPLEMENTATION_PLAN.md's Phase 6
    // scope). This endpoint delivers the ledger side now: given an explicit
    // list of accrual lines (the same shape Portfolio's job will supply
    // once it exists), it posts one balanced transaction per office +
    // currency debiting the "interest receivable" account and crediting the
    // "interest income" account, both taken from the request rather than
    // hardcoded so this does not need to change when Portfolio lands.
    const auto asOfDate = asStringOr(body, "tenantDate", asStringOr(body, "date"));
    if (asOfDate.empty())
        throw ApiError(drogon::k400BadRequest, "date is required", "error.msg.runaccruals.invalid");
    if (!body.isMember("accruals") || !body["accruals"].isArray() || body["accruals"].empty()) {
        Json::Value out;
        out["asOfDate"] = asOfDate;
        out["transactionsPosted"] = 0;
        out["message"] = "No accrual lines supplied; nothing to post "
                          "(Portfolio-driven automatic accrual detection is not yet available)";
        co_return out;
    }

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        int posted = 0;
        for (const auto &accrual : body["accruals"]) {
            const auto officeId = asStringOr(accrual, "officeId");
            const auto currencyCode = asStringOr(accrual, "currencyCode");
            const auto receivableAccountId = asStringOr(accrual, "receivableGlAccountId");
            const auto incomeAccountId = asStringOr(accrual, "incomeGlAccountId");
            auto amt = turbo::Money::parse(asStringOr(accrual, "amount"));
            if (officeId.empty() || currencyCode.empty() || receivableAccountId.empty() ||
                incomeAccountId.empty() || !amt || amt->isZero() || amt->isNegative())
                throw ApiError(drogon::k400BadRequest,
                               "Each accrual line requires officeId, currencyCode, "
                               "receivableGlAccountId, incomeGlAccountId and a positive amount",
                               "error.msg.runaccruals.invalid.line");
            co_await assertNotClosed(txn, officeId, asOfDate);
            co_await lockJournalChain(txn);
            std::string prevHash = co_await currentChainHead(txn);
            const std::string transactionId = turbo::ids::newUuid();
            co_await postLeg(txn, ctx, transactionId, officeId, receivableAccountId, currencyCode,
                             kTypeDebit, amt->toString(false), asOfDate, asOfDate,
                             "Periodic interest accrual", "", false, "", prevHash);
            co_await postLeg(txn, ctx, transactionId, officeId, incomeAccountId, currencyCode,
                             kTypeCredit, amt->toString(false), asOfDate, asOfDate,
                             "Periodic interest accrual", "", false, "", prevHash);
            auto legs = co_await Mapper<m::JournalEntries>(txn).findBy(
                Criteria(m::JournalEntries::Cols::_transaction_id, transactionId));
            for (auto leg : legs) {
                leg.setEntityTypeEnum(static_cast<short>(kEntityTypeAccrual));
                co_await Mapper<m::JournalEntries>(txn).update(leg);
            }
            ++posted;
        }
        co_await turbo::outbox::writeEvent(txn, ctx, "runaccruals", asOfDate, "runaccruals.executed",
                                           body);
        Json::Value out;
        out["asOfDate"] = asOfDate;
        out["transactionsPosted"] = posted;
        co_return out;
    } catch (...) {
        txn->rollback();
        throw;
    }
}

}  // namespace turbo_ledger_accounting
