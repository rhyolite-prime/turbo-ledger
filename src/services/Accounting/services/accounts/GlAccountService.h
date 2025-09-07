//
// Created by Emmanuel Addo-Odame on 06/09/2025.
//

#pragma once

#ifndef GLACCOUNTSERVICE_H
#define GLACCOUNTSERVICE_H

#include "dto/BaseApiResponse.h"
#include "dto/CreateGlAccountDto.h"
#include "dto/UpdateGlAccountDto.h"

namespace turbo_ledger_accounting::services {

    class GlAccountService {

        public:

        /**
         * @param pageNo The page number (0-based).
         * @param pageSize The number of users per page.
         * @param query Optional search query to filter users.
         * @param callback The callback function to handle the response.
         */

        void getGlAccounts(
            int pageNo,
            int pageSize,
            const std::string& query,
            const std::function<void(const dto::BaseApiResponse&)>& callback
        );

        void createGlAccount(
           const dto::CreateGlAccountDto& glAccountDto,
           const std::function<void(const dto::BaseApiResponse&)>& callback
       );

        void UpdateGlAccount(
           const dto::UpdateGlAccountDto& glAccountDto,
           const std::function<void(const dto::BaseApiResponse&)>& callback
       );

        void activateGlAccount(
           const std::string& id,
           const std::function<void(const dto::BaseApiResponse&)>& callback
       );

        void deactivateGlAccount(
            const std::string& id,
            const std::function<void(const dto::BaseApiResponse&)>& callback
        );

        void deleteGlAccount(
            const std::string& id,
            const std::function<void(const dto::BaseApiResponse&)>& callback
        );

    };

}

#endif //GLACCOUNTSERVICE_H
