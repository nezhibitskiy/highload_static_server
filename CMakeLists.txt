cmake_minimum_required(VERSION 3.16)
project(highload2dz)

set(CMAKE_CXX_STANDARD 14)

# Находим путь до папки с заголовочными файлами и записываем в ${LIBEVENT_INCLUDE_DIR}
find_path(LIBEVENT_INCLUDE_DIR event.h
    PATHS
    /usr/local
    /opt
    PATH_SUFFIXES
    include
)

# Находим бинарные файлы библиотеки и записываем в ${LIBEVENT_LIB}
find_library(LIBEVENT_LIB
    NAMES
    event
    PATHS
    /usr/local
    /opt
    PATH_SUFFIXES
    lib
    lib64
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    LIBEVENT_LIB
    LIBEVENT_INCLUDE_DIR
)

include_directories(include)

add_executable(highload2dz main.cpp src/server.cpp)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${LIBEVENT_LIB}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${LIBEVENT_INCLUDE_DIR}
)

add_executable(client.out client/client.cpp)