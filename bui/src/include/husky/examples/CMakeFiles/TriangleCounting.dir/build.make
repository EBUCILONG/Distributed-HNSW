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
include src/include/husky/examples/CMakeFiles/TriangleCounting.dir/depend.make

# Include the progress variables for this target.
include src/include/husky/examples/CMakeFiles/TriangleCounting.dir/progress.make

# Include the compile flags for this target's objects.
include src/include/husky/examples/CMakeFiles/TriangleCounting.dir/flags.make

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o: src/include/husky/examples/CMakeFiles/TriangleCounting.dir/flags.make
src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o: ../src/include/husky/examples/triangle_counting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/examples && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/examples/triangle_counting.cpp

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/examples && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/examples/triangle_counting.cpp > CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.i

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/examples && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/examples/triangle_counting.cpp -o CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.s

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.requires:

.PHONY : src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.requires

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.provides: src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.requires
	$(MAKE) -f src/include/husky/examples/CMakeFiles/TriangleCounting.dir/build.make src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.provides.build
.PHONY : src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.provides

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.provides.build: src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o


# Object files for target TriangleCounting
TriangleCounting_OBJECTS = \
"CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o"

# External object files for target TriangleCounting
TriangleCounting_EXTERNAL_OBJECTS =

src/include/husky/TriangleCounting: src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o
src/include/husky/TriangleCounting: src/include/husky/examples/CMakeFiles/TriangleCounting.dir/build.make
src/include/husky/TriangleCounting: src/include/husky/lib/libhusky-lib.a
src/include/husky/TriangleCounting: src/include/husky/io/libhusky-io.a
src/include/husky/TriangleCounting: src/include/husky/core/libhusky-core.a
src/include/husky/TriangleCounting: src/include/husky/base/libhusky-base.a
src/include/husky/TriangleCounting: src/include/husky/lib/libglog.a
src/include/husky/TriangleCounting: /usr/local/lib/libzmq.so
src/include/husky/TriangleCounting: /usr/lib64/libtcmalloc.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_system-mt.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_filesystem-mt.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_regex-mt.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_thread-mt.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_program_options-mt.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_date_time-mt.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_chrono-mt.so
src/include/husky/TriangleCounting: /data/opt/brew/lib/libboost_atomic-mt.so
src/include/husky/TriangleCounting: /usr/local/lib/libthrift.so
src/include/husky/TriangleCounting: src/include/husky/examples/CMakeFiles/TriangleCounting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../TriangleCounting"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TriangleCounting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/include/husky/examples/CMakeFiles/TriangleCounting.dir/build: src/include/husky/TriangleCounting

.PHONY : src/include/husky/examples/CMakeFiles/TriangleCounting.dir/build

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/requires: src/include/husky/examples/CMakeFiles/TriangleCounting.dir/triangle_counting.cpp.o.requires

.PHONY : src/include/husky/examples/CMakeFiles/TriangleCounting.dir/requires

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/clean:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/examples && $(CMAKE_COMMAND) -P CMakeFiles/TriangleCounting.dir/cmake_clean.cmake
.PHONY : src/include/husky/examples/CMakeFiles/TriangleCounting.dir/clean

src/include/husky/examples/CMakeFiles/TriangleCounting.dir/depend:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/examples /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/examples /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/examples/CMakeFiles/TriangleCounting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/include/husky/examples/CMakeFiles/TriangleCounting.dir/depend

