#include "CustomerService.h"

#include <drogon/orm/CoroMapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>

#include "turbo/Ids.h"
#include "turbo/Money.h"
#include "turbo/Outbox.h"
#include "turbo/Pagination.h"
#include "turbo/TenantDb.h"

#include "models/Client.h"
#include "models/ClientAddress.h"
#include "models/ClientCharge.h"
#include "models/ClientChargePaidBy.h"
#include "models/ClientCollateralManagement.h"
#include "models/ClientFamilyMember.h"
#include "models/ClientIdentifier.h"
#include "models/ClientNonPerson.h"
#include "models/ClientTransaction.h"
#include "models/ClientTransferDetails.h"
#include "models/CollateralManagement.h"

using drogon::orm::CompareOperator;
using drogon::orm::Criteria;
using drogon::orm::DrogonDbException;
using drogon::orm::SortOrder;
using drogon::orm::UnexpectedRows;
using trantor::Date;

namespace turbo_ledger_customer {

namespace m = drogon_model::TlCustomerDb;
template <typename T>
using Mapper = drogon::orm::CoroMapper<T>;

// ---------------------------------------------------------------------------
// NOTE on ORM coverage: every resource in this file goes through
// CoroMapper<Model>. `ClientCharge`, `ClientChargePaidBy`, `ClientIdentifier`,
// `ClientNonPerson`, `ClientTransaction` and `ClientTransferDetails` are
// untouched, genuine drogon_ctl output (generated against the V001 baseline,
// which already covers every column these resources need). `Client`,
// `ClientAddress` and `ClientCollateralManagement` are genuine drogon_ctl
// output regenerated to add the Phase 4 columns (kyc_status/risk_rating/
// fatca_flag/crs_flag on client; audit columns on the other two — see each
// model's own header comment). `CollateralManagement` and
// `ClientFamilyMember` are hand-authored from scratch (new V003 tables) in
// the same drogon_ctl-shape-matching style established in Phase 2.
//
// There is no raw SQL anywhere in this file.
//
// Cross-service ids this phase deliberately trusts as caller-supplied
// (office_id, staff_id, charge_id, document_type_id, *_cv_id, currency
// codes, image_id, payment_detail_id): Organization/SystemConfig/DAM own
// those catalogs in their own databases and there is no inter-service RPC
// client in this codebase yet (each service owns a dedicated Postgres
// database — see config.json — so no cross-database join is even possible).
// Template endpoints that would normally return those catalogs as dropdown
// options are documented stubs for the same reason.
// ---------------------------------------------------------------------------

namespace {

constexpr const char *kZeroUuid = "00000000-0000-0000-0000-000000000000";

// client.status — local enum (Fineract's exact numeric codes were not
// reliably known; the V001 baseline already fixed `status DEFAULT 300 NOT
// NULL`, which becomes kStatusPending below).
constexpr int kStatusPending = 300;
constexpr int kStatusActive = 100;
constexpr int kStatusRejected = 400;
constexpr int kStatusClosed = 600;
constexpr int kStatusWithdrawn = 700;

// client.sub_status — used only to track an in-flight office transfer while
// status remains ACTIVE throughout, matching Fineract's design.
constexpr int kSubStatusTransferInProgress = 1;

// client.kyc_status
constexpr int kKycPending = 100;
constexpr int kKycVerified = 200;
constexpr int kKycRejected = 300;

// client.risk_rating
constexpr int kRiskLow = 100;

// client_transaction.transaction_type — local enum, this service only ever
// originates charge-payment transactions (no savings/loan accounts exist
// yet to originate other transaction types).
constexpr int kTxnTypePayCharge = 1;
constexpr int kTxnTypeWaiveCharge = 2;

// client_transfer_details.transfer_type — repurposed as the outcome of the
// transfer request this row represents (Fineract itself uses this column
// for a similar categorical purpose). Exactly one row per client may sit at
// kTransferProposed at a time (enforced by client.sub_status).
constexpr int kTransferProposed = 1;
constexpr int kTransferAccepted = 2;
constexpr int kTransferRejected = 3;
constexpr int kTransferWithdrawn = 4;

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

Json::Value moneyJson(const std::string &dbNumeric) {
    auto parsed = turbo::Money::parse(dbNumeric);
    return parsed ? Json::Value(parsed->toString(false)) : Json::Value(dbNumeric);
}

std::string userIdOr(const turbo::RequestContext &ctx) {
    return ctx.userId.empty() ? kZeroUuid : ctx.userId;
}

std::string clientStatusLabel(int status) {
    switch (status) {
        case kStatusPending: return "Pending";
        case kStatusActive: return "Active";
        case kStatusRejected: return "Rejected";
        case kStatusClosed: return "Closed";
        case kStatusWithdrawn: return "Withdrawn";
        default: return "Unknown";
    }
}

std::string kycStatusLabel(int status) {
    switch (status) {
        case kKycPending: return "Pending";
        case kKycVerified: return "Verified";
        case kKycRejected: return "Rejected";
        default: return "Unknown";
    }
}

Json::Value clientJson(const m::Client &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["accountNo"] = row.getValueOfAccountNo();
    if (row.getExternalId()) j["externalId"] = row.getValueOfExternalId();
    j["status"] = row.getValueOfStatus();
    j["statusLabel"] = clientStatusLabel(row.getValueOfStatus());
    j["active"] = row.getValueOfStatus() == kStatusActive;
    if (row.getSubStatus()) j["subStatus"] = row.getValueOfSubStatus();
    if (row.getOfficeId()) j["officeId"] = row.getValueOfOfficeId();
    if (row.getTransferToOfficeId()) j["transferToOfficeId"] = row.getValueOfTransferToOfficeId();
    if (row.getProposedTransferDate()) j["proposedTransferDate"] = dateStr(row.getValueOfProposedTransferDate());
    if (row.getStaffId()) j["staffId"] = row.getValueOfStaffId();
    if (row.getFirstname()) j["firstname"] = row.getValueOfFirstname();
    if (row.getMiddlename()) j["middlename"] = row.getValueOfMiddlename();
    if (row.getLastname()) j["lastname"] = row.getValueOfLastname();
    if (row.getFullname()) j["fullname"] = row.getValueOfFullname();
    if (row.getDisplayName()) j["displayName"] = row.getValueOfDisplayName();
    if (row.getMobileNo()) j["mobileNo"] = row.getValueOfMobileNo();
    if (row.getEmailAddress()) j["emailAddress"] = row.getValueOfEmailAddress();
    j["isStaff"] = row.getValueOfIsStaff();
    if (row.getGenderCvId()) j["genderCvId"] = row.getValueOfGenderCvId();
    if (row.getDateOfBirth()) j["dateOfBirth"] = dateStr(row.getValueOfDateOfBirth());
    if (row.getImageId()) j["imageId"] = row.getValueOfImageId();
    if (row.getClientTypeCvId()) j["clientTypeCvId"] = row.getValueOfClientTypeCvId();
    if (row.getClientClassificationCvId())
        j["clientClassificationCvId"] = row.getValueOfClientClassificationCvId();
    if (row.getLegalStructure()) j["legalFormId"] = row.getValueOfLegalStructure();
    if (row.getActivationDate()) j["activationDate"] = dateStr(row.getValueOfActivationDate());
    if (row.getOfficeJoiningDate()) j["officeJoiningDate"] = dateStr(row.getValueOfOfficeJoiningDate());
    if (row.getSubmittedonDate()) j["submittedOnDate"] = dateStr(row.getValueOfSubmittedonDate());
    if (row.getClosedonDate()) j["closedOnDate"] = dateStr(row.getValueOfClosedonDate());
    if (row.getClosureReasonCvId()) j["closureReasonCvId"] = row.getValueOfClosureReasonCvId();
    if (row.getRejectReasonCvId()) j["rejectReasonCvId"] = row.getValueOfRejectReasonCvId();
    if (row.getRejectedonDate()) j["rejectedOnDate"] = dateStr(row.getValueOfRejectedonDate());
    if (row.getWithdrawReasonCvId()) j["withdrawReasonCvId"] = row.getValueOfWithdrawReasonCvId();
    if (row.getWithdrawnOnDate()) j["withdrawnOnDate"] = dateStr(row.getValueOfWithdrawnOnDate());
    if (row.getReactivatedOnDate()) j["reactivatedOnDate"] = dateStr(row.getValueOfReactivatedOnDate());
    if (row.getReopenedOnDate()) j["reopenedOnDate"] = dateStr(row.getValueOfReopenedOnDate());
    if (row.getDefaultSavingsProduct()) j["defaultSavingsProductId"] = row.getValueOfDefaultSavingsProduct();
    if (row.getDefaultSavingsAccount()) j["defaultSavingsAccountId"] = row.getValueOfDefaultSavingsAccount();
    j["kycStatus"] = row.getValueOfKycStatus();
    j["kycStatusLabel"] = kycStatusLabel(row.getValueOfKycStatus());
    j["riskRating"] = row.getValueOfRiskRating();
    j["fatcaFlag"] = row.getValueOfFatcaFlag();
    j["crsFlag"] = row.getValueOfCrsFlag();
    if (row.getCreatedBy()) j["createdBy"] = row.getValueOfCreatedBy();
    if (row.getCreatedAt()) j["createdAt"] = dateStr(row.getValueOfCreatedAt());
    if (row.getModifiedBy()) j["modifiedBy"] = row.getValueOfModifiedBy();
    if (row.getModifiedAt()) j["modifiedAt"] = dateStr(row.getValueOfModifiedAt());
    return j;
}

Json::Value clientAddressJson(const m::ClientAddress &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["clientId"] = row.getValueOfClientId();
    if (row.getStreet()) j["street"] = row.getValueOfStreet();
    if (row.getAddressLine1()) j["addressLine1"] = row.getValueOfAddressLine1();
    if (row.getAddressLine2()) j["addressLine2"] = row.getValueOfAddressLine2();
    if (row.getCity()) j["city"] = row.getValueOfCity();
    if (row.getStateOrProvince()) j["stateOrProvince"] = row.getValueOfStateOrProvince();
    if (row.getCountry()) j["country"] = row.getValueOfCountry();
    if (row.getCountryCode()) j["countryCode"] = row.getValueOfCountryCode();
    if (row.getAddressTypeId()) j["addressTypeId"] = row.getValueOfAddressTypeId();
    j["isActive"] = row.getValueOfIsActive();
    if (row.getCreatedBy()) j["createdBy"] = row.getValueOfCreatedBy();
    if (row.getCreatedAt()) j["createdAt"] = dateStr(row.getValueOfCreatedAt());
    if (row.getUpdatedBy()) j["updatedBy"] = row.getValueOfUpdatedBy();
    if (row.getUpdatedAt()) j["updatedAt"] = dateStr(row.getValueOfUpdatedAt());
    return j;
}

Json::Value clientIdentifierJson(const m::ClientIdentifier &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["clientId"] = row.getValueOfClientId();
    j["documentTypeId"] = row.getValueOfDocumentTypeId();
    j["documentKey"] = row.getValueOfDocumentKey();
    j["status"] = row.getValueOfStatus();
    if (row.getActive()) j["active"] = row.getValueOfActive();
    if (row.getDescription()) j["description"] = row.getValueOfDescription();
    j["createdBy"] = row.getValueOfCreatedBy();
    j["lastModifiedBy"] = row.getValueOfLastModifiedBy();
    if (row.getCreatedDate()) j["createdDate"] = dateStr(row.getValueOfCreatedDate());
    if (row.getLastmodifiedDate()) j["lastModifiedDate"] = dateStr(row.getValueOfLastmodifiedDate());
    return j;
}

Json::Value familyMemberJson(const m::ClientFamilyMember &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["clientId"] = row.getValueOfClientId();
    j["firstname"] = row.getValueOfFirstname();
    if (row.getMiddlename()) j["middlename"] = row.getValueOfMiddlename();
    j["lastname"] = row.getValueOfLastname();
    if (row.getQualification()) j["qualification"] = row.getValueOfQualification();
    if (row.getMobileNumber()) j["mobileNumber"] = row.getValueOfMobileNumber();
    if (row.getAge()) j["age"] = row.getValueOfAge();
    j["isDependent"] = row.getValueOfIsDependent();
    if (row.getRelationshipCvId()) j["relationshipCvId"] = row.getValueOfRelationshipCvId();
    if (row.getMaritalStatusCvId()) j["maritalStatusCvId"] = row.getValueOfMaritalStatusCvId();
    if (row.getGenderCvId()) j["genderCvId"] = row.getValueOfGenderCvId();
    if (row.getDateOfBirth()) j["dateOfBirth"] = dateStr(row.getValueOfDateOfBirth());
    if (row.getProfessionCvId()) j["professionCvId"] = row.getValueOfProfessionCvId();
    return j;
}

Json::Value collateralProductJson(const m::CollateralManagement &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["name"] = row.getValueOfName();
    if (row.getQuality()) j["quality"] = row.getValueOfQuality();
    if (row.getBasePrice()) j["basePrice"] = moneyJson(row.getValueOfBasePrice());
    if (row.getCurrencyCode()) j["currencyCode"] = row.getValueOfCurrencyCode();
    if (row.getPctToBase()) j["pctToBase"] = moneyJson(row.getValueOfPctToBase());
    if (row.getUnitType()) j["unitType"] = row.getValueOfUnitType();
    return j;
}

Json::Value clientCollateralJson(const m::ClientCollateralManagement &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["clientId"] = row.getValueOfClientId();
    j["collateralId"] = row.getValueOfCollateralId();
    j["quantity"] = moneyJson(row.getValueOfQuantity());
    return j;
}

Json::Value clientChargeJson(const m::ClientCharge &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["clientId"] = row.getValueOfClientId();
    j["chargeId"] = row.getValueOfChargeId();
    j["isPenalty"] = row.getValueOfIsPenalty();
    j["chargeTimeEnum"] = row.getValueOfChargeTimeEnum();
    if (row.getChargeDueDate()) j["dueDate"] = dateStr(row.getValueOfChargeDueDate());
    j["chargeCalculationEnum"] = row.getValueOfChargeCalculationEnum();
    j["amount"] = moneyJson(row.getValueOfAmount());
    if (row.getAmountPaidDerived()) j["amountPaid"] = moneyJson(row.getValueOfAmountPaidDerived());
    if (row.getAmountWaivedDerived()) j["amountWaived"] = moneyJson(row.getValueOfAmountWaivedDerived());
    j["amountOutstanding"] = moneyJson(row.getValueOfAmountOutstandingDerived());
    if (row.getIsPaidDerived()) j["isPaid"] = row.getValueOfIsPaidDerived();
    if (row.getWaived()) j["waived"] = row.getValueOfWaived();
    if (row.getIsActive()) j["isActive"] = row.getValueOfIsActive();
    return j;
}

Json::Value clientTransactionJson(const m::ClientTransaction &row) {
    Json::Value j;
    j["id"] = row.getValueOfId();
    j["clientId"] = row.getValueOfClientId();
    j["officeId"] = row.getValueOfOfficeId();
    j["currencyCode"] = row.getValueOfCurrencyCode();
    j["isReversed"] = row.getValueOfIsReversed();
    if (row.getExternalId()) j["externalId"] = row.getValueOfExternalId();
    j["transactionDate"] = dateStr(row.getValueOfTransactionDate());
    j["transactionType"] = row.getValueOfTransactionType();
    j["amount"] = moneyJson(row.getValueOfAmount());
    j["submittedOnDate"] = dateStr(row.getValueOfSubmittedOnDate());
    return j;
}

}  // namespace

drogon::orm::DbClientPtr CustomerService::db() { return drogon::app().getDbClient(); }

void CustomerService::requirePermission(const turbo::RequestContext &ctx, const std::string &code) {
    if (!ctx.hasPermission(code))
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

// ---------------------------------------------------------------------------
// clients: internal JSON assemblers
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::clientToJson(Txn txn, const std::string &id) {
    Mapper<m::Client> mapper(txn);
    m::Client row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client not found", "error.msg.client.not.found");
    }
    co_return clientJson(row);
}

drogon::Task<std::string> CustomerService::resolveClientIdByExternalId(Txn txn,
                                                                        const std::string &externalId) {
    auto rows =
        co_await Mapper<m::Client>(txn).findBy(Criteria(m::Client::Cols::_external_id, externalId));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Client not found", "error.msg.client.not.found");
    co_return rows.front().getValueOfId();
}

drogon::Task<Json::Value> CustomerService::clientAddressToJson(Txn txn, const std::string &id) {
    Mapper<m::ClientAddress> mapper(txn);
    m::ClientAddress row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client address not found",
                       "error.msg.clientaddress.not.found");
    }
    co_return clientAddressJson(row);
}

