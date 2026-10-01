#!/usr/bin/env python3
"""
genmodel.py — hand-authored-model generator matching drogon_ctl's real output
shape, for the subset of the generated API this codebase's CoroMapper<T>
usage actually needs (row-mapping + CRUD via Mapper/CoroMapper).

Why this exists: `drogon_ctl create_model` requires a live Postgres
connection, which isn't available in this sandbox. Every new table added by
a phase still needs a genuine-shaped model so the service code can use
CoroMapper<T> instead of raw SQL (see IMPLEMENTATION_PLAN.md — raw SQL is
only acceptable for a handful of documented structural exceptions:
Postgres advisory locks, dynamic per-tenant datatables, composite-key
lookups with no natural single-column model). This script produces the
insert/update/find machinery drogon_ctl would generate, but *omits* the
Json::Value constructors, updateByJson/updateByMasqueradedJson,
validateJsonFor.../validJsonOfField and toJson/toString/toMasqueradedJson
methods — nothing in these services calls them (JSON responses are built by
hand in the *Service classes), so they would just be more surface area to
keep correct. Regenerate for real with `drogon_ctl create_model` against a
live DB with this table if those are ever actually needed.

Usage: import and call `generate(...)`, or edit the __main__ block below
per model and run `python3 genmodel.py`.

Column types understood (maps to the exact (cpp_type, db_type_label, length)
triples drogon_ctl itself emits — verified against genuine generated models
in this repo, e.g. Client.h/.cc, ProvisioningEntry.h/.cc):
    uuid                -> std::string / "uuid"
    varchar(N)           -> std::string / "character varying", length N
    text                -> std::string / "text"
    int                 -> int32_t / "integer", length 4
    bigint              -> int64_t / "bigint", length 8
    bool                -> bool / "boolean", length 1
    date                -> ::trantor::Date / "date"
    timestamptz         -> ::trantor::Date / "timestamp with time zone"
    numeric             -> std::string / "numeric"
"""
from __future__ import annotations

import re
from dataclasses import dataclass, field
from typing import List


def to_pascal(snake: str) -> str:
    return "".join(p.capitalize() for p in snake.split("_"))


def to_camel(snake: str) -> str:
    pascal = to_pascal(snake)
    return pascal[0].lower() + pascal[1:] if pascal else pascal


@dataclass
class Column:
    name: str  # snake_case db column name
    type: str  # one of the keys in TYPE_MAP (varchar/numeric may include length via `length=`)
    length: int = 0
    not_null: bool = False
    pk: bool = False
    has_default: bool = False  # DB-side default (server generates a value if omitted)

    @property
    def pascal(self) -> str:
        return to_pascal(self.name)

    @property
    def camel(self) -> str:
        return to_camel(self.name)

    @property
    def member(self) -> str:
        return self.camel + "_"


TYPE_MAP = {
    "uuid": ("std::string", "uuid", 0),
    "varchar": ("std::string", "character varying", None),  # length supplied per-column
    "text": ("std::string", "text", 0),
    "jsonb": ("std::string", "jsonb", 0),
    "int": ("int32_t", "integer", 4),
    "bigint": ("int64_t", "bigint", 8),
    "bool": ("bool", "boolean", 1),
    "date": ("::trantor::Date", "date", 0),
    "timestamptz": ("::trantor::Date", "timestamp with time zone", 0),
    "numeric": ("std::string", "numeric", 0),
}


def cpp_type(col: Column) -> str:
    return TYPE_MAP[col.type][0]


def db_type_label(col: Column) -> str:
    return TYPE_MAP[col.type][1]


def col_length(col: Column) -> int:
    if col.type == "varchar":
        return col.length
    return TYPE_MAP[col.type][2]


