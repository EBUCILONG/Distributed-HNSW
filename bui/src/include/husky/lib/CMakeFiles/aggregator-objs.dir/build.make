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
include src/include/husky/lib/CMakeFiles/aggregator-objs.dir/depend.make

# Include the progress variables for this target.
include src/include/husky/lib/CMakeFiles/aggregator-objs.dir/progress.make

# Include the compile flags for this target's objects.
include src/include/husky/lib/CMakeFiles/aggregator-objs.dir/flags.make

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/flags.make
src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o: ../src/include/husky/lib/aggregator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aggregator-objs.dir/aggregator.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator.cpp

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aggregator-objs.dir/aggregator.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator.cpp > CMakeFiles/aggregator-objs.dir/aggregator.cpp.i

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aggregator-objs.dir/aggregator.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator.cpp -o CMakeFiles/aggregator-objs.dir/aggregator.cpp.s

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.requires:

.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.requires

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.provides: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.requires
	$(MAKE) -f src/include/husky/lib/CMakeFiles/aggregator-objs.dir/build.make src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.provides.build
.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.provides

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.provides.build: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o


src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/flags.make
src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o: ../src/include/husky/lib/aggregator_object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator_object.cpp

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator_object.cpp > CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.i

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator_object.cpp -o CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.s

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.requires:

.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.requires

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.provides: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.requires
	$(MAKE) -f src/include/husky/lib/CMakeFiles/aggregator-objs.dir/build.make src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.provides.build
.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.provides

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.provides.build: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o


src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/flags.make
src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o: ../src/include/husky/lib/aggregator_factory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator_factory.cpp

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator_factory.cpp > CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.i

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib/aggregator_factory.cpp -o CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.s

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.requires:

.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.requires

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.provides: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.requires
	$(MAKE) -f src/include/husky/lib/CMakeFiles/aggregator-objs.dir/build.make src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.provides.build
.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.provides

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.provides.build: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o


aggregator-objs: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o
aggregator-objs: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o
aggregator-objs: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o
aggregator-objs: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/build.make

.PHONY : aggregator-objs

# Rule to build all files generated by this target.
src/include/husky/lib/CMakeFiles/aggregator-objs.dir/build: aggregator-objs

.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/build

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/requires: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator.cpp.o.requires
src/include/husky/lib/CMakeFiles/aggregator-objs.dir/requires: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_object.cpp.o.requires
src/include/husky/lib/CMakeFiles/aggregator-objs.dir/requires: src/include/husky/lib/CMakeFiles/aggregator-objs.dir/aggregator_factory.cpp.o.requires

.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/requires

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/clean:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib && $(CMAKE_COMMAND) -P CMakeFiles/aggregator-objs.dir/cmake_clean.cmake
.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/clean

src/include/husky/lib/CMakeFiles/aggregator-objs.dir/depend:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/lib /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/lib/CMakeFiles/aggregator-objs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/include/husky/lib/CMakeFiles/aggregator-objs.dir/depend
