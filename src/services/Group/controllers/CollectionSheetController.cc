#include "CollectionSheetController.h"

#include "turbo/ApiResponse.h"

using turbo::ApiResponse;

Task<HttpResponsePtr> CollectionSheetController::submit(HttpRequestPtr) {
    co_return ApiResponse::httpNotImplemented(
        "collectionsheet (needs Portfolio repayment schedules + DepositAccountManagement savings-due "
        "amounts + attendance/calendar data this phase doesn't own)");
}
