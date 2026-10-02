--
-- V001__baseline.sql — SelfService (BFF) baseline schema.
--
-- SelfService owns no financial ledger data of its own — it is a
-- backend-for-frontend that composes Customer/Portfolio/DepositAccountManagement
-- over signed internal HTTP calls (see turbo::InternalClient). The tables
-- here are strictly SelfService-local concerns that have no home in any
-- other service:
--   * self_service_users / self_service_registrations: the self-service
--     identity layer. Scope decision (see IMPLEMENTATION_PLAN.md Phase 9
--     as-built notes): a self-service user is linked 1:1 to exactly one
--     Customer client id (Fineract supports multi-client "linked accounts"
--     per self-service user; this is simplified away, consistent with
--     prior-phase simplification precedent). Registration approval is a
--     local PENDING/APPROVED/REJECTED row, not a re-implementation of
--     Identity's user-creation/password-hashing flow: approving a
--     registration still requires an operator to separately create the
--     Identity platform user and pass its id into
--     POST self/registration/user.
--   * device_registrations: push-notification device tokens.
--   * tpt_beneficiaries: saved third-party-transfer beneficiaries.
--   * pockets: a self-service user's personalized dashboard of linked
--     accounts (own + favorited), purely a view-ordering concern.
--   * client_images: Customer has no profile-image support to compose
--     against, so self-service profile images are stored locally as
--     base64 text (small images only; no object storage in this sandbox).
--
-- Runs inside a tenant schema (search_path pinned by the migration runner).
--

CREATE TABLE IF NOT EXISTS self_service_users (
    id                  uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    identity_user_id    varchar(64) NOT NULL,   -- Identity platform user id (JWT subject)
    client_id           varchar(64) NOT NULL,   -- the single linked Customer client
    username            varchar(100) NOT NULL,
    mobile_no           varchar(32),
    email               varchar(120),
    status              varchar(20) NOT NULL DEFAULT 'ACTIVE',
    created_at          timestamptz NOT NULL DEFAULT now(),
    updated_at          timestamptz NOT NULL DEFAULT now()
);
CREATE UNIQUE INDEX IF NOT EXISTS uq_self_service_users_username ON self_service_users(username);
CREATE UNIQUE INDEX IF NOT EXISTS uq_self_service_users_identity ON self_service_users(identity_user_id);
CREATE INDEX IF NOT EXISTS idx_self_service_users_client ON self_service_users(client_id);

CREATE TABLE IF NOT EXISTS self_service_registrations (
    id                      uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    first_name              varchar(100) NOT NULL,
    last_name               varchar(100) NOT NULL,
    mobile_no               varchar(32) NOT NULL,
    account_number          varchar(100),
    authentication_mode     varchar(20) NOT NULL DEFAULT 'APP',
    status                  varchar(20) NOT NULL DEFAULT 'PENDING',
    created_at              timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_self_service_registrations_status ON self_service_registrations(status);

CREATE TABLE IF NOT EXISTS device_registrations (
    id                      uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    self_service_user_id   varchar(64) NOT NULL,
    client_id               varchar(64) NOT NULL,
    device_id               varchar(150) NOT NULL,
    device_name             varchar(150),
    status                  varchar(20) NOT NULL DEFAULT 'ACTIVE',
    created_at              timestamptz NOT NULL DEFAULT now(),
    updated_at              timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_device_registrations_user ON device_registrations(self_service_user_id);

CREATE TABLE IF NOT EXISTS tpt_beneficiaries (
    id                      uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    self_service_user_id   varchar(64) NOT NULL,
    name                    varchar(150) NOT NULL,
    account_type            varchar(20) NOT NULL,
    account_number          varchar(100) NOT NULL,
    transfer_limit          numeric,
    status                  varchar(20) NOT NULL DEFAULT 'ACTIVE',
    created_at              timestamptz NOT NULL DEFAULT now(),
    updated_at              timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_tpt_beneficiaries_user ON tpt_beneficiaries(self_service_user_id);

CREATE TABLE IF NOT EXISTS pockets (
    id                      uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    self_service_user_id   varchar(64) NOT NULL,
    account_type            varchar(20) NOT NULL,
    account_id              varchar(64) NOT NULL,
    is_default              boolean NOT NULL DEFAULT false,
    created_at              timestamptz NOT NULL DEFAULT now()
);
CREATE INDEX IF NOT EXISTS idx_pockets_user ON pockets(self_service_user_id);

CREATE TABLE IF NOT EXISTS client_images (
    id                      uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    client_id               varchar(64) NOT NULL,
    content_type            varchar(100) NOT NULL,
    image_data              text NOT NULL,   -- base64-encoded
    created_at              timestamptz NOT NULL DEFAULT now(),
    updated_at              timestamptz NOT NULL DEFAULT now()
);
CREATE UNIQUE INDEX IF NOT EXISTS uq_client_images_client ON client_images(client_id);
