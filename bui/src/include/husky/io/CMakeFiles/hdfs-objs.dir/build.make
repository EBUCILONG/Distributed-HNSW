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
include src/include/husky/io/CMakeFiles/hdfs-objs.dir/depend.make

# Include the progress variables for this target.
include src/include/husky/io/CMakeFiles/hdfs-objs.dir/progress.make

# Include the compile flags for this target's objects.
include src/include/husky/io/CMakeFiles/hdfs-objs.dir/flags.make

src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o: src/include/husky/io/CMakeFiles/hdfs-objs.dir/flags.make
src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o: ../src/include/husky/io/hdfs_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/io && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/io/hdfs_manager.cpp

src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/io && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/io/hdfs_manager.cpp > CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.i

src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/io && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/io/hdfs_manager.cpp -o CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.s

src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.requires:

.PHONY : src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.requires

src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.provides: src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.requires
	$(MAKE) -f src/include/husky/io/CMakeFiles/hdfs-objs.dir/build.make src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.provides.build
.PHONY : src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.provides

src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.provides.build: src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o


hdfs-objs: src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o
hdfs-objs: src/include/husky/io/CMakeFiles/hdfs-objs.dir/build.make

.PHONY : hdfs-objs

# Rule to build all files generated by this target.
src/include/husky/io/CMakeFiles/hdfs-objs.dir/build: hdfs-objs

.PHONY : src/include/husky/io/CMakeFiles/hdfs-objs.dir/build

src/include/husky/io/CMakeFiles/hdfs-objs.dir/requires: src/include/husky/io/CMakeFiles/hdfs-objs.dir/hdfs_manager.cpp.o.requires

.PHONY : src/include/husky/io/CMakeFiles/hdfs-objs.dir/requires

src/include/husky/io/CMakeFiles/hdfs-objs.dir/clean:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/io && $(CMAKE_COMMAND) -P CMakeFiles/hdfs-objs.dir/cmake_clean.cmake
.PHONY : src/include/husky/io/CMakeFiles/hdfs-objs.dir/clean

src/include/husky/io/CMakeFiles/hdfs-objs.dir/depend:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/husky/io /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/io /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/husky/io/CMakeFiles/hdfs-objs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/include/husky/io/CMakeFiles/hdfs-objs.dir/depend

