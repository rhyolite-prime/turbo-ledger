#!/usr/bin/env bash
#
# smoke_phase2.sh — end-to-end verification of Phase 2 (Organization & SystemConfig).
#
# Exercises, through the API Gateway, on a freshly provisioned tenant:
#   office tree + staff (Organization) -> codes/code values seeded (SystemConfig)
#   -> currencies/paymenttypes/holidays spot checks -> hooks/businessdate/caches
#   -> the datatables engine: create a datatable, attach an entry to a synthetic
#      entity id, read it back, update it, then tear it down.
#
# NOTE on the Phase 2 exit criterion "datatable creatable and attachable to
# m_client and surfacing in client responses": the Customer service (which will
# own `m_client` / `clients`) doesn't exist until Phase 3, so this script proves
# the datatable engine end-to-end against a synthetic apptable id instead. Once
# Customer ships, re-run this against a real client id and assert the datatable
# section appears in `GET clients/get-details/{id}`.
#
# Prereqs: gateway :7499, Identity :7500, Accounting :7501, Organization :7503,
# SystemConfig :7509, Provisioner :7512 all running (see src/tools/dev_up.sh).
#
# Usage: bash src/tools/smoke_phase2.sh [gateway-base-url]

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

TENANT="p2_$((RANDOM % 90000 + 10000))"

# ---------------------------------------------------------------- [1] host
say 1 "Host admin signs in and provisions tenant '$TENANT'"
HT=$(curl -s -X POST "$GW/api/v1/auth/signin" -H 'TL-Tenant-Id: default' \
        -H 'Content-Type: application/json' \
        -d '{"usernameOrEmail":"admin","password":"Passw0rd!"}' | jget result.token)
check "host admin signin returns a JWT" "yes" "$([[ -n "$HT" ]] && echo yes || echo no)"
CREATE=$(curl -s -X POST "$GW/api/v1/tenants/create" -H 'TL-Tenant-Id: default' \
        -H "Authorization: Bearer $HT" -H 'Content-Type: application/json' \
        -d "{\"id\":\"$TENANT\",\"name\":\"Phase2 Bank\"}")
check "tenant create succeeds" "true" "$(echo "$CREATE" | jget success)"
APW=$(echo "$CREATE" | jget result.adminPassword)
check "one-time admin password returned" "yes" "$([[ -n "$APW" ]] && echo yes || echo no)"

sleep "$TTL_WAIT"

AT=$(curl -s -X POST "$GW/api/v1/auth/signin" -H "TL-Tenant-Id: $TENANT" \
        -H 'Content-Type: application/json' \
        -d "{\"usernameOrEmail\":\"admin\",\"password\":\"$APW\"}" | jget result.token)
check "tenant admin signin returns a JWT" "yes" "$([[ -n "$AT" ]] && echo yes || echo no)"
AUTH=(-H "TL-Tenant-Id: $TENANT" -H "Authorization: Bearer $AT")

# ------------------------------------------------------- [2] Organization
say 2 "Organization: office tree + staff seeded for the new tenant"
OFFICES=$(curl -s "${AUTH[@]}" "$GW/api/v1/offices/get-all")
check "head office exists" "yes" "$(echo "$OFFICES" | grep -qi 'head office' && echo yes || echo no)"
HEAD_ID=$(echo "$OFFICES" | jget result.0.id)
check "head office id resolved" "yes" "$([[ -n "$HEAD_ID" ]] && echo yes || echo no)"

BRANCH=$(curl -s -X POST "${AUTH[@]}" -H 'Content-Type: application/json' \
        "$GW/api/v1/offices/create" \
        -d "{\"name\":\"Smoke Branch\",\"parentId\":\"$HEAD_ID\",\"openingDate\":\"2024-01-01\"}")
check "branch office created" "true" "$(echo "$BRANCH" | jget success)"

STAFF=$(curl -s -X POST "${AUTH[@]}" -H 'Content-Type: application/json' \
        "$GW/api/v1/staff/create" \
        -d "{\"officeId\":\"$HEAD_ID\",\"firstname\":\"Sam\",\"lastname\":\"Smoke\",\"isLoanOfficer\":false}")
check "staff created" "true" "$(echo "$STAFF" | jget success)"

CCY=$(curl -s "${AUTH[@]}" "$GW/api/v1/currencies/get-all")
check "currencies endpoint reachable" "yes" "$([[ -n "$(echo "$CCY" | jget success)" ]] && echo yes || echo no)"

