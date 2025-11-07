cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

# Build xlsxio as static library
ExternalProject_Add(xlsxio_external
    GIT_REPOSITORY https://github.com/brechtsanders/xlsxio.git
    GIT_TAG master
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release
    INSTALL_DIR ${CMAKE_BINARY_DIR}/xlsxio-install
    BUILD_BYPRODUCTS 
        ${CMAKE_BINARY_DIR}/xlsxio-install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}xlsxio_write${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${CMAKE_BINARY_DIR}/xlsxio-install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}xlsxio_read${CMAKE_STATIC_LIBRARY_SUFFIX}
)

# Create imported targets
add_library(xlsxio_write STATIC IMPORTED)
add_library(xlsxio_read STATIC IMPORTED)

set_target_properties(xlsxio_write PROPERTIES
    IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/xlsxio-install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}xlsxio_write${CMAKE_STATIC_LIBRARY_SUFFIX}
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}/xlsxio-install/include
)

set_target_properties(xlsxio_read PROPERTIES
    IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/xlsxio-install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}xlsxio_read${CMAKE_STATIC_LIBRARY_SUFFIX}
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}/xlsxio-install/include
)

add_dependencies(xlsxio_write xlsxio_external)
add_dependencies(xlsxio_read xlsxio_external)

add_executable(MyApp src/main.cpp)
target_link_libraries(MyApp PRIVATE xlsxio_write xlsxio_read)

# Static linking
if(WIN32)
    if(MINGW)
        target_link_libraries(MyApp PRIVATE -static -static-libgcc -static-libstdc++)
    endif()
else()
    target_link_libraries(MyApp PRIVATE -static-libgcc -static-libstdc++)
endif()
