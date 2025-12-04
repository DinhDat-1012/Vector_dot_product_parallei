cmake_minimum_required(VERSION 4.0)
project(OpenMP_prj)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenMP_prj main.cpp)
find_package(OpenMP REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
