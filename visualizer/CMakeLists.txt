cmake_minimum_required(VERSION 3.0)

project(visualizer CXX)

file(GLOB sources src/* include/*)
set(incl include)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall)
target_include_directories(${PROJECT_NAME} PRIVATE ${incl})