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


file(GLOB_RECURSE GAME_SOURCES Source/*.cpp 
../Source/*.cpp
 )
file(GLOB_RECURSE GAME_HEADERS Source/*.h  ../Source/*.h)
# Executable
link_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(CraftRogue ${GAME_SOURCES} ${ENGINE_SOURCES} ${GAME_HEADERS})

# Include directory
target_include_directories(CraftRogue PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source #TODO this is not necessary
    ../Source )

# Link with library
target_link_libraries(CraftRogue PUBLIC ncurses)

# Include directory
#target_include_directories(CraftRogue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Install for the executable
install(TARGETS CraftRogue
    RUNTIME DESTINATION bin)

# Include directories for the installed package
install(DIRECTORY Source/
    DESTINATION include/CraftRogue
    FILES_MATCHING PATTERN "*.h")
set(CPACK_GENERATOR "DEB")  # Choose package formats
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK") #required
INCLUDE(CPack)
