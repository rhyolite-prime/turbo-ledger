#include "OrganizationService.h"

#include <drogon/orm/CoroMapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>

#include <map>
#include <set>

#include "turbo/Outbox.h"
#include "turbo/TenantDb.h"

#include "models/EntityMapping.h"
#include "models/EntityRelation.h"
#include "models/Fund.h"
#include "models/Holiday.h"
#include "models/Office.h"
#include "models/OfficeTransaction.h"
#include "models/OrganisationCurrency.h"
#include "models/PaymentType.h"
#include "models/Staff.h"
#include "models/TaxComponent.h"
#include "models/TaxGroup.h"
#include "models/TaxGroupMapping.h"
#include "models/WorkingDays.h"

using drogon::orm::CompareOperator;
using drogon::orm::Criteria;
using drogon::orm::DrogonDbException;
using drogon::orm::UnexpectedRows;
using trantor::Date;

namespace turbo_ledger_organization {

namespace m = drogon_model::TlOrganizationDb;
template <typename T>
using Mapper = drogon::orm::CoroMapper<T>;

namespace {

constexpr const char *kZeroUuid = "00000000-0000-0000-0000-000000000000";

// NOTE on ORM coverage: every resource in this file goes through
// CoroMapper<Model>. The models for staff / holiday / working_days / fund /
// tax_component / tax_group / tax_group_mapping / entity_relation /
// entity_mapping (added by the V003 migration, after the original
// `drogon_ctl create_model` run) are hand-authored in models/*.{h,cc} since
// this sandbox has no live Postgres to regenerate them against — see the
// header comment on each of those files for exactly which drogon_ctl
// methods are (and are not) reproduced, and why. `OrganisationCurrency` was
// likewise hand-patched to add the V003 `is_enabled` column.
//
// Two narrow, intentional exceptions remain on raw execSqlCoro:
//   - `holiday_office` is a pure many-to-many join table with a composite
//     primary key (holiday_id, office_id) and no surrogate id column, so it
//     cannot be expressed as a single-primary-key CoroMapper<T> model; its
//     three call sites (existence-check, insert, and the office-scoped
//     EXISTS filter in listHolidays) stay on direct SQL.
//   - the SystemConfig service's `dt_<name>` datatables engine (not in this
//     file) operates on runtime-defined table shapes that cannot be
//     represented by a compile-time model at all.
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

double asDoubleOr(const Json::Value &v, const char *key, double fallback) {
    return v.isMember(key) && v[key].isNumeric() ? v[key].asDouble() : fallback;
}

int asIntOr(const Json::Value &v, const char *key, int fallback) {
    return v.isMember(key) && v[key].isNumeric() ? v[key].asInt() : fallback;
}

}  // namespace

drogon::orm::DbClientPtr OrganizationService::db() { return drogon::app().getDbClient(); }

void OrganizationService::requirePermission(const turbo::RequestContext &ctx,
                                            const std::string &code) {
    if (!ctx.hasPermission(code))
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

// ---------------------------------------------------------------------------
// offices
//
// NOTE: the generated Office model predates the V003 migration's
// `is_deleted` / `created_at` ALTER TABLEs, so those two columns are not
// ORM-visible. `is_deleted` was a read-only filter that nothing in this
// service ever set to true (offices are never hard- or soft-deleted via
// this API, matching Fineract), so dropping the filter here is a no-op in
// practice; `created_at` was never read. Regenerate the model to restore
// both if a future feature needs them.
// ---------------------------------------------------------------------------

namespace {
Json::Value officeJson(const m::Office &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getValueOfName();
    j["externalId"] = row.getExternalId() ? row.getValueOfExternalId() : "";
    j["openingDate"] = dateStr(row.getValueOfOpeningDate());
    j["hierarchy"] = row.getHierarchy() ? row.getValueOfHierarchy() : "";
    return j;
}
}  // namespace

drogon::Task<Json::Value> OrganizationService::officeToJson(Txn txn, const std::string &id) {
    Mapper<m::Office> mapper(txn);
    m::Office row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    }
    Json::Value j = officeJson(row);
    const auto parentId = row.getValueOfParentId();
    if (parentId != kZeroUuid) {
        j["parentId"] = parentId;
        try {
            auto prow = co_await mapper.findByPrimaryKey(parentId);
            j["parentName"] = prow.getValueOfName();
        } catch (const UnexpectedRows &) {
            // dangling parent reference; omit parentName rather than fail the read
        }
    }
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listOffices(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Office> mapper(txn);
    mapper.orderBy(m::Office::Cols::_hierarchy).orderBy(m::Office::Cols::_name);
    auto rows = co_await mapper.findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j = officeJson(r);
        const auto parentId = r.getValueOfParentId();
        if (parentId != kZeroUuid) j["parentId"] = parentId;
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getOffice(const turbo::RequestContext &ctx,
                                                         const std::string &id) {
    requirePermission(ctx, "READ_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await officeToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::getOfficeByExternalId(
    const turbo::RequestContext &ctx, const std::string &externalId) {
    requirePermission(ctx, "READ_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Office>(txn).findBy(
        Criteria(m::Office::Cols::_external_id, externalId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    co_return co_await officeToJson(txn, rows[0].getValueOfId());
}

drogon::Task<Json::Value> OrganizationService::createOffice(const turbo::RequestContext &ctx,
                                                            const Json::Value &body) {
    requirePermission(ctx, "CREATE_OFFICE");
    const std::string name = asStringOr(body, "name");
    const std::string openingDate = asStringOr(body, "openingDate");
    if (name.empty() || openingDate.empty())
        throw ApiError(drogon::k400BadRequest, "'name' and 'openingDate' are required",
                       "error.msg.organization.office.validation");
    const std::string parentId = asStringOr(body, "parentId");
    const std::string externalId = asStringOr(body, "externalId");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Office> mapper(txn);
    std::string parentHierarchy = ".";
    std::string parentIdValue = kZeroUuid;
    if (!parentId.empty()) {
        try {
            auto prow = co_await mapper.findByPrimaryKey(parentId);
            parentHierarchy = prow.getHierarchy() ? prow.getValueOfHierarchy() : ".";
            if (parentHierarchy.empty()) parentHierarchy = ".";
            parentIdValue = parentId;
        } catch (const UnexpectedRows &) {
            throw ApiError(drogon::k400BadRequest, "Unknown parentId: " + parentId,
                           "error.msg.organization.office.parent.not.found");
        }
    }

    m::Office row;
    row.setParentId(parentIdValue);
    row.setName(name);
    row.setOpeningDate(dateOr(openingDate, Date::now()));
    row.setUpdatedAt(Date::now());
    if (!externalId.empty()) row.setExternalId(externalId);
    try {
        auto inserted = co_await mapper.insert(row);
        const std::string id = inserted.getValueOfId();
        const std::string hierarchy = parentHierarchy + id + ".";
        inserted.setHierarchy(hierarchy);
        co_await mapper.update(inserted);
        co_await turbo::outbox::writeEvent(txn, ctx, "office", id, "office.created",
                                           Json::Value(Json::objectValue));
        co_return co_await officeToJson(txn, id);
    } catch (const DrogonDbException &e) {
        throw ApiError(drogon::k409Conflict, "An office with this name or external id already exists",
                       "error.msg.organization.office.duplicate");
    }
}

drogon::Task<Json::Value> OrganizationService::updateOffice(const turbo::RequestContext &ctx,
                                                            const std::string &id,
                                                            const Json::Value &body) {
    requirePermission(ctx, "UPDATE_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Office> mapper(txn);
    m::Office row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    }
    if (!asStringOr(body, "name").empty()) row.setName(asStringOr(body, "name"));
    if (!asStringOr(body, "openingDate").empty())
        row.setOpeningDate(dateOr(asStringOr(body, "openingDate"), row.getValueOfOpeningDate()));
    if (!asStringOr(body, "externalId").empty()) row.setExternalId(asStringOr(body, "externalId"));
    row.setUpdatedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "office", id, "office.updated", body);
    co_return co_await officeToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::updateOfficeByExternalId(
    const turbo::RequestContext &ctx, const std::string &externalId, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Office>(txn).findBy(
        Criteria(m::Office::Cols::_external_id, externalId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    co_return co_await updateOffice(ctx, rows[0].getValueOfId(), body);
}

drogon::Task<Json::Value> OrganizationService::officeTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Office>(txn).orderBy(m::Office::Cols::_name).findAll();
    Json::Value options(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        options.append(j);
    }
    Json::Value out;
    out["parentOfficeOptions"] = options;
    co_return out;
}

// ---------------------------------------------------------------------------
// office transactions
// ---------------------------------------------------------------------------

// office_transaction has a generated model too, but the from/to office name
// join has no ORM equivalent (Drogon's CoroMapper doesn't do joins), so
// office names are resolved with two extra findByPrimaryKey lookups per
// row. Traffic on this endpoint is low (manual inter-office cash
// transfers), so the N+1 pattern is an acceptable trade for staying off
// raw SQL here; revisit if this table grows large.
drogon::Task<Json::Value> OrganizationService::listOfficeTransactions(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_OFFICETRANSACTION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::OfficeTransaction> txMapper(txn);
    Mapper<m::Office> officeMapper(txn);
    auto rows = co_await txMapper.orderBy(m::OfficeTransaction::Cols::_transaction_date,
                                          drogon::orm::SortOrder::DESC)
                    .orderBy(m::OfficeTransaction::Cols::_id, drogon::orm::SortOrder::DESC)
                    .findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["fromOfficeId"] = r.getFromOfficeId() ? r.getValueOfFromOfficeId() : "";
        j["toOfficeId"] = r.getToOfficeId() ? r.getValueOfToOfficeId() : "";
        j["fromOfficeName"] = "";
        j["toOfficeName"] = "";
        try {
            if (r.getFromOfficeId())
                j["fromOfficeName"] =
                    (co_await officeMapper.findByPrimaryKey(r.getValueOfFromOfficeId())).getValueOfName();
        } catch (const UnexpectedRows &) {
        }
        try {
            if (r.getToOfficeId())
                j["toOfficeName"] =
                    (co_await officeMapper.findByPrimaryKey(r.getValueOfToOfficeId())).getValueOfName();
        } catch (const UnexpectedRows &) {
        }
        j["currencyCode"] = r.getValueOfCurrencyCode();
        j["transactionAmount"] = std::stod(r.getValueOfTransactionAmount());
        j["transactionDate"] = dateStr(r.getValueOfTransactionDate());
        j["description"] = r.getDescription() ? r.getValueOfDescription() : "";
        list.append(j);
    }
    Json::Value out;
    out["pageItems"] = list;
    out["totalFilteredRecords"] = static_cast<Json::UInt64>(rows.size());
    co_return out;
}

drogon::Task<Json::Value> OrganizationService::createOfficeTransaction(
    const turbo::RequestContext &ctx, const Json::Value &body) {
    requirePermission(ctx, "CREATE_OFFICETRANSACTION");
    const std::string fromOfficeId = asStringOr(body, "fromOfficeId");
    const std::string toOfficeId = asStringOr(body, "toOfficeId");
    const std::string currencyCode = asStringOr(body, "currencyCode");
    const std::string transactionDate = asStringOr(body, "transactionDate");
    const double amount = asDoubleOr(body, "transactionAmount", -1);
    if (fromOfficeId.empty() || toOfficeId.empty() || currencyCode.empty() ||
        transactionDate.empty() || amount <= 0)
        throw ApiError(drogon::k400BadRequest,
                       "'fromOfficeId', 'toOfficeId', 'currencyCode', 'transactionDate' and a "
                       "positive 'transactionAmount' are required",
                       "error.msg.organization.officetransaction.validation");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto currencyRows = co_await Mapper<m::OrganisationCurrency>(txn).findBy(
        Criteria(m::OrganisationCurrency::Cols::_code, currencyCode));
    if (currencyRows.empty())
        throw ApiError(drogon::k400BadRequest, "Unknown currency code: " + currencyCode,
                       "error.msg.organization.currency.not.found");
    const int decimals = currencyRows[0].getValueOfDecimalPlaces();

    m::OfficeTransaction row;
    row.setFromOfficeId(fromOfficeId);
    row.setToOfficeId(toOfficeId);
    row.setCurrencyCode(currencyCode);
    row.setCurrencyDigits(decimals);
    row.setTransactionAmount(std::to_string(amount));
    row.setTransactionDate(dateOr(transactionDate, Date::now()));
    if (!asStringOr(body, "description").empty())
        row.setDescription(asStringOr(body, "description"));

    auto inserted = co_await Mapper<m::OfficeTransaction>(txn).insert(row);
    const std::string id = inserted.getValueOfId();
    co_await turbo::outbox::writeEvent(txn, ctx, "officetransaction", id,
                                       "officetransaction.created", body);
    Json::Value out;
    out["officeTransactionId"] = id;
    co_return out;
}

drogon::Task<void> OrganizationService::deleteOfficeTransaction(const turbo::RequestContext &ctx,
                                                                 const std::string &id) {
    requirePermission(ctx, "DELETE_OFFICETRANSACTION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::OfficeTransaction>(txn).deleteByPrimaryKey(id);
    if (affected == 0)
        throw ApiError(drogon::k404NotFound, "Office transaction not found",
                       "error.msg.organization.officetransaction.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "officetransaction", id,
                                       "officetransaction.deleted", Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> OrganizationService::officeTransactionTemplate(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_OFFICETRANSACTION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto offices = co_await Mapper<m::Office>(txn).orderBy(m::Office::Cols::_name).findAll();
    auto currencies = co_await Mapper<m::OrganisationCurrency>(txn)
                          .orderBy(m::OrganisationCurrency::Cols::_code)
                          .findBy(Criteria(m::OrganisationCurrency::Cols::_is_enabled, true));
    Json::Value officeOptions(Json::arrayValue);
    for (const auto &r : offices) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        officeOptions.append(j);
    }
    Json::Value currencyOptions(Json::arrayValue);
    for (const auto &r : currencies) {
        Json::Value j;
        j["code"] = r.getValueOfCode();
        j["name"] = r.getValueOfName();
        j["displaySymbol"] = r.getDisplaySymbol() ? r.getValueOfDisplaySymbol() : "";
        currencyOptions.append(j);
    }
    Json::Value out;
    out["officeOptions"] = officeOptions;
    out["currencyOptions"] = currencyOptions;
    co_return out;
}

// ---------------------------------------------------------------------------
// staff
// ---------------------------------------------------------------------------

namespace {
Json::Value staffJson(const m::Staff &row, const std::string &officeName) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["officeId"] = row.getValueOfOfficeId();
    j["officeName"] = officeName;
    j["firstname"] = row.getValueOfFirstname();
    j["lastname"] = row.getValueOfLastname();
    j["displayName"] = row.getValueOfDisplayName();
    j["externalId"] = row.getExternalId() ? row.getValueOfExternalId() : "";
    j["mobileNo"] = row.getMobileNo() ? row.getValueOfMobileNo() : "";
    j["isLoanOfficer"] = row.getValueOfIsLoanOfficer();
    j["isActive"] = row.getValueOfIsActive();
    j["joiningDate"] = row.getJoiningDate() ? dateStr(row.getValueOfJoiningDate()) : "";
    return j;
}
}  // namespace

// Staff has no ORM join equivalent for the office name (CoroMapper doesn't
// do joins), so it is resolved with an extra findByPrimaryKey lookup per
// row/list, same trade-off already accepted for office transactions above.
drogon::Task<Json::Value> OrganizationService::staffToJson(Txn txn, const std::string &id) {
    m::Staff row;
    try {
        row = co_await Mapper<m::Staff>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Staff member not found",
                       "error.msg.organization.staff.not.found");
    }
    std::string officeName;
    try {
        officeName = (co_await Mapper<m::Office>(txn).findByPrimaryKey(row.getValueOfOfficeId()))
                         .getValueOfName();
    } catch (const UnexpectedRows &) {
    }
    co_return staffJson(row, officeName);
}

drogon::Task<Json::Value> OrganizationService::listStaff(const turbo::RequestContext &ctx,
                                                         const std::string &officeId,
                                                         bool loanOfficersOnly) {
    requirePermission(ctx, "READ_STAFF");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);

    std::map<std::string, std::string> officeNames;
    for (const auto &o : co_await Mapper<m::Office>(txn).findAll())
        officeNames[o.getValueOfId()] = o.getValueOfName();

    Mapper<m::Staff> mapper(txn);
    mapper.orderBy(m::Staff::Cols::_lastname).orderBy(m::Staff::Cols::_firstname);
    std::vector<m::Staff> rows;
    if (!officeId.empty() && loanOfficersOnly) {
        rows = co_await mapper.findBy(Criteria(m::Staff::Cols::_office_id, officeId) &&
                                      Criteria(m::Staff::Cols::_is_loan_officer, true));
    } else if (!officeId.empty()) {
        rows = co_await mapper.findBy(Criteria(m::Staff::Cols::_office_id, officeId));
    } else if (loanOfficersOnly) {
        rows = co_await mapper.findBy(Criteria(m::Staff::Cols::_is_loan_officer, true));
    } else {
        rows = co_await mapper.findAll();
    }
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(staffJson(r, officeNames[r.getValueOfOfficeId()]));
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getStaff(const turbo::RequestContext &ctx,
                                                        const std::string &id) {
    requirePermission(ctx, "READ_STAFF");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await staffToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::createStaff(const turbo::RequestContext &ctx,
                                                           const Json::Value &body) {
    requirePermission(ctx, "CREATE_STAFF");
    const std::string officeId = asStringOr(body, "officeId");
    const std::string firstname = asStringOr(body, "firstname");
    const std::string lastname = asStringOr(body, "lastname");
    if (officeId.empty() || firstname.empty() || lastname.empty())
        throw ApiError(drogon::k400BadRequest,
                       "'officeId', 'firstname' and 'lastname' are required",
                       "error.msg.organization.staff.validation");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        // is_deleted isn't on the generated Office model (see the office
        // section note above); offices are never soft-deleted via this API
        // in practice, so the existence check alone is equivalent here.
        co_await Mapper<m::Office>(txn).findByPrimaryKey(officeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k400BadRequest, "Unknown officeId: " + officeId,
                       "error.msg.organization.office.not.found");
    }

    m::Staff row;
    row.setOfficeId(officeId);
    row.setFirstname(firstname);
    row.setLastname(lastname);
    if (!asStringOr(body, "externalId").empty()) row.setExternalId(asStringOr(body, "externalId"));
    if (!asStringOr(body, "mobileNo").empty()) row.setMobileNo(asStringOr(body, "mobileNo"));
    row.setIsLoanOfficer(asBoolOr(body, "isLoanOfficer", false));
    if (!asStringOr(body, "joiningDate").empty())
        row.setJoiningDate(dateOr(asStringOr(body, "joiningDate"), Date::now()));
    row.setIsActive(true);
    row.setCreatedAt(Date::now());
    row.setModifiedAt(Date::now());
    try {
        auto inserted = co_await Mapper<m::Staff>(txn).insert(row);
        const std::string id = inserted.getValueOfId();
        co_await turbo::outbox::writeEvent(txn, ctx, "staff", id, "staff.created", body);
        co_return co_await staffToJson(txn, id);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "A staff member with this external id already exists",
                       "error.msg.organization.staff.duplicate");
    }
}

drogon::Task<Json::Value> OrganizationService::updateStaff(const turbo::RequestContext &ctx,
                                                           const std::string &id,
                                                           const Json::Value &body) {
    requirePermission(ctx, "UPDATE_STAFF");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Staff> mapper(txn);
    m::Staff row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Staff member not found",
                       "error.msg.organization.staff.not.found");
    }
    if (!asStringOr(body, "firstname").empty()) row.setFirstname(asStringOr(body, "firstname"));
    if (!asStringOr(body, "lastname").empty()) row.setLastname(asStringOr(body, "lastname"));
    if (!asStringOr(body, "mobileNo").empty()) row.setMobileNo(asStringOr(body, "mobileNo"));
    if (body.isMember("isLoanOfficer")) row.setIsLoanOfficer(asBoolOr(body, "isLoanOfficer", false));
    if (body.isMember("isActive")) row.setIsActive(asBoolOr(body, "isActive", true));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "staff", id, "staff.updated", body);
    co_return co_await staffToJson(txn, id);
}

// ---------------------------------------------------------------------------
// holidays
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::holidayToJson(Txn txn, const std::string &id) {
    m::Holiday row;
    try {
        row = co_await Mapper<m::Holiday>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Holiday not found",
                       "error.msg.organization.holiday.not.found");
    }
    if (row.getValueOfStatus() == "DELETED")
        throw ApiError(drogon::k404NotFound, "Holiday not found",
                       "error.msg.organization.holiday.not.found");
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getValueOfName();
    j["fromDate"] = dateStr(row.getValueOfFromDate());
    j["toDate"] = dateStr(row.getValueOfToDate());
    j["repaymentsRescheduledTo"] =
        row.getRepaymentScheduledTo() ? dateStr(row.getValueOfRepaymentScheduledTo()) : "";
    j["description"] = row.getDescription() ? row.getValueOfDescription() : "";
    j["status"] = row.getValueOfStatus();
    j["appliesToAllOffices"] = row.getValueOfAppliesToAllOffices();
    if (!row.getValueOfAppliesToAllOffices()) {
        // holiday_office is a pure many-to-many join table with a composite
        // primary key (holiday_id, office_id) and no surrogate id column, so
        // it can't be a single-primary-key CoroMapper<T> model — see the
        // file-level ORM coverage note above.
        auto offices = co_await txn->execSqlCoro(
            "SELECT o.id::text AS id, o.name FROM holiday_office ho "
            "JOIN office o ON o.id = ho.office_id WHERE ho.holiday_id::text = $1", id);
        Json::Value offs(Json::arrayValue);
        for (const auto &o : offices) {
            Json::Value oj;
            oj["id"] = o["id"].as<std::string>();
            oj["name"] = o["name"].as<std::string>();
            offs.append(oj);
        }
        j["offices"] = offs;
    }
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listHolidays(const turbo::RequestContext &ctx,
                                                            const std::string &officeId) {
    requirePermission(ctx, "READ_HOLIDAY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto toList = [](const std::vector<m::Holiday> &rows) {
        Json::Value list(Json::arrayValue);
        for (const auto &r : rows) {
            Json::Value j;
            j["id"] = r.getValueOfId();
            j["name"] = r.getValueOfName();
            j["fromDate"] = dateStr(r.getValueOfFromDate());
            j["toDate"] = dateStr(r.getValueOfToDate());
            j["status"] = r.getValueOfStatus();
            list.append(j);
        }
        return list;
    };
    auto rows = co_await Mapper<m::Holiday>(txn)
                    .orderBy(m::Holiday::Cols::_from_date, drogon::orm::SortOrder::DESC)
                    .findBy(Criteria(m::Holiday::Cols::_status, CompareOperator::NE, "DELETED"));
    if (officeId.empty()) co_return toList(rows);

    // holiday_office join-table exception (see note above): fetch the set of
    // holiday ids explicitly linked to this office with one narrow raw
    // query, then filter the ORM-fetched holidays in-process.
    auto linked = co_await txn->execSqlCoro(
        "SELECT holiday_id::text AS holiday_id FROM holiday_office WHERE office_id::text = $1",
        officeId);
    std::set<std::string> linkedIds;
    for (const auto &r : linked) linkedIds.insert(r["holiday_id"].as<std::string>());
    std::vector<m::Holiday> filtered;
    for (auto &r : rows) {
        if (r.getValueOfAppliesToAllOffices() || linkedIds.count(r.getValueOfId()))
            filtered.push_back(r);
    }
    co_return toList(filtered);
}

drogon::Task<Json::Value> OrganizationService::getHoliday(const turbo::RequestContext &ctx,
                                                          const std::string &id) {
    requirePermission(ctx, "READ_HOLIDAY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await holidayToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::createHoliday(const turbo::RequestContext &ctx,
                                                             const Json::Value &body) {
    requirePermission(ctx, "CREATE_HOLIDAY");
    const std::string name = asStringOr(body, "name");
    const std::string fromDate = asStringOr(body, "fromDate");
    const std::string toDate = asStringOr(body, "toDate");
    if (name.empty() || fromDate.empty() || toDate.empty())
        throw ApiError(drogon::k400BadRequest, "'name', 'fromDate' and 'toDate' are required",
                       "error.msg.organization.holiday.validation");
    const bool appliesToAll = !body.isMember("offices") || body["offices"].empty();

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::Holiday row;
    row.setName(name);
    row.setFromDate(dateOr(fromDate, Date::now()));
    row.setToDate(dateOr(toDate, Date::now()));
    if (!asStringOr(body, "repaymentsRescheduledTo").empty())
        row.setRepaymentScheduledTo(dateOr(asStringOr(body, "repaymentsRescheduledTo"), Date::now()));
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    row.setAppliesToAllOffices(appliesToAll);
    row.setStatus("PENDING_FOR_ACTIVATION");
    row.setCreatedAt(Date::now());
    row.setModifiedAt(Date::now());
    auto inserted = co_await Mapper<m::Holiday>(txn).insert(row);
    const std::string id = inserted.getValueOfId();
    if (!appliesToAll) {
        // holiday_office join-table exception (see note above).
        for (const auto &officeId : body["offices"]) {
            co_await txn->execSqlCoro(
                "INSERT INTO holiday_office (holiday_id, office_id) VALUES ($1::uuid, $2::uuid)",
                id, officeId.asString());
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "holiday", id, "holiday.created", body);
    co_return co_await holidayToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::updateHoliday(const turbo::RequestContext &ctx,
                                                             const std::string &id,
                                                             const Json::Value &body) {
    requirePermission(ctx, "UPDATE_HOLIDAY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Holiday> mapper(txn);
    m::Holiday row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound,
                       "Holiday not found or is no longer pending activation",
                       "error.msg.organization.holiday.not.found");
    }
    if (row.getValueOfStatus() != "PENDING_FOR_ACTIVATION")
        throw ApiError(drogon::k404NotFound,
                       "Holiday not found or is no longer pending activation",
                       "error.msg.organization.holiday.not.found");
    if (!asStringOr(body, "name").empty()) row.setName(asStringOr(body, "name"));
    if (!asStringOr(body, "fromDate").empty())
        row.setFromDate(dateOr(asStringOr(body, "fromDate"), row.getValueOfFromDate()));
    if (!asStringOr(body, "toDate").empty())
        row.setToDate(dateOr(asStringOr(body, "toDate"), row.getValueOfToDate()));
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "holiday", id, "holiday.updated", body);
    co_return co_await holidayToJson(txn, id);
}

drogon::Task<void> OrganizationService::deleteHoliday(const turbo::RequestContext &ctx,
                                                      const std::string &id) {
    requirePermission(ctx, "DELETE_HOLIDAY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Holiday> mapper(txn);
    m::Holiday row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Holiday not found",
                       "error.msg.organization.holiday.not.found");
    }
    if (row.getValueOfStatus() == "DELETED")
        throw ApiError(drogon::k404NotFound, "Holiday not found",
                       "error.msg.organization.holiday.not.found");
    row.setStatus("DELETED");
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "holiday", id, "holiday.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> OrganizationService::activateHoliday(const turbo::RequestContext &ctx,
                                                               const std::string &id) {
    requirePermission(ctx, "ACTIVATE_HOLIDAY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Holiday> mapper(txn);
    m::Holiday row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound,
                       "Holiday not found or is not pending activation",
                       "error.msg.organization.holiday.not.found");
    }
    if (row.getValueOfStatus() != "PENDING_FOR_ACTIVATION")
        throw ApiError(drogon::k404NotFound,
                       "Holiday not found or is not pending activation",
                       "error.msg.organization.holiday.not.found");
    row.setStatus("ACTIVE");
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "holiday", id, "holiday.activated",
                                       Json::Value(Json::objectValue));
    co_return co_await holidayToJson(txn, id);
}

