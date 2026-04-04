#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class LoansController : public drogon::HttpController<LoansController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/loans/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(LoansController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(LoansController::getLoanDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(LoansController::getLoans, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(LoansController::getGlimApplication, std::string(PREFIX) + "glim-account/{1}", Get);
    ADD_METHOD_TO(LoansController::updateLoanApplication, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(LoansController::calculateLoanRepaymentSchedule, std::string(PREFIX) + "{1}/calculate-loan-schedule", Post);
    ADD_METHOD_TO(LoansController::submitLoanApplication, std::string(PREFIX) + "submit-application", Post);
    ADD_METHOD_TO(LoansController::approveLoanApplication, std::string(PREFIX) + "{1}/approve-application", Post);
    ADD_METHOD_TO(LoansController::recoverLoanGuarantee, std::string(PREFIX) + "{1}/recover-guarantees", Post);
    ADD_METHOD_TO(LoansController::undoLoanApplicationApproval, std::string(PREFIX) + "{1}/undo-approval", Post);
    ADD_METHOD_TO(LoansController::assignLoanOfficer, std::string(PREFIX) + "{1}/assign-loan-officer", Post);
    ADD_METHOD_TO(LoansController::unassignLoanOfficer, std::string(PREFIX) + "{1}/unassign-loan-officer", Post);
    ADD_METHOD_TO(LoansController::rejectLoanApplication, std::string(PREFIX) + "{1}/reject", Post);
    ADD_METHOD_TO(LoansController::withdrawLoanApplicationByApplicant, std::string(PREFIX) + "{1}/withdrawn-by-applicant", Post);
    ADD_METHOD_TO(LoansController::disburseLoan, std::string(PREFIX) + "{1}/disburse", Post);
    ADD_METHOD_TO(LoansController::disburseLoanToSavingsAccount, std::string(PREFIX) + "{1}/disburse-to-savings", Post);
    ADD_METHOD_TO(LoansController::undoLoanDisbursal, std::string(PREFIX) + "{1}/undo-disbursal", Post);
    ADD_METHOD_TO(LoansController::submitGlimApplication, std::string(PREFIX) + "submit-glim-application", Post);
    ADD_METHOD_TO(LoansController::approveGlimApplication, std::string(PREFIX) + "glim-account/{1}/approve", Post);
    ADD_METHOD_TO(LoansController::undoApprovalGlimApplication, std::string(PREFIX) + "glim-account/{1}/undo-approval", Post);
    ADD_METHOD_TO(LoansController::rejectGlimApplication, std::string(PREFIX) + "glim-account/{1}/reject", Post);
    ADD_METHOD_TO(LoansController::disburseGlimApplication, std::string(PREFIX) + "glim-account/{1}/disburse", Post);
    ADD_METHOD_TO(LoansController::undoDisbursalGlimApplication, std::string(PREFIX) + "glim-account/{1}/undo-disbursal", Post);
    ADD_METHOD_TO(LoansController::repaymentGlimApplication, std::string(PREFIX) + "glim-account/{1}/repayment", Post);
    ADD_METHOD_TO(LoansController::deleteLoanApplication, std::string(PREFIX) + "{1}", Delete);
    //loan transactions
    ADD_METHOD_TO(LoansController::retrieveLoanTransactionTemplate, std::string(PREFIX) + "{1}/transactions/template", Get);
    ADD_METHOD_TO(LoansController::makeLoanRepayment, std::string(PREFIX) + "{1}/transactions/repayment", Post);
    ADD_METHOD_TO(LoansController::refundActiveLoanByCash, std::string(PREFIX) + "{1}/transactions/refund-by-cash", Post);
    ADD_METHOD_TO(LoansController::refundActiveLoanByMomo, std::string(PREFIX) + "{1}/transactions/refund-by-momo", Post);
    ADD_METHOD_TO(LoansController::foreclosureOfActiveLoan, std::string(PREFIX) + "{1}/transactions/fore-closure", Post);
    ADD_METHOD_TO(LoansController::waiveInterestOnActiveLoan, std::string(PREFIX) + "{1}/transactions/waive-interest", Post);
    ADD_METHOD_TO(LoansController::writeOffActiveLoan, std::string(PREFIX) + "{1}/transactions/write-off", Post);
    ADD_METHOD_TO(LoansController::makeRecoveryPaymentLoan, std::string(PREFIX) + "{1}/transactions/recovery-payment", Post);
    ADD_METHOD_TO(LoansController::undoLoanWriteOffTransaction, std::string(PREFIX) + "{1}/transactions/undo-write-off", Post);
    ADD_METHOD_TO(LoansController::getLoanTransactionDetails, std::string(PREFIX) + "{1}/transactions/{2}", Get);
    ADD_METHOD_TO(LoansController::adjustLoanTransaction, std::string(PREFIX) + "{1}/transactions/{2}", Put);
    ADD_METHOD_TO(LoansController::adjustLoanTransaction, std::string(PREFIX) + "{1}/transactions/{2}", Put);
    // loan guarantors
    ADD_METHOD_TO(LoansController::getGuarantor, std::string(PREFIX) + "{1}/guarantors", Get);
    ADD_METHOD_TO(LoansController::retrieveGuarantorsDetailsTemplate, std::string(PREFIX) + "{1}/guarantors/template", Get);
    ADD_METHOD_TO(LoansController::getGuarantorDetails, std::string(PREFIX) + "{1}/guarantors/{2}", Get);
    ADD_METHOD_TO(LoansController::createGuarantor, std::string(PREFIX) + "{1}/guarantors", Post);
    ADD_METHOD_TO(LoansController::updateGuarantor, std::string(PREFIX) + "{1}/guarantors/{2}", Put);
    ADD_METHOD_TO(LoansController::deleteGuarantor, std::string(PREFIX) + "{1}/guarantors/{2}", Delete);
    //collateral
    ADD_METHOD_TO(LoansController::getLoanCollaterals, std::string(PREFIX) + "{1}/collaterals", Get);
    ADD_METHOD_TO(LoansController::getLoanCollateralDetailTemplate, std::string(PREFIX) + "{1}/collaterals/template", Get);
    ADD_METHOD_TO(LoansController::getLoanCollateralDetails, std::string(PREFIX) + "{1}/collaterals/{2}", Get);
    ADD_METHOD_TO(LoansController::createLoanCollateral, std::string(PREFIX) + "{1}/collaterals/{2}", Post);
    ADD_METHOD_TO(LoansController::updateLoanCollateral, std::string(PREFIX) + "{1}/collaterals/{2}", Put);
    ADD_METHOD_TO(LoansController::deleteLoanCollateral, std::string(PREFIX) + "{1}/collaterals/{2}", Delete);
    //loan charges
    ADD_METHOD_TO(LoansController::getLoanCharges, std::string(PREFIX) + "{1}/charges", Get);
    ADD_METHOD_TO(LoansController::retrieveLoanChargesTemplate, std::string(PREFIX) + "{1}/charges/template", Get);
    ADD_METHOD_TO(LoansController::getLoanChargesDetails, std::string(PREFIX) + "{1}/charges/{2}", Get);
    ADD_METHOD_TO(LoansController::createLoanCharge, std::string(PREFIX) + "{1}/charges", Post);
    ADD_METHOD_TO(LoansController::updateLoanCharge, std::string(PREFIX) + "{1}/charges/{2}", Put);
    ADD_METHOD_TO(LoansController::payLoanCharge, std::string(PREFIX) + "{1}/charges/{2}/pay", Put);
    ADD_METHOD_TO(LoansController::deleteLoanCharge, std::string(PREFIX) + "{1}/charges/{2}", Delete);
    //
    METHOD_LIST_END

    void getLoanDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getCharges(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
