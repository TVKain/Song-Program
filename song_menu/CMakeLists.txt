cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(song_menu VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.c)

add_executable(main main/main.c ${SRC_FILES})

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/main/songs9.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})