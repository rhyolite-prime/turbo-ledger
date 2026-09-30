#!/usr/bin/env python3
"""
Turbo Ledger CI lint — every drogon coroutine handler must co_return.

A `Task<...>` function body that never reaches a co_return / co_await is
undefined behaviour (the coroutine falls off the end). This has bitten us
before (empty Accounting controller bodies); this check fails CI when it
happens again.

Usage: check_coroutines.py [root_dir]   (defaults to src/services + src/libs)
"""
import os
import re
import sys

SIGNATURE = re.compile(r"\bTask\s*<[^;{]*?>\s*[\w:]+\s*\([^;{]*\)\s*(?:const\s*)?\{")


def find_body(text: str, open_brace_idx: int) -> str:
    depth = 0
    for i in range(open_brace_idx, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return text[open_brace_idx : i + 1]
    return text[open_brace_idx:]


def check_file(path: str):
    with open(path, "r", encoding="utf-8", errors="replace") as fh:
        text = fh.read()
    problems = []
    for m in SIGNATURE.finditer(text):
        open_brace = text.index("{", m.start())
        body = find_body(text, open_brace)
        if "co_return" not in body and "co_await" not in body and "co_yield" not in body:
            line = text[: m.start()].count("\n") + 1
            sig = " ".join(m.group(0).split())[:100]
            problems.append((line, sig))
    return problems


def main() -> None:
    roots = sys.argv[1:] or ["src/services", "src/libs"]
    failures = 0
    for root in roots:
        for dirpath, dirnames, filenames in os.walk(root):
            dirnames[:] = [d for d in dirnames if d not in
                           ("build", "external_deps", ".git", "node_modules")]
            for name in filenames:
                if not name.endswith((".cc", ".cpp", ".h", ".hpp")):
                    continue
                path = os.path.join(dirpath, name)
                for line, sig in check_file(path):
                    print(f"{path}:{line}: coroutine without co_return/co_await: {sig}")
                    failures += 1
    if failures:
        print(f"\ncheck_coroutines: {failures} offending coroutine(s)")
        sys.exit(1)
    print("check_coroutines: OK")


if __name__ == "__main__":
    main()
