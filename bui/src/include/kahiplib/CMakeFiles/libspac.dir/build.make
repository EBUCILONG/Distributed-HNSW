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
include src/include/kahiplib/CMakeFiles/libspac.dir/depend.make

# Include the progress variables for this target.
include src/include/kahiplib/CMakeFiles/libspac.dir/progress.make

# Include the compile flags for this target's objects.
include src/include/kahiplib/CMakeFiles/libspac.dir/flags.make

src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o: src/include/kahiplib/CMakeFiles/libspac.dir/flags.make
src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o: ../src/include/kahiplib/lib/spac/spac.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/ccache /data/opt/brew/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libspac.dir/lib/spac/spac.cpp.o -c /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/spac/spac.cpp

src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libspac.dir/lib/spac/spac.cpp.i"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/spac/spac.cpp > CMakeFiles/libspac.dir/lib/spac/spac.cpp.i

src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libspac.dir/lib/spac/spac.cpp.s"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && /data/opt/brew/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib/lib/spac/spac.cpp -o CMakeFiles/libspac.dir/lib/spac/spac.cpp.s

src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.requires:

.PHONY : src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.requires

src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.provides: src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.requires
	$(MAKE) -f src/include/kahiplib/CMakeFiles/libspac.dir/build.make src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.provides.build
.PHONY : src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.provides

src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.provides.build: src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o


# Object files for target libspac
libspac_OBJECTS = \
"CMakeFiles/libspac.dir/lib/spac/spac.cpp.o"

# External object files for target libspac
libspac_EXTERNAL_OBJECTS =

src/include/kahiplib/liblibspac.a: src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o
src/include/kahiplib/liblibspac.a: src/include/kahiplib/CMakeFiles/libspac.dir/build.make
src/include/kahiplib/liblibspac.a: src/include/kahiplib/CMakeFiles/libspac.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblibspac.a"
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && $(CMAKE_COMMAND) -P CMakeFiles/libspac.dir/cmake_clean_target.cmake
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libspac.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/include/kahiplib/CMakeFiles/libspac.dir/build: src/include/kahiplib/liblibspac.a

.PHONY : src/include/kahiplib/CMakeFiles/libspac.dir/build

src/include/kahiplib/CMakeFiles/libspac.dir/requires: src/include/kahiplib/CMakeFiles/libspac.dir/lib/spac/spac.cpp.o.requires

.PHONY : src/include/kahiplib/CMakeFiles/libspac.dir/requires

src/include/kahiplib/CMakeFiles/libspac.dir/clean:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib && $(CMAKE_COMMAND) -P CMakeFiles/libspac.dir/cmake_clean.cmake
.PHONY : src/include/kahiplib/CMakeFiles/libspac.dir/clean

src/include/kahiplib/CMakeFiles/libspac.dir/depend:
	cd /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/sydeng/repositary/hnsw-repo/Distributed-HNSW /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/kahiplib /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/bui/src/include/kahiplib/CMakeFiles/libspac.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/include/kahiplib/CMakeFiles/libspac.dir/depend
