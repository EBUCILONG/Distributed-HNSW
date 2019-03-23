cmake_minimum_required(VERSION 2.8)

project(DistributedHNSW)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/include/kahiplib/)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp ")

find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} )

#find_package (Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})

find_package(Boost COMPONENTS system filesystem regex thread program_options date_time chrono)
include_directories(${Boost_INCLUDE_DIRS})


find_package (OpenMP)
include_directories(${OpenMP_INCLUDE_DIRS})

find_package (MPI)
include_directories(${MPI_INCLUDE_PATH})

link_libraries(-lpthread)

INCLUDE_DIRECTORIES(
        ${DistributedHNSW_SOURCE_DIR}/src/include
        ${DistributedHNSW_SOURCE_DIR}/src/include/kahiplib/interface
)

SET(EXAMPLES
    bug
    sift1k
)

FOREACH(EXAMPLE ${EXAMPLES} )
    ADD_EXECUTABLE(${EXAMPLE} src/apps/${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} ${Boost_LIBRARIES} ${MPI_C_LIBRARIES} libkaffpa libmapping)
ENDFOREACH(EXAMPLE)


