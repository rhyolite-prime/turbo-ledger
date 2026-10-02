#!/usr/bin/env python3
"""
gen_postman.py — generate Postman v2.1 collections for a phase of
turbo-ledger controllers, mirroring the hand-authored style of
src/docs/TurboLedger-Phase{0..5}.postman_collection.json:

  - one top-level folder per controller ("resource"), items in declaration
    order, named from the handler method name;
  - GET/DELETE requests have no body; POST/PUT bodies are "auto-derived from
    the actual field reads" in the underlying service method (asStringOr/
    asIntOr/asDoubleOr/asBoolOr/moneyOr/dateOr/body.isMember/body[...]
    patterns), same disclosed heuristic used by the earlier hand-authored
    collections;
  - a "0 - Auth" folder identical in shape to the earlier phases (tenant
    admin sign-in, sets {{token}});
  - collection variables baseUrl / tenantId / token.

This is a best-effort generator, not a guarantee of 100% correct example
payloads — placeholder values are generic and so is the field-name-based
type/example inference. Cross-check against the real controller/service
source for anything load-bearing.

Usage:
    python3 src/tools/gen_postman.py
(edit the PHASES table below to add/adjust phases; it already covers 6-9)
"""
import json
import re
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / "src"
DOCS = SRC / "docs"

HTTP_VERBS = {"Get", "Post", "Put", "Delete", "Patch"}


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")


def extract_prefix(header_text: str) -> str:
    m = re.search(r'PREFIX\s*=\s*"([^"]+)"', header_text)
    return m.group(1) if m else ""


def split_top_level_commas(s: str):
    """Split on commas that are not inside parens/quotes."""
    parts = []
    depth = 0
    cur = []
    in_str = False
    i = 0
    while i < len(s):
        c = s[i]
        if in_str:
            cur.append(c)
            if c == '"' and s[i - 1] != "\\":
                in_str = False
            i += 1
            continue
        if c == '"':
            in_str = True
            cur.append(c)
        elif c in "([":
            depth += 1
            cur.append(c)
        elif c in ")]":
            depth -= 1
            cur.append(c)
        elif c == "," and depth == 0:
            parts.append("".join(cur))
            cur = []
        else:
            cur.append(c)
        i += 1
    if cur:
        parts.append("".join(cur))
    return [p.strip() for p in parts]


def eval_path_expr(expr: str, prefix: str) -> str:
    """Evaluate a C++ expression like std::string(PREFIX) + "foo/" + "{1}/bar"
    into the literal path string, given the controller's PREFIX value."""
    expr = expr.strip()
    parts = [p.strip() for p in expr.split("+")]
    out = []
    for p in parts:
        if p in ("std::string(PREFIX)", "PREFIX", "std::string(PREFIX )"):
            out.append(prefix)
        elif p.startswith('"') and p.endswith('"'):
            out.append(p[1:-1])
        else:
            # unexpected dynamic segment; best-effort passthrough
            out.append(p)
    return "".join(out)


def parse_controller(header_path: Path):
    """Return (class_name, prefix, [ (method_name, path, verbs) ]) for one
    controller header's METHOD_LIST_BEGIN..END block."""
    text = read(header_path)
    class_m = re.search(r"class\s+(\w+)\s*:\s*public\s+drogon::HttpController", text)
    class_name = class_m.group(1) if class_m else header_path.stem
    prefix = extract_prefix(text)

    block_m = re.search(r"METHOD_LIST_BEGIN(.*?)METHOD_LIST_END", text, re.S)
    if not block_m:
        return class_name, prefix, []
    block = block_m.group(1)

    routes = []
    # Each statement: ADD_METHOD_TO(Class::method, <pathExpr>, <Verb...>, FILTER);
    for stmt_m in re.finditer(r"ADD_METHOD_TO\s*\((.*?)\)\s*;", block, re.S):
        stmt = stmt_m.group(1)
        args = split_top_level_commas(stmt)
        if len(args) < 3:
            continue
        handler = args[0].strip()
        method_name = handler.split("::")[-1].strip()
        path_expr = args[1].strip()
        # remaining args up to (but excluding) the trailing FILTER token are verbs
        rest = args[2:]
        verbs = []
        for a in rest:
            a = a.strip()
            if a in HTTP_VERBS:
                verbs.append(a)
            elif a == "Options":
                continue
            else:
                # FILTER constant (e.g. FILTER, "turbo::...") — stop
                break
        if not verbs:
            continue
        path = eval_path_expr(path_expr, prefix)
        routes.append((method_name, path, verbs))
    return class_name, prefix, routes


