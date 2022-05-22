cmake_minimum_required(VERSION 3.0.0)
project(Drawer VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(draw ${SOURCES} main.cpp)

add_executable(test_line ${SOURCES} test/line_cmd/test_line.cpp)
add_test(NAME test_line COMMAND test_line -g 256 script.txt WORKING_DIRECTORY ../test/line_cmd)
set_tests_properties(test_line PROPERTIES PASS_REGULAR_EXPRESSION "OK")
