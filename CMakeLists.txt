# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(ConsoleCraftEngine)

# Source files
file(GLOB_RECURSE SOURCES
    Source/*.cpp
)

# Header files
file(GLOB_RECURSE HEADERS
    Source/*.h
)

# Library
add_library(ConsoleCraftEngine SHARED ${SOURCES} ${HEADERS})

# Include directory
target_include_directories(ConsoleCraftEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