# ---------------------------------------------------------------------------
# Body inference: find the handler's underlying service method and harvest
# field reads from it.
# ---------------------------------------------------------------------------

FIELD_RE = re.compile(
    r"\b(asStringOr|asIntOr|asInt64Or|asDoubleOr|asBoolOr|moneyOr|dateOr)\s*\(\s*(?:\*?\s*)?body\s*,\s*\"([A-Za-z0-9_]+)\""
)
MEMBER_RE = re.compile(r'body(?:\[\")?\.isMember\(\s*"([A-Za-z0-9_]+)"\s*\)')
INDEX_RE = re.compile(r'body\["([A-Za-z0-9_]+)"\]')

TYPE_BY_FN = {
    "asStringOr": "string",
    "asIntOr": "int",
    "asInt64Or": "int",
    "asDoubleOr": "number",
    "asBoolOr": "bool",
    "moneyOr": "number",
    "dateOr": "date",
}


def harvest_fields(text: str):
    """Return an ordered dict of fieldName -> inferred type from a chunk of
    C++ source (a single service method body, or a whole file as fallback)."""
    fields = {}
    for fn, name in FIELD_RE.findall(text):
        fields.setdefault(name, TYPE_BY_FN.get(fn, "string"))
    for name in MEMBER_RE.findall(text):
        fields.setdefault(name, "string")
    for name in INDEX_RE.findall(text):
        fields.setdefault(name, "string")
    return fields


def find_function_body(cc_text: str, class_name: str, method_name: str):
    """Extract the source of `<ReturnType> Class::method(...) { ... }` up to
    (but not including) the next top-level function definition of the same
    qualified-name style, by locating the next `ClassName::` occurrence (or
    EOF)."""
    pat = re.compile(rf"\b{re.escape(class_name)}::{re.escape(method_name)}\s*\(")
    m = pat.search(cc_text)
    if not m:
        return ""
    start = m.start()
    nxt = re.search(rf"\b{re.escape(class_name)}::\w+\s*\(", cc_text[m.end():])
    end = m.end() + nxt.start() if nxt else len(cc_text)
    return cc_text[start:end]


def find_free_function_body(text: str, func_name: str):
    """Extract the source of a file-scope free function (not a class member,
    e.g. a small `static`/anonymous-namespace helper like
    `Task<Json::Value> postCashierTransaction(...) { ... }`) by locating a
    definition-shaped line (starts at BOL with return-type-like tokens, not
    an invocation) and brace-counting to the matching close brace."""
    pat = re.compile(rf"(?m)^[A-Za-z_][\w:<>,\s\*&]*\b{re.escape(func_name)}\s*\(")
    m = pat.search(text)
    if not m:
        return ""
    start = m.start()
    brace_idx = text.find("{", m.end())
    if brace_idx == -1:
        return ""
    depth = 0
    i = brace_idx
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return text[start:i + 1]
        i += 1
    return ""


def find_handler_body_and_service_calls(controller_cc_text: str, class_name: str, method_name: str):
    body = find_function_body(controller_cc_text, class_name, method_name)
    calls = re.findall(r"svc\(\)\.(\w+)\s*\(", body)
    return body, calls


FORWARD_CALL_RE = re.compile(
    r'\.call\(\s*systemCtx\((?:[^()]|\([^()]*\))*\)\s*,\s*drogon::(Get|Post|Put|Delete|Patch)\s*,\s*'
    r'((?:"[^"]*"|\w+)(?:\s*\+\s*(?:"[^"]*"|\w+))*)'
)


def _forward_path_segments(expr):
    """Tokenize a (possibly concatenated) C++ path expression like
    '"/api/v1/savingsaccounts/" + id + "/update"' into path segments, where
    a segment built purely from a non-literal identifier (no surrounding
    literal text) is represented as the sentinel "\x00" (a dynamic /
    unknown-value segment) so it can be matched against either a literal
    route segment or a `{N}` route placeholder."""
    tokens = re.findall(r'"([^"]*)"|(\w+)', expr)
    s = ""
    for lit, var in tokens:
        if var:
            s += "\x00"
        else:
            s += lit
    return s.split("/")


def _route_template_segments(path_template):
    return path_template.split("/")