drogon::Task<Json::Value> CustomerService::clientIdentifierToJson(Txn txn, const std::string &id) {
    Mapper<m::ClientIdentifier> mapper(txn);
    m::ClientIdentifier row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client identifier not found",
                       "error.msg.clientidentifier.not.found");
    }
    co_return clientIdentifierJson(row);
}

drogon::Task<Json::Value> CustomerService::familyMemberToJson(Txn txn, const std::string &id) {
    Mapper<m::ClientFamilyMember> mapper(txn);
    m::ClientFamilyMember row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Family member not found",
                       "error.msg.familymember.not.found");
    }
    co_return familyMemberJson(row);
}

drogon::Task<Json::Value> CustomerService::clientCollateralToJson(Txn txn, const std::string &id) {
    Mapper<m::ClientCollateralManagement> mapper(txn);
    m::ClientCollateralManagement row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client collateral not found",
                       "error.msg.clientcollateral.not.found");
    }
    co_return clientCollateralJson(row);
}

drogon::Task<Json::Value> CustomerService::clientChargeToJson(Txn txn, const std::string &id) {
    Mapper<m::ClientCharge> mapper(txn);
    m::ClientCharge row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client charge not found",
                       "error.msg.clientcharge.not.found");
    }
    co_return clientChargeJson(row);
}

drogon::Task<Json::Value> CustomerService::clientTransactionToJson(Txn txn, const std::string &id) {
    Mapper<m::ClientTransaction> mapper(txn);
    m::ClientTransaction row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client transaction not found",
                       "error.msg.clienttransaction.not.found");
    }
    co_return clientTransactionJson(row);
}

drogon::Task<Json::Value> CustomerService::collateralProductToJson(Txn txn, const std::string &id) {
    Mapper<m::CollateralManagement> mapper(txn);
    m::CollateralManagement row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Collateral product not found",
                       "error.msg.collateralproduct.not.found");
    }
    co_return collateralProductJson(row);
}