Json::Value OrganizationService::holidayTemplate(const turbo::RequestContext &) {
    Json::Value options(Json::arrayValue);
    for (const auto *v : {"SAME_DAY", "MOVE_TO_NEXT_WORKING_DAY", "MOVE_TO_NEXT_REPAYMENT_MEETING_DAY"})
        options.append(v);
    Json::Value out;
    out["repaymentScheduleTypeOptions"] = options;
    return out;
}

// ---------------------------------------------------------------------------
// working days
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::getWorkingDays(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_WORKINGDAYS");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Json::Value out;
    m::WorkingDays row;
    try {
        row = co_await Mapper<m::WorkingDays>(txn).findByPrimaryKey(1);
    } catch (const UnexpectedRows &) {
        co_return out;
    }
    Json::Value days(Json::arrayValue);
    std::string raw = row.getValueOfWorkingDays();
    std::string cur;
    for (char c : raw + ",") {
        if (c == ',') {
            if (!cur.empty()) days.append(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }
    out["recurrence"] = raw;
    out["workingDays"] = days;
    out["repaymentReschedulingType"] = row.getValueOfRepaymentReschedulingType();
    out["extendTermForDailyRepayments"] = row.getValueOfExtendTermForDailyRepayments();
    co_return out;
}

drogon::Task<Json::Value> OrganizationService::updateWorkingDays(const turbo::RequestContext &ctx,
                                                                 const Json::Value &body) {
    requirePermission(ctx, "UPDATE_WORKINGDAYS");
    std::string days;
    if (body.isMember("workingDays") && body["workingDays"].isArray()) {
        for (const auto &d : body["workingDays"]) {
            if (!days.empty()) days += ",";
            days += d.asString();
        }
    }
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::WorkingDays> mapper(txn);
    m::WorkingDays row = co_await mapper.findByPrimaryKey(1);
    if (!days.empty()) row.setWorkingDays(days);
    if (!asStringOr(body, "repaymentReschedulingType").empty())
        row.setRepaymentReschedulingType(asStringOr(body, "repaymentReschedulingType"));
    if (body.isMember("extendTermForDailyRepayments"))
        row.setExtendTermForDailyRepayments(asBoolOr(body, "extendTermForDailyRepayments", false));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "workingdays", "1", "workingdays.updated", body);
    co_return co_await getWorkingDays(ctx);
}

Json::Value OrganizationService::workingDaysTemplate(const turbo::RequestContext &) {
    Json::Value days(Json::arrayValue);
    for (const auto *d : {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"})
        days.append(d);
    Json::Value options(Json::arrayValue);
    for (const auto *v : {"SAME_DAY", "MOVE_TO_NEXT_WORKING_DAY", "MOVE_TO_NEXT_REPAYMENT_MEETING_DAY"})
        options.append(v);
    Json::Value out;
    out["dayOptions"] = days;
    out["repaymentReschedulingTypeOptions"] = options;
    return out;
}

// ---------------------------------------------------------------------------
// currencies
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::getCurrencies(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CURRENCY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await Mapper<m::OrganisationCurrency>(txn).orderBy(m::OrganisationCurrency::Cols::_code).findAll();
    Json::Value selected(Json::arrayValue);
    Json::Value all(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["code"] = r.getValueOfCode();
        j["name"] = r.getValueOfName();
        j["decimalPlaces"] = r.getValueOfDecimalPlaces();
        j["displaySymbol"] = r.getDisplaySymbol() ? r.getValueOfDisplaySymbol() : "";
        all.append(j);
        if (r.getValueOfIsEnabled()) selected.append(j);
    }
    Json::Value out;
    out["selectedCurrencyOptions"] = selected;
    out["currencyOptions"] = all;
    co_return out;
}

drogon::Task<Json::Value> OrganizationService::updateCurrencies(const turbo::RequestContext &ctx,
                                                                const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CURRENCY");
    if (!body.isMember("currencies") || !body["currencies"].isArray())
        throw ApiError(drogon::k400BadRequest, "'currencies' must be an array of ISO codes",
                       "error.msg.organization.currency.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::OrganisationCurrency> mapper(txn);
    auto allCurrencies = co_await mapper.findAll();
    for (auto row : allCurrencies) {
        row.setIsEnabled(false);
        co_await mapper.update(row);
    }
    for (const auto &code : body["currencies"]) {
        auto matches = co_await mapper.findBy(
            Criteria(m::OrganisationCurrency::Cols::_code, code.asString()));
        if (matches.empty())
            throw ApiError(drogon::k400BadRequest, "Unknown currency code: " + code.asString(),
                           "error.msg.organization.currency.not.found");
        matches[0].setIsEnabled(true);
        co_await mapper.update(matches[0]);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "currency", "org", "currency.updated", body);
    co_return co_await getCurrencies(ctx);
}

// ---------------------------------------------------------------------------
// funds
// ---------------------------------------------------------------------------

namespace {
Json::Value fundJson(const m::Fund &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getValueOfName();
    j["externalId"] = row.getExternalId() ? row.getValueOfExternalId() : "";
    return j;
}
}  // namespace

drogon::Task<Json::Value> OrganizationService::fundToJson(Txn txn, const std::string &id) {
    try {
        co_return fundJson(co_await Mapper<m::Fund>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Fund not found", "error.msg.organization.fund.not.found");
    }
}

drogon::Task<Json::Value> OrganizationService::listFunds(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_FUND");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Fund>(txn).orderBy(m::Fund::Cols::_name).findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(fundJson(r));
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getFund(const turbo::RequestContext &ctx,
                                                       const std::string &id) {
    requirePermission(ctx, "READ_FUND");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await fundToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::createFund(const turbo::RequestContext &ctx,
                                                          const Json::Value &body) {
    requirePermission(ctx, "CREATE_FUND");
    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.organization.fund.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::Fund row;
    row.setName(name);
    if (!asStringOr(body, "externalId").empty()) row.setExternalId(asStringOr(body, "externalId"));
    row.setCreatedAt(Date::now());
    row.setModifiedAt(Date::now());
    try {
        auto inserted = co_await Mapper<m::Fund>(txn).insert(row);
        const std::string id = inserted.getValueOfId();
        co_await turbo::outbox::writeEvent(txn, ctx, "fund", id, "fund.created", body);
        co_return co_await fundToJson(txn, id);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "A fund with this name already exists",
                       "error.msg.organization.fund.duplicate");
    }
}

drogon::Task<Json::Value> OrganizationService::updateFund(const turbo::RequestContext &ctx,
                                                          const std::string &id,
                                                          const Json::Value &body) {
    requirePermission(ctx, "UPDATE_FUND");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Fund> mapper(txn);
    m::Fund row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Fund not found", "error.msg.organization.fund.not.found");
    }
    if (!asStringOr(body, "name").empty()) row.setName(asStringOr(body, "name"));
    if (!asStringOr(body, "externalId").empty()) row.setExternalId(asStringOr(body, "externalId"));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "fund", id, "fund.updated", body);
    co_return co_await fundToJson(txn, id);
}

// ---------------------------------------------------------------------------
// payment types
// ---------------------------------------------------------------------------

namespace {
Json::Value paymentTypeJson(const m::PaymentType &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getValue() ? row.getValueOfValue() : "";
    j["description"] = row.getDescription() ? row.getValueOfDescription() : "";
    j["isCashPayment"] = row.getIsCashPayment() ? row.getValueOfIsCashPayment() : false;
    j["position"] = row.getValueOfOrderPosition();
    j["isSystemDefined"] = row.getIsSystemDefined() ? row.getValueOfIsSystemDefined() : false;
    return j;
}
}  // namespace

drogon::Task<Json::Value> OrganizationService::paymentTypeToJson(Txn txn, const std::string &id) {
    try {
        co_return paymentTypeJson(co_await Mapper<m::PaymentType>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Payment type not found",
                       "error.msg.organization.paymenttype.not.found");
    }
}

drogon::Task<Json::Value> OrganizationService::listPaymentTypes(const turbo::RequestContext &ctx,
                                                                bool onlyActive) {
    requirePermission(ctx, "READ_PAYMENTTYPE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::PaymentType>(txn)
                    .orderBy(m::PaymentType::Cols::_order_position)
                    .orderBy(m::PaymentType::Cols::_value)
                    .findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(paymentTypeJson(r));
    (void)onlyActive;  // payment_type has no disabled flag yet; reserved for parity
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getPaymentType(const turbo::RequestContext &ctx,
                                                              const std::string &id) {
    requirePermission(ctx, "READ_PAYMENTTYPE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await paymentTypeToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::createPaymentType(const turbo::RequestContext &ctx,
                                                                 const Json::Value &body) {
    requirePermission(ctx, "CREATE_PAYMENTTYPE");
    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.organization.paymenttype.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::PaymentType row;
    row.setValue(name);
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    row.setIsCashPayment(asBoolOr(body, "isCashPayment", false));
    row.setOrderPosition(asIntOr(body, "position", 0));
    try {
        auto inserted = co_await Mapper<m::PaymentType>(txn).insert(row);
        const std::string id = inserted.getValueOfId();
        co_await turbo::outbox::writeEvent(txn, ctx, "paymenttype", id, "paymenttype.created", body);
        co_return paymentTypeJson(inserted);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "A payment type with this name already exists",
                       "error.msg.organization.paymenttype.duplicate");
    }
}

drogon::Task<Json::Value> OrganizationService::updatePaymentType(const turbo::RequestContext &ctx,
                                                                 const std::string &id,
                                                                 const Json::Value &body) {
    requirePermission(ctx, "UPDATE_PAYMENTTYPE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::PaymentType> mapper(txn);
    m::PaymentType row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Payment type not found",
                       "error.msg.organization.paymenttype.not.found");
    }
    if (!asStringOr(body, "name").empty()) row.setValue(asStringOr(body, "name"));
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    if (body.isMember("isCashPayment")) row.setIsCashPayment(asBoolOr(body, "isCashPayment", false));
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "paymenttype", id, "paymenttype.updated", body);
    co_return co_await paymentTypeToJson(txn, id);
}

drogon::Task<void> OrganizationService::deletePaymentType(const turbo::RequestContext &ctx,
                                                          const std::string &id) {
    requirePermission(ctx, "DELETE_PAYMENTTYPE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::PaymentType> mapper(txn);
    m::PaymentType row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Payment type not found",
                       "error.msg.organization.paymenttype.not.found");
    }
    if (row.getIsSystemDefined() && row.getValueOfIsSystemDefined())
        throw ApiError(drogon::k403Forbidden, "System-defined payment types cannot be deleted",
                       "error.msg.organization.paymenttype.protected");
    co_await mapper.deleteByPrimaryKey(id);
    co_await turbo::outbox::writeEvent(txn, ctx, "paymenttype", id, "paymenttype.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// entity-to-entity mapping
// ---------------------------------------------------------------------------

namespace {
Json::Value entityMappingJson(const m::EntityMapping &row, const m::EntityRelation &relation) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["relationId"] = row.getValueOfRelationId();
    j["codeFrom"] = relation.getValueOfCodeFrom();
    j["codeTo"] = relation.getValueOfCodeTo();
    j["fromId"] = row.getValueOfFromId();
    j["toId"] = row.getValueOfToId();
    return j;
}
}  // namespace

// entity_mapping -> entity_relation has no ORM join equivalent (CoroMapper
// doesn't do joins), so the relation's code_from/code_to are resolved with
// extra findByPrimaryKey lookups, same trade-off already accepted for
// office transactions and staff above.
drogon::Task<Json::Value> OrganizationService::listEntityMappings(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    std::map<std::string, m::EntityRelation> relations;
    for (const auto &r : co_await Mapper<m::EntityRelation>(txn).findAll())
        relations.emplace(r.getValueOfId(), r);
    auto rows = co_await Mapper<m::EntityMapping>(txn)
                    .orderBy(m::EntityMapping::Cols::_created_at, drogon::orm::SortOrder::DESC)
                    .findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(entityMappingJson(r, relations[r.getValueOfRelationId()]));
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getEntityMapping(const turbo::RequestContext &ctx,
                                                                const std::string &mapId) {
    requirePermission(ctx, "READ_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::EntityMapping row;
    try {
        row = co_await Mapper<m::EntityMapping>(txn).findByPrimaryKey(mapId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Entity mapping not found",
                       "error.msg.organization.entitymapping.not.found");
    }
    auto relation = co_await Mapper<m::EntityRelation>(txn).findByPrimaryKey(row.getValueOfRelationId());
    co_return entityMappingJson(row, relation);
}

drogon::Task<Json::Value> OrganizationService::queryEntityMappings(
    const turbo::RequestContext &ctx, const std::string &relId, const std::string &fromId,
    const std::string &toId) {
    requirePermission(ctx, "READ_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto relation = co_await Mapper<m::EntityRelation>(txn).findByPrimaryKey(relId);
    auto rows = co_await Mapper<m::EntityMapping>(txn).findBy(
        Criteria(m::EntityMapping::Cols::_relation_id, relId) &&
        Criteria(m::EntityMapping::Cols::_from_id, fromId) &&
        Criteria(m::EntityMapping::Cols::_to_id, toId));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(entityMappingJson(r, relation));
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::createEntityMapping(
    const turbo::RequestContext &ctx, const std::string &relId, const Json::Value &body) {
    requirePermission(ctx, "CREATE_ENTITYTOENTITYMAPPING");
    const std::string fromId = asStringOr(body, "fromId");
    const std::string toId = asStringOr(body, "toId");
    if (fromId.empty() || toId.empty())
        throw ApiError(drogon::k400BadRequest, "'fromId' and 'toId' are required",
                       "error.msg.organization.entitymapping.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_await Mapper<m::EntityRelation>(txn).findByPrimaryKey(relId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k400BadRequest, "Unknown relation id: " + relId,
                       "error.msg.organization.entityrelation.not.found");
    }
    m::EntityMapping row;
    row.setRelationId(relId);
    row.setFromId(fromId);
    row.setToId(toId);
    row.setCreatedAt(Date::now());
    auto inserted = co_await Mapper<m::EntityMapping>(txn).insert(row);
    const std::string id = inserted.getValueOfId();
    co_await turbo::outbox::writeEvent(txn, ctx, "entitymapping", id, "entitymapping.created", body);
    co_return co_await getEntityMapping(ctx, id);
}

drogon::Task<Json::Value> OrganizationService::updateEntityMapping(
    const turbo::RequestContext &ctx, const std::string &mapId, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::EntityMapping> mapper(txn);
    m::EntityMapping row;
    try {
        row = co_await mapper.findByPrimaryKey(mapId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Entity mapping not found",
                       "error.msg.organization.entitymapping.not.found");
    }
    if (!asStringOr(body, "toId").empty()) row.setToId(asStringOr(body, "toId"));
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "entitymapping", mapId, "entitymapping.updated",
                                       body);
    co_return co_await getEntityMapping(ctx, mapId);
}

drogon::Task<void> OrganizationService::deleteEntityMapping(const turbo::RequestContext &ctx,
                                                            const std::string &mapId) {
    requirePermission(ctx, "DELETE_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::EntityMapping>(txn).deleteByPrimaryKey(mapId);
    if (affected == 0)
        throw ApiError(drogon::k404NotFound, "Entity mapping not found",
                       "error.msg.organization.entitymapping.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "entitymapping", mapId, "entitymapping.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// taxes
// ---------------------------------------------------------------------------

namespace {
Json::Value taxComponentJson(const m::TaxComponent &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getValueOfName();
    j["percentage"] = std::stod(row.getValueOfPercentage());
    j["startDate"] = dateStr(row.getValueOfStartDate());
    j["debitAccountId"] = row.getDebitAccountId() ? row.getValueOfDebitAccountId() : "";
    j["creditAccountId"] = row.getCreditAccountId() ? row.getValueOfCreditAccountId() : "";
    return j;
}
}  // namespace

drogon::Task<Json::Value> OrganizationService::taxComponentToJson(Txn txn, const std::string &id) {
    try {
        co_return taxComponentJson(co_await Mapper<m::TaxComponent>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Tax component not found",
                       "error.msg.organization.taxcomponent.not.found");
    }
}

drogon::Task<Json::Value> OrganizationService::listTaxComponents(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_TAXCOMPONENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::TaxComponent>(txn).orderBy(m::TaxComponent::Cols::_name).findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(taxComponentJson(r));
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getTaxComponent(const turbo::RequestContext &ctx,
                                                               const std::string &id) {
    requirePermission(ctx, "READ_TAXCOMPONENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await taxComponentToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::createTaxComponent(const turbo::RequestContext &ctx,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "CREATE_TAXCOMPONENT");
    const std::string name = asStringOr(body, "name");
    const std::string startDate = asStringOr(body, "startDate");
    const double percentage = asDoubleOr(body, "percentage", -1);
    if (name.empty() || startDate.empty() || percentage < 0)
        throw ApiError(drogon::k400BadRequest,
                       "'name', 'startDate' and a non-negative 'percentage' are required",
                       "error.msg.organization.taxcomponent.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::TaxComponent row;
    row.setName(name);
    row.setPercentage(std::to_string(percentage));
    row.setStartDate(dateOr(startDate, Date::now()));
    if (!asStringOr(body, "debitAccountId").empty())
        row.setDebitAccountId(asStringOr(body, "debitAccountId"));
    if (!asStringOr(body, "creditAccountId").empty())
        row.setCreditAccountId(asStringOr(body, "creditAccountId"));
    row.setCreatedAt(Date::now());
    row.setModifiedAt(Date::now());
    try {
        auto inserted = co_await Mapper<m::TaxComponent>(txn).insert(row);
        const std::string id = inserted.getValueOfId();
        co_await turbo::outbox::writeEvent(txn, ctx, "taxcomponent", id, "taxcomponent.created",
                                           body);
        co_return co_await taxComponentToJson(txn, id);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "A tax component with this name already exists",
                       "error.msg.organization.taxcomponent.duplicate");
    }
}

drogon::Task<Json::Value> OrganizationService::updateTaxComponent(const turbo::RequestContext &ctx,
                                                                  const std::string &id,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_TAXCOMPONENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::TaxComponent> mapper(txn);
    m::TaxComponent row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Tax component not found",
                       "error.msg.organization.taxcomponent.not.found");
    }
    if (!asStringOr(body, "name").empty()) row.setName(asStringOr(body, "name"));
    if (body.isMember("percentage")) row.setPercentage(std::to_string(asDoubleOr(body, "percentage", 0)));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "taxcomponent", id, "taxcomponent.updated", body);
    co_return co_await taxComponentToJson(txn, id);
}

// tax_group -> tax_group_mapping -> tax_component has no ORM join
// equivalent (CoroMapper doesn't do joins), so each mapping's component
// name/percentage is resolved with an extra findByPrimaryKey lookup, same
// trade-off already accepted elsewhere in this file.
drogon::Task<Json::Value> OrganizationService::taxGroupToJson(Txn txn, const std::string &id) {
    m::TaxGroup group;
    try {
        group = co_await Mapper<m::TaxGroup>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Tax group not found",
                       "error.msg.organization.taxgroup.not.found");
    }
    Json::Value j;
    j["id"] = group.getValueOfId();
    j["name"] = group.getValueOfName();
    auto mappings = co_await Mapper<m::TaxGroupMapping>(txn)
                        .orderBy(m::TaxGroupMapping::Cols::_start_date)
                        .findBy(Criteria(m::TaxGroupMapping::Cols::_tax_group_id, id));
    Json::Value comps(Json::arrayValue);
    for (const auto &mapping : mappings) {
        try {
            auto component =
                co_await Mapper<m::TaxComponent>(txn).findByPrimaryKey(mapping.getValueOfTaxComponentId());
            Json::Value cj;
            cj["id"] = component.getValueOfId();
            cj["name"] = component.getValueOfName();
            cj["percentage"] = std::stod(component.getValueOfPercentage());
            cj["startDate"] = dateStr(mapping.getValueOfStartDate());
            comps.append(cj);
        } catch (const UnexpectedRows &) {
        }
    }
    j["taxComponents"] = comps;
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listTaxGroups(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_TAXGROUP");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::TaxGroup>(txn).orderBy(m::TaxGroup::Cols::_name).findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["name"] = r.getValueOfName();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getTaxGroup(const turbo::RequestContext &ctx,
                                                           const std::string &id) {
    requirePermission(ctx, "READ_TAXGROUP");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await taxGroupToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::createTaxGroup(const turbo::RequestContext &ctx,
                                                              const Json::Value &body) {
    requirePermission(ctx, "CREATE_TAXGROUP");
    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.organization.taxgroup.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        m::TaxGroup group;
        group.setName(name);
        group.setCreatedAt(Date::now());
        group.setModifiedAt(Date::now());
        auto inserted = co_await Mapper<m::TaxGroup>(txn).insert(group);
        const std::string id = inserted.getValueOfId();
        if (body.isMember("taxComponents") && body["taxComponents"].isArray()) {
            for (const auto &tc : body["taxComponents"]) {
                const std::string componentId = asStringOr(tc, "taxComponentId");
                const std::string startDate = asStringOr(tc, "startDate");
                if (componentId.empty() || startDate.empty()) continue;
                m::TaxGroupMapping mapping;
                mapping.setTaxGroupId(id);
                mapping.setTaxComponentId(componentId);
                mapping.setStartDate(dateOr(startDate, Date::now()));
                co_await Mapper<m::TaxGroupMapping>(txn).insert(mapping);
            }
        }
        co_await turbo::outbox::writeEvent(txn, ctx, "taxgroup", id, "taxgroup.created", body);
        co_return co_await taxGroupToJson(txn, id);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "A tax group with this name already exists",
                       "error.msg.organization.taxgroup.duplicate");
    }
}

drogon::Task<Json::Value> OrganizationService::updateTaxGroup(const turbo::RequestContext &ctx,
                                                              const std::string &id,
                                                              const Json::Value &body) {
    requirePermission(ctx, "UPDATE_TAXGROUP");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::TaxGroup> mapper(txn);
    m::TaxGroup group;
    try {
        group = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Tax group not found",
                       "error.msg.organization.taxgroup.not.found");
    }
    if (!asStringOr(body, "name").empty()) group.setName(asStringOr(body, "name"));
    group.setModifiedAt(Date::now());
    co_await mapper.update(group);
    if (body.isMember("taxComponents") && body["taxComponents"].isArray()) {
        co_await Mapper<m::TaxGroupMapping>(txn).deleteBy(
            Criteria(m::TaxGroupMapping::Cols::_tax_group_id, id));
        for (const auto &tc : body["taxComponents"]) {
            const std::string componentId = asStringOr(tc, "taxComponentId");
            const std::string startDate = asStringOr(tc, "startDate");
            if (componentId.empty() || startDate.empty()) continue;
            m::TaxGroupMapping mapping;
            mapping.setTaxGroupId(id);
            mapping.setTaxComponentId(componentId);
            mapping.setStartDate(dateOr(startDate, Date::now()));
            co_await Mapper<m::TaxGroupMapping>(txn).insert(mapping);
        }
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "taxgroup", id, "taxgroup.updated", body);
    co_return co_await taxGroupToJson(txn, id);
}

Json::Value OrganizationService::taxComponentTemplate(const turbo::RequestContext &) {
    Json::Value out;
    Json::Value types(Json::arrayValue);
    types.append("DEBIT");
    types.append("CREDIT");
    out["taxComponentTypeOptions"] = types;
    return out;
}

Json::Value OrganizationService::taxGroupTemplate(const turbo::RequestContext &) {
    Json::Value out;
    out["taxComponents"] = Json::Value(Json::arrayValue);
    return out;
}

}  // namespace turbo_ledger_organization
