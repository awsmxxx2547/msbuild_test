cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For static linking
add_compile_definitions(XLSXIO_STATIC)

# Set static runtime for MSVC
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()

# Function to find and link libraries safely
function(safe_target_link_libraries target)
    foreach(lib IN LISTS ARGN)
        find_library(LIB_${lib} 
            NAMES ${lib} 
            PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/lib
            NO_DEFAULT_PATH
        )
        if(LIB_${lib})
            message(STATUS "Found library: ${LIB_${lib}}")
            target_link_libraries(${target} PRIVATE ${LIB_${lib}})
        else()
            message(STATUS "Library ${lib} not found, trying system search")
            target_link_libraries(${target} PRIVATE ${lib})
        endif()
    endforeach()
endfunction()

add_executable(MyApp src/main.cpp)

target_include_directories(MyApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/include
)

# Try to link xlsxio libraries
safe_target_link_libraries(MyApp 
    xlsxio_write
    xlsxio_read
)

# Add Windows system libraries (these should always be available)
target_link_libraries(MyApp PRIVATE 
    ole32 
    shell32 
    user32 
    advapi32
    ws2_32
    crypt32
)

target_compile_definitions(MyApp PRIVATE 
    XLSXIO_STATIC
    _CRT_SECURE_NO_WARNINGS
)