// ---------------------------------------------------------------------------
// clients: core CRUD
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listClients(const turbo::RequestContext &ctx,
                                                        const std::string &officeId,
                                                        const std::string &staffId,
                                                        const std::string &status,
                                                        const std::string &displayNameLike, int offset,
                                                        int limit) {
    requirePermission(ctx, "READ_CLIENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Client> mapper(txn);
    Criteria crit;
    auto add = [&](Criteria c) { crit = crit ? (crit && c) : c; };
    if (!officeId.empty()) add(Criteria(m::Client::Cols::_office_id, officeId));
    if (!staffId.empty()) add(Criteria(m::Client::Cols::_staff_id, staffId));
    if (!status.empty()) add(Criteria(m::Client::Cols::_status, std::stoi(status)));
    if (!displayNameLike.empty())
        add(Criteria(m::Client::Cols::_display_name, CompareOperator::Like, "%" + displayNameLike + "%"));

    const auto total = crit ? co_await mapper.count(crit) : co_await mapper.count();
    mapper.orderBy(m::Client::Cols::_display_name).limit(limit).offset(offset);
    auto rows = crit ? co_await mapper.findBy(crit) : co_await mapper.findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(clientJson(r));
    co_return turbo::pagedResult(static_cast<std::int64_t>(total), items);
}

drogon::Task<Json::Value> CustomerService::getClient(const turbo::RequestContext &ctx,
                                                     const std::string &id) {
    requirePermission(ctx, "READ_CLIENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await clientToJson(txn, id);
}

drogon::Task<Json::Value> CustomerService::getClientByExternalId(const turbo::RequestContext &ctx,
                                                                 const std::string &externalId) {
    requirePermission(ctx, "READ_CLIENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    const auto id = co_await resolveClientIdByExternalId(txn, externalId);
    co_return co_await clientToJson(txn, id);
}

drogon::Task<Json::Value> CustomerService::createClient(const turbo::RequestContext &ctx,
                                                        const Json::Value &body) {
    requirePermission(ctx, "CREATE_CLIENT");
    const auto officeId = asStringOr(body, "officeId");
    const auto firstname = asStringOr(body, "firstname");
    const auto lastname = asStringOr(body, "lastname");
    const auto fullname = asStringOr(body, "fullname");
    if (officeId.empty())
        throw ApiError(drogon::k400BadRequest, "officeId is required", "error.msg.client.office.required");
    if (fullname.empty() && (firstname.empty() || lastname.empty()))
        throw ApiError(drogon::k400BadRequest,
                       "Either fullname or both firstname and lastname are required",
                       "error.msg.client.name.required");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Client> mapper(txn);

    m::Client row;
    row.setOfficeId(officeId);
    row.setAccountNo(asStringOr(body, "accountNo", "CL" + turbo::ids::newUuid().substr(0, 10)));
    if (!asStringOr(body, "externalId").empty()) row.setExternalId(asStringOr(body, "externalId"));
    if (!asStringOr(body, "staffId").empty()) row.setStaffId(asStringOr(body, "staffId"));
    if (!firstname.empty()) row.setFirstname(firstname);
    if (!asStringOr(body, "middlename").empty()) row.setMiddlename(asStringOr(body, "middlename"));
    if (!lastname.empty()) row.setLastname(lastname);
    if (!fullname.empty()) row.setFullname(fullname);
    row.setDisplayName(fullname.empty() ? (firstname + " " + lastname) : fullname);
    if (!asStringOr(body, "mobileNo").empty()) row.setMobileNo(asStringOr(body, "mobileNo"));
    if (!asStringOr(body, "emailAddress").empty()) row.setEmailAddress(asStringOr(body, "emailAddress"));
    row.setIsStaff(asBoolOr(body, "isStaff", false));
    if (!asStringOr(body, "genderCvId").empty()) row.setGenderCvId(asStringOr(body, "genderCvId"));
    if (!asStringOr(body, "dateOfBirth").empty())
        row.setDateOfBirth(dateOr(asStringOr(body, "dateOfBirth"), Date()));
    if (!asStringOr(body, "clientTypeCvId").empty())
        row.setClientTypeCvId(asStringOr(body, "clientTypeCvId"));
    if (!asStringOr(body, "clientClassificationCvId").empty())
        row.setClientClassificationCvId(asStringOr(body, "clientClassificationCvId"));
    if (body.isMember("legalFormId")) row.setLegalStructure(asIntOr(body, "legalFormId", 1));
    const auto submittedOn = dateOr(asStringOr(body, "submittedOnDate"), Date::now());
    row.setSubmittedonDate(submittedOn);
    row.setStatus(kStatusPending);
    row.setKycStatus(asIntOr(body, "kycStatus", kKycPending));
    row.setRiskRating(asIntOr(body, "riskRating", kRiskLow));
    row.setFatcaFlag(asBoolOr(body, "fatcaFlag", false));
    row.setCrsFlag(asBoolOr(body, "crsFlag", false));
    if (!ctx.userId.empty()) row.setCreatedBy(ctx.userId);
    row.setCreatedAt(Date::now());

    try {
        row = co_await mapper.insert(row);
    } catch (const DrogonDbException &e) {
        throw ApiError(drogon::k400BadRequest,
                       std::string("Could not create client: ") + e.base().what(),
                       "error.msg.client.duplicate.accountNo");
    }

    if (body.isMember("nonPerson") && body["nonPerson"].isObject()) {
        const auto &np = body["nonPerson"];
        const auto constitutionCvId = asStringOr(np, "constitutionCvId");
        if (constitutionCvId.empty())
            throw ApiError(drogon::k400BadRequest, "nonPerson.constitutionCvId is required",
                           "error.msg.client.nonperson.constitution.required");
        m::ClientNonPerson npRow;
        npRow.setClientId(row.getValueOfId());
        npRow.setConstitutionCvId(constitutionCvId);
        if (!asStringOr(np, "incorpNo").empty()) npRow.setIncorpNo(asStringOr(np, "incorpNo"));
        if (!asStringOr(np, "incorpValidityTill").empty())
            npRow.setIncorpValidityTill(dateOr(asStringOr(np, "incorpValidityTill"), Date()));
        if (!asStringOr(np, "mainBusinessLineCvId").empty())
            npRow.setMainBusinessLineCvId(asStringOr(np, "mainBusinessLineCvId"));
        if (!asStringOr(np, "remarks").empty()) npRow.setRemarks(asStringOr(np, "remarks"));
        co_await Mapper<m::ClientNonPerson>(txn).insert(npRow);
    }

    co_await turbo::outbox::writeEvent(txn, ctx, "client", row.getValueOfId(), "client.created",
                                       clientJson(row));

    if (asBoolOr(body, "active", false)) {
        co_await applyClientCommand(txn, ctx, row.getValueOfId(), "activate", body);
    }

    co_return co_await clientToJson(txn, row.getValueOfId());
}

drogon::Task<Json::Value> CustomerService::updateClient(const turbo::RequestContext &ctx,
                                                        const std::string &id,
                                                        const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CLIENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Client> mapper(txn);
    m::Client row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client not found", "error.msg.client.not.found");
    }

    if (body.isMember("externalId")) {
        const auto v = asStringOr(body, "externalId");
        if (v.empty()) row.setExternalIdToNull(); else row.setExternalId(v);
    }
    if (body.isMember("staffId")) {
        const auto v = asStringOr(body, "staffId");
        if (v.empty()) row.setStaffIdToNull(); else row.setStaffId(v);
    }
    if (body.isMember("firstname")) row.setFirstname(asStringOr(body, "firstname"));
    if (body.isMember("middlename")) row.setMiddlename(asStringOr(body, "middlename"));
    if (body.isMember("lastname")) row.setLastname(asStringOr(body, "lastname"));
    if (body.isMember("fullname")) row.setFullname(asStringOr(body, "fullname"));
    if (body.isMember("firstname") || body.isMember("lastname") || body.isMember("fullname")) {
        const auto fn = row.getFullname() ? row.getValueOfFullname() : "";
        row.setDisplayName(fn.empty() ? (row.getValueOfFirstname() + " " + row.getValueOfLastname()) : fn);
    }
    if (body.isMember("mobileNo")) row.setMobileNo(asStringOr(body, "mobileNo"));
    if (body.isMember("emailAddress")) row.setEmailAddress(asStringOr(body, "emailAddress"));
    if (body.isMember("genderCvId")) row.setGenderCvId(asStringOr(body, "genderCvId"));
    if (body.isMember("dateOfBirth")) row.setDateOfBirth(dateOr(asStringOr(body, "dateOfBirth"), Date()));
    if (body.isMember("clientTypeCvId")) row.setClientTypeCvId(asStringOr(body, "clientTypeCvId"));
    if (body.isMember("clientClassificationCvId"))
        row.setClientClassificationCvId(asStringOr(body, "clientClassificationCvId"));
    if (body.isMember("legalFormId")) row.setLegalStructure(asIntOr(body, "legalFormId", 1));
    if (body.isMember("defaultSavingsProductId"))
        row.setDefaultSavingsProduct(asStringOr(body, "defaultSavingsProductId"));
    if (body.isMember("kycStatus")) row.setKycStatus(asIntOr(body, "kycStatus", kKycPending));
    if (body.isMember("riskRating")) row.setRiskRating(asIntOr(body, "riskRating", kRiskLow));
    if (body.isMember("fatcaFlag")) row.setFatcaFlag(asBoolOr(body, "fatcaFlag", false));
    if (body.isMember("crsFlag")) row.setCrsFlag(asBoolOr(body, "crsFlag", false));
    if (!ctx.userId.empty()) row.setModifiedBy(ctx.userId);
    row.setModifiedAt(Date::now());
    row.setUpdatedOn(Date::now());
    if (!ctx.userId.empty()) row.setUpdatedBy(ctx.userId);

    co_await mapper.update(row);

    if (body.isMember("nonPerson") && body["nonPerson"].isObject()) {
        const auto &np = body["nonPerson"];
        auto npRows = co_await Mapper<m::ClientNonPerson>(txn).findBy(
            Criteria(m::ClientNonPerson::Cols::_client_id, id));
        m::ClientNonPerson npRow;
        const bool exists = !npRows.empty();
        if (exists) npRow = npRows.front();
        npRow.setClientId(id);
        if (!asStringOr(np, "constitutionCvId").empty())
            npRow.setConstitutionCvId(asStringOr(np, "constitutionCvId"));
        if (!asStringOr(np, "incorpNo").empty()) npRow.setIncorpNo(asStringOr(np, "incorpNo"));
        if (!asStringOr(np, "incorpValidityTill").empty())
            npRow.setIncorpValidityTill(dateOr(asStringOr(np, "incorpValidityTill"), Date()));
        if (!asStringOr(np, "mainBusinessLineCvId").empty())
            npRow.setMainBusinessLineCvId(asStringOr(np, "mainBusinessLineCvId"));
        if (!asStringOr(np, "remarks").empty()) npRow.setRemarks(asStringOr(np, "remarks"));
        if (exists)
            co_await Mapper<m::ClientNonPerson>(txn).update(npRow);
        else
            co_await Mapper<m::ClientNonPerson>(txn).insert(npRow);
    }

    co_await turbo::outbox::writeEvent(txn, ctx, "client", id, "client.updated", body);
    co_return co_await clientToJson(txn, id);
}

drogon::Task<void> CustomerService::deleteClient(const turbo::RequestContext &ctx, const std::string &id) {
    requirePermission(ctx, "DELETE_CLIENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Client> mapper(txn);
    m::Client row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client not found", "error.msg.client.not.found");
    }
    if (row.getValueOfStatus() == kStatusActive)
        throw ApiError(drogon::k409Conflict, "Cannot delete an active client",
                       "error.msg.client.delete.active");
    co_await mapper.deleteByPrimaryKey(id);
    co_await turbo::outbox::writeEvent(txn, ctx, "client", id, "client.deleted", Json::Value());
}

drogon::Task<void> CustomerService::deleteClientByExternalId(const turbo::RequestContext &ctx,
                                                             const std::string &externalId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    const auto id = co_await resolveClientIdByExternalId(txn, externalId);
    co_await deleteClient(ctx, id);
}

Json::Value CustomerService::clientTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CLIENT");
    Json::Value out;
    out["statusOptions"] = Json::Value(Json::arrayValue);
    for (int s : {kStatusPending, kStatusActive, kStatusRejected, kStatusClosed, kStatusWithdrawn}) {
        Json::Value o;
        o["id"] = s;
        o["value"] = clientStatusLabel(s);
        out["statusOptions"].append(o);
    }
    // officeOptions/staffOptions/genderOptions/etc. are owned by
    // Organization/SystemConfig, each in its own database; there is no
    // inter-service RPC client yet, so those dropdowns are deliberately
    // left for the API caller/BFF layer to populate from those services.
    return out;
}

// ---------------------------------------------------------------------------
// clients: lifecycle & transfer commands
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::handleClientCommand(const turbo::RequestContext &ctx,
                                                                const std::string &id,
                                                                const std::string &command,
                                                                const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await applyClientCommand(txn, ctx, id, command, body);
}

drogon::Task<Json::Value> CustomerService::handleClientCommandByExternalId(
    const turbo::RequestContext &ctx, const std::string &externalId, const std::string &command,
    const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    const auto id = co_await resolveClientIdByExternalId(txn, externalId);
    co_return co_await applyClientCommand(txn, ctx, id, command, body);
}

drogon::Task<Json::Value> CustomerService::applyClientCommand(Txn txn, const turbo::RequestContext &ctx,
                                                              const std::string &id,
                                                              const std::string &command,
                                                              const Json::Value &body) {
    Mapper<m::Client> mapper(txn);
    m::Client row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client not found", "error.msg.client.not.found");
    }
    const int status = row.getValueOfStatus();

    auto invalidTransition = [&]() {
        throw ApiError(drogon::k409Conflict,
                       "Command '" + command + "' is not valid for client status " +
                           clientStatusLabel(status),
                       "error.msg.client.invalid.transition");
    };

    std::string eventType = "client." + command;
    std::string permission;

    if (command == "activate") {
        permission = "ACTIVATE_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusPending) invalidTransition();
        row.setStatus(kStatusActive);
        row.setActivationDate(dateOr(asStringOr(body, "activationDate"), Date::now()));
        row.setOfficeJoiningDate(row.getValueOfActivationDate());
        if (!ctx.userId.empty()) row.setActivatedonUserid(ctx.userId);
    } else if (command == "close") {
        permission = "CLOSE_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusActive && status != kStatusPending) invalidTransition();
        row.setStatus(kStatusClosed);
        row.setClosedonDate(dateOr(asStringOr(body, "closureDate"), Date::now()));
        if (!asStringOr(body, "closureReasonCvId").empty())
            row.setClosureReasonCvId(asStringOr(body, "closureReasonCvId"));
        if (!ctx.userId.empty()) row.setClosedonUserid(ctx.userId);
    } else if (command == "reject") {
        permission = "REJECT_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusPending) invalidTransition();
        row.setStatus(kStatusRejected);
        row.setRejectedonDate(dateOr(asStringOr(body, "rejectionDate"), Date::now()));
        if (!asStringOr(body, "rejectReasonCvId").empty())
            row.setRejectReasonCvId(asStringOr(body, "rejectReasonCvId"));
        if (!ctx.userId.empty()) row.setRejectedonUserid(ctx.userId);
    } else if (command == "withdraw") {
        permission = "WITHDRAW_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusPending) invalidTransition();
        row.setStatus(kStatusWithdrawn);
        row.setWithdrawnOnDate(dateOr(asStringOr(body, "withdrawalDate"), Date::now()));
        if (!asStringOr(body, "withdrawReasonCvId").empty())
            row.setWithdrawReasonCvId(asStringOr(body, "withdrawReasonCvId"));
        if (!ctx.userId.empty()) row.setWithdrawOnUserid(ctx.userId);
    } else if (command == "reactivate") {
        permission = "REACTIVATE_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusClosed) invalidTransition();
        row.setStatus(kStatusPending);
        row.setReactivatedOnDate(dateOr(asStringOr(body, "reactivationDate"), Date::now()));
        if (!ctx.userId.empty()) row.setReopenedByUserid(ctx.userId);
        row.setReopenedOnDate(row.getValueOfReactivatedOnDate());
    } else if (command == "undoRejection") {
        permission = "UNDOREJECTION_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusRejected) invalidTransition();
        row.setStatus(kStatusPending);
        row.setRejectReasonCvIdToNull();
        row.setRejectedonDateToNull();
        row.setRejectedonUseridToNull();
    } else if (command == "undoWithdrawal") {
        permission = "UNDOWITHDRAWAL_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusWithdrawn) invalidTransition();
        row.setStatus(kStatusPending);
        row.setWithdrawReasonCvIdToNull();
        row.setWithdrawnOnDateToNull();
        row.setWithdrawOnUseridToNull();
    } else if (command == "assignStaff") {
        permission = "ASSIGNSTAFF_CLIENT";
        requirePermission(ctx, permission);
        const auto staffId = asStringOr(body, "staffId");
        if (staffId.empty())
            throw ApiError(drogon::k400BadRequest, "staffId is required",
                           "error.msg.client.staffId.required");
        row.setStaffId(staffId);
    } else if (command == "unassignStaff") {
        permission = "UNASSIGNSTAFF_CLIENT";
        requirePermission(ctx, permission);
        row.setStaffIdToNull();
    } else if (command == "updateSavingsAccount") {
        permission = "UPDATESAVINGSACCOUNT_CLIENT";
        requirePermission(ctx, permission);
        const auto savingsAccountId = asStringOr(body, "savingsAccountId");
        if (savingsAccountId.empty())
            throw ApiError(drogon::k400BadRequest, "savingsAccountId is required",
                           "error.msg.client.savingsAccountId.required");
        row.setDefaultSavingsAccount(savingsAccountId);
    } else if (command == "proposeTransfer") {
        permission = "PROPOSETRANSFER_CLIENT";
        requirePermission(ctx, permission);
        if (status != kStatusActive) invalidTransition();
        if (row.getSubStatus() && row.getValueOfSubStatus() == kSubStatusTransferInProgress)
            throw ApiError(drogon::k409Conflict, "A transfer is already in progress for this client",
                           "error.msg.client.transfer.already.in.progress");
        const auto destinationOfficeId = asStringOr(body, "destinationOfficeId");
        if (destinationOfficeId.empty())
            throw ApiError(drogon::k400BadRequest, "destinationOfficeId is required",
                           "error.msg.client.transfer.destination.required");
        const auto transferDate = dateOr(asStringOr(body, "transferDate"), Date::now());
        m::ClientTransferDetails t;
        t.setClientId(id);
        t.setFromOfficeId(row.getValueOfOfficeId());
        t.setToOfficeId(destinationOfficeId);
        t.setProposedTransferDate(transferDate);
        t.setTransferType(kTransferProposed);
        t.setSubmittedOn(Date::now());
        t.setSubmittedBy(userIdOr(ctx));
        co_await Mapper<m::ClientTransferDetails>(txn).insert(t);
        row.setTransferToOfficeId(destinationOfficeId);
        row.setProposedTransferDate(transferDate);
        row.setSubStatus(kSubStatusTransferInProgress);
    } else if (command == "withdrawTransfer" || command == "rejectTransfer") {
        permission = command == "withdrawTransfer" ? "WITHDRAWTRANSFER_CLIENT" : "REJECTTRANSFER_CLIENT";
        requirePermission(ctx, permission);
        if (!row.getSubStatus() || row.getValueOfSubStatus() != kSubStatusTransferInProgress)
            throw ApiError(drogon::k409Conflict, "No transfer is in progress for this client",
                           "error.msg.client.transfer.not.in.progress");
        auto pending = co_await Mapper<m::ClientTransferDetails>(txn).findBy(
            Criteria(m::ClientTransferDetails::Cols::_client_id, id) &&
            Criteria(m::ClientTransferDetails::Cols::_transfer_type, kTransferProposed));
        for (auto &t : pending) {
            t.setTransferType(command == "withdrawTransfer" ? kTransferWithdrawn : kTransferRejected);
            co_await Mapper<m::ClientTransferDetails>(txn).update(t);
        }
        row.setTransferToOfficeIdToNull();
        row.setProposedTransferDateToNull();
        row.setSubStatusToNull();
    } else if (command == "acceptTransfer") {
        permission = "ACCEPTTRANSFER_CLIENT";
        requirePermission(ctx, permission);
        if (!row.getSubStatus() || row.getValueOfSubStatus() != kSubStatusTransferInProgress)
            throw ApiError(drogon::k409Conflict, "No transfer is in progress for this client",
                           "error.msg.client.transfer.not.in.progress");
        auto pending = co_await Mapper<m::ClientTransferDetails>(txn).findBy(
            Criteria(m::ClientTransferDetails::Cols::_client_id, id) &&
            Criteria(m::ClientTransferDetails::Cols::_transfer_type, kTransferProposed));
        for (auto &t : pending) {
            t.setTransferType(kTransferAccepted);
            co_await Mapper<m::ClientTransferDetails>(txn).update(t);
        }
        row.setOfficeId(row.getValueOfTransferToOfficeId());
        row.setOfficeJoiningDate(Date::now());
        row.setTransferToOfficeIdToNull();
        row.setProposedTransferDateToNull();
        row.setSubStatusToNull();
    } else {
        throw ApiError(drogon::k400BadRequest, "Unknown command: " + command,
                       "error.msg.client.unknown.command");
    }

    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "client", id, eventType, body);
    co_return co_await clientToJson(txn, id);
}

