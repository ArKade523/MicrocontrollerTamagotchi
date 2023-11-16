# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.12)

# Project name and C++ standard
project(microcontroller_tamagotchi)
set(CMAKE_CXX_STANDARD 17) 

# options for building the microcontroller version or the Raylib version
option(BUILD_MICROCONTROLLER "Build the microcontroller version" OFF)
option(BUILD_RAYLIB "Build the Raylib version" OFF)

# if (BUILD_MICROCONTROLLER)
#     message("Building the microcontroller version")
#     add_subdirectory(microcontroller)
# endif()

if(BUILD_RAYLIB)
    message("Building the Raylib version")
    add_subdirectory(raylib)
endif()