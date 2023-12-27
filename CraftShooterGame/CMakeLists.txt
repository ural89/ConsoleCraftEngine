# ConsoleCraftEngine/CraftShooterGame/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(CraftShooterGame)

# Source files
file(GLOB_RECURSE SOURCES
    Source/*.cpp
)

# Header files
file(GLOB_RECURSE HEADERS
    Source/*.h
)



# Executable
add_executable(my_game ${SOURCES} ${HEADERS})

# Include directory
target_include_directories(my_game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
    ${CMAKE_CURRENT_SOURCE_DIR}/../../ConsoleCraftEngine/Source  # Adjust the path accordingly
)
# Link with ConsoleCraftEngine library
target_link_libraries(my_game PUBLIC ConsoleCraftEngine ncurses)

# Include directory
target_include_directories(my_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

