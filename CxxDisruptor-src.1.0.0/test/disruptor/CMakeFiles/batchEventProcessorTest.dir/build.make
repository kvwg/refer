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
include test/disruptor/CMakeFiles/batchEventProcessorTest.dir/depend.make

# Include the progress variables for this target.
include test/disruptor/CMakeFiles/batchEventProcessorTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/disruptor/CMakeFiles/batchEventProcessorTest.dir/flags.make

test/disruptor/batchEventProcessorTest.cpp: test/disruptor/batchEventProcessorTest.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating batchEventProcessorTest.cpp"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/python /usr/bin/cxxtestgen --error-printer -o /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/batchEventProcessorTest.cpp /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/batchEventProcessorTest.h

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o: test/disruptor/CMakeFiles/batchEventProcessorTest.dir/flags.make
test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o: test/disruptor/batchEventProcessorTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/baastruph/projects/CxxDisruptor/trunk/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o -c /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/batchEventProcessorTest.cpp

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.i"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/batchEventProcessorTest.cpp > CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.i

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.s"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/batchEventProcessorTest.cpp -o CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.s

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.requires:
.PHONY : test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.requires

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.provides: test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.requires
	$(MAKE) -f test/disruptor/CMakeFiles/batchEventProcessorTest.dir/build.make test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.provides.build
.PHONY : test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.provides

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.provides.build: test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o

# Object files for target batchEventProcessorTest
batchEventProcessorTest_OBJECTS = \
"CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o"

# External object files for target batchEventProcessorTest
batchEventProcessorTest_EXTERNAL_OBJECTS =

test/disruptor/batchEventProcessorTest: test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o
test/disruptor/batchEventProcessorTest: test/disruptor/CMakeFiles/batchEventProcessorTest.dir/build.make
test/disruptor/batchEventProcessorTest: libCxxDisruptor.so
test/disruptor/batchEventProcessorTest: test/disruptor/CMakeFiles/batchEventProcessorTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable batchEventProcessorTest"
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/batchEventProcessorTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/disruptor/CMakeFiles/batchEventProcessorTest.dir/build: test/disruptor/batchEventProcessorTest
.PHONY : test/disruptor/CMakeFiles/batchEventProcessorTest.dir/build

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/requires: test/disruptor/CMakeFiles/batchEventProcessorTest.dir/batchEventProcessorTest.cpp.o.requires
.PHONY : test/disruptor/CMakeFiles/batchEventProcessorTest.dir/requires

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/clean:
	cd /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor && $(CMAKE_COMMAND) -P CMakeFiles/batchEventProcessorTest.dir/cmake_clean.cmake
.PHONY : test/disruptor/CMakeFiles/batchEventProcessorTest.dir/clean

test/disruptor/CMakeFiles/batchEventProcessorTest.dir/depend: test/disruptor/batchEventProcessorTest.cpp
	cd /home/baastruph/projects/CxxDisruptor/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor /home/baastruph/projects/CxxDisruptor/trunk /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor /home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/CMakeFiles/batchEventProcessorTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/disruptor/CMakeFiles/batchEventProcessorTest.dir/depend

