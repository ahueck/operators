include_directories(${PROJECT_SOURCE_DIR}/test/include)

set(unit_test_names adouble_h)

foreach(name ${unit_test_names})
  add_executable(test_${name}${EXE_SUFFIX} src/test_${name}.cpp)
endforeach()
