//
// Created by Emmanuel Addo-Odame on 07/04/2026.
//

#ifndef ORGANIZATION_LOANPRODUCTDTO_H
#define ORGANIZATION_LOANPRODUCTDTO_H

#include <json/json.h>
#include <string>
#include <vector>

namespace organization::dto {

    struct RepaymentVariationDto {
        int valueConditionType{0};
        std::string borrowerCycleNumber;
        std::string minValue;
        std::string defaultValue;
        std::string maxValue;

        void fromJson(const Json::Value& json) {
            if (json.isMember("valueConditionType") && !json["valueConditionType"].isNull())
                valueConditionType = json["valueConditionType"].asInt();
            if (json.isMember("borrowerCycleNumber") && !json["borrowerCycleNumber"].isNull())
                borrowerCycleNumber = json["borrowerCycleNumber"].asString();
            if (json.isMember("minValue") && !json["minValue"].isNull())
                minValue = json["minValue"].asString();
            if (json.isMember("defaultValue") && !json["defaultValue"].isNull())
                defaultValue = json["defaultValue"].asString();
            if (json.isMember("maxValue") && !json["maxValue"].isNull())
                maxValue = json["maxValue"].asString();
        }
    };

    struct AttributeOverridesDto {
        bool amortizationType{false};
        bool interestType{false};
        bool transactionProcessingStrategyId{false};
        bool interestCalculationPeriodType{false};
        bool inArrearsTolerance{false};
        bool repaymentEvery{false};
        bool graceOnPrincipalAndInterestPayment{false};
        bool graceOnArrearsAgeing{false};

        void fromJson(const Json::Value& json) {
            if (json.isMember("amortizationType") && !json["amortizationType"].isNull())
                amortizationType = json["amortizationType"].asBool();
            if (json.isMember("interestType") && !json["interestType"].isNull())
                interestType = json["interestType"].asBool();
            if (json.isMember("transactionProcessingStrategyId") && !json["transactionProcessingStrategyId"].isNull())
                transactionProcessingStrategyId = json["transactionProcessingStrategyId"].asBool();
            if (json.isMember("interestCalculationPeriodType") && !json["interestCalculationPeriodType"].isNull())
                interestCalculationPeriodType = json["interestCalculationPeriodType"].asBool();
            if (json.isMember("inArrearsTolerance") && !json["inArrearsTolerance"].isNull())
                inArrearsTolerance = json["inArrearsTolerance"].asBool();
            if (json.isMember("repaymentEvery") && !json["repaymentEvery"].isNull())
                repaymentEvery = json["repaymentEvery"].asBool();
            if (json.isMember("graceOnPrincipalAndInterestPayment") && !json["graceOnPrincipalAndInterestPayment"].isNull())
                graceOnPrincipalAndInterestPayment = json["graceOnPrincipalAndInterestPayment"].asBool();
            if (json.isMember("graceOnArrearsAgeing") && !json["graceOnArrearsAgeing"].isNull())
                graceOnArrearsAgeing = json["graceOnArrearsAgeing"].asBool();
        }
    };

    class LoanProductDto {

    public:
        LoanProductDto() = default;

        void fromJson(const Json::Value& json);

