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
CMAKE_SOURCE_DIR = /home/jandres/CompScie/AIProjectv2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jandres/CompScie/AIProjectv2/build

# Include any dependencies generated for this target.
include src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/depend.make

# Include the progress variables for this target.
include src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/progress.make

# Include the compile flags for this target's objects.
include src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/flags.make

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/flags.make
src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o: ../src/intrinsic/GradientDescent.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jandres/CompScie/AIProjectv2/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o"
	cd /home/jandres/CompScie/AIProjectv2/build/src/intrinsic && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o -c /home/jandres/CompScie/AIProjectv2/src/intrinsic/GradientDescent.cpp

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.i"
	cd /home/jandres/CompScie/AIProjectv2/build/src/intrinsic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jandres/CompScie/AIProjectv2/src/intrinsic/GradientDescent.cpp > CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.i

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.s"
	cd /home/jandres/CompScie/AIProjectv2/build/src/intrinsic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jandres/CompScie/AIProjectv2/src/intrinsic/GradientDescent.cpp -o CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.s

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.requires:
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.requires

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.provides: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.requires
	$(MAKE) -f src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/build.make src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.provides.build
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.provides

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.provides.build: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/flags.make
src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o: ../src/intrinsic/TileCode.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jandres/CompScie/AIProjectv2/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o"
	cd /home/jandres/CompScie/AIProjectv2/build/src/intrinsic && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o -c /home/jandres/CompScie/AIProjectv2/src/intrinsic/TileCode.cpp

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.i"
	cd /home/jandres/CompScie/AIProjectv2/build/src/intrinsic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jandres/CompScie/AIProjectv2/src/intrinsic/TileCode.cpp > CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.i

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.s"
	cd /home/jandres/CompScie/AIProjectv2/build/src/intrinsic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jandres/CompScie/AIProjectv2/src/intrinsic/TileCode.cpp -o CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.s

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.requires:
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.requires

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.provides: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.requires
	$(MAKE) -f src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/build.make src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.provides.build
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.provides

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.provides.build: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o

aiproject2Intrinsic: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o
aiproject2Intrinsic: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o
aiproject2Intrinsic: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/build.make
.PHONY : aiproject2Intrinsic

# Rule to build all files generated by this target.
src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/build: aiproject2Intrinsic
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/build

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/requires: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/GradientDescent.cpp.o.requires
src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/requires: src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/TileCode.cpp.o.requires
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/requires

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/clean:
	cd /home/jandres/CompScie/AIProjectv2/build/src/intrinsic && $(CMAKE_COMMAND) -P CMakeFiles/aiproject2Intrinsic.dir/cmake_clean.cmake
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/clean

src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/depend:
	cd /home/jandres/CompScie/AIProjectv2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jandres/CompScie/AIProjectv2 /home/jandres/CompScie/AIProjectv2/src/intrinsic /home/jandres/CompScie/AIProjectv2/build /home/jandres/CompScie/AIProjectv2/build/src/intrinsic /home/jandres/CompScie/AIProjectv2/build/src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/intrinsic/CMakeFiles/aiproject2Intrinsic.dir/depend
