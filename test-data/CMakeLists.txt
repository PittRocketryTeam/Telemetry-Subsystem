cmake_minimum_required(VERSION 3.0)

project(td)

file(GLOB sources *.cpp *.hpp)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -O2)
target_link_libraries(${PROJECT_NAME} PRIVATE m)
