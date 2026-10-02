//
// turbo::TenantStatus — the tenant lifecycle state machine, shared by the
// Provisioner (owner of the registry) and the ApiGateway (edge enforcement).
//
// The wire format (JSON payloads, TL headers) and the database column
// (Postgres ENUM `tenant_status`) both use the upper-case labels produced
// by toString(); C++ code must only ever pass the enum around.
//
//   PENDING ──▶ PROVISIONING ──▶ ACTIVE ◀──▶ SUSPENDED
//      │              │            │             │
//      │              ▼            ▼             ▼
//      └──────────▶ FAILED       CLOSED (terminal)
//
#pragma once

#include <array>
#include <optional>
#include <string_view>

namespace turbo {

enum class TenantStatus {
    Pending,       ///< registered, provisioning not started
    Provisioning,  ///< schemas/seeds being applied
    Active,        ///< serving traffic
    Suspended,     ///< traffic blocked at the edge, data retained
    Closed,        ///< terminal; never serves traffic again
    Failed,        ///< provisioning aborted; safe to retry via re-create
};

inline constexpr std::array<TenantStatus, 6> kAllTenantStatuses = {
    TenantStatus::Pending,   TenantStatus::Provisioning, TenantStatus::Active,
    TenantStatus::Suspended, TenantStatus::Closed,       TenantStatus::Failed,
};

constexpr std::string_view toString(TenantStatus status) {
    switch (status) {
        case TenantStatus::Pending:      return "PENDING";
        case TenantStatus::Provisioning: return "PROVISIONING";
        case TenantStatus::Active:       return "ACTIVE";
        case TenantStatus::Suspended:    return "SUSPENDED";
        case TenantStatus::Closed:       return "CLOSED";
        case TenantStatus::Failed:       return "FAILED";
    }
    return "PENDING";  // unreachable with a valid enum value
}

constexpr std::optional<TenantStatus> tenantStatusFromString(std::string_view text) {
    for (const auto status : kAllTenantStatuses)
        if (text == toString(status)) return status;
    return std::nullopt;
}

/// May the tenant serve API traffic in this state?
constexpr bool isServing(TenantStatus status) { return status == TenantStatus::Active; }

/// Legal lifecycle transitions (used by the Provisioner's setStatus).
constexpr bool isLegalTransition(TenantStatus from, TenantStatus to) {
    switch (to) {
        case TenantStatus::Active:
            return from == TenantStatus::Suspended || from == TenantStatus::Pending;
        case TenantStatus::Suspended:
            return from == TenantStatus::Active;
        case TenantStatus::Closed:
            return from != TenantStatus::Closed;
        case TenantStatus::Provisioning:
            return from == TenantStatus::Pending;
        case TenantStatus::Failed:
            return from == TenantStatus::Provisioning || from == TenantStatus::Pending;
        case TenantStatus::Pending:
            return false;  // initial state only
    }
    return false;
}

}  // namespace turbo
