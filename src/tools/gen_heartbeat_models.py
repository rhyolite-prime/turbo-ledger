#!/usr/bin/env python3
"""One-off invocation of genmodel.py for the HeartBeat service's 4 tables."""
import sys
import os

sys.path.insert(0, os.path.dirname(__file__))
from genmodel import Column, ModelSpec, generate

NS = "TlHeartBeatDb"
OUT = os.path.join(os.path.dirname(__file__), "..", "services", "HeartBeat", "models")

job = ModelSpec(
    class_name="Job",
    table_name="jobs",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("short_name", "varchar", length=100, not_null=True),
        Column("display_name", "varchar", length=200, not_null=True),
        Column("description", "text"),
        Column("cron_expression", "varchar", length=100),
        Column("is_active", "bool", not_null=True, has_default=True),
        Column("is_misfired", "bool", not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

job_run_history = ModelSpec(
    class_name="JobRunHistory",
    table_name="job_run_history",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("job_id", "uuid", not_null=True),
        Column("version", "bigint", not_null=True),
        Column("start_time", "timestamptz", not_null=True),
        Column("end_time", "timestamptz"),
        Column("status", "varchar", length=20, not_null=True),
        Column("trigger_type", "varchar", length=20, not_null=True),
        Column("error_log", "text"),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

job_business_step = ModelSpec(
    class_name="JobBusinessStep",
    table_name="job_business_steps",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("job_id", "uuid", not_null=True),
        Column("step_name", "varchar", length=200, not_null=True),
        Column("step_order", "int", not_null=True),
        Column("is_enabled", "bool", not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

scheduler_state = ModelSpec(
    class_name="SchedulerState",
    table_name="scheduler_state",
    namespace=NS,
    columns=[
        Column("id", "int", pk=True, not_null=True, has_default=True),
        Column("is_active", "bool", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

if __name__ == "__main__":
    os.makedirs(OUT, exist_ok=True)
    for spec in (job, job_run_history, job_business_step, scheduler_state):
        generate(spec, OUT)
