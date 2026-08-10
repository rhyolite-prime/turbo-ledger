cmake_minimum_required(VERSION 3.5)
project(Identity CXX)

include(CheckIncludeFileCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fcoroutines)
endif()

add_compile_options("-include" "${CMAKE_CURRENT_SOURCE_DIR}/utils/codecvt_helper.h" "-Wno-deprecated-declarations")

add_executable(${PROJECT_NAME} main.cc
        dto/BaseApiResponse.h
        constants/ErrorCodes.h
        services/users/UserService.h
        services/users/UserService.cc
        services/roles/RoleService.h
        services/roles/RoleService.cc
        services/api_keys/ApiKeyService.h
        services/business_accounts/BusinessAccountService.h
        services/business_accounts/BusinessAccountService.cc
        dto/BusinessAccountDto.h
        constants/StatusType.h
        utils/JsonUtils.h
        services/audit_logs/AuditLogService.h
        services/audit_logs/AuditLogService.cc
        services/audit_logs/AuditScope.h
        services/audit_logs/AuditScope.cc
        dto/ApiKeyDto.h
        services/api_keys/ApiKeyService.cc
        utils/IdGeneratorUtils.h
        utils/IdGeneratorUtils.cc
        dto/RoleDto.h
        dto/UserDto.h
        dto/SigninDto.h
        utils/PasswordUtils.h
        utils/PasswordUtils.cc
        utils/codecvt_helper.h
        dto/UserIdentityDto.h
        services/redis/RedisCacheManager.h
        services/redis/RedisCacheManager.cc
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
add_subdirectory(external_deps/Bcrypt.cpp)
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
aux_source_directory(constants PLUGIN_SRC)
aux_source_directory(services/users SERVICE_SRC)
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
               ${SERVICE_SRC}
               ${CONSTANTS_SRC}
               ${MODEL_SRC})
# ##############################################################################
# uncomment the following line for dynamically loading views 
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################

add_subdirectory(test)
