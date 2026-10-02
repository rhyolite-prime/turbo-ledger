/**
 *  Client.cc
 *
 *  See Client.h for the hand-authored-subset note.
 *
 */

#include "Client.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::TlCustomerDb;

const std::string Client::Cols::_id = "\"id\"";
const std::string Client::Cols::_business_id = "\"business_id\"";
const std::string Client::Cols::_account_no = "\"account_no\"";
const std::string Client::Cols::_external_id = "\"external_id\"";
const std::string Client::Cols::_status = "\"status\"";
const std::string Client::Cols::_sub_status = "\"sub_status\"";
const std::string Client::Cols::_activation_date = "\"activation_date\"";
const std::string Client::Cols::_office_joining_date = "\"office_joining_date\"";
const std::string Client::Cols::_office_id = "\"office_id\"";
const std::string Client::Cols::_transfer_to_office_id = "\"transfer_to_office_id\"";
const std::string Client::Cols::_staff_id = "\"staff_id\"";
const std::string Client::Cols::_firstname = "\"firstname\"";
const std::string Client::Cols::_middlename = "\"middlename\"";
const std::string Client::Cols::_lastname = "\"lastname\"";
const std::string Client::Cols::_fullname = "\"fullname\"";
const std::string Client::Cols::_display_name = "\"display_name\"";
const std::string Client::Cols::_mobile_no = "\"mobile_no\"";
const std::string Client::Cols::_is_staff = "\"is_staff\"";
const std::string Client::Cols::_gender_cv_id = "\"gender_cv_id\"";
const std::string Client::Cols::_date_of_birth = "\"date_of_birth\"";
const std::string Client::Cols::_image_id = "\"image_id\"";
const std::string Client::Cols::_closure_reason_cv_id = "\"closure_reason_cv_id\"";
const std::string Client::Cols::_closedon_date = "\"closedon_date\"";
const std::string Client::Cols::_updated_by = "\"updated_by\"";
const std::string Client::Cols::_updated_on = "\"updated_on\"";
const std::string Client::Cols::_submittedon_date = "\"submittedon_date\"";
const std::string Client::Cols::_activatedon_userid = "\"activatedon_userid\"";
const std::string Client::Cols::_closedon_userid = "\"closedon_userid\"";
const std::string Client::Cols::_default_savings_product = "\"default_savings_product\"";
const std::string Client::Cols::_default_savings_account = "\"default_savings_account\"";
const std::string Client::Cols::_client_type_cv_id = "\"client_type_cv_id\"";
const std::string Client::Cols::_client_classification_cv_id = "\"client_classification_cv_id\"";
const std::string Client::Cols::_reject_reason_cv_id = "\"reject_reason_cv_id\"";
const std::string Client::Cols::_rejectedon_date = "\"rejectedon_date\"";
const std::string Client::Cols::_rejectedon_userid = "\"rejectedon_userid\"";
const std::string Client::Cols::_withdraw_reason_cv_id = "\"withdraw_reason_cv_id\"";
const std::string Client::Cols::_withdrawn_on_date = "\"withdrawn_on_date\"";
const std::string Client::Cols::_withdraw_on_userid = "\"withdraw_on_userid\"";
const std::string Client::Cols::_reactivated_on_date = "\"reactivated_on_date\"";
const std::string Client::Cols::_reactivated_on_userid = "\"reactivated_on_userid\"";
const std::string Client::Cols::_legal_structure = "\"legal_structure\"";
const std::string Client::Cols::_reopened_on_date = "\"reopened_on_date\"";
const std::string Client::Cols::_reopened_by_userid = "\"reopened_by_userid\"";
const std::string Client::Cols::_email_address = "\"email_address\"";
const std::string Client::Cols::_proposed_transfer_date = "\"proposed_transfer_date\"";
const std::string Client::Cols::_created_by = "\"created_by\"";
const std::string Client::Cols::_created_at = "\"created_at\"";
const std::string Client::Cols::_modified_by = "\"modified_by\"";
const std::string Client::Cols::_modified_at = "\"modified_at\"";
const std::string Client::Cols::_kyc_status = "\"kyc_status\"";
const std::string Client::Cols::_risk_rating = "\"risk_rating\"";
const std::string Client::Cols::_fatca_flag = "\"fatca_flag\"";
const std::string Client::Cols::_crs_flag = "\"crs_flag\"";
const std::string Client::primaryKeyName = "id";
const bool Client::hasPrimaryKey = true;
const std::string Client::tableName = "\"client\"";

