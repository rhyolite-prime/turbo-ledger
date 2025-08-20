# Use a multi-stage build for smaller final image
    FROM gcc:12 AS builder

    # Install dependencies
    RUN apt-get update && apt-get install -y \
        cmake \
        git \
        libssl-dev \
        libjsoncpp-dev \
        libsqlite3-dev \
        postgresql-server-dev-all \
        uuid-dev \
        zlib1g-dev \
        && rm -rf /var/lib/apt/lists/*

    # Clone and build Drogon (matching GitHub Actions workflow)
    WORKDIR /usr/src
    RUN git clone https://github.com/drogonframework/drogon.git && \
        cd drogon && \
        git submodule update --init --recursive && \
        mkdir build && cd build && \
        cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_POSTGRESQL=ON .. && \
        make -j$(nproc) && \
        make install

    # Build JWT-CPP (header-only, just need to install)
    RUN git clone https://github.com/Thalhammer/jwt-cpp.git && \
        mkdir -p jwt-cpp/build && \
        cd jwt-cpp/build && \
        cmake .. && \
        make install

    # Clone and build bcrypt
    RUN git clone https://github.com/kay-smith/Bcrypt.cpp && \
        cd Bcrypt.cpp && \
        cat > CMakeLists.txt << 'EOL'
    cmake_minimum_required(VERSION 3.10)

    option(BUILD_TESTS "Build test programs" OFF)

    project(bcrypt VERSION 1.0 LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Library
    add_library(bcrypt src/bcrypt.cpp src/blowfish.cpp)
    target_include_directories(bcrypt
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )

    # Tests
    if(BUILD_TESTS)
      add_executable(test test/main.cpp)
      target_link_libraries(test PRIVATE bcrypt)
    endif()

    include(GNUInstallDirs)

    install(TARGETS bcrypt
        EXPORT bcryptTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(EXPORT bcryptTargets
        FILE bcryptConfig.cmake
        NAMESPACE bcrypt::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bcrypt
    )
    EOL
    RUN cd Bcrypt.cpp && \
        mkdir -p build && \
        cd build && \
        cmake .. && \
        make -j$(nproc) && \
        make install

    # Copy and build the application
    WORKDIR /usr/src/app
    COPY . .
    RUN mkdir build && \
        cd build && \
        cmake -DCMAKE_BUILD_TYPE=Release .. && \
        make -j$(nproc)

    # Create the runtime image
    FROM debian:bullseye-slim

    # Install runtime dependencies
    RUN apt-get update && apt-get install -y \
        libssl1.1 \
        libjsoncpp24 \
        libsqlite3-0 \
        libpq5 \
        zlib1g \
        && rm -rf /var/lib/apt/lists/*

    # Copy the built application and required files
    WORKDIR /app
    COPY --from=builder /usr/src/app/build/turbo_ledger_identity .
    COPY --from=builder /usr/src/app/config.json .

    # Expose the port the service runs on
    EXPOSE 8080

    # Set environment variables
    ENV TZ=UTC

    # Command to run when the container starts
    CMD ["./turbo_ledger_identity"]