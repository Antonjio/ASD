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
CMAKE_SOURCE_DIR = /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MinHeap.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MinHeap.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MinHeap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MinHeap.dir/flags.make

CMakeFiles/MinHeap.dir/main.cpp.o: CMakeFiles/MinHeap.dir/flags.make
CMakeFiles/MinHeap.dir/main.cpp.o: ../main.cpp
CMakeFiles/MinHeap.dir/main.cpp.o: CMakeFiles/MinHeap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MinHeap.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MinHeap.dir/main.cpp.o -MF CMakeFiles/MinHeap.dir/main.cpp.o.d -o CMakeFiles/MinHeap.dir/main.cpp.o -c /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/main.cpp

CMakeFiles/MinHeap.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MinHeap.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/main.cpp > CMakeFiles/MinHeap.dir/main.cpp.i

CMakeFiles/MinHeap.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MinHeap.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/main.cpp -o CMakeFiles/MinHeap.dir/main.cpp.s

# Object files for target MinHeap
MinHeap_OBJECTS = \
"CMakeFiles/MinHeap.dir/main.cpp.o"

# External object files for target MinHeap
MinHeap_EXTERNAL_OBJECTS =

MinHeap: CMakeFiles/MinHeap.dir/main.cpp.o
MinHeap: CMakeFiles/MinHeap.dir/build.make
MinHeap: CMakeFiles/MinHeap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MinHeap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MinHeap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MinHeap.dir/build: MinHeap
.PHONY : CMakeFiles/MinHeap.dir/build

CMakeFiles/MinHeap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MinHeap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MinHeap.dir/clean

CMakeFiles/MinHeap.dir/depend:
	cd /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/cmake-build-debug /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/cmake-build-debug /mnt/c/Users/anton/Desktop/ASD/ASD/Heap/MinHeap/cmake-build-debug/CMakeFiles/MinHeap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MinHeap.dir/depend

