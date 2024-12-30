# ConsoleCraftEngine/CraftRogueGame/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(RogueGame)



# Source files
file(GLOB_RECURSE ENGINE_SOURCES
    ../Source/*.cpp
)

# Header files
file(GLOB_RECURSE ENGINE_HEADERS
    ../Source/*.h
)


file(GLOB_RECURSE GAME_SOURCES Source/*.cpp)
file(GLOB_RECURSE GAME_HEADERS Source/*.h)
# Executable
link_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(CraftRogue ${ENGINE_SOURCES} ${GAME_SOURCES} ${GAME_HEADERS} ${ENGINE_HEADERS})

# Include directory
target_include_directories(CraftRogue PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../ConsoleCraftEngine/Source
)

# Link with ConsoleCraftEngine library
target_link_libraries(CraftRogue PUBLIC  ncurses)

# Include directory
#target_include_directories(CraftRogue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