@dataclass
class ModelSpec:
    class_name: str  # e.g. "ClientFamilyMember"
    table_name: str  # e.g. "client_family_members"
    namespace: str  # e.g. "TlCustomerDb"
    columns: List[Column] = field(default_factory=list)

    @property
    def pk_index(self) -> int:
        for i, c in enumerate(self.columns):
            if c.pk:
                return i
        return 0


# ---------------------------------------------------------------------------
# Row-value parsing snippets per C++ type (mirrors genuine drogon_ctl output).
# ---------------------------------------------------------------------------

def row_parse_snippet(col: Column, accessor: str, target_member: str) -> str:
    t = cpp_type(col)
    if t == "::trantor::Date" and db_type_label(col) == "date":
        return (
            f"auto daysStr = {accessor}.as<std::string>();\n"
            f"            struct tm stm;\n"
            f"            memset(&stm,0,sizeof(stm));\n"
            f"            strptime(daysStr.c_str(),\"%Y-%m-%d\",&stm);\n"
            f"            time_t t = mktime(&stm);\n"
            f"            {target_member}=std::make_shared<::trantor::Date>(t*1000000);"
        )
    if t == "::trantor::Date":
        return (
            f"auto timeStr = {accessor}.as<std::string>();\n"
            f"            struct tm stm;\n"
            f"            memset(&stm,0,sizeof(stm));\n"
            f"            auto p = strptime(timeStr.c_str(),\"%Y-%m-%d %H:%M:%S\",&stm);\n"
            f"            time_t t = mktime(&stm);\n"
            f"            size_t decimalNum = 0;\n"
            f"            if(p)\n"
            f"            {{\n"
            f"                if(*p=='.')\n"
            f"                {{\n"
            f"                    std::string decimals(p+1,&timeStr[timeStr.length()]);\n"
            f"                    while(decimals.length()<6)\n"
            f"                    {{\n"
            f"                        decimals += \"0\";\n"
            f"                    }}\n"
            f"                    decimalNum = (size_t)atol(decimals.c_str());\n"
            f"                }}\n"
            f"                {target_member}=std::make_shared<::trantor::Date>(t*1000000+decimalNum);\n"
            f"            }}"
        )
    return f"{target_member}=std::make_shared<{t}>({accessor}.as<{t}>());"


