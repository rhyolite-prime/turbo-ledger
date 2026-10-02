#!/usr/bin/env bash
#
# bootstrap_toolchain.sh — best-effort recipe for standing up a full build +
# runtime toolchain for turbo-ledger in a bare sandbox that has NO working
# apt/package-manager network access (only github.com / codeload.github.com /
# pypi.org-style HTTPS egress is reachable — plain HTTP, and HTTPS to
# deb.debian.org / apt.postgresql.org, are both unreachable in that
# environment). If your environment *does* have working apt, just
# `apt-get install postgresql postgresql-contrib libhiredis-dev cmake ninja-build
# libssl-dev libjsoncpp-dev uuid-dev` instead and skip straight to the Drogon
# step (with -DBUILD_REDIS=ON -DBUILD_POSTGRESQL=ON).
#
# This script is a *captured recipe*, assembled from what actually worked in
# an earlier session of this project, re-typed for repeatability. It has NOT
# been re-run end-to-end in one shot in this exact form — treat it as a very
# strong starting point / checklist, not a guaranteed one-command installer.
# Run it section by section and sanity-check each step before moving on.
#
# Everything is installed under $HOME/.toolchain so it's trivially removable
# and clearly separated from system paths. Nothing here is persisted by the
# sandbox's snapshot mechanism across a container reset (only files under the
# git-tracked workspace are) — if the sandbox resets, re-run this script.

set -euo pipefail

TOOLCHAIN_DIR="${TOOLCHAIN_DIR:-$HOME/.toolchain}"
JOBS="${JOBS:-$(nproc)}"
mkdir -p "$TOOLCHAIN_DIR"/{src,build,bin,lib,include}

echo "=== 0. cmake/ninja via pip (no apt needed) ==="
python3 -m venv "$TOOLCHAIN_DIR/venv" || true
# shellcheck disable=SC1091
source "$TOOLCHAIN_DIR/venv/bin/activate"
pip install --upgrade pip
pip install cmake ninja bcrypt psycopg2-binary
# Make cmake/ninja discoverable without re-activating the venv every shell:
ln -sf "$TOOLCHAIN_DIR/venv/bin/cmake" "$TOOLCHAIN_DIR/bin/cmake"
ln -sf "$TOOLCHAIN_DIR/venv/bin/ninja" "$TOOLCHAIN_DIR/bin/ninja"

cat > "$TOOLCHAIN_DIR/env.sh" <<EOF
# source this before any build/psql/toolchain-binary command.
export TOOLCHAIN_DIR="$TOOLCHAIN_DIR"
export PATH="\$TOOLCHAIN_DIR/bin:\$TOOLCHAIN_DIR/pg/bin:\$PATH"
export LD_LIBRARY_PATH="\$TOOLCHAIN_DIR/lib:\$TOOLCHAIN_DIR/pg/lib:\${LD_LIBRARY_PATH:-}"
export PKG_CONFIG_PATH="\$TOOLCHAIN_DIR/lib/pkgconfig:\${PKG_CONFIG_PATH:-}"
export PGDATA="\$TOOLCHAIN_DIR/pgdata"
export PGHOST=127.0.0.1
export PGPORT=5432
export PGUSER=postgres
EOF
echo "Wrote $TOOLCHAIN_DIR/env.sh — 'source ~/.toolchain/env.sh' in every new shell."
# shellcheck disable=SC1090
source "$TOOLCHAIN_DIR/env.sh"

echo "=== 1. OpenSSL (system ships libssl.so.3 runtime but no headers/libssl-dev) ==="
cd "$TOOLCHAIN_DIR/src"
[ -d openssl ] || git clone --depth 1 --branch openssl-3.2.6 https://github.com/openssl/openssl.git
cd openssl
./Configure --prefix="$TOOLCHAIN_DIR" --openssldir="$TOOLCHAIN_DIR/ssl" shared
make -j"$JOBS"
make install_sw   # skip install_docs/install_ssldirs — much faster

echo "=== 2. jsoncpp (pin 1.9.5 — Drogon's FindJsoncpp.cmake does a lexicographic"
echo "    version compare against '1.7' and spuriously rejects 1.10.x) ==="
cd "$TOOLCHAIN_DIR/src"
[ -d jsoncpp ] || git clone --depth 1 --branch 1.9.5 https://github.com/open-source-parsers/jsoncpp.git
cmake -S jsoncpp -B "$TOOLCHAIN_DIR/build/jsoncpp" -G Ninja \
  -DCMAKE_INSTALL_PREFIX="$TOOLCHAIN_DIR" -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF -DJSONCPP_WITH_TESTS=OFF
cmake --build "$TOOLCHAIN_DIR/build/jsoncpp" -j"$JOBS"
cmake --install "$TOOLCHAIN_DIR/build/jsoncpp"

echo "=== 3. libuuid header (system has libuuid.so.1 runtime, no uuid.h) ==="
cd "$TOOLCHAIN_DIR/src"
[ -d util-linux ] || git clone --depth 1 --branch v2.39 https://github.com/util-linux/util-linux.git
mkdir -p "$TOOLCHAIN_DIR/include/uuid"
cp util-linux/libuuid/src/uuid.h "$TOOLCHAIN_DIR/include/uuid/uuid.h"
# Point the linker at the system runtime lib by name; no .so symlink needed
# if the system package already provides libuuid.so.1 (confirm with
# `ldconfig -p | grep libuuid`). If it's missing entirely, build libuuid from
# the same util-linux checkout instead (./autogen.sh && ./configure
# --disable-all-programs --enable-libuuid && make && make install).

