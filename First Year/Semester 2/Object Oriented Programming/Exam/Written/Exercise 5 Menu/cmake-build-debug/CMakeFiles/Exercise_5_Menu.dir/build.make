# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Exercise_5_Menu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Exercise_5_Menu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Exercise_5_Menu.dir/flags.make

CMakeFiles/Exercise_5_Menu.dir/classes.cpp.obj: CMakeFiles/Exercise_5_Menu.dir/flags.make
CMakeFiles/Exercise_5_Menu.dir/classes.cpp.obj: CMakeFiles/Exercise_5_Menu.dir/includes_CXX.rsp
CMakeFiles/Exercise_5_Menu.dir/classes.cpp.obj: ../classes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Exercise_5_Menu.dir/classes.cpp.obj"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Exercise_5_Menu.dir\classes.cpp.obj -c "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\classes.cpp"

CMakeFiles/Exercise_5_Menu.dir/classes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Exercise_5_Menu.dir/classes.cpp.i"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\classes.cpp" > CMakeFiles\Exercise_5_Menu.dir\classes.cpp.i

CMakeFiles/Exercise_5_Menu.dir/classes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Exercise_5_Menu.dir/classes.cpp.s"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\classes.cpp" -o CMakeFiles\Exercise_5_Menu.dir\classes.cpp.s

CMakeFiles/Exercise_5_Menu.dir/main.cpp.obj: CMakeFiles/Exercise_5_Menu.dir/flags.make
CMakeFiles/Exercise_5_Menu.dir/main.cpp.obj: CMakeFiles/Exercise_5_Menu.dir/includes_CXX.rsp
CMakeFiles/Exercise_5_Menu.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Exercise_5_Menu.dir/main.cpp.obj"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Exercise_5_Menu.dir\main.cpp.obj -c "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\main.cpp"

CMakeFiles/Exercise_5_Menu.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Exercise_5_Menu.dir/main.cpp.i"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\main.cpp" > CMakeFiles\Exercise_5_Menu.dir\main.cpp.i

CMakeFiles/Exercise_5_Menu.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Exercise_5_Menu.dir/main.cpp.s"
	C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\main.cpp" -o CMakeFiles\Exercise_5_Menu.dir\main.cpp.s

# Object files for target Exercise_5_Menu
Exercise_5_Menu_OBJECTS = \
"CMakeFiles/Exercise_5_Menu.dir/classes.cpp.obj" \
"CMakeFiles/Exercise_5_Menu.dir/main.cpp.obj"

# External object files for target Exercise_5_Menu
Exercise_5_Menu_EXTERNAL_OBJECTS =

Exercise_5_Menu.exe: CMakeFiles/Exercise_5_Menu.dir/classes.cpp.obj
Exercise_5_Menu.exe: CMakeFiles/Exercise_5_Menu.dir/main.cpp.obj
Exercise_5_Menu.exe: CMakeFiles/Exercise_5_Menu.dir/build.make
Exercise_5_Menu.exe: CMakeFiles/Exercise_5_Menu.dir/linklibs.rsp
Exercise_5_Menu.exe: CMakeFiles/Exercise_5_Menu.dir/objects1.rsp
Exercise_5_Menu.exe: CMakeFiles/Exercise_5_Menu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Exercise_5_Menu.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Exercise_5_Menu.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Exercise_5_Menu.dir/build: Exercise_5_Menu.exe

.PHONY : CMakeFiles/Exercise_5_Menu.dir/build

CMakeFiles/Exercise_5_Menu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Exercise_5_Menu.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Exercise_5_Menu.dir/clean

CMakeFiles/Exercise_5_Menu.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu" "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu" "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\cmake-build-debug" "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\cmake-build-debug" "D:\Desktop Folders\Facultate\Sem 2\Object Oriented Programming\Exam\Written\Exercise 5 Menu\cmake-build-debug\CMakeFiles\Exercise_5_Menu.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Exercise_5_Menu.dir/depend

