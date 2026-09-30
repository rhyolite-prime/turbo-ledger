cmake_minimum_required(VERSION 3.16)
project(turbo CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fcoroutines)
endif()

find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(turbo STATIC
        src/RequestContext.cc
        src/ContextCodec.cc
        src/Money.cc
        src/Pagination.cc
        src/TenantDb.cc
        src/Outbox.cc
        src/Ids.cc
        src/Health.cc
        src/filters/TrustedContextFilter.cc
)
add_library(turbo::turbo ALIAS turbo)

target_include_directories(turbo PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(turbo PUBLIC Drogon::Drogon OpenSSL::Crypto)

# ------------------------------------------------------------------ tests ----
option(TL_BUILD_TESTS "Build turbo library unit tests" ON)
if(TL_BUILD_TESTS)
    enable_testing()
    add_executable(turbo_tests tests/turbo_tests.cc)
    target_link_libraries(turbo_tests PRIVATE turbo)
    add_test(NAME turbo_tests COMMAND turbo_tests)
endif()
