#!/usr/bin/env bash
#
# Turbo Ledger — Phase 0 smoke test.
#
# Runs the full Phase 0 acceptance checklist against a running stack
# (gateway + Identity + Accounting). Exits non-zero on the first failure.
#
# Usage:
#   src/tools/smoke_test.sh [GATEWAY_URL] [USERNAME] [PASSWORD]
#   GATEWAY=http://127.0.0.1:7499 src/tools/smoke_test.sh
#
set -u

GATEWAY="${1:-${GATEWAY:-http://127.0.0.1:7499}}"
USERNAME="${2:-${TL_USER:-admin}}"
PASSWORD="${3:-${TL_PASS:-Passw0rd!}}"
TENANT="${TL_TENANT:-default}"

PASS=0
FAIL=0

check() { # check <description> <actual> <expected>
    local desc="$1" actual="$2" expected="$3"
    if [ "$actual" = "$expected" ]; then
        printf '  \033[32mPASS\033[0m %-55s (%s)\n' "$desc" "$actual"
        PASS=$((PASS+1))
    else
        printf '  \033[31mFAIL\033[0m %-55s (got %s, want %s)\n' "$desc" "$actual" "$expected"
        FAIL=$((FAIL+1))
    fi
}

code() { curl -s -o /dev/null -w '%{http_code}' -m 10 "$@"; }

echo "== Turbo Ledger Phase 0 smoke test =="
echo "   gateway: $GATEWAY   tenant: $TENANT"
echo

echo "[1] Health & routing"
health_status=$(curl -s -m 10 "$GATEWAY/health" | python3 -c 'import json,sys;print(json.load(sys.stdin).get("status",""))' 2>/dev/null)
check "GET /health aggregate status UP" "$health_status" "UP"
check "GET /gateway/routes reachable" "$(code "$GATEWAY/gateway/routes")" "200"

echo
echo "[2] Tenant guardrails"
check "missing TL-Tenant-Id -> 400"   "$(code -X POST "$GATEWAY/api/v1/auth/signin")" "400"
check "unknown tenant -> 404"         "$(code -X POST "$GATEWAY/api/v1/auth/signin" -H 'TL-Tenant-Id: no_such_tenant')" "404"
check "suspended tenant -> 403"       "$(code -X POST "$GATEWAY/api/v1/auth/signin" -H 'TL-Tenant-Id: closed_bank')" "403"
check "malformed tenant id -> 400"    "$(code -X POST "$GATEWAY/api/v1/auth/signin" -H 'TL-Tenant-Id: Bad;Tenant')" "400"

echo
echo "[3] Authentication at the edge"
signin=$(curl -s -m 10 -X POST "$GATEWAY/api/v1/auth/signin" \
    -H "TL-Tenant-Id: $TENANT" -H 'Content-Type: application/json' \
    -d "{\"usernameOrEmail\":\"$USERNAME\",\"password\":\"$PASSWORD\"}")
TOKEN=$(printf '%s' "$signin" | python3 -c 'import json,sys
try: print(json.load(sys.stdin)["result"]["token"])
except Exception: print("")' 2>/dev/null)
check "signin returns a JWT" "$([ -n "$TOKEN" ] && echo yes)" "yes"
check "protected route w/o credentials -> 401" \
    "$(code "$GATEWAY/api/v1/accounting/gl-accounts/get-all" -H "TL-Tenant-Id: $TENANT")" "401"
check "tampered bearer token -> 401" \
    "$(code "$GATEWAY/api/v1/accounting/gl-accounts/get-all" -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer ${TOKEN}x")" "401"

echo
echo "[4] Gateway -> service trusted context (signed TL-Context)"
acct=$(curl -s -m 10 -D /tmp/tl_smoke_hdrs "$GATEWAY/api/v1/accounting/gl-accounts/get-all" \
    -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $TOKEN")
acct_code=$(printf '%s' "$acct" | python3 -c 'import json,sys
try: print(json.load(sys.stdin)["error"]["userMessageGlobalisationCode"])
except Exception: print("")' 2>/dev/null)
check "Accounting accepts signed context (501 stub envelope)" "$acct_code" "error.msg.platform.not.implemented"
check "X-Request-Id propagated" \
    "$(grep -ci '^x-request-id' /tmp/tl_smoke_hdrs | tr -d '[:space:]')" "1"
check "direct service call w/o TL-Context rejected (401)" \
    "$(code "${GATEWAY%:*}:7501/api/v1/accounting/gl-accounts/get-all" 2>/dev/null || echo skip)" "401"

echo
echo "[5] Idempotency-Key replay"
KEY="smoke-$(date +%s)-$$"
curl -s -o /dev/null -m 10 -X POST "$GATEWAY/api/v1/accounting/gl-accounts/create" \
    -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $TOKEN" \
    -H 'Content-Type: application/json' -H "Idempotency-Key: $KEY" -d '{"name":"Cash"}'
replayed=$(curl -s -o /dev/null -m 10 -D - -X POST "$GATEWAY/api/v1/accounting/gl-accounts/create" \
    -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $TOKEN" \
    -H 'Content-Type: application/json' -H "Idempotency-Key: $KEY" -d '{"name":"Cash"}' \
    | grep -ci '^idempotency-replayed' | tr -d '[:space:]')
check "second POST with same key is replayed" "$replayed" "1"

echo
echo "[6] Rate limiting (400-request burst, expect some 429s)"
throttled=$(seq 1 400 | xargs -P 8 -I{} curl -s -o /dev/null -w '%{http_code}\n' -m 10 \
    "$GATEWAY/api/v1/accounting/gl-accounts/get-all" \
    -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $TOKEN" | grep -c 429)
check "429s observed under burst" "$([ "$throttled" -gt 0 ] && echo yes)" "yes"
echo "       ($throttled/400 throttled)"

echo
echo "== Result: $PASS passed, $FAIL failed =="
[ "$FAIL" -eq 0 ]
