# Local development with CLion + Postman (Phase 0)

Gets Identity, Accounting and the ApiGateway running from CLion, with
PostgreSQL/Redis local, and the Phase 0 Postman collection passing.

---

## 1. Install prerequisites

**macOS (Homebrew):**
```bash
brew install cmake ninja drogon openssl@3 jsoncpp hiredis libpq postgresql@16 redis
brew services start postgresql@16     # or use Postgres.app
brew services start redis
```

**Ubuntu/Debian:**
```bash
sudo apt install g++ cmake ninja-build libjsoncpp-dev uuid-dev zlib1g-dev \
     libssl-dev libhiredis-dev libpq-dev postgresql redis-server
# Drogon is not packaged — build once from source:
git clone --depth 1 --branch v1.9.8 --recurse-submodules https://github.com/drogonframework/drogon
cmake -S drogon -B drogon/build -DBUILD_EXAMPLES=OFF -DBUILD_CTL=OFF -DBUILD_TESTING=OFF
cmake --build drogon/build -j && sudo cmake --install drogon/build
```

> Bcrypt and jwt-cpp are fetched automatically at CMake configure time
> (`cmake/TurboExternalDeps.cmake`) — nothing to install for those.

## 2. Open in CLion

1. **File ▸ Open** the repository root (it contains the superbuild `CMakeLists.txt`).
2. **Settings ▸ Build, Execution, Deployment ▸ CMake** — in the active profile set *CMake options*:
   ```
   -G Ninja -DTL_SERVICES="Identity;Accounting;ApiGateway"
   ```
   macOS only (Homebrew keg-only OpenSSL), append:
   ```
   -DCMAKE_PREFIX_PATH="$(brew --prefix);$(brew --prefix openssl@3);$(brew --prefix libpq)"
   ```
3. Reload CMake. You get four targets: **Identity**, **Accounting**, **ApiGateway**, **turbo_tests**.

### Run configurations — set the working directory (important!)

Every service loads `../config.json` **relative to its working directory**.
For each of the three run configurations (Run ▸ Edit Configurations…):

| Target     | Working directory                                  |
|------------|----------------------------------------------------|
| Identity   | `$PROJECT_DIR$/src/services/Identity/rundir`       |
| Accounting | `$PROJECT_DIR$/src/services/Accounting/rundir`     |
| ApiGateway | `$PROJECT_DIR$/src/services/ApiGateway/rundir`     |

Create the folders once: `mkdir -p src/services/{Identity,Accounting,ApiGateway}/rundir`

(You can also create a *Compound* run configuration that launches all three.)

## 3. Database & seed data

```bash
createdb -U postgres TlIdentity
createdb -U postgres TlAccounting

# legacy public-schema tables (Identity/Accounting are tenantised in Phase 1):
psql -U postgres -d TlIdentity  -v ON_ERROR_STOP=1 -f src/services/Identity/migrations/V001__baseline.sql
psql -U postgres -d TlAccounting -v ON_ERROR_STOP=1 -f src/services/Accounting/migrations/V001__baseline.sql

# per-tenant schemas via the migration runner:
python3 src/tools/migrate.py --service Identity   --tenant default --tenant demo_bank \
    --database-url postgresql://postgres@127.0.0.1:5432/TlIdentity
python3 src/tools/migrate.py --service Accounting --tenant default --tenant demo_bank \
    --database-url postgresql://postgres@127.0.0.1:5432/TlAccounting
```

Seed the demo login (`admin` / `Passw0rd!` — the hash below IS `Passw0rd!`):

```bash
psql -U postgres -d TlIdentity -c "
INSERT INTO public.users (first_name, last_name, email, username, password_hash,
                          is_active, is_locked_out, business_id)
VALUES ('Demo','Admin','admin@turboledger.dev','admin',
        '\$2b\$10\$yGcJpfi3iuRGCispo6.Ca.d97.7j0RnpIkNSSlMRc3smblfAP1m6C',
        true, false, NULL);"
```

If your local Postgres user/password differ from `postgres`/`postgres`, edit
`db_clients` in `src/services/Identity/config.json` and
`src/services/Accounting/config.json`.

## 4. Start & verify

Run **Identity**, **Accounting**, **ApiGateway** from CLion (ports 7500, 7501, 7499).

```bash
curl http://127.0.0.1:7499/health        # both services must report UP
src/tools/smoke_test.sh                  # 14-check acceptance suite
```

## 5. Test from Postman

1. **Import ▸** `src/docs/TurboLedger-Phase0.postman_collection.json`.
2. Run **03 Sign in** — its test script stores the JWT into `{{token}}` automatically.
3. Run the rest (or the whole collection via the Collection Runner):

| Request | Expected |
|---|---|
| 01 Gateway health | 200, identity+accounting `UP` |
| 02 Route table | 200, list of routes |
| 03 Sign in | 200, JWT captured |
| 04 GL accounts list | **501** structured stub (implemented in Phase 3) + `X-Request-Id` header |
| 05 Create GL account ×2 | 2nd send returns `Idempotency-Replayed: true` |
| N1–N6 negative tests | 400 / 404 / 403 / 401 / 401 / 401 |

Every request needs the `TL-Tenant-Id` header (collection variable `tenant`,
default `default`) — that is the multi-tenancy contract from the plan.

## Troubleshooting

- **"Failed to load config file"** → the run configuration's working directory
  is wrong (see the table above).
- **Signin 500 / DB errors** → check Postgres credentials in the service
  `config.json`; confirm `TlIdentity` has the `users` table.
- **Gateway 502 upstream unavailable** → Identity/Accounting not running, or
  ports differ from `src/services/ApiGateway/config.json`'s `services` map.
- **401 "Invalid TL-Context"** on direct service calls → expected; go through
  the gateway (only it can mint the signed context).
- **Redis warnings at startup** → harmless in Phase 0; start Redis to silence.