def _segments_match(call_segments, route_segments):
    """Return (True, score) if the two segment lists are compatible, else
    False. `score` counts exact literal equalities, used to pick the best
    candidate when more than one route matches (e.g. an ambiguous dynamic
    segment)."""
    if len(call_segments) != len(route_segments):
        return False
    score = 0
    for c, r in zip(call_segments, route_segments):
        if re.fullmatch(r"\{\d+\}", r):
            continue  # route wildcard segment: matches anything
        if c == r:
            score += 1
            continue
        if c == "\x00":
            continue  # purely-dynamic call segment matches any literal route segment
        return False
    return True, score


def build_global_route_index():
    """Scan every controller header in the whole repo and build a list of
    (verb, path_template_segments, controller_cc_path, class_name,
    method_name), so a thin pass-through composition call (SelfService ->
    Portfolio, etc.) can be resolved to the real downstream handler that
    reads the body -- even when the forwarded path is a concatenated
    expression (literal + variable segments) and/or the downstream route
    uses a generic `{N}` path placeholder in a position that the forward
    call fills with a literal "kind" segment (e.g. ".../accounts/{1}/create"
    called as ".../accounts/share/create")."""
    entries = []
    for header in sorted((SRC / "services").glob("*/controllers/*.h")):
        class_name, prefix, routes = parse_controller(header)
        cc = header.with_suffix(".cc")
        for method_name, path, verbs in routes:
            segs = _route_template_segments(path)
            for verb in verbs:
                entries.append((verb, segs, cc, class_name, method_name))
    return entries


def resolve_forward_call(route_index, verb, path_expr):
    call_segs = _forward_path_segments(path_expr)
    best = None
    best_score = -1
    for rverb, rsegs, cc, class_name, method_name in route_index:
        if rverb != verb:
            continue
        result = _segments_match(call_segs, rsegs)
        if not result:
            continue
        _, score = result
        if score > best_score:
            best_score = score
            best = (cc, class_name, method_name)
    return best


def build_global_service_texts():
    """Returns (ordered_texts, by_service_dir) where by_service_dir maps a
    service directory name (e.g. "Portfolio") to the list of texts of its
    own services/*.cc files, so callers can search a specific microservice's
    own sources first instead of accidentally matching a same-named method
    defined in a different, unrelated service."""
    paths = sorted((SRC / "services").glob("*/services/*.cc"))
    texts = [read(p) for p in paths]
    by_service_dir = {}
    for p, t in zip(paths, texts):
        # path looks like .../src/services/<ServiceDir>/services/<File>.cc
        svc_dir = p.parent.parent.name
        by_service_dir.setdefault(svc_dir, []).append(t)
    return texts, by_service_dir


GLOBAL_ROUTE_INDEX = None
GLOBAL_SERVICE_TEXTS = None
GLOBAL_SERVICE_TEXTS_BY_DIR = None


def _lazy_globals():
    global GLOBAL_ROUTE_INDEX, GLOBAL_SERVICE_TEXTS, GLOBAL_SERVICE_TEXTS_BY_DIR
    if GLOBAL_ROUTE_INDEX is None:
        GLOBAL_ROUTE_INDEX = build_global_route_index()
        GLOBAL_SERVICE_TEXTS, GLOBAL_SERVICE_TEXTS_BY_DIR = build_global_service_texts()
    return GLOBAL_ROUTE_INDEX, GLOBAL_SERVICE_TEXTS


_controller_cc_cache = {}


def _read_cached(path: Path) -> str:
    if path not in _controller_cc_cache:
        _controller_cc_cache[path] = read(path) if path.exists() else ""
    return _controller_cc_cache[path]


_CPP_KEYWORDS_NOT_CALLS = {
    "if", "while", "for", "switch", "return", "throw", "catch", "co_await",
    "co_return", "co_yield", "sizeof", "static_cast", "dynamic_cast",
    "const_cast", "reinterpret_cast", "using", "namespace", "class", "struct",
}


