CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(Operators)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_VERBOSE_MAKEFILE on)

if(NOT BINARY_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${BINARY_OUTPUT_DIRECTORY})
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

message(STATUS "Binary output directory: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include_directories(${PROJECT_SOURCE_DIR}/include)

# Builds have to be explicitly disabled
if(NOT MAKE_TEST EQUAL 0)
  message(STATUS "Requested generation of tests.")
  add_subdirectory(test)
endif()
