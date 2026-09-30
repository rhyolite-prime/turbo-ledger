cmake_minimum_required(VERSION 3.5)
project(Customer CXX)

include(CheckIncludeFileCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options("-include" "${CMAKE_CURRENT_SOURCE_DIR}/utils/codecvt_helper.h" "-Wno-deprecated-declarations")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fcoroutines)
endif()



add_executable(${PROJECT_NAME} main.cc
        controllers/ClientsController.h
        controllers/SelfController.h
        services/dam/DamApi.h
        services/identity/IdentityApi.h
        services/office/OfficeApi.h
        services/portfolio/PortfolioApi.h
        services/client/ClientService.h
        services/client/ClientService.cc
        dto/BaseApiResponse.h
        dto/ClientDto.h
        constants/LegalForm.h
        constants/ErrorCodes.h
        plugins/CustomerServicePlugin.h
        constants/ClientStatus.h
        dto/CloseClientDto.h
        dto/ActivateClientDto.h
        dto/RejectClientDto.h
        dto/ReactivateClientDto.h
        dto/UndoRejectOrWithdrawalClientDto.h
        dto/WithdrawClientDto.h
        dto/AssignStaffToClientDto.h
        dto/UpdateDefaultSavingsAccountDto.h
        dto/ProposeClientTransferDto.h
        dto/WithdrawOrRejectClientTransferDto.h
        dto/AcceptClientTransferDto.h
        dto/ProposeAndAcceptClientTransferDto.h
        dto/ClientAddressDto.h
        dto/ClientIdentifierDto.h
        dto/ClientChargeDto.h
        dto/PayClientChargeDto.h
        utils/codecvt_helper.h
        services/identity/IdentityApi.cc
        services/redis/RedisCacheManager.h
        services/redis/RedisCacheManager.cc
        dto/StandingInstructionDto.h
        dto/AccountTransferDto.h
)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon bcrypt OpenSSL::SSL OpenSSL::Crypto)

# ##############################################################################

if (CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})
# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)
# use the following line to create views with namespace CHANGE_ME prefixed
# and path namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE CHANGE_ME)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC})
# ##############################################################################
# uncomment the following line for dynamically loading views 
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################

# Shared external dependencies (services/external_deps/)
set(SHARED_EXTERNAL_DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../external_deps")

# Your intentional/canonical Bcrypt
if(NOT TARGET bcrypt)
    add_subdirectory(
            ${SHARED_EXTERNAL_DEPS_DIR}/Bcrypt
            external_deps/Bcrypt
    )
endif()

# jwt-cpp
set(USE_EXTERNAL_BCRYPT ON CACHE BOOL "" FORCE)

if(NOT TARGET jwt-cpp)
    add_subdirectory(
            ${SHARED_EXTERNAL_DEPS_DIR}/jwt-cpp
            external_deps/jwt-cpp
    )
endif()

# Add the include directory for jwt-cpp
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/models
        ${SHARED_EXTERNAL_DEPS_DIR}/jwt-cpp/include  # Add this line
)