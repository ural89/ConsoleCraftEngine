# ConsoleCraftEngine/CraftRogueGame/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(RogueGame)



# Source files
file(GLOB_RECURSE ENGINE_SOURCES
    Source/*.cpp
)

# Header files
file(GLOB_RECURSE ENGINE_HEADERS
     Source/*.h
)



file(GLOB_RECURSE GAME_SOURCES CraftRogue/Source/*.cpp)
file(GLOB_RECURSE GAME_HEADERS CraftRogue/Source/*.h)
# Executable
link_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(CraftRogue ${GAME_SOURCES} ${GAME_HEADERS} ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Include directory
target_include_directories(CraftRogue PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Link with ConsoleCraftEngine library
target_link_libraries(CraftRogue PUBLIC  ncurses)

# Include directory
#target_include_directories(CraftRogue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

