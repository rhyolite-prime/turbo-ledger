//
// libturbo unit tests — no running server or database required.
//
#include <cassert>
#include <cstdio>
#include <string>

#include <drogon/HttpRequest.h>

#include "turbo/ApiResponse.h"
#include "turbo/ContextCodec.h"
#include "turbo/Ids.h"
#include "turbo/Money.h"
#include "turbo/Pagination.h"
#include "turbo/RequestContext.h"
#include "turbo/TenantStatus.h"

static int g_failures = 0;
#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            ++g_failures;                                                  \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);    \
        }                                                                  \
    } while (0)

static void testMoney() {
    using turbo::Money;

    CHECK(Money::parse("0")->micros() == 0);
    CHECK(Money::parse("1")->micros() == 1000000);
    CHECK(Money::parse("-12.5")->micros() == -12500000);
    CHECK(Money::parse("0.000001")->micros() == 1);
    CHECK(!Money::parse("0.0000001"));  // 7 decimals
    CHECK(!Money::parse("12."));
    CHECK(!Money::parse("1e5"));
    CHECK(!Money::parse("abc"));
    CHECK(!Money::parse(""));

    CHECK(Money::parse("12.5")->toString() == "12.5");
    CHECK(Money::parse("-12.5")->toString() == "-12.5");
    CHECK(Money::parse("3")->toString() == "3");
    CHECK(Money::parse("3")->toString(false) == "3.000000");

    auto a = *Money::parse("10.25");
    auto b = *Money::parse("0.75");
    CHECK((a + b).toString() == "11");
    CHECK((a - b).toString() == "9.5");
    CHECK(a.times(4).toString() == "41");

    // Half-even rounding: 2.5 -> 2, 3.5 -> 4 (at cents)
    CHECK(Money::parse("0.025")->roundTo(2).toString() == "0.02");
    CHECK(Money::parse("0.035")->roundTo(2).toString() == "0.04");
    CHECK(Money::parse("-0.025")->roundTo(2).toString() == "-0.02");

    // Allocation preserves the exact total.
    auto shares = Money::parse("100")->allocate(3);
    turbo::Money sum;
    for (auto &s : shares) sum += s;
    CHECK(sum == *Money::parse("100"));
    CHECK(shares[0].micros() >= shares[2].micros());

    // Ratio: 100 * 1/3 with half-even rounding at micros.
    CHECK(Money::parse("100")->timesRatio(1, 3).toString() == "33.333333");

    bool threw = false;
    try {
        Money::fromMicros(INT64_MAX).times(2);
    } catch (const turbo::MoneyError &) {
        threw = true;
    }
    CHECK(threw);
}

static void testContextCodec() {
    using turbo::ContextCodec;
    using turbo::RequestContext;

    RequestContext ctx;
    ctx.tenantId = "acme_bank";
    ctx.userId = "u-123";
    ctx.username = "jdoe";
    ctx.authScheme = "jwt";
    ctx.permissions = {"CREATE_JOURNALENTRY", "READ_GLACCOUNT"};
    ctx.requestId = turbo::ids::newRequestId();
    ctx.issuedAtEpoch = 1700000000;
    ctx.expiresAtEpoch = 4102444800;  // far future

    const std::string secret = "test-secret";
    auto token = ContextCodec::encode(ctx, secret);

    std::string err;
    auto decoded = ContextCodec::decode(token, secret, &err);
    CHECK(decoded.has_value());
    CHECK(decoded->tenantId == "acme_bank");
    CHECK(decoded->tenantSchema() == "t_acme_bank");
    CHECK(decoded->username == "jdoe");
    CHECK(decoded->permissions.size() == 2);
    CHECK(decoded->hasPermission("READ_GLACCOUNT"));
    CHECK(!decoded->hasPermission("DELETE_GLACCOUNT"));

    // Tampered payload must fail.
    auto tampered = token;
    tampered[5] = tampered[5] == 'A' ? 'B' : 'A';
    CHECK(!ContextCodec::decode(tampered, secret, &err));

    // Wrong secret must fail.
    CHECK(!ContextCodec::decode(token, "other-secret", &err));

    // Expired context must fail.
    ctx.expiresAtEpoch = 1000;
    CHECK(!ContextCodec::decode(ContextCodec::encode(ctx, secret), secret, &err));
    CHECK(err == "context expired");

    // Tenant id validation.
    CHECK(RequestContext::isValidTenantId("default"));
    CHECK(RequestContext::isValidTenantId("acme_bank_2"));
    CHECK(!RequestContext::isValidTenantId("Acme"));
    CHECK(!RequestContext::isValidTenantId("a b"));
    CHECK(!RequestContext::isValidTenantId(""));
    CHECK(!RequestContext::isValidTenantId("x; DROP TABLE"));
}

