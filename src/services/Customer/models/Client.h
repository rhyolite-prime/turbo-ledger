/**
 *  Client.h
 *
 *  Hand-authored to match drogon_ctl's real generated output for the subset
 *  of the API this codebase's CoroMapper<Client> usage actually needs
 *  (row-mapping + CRUD via Mapper/CoroMapper). The Json::Value constructors,
 *  updateByJson/updateByMasqueradedJson, validateJsonFor.../validJsonOfField
 *  and toJson/toString/toMasqueradedJson methods that a live
 *  `drogon_ctl create_model` run would also emit are intentionally omitted
 *  here since nothing in this codebase calls them; regenerate with
 *  `drogon_ctl create_model` against a live DB with this table if those are
 *  ever needed.
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace TlCustomerDb
{

class Client
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _business_id;
        static const std::string _account_no;
        static const std::string _external_id;
        static const std::string _status;
        static const std::string _sub_status;
        static const std::string _activation_date;
        static const std::string _office_joining_date;
        static const std::string _office_id;
        static const std::string _transfer_to_office_id;
        static const std::string _staff_id;
        static const std::string _firstname;
        static const std::string _middlename;
        static const std::string _lastname;
        static const std::string _fullname;
        static const std::string _display_name;
        static const std::string _mobile_no;
        static const std::string _is_staff;
        static const std::string _gender_cv_id;
        static const std::string _date_of_birth;
        static const std::string _image_id;
        static const std::string _closure_reason_cv_id;
        static const std::string _closedon_date;
        static const std::string _updated_by;
        static const std::string _updated_on;
        static const std::string _submittedon_date;
        static const std::string _activatedon_userid;
        static const std::string _closedon_userid;
        static const std::string _default_savings_product;
        static const std::string _default_savings_account;
        static const std::string _client_type_cv_id;
        static const std::string _client_classification_cv_id;
        static const std::string _reject_reason_cv_id;
        static const std::string _rejectedon_date;
        static const std::string _rejectedon_userid;
        static const std::string _withdraw_reason_cv_id;
        static const std::string _withdrawn_on_date;
        static const std::string _withdraw_on_userid;
        static const std::string _reactivated_on_date;
        static const std::string _reactivated_on_userid;
        static const std::string _legal_structure;
        static const std::string _reopened_on_date;
        static const std::string _reopened_by_userid;
        static const std::string _email_address;
        static const std::string _proposed_transfer_date;
        static const std::string _created_by;
        static const std::string _created_at;
        static const std::string _modified_by;
        static const std::string _modified_at;
        static const std::string _kyc_status;
        static const std::string _risk_rating;
        static const std::string _fatca_flag;
        static const std::string _crs_flag;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = std::string;
    const PrimaryKeyType &getPrimaryKey() const;

    explicit Client(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    Client() = default;

    /**  For column id  */
    const std::string &getValueOfId() const noexcept;
    const std::shared_ptr<std::string> &getId() const noexcept;
    void setId(const std::string &pId) noexcept;
    void setId(std::string &&pId) noexcept;

    /**  For column business_id  */
    const std::string &getValueOfBusinessId() const noexcept;
    const std::shared_ptr<std::string> &getBusinessId() const noexcept;
    void setBusinessId(const std::string &pBusinessId) noexcept;
    void setBusinessId(std::string &&pBusinessId) noexcept;
    void setBusinessIdToNull() noexcept;

    /**  For column account_no  */
    const std::string &getValueOfAccountNo() const noexcept;
    const std::shared_ptr<std::string> &getAccountNo() const noexcept;
    void setAccountNo(const std::string &pAccountNo) noexcept;
    void setAccountNo(std::string &&pAccountNo) noexcept;

    /**  For column external_id  */
    const std::string &getValueOfExternalId() const noexcept;
    const std::shared_ptr<std::string> &getExternalId() const noexcept;
    void setExternalId(const std::string &pExternalId) noexcept;
    void setExternalId(std::string &&pExternalId) noexcept;
    void setExternalIdToNull() noexcept;

    /**  For column status  */
    const int32_t &getValueOfStatus() const noexcept;
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column sub_status  */
    const int32_t &getValueOfSubStatus() const noexcept;
    const std::shared_ptr<int32_t> &getSubStatus() const noexcept;
    void setSubStatus(const int32_t &pSubStatus) noexcept;
    void setSubStatusToNull() noexcept;

    /**  For column activation_date  */
    const ::trantor::Date &getValueOfActivationDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getActivationDate() const noexcept;
    void setActivationDate(const ::trantor::Date &pActivationDate) noexcept;
    void setActivationDateToNull() noexcept;

    /**  For column office_joining_date  */
    const ::trantor::Date &getValueOfOfficeJoiningDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getOfficeJoiningDate() const noexcept;
    void setOfficeJoiningDate(const ::trantor::Date &pOfficeJoiningDate) noexcept;
    void setOfficeJoiningDateToNull() noexcept;

    /**  For column office_id  */
    const std::string &getValueOfOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getOfficeId() const noexcept;
    void setOfficeId(const std::string &pOfficeId) noexcept;
    void setOfficeId(std::string &&pOfficeId) noexcept;
    void setOfficeIdToNull() noexcept;

    /**  For column transfer_to_office_id  */
    const std::string &getValueOfTransferToOfficeId() const noexcept;
    const std::shared_ptr<std::string> &getTransferToOfficeId() const noexcept;
    void setTransferToOfficeId(const std::string &pTransferToOfficeId) noexcept;
    void setTransferToOfficeId(std::string &&pTransferToOfficeId) noexcept;
    void setTransferToOfficeIdToNull() noexcept;

    /**  For column staff_id  */
    const std::string &getValueOfStaffId() const noexcept;
    const std::shared_ptr<std::string> &getStaffId() const noexcept;
    void setStaffId(const std::string &pStaffId) noexcept;
    void setStaffId(std::string &&pStaffId) noexcept;
    void setStaffIdToNull() noexcept;

    /**  For column firstname  */
    const std::string &getValueOfFirstname() const noexcept;
    const std::shared_ptr<std::string> &getFirstname() const noexcept;
    void setFirstname(const std::string &pFirstname) noexcept;
    void setFirstname(std::string &&pFirstname) noexcept;
    void setFirstnameToNull() noexcept;

    /**  For column middlename  */
    const std::string &getValueOfMiddlename() const noexcept;
    const std::shared_ptr<std::string> &getMiddlename() const noexcept;
    void setMiddlename(const std::string &pMiddlename) noexcept;
    void setMiddlename(std::string &&pMiddlename) noexcept;
    void setMiddlenameToNull() noexcept;

    /**  For column lastname  */
    const std::string &getValueOfLastname() const noexcept;
    const std::shared_ptr<std::string> &getLastname() const noexcept;
    void setLastname(const std::string &pLastname) noexcept;
    void setLastname(std::string &&pLastname) noexcept;
    void setLastnameToNull() noexcept;

    /**  For column fullname  */
    const std::string &getValueOfFullname() const noexcept;
    const std::shared_ptr<std::string> &getFullname() const noexcept;
    void setFullname(const std::string &pFullname) noexcept;
    void setFullname(std::string &&pFullname) noexcept;
    void setFullnameToNull() noexcept;

    /**  For column display_name  */
    const std::string &getValueOfDisplayName() const noexcept;
    const std::shared_ptr<std::string> &getDisplayName() const noexcept;
    void setDisplayName(const std::string &pDisplayName) noexcept;
    void setDisplayName(std::string &&pDisplayName) noexcept;
    void setDisplayNameToNull() noexcept;

    /**  For column mobile_no  */
    const std::string &getValueOfMobileNo() const noexcept;
    const std::shared_ptr<std::string> &getMobileNo() const noexcept;
    void setMobileNo(const std::string &pMobileNo) noexcept;
    void setMobileNo(std::string &&pMobileNo) noexcept;
    void setMobileNoToNull() noexcept;

    /**  For column is_staff  */
    const bool &getValueOfIsStaff() const noexcept;
    const std::shared_ptr<bool> &getIsStaff() const noexcept;
    void setIsStaff(const bool &pIsStaff) noexcept;

    /**  For column gender_cv_id  */
    const std::string &getValueOfGenderCvId() const noexcept;
    const std::shared_ptr<std::string> &getGenderCvId() const noexcept;
    void setGenderCvId(const std::string &pGenderCvId) noexcept;
    void setGenderCvId(std::string &&pGenderCvId) noexcept;
    void setGenderCvIdToNull() noexcept;

    /**  For column date_of_birth  */
    const ::trantor::Date &getValueOfDateOfBirth() const noexcept;
    const std::shared_ptr<::trantor::Date> &getDateOfBirth() const noexcept;
    void setDateOfBirth(const ::trantor::Date &pDateOfBirth) noexcept;
    void setDateOfBirthToNull() noexcept;

    /**  For column image_id  */
    const std::string &getValueOfImageId() const noexcept;
    const std::shared_ptr<std::string> &getImageId() const noexcept;
    void setImageId(const std::string &pImageId) noexcept;
    void setImageId(std::string &&pImageId) noexcept;
    void setImageIdToNull() noexcept;

    /**  For column closure_reason_cv_id  */
    const std::string &getValueOfClosureReasonCvId() const noexcept;
    const std::shared_ptr<std::string> &getClosureReasonCvId() const noexcept;
    void setClosureReasonCvId(const std::string &pClosureReasonCvId) noexcept;
    void setClosureReasonCvId(std::string &&pClosureReasonCvId) noexcept;
    void setClosureReasonCvIdToNull() noexcept;

    /**  For column closedon_date  */
    const ::trantor::Date &getValueOfClosedonDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getClosedonDate() const noexcept;
    void setClosedonDate(const ::trantor::Date &pClosedonDate) noexcept;
    void setClosedonDateToNull() noexcept;

    /**  For column updated_by  */
    const std::string &getValueOfUpdatedBy() const noexcept;
    const std::shared_ptr<std::string> &getUpdatedBy() const noexcept;
    void setUpdatedBy(const std::string &pUpdatedBy) noexcept;
    void setUpdatedBy(std::string &&pUpdatedBy) noexcept;
    void setUpdatedByToNull() noexcept;

    /**  For column updated_on  */
    const ::trantor::Date &getValueOfUpdatedOn() const noexcept;
    const std::shared_ptr<::trantor::Date> &getUpdatedOn() const noexcept;
    void setUpdatedOn(const ::trantor::Date &pUpdatedOn) noexcept;
    void setUpdatedOnToNull() noexcept;

    /**  For column submittedon_date  */
    const ::trantor::Date &getValueOfSubmittedonDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getSubmittedonDate() const noexcept;
    void setSubmittedonDate(const ::trantor::Date &pSubmittedonDate) noexcept;
    void setSubmittedonDateToNull() noexcept;

    /**  For column activatedon_userid  */
    const std::string &getValueOfActivatedonUserid() const noexcept;
    const std::shared_ptr<std::string> &getActivatedonUserid() const noexcept;
    void setActivatedonUserid(const std::string &pActivatedonUserid) noexcept;
    void setActivatedonUserid(std::string &&pActivatedonUserid) noexcept;
    void setActivatedonUseridToNull() noexcept;

    /**  For column closedon_userid  */
    const std::string &getValueOfClosedonUserid() const noexcept;
    const std::shared_ptr<std::string> &getClosedonUserid() const noexcept;
    void setClosedonUserid(const std::string &pClosedonUserid) noexcept;
    void setClosedonUserid(std::string &&pClosedonUserid) noexcept;
    void setClosedonUseridToNull() noexcept;

    /**  For column default_savings_product  */
    const std::string &getValueOfDefaultSavingsProduct() const noexcept;
    const std::shared_ptr<std::string> &getDefaultSavingsProduct() const noexcept;
    void setDefaultSavingsProduct(const std::string &pDefaultSavingsProduct) noexcept;
    void setDefaultSavingsProduct(std::string &&pDefaultSavingsProduct) noexcept;
    void setDefaultSavingsProductToNull() noexcept;

    /**  For column default_savings_account  */
    const std::string &getValueOfDefaultSavingsAccount() const noexcept;
    const std::shared_ptr<std::string> &getDefaultSavingsAccount() const noexcept;
    void setDefaultSavingsAccount(const std::string &pDefaultSavingsAccount) noexcept;
    void setDefaultSavingsAccount(std::string &&pDefaultSavingsAccount) noexcept;
    void setDefaultSavingsAccountToNull() noexcept;

    /**  For column client_type_cv_id  */
    const std::string &getValueOfClientTypeCvId() const noexcept;
    const std::shared_ptr<std::string> &getClientTypeCvId() const noexcept;
    void setClientTypeCvId(const std::string &pClientTypeCvId) noexcept;
    void setClientTypeCvId(std::string &&pClientTypeCvId) noexcept;
    void setClientTypeCvIdToNull() noexcept;

    /**  For column client_classification_cv_id  */
    const std::string &getValueOfClientClassificationCvId() const noexcept;
    const std::shared_ptr<std::string> &getClientClassificationCvId() const noexcept;
    void setClientClassificationCvId(const std::string &pClientClassificationCvId) noexcept;
    void setClientClassificationCvId(std::string &&pClientClassificationCvId) noexcept;
    void setClientClassificationCvIdToNull() noexcept;

    /**  For column reject_reason_cv_id  */
    const std::string &getValueOfRejectReasonCvId() const noexcept;
    const std::shared_ptr<std::string> &getRejectReasonCvId() const noexcept;
    void setRejectReasonCvId(const std::string &pRejectReasonCvId) noexcept;
    void setRejectReasonCvId(std::string &&pRejectReasonCvId) noexcept;
    void setRejectReasonCvIdToNull() noexcept;

    /**  For column rejectedon_date  */
    const ::trantor::Date &getValueOfRejectedonDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getRejectedonDate() const noexcept;
    void setRejectedonDate(const ::trantor::Date &pRejectedonDate) noexcept;
    void setRejectedonDateToNull() noexcept;

    /**  For column rejectedon_userid  */
    const std::string &getValueOfRejectedonUserid() const noexcept;
    const std::shared_ptr<std::string> &getRejectedonUserid() const noexcept;
    void setRejectedonUserid(const std::string &pRejectedonUserid) noexcept;
    void setRejectedonUserid(std::string &&pRejectedonUserid) noexcept;
    void setRejectedonUseridToNull() noexcept;

    /**  For column withdraw_reason_cv_id  */
    const std::string &getValueOfWithdrawReasonCvId() const noexcept;
    const std::shared_ptr<std::string> &getWithdrawReasonCvId() const noexcept;
    void setWithdrawReasonCvId(const std::string &pWithdrawReasonCvId) noexcept;
    void setWithdrawReasonCvId(std::string &&pWithdrawReasonCvId) noexcept;
    void setWithdrawReasonCvIdToNull() noexcept;

    /**  For column withdrawn_on_date  */
    const ::trantor::Date &getValueOfWithdrawnOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getWithdrawnOnDate() const noexcept;
    void setWithdrawnOnDate(const ::trantor::Date &pWithdrawnOnDate) noexcept;
    void setWithdrawnOnDateToNull() noexcept;

    /**  For column withdraw_on_userid  */
    const std::string &getValueOfWithdrawOnUserid() const noexcept;
    const std::shared_ptr<std::string> &getWithdrawOnUserid() const noexcept;
    void setWithdrawOnUserid(const std::string &pWithdrawOnUserid) noexcept;
    void setWithdrawOnUserid(std::string &&pWithdrawOnUserid) noexcept;
    void setWithdrawOnUseridToNull() noexcept;

    /**  For column reactivated_on_date  */
    const ::trantor::Date &getValueOfReactivatedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getReactivatedOnDate() const noexcept;
    void setReactivatedOnDate(const ::trantor::Date &pReactivatedOnDate) noexcept;
    void setReactivatedOnDateToNull() noexcept;

    /**  For column reactivated_on_userid  */
    const std::string &getValueOfReactivatedOnUserid() const noexcept;
    const std::shared_ptr<std::string> &getReactivatedOnUserid() const noexcept;
    void setReactivatedOnUserid(const std::string &pReactivatedOnUserid) noexcept;
    void setReactivatedOnUserid(std::string &&pReactivatedOnUserid) noexcept;
    void setReactivatedOnUseridToNull() noexcept;

    /**  For column legal_structure  */
    const int32_t &getValueOfLegalStructure() const noexcept;
    const std::shared_ptr<int32_t> &getLegalStructure() const noexcept;
    void setLegalStructure(const int32_t &pLegalStructure) noexcept;
    void setLegalStructureToNull() noexcept;

    /**  For column reopened_on_date  */
    const ::trantor::Date &getValueOfReopenedOnDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getReopenedOnDate() const noexcept;
    void setReopenedOnDate(const ::trantor::Date &pReopenedOnDate) noexcept;
    void setReopenedOnDateToNull() noexcept;

    /**  For column reopened_by_userid  */
    const std::string &getValueOfReopenedByUserid() const noexcept;
    const std::shared_ptr<std::string> &getReopenedByUserid() const noexcept;
    void setReopenedByUserid(const std::string &pReopenedByUserid) noexcept;
    void setReopenedByUserid(std::string &&pReopenedByUserid) noexcept;
    void setReopenedByUseridToNull() noexcept;

    /**  For column email_address  */
    const std::string &getValueOfEmailAddress() const noexcept;
    const std::shared_ptr<std::string> &getEmailAddress() const noexcept;
    void setEmailAddress(const std::string &pEmailAddress) noexcept;
    void setEmailAddress(std::string &&pEmailAddress) noexcept;
    void setEmailAddressToNull() noexcept;

    /**  For column proposed_transfer_date  */
    const ::trantor::Date &getValueOfProposedTransferDate() const noexcept;
    const std::shared_ptr<::trantor::Date> &getProposedTransferDate() const noexcept;
    void setProposedTransferDate(const ::trantor::Date &pProposedTransferDate) noexcept;
    void setProposedTransferDateToNull() noexcept;

    /**  For column created_by  */
    const std::string &getValueOfCreatedBy() const noexcept;
    const std::shared_ptr<std::string> &getCreatedBy() const noexcept;
    void setCreatedBy(const std::string &pCreatedBy) noexcept;
    void setCreatedBy(std::string &&pCreatedBy) noexcept;
    void setCreatedByToNull() noexcept;

    /**  For column created_at  */
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;
    void setCreatedAtToNull() noexcept;

    /**  For column modified_by  */
    const std::string &getValueOfModifiedBy() const noexcept;
    const std::shared_ptr<std::string> &getModifiedBy() const noexcept;
    void setModifiedBy(const std::string &pModifiedBy) noexcept;
    void setModifiedBy(std::string &&pModifiedBy) noexcept;
    void setModifiedByToNull() noexcept;

    /**  For column modified_at  */
    const ::trantor::Date &getValueOfModifiedAt() const noexcept;
    const std::shared_ptr<::trantor::Date> &getModifiedAt() const noexcept;
    void setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept;
    void setModifiedAtToNull() noexcept;

    /**  For column kyc_status  */
    const int32_t &getValueOfKycStatus() const noexcept;
    const std::shared_ptr<int32_t> &getKycStatus() const noexcept;
    void setKycStatus(const int32_t &pKycStatus) noexcept;

    /**  For column risk_rating  */
    const int32_t &getValueOfRiskRating() const noexcept;
    const std::shared_ptr<int32_t> &getRiskRating() const noexcept;
    void setRiskRating(const int32_t &pRiskRating) noexcept;

    /**  For column fatca_flag  */
    const bool &getValueOfFatcaFlag() const noexcept;
    const std::shared_ptr<bool> &getFatcaFlag() const noexcept;
    void setFatcaFlag(const bool &pFatcaFlag) noexcept;

    /**  For column crs_flag  */
    const bool &getValueOfCrsFlag() const noexcept;
    const std::shared_ptr<bool> &getCrsFlag() const noexcept;
    void setCrsFlag(const bool &pCrsFlag) noexcept;

    static size_t getColumnNumber() noexcept {  return 53;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

  private:
    friend drogon::orm::Mapper<Client>;
    friend drogon::orm::BaseBuilder<Client, true, true>;
    friend drogon::orm::BaseBuilder<Client, true, false>;
    friend drogon::orm::BaseBuilder<Client, false, true>;
    friend drogon::orm::BaseBuilder<Client, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Client>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<std::string> id_;
    std::shared_ptr<std::string> businessId_;
    std::shared_ptr<std::string> accountNo_;
    std::shared_ptr<std::string> externalId_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<int32_t> subStatus_;
    std::shared_ptr<::trantor::Date> activationDate_;
    std::shared_ptr<::trantor::Date> officeJoiningDate_;
    std::shared_ptr<std::string> officeId_;
    std::shared_ptr<std::string> transferToOfficeId_;
    std::shared_ptr<std::string> staffId_;
    std::shared_ptr<std::string> firstname_;
    std::shared_ptr<std::string> middlename_;
    std::shared_ptr<std::string> lastname_;
    std::shared_ptr<std::string> fullname_;
    std::shared_ptr<std::string> displayName_;
    std::shared_ptr<std::string> mobileNo_;
    std::shared_ptr<bool> isStaff_;
    std::shared_ptr<std::string> genderCvId_;
    std::shared_ptr<::trantor::Date> dateOfBirth_;
    std::shared_ptr<std::string> imageId_;
    std::shared_ptr<std::string> closureReasonCvId_;
    std::shared_ptr<::trantor::Date> closedonDate_;
    std::shared_ptr<std::string> updatedBy_;
    std::shared_ptr<::trantor::Date> updatedOn_;
    std::shared_ptr<::trantor::Date> submittedonDate_;
    std::shared_ptr<std::string> activatedonUserid_;
    std::shared_ptr<std::string> closedonUserid_;
    std::shared_ptr<std::string> defaultSavingsProduct_;
    std::shared_ptr<std::string> defaultSavingsAccount_;
    std::shared_ptr<std::string> clientTypeCvId_;
    std::shared_ptr<std::string> clientClassificationCvId_;
    std::shared_ptr<std::string> rejectReasonCvId_;
    std::shared_ptr<::trantor::Date> rejectedonDate_;
    std::shared_ptr<std::string> rejectedonUserid_;
    std::shared_ptr<std::string> withdrawReasonCvId_;
    std::shared_ptr<::trantor::Date> withdrawnOnDate_;
    std::shared_ptr<std::string> withdrawOnUserid_;
    std::shared_ptr<::trantor::Date> reactivatedOnDate_;
    std::shared_ptr<std::string> reactivatedOnUserid_;
    std::shared_ptr<int32_t> legalStructure_;
    std::shared_ptr<::trantor::Date> reopenedOnDate_;
    std::shared_ptr<std::string> reopenedByUserid_;
    std::shared_ptr<std::string> emailAddress_;
    std::shared_ptr<::trantor::Date> proposedTransferDate_;
    std::shared_ptr<std::string> createdBy_;
    std::shared_ptr<::trantor::Date> createdAt_;
    std::shared_ptr<std::string> modifiedBy_;
    std::shared_ptr<::trantor::Date> modifiedAt_;
    std::shared_ptr<int32_t> kycStatus_;
    std::shared_ptr<int32_t> riskRating_;
    std::shared_ptr<bool> fatcaFlag_;
    std::shared_ptr<bool> crsFlag_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[53]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
        sql += "id,";
        ++parametersCount;
        if(!dirtyFlag_[0])
        {
            needSelection=true;
        }
        if(dirtyFlag_[1])
        {
            sql += "business_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "account_no,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "external_id,";
            ++parametersCount;
        }
        sql += "status,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        if(dirtyFlag_[5])
        {
            sql += "sub_status,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "activation_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "office_joining_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "office_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "transfer_to_office_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "staff_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "firstname,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "middlename,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "lastname,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "fullname,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "display_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[16])
        {
            sql += "mobile_no,";
            ++parametersCount;
        }
        sql += "is_staff,";
        ++parametersCount;
        if(!dirtyFlag_[17])
        {
            needSelection=true;
        }
        if(dirtyFlag_[18])
        {
            sql += "gender_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[19])
        {
            sql += "date_of_birth,";
            ++parametersCount;
        }
        if(dirtyFlag_[20])
        {
            sql += "image_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[21])
        {
            sql += "closure_reason_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[22])
        {
            sql += "closedon_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[23])
        {
            sql += "updated_by,";
            ++parametersCount;
        }
        if(dirtyFlag_[24])
        {
            sql += "updated_on,";
            ++parametersCount;
        }
        if(dirtyFlag_[25])
        {
            sql += "submittedon_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[26])
        {
            sql += "activatedon_userid,";
            ++parametersCount;
        }
        if(dirtyFlag_[27])
        {
            sql += "closedon_userid,";
            ++parametersCount;
        }
        if(dirtyFlag_[28])
        {
            sql += "default_savings_product,";
            ++parametersCount;
        }
        if(dirtyFlag_[29])
        {
            sql += "default_savings_account,";
            ++parametersCount;
        }
        if(dirtyFlag_[30])
        {
            sql += "client_type_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[31])
        {
            sql += "client_classification_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[32])
        {
            sql += "reject_reason_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[33])
        {
            sql += "rejectedon_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[34])
        {
            sql += "rejectedon_userid,";
            ++parametersCount;
        }
        if(dirtyFlag_[35])
        {
            sql += "withdraw_reason_cv_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[36])
        {
            sql += "withdrawn_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[37])
        {
            sql += "withdraw_on_userid,";
            ++parametersCount;
        }
        if(dirtyFlag_[38])
        {
            sql += "reactivated_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[39])
        {
            sql += "reactivated_on_userid,";
            ++parametersCount;
        }
        if(dirtyFlag_[40])
        {
            sql += "legal_structure,";
            ++parametersCount;
        }
        if(dirtyFlag_[41])
        {
            sql += "reopened_on_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[42])
        {
            sql += "reopened_by_userid,";
            ++parametersCount;
        }
        if(dirtyFlag_[43])
        {
            sql += "email_address,";
            ++parametersCount;
        }
        if(dirtyFlag_[44])
        {
            sql += "proposed_transfer_date,";
            ++parametersCount;
        }
        if(dirtyFlag_[45])
        {
            sql += "created_by,";
            ++parametersCount;
        }
        sql += "created_at,";
        ++parametersCount;
        if(!dirtyFlag_[46])
        {
            needSelection=true;
        }
        if(dirtyFlag_[47])
        {
            sql += "modified_by,";
            ++parametersCount;
        }
        sql += "modified_at,";
        ++parametersCount;
        if(!dirtyFlag_[48])
        {
            needSelection=true;
        }
        sql += "kyc_status,";
        ++parametersCount;
        if(!dirtyFlag_[49])
        {
            needSelection=true;
        }
        sql += "risk_rating,";
        ++parametersCount;
        if(!dirtyFlag_[50])
        {
            needSelection=true;
        }
        sql += "fatca_flag,";
        ++parametersCount;
        if(!dirtyFlag_[51])
        {
            needSelection=true;
        }
        sql += "crs_flag,";
        ++parametersCount;
        if(!dirtyFlag_[52])
        {
            needSelection=true;
        }
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        if(dirtyFlag_[0])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[1])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[2])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[4])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[5])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[6])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[7])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[8])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[11])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[12])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[13])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[14])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[16])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[17])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[18])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[19])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[20])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[21])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[22])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[23])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[24])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[25])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[26])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[27])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[28])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[29])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[30])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[31])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[32])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[33])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[34])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[35])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[36])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[37])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[38])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[39])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[40])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[41])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[42])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[43])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[44])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[45])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[46])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[47])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[48])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[49])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[50])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[51])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[52])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace TlCustomerDb
} // namespace drogon_model
