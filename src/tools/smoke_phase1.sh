#!/usr/bin/env bash
#
# smoke_phase1.sh — end-to-end verification of Phase 1 (Tenancy & Identity).
#
# Exercises the full tenant lifecycle through the API Gateway:
#   provision tenant -> tenant admin signin -> RBAC (roles/permissions/users)
#   -> maker-checker round trip on CREATE_USER -> self profile & password
#   -> suspend / activate / close lifecycle -> cross-tenant token rejection.
#
# Prereqs: gateway :7499, Identity :7500, Accounting :7501, Provisioner :7512
# all running (see src/tools/dev_up.sh), host admin admin/Passw0rd! seeded.
#
# Each run provisions a fresh tenant (phx_<rand>) and closes it at the end.
# Usage: bash src/tools/smoke_phase1.sh [gateway-base-url]

set -u
GW="${1:-http://127.0.0.1:7499}"
TTL_WAIT=6   # gateway tenant-registry cache TTL (5s) + 1
PASS=0; FAIL=0

say()   { printf '\n[%s] %s\n' "$1" "$2"; }
check() { # check <label> <expected> <actual>
    local label="$1" expected="$2" actual="$3"
    if [[ "$actual" == "$expected" ]]; then
        printf '  \033[32mPASS\033[0m %-55s (%s)\n' "$label" "$actual"; PASS=$((PASS+1))
    else
        printf '  \033[31mFAIL\033[0m %-55s (expected %s, got %s)\n' "$label" "$expected" "$actual"; FAIL=$((FAIL+1))
    fi
}
jget() { python3 -c "import json,sys
try:
    d = json.load(sys.stdin)
    for k in '$1'.split('.'):
        d = d[int(k)] if isinstance(d, list) else d.get(k)
        if d is None: break
    print('' if d is None else (json.dumps(d) if isinstance(d,(dict,list,bool)) else d))
except Exception:
    print('')"; }

TENANT="phx_$((RANDOM % 90000 + 10000))"

# ---------------------------------------------------------------- [1] host
say 1 "Host admin signs in on the 'default' tenant"
HT=$(curl -s -X POST "$GW/api/v1/auth/signin" -H 'TL-Tenant-Id: default' \
        -H 'Content-Type: application/json' \
        -d '{"usernameOrEmail":"admin","password":"Passw0rd!"}' | jget result.token)
check "host admin signin returns a JWT" "yes" "$([[ -n "$HT" ]] && echo yes || echo no)"

# ------------------------------------------------------------ [2] provision
say 2 "Provision tenant '$TENANT' end-to-end"
CREATE=$(curl -s -X POST "$GW/api/v1/tenants/create" -H 'TL-Tenant-Id: default' \
        -H "Authorization: Bearer $HT" -H 'Content-Type: application/json' \
        -d "{\"id\":\"$TENANT\",\"name\":\"Phoenix Bank\"}")
check "tenant create succeeds"        "true"   "$(echo "$CREATE" | jget success)"
check "tenant is ACTIVE"              "ACTIVE" "$(echo "$CREATE" | jget result.status)"
APW=$(echo "$CREATE" | jget result.adminPassword)
check "one-time admin password returned" "yes" "$([[ -n "$APW" ]] && echo yes || echo no)"
MIG=$(echo "$CREATE" | jget result.services.0.migrationsApplied)
check "identity migrations applied"   "4"      "$MIG"
DUP=$(curl -s -o /dev/null -w '%{http_code}' -X POST "$GW/api/v1/tenants/create" \
        -H 'TL-Tenant-Id: default' -H "Authorization: Bearer $HT" \
        -H 'Content-Type: application/json' -d "{\"id\":\"$TENANT\",\"name\":\"Dup\"}")
check "duplicate tenant id -> 409"    "409"    "$DUP"

sleep "$TTL_WAIT"   # let the gateway registry cache pick up the new tenant

# ---------------------------------------------------------- [3] tenant admin
say 3 "Tenant admin signs in under TL-Tenant-Id: $TENANT"
AT=$(curl -s -X POST "$GW/api/v1/auth/signin" -H "TL-Tenant-Id: $TENANT" \
        -H 'Content-Type: application/json' \
        -d "{\"usernameOrEmail\":\"admin\",\"password\":\"$APW\"}" | jget result.token)
check "tenant admin signin returns a JWT" "yes" "$([[ -n "$AT" ]] && echo yes || echo no)"
NPERM=$(curl -s "$GW/api/v1/permissions/get-all" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" | jget result.totalCount)
check "permission catalog is populated" "yes" "$([[ "${NPERM:-0}" -gt 0 ]] && echo yes || echo no)"
SELF=$(curl -s "$GW/api/v1/self/userdetails" -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $AT")
check "self userdetails has ALL_FUNCTIONS" "yes" \
      "$(echo "$SELF" | grep -q ALL_FUNCTIONS && echo yes || echo no)"

say 4 "Tenant management is host-plane only"
FORB=$(curl -s -o /dev/null -w '%{http_code}' -X POST "$GW/api/v1/tenants/create" \
        -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $AT" \
        -H 'Content-Type: application/json' -d '{"id":"nope","name":"Nope"}')
check "tenant JWT cannot manage tenants -> 403" "403" "$FORB"

# ------------------------------------------------------------- [5] rbac
say 5 "Roles and immediate user creation"
ROLE=$(curl -s -X POST "$GW/api/v1/roles/create" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" -H 'Content-Type: application/json' \
        -d '{"name":"Branch supervisor","description":"Approves branch ops"}')
check "role created" "true" "$(echo "$ROLE" | jget success)"
ALICE=$(curl -s -X POST "$GW/api/v1/users/create" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" -H 'Content-Type: application/json' \
        -d '{"username":"alice","email":"alice@phx.dev","firstName":"Alice","lastName":"Ops","password":"Passw0rd!1","roles":["Admin"]}')
check "user created immediately (no maker-checker)" "true" "$(echo "$ALICE" | jget success)"

# ------------------------------------------------------- [6] maker-checker
say 6 "Maker-checker round trip on CREATE_USER"
MC=$(curl -s -X PUT "$GW/api/v1/permissions/maker-checker" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" -H 'Content-Type: application/json' \
        -d '{"code":"CREATE_USER","enabled":true}')
check "maker-checker enabled on CREATE_USER" "true" "$(echo "$MC" | jget success)"
BOB=$(curl -s -X POST "$GW/api/v1/users/create" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" -H 'Content-Type: application/json' \
        -d '{"username":"bob","email":"bob@phx.dev","firstName":"Bob","lastName":"Teller","password":"Passw0rd!2","roles":["Teller"]}')
check "create user now pends for approval" "true" "$(echo "$BOB" | jget result.pendingApproval)"
CMD=$(echo "$BOB" | jget result.commandId)
PRE=$(curl -s -X POST "$GW/api/v1/auth/signin" -H "TL-Tenant-Id: $TENANT" \
        -H 'Content-Type: application/json' \
        -d '{"usernameOrEmail":"bob","password":"Passw0rd!2"}' | jget success)
check "pending user cannot sign in yet" "false" "$PRE"
LISTED=$(curl -s "$GW/api/v1/makercheckers/get-all?status=PENDING" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" | grep -c "$CMD")
check "command visible in pending queue" "1" "$LISTED"
APPROVE=$(curl -s -X POST "$GW/api/v1/makercheckers/approve/$CMD" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT")
check "approve executes the command" "APPROVED" "$(echo "$APPROVE" | jget result.status)"
POST=$(curl -s -X POST "$GW/api/v1/auth/signin" -H "TL-Tenant-Id: $TENANT" \
        -H 'Content-Type: application/json' \
        -d '{"usernameOrEmail":"bob","password":"Passw0rd!2"}' | jget success)
check "approved user can sign in" "true" "$POST"

DAVE=$(curl -s -X POST "$GW/api/v1/users/create" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" -H 'Content-Type: application/json' \
        -d '{"username":"dave","email":"dave@phx.dev","firstName":"Dave","lastName":"Reject","password":"Passw0rd!4","roles":["Teller"]}')
DCMD=$(echo "$DAVE" | jget result.commandId)
REJECT=$(curl -s -X POST "$GW/api/v1/makercheckers/reject/$DCMD" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT")
check "reject marks command REJECTED" "REJECTED" "$(echo "$REJECT" | jget result.status)"
DSIGN=$(curl -s -X POST "$GW/api/v1/auth/signin" -H "TL-Tenant-Id: $TENANT" \
        -H 'Content-Type: application/json' \
        -d '{"usernameOrEmail":"dave","password":"Passw0rd!4"}' | jget success)
check "rejected user was never created" "false" "$DSIGN"

# ----------------------------------------------------------- [7] self svc
say 7 "Self-service password change"
CHG=$(curl -s -X POST "$GW/api/v1/self/change-password" -H "TL-Tenant-Id: $TENANT" \
        -H "Authorization: Bearer $AT" -H 'Content-Type: application/json' \
        -d "{\"oldPassword\":\"$APW\",\"newPassword\":\"N3wPassw0rd!\"}")
check "change-password succeeds" "true" "$(echo "$CHG" | jget success)"
RESIGN=$(curl -s -X POST "$GW/api/v1/auth/signin" -H "TL-Tenant-Id: $TENANT" \
        -H 'Content-Type: application/json' \
        -d '{"usernameOrEmail":"admin","password":"N3wPassw0rd!"}' | jget success)
check "signin works with the new password" "true" "$RESIGN"

# ---------------------------------------------------------- [8] lifecycle
say 8 "Tenant lifecycle: suspend / activate / close"
curl -s -X POST "$GW/api/v1/tenants/suspend/$TENANT" -H 'TL-Tenant-Id: default' \
        -H "Authorization: Bearer $HT" > /dev/null
sleep "$TTL_WAIT"
SUS=$(curl -s -o /dev/null -w '%{http_code}' "$GW/api/v1/roles/get-all" \
        -H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $AT")
check "suspended tenant traffic -> 403" "403" "$SUS"
ACT=$(curl -s -X POST "$GW/api/v1/tenants/activate/$TENANT" -H 'TL-Tenant-Id: default' \
        -H "Authorization: Bearer $HT" | jget result.status)
check "tenant reactivated" "ACTIVE" "$ACT"
XT=$(curl -s -o /dev/null -w '%{http_code}' "$GW/api/v1/roles/get-all" \
        -H 'TL-Tenant-Id: demo_bank' -H "Authorization: Bearer $AT")
check "token replayed on another tenant -> 401" "401" "$XT"
CLOSE=$(curl -s -X POST "$GW/api/v1/tenants/close/$TENANT" -H 'TL-Tenant-Id: default' \
        -H "Authorization: Bearer $HT" | jget result.status)
check "tenant closed" "CLOSED" "$CLOSE"

printf '\n== Result: %d passed, %d failed ==\n' "$PASS" "$FAIL"
[[ "$FAIL" -eq 0 ]]
