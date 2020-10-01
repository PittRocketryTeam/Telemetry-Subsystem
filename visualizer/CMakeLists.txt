cmake_minimum_required(VERSION 3.0)

project(visualizer CXX)

file(GLOB sources src/* include/*)

set(incl include)
set(flags -Wall -g -std=c++17)
set(libs -lX11 m)

find_package(PkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(ASSIMP REQUIRED assimp)

find_path(BOOST_INCL boost)
find_path(GLM_INCL glm)
find_path(JSON_INCL nlohmann)

set(incl
    ${incl}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
    ${GLM_INCL}
    ${JSON_INCL}
)

set(libs
    ${libs}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${ASSIMP_LIBRARIES} 
)

file(GLOB assets assets/*)
file(COPY ${assets} DESTINATION ./assets)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE ${flags})
target_include_directories(${PROJECT_NAME} PRIVATE ${incl})
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs})   

if (${BUILD_EXAMPLES})

file(GLOB exsrcs ./examples/src/* ./examples/include/*)

list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set(exname examples)

add_executable(${exname} ${sources} ${exsrcs})
target_compile_options(${exname} PRIVATE ${flags})
target_include_directories(${exname} PRIVATE ${incl} ../include)
target_link_libraries(${exname} PRIVATE ${libs})

endif()