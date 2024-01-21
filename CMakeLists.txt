cmake_minimum_required(VERSION 3.26)

project(advent2023)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)

add_custom_target(format
  COMMAND clang-format -i -style=file ${ALL_SOURCE_FILES}
)

add_subdirectory(lib/abseil-cpp)

add_executable(day01 day01.cpp)
target_link_libraries(day01 absl::strings absl::str_format)

add_executable(day02 day02.cpp)
target_link_libraries(day02 absl::strings absl::str_format)
