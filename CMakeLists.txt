cmake_policy(SET CMP0076 NEW)

cmake_minimum_required(VERSION 3.13)

project(Reversi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Werror  -Wextra -O0 -g")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_executable(reversi ${SRC_DIR}/reversi.cc)
target_include_directories(reversi PUBLIC ${SRC_DIR})

