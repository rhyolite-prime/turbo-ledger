#include "LoanProductsController.h"

#include "dto/BaseApiResponse.h"


void LoanProductsController::getLoanProducts(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    turbo_ledger_portfolio::dto::BaseApiResponse response;
    response.success = true;

    Json::Value loanProduct;
    loanProduct["id"] = 1;
    loanProduct["name"] = "personal loan product";
    loanProduct["includeInBorrowerCycle"] = false;
    loanProduct["useBorrowerCycle"] = false;
    loanProduct["startDate"] = "23-02-2026";
    loanProduct["closeDate"] = "23-02-2026";
    loanProduct["status"] = "active";
    loanProduct["principal"] = 10000.00;
    loanProduct["minPrincipal"] = 5000;
    loanProduct["maxPrincipal"] = 1500;
    loanProduct["numberOfRepayments"] = 10;
    loanProduct["minNumberOfRepayments"] = 5;
    loanProduct["maxNumberOfRepayments"] = 15;
    loanProduct["repaymentEvery"] = 7;
    loanProduct["transactionProcessingStrategyId"] = 7;
    loanProduct["transactionProcessingStrategyName"] = "Turbo Ledger Style";
    loanProduct["interestRatePerPeriod"] = 15;

    Json::Value offices(Json::arrayValue);
    offices.append(loanProduct);

    response.result = offices;
    response.message = "Loan Products retrieved successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);
}


