#!/usr/bin/env bash
#
# Turbo Ledger — local dev bootstrap (no Docker needed).
#
# Prereqs: postgres + redis binaries on PATH (or set $PG_BIN), built repo
# (cmake -B build && cmake --build build), psql.
#
# Usage:  src/tools/dev_up.sh [PGDATA_DIR]
#
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
PGDATA="${1:-$HOME/pgdata-tl}"
PG_BIN="${PG_BIN:-}"
PSQL="${PG_BIN:+$PG_BIN/}psql"

echo "==> Postgres cluster: $PGDATA"
if [ ! -f "$PGDATA/PG_VERSION" ]; then
    "${PG_BIN:+$PG_BIN/}initdb" -D "$PGDATA" -U postgres --auth=trust -E UTF8
fi
"${PG_BIN:+$PG_BIN/}pg_ctl" -D "$PGDATA" -l "$PGDATA/server.log" \
    -o "-p 5432 -c listen_addresses=127.0.0.1" start || true

echo "==> Databases"
for db in TlIdentity TlAccounting; do
    "${PG_BIN:+$PG_BIN/}createdb" -h 127.0.0.1 -U postgres "$db" 2>/dev/null || true
done

echo "==> Legacy (public schema) baselines for not-yet-tenantised services"
$PSQL -h 127.0.0.1 -U postgres -d TlIdentity  -v ON_ERROR_STOP=1 -q \
    -f "$REPO_ROOT/src/services/Identity/migrations/V001__baseline.sql" 2>/dev/null || true
$PSQL -h 127.0.0.1 -U postgres -d TlAccounting -v ON_ERROR_STOP=1 -q \
    -f "$REPO_ROOT/src/services/Accounting/migrations/V001__baseline.sql" 2>/dev/null || true

echo "==> Per-tenant schemas (default, demo_bank)"
PSQL="$PSQL" python3 "$REPO_ROOT/src/tools/migrate.py" --service Identity \
    --tenant default --tenant demo_bank \
    --database-url "postgresql://postgres@127.0.0.1:5432/TlIdentity"
PSQL="$PSQL" python3 "$REPO_ROOT/src/tools/migrate.py" --service Accounting \
    --tenant default --tenant demo_bank \
    --database-url "postgresql://postgres@127.0.0.1:5432/TlAccounting"

echo "==> Redis"
(redis-server --port 6379 --save '' --appendonly no --daemonize yes) || true

echo "==> Services (run each from its rundir so ../config.json resolves)"
for svc in Identity Accounting ApiGateway; do
    mkdir -p "$REPO_ROOT/src/services/$svc/rundir"
    (cd "$REPO_ROOT/src/services/$svc/rundir" && \
        nohup "$REPO_ROOT/build/src/services/$svc/$svc" > "$svc.log" 2>&1 &)
    echo "    $svc started"
done

sleep 2
echo "==> Health"
curl -s http://127.0.0.1:7499/health || true
echo
echo "Gateway: http://127.0.0.1:7499  (send TL-Tenant-Id: default)"
