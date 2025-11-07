cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For static linking, define this before including headers
add_compile_definitions(XLSXIO_STATIC)

# Set static runtime for MSVC
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# Find xlsxio libraries - look in both static and dynamic locations
find_path(XLSXIO_INCLUDE_DIR
    NAMES xlsxio_write.h
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/include
        ${VCPKG_ROOT}/installed/x64-windows-static/include
        ${VCPKG_ROOT}/installed/x64-windows/include
    REQUIRED
)

# Look for static libraries first
find_library(XLSXIO_WRITE_LIB
    NAMES xlsxio_write_static xlsxio_write libxlsxio_write
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib
        ${VCPKG_ROOT}/installed/x64-windows-static/lib
        ${VCPKG_ROOT}/installed/x64-windows/lib
    REQUIRED
)

find_library(XLSXIO_READ_LIB
    NAMES xlsxio_read_static xlsxio_read libxlsxio_read
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib
        ${VCPKG_ROOT}/installed/x64-windows-static/lib
        ${VCPKG_ROOT}/installed/x64-windows/lib
    REQUIRED
)

# Debug information
message(STATUS "XLSXIO_INCLUDE_DIR: ${XLSXIO_INCLUDE_DIR}")
message(STATUS "XLSXIO_WRITE_LIB: ${XLSXIO_WRITE_LIB}")
message(STATUS "XLSXIO_READ_LIB: ${XLSXIO_READ_LIB}")

add_executable(MyApp src/main.cpp)

target_include_directories(MyApp PRIVATE ${XLSXIO_INCLUDE_DIR})

# Link the actual library files we found
target_link_libraries(MyApp PRIVATE 
    ${XLSXIO_WRITE_LIB}
    ${XLSXIO_READ_LIB}
)

# Link required dependencies for static build
target_link_libraries(MyApp PRIVATE 
    zlibstatic
    libexpatMD
    bzip2
    ole32 
    shell32 
    user32 
    advapi32
    ws2_32
    crypt32
)

# Additional compile definitions for static build
target_compile_definitions(MyApp PRIVATE 
    XLSXIO_STATIC
    _CRT_SECURE_NO_WARNINGS
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)
