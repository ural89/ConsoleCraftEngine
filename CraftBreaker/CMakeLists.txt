# ConsoleCraftEngine/CraftBreaker/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(CraftBreaker)



# Source files
file(GLOB_RECURSE ENGINE_SOURCES
    ../Source/*.cpp
)

# Header files
file(GLOB_RECURSE ENGINE_HEADERS
    ../Source/*.h
)
add_library(ConsoleCraftEngine SHARED ${ENGINE_SOURCES} )


file(GLOB_RECURSE GAME_SOURCES Source/*.cpp)
file(GLOB_RECURSE GAME_HEADERS Source/*.h)
# Executable
link_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(CraftBreaker ${GAME_SOURCES} )

# Include directory
target_include_directories(CraftBreaker PUBLIC
    #${CMAKE_CURRENT_SOURCE_DIR}/Source #TODO this is not necessary
    ${CMAKE_CURRENT_SOURCE_DIR}/../../ConsoleCraftEngine/Source )

# Link with ConsoleCraftEngine library
target_link_libraries(CraftBreaker PUBLIC ConsoleCraftEngine ncurses)

# Include directory
#target_include_directories(CraftBreaker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

