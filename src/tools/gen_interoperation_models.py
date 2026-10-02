#!/usr/bin/env python3
"""One-off invocation of genmodel.py for the Interoperation service's 4 tables."""
import sys
import os

sys.path.insert(0, os.path.dirname(__file__))
from genmodel import Column, ModelSpec, generate

NS = "TlInteroperationDb"
OUT = os.path.join(os.path.dirname(__file__), "..", "services", "Interoperation", "models")

interop_identifier = ModelSpec(
    class_name="InteropIdentifier",
    table_name="interop_identifiers",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("id_type", "varchar", length=50, not_null=True),
        Column("id_value", "varchar", length=150, not_null=True),
        Column("sub_id_or_type", "varchar", length=50),
        Column("account_id", "varchar", length=64, not_null=True),
        Column("account_type", "varchar", length=20, not_null=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

interop_quote = ModelSpec(
    class_name="InteropQuote",
    table_name="interop_quotes",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("transaction_code", "varchar", length=64, not_null=True),
        Column("quote_code", "varchar", length=64, not_null=True),
        Column("account_id", "varchar", length=64, not_null=True),
        Column("amount", "numeric", not_null=True),
        Column("fee_amount", "numeric", not_null=True, has_default=True),
        Column("currency", "varchar", length=10, not_null=True, has_default=True),
        Column("expiration", "timestamptz"),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

interop_request = ModelSpec(
    class_name="InteropRequest",
    table_name="interop_requests",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("transaction_code", "varchar", length=64, not_null=True),
        Column("request_code", "varchar", length=64, not_null=True),
        Column("account_id", "varchar", length=64, not_null=True),
        Column("amount", "numeric", not_null=True),
        Column("currency", "varchar", length=10, not_null=True, has_default=True),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

interop_transfer = ModelSpec(
    class_name="InteropTransfer",
    table_name="interop_transfers",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("transaction_code", "varchar", length=64, not_null=True),
        Column("transfer_code", "varchar", length=64, not_null=True),
        Column("account_id", "varchar", length=64, not_null=True),
        Column("amount", "numeric", not_null=True),
        Column("currency", "varchar", length=10, not_null=True, has_default=True),
        Column("transfer_action", "varchar", length=20, not_null=True, has_default=True),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

if __name__ == "__main__":
    os.makedirs(OUT, exist_ok=True)
    for spec in (interop_identifier, interop_quote, interop_request, interop_transfer):
        generate(spec, OUT)
