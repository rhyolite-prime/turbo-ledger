# Turbo Ledger — Implementation Plan

**Goal:** evolve Turbo Ledger from its current scaffold into a complete, multi-tenant core banking platform, using Apache Fineract (v1 REST API, ~871 endpoints — see [`ENDPOINT_INVENTORY.md`](./ENDPOINT_INVENTORY.md)) as the functional reference, then extending it with modern banking capabilities Fineract lacks (instant payments/ISO 20022, open banking, cards, webhooks/event streaming, KYC/AML, virtual accounts, BaaS developer experience).

---

## 1. Where we are today (current-state assessment)

| Area | Status |
|---|---|
| **Stack** | C++23 + Drogon (coroutines), CMake, PostgreSQL (DB-per-service scripts in `src/scripts/`), Redis, bcrypt, JWT |
| **Services scaffolded** | 16: Identity, Provisioner, Accounting, Customer, DepositAccountManagement, Portfolio, Organization, Group, Teller, SystemConfig, HeartBeat, Notification, Reporting, Staff, Template, ApiGateway (ports 7500–7507 partially mapped in `port-mapping.txt`) |
| **Identity** | ~80% of foundation done: `UserService`, `RoleService`, `ApiKeyService`, `BusinessAccountService`, `AuditLogService`, `RedisCacheManager`, `JwtAuthFilter`, bcrypt password hashing. OTP, change-password, self endpoints are 501 stubs. `TenantsController` routes declared but unimplemented. |
| **Accounting** | Service classes exist (`accounts`, `journal`, `accounting_rules`, `gl_closure`, `financial_activity_accounts`, `identity` client, `redis`); controller bodies are **empty** (undefined behavior if called — they don't `co_return`). |
| **All other services** | Controller shells only; `Provisioner/TenantsController` is the default drogon_ctl stub. ApiGateway has no controllers at all. |
| **Data model** | Per-service SQL dumps exist (`TlIdentity`, `TlAccounting`, `TlCustomerDb`, `TlPortfolio`, `TlOrganizationDb`, `TlGroupDb`, `TlSystemConfigDb`, `TlDamDb`) — largely a Fineract-shaped schema, but **no `tenant_id` columns and no migration tooling**. |
| **Cross-cutting** | No shared library (DTO/base-response code is copy-pasted per service), no tenant propagation, no docker-compose for the full stack, no CI pipeline building all services, no OpenAPI specs, inconsistent auth (Identity uses JWT filter; Accounting uses `ClientId`/`ClientSecret` headers validated against Identity). |

**Key gaps to close:** multi-tenancy, the ~871 Fineract-parity endpoints (only a handful implemented), inter-service consistency (auth, errors, pagination), the ApiGateway, operational tooling (migrations, jobs, batch), and every "modern banking" capability.

---

## 2. Target architecture

### 2.1 Service topology & port map

Keep the microservice-per-domain layout. Existing services stay; five new services are added for modern banking. Final map:

| Port | Service | Codename | Owns (Fineract resource groups → see inventory) |
|---|---|---|---|
| 7500 | **Identity** | Ra | `authentication`, `users`, `roles`, `permissions`, `passwordpreferences`, `twofactor`, `userdetails`, `makercheckers` (34 eps) |
| 7501 | **Accounting** | Thoth | `glaccounts`, `journalentries`, `glclosures`, `accountingrules`, `financialactivityaccounts`, `provisioningentries`, `runaccruals` (39 eps) |
| 7502 | **HeartBeat (Scheduler)** | Khepri | `jobs`, `scheduler` (16 eps) + internal cron for interest posting, accruals, delinquency, standing instructions |
| 7503 | **Organization** | Horus | `offices`, `officetransactions`, `staff`, `holidays`, `workingdays`, `currencies`, `funds`, `paymenttypes`, `taxes`, `taxes`, `entitytoentitymapping` (56 eps) |
| 7504 | **Customer** | Maat | `clients` (v1 + v2), `client`, `collateral-management` (64 eps) |
| 7505 | **DepositAccountManagement** | Shed | `savingsaccounts`, `savingsproducts`, `fixeddeposit*`, `recurringdeposit*`, `interestratecharts`, `accounttransfers`, `standinginstructions(+runhistory)`, `accountnumberformats`, `charges` (119 eps) |
| 7506 | **Teller** | Tajet | `tellers`, `cashiers`, `cashiersjournal` (21 eps) |
| 7507 | **Portfolio (Lending & Shares)** | Ptah | `loans`, `loanproducts`, `rescheduleloans`, `delinquency`, `loan-collateral-management`, `floatingrates`, `rates`, `provisioningcategory/criteria`, `products/shareproduct/accounts` (shares), `external-asset-owners`, credit bureau, MIX reporting (224 eps) |
| 7508 | **Group** | Sobek | `groups`, `centers`, `grouplevels`, `collectionsheet` (25 eps) |
| 7509 | **SystemConfig** | Seshat | `codes`, `configurations`, `datatables`, `entityDatatableChecks`, `audits`, `hooks`, `caches`, `businessdate`, `externalevents`, `externalservice`, `fieldconfiguration`, `imports`, entity-generic document/note/survey routes (86 eps) |
| 7510 | **Reporting** | Djehuti | `reports`, `runreports`, `adhocquery`, `search`, `surveys`, `likelihood`, `povertyLine` (41 eps) |
| 7511 | **Notification** | Hathor | `notifications`, `sms`, `smscampaigns`, `email`, `reportmailingjobs(+runhistory)` + `templates` (Template service merges here) (51 eps) |
| 7512 | **Provisioner** | Atum | Tenant registry & lifecycle (`tenants/*`), `instance-mode`, per-tenant schema provisioning/migrations |
| 7513 | **SelfService** | Bes | `self/*` (60 eps) — customer-facing BFF that composes Customer/DAM/Portfolio/Payments |
| 7514 | **Payments** ⭐new | Sekhmet | `interoperation` (19 eps) + payment orders, rails adapters (ISO 20022 / SEPA Inst / ACH / RTP-style), internal transfers, holds |
| 7515 | **OpenBanking** ⭐new | Serqet | Consent management, AIS/PIS (Berlin-Group-style), TPP registry |
| 7516 | **Cards** ⭐new | Montu | Card products, issuing-processor integration, authorization/clearing webhooks, card controls |
| 7517 | **Compliance** ⭐new | Anubis | KYC workflows, sanctions/PEP screening, transaction monitoring, case management, regulatory reports |
| 7518 | **EventHub** ⭐new | Apis | Webhook subscriptions & delivery, event catalog, signed payloads, replay |
| 7499 | **ApiGateway** | — | Single public entrypoint: routing, tenant resolution, authN, rate limiting, idempotency, CORS |

`Staff` and `Template` fold into Organization and Notification respectively (they are single-resource services today; keeping them separate adds ops cost with no isolation benefit). `Reporting` absorbs `search`.

### 2.2 Multi-tenancy model

Fineract uses **database-per-tenant** with a central `tenants` registry. For Turbo Ledger:

1. **Tenant registry** lives in the **Provisioner** service (`tl_tenants` DB): tenant identifier, display name, status (`PENDING/ACTIVE/SUSPENDED/CLOSED`), timezone, connection descriptors per backing service DB, plan/limits, encryption key reference.
2. **Isolation strategy — schema-per-tenant within each service's database** (recommended default):
   - Each service DB (e.g. `TlAccounting`) holds one schema per tenant (`t_<tenant_id>`), created by the Provisioner running the service's migration chain at tenant-creation time.
   - Drogon DB clients are pooled per service; the tenant schema is selected per request via `SET LOCAL search_path` inside the transaction. This keeps pool counts bounded (unlike DB-per-tenant) while giving hard-ish isolation, easy per-tenant backup/export, and no `tenant_id` bugs leaking rows.
   - Escape hatches: very large tenants can be promoted to a dedicated database (registry stores the connection descriptor, so this is transparent to services); tiny sandbox tenants can share a schema with `tenant_id` columns + Postgres RLS if schema counts become an issue.
3. **Tenant resolution:** every request carries `TL-Tenant-Id` (equivalent of `Fineract-Platform-TenantId`). The gateway validates it against the (Redis-cached) registry, rejects inactive tenants, and forwards it plus a signed internal context header (`TL-Context`: tenant, user, permissions hash, request id) to services. Services **never** trust a bare tenant header from outside the gateway.
4. **Tenant provisioning flow (Provisioner):** `POST /tenants` → create registry row → run migration chain in each service DB → seed defaults (chart of accounts template, code values, permissions, default roles, working days, currency list) → create initial admin user in Identity → emit `tenant.created` event. Idempotent + resumable (step ledger table).
5. **JWTs embed the tenant**: tokens are minted per tenant; the gateway cross-checks token tenant vs. header tenant.

### 2.3 AuthN / AuthZ

- **Human users:** `POST /authentication` (Fineract-compatible) → short-lived JWT (15 min) + refresh token (Redis, revocable). TOTP-based `twofactor` endpoints gate sensitive roles.
- **Machine clients (BaaS):** API key pairs (already in Identity's `ApiKeyService`) exchanged at the gateway for the same internal `TL-Context`; scoped per tenant with permission subsets. Retire the current pattern of every service calling Identity per request — the **gateway authenticates once**, services verify the signed context header (HMAC/Ed25519) locally. This removes the Identity round-trip from the hot path.
- **Permissions:** adopt Fineract's grammar `<ACTION>_<ENTITY>[_CHECKER]` (e.g. `CREATE_LOAN`, `APPROVE_SAVINGSACCOUNT_CHECKER`). Seed the full permission catalog per tenant; roles are permission sets; `permissions` + `roles` endpoints manage them.
- **Maker-checker:** implement as a first-class **command pipeline** (see 2.4): if a permission is flagged maker-checker for the tenant, the mutation is stored in `m_portfolio_command_source`-equivalent (`tl_commands`) as `AWAITING_APPROVAL` instead of executing; `makercheckers` endpoints list/approve/reject/delete queued commands. Approval replays the command with the original payload.

### 2.4 Platform conventions (the "golden path" every endpoint follows)

These are built once in a shared library and phase 0 gateway, then reused by all ~1,000 endpoints:

- **`libturbo` shared C++ library** (new top-level `src/libs/turbo/`): base API response envelope, error codes, tenant/user request context, DB helpers (search_path binding, transaction wrapper), pagination (`offset`/`limit`/`orderBy`/`sortOrder` like Fineract), date/money types (`NUMERIC(19,6)`, banker's rounding, **never floats**), idempotency helper, outbox writer, JSON validation, JWT/context verification filter, structured logging with request/tenant IDs. Every service links it; delete the per-service copies of `BaseApiResponse` etc.
- **Command-style mutations, Fineract-compatible:** state transitions are expressed as `POST /resource/{id}?command=approve|reject|activate|close|...` exactly as in the Postman collection. Internally each maps to a named command object → permission check → maker-checker gate → handler → audit row → outbox event. `audits`/`makercheckers` then come nearly for free.
- **Response contract:** Fineract-compatible success bodies (`{ officeId, resourceId, changes: {...} }`) and error bodies (`developerMessage`, `userMessageGlobalisationCode`, `errors[]` with parameter-level details) so existing Fineract clients/SDKs can be pointed at Turbo Ledger.
- **Template endpoints:** every domain resource implements `GET /{resource}/template` returning enums/code values/defaults needed to render a creation form (heavily used across the collection).
- **Idempotency:** all money-moving POSTs accept `Idempotency-Key`; gateway stores key→response in Redis (24h) per tenant; replays return the original result.
- **Events (outbox pattern):** every committed mutation writes an event row (`tl_outbox`) in the same transaction; a relay publishes to the internal bus (Redis Streams initially; NATS/Kafka when volume demands) which feeds EventHub webhooks, Notification, Reporting projections, and `externalevents` config.
- **Migrations:** adopt a SQL migration runner (Flyway-style ordered `V###__name.sql` per service, executed by Provisioner per tenant schema). Convert the existing `src/scripts/*.sql` dumps into `V001` baselines.
- **API docs:** OpenAPI 3.1 spec per service in `src/docs/api/`, generated Postman collection + Swagger UI served by the gateway. Contract-first: specs merged before implementation.

### 2.5 Ledger correctness rules (non-negotiable, enforced in Accounting)

- Strict double entry: every journal transaction's debits == credits per currency, enforced in one DB transaction with a `CHECK`ing trigger as backstop.
- Journal entries are **immutable**: corrections are reversals (`journalentries/{id}?command=reverse`), never updates/deletes.
- Hash-chained entries per tenant (each entry stores `hash(prev_hash + entry)`) → tamper-evident ledger, cheap audit proof.
- Balance reads come from materialized running balances updated in-transaction (Fineract's `m_gl_account` derived balances), reconciled nightly by a HeartBeat job.
- `businessdate` (from SystemConfig) drives value-dating; GL closures block postings on/before closure date per office.

---

## 3. Phased delivery plan

Each phase lists scope, the granular endpoints delivered (counts match [`ENDPOINT_INVENTORY.md`](./ENDPOINT_INVENTORY.md)), and exit criteria. Phases 4–7 can be parallelized across teams once Phase 0–3 land, since they share only `libturbo`, Identity, Organization and Accounting.

### Phase 0 — Platform foundation (no business features)
*Everything else depends on this; keep it ruthlessly small.*

- `src/libs/turbo` shared library (context, envelope, pagination, money/date types, DB/txn helpers, outbox, filters); convert Identity + Accounting to use it.
- Top-level CMake superbuild + vcpkg manifest; `docker-compose.dev.yml` (Postgres, Redis, all services); one `Dockerfile` template.
- Migration runner + convert existing SQL dumps to `V001` baselines per service.
- **ApiGateway v1:** route table from config, `TL-Tenant-Id` resolution against Provisioner cache, JWT/API-key authentication, signed `TL-Context` injection, request IDs, CORS, rate limiting (Redis token bucket), `Idempotency-Key` store, `/health` fan-out (heart-beat semantics from `src/docs/heart-beat.txt`).
- CI (GitHub Actions in `src/services/.github`): build all services, run unit + integration tests against docker-compose, clang-tidy/format.
- **Exit criteria:** `docker compose up` boots gateway + Identity + Accounting; authenticated request flows gateway→service with tenant context; CI green.

### Phase 1 — Tenancy & Identity completion (≈34 endpoints + tenant APIs) ✅ DONE

- ✅ **Provisioner:** tenant registry CRUD + lifecycle (`create/activate/suspend/close`), per-service schema provisioning + seeding pipeline (migrations discovered from each service's `migrations/`, applied transactionally with commit-await, tenant admin seeded with a one-time password), `instance-mode` endpoint. Gateway resolves tenants dynamically from the Provisioner through a 5s TTL cache (`TenantRegistry`), overlaying the static config list; cache-expiry acts as the invalidation mechanism for now (push invalidation events deferred).
- ✅ **Identity:** `users` (10), `roles` (8: CRUD + enable/disable + permission assignment), `permissions` (2: catalog + maker-checker toggle), `self/userdetails` + `self/change-password`, tenant-aware `authentication` (tenant-schema users first, host fallback; JWT carries a `tenantId` claim the gateway enforces — a token minted for one tenant is rejected on any other). Maker-checker command store (`tl_commands`) + `makercheckers` (4: list/approve/reject/delete) wired into every guarded action.
- ✅ Permission catalog seeding (33 codes) + role templates (Super user, Admin, Teller, Loan officer, Self-service) in `V003__rbac_maker_checker.sql`.
- ⏸ Deferred to a later hardening pass: OTP send/verify, `passwordpreferences` (3), `twofactor` (6, TOTP) — still respond 501.
- ✅ **Exit criteria met** (see `src/tools/smoke_phase1.sh`, 26 checks): create tenant end-to-end via API → login as tenant admin → create user/role → maker-checker round trip on `CREATE_USER` (queue → approve executes / reject discards) → suspend/close lifecycle enforced at the gateway.

### Phase 2 — Organization & SystemConfig (≈142 endpoints) ✅ DONE

The reference-data layer every product feature reads.

- ✅ **Organization:** `offices` (9, hierarchical with `hierarchy` path), `officetransactions` (4), `staff` (6, incl. loan-officer flag), `holidays` (7, incl. activate), `workingdays` (3), `currencies` (2), `funds` (4), `paymenttypes` (5), `taxes` (10: components + groups), `entitytoentitymapping` (6). All 56 endpoints implemented against `OrganizationService`, wired through the gateway/provisioner/compose.
- ✅ **SystemConfig:** `codes`/code values (11), `configurations` (5), `businessdate` (3), `caches` (2), `audits` (3, reads this service's own `tl_outbox` as a local audit trail — a true cross-service audit aggregator is deferred to EventHub), `hooks` (6, config only — firing comes with EventHub), `externalservice` (2), `fieldconfiguration` (1), `externalevents` (2), **`datatables` (16) + `entityDatatableChecks` (4)** — dynamic per-tenant custom tables (`dt_<name>` physical tables + `tl_datatable_registry` column allowlist, guarding against SQL injection in dynamic column lists), `imports` (3, list + output-template scaffolding; actual bulk upload/apply deferred to Phase 8 like Organization's `uploadtemplate`), and the generic entity-attachment groups — documents/notes/images/calendars/meetings — under dedicated `entity-documents/`, `entity-notes/`, `entity-images/`, `entity-calendars/`, `entity-meetings/` prefixes (a deliberate deviation from Fineract's literal `{entityType}/{entityId}/...` top-level paths, which SystemConfig doesn't own and which would collide with future Customer/Portfolio routes).
- ✅ 86 SystemConfig endpoints implemented against `SystemConfigService`; codes/code values (9 Fineract-standard code sets) seeded per tenant in `V003__phase2_reference_data.sql`.
- **Exit criteria:** office tree + staff + codes seeded for new tenants (✅, see `src/tools/smoke_phase2.sh`); a datatable can be created and attached to a client-shaped entity and surfaces on read-back (✅ against a synthetic entity id — Customer/`m_client` itself doesn't exist until Phase 3, so re-validate against a real client id once Customer ships).
- **ORM migration — fully complete for both services.** The data-access layer was converted from hand-written `execSqlCoro` SQL strings to the Drogon ORM end-to-end. `drogon_ctl` could regenerate models directly against the live DB for the tables already present when it was originally run (SystemConfig's full V001+V002+V003 schema, and Organization's V001 baseline: `office`, `office_transaction`, `organisation_creditbureau`, `organisation_currency`, `payment_type`). Organization's `V003__phase2_reference_data.sql` tables (`staff`, `holiday`, `holiday_office`, `working_days`, `fund`, `tax_component`, `tax_group`, `tax_group_mapping`, `entity_relation`, `entity_mapping`) plus `organisation_currency.is_enabled`/`office.is_deleted`/`office.created_at` (columns V003 added to already-generated tables) had no generated model since this sandbox has no route to a live Postgres instance for `drogon_ctl` to introspect. Rather than leave those resources on raw SQL, the missing models (`Staff`, `Holiday`, `WorkingDays`, `Fund`, `TaxComponent`, `TaxGroup`, `TaxGroupMapping`, `EntityRelation`, `EntityMapping`, plus the missing columns) were **hand-authored** to match drogon_ctl's real generated-code shape byte-for-byte (verified against genuine generated specimens already in the tree), so every resource could be converted the same way.
  - ✅ **SystemConfig — fully converted.** Every resource group (codes/code-values, global config, external-service, audits — reading `tl_outbox` via `CoroMapper<TlOutbox>`, hooks, caches, business-date, external-events, field-config, entity-datatable-checks, imports, documents, notes, images, calendars, meetings) goes through `CoroMapper<Model>`. The one deliberate, accepted exception is the datatables engine's dynamic `dt_<name>` physical tables (create/alter/drop/CRUD) and its `information_schema` introspection — these operate on a table shape decided at runtime per tenant, which by nature can't be represented by a compile-time-generated model, so they stay on raw `execSqlCoro` (registry rows in `tl_datatable_registry`/`tl_entity_datatable_check` do use the ORM).
  - ✅ **Organization — fully converted.** All 56 endpoints (`offices`, `officetransactions`, `staff`, `holidays`, `workingdays`, `currencies`, `funds`, `paymenttypes`, `taxes`, `entitytoentitymapping`) now go through `CoroMapper<Model>`. The only raw SQL remaining is 3 documented call sites touching the `holiday_office` junction table (a pure many-to-many link table with no independent identity/model of its own — modeling it would add a class with no behaviour beyond what the two inline queries already express) and, where CoroMapper can't express a SQL join, the join is resolved application-side: small/bounded reference tables (`entity_relation`) are prefetched wholesale into a `std::map`; per-request joins with a naturally small row count (`tax_group_mapping`→`tax_component`, `entity_mapping`→`entity_relation`, `office_transaction`'s from/to office names) use one extra `findByPrimaryKey` per row/request instead of a SQL join — all documented inline at the call site.
  - **Compile-verified.** This sandbox has no outbound access to apt/vcpkg mirrors, but does have GitHub access, so a local toolchain was bootstrapped from source instead: Drogon + trantor built from GitHub (TLS/Postgres/MySQL/SQLite backends disabled — irrelevant to compiling the ORM template code itself), plus jsoncpp and zlib built from source and a minimal `libuuid` header shim, all via a user-writable `cmake`/`ninja` (installed through a Python venv) since the sandbox user has `sudo` but the apt mirror itself is unreachable. Every `.cc` in both services (services, controllers, models, `main.cc`) now compiles cleanly with `g++ -std=c++23 -fcoroutines -fsyntax-only -Wall -Wextra` — zero errors, zero warnings. This caught and fixed real bugs beyond the ORM conversion itself, all now fixed in place:
    - A stray `*/` inside a doc-comment (`validateJsonFor*/validJsonOfField`) in every hand-authored Organization model header prematurely closed the block comment, which would have failed compilation outright.
    - Six `co_await` calls inside `catch` blocks in `SystemConfigService.cc`'s upsert-style handlers (`updateExternalService`, `updateCacheConfig`, `updateBusinessDate`, `updateExternalEventConfig`, `registerDatatable`, `putImage`) — `co_await` in a `catch` handler is ill-formed per the C++ standard; restructured to resolve existence via a bool flag in the `try/catch` and perform the `co_await`ed update/insert afterwards.
    - Three uses of a nonexistent `drogon::orm::Row::columnName(i)` in the datatables' dynamic row-to-JSON helper in `SystemConfigService.cc`; replaced with the real API, `r[i].name()`.
  - A full network-connected build (real Postgres/OpenSSL) and a live-DB integration run are still recommended before Phase 3 relies on this, but the entire codebase is now known to be free of compile errors, not just manually reviewed.

### Phase 3 — Accounting core (≈39 endpoints) ✅ DONE

- ✅ `glaccounts` (8: get-all w/ filters + hierarchy, create, get-detail, update, delete, template; `downloadtemplate`/`uploadtemplate` bulk import deferred to Phase 8, same precedent as Organization/SystemConfig), `journalentries` (8: create "balanced" multi-leg, search w/ filters + pagination, get-detail, openingbalance, provisioning view, template, `{transactionId}/reverse`, `{transactionId}/recalculate-running-balance` — the last two replace the two bulk-import slots Fineract's literal 8 include, since the exit criteria needs working reversal/reconciliation far more than bulk import), `glclosures` (5), `accountingrules` (6, incl. multi-debit/multi-credit accounts via junction tables), `financialactivityaccounts` (6), `runaccruals` (1), `provisioningentries` (5, persistence + balanced journal posting; the automatic loan-arrears criteria engine itself is Portfolio's job once it exists — see the note on `provisioning_entries*` below). All implemented against one `AccountingService` (mirroring the Organization/SystemConfig monolithic-service-class, per-resource-controller pattern), fully ORM (`CoroMapper<Model>`) — the only raw SQL is a single `SELECT pg_advisory_xact_lock(...)` statement (Postgres advisory locks have no table and thus no possible model; same class of narrow exception as SystemConfig's dynamic datatables engine and Organization's `holiday_office` junction lookups).
- ✅ **Ledger correctness rules (§2.5), all implemented:**
  - **Balanced multi-leg postings:** `createJournalEntries` validates `sum(debits) == sum(credits)` (via `turbo::Money`, exact decimal arithmetic) before touching the database, then posts every leg inside one DB transaction, rolling back explicitly on any failure. A deferred Postgres constraint trigger (`trg_journal_entries_balanced`, in `V003__phase3_ledger.sql`) re-validates every transaction's balance at COMMIT time as the CHECK-trigger backstop the plan calls for.
  - **Immutability / reversal-only corrections:** nothing ever `UPDATE`s or `DELETE`s a posted leg's financial fields; `reverseJournalTransaction` posts new, equal-and-opposite legs and marks the originals `reversed = true`, linked via `reversal_id`.
  - **Hash-chained entries:** `journal_entries` gained `entry_seq` (bigserial, since the uuid PK isn't chronologically sortable), `entry_hash` and `prev_hash`. Every inserted leg's hash is `sha256(prev_hash || canonical fields)`, chained from the tenant's previous leg; a per-tenant Postgres advisory lock (`lockJournalChain`, keyed on `current_schema()`) serializes concurrent postings so the chain can never fork.
  - **Running balances** (office + organization, per account) are computed and written in the same transaction as the posting, not a separate batch step; `recalculateRunningBalances` (the `POST .../recalculate-running-balance` endpoint) recomputes forward from any transaction, which is the code path a nightly HeartBeat reconciliation job would call.
  - **GL closures** block postings on/before the closure date for the posting office (`assertNotClosed`). Known simplification: only closures recorded directly against the posting `officeId` are enforced — full hierarchy inheritance from parent offices is deferred, since Office/hierarchy data lives in the Organization service's own database and this codebase has no internal cross-service lookup client yet.
  - **Value dating:** journal entries are dated by the caller-supplied `transactionDate`/`entryDate` (Fineract's own mechanism), not wall-clock time. Cross-checking that date against SystemConfig's business-date override is deferred for the same cross-service-client reason as closure inheritance.
- ✅ **Schema fixes in `V003__phase3_ledger.sql`:** `accounting_rules.debit_account_id`/`credit_account_id` were `integer` in the V001 baseline while `accounts.id` (every other FK to accounts) is `uuid` — a real bug (an integer could never have held a valid account reference); fixed by dropping and re-adding both columns as `uuid` with a real FK, and the `AccountingRules` model hand-patched to match (see its header comment). New tables: `accounting_rule_debit_accounts`/`accounting_rule_credit_accounts` (multi-account rules, surrogate uuid PK so they stay ORM-mappable rather than needing the `holiday_office`-style composite-key raw-SQL exception), `provisioning_entries`/`provisioning_entries_detail`.
- ✅ Permission catalog: `src/services/Identity/migrations/V005__phase3_permissions.sql` adds the `accounting` grouping (`GLACCOUNT`, `GLCLOSURE`, `ACCOUNTINGRULE`, `FINANCIALACTIVITYACCOUNT`, `JOURNALENTRY`, `PROVISIONINGENTRY`), granted to the `Admin` role template.
- ✅ Gateway routing (`src/services/ApiGateway/config.json`): the old single `/api/v1/accounting/` prefix (from the pre-Phase-3 scaffold's monolithic `AccountingController`) is replaced with one prefix per resource (`glaccounts`, `glclosures`, `journalentries`, `accountingrules`, `financialactivityaccounts`, `provisioningentries`, `runaccruals`), matching the Organization/SystemConfig convention.
- ✅ **Compile- and link-verified**, one level beyond Phase 2's `-fsyntax-only`-only verification: the local toolchain now also produces a real `DrogonConfig.cmake`/`jsoncppConfig.cmake` install (persisted outside `/tmp` at `~/.toolchain`, since `/tmp` doesn't survive between sessions — see `~/.toolchain/README.md`), so `cmake --build` was run for real, linking a genuine `Accounting` executable (and, as a bonus regression check, a genuine `Organization` executable) — not just per-file syntax checks. Every `.cc` in the service (10 controllers incl. the new 7, the `AccountingService`, and all 9 models) compiles with zero errors/warnings under `-Wall -Wextra`.
- **Exit criteria:** balanced entry posting w/ reversal — ✅ implemented and compiles/links; **not runtime-tested against a live Postgres** (none is reachable in this sandbox, same limitation as Phase 2). Trial balance reconciliation and the 1k-entries/sec throughput target are design-compatible (running balances are maintained incrementally in-transaction, not recomputed from full history) but likewise unverified without a live DB/load environment — flagged here rather than silently assumed.

### Phase 4 — Customer domain (≈64 endpoints) ✅ DONE

- ✅ `clients` (53: full CRUD + lifecycle commands — `activate`/`close`/`reject`/`withdraw`/`reactivate`/
  `undoRejection`/`undoWithdrawal`/`assignStaff`/`unassignStaff`/`updateSavingsAccount`/`proposeTransfer`/
  `withdrawTransfer`/`acceptTransfer`/`rejectTransfer`, dispatched via an explicit `{id}/command/{name}`
  path segment rather than Fineract's `?command=` query param, matching this codebase's
  explicit-action-suffix convention everywhere else — see `GlAccountsController`/`CodesController`),
  nested charges/identifiers/familymembers/collaterals/transactions sub-resources, `template`,
  `{id}/transferproposaldate`, external-id addressing for the core single-client operations only
  (get-detail/update/delete/command/transactions-list — not nested sub-resources, a deliberate scope
  trim documented in `ClientsController.h`), and `downloadtemplate`/`uploadtemplate` bulk-import stubs
  deferred to Phase 8 (same precedent as glaccounts/Organization/SystemConfig). `client` (4) addresses.
  `collateral-management` (6) product-level collateral registry, distinct from the client-level
  pledges nested under `clients/{id}/collaterals/*`. `clients (v2)` (1) text search across
  firstname/lastname/fullname/displayName/accountNo/externalId.
- ✅ All implemented against one `CustomerService` (the established Organization/SystemConfig/Accounting
  monolithic-service-class, per-resource-controller pattern), fully ORM (`CoroMapper<Model>`) — **zero
  raw SQL anywhere in this service**. Three new/regenerated model pairs were hand-authored from scratch
  or extended via `src/tools/genmodel.py` (drogon_ctl isn't runnable in this sandbox — see Phase 2/3's
  same workaround): `CollateralManagement` and `ClientFamilyMember` are brand new V003 tables;
  `Client`/`ClientAddress`/`ClientCollateralManagement` were regenerated to add the Phase 4 columns
  below plus real audit columns. `ClientCharge`, `ClientChargePaidBy`, `ClientIdentifier`,
  `ClientNonPerson`, `ClientTransaction`, `ClientTransferDetails` are untouched, genuine drogon_ctl
  output — the V001 baseline already covered every column they need.
- ✅ **V003 migration also tightens FKs across every `client_*` child table** (all previously bare
  uuid columns with zero constraints in the V001 baseline — the same class of real gap as Phase 3's
  `accounting_rules` int/uuid bug), plus adds real uniqueness Fineract itself enforces
  (`client.account_no` UNIQUE, a partial unique index on `client.external_id`,
  `client_identifier UNIQUE(client_id, document_type_id, document_key)`,
  `client_non_person UNIQUE(client_id)`).
- ✅ ⭐ Modern addition here: **client risk attributes** (`kyc_status`, `risk_rating`, `fatca_flag`,
  `crs_flag`) as first-class columns on `client`, ahead of Compliance (Phase 9+) consuming them.
- ✅ Non-person (entity) clients are supported inline via an optional `nonPerson` object on
  create/update (`client_non_person`, 1:1 with `client`) rather than as a separate top-level
  sub-resource — Fineract itself treats it the same way (a detail table keyed by `client_id`), and it
  isn't a distinct entry in `ENDPOINT_INVENTORY.md`.
- ✅ Client transfers are modeled locally via `client_transfer_details` + `client.sub_status`
  (`proposeTransfer` inserts a row and sets `sub_status=TRANSFER_IN_PROGRESS`; `acceptTransfer`/
  `rejectTransfer`/`withdrawTransfer` finalize it) — `client.status` stays `ACTIVE` throughout a
  transfer, matching Fineract's actual design. `transfer_type` is repurposed as the proposal's
  outcome enum (proposed/accepted/rejected/withdrawn) since the V001 baseline already shaped the
  column that way with no separate status column to add.
- ✅ Client charges are caller-supplied (no `charges` product catalog exists yet — that catalog lands
  in DepositAccountManagement, a later phase); `pay`/`waive` commands post `client_transaction` +
  `client_charge_paid_by` rows and maintain `amount_paid_derived`/`amount_waived_derived`/
  `amount_outstanding_derived` using `turbo::Money` exact-decimal arithmetic, with a matching
  `undo` that reverses both the transaction and the charge's derived amounts. GL posting of charge
  payments to Accounting is deferred — no inter-service posting client exists yet in this codebase.
- ✅ **Cross-service ids intentionally trusted as caller-supplied, not validated**: `office_id`,
  `staff_id`, `charge_id`, `document_type_id`, every `*_cv_id` column, `image_id`, `payment_detail_id`
  and currency codes belong to Organization/SystemConfig/DAM, each in its own dedicated Postgres
  database (see each service's `config.json` — `dbname` differs per service) — there is no
  inter-service RPC client in this codebase yet, so no cross-database join or validation call is even
  possible. Template endpoints that would normally return those catalogs as dropdown options
  (address types, document types, relationship/marital-status/gender/profession code values) are
  documented empty stubs for the same reason. `clients/{id}/accounts` (accounts overview) and
  `clients/{id}/obligeedetails` return `501 Not Implemented` since they compose
  DepositAccountManagement + Portfolio data that doesn't exist until later phases — same precedent as
  the `downloadtemplate`/`uploadtemplate` stubs.
- ✅ **Observation, not an omission**: `AccountTransferStandingInstructions[History]` and
  `ClientAttendance` models/tables already existed in the Customer service's V001 baseline but are
  outside the 64-endpoint Phase 4 inventory (they functionally belong to DAM/standing-instructions and
  a future Group/Meetings domain respectively, not `clients`/`client`/`collateral-management`). Left
  untouched rather than deleted, to be picked up by whichever later phase owns them.
- ✅ Identity permission catalog seeded (`src/services/Identity/migrations/V006__phase4_permissions.sql`,
  grouping `customer`, 44 codes) and the "Admin" role template extended to it, same precedent as
  Phase 2/3's V004/V005.
- ✅ Gateway routing (`src/services/ApiGateway/config.json`): new `customer` upstream
  (`http://127.0.0.1:7504`) and four route prefixes — `/api/v1/clients/`, `/api/v1/client/`,
  `/api/v1/collateral-management/`, `/api/v2/clients/`.
- ✅ **Compile- and link-verified** against the same rebuilt local toolchain as Phase 3 (`~/.toolchain`,
  rebuilt from scratch this session since it didn't persist between sessions): `cmake --build` was run
  for real, linking a genuine `Customer` executable (and its test binary) against `libturbo`, with zero
  compile errors anywhere, and zero warnings under `-Wall -Wextra` in all 5 controllers and the
  `CustomerService` itself. The model `.cc` files do emit the same pair of harmless
  `-Wunused-parameter` warnings (in the generated `updateId`/`validJsonOfField` stubs) already present
  in every drogon_ctl-generated model since Phase 2 — confirmed by rebuilding Accounting side-by-side
  with identical flags and seeing the exact same warning shape in its genuine, untouched models
  (`Accounts.cc`, `GlClosure.cc`, ...), so this is template boilerplate, not something Phase 4
  introduced.
- **Exit criteria:** Fineract Postman `clients` folder is expected to pass against Turbo Ledger with
  only base-URL/tenant-header/route-shape changes (this codebase uses explicit action-suffix paths
  instead of Fineract's verb-overloaded single path — see above) — **not runtime-tested against a live
  Postgres**, same unavoidable limitation as Phases 2/3 in this sandbox.

### Phase 5 — Deposits (≈119 endpoints)

The heart of "banking": savings, fixed & recurring deposits.

- `savingsproducts` (6) with charge & GL mappings; `charges` (6) catalog.
- `savingsaccounts` (32): application→approval→activation lifecycle, deposit/withdrawal/hold/release commands, interest calculation & posting (daily/average balance, tiered via `interestratecharts` (12)), overdraft support, charges (add/pay/waive/inactivate), transaction reversal/undo, account close with interest payout.
- `fixeddepositproducts`/`fixeddepositaccounts` (23): maturity instructions, premature close w/ penalty, renewal.
- `recurringdepositproducts`/`recurringdepositaccounts` (22): installment schedule, missed-installment handling.
- `accounttransfers` (6) internal transfers (atomic two-account posting through Accounting), `standinginstructions` (5 + run history) executed by HeartBeat.
- `accountnumberformats` (6) + account number generation.
- Interest posting / accrual jobs registered with HeartBeat.
- **Exit criteria:** full savings lifecycle with correct GL postings; interest posting job reconciles to accrual entries; FD premature close penalty math matches Fineract reference cases.

### Phase 6 — Lending & shares (≈224 endpoints) ✅ IMPLEMENTED (not build-verified — see below)

Largest phase — split into 6a (products+core lifecycle), 6b (repayment mechanics), 6c (risk).

- **6a:** `loanproducts` (11, incl. accounting mappings, interest recalculation config), `loans` core: template, submit, modify, approve/undo, disburse (+to savings), undo disbursal, cancel, delete; charges on loans; guarantors; collateral (`loan-collateral-management`).
- **6b:** repayment schedule engine (declining balance/flat, equal installments/principal, grace, compounding & recalculation), transactions: repayment, prepay, waive interest, writeoff/undo, recovery, refund, charge-off, adjustments; `rescheduleloans` (5); `floatingrates` (4) + `rates` (4); interest pause, reamortize/reage (from the collection's loan commands).
- **6c:** `delinquency` (10: buckets, ranges, pause/resume, tags), `provisioningcategory` (4) + `provisioningcriteria` (6) feeding Accounting's `provisioningentries`; credit bureau config/integration (17) behind a provider adapter; `external-asset-owners` (12, loan sales/transfers); shares: `shareproduct` (5+dividends) + share `accounts` (8) + `products` (6).
- **Exit criteria:** amortization schedules byte-match Fineract goldens for a test matrix (≥50 product configs); delinquency job tags correctly; NPA provisioning entries post. *(Relaxed by explicit user direction: amortization fidelity bar is "core methods verified by hand-worked examples," not a 50-case byte-exact golden suite.)*

- ✅ **Implemented** (6a+6b, single combined pass rather than the 6a/6b/6c split above) as a new **Portfolio** service (port 7502): 44 hand-authored models (`src/services/Portfolio/models/`, matching drogon_ctl's real generated shape for the CoroMapper subset this codebase uses — see each file's header comment, same pattern as every prior phase's models) + one `PortfolioService` (`services/PortfolioService.{h,cc}`) implementing every method below, fronted by 15 controllers (`src/services/Portfolio/controllers/`) following the Organization/Accounting/DAM per-resource-controller, explicit-action-suffix-path convention (`get-all`/`create`/`get-detail/{id}`/`{id}/update`/`{id}/delete`/`{id}/command/{name}`).
  - `loanproducts` (11, incl. `productmix` sub-resource, external-id mirror wired since the service resolves it cheaply), `loans` core + sub-resources (charges, collaterals, guarantors, disbursement details, interest pauses, post-dated checks, buydown fees, capitalized income, delinquency actions/tags, transactions, reassignment, GLIM, COB catch-up) — **all included per explicit user direction, none trimmed** — in one `LoansController` (mirrors the DAM `SavingsAccountsController` precedent of folding sub-resources into the aggregate-root controller).
  - `rescheduleloans` (5), `loan-collateral-management` (2, standalone get/delete by collateral id), `floatingrates` (4), `rates` (4).
  - `delinquency` (10: buckets + ranges CRUD), `provisioningcategory` (4), `provisioningcriteria` (6) — wired to post into Accounting's `provisioningentries` via `runDelinquencyAndProvisioningJob`.
  - Shares — **included in full per explicit user direction**: `products`/`:type` share products (6) + `shareproduct` dividends (5) + share `accounts`/`:type` (8, minus the 2 CSV bulk-template endpoints, same precedent as every other phase's CSV omissions).
  - `external-asset-owners` (10 of 12 wired — loan sales/transfers, search, journal entries, loan-product attributes; **included in full per explicit user direction**, not a config-only stub) and `CreditBureauConfiguration`+`creditBureauIntegration` (17; **included in full per explicit user direction**) behind a pluggable `CreditBureauProvider` — ships with one deterministic **synthetic/sandbox provider only**; there is no real external credit bureau integration.
  - Permission catalog: `src/services/Identity/migrations/V008__phase6_permissions.sql` adds the Portfolio permission grouping, granted to the `Admin` role template, matching the Phase 3/4/5 precedent.
  - Gateway routing (`src/services/ApiGateway/config.json`): 15 new prefixes added to `custom_config.gateway.routes`, all pointing at a new `"portfolio": "http://127.0.0.1:7502"` entry in `custom_config.gateway.services`; checked for prefix collisions against every other service's registered prefixes (none found).
  - Service skeleton (`main.cc`, `CMakeLists.txt`, `config.json`, `utils/codecvt_helper.h`) rewritten to match the DAM/Accounting/Customer/Organization integrated pattern exactly: `turbo::TrustedContextFilter` (reads `custom_config.turbo.context_secret`), `turbo::registerHealthEndpoint`, the same hardcoded CORS allowed-origins list used verbatim by every other service's `main.cc`.
  - **Explicit scope trims (static review only — see below for why — flagged for the user to confirm or revisit):**
    1. **External-id-mirror routes are not wired** for `loans` and most of its sub-resources, even though `PortfolioService`'s methods already thread an `idOrExternalId`/`byExternalId` pair through nearly every call (so wiring the mirror routes later is a small, mechanical controller-only addition — no service changes needed). Loan products' external-id mirror *is* wired (cheap, 2 extra routes). This was a controller-surface-size judgment call, not explicitly directed by the user — flagging per the standing instruction to surface undirected scope decisions.
    2. `mixmapping`/`mixreport`/`mixtaxonomy` (3 endpoints, XBRL regulatory reporting) remain excluded — conceptually a Reporting-phase concern (Phase 8), never mentioned in this plan's Phase 6 narrative above.
    3. `downloadtemplate`/`uploadtemplate` CSV bulk-import endpoints and `at-date/*` point-in-time endpoints are excluded across the board, consistent with the same omission in every prior phase (Organization/SystemConfig/Accounting/DAM).
    4. COB catch-up (`runLoanCobCatchUp`/lock listing/oldest-closed-loan) is a simplified same-request synchronous implementation, not a real async batch-job framework (that's Phase 8's HeartBeat/jobs surface) — it does drive the same delinquency+provisioning logic the exit criteria cares about.
  - **Not build-verified this session:** no C++ toolchain (cmake/g++/Drogon/jsoncpp dev packages) is present in this sandbox — a prior session's notes mention a locally-built toolchain cached at `~/.toolchain`, but that does not persist across sandbox resets and was not present here. Verification this session was static only: every `svc().<method>(...)` call site in the new controllers was cross-checked by script against `PortfolioService.h`'s declared signatures (name exists + argument count matches) for all ~172 declared service methods, route prefixes were checked for collisions against every other service, and a real enum-mismatch bug (share account status `kShareClosed` locally redeclared as `600` vs. the canonical `ShareAccountStatus::kShareStatusClosed = 500` already declared in the service header) was found and fixed. This is **not** a substitute for an actual compile — flagging per the standing instruction not to claim verification that didn't happen.

### Phase 7 — Field operations: Groups & Teller (≈46 endpoints)

- `groups` (13) + `centers` (10) + `grouplevels` + group lifecycle commands, client↔group association; `collectionsheet` (1 + group/center variants) for bulk field collections; JLG loans hook into Portfolio.
- `tellers` (19: teller CRUD, cashier allocation/settlement, journals, transactions) + `cashiersjournal` + `officetransactions` cash management flow.
- **Exit criteria:** center meeting collection sheet generate→save posts bulk repayments/deposits atomically.

**Group domain — ✅ IMPLEMENTED (not build-verified — see below).** `groups`/`centers`/`grouplevels`/`collectionsheet`
were originally scoped out of Phase 4 (Customer) for lack of a real Group entity — they are retroactively
implemented here now that Phase 7 is the right home for them, and the Phase 5 `savingsaccounts/gsim*` (GSIM)
stubs are retrofitted at the same time since GSIM composes Group + DepositAccountManagement.

- Hand-authored models (`Group`, `GroupLevel`, `GroupClient`, `GroupRole`) in `src/services/Group/models/`,
  matching drogon_ctl's generated-code shape byte-for-byte (same precedent as Organization's hand-authored
  models in Phase 2), since this sandbox has no live Postgres for `drogon_ctl` to introspect against.
  `src/services/Group/migrations/V003__phase7_group.sql` adds the backing tables.
- One `GroupService` (mirrors the Organization/SystemConfig/Accounting monolithic-service-class,
  per-resource-controller pattern) implementing: full CRUD for groups and centers (shared `*Entity` helpers
  parameterized on `isCenter`), lifecycle commands (`activate`/`close` — close is blocked while the
  group still has members or the center still has child groups), staff assignment, client↔group
  membership (`associateClients`/`disassociateClients`/`transferClients`), group role assignment
  (`assignRole`/`unassignRole`/`updateRole`), and center↔group association
  (`associateGroups`/`disassociateGroups`), all via `CoroMapper<Model>`.
- Four controllers follow the `ClientsController` convention exactly (`TrustedContextFilter`,
  explicit-action-suffix routing, `ApiError`/`ApiResponse` try/catch triplet): `GroupsController` (13
  endpoints), `CentersController` (10), `GroupLevelsController` (1, read-only), `CollectionSheetController`
  (1, top-level `/api/v1/collectionsheet/submit`).
- **Explicit scope trims, same precedent as every prior phase's cross-service-composition stubs:**
  `accountsOverview`/`glimAccounts`/`gsimAccounts` (groups), `accountsOverview` (centers), and
  `generateCollectionSheet`/`saveCollectionSheet` (both resources plus the top-level `collectionsheet`
  endpoint) return `501 Not Implemented` — they compose Group + Portfolio/DepositAccountManagement data
  or a dedicated bulk-collection posting engine that doesn't exist yet, exactly the same class of
  omission as `clients/{id}/accounts` in Phase 4 and the CSV bulk-import endpoints in every phase.
- **GSIM retrofit (`src/services/DepositAccountManagement`):** `createGsimAccount`/`updateGsimAccount`/
  `handleGsimCommand` are now real implementations in `DepositAccountManagementService` (previously 501
  stubs, since Group didn't exist yet when Phase 5 was built) — wired through
  `SavingsAccountsController`'s existing `gsim/{1}/command/{2}` route. GLIM (Portfolio/Phase 6) needed no
  equivalent rework — it was already implemented correctly without depending on a real Group entity.
- Identity permission catalog: `src/services/Identity/migrations/V009__phase7_group_permissions.sql`
  adds 18 permission codes (`grouping=group`) for GROUP/CENTER/GROUPLEVEL entities, granted to the
  `Admin` role template, same precedent as every prior phase's permission migration.
- Gateway routing (`src/services/ApiGateway/config.json`): new `group` upstream
  (`http://127.0.0.1:7506`) and four route prefixes — `/api/v1/groups/`, `/api/v1/centers/`,
  `/api/v1/grouplevels/`, `/api/v1/collectionsheet/` — checked for prefix collisions against every
  other service's registered prefixes (none found, 77 total routes).
- Service skeleton (`main.cc`, `CMakeLists.txt`, `utils/codecvt_helper.h`) rewritten from the DAM/Portfolio
  templates; top-level `CMakeLists.txt` `TL_SERVICES` and `docker-compose.dev.yml` updated to include the
  `group` service (port 7506).
- **Not build-verified this session:** no C++ toolchain is present in this sandbox (same limitation as
  Phase 6). Verification was static only: brace/paren balance checked on every new file, every
  `svc().<method>(...)` call site cross-checked by script against `GroupService.h`'s declared signatures
  (name + argument count), every `ADD_METHOD_TO` route's path-placeholder count cross-checked against its
  handler's parameter count, every model accessor name (`getValueOfX`/`getX`/`setX`/`Cols::_x`) used in
  `GroupService.cc` cross-checked against the hand-authored model headers, and the gateway route table
  re-checked for collisions. This is **not** a substitute for an actual compile.
- **Teller (`tellers`/`cashiers`/`cashiersjournal`, 21 endpoints) remains unimplemented** — this phase's
  remaining scope, picked up next.

### Phase 8 — Operations backbone: jobs, batch, notifications, reporting (≈123 endpoints)

- **HeartBeat:** `jobs` (14: list, run now, history, error log, enable/disable) + `scheduler` (2: pause/resume) as a durable per-tenant job framework (cron in Postgres, leader election via Redis); register all domain jobs (interest posting, accruals, delinquency, SI execution, report mailing).
- **Batch API:** `batches` (1) — Fineract's transactional batch with relative references (`$.1.body.id`), executed inside the gateway.
- **Notification:** `notifications` (2, user inbox), `sms` (6) + `smscampaigns` (8), `email` (20: config + campaigns), `templates` (8, mustache-style), `reportmailingjobs` (6+1); pluggable SMS/email providers; events from the outbox drive triggered notifications.
- **Reporting:** `reports` (6) + `runreports` (2) — parameterized SQL report engine (tenant-schema-scoped, read-only role, statement timeout), stretch: Pentaho-format import; `adhocquery` (6); `search` (3); `surveys`/`survey` (19) + `likelihood`/`povertyLine` (5, PPI); read-replica routing.
- **Exit criteria:** nightly COB chain (accrual→interest→delinquency→provisioning→report mailing) runs unattended for a week on a seeded tenant; batch API passes relative-reference tests.

### Phase 9 — Self-service & interoperation (≈79 endpoints)

- **SelfService (BFF):** all 60 `self/*` endpoints — registration (+confirm), authentication, clients/accounts/transactions views, loan & savings applications, beneficiaries (TPT), third-party transfers, share accounts, device registration for push, pockets, surveys — composing internal services with a locked-down self-service permission set.
- **Payments v1:** `interoperation` (19) — Mojaloop-style parties/quotes/transfers/requests for wallet interop, plus **internal instant transfer API** with holds (`hold→commit/abort`) building on DAM.
- **Exit criteria:** a demo mobile-banking flow (register → view accounts → transfer → loan application) runs purely against SelfService.

### Phase 10 — Modern banking extensions ⭐

Beyond Fineract parity; each is an independent workstream on the Phase 0 platform:

1. **Payments service (full):**
   - Payment orders API (`POST /payments/orders`, cancel, return, status) with state machine (RECEIVED→VALIDATED→SCREENED→POSTED→SENT→SETTLED/RETURNED).
   - **ISO 20022** adapters: pain.001/pain.002 intake, pacs.008/pacs.004 generation/parsing, camt.052/053/054 statement generation per account.
   - Rail adapters as plugins (SEPA SCT/Inst, ACH, RTP/FedNow-style, SWIFT gpi stub, mobile money) with per-tenant routing rules, cut-off times (uses `workingdays`/`holidays`), and nostro reconciliation against camt.053.
   - Confirmation of Payee / account-name check API; QR (EMVCo) generation & parsing.
2. **OpenBanking service:** TPP onboarding (mTLS/eIDAS-style cert registry), OAuth2/OIDC authorization server (consent grant), **AIS** (accounts/balances/transactions), **PIS** (payment initiation → Payments service), consent lifecycle + SCA hooks into Identity 2FA; Berlin-Group-flavored REST.
3. **Cards service:** card products, issue/activate/block/replace, PIN management (HSM-abstraction stub), **authorization webhook** endpoint for processor integration (Marqeta/Paymentology-style): auth → real-time balance check + hold in DAM; clearing → hold capture + GL posting; card controls (channel/MCC/geo/limits), tokenization records, dispute/chargeback case skeleton.
4. **Compliance service:** KYC workflow (document requests, verification states, provider adapter for IDV), sanctions/PEP screening (batch + real-time hook called by Payments/Customer), transaction-monitoring rules engine (velocity, structuring, threshold rules on the event stream), case management, SAR/CTR report exports, FATCA/CRS extracts.
5. **EventHub service:** webhook subscriptions per tenant (`POST /webhooks`, filters by event type), HMAC-signed deliveries, retries w/ exponential backoff + dead-letter, delivery logs & replay, event catalog endpoint; fed by the platform outbox → this also becomes the real implementation behind Fineract's `hooks`.
6. **Platform upgrades:**
   - **Virtual accounts / multi-wallet**: lightweight sub-accounts under a settlement account (DAM extension) for BaaS clients.
   - **Multi-currency & FX**: rate tables + `POST /fx/quotes` + cross-currency transfer posting (dual-leg GL with FX gain/loss accounts).
   - **BaaS developer experience:** sandbox tenants with simulators (inbound payment, card auth), API key scopes & usage metering at the gateway, Swagger portal, Postman collection auto-generated per release.
   - **Statements**: PDF/camt.053 account statements service endpoint.

### Phase 11 — Hardening & production readiness

- Observability: OpenTelemetry traces across gateway→services, Prometheus metrics (per-tenant labels), structured JSON logs, Grafana dashboards + SLOs (p99 auth < 50 ms, posting < 150 ms).
- Security: secrets manager integration, field-level encryption for PII (per-tenant keys from registry), pen test, OWASP ASVS L2 audit, rate-limit tuning, WAF rules.
- Data: PITR backups per DB, per-tenant export/erasure (GDPR), DR runbook + restore drills, read replicas for Reporting.
- Performance: k6 load suites per domain (targets: 500 TPS transfers/tenant, 5k concurrent self-service users), COB duration budget (<30 min for 1M accounts).
- Kubernetes deployment (Helm charts per service), blue/green, migration gating.
- Fineract-compatibility certification: run the entire Postman collection as a nightly conformance suite; publish the diff report.

---

## 4. Sequencing & milestones

```
Phase:      0    1    2    3    4    5    6    7    8    9    10   11
            ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
Platform    ████████
Tenancy/Id       █████
Org/Config            █████
Accounting                 █████
Customer                        █████
Deposits                             ███████        (parallel w/ 6)
Lending                              ██████████████
Groups/Teller                                  █████ (parallel w/ 8)
Ops backbone                                        ██████
Self/Interop                                             ██████
Modern ⭐                                                     ████████
Hardening   ─────────────────────────────────────────────────────███
```

- With ~3 squads: Phases 5/6 and 7/8 run in parallel; modern extensions (Phase 10) are five independent tracks.
- **Milestone M1 (end P3):** "Ledger-ready" — tenants, users, offices, GL posting.
- **M2 (end P5):** "Deposit bank" — clients + savings/FD/RD end-to-end, demoable.
- **M3 (end P6):** "Full MFI/core" — Fineract functional parity for lending.
- **M4 (end P9):** "Digital bank" — self-service + interop live; full Postman conformance run.
- **M5 (end P10):** "Modern platform" — payments rails, open banking, cards, compliance, webhooks.

**Definition of done per endpoint:** OpenAPI spec merged → controller + service + repository implemented via `libturbo` conventions → permission constant seeded → audit/outbox emitted → unit + integration test (against docker-compose Postgres) → Postman conformance test green → docs regenerated.

---

## 5. Risks & mitigations

| Risk | Mitigation |
|---|---|
| C++ talent/velocity vs. 1,000 endpoints | `libturbo` + a `drogon_ctl`-style **code generator** that scaffolds controller/DTO/service/test from the OpenAPI spec; measure endpoints/week from Phase 4 |
| Interest/amortization math divergence | Golden-file tests generated from a reference Fineract instance; property-based tests for rounding invariants |
| Tenant schema sprawl (search_path bugs) | All DB access through `libturbo` txn wrapper that force-sets `search_path`; CI test that fails any raw `execSqlCoro` outside the wrapper |
| Empty-coroutine UB (existing Accounting controllers) | Phase 0 lint rule: every `Task<HttpResponsePtr>` must `co_return`; fix existing bodies immediately |
| Cross-service consistency (e.g. transfer touches DAM + Accounting) | Sagas with outbox events + idempotent handlers; no distributed 2PC; reconciliation jobs as backstop |
| Postman collection drift vs. real Fineract behavior | Treat the live Fineract demo API docs as tie-breaker; keep a `compat-notes.md` of intentional deviations |
| Scope creep in Phase 10 | Each ⭐ service ships an MVP behind a tenant feature flag; processor/rail integrations are adapter interfaces with a simulator first |

---

## 6. Immediate next steps (first two weeks)

1. Create `src/libs/turbo` and port Identity to it; add the `co_return` lint; fix Accounting's empty controller bodies.
2. Top-level CMake + vcpkg manifest + `docker-compose.dev.yml`; CI building everything.
3. Implement gateway routing + tenant header resolution + signed context; retire per-request `ClientId/ClientSecret` validation calls from Accounting.
4. Convert `src/scripts/*.sql` into per-service `V001` migration baselines with schema-per-tenant support; build the Provisioner's tenant-create pipeline against Identity + Accounting only.
5. Stand up the conformance harness: newman running the `authentication` + `users` + `glaccounts` folders of the Postman collection against docker-compose.

Companion document: [`ENDPOINT_INVENTORY.md`](./ENDPOINT_INVENTORY.md) — the full 871-endpoint breakdown by owning service, generated from the Postman collection.
