include_directories(${PROJECT_SOURCE_DIR}/test/include)

set(unit_test_names 
  src/test_adouble_h.cpp 
  src/test_adouble_et.cpp 
)

message(STATUS "Unit test source files: " ${unit_test_names})

add_executable(test_runner${EXE_SUFFIX} src/main.cpp ${unit_test_names})
add_executable(test_adouble_tao${EXE_SUFFIX} src/test_adouble_tao.cpp)