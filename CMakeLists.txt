cmake_minimum_required (VERSION 3.1)

project(OpenSLES-soft)

file(GLOB_RECURSE SLESWRAPPER_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_library(OpenSLES STATIC ${SLESWRAPPER_SOURCES})
target_include_directories(OpenSLES PUBLIC ${PROJECT_SOURCE_DIR}/src)