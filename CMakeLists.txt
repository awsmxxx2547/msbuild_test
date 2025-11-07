cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find xlsxio package
find_package(xlsxio CONFIG REQUIRED)

add_executable(MyApp src/main.cpp)

# Link with the imported targets from xlsxio
target_link_libraries(MyApp PRIVATE xlsxio::xlsxio_write xlsxio::xlsxio_read)

# Add include directories if needed (usually handled by the package, but just in case)
if(TARGET xlsxio::xlsxio_write)
    get_target_property(XLSXIO_INCLUDE_DIR xlsxio::xlsxio_write INTERFACE_INCLUDE_DIRECTORIES)
    if(XLSXIO_INCLUDE_DIR)
        target_include_directories(MyApp PRIVATE ${XLSXIO_INCLUDE_DIR})
    endif()
endif()