echo "=== 4. hiredis (needed for Drogon's Redis nosql client — used by"
echo "    HeartBeat-style job scheduling / rate limiting if/when added) ==="
cd "$TOOLCHAIN_DIR/src"
[ -d hiredis ] || git clone --depth 1 --branch v1.5.0 https://github.com/redis/hiredis.git
cmake -S hiredis -B "$TOOLCHAIN_DIR/build/hiredis" -G Ninja \
  -DCMAKE_INSTALL_PREFIX="$TOOLCHAIN_DIR" -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_SSL=OFF -DBUILD_SHARED_LIBS=OFF -DDISABLE_TESTS=ON
cmake --build "$TOOLCHAIN_DIR/build/hiredis" -j"$JOBS"
cmake --install "$TOOLCHAIN_DIR/build/hiredis"

echo "=== 5. PostgreSQL 16 server + libpq (client headers for Drogon's postgres"
echo "    driver) — built from source since apt.postgresql.org is unreachable ==="
cd "$TOOLCHAIN_DIR/src"
[ -d postgres ] || git clone --depth 1 --branch REL_16_STABLE https://github.com/postgres/postgres.git
cd postgres
./configure --prefix="$TOOLCHAIN_DIR/pg" --without-icu
make -j"$JOBS"
make install
# Initialize + start a local cluster:
if [ ! -s "$PGDATA/PG_VERSION" ]; then
  "$TOOLCHAIN_DIR/pg/bin/initdb" -D "$PGDATA" -U postgres
fi
"$TOOLCHAIN_DIR/pg/bin/pg_ctl" -D "$PGDATA" -l "$TOOLCHAIN_DIR/pg/logfile" \
  -o "-h 127.0.0.1 -p 5432" start || true
sleep 2
"$TOOLCHAIN_DIR/pg/bin/pg_isready" -h 127.0.0.1 -p 5432

echo "=== 6. Create the per-service databases ==="
# See docker/initdb/01-create-databases.sql for the authoritative list — keep
# this in sync with it.
for db in TlIdentity TlAccounting TlOrganizationDb TlSystemConfigDb TlCustomerDb \
          TlDamDb TlPortfolioDb TlGroupDb TlTellerDb TlHeartBeatDb TlTemplateDb \
          TlNotificationDb TlSelfServiceDb TlInteroperationDb TlProvisioner; do
  "$TOOLCHAIN_DIR/pg/bin/createdb" -h 127.0.0.1 -U postgres "$db" 2>/dev/null || true
done

echo "=== 7. Drogon (built against the above — enables both Postgres AND Redis" 
echo "    nosql clients, unlike the Phase 8 DB-less build) ==="
cd "$TOOLCHAIN_DIR/src"
[ -d drogon ] || git clone --recurse-submodules --depth 1 --branch v1.9.8 https://github.com/drogonframework/drogon.git
cmake -S drogon -B "$TOOLCHAIN_DIR/build/drogon" -G Ninja \
  -DCMAKE_INSTALL_PREFIX="$TOOLCHAIN_DIR" -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="$TOOLCHAIN_DIR" \
  -DBUILD_POSTGRESQL=ON -DBUILD_MYSQL=OFF -DBUILD_SQLITE=OFF -DBUILD_REDIS=ON \
  -DBUILD_EXAMPLES=OFF -DBUILD_CTL=ON
cmake --build "$TOOLCHAIN_DIR/build/drogon" -j"$JOBS"
cmake --install "$TOOLCHAIN_DIR/build/drogon"
# Sanity check: cmake's configure-step log for turbo-ledger itself should say
# "Found Hiredis" and "Found PostgreSQL" once this is done.

echo "=== 8. Build turbo-ledger itself ==="
TL_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cmake -S "$TL_ROOT" -B "$TL_ROOT/build" -G Ninja \
  -DCMAKE_PREFIX_PATH="$TOOLCHAIN_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$TL_ROOT/build" -j"$JOBS"

echo "=== 9. Run migrations per service (see src/tools/migrate.py) ==="
echo "Example:"
echo "  python3 $TL_ROOT/src/tools/migrate.py --service Identity --tenant default \\"
echo "      --database-url postgresql://postgres@127.0.0.1:5432/TlIdentity"
echo "(repeat for every service in the list above — Provisioner self-initializes"
echo " its schema at runtime and does NOT need migrate.py)"

echo "=== 10. Bootstrap a first admin user (no committed seed script exists yet —"
echo "    see IMPLEMENTATION_PLAN.md Phase 9 'admin-user seed' gap note) ==="
cat <<'PYEOF'
python3 - <<'PY'
import bcrypt
print(bcrypt.hashpw(b"password", bcrypt.gensalt()).decode())
PY
# Then manually INSERT a row into TlIdentity's tenant-schema users table with
# that hash, and grant it the "Super user" role — see IMPLEMENTATION_PLAN.md
# for the exact table/column names as they exist in this codebase.
PYEOF

echo "=== Done (if every step above succeeded). Start services from each"
echo "service's own rundir, e.g.:"
echo "  cd $TL_ROOT/src/services/Identity/rundir && $TL_ROOT/build/src/services/Identity/Identity &"
echo "Repeat per service, then the gateway last (it depends_on every upstream"
echo "being reachable to serve well, though it will still start without them)."
