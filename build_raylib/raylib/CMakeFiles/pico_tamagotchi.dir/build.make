# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kadeangell/Documents/Tamagotchi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kadeangell/Documents/Tamagotchi/build_raylib

# Include any dependencies generated for this target.
include raylib/CMakeFiles/pico_tamagotchi.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include raylib/CMakeFiles/pico_tamagotchi.dir/compiler_depend.make

# Include the progress variables for this target.
include raylib/CMakeFiles/pico_tamagotchi.dir/progress.make

# Include the compile flags for this target's objects.
include raylib/CMakeFiles/pico_tamagotchi.dir/flags.make

raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.o: raylib/CMakeFiles/pico_tamagotchi.dir/flags.make
raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.o: /Users/kadeangell/Documents/Tamagotchi/raylib/main.cpp
raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.o: raylib/CMakeFiles/pico_tamagotchi.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kadeangell/Documents/Tamagotchi/build_raylib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.o"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.o -MF CMakeFiles/pico_tamagotchi.dir/main.cpp.o.d -o CMakeFiles/pico_tamagotchi.dir/main.cpp.o -c /Users/kadeangell/Documents/Tamagotchi/raylib/main.cpp

raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pico_tamagotchi.dir/main.cpp.i"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kadeangell/Documents/Tamagotchi/raylib/main.cpp > CMakeFiles/pico_tamagotchi.dir/main.cpp.i

raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pico_tamagotchi.dir/main.cpp.s"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kadeangell/Documents/Tamagotchi/raylib/main.cpp -o CMakeFiles/pico_tamagotchi.dir/main.cpp.s

raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o: raylib/CMakeFiles/pico_tamagotchi.dir/flags.make
raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o: /Users/kadeangell/Documents/Tamagotchi/Tamagotchi.cpp
raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o: raylib/CMakeFiles/pico_tamagotchi.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kadeangell/Documents/Tamagotchi/build_raylib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o -MF CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o.d -o CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o -c /Users/kadeangell/Documents/Tamagotchi/Tamagotchi.cpp

raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.i"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kadeangell/Documents/Tamagotchi/Tamagotchi.cpp > CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.i

raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.s"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kadeangell/Documents/Tamagotchi/Tamagotchi.cpp -o CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.s

raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o: raylib/CMakeFiles/pico_tamagotchi.dir/flags.make
raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o: /Users/kadeangell/Documents/Tamagotchi/raylib/RaylibDisplay.cpp
raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o: raylib/CMakeFiles/pico_tamagotchi.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kadeangell/Documents/Tamagotchi/build_raylib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o -MF CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o.d -o CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o -c /Users/kadeangell/Documents/Tamagotchi/raylib/RaylibDisplay.cpp

raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.i"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kadeangell/Documents/Tamagotchi/raylib/RaylibDisplay.cpp > CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.i

raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.s"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kadeangell/Documents/Tamagotchi/raylib/RaylibDisplay.cpp -o CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.s

# Object files for target pico_tamagotchi
pico_tamagotchi_OBJECTS = \
"CMakeFiles/pico_tamagotchi.dir/main.cpp.o" \
"CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o" \
"CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o"

# External object files for target pico_tamagotchi
pico_tamagotchi_EXTERNAL_OBJECTS =

raylib/pico_tamagotchi: raylib/CMakeFiles/pico_tamagotchi.dir/main.cpp.o
raylib/pico_tamagotchi: raylib/CMakeFiles/pico_tamagotchi.dir/__/Tamagotchi.cpp.o
raylib/pico_tamagotchi: raylib/CMakeFiles/pico_tamagotchi.dir/RaylibDisplay.cpp.o
raylib/pico_tamagotchi: raylib/CMakeFiles/pico_tamagotchi.dir/build.make
raylib/pico_tamagotchi: /usr/local/Cellar/raylib/4.5.0/lib/libraylib.dylib
raylib/pico_tamagotchi: raylib/CMakeFiles/pico_tamagotchi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kadeangell/Documents/Tamagotchi/build_raylib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable pico_tamagotchi"
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pico_tamagotchi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
raylib/CMakeFiles/pico_tamagotchi.dir/build: raylib/pico_tamagotchi
.PHONY : raylib/CMakeFiles/pico_tamagotchi.dir/build

raylib/CMakeFiles/pico_tamagotchi.dir/clean:
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib && $(CMAKE_COMMAND) -P CMakeFiles/pico_tamagotchi.dir/cmake_clean.cmake
.PHONY : raylib/CMakeFiles/pico_tamagotchi.dir/clean

raylib/CMakeFiles/pico_tamagotchi.dir/depend:
	cd /Users/kadeangell/Documents/Tamagotchi/build_raylib && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kadeangell/Documents/Tamagotchi /Users/kadeangell/Documents/Tamagotchi/raylib /Users/kadeangell/Documents/Tamagotchi/build_raylib /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib /Users/kadeangell/Documents/Tamagotchi/build_raylib/raylib/CMakeFiles/pico_tamagotchi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : raylib/CMakeFiles/pico_tamagotchi.dir/depend