def harvest_private_helpers(chunk, svc_class, svc_text, visited=None, max_depth=2):
    """Some service methods delegate to a same-class private helper rather
    than either reading fields locally or forwarding to another
    microservice (e.g. `createGroup(ctx, body) { return createEntity(ctx,
    false, body); }`, where `createEntity` is the one that actually reads
    `body`'s fields). Scan `chunk` for calls that resolve to another method
    of the *same* class in the *same* source file and recurse into those."""
    if visited is None:
        visited = set()
    if max_depth < 0 or not svc_text:
        return {}
    candidates = re.findall(r"\b([A-Za-z_]\w*)\s*\(", chunk)
    for cand in candidates:
        if cand in _CPP_KEYWORDS_NOT_CALLS or cand in visited:
            continue
        visited.add(cand)
        sub_chunk = ""
        if re.search(rf"\b{re.escape(svc_class)}::{re.escape(cand)}\s*\(", svc_text):
            sub_chunk = find_function_body(svc_text, svc_class, cand)
        if not sub_chunk:
            # Fall back to a same-file free function / static helper (not a
            # class member) — e.g. `postCashierTransaction(...)` called by
            # `TellerService::allocateCash` but defined at file scope.
            sub_chunk = find_free_function_body(svc_text, cand)
        if not sub_chunk:
            continue
        f = harvest_fields(sub_chunk)
        if f:
            return f
        nested = harvest_private_helpers(sub_chunk, svc_class, svc_text, visited, max_depth - 1)
        if nested:
            return nested
    return {}


def harvest_for_handler(controller_cc_text, class_name, method_name, service_sources, depth=0):
    """Find the controller handler, follow to the service method(s) it
    calls, and harvest field reads from those. If a service method turns out
    to be a thin pass-through composition call to another microservice
    (`.call(systemCtx(...), drogon::Verb, "/api/v1/.../literal", body)`)
    with no local field reads of its own, resolve the literal path through
    the global route index and recurse into the real downstream handler
    (capped depth to avoid pathological cycles)."""
    _, calls = find_handler_body_and_service_calls(controller_cc_text, class_name, method_name)
    fields = {}
    route_index, global_texts = _lazy_globals()
    # Search own/explicitly-passed sources first (most specific), then the
    # full repo-wide corpus as a fallback. NOTE: do not keep prepending the
    # *original* top-level service_sources on every recursive hop below —
    # that caused cross-service name collisions (e.g. two services each
    # defining a differently-scoped method with the same short name, like
    # "createLoan") to resolve to the wrong, already-visited service and
    # self-loop until the depth cap, instead of reaching the real downstream
    # handler. Each recursive call instead searches its own target service's
    # sources first.
    for call in calls:
        svc_class, chunk = None, ""
        for svc_text in service_sources + global_texts:
            m = re.search(rf"\b(\w+)::{re.escape(call)}\s*\(", svc_text)
            if m:
                svc_class = m.group(1)
                chunk = find_function_body(svc_text, svc_class, call)
                if chunk:
                    break
        if not chunk:
            continue
        local_fields = harvest_fields(chunk)
        if local_fields:
            fields.update(local_fields)
            continue
        if depth >= 3:
            continue
        # A composition method may make *several* forward calls (e.g. a GET
        # to re-read/own-ership-check a record, then a PUT/POST that
        # actually carries the mutating body). Try every forward call found
        # in the chunk, preferring non-GET ones first (those are the ones
        # most likely to carry the interesting body), and use the first
        # one whose resolved downstream handler actually yields fields.
        fwd_matches = list(FORWARD_CALL_RE.finditer(chunk))
        fwd_matches.sort(key=lambda fm: 0 if fm.group(1) != "Get" else 1)
        resolved_fields = {}
        for fwd in fwd_matches:
            verb, path_expr = fwd.group(1), fwd.group(2)
            target = resolve_forward_call(route_index, verb, path_expr)
            if not target:
                continue
            target_cc_path, target_class, target_method = target
            target_cc_text = _read_cached(target_cc_path)
            # Prioritize the downstream service's own services/*.cc sources
            # so we don't accidentally re-match a same-named method still
            # sitting in the *caller's* service sources (which would
            # otherwise sit at the front of the search order and cause an
            # infinite self-loop).
            svc_dir_name = target_cc_path.parent.parent.name
            own_sources = (GLOBAL_SERVICE_TEXTS_BY_DIR or {}).get(svc_dir_name, [])
            next_sources = list(own_sources) + global_texts
            resolved_fields = harvest_for_handler(
                target_cc_text, target_class, target_method, next_sources, depth + 1
            )
            if resolved_fields:
                break
        if not resolved_fields:
            resolved_fields = harvest_private_helpers(chunk, svc_class, svc_text)
        fields.update(resolved_fields)
    return fields


def infer_body_fields(controller_cc_text, service_sources, class_name, method_name):
    return harvest_for_handler(controller_cc_text, class_name, method_name, service_sources)


# ---------------------------------------------------------------------------
# Example-value heuristics
# ---------------------------------------------------------------------------