const std::vector<typename Client::MetaData> Client::metaData_={
{"id","std::string","uuid",0,0,1,1},
{"business_id","std::string","uuid",0,0,0,0},
{"account_no","std::string","character varying",20,0,0,1},
{"external_id","std::string","character varying",100,0,0,0},
{"status","int32_t","integer",4,0,0,1},
{"sub_status","int32_t","integer",4,0,0,0},
{"activation_date","::trantor::Date","date",0,0,0,0},
{"office_joining_date","::trantor::Date","date",0,0,0,0},
{"office_id","std::string","uuid",0,0,0,0},
{"transfer_to_office_id","std::string","uuid",0,0,0,0},
{"staff_id","std::string","uuid",0,0,0,0},
{"firstname","std::string","character varying",80,0,0,0},
{"middlename","std::string","character varying",80,0,0,0},
{"lastname","std::string","character varying",80,0,0,0},
{"fullname","std::string","character varying",240,0,0,0},
{"display_name","std::string","character varying",200,0,0,0},
{"mobile_no","std::string","character varying",20,0,0,0},
{"is_staff","bool","boolean",1,0,0,1},
{"gender_cv_id","std::string","uuid",0,0,0,0},
{"date_of_birth","::trantor::Date","date",0,0,0,0},
{"image_id","std::string","uuid",0,0,0,0},
{"closure_reason_cv_id","std::string","uuid",0,0,0,0},
{"closedon_date","::trantor::Date","date",0,0,0,0},
{"updated_by","std::string","uuid",0,0,0,0},
{"updated_on","::trantor::Date","date",0,0,0,0},
{"submittedon_date","::trantor::Date","date",0,0,0,0},
{"activatedon_userid","std::string","uuid",0,0,0,0},
{"closedon_userid","std::string","uuid",0,0,0,0},
{"default_savings_product","std::string","uuid",0,0,0,0},
{"default_savings_account","std::string","uuid",0,0,0,0},
{"client_type_cv_id","std::string","uuid",0,0,0,0},
{"client_classification_cv_id","std::string","uuid",0,0,0,0},
{"reject_reason_cv_id","std::string","uuid",0,0,0,0},
{"rejectedon_date","::trantor::Date","date",0,0,0,0},
{"rejectedon_userid","std::string","uuid",0,0,0,0},
{"withdraw_reason_cv_id","std::string","uuid",0,0,0,0},
{"withdrawn_on_date","::trantor::Date","date",0,0,0,0},
{"withdraw_on_userid","std::string","uuid",0,0,0,0},
{"reactivated_on_date","::trantor::Date","date",0,0,0,0},
{"reactivated_on_userid","std::string","uuid",0,0,0,0},
{"legal_structure","int32_t","integer",4,0,0,0},
{"reopened_on_date","::trantor::Date","date",0,0,0,0},
{"reopened_by_userid","std::string","uuid",0,0,0,0},
{"email_address","std::string","character varying",150,0,0,0},
{"proposed_transfer_date","::trantor::Date","date",0,0,0,0},
{"created_by","std::string","uuid",0,0,0,0},
{"created_at","::trantor::Date","timestamp with time zone",0,0,0,0},
{"modified_by","std::string","uuid",0,0,0,0},
{"modified_at","::trantor::Date","timestamp with time zone",0,0,0,0},
{"kyc_status","int32_t","integer",4,0,0,1},
{"risk_rating","int32_t","integer",4,0,0,1},
{"fatca_flag","bool","boolean",1,0,0,1},
{"crs_flag","bool","boolean",1,0,0,1}
};
const std::string &Client::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Client::Client(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<std::string>(r["id"].as<std::string>());
        }
        if(!r["business_id"].isNull())
        {
            businessId_=std::make_shared<std::string>(r["business_id"].as<std::string>());
        }
        if(!r["account_no"].isNull())
        {
            accountNo_=std::make_shared<std::string>(r["account_no"].as<std::string>());
        }
        if(!r["external_id"].isNull())
        {
            externalId_=std::make_shared<std::string>(r["external_id"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["sub_status"].isNull())
        {
            subStatus_=std::make_shared<int32_t>(r["sub_status"].as<int32_t>());
        }
        if(!r["activation_date"].isNull())
        {
            auto daysStr = r["activation_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["office_joining_date"].isNull())
        {
            auto daysStr = r["office_joining_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            officeJoiningDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["office_id"].isNull())
        {
            officeId_=std::make_shared<std::string>(r["office_id"].as<std::string>());
        }
        if(!r["transfer_to_office_id"].isNull())
        {
            transferToOfficeId_=std::make_shared<std::string>(r["transfer_to_office_id"].as<std::string>());
        }
        if(!r["staff_id"].isNull())
        {
            staffId_=std::make_shared<std::string>(r["staff_id"].as<std::string>());
        }
        if(!r["firstname"].isNull())
        {
            firstname_=std::make_shared<std::string>(r["firstname"].as<std::string>());
        }
        if(!r["middlename"].isNull())
        {
            middlename_=std::make_shared<std::string>(r["middlename"].as<std::string>());
        }
        if(!r["lastname"].isNull())
        {
            lastname_=std::make_shared<std::string>(r["lastname"].as<std::string>());
        }
        if(!r["fullname"].isNull())
        {
            fullname_=std::make_shared<std::string>(r["fullname"].as<std::string>());
        }
        if(!r["display_name"].isNull())
        {
            displayName_=std::make_shared<std::string>(r["display_name"].as<std::string>());
        }
        if(!r["mobile_no"].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r["mobile_no"].as<std::string>());
        }
        if(!r["is_staff"].isNull())
        {
            isStaff_=std::make_shared<bool>(r["is_staff"].as<bool>());
        }
        if(!r["gender_cv_id"].isNull())
        {
            genderCvId_=std::make_shared<std::string>(r["gender_cv_id"].as<std::string>());
        }
        if(!r["date_of_birth"].isNull())
        {
            auto daysStr = r["date_of_birth"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dateOfBirth_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["image_id"].isNull())
        {
            imageId_=std::make_shared<std::string>(r["image_id"].as<std::string>());
        }
        if(!r["closure_reason_cv_id"].isNull())
        {
            closureReasonCvId_=std::make_shared<std::string>(r["closure_reason_cv_id"].as<std::string>());
        }
        if(!r["closedon_date"].isNull())
        {
            auto daysStr = r["closedon_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["updated_by"].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r["updated_by"].as<std::string>());
        }
        if(!r["updated_on"].isNull())
        {
            auto daysStr = r["updated_on"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            updatedOn_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["submittedon_date"].isNull())
        {
            auto daysStr = r["submittedon_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["activatedon_userid"].isNull())
        {
            activatedonUserid_=std::make_shared<std::string>(r["activatedon_userid"].as<std::string>());
        }
        if(!r["closedon_userid"].isNull())
        {
            closedonUserid_=std::make_shared<std::string>(r["closedon_userid"].as<std::string>());
        }
        if(!r["default_savings_product"].isNull())
        {
            defaultSavingsProduct_=std::make_shared<std::string>(r["default_savings_product"].as<std::string>());
        }
        if(!r["default_savings_account"].isNull())
        {
            defaultSavingsAccount_=std::make_shared<std::string>(r["default_savings_account"].as<std::string>());
        }
        if(!r["client_type_cv_id"].isNull())
        {
            clientTypeCvId_=std::make_shared<std::string>(r["client_type_cv_id"].as<std::string>());
        }
        if(!r["client_classification_cv_id"].isNull())
        {
            clientClassificationCvId_=std::make_shared<std::string>(r["client_classification_cv_id"].as<std::string>());
        }
        if(!r["reject_reason_cv_id"].isNull())
        {
            rejectReasonCvId_=std::make_shared<std::string>(r["reject_reason_cv_id"].as<std::string>());
        }
        if(!r["rejectedon_date"].isNull())
        {
            auto daysStr = r["rejectedon_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rejectedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["rejectedon_userid"].isNull())
        {
            rejectedonUserid_=std::make_shared<std::string>(r["rejectedon_userid"].as<std::string>());
        }
        if(!r["withdraw_reason_cv_id"].isNull())
        {
            withdrawReasonCvId_=std::make_shared<std::string>(r["withdraw_reason_cv_id"].as<std::string>());
        }
        if(!r["withdrawn_on_date"].isNull())
        {
            auto daysStr = r["withdrawn_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            withdrawnOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["withdraw_on_userid"].isNull())
        {
            withdrawOnUserid_=std::make_shared<std::string>(r["withdraw_on_userid"].as<std::string>());
        }
        if(!r["reactivated_on_date"].isNull())
        {
            auto daysStr = r["reactivated_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            reactivatedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["reactivated_on_userid"].isNull())
        {
            reactivatedOnUserid_=std::make_shared<std::string>(r["reactivated_on_userid"].as<std::string>());
        }
        if(!r["legal_structure"].isNull())
        {
            legalStructure_=std::make_shared<int32_t>(r["legal_structure"].as<int32_t>());
        }
        if(!r["reopened_on_date"].isNull())
        {
            auto daysStr = r["reopened_on_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            reopenedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["reopened_by_userid"].isNull())
        {
            reopenedByUserid_=std::make_shared<std::string>(r["reopened_by_userid"].as<std::string>());
        }
        if(!r["email_address"].isNull())
        {
            emailAddress_=std::make_shared<std::string>(r["email_address"].as<std::string>());
        }
        if(!r["proposed_transfer_date"].isNull())
        {
            auto daysStr = r["proposed_transfer_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            proposedTransferDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        if(!r["created_by"].isNull())
        {
            createdBy_=std::make_shared<std::string>(r["created_by"].as<std::string>());
        }
        if(!r["created_at"].isNull())
        {
            auto timeStr = r["created_at"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["modified_by"].isNull())
        {
            modifiedBy_=std::make_shared<std::string>(r["modified_by"].as<std::string>());
        }
        if(!r["modified_at"].isNull())
        {
            auto timeStr = r["modified_at"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["kyc_status"].isNull())
        {
            kycStatus_=std::make_shared<int32_t>(r["kyc_status"].as<int32_t>());
        }
        if(!r["risk_rating"].isNull())
        {
            riskRating_=std::make_shared<int32_t>(r["risk_rating"].as<int32_t>());
        }
        if(!r["fatca_flag"].isNull())
        {
            fatcaFlag_=std::make_shared<bool>(r["fatca_flag"].as<bool>());
        }
        if(!r["crs_flag"].isNull())
        {
            crsFlag_=std::make_shared<bool>(r["crs_flag"].as<bool>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 53 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            businessId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            accountNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            externalId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            subStatus_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            activationDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            officeJoiningDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 8;
        if(!r[index].isNull())
        {
            officeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 9;
        if(!r[index].isNull())
        {
            transferToOfficeId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 10;
        if(!r[index].isNull())
        {
            staffId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 11;
        if(!r[index].isNull())
        {
            firstname_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 12;
        if(!r[index].isNull())
        {
            middlename_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 13;
        if(!r[index].isNull())
        {
            lastname_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 14;
        if(!r[index].isNull())
        {
            fullname_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 15;
        if(!r[index].isNull())
        {
            displayName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 16;
        if(!r[index].isNull())
        {
            mobileNo_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 17;
        if(!r[index].isNull())
        {
            isStaff_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 18;
        if(!r[index].isNull())
        {
            genderCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 19;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            dateOfBirth_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 20;
        if(!r[index].isNull())
        {
            imageId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 21;
        if(!r[index].isNull())
        {
            closureReasonCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 22;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            closedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 23;
        if(!r[index].isNull())
        {
            updatedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 24;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            updatedOn_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 25;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            submittedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 26;
        if(!r[index].isNull())
        {
            activatedonUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 27;
        if(!r[index].isNull())
        {
            closedonUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 28;
        if(!r[index].isNull())
        {
            defaultSavingsProduct_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 29;
        if(!r[index].isNull())
        {
            defaultSavingsAccount_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 30;
        if(!r[index].isNull())
        {
            clientTypeCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 31;
        if(!r[index].isNull())
        {
            clientClassificationCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 32;
        if(!r[index].isNull())
        {
            rejectReasonCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 33;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            rejectedonDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 34;
        if(!r[index].isNull())
        {
            rejectedonUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 35;
        if(!r[index].isNull())
        {
            withdrawReasonCvId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 36;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            withdrawnOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 37;
        if(!r[index].isNull())
        {
            withdrawOnUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 38;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            reactivatedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 39;
        if(!r[index].isNull())
        {
            reactivatedOnUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 40;
        if(!r[index].isNull())
        {
            legalStructure_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 41;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            reopenedOnDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 42;
        if(!r[index].isNull())
        {
            reopenedByUserid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 43;
        if(!r[index].isNull())
        {
            emailAddress_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 44;
        if(!r[index].isNull())
        {
            auto daysStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            strptime(daysStr.c_str(),"%Y-%m-%d",&stm);
            time_t t = mktime(&stm);
            proposedTransferDate_=std::make_shared<::trantor::Date>(t*1000000);
        }
        index = offset + 45;
        if(!r[index].isNull())
        {
            createdBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 46;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createdAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 47;
        if(!r[index].isNull())
        {
            modifiedBy_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 48;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                modifiedAt_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 49;
        if(!r[index].isNull())
        {
            kycStatus_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 50;
        if(!r[index].isNull())
        {
            riskRating_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 51;
        if(!r[index].isNull())
        {
            fatcaFlag_=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 52;
        if(!r[index].isNull())
        {
            crsFlag_=std::make_shared<bool>(r[index].as<bool>());
        }
    }

}
const std::string &Client::getValueOfId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getId() const noexcept
{
    return id_;
}
void Client::setId(const std::string &pId) noexcept
{
    id_ = std::make_shared<std::string>(pId);
    dirtyFlag_[0] = true;
}
void Client::setId(std::string &&pId) noexcept
{
    id_ = std::make_shared<std::string>(std::move(pId));
    dirtyFlag_[0] = true;
}
const typename Client::PrimaryKeyType & Client::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Client::getValueOfBusinessId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(businessId_)
        return *businessId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getBusinessId() const noexcept
{
    return businessId_;
}
void Client::setBusinessId(const std::string &pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(pBusinessId);
    dirtyFlag_[1] = true;
}
void Client::setBusinessId(std::string &&pBusinessId) noexcept
{
    businessId_ = std::make_shared<std::string>(std::move(pBusinessId));
    dirtyFlag_[1] = true;
}
void Client::setBusinessIdToNull() noexcept
{
    businessId_.reset();
    dirtyFlag_[1] = true;
}

const std::string &Client::getValueOfAccountNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(accountNo_)
        return *accountNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getAccountNo() const noexcept
{
    return accountNo_;
}
void Client::setAccountNo(const std::string &pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(pAccountNo);
    dirtyFlag_[2] = true;
}
void Client::setAccountNo(std::string &&pAccountNo) noexcept
{
    accountNo_ = std::make_shared<std::string>(std::move(pAccountNo));
    dirtyFlag_[2] = true;
}

const std::string &Client::getValueOfExternalId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(externalId_)
        return *externalId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getExternalId() const noexcept
{
    return externalId_;
}
void Client::setExternalId(const std::string &pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(pExternalId);
    dirtyFlag_[3] = true;
}
void Client::setExternalId(std::string &&pExternalId) noexcept
{
    externalId_ = std::make_shared<std::string>(std::move(pExternalId));
    dirtyFlag_[3] = true;
}
void Client::setExternalIdToNull() noexcept
{
    externalId_.reset();
    dirtyFlag_[3] = true;
}

const int32_t &Client::getValueOfStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Client::getStatus() const noexcept
{
    return status_;
}
void Client::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[4] = true;
}

const int32_t &Client::getValueOfSubStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(subStatus_)
        return *subStatus_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Client::getSubStatus() const noexcept
{
    return subStatus_;
}
void Client::setSubStatus(const int32_t &pSubStatus) noexcept
{
    subStatus_ = std::make_shared<int32_t>(pSubStatus);
    dirtyFlag_[5] = true;
}
void Client::setSubStatusToNull() noexcept
{
    subStatus_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &Client::getValueOfActivationDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(activationDate_)
        return *activationDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getActivationDate() const noexcept
{
    return activationDate_;
}
void Client::setActivationDate(const ::trantor::Date &pActivationDate) noexcept
{
    activationDate_ = std::make_shared<::trantor::Date>(pActivationDate);
    dirtyFlag_[6] = true;
}
void Client::setActivationDateToNull() noexcept
{
    activationDate_.reset();
    dirtyFlag_[6] = true;
}

const ::trantor::Date &Client::getValueOfOfficeJoiningDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(officeJoiningDate_)
        return *officeJoiningDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getOfficeJoiningDate() const noexcept
{
    return officeJoiningDate_;
}
void Client::setOfficeJoiningDate(const ::trantor::Date &pOfficeJoiningDate) noexcept
{
    officeJoiningDate_ = std::make_shared<::trantor::Date>(pOfficeJoiningDate);
    dirtyFlag_[7] = true;
}
void Client::setOfficeJoiningDateToNull() noexcept
{
    officeJoiningDate_.reset();
    dirtyFlag_[7] = true;
}

const std::string &Client::getValueOfOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(officeId_)
        return *officeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getOfficeId() const noexcept
{
    return officeId_;
}
void Client::setOfficeId(const std::string &pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(pOfficeId);
    dirtyFlag_[8] = true;
}
void Client::setOfficeId(std::string &&pOfficeId) noexcept
{
    officeId_ = std::make_shared<std::string>(std::move(pOfficeId));
    dirtyFlag_[8] = true;
}
void Client::setOfficeIdToNull() noexcept
{
    officeId_.reset();
    dirtyFlag_[8] = true;
}

const std::string &Client::getValueOfTransferToOfficeId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(transferToOfficeId_)
        return *transferToOfficeId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getTransferToOfficeId() const noexcept
{
    return transferToOfficeId_;
}
void Client::setTransferToOfficeId(const std::string &pTransferToOfficeId) noexcept
{
    transferToOfficeId_ = std::make_shared<std::string>(pTransferToOfficeId);
    dirtyFlag_[9] = true;
}
void Client::setTransferToOfficeId(std::string &&pTransferToOfficeId) noexcept
{
    transferToOfficeId_ = std::make_shared<std::string>(std::move(pTransferToOfficeId));
    dirtyFlag_[9] = true;
}
void Client::setTransferToOfficeIdToNull() noexcept
{
    transferToOfficeId_.reset();
    dirtyFlag_[9] = true;
}

const std::string &Client::getValueOfStaffId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(staffId_)
        return *staffId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getStaffId() const noexcept
{
    return staffId_;
}
void Client::setStaffId(const std::string &pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(pStaffId);
    dirtyFlag_[10] = true;
}
void Client::setStaffId(std::string &&pStaffId) noexcept
{
    staffId_ = std::make_shared<std::string>(std::move(pStaffId));
    dirtyFlag_[10] = true;
}
void Client::setStaffIdToNull() noexcept
{
    staffId_.reset();
    dirtyFlag_[10] = true;
}

const std::string &Client::getValueOfFirstname() const noexcept
{
    static const std::string defaultValue = std::string();
    if(firstname_)
        return *firstname_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getFirstname() const noexcept
{
    return firstname_;
}
void Client::setFirstname(const std::string &pFirstname) noexcept
{
    firstname_ = std::make_shared<std::string>(pFirstname);
    dirtyFlag_[11] = true;
}
void Client::setFirstname(std::string &&pFirstname) noexcept
{
    firstname_ = std::make_shared<std::string>(std::move(pFirstname));
    dirtyFlag_[11] = true;
}
void Client::setFirstnameToNull() noexcept
{
    firstname_.reset();
    dirtyFlag_[11] = true;
}

const std::string &Client::getValueOfMiddlename() const noexcept
{
    static const std::string defaultValue = std::string();
    if(middlename_)
        return *middlename_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getMiddlename() const noexcept
{
    return middlename_;
}
void Client::setMiddlename(const std::string &pMiddlename) noexcept
{
    middlename_ = std::make_shared<std::string>(pMiddlename);
    dirtyFlag_[12] = true;
}
void Client::setMiddlename(std::string &&pMiddlename) noexcept
{
    middlename_ = std::make_shared<std::string>(std::move(pMiddlename));
    dirtyFlag_[12] = true;
}
void Client::setMiddlenameToNull() noexcept
{
    middlename_.reset();
    dirtyFlag_[12] = true;
}

const std::string &Client::getValueOfLastname() const noexcept
{
    static const std::string defaultValue = std::string();
    if(lastname_)
        return *lastname_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getLastname() const noexcept
{
    return lastname_;
}
void Client::setLastname(const std::string &pLastname) noexcept
{
    lastname_ = std::make_shared<std::string>(pLastname);
    dirtyFlag_[13] = true;
}
void Client::setLastname(std::string &&pLastname) noexcept
{
    lastname_ = std::make_shared<std::string>(std::move(pLastname));
    dirtyFlag_[13] = true;
}
void Client::setLastnameToNull() noexcept
{
    lastname_.reset();
    dirtyFlag_[13] = true;
}

const std::string &Client::getValueOfFullname() const noexcept
{
    static const std::string defaultValue = std::string();
    if(fullname_)
        return *fullname_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getFullname() const noexcept
{
    return fullname_;
}
void Client::setFullname(const std::string &pFullname) noexcept
{
    fullname_ = std::make_shared<std::string>(pFullname);
    dirtyFlag_[14] = true;
}
void Client::setFullname(std::string &&pFullname) noexcept
{
    fullname_ = std::make_shared<std::string>(std::move(pFullname));
    dirtyFlag_[14] = true;
}
void Client::setFullnameToNull() noexcept
{
    fullname_.reset();
    dirtyFlag_[14] = true;
}

const std::string &Client::getValueOfDisplayName() const noexcept
{
    static const std::string defaultValue = std::string();
    if(displayName_)
        return *displayName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getDisplayName() const noexcept
{
    return displayName_;
}
void Client::setDisplayName(const std::string &pDisplayName) noexcept
{
    displayName_ = std::make_shared<std::string>(pDisplayName);
    dirtyFlag_[15] = true;
}
void Client::setDisplayName(std::string &&pDisplayName) noexcept
{
    displayName_ = std::make_shared<std::string>(std::move(pDisplayName));
    dirtyFlag_[15] = true;
}
void Client::setDisplayNameToNull() noexcept
{
    displayName_.reset();
    dirtyFlag_[15] = true;
}

const std::string &Client::getValueOfMobileNo() const noexcept
{
    static const std::string defaultValue = std::string();
    if(mobileNo_)
        return *mobileNo_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getMobileNo() const noexcept
{
    return mobileNo_;
}
void Client::setMobileNo(const std::string &pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(pMobileNo);
    dirtyFlag_[16] = true;
}
void Client::setMobileNo(std::string &&pMobileNo) noexcept
{
    mobileNo_ = std::make_shared<std::string>(std::move(pMobileNo));
    dirtyFlag_[16] = true;
}
void Client::setMobileNoToNull() noexcept
{
    mobileNo_.reset();
    dirtyFlag_[16] = true;
}

const bool &Client::getValueOfIsStaff() const noexcept
{
    static const bool defaultValue = bool();
    if(isStaff_)
        return *isStaff_;
    return defaultValue;
}
const std::shared_ptr<bool> &Client::getIsStaff() const noexcept
{
    return isStaff_;
}
void Client::setIsStaff(const bool &pIsStaff) noexcept
{
    isStaff_ = std::make_shared<bool>(pIsStaff);
    dirtyFlag_[17] = true;
}

const std::string &Client::getValueOfGenderCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(genderCvId_)
        return *genderCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getGenderCvId() const noexcept
{
    return genderCvId_;
}
void Client::setGenderCvId(const std::string &pGenderCvId) noexcept
{
    genderCvId_ = std::make_shared<std::string>(pGenderCvId);
    dirtyFlag_[18] = true;
}
void Client::setGenderCvId(std::string &&pGenderCvId) noexcept
{
    genderCvId_ = std::make_shared<std::string>(std::move(pGenderCvId));
    dirtyFlag_[18] = true;
}
void Client::setGenderCvIdToNull() noexcept
{
    genderCvId_.reset();
    dirtyFlag_[18] = true;
}

const ::trantor::Date &Client::getValueOfDateOfBirth() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(dateOfBirth_)
        return *dateOfBirth_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getDateOfBirth() const noexcept
{
    return dateOfBirth_;
}
void Client::setDateOfBirth(const ::trantor::Date &pDateOfBirth) noexcept
{
    dateOfBirth_ = std::make_shared<::trantor::Date>(pDateOfBirth);
    dirtyFlag_[19] = true;
}
void Client::setDateOfBirthToNull() noexcept
{
    dateOfBirth_.reset();
    dirtyFlag_[19] = true;
}

const std::string &Client::getValueOfImageId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(imageId_)
        return *imageId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getImageId() const noexcept
{
    return imageId_;
}
void Client::setImageId(const std::string &pImageId) noexcept
{
    imageId_ = std::make_shared<std::string>(pImageId);
    dirtyFlag_[20] = true;
}
void Client::setImageId(std::string &&pImageId) noexcept
{
    imageId_ = std::make_shared<std::string>(std::move(pImageId));
    dirtyFlag_[20] = true;
}
void Client::setImageIdToNull() noexcept
{
    imageId_.reset();
    dirtyFlag_[20] = true;
}

const std::string &Client::getValueOfClosureReasonCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(closureReasonCvId_)
        return *closureReasonCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getClosureReasonCvId() const noexcept
{
    return closureReasonCvId_;
}
void Client::setClosureReasonCvId(const std::string &pClosureReasonCvId) noexcept
{
    closureReasonCvId_ = std::make_shared<std::string>(pClosureReasonCvId);
    dirtyFlag_[21] = true;
}
void Client::setClosureReasonCvId(std::string &&pClosureReasonCvId) noexcept
{
    closureReasonCvId_ = std::make_shared<std::string>(std::move(pClosureReasonCvId));
    dirtyFlag_[21] = true;
}
void Client::setClosureReasonCvIdToNull() noexcept
{
    closureReasonCvId_.reset();
    dirtyFlag_[21] = true;
}

const ::trantor::Date &Client::getValueOfClosedonDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(closedonDate_)
        return *closedonDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getClosedonDate() const noexcept
{
    return closedonDate_;
}
void Client::setClosedonDate(const ::trantor::Date &pClosedonDate) noexcept
{
    closedonDate_ = std::make_shared<::trantor::Date>(pClosedonDate);
    dirtyFlag_[22] = true;
}
void Client::setClosedonDateToNull() noexcept
{
    closedonDate_.reset();
    dirtyFlag_[22] = true;
}

const std::string &Client::getValueOfUpdatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(updatedBy_)
        return *updatedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getUpdatedBy() const noexcept
{
    return updatedBy_;
}
void Client::setUpdatedBy(const std::string &pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(pUpdatedBy);
    dirtyFlag_[23] = true;
}
void Client::setUpdatedBy(std::string &&pUpdatedBy) noexcept
{
    updatedBy_ = std::make_shared<std::string>(std::move(pUpdatedBy));
    dirtyFlag_[23] = true;
}
void Client::setUpdatedByToNull() noexcept
{
    updatedBy_.reset();
    dirtyFlag_[23] = true;
}

const ::trantor::Date &Client::getValueOfUpdatedOn() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(updatedOn_)
        return *updatedOn_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getUpdatedOn() const noexcept
{
    return updatedOn_;
}
void Client::setUpdatedOn(const ::trantor::Date &pUpdatedOn) noexcept
{
    updatedOn_ = std::make_shared<::trantor::Date>(pUpdatedOn);
    dirtyFlag_[24] = true;
}
void Client::setUpdatedOnToNull() noexcept
{
    updatedOn_.reset();
    dirtyFlag_[24] = true;
}

const ::trantor::Date &Client::getValueOfSubmittedonDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(submittedonDate_)
        return *submittedonDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getSubmittedonDate() const noexcept
{
    return submittedonDate_;
}
void Client::setSubmittedonDate(const ::trantor::Date &pSubmittedonDate) noexcept
{
    submittedonDate_ = std::make_shared<::trantor::Date>(pSubmittedonDate);
    dirtyFlag_[25] = true;
}
void Client::setSubmittedonDateToNull() noexcept
{
    submittedonDate_.reset();
    dirtyFlag_[25] = true;
}

const std::string &Client::getValueOfActivatedonUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(activatedonUserid_)
        return *activatedonUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getActivatedonUserid() const noexcept
{
    return activatedonUserid_;
}
void Client::setActivatedonUserid(const std::string &pActivatedonUserid) noexcept
{
    activatedonUserid_ = std::make_shared<std::string>(pActivatedonUserid);
    dirtyFlag_[26] = true;
}
void Client::setActivatedonUserid(std::string &&pActivatedonUserid) noexcept
{
    activatedonUserid_ = std::make_shared<std::string>(std::move(pActivatedonUserid));
    dirtyFlag_[26] = true;
}
void Client::setActivatedonUseridToNull() noexcept
{
    activatedonUserid_.reset();
    dirtyFlag_[26] = true;
}

const std::string &Client::getValueOfClosedonUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(closedonUserid_)
        return *closedonUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getClosedonUserid() const noexcept
{
    return closedonUserid_;
}
void Client::setClosedonUserid(const std::string &pClosedonUserid) noexcept
{
    closedonUserid_ = std::make_shared<std::string>(pClosedonUserid);
    dirtyFlag_[27] = true;
}
void Client::setClosedonUserid(std::string &&pClosedonUserid) noexcept
{
    closedonUserid_ = std::make_shared<std::string>(std::move(pClosedonUserid));
    dirtyFlag_[27] = true;
}
void Client::setClosedonUseridToNull() noexcept
{
    closedonUserid_.reset();
    dirtyFlag_[27] = true;
}

const std::string &Client::getValueOfDefaultSavingsProduct() const noexcept
{
    static const std::string defaultValue = std::string();
    if(defaultSavingsProduct_)
        return *defaultSavingsProduct_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getDefaultSavingsProduct() const noexcept
{
    return defaultSavingsProduct_;
}
void Client::setDefaultSavingsProduct(const std::string &pDefaultSavingsProduct) noexcept
{
    defaultSavingsProduct_ = std::make_shared<std::string>(pDefaultSavingsProduct);
    dirtyFlag_[28] = true;
}
void Client::setDefaultSavingsProduct(std::string &&pDefaultSavingsProduct) noexcept
{
    defaultSavingsProduct_ = std::make_shared<std::string>(std::move(pDefaultSavingsProduct));
    dirtyFlag_[28] = true;
}
void Client::setDefaultSavingsProductToNull() noexcept
{
    defaultSavingsProduct_.reset();
    dirtyFlag_[28] = true;
}

const std::string &Client::getValueOfDefaultSavingsAccount() const noexcept
{
    static const std::string defaultValue = std::string();
    if(defaultSavingsAccount_)
        return *defaultSavingsAccount_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getDefaultSavingsAccount() const noexcept
{
    return defaultSavingsAccount_;
}
void Client::setDefaultSavingsAccount(const std::string &pDefaultSavingsAccount) noexcept
{
    defaultSavingsAccount_ = std::make_shared<std::string>(pDefaultSavingsAccount);
    dirtyFlag_[29] = true;
}
void Client::setDefaultSavingsAccount(std::string &&pDefaultSavingsAccount) noexcept
{
    defaultSavingsAccount_ = std::make_shared<std::string>(std::move(pDefaultSavingsAccount));
    dirtyFlag_[29] = true;
}
void Client::setDefaultSavingsAccountToNull() noexcept
{
    defaultSavingsAccount_.reset();
    dirtyFlag_[29] = true;
}

const std::string &Client::getValueOfClientTypeCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientTypeCvId_)
        return *clientTypeCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getClientTypeCvId() const noexcept
{
    return clientTypeCvId_;
}
void Client::setClientTypeCvId(const std::string &pClientTypeCvId) noexcept
{
    clientTypeCvId_ = std::make_shared<std::string>(pClientTypeCvId);
    dirtyFlag_[30] = true;
}
void Client::setClientTypeCvId(std::string &&pClientTypeCvId) noexcept
{
    clientTypeCvId_ = std::make_shared<std::string>(std::move(pClientTypeCvId));
    dirtyFlag_[30] = true;
}
void Client::setClientTypeCvIdToNull() noexcept
{
    clientTypeCvId_.reset();
    dirtyFlag_[30] = true;
}

const std::string &Client::getValueOfClientClassificationCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(clientClassificationCvId_)
        return *clientClassificationCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getClientClassificationCvId() const noexcept
{
    return clientClassificationCvId_;
}
void Client::setClientClassificationCvId(const std::string &pClientClassificationCvId) noexcept
{
    clientClassificationCvId_ = std::make_shared<std::string>(pClientClassificationCvId);
    dirtyFlag_[31] = true;
}
void Client::setClientClassificationCvId(std::string &&pClientClassificationCvId) noexcept
{
    clientClassificationCvId_ = std::make_shared<std::string>(std::move(pClientClassificationCvId));
    dirtyFlag_[31] = true;
}
void Client::setClientClassificationCvIdToNull() noexcept
{
    clientClassificationCvId_.reset();
    dirtyFlag_[31] = true;
}

const std::string &Client::getValueOfRejectReasonCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(rejectReasonCvId_)
        return *rejectReasonCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getRejectReasonCvId() const noexcept
{
    return rejectReasonCvId_;
}
void Client::setRejectReasonCvId(const std::string &pRejectReasonCvId) noexcept
{
    rejectReasonCvId_ = std::make_shared<std::string>(pRejectReasonCvId);
    dirtyFlag_[32] = true;
}
void Client::setRejectReasonCvId(std::string &&pRejectReasonCvId) noexcept
{
    rejectReasonCvId_ = std::make_shared<std::string>(std::move(pRejectReasonCvId));
    dirtyFlag_[32] = true;
}
void Client::setRejectReasonCvIdToNull() noexcept
{
    rejectReasonCvId_.reset();
    dirtyFlag_[32] = true;
}

const ::trantor::Date &Client::getValueOfRejectedonDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(rejectedonDate_)
        return *rejectedonDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getRejectedonDate() const noexcept
{
    return rejectedonDate_;
}
void Client::setRejectedonDate(const ::trantor::Date &pRejectedonDate) noexcept
{
    rejectedonDate_ = std::make_shared<::trantor::Date>(pRejectedonDate);
    dirtyFlag_[33] = true;
}
void Client::setRejectedonDateToNull() noexcept
{
    rejectedonDate_.reset();
    dirtyFlag_[33] = true;
}

const std::string &Client::getValueOfRejectedonUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(rejectedonUserid_)
        return *rejectedonUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getRejectedonUserid() const noexcept
{
    return rejectedonUserid_;
}
void Client::setRejectedonUserid(const std::string &pRejectedonUserid) noexcept
{
    rejectedonUserid_ = std::make_shared<std::string>(pRejectedonUserid);
    dirtyFlag_[34] = true;
}
void Client::setRejectedonUserid(std::string &&pRejectedonUserid) noexcept
{
    rejectedonUserid_ = std::make_shared<std::string>(std::move(pRejectedonUserid));
    dirtyFlag_[34] = true;
}
void Client::setRejectedonUseridToNull() noexcept
{
    rejectedonUserid_.reset();
    dirtyFlag_[34] = true;
}

const std::string &Client::getValueOfWithdrawReasonCvId() const noexcept
{
    static const std::string defaultValue = std::string();
    if(withdrawReasonCvId_)
        return *withdrawReasonCvId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getWithdrawReasonCvId() const noexcept
{
    return withdrawReasonCvId_;
}
void Client::setWithdrawReasonCvId(const std::string &pWithdrawReasonCvId) noexcept
{
    withdrawReasonCvId_ = std::make_shared<std::string>(pWithdrawReasonCvId);
    dirtyFlag_[35] = true;
}
void Client::setWithdrawReasonCvId(std::string &&pWithdrawReasonCvId) noexcept
{
    withdrawReasonCvId_ = std::make_shared<std::string>(std::move(pWithdrawReasonCvId));
    dirtyFlag_[35] = true;
}
void Client::setWithdrawReasonCvIdToNull() noexcept
{
    withdrawReasonCvId_.reset();
    dirtyFlag_[35] = true;
}

const ::trantor::Date &Client::getValueOfWithdrawnOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(withdrawnOnDate_)
        return *withdrawnOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getWithdrawnOnDate() const noexcept
{
    return withdrawnOnDate_;
}
void Client::setWithdrawnOnDate(const ::trantor::Date &pWithdrawnOnDate) noexcept
{
    withdrawnOnDate_ = std::make_shared<::trantor::Date>(pWithdrawnOnDate);
    dirtyFlag_[36] = true;
}
void Client::setWithdrawnOnDateToNull() noexcept
{
    withdrawnOnDate_.reset();
    dirtyFlag_[36] = true;
}

const std::string &Client::getValueOfWithdrawOnUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(withdrawOnUserid_)
        return *withdrawOnUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getWithdrawOnUserid() const noexcept
{
    return withdrawOnUserid_;
}
void Client::setWithdrawOnUserid(const std::string &pWithdrawOnUserid) noexcept
{
    withdrawOnUserid_ = std::make_shared<std::string>(pWithdrawOnUserid);
    dirtyFlag_[37] = true;
}
void Client::setWithdrawOnUserid(std::string &&pWithdrawOnUserid) noexcept
{
    withdrawOnUserid_ = std::make_shared<std::string>(std::move(pWithdrawOnUserid));
    dirtyFlag_[37] = true;
}
void Client::setWithdrawOnUseridToNull() noexcept
{
    withdrawOnUserid_.reset();
    dirtyFlag_[37] = true;
}

const ::trantor::Date &Client::getValueOfReactivatedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(reactivatedOnDate_)
        return *reactivatedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getReactivatedOnDate() const noexcept
{
    return reactivatedOnDate_;
}
void Client::setReactivatedOnDate(const ::trantor::Date &pReactivatedOnDate) noexcept
{
    reactivatedOnDate_ = std::make_shared<::trantor::Date>(pReactivatedOnDate);
    dirtyFlag_[38] = true;
}
void Client::setReactivatedOnDateToNull() noexcept
{
    reactivatedOnDate_.reset();
    dirtyFlag_[38] = true;
}

const std::string &Client::getValueOfReactivatedOnUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reactivatedOnUserid_)
        return *reactivatedOnUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getReactivatedOnUserid() const noexcept
{
    return reactivatedOnUserid_;
}
void Client::setReactivatedOnUserid(const std::string &pReactivatedOnUserid) noexcept
{
    reactivatedOnUserid_ = std::make_shared<std::string>(pReactivatedOnUserid);
    dirtyFlag_[39] = true;
}
void Client::setReactivatedOnUserid(std::string &&pReactivatedOnUserid) noexcept
{
    reactivatedOnUserid_ = std::make_shared<std::string>(std::move(pReactivatedOnUserid));
    dirtyFlag_[39] = true;
}
void Client::setReactivatedOnUseridToNull() noexcept
{
    reactivatedOnUserid_.reset();
    dirtyFlag_[39] = true;
}

const int32_t &Client::getValueOfLegalStructure() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(legalStructure_)
        return *legalStructure_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Client::getLegalStructure() const noexcept
{
    return legalStructure_;
}
void Client::setLegalStructure(const int32_t &pLegalStructure) noexcept
{
    legalStructure_ = std::make_shared<int32_t>(pLegalStructure);
    dirtyFlag_[40] = true;
}
void Client::setLegalStructureToNull() noexcept
{
    legalStructure_.reset();
    dirtyFlag_[40] = true;
}

const ::trantor::Date &Client::getValueOfReopenedOnDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(reopenedOnDate_)
        return *reopenedOnDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getReopenedOnDate() const noexcept
{
    return reopenedOnDate_;
}
void Client::setReopenedOnDate(const ::trantor::Date &pReopenedOnDate) noexcept
{
    reopenedOnDate_ = std::make_shared<::trantor::Date>(pReopenedOnDate);
    dirtyFlag_[41] = true;
}
void Client::setReopenedOnDateToNull() noexcept
{
    reopenedOnDate_.reset();
    dirtyFlag_[41] = true;
}

const std::string &Client::getValueOfReopenedByUserid() const noexcept
{
    static const std::string defaultValue = std::string();
    if(reopenedByUserid_)
        return *reopenedByUserid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getReopenedByUserid() const noexcept
{
    return reopenedByUserid_;
}
void Client::setReopenedByUserid(const std::string &pReopenedByUserid) noexcept
{
    reopenedByUserid_ = std::make_shared<std::string>(pReopenedByUserid);
    dirtyFlag_[42] = true;
}
void Client::setReopenedByUserid(std::string &&pReopenedByUserid) noexcept
{
    reopenedByUserid_ = std::make_shared<std::string>(std::move(pReopenedByUserid));
    dirtyFlag_[42] = true;
}
void Client::setReopenedByUseridToNull() noexcept
{
    reopenedByUserid_.reset();
    dirtyFlag_[42] = true;
}

const std::string &Client::getValueOfEmailAddress() const noexcept
{
    static const std::string defaultValue = std::string();
    if(emailAddress_)
        return *emailAddress_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getEmailAddress() const noexcept
{
    return emailAddress_;
}
void Client::setEmailAddress(const std::string &pEmailAddress) noexcept
{
    emailAddress_ = std::make_shared<std::string>(pEmailAddress);
    dirtyFlag_[43] = true;
}
void Client::setEmailAddress(std::string &&pEmailAddress) noexcept
{
    emailAddress_ = std::make_shared<std::string>(std::move(pEmailAddress));
    dirtyFlag_[43] = true;
}
void Client::setEmailAddressToNull() noexcept
{
    emailAddress_.reset();
    dirtyFlag_[43] = true;
}

const ::trantor::Date &Client::getValueOfProposedTransferDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(proposedTransferDate_)
        return *proposedTransferDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getProposedTransferDate() const noexcept
{
    return proposedTransferDate_;
}
void Client::setProposedTransferDate(const ::trantor::Date &pProposedTransferDate) noexcept
{
    proposedTransferDate_ = std::make_shared<::trantor::Date>(pProposedTransferDate);
    dirtyFlag_[44] = true;
}
void Client::setProposedTransferDateToNull() noexcept
{
    proposedTransferDate_.reset();
    dirtyFlag_[44] = true;
}

const std::string &Client::getValueOfCreatedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(createdBy_)
        return *createdBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getCreatedBy() const noexcept
{
    return createdBy_;
}
void Client::setCreatedBy(const std::string &pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(pCreatedBy);
    dirtyFlag_[45] = true;
}
void Client::setCreatedBy(std::string &&pCreatedBy) noexcept
{
    createdBy_ = std::make_shared<std::string>(std::move(pCreatedBy));
    dirtyFlag_[45] = true;
}
void Client::setCreatedByToNull() noexcept
{
    createdBy_.reset();
    dirtyFlag_[45] = true;
}

const ::trantor::Date &Client::getValueOfCreatedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(createdAt_)
        return *createdAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getCreatedAt() const noexcept
{
    return createdAt_;
}
void Client::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    createdAt_ = std::make_shared<::trantor::Date>(pCreatedAt);
    dirtyFlag_[46] = true;
}
void Client::setCreatedAtToNull() noexcept
{
    createdAt_.reset();
    dirtyFlag_[46] = true;
}

const std::string &Client::getValueOfModifiedBy() const noexcept
{
    static const std::string defaultValue = std::string();
    if(modifiedBy_)
        return *modifiedBy_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Client::getModifiedBy() const noexcept
{
    return modifiedBy_;
}
void Client::setModifiedBy(const std::string &pModifiedBy) noexcept
{
    modifiedBy_ = std::make_shared<std::string>(pModifiedBy);
    dirtyFlag_[47] = true;
}
void Client::setModifiedBy(std::string &&pModifiedBy) noexcept
{
    modifiedBy_ = std::make_shared<std::string>(std::move(pModifiedBy));
    dirtyFlag_[47] = true;
}
void Client::setModifiedByToNull() noexcept
{
    modifiedBy_.reset();
    dirtyFlag_[47] = true;
}

const ::trantor::Date &Client::getValueOfModifiedAt() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(modifiedAt_)
        return *modifiedAt_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Client::getModifiedAt() const noexcept
{
    return modifiedAt_;
}
void Client::setModifiedAt(const ::trantor::Date &pModifiedAt) noexcept
{
    modifiedAt_ = std::make_shared<::trantor::Date>(pModifiedAt);
    dirtyFlag_[48] = true;
}
void Client::setModifiedAtToNull() noexcept
{
    modifiedAt_.reset();
    dirtyFlag_[48] = true;
}

const int32_t &Client::getValueOfKycStatus() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(kycStatus_)
        return *kycStatus_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Client::getKycStatus() const noexcept
{
    return kycStatus_;
}
void Client::setKycStatus(const int32_t &pKycStatus) noexcept
{
    kycStatus_ = std::make_shared<int32_t>(pKycStatus);
    dirtyFlag_[49] = true;
}

const int32_t &Client::getValueOfRiskRating() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(riskRating_)
        return *riskRating_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Client::getRiskRating() const noexcept
{
    return riskRating_;
}
void Client::setRiskRating(const int32_t &pRiskRating) noexcept
{
    riskRating_ = std::make_shared<int32_t>(pRiskRating);
    dirtyFlag_[50] = true;
}

const bool &Client::getValueOfFatcaFlag() const noexcept
{
    static const bool defaultValue = bool();
    if(fatcaFlag_)
        return *fatcaFlag_;
    return defaultValue;
}
const std::shared_ptr<bool> &Client::getFatcaFlag() const noexcept
{
    return fatcaFlag_;
}
void Client::setFatcaFlag(const bool &pFatcaFlag) noexcept
{
    fatcaFlag_ = std::make_shared<bool>(pFatcaFlag);
    dirtyFlag_[51] = true;
}

const bool &Client::getValueOfCrsFlag() const noexcept
{
    static const bool defaultValue = bool();
    if(crsFlag_)
        return *crsFlag_;
    return defaultValue;
}
const std::shared_ptr<bool> &Client::getCrsFlag() const noexcept
{
    return crsFlag_;
}
void Client::setCrsFlag(const bool &pCrsFlag) noexcept
{
    crsFlag_ = std::make_shared<bool>(pCrsFlag);
    dirtyFlag_[52] = true;
}

void Client::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Client::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "id",
        "business_id",
        "account_no",
        "external_id",
        "status",
        "sub_status",
        "activation_date",
        "office_joining_date",
        "office_id",
        "transfer_to_office_id",
        "staff_id",
        "firstname",
        "middlename",
        "lastname",
        "fullname",
        "display_name",
        "mobile_no",
        "is_staff",
        "gender_cv_id",
        "date_of_birth",
        "image_id",
        "closure_reason_cv_id",
        "closedon_date",
        "updated_by",
        "updated_on",
        "submittedon_date",
        "activatedon_userid",
        "closedon_userid",
        "default_savings_product",
        "default_savings_account",
        "client_type_cv_id",
        "client_classification_cv_id",
        "reject_reason_cv_id",
        "rejectedon_date",
        "rejectedon_userid",
        "withdraw_reason_cv_id",
        "withdrawn_on_date",
        "withdraw_on_userid",
        "reactivated_on_date",
        "reactivated_on_userid",
        "legal_structure",
        "reopened_on_date",
        "reopened_by_userid",
        "email_address",
        "proposed_transfer_date",
        "created_by",
        "created_at",
        "modified_by",
        "modified_at",
        "kyc_status",
        "risk_rating",
        "fatca_flag",
        "crs_flag"
    };
    return inCols;
}

void Client::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getSubStatus())
        {
            binder << getValueOfSubStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getActivationDate())
        {
            binder << getValueOfActivationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getOfficeJoiningDate())
        {
            binder << getValueOfOfficeJoiningDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getTransferToOfficeId())
        {
            binder << getValueOfTransferToOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getStaffId())
        {
            binder << getValueOfStaffId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getFirstname())
        {
            binder << getValueOfFirstname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getMiddlename())
        {
            binder << getValueOfMiddlename();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getLastname())
        {
            binder << getValueOfLastname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getFullname())
        {
            binder << getValueOfFullname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getDisplayName())
        {
            binder << getValueOfDisplayName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getMobileNo())
        {
            binder << getValueOfMobileNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getIsStaff())
        {
            binder << getValueOfIsStaff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getGenderCvId())
        {
            binder << getValueOfGenderCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getDateOfBirth())
        {
            binder << getValueOfDateOfBirth();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getImageId())
        {
            binder << getValueOfImageId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getClosureReasonCvId())
        {
            binder << getValueOfClosureReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getClosedonDate())
        {
            binder << getValueOfClosedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getUpdatedOn())
        {
            binder << getValueOfUpdatedOn();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getSubmittedonDate())
        {
            binder << getValueOfSubmittedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getActivatedonUserid())
        {
            binder << getValueOfActivatedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
    {
        if(getClosedonUserid())
        {
            binder << getValueOfClosedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
    {
        if(getDefaultSavingsProduct())
        {
            binder << getValueOfDefaultSavingsProduct();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getDefaultSavingsAccount())
        {
            binder << getValueOfDefaultSavingsAccount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getClientTypeCvId())
        {
            binder << getValueOfClientTypeCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getClientClassificationCvId())
        {
            binder << getValueOfClientClassificationCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getRejectReasonCvId())
        {
            binder << getValueOfRejectReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getRejectedonDate())
        {
            binder << getValueOfRejectedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getRejectedonUserid())
        {
            binder << getValueOfRejectedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
    {
        if(getWithdrawReasonCvId())
        {
            binder << getValueOfWithdrawReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
    {
        if(getWithdrawnOnDate())
        {
            binder << getValueOfWithdrawnOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
    {
        if(getWithdrawOnUserid())
        {
            binder << getValueOfWithdrawOnUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getReactivatedOnDate())
        {
            binder << getValueOfReactivatedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getReactivatedOnUserid())
        {
            binder << getValueOfReactivatedOnUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getLegalStructure())
        {
            binder << getValueOfLegalStructure();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
    {
        if(getReopenedOnDate())
        {
            binder << getValueOfReopenedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getReopenedByUserid())
        {
            binder << getValueOfReopenedByUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getEmailAddress())
        {
            binder << getValueOfEmailAddress();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getProposedTransferDate())
        {
            binder << getValueOfProposedTransferDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getModifiedBy())
        {
            binder << getValueOfModifiedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getKycStatus())
        {
            binder << getValueOfKycStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getRiskRating())
        {
            binder << getValueOfRiskRating();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getFatcaFlag())
        {
            binder << getValueOfFatcaFlag();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getCrsFlag())
        {
            binder << getValueOfCrsFlag();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Client::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    if(dirtyFlag_[6])
    {
        ret.push_back(getColumnName(6));
    }
    if(dirtyFlag_[7])
    {
        ret.push_back(getColumnName(7));
    }
    if(dirtyFlag_[8])
    {
        ret.push_back(getColumnName(8));
    }
    if(dirtyFlag_[9])
    {
        ret.push_back(getColumnName(9));
    }
    if(dirtyFlag_[10])
    {
        ret.push_back(getColumnName(10));
    }
    if(dirtyFlag_[11])
    {
        ret.push_back(getColumnName(11));
    }
    if(dirtyFlag_[12])
    {
        ret.push_back(getColumnName(12));
    }
    if(dirtyFlag_[13])
    {
        ret.push_back(getColumnName(13));
    }
    if(dirtyFlag_[14])
    {
        ret.push_back(getColumnName(14));
    }
    if(dirtyFlag_[15])
    {
        ret.push_back(getColumnName(15));
    }
    if(dirtyFlag_[16])
    {
        ret.push_back(getColumnName(16));
    }
    if(dirtyFlag_[17])
    {
        ret.push_back(getColumnName(17));
    }
    if(dirtyFlag_[18])
    {
        ret.push_back(getColumnName(18));
    }
    if(dirtyFlag_[19])
    {
        ret.push_back(getColumnName(19));
    }
    if(dirtyFlag_[20])
    {
        ret.push_back(getColumnName(20));
    }
    if(dirtyFlag_[21])
    {
        ret.push_back(getColumnName(21));
    }
    if(dirtyFlag_[22])
    {
        ret.push_back(getColumnName(22));
    }
    if(dirtyFlag_[23])
    {
        ret.push_back(getColumnName(23));
    }
    if(dirtyFlag_[24])
    {
        ret.push_back(getColumnName(24));
    }
    if(dirtyFlag_[25])
    {
        ret.push_back(getColumnName(25));
    }
    if(dirtyFlag_[26])
    {
        ret.push_back(getColumnName(26));
    }
    if(dirtyFlag_[27])
    {
        ret.push_back(getColumnName(27));
    }
    if(dirtyFlag_[28])
    {
        ret.push_back(getColumnName(28));
    }
    if(dirtyFlag_[29])
    {
        ret.push_back(getColumnName(29));
    }
    if(dirtyFlag_[30])
    {
        ret.push_back(getColumnName(30));
    }
    if(dirtyFlag_[31])
    {
        ret.push_back(getColumnName(31));
    }
    if(dirtyFlag_[32])
    {
        ret.push_back(getColumnName(32));
    }
    if(dirtyFlag_[33])
    {
        ret.push_back(getColumnName(33));
    }
    if(dirtyFlag_[34])
    {
        ret.push_back(getColumnName(34));
    }
    if(dirtyFlag_[35])
    {
        ret.push_back(getColumnName(35));
    }
    if(dirtyFlag_[36])
    {
        ret.push_back(getColumnName(36));
    }
    if(dirtyFlag_[37])
    {
        ret.push_back(getColumnName(37));
    }
    if(dirtyFlag_[38])
    {
        ret.push_back(getColumnName(38));
    }
    if(dirtyFlag_[39])
    {
        ret.push_back(getColumnName(39));
    }
    if(dirtyFlag_[40])
    {
        ret.push_back(getColumnName(40));
    }
    if(dirtyFlag_[41])
    {
        ret.push_back(getColumnName(41));
    }
    if(dirtyFlag_[42])
    {
        ret.push_back(getColumnName(42));
    }
    if(dirtyFlag_[43])
    {
        ret.push_back(getColumnName(43));
    }
    if(dirtyFlag_[44])
    {
        ret.push_back(getColumnName(44));
    }
    if(dirtyFlag_[45])
    {
        ret.push_back(getColumnName(45));
    }
    if(dirtyFlag_[46])
    {
        ret.push_back(getColumnName(46));
    }
    if(dirtyFlag_[47])
    {
        ret.push_back(getColumnName(47));
    }
    if(dirtyFlag_[48])
    {
        ret.push_back(getColumnName(48));
    }
    if(dirtyFlag_[49])
    {
        ret.push_back(getColumnName(49));
    }
    if(dirtyFlag_[50])
    {
        ret.push_back(getColumnName(50));
    }
    if(dirtyFlag_[51])
    {
        ret.push_back(getColumnName(51));
    }
    if(dirtyFlag_[52])
    {
        ret.push_back(getColumnName(52));
    }
    return ret;
}

void Client::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getBusinessId())
        {
            binder << getValueOfBusinessId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getAccountNo())
        {
            binder << getValueOfAccountNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getExternalId())
        {
            binder << getValueOfExternalId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getSubStatus())
        {
            binder << getValueOfSubStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getActivationDate())
        {
            binder << getValueOfActivationDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getOfficeJoiningDate())
        {
            binder << getValueOfOfficeJoiningDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[8])
    {
        if(getOfficeId())
        {
            binder << getValueOfOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[9])
    {
        if(getTransferToOfficeId())
        {
            binder << getValueOfTransferToOfficeId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[10])
    {
        if(getStaffId())
        {
            binder << getValueOfStaffId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[11])
    {
        if(getFirstname())
        {
            binder << getValueOfFirstname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[12])
    {
        if(getMiddlename())
        {
            binder << getValueOfMiddlename();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[13])
    {
        if(getLastname())
        {
            binder << getValueOfLastname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[14])
    {
        if(getFullname())
        {
            binder << getValueOfFullname();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[15])
    {
        if(getDisplayName())
        {
            binder << getValueOfDisplayName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[16])
    {
        if(getMobileNo())
        {
            binder << getValueOfMobileNo();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[17])
    {
        if(getIsStaff())
        {
            binder << getValueOfIsStaff();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[18])
    {
        if(getGenderCvId())
        {
            binder << getValueOfGenderCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[19])
    {
        if(getDateOfBirth())
        {
            binder << getValueOfDateOfBirth();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[20])
    {
        if(getImageId())
        {
            binder << getValueOfImageId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[21])
    {
        if(getClosureReasonCvId())
        {
            binder << getValueOfClosureReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[22])
    {
        if(getClosedonDate())
        {
            binder << getValueOfClosedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[23])
    {
        if(getUpdatedBy())
        {
            binder << getValueOfUpdatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[24])
    {
        if(getUpdatedOn())
        {
            binder << getValueOfUpdatedOn();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[25])
    {
        if(getSubmittedonDate())
        {
            binder << getValueOfSubmittedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[26])
    {
        if(getActivatedonUserid())
        {
            binder << getValueOfActivatedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[27])
    {
        if(getClosedonUserid())
        {
            binder << getValueOfClosedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[28])
    {
        if(getDefaultSavingsProduct())
        {
            binder << getValueOfDefaultSavingsProduct();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[29])
    {
        if(getDefaultSavingsAccount())
        {
            binder << getValueOfDefaultSavingsAccount();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[30])
    {
        if(getClientTypeCvId())
        {
            binder << getValueOfClientTypeCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[31])
    {
        if(getClientClassificationCvId())
        {
            binder << getValueOfClientClassificationCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[32])
    {
        if(getRejectReasonCvId())
        {
            binder << getValueOfRejectReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[33])
    {
        if(getRejectedonDate())
        {
            binder << getValueOfRejectedonDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[34])
    {
        if(getRejectedonUserid())
        {
            binder << getValueOfRejectedonUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[35])
    {
        if(getWithdrawReasonCvId())
        {
            binder << getValueOfWithdrawReasonCvId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[36])
    {
        if(getWithdrawnOnDate())
        {
            binder << getValueOfWithdrawnOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[37])
    {
        if(getWithdrawOnUserid())
        {
            binder << getValueOfWithdrawOnUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[38])
    {
        if(getReactivatedOnDate())
        {
            binder << getValueOfReactivatedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[39])
    {
        if(getReactivatedOnUserid())
        {
            binder << getValueOfReactivatedOnUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[40])
    {
        if(getLegalStructure())
        {
            binder << getValueOfLegalStructure();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[41])
    {
        if(getReopenedOnDate())
        {
            binder << getValueOfReopenedOnDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[42])
    {
        if(getReopenedByUserid())
        {
            binder << getValueOfReopenedByUserid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[43])
    {
        if(getEmailAddress())
        {
            binder << getValueOfEmailAddress();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[44])
    {
        if(getProposedTransferDate())
        {
            binder << getValueOfProposedTransferDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[45])
    {
        if(getCreatedBy())
        {
            binder << getValueOfCreatedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[46])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[47])
    {
        if(getModifiedBy())
        {
            binder << getValueOfModifiedBy();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[48])
    {
        if(getModifiedAt())
        {
            binder << getValueOfModifiedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[49])
    {
        if(getKycStatus())
        {
            binder << getValueOfKycStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[50])
    {
        if(getRiskRating())
        {
            binder << getValueOfRiskRating();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[51])
    {
        if(getFatcaFlag())
        {
            binder << getValueOfFatcaFlag();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[52])
    {
        if(getCrsFlag())
        {
            binder << getValueOfCrsFlag();
        }
        else
        {
            binder << nullptr;
        }
    }
}
