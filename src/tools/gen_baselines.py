#!/usr/bin/env python3
"""
Turbo Ledger — convert the pg_dump files in src/scripts/ into V001 baseline
migrations (schema-per-tenant compatible).

Plain-SQL dumps are sanitised directly; custom-format (PGDMP) dumps are first
converted with pg_restore (set PG_RESTORE to point at a new-enough binary).

Sanitisation:
  * drop \\restrict / \\unrestrict psql metacommands
  * drop SET / set_config session statements (the runner pins search_path)
  * drop OWNER TO / GRANT / REVOKE
  * strip the "public." schema qualifier so objects land in the tenant schema

Usage:  gen_baselines.py [--only TlAccounting] [--scripts-dir src/scripts]
"""
import argparse
import os
import re
import subprocess
import sys

# dump file -> service directory
DUMP_TO_SERVICE = {
    "TlIdentity.sql": "Identity",
    "TlAccounting.sql": "Accounting",
    "TlCustomerDb.sql": "Customer",
    "TlDamDb.sql": "DepositAccountManagement",
    "TlGroupDb.sql": "Group",
    "TlOrganizationDb.sql": "Organization",
    "TlPortfolio.sql": "Portfolio",
    "TlSystemConfigDb.sql": "SystemConfig",
}

DROP_LINE_PATTERNS = [
    # uuid-ossp is replaced by the core gen_random_uuid() (PG13+): keeps the
    # baselines runnable on minimal builds without contrib extensions.
    re.compile(r'^CREATE EXTENSION IF NOT EXISTS "uuid-ossp"'),
    re.compile(r'^COMMENT ON EXTENSION "?uuid-ossp"?'),
    re.compile(r"^\\(un)?restrict\b"),
    re.compile(r"^SET\s+\w+"),
    re.compile(r"^SELECT pg_catalog\.set_config"),
    re.compile(r"^ALTER .* OWNER TO\b"),
    re.compile(r"^GRANT\b"),
    re.compile(r"^REVOKE\b"),
    re.compile(r"^CREATE SCHEMA public\b"),
    re.compile(r"^COMMENT ON SCHEMA public\b"),
]


def is_binary_dump(path: str) -> bool:
    with open(path, "rb") as fh:
        return fh.read(5) == b"PGDMP"


def to_sql(path: str) -> str:
    if is_binary_dump(path):
        # Prefer pg_restore when a new-enough binary is around...
        pg_restore = os.environ.get("PG_RESTORE", "pg_restore")
        try:
            result = subprocess.run(
                [pg_restore, "--no-owner", "--no-privileges", "--schema-only", "-f", "-", path],
                capture_output=True, text=True)
            if result.returncode == 0:
                return result.stdout
        except FileNotFoundError:
            pass  # no pg_restore on PATH; use the built-in reader
        # ...otherwise fall back to our own PGDMP TOC reader (src/tools/pgdmp_schema.py),
        # which handles archive versions newer than the local pg_restore.
        script = os.path.join(os.path.dirname(os.path.abspath(__file__)), "pgdmp_schema.py")
        result = subprocess.run(
            [sys.executable, script, path, "--sections", "pre-data,post-data"],
            capture_output=True, text=True)
        if result.returncode != 0:
            raise RuntimeError(
                f"could not read {os.path.basename(path)} with pg_restore or "
                f"pgdmp_schema.py:\n{result.stderr.strip()}")
        return result.stdout
    with open(path, "r", encoding="utf-8", errors="replace") as fh:
        return fh.read()


def sanitise(sql: str) -> str:
    out_lines = []
    for line in sql.splitlines():
        stripped = line.strip()
        if any(p.match(stripped) for p in DROP_LINE_PATTERNS):
            continue
        # unqualify the public schema so objects land in the tenant schema
        line = re.sub(r"\bpublic\.", "", line)
        # portable UUID default (uuid-ossp -> core gen_random_uuid, PG13+)
        line = line.replace("uuid_generate_v4()", "gen_random_uuid()")
        out_lines.append(line)
    body = "\n".join(out_lines)
    body = re.sub(r"\n{3,}", "\n\n", body)
    return body.strip() + "\n"


HEADER = """--
-- V001__baseline.sql — generated from src/scripts/{dump} by src/tools/gen_baselines.py
--
-- Applied per tenant into schema t_<tenantId> by src/tools/migrate.py
-- (which pins search_path; do NOT add SET search_path here).
--

"""


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--scripts-dir", default=None)
    parser.add_argument("--only", action="append", default=None,
                        help="limit to specific dump basenames (without .sql)")
    args = parser.parse_args()

    repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
    scripts_dir = args.scripts_dir or os.path.join(repo_root, "src", "scripts")

    failures = []
    for dump, service in DUMP_TO_SERVICE.items():
        if args.only and dump.removesuffix(".sql") not in args.only:
            continue
        src = os.path.join(scripts_dir, dump)
        if not os.path.exists(src):
            print(f"skip {dump}: not found")
            continue
        dest_dir = os.path.join(repo_root, "src", "services", service, "migrations")
        os.makedirs(dest_dir, exist_ok=True)
        dest = os.path.join(dest_dir, "V001__baseline.sql")
        try:
            sql = sanitise(to_sql(src))
        except RuntimeError as e:
            print(f"FAIL {dump}: {e}", file=sys.stderr)
            failures.append(dump)
            continue
        with open(dest, "w", encoding="utf-8") as fh:
            fh.write(HEADER.format(dump=dump))
            fh.write(sql)
        print(f"wrote {os.path.relpath(dest, repo_root)} ({len(sql.splitlines())} lines)")

    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
