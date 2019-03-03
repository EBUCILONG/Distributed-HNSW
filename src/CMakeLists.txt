cmake_minimum_required(VERSION 2.8)

project(DistributedHNSW)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} )

#find_package (Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})

find_package(Boost COMPONENTS system filesystem regex thread program_options date_time chrono)
include_directories(${Boost_INCLUDE_DIRS})

# Find OpenMP
#set(OpenMP_C "${CMAKE_C_COMPILER}")
#set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
#set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
#set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
#set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
#set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
#set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
#set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
#set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
#set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
#set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
#set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})

#find_package(OpenMP REQUIRED)

#if (OPENMP_FOUND)
#    include_directories("${OPENMP_INCLUDES}")
#    link_directories("${OPENMP_LIBRARIES}")
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif(OPENMP_FOUND)

#find_package(OpenMP)
#if (OPENMP_FOUND)
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()

link_libraries(-lpthread -libomp)

INCLUDE_DIRECTORIES(
    # ${DistributedHNSW_SOURCE_DIR}/src/include
)

SET(EXAMPLES
    sift1k
)

FOREACH(EXAMPLE ${EXAMPLES} )
    ADD_EXECUTABLE(${EXAMPLE} apps/${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} ${Boost_LIBRARIES})
ENDFOREACH(EXAMPLE)

#SET(MIPS
#    )

#FOREACH(EXAMPLE ${MIPS} )
#    ADD_EXECUTABLE(${EXAMPLE} mips/${EXAMPLE}.cpp)
#    target_link_libraries(${EXAMPLE} ${Boost_LIBRARIES})
#ENDFOREACH(EXAMPLE)


#SET(EXAMPLES
#        ground_truth
#    )

#FOREACH(EXAMPLE ${EXAMPLES} )
#    ADD_EXECUTABLE(${EXAMPLE} tool/${EXAMPLE}.cpp)
#    target_link_libraries(${EXAMPLE} ${Boost_LIBRARIES})
#ENDFOREACH(EXAMPLE)
