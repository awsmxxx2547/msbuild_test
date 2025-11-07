cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set static runtime for MSVC
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# For static linking, we need to find static libraries
find_path(XLSXIO_INCLUDE_DIR
    NAMES xlsxio_write.h
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/include
)

find_library(XLSXIO_WRITE_LIB
    NAMES xlsxio_write libxlsxio_write
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib
)

find_library(XLSXIO_READ_LIB
    NAMES xlsxio_read libxlsxio_read
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib
)

# Also find static dependencies
find_library(ZLIB_LIB
    NAMES zlib zlibstatic zlibstaticd
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib
)

find_library(EXPAT_LIB
    NAMES expat libexpat
    PATHS 
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib
)

message(STATUS "XLSXIO_INCLUDE_DIR: ${XLSXIO_INCLUDE_DIR}")
message(STATUS "XLSXIO_WRITE_LIB: ${XLSXIO_WRITE_LIB}")
message(STATUS "XLSXIO_READ_LIB: ${XLSXIO_READ_LIB}")

add_executable(MyApp src/main.cpp)

if(XLSXIO_INCLUDE_DIR)
    target_include_directories(MyApp PRIVATE ${XLSXIO_INCLUDE_DIR})
endif()

# Link all required libraries for static build
if(XLSXIO_WRITE_LIB AND XLSXIO_READ_LIB)
    target_link_libraries(MyApp PRIVATE 
        ${XLSXIO_WRITE_LIB} 
        ${XLSXIO_READ_LIB}
    )
    
    # Add static dependencies if found
    if(ZLIB_LIB)
        target_link_libraries(MyApp PRIVATE ${ZLIB_LIB})
    endif()
    
    if(EXPAT_LIB)
        target_link_libraries(MyApp PRIVATE ${EXPAT_LIB})
    endif()
else()
    # Fallback: try library names directly
    target_link_libraries(MyApp PRIVATE xlsxio_write xlsxio_read)
endif()

# Windows system libraries for static build
target_link_libraries(MyApp PRIVATE 
    ole32 
    shell32 
    user32 
    advapi32
    ws2_32  # For networking if needed
)

# For static builds, we might need these definitions
if(MSVC)
    target_compile_definitions(MyApp PRIVATE 
        _CRT_SECURE_NO_WARNINGS
        NOMINMAX
    )
endif()
