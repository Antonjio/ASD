# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RB.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RB.dir/flags.make

CMakeFiles/RB.dir/main.cpp.o: CMakeFiles/RB.dir/flags.make
CMakeFiles/RB.dir/main.cpp.o: ../main.cpp
CMakeFiles/RB.dir/main.cpp.o: CMakeFiles/RB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RB.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RB.dir/main.cpp.o -MF CMakeFiles/RB.dir/main.cpp.o.d -o CMakeFiles/RB.dir/main.cpp.o -c /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/main.cpp

CMakeFiles/RB.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RB.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/main.cpp > CMakeFiles/RB.dir/main.cpp.i

CMakeFiles/RB.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RB.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/main.cpp -o CMakeFiles/RB.dir/main.cpp.s

# Object files for target RB
RB_OBJECTS = \
"CMakeFiles/RB.dir/main.cpp.o"

# External object files for target RB
RB_EXTERNAL_OBJECTS =

RB: CMakeFiles/RB.dir/main.cpp.o
RB: CMakeFiles/RB.dir/build.make
RB: CMakeFiles/RB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RB.dir/build: RB
.PHONY : CMakeFiles/RB.dir/build

CMakeFiles/RB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RB.dir/clean

CMakeFiles/RB.dir/depend:
	cd /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/cmake-build-debug /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/cmake-build-debug /mnt/c/Users/anton/Desktop/ASD/FeroneCodice/RB/cmake-build-debug/CMakeFiles/RB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RB.dir/depend

