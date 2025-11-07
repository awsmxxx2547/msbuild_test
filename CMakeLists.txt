cmake_minimum_required(VERSION 3.16)  # <-- ДОБАВЛЕНО
project(MyApp)                       # <-- ДОБАВЛЕНО

# --- Настройки для статической линковки ---
set(BUILD_SHARED_LIBS OFF) 
# Эта строка теперь не так критична, так как триплет указан в шаге GitHub Actions
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "vcpkg triplet for static linking")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find xlsxio package
find_package(xlsxio CONFIG REQUIRED)

add_executable(MyApp src/main.cpp)

# Print found information for debugging (Опционально)
message(STATUS "xlsxio found: ${xlsxio_FOUND}")
message(STATUS "xlsxio version: ${xlsxio_VERSION}")

# Линкуем с импортированными целями
target_link_libraries(MyApp PRIVATE xlsxio::xlsxio_write xlsxio::xlsxio_read)
