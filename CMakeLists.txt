cmake_minimum_required(VERSION 3.0.0)
project(Drawer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(draw ${SOURCES} main.cpp)
add_executable(autotest ${SOURCES} test/test.cpp)

add_test(NAME general COMMAND autotest WORKING_DIRECTORY ../test/general)
set_tests_properties(general PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME line_cmd COMMAND autotest WORKING_DIRECTORY ../test/line_cmd)
set_tests_properties(line_cmd PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME text_cmd COMMAND autotest WORKING_DIRECTORY ../test/text_cmd)
set_tests_properties(text_cmd PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME macro_cmd COMMAND autotest WORKING_DIRECTORY ../test/macro_cmd)
set_tests_properties(macro_cmd PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME color_cmd COMMAND autotest WORKING_DIRECTORY ../test/color_cmd)
set_tests_properties(color_cmd PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME undo_cmd COMMAND autotest WORKING_DIRECTORY ../test/undo_cmd)
set_tests_properties(undo_cmd PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME redo_cmd COMMAND autotest WORKING_DIRECTORY ../test/redo_cmd)
set_tests_properties(redo_cmd PROPERTIES PASS_REGULAR_EXPRESSION "OK")

# add_test(NAME test_line COMMAND test_line -g 256 script.txt WORKING_DIRECTORY ../test/line_cmd)
# set_tests_properties(test_line PROPERTIES PASS_REGULAR_EXPRESSION "OK")
