cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the package
find_package(xlsxio CONFIG REQUIRED)

# Print found information for debugging
message(STATUS "xlsxio found: ${xlsxio_FOUND}")
message(STATUS "xlsxio version: ${xlsxio_VERSION}")

add_executable(MyApp src/main.cpp)

# Link the libraries - try different target names
if(TARGET xlsxio::xlsxio_write)
    target_link_libraries(MyApp PRIVATE xlsxio::xlsxio_write xlsxio::xlsxio_read)
elseif(TARGET xlsxio_write)
    target_link_libraries(MyApp PRIVATE xlsxio_write xlsxio_read)
else()
    # Fallback: try to find and link manually
    find_path(XLSXIO_INCLUDE_DIR xlsxio_write.h)
    find_library(XLSXIO_WRITE_LIB xlsxio_write)
    find_library(XLSXIO_READ_LIB xlsxio_read)
    
    if(XLSXIO_INCLUDE_DIR AND XLSXIO_WRITE_LIB AND XLSXIO_READ_LIB)
        target_include_directories(MyApp PRIVATE ${XLSXIO_INCLUDE_DIR})
        target_link_libraries(MyApp PRIVATE ${XLSXIO_WRITE_LIB} ${XLSXIO_READ_LIB})
    else()
        message(FATAL_ERROR "xlsxio libraries not found")
    endif()
endif()
