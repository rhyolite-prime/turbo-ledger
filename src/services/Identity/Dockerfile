# Use a multi-stage build for smaller final image
FROM gcc:12 AS builder

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    git \
    libssl-dev \
    libjsoncpp-dev \
    libhiredis-dev \
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
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_POSTGRESQL=ON \
          -DBUILD_MYSQL=OFF \
          -DBUILD_SQLITE=OFF \
          -DBUILD_REDIS=ON \
          .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig

# Build JWT-CPP (header-only, just need to install)
RUN git clone https://github.com/Thalhammer/jwt-cpp.git && \
    mkdir -p jwt-cpp/build && \
    cd jwt-cpp/build && \
    cmake .. && \
    make install

# Clone and build bcrypt
WORKDIR /usr/src
RUN git clone https://github.com/kay-smith/Bcrypt.cpp
WORKDIR /usr/src/Bcrypt.cpp

# Create CMakeLists.txt file for bcrypt
RUN echo 'cmake_minimum_required(VERSION 3.10)' > CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo 'option(BUILD_TESTS "Build test programs" OFF)' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo 'project(bcrypt VERSION 1.0 LANGUAGES CXX)' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo 'set(CMAKE_CXX_STANDARD 11)' >> CMakeLists.txt && \
    echo 'set(CMAKE_CXX_STANDARD_REQUIRED ON)' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo '# Library' >> CMakeLists.txt && \
    echo 'add_library(bcrypt src/bcrypt.cpp src/blowfish.cpp)' >> CMakeLists.txt && \
    echo 'target_include_directories(bcrypt' >> CMakeLists.txt && \
    echo '    PRIVATE' >> CMakeLists.txt && \
    echo '        ${CMAKE_CURRENT_SOURCE_DIR}/src' >> CMakeLists.txt && \
    echo '    PUBLIC' >> CMakeLists.txt && \
    echo '        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>' >> CMakeLists.txt && \
    echo '        $<INSTALL_INTERFACE:include>' >> CMakeLists.txt && \
    echo ')' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo '# Tests' >> CMakeLists.txt && \
    echo 'if(BUILD_TESTS)' >> CMakeLists.txt && \
    echo '  add_executable(test test/main.cpp)' >> CMakeLists.txt && \
    echo '  target_link_libraries(test PRIVATE bcrypt)' >> CMakeLists.txt && \
    echo 'endif()' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo 'include(GNUInstallDirs)' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo 'install(TARGETS bcrypt' >> CMakeLists.txt && \
    echo '    EXPORT bcryptTargets' >> CMakeLists.txt && \
    echo '    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}' >> CMakeLists.txt && \
    echo '    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}' >> CMakeLists.txt && \
    echo '    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}' >> CMakeLists.txt && \
    echo ')' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo 'install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})' >> CMakeLists.txt && \
    echo '' >> CMakeLists.txt && \
    echo 'install(EXPORT bcryptTargets' >> CMakeLists.txt && \
    echo '    FILE bcryptConfig.cmake' >> CMakeLists.txt && \
    echo '    NAMESPACE bcrypt::' >> CMakeLists.txt && \
    echo '    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bcrypt' >> CMakeLists.txt && \
    echo ')' >> CMakeLists.txt

# Build and install bcrypt
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig

# Copy and build the application
WORKDIR /usr/src/app
COPY . .
RUN rm -rf build && \
    mkdir -p build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Create the runtime image - Use same base as builder to ensure library compatibility
FROM debian:bookworm-slim

# Install runtime dependencies with correct versions
RUN apt-get update && apt-get install -y \
    libssl3 \
    libjsoncpp25 \
    libpq5 \
    libuuid1 \
    zlib1g \
    ca-certificates \
    libbrotli1 \
    libmariadb3 \
    libhiredis0.14 \
    && rm -rf /var/lib/apt/lists/*

# Copy built libraries from builder stage
COPY --from=builder /usr/local/lib/libdrogon.so* /usr/local/lib/
COPY --from=builder /usr/local/lib/libtrantor.so* /usr/local/lib/
COPY --from=builder /usr/local/lib/libbcrypt.* /usr/local/lib/

# Update library cache
RUN ldconfig

# Copy the built application and required files
WORKDIR /app
COPY --from=builder /usr/src/app/build/Identity .
COPY --from=builder /usr/src/app/config.json .

# Create non-root user for security
RUN groupadd -r appgroup && useradd -r -g appgroup appuser && \
    chown -R appuser:appgroup /app && \
    chmod +x /app/Identity

# Switch to non-root user
USER appuser

# Expose the port the service runs on
EXPOSE 5001

# Set environment variables
ENV TZ=UTC
ENV LD_LIBRARY_PATH=/usr/local/lib

# Command to run when the container starts
CMD ["./Identity"]