void LoanProductsController::getLoanProductDetails(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    turbo_ledger_portfolio::dto::BaseApiResponse response;
    response.success = true;

    Json::Value loanProductTemplate;

    // Basic properties
    loanProductTemplate["includeInBorrowerCycle"] = false;
    loanProductTemplate["useBorrowerCycle"] = false;

    // Currency
    Json::Value currency;
    currency["code"] = "";
    currency["name"] = "";
    currency["decimalPlaces"] = 0;
    currency["inMultiplesOf"] = 0;
    currency["displaySymbol"] = "";
    currency["nameCode"] = "";
    currency["displayLabel"] = " []";
    loanProductTemplate["currency"] = currency;

    // Repayment Frequency Type
    Json::Value repaymentFrequencyType;
    repaymentFrequencyType["id"] = 2;
    repaymentFrequencyType["code"] = "repaymentFrequency.periodFrequencyType.months";
    repaymentFrequencyType["value"] = "Months";
    loanProductTemplate["repaymentFrequencyType"] = repaymentFrequencyType;

    // Interest Rate Frequency Type
    Json::Value interestRateFrequencyType;
    interestRateFrequencyType["id"] = 2;
    interestRateFrequencyType["code"] = "interestRateFrequency.periodFrequencyType.months";
    interestRateFrequencyType["value"] = "Per month";
    loanProductTemplate["interestRateFrequencyType"] = interestRateFrequencyType;

    // Amortization Type
    Json::Value amortizationType;
    amortizationType["id"] = 1;
    amortizationType["code"] = "amortizationType.equal.installments";
    amortizationType["value"] = "Equal installments";
    loanProductTemplate["amortizationType"] = amortizationType;

    // Interest Type
    Json::Value interestType;
    interestType["id"] = 0;
    interestType["code"] = "interestType.declining.balance";
    interestType["value"] = "Declining Balance";
    loanProductTemplate["interestType"] = interestType;

    // Interest Calculation Period Type
    Json::Value interestCalculationPeriodType;
    interestCalculationPeriodType["id"] = 1;
    interestCalculationPeriodType["code"] = "interestCalculationPeriodType.same.as.repayment.period";
    interestCalculationPeriodType["value"] = "Same as repayment period";
    loanProductTemplate["interestCalculationPeriodType"] = interestCalculationPeriodType;

    // Borrower Cycle Variations
    loanProductTemplate["principalVariationsForBorrowerCycle"] = Json::Value(Json::arrayValue);
    loanProductTemplate["interestRateVariationsForBorrowerCycle"] = Json::Value(Json::arrayValue);
    loanProductTemplate["numberOfRepaymentVariationsForBorrowerCycle"] = Json::Value(Json::arrayValue);

    // Accounting Rule
    Json::Value accountingRule;
    accountingRule["id"] = 1;
    accountingRule["code"] = "accountingRuleType.none";
    accountingRule["value"] = "NONE";
    loanProductTemplate["accountingRule"] = accountingRule;

    // Days In Month Type
    Json::Value daysInMonthType;
    daysInMonthType["id"] = 1;
    daysInMonthType["code"] = "DaysInMonthType.actual";
    daysInMonthType["value"] = "Actual";
    loanProductTemplate["daysInMonthType"] = daysInMonthType;

    // Days In Year Type
    Json::Value daysInYearType;
    daysInYearType["id"] = 1;
    daysInYearType["code"] = "DaysInYearType.actual";
    daysInYearType["value"] = "Actual";
    loanProductTemplate["daysInYearType"] = daysInYearType;

    // Interest Recalculation
    loanProductTemplate["isInterestRecalculationEnabled"] = false;
    Json::Value interestRecalculationData;
    Json::Value compoundingType;
    compoundingType["id"] = 0;
    compoundingType["code"] = "interestRecalculationCompoundingMethod.none";
    compoundingType["value"] = "None";
    interestRecalculationData["interestRecalculationCompoundingType"] = compoundingType;

    Json::Value rescheduleStrategyType;
    rescheduleStrategyType["id"] = 3;
    rescheduleStrategyType["code"] = "loanRescheduleStrategyMethod.reduce.emi.amount";
    rescheduleStrategyType["value"] = "Reduce EMI amount";
    interestRecalculationData["rescheduleStrategyType"] = rescheduleStrategyType;

    Json::Value preClosureStrategy;
    preClosureStrategy["id"] = 1;
    preClosureStrategy["code"] = "loanPreClosureInterestCalculationStrategy.tillPreClosureDate";
    preClosureStrategy["value"] = "Till preclose Date";
    interestRecalculationData["preClosureInterestCalculationStrategy"] = preClosureStrategy;
    loanProductTemplate["interestRecalculationData"] = interestRecalculationData;

    // Payment Type Options
    Json::Value paymentTypeOptions(Json::arrayValue);
    Json::Value paymentType;
    paymentType["id"] = 10;
    paymentType["name"] = "check";
    paymentType["position"] = 1;
    paymentTypeOptions.append(paymentType);
    loanProductTemplate["paymentTypeOptions"] = paymentTypeOptions;

    // Currency Options
    Json::Value currencyOptions(Json::arrayValue);
    Json::Value usdCurrency;
    usdCurrency["code"] = "USD";
    usdCurrency["name"] = "US Dollar";
    usdCurrency["decimalPlaces"] = 2;
    usdCurrency["displaySymbol"] = "$";
    usdCurrency["nameCode"] = "currency.USD";
    usdCurrency["displayLabel"] = "US Dollar ($)";
    currencyOptions.append(usdCurrency);
    loanProductTemplate["currencyOptions"] = currencyOptions;

    // Repayment Frequency Type Options
    Json::Value repaymentFrequencyTypeOptions(Json::arrayValue);
    Json::Value repayDays, repayWeeks, repayMonths;
    repayDays["id"] = 0;
    repayDays["code"] = "repaymentFrequency.periodFrequencyType.days";
    repayDays["value"] = "Days";
    repayWeeks["id"] = 1;
    repayWeeks["code"] = "repaymentFrequency.periodFrequencyType.weeks";
    repayWeeks["value"] = "Weeks";
    repayMonths["id"] = 2;
    repayMonths["code"] = "repaymentFrequency.periodFrequencyType.months";
    repayMonths["value"] = "Months";
    repaymentFrequencyTypeOptions.append(repayDays);
    repaymentFrequencyTypeOptions.append(repayWeeks);
    repaymentFrequencyTypeOptions.append(repayMonths);
    loanProductTemplate["repaymentFrequencyTypeOptions"] = repaymentFrequencyTypeOptions;

    // Pre Closure Interest Calculation Strategy Options
    Json::Value preClosureOptions(Json::arrayValue);
    Json::Value preClose1, preClose2;
    preClose1["id"] = 1;
    preClose1["code"] = "loanPreClosureInterestCalculationStrategy.tillPreClosureDate";
    preClose1["value"] = "Till preclose Date";
    preClose2["id"] = 2;
    preClose2["code"] = "loanPreClosureInterestCalculationStrategy.tillRestFrequencyDate";
    preClose2["value"] = "Till rest Frequency Date";
    preClosureOptions.append(preClose1);
    preClosureOptions.append(preClose2);
    loanProductTemplate["preClosureInterestCalculationStrategyOptions"] = preClosureOptions;

    // Interest Rate Frequency Type Options
    Json::Value interestRateFrequencyTypeOptions(Json::arrayValue);
    Json::Value intRateMonths, intRateYears;
    intRateMonths["id"] = 2;
    intRateMonths["code"] = "interestRateFrequency.periodFrequencyType.months";
    intRateMonths["value"] = "Per month";
    intRateYears["id"] = 3;
    intRateYears["code"] = "interestRateFrequency.periodFrequencyType.years";
    intRateYears["value"] = "Per year";
    interestRateFrequencyTypeOptions.append(intRateMonths);
    interestRateFrequencyTypeOptions.append(intRateYears);
    loanProductTemplate["interestRateFrequencyTypeOptions"] = interestRateFrequencyTypeOptions;

    // Amortization Type Options
    Json::Value amortizationTypeOptions(Json::arrayValue);
    Json::Value amortEqual, amortPrincipal;
    amortEqual["id"] = 1;
    amortEqual["code"] = "amortizationType.equal.installments";
    amortEqual["value"] = "Equal installments";
    amortPrincipal["id"] = 0;
    amortPrincipal["code"] = "amortizationType.equal.principal";
    amortPrincipal["value"] = "Equal principal payments";
    amortizationTypeOptions.append(amortEqual);
    amortizationTypeOptions.append(amortPrincipal);
    loanProductTemplate["amortizationTypeOptions"] = amortizationTypeOptions;

    // Interest Type Options
    Json::Value interestTypeOptions(Json::arrayValue);
    Json::Value intFlat, intDeclining;
    intFlat["id"] = 1;
    intFlat["code"] = "interestType.flat";
    intFlat["value"] = "Flat";
    intDeclining["id"] = 0;
    intDeclining["code"] = "interestType.declining.balance";
    intDeclining["value"] = "Declining Balance";
    interestTypeOptions.append(intFlat);
    interestTypeOptions.append(intDeclining);
    loanProductTemplate["interestTypeOptions"] = interestTypeOptions;

    // Interest Calculation Period Type Options
    Json::Value interestCalcPeriodOptions(Json::arrayValue);
    Json::Value calcDaily, calcSameAsRepay;
    calcDaily["id"] = 0;
    calcDaily["code"] = "interestCalculationPeriodType.daily";
    calcDaily["value"] = "Daily";
    calcSameAsRepay["id"] = 1;
    calcSameAsRepay["code"] = "interestCalculationPeriodType.same.as.repayment.period";
    calcSameAsRepay["value"] = "Same as repayment period";
    interestCalcPeriodOptions.append(calcDaily);
    interestCalcPeriodOptions.append(calcSameAsRepay);
    loanProductTemplate["interestCalculationPeriodTypeOptions"] = interestCalcPeriodOptions;

    // Transaction Processing Strategy Options
    Json::Value transactionStrategyOptions(Json::arrayValue);
    Json::Value strategy1, strategy2, strategy3, strategy4, strategy5, strategy6;
    strategy1["id"] = 1;
    strategy1["code"] = "mifos-standard-strategy";
    strategy1["name"] = "Penalties, Fees, Interest, Principal order";
    strategy2["id"] = 2;
    strategy2["code"] = "heavensfamily-strategy";
    strategy2["name"] = "HeavensFamily Unique";
    strategy3["id"] = 3;
    strategy3["code"] = "creocore-strategy";
    strategy3["name"] = "Creocore Unique";
    strategy4["id"] = 4;
    strategy4["code"] = "rbi-india-strategy";
    strategy4["name"] = "Overdue/Due Fee/Int,Principal";
    strategy5["id"] = 5;
    strategy5["code"] = "principal-interest-penalties-fees-order-strategy";
    strategy5["name"] = "Principal Interest Penalties Fees Order";
    strategy6["id"] = 6;
    strategy6["code"] = "interest-principal-penalties-fees-order-strategy";
    strategy6["name"] = "Interest Principal Penalties Fees Order";
    transactionStrategyOptions.append(strategy1);
    transactionStrategyOptions.append(strategy2);
    transactionStrategyOptions.append(strategy3);
    transactionStrategyOptions.append(strategy4);
    transactionStrategyOptions.append(strategy5);
    transactionStrategyOptions.append(strategy6);
    loanProductTemplate["transactionProcessingStrategyOptions"] = transactionStrategyOptions;

    // Charge Options (abbreviated for readability - showing pattern)
    Json::Value chargeOptions(Json::arrayValue);
    // Helper lambda to create currency for charges
    auto createUSDCurrency = []() {
        Json::Value curr;
        curr["code"] = "USD";
        curr["name"] = "US Dollar";
        curr["decimalPlaces"] = 2;
        curr["displaySymbol"] = "$";
        curr["nameCode"] = "currency.USD";
        curr["displayLabel"] = "US Dollar ($)";
        return curr;
    };

    // Charge 1: des charge
    Json::Value charge1;
    charge1["id"] = 5;
    charge1["name"] = "des charge";
    charge1["active"] = true;
    charge1["penalty"] = false;
    charge1["currency"] = createUSDCurrency();
    charge1["amount"] = 100.000000;
    Json::Value chargeTime1;
    chargeTime1["id"] = 1;
    chargeTime1["code"] = "chargeTimeType.disbursement";
    chargeTime1["value"] = "Disbursement";
    charge1["chargeTimeType"] = chargeTime1;
    Json::Value chargeApplies1;
    chargeApplies1["id"] = 1;
    chargeApplies1["code"] = "chargeAppliesTo.loan";
    chargeApplies1["value"] = "Loan";
    charge1["chargeAppliesTo"] = chargeApplies1;
    Json::Value chargeCalc1;
    chargeCalc1["id"] = 1;
    chargeCalc1["code"] = "chargeCalculationType.flat";
    chargeCalc1["value"] = "Flat";
    charge1["chargeCalculationType"] = chargeCalc1;
    Json::Value chargePayment1;
    chargePayment1["id"] = 0;
    chargePayment1["code"] = "chargepaymentmode.regular";
    chargePayment1["value"] = "Regular";
    charge1["chargePaymentMode"] = chargePayment1;
    chargeOptions.append(charge1);

    // Charge 2: flat install
    Json::Value charge2;
    charge2["id"] = 1;
    charge2["name"] = "flat install";
    charge2["active"] = true;
    charge2["penalty"] = false;
    charge2["currency"] = createUSDCurrency();
    charge2["amount"] = 50.000000;
    Json::Value chargeTime2;
    chargeTime2["id"] = 8;
    chargeTime2["code"] = "chargeTimeType.instalmentFee";
    chargeTime2["value"] = "Instalment Fee";
    charge2["chargeTimeType"] = chargeTime2;
    charge2["chargeAppliesTo"] = chargeApplies1;
    charge2["chargeCalculationType"] = chargeCalc1;
    charge2["chargePaymentMode"] = chargePayment1;
    chargeOptions.append(charge2);

    // Continue with remaining charges following the same pattern...
    // (I'll add a few more to demonstrate)

    Json::Value charge3;
    charge3["id"] = 9;
    charge3["name"] = "install amt+int";
    charge3["active"] = true;
    charge3["penalty"] = false;
    charge3["currency"] = createUSDCurrency();
    charge3["amount"] = 5.000000;
    charge3["chargeTimeType"] = chargeTime2;
    charge3["chargeAppliesTo"] = chargeApplies1;
    Json::Value chargeCalc3;
    chargeCalc3["id"] = 3;
    chargeCalc3["code"] = "chargeCalculationType.percent.of.amount.and.interest";
    chargeCalc3["value"] = "% Loan Amount + Interest";
    charge3["chargeCalculationType"] = chargeCalc3;
    charge3["chargePaymentMode"] = chargePayment1;
    chargeOptions.append(charge3);

    // Add remaining charges similarly...
    loanProductTemplate["chargeOptions"] = chargeOptions;

    // Accounting Rule Options
    Json::Value accountingRuleOptions(Json::arrayValue);
    Json::Value accRule1, accRule2, accRule3;
    accRule1["id"] = 1;
    accRule1["code"] = "accountingRuleType.none";
    accRule1["value"] = "NONE";
    accRule2["id"] = 2;
    accRule2["code"] = "accountingRuleType.cash";
    accRule2["value"] = "CASH BASED";
    accRule3["id"] = 3;
    accRule3["code"] = "accountingRuleType.accrual";
    accRule3["value"] = "ACCRUAL BASED";
    accountingRuleOptions.append(accRule1);
    accountingRuleOptions.append(accRule2);
    accountingRuleOptions.append(accRule3);
    loanProductTemplate["accountingRuleOptions"] = accountingRuleOptions;

    // Accounting Mapping Options
    Json::Value accountingMappingOptions;

    // Liability Account Options
    Json::Value liabilityAccountOptions(Json::arrayValue);
    Json::Value liability1;
    liability1["id"] = 11;
    liability1["name"] = "over payment";
    liability1["glCode"] = "13";
    liability1["disabled"] = false;
    liability1["manualEntriesAllowed"] = true;
    Json::Value liabType;
    liabType["id"] = 2;
    liabType["code"] = "accountType.liability";
    liabType["value"] = "LIABILITY";
    liability1["type"] = liabType;
    Json::Value usage;
    usage["id"] = 1;
    usage["code"] = "accountUsage.detail";
    usage["value"] = "DETAIL";
    liability1["usage"] = usage;
    liability1["nameDecorated"] = "over payment";
    Json::Value tagId;
    tagId["id"] = 0;
    liability1["tagId"] = tagId;
    liability1["organizationRunningBalance"] = 0;
    liabilityAccountOptions.append(liability1);
    accountingMappingOptions["liabilityAccountOptions"] = liabilityAccountOptions;

    // Asset Account Options
    Json::Value assetAccountOptions(Json::arrayValue);
    Json::Value asset1, asset2, asset3;
    asset1["id"] = 1;
    asset1["name"] = "fund source";
    asset1["glCode"] = "01";
    asset1["disabled"] = false;
    asset1["manualEntriesAllowed"] = true;
    Json::Value assetType;
    assetType["id"] = 1;
    assetType["code"] = "accountType.asset";
    assetType["value"] = "ASSET";
    asset1["type"] = assetType;
    asset1["usage"] = usage;
    asset1["nameDecorated"] = "fund source";
    asset1["tagId"] = tagId;
    asset1["organizationRunningBalance"] = -60000;

    asset2["id"] = 2;
    asset2["name"] = "Loan portfolio";
    asset2["glCode"] = "02";
    asset2["disabled"] = false;
    asset2["manualEntriesAllowed"] = true;
    asset2["type"] = assetType;
    asset2["usage"] = usage;
    asset2["nameDecorated"] = "Loan portfolio";
    asset2["tagId"] = tagId;
    asset2["organizationRunningBalance"] = 60000;

    asset3["id"] = 3;
    asset3["name"] = "transfers";
    asset3["glCode"] = "03";
    asset3["disabled"] = false;
    asset3["manualEntriesAllowed"] = true;
    asset3["type"] = assetType;
    asset3["usage"] = usage;
    asset3["nameDecorated"] = "transfers";
    asset3["tagId"] = tagId;
    asset3["organizationRunningBalance"] = 0;

    assetAccountOptions.append(asset1);
    assetAccountOptions.append(asset2);
    assetAccountOptions.append(asset3);
    accountingMappingOptions["assetAccountOptions"] = assetAccountOptions;

    // Expense Account Options
    Json::Value expenseAccountOptions(Json::arrayValue);
    Json::Value expense1;
    expense1["id"] = 10;
    expense1["name"] = "loans written off 2";
    expense1["glCode"] = "12";
    expense1["disabled"] = false;
    expense1["manualEntriesAllowed"] = true;
    Json::Value expenseType;
    expenseType["id"] = 5;
    expenseType["code"] = "accountType.expense";
    expenseType["value"] = "EXPENSE";
    expense1["type"] = expenseType;
    expense1["usage"] = usage;
    expense1["nameDecorated"] = "loans written off 2";
    expense1["tagId"] = tagId;
    expense1["organizationRunningBalance"] = 0;
    expenseAccountOptions.append(expense1);
    accountingMappingOptions["expenseAccountOptions"] = expenseAccountOptions;

    // Income Account Options
    Json::Value incomeAccountOptions(Json::arrayValue);
    Json::Value income1, income2, income3;
    Json::Value incomeType;
    incomeType["id"] = 4;
    incomeType["code"] = "accountType.income";
    incomeType["value"] = "INCOME";

    income1["id"] = 4;
    income1["name"] = "income from interest";
    income1["glCode"] = "04";
    income1["disabled"] = false;
    income1["manualEntriesAllowed"] = true;
    income1["type"] = incomeType;
    income1["usage"] = usage;
    income1["nameDecorated"] = "income from interest";
    income1["tagId"] = tagId;
    income1["organizationRunningBalance"] = 19;

    income2["id"] = 8;
    income2["name"] = "income from fees 2";
    income2["glCode"] = "10";
    income2["disabled"] = false;
    income2["manualEntriesAllowed"] = true;
    income2["type"] = incomeType;
    income2["usage"] = usage;
    income2["nameDecorated"] = "income from fees 2";
    income2["tagId"] = tagId;
    income2["organizationRunningBalance"] = 0;

    income3["id"] = 9;
    income3["name"] = "income from penalities 2";
    income3["glCode"] = "11";
    income3["disabled"] = false;
    income3["manualEntriesAllowed"] = true;
    income3["type"] = incomeType;
    income3["usage"] = usage;
    income3["nameDecorated"] = "income from penalities 2";
    income3["tagId"] = tagId;
    income3["organizationRunningBalance"] = 0;

    incomeAccountOptions.append(income1);
    incomeAccountOptions.append(income2);
    incomeAccountOptions.append(income3);
    accountingMappingOptions["incomeAccountOptions"] = incomeAccountOptions;

    loanProductTemplate["accountingMappingOptions"] = accountingMappingOptions;

    // Value Condition Type Options
    Json::Value valueConditionTypeOptions(Json::arrayValue);
    Json::Value valCond1, valCond2;
    valCond1["id"] = 2;
    valCond1["code"] = "LoanProductValueConditionType.equal";
    valCond1["value"] = "equals";
    valCond2["id"] = 3;
    valCond2["code"] = "LoanProductValueConditionType.greterthan";
    valCond2["value"] = "greter than";
    valueConditionTypeOptions.append(valCond1);
    valueConditionTypeOptions.append(valCond2);
    loanProductTemplate["valueConditionTypeOptions"] = valueConditionTypeOptions;

    // Days In Month Type Options
    Json::Value daysInMonthTypeOptions(Json::arrayValue);
    Json::Value dayMonth1, dayMonth2;
    dayMonth1["id"] = 1;
    dayMonth1["code"] = "DaysInMonthType.actual";
    dayMonth1["value"] = "Actual";
    dayMonth2["id"] = 30;
    dayMonth2["code"] = "DaysInMonthType.days360";
    dayMonth2["value"] = "30 Days";
    daysInMonthTypeOptions.append(dayMonth1);
    daysInMonthTypeOptions.append(dayMonth2);
    loanProductTemplate["daysInMonthTypeOptions"] = daysInMonthTypeOptions;

    // Days In Year Type Options
    Json::Value daysInYearTypeOptions(Json::arrayValue);
    Json::Value dayYear1, dayYear2, dayYear3, dayYear4;
    dayYear1["id"] = 1;
    dayYear1["code"] = "DaysInYearType.actual";
    dayYear1["value"] = "Actual";
    dayYear2["id"] = 360;
    dayYear2["code"] = "DaysInYearType.days360";
    dayYear2["value"] = "360 Days";
    dayYear3["id"] = 364;
    dayYear3["code"] = "DaysInYearType.days364";
    dayYear3["value"] = "364 Days";
    dayYear4["id"] = 365;
    dayYear4["code"] = "DaysInYearType.days365";
    dayYear4["value"] = "365 Days";
    daysInYearTypeOptions.append(dayYear1);
    daysInYearTypeOptions.append(dayYear2);
    daysInYearTypeOptions.append(dayYear3);
    daysInYearTypeOptions.append(dayYear4);
    loanProductTemplate["daysInYearTypeOptions"] = daysInYearTypeOptions;

    // Interest Recalculation Compounding Type Options
    Json::Value intRecalcCompoundingOptions(Json::arrayValue);
    Json::Value compound1, compound2, compound3, compound4;
    compound1["id"] = 0;
    compound1["code"] = "interestRecalculationCompoundingMethod.none";
    compound1["value"] = "None";
    compound2["id"] = 2;
    compound2["code"] = "interestRecalculationCompoundingMethod.fee";
    compound2["value"] = "Fee";
    compound3["id"] = 1;
    compound3["code"] = "interestRecalculationCompoundingMethod.interest";
    compound3["value"] = "Interest";
    compound4["id"] = 3;
    compound4["code"] = "interestRecalculationCompoundingMethod.interest.and.fee";
    compound4["value"] = "Fee and Interest";
    intRecalcCompoundingOptions.append(compound1);
    intRecalcCompoundingOptions.append(compound2);
    intRecalcCompoundingOptions.append(compound3);
    intRecalcCompoundingOptions.append(compound4);
    loanProductTemplate["interestRecalculationCompoundingTypeOptions"] = intRecalcCompoundingOptions;

    // Reschedule Strategy Type Options
    Json::Value rescheduleStrategyOptions(Json::arrayValue);
    Json::Value reschedule1, reschedule2, reschedule3;
    reschedule1["id"] = 3;
    reschedule1["code"] = "loanRescheduleStrategyMethod.reduce.emi.amount";
    reschedule1["value"] = "Reduce EMI amount";
    reschedule2["id"] = 2;
    reschedule2["code"] = "loanRescheduleStrategyMethod.reduce.number.of.installments";
    reschedule2["value"] = "Reduce number of installments";
    reschedule3["id"] = 1;
    reschedule3["code"] = "loanRescheduleStrategyMethod.reschedule.next.repayments";
    reschedule3["value"] = "Reschedule next repayments";
    rescheduleStrategyOptions.append(reschedule1);
    rescheduleStrategyOptions.append(reschedule2);
    rescheduleStrategyOptions.append(reschedule3);
    loanProductTemplate["rescheduleStrategyTypeOptions"] = rescheduleStrategyOptions;

    // Interest Recalculation Frequency Type Options
    Json::Value intRecalcFreqOptions(Json::arrayValue);
    Json::Value freq1, freq2, freq3, freq4;
    freq1["id"] = 1;
    freq1["code"] = "interestRecalculationFrequencyType.same.as.repayment.period";
    freq1["value"] = "Same as repayment period";
    freq2["id"] = 2;
    freq2["code"] = "interestRecalculationFrequencyType.daily";
    freq2["value"] = "Daily";
    freq3["id"] = 3;
    freq3["code"] = "interestRecalculationFrequencyType.weekly";
    freq3["value"] = "Weekly";
    freq4["id"] = 4;
    freq4["code"] = "interestRecalculationFrequencyType.monthly";
    freq4["value"] = "Monthly";
    intRecalcFreqOptions.append(freq1);
    intRecalcFreqOptions.append(freq2);
    intRecalcFreqOptions.append(freq3);
    intRecalcFreqOptions.append(freq4);
    loanProductTemplate["interestRecalculationFrequencyTypeOptions"] = intRecalcFreqOptions;

    response.result = loanProductTemplate;
    response.message = "Loan Product Template retrieved successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);
}


