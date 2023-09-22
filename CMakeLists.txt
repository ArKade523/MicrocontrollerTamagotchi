# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.12)

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Project name and C++ standard
project(pico_tamagotchi)
set(CMAKE_CXX_STANDARD 17)  # or whatever C++ standard you'd like to use

# Initialize the Pico SDK
pico_sdk_init()

# Add all your files here
add_executable(pico_tamagotchi
    main.cpp
    Tamagotchi.cpp
    Display.hpp  # Header-only files can be included here as well to show up in IDEs
)

# Enable stdio over USB and disable stdio over UART
pico_enable_stdio_usb(pico_tamagotchi 1)
pico_enable_stdio_uart(pico_tamagotchi 0)

# Generate additional output formats (.hex, .uf2, etc.)
pico_add_extra_outputs(pico_tamagotchi)

# Link the required libraries
target_link_libraries(pico_tamagotchi pico_stdlib hardware_i2c)
