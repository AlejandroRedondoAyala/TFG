# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alejandro/TFG/catkin_ws/src/mavros/mavros

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alejandro/TFG/catkin_ws/build/mavros

# Include any dependencies generated for this target.
include gtest/gtest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include gtest/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include gtest/gtest/CMakeFiles/gtest.dir/flags.make

gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: gtest/gtest/CMakeFiles/gtest.dir/flags.make
gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: /usr/src/gtest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alejandro/TFG/catkin_ws/build/mavros/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/alejandro/TFG/catkin_ws/build/mavros/gtest/gtest && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /usr/src/gtest/src/gtest-all.cc

gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/alejandro/TFG/catkin_ws/build/mavros/gtest/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/src/gtest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/alejandro/TFG/catkin_ws/build/mavros/gtest/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/src/gtest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires:

.PHONY : gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides: gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires
	$(MAKE) -f gtest/gtest/CMakeFiles/gtest.dir/build.make gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build
.PHONY : gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides

gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build: gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o


# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

gtest/gtest/libgtest.so: gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
gtest/gtest/libgtest.so: gtest/gtest/CMakeFiles/gtest.dir/build.make
gtest/gtest/libgtest.so: gtest/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alejandro/TFG/catkin_ws/build/mavros/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libgtest.so"
	cd /home/alejandro/TFG/catkin_ws/build/mavros/gtest/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gtest/gtest/CMakeFiles/gtest.dir/build: gtest/gtest/libgtest.so

.PHONY : gtest/gtest/CMakeFiles/gtest.dir/build

gtest/gtest/CMakeFiles/gtest.dir/requires: gtest/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

.PHONY : gtest/gtest/CMakeFiles/gtest.dir/requires

gtest/gtest/CMakeFiles/gtest.dir/clean:
	cd /home/alejandro/TFG/catkin_ws/build/mavros/gtest/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : gtest/gtest/CMakeFiles/gtest.dir/clean

gtest/gtest/CMakeFiles/gtest.dir/depend:
	cd /home/alejandro/TFG/catkin_ws/build/mavros && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alejandro/TFG/catkin_ws/src/mavros/mavros /usr/src/gtest /home/alejandro/TFG/catkin_ws/build/mavros /home/alejandro/TFG/catkin_ws/build/mavros/gtest/gtest /home/alejandro/TFG/catkin_ws/build/mavros/gtest/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gtest/gtest/CMakeFiles/gtest.dir/depend

