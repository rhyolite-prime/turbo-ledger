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
    # Sanity-check the vendored checkout really is Bcrypt.cpp (a stale or
    # misconfigured submodule would otherwise break the build in odd ways).
    if(EXISTS "${TURBO_EXTERNAL_DEPS_DIR}/Bcrypt/CMakeLists.txt"
       AND EXISTS "${TURBO_EXTERNAL_DEPS_DIR}/Bcrypt/include/bcrypt.h")
        add_subdirectory("${TURBO_EXTERNAL_DEPS_DIR}/Bcrypt"
                         "${CMAKE_BINARY_DIR}/external_deps/Bcrypt")
    else()
        message(STATUS "external_deps/Bcrypt not checked out - fetching Bcrypt.cpp")
        # Same fork + commit the src/services/external_deps/Bcrypt submodule pins.
        FetchContent_Declare(turbo_bcrypt
            GIT_REPOSITORY https://github.com/kay-smith/Bcrypt.cpp
            GIT_TAG 0d18b6a99e8c57627910db4ef9a7706c009b12ad)
        FetchContent_MakeAvailable(turbo_bcrypt)
    endif()
endfunction()

function(_turbo_ensure_jwt_cpp)
    if(TARGET jwt-cpp)
        return()
    endif()
    # Sanity-check the vendored checkout really is jwt-cpp: at one point the
    # submodule URL mistakenly pointed at Bcrypt.cpp, which both collided with
    # the 'bcrypt' target and left jwt-cpp/jwt.h missing. Validate the header
    # before trusting the directory; otherwise fall back to FetchContent.
    if(EXISTS "${TURBO_EXTERNAL_DEPS_DIR}/jwt-cpp/CMakeLists.txt"
       AND EXISTS "${TURBO_EXTERNAL_DEPS_DIR}/jwt-cpp/include/jwt-cpp/jwt.h")
        set(JWT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory("${TURBO_EXTERNAL_DEPS_DIR}/jwt-cpp"
                         "${CMAKE_BINARY_DIR}/external_deps/jwt-cpp")
    else()
        if(EXISTS "${TURBO_EXTERNAL_DEPS_DIR}/jwt-cpp/CMakeLists.txt")
            message(WARNING
                "external_deps/jwt-cpp exists but does not look like jwt-cpp "
                "(missing include/jwt-cpp/jwt.h) - check the submodule URL in "
                ".gitmodules. Falling back to FetchContent.")
        else()
            message(STATUS "external_deps/jwt-cpp not checked out - fetching jwt-cpp")
        endif()
        set(JWT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        # Same fork + commit the src/services/external_deps/jwt-cpp submodule pins.
        FetchContent_Declare(turbo_jwt_cpp
            GIT_REPOSITORY https://github.com/kay-smith/jwt-cpp
            GIT_TAG 0a503e75084cfdb48cc2186e6b961444eb819007)
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
