# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/baastruph/projects/CxxDisruptor/trunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/baastruph/projects/CxxDisruptor/trunk

# Include any dependencies generated for this target.
include test/disruptor/CMakeFiles/garbageListTest.dir/depend.make

# Include the progress variables for this target.
include test/disruptor/CMakeFiles/garbageListTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/disruptor/CMakeFiles/garbageListTest.dir/flags.make

test/disruptor/garbageListTest.cpp: test/disruptor/garbageListTest.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating garbageListTest.cpp"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/python /usr/bin/cxxtestgen --error-printer -o /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/garbageListTest.cpp /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/garbageListTest.h

test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o: test/disruptor/CMakeFiles/garbageListTest.dir/flags.make
test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o: test/disruptor/garbageListTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o -c /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/garbageListTest.cpp

test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/garbageListTest.dir/garbageListTest.cpp.i"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/garbageListTest.cpp > CMakeFiles/garbageListTest.dir/garbageListTest.cpp.i

test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/garbageListTest.dir/garbageListTest.cpp.s"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/garbageListTest.cpp -o CMakeFiles/garbageListTest.dir/garbageListTest.cpp.s

test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.requires:
.PHONY : test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.requires

test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.provides: test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.requires
	$(MAKE) -f test/disruptor/CMakeFiles/garbageListTest.dir/build.make test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.provides.build
.PHONY : test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.provides

test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.provides.build: test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o

# Object files for target garbageListTest
garbageListTest_OBJECTS = \
"CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o"

# External object files for target garbageListTest
garbageListTest_EXTERNAL_OBJECTS =

test/disruptor/garbageListTest: test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o
test/disruptor/garbageListTest: test/disruptor/CMakeFiles/garbageListTest.dir/build.make
test/disruptor/garbageListTest: libCxxDisruptor.so
test/disruptor/garbageListTest: test/disruptor/CMakeFiles/garbageListTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable garbageListTest"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/garbageListTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/disruptor/CMakeFiles/garbageListTest.dir/build: test/disruptor/garbageListTest
.PHONY : test/disruptor/CMakeFiles/garbageListTest.dir/build

test/disruptor/CMakeFiles/garbageListTest.dir/requires: test/disruptor/CMakeFiles/garbageListTest.dir/garbageListTest.cpp.o.requires
.PHONY : test/disruptor/CMakeFiles/garbageListTest.dir/requires

test/disruptor/CMakeFiles/garbageListTest.dir/clean:
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && $(CMAKE_COMMAND) -P CMakeFiles/garbageListTest.dir/cmake_clean.cmake
.PHONY : test/disruptor/CMakeFiles/garbageListTest.dir/clean

test/disruptor/CMakeFiles/garbageListTest.dir/depend: test/disruptor/garbageListTest.cpp
	cd /home/baastruph/projects/CxxDisruptor/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/CMakeFiles/garbageListTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/disruptor/CMakeFiles/garbageListTest.dir/depend

