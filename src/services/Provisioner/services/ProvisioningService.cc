#include "ProvisioningService.h"

#include <bcrypt.h>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <regex>
#include <set>
#include <sstream>

#include "turbo/Ids.h"
#include "turbo/RequestContext.h"
#include "turbo/TenantDb.h"

namespace fs = std::filesystem;

namespace provisioner {

namespace {

const std::regex kMigrationRe(R"(^V(\d+)__([A-Za-z0-9_\-]+)\.sql$)");

Json::Value tenantRowToJson(const drogon::orm::Row &row) {
    Json::Value j;
    j["id"] = row["id"].as<std::string>();
    j["name"] = row["name"].as<std::string>();
    j["status"] = row["status"].as<std::string>();
    j["createdAt"] = row["created_at"].isNull() ? "" : row["created_at"].as<std::string>();
    j["updatedAt"] = row["updated_at"].isNull() ? "" : row["updated_at"].as<std::string>();
    return j;
}

std::string generatePassword() {
    // e.g. "Tl!4f9c2ab17d3e" — mixed class, 15 chars, returned exactly once.
    std::string uuid = turbo::ids::newUuid();
    uuid.erase(std::remove(uuid.begin(), uuid.end(), '-'), uuid.end());
    return "Tl!" + uuid.substr(0, 12);
}

/// Awaits the actual COMMIT of a Drogon transaction. Drogon commits
/// asynchronously when the Transaction is destroyed, so without this a
/// follow-up query on another pooled connection can race the commit and
/// not see its effects. Takes ownership of (and consumes) the last
/// reference to the transaction.
struct TxnCommitAwaiter : public drogon::CallbackAwaiter<bool> {
    explicit TxnCommitAwaiter(std::shared_ptr<drogon::orm::Transaction> &&txn)
        : txn_(std::move(txn)) {}
    void await_suspend(std::coroutine_handle<> handle) {
        txn_->setCommitCallback([this, handle](bool committed) {
            setValue(committed);
            handle.resume();
        });
        txn_.reset();  // drop the last reference -> destructor queues COMMIT
    }

