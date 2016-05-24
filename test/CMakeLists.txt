include_directories(${PROJECT_SOURCE_DIR}/test/include)

#set(unit_test_names adouble_h)

file(GLOB test_src "src/*.cpp")

message(STATUS "Unit test source files: " ${test_src})

add_executable(test_runner${EXE_SUFFIX} ${test_src}) #src/main.cpp src/test_adouble_h.cpp)