        // Getters
        [[nodiscard]] const std::string& getCurrencyCode() const { return currencyCode; }
        [[nodiscard]] const std::string& getIncludeInBorrowerCycle() const { return includeInBorrowerCycle; }
        [[nodiscard]] bool isUseBorrowerCycle() const { return useBorrowerCycle; }
        [[nodiscard]] const std::string& getDigitsAfterDecimal() const { return digitsAfterDecimal; }
        [[nodiscard]] const std::string& getInMultiplesOf() const { return inMultiplesOf; }
        [[nodiscard]] int getRepaymentFrequencyType() const { return repaymentFrequencyType; }
        [[nodiscard]] int getInterestRateFrequencyType() const { return interestRateFrequencyType; }
        [[nodiscard]] int getAmortizationType() const { return amortizationType; }
        [[nodiscard]] int getInterestType() const { return interestType; }
        [[nodiscard]] int getInterestCalculationPeriodType() const { return interestCalculationPeriodType; }
        [[nodiscard]] int getTransactionProcessingStrategyId() const { return transactionProcessingStrategyId; }
        [[nodiscard]] const Json::Value& getPrincipalVariationsForBorrowerCycle() const { return principalVariationsForBorrowerCycle; }
        [[nodiscard]] const Json::Value& getInterestRateVariationsForBorrowerCycle() const { return interestRateVariationsForBorrowerCycle; }
        [[nodiscard]] const std::vector<RepaymentVariationDto>& getNumberOfRepaymentVariationsForBorrowerCycle() const { return numberOfRepaymentVariationsForBorrowerCycle; }
        [[nodiscard]] const AttributeOverridesDto& getAllowAttributeOverrides() const { return allowAttributeOverrides; }
        [[nodiscard]] const std::string& getAccountingRule() const { return accountingRule; }
        [[nodiscard]] const std::string& getName() const { return name; }
        [[nodiscard]] const std::string& getShortName() const { return shortName; }
        [[nodiscard]] const std::string& getPrincipal() const { return principal; }
        [[nodiscard]] const std::string& getNumberOfRepayments() const { return numberOfRepayments; }
        [[nodiscard]] const std::string& getRepaymentEvery() const { return repaymentEvery; }
        [[nodiscard]] const std::string& getInterestRatePerPeriod() const { return interestRatePerPeriod; }
        [[nodiscard]] const Json::Value& getPaymentChannelToFundSourceMappings() const { return paymentChannelToFundSourceMappings; }
        [[nodiscard]] const Json::Value& getFeeToIncomeAccountMappings() const { return feeToIncomeAccountMappings; }
        [[nodiscard]] const Json::Value& getPenaltyToIncomeAccountMappings() const { return penaltyToIncomeAccountMappings; }
        [[nodiscard]] const Json::Value& getCharges() const { return charges; }
        [[nodiscard]] int getOverdueDaysForNPA() const { return overdueDaysForNPA; }
        [[nodiscard]] int getFundSourceAccountId() const { return fundSourceAccountId; }
        [[nodiscard]] int getLoanPortfolioAccountId() const { return loanPortfolioAccountId; }
        [[nodiscard]] int getTransfersInSuspenseAccountId() const { return transfersInSuspenseAccountId; }
        [[nodiscard]] int getInterestOnLoanAccountId() const { return interestOnLoanAccountId; }
        [[nodiscard]] int getIncomeFromFeeAccountId() const { return incomeFromFeeAccountId; }
        [[nodiscard]] int getIncomeFromPenaltyAccountId() const { return incomeFromPenaltyAccountId; }
        [[nodiscard]] int getWriteOffAccountId() const { return writeOffAccountId; }
        [[nodiscard]] int getOverpaymentLiabilityAccountId() const { return overpaymentLiabilityAccountId; }
        [[nodiscard]] int getDaysInMonthType() const { return daysInMonthType; }
        [[nodiscard]] int getDaysInYearType() const { return daysInYearType; }
        [[nodiscard]] const std::string& getIsInterestRecalculationEnabled() const { return isInterestRecalculationEnabled; }
        [[nodiscard]] const std::string& getHoldGuaranteeFunds() const { return holdGuaranteeFunds; }
        [[nodiscard]] int getPrincipalThresholdForLastInstallment() const { return principalThresholdForLastInstallment; }

