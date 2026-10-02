#!/usr/bin/env python3
"""One-off invocation of genmodel.py for the SelfService service's 6 tables."""
import sys
import os

sys.path.insert(0, os.path.dirname(__file__))
from genmodel import Column, ModelSpec, generate

NS = "TlSelfServiceDb"
OUT = os.path.join(os.path.dirname(__file__), "..", "services", "SelfService", "models")

self_service_user = ModelSpec(
    class_name="SelfServiceUser",
    table_name="self_service_users",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("identity_user_id", "varchar", length=64, not_null=True),
        Column("client_id", "varchar", length=64, not_null=True),
        Column("username", "varchar", length=100, not_null=True),
        Column("mobile_no", "varchar", length=32),
        Column("email", "varchar", length=120),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

self_service_registration = ModelSpec(
    class_name="SelfServiceRegistration",
    table_name="self_service_registrations",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("first_name", "varchar", length=100, not_null=True),
        Column("last_name", "varchar", length=100, not_null=True),
        Column("mobile_no", "varchar", length=32, not_null=True),
        Column("account_number", "varchar", length=100),
        Column("authentication_mode", "varchar", length=20, not_null=True, has_default=True),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

device_registration = ModelSpec(
    class_name="DeviceRegistration",
    table_name="device_registrations",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("self_service_user_id", "varchar", length=64, not_null=True),
        Column("client_id", "varchar", length=64, not_null=True),
        Column("device_id", "varchar", length=150, not_null=True),
        Column("device_name", "varchar", length=150),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

tpt_beneficiary = ModelSpec(
    class_name="TptBeneficiary",
    table_name="tpt_beneficiaries",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("self_service_user_id", "varchar", length=64, not_null=True),
        Column("name", "varchar", length=150, not_null=True),
        Column("account_type", "varchar", length=20, not_null=True),
        Column("account_number", "varchar", length=100, not_null=True),
        Column("transfer_limit", "numeric"),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

pocket = ModelSpec(
    class_name="Pocket",
    table_name="pockets",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("self_service_user_id", "varchar", length=64, not_null=True),
        Column("account_type", "varchar", length=20, not_null=True),
        Column("account_id", "varchar", length=64, not_null=True),
        Column("is_default", "bool", not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

client_image = ModelSpec(
    class_name="ClientImage",
    table_name="client_images",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("client_id", "varchar", length=64, not_null=True),
        Column("content_type", "varchar", length=100, not_null=True),
        Column("image_data", "text", not_null=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

if __name__ == "__main__":
    os.makedirs(OUT, exist_ok=True)
    for spec in (
        self_service_user,
        self_service_registration,
        device_registration,
        tpt_beneficiary,
        pocket,
        client_image,
    ):
        generate(spec, OUT)