def generate_header(spec: ModelSpec) -> str:
    cols = spec.columns
    n = len(cols)
    lines = []
    lines.append("/**")
    lines.append(f" *  {spec.class_name}.h")
    lines.append(" *")
    lines.append(
        " *  Hand-authored to match drogon_ctl's real generated output for the subset"
    )
    lines.append(
        f" *  of the API this codebase's CoroMapper<{spec.class_name}> usage actually needs"
    )
    lines.append(
        " *  (row-mapping + CRUD via Mapper/CoroMapper). The Json::Value constructors,"
    )
    lines.append(
        " *  updateByJson/updateByMasqueradedJson, validateJsonFor.../validJsonOfField"
    )
    lines.append(
        " *  and toJson/toString/toMasqueradedJson methods that a live"
    )
    lines.append(
        " *  `drogon_ctl create_model` run would also emit are intentionally omitted"
    )
    lines.append(
        " *  here since nothing in this codebase calls them; regenerate with"
    )
    lines.append(
        " *  `drogon_ctl create_model` against a live DB with this table if those are"
    )
    lines.append(" *  ever needed.")
    lines.append(" *")
    lines.append(" */")
    lines.append("")
    lines.append("#pragma once")
    lines.append("#include <drogon/orm/Result.h>")
    lines.append("#include <drogon/orm/Row.h>")
    lines.append("#include <drogon/orm/Field.h>")
    lines.append("#include <drogon/orm/SqlBinder.h>")
    lines.append("#include <drogon/orm/Mapper.h>")
    lines.append("#include <drogon/orm/BaseBuilder.h>")
    lines.append("#ifdef __cpp_impl_coroutine")
    lines.append("#include <drogon/orm/CoroMapper.h>")
    lines.append("#endif")
    lines.append("#include <trantor/utils/Date.h>")
    lines.append("#include <trantor/utils/Logger.h>")
    lines.append("#include <json/json.h>")
    lines.append("#include <string>")
    lines.append("#include <string_view>")
    lines.append("#include <memory>")
    lines.append("#include <vector>")
    lines.append("#include <tuple>")
    lines.append("#include <stdint.h>")
    lines.append("#include <iostream>")
    lines.append("")
    lines.append("namespace drogon")
    lines.append("{")
    lines.append("namespace orm")
    lines.append("{")
    lines.append("class DbClient;")
    lines.append("using DbClientPtr = std::shared_ptr<DbClient>;")
    lines.append("}")
    lines.append("}")
    lines.append("namespace drogon_model")
    lines.append("{")
    lines.append(f"namespace {spec.namespace}")
    lines.append("{")
    lines.append("")
    lines.append(f"class {spec.class_name}")
    lines.append("{")
    lines.append("  public:")
    lines.append("    struct Cols")
    lines.append("    {")
    for c in cols:
        lines.append(f"        static const std::string _{c.name};")
    lines.append("    };")
    lines.append("")
    lines.append("    static const int primaryKeyNumber;")
    lines.append("    static const std::string tableName;")
    lines.append("    static const bool hasPrimaryKey;")
    lines.append("    static const std::string primaryKeyName;")
    lines.append(f"    using PrimaryKeyType = {cpp_type(spec.columns[spec.pk_index])};")
    lines.append("    const PrimaryKeyType &getPrimaryKey() const;")
    lines.append("")
    lines.append("    explicit " + spec.class_name + "(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;")
    lines.append("")
    lines.append(f"    {spec.class_name}() = default;")
    lines.append("")
    for c in cols:
        t = cpp_type(c)
        lines.append(f"    /**  For column {c.name}  */")
        lines.append(f"    const {t} &getValueOf{c.pascal}() const noexcept;")
        lines.append(f"    const std::shared_ptr<{t}> &get{c.pascal}() const noexcept;")
        if t == "std::string":
            lines.append(f"    void set{c.pascal}(const {t} &p{c.pascal}) noexcept;")
            lines.append(f"    void set{c.pascal}({t} &&p{c.pascal}) noexcept;")
        else:
            lines.append(f"    void set{c.pascal}(const {t} &p{c.pascal}) noexcept;")
        if not c.not_null and not c.pk:
            lines.append(f"    void set{c.pascal}ToNull() noexcept;")
        lines.append("")
    lines.append(f"    static size_t getColumnNumber() noexcept {{  return {n};  }}")
    lines.append("    static const std::string &getColumnName(size_t index) noexcept(false);")
    lines.append("")
    lines.append("  private:")
    lines.append(f"    friend drogon::orm::Mapper<{spec.class_name}>;")
    lines.append(f"    friend drogon::orm::BaseBuilder<{spec.class_name}, true, true>;")
    lines.append(f"    friend drogon::orm::BaseBuilder<{spec.class_name}, true, false>;")
    lines.append(f"    friend drogon::orm::BaseBuilder<{spec.class_name}, false, true>;")
    lines.append(f"    friend drogon::orm::BaseBuilder<{spec.class_name}, false, false>;")
    lines.append("#ifdef __cpp_impl_coroutine")
    lines.append(f"    friend drogon::orm::CoroMapper<{spec.class_name}>;")
    lines.append("#endif")
    lines.append("    static const std::vector<std::string> &insertColumns() noexcept;")
    lines.append("    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;")
    lines.append("    const std::vector<std::string> updateColumns() const;")
    lines.append("    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;")
    lines.append("    ///For mysql or sqlite3")
    lines.append("    void updateId(const uint64_t id);")
    for c in cols:
        lines.append(f"    std::shared_ptr<{cpp_type(c)}> {c.member};")
    lines.append("    struct MetaData")
    lines.append("    {")
    lines.append("        const std::string colName_;")
    lines.append("        const std::string colType_;")
    lines.append("        const std::string colDatabaseType_;")
    lines.append("        const ssize_t colLength_;")
    lines.append("        const bool isAutoVal_;")
    lines.append("        const bool isPrimaryKey_;")
    lines.append("        const bool notNull_;")
    lines.append("    };")
    lines.append("    static const std::vector<MetaData> metaData_;")
    lines.append(f"    bool dirtyFlag_[{n}]={{ false }};")
    lines.append("  public:")
    lines.append("    static const std::string &sqlForFindingByPrimaryKey()")
    lines.append("    {")
    lines.append("        static const std::string sql=\"select * from \" + tableName + \" where id = $1\";")
    lines.append("        return sql;")
    lines.append("    }")
    lines.append("")
    lines.append("    static const std::string &sqlForDeletingByPrimaryKey()")
    lines.append("    {")
    lines.append("        static const std::string sql=\"delete from \" + tableName + \" where id = $1\";")
    lines.append("        return sql;")
    lines.append("    }")
    lines.append("    std::string sqlForInserting(bool &needSelection) const")
    lines.append("    {")
    lines.append("        std::string sql=\"insert into \" + tableName + \" (\";")
    lines.append("        size_t parametersCount = 0;")
    lines.append("        needSelection = false;")
    for i, c in enumerate(cols):
        if i == spec.pk_index or c.has_default:
            lines.append(f"        sql += \"{c.name},\";")
            lines.append("        ++parametersCount;")
            lines.append(f"        if(!dirtyFlag_[{i}])")
            lines.append("        {")
            lines.append("            needSelection=true;")
            lines.append("        }")
        else:
            lines.append(f"        if(dirtyFlag_[{i}])")
            lines.append("        {")
            lines.append(f"            sql += \"{c.name},\";")
            lines.append("            ++parametersCount;")
            lines.append("        }")
    lines.append("        if(parametersCount > 0)")
    lines.append("        {")
    lines.append("            sql[sql.length()-1]=')';")
    lines.append("            sql += \" values (\";")
    lines.append("        }")
    lines.append("        else")
    lines.append("            sql += \") values (\";")
    lines.append("")
    lines.append("        int placeholder=1;")
    lines.append("        char placeholderStr[64];")
    lines.append("        size_t n=0;")
    for i, c in enumerate(cols):
        lines.append(f"        if(dirtyFlag_[{i}])")
        lines.append("        {")
        lines.append("            n = snprintf(placeholderStr,sizeof(placeholderStr),\"$%d,\",placeholder++);")
        lines.append("            sql.append(placeholderStr, n);")
        lines.append("        }")
        if i == spec.pk_index or c.has_default:
            lines.append("        else")
            lines.append("        {")
            lines.append("            sql +=\"default,\";")
            lines.append("        }")
    lines.append("        if(parametersCount > 0)")
    lines.append("        {")
    lines.append("            sql.resize(sql.length() - 1);")
    lines.append("        }")
    lines.append("        if(needSelection)")
    lines.append("        {")
    lines.append("            sql.append(\") returning *\");")
    lines.append("        }")
    lines.append("        else")
    lines.append("        {")
    lines.append("            sql.append(1, ')');")
    lines.append("        }")
    lines.append("        LOG_TRACE << sql;")
    lines.append("        return sql;")
    lines.append("    }")
    lines.append("};")
    lines.append(f"}} // namespace {spec.namespace}")
    lines.append("} // namespace drogon_model")
    lines.append("")
    return "\n".join(lines)


