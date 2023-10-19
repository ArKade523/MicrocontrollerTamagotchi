# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.12)

# Project name and C++ standard
project(pico_tamagotchi)
set(CMAKE_CXX_STANDARD 17)  # or whatever C++ standard you'd like to useo

# options for building the pico version or the Raylib version
option(BUILD_PICO "Build the Pico version" OFF)
option(BUILD_RAYLIB "Build the Raylib version" OFF)

if (BUILD_PICO)
    message("Building the Pico version")
    add_subdirectory(pico)
endif()

if(BUILD_RAYLIB)
    message("Building the Raylib version")
    add_subdirectory(raylib)
endif()