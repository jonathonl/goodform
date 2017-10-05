cmake_minimum_required(VERSION 2.8.4)
project(goodform)

include_directories("./include")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER "/opt/local/bin/g++-mp-7")
set(CMAKE_CC_COMPILER "/opt/local/bin/gcc-mp-7")

set(HEADER_FILES
  include/form.hpp
  include/variant.hpp
  include/msgpack.hpp
  include/json.hpp
  include/portable_endian.hpp)

set(SOURCE_FILES
  src/variant.cpp
  src/msgpack.cpp
  src/json.cpp
  src/form.cpp)

add_library(goodform ${SOURCE_FILES} ${HEADER_FILES})

add_executable(variant-test tests/variant-test.cpp)
target_link_libraries(variant-test goodform)