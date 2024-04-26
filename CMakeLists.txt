# Bump to version 3.8
cmake_minimum_required(VERSION 3.8)

project(ConsoleCraftEngine)

################################################################

# Option: CMake install prefix
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/Build" CACHE PATH "Default install prefix" FORCE)

# Option: Configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)

# Set the directory for the binaries
set(BIN_DIR ${PROJECT_SOURCE_DIR}/Bin/${CMAKE_BUILD_TYPE})

################################################################

# Define available platforms
set(PLATFORM_LIST "Windows" "Linux" "MacOS")

# Target platform
set(PLATFORM "Windows" CACHE STRING "Select the plaform")
set_property(CACHE PLATFORM PROPERTY STRINGS ${PLATFORM_LIST})

################################################################

# Define options for library type
set(ENGINE_LIBRARY_TYPE "STATIC" CACHE STRING "Type of Engine library: STATIC or SHARED")
set_property(CACHE ENGINE_LIBRARY_TYPE PROPERTY STRINGS STATIC SHARED)

################################################################

# Define available projects
set(PROJECT_LIST "Match" "Rogue" "Shooter")

# Enable/disable options for each project
foreach(PROJECT ${PROJECT_LIST})
  option(BUILD_${PROJECT} "Build ${PROJECT}" ON)
endforeach()

# Option: Startup project
set(STARTUP_PROJECT "Match" CACHE STRING "Select the startup project")
set_property(CACHE STARTUP_PROJECT PROPERTY STRINGS ${PROJECT_LIST})

################################################################

set(RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")

# Source
file(GLOB_RECURSE RUNTIME_HEADERS ${RUNTIME_DIR}/*.h)
file(GLOB_RECURSE RUNTIME_SOURCES ${RUNTIME_DIR}/*.cpp)

# Project
add_library(Engine ${ENGINE_LIBRARY_TYPE} ${RUNTIME_HEADERS} ${RUNTIME_SOURCES})

################################################################

if(${PLATFORM} STREQUAL "Windows")
  ##
elseif(${PLATFORM} STREQUAL "Linux")
  target_link_libraries(Engine PRIVATE Engine ncurses)
elseif(${PLATFORM} STREQUAL "MacOS")
  target_link_libraries(Engine PRIVATE Engine ncurses)
endif()


################################################################

# Check that our start up project is enabled
if(NOT BUILD_${STARTUP_PROJECT})
  message(FATAL_ERROR "Startup project ${STARTUP_PROJECT} is not enabled")
endif()

################################################################

# Set the output directory
set_target_properties(Engine PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)

# C++ version
target_compile_features(Engine PRIVATE cxx_std_20)

# Include directory
target_include_directories(Engine PUBLIC ${RUNTIME_DIR})

if(${ENGINE_LIBRARY_TYPE} STREQUAL SHARED)
    target_compile_definitions(Engine PRIVATE GE_SHARED)
    target_compile_definitions(Engine PRIVATE GE_BUILD_DLL)
endif()

# Group source and header files in IDE
source_group(
  TREE "${RUNTIME_DIR}"
  PREFIX "Header Files"
  FILES ${RUNTIME_HEADERS}
)

source_group(
  TREE "${RUNTIME_DIR}"
  PREFIX "Source Files"
  FILES ${RUNTIME_SOURCES}
)

################################################################

foreach(PROJECT ${PROJECT_LIST})
  if(BUILD_${PROJECT})
    set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Games/${PROJECT}/Source/")

    if(${ENGINE_LIBRARY_TYPE} STREQUAL SHARED)
        target_compile_definitions(Engine PRIVATE GE_SHARED)
    endif()

    # Source
    file(GLOB_RECURSE HEADERS ${PROJECT_DIR}/*.h)
    file(GLOB_RECURSE SOURCES ${PROJECT_DIR}/*.cpp)

    # Project
    add_executable(${PROJECT} ${SOURCES} ${HEADERS})

    # Set the output directory
    set_target_properties(${PROJECT} PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
      LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
      RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    )

    # C++ version
    target_compile_features(${PROJECT} PRIVATE cxx_std_20)

    # Include directory for Engine headers
    target_include_directories(${PROJECT} PUBLIC ${RUNTIME_DIR})
    target_include_directories(${PROJECT} PUBLIC ${PROJECT_DIR})

    # Link with Engine library
    target_link_libraries(${PROJECT} PRIVATE Engine)

    # Group source and header files in IDE
    source_group(
      TREE "${PROJECT_DIR}"
      PREFIX "Header Files"
      FILES ${HEADERS}
    )

    source_group(
      TREE "${PROJECT_DIR}"
      PREFIX "Source Files"
      FILES ${SOURCES}
    )

    # Set the startup project
    if(${PROJECT} STREQUAL ${STARTUP_PROJECT})
      set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT})
    endif()

  endif()
endforeach()
