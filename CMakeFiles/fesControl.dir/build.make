# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/cnbi/dev/fesapps/fesjson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cnbi/dev/fesapps/fesjson

# Include any dependencies generated for this target.
include CMakeFiles/fesControl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fesControl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fesControl.dir/flags.make

CMakeFiles/fesControl.dir/main.cpp.o: CMakeFiles/fesControl.dir/flags.make
CMakeFiles/fesControl.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cnbi/dev/fesapps/fesjson/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fesControl.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fesControl.dir/main.cpp.o -c /home/cnbi/dev/fesapps/fesjson/main.cpp

CMakeFiles/fesControl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fesControl.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cnbi/dev/fesapps/fesjson/main.cpp > CMakeFiles/fesControl.dir/main.cpp.i

CMakeFiles/fesControl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fesControl.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cnbi/dev/fesapps/fesjson/main.cpp -o CMakeFiles/fesControl.dir/main.cpp.s

CMakeFiles/fesControl.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/fesControl.dir/main.cpp.o.requires

CMakeFiles/fesControl.dir/main.cpp.o.provides: CMakeFiles/fesControl.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/fesControl.dir/build.make CMakeFiles/fesControl.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/fesControl.dir/main.cpp.o.provides

CMakeFiles/fesControl.dir/main.cpp.o.provides.build: CMakeFiles/fesControl.dir/main.cpp.o


CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o: CMakeFiles/fesControl.dir/flags.make
CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o: src/GUI/GUIFESStimulator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cnbi/dev/fesapps/fesjson/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o -c /home/cnbi/dev/fesapps/fesjson/src/GUI/GUIFESStimulator.cpp

CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cnbi/dev/fesapps/fesjson/src/GUI/GUIFESStimulator.cpp > CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.i

CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cnbi/dev/fesapps/fesjson/src/GUI/GUIFESStimulator.cpp -o CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.s

CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.requires:

.PHONY : CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.requires

CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.provides: CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.requires
	$(MAKE) -f CMakeFiles/fesControl.dir/build.make CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.provides.build
.PHONY : CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.provides

CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.provides.build: CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o


# Object files for target fesControl
fesControl_OBJECTS = \
"CMakeFiles/fesControl.dir/main.cpp.o" \
"CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o"

# External object files for target fesControl
fesControl_EXTERNAL_OBJECTS =

build/fesControl: CMakeFiles/fesControl.dir/main.cpp.o
build/fesControl: CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o
build/fesControl: CMakeFiles/fesControl.dir/build.make
build/fesControl: libfescontrol.a
build/fesControl: CMakeFiles/fesControl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cnbi/dev/fesapps/fesjson/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable build/fesControl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fesControl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fesControl.dir/build: build/fesControl

.PHONY : CMakeFiles/fesControl.dir/build

CMakeFiles/fesControl.dir/requires: CMakeFiles/fesControl.dir/main.cpp.o.requires
CMakeFiles/fesControl.dir/requires: CMakeFiles/fesControl.dir/src/GUI/GUIFESStimulator.cpp.o.requires

.PHONY : CMakeFiles/fesControl.dir/requires

CMakeFiles/fesControl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fesControl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fesControl.dir/clean

CMakeFiles/fesControl.dir/depend:
	cd /home/cnbi/dev/fesapps/fesjson && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cnbi/dev/fesapps/fesjson /home/cnbi/dev/fesapps/fesjson /home/cnbi/dev/fesapps/fesjson /home/cnbi/dev/fesapps/fesjson /home/cnbi/dev/fesapps/fesjson/CMakeFiles/fesControl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fesControl.dir/depend
