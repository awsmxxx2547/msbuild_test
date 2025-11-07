cmake_minimum_required(VERSION 3.16)
project(MyApp)

# --- Настройки для статической линковки ---
set(BUILD_SHARED_LIBS OFF) 
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "vcpkg triplet for static linking")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find xlsxio package
find_package(xlsxio CONFIG REQUIRED)

add_executable(MyApp src/main.cpp)

# 🔑 КЛЮЧЕВОЕ ИСПРАВЛЕНИЕ: 
# Явно добавляем пути включения (include directories) из целей vcpkg к вашему приложению.
# Используем PRIVATE, чтобы пути были доступны только для компиляции MyApp.
target_include_directories(MyApp PRIVATE 
    $<TARGET_PROPERTY:xlsxio::xlsxio_write,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:xlsxio::xlsxio_read,INTERFACE_INCLUDE_DIRECTORIES>
)

# Линкуем с импортированными целями
target_link_libraries(MyApp PRIVATE xlsxio::xlsxio_write xlsxio::xlsxio_read)
