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
include test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/depend.make

# Include the progress variables for this target.
include test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/flags.make

test/atomic/atomicInt64ArrayTest.cpp: test/atomic/atomicInt64ArrayTest.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating atomicInt64ArrayTest.cpp"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/atomic && /usr/bin/python /usr/bin/cxxtestgen --error-printer -o /home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64ArrayTest.cpp /home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64ArrayTest.h

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o: test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/flags.make
test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o: test/atomic/atomicInt64ArrayTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/atomic && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o -c /home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64ArrayTest.cpp

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.i"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/atomic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64ArrayTest.cpp > CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.i

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.s"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/atomic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64ArrayTest.cpp -o CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.s

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.requires:
.PHONY : test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.requires

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.provides: test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.requires
	$(MAKE) -f test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/build.make test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.provides.build
.PHONY : test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.provides

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.provides.build: test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o

# Object files for target atomicInt64ArrayTest
atomicInt64ArrayTest_OBJECTS = \
"CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o"

# External object files for target atomicInt64ArrayTest
atomicInt64ArrayTest_EXTERNAL_OBJECTS =

test/atomic/atomicInt64ArrayTest: test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o
test/atomic/atomicInt64ArrayTest: test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/build.make
test/atomic/atomicInt64ArrayTest: libCxxDisruptor.so
test/atomic/atomicInt64ArrayTest: test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable atomicInt64ArrayTest"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/atomic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/atomicInt64ArrayTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/build: test/atomic/atomicInt64ArrayTest
.PHONY : test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/build

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/requires: test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/atomicInt64ArrayTest.cpp.o.requires
.PHONY : test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/requires

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/clean:
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/atomic && $(CMAKE_COMMAND) -P CMakeFiles/atomicInt64ArrayTest.dir/cmake_clean.cmake
.PHONY : test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/clean

test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/depend: test/atomic/atomicInt64ArrayTest.cpp
	cd /home/baastruph/projects/CxxDisruptor/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/atomic /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/atomic /home/baastruph/projects/CxxDisruptor/trunk/test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/atomic/CMakeFiles/atomicInt64ArrayTest.dir/depend
