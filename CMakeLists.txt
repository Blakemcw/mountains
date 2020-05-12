cmake_minimum_required (VERSION 3.17.2)
project (MOUNTAINS)

set(CMAKE_CXX_STANDARD 11)

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
