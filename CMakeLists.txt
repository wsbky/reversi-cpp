cmake_policy(SET CMP0076 NEW)

cmake_minimum_required(VERSION 3.13)

project(Reversi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_executable(reversi ${SRC_DIR}/reversi.cc)
target_include_directories(reversi PUBLIC ${SRC_DIR})
target_compile_options(reversi PUBLIC
    $<$<CONFIG:Release>:-Wall -Werror -Wextra -O2>
    $<$<CONFIG:Debug>:-Wall -Werror -Wextra -O0 -g>
)
