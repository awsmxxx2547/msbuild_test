cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force static runtime and definitions
if(MSVC)
    add_compile_options(
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:Debug>:/MTd>
    )
endif()

add_executable(MyApp src/main.cpp)

# Directly specify the library files
target_include_directories(MyApp PRIVATE 
    $ENV{VCPKG_ROOT}/installed/x64-windows-static/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/include
)

# Try different library naming patterns
target_link_libraries(MyApp PRIVATE 
    $ENV{VCPKG_ROOT}/installed/x64-windows-static/lib/xlsxio_write.lib
    $ENV{VCPKG_ROOT}/installed/x64-windows-static/lib/xlsxio_read.lib
)

# Alternative: If direct paths don't work, use find_library
# find_library(XLSXIO_WRITE xlsxio_write PATHS $ENV{VCPKG_ROOT}/installed/x64-windows-static/lib REQUIRED)
# find_library(XLSXIO_READ xlsxio_read PATHS $ENV{VCPKG_ROOT}/installed/x64-windows-static/lib REQUIRED)
# target_link_libraries(MyApp PRIVATE ${XLSXIO_WRITE} ${XLSXIO_READ})

target_link_libraries(MyApp PRIVATE 
    ole32 
    shell32
)

target_compile_definitions(MyApp PRIVATE 
    XLSXIO_STATIC
    _CRT_SECURE_NO_WARNINGS
)