def generate_source(spec: ModelSpec) -> str:
    cols = spec.columns
    n = len(cols)
    cn = spec.class_name
    lines = []
    lines.append("/**")
    lines.append(f" *  {cn}.cc")
    lines.append(" *")
    lines.append(f" *  See {cn}.h for the hand-authored-subset note.")
    lines.append(" *")
    lines.append(" */")
    lines.append("")
    lines.append(f"#include \"{cn}.h\"")
    lines.append("#include <drogon/utils/Utilities.h>")
    lines.append("#include <string>")
    lines.append("")
    lines.append("using namespace drogon;")
    lines.append("using namespace drogon::orm;")
    lines.append(f"using namespace drogon_model::{spec.namespace};")
    lines.append("")
    for c in cols:
        lines.append(f"const std::string {cn}::Cols::_{c.name} = \"\\\"{c.name}\\\"\";")
    lines.append(f"const std::string {cn}::primaryKeyName = \"id\";")
    lines.append(f"const bool {cn}::hasPrimaryKey = true;")
    lines.append(f"const std::string {cn}::tableName = \"\\\"{spec.table_name}\\\"\";")
    lines.append("")
    lines.append(f"const std::vector<typename {cn}::MetaData> {cn}::metaData_={{")
    meta_rows = []
    for i, c in enumerate(cols):
        length = col_length(c)
        meta_rows.append(
            f"{{\"{c.name}\",\"{cpp_type(c)}\",\"{db_type_label(c)}\",{length},0,"
            f"{1 if c.pk else 0},{1 if (c.not_null or c.pk) else 0}}}"
        )
    lines.append(",\n".join(meta_rows))
    lines.append("};")
    lines.append(f"const std::string &{cn}::getColumnName(size_t index) noexcept(false)")
    lines.append("{")
    lines.append("    assert(index < metaData_.size());")
    lines.append("    return metaData_[index].colName_;")
    lines.append("}")
    lines.append(f"{cn}::{cn}(const Row &r, const ssize_t indexOffset) noexcept")
    lines.append("{")
    lines.append("    if(indexOffset < 0)")
    lines.append("    {")
    for c in cols:
        accessor = f"r[\"{c.name}\"]"
        lines.append(f"        if(!{accessor}.isNull())")
        lines.append("        {")
        lines.append("            " + row_parse_snippet(c, accessor, c.member))
        lines.append("        }")
    lines.append("    }")
    lines.append("    else")
    lines.append("    {")
    lines.append("        size_t offset = (size_t)indexOffset;")
    lines.append(f"        if(offset + {n} > r.size())")
    lines.append("        {")
    lines.append("            LOG_FATAL << \"Invalid SQL result for this model\";")
    lines.append("            return;")
    lines.append("        }")
    lines.append("        size_t index;")
    for i, c in enumerate(cols):
        lines.append(f"        index = offset + {i};")
        lines.append("        if(!r[index].isNull())")
        lines.append("        {")
        lines.append("            " + row_parse_snippet(c, "r[index]", c.member))
        lines.append("        }")
    lines.append("    }")
    lines.append("")
    lines.append("}")

    for i, c in enumerate(cols):
        t = cpp_type(c)
        lines.append(f"const {t} &{cn}::getValueOf{c.pascal}() const noexcept")
        lines.append("{")
        lines.append(f"    static const {t} defaultValue = {t}();")
        lines.append(f"    if({c.member})")
        lines.append(f"        return *{c.member};")
        lines.append("    return defaultValue;")
        lines.append("}")
        lines.append(f"const std::shared_ptr<{t}> &{cn}::get{c.pascal}() const noexcept")
        lines.append("{")
        lines.append(f"    return {c.member};")
        lines.append("}")
        if t == "std::string":
            lines.append(f"void {cn}::set{c.pascal}(const {t} &p{c.pascal}) noexcept")
            lines.append("{")
            lines.append(f"    {c.member} = std::make_shared<{t}>(p{c.pascal});")
            lines.append(f"    dirtyFlag_[{i}] = true;")
            lines.append("}")
            lines.append(f"void {cn}::set{c.pascal}({t} &&p{c.pascal}) noexcept")
            lines.append("{")
            lines.append(f"    {c.member} = std::make_shared<{t}>(std::move(p{c.pascal}));")
            lines.append(f"    dirtyFlag_[{i}] = true;")
            lines.append("}")
        else:
            lines.append(f"void {cn}::set{c.pascal}(const {t} &p{c.pascal}) noexcept")
            lines.append("{")
            lines.append(f"    {c.member} = std::make_shared<{t}>(p{c.pascal});")
            lines.append(f"    dirtyFlag_[{i}] = true;")
            lines.append("}")
        if not c.not_null and not c.pk:
            lines.append(f"void {cn}::set{c.pascal}ToNull() noexcept")
            lines.append("{")
            lines.append(f"    {c.member}.reset();")
            lines.append(f"    dirtyFlag_[{i}] = true;")
            lines.append("}")
        if c.pk:
            lines.append(f"const typename {cn}::PrimaryKeyType & {cn}::getPrimaryKey() const")
            lines.append("{")
            lines.append(f"    assert({c.member});")
            lines.append(f"    return *{c.member};")
            lines.append("}")
        lines.append("")

    lines.append(f"void {cn}::updateId(const uint64_t id)")
    lines.append("{")
    lines.append("}")
    lines.append("")
    lines.append(f"const std::vector<std::string> &{cn}::insertColumns() noexcept")
    lines.append("{")
    lines.append("    static const std::vector<std::string> inCols={")
    lines.append(",\n".join(f"        \"{c.name}\"" for c in cols))
    lines.append("    };")
    lines.append("    return inCols;")
    lines.append("}")
    lines.append("")
    lines.append(f"void {cn}::outputArgs(drogon::orm::internal::SqlBinder &binder) const")
    lines.append("{")
    for i, c in enumerate(cols):
        lines.append(f"    if(dirtyFlag_[{i}])")
        lines.append("    {")
        lines.append(f"        if(get{c.pascal}())")
        lines.append("        {")
        lines.append(f"            binder << getValueOf{c.pascal}();")
        lines.append("        }")
        lines.append("        else")
        lines.append("        {")
        lines.append("            binder << nullptr;")
        lines.append("        }")
        lines.append("    }")
    lines.append("}")
    lines.append("")
    lines.append(f"const std::vector<std::string> {cn}::updateColumns() const")
    lines.append("{")
    lines.append("    std::vector<std::string> ret;")
    for i in range(n):
        lines.append(f"    if(dirtyFlag_[{i}])")
        lines.append("    {")
        lines.append(f"        ret.push_back(getColumnName({i}));")
        lines.append("    }")
    lines.append("    return ret;")
    lines.append("}")
    lines.append("")
    lines.append(f"void {cn}::updateArgs(drogon::orm::internal::SqlBinder &binder) const")
    lines.append("{")
    for i, c in enumerate(cols):
        lines.append(f"    if(dirtyFlag_[{i}])")
        lines.append("    {")
        lines.append(f"        if(get{c.pascal}())")
        lines.append("        {")
        lines.append(f"            binder << getValueOf{c.pascal}();")
        lines.append("        }")
        lines.append("        else")
        lines.append("        {")
        lines.append("            binder << nullptr;")
        lines.append("        }")
        lines.append("    }")
    lines.append("}")
    lines.append("")
    return "\n".join(lines)


def generate(spec: ModelSpec, out_dir: str) -> None:
    import os

    h = generate_header(spec)
    cc = generate_source(spec)
    with open(os.path.join(out_dir, spec.class_name + ".h"), "w") as f:
        f.write(h)
    with open(os.path.join(out_dir, spec.class_name + ".cc"), "w") as f:
        f.write(cc)
    print(f"wrote {spec.class_name}.h / .cc to {out_dir}")


if __name__ == "__main__":
    import sys

    print(__doc__)
    sys.exit(0)
