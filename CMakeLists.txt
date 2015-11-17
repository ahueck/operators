CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Operators)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_VERBOSE_MAKEFILE on)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)


if(NOT NO_TEST)
  message(STATUS "Requested generation of tests.")
  add_subdirectory(test)
endif()
