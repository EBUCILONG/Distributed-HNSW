cmake_minimum_required(VERSION 2.8)

project(DistributedHNSW)

add_subdirectory(${DistributedHNSW_SOURCE_DIR}/src/include/kahiplib/)

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
)

SET(EXAMPLES
    bug
    #sift1k
)

#add_executable(interface_test interface/kaHIP_interface.cpp)
#target_include_directories(interface_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/interface)
#target_compile_definitions(interface_test PRIVATE "-DMODE_KAFFPA")
#target_link_libraries(interface_test libkaffpa libmapping ${OpenMP_CXX_LIBRARIES})

FOREACH(EXAMPLE ${EXAMPLES} )
    ADD_EXECUTABLE(${EXAMPLE} src/apps/${EXAMPLE}.cpp ${DistributedHNSW_SOURCE_DIR}/src/include/kahiplib/interface/kaHIP_interface.cpp)
    target_link_libraries(${EXAMPLE} ${Boost_LIBRARIES} ${MPI_C_LIBRARIES} libkaffpa libmapping ${OpenMP_CXX_LIBRARIES})
ENDFOREACH(EXAMPLE)


