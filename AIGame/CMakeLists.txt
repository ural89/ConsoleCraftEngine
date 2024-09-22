cmake_minimum_required(VERSION 3.10)
project(AIGame)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE ENGINE_SOURCES ../Source/*.cpp)
file(GLOB_RECURSE ENGINE_HEADERS ../Source/*.h)


add_library(ConsoleCraftEngine SHARED ${ENGINE_SOURCES} )
file(GLOB_RECURSE GAME_SOURCES Source/*.cpp)
file(GLOB_RECURSE GAME_HEADERS Source/*.h)


link_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(AIGame ${GAME_SOURCES} ${GAME_HEADERS})
include_directories(Engine/Source/)
target_include_directories(AIGame PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/Source
${CMAKE_CURRENT_SOURCE_DIR}/../Source)


target_link_libraries(AIGame PUBLIC ConsoleCraftEngine ncurses)
