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
include test/base/CMakeFiles/identityHashMapTest.dir/depend.make

# Include the progress variables for this target.
include test/base/CMakeFiles/identityHashMapTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/base/CMakeFiles/identityHashMapTest.dir/flags.make

test/base/identityHashMapTest.cpp: test/base/identityHashMapTest.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating identityHashMapTest.cpp"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/base && /usr/bin/python /usr/bin/cxxtestgen --error-printer -o /home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashMapTest.cpp /home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashMapTest.h

test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o: test/base/CMakeFiles/identityHashMapTest.dir/flags.make
test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o: test/base/identityHashMapTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o -c /home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashMapTest.cpp

test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.i"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashMapTest.cpp > CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.i

test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.s"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashMapTest.cpp -o CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.s

test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.requires:
.PHONY : test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.requires

test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.provides: test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.requires
	$(MAKE) -f test/base/CMakeFiles/identityHashMapTest.dir/build.make test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.provides.build
.PHONY : test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.provides

test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.provides.build: test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o

# Object files for target identityHashMapTest
identityHashMapTest_OBJECTS = \
"CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o"

# External object files for target identityHashMapTest
identityHashMapTest_EXTERNAL_OBJECTS =

test/base/identityHashMapTest: test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o
test/base/identityHashMapTest: test/base/CMakeFiles/identityHashMapTest.dir/build.make
test/base/identityHashMapTest: libCxxDisruptor.so
test/base/identityHashMapTest: test/base/CMakeFiles/identityHashMapTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable identityHashMapTest"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/identityHashMapTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/base/CMakeFiles/identityHashMapTest.dir/build: test/base/identityHashMapTest
.PHONY : test/base/CMakeFiles/identityHashMapTest.dir/build

test/base/CMakeFiles/identityHashMapTest.dir/requires: test/base/CMakeFiles/identityHashMapTest.dir/identityHashMapTest.cpp.o.requires
.PHONY : test/base/CMakeFiles/identityHashMapTest.dir/requires

test/base/CMakeFiles/identityHashMapTest.dir/clean:
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/base && $(CMAKE_COMMAND) -P CMakeFiles/identityHashMapTest.dir/cmake_clean.cmake
.PHONY : test/base/CMakeFiles/identityHashMapTest.dir/clean

test/base/CMakeFiles/identityHashMapTest.dir/depend: test/base/identityHashMapTest.cpp
	cd /home/baastruph/projects/CxxDisruptor/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/base /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/base /home/baastruph/projects/CxxDisruptor/trunk/test/base/CMakeFiles/identityHashMapTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/base/CMakeFiles/identityHashMapTest.dir/depend

