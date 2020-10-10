cmake_minimum_required(VERSION 3.0)

project(visualizer CXX)

file(GLOB sources src/* include/*)

set(incl include)
set(flags -Wall -g -std=c++17)
set(libs -lX11 m)

# using vcpkg
if (NOT ${CMAKE_TOOLCHAIN_FILE} STREQUAL "")

    message(STATUS "Using vcpkg")

    find_package(SDL2 CONFIG REQUIRED)
    find_package(sdl2-image CONFIG REQUIRED)
    find_package(sdl2-ttf CONFIG REQUIRED)
    find_package(GLEW CONFIG REQUIRED)
    find_package(assimp CONFIG REQUIRED)
    find_package(Bullet CONFIG REQUIRED)

    set(libs
        ${libs}
        SDL2::SDL2
        SDL2::SDL2main
        SDL2::SDL2_image
	    SDL2::SDL2_ttf
        GLEW::GLEW
        assimp::assimp
        LinearMath
        Bullet3Common
        BulletDynamics
        BulletSoftBody
    )

else ()

    find_package(PkgConfig)

    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    #pkg_check_modules(CAIRO REQUIRED cairo)
    pkg_check_modules(GLEW REQUIRED glew)
    pkg_check_modules(ASSIMP REQUIRED assimp)

    set(incl
        ${incl}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
	    ${SDL2_TTF_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
        ${NLOHMANN_JSON_INCL}
        ${ASSIMP_INCLUDE_DIRS}
    )

    set(libs
        ${libs}
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
    	${SDL2_TTF_LIBRARIES}
	    ${GLEW_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        m
    )
endif()

file(GLOB assets assets/*)
file(COPY ${assets} DESTINATION ./assets)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE ${flags})
target_include_directories(${PROJECT_NAME} PRIVATE ${incl})
<<<<<<< Updated upstream
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
=======
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs})
>>>>>>> Stashed changes
