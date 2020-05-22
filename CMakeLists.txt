cmake_minimum_required (VERSION 3.17.2)
project (MOUNTAINS)

set(CMAKE_CXX_STANDARD 11)

# Suppress warnings of the deprecation of glut functions on macOS.
if(APPLE)
    add_definitions(-Wno-deprecated-declarations)
endif()

# Find the packages we need.
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Linux
# If not on macOS, we need glew.
if(UNIX AND NOT APPLE)
    find_package(GLEW REQUIRED)
endif()

# OPENGL_INCLUDE_DIR, GLUT_INCLUDE_DIR, OPENGL_LIBRARIES, and GLUT_LIBRARIES 
# are CMake built-in variables defined when the packages are found.
set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
set(LIBRARIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

# If not on macOS, add glew include directory and library path to lists.
if(UNIX AND NOT APPLE) 
    list(APPEND INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
    list(APPEND LIBRARIES ${GLEW_LIBRARIES})
endif()

# Add the list of include paths to be used to search for include files.
include_directories(${INCLUDE_DIRS})

file(GLOB MAIN
    src/main.cc
)

file(GLOB SOURCES
    src/mountain.*
)

file(GLOB TESTFILES
    test/*.h
    test/*.cc
)

include_directories (src, test)
add_subdirectory (src)
add_subdirectory (test)