def example_value(field: str, ftype: str):
    lf = field.lower()
    if ftype == "bool":
        return True
    if ftype == "date":
        return "2026-01-15"
    if ftype in ("int", "number"):
        if lf.endswith("id"):
            return 1
        if "date" in lf:
            return "2026-01-15"
        if "rate" in lf or "amount" in lf or "principal" in lf or "balance" in lf:
            return 100 if ftype == "int" else 100.0
        return 1 if ftype == "int" else 1.0
    # strings
    if lf.endswith("id") and lf != "id":
        return "1"
    if "date" in lf:
        return "2026-01-15"
    if lf in ("currencycode",):
        return "USD"
    if "email" in lf:
        return "user@example.com"
    if "mobileno" in lf or "phone" in lf:
        return "+10000000000"
    if "name" in lf:
        return "Example " + field
    if "code" in lf:
        return "EXAMPLE_CODE"
    if "description" in lf or "note" in lf or "remark" in lf:
        return "Example " + field
    if "externalid" in lf:
        return "EXT-0001"
    if "username" in lf:
        return "exampleuser"
    if "password" in lf:
        return "Passw0rd!"
    return "example"


def build_body_json(fields: dict):
    if not fields:
        return None
    obj = {}
    for name, ftype in fields.items():
        obj[name] = example_value(name, ftype)
    return json.dumps(obj, indent=2)


# ---------------------------------------------------------------------------
# Path -> Postman URL conversion
# ---------------------------------------------------------------------------

def humanize_segment(seg: str) -> str:
    # "savingsaccounts" -> "Savings Accounts", "cashiersjournal" -> "Cashiers Journal"
    seg = seg.replace("-", " ")
    return seg


def folder_name_for_class(class_name: str) -> str:
    name = class_name
    if name.endswith("Controller"):
        name = name[: -len("Controller")]
    # split CamelCase into words
    words = re.findall(r"[A-Z][a-z0-9]*|[A-Z]+(?![a-z])", name)
    return " ".join(words) if words else name


def method_display_name(method_name: str) -> str:
    words = re.findall(r"[A-Z][a-z0-9]*|[a-z0-9]+|[A-Z]+(?![a-z])", method_name)
    words = [w for w in words if w]
    title = " ".join(w.capitalize() if not w.isupper() else w for w in words)
    return title


# Segments that describe an *action*, not a resource — never use these as
# the basis for naming the placeholder that follows/precedes them.
VERB_SEGMENTS = {
    "api", "v1", "get-all", "get-detail", "get-steps", "available-steps",
    "create", "update", "delete", "template", "command", "activate",
    "approve", "reject", "undo", "status", "run", "run-now", "transfer",
    "prepare", "adjust", "close",
}

# Placeholders immediately after one of these literal segments get a fixed,
# descriptive name + example value instead of "<resource>Id".
SPECIAL_PRECEDING = {
    "command": ("command", "approve"),
    "short-name": ("shortName", "example-job"),
}


def path_placeholder_names(path: str, resource_hint: str):
    """Walk the path, naming each {N} placeholder after the nearest
    preceding *resource-like* literal segment (singularized, +Id), skipping
    verb/action segments. Returns {segment: (name, example_value)}."""
    segs = [s for s in path.strip("/").split("/")]
    names = {}
    last_literal = resource_hint
    immediate_prev = None
    used = set()
    for seg in segs:
        m = re.fullmatch(r"\{(\d+)\}", seg)
        if m:
            if immediate_prev in SPECIAL_PRECEDING:
                name, example = SPECIAL_PRECEDING[immediate_prev]
            else:
                base = last_literal.rstrip("s")
                if base.endswith("ie"):
                    base = base[:-2] + "y"
                name = base + "Id" if not base.lower().endswith("id") else base
                example = "1"
            if name in used:
                name = f"{name}{m.group(1)}"
            used.add(name)
            names[seg] = (name, example)
        else:
            immediate_prev = seg
            if seg not in VERB_SEGMENTS:
                last_literal = seg
    return names


def to_postman_url(base_var: str, path: str, resource_hint: str):
    placeholder_names = path_placeholder_names(path, resource_hint)
    segs = [s for s in path.strip("/").split("/") if s != ""]
    raw_segs = []
    path_list = []
    variables = []
    for seg in segs:
        m = re.fullmatch(r"\{(\d+)\}", seg)
        if m:
            name, example = placeholder_names.get(seg, (f"id{m.group(1)}", "1"))
            raw_segs.append(f":{name}")
            path_list.append(f":{name}")
            variables.append({"key": name, "value": example})
        else:
            raw_segs.append(seg)
            path_list.append(seg)
    raw = "{{" + base_var + "}}/" + "/".join(raw_segs)
    url = {
        "raw": raw,
        "host": ["{{" + base_var + "}}"],
        "path": path_list,
    }
    if variables:
        url["variable"] = variables
    return url


