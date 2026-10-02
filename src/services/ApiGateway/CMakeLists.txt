cmake_minimum_required(VERSION 3.16)
project(ApiGateway CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GCC < 13 needs -fcoroutines even in C++20/23 mode; GCC >= 13 and Clang enable
# coroutines automatically (and Clang rejects the flag).
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    add_compile_options(-fcoroutines)
endif()

add_executable(${PROJECT_NAME} main.cc
        src/GatewayCore.h
        src/GatewayCore.cc
        src/TenantRegistry.h
        src/TenantRegistry.cc
        src/RateLimiter.h
        src/RateLimiter.cc
        src/IdempotencyStore.h
        src/IdempotencyStore.cc
)

find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# Shared platform library (libturbo)
if(NOT TARGET turbo)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/turbo turbo_build)
endif()

# Shared external deps (jwt-cpp)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/TurboExternalDeps.cmake)
turbo_require_jwt_cpp(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# turbo::turbo already publicly links Drogon::Drogon and OpenSSL::Crypto;
# don't relist them here or the linker will see libdrogon.a twice.
target_link_libraries(${PROJECT_NAME} PRIVATE turbo::turbo OpenSSL::SSL)

aux_source_directory(test TEST_SRC)
if(TEST_SRC)
    # legacy scaffold tests folder is kept but not built by default
endif()
