#!/usr/bin/env python3
"""
Turbo Ledger — per-tenant schema migration runner.

Each service database hosts one Postgres schema per tenant ("t_<tenantId>").
Migrations live in src/services/<Service>/migrations/V###__name.sql and are
applied in order, tracked in <schema>.tl_schema_history.

Usage:
  migrate.py --service Accounting --tenant default \
             --database-url postgresql://postgres:postgres@127.0.0.1:5432/TlAccounting

  # apply to several tenants at once
  migrate.py --service Accounting --tenant default --tenant demo_bank ...

Requires the `psql` binary (override with PSQL env var).
"""
import argparse
import os
import re
import subprocess
import sys

TENANT_RE = re.compile(r"^[a-z0-9][a-z0-9_]{0,39}$")
MIGRATION_RE = re.compile(r"^V(\d+)__([A-Za-z0-9_\-]+)\.sql$")

PSQL = os.environ.get("PSQL", "psql")


def run_psql(database_url: str, sql: str, quiet: bool = True) -> str:
    cmd = [PSQL, database_url, "-X", "-v", "ON_ERROR_STOP=1", "-q" if quiet else "-a",
           "-t", "-A", "-c", sql]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        raise SystemExit(f"psql failed:\n{result.stderr.strip()}")
    return result.stdout.strip()


def run_psql_file(database_url: str, schema: str, path: str) -> None:
    # Pin search_path for the whole session, then stream the migration file.
    with open(path, "r", encoding="utf-8") as fh:
        body = fh.read()
    script = f'SET search_path TO "{schema}", public;\n{body}'
    cmd = [PSQL, database_url, "-X", "-v", "ON_ERROR_STOP=1", "-q", "-f", "-"]
    result = subprocess.run(cmd, input=script, capture_output=True, text=True)
    if result.returncode != 0:
        raise SystemExit(f"migration {os.path.basename(path)} failed:\n{result.stderr.strip()}")


def discover_migrations(migrations_dir: str):
    entries = []
    for name in os.listdir(migrations_dir):
        m = MIGRATION_RE.match(name)
        if m:
            entries.append((int(m.group(1)), name))
    entries.sort()
    versions = [v for v, _ in entries]
    if len(versions) != len(set(versions)):
        raise SystemExit(f"duplicate migration versions in {migrations_dir}")
    return entries


def migrate_tenant(database_url: str, migrations_dir: str, tenant: str, dry_run: bool) -> None:
    if not TENANT_RE.match(tenant):
        raise SystemExit(f"invalid tenant id: {tenant!r}")
    schema = f"t_{tenant}"

    run_psql(database_url, f'CREATE SCHEMA IF NOT EXISTS "{schema}"')
    run_psql(database_url, f'''
        CREATE TABLE IF NOT EXISTS "{schema}".tl_schema_history (
            version     INTEGER PRIMARY KEY,
            name        TEXT NOT NULL,
            applied_at  TIMESTAMPTZ NOT NULL DEFAULT now()
        )''')

    applied = set()
    out = run_psql(database_url, f'SELECT version FROM "{schema}".tl_schema_history')
    for line in out.splitlines():
        line = line.strip()
        if line:
            applied.add(int(line))

    pending = [(v, n) for v, n in discover_migrations(migrations_dir) if v not in applied]
    if not pending:
        print(f"  [{tenant}] up to date ({len(applied)} applied)")
        return

    for version, name in pending:
        print(f"  [{tenant}] applying V{version:03d} {name}" + (" (dry-run)" if dry_run else ""))
        if dry_run:
            continue
        run_psql_file(database_url, schema, os.path.join(migrations_dir, name))
        run_psql(database_url,
                 f'INSERT INTO "{schema}".tl_schema_history (version, name) '
                 f"VALUES ({version}, '{name}')")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--service", required=True, help="service name, e.g. Accounting")
    parser.add_argument("--tenant", action="append", required=True,
                        help="tenant id (repeatable)")
    parser.add_argument("--database-url", required=True)
    parser.add_argument("--migrations-dir", default=None,
                        help="defaults to src/services/<Service>/migrations")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    migrations_dir = args.migrations_dir
    if migrations_dir is None:
        repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
        migrations_dir = os.path.join(repo_root, "src", "services", args.service, "migrations")
    if not os.path.isdir(migrations_dir):
        raise SystemExit(f"no migrations directory: {migrations_dir}")

    print(f"Migrating service {args.service} ({migrations_dir})")
    for tenant in args.tenant:
        migrate_tenant(args.database_url, migrations_dir, tenant, args.dry_run)
    print("done")


if __name__ == "__main__":
    main()
