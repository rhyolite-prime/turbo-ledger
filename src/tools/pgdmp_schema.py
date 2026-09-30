#!/usr/bin/env python3
"""
Turbo Ledger — extract schema SQL from a pg_dump *custom format* archive
(PGDMP) without pg_restore.

Reads the archive TOC (which stores each object's CREATE statement as plain
text) and prints the definitions in archive order, approximating
`pg_restore --schema-only --no-owner --no-privileges`.

Supports archive versions 1.12 – 1.16 (pg_dump 9.x – 18.x).

Usage: pgdmp_schema.py DUMPFILE [--sections pre-data,post-data]
"""
import argparse
import struct
import sys


class Reader:
    def __init__(self, data: bytes):
        self.data = data
        self.pos = 0

    def byte(self) -> int:
        b = self.data[self.pos]
        self.pos += 1
        return b

    def take(self, n: int) -> bytes:
        out = self.data[self.pos:self.pos + n]
        self.pos += n
        return out


class PgDumpArchive:
    def __init__(self, path: str):
        with open(path, "rb") as fh:
            self.r = Reader(fh.read())
        self._read_header()
        self._read_toc()

    # -- primitives ---------------------------------------------------------
    def _int(self) -> int:
        sign = self.r.byte()
        value = 0
        for i in range(self.int_size):
            value |= self.r.byte() << (8 * i)
        return -value if sign else value

    def _str(self):
        length = self._int()
        if length < 0:
            return None
        return self.r.take(length).decode("utf-8", errors="replace")

    def _offset(self) -> int:
        self.r.byte()  # offset flag (known/unknown)
        value = 0
        for i in range(self.off_size):
            value |= self.r.byte() << (8 * i)
        return value

    # -- header ---------------------------------------------------------------
    def _read_header(self):
        if self.r.take(5) != b"PGDMP":
            raise SystemExit("not a pg_dump custom-format archive")
        vmaj, vmin, vrev = self.r.byte(), self.r.byte(), self.r.byte()
        self.version = (vmaj, vmin)
        self.int_size = self.r.byte()
        self.off_size = self.r.byte()
        fmt = self.r.byte()
        if fmt != 1:  # archCustom
            raise SystemExit(f"unsupported archive format code {fmt}")
        if self.version >= (1, 15):
            self.r.byte()  # compression algorithm
        else:
            self._int()    # legacy compression level
        for _ in range(7):  # sec/min/hour/mday/mon/year/isdst
            self._int()
        self.dbname = self._str()
        self.server_version = self._str()
        self.dump_version = self._str()

    # -- table of contents -------------------------------------------------------
    def _read_toc(self):
        count = self._int()
        self.entries = []
        for _ in range(count):
            e = {}
            e["dump_id"] = self._int()
            e["had_dumper"] = self._int()
            e["tableoid"] = self._str()
            e["oid"] = self._str()
            e["tag"] = self._str()
            e["desc"] = self._str()
            e["section"] = self._int() if self.version >= (1, 11) else 0
            e["defn"] = self._str()
            e["drop_stmt"] = self._str()
            e["copy_stmt"] = self._str()
            e["namespace"] = self._str()
            e["tablespace"] = self._str() if self.version >= (1, 10) else None
            e["tableam"] = self._str() if self.version >= (1, 14) else None
            if self.version >= (1, 16):
                e["relkind"] = self._int()
            e["owner"] = self._str()
            self._str()  # withOids (legacy "true"/"false")
            deps = []
            while True:
                dep = self._str()
                if dep is None:
                    break
                deps.append(dep)
            e["deps"] = deps
            e["data_pos"] = self._offset()
            self.entries.append(e)


# teSection enum: SECTION_NONE=1, SECTION_PRE_DATA=2, SECTION_DATA=3, SECTION_POST_DATA=4
SECTION_NAMES = {1: "none", 2: "pre-data", 3: "data", 4: "post-data"}

SKIP_DESCS = {
    "COMMENT", "ACL", "DEFAULT ACL",  # privileges/comments: not wanted in baselines
    "DATABASE", "DATABASE PROPERTIES",
    "SEARCHPATH", "ENCODING", "STDSTRINGS",
}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dumpfile")
    parser.add_argument("--sections", default="pre-data,post-data",
                        help="comma list of pre-data,data,post-data")
    parser.add_argument("--list", action="store_true", help="print TOC only")
    args = parser.parse_args()

    archive = PgDumpArchive(args.dumpfile)
    wanted = {s.strip() for s in args.sections.split(",")}

    if args.list:
        for e in archive.entries:
            print(f"{e['dump_id']:5d} {SECTION_NAMES.get(e['section'], '?'):9s} "
                  f"{e['desc'] or '':30s} {e['tag'] or ''}")
        return

    print(f"-- extracted from {args.dumpfile}")
    print(f"-- source database: {archive.dbname} "
          f"(server {archive.server_version}, pg_dump {archive.dump_version}, "
          f"archive v{archive.version[0]}.{archive.version[1]})")
    print()
    for e in archive.entries:
        section = SECTION_NAMES.get(e["section"])
        if section not in wanted:
            continue
        if not e["defn"]:
            continue
        if (e["desc"] or "") in SKIP_DESCS:
            continue
        print(f"--\n-- {e['desc']}: {e['tag']}\n--")
        print(e["defn"].rstrip())
        print()


if __name__ == "__main__":
    main()
