# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build

# Include any dependencies generated for this target.
include CMakeFiles/my_game.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_game.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_game.dir/flags.make

CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o: ../Source/Components/PlayerController.cpp
CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o -MF CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o.d -o CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Components/PlayerController.cpp

CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Components/PlayerController.cpp > CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.i

CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Components/PlayerController.cpp -o CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.s

CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o: ../Source/GameObjects/Pong/Ball.cpp
CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o -MF CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o.d -o CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Pong/Ball.cpp

CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Pong/Ball.cpp > CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.i

CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Pong/Ball.cpp -o CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.s

CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o: ../Source/GameObjects/Pong/Paddle.cpp
CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o -MF CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o.d -o CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Pong/Paddle.cpp

CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Pong/Paddle.cpp > CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.i

CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Pong/Paddle.cpp -o CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.s

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o: ../Source/GameObjects/Shooter/Bullet.cpp
CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o -MF CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o.d -o CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/Bullet.cpp

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/Bullet.cpp > CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.i

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/Bullet.cpp -o CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.s

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o: ../Source/GameObjects/Shooter/Enemy.cpp
CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o -MF CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o.d -o CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/Enemy.cpp

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/Enemy.cpp > CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.i

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/Enemy.cpp -o CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.s

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o: ../Source/GameObjects/Shooter/PlayerShip.cpp
CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o -MF CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o.d -o CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/PlayerShip.cpp

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/PlayerShip.cpp > CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.i

CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/GameObjects/Shooter/PlayerShip.cpp -o CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.s

CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o: ../Source/Scenes/Pong/PongScene.cpp
CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o -MF CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o.d -o CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Scenes/Pong/PongScene.cpp

CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Scenes/Pong/PongScene.cpp > CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.i

CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Scenes/Pong/PongScene.cpp -o CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.s

CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o: ../Source/Scenes/Shooter/ShooterScene.cpp
CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o -MF CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o.d -o CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Scenes/Shooter/ShooterScene.cpp

CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Scenes/Shooter/ShooterScene.cpp > CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.i

CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/Scenes/Shooter/ShooterScene.cpp -o CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.s

CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o: CMakeFiles/my_game.dir/flags.make
CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o: ../Source/ShooterGameEntry.cpp
CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o: CMakeFiles/my_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o -MF CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o.d -o CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o -c /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/ShooterGameEntry.cpp

CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/ShooterGameEntry.cpp > CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.i

CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/Source/ShooterGameEntry.cpp -o CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.s

# Object files for target my_game
my_game_OBJECTS = \
"CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o" \
"CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o" \
"CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o" \
"CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o" \
"CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o" \
"CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o" \
"CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o" \
"CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o" \
"CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o"

# External object files for target my_game
my_game_EXTERNAL_OBJECTS =

my_game: CMakeFiles/my_game.dir/Source/Components/PlayerController.cpp.o
my_game: CMakeFiles/my_game.dir/Source/GameObjects/Pong/Ball.cpp.o
my_game: CMakeFiles/my_game.dir/Source/GameObjects/Pong/Paddle.cpp.o
my_game: CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Bullet.cpp.o
my_game: CMakeFiles/my_game.dir/Source/GameObjects/Shooter/Enemy.cpp.o
my_game: CMakeFiles/my_game.dir/Source/GameObjects/Shooter/PlayerShip.cpp.o
my_game: CMakeFiles/my_game.dir/Source/Scenes/Pong/PongScene.cpp.o
my_game: CMakeFiles/my_game.dir/Source/Scenes/Shooter/ShooterScene.cpp.o
my_game: CMakeFiles/my_game.dir/Source/ShooterGameEntry.cpp.o
my_game: CMakeFiles/my_game.dir/build.make
my_game: CMakeFiles/my_game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable my_game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_game.dir/build: my_game
.PHONY : CMakeFiles/my_game.dir/build

CMakeFiles/my_game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_game.dir/clean

CMakeFiles/my_game.dir/depend:
	cd /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build /home/ural/Documents/GitHub/ConsoleCraftEngine/CraftShooterGame/build/CMakeFiles/my_game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_game.dir/depend

