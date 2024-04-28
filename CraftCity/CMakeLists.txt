# ConsoleCraftEngine/CraftCity/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(CraftCity)
set(CMAKE_BUILD_TYPE Debug)


# Source files
file(GLOB_RECURSE ENGINE_SOURCES
    ../Source/*.cpp
)

# Header files
file(GLOB_RECURSE ENGINE_HEADERS
    ../Source/*.h
)
add_library(ConsoleCraftEnginePrivate SHARED ${ENGINE_SOURCES} )


file(GLOB_RECURSE GAME_SOURCES Source/*.cpp)
file(GLOB_RECURSE GAME_HEADERS Source/*.h)
# Executable
link_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(CraftCity ${GAME_SOURCES} ${GAME_HEADERS})

# Include directory
target_include_directories(CraftCity PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source #TODO this is not necessary
    ../Source )

# Link with ConsoleCraftEngine library
target_link_libraries(CraftCity PUBLIC ConsoleCraftEnginePrivate ncurses)

# Include directory
#target_include_directories(CraftCity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

