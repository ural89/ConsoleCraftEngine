# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(my_library)

# Source files
file(GLOB_RECURSE SOURCES
    Source/*.cpp
)

# Header files
file(GLOB_RECURSE HEADERS
    Source/*.h
)

# Library
add_library(my_library SHARED ${SOURCES} ${HEADERS})

# Include directory
target_include_directories(my_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

