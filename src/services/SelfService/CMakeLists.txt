cmake_minimum_required(VERSION 3.10)
project(SelfService CXX)

include(CheckIncludeFileCXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GCC < 13 needs -fcoroutines even in C++20/23 mode; GCC >= 13 and Clang enable
# coroutines automatically (and Clang rejects the flag).
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    add_compile_options(-fcoroutines)
endif()

add_compile_options("-include" "${CMAKE_CURRENT_SOURCE_DIR}/utils/codecvt_helper.h" "-Wno-deprecated-declarations")

add_executable(${PROJECT_NAME} main.cc
        services/SelfServiceService.h
        services/SelfServiceService.cc
        utils/codecvt_helper.h)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon
# add_subdirectory(drogon)
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# Shared platform library (libturbo)
if(NOT TARGET turbo)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/turbo turbo_build)
endif()

# turbo::turbo already publicly links Drogon::Drogon and OpenSSL::Crypto;
# don't relist them here or the linker will see libdrogon.a twice.
target_link_libraries(${PROJECT_NAME} PRIVATE turbo::turbo OpenSSL::SSL)

# ##############################################################################

if (CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++${CMAKE_CXX_STANDARD}")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(models MODEL_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${MODEL_SRC})
# ##############################################################################

add_subdirectory(test)
