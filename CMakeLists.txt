cmake_minimum_required(VERSION 3.0.0)
project(CS014_Lab13 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

add_executable( jug_problem
    ../src/main.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)