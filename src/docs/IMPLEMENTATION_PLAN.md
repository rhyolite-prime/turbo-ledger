# Turbo Ledger — Implementation Plan

**Goal:** evolve Turbo Ledger from its current scaffold into a complete, multi-tenant core banking platform, using Apache Fineract (v1 REST API, ~871 endpoints — see [`ENDPOINT_INVENTORY.md`](./ENDPOINT_INVENTORY.md)) as the functional reference, then extending it with modern banking capabilities Fineract lacks (instant payments/ISO 20022, open banking, cards, webhooks/event streaming, KYC/AML, virtual accounts, BaaS developer experience).

---

## 1. Where we are today (current-state assessment)

| Area | Status |
|---|---|
| **Stack** | C++20 + Drogon (coroutines), CMake, PostgreSQL (DB-per-service scripts in `src/scripts/`), Redis, bcrypt, JWT |
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

### Phase 1 — Tenancy & Identity completion (≈34 endpoints + tenant APIs)

- **Provisioner:** tenant registry CRUD + lifecycle (`create/activate/suspend/close`), per-service schema provisioning + seeding pipeline, `instance-mode` endpoint, tenant cache invalidation events.
- **Identity:** finish 501 stubs (OTP send/verify, change password, self profile); `users` (9), `roles` (8: CRUD + enable/disable + permission assignment), `permissions` (2), `passwordpreferences` (3), `twofactor` (6, TOTP), `userdetails`, `authentication`; maker-checker command store + `makercheckers` (4).
- Permission catalog seeding; role templates (Super user, Admin, Teller, Loan officer, Self-service).
- **Exit criteria:** create tenant end-to-end via API → login as tenant admin → create user/role → maker-checker round trip on `CREATE_USER`.

### Phase 2 — Organization & SystemConfig (≈142 endpoints)

The reference-data layer every product feature reads.

- **Organization:** `offices` (9, hierarchical with `hierarchy` path), `officetransactions` (4), `staff` (6, incl. loan-officer flag), `holidays` (7, incl. activate), `workingdays` (3), `currencies` (2), `funds` (4), `paymenttypes` (5), `taxes` (10: components + groups), `entitytoentitymapping` (6).
- **SystemConfig:** `codes`/code values (11), `configurations` (5), `businessdate` (3), `caches` (2), `audits` (3, reads the command/audit store), `hooks` (6, config only — firing comes with EventHub), `externalservice` (2), `fieldconfiguration`, `externalevents` (2), **`datatables` (16) + `entityDatatableChecks` (4)** — dynamic per-tenant custom tables attached to entities (build early; clients/loans endpoints embed datatable data), entity-generic routes: documents (`{entityType}/{entityId}/documents`), notes, images (Base64 + multipart, S3-compatible object storage), `imports` (3, bulk Excel/CSV import scaffolding).
- **Exit criteria:** office tree + staff + codes seeded for new tenants; a datatable can be created and attached to `m_client` and surfaces in client responses.

### Phase 3 — Accounting core (≈39 endpoints)

- Implement the empty controller bodies: `glaccounts` (8, tree + template + disable), `journalentries` (8: create balanced multi-leg, search w/ filters, reverse command, provisioning entries view, opening balances), `glclosures` (5), `accountingrules` (6), `financialactivityaccounts` (6), `runaccruals`, `provisioningentries` (5, driven by Portfolio criteria later).
- Ledger correctness rules from §2.5 (immutability, hash chain, running balances, closure enforcement).
- Chart-of-accounts template seeding per tenant; product-to-GL mapping tables (consumed by DAM/Portfolio in later phases).
- **Exit criteria:** balanced entry posting w/ reversal; trial balance report reconciles; posting blocked after closure; 1k entries/sec sustained on dev hardware.

### Phase 4 — Customer domain (≈64 endpoints)

- `clients` (53 + v2 list): full lifecycle commands (`activate`, `close`, `reject`, `withdraw`, `reactivate`, `undoRejection`, `assignStaff`, `proposeTransfer`, `acceptTransfer`, ...), addresses, family members, identifiers (with document images), client charges, client transactions (pay/waive/undo), non-person (entity) clients, client accounts overview (composes DAM+Portfolio via async fan-out).
- `collateral-management` (6) product-level collateral registry.
- Wire in datatables/documents/notes/images from Phase 2.
- ⭐ Modern addition here: **client risk attributes** (KYC status, risk rating, FATCA/CRS flags) as first-class columns, consumed by Compliance in Phase 9.
- **Exit criteria:** Fineract Postman `clients` folder passes against Turbo Ledger with only base-URL/tenant-header changes.

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

### Phase 6 — Lending & shares (≈224 endpoints)

Largest phase — split into 6a (products+core lifecycle), 6b (repayment mechanics), 6c (risk).

- **6a:** `loanproducts` (11, incl. accounting mappings, interest recalculation config), `loans` core: template, submit, modify, approve/undo, disburse (+to savings), undo disbursal, cancel, delete; charges on loans; guarantors; collateral (`loan-collateral-management`).
- **6b:** repayment schedule engine (declining balance/flat, equal installments/principal, grace, compounding & recalculation), transactions: repayment, prepay, waive interest, writeoff/undo, recovery, refund, charge-off, adjustments; `rescheduleloans` (5); `floatingrates` (4) + `rates` (4); interest pause, reamortize/reage (from the collection's loan commands).
- **6c:** `delinquency` (10: buckets, ranges, pause/resume, tags), `provisioningcategory` (4) + `provisioningcriteria` (6) feeding Accounting's `provisioningentries`; credit bureau config/integration (17) behind a provider adapter; `external-asset-owners` (12, loan sales/transfers); shares: `shareproduct` (5+dividends) + share `accounts` (8) + `products` (6).
- **Exit criteria:** amortization schedules byte-match Fineract goldens for a test matrix (≥50 product configs); delinquency job tags correctly; NPA provisioning entries post.

### Phase 7 — Field operations: Groups & Teller (≈46 endpoints)

- `groups` (13) + `centers` (10) + `grouplevels` + group lifecycle commands, client↔group association; `collectionsheet` (1 + group/center variants) for bulk field collections; JLG loans hook into Portfolio.
- `tellers` (19: teller CRUD, cashier allocation/settlement, journals, transactions) + `cashiersjournal` + `officetransactions` cash management flow.
- **Exit criteria:** center meeting collection sheet generate→save posts bulk repayments/deposits atomically.

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
