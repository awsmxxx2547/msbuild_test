cmake_minimum_required(VERSION 3.15)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(xlsxio REQUIRED)

add_executable(MyApp src/main.cpp)

target_link_libraries(MyApp PRIVATE xlsxio_read xlsxio_write)
