cmake_minimum_required(VERSION 2.8.4)
project(goodform)

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set(CMAKE_CXX_COMPILER "/opt/local/bin/g++-mp-4.9")
# set(CMAKE_CC_COMPILER "/opt/local/bin/gcc-mp-4.9")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(SOURCE_FILES
  src/variant.cpp
  src/msgpack.cpp
  src/json.cpp)

add_library(goodform SHARED ${SOURCE_FILES})

add_library(goodform-static STATIC ${SOURCE_FILES})

add_executable(variant-test tests/variant-test.cpp ${SOURCE_FILES})

target_include_directories(goodform PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