drogon::Task<Json::Value> CustomerService::clientTransferTemplate(const turbo::RequestContext &ctx,
                                                                  const std::string &id) {
    requirePermission(ctx, "READ_CLIENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto j = co_await clientToJson(txn, id);
    Json::Value out;
    out["clientId"] = j["id"];
    if (j.isMember("officeId")) out["officeId"] = j["officeId"];
    out["minProposedTransferDate"] = dateStr(Date::now());
    co_return out;
}

// ---------------------------------------------------------------------------
// client (addresses)
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listClientAddresses(const turbo::RequestContext &ctx,
                                                                const std::string &clientId) {
    requirePermission(ctx, "READ_CLIENTADDRESS");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);
    auto rows = co_await Mapper<m::ClientAddress>(txn).findBy(
        Criteria(m::ClientAddress::Cols::_client_id, clientId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(clientAddressJson(r));
    co_return items;
}

drogon::Task<Json::Value> CustomerService::createClientAddress(const turbo::RequestContext &ctx,
                                                               const std::string &clientId,
                                                               const Json::Value &body) {
    requirePermission(ctx, "CREATE_CLIENTADDRESS");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);

    m::ClientAddress row;
    row.setClientId(clientId);
    if (!asStringOr(body, "street").empty()) row.setStreet(asStringOr(body, "street"));
    if (!asStringOr(body, "addressLine1").empty()) row.setAddressLine1(asStringOr(body, "addressLine1"));
    if (!asStringOr(body, "addressLine2").empty()) row.setAddressLine2(asStringOr(body, "addressLine2"));
    if (!asStringOr(body, "city").empty()) row.setCity(asStringOr(body, "city"));
    if (!asStringOr(body, "stateOrProvince").empty())
        row.setStateOrProvince(asStringOr(body, "stateOrProvince"));
    if (!asStringOr(body, "country").empty()) row.setCountry(asStringOr(body, "country"));
    if (!asStringOr(body, "countryCode").empty()) row.setCountryCode(asStringOr(body, "countryCode"));
    if (!asStringOr(body, "addressTypeId").empty()) row.setAddressTypeId(asStringOr(body, "addressTypeId"));
    row.setIsActive(asBoolOr(body, "isActive", true));
    if (!ctx.userId.empty()) row.setCreatedBy(ctx.userId);
    row.setCreatedAt(Date::now());

    row = co_await Mapper<m::ClientAddress>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientaddress", row.getValueOfId(),
                                       "clientaddress.created", clientAddressJson(row));
    co_return clientAddressJson(row);
}