# ---------------------------------------------------------------------------
# Postman item construction
# ---------------------------------------------------------------------------

def make_request_item(name, verb, path, body_json, resource_hint):
    headers = [
        {"key": "TL-Tenant-Id", "value": "{{tenantId}}"},
        {"key": "Authorization", "value": "Bearer {{token}}"},
    ]
    request = {
        "method": verb.upper(),
        "header": headers,
        "url": to_postman_url("baseUrl", path, resource_hint),
    }
    if body_json is not None:
        headers.append({"key": "Content-Type", "value": "application/json"})
        request["body"] = {"mode": "raw", "raw": body_json}
    return {"name": name, "request": request, "response": []}


def auth_folder():
    return {
        "name": "0 \u00b7 Auth",
        "item": [
            {
                "name": "Tenant admin sign in",
                "request": {
                    "method": "POST",
                    "header": [
                        {"key": "TL-Tenant-Id", "value": "{{tenantId}}"},
                        {"key": "Content-Type", "value": "application/json"},
                    ],
                    "url": {
                        "raw": "{{baseUrl}}/api/v1/auth/signin",
                        "host": ["{{baseUrl}}"],
                        "path": ["api", "v1", "auth", "signin"],
                    },
                    "body": {
                        "mode": "raw",
                        "raw": '{\n  "usernameOrEmail": "admin",\n  "password": "Passw0rd!"\n}',
                    },
                },
                "response": [],
                "event": [
                    {
                        "listen": "test",
                        "script": {
                            "type": "text/javascript",
                            "exec": [
                                "const d = pm.response.json();",
                                "pm.test('signin ok', () => pm.expect(d.success).to.be.true);",
                                "pm.collectionVariables.set('token', d.result.token);",
                            ],
                        },
                    }
                ],
            }
        ],
    }


def build_collection(info_name, description, folders):
    return {
        "info": {
            "_postman_id": str(uuid.uuid4()),
            "name": info_name,
            "description": description,
            "schema": "https://schema.getpostman.com/json/collection/v2.1.0/collection.json",
        },
        "variable": [
            {"key": "baseUrl", "value": "http://127.0.0.1:7499"},
            {"key": "tenantId", "value": "acme_bank"},
            {"key": "token", "value": ""},
        ],
        "item": [auth_folder()] + folders,
    }


# ---------------------------------------------------------------------------
# Per-phase controller -> service-source-file mapping
# ---------------------------------------------------------------------------

def gen_phase(phase_no: int, title: str, description: str, controllers: list, service_sources: list, out_name: str = None):
    """controllers: list of Path to header files (in display order).
    service_sources: list of Path to .cc files to search for field reads
    (usually the one big <Service>.cc for that microservice, but can span
    several files e.g. SelfService's controllers + services)."""
    service_texts = [read(p) for p in service_sources if p.exists()]
    folders = []
    total = 0
    for header in controllers:
        cc = header.with_suffix(".cc")
        controller_cc_text = read(cc) if cc.exists() else ""
        class_name, prefix, routes = parse_controller(header)
        resource_hint = prefix.strip("/").split("/")[-1] or class_name.lower()
        items = []
        for method_name, path, verbs in routes:
            for verb in verbs:
                body_json = None
                if verb in ("Post", "Put", "Patch"):
                    fields = infer_body_fields(controller_cc_text, service_texts, class_name, method_name)
                    body_json = build_body_json(fields)
                display = method_display_name(method_name)
                if len(verbs) > 1:
                    display = f"{display} ({verb})"
                items.append(make_request_item(display, verb, path, body_json, resource_hint))
                total += 1
        if items:
            folders.append({"name": folder_name_for_class(class_name), "item": items})
    coll = build_collection(title, description, folders)
    out_path = DOCS / (out_name or f"TurboLedger-Phase{phase_no}.postman_collection.json")
    out_path.write_text(json.dumps(coll, indent=2) + "\n", encoding="utf-8")
    print(f"Phase {phase_no}: wrote {out_path} ({total} requests across {len(folders)} folders)")
    return out_path