  private:
    std::shared_ptr<drogon::orm::Transaction> txn_;
};

drogon::Task<void> commitTxn(std::shared_ptr<drogon::orm::Transaction> txn) {
    const bool ok = co_await TxnCommitAwaiter(std::move(txn));
    if (!ok) throw std::runtime_error("Transaction commit failed");
    co_return;
}

}  // namespace

ProvisioningService &ProvisioningService::instance() {
    static ProvisioningService service;
    return service;
}

void ProvisioningService::initFromConfig() {
    const auto &cfg = drogon::app().getCustomConfig()["provisioner"];
    staticTenants_ = cfg["static_tenants"];
    instanceMode_ = cfg["instance_mode"];
    targets_.clear();
    for (const auto &s : cfg["services"]) {
        ServiceTarget t;
        t.name = s.get("name", "").asString();
        t.dbClient = s.get("db_client", "").asString();
        t.migrationsDir = s.get("migrations_dir", "").asString();
        t.seedAdmin = s.get("seed_admin", false).asBool();
        if (!t.name.empty() && !t.dbClient.empty() && !t.migrationsDir.empty())
            targets_.push_back(t);
    }
    LOG_INFO << "Provisioner configured with " << targets_.size() << " service target(s)";
}

drogon::Task<void> ProvisioningService::ensureRegistry() {
    if (registryReady_) co_return;
    auto client = drogon::app().getDbClient();
    auto txn = co_await client->newTransactionCoro();
    // Native Postgres ENUM mirroring turbo::TenantStatus (CREATE TYPE has no
    // IF NOT EXISTS, hence the DO block).
    std::string labels;
    for (const auto status : turbo::kAllTenantStatuses) {
        if (!labels.empty()) labels += ", ";
        labels += "'" + std::string(turbo::toString(status)) + "'";
    }
    co_await txn->execSqlCoro(
        "DO $do$ BEGIN "
        "  IF NOT EXISTS (SELECT 1 FROM pg_type WHERE typname = 'tenant_status') THEN "
        "    CREATE TYPE public.tenant_status AS ENUM (" + labels + "); "
        "  END IF; "
        "END $do$");
    co_await txn->execSqlCoro(
        "CREATE TABLE IF NOT EXISTS public.tenants ("
        "  id         varchar(40) PRIMARY KEY,"
        "  name       varchar(200) NOT NULL,"
        "  status     public.tenant_status NOT NULL DEFAULT 'PENDING',"
        "  details    jsonb        NOT NULL DEFAULT '{}'::jsonb,"
        "  created_at timestamptz  NOT NULL DEFAULT now(),"
        "  updated_at timestamptz  NOT NULL DEFAULT now())");
    // One-time upgrade of registries created before the ENUM existed
    // (varchar + CHECK constraint -> tenant_status).
    co_await txn->execSqlCoro(
        "DO $do$ BEGIN "
        "  IF EXISTS (SELECT 1 FROM information_schema.columns "
        "             WHERE table_schema = 'public' AND table_name = 'tenants' "
        "               AND column_name = 'status' AND udt_name <> 'tenant_status') THEN "
        "    ALTER TABLE public.tenants DROP CONSTRAINT IF EXISTS chk_tenants_status; "
        "    ALTER TABLE public.tenants ALTER COLUMN status DROP DEFAULT; "
        "    ALTER TABLE public.tenants ALTER COLUMN status "
        "      TYPE public.tenant_status USING status::public.tenant_status; "
        "    ALTER TABLE public.tenants ALTER COLUMN status "
        "      SET DEFAULT 'PENDING'::public.tenant_status; "
        "  END IF; "
        "END $do$");
    for (const auto &t : staticTenants_) {
        const std::string rawStatus = t.get("status", "ACTIVE").asString();
        const auto status = turbo::tenantStatusFromString(rawStatus);
        if (!status) {
            LOG_WARN << "static_tenants entry '" << t.get("id", "").asString()
                     << "' has unknown status '" << rawStatus << "', skipping";
            continue;
        }
        co_await txn->execSqlCoro(
            "INSERT INTO public.tenants (id, name, status) "
            "VALUES ($1, $2, $3::public.tenant_status) ON CONFLICT (id) DO NOTHING",
            t.get("id", "").asString(), t.get("name", "").asString(),
            std::string(turbo::toString(*status)));
    }
    co_await commitTxn(std::move(txn));
    registryReady_ = true;
    LOG_INFO << "Tenant registry ready (public.tenants)";
    co_return;
}

drogon::Task<Json::Value> ProvisioningService::listTenants() {
    co_await ensureRegistry();
    auto client = drogon::app().getDbClient();
    auto txn = co_await client->newTransactionCoro();
    auto rows = co_await txn->execSqlCoro(
        "SELECT id, name, status::text AS status, created_at::text AS created_at, "
        "  updated_at::text AS updated_at FROM public.tenants ORDER BY id");
    Json::Value list(Json::arrayValue);
    for (const auto &row : rows) list.append(tenantRowToJson(row));
    Json::Value out;
    out["tenants"] = list;
    out["totalCount"] = static_cast<Json::UInt64>(rows.size());
    co_return out;
}

drogon::Task<Json::Value> ProvisioningService::getTenant(const std::string &id) {
    co_await ensureRegistry();
    auto client = drogon::app().getDbClient();
    auto txn = co_await client->newTransactionCoro();
    auto rows = co_await txn->execSqlCoro(
        "SELECT id, name, status::text AS status, created_at::text AS created_at, "
        "  updated_at::text AS updated_at FROM public.tenants WHERE id = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Unknown tenant: " + id,
                       "error.msg.provisioner.tenant.not.found");
    co_return tenantRowToJson(rows[0]);
}

drogon::Task<Json::Value> ProvisioningService::createTenant(const Json::Value &body) {
    co_await ensureRegistry();
    const std::string id = body.get("id", "").asString();
    const std::string name = body.get("name", "").asString();
    if (!turbo::RequestContext::isValidTenantId(id))
        throw ApiError(drogon::k400BadRequest,
                       "Tenant id must match ^[a-z0-9][a-z0-9_]{0,39}$",
                       "error.msg.provisioner.tenant.id.invalid");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.provisioner.tenant.name.required");

    auto client = drogon::app().getDbClient();
    {
        auto txn = co_await client->newTransactionCoro();
        auto inserted = co_await txn->execSqlCoro(
            "INSERT INTO public.tenants (id, name, status) "
            "VALUES ($1, $2, $3::public.tenant_status) "
            "ON CONFLICT (id) DO NOTHING RETURNING id",
            id, name, std::string(turbo::toString(turbo::TenantStatus::Provisioning)));
        if (inserted.size() == 0)
            throw ApiError(drogon::k409Conflict, "Tenant already exists: " + id,
                           "error.msg.provisioner.tenant.duplicate");
        co_await commitTxn(std::move(txn));
    }

    const std::string adminUsername = body.get("adminUsername", "admin").asString();
    const std::string adminEmail =
        body.get("adminEmail", adminUsername + "@" + id + ".turboledger.dev").asString();
    std::string adminPassword = body.get("adminPassword", "").asString();
    const bool generated = adminPassword.empty();
    if (generated) adminPassword = generatePassword();

    Json::Value serviceReport(Json::arrayValue);
    std::string failure;
    try {
        for (const auto &target : targets_) {
            const int applied = co_await provisionServiceSchemas(target, id);
            Json::Value s;
            s["service"] = target.name;
            s["migrationsApplied"] = applied;
            serviceReport.append(s);
            if (target.seedAdmin) {
                co_await seedTenantAdmin(target, id, adminUsername, adminEmail,
                                         bcrypt::generateHash(adminPassword, 10));
            }
        }
    } catch (const std::exception &e) {
        failure = e.what();  // co_await is illegal inside a handler; finish outside
    }
    if (!failure.empty()) {
        auto txn = co_await client->newTransactionCoro();
        co_await txn->execSqlCoro(
            "UPDATE public.tenants SET status = $3::public.tenant_status, updated_at = now(), "
            "  details = jsonb_set(details, '{failure}', to_jsonb($2::text)) WHERE id = $1",
            id, failure, std::string(turbo::toString(turbo::TenantStatus::Failed)));
        co_await commitTxn(std::move(txn));
        throw ApiError(drogon::k500InternalServerError,
                       "Tenant provisioning failed: " + failure,
                       "error.msg.provisioner.provisioning.failed");
    }

    {
        auto txn = co_await client->newTransactionCoro();
        co_await txn->execSqlCoro(
            "UPDATE public.tenants SET status = $2::public.tenant_status, updated_at = now() "
            "WHERE id = $1",
            id, std::string(turbo::toString(turbo::TenantStatus::Active)));
        co_await commitTxn(std::move(txn));
    }

    Json::Value out;
    out["tenantId"] = id;
    out["name"] = name;
    out["status"] = std::string(turbo::toString(turbo::TenantStatus::Active));
    out["services"] = serviceReport;
    out["adminUsername"] = adminUsername;
    out["adminEmail"] = adminEmail;
    if (generated) out["adminPassword"] = adminPassword;  // returned exactly once
    LOG_INFO << "Tenant '" << id << "' provisioned (" << targets_.size() << " service(s))";
    co_return out;
}

drogon::Task<Json::Value> ProvisioningService::setStatus(const std::string &id,
                                                         const turbo::TenantStatus newStatus) {
    co_await ensureRegistry();
    auto client = drogon::app().getDbClient();
    auto txn = co_await client->newTransactionCoro();
    auto rows = co_await txn->execSqlCoro(
        "SELECT status::text AS status FROM public.tenants WHERE id = $1 FOR UPDATE", id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Unknown tenant: " + id,
                       "error.msg.provisioner.tenant.not.found");
    const std::string currentLabel = rows[0]["status"].as<std::string>();
    const auto current = turbo::tenantStatusFromString(currentLabel);
    if (!current)
        throw std::runtime_error("Corrupt tenant registry: unknown status '" + currentLabel +
                                 "' for tenant " + id);

    if (!turbo::isLegalTransition(*current, newStatus))
        throw ApiError(drogon::k409Conflict,
                       "Illegal status transition " + currentLabel + " -> " +
                           std::string(turbo::toString(newStatus)),
                       "error.msg.provisioner.tenant.transition");

    co_await txn->execSqlCoro(
        "UPDATE public.tenants SET status = $2::public.tenant_status, updated_at = now() "
        "WHERE id = $1",
        id, std::string(turbo::toString(newStatus)));
    co_await commitTxn(std::move(txn));
    Json::Value out;
    out["id"] = id;
    out["previousStatus"] = currentLabel;
    out["status"] = std::string(turbo::toString(newStatus));
    co_return out;
}

Json::Value ProvisioningService::instanceMode() const {
    Json::Value out;
    out["readEnabled"] = instanceMode_.get("read_enabled", true).asBool();
    out["writeEnabled"] = instanceMode_.get("write_enabled", true).asBool();
    out["batchEnabled"] = instanceMode_.get("batch_enabled", true).asBool();
    return out;
}

// ---------------------------------------------------------------------------
// Pipeline internals
// ---------------------------------------------------------------------------

drogon::Task<int> ProvisioningService::provisionServiceSchemas(const ServiceTarget &target,
                                                               const std::string &tenantId) {
    // discover migrations
    std::vector<std::pair<int, std::string>> files;
    if (!fs::is_directory(target.migrationsDir))
        throw std::runtime_error(target.name + ": migrations dir not found: " +
                                 target.migrationsDir);
    for (const auto &entry : fs::directory_iterator(target.migrationsDir)) {
        std::smatch m;
        const std::string fname = entry.path().filename().string();
        if (entry.is_regular_file() && std::regex_match(fname, m, kMigrationRe))
            files.emplace_back(std::stoi(m[1].str()), fname);
    }
    std::sort(files.begin(), files.end());

    auto client = drogon::app().getDbClient(target.dbClient);
    if (!client) throw std::runtime_error(target.name + ": db client not configured");
    const std::string schema = turbo::db::quoteIdentifier("t_" + tenantId);

    auto txn = co_await client->newTransactionCoro();
    co_await txn->execSqlCoro("CREATE SCHEMA IF NOT EXISTS " + schema);
    co_await txn->execSqlCoro(
        "CREATE TABLE IF NOT EXISTS " + schema +
        ".tl_schema_history (version INTEGER PRIMARY KEY, name TEXT NOT NULL, "
        "applied_at TIMESTAMPTZ NOT NULL DEFAULT now())");

    std::set<int> applied;
    auto seen = co_await txn->execSqlCoro("SELECT version FROM " + schema + ".tl_schema_history");
    for (const auto &row : seen) applied.insert(row["version"].as<int>());

    co_await txn->execSqlCoro("SET LOCAL search_path TO " + schema);
    int count = 0;
    for (const auto &[version, fname] : files) {
        if (applied.contains(version)) continue;
        std::ifstream in(fs::path(target.migrationsDir) / fname);
        std::stringstream buffer;
        buffer << in.rdbuf();
        for (const auto &stmt : splitSqlStatements(buffer.str()))
            co_await txn->execSqlCoro(stmt);
        co_await txn->execSqlCoro(
            "INSERT INTO " + schema + ".tl_schema_history (version, name) VALUES ($1, $2)",
            version, fname);
        ++count;
        LOG_INFO << "  [" << tenantId << "/" << target.name << "] applied " << fname;
    }
    co_await commitTxn(std::move(txn));
    co_return count;
}

drogon::Task<void> ProvisioningService::seedTenantAdmin(const ServiceTarget &target,
                                                        const std::string &tenantId,
                                                        const std::string &username,
                                                        const std::string &email,
                                                        const std::string &passwordHash) {
    auto client = drogon::app().getDbClient(target.dbClient);
    auto txn = co_await client->newTransactionCoro();
    co_await txn->execSqlCoro("SET LOCAL search_path TO " +
                              turbo::db::quoteIdentifier("t_" + tenantId));

    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO users (first_name, last_name, email, username, password_hash, "
        "                   is_active, is_locked_out, roles) "
        "VALUES ('Tenant', 'Admin', $1, $2, $3, true, false, '[]'::jsonb) "
        "ON CONFLICT DO NOTHING RETURNING id::text AS id",
        email, username, passwordHash);
    if (rows.size() == 0) {
        LOG_WARN << "Tenant admin '" << username << "' already present in t_" << tenantId;
        txn->rollback();
        co_return;
    }
    auto linked = co_await txn->execSqlCoro(
        "INSERT INTO user_roles (user_id, role_id) "
        "SELECT $1::uuid, id FROM roles WHERE name = 'Super user' RETURNING role_id",
        rows[0]["id"].as<std::string>());
    if (linked.size() == 0) {
        txn->rollback();
        throw std::runtime_error("Super user role missing in tenant schema t_" + tenantId +
                                 " (V003 migration not applied?)");
    }
    co_await commitTxn(std::move(txn));
    co_return;
}

// ---------------------------------------------------------------------------
// SQL statement splitter
// ---------------------------------------------------------------------------

namespace {

const std::regex kCopyStdinRe(R"(^COPY\s+([\s\S]+)\s+FROM\s+stdin$)",
                              std::regex::icase);

/// Unescape one field of PostgreSQL COPY text format (\t, \n, \\, ...).
std::string unescapeCopyField(const std::string &field) {
    std::string out;
    out.reserve(field.size());
    for (size_t i = 0; i < field.size(); ++i) {
        if (field[i] != '\\' || i + 1 >= field.size()) {
            out += field[i];
            continue;
        }
        switch (field[++i]) {
            case 'b': out += '\b'; break;
            case 'f': out += '\f'; break;
            case 'n': out += '\n'; break;
            case 'r': out += '\r'; break;
            case 't': out += '\t'; break;
            case 'v': out += '\v'; break;
            case '\\': out += '\\'; break;
            default: out += field[i]; break;  // \. and friends: literal
        }
    }
    return out;
}

std::string sqlLiteral(const std::string &value) {
    std::string out = "'";
    for (const char c : value) {
        out += c;
        if (c == '\'') out += '\'';
    }
    out += "'";
    return out;
}

/// Convert the data lines of a `COPY <target> FROM stdin` block into one
/// INSERT statement per row. Drogon/libpq cannot enter COPY-IN mode, so the
/// block (terminated by a `\.` line) must be rewritten before execution.
void appendCopyRowsAsInserts(const std::string &target, const std::string &sql,
                             size_t &i, std::vector<std::string> &out) {
    const size_t n = sql.size();
    if (i < n && sql[i] == '\r') ++i;
    if (i < n && sql[i] == '\n') ++i;
    while (i < n) {
        size_t eol = sql.find('\n', i);
        if (eol == std::string::npos) eol = n;
        std::string line = sql.substr(i, eol - i);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        i = std::min(n, eol + 1);
        if (line == "\\.") break;  // end-of-data marker
        if (line.empty()) continue;
        // Fields are tab-separated; a raw tab never appears inside a field.
        std::vector<std::string> fields;
        size_t start = 0;
        while (true) {
            const size_t tab = line.find('\t', start);
            fields.push_back(line.substr(start, tab - start));
            if (tab == std::string::npos) break;
            start = tab + 1;
        }
        std::string values;
        for (const auto &f : fields) {
            if (!values.empty()) values += ", ";
            values += (f == "\\N") ? "NULL" : sqlLiteral(unescapeCopyField(f));
        }
        out.push_back("INSERT INTO " + target + " VALUES (" + values + ")");
    }
}

}  // namespace

std::vector<std::string> ProvisioningService::splitSqlStatements(const std::string &sql) {
    std::vector<std::string> out;
    std::string current;
    size_t i = 0;
    const size_t n = sql.size();

    while (i < n) {
        const char c = sql[i];
        // line comment
        if (c == '-' && i + 1 < n && sql[i + 1] == '-') {
            while (i < n && sql[i] != '\n') ++i;
            continue;
        }
        // block comment
        if (c == '/' && i + 1 < n && sql[i + 1] == '*') {
            i += 2;
            while (i + 1 < n && !(sql[i] == '*' && sql[i + 1] == '/')) ++i;
            i = std::min(n, i + 2);
            continue;
        }
        // single-quoted string ('' escapes)
        if (c == '\'') {
            current += c;
            ++i;
            while (i < n) {
                current += sql[i];
                if (sql[i] == '\'') {
                    if (i + 1 < n && sql[i + 1] == '\'') { current += sql[++i]; }
                    else { ++i; break; }
                }
                ++i;
            }
            continue;
        }
        // double-quoted identifier
        if (c == '"') {
            current += c;
            ++i;
            while (i < n) {
                current += sql[i];
                if (sql[i] == '"') { ++i; break; }
                ++i;
            }
            continue;
        }
        // dollar-quoted block ($tag$ ... $tag$)
        if (c == '$') {
            size_t j = i + 1;
            while (j < n && (std::isalnum(static_cast<unsigned char>(sql[j])) || sql[j] == '_'))
                ++j;
            if (j < n && sql[j] == '$') {
                const std::string tag = sql.substr(i, j - i + 1);
                const size_t close = sql.find(tag, j + 1);
                const size_t end = (close == std::string::npos) ? n : close + tag.size();
                current += sql.substr(i, end - i);
                i = end;
                continue;
            }
        }
        if (c == ';') {
            std::string trimmed = current;
            trimmed.erase(0, trimmed.find_first_not_of(" \t\r\n"));
            trimmed.erase(trimmed.find_last_not_of(" \t\r\n") + 1);
            current.clear();
            ++i;
            std::smatch copyMatch;
            if (std::regex_match(trimmed, copyMatch, kCopyStdinRe)) {
                // pg_dump data section: libpq/Drogon cannot speak COPY-IN, so
                // rewrite the block as INSERTs (empty blocks vanish entirely).
                appendCopyRowsAsInserts(copyMatch[1].str(), sql, i, out);
                continue;
            }
            if (!trimmed.empty()) out.push_back(trimmed);
            continue;
        }
        current += c;
        ++i;
    }
    std::string trimmed = current;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\r\n"));
    trimmed.erase(trimmed.find_last_not_of(" \t\r\n") + 1);
    if (!trimmed.empty()) out.push_back(trimmed);
    return out;
}

}  // namespace provisioner
