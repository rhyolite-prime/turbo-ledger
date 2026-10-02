#!/usr/bin/env python3
"""One-off invocation of genmodel.py for the Notification service's 8 tables."""
import sys
import os

sys.path.insert(0, os.path.dirname(__file__))
from genmodel import Column, ModelSpec, generate

NS = "TlNotificationDb"
OUT = os.path.join(os.path.dirname(__file__), "..", "services", "Notification", "models")

notification = ModelSpec(
    class_name="Notification",
    table_name="notifications",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("user_id", "varchar", length=64, not_null=True),
        Column("actor_id", "varchar", length=64),
        Column("object_type", "varchar", length=50, not_null=True),
        Column("object_id", "varchar", length=64),
        Column("action", "varchar", length=50, not_null=True),
        Column("content", "text", not_null=True),
        Column("is_read", "bool", not_null=True, has_default=True),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

sms_campaign = ModelSpec(
    class_name="SmsCampaign",
    table_name="sms_campaigns",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("campaign_name", "varchar", length=200, not_null=True),
        Column("campaign_type", "varchar", length=20, not_null=True, has_default=True),
        Column("message", "text", not_null=True),
        Column("param_value", "jsonb", not_null=True, has_default=True),
        Column("recurrence", "varchar", length=100),
        Column("next_trigger_date", "timestamptz"),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("provider_id", "varchar", length=100),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

sms_message = ModelSpec(
    class_name="SmsMessage",
    table_name="sms_messages",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("campaign_id", "uuid"),
        Column("client_id", "varchar", length=64),
        Column("group_id", "varchar", length=64),
        Column("staff_id", "varchar", length=64),
        Column("mobile_no", "varchar", length=32, not_null=True),
        Column("message", "text", not_null=True),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("provider_id", "varchar", length=100),
        Column("error_message", "text"),
        Column("submitted_on_date", "timestamptz"),
        Column("delivered_on_date", "timestamptz"),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

email_configuration = ModelSpec(
    class_name="EmailConfiguration",
    table_name="email_configuration",
    namespace=NS,
    columns=[
        Column("id", "int", pk=True, not_null=True, has_default=True),
        Column("smtp_host", "varchar", length=255),
        Column("smtp_port", "int", not_null=True, has_default=True),
        Column("smtp_username", "varchar", length=255),
        Column("smtp_password", "varchar", length=255),
        Column("from_email", "varchar", length=255),
        Column("from_name", "varchar", length=255),
        Column("use_tls", "bool", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

email_campaign = ModelSpec(
    class_name="EmailCampaign",
    table_name="email_campaigns",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("campaign_name", "varchar", length=200, not_null=True),
        Column("subject", "varchar", length=255, not_null=True),
        Column("message", "text", not_null=True),
        Column("param_value", "jsonb", not_null=True, has_default=True),
        Column("recurrence", "varchar", length=100),
        Column("next_trigger_date", "timestamptz"),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("attachment_file_format", "varchar", length=10),
        Column("stretchy_report_name", "varchar", length=200),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

email_message = ModelSpec(
    class_name="EmailMessage",
    table_name="email_messages",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("campaign_id", "uuid"),
        Column("client_id", "varchar", length=64),
        Column("group_id", "varchar", length=64),
        Column("staff_id", "varchar", length=64),
        Column("email_address", "varchar", length=255, not_null=True),
        Column("email_subject", "varchar", length=255, not_null=True),
        Column("email_message", "text", not_null=True),
        Column("status", "varchar", length=20, not_null=True, has_default=True),
        Column("error_message", "text"),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

report_mailing_job = ModelSpec(
    class_name="ReportMailingJob",
    table_name="report_mailing_jobs",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("name", "varchar", length=200, not_null=True),
        Column("description", "text"),
        Column("report_name", "varchar", length=200, not_null=True),
        Column("report_params", "jsonb", not_null=True, has_default=True),
        Column("start_date_time", "timestamptz", not_null=True),
        Column("recurrence", "varchar", length=100),
        Column("email_recipients", "text", not_null=True),
        Column("email_subject", "varchar", length=255, not_null=True),
        Column("email_message", "text"),
        Column("email_attachment_file_format", "varchar", length=10, not_null=True, has_default=True),
        Column("is_active", "bool", not_null=True, has_default=True),
        Column("previous_run_status", "varchar", length=20),
        Column("previous_run_error_message", "text"),
        Column("previous_run_start_time", "timestamptz"),
        Column("previous_run_end_time", "timestamptz"),
        Column("next_run_time", "timestamptz"),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
        Column("updated_at", "timestamptz", not_null=True, has_default=True),
    ],
)

report_mailing_job_run_history = ModelSpec(
    class_name="ReportMailingJobRunHistory",
    table_name="report_mailing_job_run_history",
    namespace=NS,
    columns=[
        Column("id", "uuid", pk=True, not_null=True, has_default=True),
        Column("job_id", "uuid", not_null=True),
        Column("start_time", "timestamptz", not_null=True),
        Column("end_time", "timestamptz"),
        Column("status", "varchar", length=20, not_null=True),
        Column("error_message", "text"),
        Column("created_at", "timestamptz", not_null=True, has_default=True),
    ],
)

if __name__ == "__main__":
    os.makedirs(OUT, exist_ok=True)
    for spec in (
        notification,
        sms_campaign,
        sms_message,
        email_configuration,
        email_campaign,
        email_message,
        report_mailing_job,
        report_mailing_job_run_history,
    ):
        generate(spec, OUT)
