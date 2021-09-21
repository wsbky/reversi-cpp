cmake_policy(SET CMP0076 NEW)

cmake_minimum_required(VERSION 3.13)

project(Reversi-InstructionTest)

message("compiler: ${CMAKE_CXX_COMPILER}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
message("std=c++${CMAKE_CXX_STANDARD}")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/test_sources)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../src)

add_compile_options(-Wall -Werror -Wextra -Wno-sign-conversion -Wshadow)

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)
include(GoogleTest)

add_executable(itest-eval2 ${SRC_DIR}/eval2.cc)
target_include_directories(itest-eval2 PUBLIC ${INCLUDE_DIR})
target_link_libraries(itest-eval2 gtest_main)
