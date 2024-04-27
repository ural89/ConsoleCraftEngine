cmake_minimum_required(VERSION 3.8)

project(ConsoleCraftEngine)

################################################################

# Needed to so VS exports a lib file with a DLL
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Option: CMake install prefix
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/Build" CACHE INTERNAL "Default install prefix" FORCE)

# Option: Configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE INTERNAL "Configurations" FORCE)

# Set the directory for the binaries
set(BIN_DIR ${PROJECT_SOURCE_DIR}/Bin/${CMAKE_BUILD_TYPE})

set(RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")

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

# Check that our start up project is enabled
if(NOT BUILD_${STARTUP_PROJECT})
  message(FATAL_ERROR "Startup project ${STARTUP_PROJECT} is not enabled")
endif()

################################################################

set(COMMON_COMPILE_OPTIONS "/Zc:__cplusplus")

# Set common functionality
function(apply_common_settings TARGET)
  #
  set_target_properties(${TARGET} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
  )

  # Set OS-specific definitions and libraries
  if(${PLATFORM} STREQUAL "Windows")
    target_compile_definitions(${TARGET} PRIVATE OS_WINDOWS)
  elseif(${PLATFORM} STREQUAL "Linux")
    target_compile_definitions(${TARGET} PRIVATE OS_LINUX)
    target_link_libraries(${TARGET} PRIVATE ncurses)
  elseif(${PLATFORM} STREQUAL "MacOS")
    target_compile_definitions(${TARGET} PRIVATE OS_MACOS)
    target_link_libraries(${TARGET} PRIVATE ncurses)
  endif()

  # Add debug flag for debug builds
  #target_compile_definitions(${TARGET} PRIVATE "<CONFIG:Debug:DEBUG_ENABLED>")
  
  target_compile_features(${TARGET} PRIVATE cxx_std_20)  
  target_compile_options(${TARGET} PRIVATE ${COMMON_COMPILE_OPTIONS})

endfunction()

################################################################

# Source
file(GLOB_RECURSE RUNTIME_HEADERS ${RUNTIME_DIR}/*.h)
file(GLOB_RECURSE RUNTIME_SOURCES ${RUNTIME_DIR}/*.cpp)

# Project
add_library(Engine ${ENGINE_LIBRARY_TYPE} ${RUNTIME_HEADERS} ${RUNTIME_SOURCES})

apply_common_settings(Engine)

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

    apply_common_settings(${PROJECT})

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
