#!/usr/bin/env python3
"""One-off invocation of genmodel.py for the Template service's 2 tables."""
import sys
import os

sys.path.insert(0, os.path.dirname(__file__))
from genmodel import Column, ModelSpec, generate

NS = "TlTemplateDb"
OUT = os.path.join(os.path.dirname(__file__), "..", "services", "Template", "models")

template = ModelSpec(
    class_name="Template",
    table_name="templates",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("name", "varchar", length=200, not_null=True),
        Column("text", "text", not_null=True),
        Column("entity", "varchar", length=100, not_null=True),
        Column("template_type", "varchar", length=20, not_null=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

template_mapper = ModelSpec(
    class_name="TemplateMapper",
    table_name="template_mappers",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("template_id", "uuid", not_null=True),
        Column("mapper_key", "varchar", length=100, not_null=True),
        Column("mapper_order", "int", not_null=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

if __name__ == "__main__":
    os.makedirs(OUT, exist_ok=True)
    for spec in (template, template_mapper):
        generate(spec, OUT)
