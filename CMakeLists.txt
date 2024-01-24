cmake_minimum_required(VERSION 3.26)

project(advent2023)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)

add_custom_target(format
  COMMAND clang-format -i -style=file ${ALL_SOURCE_FILES}
)

add_subdirectory(lib/abseil-cpp)

function(add_day day)
  add_executable(${day} ${day}.cpp)
  target_link_libraries(${day} absl::strings absl::str_format)
endfunction()

add_day(day01)
add_day(day02)
add_day(day03)
