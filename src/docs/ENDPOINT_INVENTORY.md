# Turbo Ledger — Granular Endpoint Inventory

Derived from `Apache Fineract REST API.postman_collection.json` (871 requests), grouped by the Turbo Ledger service that will own each resource. Companion to `IMPLEMENTATION_PLAN.md`.

Legend: paths relative to the gateway root; tenant is resolved from the `TL-Tenant-Id` header. `:param` denotes a path parameter.

## Ownership summary

| Service | Resource groups | Endpoints |
|---|---|---|
| Identity | `authentication`, `users`, `roles`, `permissions`, `passwordpreferences`, `twofactor`, `userdetails`, `makercheckers` | 34 |
| Provisioner (Tenancy) | `instance-mode` | 1 |
| Organization | `offices`, `officetransactions`, `staff`, `holidays`, `workingdays`, `currencies`, `funds`, `paymenttypes`, `entitytoentitymapping`, `taxes` | 56 |
| Customer | `clients`, `client`, `collateral-management`, `clients (v2)` | 64 |
| Group | `groups`, `centers`, `grouplevels`, `collectionsheet` | 25 |
| DepositAccountManagement | `savingsaccounts`, `savingsproducts`, `fixeddepositaccounts`, `fixeddepositproducts`, `recurringdepositaccounts`, `recurringdepositproducts`, `interestratecharts`, `accounttransfers`, `standinginstructions`, `standinginstructionrunhistory`, `accountnumberformats`, `charges` | 119 |
| Portfolio (Lending & Shares) | `loans`, `loanproducts`, `rescheduleloans`, `loan-collateral-management`, `floatingrates`, `rates`, `delinquency`, `provisioningcategory`, `provisioningcriteria`, `products`, `shareproduct`, `accounts`, `external-asset-owners`, `CreditBureauConfiguration`, `creditBureauIntegration`, `mixmapping`, `mixreport`, `mixtaxonomy` | 224 |
| Accounting | `glaccounts`, `glclosures`, `journalentries`, `accountingrules`, `financialactivityaccounts`, `provisioningentries`, `runaccruals` | 39 |
| Teller | `tellers`, `cashiers`, `cashiersjournal` | 21 |
| SystemConfig | `codes`, `configurations`, `externalservice`, `audits`, `hooks`, `caches`, `businessdate`, `externalevents`, `fieldconfiguration`, `datatables`, `entityDatatableChecks`, `imports`, `{entityType}`, `{entity}`, `{resourceType}` | 86 |
| Scheduler (HeartBeat) | `jobs`, `scheduler` | 16 |
| Reporting | `reports`, `runreports`, `adhocquery`, `search`, `surveys`, `survey`, `likelihood`, `povertyLine` | 41 |
| Notification | `notifications`, `sms`, `smscampaigns`, `email`, `reportmailingjobs`, `reportmailingjobrunhistory` | 43 |
| Template | `templates` | 8 |
| SelfService | `self` | 60 |
| Interoperation (Payments) | `interoperation` | 19 |
| Batch/Misc | `batches`, `echo`, `internal` | 15 |

## Identity — 34 endpoints

### `authentication` (1)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/authentication` | Verify authentication |

### `users` (9)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/users/downloadtemplate` | get User Template |
| GET | `v1/users/template` | Retrieve User Details Template |
| POST | `v1/users/uploadtemplate` | post Users Template |
| POST | `v1/users/:userId/pwd` | Change the password of a User |
| DELETE | `v1/users/:userId` | Delete a User |
| GET | `v1/users/:userId` | Retrieve a User |
| PUT | `v1/users/:userId` | Update a User |
| GET | `v1/users` | Retrieve list of users |
| POST | `v1/users` | Create a User |

### `roles` (8)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/roles/:roleId/permissions` | Retrieve a Role's Permissions |
| PUT | `v1/roles/:roleId/permissions` | Update a Role's Permissions |
| DELETE | `v1/roles/:roleId` | Delete a Role |
| GET | `v1/roles/:roleId` | Retrieve a Role |
| POST | `v1/roles/:roleId` | Enable Role / Disable Role |
| PUT | `v1/roles/:roleId` | Update a Role |
| GET | `v1/roles` | List Roles |
| POST | `v1/roles` | Create a New Role |

### `permissions` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/permissions` | List Application Permissions |
| PUT | `v1/permissions` | Enable/Disable Permissions for Maker Checker |

### `passwordpreferences` (3)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/passwordpreferences/template` | List Application Password validation policies |
| GET | `v1/passwordpreferences` | retrieve 1 |
| PUT | `v1/passwordpreferences` | Update password preferences |

### `twofactor` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/twofactor/configure` | retrieve All 9 |
| PUT | `v1/twofactor/configure` | update Configuration 3 |
| POST | `v1/twofactor/invalidate` | update Configuration 2 |
| POST | `v1/twofactor/validate` | validate |
| GET | `v1/twofactor` | get OTP Delivery Methods |
| POST | `v1/twofactor` | request Token |

### `userdetails` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/userdetails` | Fetch authenticated user details
 |

### `makercheckers` (4)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/makercheckers/searchtemplate` | Maker Checker Search Template |
| DELETE | `v1/makercheckers/:auditId` | Delete Maker Checker Entry |
| POST | `v1/makercheckers/:auditId` | Approve Maker Checker Entry / Reject Maker Checker Entry |
| GET | `v1/makercheckers` | List Maker Checker Entries |

## Provisioner (Tenancy) — 1 endpoints

### `instance-mode` (1)

| Method | Path | Operation |
|---|---|---|
| PUT | `v1/instance-mode` | Changes the Fineract instance mode |

## Organization — 56 endpoints

### `offices` (9)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/offices/downloadtemplate` | get Office Template |
| GET | `v1/offices/external-id/:externalId` | Retrieve an Office using external id |
| PUT | `v1/offices/external-id/:externalId` | Update Office |
| GET | `v1/offices/template` | Retrieve Office Details Template |
| POST | `v1/offices/uploadtemplate` | post Office Template |
| GET | `v1/offices/:officeId` | Retrieve an Office |
| PUT | `v1/offices/:officeId` | Update Office |
| GET | `v1/offices` | List Offices |
| POST | `v1/offices` | Create an Office |

### `officetransactions` (4)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/officetransactions/template` | new Office Transaction Details |
| DELETE | `v1/officetransactions/:transactionId` | delete 7 |
| GET | `v1/officetransactions` | retrieve Office Transactions |
| POST | `v1/officetransactions` | transfer Money From |

### `staff` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/staff/downloadtemplate` | get Template 1 |
| POST | `v1/staff/uploadtemplate` | post Template |
| GET | `v1/staff/:staffId` | Retrieve a Staff Member |
| PUT | `v1/staff/:staffId` | Update a Staff Member |
| GET | `v1/staff` | Retrieve Staff |
| POST | `v1/staff` | Create a staff member |

### `holidays` (7)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/holidays/template` | retrieve Repayment Schedule Updation Tye Options |
| DELETE | `v1/holidays/:holidayId` | Delete a Holiday |
| GET | `v1/holidays/:holidayId` | Retrieve a Holiday |
| POST | `v1/holidays/:holidayId` | Activate a Holiday |
| PUT | `v1/holidays/:holidayId` | Update a Holiday |
| GET | `v1/holidays` | List Holidays |
| POST | `v1/holidays` | Create a Holiday |

### `workingdays` (3)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/workingdays/template` | Working Days Template |
| GET | `v1/workingdays` | List Working days |
| PUT | `v1/workingdays` | Update a Working Day |

### `currencies` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/currencies` | Retrieve Currency Configuration |
| PUT | `v1/currencies` | Update Currency Configuration |

### `funds` (4)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/funds/:fundId` | Retrieve a Fund |
| PUT | `v1/funds/:fundId` | Update a Fund |
| GET | `v1/funds` | Retrieve Funds |
| POST | `v1/funds` | Create a Fund |

### `paymenttypes` (5)

| Method | Path | Operation |
|---|---|---|
| DELETE | `v1/paymenttypes/:paymentTypeId` | Delete a Payment Type |
| GET | `v1/paymenttypes/:paymentTypeId` | Retrieve a Payment Type |
| PUT | `v1/paymenttypes/:paymentTypeId` | Update a Payment Type |
| GET | `v1/paymenttypes` | Retrieve all Payment Types |
| POST | `v1/paymenttypes` | Create a Payment Type |

### `entitytoentitymapping` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/entitytoentitymapping/:mapId/:fromId/:toId` | get Entity To Entity Mappings |
| DELETE | `v1/entitytoentitymapping/:mapId` | delete 4 |
| GET | `v1/entitytoentitymapping/:mapId` | retrieve One 4 |
| PUT | `v1/entitytoentitymapping/:mapId` | update Map |
| POST | `v1/entitytoentitymapping/:relId` | create Map |
| GET | `v1/entitytoentitymapping` | retrieve All 7 |

### `taxes` (10)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/taxes/component/template` | retrieve Template 21 |
| GET | `v1/taxes/component/:taxComponentId` | Retrieve Tax Component |
| PUT | `v1/taxes/component/:taxComponentId` | Update Tax Component |
| GET | `v1/taxes/component` | List Tax Components |
| POST | `v1/taxes/component` | Create a new Tax Component |
| GET | `v1/taxes/group/template` | retrieve Template 22 |
| GET | `v1/taxes/group/:taxGroupId` | Retrieve Tax Group |
| PUT | `v1/taxes/group/:taxGroupId` | Update Tax Group |
| GET | `v1/taxes/group` | List Tax Group |
| POST | `v1/taxes/group` | Create a new Tax Group |

## Customer — 64 endpoints

