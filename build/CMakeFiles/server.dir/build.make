# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build"

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/codegen:
.PHONY : CMakeFiles/server.dir/codegen

CMakeFiles/server.dir/BankBackend/src/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/BankBackend/src/server.cpp.o: /Users/ayaanmunshi/Desktop/Year\ 3/Semester\ 2/SE\ 3313/onlinebankingsystem/BankBackend/src/server.cpp
CMakeFiles/server.dir/BankBackend/src/server.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/BankBackend/src/server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/BankBackend/src/server.cpp.o -MF CMakeFiles/server.dir/BankBackend/src/server.cpp.o.d -o CMakeFiles/server.dir/BankBackend/src/server.cpp.o -c "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/server.cpp"

CMakeFiles/server.dir/BankBackend/src/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/BankBackend/src/server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/server.cpp" > CMakeFiles/server.dir/BankBackend/src/server.cpp.i

CMakeFiles/server.dir/BankBackend/src/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/BankBackend/src/server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/server.cpp" -o CMakeFiles/server.dir/BankBackend/src/server.cpp.s

CMakeFiles/server.dir/BankBackend/src/db.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/BankBackend/src/db.cpp.o: /Users/ayaanmunshi/Desktop/Year\ 3/Semester\ 2/SE\ 3313/onlinebankingsystem/BankBackend/src/db.cpp
CMakeFiles/server.dir/BankBackend/src/db.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/BankBackend/src/db.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/BankBackend/src/db.cpp.o -MF CMakeFiles/server.dir/BankBackend/src/db.cpp.o.d -o CMakeFiles/server.dir/BankBackend/src/db.cpp.o -c "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/db.cpp"

CMakeFiles/server.dir/BankBackend/src/db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/BankBackend/src/db.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/db.cpp" > CMakeFiles/server.dir/BankBackend/src/db.cpp.i

CMakeFiles/server.dir/BankBackend/src/db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/BankBackend/src/db.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/db.cpp" -o CMakeFiles/server.dir/BankBackend/src/db.cpp.s

CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o: /Users/ayaanmunshi/Desktop/Year\ 3/Semester\ 2/SE\ 3313/onlinebankingsystem/BankBackend/src/models/transaction.cpp
CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o -MF CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o.d -o CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o -c "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/models/transaction.cpp"

CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/models/transaction.cpp" > CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.i

CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/models/transaction.cpp" -o CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.s

CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o: /Users/ayaanmunshi/Desktop/Year\ 3/Semester\ 2/SE\ 3313/onlinebankingsystem/BankBackend/src/routes/handlers.cpp
CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o -MF CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o.d -o CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o -c "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/routes/handlers.cpp"

CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/routes/handlers.cpp" > CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.i

CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/BankBackend/src/routes/handlers.cpp" -o CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/BankBackend/src/server.cpp.o" \
"CMakeFiles/server.dir/BankBackend/src/db.cpp.o" \
"CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o" \
"CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/BankBackend/src/server.cpp.o
server: CMakeFiles/server.dir/BankBackend/src/db.cpp.o
server: CMakeFiles/server.dir/BankBackend/src/models/transaction.cpp.o
server: CMakeFiles/server.dir/BankBackend/src/routes/handlers.cpp.o
server: CMakeFiles/server.dir/build.make
server: /opt/homebrew/lib/libboost_system.dylib
server: /opt/homebrew/lib/libboost_thread.dylib
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem" "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem" "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build" "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build" "/Users/ayaanmunshi/Desktop/Year 3/Semester 2/SE 3313/onlinebankingsystem/build/CMakeFiles/server.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/server.dir/depend

