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
include CMakeFiles/interface_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/interface_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/interface_test.dir/flags.make

# Object files for target interface_test
interface_test_OBJECTS =

# External object files for target interface_test
interface_test_EXTERNAL_OBJECTS =

interface_test: CMakeFiles/interface_test.dir/build.make
interface_test: src/include/kahiplib/liblibkaffpa.a
interface_test: src/include/kahiplib/liblibmapping.a
interface_test: /data/opt/brew/Cellar/gcc/5.2.0/lib64/libgomp.so
interface_test: /usr/lib64/libpthread.so
interface_test: CMakeFiles/interface_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX executable interface_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interface_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/interface_test.dir/build: interface_test

.PHONY : CMakeFiles/interface_test.dir/build

CMakeFiles/interface_test.dir/requires:

.PHONY : CMakeFiles/interface_test.dir/requires

CMakeFiles/interface_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/interface_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/interface_test.dir/clean

CMakeFiles/interface_test.dir/depend:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles/interface_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/interface_test.dir/depend
