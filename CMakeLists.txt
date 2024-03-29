cmake_minimum_required(VERSION 2.8)

project(DistributedHNSW)

add_subdirectory(${DistributedHNSW_SOURCE_DIR}/src/include/kahiplib/)
add_subdirectory(${DistributedHNSW_SOURCE_DIR}/src/include/cppkafka/)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp ")

find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} )

find_package (Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(Boost COMPONENTS system filesystem regex thread program_options date_time chrono)
include_directories(${Boost_INCLUDE_DIRS})


find_package (OpenMP)
include_directories(${OpenMP_INCLUDE_DIRS})

find_package (MPI)
include_directories(${MPI_INCLUDE_PATH})

find_package(Zookeeper REQUIRED)
include_directories(${Zookeeper_INCLUDE_DIRS})

set(HDFS_INCLUDE_DIR "/data/opt/hadoop-2.6.0/include/")
set(HDFS_LIBRARY_DIR "/data/opt/hadoop-2.6.0/lib/native/")



link_libraries(-lpthread)

INCLUDE_DIRECTORIES(${DistributedHNSW_SOURCE_DIR}/src/include ${RDKAFKA_INCLUDE_DIR} ${HDFS_INCLUDE_DIR})
link_libraries(${HDFS_LIBRARY_DIR}/libhdfs.so)


SET(EXAMPLES
    #bug
    #bug2
    #start_customer
    #start_benchmark_evaluator
    #start_throughput_evaluator
    #start_customer_endless
    ground_truth
    recover_single_machine
    naive_machine
    #tt
    #single_machine
    #binary_machine
    #fvecs_hnsw_machine
    #dataset_partitioner
    #wakerate_tester
    #idvecs_hnsw_machine
    #load_hnsw
    #sift1k
    ip_partition
    start_customer_rotate
    start_delay_evaluator
)

#add_executable(interface_test interface/kaHIP_interface.cpp)
#target_include_directories(interface_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/interface)
#target_compile_definitions(interface_test PRIVATE "-DMODE_KAFFPA")
#target_link_libraries(interface_test libkaffpa libmapping ${OpenMP_CXX_LIBRARIES})

SET(IPEXAMPLES
        ip_partition
        )

FOREACH(EXAMPLE ${EXAMPLES} )
    ADD_EXECUTABLE(${EXAMPLE} src/apps/${EXAMPLE}.cpp )
    target_link_libraries(${EXAMPLE} ${Boost_LIBRARIES} ${MPI_C_LIBRARIES} ${Zookeeper_LIBRARIES} libkaffpa ${RDKAFKA_LIBRARY} cppkafka libmapping ${OpenMP_CXX_LIBRARIES})
ENDFOREACH(EXAMPLE)
