//
// Phase 9 cleanup: this service used to own full user CRUD (getAll, create,
// update, lock/unlock, activate/deactivate, delete), but every one of those
// methods queried a raw, unscoped DbClient filtered by a `business_id`
// column rather than switching into the caller's tenant schema — and none
// of it was reachable anyway: UsersController has used
// turbo_ledger_identity::rbac::RbacService (proper beginTenantTxn-based
// tenant-schema access) for all of that since Phase 1. That dead,
// non-tenant-aware code has been removed; only sign-in — which IS still
// live (AuthController) and already tenant-schema-aware for the common
// case via tryTenantSignin — remains here.
//

#pragma once

#include <drogon/drogon.h>
#include <optional>
#include "dto/BaseApiResponse.h"
#include "dto/SigninDto.h"


namespace turbo_ledger_identity::services
{
    class UserService
    {
    public:
        drogon::Task<dto::BaseApiResponse> validateUserCredentials(const dto::SigninDto &dto);

        /// Phase 1: tenant-aware signin — tenant schema first, host fallback.
        drogon::Task<dto::BaseApiResponse> validateUserCredentials(const dto::SigninDto &dto,
                                                                   const std::string &tenantId);

    private:
        drogon::Task<std::optional<dto::BaseApiResponse>> tryTenantSignin(
            const dto::SigninDto &dto, const std::string &tenantId);

    };
}
