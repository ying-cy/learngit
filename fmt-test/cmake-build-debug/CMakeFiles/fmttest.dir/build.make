# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/yilia/software/CLion-2020.1/clion-2020.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yilia/software/CLion-2020.1/clion-2020.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yilia/桌面/CMKAE-PRACTICE/fmt-test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/fmttest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fmttest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fmttest.dir/flags.make

CMakeFiles/fmttest.dir/test.cpp.o: CMakeFiles/fmttest.dir/flags.make
CMakeFiles/fmttest.dir/test.cpp.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yilia/桌面/CMKAE-PRACTICE/fmt-test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fmttest.dir/test.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fmttest.dir/test.cpp.o -c /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/test.cpp

CMakeFiles/fmttest.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fmttest.dir/test.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/test.cpp > CMakeFiles/fmttest.dir/test.cpp.i

CMakeFiles/fmttest.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fmttest.dir/test.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/test.cpp -o CMakeFiles/fmttest.dir/test.cpp.s

# Object files for target fmttest
fmttest_OBJECTS = \
"CMakeFiles/fmttest.dir/test.cpp.o"

# External object files for target fmttest
fmttest_EXTERNAL_OBJECTS =

fmttest: CMakeFiles/fmttest.dir/test.cpp.o
fmttest: CMakeFiles/fmttest.dir/build.make
fmttest: CMakeFiles/fmttest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yilia/桌面/CMKAE-PRACTICE/fmt-test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fmttest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fmttest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fmttest.dir/build: fmttest

.PHONY : CMakeFiles/fmttest.dir/build

CMakeFiles/fmttest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fmttest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fmttest.dir/clean

CMakeFiles/fmttest.dir/depend:
	cd /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yilia/桌面/CMKAE-PRACTICE/fmt-test /home/yilia/桌面/CMKAE-PRACTICE/fmt-test /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/cmake-build-debug /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/cmake-build-debug /home/yilia/桌面/CMKAE-PRACTICE/fmt-test/cmake-build-debug/CMakeFiles/fmttest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fmttest.dir/depend
