cmake_minimum_required(VERSION 3.0.0)
project(A_STAR_SEARCH_ALGORITHM VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

add_executable(A_STAR_SEARCH_ALGORITHM main.cpp AStarSearch.cpp AStarSearch.hpp Node.cpp Node.hpp Grid.cpp Grid.hpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
