# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/oruqimaru/hnsw-repo/Distributed-HNSW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bug2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bug2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bug2.dir/flags.make

CMakeFiles/bug2.dir/src/apps/bug2.cpp.o: CMakeFiles/bug2.dir/flags.make
CMakeFiles/bug2.dir/src/apps/bug2.cpp.o: ../src/apps/bug2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bug2.dir/src/apps/bug2.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bug2.dir/src/apps/bug2.cpp.o -c /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/apps/bug2.cpp

CMakeFiles/bug2.dir/src/apps/bug2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bug2.dir/src/apps/bug2.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/apps/bug2.cpp > CMakeFiles/bug2.dir/src/apps/bug2.cpp.i

CMakeFiles/bug2.dir/src/apps/bug2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bug2.dir/src/apps/bug2.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/apps/bug2.cpp -o CMakeFiles/bug2.dir/src/apps/bug2.cpp.s

# Object files for target bug2
bug2_OBJECTS = \
"CMakeFiles/bug2.dir/src/apps/bug2.cpp.o"

# External object files for target bug2
bug2_EXTERNAL_OBJECTS =

bug2: CMakeFiles/bug2.dir/src/apps/bug2.cpp.o
bug2: CMakeFiles/bug2.dir/build.make
bug2: /usr/local/lib/libboost_system-mt.dylib
bug2: /usr/local/lib/libboost_filesystem-mt.dylib
bug2: /usr/local/lib/libboost_regex-mt.dylib
bug2: /usr/local/lib/libboost_thread-mt.dylib
bug2: /usr/local/lib/libboost_program_options-mt.dylib
bug2: /usr/local/lib/libboost_date_time-mt.dylib
bug2: /usr/local/lib/libboost_chrono-mt.dylib
bug2: /usr/local/lib/libboost_atomic-mt.dylib
bug2: /usr/local/Cellar/open-mpi/4.0.0/lib/libmpi.dylib
bug2: /usr/local/lib/libzookeeper_mt.dylib
bug2: src/include/kahiplib/liblibkaffpa.a
bug2: src/include/kahiplib/liblibmapping.a
bug2: CMakeFiles/bug2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bug2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bug2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bug2.dir/build: bug2

.PHONY : CMakeFiles/bug2.dir/build

CMakeFiles/bug2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bug2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bug2.dir/clean

CMakeFiles/bug2.dir/depend:
	cd /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oruqimaru/hnsw-repo/Distributed-HNSW /Users/oruqimaru/hnsw-repo/Distributed-HNSW /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug/CMakeFiles/bug2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bug2.dir/depend

