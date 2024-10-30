# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/debian/dev/AOD/lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/debian/dev/AOD/lab1

# Include any dependencies generated for this target.
include CMakeFiles/BFS.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BFS.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BFS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BFS.dir/flags.make

CMakeFiles/BFS.dir/src/BFS.cpp.o: CMakeFiles/BFS.dir/flags.make
CMakeFiles/BFS.dir/src/BFS.cpp.o: src/BFS.cpp
CMakeFiles/BFS.dir/src/BFS.cpp.o: CMakeFiles/BFS.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/dev/AOD/lab1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BFS.dir/src/BFS.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BFS.dir/src/BFS.cpp.o -MF CMakeFiles/BFS.dir/src/BFS.cpp.o.d -o CMakeFiles/BFS.dir/src/BFS.cpp.o -c /home/debian/dev/AOD/lab1/src/BFS.cpp

CMakeFiles/BFS.dir/src/BFS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BFS.dir/src/BFS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/dev/AOD/lab1/src/BFS.cpp > CMakeFiles/BFS.dir/src/BFS.cpp.i

CMakeFiles/BFS.dir/src/BFS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BFS.dir/src/BFS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/dev/AOD/lab1/src/BFS.cpp -o CMakeFiles/BFS.dir/src/BFS.cpp.s

CMakeFiles/BFS.dir/src/graph_alg.cpp.o: CMakeFiles/BFS.dir/flags.make
CMakeFiles/BFS.dir/src/graph_alg.cpp.o: src/graph_alg.cpp
CMakeFiles/BFS.dir/src/graph_alg.cpp.o: CMakeFiles/BFS.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/dev/AOD/lab1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BFS.dir/src/graph_alg.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BFS.dir/src/graph_alg.cpp.o -MF CMakeFiles/BFS.dir/src/graph_alg.cpp.o.d -o CMakeFiles/BFS.dir/src/graph_alg.cpp.o -c /home/debian/dev/AOD/lab1/src/graph_alg.cpp

CMakeFiles/BFS.dir/src/graph_alg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BFS.dir/src/graph_alg.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/dev/AOD/lab1/src/graph_alg.cpp > CMakeFiles/BFS.dir/src/graph_alg.cpp.i

CMakeFiles/BFS.dir/src/graph_alg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BFS.dir/src/graph_alg.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/dev/AOD/lab1/src/graph_alg.cpp -o CMakeFiles/BFS.dir/src/graph_alg.cpp.s

# Object files for target BFS
BFS_OBJECTS = \
"CMakeFiles/BFS.dir/src/BFS.cpp.o" \
"CMakeFiles/BFS.dir/src/graph_alg.cpp.o"

# External object files for target BFS
BFS_EXTERNAL_OBJECTS =

BFS: CMakeFiles/BFS.dir/src/BFS.cpp.o
BFS: CMakeFiles/BFS.dir/src/graph_alg.cpp.o
BFS: CMakeFiles/BFS.dir/build.make
BFS: CMakeFiles/BFS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/debian/dev/AOD/lab1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable BFS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BFS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BFS.dir/build: BFS
.PHONY : CMakeFiles/BFS.dir/build

CMakeFiles/BFS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BFS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BFS.dir/clean

CMakeFiles/BFS.dir/depend:
	cd /home/debian/dev/AOD/lab1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/debian/dev/AOD/lab1 /home/debian/dev/AOD/lab1 /home/debian/dev/AOD/lab1 /home/debian/dev/AOD/lab1 /home/debian/dev/AOD/lab1/CMakeFiles/BFS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BFS.dir/depend

