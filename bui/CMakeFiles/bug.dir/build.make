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
include CMakeFiles/bug.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bug.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bug.dir/flags.make

CMakeFiles/bug.dir/src/apps/bug.cpp.o: CMakeFiles/bug.dir/flags.make
CMakeFiles/bug.dir/src/apps/bug.cpp.o: ../src/apps/bug.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bug.dir/src/apps/bug.cpp.o"
	/data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bug.dir/src/apps/bug.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/apps/bug.cpp

CMakeFiles/bug.dir/src/apps/bug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bug.dir/src/apps/bug.cpp.i"
	/data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/apps/bug.cpp > CMakeFiles/bug.dir/src/apps/bug.cpp.i

CMakeFiles/bug.dir/src/apps/bug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bug.dir/src/apps/bug.cpp.s"
	/data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/apps/bug.cpp -o CMakeFiles/bug.dir/src/apps/bug.cpp.s

CMakeFiles/bug.dir/src/apps/bug.cpp.o.requires:

.PHONY : CMakeFiles/bug.dir/src/apps/bug.cpp.o.requires

CMakeFiles/bug.dir/src/apps/bug.cpp.o.provides: CMakeFiles/bug.dir/src/apps/bug.cpp.o.requires
	$(MAKE) -f CMakeFiles/bug.dir/build.make CMakeFiles/bug.dir/src/apps/bug.cpp.o.provides.build
.PHONY : CMakeFiles/bug.dir/src/apps/bug.cpp.o.provides

CMakeFiles/bug.dir/src/apps/bug.cpp.o.provides.build: CMakeFiles/bug.dir/src/apps/bug.cpp.o


# Object files for target bug
bug_OBJECTS = \
"CMakeFiles/bug.dir/src/apps/bug.cpp.o"

# External object files for target bug
bug_EXTERNAL_OBJECTS =

bug: CMakeFiles/bug.dir/src/apps/bug.cpp.o
bug: CMakeFiles/bug.dir/build.make
bug: /data/opt/brew/lib/libboost_system-mt.so
bug: /data/opt/brew/lib/libboost_filesystem-mt.so
bug: /data/opt/brew/lib/libboost_regex-mt.so
bug: /data/opt/brew/lib/libboost_thread-mt.so
bug: /data/opt/brew/lib/libboost_program_options-mt.so
bug: /data/opt/brew/lib/libboost_date_time-mt.so
bug: /data/opt/brew/lib/libboost_chrono-mt.so
bug: /data/opt/brew/lib/libboost_atomic-mt.so
bug: /data/opt/brew/lib/libmpi.so
bug: src/include/kahiplib/liblibkaffpa.a
bug: src/include/kahiplib/liblibmapping.a
bug: /data/opt/brew/Cellar/gcc/5.2.0/lib64/libgomp.so
bug: /usr/lib64/libpthread.so
bug: CMakeFiles/bug.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bug"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bug.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bug.dir/build: bug

.PHONY : CMakeFiles/bug.dir/build

CMakeFiles/bug.dir/requires: CMakeFiles/bug.dir/src/apps/bug.cpp.o.requires

.PHONY : CMakeFiles/bug.dir/requires

CMakeFiles/bug.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bug.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bug.dir/clean

CMakeFiles/bug.dir/depend:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles/bug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bug.dir/depend