### `clients` (53)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/clients/downloadtemplate` | get Client Template |
| GET | `v1/clients/external-id/:clientExternalId/transactions/external-id/:transactionExternalId` | Retrieve a Client Transaction |
| POST | `v1/clients/external-id/:clientExternalId/transactions/external-id/:transactionExternalId` | Undo a Client Transaction |
| GET | `v1/clients/external-id/:clientExternalId/transactions/:transactionId` | Retrieve a Client Transaction |
| POST | `v1/clients/external-id/:clientExternalId/transactions/:transactionId` | Undo a Client Transaction |
| GET | `v1/clients/external-id/:clientExternalId/transactions` | List Client Transactions |
| GET | `v1/clients/external-id/:externalId/accounts` | Retrieve client accounts overview |
| GET | `v1/clients/external-id/:externalId/obligeedetails` | Retrieve client obligee details |
| GET | `v1/clients/external-id/:externalId/transferproposaldate` | Retrieve client transfer template |
| DELETE | `v1/clients/external-id/:externalId` | Delete a Client |
| GET | `v1/clients/external-id/:externalId` | Retrieve a Client by External Id |
| POST | `v1/clients/external-id/:externalId` | Activate a Client / Close a Client / Reject a Client / Withdraw a Client / Reactivate a Client / UndoReject a Client / UndoWithdraw a Client / Assign a Staff / Unassign a Staff / Update Default Savings Account / Propose a Client Transfer / Withdraw a Clie |
| PUT | `v1/clients/external-id/:externalId` | Update a Client using the External Id |
| GET | `v1/clients/template` | Retrieve Client Details Template |
| POST | `v1/clients/uploadtemplate` | post Client Template |
| GET | `v1/clients/:clientId/accounts` | Retrieve client accounts overview |
| GET | `v1/clients/:clientId/charges/template` | retrieve Template 4 |
| DELETE | `v1/clients/:clientId/charges/:chargeId` | Delete a Client Charge |
| GET | `v1/clients/:clientId/charges/:chargeId` | Retrieve a Client Charge |
| POST | `v1/clients/:clientId/charges/:chargeId` | Pay a Client Charge / Waive a Client Charge |
| GET | `v1/clients/:clientId/charges` | List Client Charges |
| POST | `v1/clients/:clientId/charges` | Add Client Charge |
| GET | `v1/clients/:clientId/collaterals/template` | Get Client Collateral Template |
| GET | `v1/clients/:clientId/collaterals/:clientCollateralId` | Get Client Collateral Data |
| DELETE | `v1/clients/:clientId/collaterals/:collateralId` | Delete Client Collateral |
| PUT | `v1/clients/:clientId/collaterals/:collateralId` | Update New Collateral of a Client |
| GET | `v1/clients/:clientId/collaterals` | Get Clients Collateral Products |
| POST | `v1/clients/:clientId/collaterals` | Add New Collateral For a Client |
| GET | `v1/clients/:clientId/familymembers/template` | get Template 2 |
| DELETE | `v1/clients/:clientId/familymembers/:familyMemberId` | delete Client Family Members |
| GET | `v1/clients/:clientId/familymembers/:familyMemberId` | get Family Member |
| PUT | `v1/clients/:clientId/familymembers/:familyMemberId` | update Client Family Members |
| GET | `v1/clients/:clientId/familymembers` | get Family Members |
| POST | `v1/clients/:clientId/familymembers` | add Client Family Members |
| GET | `v1/clients/:clientId/identifiers/template` | Retrieve Client Identifier Details Template |
| DELETE | `v1/clients/:clientId/identifiers/:identifierId` | Delete a Client Identifier |
| GET | `v1/clients/:clientId/identifiers/:identifierId` | Retrieve a Client Identifier |
| PUT | `v1/clients/:clientId/identifiers/:identifierId` | Update a Client Identifier |
| GET | `v1/clients/:clientId/identifiers` | List all Identifiers for a Client |
| POST | `v1/clients/:clientId/identifiers` | Create an Identifier for a Client |
| GET | `v1/clients/:clientId/obligeedetails` | Retrieve client obligee details |
| GET | `v1/clients/:clientId/transactions/external-id/:transactionExternalId` | Retrieve a Client Transaction |
| POST | `v1/clients/:clientId/transactions/external-id/:transactionExternalId` | Undo a Client Transaction |
| GET | `v1/clients/:clientId/transactions/:transactionId` | Retrieve a Client Transaction |
| POST | `v1/clients/:clientId/transactions/:transactionId` | Undo a Client Transaction |
| GET | `v1/clients/:clientId/transactions` | List Client Transactions |
| GET | `v1/clients/:clientId/transferproposaldate` | Retrieve client transfer template |
| DELETE | `v1/clients/:clientId` | Delete a Client |
| GET | `v1/clients/:clientId` | Retrieve a Client |
| POST | `v1/clients/:clientId` | Activate a Client / Close a Client / Reject a Client / Withdraw a Client / Reactivate a Client / UndoReject a Client / UndoWithdraw a Client / Assign a Staff / Unassign a Staff / Update Default Savings Account / Propose a Client Transfer / Withdraw a Clie |
| PUT | `v1/clients/:clientId` | Update a Client |
| GET | `v1/clients` | List Clients |
| POST | `v1/clients` | Create a Client |

### `client` (4)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/client/addresses/template` | get Addresses Template |
| GET | `v1/client/:clientid/addresses` | List all addresses for a Client |
| POST | `v1/client/:clientid/addresses` | Create an address for a Client |
| PUT | `v1/client/:clientid/addresses` | Update an address for a Client |

### `collateral-management` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/collateral-management/template` | Get Collateral Template |
| DELETE | `v1/collateral-management/:collateralId` | Delete a Collateral |
| GET | `v1/collateral-management/:collateralId` | Get Collateral |
| PUT | `v1/collateral-management/:collateralId` | Update Collateral |
| GET | `v1/collateral-management` | Get All Collaterals |
| POST | `v1/collateral-management` | Create a new collateral |

### `clients (v2)` (1)

| Method | Path | Operation |
|---|---|---|
| POST | `v2/clients/search` | Search Clients by text |

## Group — 25 endpoints

### `groups` (13)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/groups/downloadtemplate` | get Groups Template |
| GET | `v1/groups/template` | Retrieve Group Template |
| POST | `v1/groups/uploadtemplate` | post Group Template |
| GET | `v1/groups/:groupId/accounts` | Retrieve Group accounts overview |
| POST | `v1/groups/:groupId/command/unassign_staff` | Unassign a Staff |
| GET | `v1/groups/:groupId/glimaccounts` | retrieveglim Accounts |
| GET | `v1/groups/:groupId/gsimaccounts` | retrieve Gsim Accounts |
| DELETE | `v1/groups/:groupId` | Delete a Group |
| GET | `v1/groups/:groupId` | Retrieve a Group |
| POST | `v1/groups/:groupId` | Activate a Group / Associate Clients / Disassociate Clients / Transfer Clients across groups / Generate Collection Sheet / Save Collection Sheet / Unassign a Staff / Assign a Staff / Close a Group / Unassign a Role / Update a Role |
| PUT | `v1/groups/:groupId` | Update a Group |
| GET | `v1/groups` | List Groups |
| POST | `v1/groups` | Create a Group |

### `centers` (10)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/centers/downloadtemplate` | get Centers Template |
| GET | `v1/centers/template` | Retrieve a Center Template |
| POST | `v1/centers/uploadtemplate` | post Centers Template |
| GET | `v1/centers/:centerId/accounts` | Retrieve Center accounts overview |
| DELETE | `v1/centers/:centerId` | Delete a Center |
| GET | `v1/centers/:centerId` | Retrieve a Center |
| POST | `v1/centers/:centerId` | Activate a Center / Generate Collection Sheet / Save Collection Sheet / Close a Center / Associate Groups / Disassociate Groups |
| PUT | `v1/centers/:centerId` | Update a Center |
| GET | `v1/centers` | List Centers |
| POST | `v1/centers` | Create a Center |

### `grouplevels` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/grouplevels` | retrieve All Groups |

### `collectionsheet` (1)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/collectionsheet` | Generate Individual Collection Sheet / Save Collection Sheet |

## DepositAccountManagement — 119 endpoints

### `savingsaccounts` (32)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/savingsaccounts/downloadtemplate` | get Savings Template |
| DELETE | `v1/savingsaccounts/external-id/:externalId` | Delete a savings application |
| GET | `v1/savingsaccounts/external-id/:externalId` | retrieve One 26 |
| POST | `v1/savingsaccounts/external-id/:externalId` | Approve savings application / Undo approval savings application / Assign Savings Officer / Unassign Savings Officer / Reject savings application / Withdraw savings application / Activate a savings account / Close a savings account / Calculate Interest on  |
| PUT | `v1/savingsaccounts/external-id/:externalId` | Modify a savings application / Modify savings account withhold tax applicability |
| PUT | `v1/savingsaccounts/gsim/:parentAccountId` | update Gsim |
| POST | `v1/savingsaccounts/gsim` | submit GSIM Application |
| POST | `v1/savingsaccounts/gsimcommands/:parentAccountId` | handle GSIM Commands |
| GET | `v1/savingsaccounts/template` | Retrieve Savings Account Template |
| GET | `v1/savingsaccounts/transactions/downloadtemplate` | get Savings Transaction Template |
| POST | `v1/savingsaccounts/transactions/uploadtemplate` | post Savings Transaction Template |
| POST | `v1/savingsaccounts/uploadtemplate` | post Savings Template |
| DELETE | `v1/savingsaccounts/:accountId` | Delete a savings application |
| GET | `v1/savingsaccounts/:accountId` | retrieve One 25 |
| POST | `v1/savingsaccounts/:accountId` | Approve savings application / Undo approval savings application / Assign Savings Officer / Unassign Savings Officer / Reject savings application / Withdraw savings application / Activate a savings account / Close a savings account / Calculate Interest on  |
| PUT | `v1/savingsaccounts/:accountId` | Modify a savings application / Modify savings account withhold tax applicability |
| GET | `v1/savingsaccounts/:savingsAccountId/charges/template` | Retrieve Savings Charges Template |
| DELETE | `v1/savingsaccounts/:savingsAccountId/charges/:savingsAccountChargeId` | Delete a Savings account Charge |
| GET | `v1/savingsaccounts/:savingsAccountId/charges/:savingsAccountChargeId` | Retrieve a Savings account Charge |
| POST | `v1/savingsaccounts/:savingsAccountId/charges/:savingsAccountChargeId` | Pay a Savings account Charge / Waive off a Savings account Charge / Inactivate a Savings account Charge |
| PUT | `v1/savingsaccounts/:savingsAccountId/charges/:savingsAccountChargeId` | Update a Savings account Charge |
| GET | `v1/savingsaccounts/:savingsAccountId/charges` | List Savings Charges |
| POST | `v1/savingsaccounts/:savingsAccountId/charges` | Create a Savings account Charge |
| GET | `v1/savingsaccounts/:savingsId/onholdtransactions` | retrieve All 28 |
| POST | `v1/savingsaccounts/:savingsId/transactions/query` | Advanced search Savings Account Transactions |
| GET | `v1/savingsaccounts/:savingsId/transactions/search` | Search Savings Account Transactions |
| GET | `v1/savingsaccounts/:savingsId/transactions/template` | retrieve Template 19 |
| GET | `v1/savingsaccounts/:savingsId/transactions/:transactionId` | retrieve One 24 |
| POST | `v1/savingsaccounts/:savingsId/transactions/:transactionId` | Undo/Reverse/Modify/Release Amount transaction API |
| POST | `v1/savingsaccounts/:savingsId/transactions` | transaction 2 |
| GET | `v1/savingsaccounts` | List savings applications/accounts |
| POST | `v1/savingsaccounts` | Submit new savings application |