drogon::Task<Json::Value> CustomerService::updateClientAddress(const turbo::RequestContext &ctx,
                                                               const std::string &clientId,
                                                               const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CLIENTADDRESS");
    const auto addressId = asStringOr(body, "addressId", asStringOr(body, "id"));
    if (addressId.empty())
        throw ApiError(drogon::k400BadRequest, "addressId is required",
                       "error.msg.clientaddress.id.required");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientAddress> mapper(txn);
    m::ClientAddress row;
    try {
        row = co_await mapper.findByPrimaryKey(addressId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client address not found",
                       "error.msg.clientaddress.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client address not found",
                       "error.msg.clientaddress.not.found");

    if (body.isMember("street")) row.setStreet(asStringOr(body, "street"));
    if (body.isMember("addressLine1")) row.setAddressLine1(asStringOr(body, "addressLine1"));
    if (body.isMember("addressLine2")) row.setAddressLine2(asStringOr(body, "addressLine2"));
    if (body.isMember("city")) row.setCity(asStringOr(body, "city"));
    if (body.isMember("stateOrProvince")) row.setStateOrProvince(asStringOr(body, "stateOrProvince"));
    if (body.isMember("country")) row.setCountry(asStringOr(body, "country"));
    if (body.isMember("countryCode")) row.setCountryCode(asStringOr(body, "countryCode"));
    if (body.isMember("addressTypeId")) row.setAddressTypeId(asStringOr(body, "addressTypeId"));
    if (body.isMember("isActive")) row.setIsActive(asBoolOr(body, "isActive", true));
    if (!ctx.userId.empty()) row.setUpdatedBy(ctx.userId);
    row.setUpdatedAt(Date::now());

    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientaddress", addressId, "clientaddress.updated", body);
    co_return clientAddressJson(row);
}

Json::Value CustomerService::clientAddressTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CLIENTADDRESS");
    Json::Value out;
    // addressTypeOptions/countryOptions are owned by SystemConfig's code-value
    // catalog in its own database; left for the caller/BFF to populate.
    out["addressTypeOptions"] = Json::Value(Json::arrayValue);
    return out;
}

