cmake_minimum_required(VERSION 3.16)
project(ApiGateway CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
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
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon turbo::turbo OpenSSL::SSL OpenSSL::Crypto)

aux_source_directory(test TEST_SRC)
if(TEST_SRC)
    # legacy scaffold tests folder is kept but not built by default
endif()