### `savingsproducts` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/savingsproducts/template` | Retrieve Savings Product Template |
| DELETE | `v1/savingsproducts/:productId` | Delete a Savings Product |
| GET | `v1/savingsproducts/:productId` | Retrieve a Savings Product |
| PUT | `v1/savingsproducts/:productId` | Update a Savings Product |
| GET | `v1/savingsproducts` | List Savings Products |
| POST | `v1/savingsproducts` | Create a Savings Product |

### `fixeddepositaccounts` (17)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/fixeddepositaccounts/calculate-fd-interest` | calculate Fixed Deposit Interest |
| GET | `v1/fixeddepositaccounts/downloadtemplate` | get Fixed Deposit Template |
| GET | `v1/fixeddepositaccounts/template` | Retrieve Fixed Deposit Account Template |
| GET | `v1/fixeddepositaccounts/transaction/downloadtemplate` | get Fixed Deposit Transaction Template |
| POST | `v1/fixeddepositaccounts/transaction/uploadtemplate` | post Fixed Deposit Transaction Template |
| POST | `v1/fixeddepositaccounts/uploadtemplate` | post Fixed Deposit Template |
| GET | `v1/fixeddepositaccounts/:accountId/template` | account Closure Template |
| DELETE | `v1/fixeddepositaccounts/:accountId` | Delete a fixed deposit application |
| GET | `v1/fixeddepositaccounts/:accountId` | Retrieve a fixed deposit application/account |
| POST | `v1/fixeddepositaccounts/:accountId` | Approve fixed deposit application / Undo approval fixed deposit application / Reject fixed deposit application / Withdraw fixed deposit application / Activate a fixed deposit account / Close a fixed deposit account / Premature Close a fixed deposit accoun |
| PUT | `v1/fixeddepositaccounts/:accountId` | Modify a fixed deposit application |
| GET | `v1/fixeddepositaccounts/:fixedDepositAccountId/transactions/template` | retrieve Template 14 |
| GET | `v1/fixeddepositaccounts/:fixedDepositAccountId/transactions/:transactionId` | retrieve One 18 |
| POST | `v1/fixeddepositaccounts/:fixedDepositAccountId/transactions/:transactionId` | adjust Transaction |
| POST | `v1/fixeddepositaccounts/:fixedDepositAccountId/transactions` | transaction |
| GET | `v1/fixeddepositaccounts` | List Fixed deposit applications/accounts |
| POST | `v1/fixeddepositaccounts` | Submit new fixed deposit application |

### `fixeddepositproducts` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/fixeddepositproducts/template` | retrieve Template 15 |
| DELETE | `v1/fixeddepositproducts/:productId` | Delete a Fixed Deposit Product |
| GET | `v1/fixeddepositproducts/:productId` | Retrieve a Fixed Deposit Product |
| PUT | `v1/fixeddepositproducts/:productId` | Update a Fixed Deposit Product |
| GET | `v1/fixeddepositproducts` | List Fixed Deposit Products |
| POST | `v1/fixeddepositproducts` | Create a Fixed Deposit Product |

### `recurringdepositaccounts` (16)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/recurringdepositaccounts/downloadtemplate` | get Recurring Deposit Template |
| GET | `v1/recurringdepositaccounts/template` | Retrieve recurring Deposit Account Template |
| GET | `v1/recurringdepositaccounts/transactions/downloadtemplate` | get Recurring Deposit Transaction Template |
| POST | `v1/recurringdepositaccounts/transactions/uploadtemplate` | post Recurring Deposit Transactions Template |
| POST | `v1/recurringdepositaccounts/uploadtemplate` | post Recurring Deposit Template |
| GET | `v1/recurringdepositaccounts/:accountId/template` | account Closure Template 1 |
| DELETE | `v1/recurringdepositaccounts/:accountId` | Delete a recurring deposit application |
| GET | `v1/recurringdepositaccounts/:accountId` | Retrieve a recurring deposit application/account |
| POST | `v1/recurringdepositaccounts/:accountId` | Approve recurring deposit application / Undo approval recurring deposit application / Reject recurring deposit application / Withdraw recurring deposit application / Activate a recurring deposit account / Update the recommended deposit amount for a recurr |
| PUT | `v1/recurringdepositaccounts/:accountId` | Modify a recurring deposit application |
| GET | `v1/recurringdepositaccounts/:recurringDepositAccountId/transactions/template` | Retrieve Recurring Deposit Account Transaction Template |
| GET | `v1/recurringdepositaccounts/:recurringDepositAccountId/transactions/:transactionId` | Retrieve Recurring Deposit Account Transaction |
| POST | `v1/recurringdepositaccounts/:recurringDepositAccountId/transactions/:transactionId` | Adjust Transaction / Undo transaction |
| POST | `v1/recurringdepositaccounts/:recurringDepositAccountId/transactions` | Deposit Transaction / Withdrawal Transaction |
| GET | `v1/recurringdepositaccounts` | List Recurring deposit applications/accounts |
| POST | `v1/recurringdepositaccounts` | Submit new recurring deposit application |

### `recurringdepositproducts` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/recurringdepositproducts/template` | retrieve Template 17 |
| DELETE | `v1/recurringdepositproducts/:productId` | Delete a Recurring Deposit Product |
| GET | `v1/recurringdepositproducts/:productId` | Retrieve a Recurring Deposit Product |
| PUT | `v1/recurringdepositproducts/:productId` | Update a Recurring Deposit Product |
| GET | `v1/recurringdepositproducts` | List Recuring Deposit Products |
| POST | `v1/recurringdepositproducts` | Create a Recurring Deposit Product |

### `interestratecharts` (12)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/interestratecharts/template` | Retrieve Chart Details Template |
| GET | `v1/interestratecharts/:chartId/chartslabs/template` | template 8 |
| DELETE | `v1/interestratecharts/:chartId/chartslabs/:chartSlabId` | Delete a Slab |
| GET | `v1/interestratecharts/:chartId/chartslabs/:chartSlabId` | Retrieve a Slab |
| PUT | `v1/interestratecharts/:chartId/chartslabs/:chartSlabId` | Update a Slab |
| GET | `v1/interestratecharts/:chartId/chartslabs` | Retrieve all Slabs |
| POST | `v1/interestratecharts/:chartId/chartslabs` | Create a Slab |
| DELETE | `v1/interestratecharts/:chartId` | Delete a Chart |
| GET | `v1/interestratecharts/:chartId` | Retrieve a Chart |
| PUT | `v1/interestratecharts/:chartId` | Update a Chart |
| GET | `v1/interestratecharts` | Retrieve all Charts |
| POST | `v1/interestratecharts` | Create a Chart |

### `accounttransfers` (6)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/accounttransfers/refundByTransfer` | Refund of an Active Loan by Transfer |
| GET | `v1/accounttransfers/template` | Retrieve Account Transfer Template |
| GET | `v1/accounttransfers/templateRefundByTransfer` | Retrieve Refund of an Active Loan by Transfer Template |
| GET | `v1/accounttransfers/:transferId` | Retrieve account transfer |
| GET | `v1/accounttransfers` | List account transfers |
| POST | `v1/accounttransfers` | Create new Transfer |

### `standinginstructions` (5)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/standinginstructions/template` | Retrieve Standing Instruction Template |
| GET | `v1/standinginstructions/:standingInstructionId` | Retrieve Standing Instruction |
| PUT | `v1/standinginstructions/:standingInstructionId` | Update Standing Instruction / Delete Standing Instruction |
| GET | `v1/standinginstructions` | List Standing Instructions |
| POST | `v1/standinginstructions` | Create new Standing Instruction |

### `standinginstructionrunhistory` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/standinginstructionrunhistory` | Standing Instructions Logged History |

### `accountnumberformats` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/accountnumberformats/template` | Retrieve Account number format Template |
| DELETE | `v1/accountnumberformats/:accountNumberFormatId` | Delete an Account number format |
| GET | `v1/accountnumberformats/:accountNumberFormatId` | Retrieve an Account number format |
| PUT | `v1/accountnumberformats/:accountNumberFormatId` | Update an Account number format |
| GET | `v1/accountnumberformats` | List Account number formats |
| POST | `v1/accountnumberformats` | Create an Account number format |

### `charges` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/charges/template` | Retrieve Charge Template |
| DELETE | `v1/charges/:chargeId` | Delete a Charge |
| GET | `v1/charges/:chargeId` | Retrieve a Charge |
| PUT | `v1/charges/:chargeId` | Update a Charge |
| GET | `v1/charges` | Retrieve Charges |
| POST | `v1/charges` | Create/Define a Charge |

## Portfolio (Lending & Shares) — 224 endpoints