        // Setters
        void setCurrencyCode(const std::string& value) { currencyCode = value; }
        void setIncludeInBorrowerCycle(const std::string& value) { includeInBorrowerCycle = value; }
        void setUseBorrowerCycle(bool value) { useBorrowerCycle = value; }
        void setDigitsAfterDecimal(const std::string& value) { digitsAfterDecimal = value; }
        void setInMultiplesOf(const std::string& value) { inMultiplesOf = value; }
        void setRepaymentFrequencyType(int value) { repaymentFrequencyType = value; }
        void setInterestRateFrequencyType(int value) { interestRateFrequencyType = value; }
        void setAmortizationType(int value) { amortizationType = value; }
        void setInterestType(int value) { interestType = value; }
        void setInterestCalculationPeriodType(int value) { interestCalculationPeriodType = value; }
        void setTransactionProcessingStrategyId(int value) { transactionProcessingStrategyId = value; }
        void setPrincipalVariationsForBorrowerCycle(const Json::Value& value) { principalVariationsForBorrowerCycle = value; }
        void setInterestRateVariationsForBorrowerCycle(const Json::Value& value) { interestRateVariationsForBorrowerCycle = value; }
        void setNumberOfRepaymentVariationsForBorrowerCycle(const std::vector<RepaymentVariationDto>& value) { numberOfRepaymentVariationsForBorrowerCycle = value; }
        void setAllowAttributeOverrides(const AttributeOverridesDto& value) { allowAttributeOverrides = value; }
        void setAccountingRule(const std::string& value) { accountingRule = value; }
        void setName(const std::string& value) { name = value; }
        void setShortName(const std::string& value) { shortName = value; }
        void setPrincipal(const std::string& value) { principal = value; }
        void setNumberOfRepayments(const std::string& value) { numberOfRepayments = value; }
        void setRepaymentEvery(const std::string& value) { repaymentEvery = value; }
        void setInterestRatePerPeriod(const std::string& value) { interestRatePerPeriod = value; }
        void setPaymentChannelToFundSourceMappings(const Json::Value& value) { paymentChannelToFundSourceMappings = value; }
        void setFeeToIncomeAccountMappings(const Json::Value& value) { feeToIncomeAccountMappings = value; }
        void setPenaltyToIncomeAccountMappings(const Json::Value& value) { penaltyToIncomeAccountMappings = value; }
        void setCharges(const Json::Value& value) { charges = value; }
        void setOverdueDaysForNPA(int value) { overdueDaysForNPA = value; }
        void setFundSourceAccountId(int value) { fundSourceAccountId = value; }
        void setLoanPortfolioAccountId(int value) { loanPortfolioAccountId = value; }
        void setTransfersInSuspenseAccountId(int value) { transfersInSuspenseAccountId = value; }
        void setInterestOnLoanAccountId(int value) { interestOnLoanAccountId = value; }
        void setIncomeFromFeeAccountId(int value) { incomeFromFeeAccountId = value; }
        void setIncomeFromPenaltyAccountId(int value) { incomeFromPenaltyAccountId = value; }
        void setWriteOffAccountId(int value) { writeOffAccountId = value; }
        void setOverpaymentLiabilityAccountId(int value) { overpaymentLiabilityAccountId = value; }
        void setDaysInMonthType(int value) { daysInMonthType = value; }
        void setDaysInYearType(int value) { daysInYearType = value; }
        void setIsInterestRecalculationEnabled(const std::string& value) { isInterestRecalculationEnabled = value; }
        void setHoldGuaranteeFunds(const std::string& value) { holdGuaranteeFunds = value; }
        void setPrincipalThresholdForLastInstallment(int value) { principalThresholdForLastInstallment = value; }

    private:

        std::string currencyCode;
        std::string includeInBorrowerCycle;
        bool useBorrowerCycle{false};
        std::string digitsAfterDecimal;
        std::string inMultiplesOf;
        int repaymentFrequencyType{0};
        int interestRateFrequencyType{0};
        int amortizationType{0};
        int interestType{0};
        int interestCalculationPeriodType{0};
        int transactionProcessingStrategyId{0};
        Json::Value principalVariationsForBorrowerCycle;
        Json::Value interestRateVariationsForBorrowerCycle;
        std::vector<RepaymentVariationDto> numberOfRepaymentVariationsForBorrowerCycle;
        AttributeOverridesDto allowAttributeOverrides;
        std::string accountingRule;
        std::string name;
        std::string shortName;
        std::string principal;
        std::string numberOfRepayments;
        std::string repaymentEvery;
        std::string interestRatePerPeriod;
        Json::Value paymentChannelToFundSourceMappings;
        Json::Value feeToIncomeAccountMappings;
        Json::Value penaltyToIncomeAccountMappings;
        Json::Value charges;
        int overdueDaysForNPA{0};
        int fundSourceAccountId{0};
        int loanPortfolioAccountId{0};
        int transfersInSuspenseAccountId{0};
        int interestOnLoanAccountId{0};
        int incomeFromFeeAccountId{0};
        int incomeFromPenaltyAccountId{0};
        int writeOffAccountId{0};
        int overpaymentLiabilityAccountId{0};
        int daysInMonthType{0};
        int daysInYearType{0};
        std::string isInterestRecalculationEnabled;
        std::string holdGuaranteeFunds;
        int principalThresholdForLastInstallment{0};
    };

