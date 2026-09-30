# Turbo Ledger

Multi-tenant core banking platform — C++20 / [Drogon](https://github.com/drogonframework/drogon) microservices, PostgreSQL (schema-per-tenant), Redis. Functionally inspired by [Apache Fineract](https://demo.mifos.io/api-docs/apiLive.htm), extended with modern banking capabilities (instant payments, open banking, cards, webhooks, KYC/AML).

📋 **Plan:** [`src/docs/IMPLEMENTATION_PLAN.md`](src/docs/IMPLEMENTATION_PLAN.md) · **Endpoint inventory:** [`src/docs/ENDPOINT_INVENTORY.md`](src/docs/ENDPOINT_INVENTORY.md) (871 endpoints mapped to owning services)

## Architecture (Phase 0)

```
                        ┌──────────────────────────────┐
  client ── TL-Tenant-Id ─▶│  ApiGateway :7499            │
           Bearer JWT      │  tenant resolve · authN ·    │
           Idempotency-Key │  rate limit · idempotency ·  │
                        │  request-id · CORS           │
                        └───────┬──────────────────────┘
                 signed TL-Context (HMAC, 60s TTL)
                    ┌───────────┴───────────┐
                    ▼                       ▼
             Identity :7500          Accounting :7501     ... (see port map in plan)
             users/roles/JWT         GL/journals (stubs)
                    │                       │
             TlIdentity DB           TlAccounting DB
             t_<tenant> schemas      t_<tenant> schemas
```

Cross-cutting code lives in **`src/libs/turbo`** (libturbo): response envelope, tenant `RequestContext`, HMAC-signed context codec, exact-decimal `Money`, Fineract-style pagination, tenant-scoped transactions (`SET LOCAL search_path`), transactional outbox, `/health`, `TrustedContextFilter`.

## Build

Requires: g++ ≥ 11, CMake ≥ 3.16, Drogon 1.9.x (with jsoncpp, OpenSSL, libpq, hiredis, libuuid, zlib).

```bash
cmake -B build -G Ninja -DTL_SERVICES="Identity;Accounting;ApiGateway"
cmake --build build -j
ctest --test-dir build --output-on-failure   # libturbo unit tests
python3 src/tools/check_coroutines.py        # CI lint: every Task<> must co_return
```

## Run (dev)

```bash
# Docker route
docker compose -f docker-compose.dev.yml up --build

# Bare-metal route (postgres/redis on PATH)
src/tools/dev_up.sh
```

Apply per-tenant migrations (schema `t_<tenant>` per service DB):

```bash
python3 src/tools/migrate.py --service Identity --tenant default \
  --database-url postgresql://postgres:postgres@127.0.0.1:5432/TlIdentity
```

Smoke test through the gateway:

```bash
curl http://127.0.0.1:7499/health
TOKEN=$(curl -s -X POST http://127.0.0.1:7499/api/v1/auth/signin \
  -H 'TL-Tenant-Id: default' -H 'Content-Type: application/json' \
  -d '{"usernameOrEmail":"admin","password":"..."}' | jq -r .result.token)
curl http://127.0.0.1:7499/api/v1/accounting/gl-accounts/get-all \
  -H 'TL-Tenant-Id: default' -H "Authorization: Bearer $TOKEN"
```

## Repo layout

```
CMakeLists.txt              superbuild (libturbo + selected services)
cmake/TurboExternalDeps.cmake  Bcrypt/jwt-cpp resolution (submodule or FetchContent)
docker/                     service Dockerfile + db init
src/libs/turbo/             shared platform library + unit tests
src/services/<Service>/     one Drogon app per bounded context
src/services/<Service>/migrations/  V###__*.sql (per-tenant, run by migrate.py)
src/tools/                  migrate.py · gen_baselines.py · pgdmp_schema.py ·
                            check_coroutines.py · dev_up.sh
src/docs/                   implementation plan · endpoint inventory · Fineract collection
```

## Conventions (enforced from Phase 0)

- **Tenancy:** every request carries `TL-Tenant-Id`; services trust only the gateway-signed `TL-Context` header; all SQL runs in tenant-scoped transactions.
- **Money:** `turbo::Money` (int64 micro-units, banker's rounding) — never floats.
- **Coroutines:** every `Task<...>` handler must `co_return` (CI lint).
- **Mutations:** command-style endpoints (`?command=approve`), audit + outbox event in the same transaction (full rollout in Phases 1–3).