### `loans` (126)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/loans/at-date/external-id/:loanExternalId` | retrieve Loan Point In Time By External Id |
| POST | `v1/loans/at-date/search/external-id` | retrieve Loans Point In Time By External Ids |
| POST | `v1/loans/at-date/search` | retrieve Loans Point In Time |
| GET | `v1/loans/at-date/:loanId` | retrieve Loan Point In Time |
| POST | `v1/loans/catch-up` | Executes Loan COB Catch Up |
| GET | `v1/loans/downloadtemplate` | get Loans Template |
| GET | `v1/loans/external-id/:loanExternalId/approved-amount` | Collects and returns the approved amount modification history for a given loan |
| PUT | `v1/loans/external-id/:loanExternalId/approved-amount` | Modifies the approved amount of the loan |
| PUT | `v1/loans/external-id/:loanExternalId/available-disbursement-amount` | Modifies the available disbursement amount of the loan |
| GET | `v1/loans/external-id/:loanExternalId/buydown-fees/external-id/:loanTransactionExternalId` | Retrieve a BuyDown Fees allocation data |
| GET | `v1/loans/external-id/:loanExternalId/buydown-fees/:loanTransactionId` | Retrieve a BuyDown Fees allocation data |
| GET | `v1/loans/external-id/:loanExternalId/buydown-fees` | Get the amortization details of Buy Down fees for a loan by external ID |
| GET | `v1/loans/external-id/:loanExternalId/capitalized-incomes/external-id/:loanTransactionExternalId` | Retrieve a capitalized income allocation data |
| GET | `v1/loans/external-id/:loanExternalId/capitalized-incomes/:loanTransactionId` | Retrieve a capitalized income allocation data |
| GET | `v1/loans/external-id/:loanExternalId/capitalized-incomes` | Get the amortization details of Capitalized Income for a loan by external ID |
| DELETE | `v1/loans/external-id/:loanExternalId/charges/external-id/:loanChargeExternalId` | Delete a Loan Charge |
| GET | `v1/loans/external-id/:loanExternalId/charges/external-id/:loanChargeExternalId` | Retrieve a Loan Charge |
| POST | `v1/loans/external-id/:loanExternalId/charges/external-id/:loanChargeExternalId` | Pay / Waive / Adjustment for Loan Charge |
| PUT | `v1/loans/external-id/:loanExternalId/charges/external-id/:loanChargeExternalId` | Update a Loan Charge |
| GET | `v1/loans/external-id/:loanExternalId/charges/template` | Retrieve Loan Charges Template |
| DELETE | `v1/loans/external-id/:loanExternalId/charges/:loanChargeId` | Delete a Loan Charge |
| GET | `v1/loans/external-id/:loanExternalId/charges/:loanChargeId` | Retrieve a Loan Charge |
| POST | `v1/loans/external-id/:loanExternalId/charges/:loanChargeId` | Pay / Waive / Adjustment for Loan Charge |
| PUT | `v1/loans/external-id/:loanExternalId/charges/:loanChargeId` | Update a Loan Charge |
| GET | `v1/loans/external-id/:loanExternalId/charges` | List Loan Charges |
| POST | `v1/loans/external-id/:loanExternalId/charges` | Create a Loan Charge (no command provided) or Pay a charge (command=pay) |
| GET | `v1/loans/external-id/:loanExternalId/deferredincome` | Get the amortization details of Capitalized Income for a loan by external ID |
| GET | `v1/loans/external-id/:loanExternalId/delinquency-actions` | Retrieve delinquency actions related to the loan |
| POST | `v1/loans/external-id/:loanExternalId/delinquency-actions` | Adds a new delinquency action for a loan |
| GET | `v1/loans/external-id/:loanExternalId/delinquencytags` | Retrieve the Loan Delinquency Tag history using the Loan Id |
| DELETE | `v1/loans/external-id/:loanExternalId/interest-pauses/:variationId` | Delete an interest pause period by external id |
| PUT | `v1/loans/external-id/:loanExternalId/interest-pauses/:variationId` | Update an interest pause period by external id |
| GET | `v1/loans/external-id/:loanExternalId/interest-pauses` | Retrieve all interest pause periods for a loan using external ID |
| POST | `v1/loans/external-id/:loanExternalId/interest-pauses` | Create a new interest pause for a loan using external ID |
| GET | `v1/loans/external-id/:loanExternalId/template` | retrieve Approval Template 1 |
| GET | `v1/loans/external-id/:loanExternalId/transactions/external-id/:externalTransactionId` | Retrieve a Transaction Details |
| POST | `v1/loans/external-id/:loanExternalId/transactions/external-id/:externalTransactionId` | Adjust a Transaction |
| PUT | `v1/loans/external-id/:loanExternalId/transactions/external-id/:transactionExternalId` | Undo a Waive Charge Transaction |
| GET | `v1/loans/external-id/:loanExternalId/transactions/template` | Retrieve Loan Transaction Template |
| GET | `v1/loans/external-id/:loanExternalId/transactions/:transactionId` | Retrieve a Transaction Details |
| POST | `v1/loans/external-id/:loanExternalId/transactions/:transactionId` | Adjust a Transaction |
| PUT | `v1/loans/external-id/:loanExternalId/transactions/:transactionId` | Undo a Waive Charge Transaction |
| GET | `v1/loans/external-id/:loanExternalId/transactions` | Retrieve Transactions |
| POST | `v1/loans/external-id/:loanExternalId/transactions` | Significant Loan Transactions |
| DELETE | `v1/loans/external-id/:loanExternalId` | Delete a Loan Application |
| GET | `v1/loans/external-id/:loanExternalId` | Retrieve a Loan |
| POST | `v1/loans/external-id/:loanExternalId` | Approve Loan Application / Recover Loan Guarantee / Undo Loan Application Approval / Assign a Loan Officer / Unassign a Loan Officer / Reject Loan Application / Applicant Withdraws from Loan Application / Disburse Loan Disburse Loan To Savings Account / U |
| PUT | `v1/loans/external-id/:loanExternalId` | Modify a loan application |
| GET | `v1/loans/glimAccount/:glimId` | get Glim Repayment Template |
| POST | `v1/loans/glimAccount/:glimId` | Approve GLIM Application / Undo GLIM Application Approval / Reject GLIM Application / Disburse Loan Disburse Loan To Savings Account / Undo Loan Disbursal |
| GET | `v1/loans/is-catch-up-running` | Retrieves whether Loan COB catch up is running |
| GET | `v1/loans/loanreassignment/template` | loan Reassignment Template |
| POST | `v1/loans/loanreassignment` | loan Reassignment |
| GET | `v1/loans/locked` | List locked loan accounts |
| GET | `v1/loans/oldest-cob-closed` | Retrieves the oldest COB processed loan |
| GET | `v1/loans/repayments/downloadtemplate` | get Loan Repayment Template |
| POST | `v1/loans/repayments/uploadtemplate` | post Loan Repayment Template |
| GET | `v1/loans/template` | Retrieve Loan Details Template |
| POST | `v1/loans/uploadtemplate` | post Loan Template |
| GET | `v1/loans/:loanId/approved-amount` | Collects and returns the approved amount modification history for a given loan |
| PUT | `v1/loans/:loanId/approved-amount` | Modifies the approved amount of the loan |
| PUT | `v1/loans/:loanId/available-disbursement-amount` | Modifies the available disbursement amount of the loan |
| GET | `v1/loans/:loanId/buydown-fees/external-id/:loanTransactionExternalId` | Retrieve a BuyDown Fees allocation data |
| GET | `v1/loans/:loanId/buydown-fees/:loanTransactionId` | Retrieve a BuyDown Fees allocation data |
| GET | `v1/loans/:loanId/buydown-fees` | Get the amortization details of Buy Down fees for a loan |
| GET | `v1/loans/:loanId/capitalized-incomes/external-id/:loanTransactionExternalId` | Retrieve a capitalized income allocation data |
| GET | `v1/loans/:loanId/capitalized-incomes/:loanTransactionId` | Retrieve a capitalized income allocation data |
| GET | `v1/loans/:loanId/capitalized-incomes` | Fetch the Capitalized Income related informations |
| DELETE | `v1/loans/:loanId/charges/external-id/:loanChargeExternalId` | Delete a Loan Charge |
| GET | `v1/loans/:loanId/charges/external-id/:loanChargeExternalId` | Retrieve a Loan Charge |
| POST | `v1/loans/:loanId/charges/external-id/:loanChargeExternalId` | Pay / Waive / Adjustment for Loan Charge |
| PUT | `v1/loans/:loanId/charges/external-id/:loanChargeExternalId` | Update a Loan Charge |
| GET | `v1/loans/:loanId/charges/template` | Retrieve Loan Charges Template |
| DELETE | `v1/loans/:loanId/charges/:loanChargeId` | Delete a Loan Charge |
| GET | `v1/loans/:loanId/charges/:loanChargeId` | Retrieve a Loan Charge |
| POST | `v1/loans/:loanId/charges/:loanChargeId` | Pay / Waive / Adjustment for Loan Charge |
| PUT | `v1/loans/:loanId/charges/:loanChargeId` | Update a Loan Charge |
| GET | `v1/loans/:loanId/charges` | List Loan Charges |
| POST | `v1/loans/:loanId/charges` | Create a Loan Charge (no command provided) or Pay a charge (command=pay) |
| GET | `v1/loans/:loanId/collaterals/template` | Retrieve Collateral Details Template |
| DELETE | `v1/loans/:loanId/collaterals/:collateralId` | Remove a Collateral |
| GET | `v1/loans/:loanId/collaterals/:collateralId` | Retrieve a Collateral |
| PUT | `v1/loans/:loanId/collaterals/:collateralId` | Update a Collateral |
| GET | `v1/loans/:loanId/collaterals` | List Loan Collaterals |
| POST | `v1/loans/:loanId/collaterals` | Create a Collateral |
| GET | `v1/loans/:loanId/deferredincome` | Fetch the Capitalized Income related informations |
| GET | `v1/loans/:loanId/delinquency-actions` | Retrieve delinquency actions related to the loan |
| POST | `v1/loans/:loanId/delinquency-actions` | Adds a new delinquency action for a loan |
| GET | `v1/loans/:loanId/delinquencytags` | Retrieve the Loan Delinquency Tag history using the Loan Id |
| PUT | `v1/loans/:loanId/disbursements/editDisbursements` | add And Delete Disbursement Detail |
| GET | `v1/loans/:loanId/disbursements/:disbursementId` | retrive Detail |
| PUT | `v1/loans/:loanId/disbursements/:disbursementId` | update Disbursement Date |
| GET | `v1/loans/:loanId/guarantors/accounts/template` | accounts Template |
| GET | `v1/loans/:loanId/guarantors/downloadtemplate` | get Guarantor Template |
| GET | `v1/loans/:loanId/guarantors/template` | new Guarantor Template |
| POST | `v1/loans/:loanId/guarantors/uploadtemplate` | post Guarantor Template |
| DELETE | `v1/loans/:loanId/guarantors/:guarantorId` | delete Guarantor |
| GET | `v1/loans/:loanId/guarantors/:guarantorId` | retrieve Guarantor Details 1 |
| PUT | `v1/loans/:loanId/guarantors/:guarantorId` | update Guarantor |
| GET | `v1/loans/:loanId/guarantors` | retrieve Guarantor Details |
| POST | `v1/loans/:loanId/guarantors` | create Guarantor |
| DELETE | `v1/loans/:loanId/interest-pauses/:variationId` | Delete an interest pause period |
| PUT | `v1/loans/:loanId/interest-pauses/:variationId` | Update an interest pause period |
| GET | `v1/loans/:loanId/interest-pauses` | Retrieve all interest pause periods for a loan |
| POST | `v1/loans/:loanId/interest-pauses` | Create a new interest pause period for a loan |
| GET | `v1/loans/:loanId/postdatedchecks/:installmentId` | Get Post Dated Check |
| DELETE | `v1/loans/:loanId/postdatedchecks/:postDatedCheckId` | Delete Post Dated Check |
| PUT | `v1/loans/:loanId/postdatedchecks/:postDatedCheckId` | Update Post Dated Check, Bounced Check |
| GET | `v1/loans/:loanId/postdatedchecks` | Get All Post Dated Checks |
| POST | `v1/loans/:loanId/schedule` | Calculate loan repayment schedule based on Loan term variations / Updates loan repayment schedule based on Loan term variations / Updates loan repayment schedule by removing Loan term variations |
| GET | `v1/loans/:loanId/template` | retrieve Approval Template |
| GET | `v1/loans/:loanId/transactions/external-id/:externalTransactionId` | Retrieve a Transaction Details |
| POST | `v1/loans/:loanId/transactions/external-id/:externalTransactionId` | Adjust a Transaction |
| PUT | `v1/loans/:loanId/transactions/external-id/:transactionExternalId` | Undo a Waive Charge Transaction |
| GET | `v1/loans/:loanId/transactions/template` | Retrieve Loan Transaction Template |
| GET | `v1/loans/:loanId/transactions/:transactionId` | Retrieve a Transaction Details |
| POST | `v1/loans/:loanId/transactions/:transactionId` | Adjust a Transaction |
| PUT | `v1/loans/:loanId/transactions/:transactionId` | Undo a Waive Charge Transaction |
| GET | `v1/loans/:loanId/transactions` | Retrieve Transactions |
| POST | `v1/loans/:loanId/transactions` | Significant Loan Transactions |
| DELETE | `v1/loans/:loanId` | Delete a Loan Application |
| GET | `v1/loans/:loanId` | Retrieve a Loan |
| POST | `v1/loans/:loanId` | Approve Loan Application / Recover Loan Guarantee / Undo Loan Application Approval / Assign a Loan Officer / Unassign a Loan Officer / Reject Loan Application / Applicant Withdraws from Loan Application / Disburse Loan Disburse Loan To Savings Account / U |
| PUT | `v1/loans/:loanId` | Modify a loan application |
| GET | `v1/loans` | List Loans |
| POST | `v1/loans` | Calculate loan repayment schedule / Submit a new Loan Application |

