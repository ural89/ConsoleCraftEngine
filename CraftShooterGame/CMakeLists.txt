cmake_minimum_required(VERSION 3.10)
project(CraftShooterGame)

# Add all .cpp and .h files in the source directory
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp" "Source/*.h")

# Add the shared library
add_library(my_library SHARED ${SOURCE_FILES})

# Add the include directories
target_include_directories(my_library PUBLIC include)

# Add your game executable
add_executable(CraftShooterGame ${SOURCE_FILES})

# Link against your shared library
target_link_libraries(CraftShooterGame my_library)

