cmake_minimum_required(VERSION 3.9)
project(HW1 C)

# trovo dove sono le librerie MPI
find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})
set(CMAKE_C_COMPILER mpicc)

# setto un pò di flag vari
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3 -pthread")

# aggiungo la directory-root da dove pescare le librerie
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# aggiungo la libreria specifica
add_library(Utility include/Utility/utility.c)
add_library(Mat_Mat include/Mat_Mat/mat_mat.c)

add_executable(HW1 main.c)

# linko le librerie (m sarebbe math.h)
target_link_libraries(HW1 Utility Mat_Mat m ${MPI_C_LIBRARIES})

