# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yilia/桌面/CMKAE-PRACTICE/addLibrary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/hello.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/hello.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/hello.dir/flags.make

lib/CMakeFiles/hello.dir/hello.c.o: lib/CMakeFiles/hello.dir/flags.make
lib/CMakeFiles/hello.dir/hello.c.o: ../lib/hello.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/CMakeFiles/hello.dir/hello.c.o"
	cd /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello.dir/hello.c.o -c /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/lib/hello.c

lib/CMakeFiles/hello.dir/hello.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello.dir/hello.c.i"
	cd /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/lib/hello.c > CMakeFiles/hello.dir/hello.c.i

lib/CMakeFiles/hello.dir/hello.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello.dir/hello.c.s"
	cd /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/lib/hello.c -o CMakeFiles/hello.dir/hello.c.s

# Object files for target hello
hello_OBJECTS = \
"CMakeFiles/hello.dir/hello.c.o"

# External object files for target hello
hello_EXTERNAL_OBJECTS =

lib/libhello.a: lib/CMakeFiles/hello.dir/hello.c.o
lib/libhello.a: lib/CMakeFiles/hello.dir/build.make
lib/libhello.a: lib/CMakeFiles/hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libhello.a"
	cd /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean_target.cmake
	cd /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/hello.dir/build: lib/libhello.a

.PHONY : lib/CMakeFiles/hello.dir/build

lib/CMakeFiles/hello.dir/clean:
	cd /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/hello.dir/clean

lib/CMakeFiles/hello.dir/depend:
	cd /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yilia/桌面/CMKAE-PRACTICE/addLibrary /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/lib /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib /home/yilia/桌面/CMKAE-PRACTICE/addLibrary/build/lib/CMakeFiles/hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/hello.dir/depend