### `loanproducts` (11)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/loanproducts/external-id/:externalProductId` | Retrieve a Loan Product |
| PUT | `v1/loanproducts/external-id/:externalProductId` | Update a Loan Product |
| GET | `v1/loanproducts/template` | Retrieve Loan Product Details Template |
| DELETE | `v1/loanproducts/:productId/productmix` | delete Product Mix |
| GET | `v1/loanproducts/:productId/productmix` | retrieve Template 12 |
| POST | `v1/loanproducts/:productId/productmix` | create Product Mix |
| PUT | `v1/loanproducts/:productId/productmix` | update Product Mix |
| GET | `v1/loanproducts/:productId` | Retrieve a Loan Product |
| PUT | `v1/loanproducts/:productId` | Update a Loan Product |
| GET | `v1/loanproducts` | List Loan Products |
| POST | `v1/loanproducts` | Create a Loan Product |

### `rescheduleloans` (5)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/rescheduleloans/template` | Retrieve all reschedule loan reasons |
| GET | `v1/rescheduleloans/:scheduleId` | Retrieve loan reschedule request by schedule id |
| POST | `v1/rescheduleloans/:scheduleId` | Update loan reschedule request |
| GET | `v1/rescheduleloans` | Retrieve all reschedule requests |
| POST | `v1/rescheduleloans` | Create loan reschedule request |

### `loan-collateral-management` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/loan-collateral-management/:collateralId` | Get Loan Collateral Details |
| DELETE | `v1/loan-collateral-management/:id` | Delete Loan Collateral |

### `floatingrates` (4)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/floatingrates/:floatingRateId` | Retrieve Floating Rate |
| PUT | `v1/floatingrates/:floatingRateId` | Update Floating Rate |
| GET | `v1/floatingrates` | List Floating Rates |
| POST | `v1/floatingrates` | Create a new Floating Rate |

### `rates` (4)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/rates/:rateId` | retrieve Rate |
| PUT | `v1/rates/:rateId` | update Rate |
| GET | `v1/rates` | get All Rates |
| POST | `v1/rates` | create Rate |

### `delinquency` (10)

| Method | Path | Operation |
|---|---|---|
| DELETE | `v1/delinquency/buckets/:delinquencyBucketId` | Delete Delinquency Bucket based on the Id |
| GET | `v1/delinquency/buckets/:delinquencyBucketId` | Retrieve a specific Delinquency Bucket based on the Id |
| PUT | `v1/delinquency/buckets/:delinquencyBucketId` | Update Delinquency Bucket based on the Id |
| GET | `v1/delinquency/buckets` | List all Delinquency Buckets |
| POST | `v1/delinquency/buckets` | Create Delinquency Bucket |
| DELETE | `v1/delinquency/ranges/:delinquencyRangeId` | Update Delinquency Range based on the Id |
| GET | `v1/delinquency/ranges/:delinquencyRangeId` | Retrieve a specific Delinquency Range based on the Id |
| PUT | `v1/delinquency/ranges/:delinquencyRangeId` | Update Delinquency Range based on the Id |
| GET | `v1/delinquency/ranges` | List all Delinquency Ranges |
| POST | `v1/delinquency/ranges` | Create Delinquency Range |

### `provisioningcategory` (4)

| Method | Path | Operation |
|---|---|---|
| DELETE | `v1/provisioningcategory/:categoryId` | delete Provisioning Category |
| PUT | `v1/provisioningcategory/:categoryId` | update Provisioning Category |
| GET | `v1/provisioningcategory` | retrieve All 15 |
| POST | `v1/provisioningcategory` | create Provisioning Category |

### `provisioningcriteria` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/provisioningcriteria/template` | retrieve Template 3 |
| DELETE | `v1/provisioningcriteria/:criteriaId` | Deletes Provisioning Criteria |
| GET | `v1/provisioningcriteria/:criteriaId` | Retrieves a Provisioning Criteria |
| PUT | `v1/provisioningcriteria/:criteriaId` | Updates a new Provisioning Criteria |
| GET | `v1/provisioningcriteria` | Retrieves all created Provisioning Criterias |
| POST | `v1/provisioningcriteria` | Create a new Provisioning Criteria |

### `products` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/products/:type/template` | retrieve Template 13 |
| GET | `v1/products/:type/:productId` | Retrieve a Share Product |
| POST | `v1/products/:type/:productId` | handle Commands 3 |
| PUT | `v1/products/:type/:productId` | Update a Share Product |
| GET | `v1/products/:type` | List Share Products |
| POST | `v1/products/:type` | Create a Share Product |

### `shareproduct` (5)

| Method | Path | Operation |
|---|---|---|
| DELETE | `v1/shareproduct/:productId/dividend/:dividendId` | delete Dividend Detail |
| GET | `v1/shareproduct/:productId/dividend/:dividendId` | retrieve Dividend Details |
| PUT | `v1/shareproduct/:productId/dividend/:dividendId` | update Dividend Detail |
| GET | `v1/shareproduct/:productId/dividend` | retrieve All 39 |
| POST | `v1/shareproduct/:productId/dividend` | create Dividend Detail |

### `accounts` (8)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/accounts/:type/downloadtemplate` | get Shared Accounts Template |
| GET | `v1/accounts/:type/template` | Retrieve Share Account Template |
| POST | `v1/accounts/:type/uploadtemplate` | post Shared Accounts Template |
| GET | `v1/accounts/:type/:accountId` | Retrieve a share application/account |
| POST | `v1/accounts/:type/:accountId` | Approve share application / Undo approval share application / Reject share application / Activate a share account / Close a share account / Apply additional shares on a share account / Approve additional shares request on a share account / Reject addition |
| PUT | `v1/accounts/:type/:accountId` | Modify a share application |
| GET | `v1/accounts/:type` | List share applications/accounts |
| POST | `v1/accounts/:type` | Submit new share application |

### `external-asset-owners` (12)

| Method | Path | Operation |
|---|---|---|
| PUT | `v1/external-asset-owners/loan-product/:loanProductId/attributes/:id` | Update a Loan Product Attribute |
| GET | `v1/external-asset-owners/loan-product/:loanProductId/attributes` | Retrieve All Loan Product Attributes |
| POST | `v1/external-asset-owners/loan-product/:loanProductId/attributes` | post External Asset Owner Loan Product Attribute |
| GET | `v1/external-asset-owners/owners/external-id/:ownerExternalId/journal-entries` | Retrieve Journal Entries of Owner |
| POST | `v1/external-asset-owners/search` | Search External Asset Owner Transfers by text or date ranges to settlement or effective dates |
| GET | `v1/external-asset-owners/transfers/active-transfer` | Retrieve Active Asset Owner Transfer |
| POST | `v1/external-asset-owners/transfers/external-id/:externalId` | transfer Request With Id 1 |
| POST | `v1/external-asset-owners/transfers/loans/external-id/:loanExternalId` | transfer Request With Loan External Id |
| POST | `v1/external-asset-owners/transfers/loans/:loanId` | transfer Request With Loan Id |
| POST | `v1/external-asset-owners/transfers/:id` | transfer Request With Id |
| GET | `v1/external-asset-owners/transfers/:transferId/journal-entries` | Retrieve Journal Entries of Transfer |
| GET | `v1/external-asset-owners/transfers` | Retrieve External Asset Owner Transfers |

