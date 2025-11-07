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

# Let vcpkg handle the library finding through the toolchain
# We'll use the library names that vcpkg provides

add_executable(MyApp src/main.cpp)

# Include directory
target_include_directories(MyApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/include
)

# Just link with the basic xlsxio libraries and let vcpkg handle dependencies
target_link_libraries(MyApp PRIVATE 
    xlsxio_write
    xlsxio_read
)

# Add Windows system libraries
target_link_libraries(MyApp PRIVATE 
    ole32 
    shell32 
    user32 
    advapi32
    ws2_32
)

# Additional compile definitions for static build
target_compile_definitions(MyApp PRIVATE 
    XLSXIO_STATIC
    _CRT_SECURE_NO_WARNINGS
    NOMINMAX
)