# ------------------------------------------------------- [3] SystemConfig
say 3 "SystemConfig: codes seeded for the new tenant"
CODES=$(curl -s "${AUTH[@]}" "$GW/api/v1/codes/get-all")
check "Gender code seeded" "yes" "$(echo "$CODES" | grep -qi '"codeName":"Gender"\|"Gender"' && echo yes || echo no)"
GENDER_ID=$(echo "$CODES" | python3 -c "import json,sys
d=json.load(sys.stdin)
items = d.get('result', d) if isinstance(d, dict) else d
for c in items:
    if c.get('codeName') == 'Gender':
        print(c.get('id')); break")
check "Gender code id resolved" "yes" "$([[ -n "$GENDER_ID" ]] && echo yes || echo no)"
VALUES=$(curl -s "${AUTH[@]}" "$GW/api/v1/codes/$GENDER_ID/codevalues/get-all")
check "Gender has seeded code values" "yes" "$([[ "$(echo "$VALUES" | python3 -c 'import json,sys
d=json.load(sys.stdin)
items = d.get("result", d) if isinstance(d, dict) else d
print(len(items) if isinstance(items, list) else 0)')" -gt 0 ]] && echo yes || echo no)"

say 4 "SystemConfig: configurations, hooks, businessdate, caches"
CFG=$(curl -s "${AUTH[@]}" "$GW/api/v1/configurations/get-all")
check "configurations reachable" "true" "$(echo "$CFG" | jget success)"
HOOK=$(curl -s -X POST "${AUTH[@]}" -H 'Content-Type: application/json' \
        "$GW/api/v1/hooks/create" \
        -d '{"name":"Web","displayName":"Smoke Hook","isActive":true}')
check "hook created" "true" "$(echo "$HOOK" | jget success)"
BDATE=$(curl -s "${AUTH[@]}" "$GW/api/v1/businessdate/get-all")
check "businessdate reachable" "true" "$(echo "$BDATE" | jget success)"
CACHE=$(curl -s "${AUTH[@]}" "$GW/api/v1/caches/get-all")
check "caches reachable" "true" "$(echo "$CACHE" | jget success)"

# --------------------------------------------------- [5] datatables engine
say 5 "Datatables engine: create, attach, query, update, teardown"
DT_NAME="smoke_extra_$((RANDOM % 9000))"
APPTABLE_ID="synthetic-entity-$((RANDOM % 9000))"

DT=$(curl -s -X POST "${AUTH[@]}" -H 'Content-Type: application/json' \
        "$GW/api/v1/datatables/create" \
        -d "{\"datatableName\":\"$DT_NAME\",\"apptableName\":\"m_client\",\"multiRow\":false,\"columns\":[{\"name\":\"favouriteColour\",\"type\":\"String\",\"mandatory\":false},{\"name\":\"riskScore\",\"type\":\"Number\",\"mandatory\":false}]}")
check "datatable created" "true" "$(echo "$DT" | jget success)"

DTLIST=$(curl -s "${AUTH[@]}" "$GW/api/v1/datatables/get-all")
check "datatable appears in get-all" "yes" "$(echo "$DTLIST" | grep -q "$DT_NAME" && echo yes || echo no)"

ENTRY=$(curl -s -X POST "${AUTH[@]}" -H 'Content-Type: application/json' \
        "$GW/api/v1/datatables/entries/$DT_NAME/$APPTABLE_ID" \
        -d '{"favouriteColour":"teal","riskScore":42}')
check "datatable entry created" "true" "$(echo "$ENTRY" | jget success)"

READBACK=$(curl -s "${AUTH[@]}" "$GW/api/v1/datatables/entries/$DT_NAME/$APPTABLE_ID")
check "entry surfaces favouriteColour=teal" "yes" "$(echo "$READBACK" | grep -q 'teal' && echo yes || echo no)"

UPDATED=$(curl -s -X PUT "${AUTH[@]}" -H 'Content-Type: application/json' \
        "$GW/api/v1/datatables/entries/$DT_NAME/$APPTABLE_ID" \
        -d '{"favouriteColour":"crimson"}')
check "datatable entry updated" "true" "$(echo "$UPDATED" | jget success)"
READBACK2=$(curl -s "${AUTH[@]}" "$GW/api/v1/datatables/entries/$DT_NAME/$APPTABLE_ID")
check "entry now surfaces favouriteColour=crimson" "yes" "$(echo "$READBACK2" | grep -q 'crimson' && echo yes || echo no)"

DEL_ENTRY=$(curl -s -X DELETE "${AUTH[@]}" "$GW/api/v1/datatables/entries/$DT_NAME/$APPTABLE_ID")
check "datatable entry deleted" "true" "$(echo "$DEL_ENTRY" | jget success)"
DEL_DT=$(curl -s -X DELETE "${AUTH[@]}" "$GW/api/v1/datatables/delete/$DT_NAME")
check "datatable dropped" "true" "$(echo "$DEL_DT" | jget success)"

# ----------------------------------------------- [6] generic entity: notes
say 6 "Generic entity notes (attach + read back against the same synthetic entity)"
NOTE=$(curl -s -X POST "${AUTH[@]}" -H 'Content-Type: application/json' \
        "$GW/api/v1/entity-notes/clients/$APPTABLE_ID/create" \
        -d '{"note":"Smoke test note"}')
check "note created" "true" "$(echo "$NOTE" | jget success)"
NOTES=$(curl -s "${AUTH[@]}" "$GW/api/v1/entity-notes/clients/$APPTABLE_ID/get-all")
check "note surfaces in list" "yes" "$(echo "$NOTES" | grep -q 'Smoke test note' && echo yes || echo no)"

# --------------------------------------------------------- [7] tear down
say 7 "Close the tenant"
CLOSE=$(curl -s -X POST "$GW/api/v1/tenants/close/$TENANT" -H 'TL-Tenant-Id: default' \
        -H "Authorization: Bearer $HT" | jget result.status)
check "tenant closed" "CLOSED" "$CLOSE"

printf '\n== Result: %d passed, %d failed ==\n' "$PASS" "$FAIL"
[[ "$FAIL" -eq 0 ]]
