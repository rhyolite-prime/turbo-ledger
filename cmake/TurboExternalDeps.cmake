# Turbo Ledger — shared external dependency resolution.
#
# Services vendor Bcrypt and jwt-cpp under src/services/external_deps (git
# submodules). When the submodules are not checked out, we fall back to
# FetchContent so a plain clone still builds.
#
# Usage from a service CMakeLists.txt:
#   include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/TurboExternalDeps.cmake)
#   turbo_require_bcrypt(${PROJECT_NAME})
#   turbo_require_jwt_cpp(${PROJECT_NAME})

include_guard(GLOBAL)
include(FetchContent)

set(TURBO_EXTERNAL_DEPS_DIR "${CMAKE_CURRENT_LIST_DIR}/../src/services/external_deps"
    CACHE PATH "Directory holding vendored external dependencies")

# CMake >= 4 dropped compatibility with ancient cmake_minimum_required values
# used by some of these third-party projects.
if(NOT DEFINED CMAKE_POLICY_VERSION_MINIMUM)
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
endif()

function(_turbo_ensure_bcrypt)
    if(TARGET bcrypt)
        return()
    endif()
    if(EXISTS "${TURBO_EXTERNAL_DEPS_DIR}/Bcrypt/CMakeLists.txt")
        add_subdirectory("${TURBO_EXTERNAL_DEPS_DIR}/Bcrypt"
                         "${CMAKE_BINARY_DIR}/external_deps/Bcrypt")
    else()
        message(STATUS "external_deps/Bcrypt not checked out - fetching Bcrypt.cpp")
        FetchContent_Declare(turbo_bcrypt
            GIT_REPOSITORY https://github.com/hilch/Bcrypt.cpp
            GIT_TAG master
            GIT_SHALLOW TRUE)
        FetchContent_MakeAvailable(turbo_bcrypt)
    endif()
endfunction()

function(_turbo_ensure_jwt_cpp)
    if(TARGET jwt-cpp)
        return()
    endif()
    if(EXISTS "${TURBO_EXTERNAL_DEPS_DIR}/jwt-cpp/CMakeLists.txt")
        set(JWT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory("${TURBO_EXTERNAL_DEPS_DIR}/jwt-cpp"
                         "${CMAKE_BINARY_DIR}/external_deps/jwt-cpp")
    else()
        message(STATUS "external_deps/jwt-cpp not checked out - fetching jwt-cpp")
        set(JWT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        FetchContent_Declare(turbo_jwt_cpp
            GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp
            GIT_TAG v0.7.1
            GIT_SHALLOW TRUE)
        FetchContent_MakeAvailable(turbo_jwt_cpp)
    endif()
endfunction()

function(turbo_require_bcrypt target)
    _turbo_ensure_bcrypt()
    target_link_libraries(${target} PRIVATE bcrypt)
endfunction()

function(turbo_require_jwt_cpp target)
    _turbo_ensure_jwt_cpp()
    if(TARGET jwt-cpp)
        target_link_libraries(${target} PRIVATE jwt-cpp)
    endif()
endfunction()