### `CreditBureauConfiguration` (12)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/CreditBureauConfiguration/config/:organisationCreditBureauId` | get Configuration |
| PUT | `v1/CreditBureauConfiguration/configuration/:configurationId` | update Credit Bureau Configuration |
| POST | `v1/CreditBureauConfiguration/configuration/:creditBureauId` | create Credit Bureau Configuration |
| GET | `v1/CreditBureauConfiguration/loanProduct/:loanProductId` | fetch Mapping By Loan Product Id |
| GET | `v1/CreditBureauConfiguration/loanProduct` | fetch Loan Products |
| POST | `v1/CreditBureauConfiguration/mappings/:organisationCreditBureauId` | create Credit Bureau Loan Product Mapping |
| GET | `v1/CreditBureauConfiguration/mappings` | get Credit Bureau Loan Product Mapping |
| PUT | `v1/CreditBureauConfiguration/mappings` | update Credit Bureau Loan Product Mapping |
| POST | `v1/CreditBureauConfiguration/organisationCreditBureau/:organisationCreditBureauId` | add Organisation Credit Bureau |
| GET | `v1/CreditBureauConfiguration/organisationCreditBureau` | get Organisation Credit Bureau |
| PUT | `v1/CreditBureauConfiguration/organisationCreditBureau` | update Credit Bureau |
| GET | `v1/CreditBureauConfiguration` | get Credit Bureau |

### `creditBureauIntegration` (5)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/creditBureauIntegration/addCreditReport` | add Credit Report |
| GET | `v1/creditBureauIntegration/creditReport/:creditBureauId` | get Saved Credit Report |
| POST | `v1/creditBureauIntegration/creditReport` | fetch Credit Report |
| DELETE | `v1/creditBureauIntegration/deleteCreditReport/:creditBureauId` | delete Credit Report |
| POST | `v1/creditBureauIntegration/saveCreditReport` | save Credit Report |

### `mixmapping` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/mixmapping` | retrieve Taxonomy Mapping |
| PUT | `v1/mixmapping` | update Taxonomy Mapping |

### `mixreport` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/mixreport` | retrieve XBRL Report |

### `mixtaxonomy` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/mixtaxonomy` | retrieve All 14 |

## Accounting — 39 endpoints

### `glaccounts` (8)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/glaccounts/downloadtemplate` | get Gl Accounts Template |
| GET | `v1/glaccounts/template` | Retrieve GL Accounts Template |
| POST | `v1/glaccounts/uploadtemplate` | post Gl Accounts Template |
| DELETE | `v1/glaccounts/:glAccountId` | Delete a GL Account |
| GET | `v1/glaccounts/:glAccountId` | Retrieve a General Ledger Account |
| PUT | `v1/glaccounts/:glAccountId` | Update a GL Account |
| GET | `v1/glaccounts` | List General Ledger Account |
| POST | `v1/glaccounts` | Create a General Ledger Account |

### `glclosures` (5)

| Method | Path | Operation |
|---|---|---|
| DELETE | `v1/glclosures/:glClosureId` | Delete an accounting closure |
| GET | `v1/glclosures/:glClosureId` | Retrieve an Accounting Closure |
| PUT | `v1/glclosures/:glClosureId` | Update an Accounting closure |
| GET | `v1/glclosures` | List Accounting closures |
| POST | `v1/glclosures` | Create an Accounting Closure |

### `journalentries` (8)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/journalentries/downloadtemplate` | get Journal Entries Template |
| GET | `v1/journalentries/openingbalance` | retrieve Opening Balance |
| GET | `v1/journalentries/provisioning` | retrieve Journal Entries |
| POST | `v1/journalentries/uploadtemplate` | post Journal Entries Template |
| GET | `v1/journalentries/:journalEntryId` | Retrieve a single Entry |
| POST | `v1/journalentries/:transactionId` | Update Running balances for Journal Entries |
| GET | `v1/journalentries` | List Journal Entries |
| POST | `v1/journalentries` | Create "Balanced" Journal Entries |

### `accountingrules` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/accountingrules/template` | Retrieve Accounting Rule Details Template |
| DELETE | `v1/accountingrules/:accountingRuleId` | Delete a Accounting Rule |
| GET | `v1/accountingrules/:accountingRuleId` | Retrieve a Accounting rule |
| PUT | `v1/accountingrules/:accountingRuleId` | Update a Accounting Rule |
| GET | `v1/accountingrules` | Retrieve Accounting Rules |
| POST | `v1/accountingrules` | Create/Define a Accounting rule |

### `financialactivityaccounts` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/financialactivityaccounts/template` | retrieve Template |
| DELETE | `v1/financialactivityaccounts/:mappingId` | Delete a Financial Activity to Account Mapping |
| GET | `v1/financialactivityaccounts/:mappingId` | Retrieve a Financial Activity to Account Mapping
 |
| PUT | `v1/financialactivityaccounts/:mappingId` | Update a Financial Activity to Account Mapping |
| GET | `v1/financialactivityaccounts` | List Financial Activities to Accounts Mappings |
| POST | `v1/financialactivityaccounts` | Create a new Financial Activity to Accounts Mapping |

### `provisioningentries` (5)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/provisioningentries/entries` | retrieve Proviioning Entries |
| GET | `v1/provisioningentries/:entryId` | Retrieves a Provisioning Entry |
| POST | `v1/provisioningentries/:entryId` | Recreates Provisioning Entry |
| GET | `v1/provisioningentries` | List all Provisioning Entries |
| POST | `v1/provisioningentries` | Create new Provisioning Entries |

### `runaccruals` (1)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/runaccruals` | Executes Periodic Accrual Accounting |

## Teller — 21 endpoints

### `tellers` (19)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/tellers/:tellerId/cashiers/template` | Find Cashiers |
| POST | `v1/tellers/:tellerId/cashiers/:cashierId/allocate` | Allocate Cash To Cashier |
| POST | `v1/tellers/:tellerId/cashiers/:cashierId/settle` | Settle Cash From Cashier |
| GET | `v1/tellers/:tellerId/cashiers/:cashierId/summaryandtransactions` | Retrieve Transactions With Summary For Cashier |
| GET | `v1/tellers/:tellerId/cashiers/:cashierId/transactions/template` | Retrieve Cashier Transaction Template |
| GET | `v1/tellers/:tellerId/cashiers/:cashierId/transactions` | Retrieve Cashier Transactions |
| DELETE | `v1/tellers/:tellerId/cashiers/:cashierId` | Delete Cashier |
| GET | `v1/tellers/:tellerId/cashiers/:cashierId` | Retrieve a cashier |
| PUT | `v1/tellers/:tellerId/cashiers/:cashierId` | Update Cashier |
| GET | `v1/tellers/:tellerId/cashiers` | List Cashiers |
| POST | `v1/tellers/:tellerId/cashiers` | Create Cashiers |
| GET | `v1/tellers/:tellerId/journals` | get Journal Data |
| GET | `v1/tellers/:tellerId/transactions/:transactionId` | find Transaction Data |
| GET | `v1/tellers/:tellerId/transactions` | get Transaction Data |
| DELETE | `v1/tellers/:tellerId` | delete Teller |
| GET | `v1/tellers/:tellerId` | Retrieve tellers |
| PUT | `v1/tellers/:tellerId` | Update teller |
| GET | `v1/tellers` | List all tellers |
| POST | `v1/tellers` | Create teller |

### `cashiers` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/cashiers` | get Cashier Data |

### `cashiersjournal` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/cashiersjournal` | get Journal Data 1 |

## SystemConfig — 86 endpoints

### `codes` (11)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/codes/name/:codeName` | Retrieve a Code |
| DELETE | `v1/codes/:codeId/codevalues/:codeValueId` | Delete a Code description |
| GET | `v1/codes/:codeId/codevalues/:codeValueId` | Retrieve a Code description |
| PUT | `v1/codes/:codeId/codevalues/:codeValueId` | Update a Code description |
| GET | `v1/codes/:codeId/codevalues` | List Code Values |
| POST | `v1/codes/:codeId/codevalues` | Create a Code description |
| DELETE | `v1/codes/:codeId` | Delete a Code |
| GET | `v1/codes/:codeId` | Retrieve a Code |
| PUT | `v1/codes/:codeId` | Update a Code |
| GET | `v1/codes` | Retrieve Codes |
| POST | `v1/codes` | Create a Code |

### `configurations` (5)

| Method | Path | Operation |
|---|---|---|
| PUT | `v1/configurations/name/:configName` | Update Global Configuration by name |
| GET | `v1/configurations/name/:name` | Retrieve Global Configuration |
| GET | `v1/configurations/:configId` | Retrieve Global Configuration |
| PUT | `v1/configurations/:configId` | Update Global Configuration |
| GET | `v1/configurations` | Retrieve Global Configuration / Retrieve Global Configuration for surveys |

### `externalservice` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/externalservice/:servicename` | Retrieve External Services Configuration |
| PUT | `v1/externalservice/:servicename` | Update External Service |

### `audits` (3)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/audits/searchtemplate` | Audit Search Template |
| GET | `v1/audits/:auditId` | Retrieve an Audit Entry |
| GET | `v1/audits` | List Audits |

### `hooks` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/hooks/template` | Retrieve Hooks Template |
| DELETE | `v1/hooks/:hookId` | Delete a Hook |
| GET | `v1/hooks/:hookId` | Retrieve a Hook |
| PUT | `v1/hooks/:hookId` | Update a Hook |
| GET | `v1/hooks` | Retrieve Hooks |
| POST | `v1/hooks` | Create a Hook |

### `caches` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/caches` | Retrieve Cache Types |
| PUT | `v1/caches` | Switch Cache |

### `businessdate` (3)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/businessdate/:type` | Retrieve a specific Business date |
| GET | `v1/businessdate` | List all business dates |
| POST | `v1/businessdate` | Update Business Date |

### `externalevents` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/externalevents/configuration` | List all external event configurations |
| PUT | `v1/externalevents/configuration` | Enable/Disable external events posting |

### `fieldconfiguration` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/fieldconfiguration/:entity` | Retrieves the Entity Field Configuration |