static void testPagination() {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setPath("/api/v1/glaccounts");
    req->setParameter("offset", "20");
    req->setParameter("limit", "999");        // must clamp to 200
    req->setParameter("orderBy", "name");
    req->setParameter("sortOrder", "desc");

    auto page = turbo::PageRequest::fromRequest(req, {"name", "gl_code"});
    CHECK(page.offset == 20);
    CHECK(page.limit == turbo::PageRequest::kMaxLimit);
    CHECK(page.orderBy == "name");
    CHECK(page.descending);
    CHECK(page.toSqlSuffix() == " ORDER BY name DESC LIMIT 200 OFFSET 20");

    // Non-whitelisted orderBy is dropped (SQLi guard).
    req->setParameter("orderBy", "name; DROP TABLE x");
    auto page2 = turbo::PageRequest::fromRequest(req, {"name"});
    CHECK(page2.orderBy.empty());
    CHECK(page2.toSqlSuffix("id") == " ORDER BY id DESC LIMIT 200 OFFSET 20");

    auto envelope = turbo::pagedResult(42, Json::Value(Json::arrayValue));
    CHECK(envelope["totalFilteredRecords"].asInt64() == 42);
    CHECK(envelope["pageItems"].isArray());
}

static void testIdsAndResponse() {
    auto u1 = turbo::ids::newUuid();
    auto u2 = turbo::ids::newUuid();
    CHECK(u1.size() == 36);
    CHECK(u1 != u2);
    CHECK(u1[14] == '4');  // uuid v4

    auto ok = turbo::ApiResponse::ok(Json::Value("data"), "done");
    CHECK(ok.toJson()["success"].asBool());
    auto fail = turbo::ApiResponse::fail("boom", "error.msg.test");
    fail.withFieldError("name", "name is required");
    auto j = fail.toJson();
    CHECK(!j["success"].asBool());
    CHECK(j["error"]["userMessageGlobalisationCode"].asString() == "error.msg.test");
    CHECK(j["error"]["errors"][0]["parameterName"].asString() == "name");
}

static void testTenantStatus() {
    using turbo::TenantStatus;
    using turbo::tenantStatusFromString;
    using turbo::toString;

    // round-trip every enumerator through its wire label
    for (const auto status : turbo::kAllTenantStatuses)
        CHECK(tenantStatusFromString(toString(status)) == status);
    CHECK(!tenantStatusFromString("active"));   // labels are case-sensitive
    CHECK(!tenantStatusFromString("DELETED"));
    CHECK(!tenantStatusFromString(""));

    CHECK(turbo::isServing(TenantStatus::Active));
    CHECK(!turbo::isServing(TenantStatus::Suspended));
    CHECK(!turbo::isServing(TenantStatus::Provisioning));

    using turbo::isLegalTransition;
    CHECK(isLegalTransition(TenantStatus::Active, TenantStatus::Suspended));
    CHECK(isLegalTransition(TenantStatus::Suspended, TenantStatus::Active));
    CHECK(isLegalTransition(TenantStatus::Pending, TenantStatus::Active));
    CHECK(isLegalTransition(TenantStatus::Active, TenantStatus::Closed));
    CHECK(isLegalTransition(TenantStatus::Failed, TenantStatus::Closed));
    CHECK(!isLegalTransition(TenantStatus::Closed, TenantStatus::Active));    // terminal
    CHECK(!isLegalTransition(TenantStatus::Closed, TenantStatus::Closed));
    CHECK(!isLegalTransition(TenantStatus::Suspended, TenantStatus::Suspended));
    CHECK(!isLegalTransition(TenantStatus::Active, TenantStatus::Pending));   // initial only
}

int main() {
    testMoney();
    testContextCodec();
    testPagination();
    testIdsAndResponse();
    testTenantStatus();
    if (g_failures == 0) {
        std::printf("turbo_tests: ALL PASSED\n");
        return 0;
    }
    std::printf("turbo_tests: %d FAILURES\n", g_failures);
    return 1;
}