// ---------------------------------------------------------------------------
// client identifiers
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listClientIdentifiers(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId) {
    requirePermission(ctx, "READ_CLIENTIDENTIFIER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);
    auto rows = co_await Mapper<m::ClientIdentifier>(txn).findBy(
        Criteria(m::ClientIdentifier::Cols::_client_id, clientId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(clientIdentifierJson(r));
    co_return items;
}

drogon::Task<Json::Value> CustomerService::getClientIdentifier(const turbo::RequestContext &ctx,
                                                                const std::string &clientId,
                                                                const std::string &identifierId) {
    requirePermission(ctx, "READ_CLIENTIDENTIFIER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto j = co_await clientIdentifierToJson(txn, identifierId);
    if (j["clientId"].asString() != clientId)
        throw ApiError(drogon::k404NotFound, "Client identifier not found",
                       "error.msg.clientidentifier.not.found");
    co_return j;
}

drogon::Task<Json::Value> CustomerService::createClientIdentifier(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "CREATE_CLIENTIDENTIFIER");
    const auto documentTypeId = asStringOr(body, "documentTypeId");
    const auto documentKey = asStringOr(body, "documentKey");
    if (documentTypeId.empty() || documentKey.empty())
        throw ApiError(drogon::k400BadRequest, "documentTypeId and documentKey are required",
                       "error.msg.clientidentifier.required");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);

    m::ClientIdentifier row;
    row.setClientId(clientId);
    row.setDocumentTypeId(documentTypeId);
    row.setDocumentKey(documentKey);
    row.setStatus(asIntOr(body, "status", 300));
    if (body.isMember("active")) row.setActive(asIntOr(body, "active", 1));
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    row.setCreatedBy(userIdOr(ctx));
    row.setLastModifiedBy(userIdOr(ctx));
    row.setCreatedDate(Date::now());
    row.setCreatedOnUtc(Date::now());

    try {
        row = co_await Mapper<m::ClientIdentifier>(txn).insert(row);
    } catch (const DrogonDbException &e) {
        throw ApiError(drogon::k400BadRequest,
                       std::string("Could not create client identifier: ") + e.base().what(),
                       "error.msg.clientidentifier.duplicate");
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "clientidentifier", row.getValueOfId(),
                                       "clientidentifier.created", clientIdentifierJson(row));
    co_return clientIdentifierJson(row);
}

drogon::Task<Json::Value> CustomerService::updateClientIdentifier(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId,
                                                                  const std::string &identifierId,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CLIENTIDENTIFIER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientIdentifier> mapper(txn);
    m::ClientIdentifier row;
    try {
        row = co_await mapper.findByPrimaryKey(identifierId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client identifier not found",
                       "error.msg.clientidentifier.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client identifier not found",
                       "error.msg.clientidentifier.not.found");

    if (body.isMember("documentTypeId")) row.setDocumentTypeId(asStringOr(body, "documentTypeId"));
    if (body.isMember("documentKey")) row.setDocumentKey(asStringOr(body, "documentKey"));
    if (body.isMember("status")) row.setStatus(asIntOr(body, "status", 300));
    if (body.isMember("active")) row.setActive(asIntOr(body, "active", 1));
    if (body.isMember("description")) row.setDescription(asStringOr(body, "description"));
    row.setLastModifiedBy(userIdOr(ctx));
    row.setLastmodifiedDate(Date::now());
    row.setLastModifiedOnUtc(Date::now());

    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientidentifier", identifierId,
                                       "clientidentifier.updated", body);
    co_return clientIdentifierJson(row);
}

drogon::Task<void> CustomerService::deleteClientIdentifier(const turbo::RequestContext &ctx,
                                                           const std::string &clientId,
                                                           const std::string &identifierId) {
    requirePermission(ctx, "DELETE_CLIENTIDENTIFIER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientIdentifier> mapper(txn);
    m::ClientIdentifier row;
    try {
        row = co_await mapper.findByPrimaryKey(identifierId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client identifier not found",
                       "error.msg.clientidentifier.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client identifier not found",
                       "error.msg.clientidentifier.not.found");
    co_await mapper.deleteByPrimaryKey(identifierId);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientidentifier", identifierId,
                                       "clientidentifier.deleted", Json::Value());
}

Json::Value CustomerService::clientIdentifierTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CLIENTIDENTIFIER");
    Json::Value out;
    // documentTypeOptions owned by SystemConfig's code-value catalog.
    out["documentTypeOptions"] = Json::Value(Json::arrayValue);
    return out;
}

// ---------------------------------------------------------------------------
// client family members
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listFamilyMembers(const turbo::RequestContext &ctx,
                                                             const std::string &clientId) {
    requirePermission(ctx, "READ_CLIENTFAMILYMEMBER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);
    auto rows = co_await Mapper<m::ClientFamilyMember>(txn).findBy(
        Criteria(m::ClientFamilyMember::Cols::_client_id, clientId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(familyMemberJson(r));
    co_return items;
}

drogon::Task<Json::Value> CustomerService::getFamilyMember(const turbo::RequestContext &ctx,
                                                           const std::string &clientId,
                                                           const std::string &familyMemberId) {
    requirePermission(ctx, "READ_CLIENTFAMILYMEMBER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto j = co_await familyMemberToJson(txn, familyMemberId);
    if (j["clientId"].asString() != clientId)
        throw ApiError(drogon::k404NotFound, "Family member not found",
                       "error.msg.familymember.not.found");
    co_return j;
}

drogon::Task<Json::Value> CustomerService::createFamilyMember(const turbo::RequestContext &ctx,
                                                              const std::string &clientId,
                                                              const Json::Value &body) {
    requirePermission(ctx, "CREATE_CLIENTFAMILYMEMBER");
    const auto firstname = asStringOr(body, "firstname");
    const auto lastname = asStringOr(body, "lastname");
    if (firstname.empty() || lastname.empty())
        throw ApiError(drogon::k400BadRequest, "firstname and lastname are required",
                       "error.msg.familymember.name.required");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);

    m::ClientFamilyMember row;
    row.setClientId(clientId);
    row.setFirstname(firstname);
    if (!asStringOr(body, "middlename").empty()) row.setMiddlename(asStringOr(body, "middlename"));
    row.setLastname(lastname);
    if (!asStringOr(body, "qualification").empty()) row.setQualification(asStringOr(body, "qualification"));
    if (!asStringOr(body, "mobileNumber").empty()) row.setMobileNumber(asStringOr(body, "mobileNumber"));
    if (body.isMember("age")) row.setAge(asIntOr(body, "age", 0));
    row.setIsDependent(asBoolOr(body, "isDependent", false));
    if (!asStringOr(body, "relationshipCvId").empty())
        row.setRelationshipCvId(asStringOr(body, "relationshipCvId"));
    if (!asStringOr(body, "maritalStatusCvId").empty())
        row.setMaritalStatusCvId(asStringOr(body, "maritalStatusCvId"));
    if (!asStringOr(body, "genderCvId").empty()) row.setGenderCvId(asStringOr(body, "genderCvId"));
    if (!asStringOr(body, "dateOfBirth").empty())
        row.setDateOfBirth(dateOr(asStringOr(body, "dateOfBirth"), Date()));
    if (!asStringOr(body, "professionCvId").empty())
        row.setProfessionCvId(asStringOr(body, "professionCvId"));
    if (!ctx.userId.empty()) row.setCreatedBy(ctx.userId);
    row.setCreatedAt(Date::now());

    row = co_await Mapper<m::ClientFamilyMember>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "familymember", row.getValueOfId(),
                                       "familymember.created", familyMemberJson(row));
    co_return familyMemberJson(row);
}

drogon::Task<Json::Value> CustomerService::updateFamilyMember(const turbo::RequestContext &ctx,
                                                              const std::string &clientId,
                                                              const std::string &familyMemberId,
                                                              const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CLIENTFAMILYMEMBER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientFamilyMember> mapper(txn);
    m::ClientFamilyMember row;
    try {
        row = co_await mapper.findByPrimaryKey(familyMemberId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Family member not found",
                       "error.msg.familymember.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Family member not found",
                       "error.msg.familymember.not.found");

    if (body.isMember("firstname")) row.setFirstname(asStringOr(body, "firstname"));
    if (body.isMember("middlename")) row.setMiddlename(asStringOr(body, "middlename"));
    if (body.isMember("lastname")) row.setLastname(asStringOr(body, "lastname"));
    if (body.isMember("qualification")) row.setQualification(asStringOr(body, "qualification"));
    if (body.isMember("mobileNumber")) row.setMobileNumber(asStringOr(body, "mobileNumber"));
    if (body.isMember("age")) row.setAge(asIntOr(body, "age", 0));
    if (body.isMember("isDependent")) row.setIsDependent(asBoolOr(body, "isDependent", false));
    if (body.isMember("relationshipCvId")) row.setRelationshipCvId(asStringOr(body, "relationshipCvId"));
    if (body.isMember("maritalStatusCvId"))
        row.setMaritalStatusCvId(asStringOr(body, "maritalStatusCvId"));
    if (body.isMember("genderCvId")) row.setGenderCvId(asStringOr(body, "genderCvId"));
    if (body.isMember("dateOfBirth")) row.setDateOfBirth(dateOr(asStringOr(body, "dateOfBirth"), Date()));
    if (body.isMember("professionCvId")) row.setProfessionCvId(asStringOr(body, "professionCvId"));
    if (!ctx.userId.empty()) row.setUpdatedBy(ctx.userId);
    row.setUpdatedAt(Date::now());

    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "familymember", familyMemberId, "familymember.updated",
                                       body);
    co_return familyMemberJson(row);
}

drogon::Task<void> CustomerService::deleteFamilyMember(const turbo::RequestContext &ctx,
                                                       const std::string &clientId,
                                                       const std::string &familyMemberId) {
    requirePermission(ctx, "DELETE_CLIENTFAMILYMEMBER");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientFamilyMember> mapper(txn);
    m::ClientFamilyMember row;
    try {
        row = co_await mapper.findByPrimaryKey(familyMemberId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Family member not found",
                       "error.msg.familymember.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Family member not found",
                       "error.msg.familymember.not.found");
    co_await mapper.deleteByPrimaryKey(familyMemberId);
    co_await turbo::outbox::writeEvent(txn, ctx, "familymember", familyMemberId, "familymember.deleted",
                                       Json::Value());
}

Json::Value CustomerService::familyMemberTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CLIENTFAMILYMEMBER");
    Json::Value out;
    out["relationshipOptions"] = Json::Value(Json::arrayValue);
    out["maritalStatusOptions"] = Json::Value(Json::arrayValue);
    out["genderOptions"] = Json::Value(Json::arrayValue);
    out["professionOptions"] = Json::Value(Json::arrayValue);
    return out;
}

// ---------------------------------------------------------------------------
// client collaterals (client-level pledge against a collateral-management product)
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listClientCollaterals(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId) {
    requirePermission(ctx, "READ_CLIENTCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);
    auto rows = co_await Mapper<m::ClientCollateralManagement>(txn).findBy(
        Criteria(m::ClientCollateralManagement::Cols::_client_id, clientId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(clientCollateralJson(r));
    co_return items;
}

drogon::Task<Json::Value> CustomerService::getClientCollateral(const turbo::RequestContext &ctx,
                                                                const std::string &clientId,
                                                                const std::string &collateralId) {
    requirePermission(ctx, "READ_CLIENTCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto j = co_await clientCollateralToJson(txn, collateralId);
    if (j["clientId"].asString() != clientId)
        throw ApiError(drogon::k404NotFound, "Client collateral not found",
                       "error.msg.clientcollateral.not.found");
    co_return j;
}

drogon::Task<Json::Value> CustomerService::createClientCollateral(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "CREATE_CLIENTCOLLATERAL");
    const auto collateralId = asStringOr(body, "collateralId");
    const auto quantity = turbo::Money::parse(asStringOr(body, "quantity"));
    if (collateralId.empty() || !quantity)
        throw ApiError(drogon::k400BadRequest, "collateralId and a valid quantity are required",
                       "error.msg.clientcollateral.required");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);
    co_await collateralProductToJson(txn, collateralId);

    m::ClientCollateralManagement row;
    row.setClientId(clientId);
    row.setCollateralId(collateralId);
    row.setQuantity(quantity->toString(false));
    if (!ctx.userId.empty()) row.setCreatedBy(ctx.userId);
    row.setCreatedAt(Date::now());

    row = co_await Mapper<m::ClientCollateralManagement>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientcollateral", row.getValueOfId(),
                                       "clientcollateral.created", clientCollateralJson(row));
    co_return clientCollateralJson(row);
}

drogon::Task<Json::Value> CustomerService::updateClientCollateral(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId,
                                                                  const std::string &collateralId,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CLIENTCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientCollateralManagement> mapper(txn);
    m::ClientCollateralManagement row;
    try {
        row = co_await mapper.findByPrimaryKey(collateralId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client collateral not found",
                       "error.msg.clientcollateral.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client collateral not found",
                       "error.msg.clientcollateral.not.found");

    if (body.isMember("quantity")) {
        const auto quantity = turbo::Money::parse(asStringOr(body, "quantity"));
        if (!quantity)
            throw ApiError(drogon::k400BadRequest, "Invalid quantity", "error.msg.clientcollateral.quantity");
        row.setQuantity(quantity->toString(false));
    }
    if (!ctx.userId.empty()) row.setUpdatedBy(ctx.userId);
    row.setUpdatedAt(Date::now());

    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientcollateral", collateralId,
                                       "clientcollateral.updated", body);
    co_return clientCollateralJson(row);
}

drogon::Task<void> CustomerService::deleteClientCollateral(const turbo::RequestContext &ctx,
                                                           const std::string &clientId,
                                                           const std::string &collateralId) {
    requirePermission(ctx, "DELETE_CLIENTCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientCollateralManagement> mapper(txn);
    m::ClientCollateralManagement row;
    try {
        row = co_await mapper.findByPrimaryKey(collateralId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client collateral not found",
                       "error.msg.clientcollateral.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client collateral not found",
                       "error.msg.clientcollateral.not.found");
    co_await mapper.deleteByPrimaryKey(collateralId);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientcollateral", collateralId,
                                       "clientcollateral.deleted", Json::Value());
}

drogon::Task<Json::Value> CustomerService::clientCollateralTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CLIENTCOLLATERAL");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CollateralManagement>(txn).orderBy(m::CollateralManagement::Cols::_name)
                    .findAll();
    Json::Value out;
    out["collateralOptions"] = Json::Value(Json::arrayValue);
    for (const auto &r : rows) out["collateralOptions"].append(collateralProductJson(r));
    co_return out;
}

// ---------------------------------------------------------------------------
// client charges
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listClientCharges(const turbo::RequestContext &ctx,
                                                             const std::string &clientId) {
    requirePermission(ctx, "READ_CLIENTCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);
    auto rows = co_await Mapper<m::ClientCharge>(txn).findBy(
        Criteria(m::ClientCharge::Cols::_client_id, clientId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(clientChargeJson(r));
    co_return items;
}

drogon::Task<Json::Value> CustomerService::getClientCharge(const turbo::RequestContext &ctx,
                                                           const std::string &clientId,
                                                           const std::string &chargeId) {
    requirePermission(ctx, "READ_CLIENTCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto j = co_await clientChargeToJson(txn, chargeId);
    if (j["clientId"].asString() != clientId)
        throw ApiError(drogon::k404NotFound, "Client charge not found", "error.msg.clientcharge.not.found");
    co_return j;
}

drogon::Task<Json::Value> CustomerService::addClientCharge(const turbo::RequestContext &ctx,
                                                           const std::string &clientId,
                                                           const Json::Value &body) {
    requirePermission(ctx, "CREATE_CLIENTCHARGE");
    const auto chargeId = asStringOr(body, "chargeId");
    const auto amount = turbo::Money::parse(asStringOr(body, "amount"));
    if (chargeId.empty() || !amount || amount->isZero() || amount->isNegative())
        throw ApiError(drogon::k400BadRequest, "chargeId and a positive amount are required",
                       "error.msg.clientcharge.required");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);

    m::ClientCharge row;
    row.setClientId(clientId);
    row.setChargeId(chargeId);
    row.setIsPenalty(asBoolOr(body, "isPenalty", false));
    row.setChargeTimeEnum(asIntOr(body, "chargeTimeEnum", 1));
    if (!asStringOr(body, "dueDate").empty()) row.setChargeDueDate(dateOr(asStringOr(body, "dueDate"), Date()));
    row.setChargeCalculationEnum(asIntOr(body, "chargeCalculationEnum", 1));
    row.setAmount(amount->toString(false));
    row.setAmountOutstandingDerived(amount->toString(false));
    row.setIsActive(true);

    row = co_await Mapper<m::ClientCharge>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientcharge", row.getValueOfId(), "clientcharge.created",
                                       clientChargeJson(row));
    co_return clientChargeJson(row);
}

drogon::Task<void> CustomerService::deleteClientCharge(const turbo::RequestContext &ctx,
                                                       const std::string &clientId,
                                                       const std::string &chargeId) {
    requirePermission(ctx, "DELETE_CLIENTCHARGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientCharge> mapper(txn);
    m::ClientCharge row;
    try {
        row = co_await mapper.findByPrimaryKey(chargeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client charge not found", "error.msg.clientcharge.not.found");
    }
    if (row.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client charge not found", "error.msg.clientcharge.not.found");
    const bool hasPayments = row.getAmountPaidDerived() &&
                             !turbo::Money::parse(row.getValueOfAmountPaidDerived())->isZero();
    const bool hasWaivers = row.getAmountWaivedDerived() &&
                            !turbo::Money::parse(row.getValueOfAmountWaivedDerived())->isZero();
    if (hasPayments || hasWaivers)
        throw ApiError(drogon::k409Conflict, "Cannot delete a charge that has payments or waivers",
                       "error.msg.clientcharge.has.transactions");
    co_await mapper.deleteByPrimaryKey(chargeId);
    co_await turbo::outbox::writeEvent(txn, ctx, "clientcharge", chargeId, "clientcharge.deleted",
                                       Json::Value());
}

drogon::Task<Json::Value> CustomerService::handleClientChargeCommand(const turbo::RequestContext &ctx,
                                                                     const std::string &clientId,
                                                                     const std::string &chargeId,
                                                                     const std::string &command,
                                                                     const Json::Value &body) {
    if (command != "pay" && command != "waive")
        throw ApiError(drogon::k400BadRequest, "Unknown command: " + command,
                       "error.msg.clientcharge.unknown.command");
    requirePermission(ctx, command == "pay" ? "PAY_CLIENTCHARGE" : "WAIVE_CLIENTCHARGE");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientCharge> chargeMapper(txn);
    m::ClientCharge charge;
    try {
        charge = co_await chargeMapper.findByPrimaryKey(chargeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client charge not found", "error.msg.clientcharge.not.found");
    }
    if (charge.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client charge not found", "error.msg.clientcharge.not.found");

    const auto outstanding = *turbo::Money::parse(charge.getValueOfAmountOutstandingDerived());
    if (outstanding.isZero())
        throw ApiError(drogon::k409Conflict, "This charge has no outstanding balance",
                       "error.msg.clientcharge.no.outstanding");

    turbo::Money applied = outstanding;
    if (command == "pay" && body.isMember("transactionAmount")) {
        auto requested = turbo::Money::parse(asStringOr(body, "transactionAmount"));
        if (!requested || requested->isZero() || requested->isNegative())
            throw ApiError(drogon::k400BadRequest, "Invalid transactionAmount",
                           "error.msg.clienttransaction.amount");
        if (*requested > outstanding)
            throw ApiError(drogon::k400BadRequest,
                           "transactionAmount exceeds the outstanding balance",
                           "error.msg.clienttransaction.amount.exceeds.outstanding");
        applied = *requested;
    }

    auto clientRow = co_await Mapper<m::Client>(txn).findByPrimaryKey(clientId);

    m::ClientTransaction txnRow;
    txnRow.setClientId(clientId);
    txnRow.setOfficeId(clientRow.getOfficeId() ? clientRow.getValueOfOfficeId() : kZeroUuid);
    // No charges/currency catalog exists yet (lands in DepositAccountManagement,
    // a later phase); currencyCode is caller-supplied with a documented default.
    txnRow.setCurrencyCode(asStringOr(body, "currencyCode", "USD"));
    txnRow.setIsReversed(false);
    const auto transactionDate = dateOr(asStringOr(body, "transactionDate"), Date::now());
    txnRow.setTransactionDate(transactionDate);
    txnRow.setTransactionType(command == "pay" ? kTxnTypePayCharge : kTxnTypeWaiveCharge);
    txnRow.setAmount(applied.toString(false));
    if (!ctx.userId.empty()) txnRow.setCreatedBy(ctx.userId);
    txnRow.setCreatedAt(Date::now());
    txnRow.setSubmittedOnDate(Date::now());

    txnRow = co_await Mapper<m::ClientTransaction>(txn).insert(txnRow);

    m::ClientChargePaidBy paidBy;
    paidBy.setClientTransactionId(txnRow.getValueOfId());
    paidBy.setClientChargeId(chargeId);
    paidBy.setAmount(applied.toString(false));
    co_await Mapper<m::ClientChargePaidBy>(txn).insert(paidBy);

    const auto newOutstanding = outstanding - applied;
    charge.setAmountOutstandingDerived(newOutstanding.toString(false));
    if (command == "pay") {
        const auto priorPaid = charge.getAmountPaidDerived()
                                   ? *turbo::Money::parse(charge.getValueOfAmountPaidDerived())
                                   : turbo::Money::fromMicros(0);
        charge.setAmountPaidDerived((priorPaid + applied).toString(false));
    } else {
        const auto priorWaived = charge.getAmountWaivedDerived()
                                     ? *turbo::Money::parse(charge.getValueOfAmountWaivedDerived())
                                     : turbo::Money::fromMicros(0);
        charge.setAmountWaivedDerived((priorWaived + applied).toString(false));
        charge.setWaived(true);
    }
    if (newOutstanding.isZero()) charge.setIsPaidDerived(true);
    co_await Mapper<m::ClientCharge>(txn).update(charge);

    co_await turbo::outbox::writeEvent(txn, ctx, "clienttransaction", txnRow.getValueOfId(),
                                       command == "pay" ? "clienttransaction.charge.paid"
                                                         : "clienttransaction.charge.waived",
                                       clientTransactionJson(txnRow));
    co_await turbo::outbox::writeEvent(txn, ctx, "clientcharge", chargeId, "clientcharge.updated",
                                       clientChargeJson(charge));

    Json::Value out;
    out["transaction"] = clientTransactionJson(txnRow);
    out["charge"] = clientChargeJson(charge);
    co_return out;
}

Json::Value CustomerService::clientChargeTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CLIENTCHARGE");
    Json::Value out;
    // The charge catalog (name/currency/default amount per chargeId) belongs
    // to DepositAccountManagement (a later phase); chargeId is caller-supplied.
    out["chargeOptions"] = Json::Value(Json::arrayValue);
    return out;
}

// ---------------------------------------------------------------------------
// client transactions
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listClientTransactions(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId) {
    requirePermission(ctx, "READ_CLIENTTRANSACTION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await clientToJson(txn, clientId);
    auto rows = co_await Mapper<m::ClientTransaction>(txn)
                    .orderBy(m::ClientTransaction::Cols::_transaction_date, SortOrder::DESC)
                    .findBy(Criteria(m::ClientTransaction::Cols::_client_id, clientId));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(clientTransactionJson(r));
    co_return items;
}

drogon::Task<Json::Value> CustomerService::getClientTransaction(const turbo::RequestContext &ctx,
                                                                 const std::string &clientId,
                                                                 const std::string &transactionId) {
    requirePermission(ctx, "READ_CLIENTTRANSACTION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto j = co_await clientTransactionToJson(txn, transactionId);
    if (j["clientId"].asString() != clientId)
        throw ApiError(drogon::k404NotFound, "Client transaction not found",
                       "error.msg.clienttransaction.not.found");
    co_return j;
}

drogon::Task<Json::Value> CustomerService::undoClientTransaction(const turbo::RequestContext &ctx,
                                                                  const std::string &clientId,
                                                                  const std::string &transactionId) {
    requirePermission(ctx, "UNDO_CLIENTTRANSACTION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ClientTransaction> txMapper(txn);
    m::ClientTransaction transaction;
    try {
        transaction = co_await txMapper.findByPrimaryKey(transactionId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Client transaction not found",
                       "error.msg.clienttransaction.not.found");
    }
    if (transaction.getValueOfClientId() != clientId)
        throw ApiError(drogon::k404NotFound, "Client transaction not found",
                       "error.msg.clienttransaction.not.found");
    if (transaction.getValueOfIsReversed())
        throw ApiError(drogon::k409Conflict, "Transaction is already reversed",
                       "error.msg.clienttransaction.already.reversed");

    const auto reversedAmount = *turbo::Money::parse(transaction.getValueOfAmount());
    auto paidByRows = co_await Mapper<m::ClientChargePaidBy>(txn).findBy(
        Criteria(m::ClientChargePaidBy::Cols::_client_transaction_id, transactionId));
    for (const auto &pb : paidByRows) {
        Mapper<m::ClientCharge> chargeMapper(txn);
        m::ClientCharge charge;
        try {
            charge = co_await chargeMapper.findByPrimaryKey(pb.getValueOfClientChargeId());
        } catch (const UnexpectedRows &) {
            continue;
        }
        const auto pbAmount = *turbo::Money::parse(pb.getValueOfAmount());
        const auto outstanding = *turbo::Money::parse(charge.getValueOfAmountOutstandingDerived());
        charge.setAmountOutstandingDerived((outstanding + pbAmount).toString(false));
        if (transaction.getValueOfTransactionType() == kTxnTypePayCharge && charge.getAmountPaidDerived()) {
            const auto paid = *turbo::Money::parse(charge.getValueOfAmountPaidDerived());
            charge.setAmountPaidDerived((paid - pbAmount).toString(false));
        } else if (transaction.getValueOfTransactionType() == kTxnTypeWaiveCharge &&
                   charge.getAmountWaivedDerived()) {
            const auto waived = *turbo::Money::parse(charge.getValueOfAmountWaivedDerived());
            charge.setAmountWaivedDerived((waived - pbAmount).toString(false));
        }
        charge.setIsPaidDerived(false);
        co_await chargeMapper.update(charge);
        co_await turbo::outbox::writeEvent(txn, ctx, "clientcharge", charge.getValueOfId(),
                                           "clientcharge.updated", clientChargeJson(charge));
    }

    transaction.setIsReversed(true);
    co_await txMapper.update(transaction);
    co_await turbo::outbox::writeEvent(txn, ctx, "clienttransaction", transactionId,
                                       "clienttransaction.reversed", clientTransactionJson(transaction));
    (void)reversedAmount;
    co_return clientTransactionJson(transaction);
}

// ---------------------------------------------------------------------------
// collateral-management (product-level registry)
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::listCollateralProducts(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_COLLATERALPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await Mapper<m::CollateralManagement>(txn).orderBy(m::CollateralManagement::Cols::_name).findAll();
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(collateralProductJson(r));
    co_return items;
}

drogon::Task<Json::Value> CustomerService::getCollateralProduct(const turbo::RequestContext &ctx,
                                                                 const std::string &id) {
    requirePermission(ctx, "READ_COLLATERALPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await collateralProductToJson(txn, id);
}

drogon::Task<Json::Value> CustomerService::createCollateralProduct(const turbo::RequestContext &ctx,
                                                                    const Json::Value &body) {
    requirePermission(ctx, "CREATE_COLLATERALPRODUCT");
    const auto name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "name is required", "error.msg.collateralproduct.name.required");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::CollateralManagement row;
    row.setName(name);
    if (!asStringOr(body, "quality").empty()) row.setQuality(asStringOr(body, "quality"));
    if (body.isMember("basePrice")) {
        auto v = turbo::Money::parse(asStringOr(body, "basePrice"));
        if (v) row.setBasePrice(v->toString(false));
    }
    if (!asStringOr(body, "currencyCode").empty()) row.setCurrencyCode(asStringOr(body, "currencyCode"));
    if (body.isMember("pctToBase")) {
        auto v = turbo::Money::parse(asStringOr(body, "pctToBase"));
        if (v) row.setPctToBase(v->toString(false));
    }
    if (!asStringOr(body, "unitType").empty()) row.setUnitType(asStringOr(body, "unitType"));
    if (!ctx.userId.empty()) row.setCreatedBy(ctx.userId);
    row.setCreatedAt(Date::now());

    row = co_await Mapper<m::CollateralManagement>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "collateralproduct", row.getValueOfId(),
                                       "collateralproduct.created", collateralProductJson(row));
    co_return collateralProductJson(row);
}

drogon::Task<Json::Value> CustomerService::updateCollateralProduct(const turbo::RequestContext &ctx,
                                                                    const std::string &id,
                                                                    const Json::Value &body) {
    requirePermission(ctx, "UPDATE_COLLATERALPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::CollateralManagement> mapper(txn);
    m::CollateralManagement row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Collateral product not found",
                       "error.msg.collateralproduct.not.found");
    }
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("quality")) row.setQuality(asStringOr(body, "quality"));
    if (body.isMember("basePrice")) {
        auto v = turbo::Money::parse(asStringOr(body, "basePrice"));
        if (v) row.setBasePrice(v->toString(false));
    }
    if (body.isMember("currencyCode")) row.setCurrencyCode(asStringOr(body, "currencyCode"));
    if (body.isMember("pctToBase")) {
        auto v = turbo::Money::parse(asStringOr(body, "pctToBase"));
        if (v) row.setPctToBase(v->toString(false));
    }
    if (body.isMember("unitType")) row.setUnitType(asStringOr(body, "unitType"));
    if (!ctx.userId.empty()) row.setUpdatedBy(ctx.userId);
    row.setUpdatedAt(Date::now());

    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "collateralproduct", id, "collateralproduct.updated", body);
    co_return collateralProductJson(row);
}

drogon::Task<void> CustomerService::deleteCollateralProduct(const turbo::RequestContext &ctx,
                                                            const std::string &id) {
    requirePermission(ctx, "DELETE_COLLATERALPRODUCT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::CollateralManagement> mapper(txn);
    try {
        co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Collateral product not found",
                       "error.msg.collateralproduct.not.found");
    }
    const auto usedCount = co_await Mapper<m::ClientCollateralManagement>(txn).count(
        Criteria(m::ClientCollateralManagement::Cols::_collateral_id, id));
    if (usedCount > 0)
        throw ApiError(drogon::k409Conflict, "Cannot delete a collateral product pledged by clients",
                       "error.msg.collateralproduct.has.pledges");
    co_await mapper.deleteByPrimaryKey(id);
    co_await turbo::outbox::writeEvent(txn, ctx, "collateralproduct", id, "collateralproduct.deleted",
                                       Json::Value());
}

Json::Value CustomerService::collateralProductTemplate(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_COLLATERALPRODUCT");
    Json::Value out;
    out["unitTypeOptions"] = Json::Value(Json::arrayValue);
    return out;
}

// ---------------------------------------------------------------------------
// v2 search
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> CustomerService::searchClientsV2(const turbo::RequestContext &ctx,
                                                           const Json::Value &body) {
    requirePermission(ctx, "READ_CLIENT");
    const auto text = asStringOr(body, "text");
    if (text.empty())
        throw ApiError(drogon::k400BadRequest, "text is required", "error.msg.client.search.text.required");
    const auto pattern = "%" + text + "%";

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Criteria crit = Criteria(m::Client::Cols::_firstname, CompareOperator::Like, pattern) ||
                    Criteria(m::Client::Cols::_lastname, CompareOperator::Like, pattern) ||
                    Criteria(m::Client::Cols::_fullname, CompareOperator::Like, pattern) ||
                    Criteria(m::Client::Cols::_display_name, CompareOperator::Like, pattern) ||
                    Criteria(m::Client::Cols::_account_no, CompareOperator::Like, pattern) ||
                    Criteria(m::Client::Cols::_external_id, CompareOperator::Like, pattern);
    auto rows = co_await Mapper<m::Client>(txn)
                    .orderBy(m::Client::Cols::_display_name)
                    .limit(50)
                    .findBy(crit);
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r.getValueOfId();
        j["accountNo"] = r.getValueOfAccountNo();
        if (r.getDisplayName()) j["displayName"] = r.getValueOfDisplayName();
        if (r.getExternalId()) j["externalId"] = r.getValueOfExternalId();
        j["status"] = r.getValueOfStatus();
        items.append(j);
    }
    co_return items;
}

}  // namespace turbo_ledger_customer
