cmake_minimum_required(VERSION 4.0)
project(OpenMP_prj)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenMP_prj main.cpp
        Vector_dot_seq.cpp
        Vector_dot_seq.h
        Vector_dot_par.cpp
        Vector_dot_par.h
        Vector_dot_par_SIMD.cpp
        Vector_dot_par_SIMD.h)
find_package(OpenMP REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
