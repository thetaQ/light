cmake_minimum_required(VERSION 2.8)

add_definitions(-fPIC -g)
set(SRCLIST src/lhset.c)

# Static Library Output
add_library(lhset STATIC ${SRCLIST})
target_include_directories(lhset PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
