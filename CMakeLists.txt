cmake_minimum_required(VERSION 3.2)
include(ExternalProject)
include(CMakePackageConfigHelpers)
project(goodform VERSION 1.0.0)

enable_testing()

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER "/opt/local/bin/g++-mp-7")
#set(CMAKE_CC_COMPILER "/opt/local/bin/gcc-mp-7")

set(HEADER_FILES
  include/goodform/form.hpp
  include/goodform/variant.hpp
  include/goodform/msgpack.hpp
  include/goodform/json.hpp
  include/goodform/portable_endian.hpp)

set(SOURCE_FILES
  src/form.cpp
  src/variant.cpp
  src/msgpack.cpp
  src/json.cpp
  src/form.cpp)

add_library(goodform ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(goodform PRIVATE include)
target_compile_features(goodform PUBLIC cxx_auto_type cxx_lambdas)

add_executable(goodform-test src/test.cpp)
target_include_directories(goodform-test PUBLIC include)
target_link_libraries(goodform-test goodform)

add_test(simple_test goodform-test simple)

install(DIRECTORY include/goodform DESTINATION include)
install(TARGETS goodform EXPORT ${PROJECT_NAME}-config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(EXPORT ${PROJECT_NAME}-config DESTINATION share/${PROJECT_NAME})
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake COMPATIBILITY SameMajorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake DESTINATION share/${PROJECT_NAME})
export(EXPORT ${PROJECT_NAME}-config)