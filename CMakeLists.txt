cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Remove XLSXIO_STATIC definition for dynamic linking
# add_definitions(-DXLSXIO_STATIC)  # COMMENT THIS OUT

add_executable(MyApp src/main.cpp)

target_include_directories(MyApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/include
)

target_link_libraries(MyApp PRIVATE 
    xlsxio_write
    xlsxio_read
    ole32 
    shell32
)

target_compile_definitions(MyApp PRIVATE 
    _CRT_SECURE_NO_WARNINGS
)