### `datatables` (16)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/datatables/deregister/:datatable` | Deregister Data Table |
| POST | `v1/datatables/register/:datatable/:apptable` | Register Data Table |
| DELETE | `v1/datatables/:datatableName` | Delete Data Table |
| PUT | `v1/datatables/:datatableName` | Update Data Table |
| GET | `v1/datatables/:datatable/query` | Query Data Table values |
| POST | `v1/datatables/:datatable/query` | Query Data Table values |
| DELETE | `v1/datatables/:datatable/:apptableId/:datatableId` | Delete Entry in Datatable (One to Many) |
| GET | `v1/datatables/:datatable/:apptableId/:datatableId` | get Datatable Many Entry |
| PUT | `v1/datatables/:datatable/:apptableId/:datatableId` | Update Entry in Data Table (One to Many) |
| DELETE | `v1/datatables/:datatable/:apptableId` | Delete Entry(s) in Data Table |
| GET | `v1/datatables/:datatable/:apptableId` | Retrieve Entry(s) from Data Table |
| POST | `v1/datatables/:datatable/:apptableId` | Create Entry in Data Table |
| PUT | `v1/datatables/:datatable/:apptableId` | Update Entry in Data Table (One to One) |
| GET | `v1/datatables/:datatable` | Retrieve Data Table Details |
| GET | `v1/datatables` | List Data Tables |
| POST | `v1/datatables` | Create Data Table |

### `entityDatatableChecks` (4)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/entityDatatableChecks/template` | Retrieve Entity-Datatable Checks Template |
| DELETE | `v1/entityDatatableChecks/:entityDatatableCheckId` | Delete Entity-Datatable Checks |
| GET | `v1/entityDatatableChecks` | List Entity-Datatable Checks |
| POST | `v1/entityDatatableChecks` | Create Entity-Datatable Checks |

### `imports` (3)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/imports/downloadOutputTemplate` | get Output Template |
| GET | `v1/imports/getOutputTemplateLocation` | retrive Output Template Location |
| GET | `v1/imports` | retrieve Import Documents |

### `{entityType}` (19)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/:entityType/:entityId/calendars/template` | retrieve New Calendar Details |
| DELETE | `v1/:entityType/:entityId/calendars/:calendarId` | delete Calendar |
| GET | `v1/:entityType/:entityId/calendars/:calendarId` | retrieve Calendar |
| PUT | `v1/:entityType/:entityId/calendars/:calendarId` | update Calendar |
| GET | `v1/:entityType/:entityId/calendars` | retrieve Calendars By Entity |
| POST | `v1/:entityType/:entityId/calendars` | create Calendar |
| GET | `v1/:entityType/:entityId/documents/:documentId/attachment` | Retrieve Binary File associated with Document |
| DELETE | `v1/:entityType/:entityId/documents/:documentId` | Remove a Document |
| GET | `v1/:entityType/:entityId/documents/:documentId` | Retrieve a Document |
| PUT | `v1/:entityType/:entityId/documents/:documentId` | Update a Document |
| GET | `v1/:entityType/:entityId/documents` | List documents |
| POST | `v1/:entityType/:entityId/documents` | Create a Document |
| GET | `v1/:entityType/:entityId/meetings/template` | template 11 |
| DELETE | `v1/:entityType/:entityId/meetings/:meetingId` | delete Meeting |
| GET | `v1/:entityType/:entityId/meetings/:meetingId` | retrieve Meeting |
| POST | `v1/:entityType/:entityId/meetings/:meetingId` | perform Meeting Commands |
| PUT | `v1/:entityType/:entityId/meetings/:meetingId` | update Meeting |
| GET | `v1/:entityType/:entityId/meetings` | retrieve Meetings |
| POST | `v1/:entityType/:entityId/meetings` | create Meeting |

### `{entity}` (4)

| Method | Path | Operation |
|---|---|---|
| DELETE | `v1/:entity/:entityId/images` | delete Client Image |
| GET | `v1/:entity/:entityId/images` | retrieve Image |
| POST | `v1/:entity/:entityId/images` | add New Client Image 1 |
| PUT | `v1/:entity/:entityId/images` | update Client Image 1 |

### `{resourceType}` (5)

| Method | Path | Operation |
|---|---|---|
| DELETE | `v1/:resourceType/:resourceId/notes/:noteId` | Delete a Resource Note |
| GET | `v1/:resourceType/:resourceId/notes/:noteId` | Retrieve a Resource Note |
| PUT | `v1/:resourceType/:resourceId/notes/:noteId` | Update a Resource Note |
| GET | `v1/:resourceType/:resourceId/notes` | Retrieve a Resource's description |
| POST | `v1/:resourceType/:resourceId/notes` | Add a Resource Note |

## Scheduler (HeartBeat) — 16 endpoints

### `jobs` (14)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/jobs/names` | List Business Jobs |
| GET | `v1/jobs/short-name/:shortName/runhistory` | Retrieve Job Run History |
| GET | `v1/jobs/short-name/:shortName` | Retrieve a Job |
| POST | `v1/jobs/short-name/:shortName` | Run a Job |
| PUT | `v1/jobs/short-name/:shortName` | Update a Job |
| GET | `v1/jobs/:jobId/runhistory` | Retrieve Job Run History |
| GET | `v1/jobs/:jobId` | Retrieve a Job |
| POST | `v1/jobs/:jobId` | Run a Job |
| PUT | `v1/jobs/:jobId` | Update a Job |
| GET | `v1/jobs/:jobName/available-steps` | List Business Step Configurations for a Job |
| POST | `v1/jobs/:jobName/inline` | Starts an inline Job |
| GET | `v1/jobs/:jobName/steps` | List Business Step Configurations for a Job |
| PUT | `v1/jobs/:jobName/steps` | List Business Step Configurations for a Job |
| GET | `v1/jobs` | Retrieve Scheduler Jobs |

### `scheduler` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/scheduler` | Retrieve Scheduler Status |
| POST | `v1/scheduler` | Activate Scheduler Jobs / Suspend Scheduler Jobs |

## Reporting — 41 endpoints

### `reports` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/reports/template` | Retrieve Report Template |
| DELETE | `v1/reports/:id` | Delete a Report |
| GET | `v1/reports/:id` | Retrieve a Report
 |
| PUT | `v1/reports/:id` | Update a Report |
| GET | `v1/reports` | List Reports |
| POST | `v1/reports` | Create a Report |

### `runreports` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/runreports/availableExports/:reportName` | Return all available export types for the specific report |
| GET | `v1/runreports/:reportName` | Running a Report |

### `adhocquery` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/adhocquery/template` | template |
| DELETE | `v1/adhocquery/:adHocId` | delete Ad Hoc Query |
| GET | `v1/adhocquery/:adHocId` | retrieve Ad Hoc Query |
| PUT | `v1/adhocquery/:adHocId` | update |
| GET | `v1/adhocquery` | retrieve All 2 |
| POST | `v1/adhocquery` | create Ad Hoc Query |

### `search` (3)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/search/advance` | Adhoc query search |
| GET | `v1/search/template` | Retrive Adhoc Search query template |
| GET | `v1/search` | Search Resources |

### `surveys` (12)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/surveys/scorecards/clients/:clientId` | find By Client 1 |
| GET | `v1/surveys/scorecards/:surveyId/clients/:clientId` | find By Survey And Client |
| GET | `v1/surveys/scorecards/:surveyId` | List all Scorecard entries |
| POST | `v1/surveys/scorecards/:surveyId` | Create a Scorecard entry |
| GET | `v1/surveys/:id` | Retrieve a Survey |
| POST | `v1/surveys/:id` | Deactivate Survey |
| PUT | `v1/surveys/:id` | edit Survey |
| GET | `v1/surveys/:surveyId/lookuptables/:key` | Retrieve a Lookup Table entry |
| GET | `v1/surveys/:surveyId/lookuptables` | List all Lookup Table entries |
| POST | `v1/surveys/:surveyId/lookuptables` | Create a Lookup Table entry |
| GET | `v1/surveys` | List all Surveys |
| POST | `v1/surveys` | Create a Survey |

### `survey` (7)

| Method | Path | Operation |
|---|---|---|
| PUT | `v1/survey/register/:surveyName/:apptable` | register |
| POST | `v1/survey/:surveyName/:apptableId` | Create an entry in the survey table |
| GET | `v1/survey/:surveyName/:clientId/:entryId` | get Survey Entry |
| DELETE | `v1/survey/:surveyName/:clientId/:fulfilledId` | delete Datatable Entries 1 |
| GET | `v1/survey/:surveyName/:clientId` | get Client Survey Overview |
| GET | `v1/survey/:surveyName` | Retrieve survey |
| GET | `v1/survey` | Retrieve surveys |

### `likelihood` (3)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/likelihood/:ppiName/:likelihoodId` | retrieve |
| PUT | `v1/likelihood/:ppiName/:likelihoodId` | update 4 |
| GET | `v1/likelihood/:ppiName` | retrieve All 11 |

### `povertyLine` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/povertyLine/:ppiName/:likelihoodId` | retrieve All 13 |
| GET | `v1/povertyLine/:ppiName` | retrieve All 12 |

## Notification — 43 endpoints

### `notifications` (2)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/notifications` | get All Notifications |
| PUT | `v1/notifications` | update 5 |

### `sms` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/sms/:campaignId/messageByStatus` | retrieve All Sms By Status |
| DELETE | `v1/sms/:resourceId` | delete 5 |
| GET | `v1/sms/:resourceId` | retrieve One 6 |
| PUT | `v1/sms/:resourceId` | update 3 |
| GET | `v1/sms` | retrieve All 10 |
| POST | `v1/sms` | create 2 |

### `smscampaigns` (8)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/smscampaigns/preview` | preview 1 |
| GET | `v1/smscampaigns/template` | Retrieve a SMS Campaign |
| DELETE | `v1/smscampaigns/:campaignId` | Delete a SMS Campaign |
| POST | `v1/smscampaigns/:campaignId` | SMS Campaign |
| PUT | `v1/smscampaigns/:campaignId` | Update a Campaign |
| GET | `v1/smscampaigns/:resourceId` | Retrieve a SMS Campaign |
| GET | `v1/smscampaigns` | List SMS Campaigns |
| POST | `v1/smscampaigns` | Create a SMS Campaign |

### `email` (20)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/email/campaign/preview` | preview |
| GET | `v1/email/campaign/template/:resourceId` | retrieve One Template |
| GET | `v1/email/campaign/template` | template 1 |
| DELETE | `v1/email/campaign/:resourceId` | delete 2 |
| GET | `v1/email/campaign/:resourceId` | retrieve One Campaign |
| POST | `v1/email/campaign/:resourceId` | activate |
| PUT | `v1/email/campaign/:resourceId` | update Campaign |
| GET | `v1/email/campaign` | retrieve All Campaign |
| POST | `v1/email/campaign` | create Campaign |
| GET | `v1/email/configuration` | retrieve All 5 |
| PUT | `v1/email/configuration` | update Configuration |
| GET | `v1/email/failedEmail` | retrieve Failed Email |
| GET | `v1/email/messageByStatus` | retrieve All Email By Status |
| GET | `v1/email/pendingEmail` | retrieve Pending Email |
| GET | `v1/email/sentEmail` | retrieve Sent Email |
| DELETE | `v1/email/:resourceId` | delete 1 |
| GET | `v1/email/:resourceId` | retrieve One 1 |
| PUT | `v1/email/:resourceId` | update 2 |
| GET | `v1/email` | retrieve All Emails |
| POST | `v1/email` | create 1 |

