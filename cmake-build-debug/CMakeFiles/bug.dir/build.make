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
include CMakeFiles/bug.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bug.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bug.dir/flags.make

CMakeFiles/bug.dir/src/apps/bug.cpp.o: CMakeFiles/bug.dir/flags.make
CMakeFiles/bug.dir/src/apps/bug.cpp.o: ../src/apps/bug.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bug.dir/src/apps/bug.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bug.dir/src/apps/bug.cpp.o -c /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/apps/bug.cpp

CMakeFiles/bug.dir/src/apps/bug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bug.dir/src/apps/bug.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/apps/bug.cpp > CMakeFiles/bug.dir/src/apps/bug.cpp.i

CMakeFiles/bug.dir/src/apps/bug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bug.dir/src/apps/bug.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/apps/bug.cpp -o CMakeFiles/bug.dir/src/apps/bug.cpp.s

CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.o: CMakeFiles/bug.dir/flags.make
CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.o: ../src/include/dhnswlib/slave.hpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.o -c /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/include/dhnswlib/slave.hpp.cpp

CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/include/dhnswlib/slave.hpp.cpp > CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.i

CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/oruqimaru/hnsw-repo/Distributed-HNSW/src/include/dhnswlib/slave.hpp.cpp -o CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.s

# Object files for target bug
bug_OBJECTS = \
"CMakeFiles/bug.dir/src/apps/bug.cpp.o" \
"CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.o"

# External object files for target bug
bug_EXTERNAL_OBJECTS =

bug: CMakeFiles/bug.dir/src/apps/bug.cpp.o
bug: CMakeFiles/bug.dir/src/include/dhnswlib/slave.hpp.cpp.o
bug: CMakeFiles/bug.dir/build.make
bug: /usr/local/lib/libboost_system-mt.dylib
bug: /usr/local/lib/libboost_filesystem-mt.dylib
bug: /usr/local/lib/libboost_regex-mt.dylib
bug: /usr/local/lib/libboost_thread-mt.dylib
bug: /usr/local/lib/libboost_program_options-mt.dylib
bug: /usr/local/lib/libboost_date_time-mt.dylib
bug: /usr/local/lib/libboost_chrono-mt.dylib
bug: /usr/local/lib/libboost_atomic-mt.dylib
bug: /usr/local/Cellar/open-mpi/4.0.0/lib/libmpi.dylib
bug: src/include/kahiplib/liblibkaffpa.a
bug: src/include/kahiplib/liblibmapping.a
bug: CMakeFiles/bug.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bug"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bug.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bug.dir/build: bug

.PHONY : CMakeFiles/bug.dir/build

CMakeFiles/bug.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bug.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bug.dir/clean

CMakeFiles/bug.dir/depend:
	cd /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oruqimaru/hnsw-repo/Distributed-HNSW /Users/oruqimaru/hnsw-repo/Distributed-HNSW /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug /Users/oruqimaru/hnsw-repo/Distributed-HNSW/cmake-build-debug/CMakeFiles/bug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bug.dir/depend

