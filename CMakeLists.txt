cmake_minimum_required(VERSION 3.0.0)
project(Drawer VERSION 0.1.0)

# include(CTest)
# enable_testing()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(draw ${SOURCES})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