def main():
    portfolio_dir = SRC / "services" / "Portfolio" / "controllers"
    portfolio_svc = SRC / "services" / "Portfolio" / "services" / "PortfolioService.cc"
    phase6_desc = (
        "Phase 6 surface through the API Gateway: loans + loanproducts, floatingrates, rates, "
        "rescheduleloans, loan-collateral-management, provisioningcategory/provisioningcriteria, "
        "delinquency buckets/ranges/actions, external-asset-owners, credit bureau configuration/"
        "integration, and shares (products/accounts/dividends) (Portfolio service).\n\n"
        "Run the '0 - Auth' request first (requires a tenant/admin already provisioned) to populate "
        "{{token}}. Collection variables: baseUrl, tenantId, token.\n\n"
        "Request bodies were auto-derived from the actual field reads in PortfolioService.cc; "
        "placeholder values are generic and should be adjusted to valid data (e.g. real product/"
        "client/office ids) for your environment.\n\n"
        "Note: LoansController only wires the numeric-:loanId-addressed route family — the parallel "
        "external-id/:loanExternalId mirror that Fineract (and PortfolioService's idOrExternalId "
        "parameter) also supports is an intentional, documented scope trim to keep the route surface "
        "manageable, same as downloadtemplate/uploadtemplate CSV bulk-import and at-date/* "
        "point-in-time endpoints."
    )
    gen_phase(
        6,
        "TurboLedger \u2014 Phase 6 (Lending & Shares)",
        phase6_desc,
        [
            portfolio_dir / "LoanProductsController.h",
            portfolio_dir / "LoansController.h",
            portfolio_dir / "FloatingRatesController.h",
            portfolio_dir / "RatesController.h",
            portfolio_dir / "RescheduleLoansController.h",
            portfolio_dir / "LoanCollateralManagementController.h",
            portfolio_dir / "ProvisioningCategoryController.h",
            portfolio_dir / "ProvisioningCriteriaController.h",
            portfolio_dir / "DelinquencyController.h",
            portfolio_dir / "ExternalAssetOwnersController.h",
            portfolio_dir / "CreditBureauConfigurationController.h",
            portfolio_dir / "CreditBureauIntegrationController.h",
            portfolio_dir / "ShareProductsController.h",
            portfolio_dir / "ShareAccountsController.h",
            portfolio_dir / "ShareProductDividendsController.h",
        ],
        [portfolio_svc],
    )

    group_dir = SRC / "services" / "Group" / "controllers"
    group_svc = SRC / "services" / "Group" / "services" / "GroupService.cc"
    teller_dir = SRC / "services" / "Teller" / "controllers"
    teller_svc = SRC / "services" / "Teller" / "services" / "TellerService.cc"
    phase7_desc = (
        "Phase 7 surface through the API Gateway: groups, centers, grouplevels, collectionsheet "
        "(Group service) and tellers, cashiers, cashiersjournal (Teller service).\n\n"
        "Run the '0 - Auth' request first (requires a tenant/admin already provisioned) to populate "
        "{{token}}. Collection variables: baseUrl, tenantId, token.\n\n"
        "Request bodies were auto-derived from the actual field reads in GroupService.cc / "
        "TellerService.cc; placeholder values are generic and should be adjusted to valid data "
        "(e.g. real office/staff/client ids) for your environment.\n\n"
        "GSIM (Group Savings) endpoints are a documented scope trim from Phase 5/7 and are not "
        "included here."
    )
    gen_phase(
        7,
        "TurboLedger \u2014 Phase 7 (Groups & Teller)",
        phase7_desc,
        [
            group_dir / "GroupsController.h",
            group_dir / "CentersController.h",
            group_dir / "GroupLevelsController.h",
            group_dir / "CollectionSheetController.h",
            teller_dir / "TellersController.h",
            teller_dir / "CashiersController.h",
            teller_dir / "CashiersJournalController.h",
        ],
        [group_svc, teller_svc],
    )

    heartbeat_dir = SRC / "services" / "HeartBeat" / "controllers"
    heartbeat_svc = SRC / "services" / "HeartBeat" / "services" / "HeartBeatService.cc"
    notification_dir = SRC / "services" / "Notification" / "controllers"
    notification_svc = SRC / "services" / "Notification" / "services" / "NotificationService.cc"
    template_dir = SRC / "services" / "Template" / "controllers"
    template_svc = SRC / "services" / "Template" / "services" / "TemplateService.cc"
    phase8_desc = (
        "Phase 8 surface through the API Gateway: jobs + scheduler (HeartBeat service); "
        "notifications, sms, smscampaigns, email, reportmailingjobs (Notification service); "
        "templates (Template service). The Batch API (POST /api/v1/batches) is implemented inside "
        "the gateway itself (see GatewayCore::handleBatch) rather than as a controller and is not "
        "included as a generated request here — see IMPLEMENTATION_PLAN.md for its relative-"
        "reference ($.<requestId>.<field>) substitution syntax and call it directly.\n\n"
        "Run the '0 - Auth' request first (requires a tenant/admin already provisioned) to populate "
        "{{token}}. Collection variables: baseUrl, tenantId, token.\n\n"
        "Request bodies were auto-derived from the actual field reads in HeartBeatService.cc / "
        "NotificationService.cc / TemplateService.cc; placeholder values are generic and should be "
        "adjusted to valid data for your environment.\n\n"
        "Reporting (reports/runreports/adhocquery/search/surveys/likelihood/povertyLine) was never "
        "built in this codebase and is out of scope here."
    )
    gen_phase(
        8,
        "TurboLedger \u2014 Phase 8 (Ops Backbone)",
        phase8_desc,
        [
            heartbeat_dir / "JobsController.h",
            heartbeat_dir / "SchedulerController.h",
            notification_dir / "NotificationsController.h",
            notification_dir / "SmsController.h",
            notification_dir / "SmsCampaignsController.h",
            notification_dir / "EmailController.h",
            notification_dir / "ReportMailingJobsController.h",
            template_dir / "TemplatesController.h",
        ],
        [heartbeat_svc, notification_svc, template_svc],
    )

    selfservice_dir = SRC / "services" / "SelfService" / "controllers"
    selfservice_svc = SRC / "services" / "SelfService" / "services" / "SelfServiceService.cc"
    interop_dir = SRC / "services" / "Interoperation" / "controllers"
    interop_svc = SRC / "services" / "Interoperation" / "services" / "InteroperationService.cc"
    phase9_desc = (
        "Phase 9 surface through the API Gateway: all self/* endpoints (SelfService, the "
        "customer-facing mobile-banking BFF) and all interoperation/* endpoints (Interoperation, "
        "Mojaloop-style payments v1).\n\n"
        "Run the '0 - Auth' request first (requires a tenant/admin already provisioned) to populate "
        "{{token}} \u2014 note that most self/* requests actually need a bearer token for a "
        "*self-service* user (one linked 1:1 to a Customer client id via self/registration/user), "
        "not the admin token the Auth folder captures; swap {{token}} manually after registering/"
        "linking a self-service user and signing in as them, same workflow as the live smoke test "
        "described in IMPLEMENTATION_PLAN.md's Phase 9 section. self/registration (the bare public "
        "submission step) and self/registration/user (admin-only linking) are the exceptions that "
        "work with no / an admin token respectively.\n\n"
        "Collection variables: baseUrl, tenantId, token.\n\n"
        "Request bodies were auto-derived from the actual field reads in SelfServiceService.cc / "
        "InteroperationService.cc; placeholder values are generic and should be adjusted to valid "
        "data (real client/account/loan ids, and for self/accounttransfers, the real "
        "PortfolioAccountType enum \u2014 Savings=2, not 1, confirmed against self/accounttransfers/"
        "template's accountTypeOptions) for your environment.\n\n"
        "self/clients/:id/images, self/runreports, and self/surveys* are disclosed local-only stubs "
        "(no Reporting/PPI service exists) \u2014 see IMPLEMENTATION_PLAN.md for the full list of "
        "Phase 9 scope-trim decisions."
    )
    gen_phase(
        9,
        "TurboLedger \u2014 Phase 9 (Self-Service & Interoperation)",
        phase9_desc,
        [
            selfservice_dir / "RegistrationController.h",
            selfservice_dir / "ClientsController.h",
            selfservice_dir / "SavingsController.h",
            selfservice_dir / "LoansController.h",
            selfservice_dir / "SharesController.h",
            selfservice_dir / "BeneficiariesController.h",
            selfservice_dir / "MiscController.h",
            interop_dir / "PartiesController.h",
            interop_dir / "QuotesController.h",
            interop_dir / "TransfersController.h",
            interop_dir / "AccountsController.h",
            interop_dir / "DisbursementController.h",
        ],
        [selfservice_svc, interop_svc],
    )


if __name__ == "__main__":
    main()