### `reportmailingjobs` (6)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/reportmailingjobs/template` | Retrieve Report Mailing Job Details Template |
| DELETE | `v1/reportmailingjobs/:entityId` | Delete a Report Mailing Job |
| GET | `v1/reportmailingjobs/:entityId` | Retrieve a Report Mailing Job |
| PUT | `v1/reportmailingjobs/:entityId` | Update a Report Mailing Job
 |
| GET | `v1/reportmailingjobs` | List Report Mailing Jobs |
| POST | `v1/reportmailingjobs` | Create a Report Mailing Job |

### `reportmailingjobrunhistory` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/reportmailingjobrunhistory` | List Report Mailing Job History |

## Template — 8 endpoints

### `templates` (8)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/templates/template` | Retrieve UGD Details Template |
| GET | `v1/templates/:templateId/template` | get Template By Template |
| DELETE | `v1/templates/:templateId` | Delete a UGD |
| GET | `v1/templates/:templateId` | Retrieve a UGD |
| POST | `v1/templates/:templateId` | merge Template |
| PUT | `v1/templates/:templateId` | Update a UGD |
| GET | `v1/templates` | Retrieve all UGDs |
| POST | `v1/templates` | Add a UGD |

## SelfService — 60 endpoints

### `self` (60)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/self/accounttransfers/template` | Retrieve Account Transfer Template |
| POST | `v1/self/accounttransfers` | Create new Transfer |
| POST | `v1/self/authentication` | Verify authentication |
| GET | `v1/self/beneficiaries/tpt/template` | Beneficiary Third Party Transfer Template |
| DELETE | `v1/self/beneficiaries/tpt/:beneficiaryId` | Delete TPT Beneficiary |
| PUT | `v1/self/beneficiaries/tpt/:beneficiaryId` | Update TPT Beneficiary |
| GET | `v1/self/beneficiaries/tpt` | Get All TPT Beneficiary |
| POST | `v1/self/beneficiaries/tpt` | Add TPT Beneficiary |
| GET | `v1/self/clients/:clientId/accounts` | Retrieve client accounts overview |
| GET | `v1/self/clients/:clientId/charges/:chargeId` | Retrieve a Client Charge |
| GET | `v1/self/clients/:clientId/charges` | List Client Charges |
| DELETE | `v1/self/clients/:clientId/images` | delete Client Image 1 |
| GET | `v1/self/clients/:clientId/images` | Retrieve Client Image |
| POST | `v1/self/clients/:clientId/images` | add New Client Image 2 |
| GET | `v1/self/clients/:clientId/obligeedetails` | retrieve Obligee Details 2 |
| GET | `v1/self/clients/:clientId/transactions/:transactionId` | Retrieve a Client Transaction |
| GET | `v1/self/clients/:clientId/transactions` | List Client Transactions |
| GET | `v1/self/clients/:clientId` | Retrieve a Client |
| GET | `v1/self/clients` | List Clients associated to the user |
| GET | `v1/self/device/registration/client/:clientId` | retrieve Device Registration By Client Id |
| DELETE | `v1/self/device/registration/:id` | delete 22 |
| GET | `v1/self/device/registration/:id` | retrieve Device Regiistration |
| PUT | `v1/self/device/registration/:id` | update Device Registration |
| GET | `v1/self/device/registration` | retrieve All Device Registrations |
| POST | `v1/self/device/registration` | register Device |
| GET | `v1/self/loanproducts/:productId` | retrieve Loan Product Details 2 |
| GET | `v1/self/loanproducts` | retrieve All Loan Products 1 |
| GET | `v1/self/loans/template` | Retrieve Loan Details Template |
| GET | `v1/self/loans/:loanId/charges/:chargeId` | Retrieve a Loan Charge |
| GET | `v1/self/loans/:loanId/charges` | List Loan Charges |
| GET | `v1/self/loans/:loanId/guarantors` | retrieve Guarantor Details 2 |
| GET | `v1/self/loans/:loanId/transactions/:transactionId` | Retrieve a Loan Transaction Details |
| GET | `v1/self/loans/:loanId` | Retrieve a Loan |
| POST | `v1/self/loans/:loanId` | Applicant Withdraws from Loan Application |
| PUT | `v1/self/loans/:loanId` | Update a Loan Application |
| POST | `v1/self/loans` | Calculate Loan Repayment Schedule / Submit a new Loan Application |
| GET | `v1/self/pockets` | Retrieve accounts linked to pocket |
| POST | `v1/self/pockets` | Link/delink accounts to/from pocket |
| GET | `v1/self/products/share/:productId` | retrieve Product 1 |
| GET | `v1/self/products/share` | retrieve All Products 1 |
| POST | `v1/self/registration/user` | create Self Service User |
| POST | `v1/self/registration` | create Self Service Registration Request |
| GET | `v1/self/runreports/:reportName` | Running A Report |
| GET | `v1/self/savingsaccounts/template` | template 18 |
| GET | `v1/self/savingsaccounts/:accountId/charges/:savingsAccountChargeId` | Retrieve a Savings account Charge |
| GET | `v1/self/savingsaccounts/:accountId/charges` | List Savings Charges |
| GET | `v1/self/savingsaccounts/:accountId/transactions/:transactionId` | Retrieve Savings Account Transaction |
| GET | `v1/self/savingsaccounts/:accountId` | Retrieve a savings account |
| PUT | `v1/self/savingsaccounts/:accountId` | modify Savings Account Application |
| POST | `v1/self/savingsaccounts` | submit Savings Account Application |
| GET | `v1/self/savingsproducts/:productId` | retrieve One 29 |
| GET | `v1/self/savingsproducts` | retrieve All 38 |
| GET | `v1/self/shareaccounts/template` | Retrieve Share Account Template |
| GET | `v1/self/shareaccounts/:accountId` | Retrieve a share application/account |
| POST | `v1/self/shareaccounts` | Submit new share application |
| GET | `v1/self/surveys/scorecards/clients/:clientId` | find By Client |
| POST | `v1/self/surveys/scorecards/:surveyId` | create Scorecard |
| GET | `v1/self/surveys` | fetch All Surveys |
| PUT | `v1/self/user` | Update User |
| GET | `v1/self/userdetails` | Fetch authenticated user details |

## Interoperation (Payments) — 19 endpoints

### `interoperation` (19)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/interoperation/accounts/:accountId/identifiers` | Query Interoperation secondary identifiers by Account Id |
| GET | `v1/interoperation/accounts/:accountId/kyc` | Query KYC by Account Id |
| GET | `v1/interoperation/accounts/:accountId/transactions` | Query transactions by Account Id |
| GET | `v1/interoperation/accounts/:accountId` | Query Interoperation Account details |
| GET | `v1/interoperation/health` | Query Interoperation Health Request |
| DELETE | `v1/interoperation/parties/:idType/:idValue/:subIdOrType` | Allow Interoperation Identifier registration |
| GET | `v1/interoperation/parties/:idType/:idValue/:subIdOrType` | Query Interoperation Account by secondary identifier |
| POST | `v1/interoperation/parties/:idType/:idValue/:subIdOrType` | Interoperation Identifier registration |
| DELETE | `v1/interoperation/parties/:idType/:idValue` | Allow Interoperation Identifier registration |
| GET | `v1/interoperation/parties/:idType/:idValue` | Query Interoperation Account by secondary identifier |
| POST | `v1/interoperation/parties/:idType/:idValue` | Interoperation Identifier registration |
| POST | `v1/interoperation/quotes` | Calculate Interoperation Quote |
| POST | `v1/interoperation/requests` | Allow Interoperation Transaction Request |
| POST | `v1/interoperation/transactions/:accountId/disburse` | Disburse Loan by Account Id |
| POST | `v1/interoperation/transactions/:accountId/loanrepayment` | Disburse Loan by Account Id |
| GET | `v1/interoperation/transactions/:transactionCode/quotes/:quoteCode` | Query Interoperation Quote |
| GET | `v1/interoperation/transactions/:transactionCode/requests/:requestCode` | Query Interoperation Transaction Request |
| GET | `v1/interoperation/transactions/:transactionCode/transfers/:transferCode` | Query Interoperation Transfer |
| POST | `v1/interoperation/transfers` | Prepare Interoperation Transfer |

## Batch/Misc — 15 endpoints

### `batches` (1)

| Method | Path | Operation |
|---|---|---|
| POST | `v1/batches` | Batch requests in a single transaction |

### `echo` (1)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/echo` | get |

### `internal` (13)

| Method | Path | Operation |
|---|---|---|
| GET | `v1/internal/client/:clientId/audit` | get Client Audit Fields |
| POST | `v1/internal/cob/fast-forward-cob-date-of-loan/:loanId` | update Loan Cob Last Date |
| GET | `v1/internal/cob/partitions/:partitionSize` | get Cob Partitions |
| PUT | `v1/internal/configurations/name/:configName/value/:configValue` | update Global Configuration |
| DELETE | `v1/internal/externalevents` | delete All External Events |
| GET | `v1/internal/externalevents` | get All External Events |
| GET | `v1/internal/loan/progressive/:loanId/model` | Fetch ProgressiveLoanInterestScheduleModel |
| POST | `v1/internal/loan/progressive/:loanId/model` | Update and Save ProgressiveLoanInterestScheduleModel |
| GET | `v1/internal/loan/status/:statusId` | get Loans By Status |
| GET | `v1/internal/loan/:loanId/advanced-payment-allocation-rules` | get Advanced Payment Allocation Rules Of Loan |
| GET | `v1/internal/loan/:loanId/audit` | get Loan Audit Fields |
| GET | `v1/internal/loan/:loanId/transaction/:transactionId/audit` | get Loan Transaction Audit Fields |
| POST | `v1/internal/loans/:loanId/place-lock/:lockOwner` | place Lock On Loan Account |
