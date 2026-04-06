cmake_minimum_required(VERSION 3.16)
project(SpaceInvaders LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RAYLIB_INCLUDE_DIR "" CACHE PATH "Path to the raylib include directory")
set(RAYLIB_LIBRARY "" CACHE FILEPATH "Path to the raylib library file (libraylib.a)")

if (NOT RAYLIB_INCLUDE_DIR)
    find_path(RAYLIB_INCLUDE_DIR raylib.h
        PATHS
            "C:/raylib/raylib/src"
            "C:/raylib/include"
    )
endif()

if (NOT RAYLIB_LIBRARY)
    find_library(RAYLIB_LIBRARY NAMES raylib
        PATHS
            "C:/raylib/raylib/src"
            "C:/raylib/lib"
    )
endif()

if (NOT RAYLIB_INCLUDE_DIR OR NOT RAYLIB_LIBRARY)
    message(FATAL_ERROR "Could not locate raylib. Set RAYLIB_INCLUDE_DIR and RAYLIB_LIBRARY to the MinGW raylib install paths.")
endif()

add_executable(SpaceInvaders
    src/game.cpp
    src/space_invaders.cpp
    src/spaceship.cpp
    src/lasers.cpp
    src/block.cpp
    src/obstacle.cpp
)

target_include_directories(SpaceInvaders PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${RAYLIB_INCLUDE_DIR}
)

target_compile_definitions(SpaceInvaders PRIVATE _UCRT)

target_link_libraries(SpaceInvaders PRIVATE
    ${RAYLIB_LIBRARY}
    winmm
    opengl32
    gdi32
    shell32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
)
