# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/f/TestCode/c++/QIC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/f/TestCode/c++/QIC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/QIC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/QIC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QIC.dir/flags.make

CMakeFiles/QIC.dir/main.cpp.o: CMakeFiles/QIC.dir/flags.make
CMakeFiles/QIC.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/f/TestCode/c++/QIC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QIC.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QIC.dir/main.cpp.o -c /cygdrive/f/TestCode/c++/QIC/main.cpp

CMakeFiles/QIC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QIC.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/f/TestCode/c++/QIC/main.cpp > CMakeFiles/QIC.dir/main.cpp.i

CMakeFiles/QIC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QIC.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/f/TestCode/c++/QIC/main.cpp -o CMakeFiles/QIC.dir/main.cpp.s

CMakeFiles/QIC.dir/sfmt.cpp.o: CMakeFiles/QIC.dir/flags.make
CMakeFiles/QIC.dir/sfmt.cpp.o: ../sfmt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/f/TestCode/c++/QIC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/QIC.dir/sfmt.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QIC.dir/sfmt.cpp.o -c /cygdrive/f/TestCode/c++/QIC/sfmt.cpp

CMakeFiles/QIC.dir/sfmt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QIC.dir/sfmt.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/f/TestCode/c++/QIC/sfmt.cpp > CMakeFiles/QIC.dir/sfmt.cpp.i

CMakeFiles/QIC.dir/sfmt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QIC.dir/sfmt.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/f/TestCode/c++/QIC/sfmt.cpp -o CMakeFiles/QIC.dir/sfmt.cpp.s

# Object files for target QIC
QIC_OBJECTS = \
"CMakeFiles/QIC.dir/main.cpp.o" \
"CMakeFiles/QIC.dir/sfmt.cpp.o"

# External object files for target QIC
QIC_EXTERNAL_OBJECTS =

QIC.exe: CMakeFiles/QIC.dir/main.cpp.o
QIC.exe: CMakeFiles/QIC.dir/sfmt.cpp.o
QIC.exe: CMakeFiles/QIC.dir/build.make
QIC.exe: CMakeFiles/QIC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/f/TestCode/c++/QIC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable QIC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QIC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QIC.dir/build: QIC.exe

.PHONY : CMakeFiles/QIC.dir/build

CMakeFiles/QIC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QIC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QIC.dir/clean

CMakeFiles/QIC.dir/depend:
	cd /cygdrive/f/TestCode/c++/QIC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/f/TestCode/c++/QIC /cygdrive/f/TestCode/c++/QIC /cygdrive/f/TestCode/c++/QIC/cmake-build-debug /cygdrive/f/TestCode/c++/QIC/cmake-build-debug /cygdrive/f/TestCode/c++/QIC/cmake-build-debug/CMakeFiles/QIC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QIC.dir/depend
