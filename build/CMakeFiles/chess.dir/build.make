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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zsyuung/kaohe5_final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zsyuung/kaohe5_final/build

# Include any dependencies generated for this target.
include CMakeFiles/chess.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess.dir/flags.make

CMakeFiles/chess.dir/main.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chess.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/main.cpp.o -c /home/zsyuung/kaohe5_final/main.cpp

CMakeFiles/chess.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/main.cpp > CMakeFiles/chess.dir/main.cpp.i

CMakeFiles/chess.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/main.cpp -o CMakeFiles/chess.dir/main.cpp.s

CMakeFiles/chess.dir/protodir/chess.pb.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/protodir/chess.pb.cpp.o: ../protodir/chess.pb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/chess.dir/protodir/chess.pb.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/protodir/chess.pb.cpp.o -c /home/zsyuung/kaohe5_final/protodir/chess.pb.cpp

CMakeFiles/chess.dir/protodir/chess.pb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/protodir/chess.pb.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/protodir/chess.pb.cpp > CMakeFiles/chess.dir/protodir/chess.pb.cpp.i

CMakeFiles/chess.dir/protodir/chess.pb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/protodir/chess.pb.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/protodir/chess.pb.cpp -o CMakeFiles/chess.dir/protodir/chess.pb.cpp.s

CMakeFiles/chess.dir/events/events.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/events/events.cpp.o: ../events/events.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/chess.dir/events/events.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/events/events.cpp.o -c /home/zsyuung/kaohe5_final/events/events.cpp

CMakeFiles/chess.dir/events/events.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/events/events.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/events/events.cpp > CMakeFiles/chess.dir/events/events.cpp.i

CMakeFiles/chess.dir/events/events.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/events/events.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/events/events.cpp -o CMakeFiles/chess.dir/events/events.cpp.s

CMakeFiles/chess.dir/events/eventtype.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/events/eventtype.cpp.o: ../events/eventtype.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/chess.dir/events/eventtype.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/events/eventtype.cpp.o -c /home/zsyuung/kaohe5_final/events/eventtype.cpp

CMakeFiles/chess.dir/events/eventtype.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/events/eventtype.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/events/eventtype.cpp > CMakeFiles/chess.dir/events/eventtype.cpp.i

CMakeFiles/chess.dir/events/eventtype.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/events/eventtype.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/events/eventtype.cpp -o CMakeFiles/chess.dir/events/eventtype.cpp.s

CMakeFiles/chess.dir/handlers/chess_handler.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/handlers/chess_handler.cpp.o: ../handlers/chess_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/chess.dir/handlers/chess_handler.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/handlers/chess_handler.cpp.o -c /home/zsyuung/kaohe5_final/handlers/chess_handler.cpp

CMakeFiles/chess.dir/handlers/chess_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/handlers/chess_handler.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/handlers/chess_handler.cpp > CMakeFiles/chess.dir/handlers/chess_handler.cpp.i

CMakeFiles/chess.dir/handlers/chess_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/handlers/chess_handler.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/handlers/chess_handler.cpp -o CMakeFiles/chess.dir/handlers/chess_handler.cpp.s

CMakeFiles/chess.dir/handlers/handlers.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/handlers/handlers.cpp.o: ../handlers/handlers.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/chess.dir/handlers/handlers.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/handlers/handlers.cpp.o -c /home/zsyuung/kaohe5_final/handlers/handlers.cpp

CMakeFiles/chess.dir/handlers/handlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/handlers/handlers.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/handlers/handlers.cpp > CMakeFiles/chess.dir/handlers/handlers.cpp.i

CMakeFiles/chess.dir/handlers/handlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/handlers/handlers.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/handlers/handlers.cpp -o CMakeFiles/chess.dir/handlers/handlers.cpp.s

CMakeFiles/chess.dir/threadpool/thread_cond.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/threadpool/thread_cond.cpp.o: ../threadpool/thread_cond.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/chess.dir/threadpool/thread_cond.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/threadpool/thread_cond.cpp.o -c /home/zsyuung/kaohe5_final/threadpool/thread_cond.cpp

CMakeFiles/chess.dir/threadpool/thread_cond.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/threadpool/thread_cond.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/threadpool/thread_cond.cpp > CMakeFiles/chess.dir/threadpool/thread_cond.cpp.i

CMakeFiles/chess.dir/threadpool/thread_cond.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/threadpool/thread_cond.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/threadpool/thread_cond.cpp -o CMakeFiles/chess.dir/threadpool/thread_cond.cpp.s

CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.o: ../threadpool/thread_mutex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.o -c /home/zsyuung/kaohe5_final/threadpool/thread_mutex.cpp

CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/threadpool/thread_mutex.cpp > CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.i

CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/threadpool/thread_mutex.cpp -o CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.s

CMakeFiles/chess.dir/threadpool/thread_pool.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/threadpool/thread_pool.cpp.o: ../threadpool/thread_pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/chess.dir/threadpool/thread_pool.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/threadpool/thread_pool.cpp.o -c /home/zsyuung/kaohe5_final/threadpool/thread_pool.cpp

