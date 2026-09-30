cmake_minimum_required(VERSION 3.10)
project(Provisioner CXX)

include(CheckIncludeFileCXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GCC < 13 needs -fcoroutines even in C++20/23 mode; GCC >= 13 and Clang enable
# coroutines automatically (and Clang rejects the flag).
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    add_compile_options(-fcoroutines)
endif()

add_executable(${PROJECT_NAME} main.cc)

find_package(Drogon CONFIG REQUIRED)

# Shared platform library (libturbo)
if(NOT TARGET turbo)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/turbo turbo_build)
endif()

# Shared external dependencies (Bcrypt with FetchContent fallback)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/TurboExternalDeps.cmake)
turbo_require_bcrypt(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon turbo::turbo)

if (CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++${CMAKE_CXX_STANDARD}")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(services SERVICE_SRC)

target_sources(${PROJECT_NAME} PRIVATE ${CTL_SRC} ${SERVICE_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
