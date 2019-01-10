cmake_minimum_required(VERSION 2.8)

add_definitions(-fPIC -g)
set(SRCLIST src/cvector.c)

# Static Library Output
add_library(cvector STATIC ${SRCLIST})
target_include_directories(cvector PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