    inline void LoanProductDto::fromJson(const Json::Value& json) {

        if (json.isMember("currencyCode") && !json["currencyCode"].isNull()) {
            currencyCode = json["currencyCode"].asString();
        }

        if (json.isMember("includeInBorrowerCycle") && !json["includeInBorrowerCycle"].isNull()) {
            includeInBorrowerCycle = json["includeInBorrowerCycle"].asString();
        }

        if (json.isMember("useBorrowerCycle") && !json["useBorrowerCycle"].isNull()) {
            useBorrowerCycle = json["useBorrowerCycle"].asBool();
        }

        if (json.isMember("digitsAfterDecimal") && !json["digitsAfterDecimal"].isNull()) {
            digitsAfterDecimal = json["digitsAfterDecimal"].asString();
        }

        if (json.isMember("inMultiplesOf") && !json["inMultiplesOf"].isNull()) {
            inMultiplesOf = json["inMultiplesOf"].asString();
        }

        if (json.isMember("repaymentFrequencyType") && !json["repaymentFrequencyType"].isNull()) {
            repaymentFrequencyType = json["repaymentFrequencyType"].asInt();
        }

        if (json.isMember("interestRateFrequencyType") && !json["interestRateFrequencyType"].isNull()) {
            interestRateFrequencyType = json["interestRateFrequencyType"].asInt();
        }

        if (json.isMember("amortizationType") && !json["amortizationType"].isNull()) {
            amortizationType = json["amortizationType"].asInt();
        }

        if (json.isMember("interestType") && !json["interestType"].isNull()) {
            interestType = json["interestType"].asInt();
        }

        if (json.isMember("interestCalculationPeriodType") && !json["interestCalculationPeriodType"].isNull()) {
            interestCalculationPeriodType = json["interestCalculationPeriodType"].asInt();
        }

        if (json.isMember("transactionProcessingStrategyId") && !json["transactionProcessingStrategyId"].isNull()) {
            transactionProcessingStrategyId = json["transactionProcessingStrategyId"].asInt();
        }

        if (json.isMember("principalVariationsForBorrowerCycle") && !json["principalVariationsForBorrowerCycle"].isNull()) {
            principalVariationsForBorrowerCycle = json["principalVariationsForBorrowerCycle"];
        }

        if (json.isMember("interestRateVariationsForBorrowerCycle") && !json["interestRateVariationsForBorrowerCycle"].isNull()) {
            interestRateVariationsForBorrowerCycle = json["interestRateVariationsForBorrowerCycle"];
        }

        if (json.isMember("numberOfRepaymentVariationsForBorrowerCycle") && json["numberOfRepaymentVariationsForBorrowerCycle"].isArray()) {
            numberOfRepaymentVariationsForBorrowerCycle.clear();
            for (const auto& item : json["numberOfRepaymentVariationsForBorrowerCycle"]) {
                RepaymentVariationDto variation;
                variation.fromJson(item);
                numberOfRepaymentVariationsForBorrowerCycle.push_back(variation);
            }
        }

        if (json.isMember("allowAttributeOverrides") && !json["allowAttributeOverrides"].isNull()) {
            allowAttributeOverrides.fromJson(json["allowAttributeOverrides"]);
        }

        if (json.isMember("accountingRule") && !json["accountingRule"].isNull()) {
            accountingRule = json["accountingRule"].asString();
        }

        if (json.isMember("name") && !json["name"].isNull()) {
            name = json["name"].asString();
        }

        if (json.isMember("shortName") && !json["shortName"].isNull()) {
            shortName = json["shortName"].asString();
        }

        if (json.isMember("principal") && !json["principal"].isNull()) {
            principal = json["principal"].asString();
        }

        if (json.isMember("numberOfRepayments") && !json["numberOfRepayments"].isNull()) {
            numberOfRepayments = json["numberOfRepayments"].asString();
        }

        if (json.isMember("repaymentEvery") && !json["repaymentEvery"].isNull()) {
            repaymentEvery = json["repaymentEvery"].asString();
        }

        if (json.isMember("interestRatePerPeriod") && !json["interestRatePerPeriod"].isNull()) {
            interestRatePerPeriod = json["interestRatePerPeriod"].asString();
        }

        if (json.isMember("paymentChannelToFundSourceMappings") && !json["paymentChannelToFundSourceMappings"].isNull()) {
            paymentChannelToFundSourceMappings = json["paymentChannelToFundSourceMappings"];
        }

        if (json.isMember("feeToIncomeAccountMappings") && !json["feeToIncomeAccountMappings"].isNull()) {
            feeToIncomeAccountMappings = json["feeToIncomeAccountMappings"];
        }

        if (json.isMember("penaltyToIncomeAccountMappings") && !json["penaltyToIncomeAccountMappings"].isNull()) {
            penaltyToIncomeAccountMappings = json["penaltyToIncomeAccountMappings"];
        }

        if (json.isMember("charges") && !json["charges"].isNull()) {
            charges = json["charges"];
        }

        if (json.isMember("overdueDaysForNPA") && !json["overdueDaysForNPA"].isNull()) {
            overdueDaysForNPA = json["overdueDaysForNPA"].asInt();
        }

        if (json.isMember("fundSourceAccountId") && !json["fundSourceAccountId"].isNull()) {
            fundSourceAccountId = json["fundSourceAccountId"].asInt();
        }

        if (json.isMember("loanPortfolioAccountId") && !json["loanPortfolioAccountId"].isNull()) {
            loanPortfolioAccountId = json["loanPortfolioAccountId"].asInt();
        }

        if (json.isMember("transfersInSuspenseAccountId") && !json["transfersInSuspenseAccountId"].isNull()) {
            transfersInSuspenseAccountId = json["transfersInSuspenseAccountId"].asInt();
        }

        if (json.isMember("interestOnLoanAccountId") && !json["interestOnLoanAccountId"].isNull()) {
            interestOnLoanAccountId = json["interestOnLoanAccountId"].asInt();
        }

        if (json.isMember("incomeFromFeeAccountId") && !json["incomeFromFeeAccountId"].isNull()) {
            incomeFromFeeAccountId = json["incomeFromFeeAccountId"].asInt();
        }

        if (json.isMember("incomeFromPenaltyAccountId") && !json["incomeFromPenaltyAccountId"].isNull()) {
            incomeFromPenaltyAccountId = json["incomeFromPenaltyAccountId"].asInt();
        }

        if (json.isMember("writeOffAccountId") && !json["writeOffAccountId"].isNull()) {
            writeOffAccountId = json["writeOffAccountId"].asInt();
        }

        if (json.isMember("overpaymentLiabilityAccountId") && !json["overpaymentLiabilityAccountId"].isNull()) {
            overpaymentLiabilityAccountId = json["overpaymentLiabilityAccountId"].asInt();
        }

        if (json.isMember("daysInMonthType") && !json["daysInMonthType"].isNull()) {
            daysInMonthType = json["daysInMonthType"].asInt();
        }

        if (json.isMember("daysInYearType") && !json["daysInYearType"].isNull()) {
            daysInYearType = json["daysInYearType"].asInt();
        }

        if (json.isMember("isInterestRecalculationEnabled") && !json["isInterestRecalculationEnabled"].isNull()) {
            isInterestRecalculationEnabled = json["isInterestRecalculationEnabled"].asString();
        }

        if (json.isMember("holdGuaranteeFunds") && !json["holdGuaranteeFunds"].isNull()) {
            holdGuaranteeFunds = json["holdGuaranteeFunds"].asString();
        }

        if (json.isMember("principalThresholdForLastInstallment") && !json["principalThresholdForLastInstallment"].isNull()) {
            principalThresholdForLastInstallment = json["principalThresholdForLastInstallment"].asInt();
        }
    }

}
#endif //ORGANIZATION_LOANPRODUCTDTO_H