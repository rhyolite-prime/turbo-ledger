#include "OrganizationService.h"

#include <drogon/orm/DbClient.h>

#include "turbo/Outbox.h"
#include "turbo/TenantDb.h"

using drogon::orm::DrogonDbException;

namespace turbo_ledger_organization {

namespace {

constexpr const char *kZeroUuid = "00000000-0000-0000-0000-000000000000";

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
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::officeToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, external_id, name, parent_id::text AS parent_id, hierarchy, "
        "  opening_date::text AS opening_date, updated_at::text AS updated_at "
        "FROM office WHERE id::text = $1 AND NOT is_deleted",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["name"] = r["name"].as<std::string>();
    j["externalId"] = r["external_id"].isNull() ? "" : r["external_id"].as<std::string>();
    j["openingDate"] = r["opening_date"].as<std::string>();
    j["hierarchy"] = r["hierarchy"].isNull() ? "" : r["hierarchy"].as<std::string>();
    const auto parentId = r["parent_id"].as<std::string>();
    if (parentId != kZeroUuid) {
        j["parentId"] = parentId;
        auto prow = co_await txn->execSqlCoro(
            "SELECT name FROM office WHERE id::text = $1", parentId);
        if (prow.size() > 0) j["parentName"] = prow[0]["name"].as<std::string>();
    }
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listOffices(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, external_id, name, parent_id::text AS parent_id, hierarchy, "
        "  opening_date::text AS opening_date "
        "FROM office WHERE NOT is_deleted ORDER BY hierarchy NULLS LAST, name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        j["externalId"] = r["external_id"].isNull() ? "" : r["external_id"].as<std::string>();
        j["hierarchy"] = r["hierarchy"].isNull() ? "" : r["hierarchy"].as<std::string>();
        j["openingDate"] = r["opening_date"].as<std::string>();
        const auto parentId = r["parent_id"].as<std::string>();
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
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id FROM office WHERE external_id = $1 AND NOT is_deleted", externalId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    co_return co_await officeToJson(txn, rows[0]["id"].as<std::string>());
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
    std::string parentHierarchy = ".";
    std::string parentIdValue = kZeroUuid;
    if (!parentId.empty()) {
        auto prow = co_await txn->execSqlCoro(
            "SELECT hierarchy FROM office WHERE id::text = $1 AND NOT is_deleted", parentId);
        if (prow.size() == 0)
            throw ApiError(drogon::k400BadRequest, "Unknown parentId: " + parentId,
                           "error.msg.organization.office.parent.not.found");
        parentHierarchy = prow[0]["hierarchy"].isNull() ? "." : prow[0]["hierarchy"].as<std::string>();
        parentIdValue = parentId;
    }

    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO office (parent_id, name, opening_date, external_id, updated_at) "
            "VALUES ($1::uuid, $2, $3::date, NULLIF($4, ''), CURRENT_DATE) RETURNING id::text AS id",
            parentIdValue, name, openingDate, externalId);
        const std::string id = rows[0]["id"].as<std::string>();
        const std::string hierarchy = parentHierarchy + id + ".";
        co_await txn->execSqlCoro("UPDATE office SET hierarchy = $2 WHERE id::text = $1", id,
                                  hierarchy);
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
    auto rows = co_await txn->execSqlCoro(
        "UPDATE office SET name = COALESCE(NULLIF($2, ''), name), "
        "  opening_date = COALESCE(NULLIF($3, '')::date, opening_date), "
        "  external_id = COALESCE(NULLIF($4, ''), external_id), updated_at = CURRENT_DATE "
        "WHERE id::text = $1 AND NOT is_deleted RETURNING id::text AS id",
        id, asStringOr(body, "name"), asStringOr(body, "openingDate"),
        asStringOr(body, "externalId"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "office", id, "office.updated", body);
    co_return co_await officeToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::updateOfficeByExternalId(
    const turbo::RequestContext &ctx, const std::string &externalId, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id FROM office WHERE external_id = $1 AND NOT is_deleted", externalId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Office not found",
                       "error.msg.organization.office.not.found");
    co_return co_await updateOffice(ctx, rows[0]["id"].as<std::string>(), body);
}

drogon::Task<Json::Value> OrganizationService::officeTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_OFFICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name FROM office WHERE NOT is_deleted ORDER BY name");
    Json::Value options(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        options.append(j);
    }
    Json::Value out;
    out["parentOfficeOptions"] = options;
    co_return out;
}

// ---------------------------------------------------------------------------
// office transactions
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::listOfficeTransactions(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_OFFICETRANSACTION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT ot.id::text AS id, ot.from_office_id::text AS from_office_id, "
        "  ot.to_office_id::text AS to_office_id, fo.name AS from_office_name, "
        "  tob.name AS to_office_name, ot.currency_code, ot.transaction_amount, "
        "  ot.transaction_date::text AS transaction_date, ot.description "
        "FROM office_transaction ot "
        "LEFT JOIN office fo ON fo.id = ot.from_office_id "
        "LEFT JOIN office tob ON tob.id = ot.to_office_id "
        "ORDER BY ot.transaction_date DESC, ot.id DESC");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["fromOfficeId"] = r["from_office_id"].isNull() ? "" : r["from_office_id"].as<std::string>();
        j["fromOfficeName"] = r["from_office_name"].isNull() ? "" : r["from_office_name"].as<std::string>();
        j["toOfficeId"] = r["to_office_id"].isNull() ? "" : r["to_office_id"].as<std::string>();
        j["toOfficeName"] = r["to_office_name"].isNull() ? "" : r["to_office_name"].as<std::string>();
        j["currencyCode"] = r["currency_code"].as<std::string>();
        j["transactionAmount"] = r["transaction_amount"].as<double>();
        j["transactionDate"] = r["transaction_date"].as<std::string>();
        j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
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
    auto currency = co_await txn->execSqlCoro(
        "SELECT decimal_places FROM organisation_currency WHERE code = $1", currencyCode);
    if (currency.size() == 0)
        throw ApiError(drogon::k400BadRequest, "Unknown currency code: " + currencyCode,
                       "error.msg.organization.currency.not.found");
    const int decimals = currency[0]["decimal_places"].as<int>();

    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO office_transaction (from_office_id, to_office_id, currency_code, "
        "  currency_digits, transaction_amount, transaction_date, description) "
        "VALUES ($1::uuid, $2::uuid, $3, $4, $5, $6::date, NULLIF($7, '')) "
        "RETURNING id::text AS id",
        fromOfficeId, toOfficeId, currencyCode, decimals, amount, transactionDate,
        asStringOr(body, "description"));
    const std::string id = rows[0]["id"].as<std::string>();
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
    auto rows =
        co_await txn->execSqlCoro("DELETE FROM office_transaction WHERE id::text = $1 RETURNING id",
                                  id);
    if (rows.size() == 0)
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
    auto offices = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name FROM office WHERE NOT is_deleted ORDER BY name");
    auto currencies = co_await txn->execSqlCoro(
        "SELECT code, name, display_symbol FROM organisation_currency WHERE is_enabled "
        "ORDER BY code");
    Json::Value officeOptions(Json::arrayValue);
    for (const auto &r : offices) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        officeOptions.append(j);
    }
    Json::Value currencyOptions(Json::arrayValue);
    for (const auto &r : currencies) {
        Json::Value j;
        j["code"] = r["code"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        j["displaySymbol"] = r["display_symbol"].isNull() ? "" : r["display_symbol"].as<std::string>();
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

drogon::Task<Json::Value> OrganizationService::staffToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT s.id::text AS id, s.office_id::text AS office_id, o.name AS office_name, "
        "  s.firstname, s.lastname, s.display_name, s.external_id, s.mobile_no, "
        "  s.is_loan_officer, s.is_active, s.joining_date::text AS joining_date "
        "FROM staff s JOIN office o ON o.id = s.office_id WHERE s.id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Staff member not found",
                       "error.msg.organization.staff.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["officeId"] = r["office_id"].as<std::string>();
    j["officeName"] = r["office_name"].as<std::string>();
    j["firstname"] = r["firstname"].as<std::string>();
    j["lastname"] = r["lastname"].as<std::string>();
    j["displayName"] = r["display_name"].as<std::string>();
    j["externalId"] = r["external_id"].isNull() ? "" : r["external_id"].as<std::string>();
    j["mobileNo"] = r["mobile_no"].isNull() ? "" : r["mobile_no"].as<std::string>();
    j["isLoanOfficer"] = r["is_loan_officer"].as<bool>();
    j["isActive"] = r["is_active"].as<bool>();
    j["joiningDate"] = r["joining_date"].isNull() ? "" : r["joining_date"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listStaff(const turbo::RequestContext &ctx,
                                                         const std::string &officeId,
                                                         bool loanOfficersOnly) {
    requirePermission(ctx, "READ_STAFF");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto toList = [](const drogon::orm::Result &rows) {
        Json::Value list(Json::arrayValue);
        for (const auto &r : rows) {
            Json::Value j;
            j["id"] = r["id"].as<std::string>();
            j["officeId"] = r["office_id"].as<std::string>();
            j["officeName"] = r["office_name"].as<std::string>();
            j["firstname"] = r["firstname"].as<std::string>();
            j["lastname"] = r["lastname"].as<std::string>();
            j["displayName"] = r["display_name"].as<std::string>();
            j["externalId"] = r["external_id"].isNull() ? "" : r["external_id"].as<std::string>();
            j["mobileNo"] = r["mobile_no"].isNull() ? "" : r["mobile_no"].as<std::string>();
            j["isLoanOfficer"] = r["is_loan_officer"].as<bool>();
            j["isActive"] = r["is_active"].as<bool>();
            list.append(j);
        }
        return list;
    };

    static const std::string kBase =
        "SELECT s.id::text AS id, s.office_id::text AS office_id, o.name AS office_name, "
        "  s.firstname, s.lastname, s.display_name, s.external_id, s.mobile_no, "
        "  s.is_loan_officer, s.is_active, s.joining_date::text AS joining_date "
        "FROM staff s JOIN office o ON o.id = s.office_id WHERE 1 = 1";

    if (!officeId.empty() && loanOfficersOnly) {
        auto rows = co_await txn->execSqlCoro(
            kBase + " AND s.office_id::text = $1 AND s.is_loan_officer ORDER BY s.lastname, s.firstname",
            officeId);
        co_return toList(rows);
    }
    if (!officeId.empty()) {
        auto rows = co_await txn->execSqlCoro(
            kBase + " AND s.office_id::text = $1 ORDER BY s.lastname, s.firstname", officeId);
        co_return toList(rows);
    }
    if (loanOfficersOnly) {
        auto rows = co_await txn->execSqlCoro(
            kBase + " AND s.is_loan_officer ORDER BY s.lastname, s.firstname");
        co_return toList(rows);
    }
    auto rows = co_await txn->execSqlCoro(kBase + " ORDER BY s.lastname, s.firstname");
    co_return toList(rows);
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
    auto office = co_await txn->execSqlCoro(
        "SELECT 1 FROM office WHERE id::text = $1 AND NOT is_deleted", officeId);
    if (office.size() == 0)
        throw ApiError(drogon::k400BadRequest, "Unknown officeId: " + officeId,
                       "error.msg.organization.office.not.found");

    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO staff (office_id, firstname, lastname, external_id, mobile_no, "
            "  is_loan_officer, joining_date) "
            "VALUES ($1::uuid, $2, $3, NULLIF($4, ''), NULLIF($5, ''), $6, NULLIF($7, '')::date) "
            "RETURNING id::text AS id",
            officeId, firstname, lastname, asStringOr(body, "externalId"),
            asStringOr(body, "mobileNo"), asBoolOr(body, "isLoanOfficer", false),
            asStringOr(body, "joiningDate"));
        const std::string id = rows[0]["id"].as<std::string>();
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
    auto current = co_await txn->execSqlCoro(
        "SELECT is_loan_officer, is_active FROM staff WHERE id::text = $1", id);
    if (current.size() == 0)
        throw ApiError(drogon::k404NotFound, "Staff member not found",
                       "error.msg.organization.staff.not.found");
    const bool isLoanOfficer = body.isMember("isLoanOfficer")
                                   ? asBoolOr(body, "isLoanOfficer", false)
                                   : current[0]["is_loan_officer"].as<bool>();
    const bool isActive = body.isMember("isActive") ? asBoolOr(body, "isActive", true)
                                                    : current[0]["is_active"].as<bool>();
    auto rows = co_await txn->execSqlCoro(
        "UPDATE staff SET firstname = COALESCE(NULLIF($2, ''), firstname), "
        "  lastname = COALESCE(NULLIF($3, ''), lastname), "
        "  mobile_no = COALESCE(NULLIF($4, ''), mobile_no), "
        "  is_loan_officer = $5, is_active = $6, modified_at = now() "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "firstname"), asStringOr(body, "lastname"),
        asStringOr(body, "mobileNo"), isLoanOfficer, isActive);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Staff member not found",
                       "error.msg.organization.staff.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "staff", id, "staff.updated", body);
    co_return co_await staffToJson(txn, id);
}

// ---------------------------------------------------------------------------
// holidays
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::holidayToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, from_date::text AS from_date, to_date::text AS to_date, "
        "  repayment_scheduled_to::text AS repayment_scheduled_to, description, status, "
        "  applies_to_all_offices "
        "FROM holiday WHERE id::text = $1 AND status <> 'DELETED'",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Holiday not found",
                       "error.msg.organization.holiday.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["name"] = r["name"].as<std::string>();
    j["fromDate"] = r["from_date"].as<std::string>();
    j["toDate"] = r["to_date"].as<std::string>();
    j["repaymentsRescheduledTo"] =
        r["repayment_scheduled_to"].isNull() ? "" : r["repayment_scheduled_to"].as<std::string>();
    j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
    j["status"] = r["status"].as<std::string>();
    j["appliesToAllOffices"] = r["applies_to_all_offices"].as<bool>();
    if (!r["applies_to_all_offices"].as<bool>()) {
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
    auto toList = [](const drogon::orm::Result &rows) {
        Json::Value list(Json::arrayValue);
        for (const auto &r : rows) {
            Json::Value j;
            j["id"] = r["id"].as<std::string>();
            j["name"] = r["name"].as<std::string>();
            j["fromDate"] = r["from_date"].as<std::string>();
            j["toDate"] = r["to_date"].as<std::string>();
            j["status"] = r["status"].as<std::string>();
            list.append(j);
        }
        return list;
    };
    if (officeId.empty()) {
        auto rows = co_await txn->execSqlCoro(
            "SELECT id::text AS id, name, from_date::text AS from_date, to_date::text AS to_date, "
            "  status FROM holiday WHERE status <> 'DELETED' ORDER BY from_date DESC");
        co_return toList(rows);
    }
    auto rows = co_await txn->execSqlCoro(
        "SELECT h.id::text AS id, h.name, h.from_date::text AS from_date, "
        "  h.to_date::text AS to_date, h.status FROM holiday h "
        "WHERE h.status <> 'DELETED' AND "
        "  (h.applies_to_all_offices OR EXISTS (SELECT 1 FROM holiday_office ho "
        "     WHERE ho.holiday_id = h.id AND ho.office_id::text = $1)) "
        "ORDER BY h.from_date DESC",
        officeId);
    co_return toList(rows);
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
    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO holiday (name, from_date, to_date, repayment_scheduled_to, description, "
        "  applies_to_all_offices) "
        "VALUES ($1, $2::date, $3::date, NULLIF($4, '')::date, NULLIF($5, ''), $6) "
        "RETURNING id::text AS id",
        name, fromDate, toDate, asStringOr(body, "repaymentsRescheduledTo"),
        asStringOr(body, "description"), appliesToAll);
    const std::string id = rows[0]["id"].as<std::string>();
    if (!appliesToAll) {
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
    auto rows = co_await txn->execSqlCoro(
        "UPDATE holiday SET name = COALESCE(NULLIF($2, ''), name), "
        "  from_date = COALESCE(NULLIF($3, '')::date, from_date), "
        "  to_date = COALESCE(NULLIF($4, '')::date, to_date), "
        "  description = COALESCE(NULLIF($5, ''), description), modified_at = now() "
        "WHERE id::text = $1 AND status = 'PENDING_FOR_ACTIVATION' RETURNING id::text AS id",
        id, asStringOr(body, "name"), asStringOr(body, "fromDate"), asStringOr(body, "toDate"),
        asStringOr(body, "description"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound,
                       "Holiday not found or is no longer pending activation",
                       "error.msg.organization.holiday.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "holiday", id, "holiday.updated", body);
    co_return co_await holidayToJson(txn, id);
}

drogon::Task<void> OrganizationService::deleteHoliday(const turbo::RequestContext &ctx,
                                                      const std::string &id) {
    requirePermission(ctx, "DELETE_HOLIDAY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE holiday SET status = 'DELETED', modified_at = now() WHERE id::text = $1 "
        "AND status <> 'DELETED' RETURNING id::text AS id",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Holiday not found",
                       "error.msg.organization.holiday.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "holiday", id, "holiday.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> OrganizationService::activateHoliday(const turbo::RequestContext &ctx,
                                                               const std::string &id) {
    requirePermission(ctx, "ACTIVATE_HOLIDAY");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE holiday SET status = 'ACTIVE', modified_at = now() WHERE id::text = $1 "
        "AND status = 'PENDING_FOR_ACTIVATION' RETURNING id::text AS id",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound,
                       "Holiday not found or is not pending activation",
                       "error.msg.organization.holiday.not.found");
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
    auto rows = co_await txn->execSqlCoro(
        "SELECT working_days, repayment_rescheduling_type, extend_term_for_daily_repayments "
        "FROM working_days WHERE id = 1");
    Json::Value out;
    if (rows.size() == 0) co_return out;
    const auto &r = rows[0];
    Json::Value days(Json::arrayValue);
    std::string raw = r["working_days"].as<std::string>();
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
    out["repaymentReschedulingType"] = r["repayment_rescheduling_type"].as<std::string>();
    out["extendTermForDailyRepayments"] = r["extend_term_for_daily_repayments"].as<bool>();
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
    auto current = co_await txn->execSqlCoro(
        "SELECT extend_term_for_daily_repayments FROM working_days WHERE id = 1");
    const bool extendTerm = body.isMember("extendTermForDailyRepayments")
                                ? asBoolOr(body, "extendTermForDailyRepayments", false)
                                : (current.size() > 0
                                       ? current[0]["extend_term_for_daily_repayments"].as<bool>()
                                       : false);
    co_await txn->execSqlCoro(
        "UPDATE working_days SET working_days = COALESCE(NULLIF($1, ''), working_days), "
        "  repayment_rescheduling_type = "
        "    COALESCE(NULLIF($2, ''), repayment_rescheduling_type), "
        "  extend_term_for_daily_repayments = $3, "
        "  modified_at = now() WHERE id = 1",
        days, asStringOr(body, "repaymentReschedulingType"), extendTerm);
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
    auto rows = co_await txn->execSqlCoro(
        "SELECT code, name, decimal_places, display_symbol, is_enabled "
        "FROM organisation_currency ORDER BY code");
    Json::Value selected(Json::arrayValue);
    Json::Value all(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["code"] = r["code"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        j["decimalPlaces"] = r["decimal_places"].as<int>();
        j["displaySymbol"] = r["display_symbol"].isNull() ? "" : r["display_symbol"].as<std::string>();
        all.append(j);
        if (r["is_enabled"].as<bool>()) selected.append(j);
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
    co_await txn->execSqlCoro("UPDATE organisation_currency SET is_enabled = false");
    for (const auto &code : body["currencies"]) {
        auto ok = co_await txn->execSqlCoro(
            "UPDATE organisation_currency SET is_enabled = true WHERE code = $1 RETURNING code",
            code.asString());
        if (ok.size() == 0)
            throw ApiError(drogon::k400BadRequest, "Unknown currency code: " + code.asString(),
                           "error.msg.organization.currency.not.found");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "currency", "org", "currency.updated", body);
    co_return co_await getCurrencies(ctx);
}

// ---------------------------------------------------------------------------
// funds
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::fundToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, external_id FROM fund WHERE id::text = $1", id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Fund not found", "error.msg.organization.fund.not.found");
    Json::Value j;
    j["id"] = rows[0]["id"].as<std::string>();
    j["name"] = rows[0]["name"].as<std::string>();
    j["externalId"] = rows[0]["external_id"].isNull() ? "" : rows[0]["external_id"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listFunds(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_FUND");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro("SELECT id::text AS id, name, external_id FROM fund ORDER BY name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        j["externalId"] = r["external_id"].isNull() ? "" : r["external_id"].as<std::string>();
        list.append(j);
    }
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
    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO fund (name, external_id) VALUES ($1, NULLIF($2, '')) "
            "RETURNING id::text AS id",
            name, asStringOr(body, "externalId"));
        const std::string id = rows[0]["id"].as<std::string>();
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
    auto rows = co_await txn->execSqlCoro(
        "UPDATE fund SET name = COALESCE(NULLIF($2, ''), name), "
        "  external_id = COALESCE(NULLIF($3, ''), external_id), modified_at = now() "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "name"), asStringOr(body, "externalId"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Fund not found", "error.msg.organization.fund.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "fund", id, "fund.updated", body);
    co_return co_await fundToJson(txn, id);
}

// ---------------------------------------------------------------------------
// payment types
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::paymentTypeToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, value, description, is_cash_payment, order_position, "
        "  is_system_defined FROM payment_type WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Payment type not found",
                       "error.msg.organization.paymenttype.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["name"] = r["value"].isNull() ? "" : r["value"].as<std::string>();
    j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
    j["isCashPayment"] = r["is_cash_payment"].as<bool>();
    j["position"] = r["order_position"].as<int>();
    j["isSystemDefined"] = r["is_system_defined"].as<bool>();
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listPaymentTypes(const turbo::RequestContext &ctx,
                                                                bool onlyActive) {
    requirePermission(ctx, "READ_PAYMENTTYPE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, value, description, is_cash_payment, order_position, "
        "  is_system_defined FROM payment_type ORDER BY order_position, value");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["value"].isNull() ? "" : r["value"].as<std::string>();
        j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
        j["isCashPayment"] = r["is_cash_payment"].as<bool>();
        j["position"] = r["order_position"].as<int>();
        j["isSystemDefined"] = r["is_system_defined"].as<bool>();
        list.append(j);
    }
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
    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO payment_type (value, description, is_cash_payment, order_position) "
            "VALUES ($1, NULLIF($2, ''), $3, $4) RETURNING id::text AS id",
            name, asStringOr(body, "description"), asBoolOr(body, "isCashPayment", false),
            asIntOr(body, "position", 0));
        const std::string id = rows[0]["id"].as<std::string>();
        co_await turbo::outbox::writeEvent(txn, ctx, "paymenttype", id, "paymenttype.created", body);
        co_return co_await paymentTypeToJson(txn, id);
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
    auto current =
        co_await txn->execSqlCoro("SELECT is_cash_payment FROM payment_type WHERE id::text = $1", id);
    if (current.size() == 0)
        throw ApiError(drogon::k404NotFound, "Payment type not found",
                       "error.msg.organization.paymenttype.not.found");
    const bool isCashPayment = body.isMember("isCashPayment")
                                   ? asBoolOr(body, "isCashPayment", false)
                                   : current[0]["is_cash_payment"].as<bool>();
    auto rows = co_await txn->execSqlCoro(
        "UPDATE payment_type SET value = COALESCE(NULLIF($2, ''), value), "
        "  description = COALESCE(NULLIF($3, ''), description), "
        "  is_cash_payment = $4 "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "name"), asStringOr(body, "description"), isCashPayment);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Payment type not found",
                       "error.msg.organization.paymenttype.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "paymenttype", id, "paymenttype.updated", body);
    co_return co_await paymentTypeToJson(txn, id);
}

drogon::Task<void> OrganizationService::deletePaymentType(const turbo::RequestContext &ctx,
                                                          const std::string &id) {
    requirePermission(ctx, "DELETE_PAYMENTTYPE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto row = co_await txn->execSqlCoro(
        "SELECT is_system_defined FROM payment_type WHERE id::text = $1", id);
    if (row.size() == 0)
        throw ApiError(drogon::k404NotFound, "Payment type not found",
                       "error.msg.organization.paymenttype.not.found");
    if (row[0]["is_system_defined"].as<bool>())
        throw ApiError(drogon::k403Forbidden, "System-defined payment types cannot be deleted",
                       "error.msg.organization.paymenttype.protected");
    co_await txn->execSqlCoro("DELETE FROM payment_type WHERE id::text = $1", id);
    co_await turbo::outbox::writeEvent(txn, ctx, "paymenttype", id, "paymenttype.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// entity-to-entity mapping
// ---------------------------------------------------------------------------

namespace {
Json::Value entityMappingRowToJson(const drogon::orm::Row &r) {
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["relationId"] = r["relation_id"].as<std::string>();
    j["codeFrom"] = r["code_from"].as<std::string>();
    j["codeTo"] = r["code_to"].as<std::string>();
    j["fromId"] = r["from_id"].as<std::string>();
    j["toId"] = r["to_id"].as<std::string>();
    return j;
}
}  // namespace

drogon::Task<Json::Value> OrganizationService::listEntityMappings(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT em.id::text AS id, em.relation_id::text AS relation_id, er.code_from, er.code_to, "
        "  em.from_id, em.to_id FROM entity_mapping em "
        "JOIN entity_relation er ON er.id = em.relation_id ORDER BY em.created_at DESC");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(entityMappingRowToJson(r));
    co_return list;
}

drogon::Task<Json::Value> OrganizationService::getEntityMapping(const turbo::RequestContext &ctx,
                                                                const std::string &mapId) {
    requirePermission(ctx, "READ_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT em.id::text AS id, em.relation_id::text AS relation_id, er.code_from, er.code_to, "
        "  em.from_id, em.to_id FROM entity_mapping em "
        "JOIN entity_relation er ON er.id = em.relation_id WHERE em.id::text = $1",
        mapId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Entity mapping not found",
                       "error.msg.organization.entitymapping.not.found");
    co_return entityMappingRowToJson(rows[0]);
}

drogon::Task<Json::Value> OrganizationService::queryEntityMappings(
    const turbo::RequestContext &ctx, const std::string &relId, const std::string &fromId,
    const std::string &toId) {
    requirePermission(ctx, "READ_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT em.id::text AS id, em.relation_id::text AS relation_id, er.code_from, er.code_to, "
        "  em.from_id, em.to_id FROM entity_mapping em "
        "JOIN entity_relation er ON er.id = em.relation_id "
        "WHERE em.relation_id::text = $1 AND em.from_id = $2 AND em.to_id = $3",
        relId, fromId, toId);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(entityMappingRowToJson(r));
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
    auto relation = co_await txn->execSqlCoro(
        "SELECT id FROM entity_relation WHERE id::text = $1", relId);
    if (relation.size() == 0)
        throw ApiError(drogon::k400BadRequest, "Unknown relation id: " + relId,
                       "error.msg.organization.entityrelation.not.found");
    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO entity_mapping (relation_id, from_id, to_id) VALUES ($1::uuid, $2, $3) "
        "RETURNING id::text AS id",
        relId, fromId, toId);
    const std::string id = rows[0]["id"].as<std::string>();
    co_await turbo::outbox::writeEvent(txn, ctx, "entitymapping", id, "entitymapping.created", body);
    co_return co_await getEntityMapping(ctx, id);
}

drogon::Task<Json::Value> OrganizationService::updateEntityMapping(
    const turbo::RequestContext &ctx, const std::string &mapId, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE entity_mapping SET to_id = COALESCE(NULLIF($2, ''), to_id) "
        "WHERE id::text = $1 RETURNING id::text AS id",
        mapId, asStringOr(body, "toId"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Entity mapping not found",
                       "error.msg.organization.entitymapping.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "entitymapping", mapId, "entitymapping.updated",
                                       body);
    co_return co_await getEntityMapping(ctx, mapId);
}

drogon::Task<void> OrganizationService::deleteEntityMapping(const turbo::RequestContext &ctx,
                                                            const std::string &mapId) {
    requirePermission(ctx, "DELETE_ENTITYTOENTITYMAPPING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "DELETE FROM entity_mapping WHERE id::text = $1 RETURNING id", mapId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Entity mapping not found",
                       "error.msg.organization.entitymapping.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "entitymapping", mapId, "entitymapping.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// taxes
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> OrganizationService::taxComponentToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, percentage, start_date::text AS start_date, "
        "  debit_account_id, credit_account_id FROM tax_component WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Tax component not found",
                       "error.msg.organization.taxcomponent.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["name"] = r["name"].as<std::string>();
    j["percentage"] = r["percentage"].as<double>();
    j["startDate"] = r["start_date"].as<std::string>();
    j["debitAccountId"] = r["debit_account_id"].isNull() ? "" : r["debit_account_id"].as<std::string>();
    j["creditAccountId"] =
        r["credit_account_id"].isNull() ? "" : r["credit_account_id"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listTaxComponents(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_TAXCOMPONENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, percentage, start_date::text AS start_date "
        "FROM tax_component ORDER BY name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        j["percentage"] = r["percentage"].as<double>();
        j["startDate"] = r["start_date"].as<std::string>();
        list.append(j);
    }
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
    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO tax_component (name, percentage, start_date, debit_account_id, "
            "  credit_account_id) VALUES ($1, $2, $3::date, NULLIF($4, ''), NULLIF($5, '')) "
            "RETURNING id::text AS id",
            name, percentage, startDate, asStringOr(body, "debitAccountId"),
            asStringOr(body, "creditAccountId"));
        const std::string id = rows[0]["id"].as<std::string>();
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
    auto current =
        co_await txn->execSqlCoro("SELECT percentage FROM tax_component WHERE id::text = $1", id);
    if (current.size() == 0)
        throw ApiError(drogon::k404NotFound, "Tax component not found",
                       "error.msg.organization.taxcomponent.not.found");
    const double percentage = body.isMember("percentage")
                                   ? asDoubleOr(body, "percentage", 0)
                                   : current[0]["percentage"].as<double>();
    auto rows = co_await txn->execSqlCoro(
        "UPDATE tax_component SET name = COALESCE(NULLIF($2, ''), name), "
        "  percentage = $3, modified_at = now() "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "name"), percentage);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Tax component not found",
                       "error.msg.organization.taxcomponent.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "taxcomponent", id, "taxcomponent.updated", body);
    co_return co_await taxComponentToJson(txn, id);
}

drogon::Task<Json::Value> OrganizationService::taxGroupToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name FROM tax_group WHERE id::text = $1", id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Tax group not found",
                       "error.msg.organization.taxgroup.not.found");
    Json::Value j;
    j["id"] = rows[0]["id"].as<std::string>();
    j["name"] = rows[0]["name"].as<std::string>();
    auto components = co_await txn->execSqlCoro(
        "SELECT tc.id::text AS id, tc.name, tc.percentage, tgm.start_date::text AS start_date "
        "FROM tax_group_mapping tgm JOIN tax_component tc ON tc.id = tgm.tax_component_id "
        "WHERE tgm.tax_group_id::text = $1 ORDER BY tgm.start_date",
        id);
    Json::Value comps(Json::arrayValue);
    for (const auto &c : components) {
        Json::Value cj;
        cj["id"] = c["id"].as<std::string>();
        cj["name"] = c["name"].as<std::string>();
        cj["percentage"] = c["percentage"].as<double>();
        cj["startDate"] = c["start_date"].as<std::string>();
        comps.append(cj);
    }
    j["taxComponents"] = comps;
    co_return j;
}

drogon::Task<Json::Value> OrganizationService::listTaxGroups(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_TAXGROUP");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro("SELECT id::text AS id, name FROM tax_group ORDER BY name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
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
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO tax_group (name) VALUES ($1) RETURNING id::text AS id", name);
        const std::string id = rows[0]["id"].as<std::string>();
        if (body.isMember("taxComponents") && body["taxComponents"].isArray()) {
            for (const auto &tc : body["taxComponents"]) {
                const std::string componentId = asStringOr(tc, "taxComponentId");
                const std::string startDate = asStringOr(tc, "startDate");
                if (componentId.empty() || startDate.empty()) continue;
                co_await txn->execSqlCoro(
                    "INSERT INTO tax_group_mapping (tax_group_id, tax_component_id, start_date) "
                    "VALUES ($1::uuid, $2::uuid, $3::date)",
                    id, componentId, startDate);
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
    auto rows = co_await txn->execSqlCoro(
        "UPDATE tax_group SET name = COALESCE(NULLIF($2, ''), name) "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "name"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Tax group not found",
                       "error.msg.organization.taxgroup.not.found");
    if (body.isMember("taxComponents") && body["taxComponents"].isArray()) {
        co_await txn->execSqlCoro("DELETE FROM tax_group_mapping WHERE tax_group_id::text = $1", id);
        for (const auto &tc : body["taxComponents"]) {
            const std::string componentId = asStringOr(tc, "taxComponentId");
            const std::string startDate = asStringOr(tc, "startDate");
            if (componentId.empty() || startDate.empty()) continue;
            co_await txn->execSqlCoro(
                "INSERT INTO tax_group_mapping (tax_group_id, tax_component_id, start_date) "
                "VALUES ($1::uuid, $2::uuid, $3::date)",
                id, componentId, startDate);
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
