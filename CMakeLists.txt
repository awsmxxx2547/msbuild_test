cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Critical: Define static before any includes
add_definitions(-DXLSXIO_STATIC)

# Set static runtime
if(MSVC)
    # Use string replacement to ensure static runtime
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    
    # Also set the property
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()

# Find the actual library files
find_library(XLSXIO_WRITE_LIB
    NAMES xlsxio_write_static xlsxio_write
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
    NO_DEFAULT_PATH
    REQUIRED
)

find_library(XLSXIO_READ_LIB
    NAMES xlsxio_read_static xlsxio_read
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
    NO_DEFAULT_PATH
    REQUIRED
)

message(STATUS "Found write library: ${XLSXIO_WRITE_LIB}")
message(STATUS "Found read library: ${XLSXIO_READ_LIB}")

add_executable(MyApp src/main.cpp)

# Include directories
target_include_directories(MyApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/include
)

# Link the actual library files we found
target_link_libraries(MyApp PRIVATE 
    ${XLSXIO_WRITE_LIB}
    ${XLSXIO_READ_LIB}
)

# Add Windows libraries that might be needed
target_link_libraries(MyApp PRIVATE 
    ole32 
    shell32 
    user32 
    advapi32
    ws2_32
)

# Make sure static definition is applied to our target too
target_compile_definitions(MyApp PRIVATE 
    XLSXIO_STATIC
    _CRT_SECURE_NO_WARNINGS
)
