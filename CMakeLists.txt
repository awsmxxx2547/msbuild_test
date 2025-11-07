# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка статической линковки по умолчанию для всего проекта
# Это ключевой шаг для статической сборки
set(BUILD_SHARED_LIBS OFF) 
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "vcpkg triplet for static linking")

# Ищем и конфигурируем пакет xlsxio.
# find_package, когда используется с toolchain vcpkg, автоматически находит 
# зависимости, установленные vcpkg.
find_package(xlsxio CONFIG REQUIRED)

add_executable(MyApp src/main.cpp)

# Печатаем найденную информацию для отладки
message(STATUS "xlsxio found: ${xlsxio_FOUND}")
message(STATUS "xlsxio version: ${xlsxio_VERSION}")

# Линкуем с импортированными целями. 
# Vcpkg гарантирует, что эти цели теперь статически связаны.
target_link_libraries(MyApp PRIVATE xlsxio::xlsxio_write xlsxio::xlsxio_read)