void LoanProductsController::getLoanProductTemplate(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    turbo_ledger_portfolio::dto::BaseApiResponse response;
    response.success = true;

    Json::Value loanProductTemplate;

    // Basic properties
    loanProductTemplate["includeInBorrowerCycle"] = false;
    loanProductTemplate["useBorrowerCycle"] = false;

    // Currency
    Json::Value currency;
    currency["code"] = "";
    currency["name"] = "";
    currency["decimalPlaces"] = 0;
    currency["inMultiplesOf"] = 0;
    currency["displaySymbol"] = "";
    currency["nameCode"] = "";
    currency["displayLabel"] = " []";
    loanProductTemplate["currency"] = currency;

    // Repayment Frequency Type
    Json::Value repaymentFrequencyType;
    repaymentFrequencyType["id"] = 2;
    repaymentFrequencyType["code"] = "repaymentFrequency.periodFrequencyType.months";
    repaymentFrequencyType["value"] = "Months";
    loanProductTemplate["repaymentFrequencyType"] = repaymentFrequencyType;

    // Interest Rate Frequency Type
    Json::Value interestRateFrequencyType;
    interestRateFrequencyType["id"] = 2;
    interestRateFrequencyType["code"] = "interestRateFrequency.periodFrequencyType.months";
    interestRateFrequencyType["value"] = "Per month";
    loanProductTemplate["interestRateFrequencyType"] = interestRateFrequencyType;

    // Amortization Type
    Json::Value amortizationType;
    amortizationType["id"] = 1;
    amortizationType["code"] = "amortizationType.equal.installments";
    amortizationType["value"] = "Equal installments";
    loanProductTemplate["amortizationType"] = amortizationType;

    // Interest Type
    Json::Value interestType;
    interestType["id"] = 0;
    interestType["code"] = "interestType.declining.balance";
    interestType["value"] = "Declining Balance";
    loanProductTemplate["interestType"] = interestType;

    // Interest Calculation Period Type
    Json::Value interestCalculationPeriodType;
    interestCalculationPeriodType["id"] = 1;
    interestCalculationPeriodType["code"] = "interestCalculationPeriodType.same.as.repayment.period";
    interestCalculationPeriodType["value"] = "Same as repayment period";
    loanProductTemplate["interestCalculationPeriodType"] = interestCalculationPeriodType;

    // Borrower Cycle Variations
    loanProductTemplate["principalVariationsForBorrowerCycle"] = Json::Value(Json::arrayValue);
    loanProductTemplate["interestRateVariationsForBorrowerCycle"] = Json::Value(Json::arrayValue);
    loanProductTemplate["numberOfRepaymentVariationsForBorrowerCycle"] = Json::Value(Json::arrayValue);

    // Accounting Rule
    Json::Value accountingRule;
    accountingRule["id"] = 1;
    accountingRule["code"] = "accountingRuleType.none";
    accountingRule["value"] = "NONE";
    loanProductTemplate["accountingRule"] = accountingRule;

    // Days In Month Type
    Json::Value daysInMonthType;
    daysInMonthType["id"] = 1;
    daysInMonthType["code"] = "DaysInMonthType.actual";
    daysInMonthType["value"] = "Actual";
    loanProductTemplate["daysInMonthType"] = daysInMonthType;

    // Days In Year Type
    Json::Value daysInYearType;
    daysInYearType["id"] = 1;
    daysInYearType["code"] = "DaysInYearType.actual";
    daysInYearType["value"] = "Actual";
    loanProductTemplate["daysInYearType"] = daysInYearType;

    // Interest Recalculation
    loanProductTemplate["isInterestRecalculationEnabled"] = false;
    Json::Value interestRecalculationData;
    Json::Value compoundingType;
    compoundingType["id"] = 0;
    compoundingType["code"] = "interestRecalculationCompoundingMethod.none";
    compoundingType["value"] = "None";
    interestRecalculationData["interestRecalculationCompoundingType"] = compoundingType;

    Json::Value rescheduleStrategyType;
    rescheduleStrategyType["id"] = 3;
    rescheduleStrategyType["code"] = "loanRescheduleStrategyMethod.reduce.emi.amount";
    rescheduleStrategyType["value"] = "Reduce EMI amount";
    interestRecalculationData["rescheduleStrategyType"] = rescheduleStrategyType;

    Json::Value preClosureStrategy;
    preClosureStrategy["id"] = 1;
    preClosureStrategy["code"] = "loanPreClosureInterestCalculationStrategy.tillPreClosureDate";
    preClosureStrategy["value"] = "Till preclose Date";
    interestRecalculationData["preClosureInterestCalculationStrategy"] = preClosureStrategy;
    loanProductTemplate["interestRecalculationData"] = interestRecalculationData;

    // Payment Type Options
    Json::Value paymentTypeOptions(Json::arrayValue);
    Json::Value paymentType;
    paymentType["id"] = 10;
    paymentType["name"] = "check";
    paymentType["position"] = 1;
    paymentTypeOptions.append(paymentType);
    loanProductTemplate["paymentTypeOptions"] = paymentTypeOptions;

    // Currency Options
    Json::Value currencyOptions(Json::arrayValue);
    Json::Value usdCurrency;
    usdCurrency["code"] = "USD";
    usdCurrency["name"] = "US Dollar";
    usdCurrency["decimalPlaces"] = 2;
    usdCurrency["displaySymbol"] = "$";
    usdCurrency["nameCode"] = "currency.USD";
    usdCurrency["displayLabel"] = "US Dollar ($)";
    currencyOptions.append(usdCurrency);
    loanProductTemplate["currencyOptions"] = currencyOptions;

    // Repayment Frequency Type Options
    Json::Value repaymentFrequencyTypeOptions(Json::arrayValue);
    Json::Value repayDays, repayWeeks, repayMonths;
    repayDays["id"] = 0;
    repayDays["code"] = "repaymentFrequency.periodFrequencyType.days";
    repayDays["value"] = "Days";
    repayWeeks["id"] = 1;
    repayWeeks["code"] = "repaymentFrequency.periodFrequencyType.weeks";
    repayWeeks["value"] = "Weeks";
    repayMonths["id"] = 2;
    repayMonths["code"] = "repaymentFrequency.periodFrequencyType.months";
    repayMonths["value"] = "Months";
    repaymentFrequencyTypeOptions.append(repayDays);
    repaymentFrequencyTypeOptions.append(repayWeeks);
    repaymentFrequencyTypeOptions.append(repayMonths);
    loanProductTemplate["repaymentFrequencyTypeOptions"] = repaymentFrequencyTypeOptions;

    // Pre Closure Interest Calculation Strategy Options
    Json::Value preClosureOptions(Json::arrayValue);
    Json::Value preClose1, preClose2;
    preClose1["id"] = 1;
    preClose1["code"] = "loanPreClosureInterestCalculationStrategy.tillPreClosureDate";
    preClose1["value"] = "Till preclose Date";
    preClose2["id"] = 2;
    preClose2["code"] = "loanPreClosureInterestCalculationStrategy.tillRestFrequencyDate";
    preClose2["value"] = "Till rest Frequency Date";
    preClosureOptions.append(preClose1);
    preClosureOptions.append(preClose2);
    loanProductTemplate["preClosureInterestCalculationStrategyOptions"] = preClosureOptions;

    // Interest Rate Frequency Type Options
    Json::Value interestRateFrequencyTypeOptions(Json::arrayValue);
    Json::Value intRateMonths, intRateYears;
    intRateMonths["id"] = 2;
    intRateMonths["code"] = "interestRateFrequency.periodFrequencyType.months";
    intRateMonths["value"] = "Per month";
    intRateYears["id"] = 3;
    intRateYears["code"] = "interestRateFrequency.periodFrequencyType.years";
    intRateYears["value"] = "Per year";
    interestRateFrequencyTypeOptions.append(intRateMonths);
    interestRateFrequencyTypeOptions.append(intRateYears);
    loanProductTemplate["interestRateFrequencyTypeOptions"] = interestRateFrequencyTypeOptions;

    // Amortization Type Options
    Json::Value amortizationTypeOptions(Json::arrayValue);
    Json::Value amortEqual, amortPrincipal;
    amortEqual["id"] = 1;
    amortEqual["code"] = "amortizationType.equal.installments";
    amortEqual["value"] = "Equal installments";
    amortPrincipal["id"] = 0;
    amortPrincipal["code"] = "amortizationType.equal.principal";
    amortPrincipal["value"] = "Equal principal payments";
    amortizationTypeOptions.append(amortEqual);
    amortizationTypeOptions.append(amortPrincipal);
    loanProductTemplate["amortizationTypeOptions"] = amortizationTypeOptions;

    // Interest Type Options
    Json::Value interestTypeOptions(Json::arrayValue);
    Json::Value intFlat, intDeclining;
    intFlat["id"] = 1;
    intFlat["code"] = "interestType.flat";
    intFlat["value"] = "Flat";
    intDeclining["id"] = 0;
    intDeclining["code"] = "interestType.declining.balance";
    intDeclining["value"] = "Declining Balance";
    interestTypeOptions.append(intFlat);
    interestTypeOptions.append(intDeclining);
    loanProductTemplate["interestTypeOptions"] = interestTypeOptions;

    // Interest Calculation Period Type Options
    Json::Value interestCalcPeriodOptions(Json::arrayValue);
    Json::Value calcDaily, calcSameAsRepay;
    calcDaily["id"] = 0;
    calcDaily["code"] = "interestCalculationPeriodType.daily";
    calcDaily["value"] = "Daily";
    calcSameAsRepay["id"] = 1;
    calcSameAsRepay["code"] = "interestCalculationPeriodType.same.as.repayment.period";
    calcSameAsRepay["value"] = "Same as repayment period";
    interestCalcPeriodOptions.append(calcDaily);
    interestCalcPeriodOptions.append(calcSameAsRepay);
    loanProductTemplate["interestCalculationPeriodTypeOptions"] = interestCalcPeriodOptions;

    // Transaction Processing Strategy Options
    Json::Value transactionStrategyOptions(Json::arrayValue);
    Json::Value strategy1, strategy2, strategy3, strategy4, strategy5, strategy6;
    strategy1["id"] = 1;
    strategy1["code"] = "mifos-standard-strategy";
    strategy1["name"] = "Penalties, Fees, Interest, Principal order";
    strategy2["id"] = 2;
    strategy2["code"] = "heavensfamily-strategy";
    strategy2["name"] = "HeavensFamily Unique";
    strategy3["id"] = 3;
    strategy3["code"] = "creocore-strategy";
    strategy3["name"] = "Creocore Unique";
    strategy4["id"] = 4;
    strategy4["code"] = "rbi-india-strategy";
    strategy4["name"] = "Overdue/Due Fee/Int,Principal";
    strategy5["id"] = 5;
    strategy5["code"] = "principal-interest-penalties-fees-order-strategy";
    strategy5["name"] = "Principal Interest Penalties Fees Order";
    strategy6["id"] = 6;
    strategy6["code"] = "interest-principal-penalties-fees-order-strategy";
    strategy6["name"] = "Interest Principal Penalties Fees Order";
    transactionStrategyOptions.append(strategy1);
    transactionStrategyOptions.append(strategy2);
    transactionStrategyOptions.append(strategy3);
    transactionStrategyOptions.append(strategy4);
    transactionStrategyOptions.append(strategy5);
    transactionStrategyOptions.append(strategy6);
    loanProductTemplate["transactionProcessingStrategyOptions"] = transactionStrategyOptions;

    // Charge Options (abbreviated for readability - showing pattern)
    Json::Value chargeOptions(Json::arrayValue);
    // Helper lambda to create currency for charges
    auto createUSDCurrency = []() {
        Json::Value curr;
        curr["code"] = "USD";
        curr["name"] = "US Dollar";
        curr["decimalPlaces"] = 2;
        curr["displaySymbol"] = "$";
        curr["nameCode"] = "currency.USD";
        curr["displayLabel"] = "US Dollar ($)";
        return curr;
    };

    // Charge 1: des charge
    Json::Value charge1;
    charge1["id"] = 5;
    charge1["name"] = "des charge";
    charge1["active"] = true;
    charge1["penalty"] = false;
    charge1["currency"] = createUSDCurrency();
    charge1["amount"] = 100.000000;
    Json::Value chargeTime1;
    chargeTime1["id"] = 1;
    chargeTime1["code"] = "chargeTimeType.disbursement";
    chargeTime1["value"] = "Disbursement";
    charge1["chargeTimeType"] = chargeTime1;
    Json::Value chargeApplies1;
    chargeApplies1["id"] = 1;
    chargeApplies1["code"] = "chargeAppliesTo.loan";
    chargeApplies1["value"] = "Loan";
    charge1["chargeAppliesTo"] = chargeApplies1;
    Json::Value chargeCalc1;
    chargeCalc1["id"] = 1;
    chargeCalc1["code"] = "chargeCalculationType.flat";
    chargeCalc1["value"] = "Flat";
    charge1["chargeCalculationType"] = chargeCalc1;
    Json::Value chargePayment1;
    chargePayment1["id"] = 0;
    chargePayment1["code"] = "chargepaymentmode.regular";
    chargePayment1["value"] = "Regular";
    charge1["chargePaymentMode"] = chargePayment1;
    chargeOptions.append(charge1);

    // Charge 2: flat install
    Json::Value charge2;
    charge2["id"] = 1;
    charge2["name"] = "flat install";
    charge2["active"] = true;
    charge2["penalty"] = false;
    charge2["currency"] = createUSDCurrency();
    charge2["amount"] = 50.000000;
    Json::Value chargeTime2;
    chargeTime2["id"] = 8;
    chargeTime2["code"] = "chargeTimeType.instalmentFee";
    chargeTime2["value"] = "Instalment Fee";
    charge2["chargeTimeType"] = chargeTime2;
    charge2["chargeAppliesTo"] = chargeApplies1;
    charge2["chargeCalculationType"] = chargeCalc1;
    charge2["chargePaymentMode"] = chargePayment1;
    chargeOptions.append(charge2);

    // Continue with remaining charges following the same pattern...
    // (I'll add a few more to demonstrate)

    Json::Value charge3;
    charge3["id"] = 9;
    charge3["name"] = "install amt+int";
    charge3["active"] = true;
    charge3["penalty"] = false;
    charge3["currency"] = createUSDCurrency();
    charge3["amount"] = 5.000000;
    charge3["chargeTimeType"] = chargeTime2;
    charge3["chargeAppliesTo"] = chargeApplies1;
    Json::Value chargeCalc3;
    chargeCalc3["id"] = 3;
    chargeCalc3["code"] = "chargeCalculationType.percent.of.amount.and.interest";
    chargeCalc3["value"] = "% Loan Amount + Interest";
    charge3["chargeCalculationType"] = chargeCalc3;
    charge3["chargePaymentMode"] = chargePayment1;
    chargeOptions.append(charge3);

    // Add remaining charges similarly...
    loanProductTemplate["chargeOptions"] = chargeOptions;

    // Accounting Rule Options
    Json::Value accountingRuleOptions(Json::arrayValue);
    Json::Value accRule1, accRule2, accRule3;
    accRule1["id"] = 1;
    accRule1["code"] = "accountingRuleType.none";
    accRule1["value"] = "NONE";
    accRule2["id"] = 2;
    accRule2["code"] = "accountingRuleType.cash";
    accRule2["value"] = "CASH BASED";
    accRule3["id"] = 3;
    accRule3["code"] = "accountingRuleType.accrual";
    accRule3["value"] = "ACCRUAL BASED";
    accountingRuleOptions.append(accRule1);
    accountingRuleOptions.append(accRule2);
    accountingRuleOptions.append(accRule3);
    loanProductTemplate["accountingRuleOptions"] = accountingRuleOptions;

    // Accounting Mapping Options
    Json::Value accountingMappingOptions;

    // Liability Account Options
    Json::Value liabilityAccountOptions(Json::arrayValue);
    Json::Value liability1;
    liability1["id"] = 11;
    liability1["name"] = "over payment";
    liability1["glCode"] = "13";
    liability1["disabled"] = false;
    liability1["manualEntriesAllowed"] = true;
    Json::Value liabType;
    liabType["id"] = 2;
    liabType["code"] = "accountType.liability";
    liabType["value"] = "LIABILITY";
    liability1["type"] = liabType;
    Json::Value usage;
    usage["id"] = 1;
    usage["code"] = "accountUsage.detail";
    usage["value"] = "DETAIL";
    liability1["usage"] = usage;
    liability1["nameDecorated"] = "over payment";
    Json::Value tagId;
    tagId["id"] = 0;
    liability1["tagId"] = tagId;
    liability1["organizationRunningBalance"] = 0;
    liabilityAccountOptions.append(liability1);
    accountingMappingOptions["liabilityAccountOptions"] = liabilityAccountOptions;

    // Asset Account Options
    Json::Value assetAccountOptions(Json::arrayValue);
    Json::Value asset1, asset2, asset3;
    asset1["id"] = 1;
    asset1["name"] = "fund source";
    asset1["glCode"] = "01";
    asset1["disabled"] = false;
    asset1["manualEntriesAllowed"] = true;
    Json::Value assetType;
    assetType["id"] = 1;
    assetType["code"] = "accountType.asset";
    assetType["value"] = "ASSET";
    asset1["type"] = assetType;
    asset1["usage"] = usage;
    asset1["nameDecorated"] = "fund source";
    asset1["tagId"] = tagId;
    asset1["organizationRunningBalance"] = -60000;

    asset2["id"] = 2;
    asset2["name"] = "Loan portfolio";
    asset2["glCode"] = "02";
    asset2["disabled"] = false;
    asset2["manualEntriesAllowed"] = true;
    asset2["type"] = assetType;
    asset2["usage"] = usage;
    asset2["nameDecorated"] = "Loan portfolio";
    asset2["tagId"] = tagId;
    asset2["organizationRunningBalance"] = 60000;

    asset3["id"] = 3;
    asset3["name"] = "transfers";
    asset3["glCode"] = "03";
    asset3["disabled"] = false;
    asset3["manualEntriesAllowed"] = true;
    asset3["type"] = assetType;
    asset3["usage"] = usage;
    asset3["nameDecorated"] = "transfers";
    asset3["tagId"] = tagId;
    asset3["organizationRunningBalance"] = 0;

    assetAccountOptions.append(asset1);
    assetAccountOptions.append(asset2);
    assetAccountOptions.append(asset3);
    accountingMappingOptions["assetAccountOptions"] = assetAccountOptions;

    // Expense Account Options
    Json::Value expenseAccountOptions(Json::arrayValue);
    Json::Value expense1;
    expense1["id"] = 10;
    expense1["name"] = "loans written off 2";
    expense1["glCode"] = "12";
    expense1["disabled"] = false;
    expense1["manualEntriesAllowed"] = true;
    Json::Value expenseType;
    expenseType["id"] = 5;
    expenseType["code"] = "accountType.expense";
    expenseType["value"] = "EXPENSE";
    expense1["type"] = expenseType;
    expense1["usage"] = usage;
    expense1["nameDecorated"] = "loans written off 2";
    expense1["tagId"] = tagId;
    expense1["organizationRunningBalance"] = 0;
    expenseAccountOptions.append(expense1);
    accountingMappingOptions["expenseAccountOptions"] = expenseAccountOptions;

    // Income Account Options
    Json::Value incomeAccountOptions(Json::arrayValue);
    Json::Value income1, income2, income3;
    Json::Value incomeType;
    incomeType["id"] = 4;
    incomeType["code"] = "accountType.income";
    incomeType["value"] = "INCOME";

    income1["id"] = 4;
    income1["name"] = "income from interest";
    income1["glCode"] = "04";
    income1["disabled"] = false;
    income1["manualEntriesAllowed"] = true;
    income1["type"] = incomeType;
    income1["usage"] = usage;
    income1["nameDecorated"] = "income from interest";
    income1["tagId"] = tagId;
    income1["organizationRunningBalance"] = 19;

    income2["id"] = 8;
    income2["name"] = "income from fees 2";
    income2["glCode"] = "10";
    income2["disabled"] = false;
    income2["manualEntriesAllowed"] = true;
    income2["type"] = incomeType;
    income2["usage"] = usage;
    income2["nameDecorated"] = "income from fees 2";
    income2["tagId"] = tagId;
    income2["organizationRunningBalance"] = 0;

    income3["id"] = 9;
    income3["name"] = "income from penalities 2";
    income3["glCode"] = "11";
    income3["disabled"] = false;
    income3["manualEntriesAllowed"] = true;
    income3["type"] = incomeType;
    income3["usage"] = usage;
    income3["nameDecorated"] = "income from penalities 2";
    income3["tagId"] = tagId;
    income3["organizationRunningBalance"] = 0;

    incomeAccountOptions.append(income1);
    incomeAccountOptions.append(income2);
    incomeAccountOptions.append(income3);
    accountingMappingOptions["incomeAccountOptions"] = incomeAccountOptions;

    loanProductTemplate["accountingMappingOptions"] = accountingMappingOptions;

    // Value Condition Type Options
    Json::Value valueConditionTypeOptions(Json::arrayValue);
    Json::Value valCond1, valCond2;
    valCond1["id"] = 2;
    valCond1["code"] = "LoanProductValueConditionType.equal";
    valCond1["value"] = "equals";
    valCond2["id"] = 3;
    valCond2["code"] = "LoanProductValueConditionType.greterthan";
    valCond2["value"] = "greter than";
    valueConditionTypeOptions.append(valCond1);
    valueConditionTypeOptions.append(valCond2);
    loanProductTemplate["valueConditionTypeOptions"] = valueConditionTypeOptions;

    // Days In Month Type Options
    Json::Value daysInMonthTypeOptions(Json::arrayValue);
    Json::Value dayMonth1, dayMonth2;
    dayMonth1["id"] = 1;
    dayMonth1["code"] = "DaysInMonthType.actual";
    dayMonth1["value"] = "Actual";
    dayMonth2["id"] = 30;
    dayMonth2["code"] = "DaysInMonthType.days360";
    dayMonth2["value"] = "30 Days";
    daysInMonthTypeOptions.append(dayMonth1);
    daysInMonthTypeOptions.append(dayMonth2);
    loanProductTemplate["daysInMonthTypeOptions"] = daysInMonthTypeOptions;

    // Days In Year Type Options
    Json::Value daysInYearTypeOptions(Json::arrayValue);
    Json::Value dayYear1, dayYear2, dayYear3, dayYear4;
    dayYear1["id"] = 1;
    dayYear1["code"] = "DaysInYearType.actual";
    dayYear1["value"] = "Actual";
    dayYear2["id"] = 360;
    dayYear2["code"] = "DaysInYearType.days360";
    dayYear2["value"] = "360 Days";
    dayYear3["id"] = 364;
    dayYear3["code"] = "DaysInYearType.days364";
    dayYear3["value"] = "364 Days";
    dayYear4["id"] = 365;
    dayYear4["code"] = "DaysInYearType.days365";
    dayYear4["value"] = "365 Days";
    daysInYearTypeOptions.append(dayYear1);
    daysInYearTypeOptions.append(dayYear2);
    daysInYearTypeOptions.append(dayYear3);
    daysInYearTypeOptions.append(dayYear4);
    loanProductTemplate["daysInYearTypeOptions"] = daysInYearTypeOptions;

    // Interest Recalculation Compounding Type Options
    Json::Value intRecalcCompoundingOptions(Json::arrayValue);
    Json::Value compound1, compound2, compound3, compound4;
    compound1["id"] = 0;
    compound1["code"] = "interestRecalculationCompoundingMethod.none";
    compound1["value"] = "None";
    compound2["id"] = 2;
    compound2["code"] = "interestRecalculationCompoundingMethod.fee";
    compound2["value"] = "Fee";
    compound3["id"] = 1;
    compound3["code"] = "interestRecalculationCompoundingMethod.interest";
    compound3["value"] = "Interest";
    compound4["id"] = 3;
    compound4["code"] = "interestRecalculationCompoundingMethod.interest.and.fee";
    compound4["value"] = "Fee and Interest";
    intRecalcCompoundingOptions.append(compound1);
    intRecalcCompoundingOptions.append(compound2);
    intRecalcCompoundingOptions.append(compound3);
    intRecalcCompoundingOptions.append(compound4);
    loanProductTemplate["interestRecalculationCompoundingTypeOptions"] = intRecalcCompoundingOptions;

    // Reschedule Strategy Type Options
    Json::Value rescheduleStrategyOptions(Json::arrayValue);
    Json::Value reschedule1, reschedule2, reschedule3;
    reschedule1["id"] = 3;
    reschedule1["code"] = "loanRescheduleStrategyMethod.reduce.emi.amount";
    reschedule1["value"] = "Reduce EMI amount";
    reschedule2["id"] = 2;
    reschedule2["code"] = "loanRescheduleStrategyMethod.reduce.number.of.installments";
    reschedule2["value"] = "Reduce number of installments";
    reschedule3["id"] = 1;
    reschedule3["code"] = "loanRescheduleStrategyMethod.reschedule.next.repayments";
    reschedule3["value"] = "Reschedule next repayments";
    rescheduleStrategyOptions.append(reschedule1);
    rescheduleStrategyOptions.append(reschedule2);
    rescheduleStrategyOptions.append(reschedule3);
    loanProductTemplate["rescheduleStrategyTypeOptions"] = rescheduleStrategyOptions;

    // Interest Recalculation Frequency Type Options
    Json::Value intRecalcFreqOptions(Json::arrayValue);
    Json::Value freq1, freq2, freq3, freq4;
    freq1["id"] = 1;
    freq1["code"] = "interestRecalculationFrequencyType.same.as.repayment.period";
    freq1["value"] = "Same as repayment period";
    freq2["id"] = 2;
    freq2["code"] = "interestRecalculationFrequencyType.daily";
    freq2["value"] = "Daily";
    freq3["id"] = 3;
    freq3["code"] = "interestRecalculationFrequencyType.weekly";
    freq3["value"] = "Weekly";
    freq4["id"] = 4;
    freq4["code"] = "interestRecalculationFrequencyType.monthly";
    freq4["value"] = "Monthly";
    intRecalcFreqOptions.append(freq1);
    intRecalcFreqOptions.append(freq2);
    intRecalcFreqOptions.append(freq3);
    intRecalcFreqOptions.append(freq4);
    loanProductTemplate["interestRecalculationFrequencyTypeOptions"] = intRecalcFreqOptions;

    response.result = loanProductTemplate;
    response.message = "Loan Product Template retrieved successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);
}


void LoanProductsController::createLoanProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

    turbo_ledger_portfolio::dto::BaseApiResponse response;
    response.success = true;

    Json::Value result;
    result["resourceId"] = 3;

    response.result = result;
    response.message = "Loan Product created successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);
}


void LoanProductsController::updateLoanProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string loanProductId) {

    turbo_ledger_portfolio::dto::BaseApiResponse response;
    response.success = true;

    Json::Value result;
    result["resourceId"] = loanProductId;

    Json::Value changes;
    changes["name"] = "Name is updated";

    result["changes"] = changes;

    response.result = result;
    response.message = "Loan Product updated successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);
}