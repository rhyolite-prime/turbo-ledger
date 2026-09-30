# Turbo Ledger — superbuild.
#
#   cmake -B build -G Ninja
#   cmake --build build -j
#   ctest --test-dir build
#
# Options:
#   -DTL_SERVICES="Identity;Accounting;ApiGateway"   services to build (default below)
#   -DTL_BUILD_TESTS=ON                              build libturbo unit tests
#
cmake_minimum_required(VERSION 3.16)
project(TurboLedger CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

option(TL_BUILD_TESTS "Build unit tests" ON)

# Services built by default in Phase 0. Add more as they are implemented,
# e.g. -DTL_SERVICES="Identity;Accounting;ApiGateway;Provisioner;Customer".
set(TL_SERVICES "Identity;Accounting;ApiGateway;Provisioner;Organization;SystemConfig;Customer" CACHE STRING
    "Semicolon-separated list of services to build")

# Shared platform library first.
add_subdirectory(src/libs/turbo)

foreach(service IN LISTS TL_SERVICES)
    set(_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/services/${service}")
    if(EXISTS "${_dir}/CMakeLists.txt")
        message(STATUS "TurboLedger: building service ${service}")
        add_subdirectory("${_dir}")
    else()
        message(WARNING "TurboLedger: service '${service}' not found at ${_dir}")
    endif()
endforeach()
