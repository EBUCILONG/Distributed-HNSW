# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /data/opt/brew/Cellar/cmake/3.10.1/bin/cmake

# The command to remove a file.
RM = /data/opt/brew/Cellar/cmake/3.10.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/sydeng/repositary/hnsw-repo/Distributed-HNSW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui

# Include any dependencies generated for this target.
include src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/depend.make

# Include the progress variables for this target.
include src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/progress.make

# Include the compile flags for this target's objects.
include src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o: ../src/include/kahiplib/lib/parallel_mh/parallel_mh_async.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/parallel_mh_async.cpp

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/parallel_mh_async.cpp > CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.i

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/parallel_mh_async.cpp -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.s

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.provides: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.provides

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o


src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o: ../src/include/kahiplib/lib/parallel_mh/population.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/population.cpp

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/population.cpp > CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.i

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/population.cpp -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.s

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.provides: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.provides

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o


src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o: ../src/include/kahiplib/lib/parallel_mh/galinier_combine/gal_combine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/galinier_combine/gal_combine.cpp

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/galinier_combine/gal_combine.cpp > CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.i

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/galinier_combine/gal_combine.cpp -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.s

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.provides: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.provides

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o


src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o: ../src/include/kahiplib/lib/parallel_mh/galinier_combine/construct_partition.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/galinier_combine/construct_partition.cpp

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/galinier_combine/construct_partition.cpp > CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.i

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/galinier_combine/construct_partition.cpp -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.s

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.provides: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.provides

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o


src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o: ../src/include/kahiplib/lib/parallel_mh/exchange/exchanger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/exchange/exchanger.cpp

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/exchange/exchanger.cpp > CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.i

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/parallel_mh/exchange/exchanger.cpp -o CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.s

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.provides: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.provides

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o


src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o: ../src/include/kahiplib/lib/tools/graph_communication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/tools/graph_communication.cpp

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/tools/graph_communication.cpp > CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.i

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/tools/graph_communication.cpp -o CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.s

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.provides: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.provides

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o


src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/flags.make
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o: ../src/include/kahiplib/lib/tools/mpi_tools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/tools/mpi_tools.cpp

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/tools/mpi_tools.cpp > CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.i

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/tools/mpi_tools.cpp -o CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.s

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.provides: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.provides

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o


# Object files for target libkaffpa_parallel
libkaffpa_parallel_OBJECTS = \
"CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o" \
"CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o" \
"CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o" \
"CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o" \
"CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o" \
"CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o" \
"CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o"

# External object files for target libkaffpa_parallel
libkaffpa_parallel_EXTERNAL_OBJECTS =

src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build.make
src/include/kahiplib/liblibkaffpa_parallel.a: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library liblibkaffpa_parallel.a"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && $(CMAKE_COMMAND) -P CMakeFiles/libkaffpa_parallel.dir/cmake_clean_target.cmake
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libkaffpa_parallel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build: src/include/kahiplib/liblibkaffpa_parallel.a

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/build

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/parallel_mh_async.cpp.o.requires
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/population.cpp.o.requires
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/gal_combine.cpp.o.requires
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/galinier_combine/construct_partition.cpp.o.requires
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/parallel_mh/exchange/exchanger.cpp.o.requires
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/graph_communication.cpp.o.requires
src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires: src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/lib/tools/mpi_tools.cpp.o.requires

.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/requires

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/clean:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && $(CMAKE_COMMAND) -P CMakeFiles/libkaffpa_parallel.dir/cmake_clean.cmake
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/clean

src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/depend:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/include/kahiplib/CMakeFiles/libkaffpa_parallel.dir/depend