CMakeFiles/chess.dir/threadpool/thread_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/threadpool/thread_pool.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/threadpool/thread_pool.cpp > CMakeFiles/chess.dir/threadpool/thread_pool.cpp.i

CMakeFiles/chess.dir/threadpool/thread_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/threadpool/thread_pool.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/threadpool/thread_pool.cpp -o CMakeFiles/chess.dir/threadpool/thread_pool.cpp.s

CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.o: ../dispatchmsgserver/dispatchmsgserver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.o -c /home/zsyuung/kaohe5_final/dispatchmsgserver/dispatchmsgserver.cpp

CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/dispatchmsgserver/dispatchmsgserver.cpp > CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.i

CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/dispatchmsgserver/dispatchmsgserver.cpp -o CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.s

CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.o: ../networkinterface/networkinterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.o -c /home/zsyuung/kaohe5_final/networkinterface/networkinterface.cpp

CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/networkinterface/networkinterface.cpp > CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.i

CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/networkinterface/networkinterface.cpp -o CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.s

CMakeFiles/chess.dir/configset/iniconfig.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/configset/iniconfig.cpp.o: ../configset/iniconfig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/chess.dir/configset/iniconfig.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/configset/iniconfig.cpp.o -c /home/zsyuung/kaohe5_final/configset/iniconfig.cpp

CMakeFiles/chess.dir/configset/iniconfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/configset/iniconfig.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/configset/iniconfig.cpp > CMakeFiles/chess.dir/configset/iniconfig.cpp.i

CMakeFiles/chess.dir/configset/iniconfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/configset/iniconfig.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/configset/iniconfig.cpp -o CMakeFiles/chess.dir/configset/iniconfig.cpp.s

CMakeFiles/chess.dir/test/test.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/test/test.cpp.o: ../test/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/chess.dir/test/test.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/test/test.cpp.o -c /home/zsyuung/kaohe5_final/test/test.cpp

CMakeFiles/chess.dir/test/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/test/test.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsyuung/kaohe5_final/test/test.cpp > CMakeFiles/chess.dir/test/test.cpp.i

CMakeFiles/chess.dir/test/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/test/test.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsyuung/kaohe5_final/test/test.cpp -o CMakeFiles/chess.dir/test/test.cpp.s

# Object files for target chess
chess_OBJECTS = \
"CMakeFiles/chess.dir/main.cpp.o" \
"CMakeFiles/chess.dir/protodir/chess.pb.cpp.o" \
"CMakeFiles/chess.dir/events/events.cpp.o" \
"CMakeFiles/chess.dir/events/eventtype.cpp.o" \
"CMakeFiles/chess.dir/handlers/chess_handler.cpp.o" \
"CMakeFiles/chess.dir/handlers/handlers.cpp.o" \
"CMakeFiles/chess.dir/threadpool/thread_cond.cpp.o" \
"CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.o" \
"CMakeFiles/chess.dir/threadpool/thread_pool.cpp.o" \
"CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.o" \
"CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.o" \
"CMakeFiles/chess.dir/configset/iniconfig.cpp.o" \
"CMakeFiles/chess.dir/test/test.cpp.o"

# External object files for target chess
chess_EXTERNAL_OBJECTS =

chess: CMakeFiles/chess.dir/main.cpp.o
chess: CMakeFiles/chess.dir/protodir/chess.pb.cpp.o
chess: CMakeFiles/chess.dir/events/events.cpp.o
chess: CMakeFiles/chess.dir/events/eventtype.cpp.o
chess: CMakeFiles/chess.dir/handlers/chess_handler.cpp.o
chess: CMakeFiles/chess.dir/handlers/handlers.cpp.o
chess: CMakeFiles/chess.dir/threadpool/thread_cond.cpp.o
chess: CMakeFiles/chess.dir/threadpool/thread_mutex.cpp.o
chess: CMakeFiles/chess.dir/threadpool/thread_pool.cpp.o
chess: CMakeFiles/chess.dir/dispatchmsgserver/dispatchmsgserver.cpp.o
chess: CMakeFiles/chess.dir/networkinterface/networkinterface.cpp.o
chess: CMakeFiles/chess.dir/configset/iniconfig.cpp.o
chess: CMakeFiles/chess.dir/test/test.cpp.o
chess: CMakeFiles/chess.dir/build.make
chess: CMakeFiles/chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zsyuung/kaohe5_final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable chess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess.dir/build: chess

.PHONY : CMakeFiles/chess.dir/build

CMakeFiles/chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chess.dir/clean

CMakeFiles/chess.dir/depend:
	cd /home/zsyuung/kaohe5_final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zsyuung/kaohe5_final /home/zsyuung/kaohe5_final /home/zsyuung/kaohe5_final/build /home/zsyuung/kaohe5_final/build /home/zsyuung/kaohe5_final/build/CMakeFiles/chess.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chess.dir/depend

